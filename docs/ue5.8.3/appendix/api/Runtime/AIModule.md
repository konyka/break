# Runtime / AIModule

- module root: `Source/Runtime/AIModule`
- headers: 195; symbols: 5931
- symbol kinds: class=193, delegate=62, enum=104, enumerator=311, externvar=9, function=1012, macro=36, member=1549, namespace=87, prototype=2237, struct=212, typedef=74, union=1, variable=44
- PrivateDependencyModuleNames: AITestSuite, AutoRTFM, EditorFramework, InputCore, Navmesh, RHI, RenderCore, SlateCore, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, Engine, GameplayTags, GameplayTasks, NavigationSystem

### `Source/Runtime/AIModule/Classes/AIController.h` (Public)


#### struct `FFocusKnowledge`  
`struct FFocusKnowledge`  
_L58-73_
- L72 _public member_ `TArray<FFocusItem> Priorities;`

#### struct `FFocusKnowledge::FFocusItem`  
`struct FFocusItem`  
_L60-70_
- L62 _public member_ `TWeakObjectPtr<AActor> Actor;`
- L63 _public member_ `FVector Position;`
- L65 _public function_ `FFocusItem()`

#### class `AAIController`  
`class AAIController : public AController, public IAIPerceptionListenerInterface, public IGameplayTaskOwnerInterface, public IGenericTeamAgentInterface, public IVisualLoggerDebugSnapshotInterface`  
_L87-458_
- reflection: `UCLASS(ClassGroup = AI, BlueprintType, Blueprintable, MinimalAPI)`
- inherits: `AController,IAIPerceptionListenerInterface,IGameplayTaskOwnerInterface,IGenericTeamAgentInterface,IVisualLoggerDebugSnapshotInterface`
- L91 _private member_ `FGameplayResourceSet ScriptClaimedResources;`
- L93 _protected member_ `FFocusKnowledge FocusInformation;`
- L98 _protected member_ `uint32 bStartAILogicOnPossess : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)` — By default AI's logic does not start when controlled Pawn is possessed. Setting this flag to true will make AI logic start when pawn is possessed
- L103 _protected member_ `uint32 bStopAILogicOnUnposses : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)` — By default AI's logic gets stopped when controlled Pawn is unpossessed. Setting this flag to false will make AI logic persist past losing control over a pawn
- L108 _public member_ `mutable uint32 bLOSflag : 1;` — `UPROPERTY()` — used for alternating LineOfSight traces
- L112 _public member_ `uint32 bSkipExtraLOSChecks : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)` — Skip extra line of sight traces to extremities of target being checked.
- L116 _public member_ `uint32 bAllowStrafe : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)` — Is strafing allowed during movement?
- L120 _public member_ `uint32 bWantsPlayerState : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)` — Specifies if this AI wants its own PlayerState.
- L124 _public member_ `uint32 bSetControlRotationFromPawnOrientation:1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)` — Copy Pawn rotation to ControlRotation, if there is no focus point.
- L128 _public member_ `uint32 bSkipRootComponentUpdate:1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)` — If true, the RootComponent's transform will not be updated when SetControlRotation() is called.
- L134 _private member_ `TObjectPtr<UPathFollowingComponent> PathFollowingComponent;` — `UPROPERTY(VisibleDefaultsOnly, Category = AI)` — Component used for moving along a path.
- L140 _public member_ `TObjectPtr<UBrainComponent> BrainComponent;` — `UPROPERTY(BlueprintReadWrite, Category = AI)` — Component responsible for behaviors.
- L143 _public member_ `TObjectPtr<UAIPerceptionComponent> PerceptionComponent;` — `UPROPERTY(VisibleDefaultsOnly, Category = AI)`
- L148 _protected member_ `TObjectPtr<UBlackboardComponent> Blackboard;` — `UPROPERTY(BlueprintReadOnly, Category = AI, meta = (AllowPrivateAccess = "true"))` — blackboard
- L151 _protected member_ `TObjectPtr<UGameplayTasksComponent> CachedGameplayTasksComponent;` — `UPROPERTY()`
- L154 _protected member_ `TSubclassOf<UNavigationQueryFilter> DefaultNavigationFilterClass;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)`
- L158 _public prototype_ `AAIController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L160 _public prototype_ `virtual void SetPawn(APawn* InPawn) override;`
- L172 _public prototype_ `EPathFollowingRequestResult::Type MoveToActor(AActor* Goal, float AcceptanceRadius = -1, bool bStopOnOverlap = true, bool bUsePathfinding = true, bool bCanStrafe = true, TSubclassOf<UNavigationQueryFilter> FilterClass = {}, bool bAllowPartialPath = true);` — `UFUNCTION(BlueprintCallable, Category = "AI|Navigation", Meta = (AdvancedDisplay = "bStopOnOverlap,bCanStrafe,bAllowPartialPath"))` — Makes AI go toward specified Goal actor (destination will be continuously updated), aborts any active path following @param AcceptanceRadius - finish move if pawn gets close enough @param bStopOnOverlap - add pawn's radius to AcceptanceRadius @param bUsePathfinding - use navigation data to calculate path (otherwise it will go in straight line) @param bCanStrafe - set focus related flag: bAllowStrafe @param FilterClass - navigation filter for pathfinding adjustments. If none specified DefaultNavigationFilterClass will be used @param bAllowPartialPath - use incomplete path when goal can't be reached @note AcceptanceRadius has default value or -1 due to Header Parser not being able to recognize UPathFollowingComponent::DefaultAcceptanceRadius
- L187 _public prototype_ `EPathFollowingRequestResult::Type MoveToLocation(const FVector& Dest, float AcceptanceRadius = -1, bool bStopOnOverlap = true, bool bUsePathfinding = true, bool bProjectDestinationToNavigation = false, bool bCanStrafe = true, TSubclassOf<UNavigationQueryFilter> FilterClass = {}, bool bAllowPartialPath = true);` — `UFUNCTION(BlueprintCallable, Category = "AI|Navigation", Meta = (AdvancedDisplay = "bStopOnOverlap,bCanStrafe,bAllowPartialPath"))` — Makes AI go toward specified Dest location, aborts any active path following @param AcceptanceRadius - finish move if pawn gets close enough @param bStopOnOverlap - add pawn's radius to AcceptanceRadius @param bUsePathfinding - use navigation data to calculate path (otherwise it will go in straight line) @param bProjectDestinationToNavigation - project location on navigation data before using it @param bCanStrafe - set focus related flag: bAllowStrafe @param FilterClass - navigation filter for pathfinding adjustments. If none specified DefaultNavigationFilterClass will be used @param bAllowPartialPath - use incomplete path when goal can't be reached @note AcceptanceRadius has default value or -1 due to Header Parser not being able to recognize UPathFollowingComponent::DefaultAcceptanceRadius
- L196 _public prototype_ `virtual FPathFollowingRequestResult MoveTo(const FAIMoveRequest& MoveRequest, FNavPathSharedPtr* OutPath = nullptr);` — Makes AI go toward specified destination @param MoveRequest - details about move @param OutPath - optional output param, filled in with assigned path @return struct holding MoveId and enum code
- L199 _public prototype_ `virtual FAIRequestID RequestMove(const FAIMoveRequest& MoveRequest, FNavPathSharedPtr Path);` — Passes move request and path object to path following
- L206 _public prototype_ `virtual void FindPathForMoveRequest(const FAIMoveRequest& MoveRequest, FPathFindingQuery& Query, FNavPathSharedPtr& OutPath) const;` — Finds path for given move request @param MoveRequest - details about move @param Query - pathfinding query for navigation system @param OutPath - generated path
- L209 _public prototype_ `bool BuildPathfindingQuery(const FAIMoveRequest& MoveRequest, FPathFindingQuery& OutQuery) const;` — Helper function for creating pathfinding query for this agent from move request data
- L212 _public prototype_ `bool BuildPathfindingQuery(const FAIMoveRequest& MoveRequest, const FVector& StartLocation, FPathFindingQuery& OutQuery) const;` — Helper function for creating pathfinding query for this agent from move request data and starting location
- L215 _public prototype_ `virtual bool PreparePathfinding(const FAIMoveRequest& MoveRequest, FPathFindingQuery& Query);` — `UE_DEPRECATED_FORGAME(4.13, "This function is now deprecated, please use FindPathForMoveRequest() for adjusting Query or BuildPathfindingQuery() for getting one.")`
- L218 _public prototype_ `virtual FAIRequestID RequestPathAndMove(const FAIMoveRequest& MoveRequest, FPathFindingQuery& Query);` — `UE_DEPRECATED_FORGAME(4.13, "This function is now deprecated, please use FindPathForMoveRequest() for adjusting pathfinding or path postprocess.")`
- L221 _public prototype_ `bool PauseMove(FAIRequestID RequestToPause);` — if AI is currently moving due to request given by RequestToPause, then the move will be paused
- L224 _public prototype_ `bool ResumeMove(FAIRequestID RequestToResume);` — resumes last AI-performed, paused request provided it's ID was equivalent to RequestToResume
- L227 _public prototype_ `virtual void StopMovement() override;` — Aborts the move the controller is currently performing
- L230 _public prototype_ `virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result);` — Called on completing current movement request
- L233 _public prototype_ `virtual void OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result);` — `UE_DEPRECATED_FORGAME(4.13, "This function is now deprecated, please use version with EPathFollowingResultDetails parameter.")`
- L236 _public prototype_ `FAIRequestID GetCurrentMoveRequestID() const;` — Returns the Move Request ID for the current move
- L240 _public member_ `FAIMoveCompletedSignature ReceiveMoveCompleted;` — `UPROPERTY(BlueprintAssignable, meta = (DisplayName = "MoveCompleted"))` — Blueprint notification that we've completed the current movement request
- L242 _public function_ `TSubclassOf<UNavigationQueryFilter> GetDefaultNavigationFilterClass() const`
- L246 _public prototype_ `EPathFollowingStatus::Type GetMoveStatus() const;` — `UFUNCTION(BlueprintCallable, Category = "AI|Navigation")` — Returns status of path following
- L250 _public prototype_ `bool HasPartialPath() const;` — `UFUNCTION(BlueprintCallable, Category = "AI|Navigation")` — Returns true if the current PathFollowingComponent's path is partial (does not reach desired destination).
- L254 _public prototype_ `FVector GetImmediateMoveDestination() const;` — `UFUNCTION(BlueprintCallable, Category = "AI|Navigation")` — Returns position of current path segment's end.
- L258 _public prototype_ `void SetMoveBlockDetection(bool bEnable);` — `UFUNCTION(BlueprintCallable, Category = "AI|Navigation")` — Updates state of movement block detection.
- L262 _public prototype_ `virtual bool RunBehaviorTree(UBehaviorTree* BTAsset);` — `UFUNCTION(BlueprintCallable, Category = "AI")` — Starts executing behavior tree.
- L266 _public prototype_ `virtual void SetControlRotation(const FRotator& NewRotation) override;` — Set the control rotation. The RootComponent's rotation will also be updated to match if bSkipRootComponentUpdate is false and RootComponent->bAbsoluteRotation is true.
- L269 _protected prototype_ `virtual void CleanupBrainComponent();`
- L272 _protected prototype_ `virtual void MergePaths(const FNavPathSharedPtr& InitialPath, FNavPathSharedPtr& InOutMergedPath) const;` — Merges the remaining points of InitialPath, with the points of InOutMergedPath. The resulting merged path is outputted into InOutMergedPath.
- L282 _public prototype_ `bool UseBlackboard(UBlackboardData* BlackboardAsset, UBlackboardComponent*& BlackboardComponent);` — `UFUNCTION(BlueprintCallable, Category = "AI")` — Makes AI use the specified Blackboard asset & creates a Blackboard Component if one does not already exist. @param	BlackboardAsset			The Blackboard asset to use. @param	BlackboardComponent		The Blackboard component that was used or created to work with the passed-in Blackboard Asset. @return true if we successfully linked the blackboard asset to the blackboard component.
- L285 _public prototype_ `virtual bool ShouldSyncBlackboardWith(const UBlackboardComponent& OtherBlackboardComponent) const;` — does this AIController allow given UBlackboardComponent sync data with it
- L288 _public prototype_ `void ClaimTaskResource(TSubclassOf<UGameplayTaskResource> ResourceClass);` — `UFUNCTION(BlueprintCallable, Category = "AI|Tasks")`
- L291 _public prototype_ `void UnclaimTaskResource(TSubclassOf<UGameplayTaskResource> ResourceClass);` — `UFUNCTION(BlueprintCallable, Category = "AI|Tasks")`
- L295 _protected prototype_ `void OnUsingBlackBoard(UBlackboardComponent* BlackboardComp, UBlackboardData* BlackboardAsset);` — `UFUNCTION(BlueprintImplementableEvent)`
- L297 _protected prototype_ `virtual bool InitializeBlackboard(UBlackboardComponent& BlackboardComp, UBlackboardData& BlackboardAsset);`
- L302 _public prototype_ `FVector GetFocalPoint() const;` — `UFUNCTION(BlueprintCallable, Category = "AI")` — Retrieve the final position that controller should be looking at.
- L304 _public prototype_ `FVector GetFocalPointForPriority(EAIFocusPriority::Type InPriority) const;`
- L308 _public prototype_ `virtual FVector GetFocalPointOnActor(const AActor *Actor) const;` — `UFUNCTION(BlueprintCallable, Category = "AI")` — Retrieve the focal point this controller should focus to on given actor.
- L312 _public prototype_ `void K2_SetFocalPoint(FVector FP);` — `UFUNCTION(BlueprintCallable, Category = "AI", meta = (DisplayName = "SetFocalPoint", ScriptName = "SetFocalPoint", Keywords = "focus"))` — Set the position that controller should be looking at.
- L316 _public prototype_ `void K2_SetFocus(AActor* NewFocus);` — `UFUNCTION(BlueprintCallable, Category = "AI", meta = (DisplayName = "SetFocus", ScriptName = "SetFocus"))` — Set Focus for actor, will set FocalPoint as a result.
- L320 _public prototype_ `AActor* GetFocusActor() const;` — `UFUNCTION(BlueprintCallable, Category = "AI")` — Get the focused actor.
- L322 _public function_ `inline AActor* GetFocusActorForPriority(EAIFocusPriority::Type InPriority) const`
- L326 _public prototype_ `void K2_ClearFocus();` — `UFUNCTION(BlueprintCallable, Category = "AI", meta = (DisplayName = "ClearFocus", ScriptName = "ClearFocus"))` — Clears Focus, will also clear FocalPoint as a result
- L341 _public prototype_ `bool SuggestTossVelocity(FVector& OutTossVelocity, FVector Start, FVector End, float TossSpeed, bool bPreferHighArc, float CollisionRadius = 0, bool bOnlyTraceUp = false);` — Computes a launch velocity vector to toss a projectile and hit the given destination. Performance note: Potentially expensive. Nonzero CollisionRadius and bOnlyTraceUp=false are the more expensive options. @param OutTossVelocity - out param stuffed with the computed velocity to use @param Start - desired start point of arc @param End - desired end point of arc @param TossSpeed - Initial speed of the theoretical projectile. Assumed to only change due to gravity for the entire lifetime of the projectile @param CollisionSize (optional) - is the size of bounding box of the tossed actor (defaults to (0,0,0) @param bOnlyTraceUp  (optional) - when true collision checks verifying the arc will only be done along the upward portion of the arc @return - true if a valid arc was computed, false if no valid solution could be found
- L344 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L345 _public prototype_ `virtual void PostInitializeComponents() override;`
- L346 _public prototype_ `virtual void PostRegisterAllComponents() override;`
- L351 _protected prototype_ `virtual void OnPossess(APawn* InPawn) override;`
- L352 _protected prototype_ `virtual void OnUnPossess() override;`
- L355 _public prototype_ `virtual bool ShouldPostponePathUpdates() const override;`
- L356 _public prototype_ `virtual void DisplayDebug(UCanvas* Canvas, const FDebugDisplayInfo& DebugDisplay, float& YL, float& YPos) override;`
- L359 _public prototype_ `virtual void GrabDebugSnapshot(FVisualLogEntry* Snapshot) const override;`
- L362 _public prototype_ `virtual void Reset() override;`
- L371 _public prototype_ `virtual bool LineOfSightTo(const AActor* Other, FVector ViewPoint = FVector(ForceInit), bool bAlternateChecks = false) const override;` — Checks line to center and top of other actor @param Other is the actor whose visibility is being checked. @param ViewPoint is eye position visibility is being checked from.  If vect(0,0,0) passed in, uses current viewtarget's eye position. @param bAlternateChecks used only in AIController implementation @return true if controller's pawn can see Other actor.
- L375 _public prototype_ `virtual void ActorsPerceptionUpdated(const TArray<AActor*>& UpdatedActors);` — Notifies AIController of changes in given actors' perception
- L378 _public prototype_ `virtual void UpdateControlRotation(float DeltaTime, bool bUpdatePawn = true);` — Update direction AI is looking based on FocalPoint
- L381 _public prototype_ `virtual void SetFocalPoint(FVector NewFocus, EAIFocusPriority::Type InPriority = EAIFocusPriority::Gameplay);` — Set FocalPoint for given priority as absolute position or offset from base.
- L384 _public prototype_ `virtual void SetFocus(AActor* NewFocus, EAIFocusPriority::Type InPriority = EAIFocusPriority::Gameplay);` — Set Focus actor for given priority, will set FocalPoint as a result.
- L388 _public prototype_ `virtual void ClearFocus(EAIFocusPriority::Type InPriority);` — Clears Focus for given priority, will also clear FocalPoint as a result @param InPriority focus priority to clear. If you don't know what to use you probably mean EAIFocusPriority::Gameplay
- L390 _public prototype_ `void SetPerceptionComponent(UAIPerceptionComponent& InPerceptionComponent);`
- L394 _public function_ `virtual UAIPerceptionComponent* GetPerceptionComponent() override`
- L399 _public prototype_ `virtual bool IsFollowingAPath() const override;`
- L400 _public prototype_ `virtual IPathFollowingAgentInterface* GetPathFollowingAgent() const override;`
- L406 _private member_ `FGenericTeamId TeamID;`
- L408 _public prototype_ `virtual void SetGenericTeamId(const FGenericTeamId& NewTeamID) override;`
- L409 _public function_ `virtual FGenericTeamId GetGenericTeamId() const override`
- L414 _public function_ `virtual UGameplayTasksComponent* GetGameplayTasksComponent(const UGameplayTask& Task) const override`
- L415 _public function_ `virtual AActor* GetGameplayTaskOwner(const UGameplayTask* Task) const override`
- L416 _public function_ `virtual AActor* GetGameplayTaskAvatar(const UGameplayTask* Task) const override`
- L417 _public function_ `virtual uint8 GetGameplayTaskDefaultPriority() const`
- L419 _public function_ `inline UGameplayTasksComponent* GetGameplayTasksComponent() const`
- L422 _public function_ `virtual void OnGameplayTaskInitialized(UGameplayTask& Task) override` — add empty overrides to fix linker errors if project implements a child class without adding GameplayTasks module dependency
- L423 _public function_ `virtual void OnGameplayTaskActivated(UGameplayTask& Task) override`
- L424 _public function_ `virtual void OnGameplayTaskDeactivated(UGameplayTask& Task) override`
- L427 _public prototype_ `virtual void OnGameplayTaskResourcesClaimed(FGameplayResourceSet NewlyClaimed, FGameplayResourceSet FreshlyReleased);` — `UFUNCTION()`
- L432 _public prototype_ `virtual FString GetDebugIcon() const;`
- L435 _public function_ `static void ToggleAIIgnorePlayers()` — Cheat/debugging functions
- L436 _public function_ `static bool AreAIIgnoringPlayers()`
- L439 _public member_ `static bool bAIIgnorePlayers;` — If true, AI controllers will ignore players.
- L444 _public function_ `UPathFollowingComponent* GetPathFollowingComponent() const` — `UFUNCTION(BlueprintCallable, Category="AI|Navigation")` — Returns PathFollowingComponent subobject
- L446 _public function_ `UAIPerceptionComponent* GetAIPerceptionComponent()` — `UFUNCTION(BlueprintPure, Category = "AI|Perception")`
- L448 _public function_ `const UAIPerceptionComponent* GetAIPerceptionComponent() const`
- L450 _public function_ `UBrainComponent* GetBrainComponent() const`
- L451 _public function_ `const UBlackboardComponent* GetBlackboardComponent() const`
- L452 _public function_ `UBlackboardComponent* GetBlackboardComponent()`
- L457 _public prototype_ `void SetPathFollowingComponent(UPathFollowingComponent* NewPFComponent);` — `UFUNCTION(BlueprintCallable, Category = "AI|Navigation")` — Note that this function does not do any pathfollowing state transfer. Intended to be called as part of initialization/setup process

#### Free symbols / members of external scopes

- L31 _namespace_ `namespace EPathFollowingRequestResult`
- L32 _namespace_ `namespace EPathFollowingResult`
- L33 _namespace_ `namespace EPathFollowingStatus`
- L42 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAIMoveCompletedSignature, FAIRequestID, RequestID, EPathFollowingResult::Type, Result);`
- L42 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAIMoveCompletedSignature, FAIRequestID, RequestID, EPathFollowingResult::Type, Result);`
- L47 _namespace_ `namespace EAIFocusPriority`
- L49 _typedef_ `typedef uint8 Type;` (scope `EAIFocusPriority`)
- L51 _variable_ `inline const Type Default = 0;` (scope `EAIFocusPriority`)
- L52 _variable_ `inline const Type Move = 1;` (scope `EAIFocusPriority`)
- L53 _variable_ `inline const Type Gameplay = 2;` (scope `EAIFocusPriority`)
- L55 _variable_ `inline const Type LastFocusPriority = Gameplay;` (scope `EAIFocusPriority`)
- L463 _namespace_ `namespace FAISystem`
- L465 _function_ `inline bool IsValidControllerAndHasValidPawn(const AController* Controller)` (scope `FAISystem`)

### `Source/Runtime/AIModule/Classes/AIResourceInterface.h` (Public)


#### class `UAIResourceInterface`  
`class UAIResourceInterface : public UInterface`  
_L12-15_
- reflection: `UINTERFACE(MinimalAPI, meta=(CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`

#### class `IAIResourceInterface`  
`class IAIResourceInterface`  
_L17-32_
- L22 _private function_ `virtual void LockResource(EAIRequestPriority::Type LockSource)` — If resource is lockable lock it with indicated priority
- L25 _private function_ `virtual void ClearResourceLock(EAIRequestPriority::Type LockSource)` — clear resource lock of the given origin
- L28 _private function_ `virtual void ForceUnlockResource()` — Force-clears all locks on resource
- L31 _private function_ `virtual bool IsResourceLocked() const` — check whether resource is currently locked

### `Source/Runtime/AIModule/Classes/AIResources.h` (Public)


#### class `UAIResource_Movement`  
`class UAIResource_Movement : public UGameplayTaskResource`  
_L10-17_
- reflection: `UCLASS(meta = (DisplayName = "AI Movement"), MinimalAPI)`
- inherits: `UGameplayTaskResource`
- L15 _private prototype_ `virtual FString GenerateDebugDescription() const override;`

#### class `UAIResource_Logic`  
`class UAIResource_Logic : public UGameplayTaskResource`  
_L20-23_
- reflection: `UCLASS(meta = (DisplayName = "AI Logic"), MinimalAPI)`
- inherits: `UGameplayTaskResource`

### `Source/Runtime/AIModule/Classes/AISubsystem.h` (Public)


#### class `UAISubsystem`  
`class UAISubsystem : public UObject, public FTickableGameObject`  
_L15-37_
- reflection: `UCLASS(config = Engine, defaultconfig, MinimalAPI)`
- inherits: `UObject,FTickableGameObject`
- desc: A class representing a common interface and behavior for AI subsystems
- L21 _private member_ `TObjectPtr<UAISystem> AISystem;` — `UPROPERTY()`
- L24 _public prototype_ `UAISubsystem(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L26 _public prototype_ `virtual UWorld* GetWorld() const override;`
- L27 _public prototype_ `virtual void BeginDestroy() override;`
- L30 _public function_ `virtual UWorld* GetTickableGameObjectWorld() const override` — FTickableGameObject begin
- L31 _public function_ `virtual void Tick(float DeltaTime) override`
- L32 _public prototype_ `virtual ETickableTickType GetTickableTickType() const override;`
- L33 _public prototype_ `virtual TStatId GetStatId() const override;`
- L36 _public function_ `UWorld* GetWorldFast() const`

### `Source/Runtime/AIModule/Classes/AISystem.h` (Public)


#### class `UAISystem`  
`class UAISystem : public UAISystemBase`  
_L26-286_
- reflection: `UCLASS(config=Engine, defaultconfig, MinimalAPI)`
- inherits: `UAISystemBase`
- L33 _protected member_ `FSoftClassPath PerceptionSystemClassName;` — `UPROPERTY(globalconfig, EditAnywhere, Category = "AISystem", meta = (MetaClass = "/Script/AIModule.AIPerceptionSystem", DisplayName = "Perception System Class"))` — Class that will be used to spawn the perception system, can be game-specific
- L37 _protected member_ `FSoftClassPath HotSpotManagerClassName;` — `UPROPERTY(globalconfig, EditAnywhere, Category = "AISystem", meta = (MetaClass = "/Script/AIModule.AIHotSpotManager", DisplayName = "AIHotSpotManager Class"))` — Class that will be used to spawn the hot spot manager, can be game-specific
- L41 _protected member_ `FSoftClassPath EnvQueryManagerClassName;` — `UPROPERTY(globalconfig, EditAnywhere, Category = "AISystem", meta = (MetaClass = "/Script/AIModule.EnvQueryManager", DisplayName = "EnvQueryManager Class"))` — Class that will be used to spawn the env query manager, can be game-specific
- L46 _public member_ `float AcceptanceRadius;` — `UPROPERTY(globalconfig, EditDefaultsOnly, Category = "Movement")` — Default AI movement's acceptance radius used to determine whether AI reached path's end
- L51 _public member_ `float PathfollowingRegularPathPointAcceptanceRadius;` — `UPROPERTY(globalconfig, EditDefaultsOnly, Category = "Movement")` — Value used for pathfollowing's internal code to determine whether AI reached path's point. @note this value is not used for path's last point. @see AcceptanceRadius
- L56 _public member_ `float PathfollowingNavLinkAcceptanceRadius;` — `UPROPERTY(globalconfig, EditDefaultsOnly, Category = "Movement")` — Similarly to PathfollowingRegularPathPointAcceptanceRadius used by pathfollowing's internals but gets applied only when next point on a path represents a begining of navigation link
- L60 _public member_ `bool bFinishMoveOnGoalOverlap;` — `UPROPERTY(globalconfig, EditDefaultsOnly, Category = "Movement")` — If true, overlapping the goal will be counted by default as finishing a move
- L64 _public member_ `bool bAcceptPartialPaths;` — `UPROPERTY(globalconfig, EditDefaultsOnly, Category = "Movement")` — Sets default value for rather move tasks accept partial paths or not
- L68 _public member_ `bool bAllowStrafing;` — `UPROPERTY(globalconfig, EditDefaultsOnly, Category = "Movement")` — Sets default value for rather move tasks allow strafing or not
- L74 _public member_ `bool bAllowControllersAsEQSQuerier;` — `UPROPERTY(globalconfig, EditDefaultsOnly, Category = "EQS")` — if enable will make EQS not complaint about using Controllers as queriers. Default behavior (false) will in places automatically convert controllers to pawns, and complain if code user bypasses the conversion or uses pawn-less controller
- L78 _public member_ `bool bEnableDebuggerPlugin;` — `UPROPERTY(globalconfig, EditDefaultsOnly, Category = "AISystem")` — if set, GameplayDebuggerPlugin will be loaded on module's startup
- L84 _public member_ `bool bForgetStaleActors;` — `UPROPERTY(globalconfig, EditDefaultsOnly, Category = "AISystem")` — If set, actors will be forgotten by the perception system when their stimulus has expired. If not set, the perception system will remember the actor even if they are no longer perceived and their stimuli has exceeded its max age
- L89 _public member_ `bool bAddBlackboardSelfKey = true;` — `UPROPERTY(globalconfig, EditDefaultsOnly, Category = "Blackboard")` — If set to true will result in automatically adding the SelfActor key to new Blackboard assets. It will also result in making sure all the BB assets loaded do have the SelfKey entry, via PostLoad
- L92 _public member_ `bool bClearBBEntryOnBTEQSFail = true;` — `UPROPERTY(globalconfig, EditDefaultsOnly, Category = "Behavior Tree")`
- L96 _public member_ `bool bBlackboardKeyDecoratorAllowsNoneAsValue = false;` — `UPROPERTY(globalconfig, EditDefaultsOnly, Category = "Behavior Tree")` — If enabled, blackboard based decorators will set key to 'Invalid' on creation or when selected key no longer exists (instead of using the first key of the blackboard).
- L100 _public member_ `TSoftObjectPtr<UBlackboardData> DefaultBlackboard;` — `UPROPERTY(globalconfig, EditDefaultsOnly, Category = "Behavior Tree")` — If set, new BTs will use this BB as default.
- L104 _public member_ `TEnumAsByte<ECollisionChannel> DefaultSightCollisionChannel;` — `UPROPERTY(globalconfig, EditDefaultsOnly, Category = "PerceptionSystem")` — Which collision channel to use for sight checks by default
- L109 _protected member_ `TObjectPtr<UBehaviorTreeManager> BehaviorTreeManager;` — `UPROPERTY(Transient)` — Behavior tree manager used by game
- L113 _protected member_ `TObjectPtr<UEnvQueryManager> EnvironmentQueryManager;` — `UPROPERTY(Transient)` — Environment query manager used by game
- L116 _protected member_ `TObjectPtr<UAIPerceptionSystem> PerceptionSystem;` — `UPROPERTY(Transient)`
- L119 _protected member_ `TArray<TObjectPtr<UAIAsyncTaskBlueprintProxy>> AllProxyObjects;` — `UPROPERTY(Transient)`
- L122 _protected member_ `TObjectPtr<UAIHotSpotManager> HotSpotManager;` — `UPROPERTY(Transient)`
- L125 _protected member_ `TObjectPtr<UNavLocalGridManager> NavLocalGrids;` — `UPROPERTY(Transient)`
- L127 _protected typedef_ `typedef TMultiMap<TWeakObjectPtr<UBlackboardData>, TWeakObjectPtr<UBlackboardComponent> > FBlackboardDataToComponentsMap;`
- L130 _protected member_ `FBlackboardDataToComponentsMap BlackboardDataToComponentsMap;` — UBlackboardComponent instances that reference the blackboard data definition
- L132 _protected member_ `FDelegateHandle ActorSpawnedDelegateHandle;`
- L134 _protected member_ `FDelegateHandle PawnBeginPlayDelegateHandle;`
- L137 _protected member_ `static FRandomStream RandomStream;` — random number stream to be used by all things AI. WIP
- L140 _public prototype_ `UAISystem(const FObjectInitializer& ObjectInitializer);`
- L142 _public prototype_ `virtual void BeginDestroy() override;`
- L144 _public prototype_ `virtual void PostInitProperties() override;`
- L147 _public prototype_ `virtual void InitializeActorsForPlay(bool bTimeGotReset) override;` — UAISystemBase begin
- L148 _public prototype_ `virtual void WorldOriginLocationChanged(FIntVector OldOriginLocation, FIntVector NewOriginLocation) override;`
- L149 _public prototype_ `virtual void CleanupWorld(bool bSessionEnded = true, bool bCleanupResources = true) override;`
- L151 _public prototype_ `virtual void CleanupWorld(bool bSessionEnded, bool bCleanupResources, UWorld* NewWorld) override;` — `UE_DEPRECATED(5.1, "NewWorld was unused and not always calculated correctly and we expect it is not needed; let us know on UDN if it is necessary.")`
- L152 _public prototype_ `virtual void StartPlay() override;`
- L156 _public function_ `inline UBehaviorTreeManager* GetBehaviorTreeManager()` — Behavior tree manager getter
- L158 _public function_ `inline const UBehaviorTreeManager* GetBehaviorTreeManager() const` — Behavior tree manager const getter
- L161 _public function_ `inline UEnvQueryManager* GetEnvironmentQueryManager()` — Environment Query manager getter
- L163 _public function_ `inline const UEnvQueryManager* GetEnvironmentQueryManager() const` — Environment Query manager const getter
- L165 _public function_ `inline UAIPerceptionSystem* GetPerceptionSystem()`
- L166 _public function_ `inline const UAIPerceptionSystem* GetPerceptionSystem() const`
- L168 _public function_ `inline UAIHotSpotManager* GetHotSpotManager()`
- L169 _public function_ `inline const UAIHotSpotManager* GetHotSpotManager() const`
- L171 _public function_ `inline UNavLocalGridManager* GetNavLocalGridManager()`
- L172 _public function_ `inline const UNavLocalGridManager* GetNavLocalGridManager() const`
- L174 _public function_ `inline static UAISystem* GetCurrentSafe(UWorld* World)`
- L179 _public function_ `inline static UAISystem* GetCurrent(UWorld& World)`
- L184 _public function_ `inline UWorld* GetOuterWorld() const`
- L186 _public function_ `virtual UWorld* GetWorld() const override`
- L188 _public function_ `inline void AddReferenceFromProxyObject(UAIAsyncTaskBlueprintProxy* BlueprintProxy)`
- L190 _public function_ `inline void RemoveReferenceToProxyObject(UAIAsyncTaskBlueprintProxy* BlueprintProxy)`
- L196 _public prototype_ `virtual void AIIgnorePlayers();` — `UFUNCTION(exec)`
- L199 _public prototype_ `virtual void AILoggingVerbose();` — `UFUNCTION(exec)`
- L202 _public prototype_ `void RunEQS(const FString& QueryName, UObject* Target);` — insta-runs EQS query for given Target
- L260 _public prototype_ `void RegisterBlackboardComponent(class UBlackboardData& BlackboardAsset, class UBlackboardComponent& BlackboardComp);` — Registers a UBlackboardComponent instance with this blackboard data asset. This will also register the component for each parent UBlackboardData asset. This should be called after the component has been initialized (i.e. InitializeComponent). The user is responsible for calling UnregisterBlackboardComponent (i.e. UninitializeComponent).
- L267 _public prototype_ `void UnregisterBlackboardComponent(class UBlackboardData& BlackboardAsset, class UBlackboardComponent& BlackboardComp);` — Unregisters a UBlackboardComponent instance with this blackboard data asset. This should be called before the component has been uninitialized (i.e. UninitializeComponent).
- L274 _public prototype_ `FBlackboardDataToComponentsIterator CreateBlackboardDataToComponentsIterator(class UBlackboardData& BlackboardAsset);` — Creates a forward only iterator for that will iterate all UBlackboardComponent instances that reference the specified BlackboardAsset and it's parents.
- L276 _public prototype_ `virtual void ConditionalLoadDebuggerPlugin();`
- L278 _public function_ `static const FRandomStream& GetRandomStream()`
- L279 _public function_ `static void SeedRandomStream(const int32 Seed)`
- L282 _protected prototype_ `virtual void OnActorSpawned(AActor* SpawnedActor);`
- L283 _protected prototype_ `virtual void OnPawnBeginPlay(APawn* Pawn);`
- L285 _protected prototype_ `void LoadDebuggerPlugin();`

#### struct `UAISystem::FBlackboardDataToComponentsIterator`  
`struct FBlackboardDataToComponentsIterator`  
_L208-251_
- desc: Iterator for traversing all UBlackboardComponent instances associated with this blackboard data asset. This is a forward only iterator.
- L211 _public prototype_ `FBlackboardDataToComponentsIterator(FBlackboardDataToComponentsMap& BlackboardDataToComponentsMap, class UBlackboardData* BlackboardAsset);`
- L213 _public function_ `inline FBlackboardDataToComponentsIterator& operator++()`
- L219 _public function_ `inline FBlackboardDataToComponentsIterator operator++(int)`
- L227 _public function_ `inline explicit operator bool() const`
- L228 _public function_ `inline bool operator !() const`
- L230 _public function_ `inline UBlackboardData* Key() const`
- L231 _public function_ `inline UBlackboardComponent* Value() const`
- L234 _private function_ `inline const FBlackboardDataToComponentsMap::TConstKeyIterator& GetCurrentIteratorRef() const`
- L235 _private function_ `inline FBlackboardDataToComponentsMap::TConstKeyIterator& GetCurrentIteratorRef()`
- L237 _private function_ `void TryMoveIteratorToParentBlackboard()`
- L246 _private member_ `int32 CurrentIteratorIndex;`
- L248 _private member_ `static const int32 InlineSize = 8;`
- L249 _private member_ `TArray<TWeakObjectPtr<UBlackboardData>> IteratorKeysForReference;`
- L250 _private member_ `TArray<FBlackboardDataToComponentsMap::TConstKeyIterator, TInlineAllocator<InlineSize>> Iterators;`

#### Free symbols / members of external scopes

- L23 _macro_ `#define GET_AI_CONFIG_VAR(a) (GetDefault<UAISystem>()->a)`

### `Source/Runtime/AIModule/Classes/AITypes.h` (Public)


#### enum `EAIOptionFlag::Type`  
`enum Type : int`  
_L55-62_
- L57 _public enumerator_ `Default`
- L58 _public enumerator_ `Enable UMETA(DisplayName = "Yes")`
- L59 _public enumerator_ `Disable UMETA(DisplayName = "No")`
- L61 _public enumerator_ `MAX UMETA(Hidden)`

#### enum `FAIDistanceType`  
`enum class FAIDistanceType : uint8`  
_L66-73_
- reflection: `UENUM()`
- L68 _public enumerator_ `Distance3D`
- L69 _public enumerator_ `Distance2D`
- L70 _public enumerator_ `DistanceZ`
- L72 _public enumerator_ `MAX UMETA(Hidden)`

#### enum `EAIForceParam::Type`  
`enum Type`  
_L90-96_
- L92 _public enumerator_ `Force`
- L93 _public enumerator_ `DoNotForce`
- L95 _public enumerator_ `MAX`

#### enum `EAILogicResuming::Type`  
`enum Type`  
_L108-112_
- L110 _public enumerator_ `Continue`
- L111 _public enumerator_ `RestartedInstead`

#### enum `EAIRequestPriority::Type`  
`enum Type : int`  
_L118-132_
- L121 _public enumerator_ `SoftScript` — Actions requested by Level Designers by placing AI-hinting elements on the map.
- L123 _public enumerator_ `Logic` — Actions AI wants to do due to its internal logic.
- L125 _public enumerator_ `HardScript` — Actions LDs really want AI to perform.
- L127 _public enumerator_ `Reaction` — Actions being result of game-world mechanics, like hit reactions, death, falling, etc. In general things not depending on what AI's thinking.
- L129 _public enumerator_ `Ultimate` — Ultimate priority, to be used with caution, makes AI perform given action regardless of anything else (for example disabled reactions).
- L131 _public enumerator_ `MAX UMETA(Hidden)`

#### enum `EAILockSource::Type`  
`enum Type : int`  
_L143-151_
- L145 _public enumerator_ `Animation`
- L146 _public enumerator_ `Logic`
- L147 _public enumerator_ `Script`
- L148 _public enumerator_ `Gameplay`
- L150 _public enumerator_ `MAX UMETA(Hidden)`

#### struct `FAINamedID`  
`template<typename TCounter> struct FAINamedID`  
_L164-217_
- L166 _public member_ `const typename TCounter::Type Index;`
- L167 _public member_ `const FName Name;`
- L169 _private member_ `static TCounter Counter;`
- L171 _protected function_ `static TCounter& GetCounter()`
- L177 _protected function_ `FAINamedID(const FName& InName, typename TCounter::Type InIndex) : Index(InIndex), Name(InName)` — back-door for forcing IDs
- L184 _public function_ `FAINamedID(const FName& InName) : Index(GetCounter().GetNextAvailableID()), Name(InName)`
- L188 _public function_ `FAINamedID(const FAINamedID& Other) : Index(Other.Index), Name(Other.Name)`
- L192 _public function_ `FAINamedID& operator=(const FAINamedID& Other)`
- L198 _public function_ `FAINamedID() : Index(typename TCounter::Type(-1)), Name(TEXT("Invalid"))`
- L202 _public function_ `operator typename TCounter::Type() const`
- L203 _public function_ `bool IsValid() const`
- L205 _public function_ `static uint32 GetSize()`
- L207 _public function_ `static FAINamedID<TCounter> InvalidID()`

#### struct `FAIGenericID`  
`template<typename TCounter> struct FAIGenericID`  
_L220-273_
- L222 _public member_ `const typename TCounter::Type Index;`
- L224 _private member_ `static TCounter Counter;`
- L226 _protected function_ `static TCounter& GetCounter()`
- L231 _protected function_ `explicit FAIGenericID(typename TCounter::Type InIndex) : Index(InIndex)`
- L237 _public function_ `FAIGenericID(const FAIGenericID& Other) : Index(Other.Index)`
- L241 _public function_ `FAIGenericID& operator=(const FAIGenericID& Other)`
- L247 _public function_ `FAIGenericID() : Index(typename TCounter::Type(-1))`
- L251 _public function_ `static FAIGenericID GetNextID()`
- L254 _public function_ `operator typename TCounter::Type() const` — `UE_DEPRECATED(5.6, "AIGenericId is not convertible to its base type anymore.")`
- L256 _public function_ `bool IsValid() const`
- L258 _public function_ `bool operator==(const FAIGenericID Other) const`
- L259 _public function_ `bool operator!=(const FAIGenericID Other) const`
- L261 _public function_ `static uint32 GetSize()`
- L263 _public function_ `static FAIGenericID<TCounter> InvalidID()`

#### struct `FAIBasicCounter`  
`template<typename TCounterType> struct FAIBasicCounter`  
_L276-286_
- L278 _public typedef_ `typedef TCounterType Type;`
- L280 _protected member_ `Type NextAvailableID;`
- L282 _public function_ `FAIBasicCounter() : NextAvailableID(Type(0))`
- L283 _public function_ `Type GetNextAvailableID()`
- L284 _public function_ `uint32 GetSize() const`
- L285 _public function_ `void OnIndexForced(Type ForcedIndex)`

#### struct `FAIResCounter`  
`struct FAIResCounter : FAIBasicCounter<uint8>`  
_L289-290_
- inherits: `FAIBasicCounter<uint8>`

#### struct `FAIResourcesSet`  
`struct FAIResourcesSet`  
_L294-318_
- L296 _public member_ `static constexpr uint32 NoResources = 0;`
- L297 _public member_ `static constexpr uint32 AllResources = uint32(-1);`
- L298 _public member_ `static constexpr uint8 MaxFlags = 32;`
- L300 _private member_ `uint32 Flags;`
- L302 _public function_ `FAIResourcesSet(uint32 ResourceSetDescription = NoResources) : Flags(ResourceSetDescription)`
- L303 _public function_ `FAIResourcesSet(const FAIResourceID& Resource) : Flags(0)`
- L308 _public function_ `FAIResourcesSet& AddResourceIndex(uint8 ResourceIndex)`
- L309 _public function_ `FAIResourcesSet& RemoveResourceIndex(uint8 ResourceIndex)`
- L310 _public function_ `bool ContainsResourceIndex(uint8 ResourceID) const`
- L312 _public function_ `FAIResourcesSet& AddResource(const FAIResourceID& Resource)`
- L313 _public function_ `FAIResourcesSet& RemoveResource(const FAIResourceID& Resource)`
- L314 _public function_ `bool ContainsResource(const FAIResourceID& Resource) const`
- L316 _public function_ `bool IsEmpty() const`
- L317 _public function_ `void Clear()`

#### struct `FAIResourceLock`  
`struct FAIResourceLock`  
_L321-378_
- desc: structure used to define which subsystem requested locking of a specific AI resource (like movement, logic, etc.)
- L324 _public typedef_ `typedef uint16 FLockFlags;` — @note feel free to change the type if you need to support more then 16 lock sources
- L326 _public prototype_ `FAIResourceLock();`
- L328 _public prototype_ `void SetLock(EAIRequestPriority::Type LockPriority);`
- L329 _public prototype_ `void ClearLock(EAIRequestPriority::Type LockPriority);`
- L332 _public prototype_ `void SetUseResourceLockCount(bool inUseResourceLockCount);` — set whether we should use resource lock count.  clears all existing locks.
- L335 _public prototype_ `void ForceClearAllLocks();` — force-clears all locks
- L337 _public function_ `inline bool IsLocked() const`
- L342 _public function_ `inline bool IsLockedBy(EAIRequestPriority::Type LockPriority) const`
- L350 _public function_ `inline bool IsAvailableFor(EAIRequestPriority::Type LockPriority) const` — Answers the question if given priority is allowed to use this resource. @Note that if resource is locked with priority LockPriority this function will return false as well
- L362 _public prototype_ `FString GetLockPriorityName() const;`
- L364 _public function_ `void operator+=(const FAIResourceLock& Other)`
- L369 _public function_ `bool operator==(const FAIResourceLock& Other) const`
- L375 _private member_ `TArray<uint8> ResourceLockCount;`
- L376 _private member_ `FLockFlags Locks;`
- L377 _private member_ `bool bUseResourceLockCount;`

#### struct `FAIRequestID`  
`struct FAIRequestID`  
_L395-447_
- reflection: `USTRUCT(BlueprintType)`
- L400 _private member_ `static constexpr uint32 AnyRequestID = 0;`
- L401 _private member_ `static constexpr uint32 InvalidRequestID = uint32(-1);`
- L404 _private member_ `uint32 RequestID;` — `UPROPERTY()`
- L407 _public function_ `FAIRequestID(uint32 InRequestID = InvalidRequestID) : RequestID(InRequestID)`
- L412 _public function_ `inline bool IsEquivalent(uint32 OtherID) const` — returns true if given ID is identical to stored ID or any of considered IDs is FAIRequestID::AnyRequest
- L417 _public function_ `inline bool IsEquivalent(FAIRequestID Other) const`
- L422 _public function_ `inline bool IsValid() const`
- L427 _public function_ `inline uint32 GetID() const`
- L429 _public function_ `void operator=(uint32 OtherID)`
- L434 _public function_ `operator uint32() const`
- L439 _public function_ `FString ToString() const`
- L444 _public member_ `static const FAIRequestID AnyRequest;`
- L445 _public member_ `static const FAIRequestID CurrentRequest;`
- L446 _public member_ `static const FAIRequestID InvalidRequest;`

#### struct `FAIMoveRequest`  
`struct FAIMoveRequest`  
_L454-574_
- reflection: `USTRUCT()`
- L458 _public prototype_ `FAIMoveRequest();`
- L459 _public prototype_ `FAIMoveRequest(const AActor* InGoalActor);`
- L460 _public prototype_ `FAIMoveRequest(const FVector& InGoalLocation);`
- L462 _public function_ `FAIMoveRequest& SetNavigationFilter(TSubclassOf<UNavigationQueryFilter> Filter)`
- L463 _public function_ `FAIMoveRequest& SetUsePathfinding(bool bPathfinding)`
- L464 _public function_ `FAIMoveRequest& SetAllowPartialPath(bool bAllowPartial)`
- L465 _public function_ `FAIMoveRequest& SetRequireNavigableEndLocation(bool bRequire)`
- L471 _public function_ `FAIMoveRequest& SetApplyCostLimitFromHeuristic(bool bApply, float InCostLimitFactor = FLT_MAX, float InMinimumCostLimit = 0.f)` — Defines if the underlying pathfind query should limit its exploration based on the navigation cost @param bApply				if set - the pathfind query cost will be limited based on the heuristic between the start and end location @param InCostLimitFactor		this multiplier is used to compute a max node cost allowed to the open list (cost limit = CostLimitFactor*InitialHeuristicEstimate) @param InMinimumCostLimit	minimum cost limit clamping value (in cost units) used to allow large deviation in short paths
- L472 _public function_ `FAIMoveRequest& SetProjectGoalLocation(bool bProject)`
- L474 _public function_ `FAIMoveRequest& SetCanStrafe(bool bStrafe)`
- L475 _public function_ `FAIMoveRequest& SetReachTestIncludesAgentRadius(bool bIncludeRadius)`
- L476 _public function_ `FAIMoveRequest& SetReachTestIncludesGoalRadius(bool bIncludeRadius)`
- L477 _public function_ `FAIMoveRequest& SetAcceptanceRadius(float Radius)`
- L478 _public function_ `FAIMoveRequest& SetUserData(const FCustomMoveSharedPtr& InUserData)`
- L479 _public function_ `FAIMoveRequest& SetUserFlags(int32 InUserFlags)`
- L480 _public function_ `FAIMoveRequest& SetStartFromPreviousPath(const bool bInStartFromPreviousPath)`
- L483 _public function_ `bool IsValid() const` — the request should be either set up to move to a location, of go to a valid actor
- L485 _public function_ `bool IsMoveToActorRequest() const`
- L486 _public function_ `AActor* GetGoalActor() const`
- L487 _public function_ `FVector GetGoalLocation() const`
- L490 _public prototype_ `FVector GetDestination() const;` — retrieves request's requested destination location, GoalActor's location or GoalLocation, depending on the request itself
- L492 _public function_ `bool IsUsingPathfinding() const`
- L493 _public function_ `bool IsUsingPartialPaths() const`
- L494 _public function_ `bool IsNavigableEndLocationRequired() const`
- L495 _public function_ `bool IsProjectingGoal() const`
- L496 _public function_ `bool IsApplyingCostLimitFromHeuristic() const`
- L497 _public function_ `float GetCostLimitFactor() const`
- L498 _public function_ `float GetMinimumCostLimit() const`
- L499 _public function_ `TSubclassOf<UNavigationQueryFilter> GetNavigationFilter() const`
- L501 _public function_ `bool CanStrafe() const`
- L502 _public function_ `bool IsReachTestIncludingAgentRadius() const`
- L503 _public function_ `bool IsReachTestIncludingGoalRadius() const`
- L504 _public function_ `float GetAcceptanceRadius() const`
- L505 _public function_ `const FCustomMoveSharedPtr& GetUserData() const`
- L506 _public function_ `int32 GetUserFlags() const`
- L508 _public function_ `const bool ShouldStartFromPreviousPath() const`
- L509 _public prototype_ `void SetGoalActor(const AActor* InGoalActor);`
- L510 _public prototype_ `void SetGoalLocation(const FVector& InGoalLocation);`
- L512 _public prototype_ `bool UpdateGoalLocation(const FVector& NewLocation) const;`
- L513 _public prototype_ `FString ToString() const;`
- L519 _protected member_ `TWeakObjectPtr<AActor> GoalActor;` — `UPROPERTY()` — move goal: actor
- L522 _protected member_ `mutable FVector GoalLocation;` — move goal: location
- L525 _protected member_ `TSubclassOf<UNavigationQueryFilter> FilterClass;` — pathfinding: navigation filter to use
- L528 _protected member_ `uint32 bInitialized : 1;` — move goal is an actor
- L531 _protected member_ `uint32 bMoveToActor : 1;` — move goal is an actor
- L534 _protected member_ `uint32 bUsePathfinding : 1;` — pathfinding: if set - regular pathfinding will be used, if not - direct path between two points
- L537 _protected member_ `uint32 bAllowPartialPath : 1;` — pathfinding: allow using incomplete path going toward goal but not reaching it
- L540 _protected member_ `uint32 bRequireNavigableEndLocation : 1;` — pathfinding: if set - require the end location to be linked to the navigation data
- L543 _protected member_ `uint32 bApplyCostLimitFromHeuristic : 1;` — pathfinding: if set - the pathfind query cost will be limited based on the heuristic between the start and end location (c.f. CostLimitFactor and MinimumCostLimit).
- L546 _protected member_ `uint32 bProjectGoalOnNavigation : 1;` — pathfinding: goal location will be projected on navigation data before use
- L549 _protected member_ `uint32 bStartFromPreviousPath : 1;` — pathfinding: the request will start from the end of the previous path (if any), and the generated path will be merged with the remaining points of the previous path
- L552 _protected member_ `uint32 bReachTestIncludesAgentRadius : 1;` — pathfollowing: acceptance radius needs to be increased by agent radius (stop on overlap vs exact point)
- L555 _protected member_ `uint32 bReachTestIncludesGoalRadius : 1;` — pathfollowing: acceptance radius needs to be increased by goal actor radius
- L558 _protected member_ `uint32 bCanStrafe : 1;` — pathfollowing: keep focal point at move goal
- L561 _protected member_ `float AcceptanceRadius;` — pathfollowing: required distance to goal to complete move
- L564 _protected member_ `float CostLimitFactor;` — pathfinding: this multiplier is used to compute a max node cost allowed to the open list (cost limit = CostLimitFactor*InitialHeuristicEstimate)
- L567 _protected member_ `float MinimumCostLimit;` — pathfinding: minimum cost limit clamping value (in cost units) used to allow large deviation in short paths
- L570 _protected member_ `FCustomMoveSharedPtr UserData;` — custom user data: structure
- L573 _protected member_ `int32 UserFlags;` — custom user data: flags

#### enum `EGenericAICheck`  
`enum class EGenericAICheck : uint8`  
_L577-588_
- reflection: `UENUM()`
- L579 _public enumerator_ `Less`
- L580 _public enumerator_ `LessOrEqual`
- L581 _public enumerator_ `Equal`
- L582 _public enumerator_ `NotEqual`
- L583 _public enumerator_ `GreaterOrEqual`
- L584 _public enumerator_ `Greater`
- L585 _public enumerator_ `IsTrue`
- L587 _public enumerator_ `MAX UMETA(Hidden)`

#### struct `FIntervalCountdown`  
`struct FIntervalCountdown`  
_L591-633_
- reflection: `USTRUCT()`
- L596 _public member_ `float Interval;` — `UPROPERTY(EditAnywhere, Category=Time)`
- L598 _public member_ `float TimeLeft;`
- L600 _public function_ `explicit FIntervalCountdown(const float InInterval = -1.f) : Interval(InInterval), TimeLeft(0)`
- L602 _public function_ `void Set(const float InNewTimeLeft)`
- L608 _public function_ `bool Tick(const float TimeDelta)` — @return True if time's up
- L615 _public function_ `void Reset()` — resets the countdown back to Interval
- L621 _public function_ `float GetElapsedTime() const` — Note that this function returns meaningful results only if Interval > 0
- L629 _public function_ `float GetElapsedTimeWithFallback(const float FallbackValue) const` — @return If Interval > 0 returns time accumulated since resetting. Oterwise returns FallbackValue

#### Free symbols / members of external scopes

- L13 _typedef_ `typedef TSharedPtr<FMoveRequestCustomData, ESPMode::ThreadSafe> FCustomMoveSharedPtr;`
- L15 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Overall AI Time"), STAT_AI_Overall, STATGROUP_AI,`
- L17 _macro_ `#define TEXT_AI_LOCATION(v) (FAISystem::IsValidLocation(v) ? *(v).ToString() : TEXT("Invalid"))`
- L19 _namespace_ `namespace FAISystem`
- L21 _externvar_ `extern const FRotator InvalidRotation;` (scope `FAISystem`)
- L22 _externvar_ `extern const FQuat InvalidOrientation;` (scope `FAISystem`)
- L23 _variable_ `inline constexpr FVector InvalidLocation = FVector(FLT_MAX, UE::Math::TVectorConstInit{});` (scope `FAISystem`)
- L24 _variable_ `inline constexpr FVector InvalidDirection = FVector(0, UE::Math::TVectorConstInit{});` (scope `FAISystem`)
- L25 _variable_ `constexpr float InvalidRange = -1.f;` (scope `FAISystem`)
- L26 _variable_ `constexpr float InfiniteInterval = -FLT_MAX;` (scope `FAISystem`)
- L27 _variable_ `constexpr uint32 InvalidUnsignedID = uint32(INDEX_NONE);` (scope `FAISystem`)
- L29 _function_ `inline bool IsValidLocation(const FVector& TestLocation)` (scope `FAISystem`)
- L36 _function_ `inline bool IsValidDirection(const FVector& TestVector)` (scope `FAISystem`)
- L41 _function_ `inline bool IsValidRotation(const FRotator& TestRotation)` (scope `FAISystem`)
- L46 _function_ `inline bool IsValidOrientation(const FQuat& TestOrientation)` (scope `FAISystem`)
- L53 _namespace_ `namespace EAIOptionFlag`
- L75 _namespace_ `namespace FAISystem`
- L77 _function_ `inline bool PickAIOption(EAIOptionFlag::Type Option, bool DefaultOption)` (scope `FAISystem`)
- L82 _function_ `inline EAIOptionFlag::Type BoolToAIOption(bool Value)` (scope `FAISystem`)
- L88 _namespace_ `namespace EAIForceParam`
- L99 _namespace_ `namespace FAIMoveFlag`
- L101 _variable_ `constexpr bool StopOnOverlap = true;` (scope `FAIMoveFlag`)
- L102 _variable_ `constexpr bool UsePathfinding = true;` (scope `FAIMoveFlag`)
- L103 _variable_ `constexpr bool IgnorePathfinding = false;` (scope `FAIMoveFlag`)
- L106 _namespace_ `namespace EAILogicResuming`
- L116 _namespace_ `namespace EAIRequestPriority`
- L135 _namespace_ `namespace EAIRequestPriority`
- L137 _variable_ `constexpr int32 Lowest = EAIRequestPriority::Logic;` (scope `EAIRequestPriority`)
- L141 _namespace_ `namespace EAILockSource`
- L213 _function_ `friend inline uint32 GetTypeHash(const FAINamedID& ID)`
- L269 _function_ `friend inline uint32 GetTypeHash(const FAIGenericID& ID)`
- L291 _typedef_ `typedef FAINamedID<FAIResCounter> FAIResourceID;`
- L380 _namespace_ `namespace FAIResources`
- L382 _externvar_ `extern const FAIResourceID InvalidResource;` (scope `FAIResources`)
- L383 _externvar_ `extern const FAIResourceID Movement;` (scope `FAIResources`)
- L384 _externvar_ `extern const FAIResourceID Logic;` (scope `FAIResources`)
- L385 _externvar_ `extern const FAIResourceID Perception;` (scope `FAIResources`)
- L387 _prototype_ `void RegisterResource(const FAIResourceID& Resource);` (scope `FAIResources`)
- L388 _prototype_ `const FAIResourceID& GetResource(int32 ResourceIndex);` (scope `FAIResources`)
- L389 _prototype_ `int32 GetResourcesCount();` (scope `FAIResources`)
- L390 _prototype_ `FString GetSetDescription(FAIResourcesSet ResourceSet);` (scope `FAIResources`)

### `Source/Runtime/AIModule/Classes/Actions/PawnAction_Move.h` (Public)


#### enum `EPawnActionMoveMode::Type`  
`enum Type : int`  
_L10-14_
- L12 _public enumerator_ `UsePathfinding`
- L13 _public enumerator_ `StraightLine`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace EPawnActionMoveMode`

### `Source/Runtime/AIModule/Classes/BehaviorTree/BTAuxiliaryNode.h` (Public)


#### struct `FBTAuxiliaryMemory`  
`struct FBTAuxiliaryMemory : public FBTInstancedNodeMemory`  
_L9-13_
- inherits: `FBTInstancedNodeMemory`
- L11 _public member_ `float NextTickRemainingTime;`
- L12 _public member_ `float AccumulatedDeltaTime;`

#### class `UBTAuxiliaryNode`  
`class UBTAuxiliaryNode : public UBTNode`  
_L30-114_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UBTNode`
- L35 _private prototype_ `void WrappedOnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;` — wrapper for node instancing: OnBecomeRelevant
- L38 _private prototype_ `void WrappedOnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;` — wrapper for node instancing: OnCeaseRelevant
- L46 _private prototype_ `bool WrappedTickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds, float& NextNeededDeltaTime) const;` — wrapper for node instancing: TickNode @param OwnerComp	The behavior tree owner of this node @param NodeMemory	The instance memory of the current node @param DeltaSeconds		DeltaTime since last call @param NextNeededDeltaTime		In out parameter, if this node needs a smaller DeltaTime it is the node's responsibility to change it @returns	True if it actually done some processing or false if it was skipped because of not ticking or in between time interval
- L48 _private prototype_ `virtual void DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const override;`
- L49 _private prototype_ `virtual uint16 GetSpecialMemorySize() const override;`
- L52 _private prototype_ `void InitializeParentLink(uint8 InChildIndex);` — fill in data about tree structure
- L55 _private prototype_ `const UBTNode* GetMyNode() const;` — @return parent task node
- L58 _private prototype_ `uint8 GetChildIndex() const;` — @return index of child in parent's array or MAX_uint8
- L64 _private prototype_ `float GetNextNeededDeltaTime(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;` — Get The next needed deltatime for this node @param OwnerComp	The behavior tree owner of this node @param NodeMemory	The instance memory of the current node @return The next needed DeltaTime
- L69 _protected member_ `uint8 bNotifyBecomeRelevant:1;` — if set, OnBecomeRelevant will be used
- L72 _protected member_ `uint8 bNotifyCeaseRelevant:1;` — if set, OnCeaseRelevant will be used
- L75 _protected member_ `uint8 bNotifyTick : 1;` — if set, OnTick will be used
- L78 _protected member_ `uint8 bTickIntervals : 1;` — if set, conditional tick will use remaining time from node's memory
- L81 _protected member_ `uint8 ChildIndex;` — child index in parent node
- L87 _protected prototype_ `virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);` — called when auxiliary node becomes active this function should be considered as const (don't modify state of object) if node is not instanced! bNotifyBecomeRelevant must be set to true for this function to be called Calling INIT_AUXILIARY_NODE_NOTIFY_FLAGS in the constructor of the node will set this flag automatically
- L93 _protected prototype_ `virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);` — called when auxiliary node becomes inactive this function should be considered as const (don't modify state of object) if node is not instanced! bNotifyCeaseRelevant must be set to true for this function to be called Calling INIT_AUXILIARY_NODE_NOTIFY_FLAGS in the constructor of the node will set this flag automatically
- L99 _protected prototype_ `virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);` — tick function this function should be considered as const (don't modify state of object) if node is not instanced! bNotifyTick must be set to true for this function to be called Calling INIT_AUXILIARY_NODE_NOTIFY_FLAGS in the constructor of the node will set this flag automatically
- L102 _protected prototype_ `void SetNextTickTime(uint8* NodeMemory, float RemainingTime) const;` — sets next tick time
- L105 _protected prototype_ `float GetNextTickRemainingTime(uint8* NodeMemory) const;` — gets remaining time for next tick
- L108 _protected function_ `template<typename TickNode, typename OnBecomeRelevant, typename OnCeaseRelevant> void InitNotifyFlags(TickNode, OnBecomeRelevant, OnCeaseRelevant)`
- L122 _function_ `inline uint8 UBTAuxiliaryNode::GetChildIndex() const`

#### Free symbols / members of external scopes

- L116 _macro_ `#define INIT_AUXILIARY_NODE_NOTIFY_FLAGS() \`

### `Source/Runtime/AIModule/Classes/BehaviorTree/BTCompositeNode.h` (Public)


#### struct `FBTCompositeMemory`  
`struct FBTCompositeMemory`  
_L15-22_
- L18 _public member_ `int8 CurrentChild;` — index of currently active child node
- L21 _public member_ `int8 OverrideChild;` — child override for next selection

#### enum `EBTChildIndex`  
`enum class EBTChildIndex : uint8`  
_L25-29_
- reflection: `UENUM()`
- L27 _public enumerator_ `FirstNode`
- L28 _public enumerator_ `TaskNode`

#### enum `EBTDecoratorLogic::Type`  
`enum Type : int`  
_L36-47_
- L38 _public enumerator_ `Invalid`
- L40 _public enumerator_ `Test` — Test decorator conditions.
- L42 _public enumerator_ `And` — logic op: AND
- L44 _public enumerator_ `Or` — logic op: OR
- L46 _public enumerator_ `Not` — logic op: NOT

#### struct `FBTDecoratorLogic`  
`struct FBTDecoratorLogic`  
_L51-63_
- reflection: `USTRUCT(BlueprintType)`
- L56 _public member_ `TEnumAsByte<EBTDecoratorLogic::Type> Operation;` — `UPROPERTY()`
- L59 _public member_ `uint16 Number;` — `UPROPERTY()`
- L61 _public function_ `FBTDecoratorLogic() : Operation(EBTDecoratorLogic::Invalid), Number(0)`
- L62 _public function_ `FBTDecoratorLogic(uint8 InOperation, uint16 InNumber) : Operation(InOperation), Number(InNumber)`

#### struct `FBTCompositeChild`  
`struct FBTCompositeChild`  
_L66-84_
- reflection: `USTRUCT(BlueprintType)`
- L72 _public member_ `TObjectPtr<UBTCompositeNode> ChildComposite = nullptr;` — `UPROPERTY(BlueprintReadOnly, Category = BehaviorTree)` — child node
- L75 _public member_ `TObjectPtr<UBTTaskNode> ChildTask = nullptr;` — `UPROPERTY(BlueprintReadOnly, Category = BehaviorTree)`
- L79 _public member_ `TArray<TObjectPtr<UBTDecorator>> Decorators;` — `UPROPERTY(BlueprintReadOnly, Category = BehaviorTree)` — execution decorators
- L83 _public member_ `TArray<FBTDecoratorLogic> DecoratorOps;` — `UPROPERTY(BlueprintReadOnly, Category = BehaviorTree)` — logic operations for decorators

#### class `UBTCompositeNode`  
`class UBTCompositeNode : public UBTNode`  
_L87-281_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UBTNode`
- L93 _private member_ `TArray<FBTCompositeChild> Children;` — `UPROPERTY(BlueprintReadOnly, Category = BehaviorTree)` — child nodes
- L97 _private member_ `TArray<TObjectPtr<UBTService>> Services;` — `UPROPERTY(BlueprintReadOnly, Category = BehaviorTree)` — service nodes
- L99 _private prototype_ `~UBTCompositeNode();`
- L102 _private prototype_ `void InitializeComposite(uint16 InLastExecutionIndex);` — fill in data about tree structure
- L105 _private prototype_ `int32 FindChildToExecute(FBehaviorTreeSearchData& SearchData, EBTNodeResult::Type& LastResult) const;` — find next child branch to execute
- L108 _private prototype_ `int32 GetChildIndex(FBehaviorTreeSearchData& SearchData, const UBTNode& ChildNode) const;` — get index of child node (handle subtrees)
- L110 _private prototype_ `int32 GetChildIndex(const UBTNode& ChildNode) const;` — get index of child node
- L113 _private prototype_ `void OnChildActivation(FBehaviorTreeSearchData& SearchData, const UBTNode& ChildNode) const;` — called before passing search to child node
- L114 _private prototype_ `void OnChildActivation(FBehaviorTreeSearchData& SearchData, int32 ChildIndex) const;`
- L123 _private prototype_ `void OnChildDeactivation(FBehaviorTreeSearchData& SearchData, const UBTNode& ChildNode, EBTNodeResult::Type& NodeResult, const bool bRequestedFromValidInstance) const;` — Notification called after child has finished search @param SearchData for any new addition or removal of extra aux nodes/ descriptor @param ChildNode is the children being deactivated @param NodeResult the raison of the deactivation @param bRequestedFromValidInstance the new requested search start is within the current active instances
- L131 _private prototype_ `void OnChildDeactivation(FBehaviorTreeSearchData& SearchData, int32 ChildIndex, EBTNodeResult::Type& NodeResult, const bool bRequestedFromValidInstance) const;` — Notification called after child has finished search @param SearchData for any new addition or removal of extra aux nodes/ descriptor @param ChildIndex of the child node being deactivated @param NodeResult the raison of the deactivation @param bRequestedFromValidInstance the new request search start is within the current active instances
- L134 _private prototype_ `void OnNodeActivation(FBehaviorTreeSearchData& SearchData) const;` — called when start enters this node
- L137 _private prototype_ `void OnNodeDeactivation(FBehaviorTreeSearchData& SearchData, EBTNodeResult::Type& NodeResult) const;` — called when search leaves this node
- L140 _private prototype_ `void OnNodeRestart(FBehaviorTreeSearchData& SearchData) const;` — called when search needs to reactivate this node
- L143 _private prototype_ `void ConditionalNotifyChildExecution(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, const UBTNode& ChildNode, EBTNodeResult::Type& NodeResult) const;` — notify about task execution start
- L146 _private prototype_ `virtual uint16 GetInstanceMemorySize() const override;` — size of instance memory
- L147 _private prototype_ `virtual void InitializeMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryInit::Type InitType) const override;`
- L148 _private prototype_ `virtual void CleanupMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryClear::Type CleanupType) const override;`
- L151 _private prototype_ `UBTNode* GetChildNode(int32 Index) const;` — @return child node at given index
- L154 _private prototype_ `int32 GetChildrenNum() const;` — @return children count
- L157 _private prototype_ `uint16 GetChildExecutionIndex(int32 Index, EBTChildIndex ChildMode = EBTChildIndex::TaskNode) const;` — @return execution index of child node
- L160 _private prototype_ `uint16 GetLastExecutionIndex() const;` — @return execution index of last node in child branches
- L163 _private prototype_ `virtual void SetChildOverride(FBehaviorTreeSearchData& SearchData, int8 Index) const;` — set override for next child index
- L166 _private prototype_ `virtual void DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const override;` — gathers description of all runtime parameters
- L169 _private prototype_ `virtual bool CanPushSubtree(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, int32 ChildIdx) const;` — check if child node can execute new subtree
- L173 _private prototype_ `virtual bool CanAbortLowerPriority() const;` — @return allowed flow abort modes for decorators
- L174 _private prototype_ `virtual bool CanAbortSelf() const;`
- L178 _private prototype_ `int32 GetMatchingChildIndex(int32 ActiveInstanceIdx, FBTNodeIndex& NodeIdx) const;` — find branch containing specified node index
- L181 _private prototype_ `uint16 GetBranchExecutionIndex(uint16 NodeInBranchIdx) const;` — get first execution index of given branch
- L184 _private prototype_ `bool DoDecoratorsAllowExecution(UBehaviorTreeComponent& OwnerComp, const int32 InstanceIdx, const int32 ChildIdx) const;` — is child execution allowed by decorators?
- L186 _private prototype_ `bool IsApplyingDecoratorScope() const;`
- L190 _private function_ `void OnChildDeactivation(FBehaviorTreeSearchData& SearchData, const UBTNode& ChildNode, EBTNodeResult::Type& NodeResult) const` — `UE_DEPRECATED(5.0, "This function is deprecated. Please use RequestBranchDeactivation instead.")` — Deprecated methods
- L192 _private function_ `void OnChildDeactivation(FBehaviorTreeSearchData& SearchData, int32 ChildIndex, EBTNodeResult::Type& NodeResult) const` — `UE_DEPRECATED(5.0, "This function is deprecated. Please use RequestBranchDeactivation instead.")`
- L198 _protected member_ `uint32 bApplyDecoratorScope : 1;` — `UPROPERTY(EditAnywhere, Category = Composite)` — if set, all decorators in branch below will be removed when execution flow leaves (decorators on this node are not affected)
- L201 _protected member_ `uint32 bUseChildExecutionNotify : 1;` — if set, NotifyChildExecution will be called
- L204 _protected member_ `uint32 bUseNodeActivationNotify : 1;` — if set, NotifyNodeActivation will be called
- L207 _protected member_ `uint32 bUseNodeDeactivationNotify : 1;` — if set, NotifyNodeDeactivation will be called
- L210 _protected member_ `uint32 bUseDecoratorsActivationCheck : 1;` — if set, CanNotifyDecoratorsOnActivation will be called
- L213 _protected member_ `uint32 bUseDecoratorsDeactivationCheck : 1;` — if set, CanNotifyDecoratorsOnDeactivation will be called
- L216 _protected member_ `uint32 bUseDecoratorsFailedActivationCheck : 1;` — if set, CanNotifyDecoratorsOnFailedActivation will be called
- L219 _protected member_ `uint16 LastExecutionIndex;` — execution index of last node in child branches
- L224 _protected prototype_ `virtual void NotifyChildExecution(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, int32 ChildIdx, EBTNodeResult::Type& NodeResult) const;` — called just after child execution, allows to modify result bUseChildExecutionNotify must be set to true for this function to be called Calling INIT_COMPOSITE_NODE_NOTIFY_FLAGS in the constructor of the node will set this flag automatically
- L229 _protected prototype_ `virtual void NotifyNodeActivation(FBehaviorTreeSearchData& SearchData) const;` — called when start enters this node bUseNodeActivationNotify must be set to true for this function to be called Calling INIT_COMPOSITE_NODE_NOTIFY_FLAGS in the constructor of the node will set this flag automatically
- L234 _protected prototype_ `virtual void NotifyNodeDeactivation(FBehaviorTreeSearchData& SearchData, EBTNodeResult::Type& NodeResult) const;` — called when start leaves this node bUseNodeDeactivationNotify must be set to true for this function to be called Calling INIT_COMPOSITE_NODE_NOTIFY_FLAGS in the constructor of the node will set this flag automatically
- L239 _protected prototype_ `virtual bool CanNotifyDecoratorsOnActivation(FBehaviorTreeSearchData& SearchData, int32 ChildIdx) const;` — check if NotifyDecoratorsOnActivation is allowed, requires bUseDecoratorsActivationCheck flag bUseDecoratorsActivationCheck must be set to true for this function to be called Calling INIT_COMPOSITE_NODE_NOTIFY_FLAGS in the constructor of the node will set this flag automatically
- L244 _protected prototype_ `virtual bool CanNotifyDecoratorsOnDeactivation(FBehaviorTreeSearchData& SearchData, int32 ChildIdx, EBTNodeResult::Type& NodeResult) const;` — check if NotifyDecoratorsOnDeactivation is allowed, requires bUseDecoratorsDeactivationCheck flag bUseDecoratorsDeactivationCheck must be set to true for this function to be called Calling INIT_COMPOSITE_NODE_NOTIFY_FLAGS in the constructor of the node will set this flag automatically
- L249 _protected prototype_ `virtual bool CanNotifyDecoratorsOnFailedActivation(FBehaviorTreeSearchData& SearchData, int32 ChildIdx, EBTNodeResult::Type& NodeResult) const;` — check if NotifyDecoratorsOnFailedActivation is allowed, requires bUseDecoratorsActivationCheck flag bUseDecoratorsFailedActivationCheck must be set to true for this function to be called Calling INIT_COMPOSITE_NODE_NOTIFY_FLAGS in the constructor of the node will set this flag automatically
- L252 _protected prototype_ `void NotifyDecoratorsOnActivation(FBehaviorTreeSearchData& SearchData, int32 ChildIdx) const;` — runs through decorators on given child node and notify them about activation
- L255 _protected prototype_ `void NotifyDecoratorsOnDeactivation(FBehaviorTreeSearchData& SearchData, int32 ChildIdx, EBTNodeResult::Type& NodeResult, const bool bIsInSameActiveInstance) const;` — runs through decorators on given child node and notify them about deactivation
- L258 _protected prototype_ `void NotifyDecoratorsOnFailedActivation(FBehaviorTreeSearchData& SearchData, int32 ChildIdx, EBTNodeResult::Type& NodeResult) const;` — runs through decorators on given child node and notify them about failed activation
- L261 _protected prototype_ `int32 GetNextChild(FBehaviorTreeSearchData& SearchData, int32 LastChildIdx, EBTNodeResult::Type LastResult) const;` — get next child to process and store it in CurrentChild
- L264 _protected prototype_ `void RequestDelayedExecution(UBehaviorTreeComponent& OwnerComp, EBTNodeResult::Type LastResult) const;` — store delayed execution request
- L267 _protected function_ `virtual int32 GetNextChildHandler(struct FBehaviorTreeSearchData& SearchData, int32 PrevChild, EBTNodeResult::Type LastResult) const`
- L271 _protected function_ `void InitNotifyFlags(NotifyChildExecution, NotifyNodeActivation, NotifyNodeDeactivation, CanNotifyDecoratorsOnActivation, CanNotifyDecoratorsOnDeactivation, CanNotifyDecoratorsOnFailedActivation)`
- L297 _function_ `inline UBTNode* UBTCompositeNode::GetChildNode(int32 Index) const`
- L306 _function_ `inline int32 UBTCompositeNode::GetChildrenNum() const`
- L311 _function_ `inline uint16 UBTCompositeNode::GetLastExecutionIndex() const`
- L316 _function_ `inline bool UBTCompositeNode::IsApplyingDecoratorScope() const`

#### Free symbols / members of external scopes

- L13 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(int32, FGetNextChildDelegate, FBehaviorTreeSearchData& , int32 , EBTNodeResult::Type );`
- L13 _prototype_ `DECLARE_DELEGATE_RetVal_ThreeParams(int32, FGetNextChildDelegate, FBehaviorTreeSearchData& , int32 , EBTNodeResult::Type );`
- L32 _namespace_ `namespace EBTDecoratorLogic`
- L283 _macro_ `#define INIT_COMPOSITE_NODE_NOTIFY_FLAGS() \`

### `Source/Runtime/AIModule/Classes/BehaviorTree/BTDecorator.h` (Public)


#### enum `EBTDecoratorAbortRequest`  
`enum class EBTDecoratorAbortRequest : uint8`  
_L10-17_
- L13 _public enumerator_ `ConditionResultChanged` — request execution update when only result of condition changes and active branch of tree can potentially change too
- L16 _public enumerator_ `ConditionPassing` — request execution update every time as long as condition is still passing

#### class `UBTDecorator`  
`class UBTDecorator : public UBTAuxiliaryNode`  
_L37-141_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UBTAuxiliaryNode`
- L42 _private prototype_ `bool WrappedCanExecute(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;` — wrapper for node instancing: CalculateRawConditionValue
- L45 _private prototype_ `void WrappedOnNodeActivation(FBehaviorTreeSearchData& SearchData) const;` — wrapper for node instancing: OnNodeActivation
- L48 _private prototype_ `void WrappedOnNodeDeactivation(FBehaviorTreeSearchData& SearchData, EBTNodeResult::Type NodeResult) const;` — wrapper for node instancing: OnNodeDeactivation
- L51 _private prototype_ `void WrappedOnNodeProcessed(FBehaviorTreeSearchData& SearchData, EBTNodeResult::Type& NodeResult) const;` — wrapper for node instancing: OnNodeProcessed
- L54 _private prototype_ `EBTFlowAbortMode::Type GetFlowAbortMode() const;` — @return flow controller's abort mode
- L57 _private prototype_ `bool IsInversed() const;` — @return true if condition should be inversed
- L59 _private prototype_ `virtual FString GetStaticDescription() const override;`
- L62 _private prototype_ `void UpdateFlowAbortMode();` — modify current flow abort mode, so it can be used with parent composite
- L65 _private prototype_ `bool IsFlowAbortModeValid() const;` — @return true if current abort mode can be used with parent composite
- L70 _protected member_ `uint32 bAllowAbortNone : 1;` — if set, FlowAbortMode can be set to None
- L73 _protected member_ `uint32 bAllowAbortLowerPri : 1;` — if set, FlowAbortMode can be set to LowerPriority and Both
- L76 _protected member_ `uint32 bAllowAbortChildNodes : 1;` — if set, FlowAbortMode can be set to Self and Both
- L79 _protected member_ `uint32 bNotifyActivation : 1;` — if set, OnNodeActivation will be used
- L82 _protected member_ `uint32 bNotifyDeactivation : 1;` — if set, OnNodeDeactivation will be used
- L85 _protected member_ `uint32 bNotifyProcessed : 1;` — if set, OnNodeProcessed will be used
- L88 _protected member_ `uint32 bShowInverseConditionDesc : 1;` — if set, static description will include default description of inversed condition
- L93 _private member_ `uint32 bInverseCondition : 1;` — `UPROPERTY(Category = Condition, EditAnywhere)` — if set, condition check result will be inversed
- L98 _protected member_ `TEnumAsByte<EBTFlowAbortMode::Type> FlowAbortMode;` — `UPROPERTY(Category=FlowControl, EditAnywhere)` — flow controller settings
- L100 _protected prototype_ `void SetIsInversed(bool bShouldBeInversed);`
- L106 _protected prototype_ `virtual void OnNodeActivation(FBehaviorTreeSearchData& SearchData);` — called when underlying node is activated this function should be considered as const (don't modify state of object) if node is not instanced! bNotifyActivation must be set to true for this function to be called Calling INIT_DECORATOR_NODE_NOTIFY_FLAGS in the constructor of the decorator will set this flag automatically
- L112 _protected prototype_ `virtual void OnNodeDeactivation(FBehaviorTreeSearchData& SearchData, EBTNodeResult::Type NodeResult);` — called when underlying node has finished this function should be considered as const (don't modify state of object) if node is not instanced! bNotifyDeactivation must be set to true for this function to be called Calling INIT_DECORATOR_NODE_NOTIFY_FLAGS in the constructor of the decorator will set this flag automatically
- L118 _protected prototype_ `virtual void OnNodeProcessed(FBehaviorTreeSearchData& SearchData, EBTNodeResult::Type& NodeResult);` — called when underlying node was processed (deactivated or failed to activate) this function should be considered as const (don't modify state of object) if node is not instanced! bNotifyProcessed must be set to true for this function to be called Calling INIT_DECORATOR_NODE_NOTIFY_FLAGS in the constructor of the decorator will set this flag automatically
- L121 _protected prototype_ `virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;` — calculates raw, core value of decorator's condition. Should not include calling IsInversed
- L125 _protected prototype_ `void ConditionalFlowAbort(UBehaviorTreeComponent& OwnerComp, EBTDecoratorAbortRequest RequestMode) const;` — more "flow aware" version of calling RequestExecution(this) on owning behavior tree component should be used in external events that may change result of CalculateRawConditionValue
- L131 _protected function_ `void InitNotifyFlags(TickNode, OnBecomeRelevant, OnCeaseRelevant, OnNodeActivation, OnNodeDeactivation, OnNodeProcessed)`
- L157 _function_ `inline EBTFlowAbortMode::Type UBTDecorator::GetFlowAbortMode() const`
- L162 _function_ `inline bool UBTDecorator::IsInversed() const`

#### Free symbols / members of external scopes

- L143 _macro_ `#define INIT_DECORATOR_NODE_NOTIFY_FLAGS() \`

### `Source/Runtime/AIModule/Classes/BehaviorTree/BTFunctionLibrary.h` (Public)


#### class `UBTFunctionLibrary`  
`class UBTFunctionLibrary : public UBlueprintFunctionLibrary`  
_L29-118_
- reflection: `UCLASS(meta=(RestrictedToClasses="BTNode"), MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- L35 _public prototype_ `static UBlackboardComponent* GetOwnersBlackboard(UBTNode* NodeOwner);` — `UFUNCTION(BlueprintPure, Category="AI|BehaviorTree", Meta=(HidePin="NodeOwner", DefaultToSelf="NodeOwner"))`
- L38 _public prototype_ `static UBehaviorTreeComponent* GetOwnerComponent(UBTNode* NodeOwner);` — `UFUNCTION(BlueprintPure, Category = "AI|BehaviorTree", Meta=(HidePin="NodeOwner", DefaultToSelf="NodeOwner"))`
- L41 _public prototype_ `static UObject* GetBlackboardValueAsObject(UBTNode* NodeOwner, const FBlackboardKeySelector& Key);` — `UFUNCTION(BlueprintPure, Category="AI|BehaviorTree", Meta=(HidePin="NodeOwner", DefaultToSelf="NodeOwner"))`
- L44 _public prototype_ `static AActor* GetBlackboardValueAsActor(UBTNode* NodeOwner, const FBlackboardKeySelector& Key);` — `UFUNCTION(BlueprintPure, Category="AI|BehaviorTree", Meta=(HidePin="NodeOwner", DefaultToSelf="NodeOwner"))`
- L47 _public prototype_ `static UClass* GetBlackboardValueAsClass(UBTNode* NodeOwner, const FBlackboardKeySelector& Key);` — `UFUNCTION(BlueprintPure, Category="AI|BehaviorTree", Meta=(HidePin="NodeOwner", DefaultToSelf="NodeOwner"))`
- L50 _public prototype_ `static uint8 GetBlackboardValueAsEnum(UBTNode* NodeOwner, const FBlackboardKeySelector& Key);` — `UFUNCTION(BlueprintPure, Category="AI|BehaviorTree", Meta=(HidePin="NodeOwner", DefaultToSelf="NodeOwner"))`
- L53 _public prototype_ `static int32 GetBlackboardValueAsInt(UBTNode* NodeOwner, const FBlackboardKeySelector& Key);` — `UFUNCTION(BlueprintPure, Category="AI|BehaviorTree", Meta=(HidePin="NodeOwner", DefaultToSelf="NodeOwner"))`
- L56 _public prototype_ `static float GetBlackboardValueAsFloat(UBTNode* NodeOwner, const FBlackboardKeySelector& Key);` — `UFUNCTION(BlueprintPure, Category="AI|BehaviorTree", Meta=(HidePin="NodeOwner", DefaultToSelf="NodeOwner"))`
- L59 _public prototype_ `static bool GetBlackboardValueAsBool(UBTNode* NodeOwner, const FBlackboardKeySelector& Key);` — `UFUNCTION(BlueprintPure, Category="AI|BehaviorTree", Meta=(HidePin="NodeOwner", DefaultToSelf="NodeOwner"))`
- L62 _public prototype_ `static FString GetBlackboardValueAsString(UBTNode* NodeOwner, const FBlackboardKeySelector& Key);` — `UFUNCTION(BlueprintPure, Category="AI|BehaviorTree", Meta=(HidePin="NodeOwner", DefaultToSelf="NodeOwner"))`
- L65 _public prototype_ `static FName GetBlackboardValueAsName(UBTNode* NodeOwner, const FBlackboardKeySelector& Key);` — `UFUNCTION(BlueprintPure, Category="AI|BehaviorTree", Meta=(HidePin="NodeOwner", DefaultToSelf="NodeOwner"))`
- L68 _public prototype_ `static FVector GetBlackboardValueAsVector(UBTNode* NodeOwner, const FBlackboardKeySelector& Key);` — `UFUNCTION(BlueprintPure, Category="AI|BehaviorTree", Meta=(HidePin="NodeOwner", DefaultToSelf="NodeOwner"))`
- L71 _public prototype_ `static FRotator GetBlackboardValueAsRotator(UBTNode* NodeOwner, const FBlackboardKeySelector& Key);` — `UFUNCTION(BlueprintPure, Category ="AI|BehaviorTree", Meta=(HidePin="NodeOwner", DefaultToSelf="NodeOwner"))`
- L74 _public prototype_ `static void SetBlackboardValueAsObject(UBTNode* NodeOwner, const FBlackboardKeySelector& Key, UObject* Value);` — `UFUNCTION(BlueprintCallable, Category="AI|BehaviorTree", Meta=(HidePin="NodeOwner", DefaultToSelf="NodeOwner"))`
- L77 _public prototype_ `static void SetBlackboardValueAsClass(UBTNode* NodeOwner, const FBlackboardKeySelector& Key, UClass* Value);` — `UFUNCTION(BlueprintCallable, Category="AI|BehaviorTree", Meta=(HidePin="NodeOwner", DefaultToSelf="NodeOwner"))`
- L80 _public prototype_ `static void SetBlackboardValueAsEnum(UBTNode* NodeOwner, const FBlackboardKeySelector& Key, uint8 Value);` — `UFUNCTION(BlueprintCallable, Category="AI|BehaviorTree", Meta=(HidePin="NodeOwner", DefaultToSelf="NodeOwner"))`
- L83 _public prototype_ `static void SetBlackboardValueAsInt(UBTNode* NodeOwner, const FBlackboardKeySelector& Key, int32 Value);` — `UFUNCTION(BlueprintCallable, Category="AI|BehaviorTree", Meta=(HidePin="NodeOwner", DefaultToSelf="NodeOwner"))`
- L86 _public prototype_ `static void SetBlackboardValueAsFloat(UBTNode* NodeOwner, const FBlackboardKeySelector& Key, float Value);` — `UFUNCTION(BlueprintCallable, Category="AI|BehaviorTree", Meta=(HidePin="NodeOwner", DefaultToSelf="NodeOwner"))`
- L89 _public prototype_ `static void SetBlackboardValueAsBool(UBTNode* NodeOwner, const FBlackboardKeySelector& Key, bool Value);` — `UFUNCTION(BlueprintCallable, Category="AI|BehaviorTree", Meta=(HidePin="NodeOwner", DefaultToSelf="NodeOwner"))`
- L92 _public prototype_ `static void SetBlackboardValueAsString(UBTNode* NodeOwner, const FBlackboardKeySelector& Key, FString Value);` — `UFUNCTION(BlueprintCallable, Category="AI|BehaviorTree", Meta=(HidePin="NodeOwner", DefaultToSelf="NodeOwner"))`
- L95 _public prototype_ `static void SetBlackboardValueAsName(UBTNode* NodeOwner, const FBlackboardKeySelector& Key, FName Value);` — `UFUNCTION(BlueprintCallable, Category="AI|BehaviorTree", Meta=(HidePin="NodeOwner", DefaultToSelf="NodeOwner"))`
- L98 _public prototype_ `static void SetBlackboardValueAsVector(UBTNode* NodeOwner, const FBlackboardKeySelector& Key, FVector Value);` — `UFUNCTION(BlueprintCallable, Category="AI|BehaviorTree", Meta=(HidePin="NodeOwner", DefaultToSelf="NodeOwner"))`
- L102 _public prototype_ `static void ClearBlackboardValueAsVector(UBTNode* NodeOwner, const FBlackboardKeySelector& Key);` — `UFUNCTION(BlueprintCallable, Category="AI|BehaviorTree", Meta=(HidePin="NodeOwner", DefaultToSelf="NodeOwner", DeprecatedFunction, DeprecationMessage="Use ClearBlackboardValue instead."))` — (DEPRECATED) Use ClearBlackboardValue instead
- L105 _public prototype_ `static void SetBlackboardValueAsRotator(UBTNode* NodeOwner, const FBlackboardKeySelector& Key, FRotator Value);` — `UFUNCTION(BlueprintCallable, Category="AI|BehaviorTree", Meta = (HidePin = "NodeOwner", DefaultToSelf = "NodeOwner"))`
- L109 _public prototype_ `static void ClearBlackboardValue(UBTNode* NodeOwner, const FBlackboardKeySelector& Key);` — `UFUNCTION(BlueprintCallable, Category="AI|BehaviorTree", Meta = (HidePin = "NodeOwner", DefaultToSelf = "NodeOwner"))` — Resets indicated value to "not set" value, based on values type
- L113 _public prototype_ `static void StartUsingExternalEvent(UBTNode* NodeOwner, AActor* OwningActor);` — `UFUNCTION(BlueprintCallable, Category="AI|BehaviorTree", Meta=(HidePin="NodeOwner", DefaultToSelf="NodeOwner", DeprecatedFunction, DeprecationMessage="No longer needed"))` — Initialize variables marked as "instance memory" and set owning actor for blackboard operations
- L117 _public prototype_ `static void StopUsingExternalEvent(UBTNode* NodeOwner);` — `UFUNCTION(BlueprintCallable, Category="AI|BehaviorTree", Meta=(HidePin="NodeOwner", DefaultToSelf="NodeOwner", DeprecatedFunction, DeprecationMessage="No longer needed"))` — Save variables marked as "instance memory" and clear owning actor

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace FBTNodeBPImplementationHelper`
- L18 _variable_ `static const int32 NoImplementation = 0;` (scope `FBTNodeBPImplementationHelper`)
- L19 _variable_ `static const int32 Generic = 1 << 0;` (scope `FBTNodeBPImplementationHelper`)
- L20 _variable_ `static const int32 AISpecific = 1 << 1;` (scope `FBTNodeBPImplementationHelper`)
- L21 _variable_ `static const int32 All = Generic | AISpecific;` (scope `FBTNodeBPImplementationHelper`)
- L25 _prototype_ `int32 CheckEventImplementationVersion(FName GenericEventName, FName AIEventName, const UObject& Object, const UClass& StopAtClass);` (scope `FBTNodeBPImplementationHelper`) — checks if given object implements GenericEventName and/or AIEventName BP events, and returns an result as flags set on return integer @return flags set in returned integer indicate kinds of events implemented by given object

### `Source/Runtime/AIModule/Classes/BehaviorTree/BTNode.h` (Public)


#### struct `FBTInstancedNodeMemory`  
`struct FBTInstancedNodeMemory`  
_L33-36_
- L35 _public member_ `int32 NodeIdx;`

#### struct `FBehaviorTreeNodeDebugContext`  
`struct FBehaviorTreeNodeDebugContext`  
_L38-44_
- L41 _public member_ `UBehaviorTreeComponent& OwnerComponent;` — Behavior Tree component of the behavior tree being debugged.
- L43 _public member_ `FString RuntimeDescription;` — Combined string of the values returned by DescribeRuntimeValues of the node at the current debug execution step.

#### class `UBTNode`  
`class UBTNode : public UObject, public IGameplayTaskOwnerInterface`  
_L47-265_
- reflection: `UCLASS(Abstract, config=Game, MinimalAPI)`
- inherits: `UObject,IGameplayTaskOwnerInterface`
- L51 _private prototype_ `virtual UWorld* GetWorld() const override;`
- L54 _private prototype_ `void InitializeNode(UBTCompositeNode* InParentNode, uint16 InExecutionIndex, uint16 InMemoryOffset, uint8 InTreeDepth);` — fill in data about tree structure
- L57 _private prototype_ `virtual void InitializeFromAsset(UBehaviorTree& Asset);` — initialize any asset related data
- L60 _private prototype_ `virtual void InitializeMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryInit::Type InitType) const;` — initialize memory block. InitializeNodeMemory template function is provided to help initialize the memory.
- L63 _private prototype_ `virtual void CleanupMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryClear::Type CleanupType) const;` — cleanup memory block. CleanupNodeMemory template function is provided to help cleanup the memory.
- L66 _private prototype_ `virtual void DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const;` — gathers description of all runtime parameters
- L69 _private prototype_ `virtual uint16 GetInstanceMemorySize() const;` — size of instance memory
- L72 _private prototype_ `virtual void OnInstanceCreated(UBehaviorTreeComponent& OwnerComp);` — called when node instance is added to tree
- L75 _private prototype_ `virtual void OnInstanceDestroyed(UBehaviorTreeComponent& OwnerComp);` — called when node instance is removed from tree
- L78 _private prototype_ `void InitializeInSubtree(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, int32& NextInstancedIndex, EBTMemoryInit::Type InitType) const;` — called on creating subtree to set up memory and instancing
- L81 _private prototype_ `void CleanupInSubtree(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryClear::Type CleanupType) const;` — called on removing subtree to cleanup memory
- L84 _private prototype_ `virtual uint16 GetSpecialMemorySize() const;` — size of special, hidden memory block for internal mechanics
- L88 _private prototype_ `void InitializeExecutionOrder(UBTNode* NextNode);` — fill in data about execution order
- L91 _private prototype_ `UBTNode* GetNextNode() const;` — @return next node in execution order
- L95 _private prototype_ `template<typename T> T* InitializeNodeMemory(uint8* NodeMemory, EBTMemoryInit::Type InitType) const;`
- L98 _private prototype_ `template <typename T> void CleanupNodeMemory(uint8* NodeMemory, EBTMemoryClear::Type CleanupType) const;`
- L101 _private prototype_ `template<typename T> T* GetNodeMemory(FBehaviorTreeSearchData& SearchData) const;`
- L104 _private prototype_ `template<typename T> const T* GetNodeMemory(const FBehaviorTreeSearchData& SearchData) const;`
- L107 _private prototype_ `template<typename T> T* GetNodeMemory(FBehaviorTreeInstance& BTInstance) const;`
- L110 _private prototype_ `template<typename T> const T* GetNodeMemory(const FBehaviorTreeInstance& BTInstance) const;`
- L113 _private prototype_ `template<typename T> T* CastInstanceNodeMemory(uint8* NodeMemory) const;`
- L117 _private prototype_ `template<typename T> T* GetSpecialNodeMemory(uint8* NodeMemory) const;` — get special memory block used for hidden shared data (e.g. node instancing)
- L120 _private prototype_ `UBTCompositeNode* GetParentNode() const;` — @return parent node
- L123 _private prototype_ `FString GetNodeName() const;` — @return name of node
- L126 _private prototype_ `uint16 GetExecutionIndex() const;` — @return execution index
- L129 _private prototype_ `uint16 GetMemoryOffset() const;` — @return memory offset
- L132 _private prototype_ `uint8 GetTreeDepth() const;` — @return depth in tree
- L135 _private prototype_ `void MarkInjectedNode();` — sets bIsInjected flag, do NOT call this function unless you really know what you are doing!
- L138 _private prototype_ `bool IsInjected() const;` — @return true if node was injected by subtree
- L141 _private prototype_ `void ForceInstancing(bool bEnable);` — sets bCreateNodeInstance flag, do NOT call this function on already pushed tree instance!
- L144 _private prototype_ `bool HasInstance() const;` — @return true if node wants to be instanced
- L147 _private prototype_ `bool IsInstanced() const;` — @return true if this object is instanced node
- L150 _private prototype_ `UBehaviorTree* GetTreeAsset() const;` — @return tree asset
- L153 _private prototype_ `UBlackboardData* GetBlackboardAsset() const;` — @return blackboard asset
- L156 _private prototype_ `UBTNode* GetNodeInstance(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;` — @return node instance if bCreateNodeInstance was set
- L157 _private prototype_ `UBTNode* GetNodeInstance(FBehaviorTreeSearchData& SearchData) const;`
- L160 _private prototype_ `FString GetRuntimeDescription(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity) const;` — @return string containing description of this node instance with all relevant runtime values
- L163 _private prototype_ `virtual FString GetStaticDescription() const;` — @return string containing description of this node with all setup values
- L167 _private prototype_ `virtual const ISlateStyle& GetNodeIconStyleSet() const;` — Get the style set from which GetNodeIconName is queried
- L170 _private prototype_ `virtual FName GetNodeIconName() const;` — Get the name of the icon used to display this node in the editor
- L173 _private prototype_ `virtual bool UsesBlueprint() const;` — Get whether this node is using a blueprint for its logic
- L176 _private prototype_ `virtual FString GetErrorMessage() const;` — Validates this node and returns the resulting error message. Empty means no error.
- L179 _private function_ `virtual void OnNodeCreated()` — Called after creating new node in behavior tree editor, use for versioning
- L181 _private prototype_ `void PreSave(FObjectPreSaveContext SaveContext) override;`
- L184 _private prototype_ `virtual const UObject* GetAssociatedAsset(TOptional<FBehaviorTreeNodeDebugContext> DebugContext) const;` — @return the external asset associated with this node that should be open on double click. If set, DebugContext contains the info of the node in the current debug step.
- L188 _private function_ `virtual void SetOwner(AActor* ActorOwner)` — Gets called only for instanced nodes(bCreateNodeInstance == true). In practive overridden by BP-implemented BT nodes
- L191 _private prototype_ `virtual UGameplayTasksComponent* GetGameplayTasksComponent(const UGameplayTask& Task) const override;` — BEGIN IGameplayTaskOwnerInterface
- L192 _private prototype_ `virtual AActor* GetGameplayTaskOwner(const UGameplayTask* Task) const override;`
- L193 _private prototype_ `virtual AActor* GetGameplayTaskAvatar(const UGameplayTask* Task) const override;`
- L194 _private prototype_ `virtual uint8 GetGameplayTaskDefaultPriority() const override;`
- L195 _private prototype_ `virtual void OnGameplayTaskInitialized(UGameplayTask& Task) override;`
- L198 _private prototype_ `UBehaviorTreeComponent* GetBTComponentForTask(UGameplayTask& Task) const;`
- L201 _private function_ `template <class T> T* NewBTAITask(UBehaviorTreeComponent& BTComponent)`
- L209 _private function_ `template <class T> T* NewBTAITask(const UClass& Class, UBehaviorTreeComponent& BTComponent)`
- L218 _private member_ `FString NodeName;` — `UPROPERTY(Category=Description, EditAnywhere, BlueprintReadOnly)` — node name
- L224 _private member_ `TObjectPtr<UBehaviorTree> TreeAsset;` — `UPROPERTY()` — source asset
- L228 _private member_ `TObjectPtr<UBTCompositeNode> ParentNode;` — `UPROPERTY()` — parent node
- L232 _private member_ `TWeakObjectPtr<UBTNode> NextExecutionNode;` — next node in execution order
- L237 _private member_ `uint16 ExecutionIndex;` — `UPROPERTY(transient)` — depth first index (execution order)
- L241 _private member_ `uint16 MemoryOffset;` — `UPROPERTY(transient)` — instance memory offset
- L245 _private member_ `uint8 TreeDepth;` — `UPROPERTY(transient)` — depth in tree
- L249 _private member_ `uint8 bIsInstanced : 1;` — `UPROPERTY(transient)` — set automatically for node instances. Should never be set manually
- L253 _private member_ `uint8 bIsInjected : 1;` — `UPROPERTY(transient)` — if set, node is injected by subtree. Should never be set manually
- L259 _protected member_ `uint8 bCreateNodeInstance : 1;` — `UPROPERTY(transient)` — if set, node will be instanced instead of using memory block and template shared with all other BT components
- L264 _protected member_ `uint8 bOwnsGameplayTasks : 1;` — `UPROPERTY(transient)` — set to true if task owns any GameplayTasks. Note this requires tasks to be created via NewBTAITask Otherwise specific BT task node class is responsible for ending the gameplay tasks on node finish
- L270 _function_ `inline UBehaviorTree* UBTNode::GetTreeAsset() const`
- L275 _function_ `inline UBTCompositeNode* UBTNode::GetParentNode() const`
- L281 _function_ `inline UBTNode* UBTNode::GetNextNode() const`
- L287 _function_ `inline uint16 UBTNode::GetExecutionIndex() const`
- L292 _function_ `inline uint16 UBTNode::GetMemoryOffset() const`
- L297 _function_ `inline uint8 UBTNode::GetTreeDepth() const`
- L302 _function_ `inline void UBTNode::MarkInjectedNode()`
- L307 _function_ `inline bool UBTNode::IsInjected() const`
- L312 _function_ `inline void UBTNode::ForceInstancing(bool bEnable)`
- L320 _function_ `inline bool UBTNode::HasInstance() const`
- L325 _function_ `inline bool UBTNode::IsInstanced() const`
- L331 _function_ `template<typename T> T* UBTNode::InitializeNodeMemory(uint8* NodeMemory, EBTMemoryInit::Type InitType) const`
- L341 _function_ `template <typename T> void UBTNode::CleanupNodeMemory(uint8* NodeMemory, EBTMemoryClear::Type CleanupType) const`
- L353 _function_ `template<typename T> T* UBTNode::GetNodeMemory(FBehaviorTreeSearchData& SearchData) const`
- L359 _function_ `template<typename T> const T* UBTNode::GetNodeMemory(const FBehaviorTreeSearchData& SearchData) const`
- L365 _function_ `template<typename T> T* UBTNode::GetNodeMemory(FBehaviorTreeInstance& BTInstance) const`
- L371 _function_ `template<typename T> const T* UBTNode::GetNodeMemory(const FBehaviorTreeInstance& BTInstance) const`
- L377 _function_ `template<typename T> T* UBTNode::CastInstanceNodeMemory(uint8* NodeMemory) const`
- L387 _function_ `template<typename T> T* UBTNode::GetSpecialNodeMemory(uint8* NodeMemory) const`

#### Free symbols / members of external scopes

- L23 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogBehaviorTree, Display, All);`

### `Source/Runtime/AIModule/Classes/BehaviorTree/BTService.h` (Public)


#### class `UBTService`  
`class UBTService : public UBTAuxiliaryNode`  
_L34-102_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UBTAuxiliaryNode`
- L38 _private prototype_ `virtual FString GetStaticDescription() const override;`
- L40 _private prototype_ `void NotifyParentActivation(FBehaviorTreeSearchData& SearchData);`
- L45 _protected prototype_ `FString GetStaticTickIntervalDescription() const;` — Gets the description of our tick interval
- L48 _protected prototype_ `virtual FString GetStaticServiceDescription() const;` — Gets the description for our service
- L52 _protected member_ `float Interval;` — `UPROPERTY(Category=Service, EditAnywhere, meta=(ClampMin="0.001"))` — defines time span between subsequent ticks of the service
- L56 _protected member_ `float RandomDeviation;` — `UPROPERTY(Category=Service, EditAnywhere, meta=(ClampMin="0.0"))` — adds random range to service's Interval
- L60 _protected member_ `uint32 bCallTickOnSearchStart : 1;` — `UPROPERTY(Category = Service, EditAnywhere, AdvancedDisplay, meta=(EditCondition = bCanTickOnSearchStartBeExposed, EditConditionHides))` — call Tick event when task search enters this node (SearchStart will be called as well)
- L64 _protected member_ `uint32 bRestartTimerOnEachActivation : 1;` — `UPROPERTY(Category = Service, EditAnywhere, AdvancedDisplay)` — if set, next tick time will be always reset to service's interval when node is activated
- L67 _protected member_ `uint32 bNotifyOnSearch : 1;` — if set, service will be notified about search entering underlying branch
- L72 _protected member_ `uint32 bCanTickOnSearchStartBeExposed : 1;` — `UPROPERTY(transient)` — if set, the service exposes the option to call Tick event when task search enters this node
- L79 _protected prototype_ `virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;` — update next tick interval this function should be considered as const (don't modify state of object) if node is not instanced! bNotifyTick must be set to true for this function to be called Calling INIT_SERVICE_NODE_NOTIFY_FLAGS in the constructor of the service will set this flag automatically
- L85 _protected prototype_ `virtual void OnSearchStart(FBehaviorTreeSearchData& SearchData);` — called when search enters underlying branch this function should be considered as const (don't modify state of object) if node is not instanced! bNotifyOnSearch must be set to true for this function to be called Calling INIT_SERVICE_NODE_NOTIFY_FLAGS in the constructor of the service will set this flag automatically
- L88 _protected prototype_ `virtual FName GetNodeIconName() const override;`
- L92 _protected prototype_ `virtual void ScheduleNextTick(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);` — set next tick time
- L95 _protected function_ `template<typename TickNode, typename OnBecomeRelevant, typename OnCeaseRelevant, typename OnSearchStart> void InitNotifyFlags(TickNode, OnBecomeRelevant, OnCeaseRelevant, OnSearchStart)`

#### Free symbols / members of external scopes

- L104 _macro_ `#define INIT_SERVICE_NODE_NOTIFY_FLAGS() \`

### `Source/Runtime/AIModule/Classes/BehaviorTree/BTTaskNode.h` (Public)


#### struct `FBTTaskMemory`  
`struct FBTTaskMemory : public FBTInstancedNodeMemory`  
_L11-15_
- inherits: `FBTInstancedNodeMemory`
- L13 _public member_ `float NextTickRemainingTime = 0.f;`
- L14 _public member_ `float AccumulatedDeltaTime = 0.f;`

#### class `UBTTaskNode`  
`class UBTTaskNode : public UBTNode`  
_L33-136_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UBTNode`
- L40 _private prototype_ `virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);` — starts this task, should return Succeeded, Failed or InProgress (use FinishLatentTask() when returning InProgress) this function should be considered as const (don't modify state of object) if node is not instanced!
- L42 _private prototype_ `virtual uint16 GetSpecialMemorySize() const override;`
- L48 _protected prototype_ `virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);` — aborts this task, should return Aborted or InProgress (use FinishLatentAbort() when returning InProgress) this function should be considered as const (don't modify state of object) if node is not instanced!
- L51 _protected prototype_ `void SetNextTickTime(uint8* NodeMemory, float RemainingTime) const;` — sets next tick time
- L55 _public prototype_ `virtual FName GetNodeIconName() const override;`
- L57 _public prototype_ `virtual void OnGameplayTaskDeactivated(UGameplayTask& Task) override;`
- L60 _public prototype_ `void ReceivedMessage(UBrainComponent* BrainComp, const FAIMessage& Message);` — message observer's hook
- L63 _public prototype_ `EBTNodeResult::Type WrappedExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;` — wrapper for node instancing: ExecuteTask
- L66 _public prototype_ `EBTNodeResult::Type WrappedAbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;` — wrapper for node instancing: AbortTask
- L74 _public prototype_ `bool WrappedTickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds, float& NextNeededDeltaTime) const;` — wrapper for node instancing: TickTask @param OwnerComp	The behavior tree owner of this node @param NodeMemory	The instance memory of the current node @param DeltaSeconds		DeltaTime since last call @param NextNeededDeltaTime		In out parameter, if this node needs a smaller DeltaTime it is the node's responsibility to change it @returns	True if it actually done some processing or false if it was skipped because of not ticking or in between time interval
- L77 _public prototype_ `void WrappedOnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) const;` — wrapper for node instancing: OnTaskFinished
- L80 _public prototype_ `void FinishLatentTask(UBehaviorTreeComponent& OwnerComp, EBTNodeResult::Type TaskResult) const;` — helper function: finish latent executing
- L83 _public prototype_ `void FinishLatentAbort(UBehaviorTreeComponent& OwnerComp) const;` — helper function: finishes latent aborting
- L86 _public prototype_ `bool ShouldIgnoreRestartSelf() const;` — @return true if task search should be discarded when this task is selected to execute but is already running
- L90 _public member_ `TArray<TObjectPtr<UBTService>> Services;` — `UPROPERTY()` — service nodes
- L96 _protected member_ `uint32 bIgnoreRestartSelf : 1;` — `UPROPERTY(EditAnywhere, Category=Task)` — if set, task search will be discarded when this task is selected to execute but is already running
- L99 _protected member_ `uint32 bNotifyTick : 1;` — if set, TickTask will be called
- L102 _protected member_ `uint32 bNotifyTaskFinished : 1;` — if set, OnTaskFinished will be called
- L108 _protected prototype_ `virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);` — ticks this task this function should be considered as const (don't modify state of object) if node is not instanced! bNotifyTick must be set to true for this function to be called Calling INIT_TASK_NODE_NOTIFY_FLAGS in the constructor of the task will set this flag automatically
- L112 _protected prototype_ `virtual void OnMessage(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, FName Message, int32 RequestID, bool bSuccess);` — message handler, default implementation will finish latent execution/abortion this function should be considered as const (don't modify state of object) if node is not instanced!
- L118 _protected prototype_ `virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult);` — called when task execution is finished this function should be considered as const (don't modify state of object) if node is not instanced! bNotifyTaskFinished must be set to true for this function to be called Calling INIT_TASK_NODE_NOTIFY_FLAGS in the constructor of the task will set this flag automatically
- L121 _protected prototype_ `void WaitForMessage(UBehaviorTreeComponent& OwnerComp, FName MessageType) const;` — register message observer
- L122 _protected prototype_ `void WaitForMessage(UBehaviorTreeComponent& OwnerComp, FName MessageType, int32 RequestID) const;`
- L125 _protected prototype_ `void StopWaitingForMessages(UBehaviorTreeComponent& OwnerComp) const;` — unregister message observers
- L128 _protected function_ `template<typename TickTask, typename OnTaskFinished> void InitNotifyFlags(TickTask, OnTaskFinished)`
- L135 _protected member_ `uint8 bTickIntervals : 1;` — if set, conditional tick will use remaining time from node's memory
- L144 _function_ `inline bool UBTTaskNode::ShouldIgnoreRestartSelf() const`

#### Free symbols / members of external scopes

- L138 _macro_ `#define INIT_TASK_NODE_NOTIFY_FLAGS() \`

### `Source/Runtime/AIModule/Classes/BehaviorTree/BehaviorTree.h` (Public)


#### class `UBehaviorTree`  
`class UBehaviorTree : public UObject, public IBlackboardAssetProvider`  
_L15-54_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UObject,IBlackboardAssetProvider`
- L21 _private member_ `TObjectPtr<UBTCompositeNode> RootNode;` — `UPROPERTY(BlueprintReadOnly, Category = BehaviorTree)` — root node of loaded tree
- L27 _private member_ `TObjectPtr<class UEdGraph> BTGraph;` — `UPROPERTY()` — Graph for Behavior Tree
- L31 _private member_ `TArray<FEditedDocumentInfo> LastEditedDocuments;` — `UPROPERTY()` — Info about the graphs we last edited
- L37 _private prototype_ `virtual UBlackboardData* GetBlackboardAsset() const override;` — @return blackboard asset
- L42 _private member_ `TObjectPtr<UBlackboardData> BlackboardAsset;` — `UPROPERTY(BlueprintReadOnly, Category = BehaviorTree)` — blackboard asset for this tree
- L46 _private member_ `TArray<TObjectPtr<UBTDecorator>> RootDecorators;` — `UPROPERTY(BlueprintReadOnly, Category = BehaviorTree)` — root level decorators, used by subtrees
- L50 _private member_ `TArray<FBTDecoratorLogic> RootDecoratorOps;` — `UPROPERTY()` — logic operators for root level decorators, used by subtrees
- L53 _private member_ `uint16 InstanceMemorySize;` — memory size required for instance of this tree

### `Source/Runtime/AIModule/Classes/BehaviorTree/BehaviorTreeComponent.h` (Public)


#### struct `FBTNodeExecutionInfo`  
`struct FBTNodeExecutionInfo`  
_L25-49_
- L28 _public member_ `FBTNodeIndex SearchStart;` — index of first task allowed to be executed
- L31 _public member_ `FBTNodeIndex SearchEnd;` — index of last task allowed to be executed
- L34 _public member_ `TObjectPtr<const UBTCompositeNode> ExecuteNode;` — node to be executed
- L37 _public member_ `uint16 ExecuteInstanceIdx;` — subtree index
- L40 _public member_ `TEnumAsByte<EBTNodeResult::Type> ContinueWithResult;` — result used for resuming execution
- L43 _public member_ `uint8 bTryNextChild : 1;` — if set, tree will try to execute next child of composite instead of forcing branch containing SearchStart
- L46 _public member_ `uint8 bIsRestart : 1;` — if set, request was not instigated by finishing task/initialization but is a restart (e.g. decorator)
- L48 _public function_ `FBTNodeExecutionInfo() : ExecuteNode(NULL), bTryNextChild(false), bIsRestart(false)`

#### struct `FBTPendingExecutionInfo`  
`struct FBTPendingExecutionInfo`  
_L51-68_
- L54 _public member_ `TObjectPtr<UBTTaskNode> NextTask;` — next task to execute
- L57 _public member_ `uint32 bOutOfNodes : 1;` — if set, tree ran out of nodes
- L60 _public member_ `uint32 bLocked : 1;` — if set, request can't be executed
- L62 _public function_ `FBTPendingExecutionInfo() : NextTask(NULL), bOutOfNodes(false), bLocked(false)`
- L63 _public function_ `bool IsSet() const`
- L64 _public function_ `bool IsLocked() const`
- L66 _public function_ `void Lock()`
- L67 _public function_ `void Unlock()`

#### struct `FBTTreeStartInfo`  
`struct FBTTreeStartInfo`  
_L70-79_
- L72 _public member_ `UBehaviorTree* Asset;`
- L73 _public member_ `EBTExecutionMode::Type ExecuteMode;`
- L74 _public member_ `uint8 bPendingInitialize : 1;`
- L76 _public function_ `FBTTreeStartInfo() : Asset(nullptr), ExecuteMode(EBTExecutionMode::Looped), bPendingInitialize(0)`
- L77 _public function_ `bool IsSet() const`
- L78 _public function_ `bool HasPendingInitialize() const`

#### enum `EBTBranchAction`  
`enum class EBTBranchAction : uint16`  
_L81-100_
- L83 _public enumerator_ `None = 0x0`
- L84 _public enumerator_ `DecoratorEvaluate = 0x1`
- L85 _public enumerator_ `DecoratorActivate_IfNotExecuting = 0x2`
- L86 _public enumerator_ `DecoratorActivate_EvenIfExecuting = 0x4`
- L87 _public enumerator_ `DecoratorActivate = DecoratorActivate_IfNotExecuting | DecoratorActivate_EvenIfExecuting`
- L88 _public enumerator_ `DecoratorDeactivate = 0x8`
- L89 _public enumerator_ `UnregisterAuxNodes = 0x10`
- L90 _public enumerator_ `StopTree_Safe = 0x20`
- L91 _public enumerator_ `StopTree_Forced = 0x40`
- L92 _public enumerator_ `ActiveNodeEvaluate = 0x80`
- L93 _public enumerator_ `SubTreeEvaluate = 0x100`
- L94 _public enumerator_ `ProcessPendingInitialize = 0x200`
- L95 _public enumerator_ `Cleanup = 0x400`
- L96 _public enumerator_ `UninitializeComponent = 0x800`
- L97 _public enumerator_ `StopTree = StopTree_Safe | StopTree_Forced`
- L98 _public enumerator_ `Changing_Topology_Actions = UnregisterAuxNodes | StopTree | ProcessPendingInitialize | Cleanup | UninitializeComponent`
- L99 _public enumerator_ `All = DecoratorEvaluate | DecoratorActivate_IfNotExecuting | DecoratorActivate_EvenIfExecuting | DecoratorDeactivate | Changing_Topology_Actions | ActiveNodeEvaluate | SubTreeEvaluate`

#### class `UBehaviorTreeComponent`  
`class UBehaviorTreeComponent : public UBrainComponent`  
_L104-573_
- reflection: `UCLASS(ClassGroup = AI, meta = (BlueprintSpawnableComponent), MinimalAPI)`
- inherits: `UBrainComponent`
- L109 _private prototype_ `virtual void RegisterComponentTickFunctions(bool bRegister) override;` — UActorComponent overrides
- L110 _private prototype_ `virtual void SetComponentTickEnabled(bool bEnabled) override;`
- L113 _private prototype_ `virtual void StartLogic() override;`
- L114 _private prototype_ `virtual void RestartLogic() override;`
- L115 _private prototype_ `virtual void StopLogic(const FString& Reason) override;`
- L116 _private prototype_ `virtual void PauseLogic(const FString& Reason) override;`
- L117 _private prototype_ `virtual EAILogicResuming::Type ResumeLogic(const FString& Reason) override;`
- L120 _private prototype_ `bool TreeHasBeenStarted() const;` — indicates instance has been initialized to work with specific BT asset
- L124 _public prototype_ `UBehaviorTreeComponent(FVTableHelper& Helper);` — DO NOT USE. This constructor is for internal usage only for hot-reload purposes.
- L126 _public prototype_ `virtual bool IsRunning() const override;`
- L127 _public prototype_ `virtual bool IsPaused() const override;`
- L128 _public prototype_ `virtual void Cleanup() override;`
- L129 _public prototype_ `virtual void HandleMessage(const FAIMessage& Message) override;`
- L133 _public prototype_ `virtual void UninitializeComponent() override;`
- L137 _public prototype_ `void StartTree(UBehaviorTree& Asset, EBTExecutionMode::Type ExecuteMode = EBTExecutionMode::Looped);` — starts execution from root
- L140 _public prototype_ `void StopTree(EBTStopMode::Type StopMode = EBTStopMode::Safe);` — stops execution
- L146 _public prototype_ `void RestartTree(EBTRestartMode RestartMode = EBTRestartMode::ForceReevaluateRootNode);` — restarts execution from root @param RestartMode to force the reevaluation of the root node, which could skip active nodes that are removed and then readded (default) or a complete restart from scratch of the tree (equivalent of StopTree then StartTree)
- L149 _public prototype_ `void RequestExecution(const UBTCompositeNode* RequestedOn, const int32 InstanceIdx, const UBTNode* RequestedBy, const int32 RequestedByChildIndex, const EBTNodeResult::Type ContinueWithResult, bool bStoreForDebugger = true);` — request execution change
- L154 _public function_ `void RequestExecution(const UBTDecorator* RequestedBy)` — replaced by the RequestBranchEvaluation from decorator
- L157 _public function_ `void RequestExecution(EBTNodeResult::Type ContinueWithResult)` — replaced by RequestBranchEvaluation with EBTNodeResult
- L161 _public prototype_ `void RequestUnregisterAuxNodesInBranch(const UBTCompositeNode* Node);` — `UE_DEPRECATED(5.0, "This function is deprecated. Please use RequestBranchDeactivation instead.")` — request unregistration of aux nodes in the specified branch
- L164 _public prototype_ `void RequestBranchEvaluation(EBTNodeResult::Type ContinueWithResult);` — request branch evaluation: helper for active node (ex: tasks)
- L167 _public prototype_ `void RequestBranchEvaluation(const UBTDecorator& RequestedBy);` — request branch evaluation: helper for decorator
- L170 _public prototype_ `void RequestBranchActivation(const UBTDecorator& RequestedBy, const bool bRequestEvenIfExecuting);` — request branch activation: helper for decorator
- L173 _public prototype_ `void RequestBranchDeactivation(const UBTDecorator& RequestedBy);` — request branch deactivation: helper for decorator
- L176 _public prototype_ `void OnTaskFinished(const UBTTaskNode* TaskNode, EBTNodeResult::Type TaskResult);` — finish latent execution or abort
- L179 _public prototype_ `void RegisterMessageObserver(const UBTTaskNode* TaskNode, FName MessageType);` — setup message observer for given task
- L180 _public prototype_ `void RegisterMessageObserver(const UBTTaskNode* TaskNode, FName MessageType, FAIRequestID MessageID);`
- L183 _public prototype_ `void UnregisterMessageObserversFrom(const UBTTaskNode* TaskNode);` — remove message observers registered with task
- L184 _public prototype_ `void UnregisterMessageObserversFrom(const FBTNodeIndex& TaskIdx);`
- L187 _public prototype_ `void RegisterParallelTask(const UBTTaskNode* TaskNode);` — add active parallel task
- L190 _public prototype_ `void UnregisterParallelTask(const UBTTaskNode* TaskNode, uint16 InstanceIdx);` — remove parallel task
- L193 _public prototype_ `void UnregisterAuxNodesUpTo(const FBTNodeIndex& Index);` — unregister all aux nodes less important than given index
- L196 _public prototype_ `void UnregisterAuxNodesInRange(const FBTNodeIndex& FromIndex, const FBTNodeIndex& ToIndex);` — unregister all aux nodes between given execution index range: FromIndex < AuxIndex < ToIndex
- L199 _public prototype_ `void UnregisterAuxNodesInBranch(const UBTCompositeNode* Node, bool bApplyImmediately = true);` — unregister all aux nodes in branch of tree
- L202 _public prototype_ `virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;` — BEGIN UActorComponent overrides
- L206 _public prototype_ `void ScheduleNextTick(float NextDeltaTime);` — Schedule when will be the next tick, 0.0f means next frame, FLT_MAX means never
- L209 _public prototype_ `void ProcessExecutionRequest();` — process execution flow
- L212 _public prototype_ `void ScheduleExecutionUpdate();` — schedule execution flow update in next tick
- L215 _public prototype_ `int32 FindInstanceContainingNode(const UBTNode* Node) const;` — tries to find behavior tree instance in context
- L218 _public prototype_ `UBTNode* FindTemplateNode(const UBTNode* Node) const;` — tries to find template node for given instanced node
- L221 _public prototype_ `UBehaviorTree* GetCurrentTree() const;` — @return current tree
- L224 _public prototype_ `UBehaviorTree* GetRootTree() const;` — @return tree from top of instance stack
- L227 _public prototype_ `const UBTNode* GetActiveNode() const;` — @return active node
- L230 _public prototype_ `uint16 GetActiveInstanceIdx() const;` — get index of active instance on stack
- L233 _public prototype_ `uint8* GetNodeMemory(const UBTNode* Node, int32 InstanceIdx) const;` — @return node memory
- L236 _public prototype_ `virtual uint8* GetNodeMemoryAux(const UBTNode* Node, int32 InstanceIdx) const;` — @return node memory. Virtual override for when GetNodeMemory fails to find NodeMemory
- L239 _public prototype_ `bool IsRestartPending() const;` — @return true if ExecutionRequest is switching to higher priority node
- L242 _public prototype_ `bool IsAbortPending() const;` — @return true if waiting for abort to finish
- L245 _public prototype_ `bool IsExecutingBranch(const UBTNode* Node, int32 ChildIndex = -1) const;` — @return true if active node is one of child nodes of given one
- L248 _public prototype_ `bool IsAuxNodeActive(const UBTAuxiliaryNode* AuxNode) const;` — @return true if aux node is currently active
- L249 _public prototype_ `bool IsAuxNodeActive(const UBTAuxiliaryNode* AuxNodeTemplate, int32 InstanceIdx) const;`
- L252 _public function_ `bool IsInstanceStackEmpty() const` — Returns true if InstanceStack contains any BT runtime instances
- L258 _public function_ `float GetAccumulatedTickDeltaTime() const` — Returns the accumulated delta time for the current tick
- L264 _public prototype_ `EBTTaskStatus::Type GetTaskStatus(const UBTTaskNode* TaskNode) const;` — @return status of speficied task
- L266 _public prototype_ `virtual FString GetDebugInfoString() const override;`
- L267 _public prototype_ `virtual FString DescribeActiveTasks() const;`
- L268 _public prototype_ `virtual FString DescribeActiveTrees() const;`
- L272 _public prototype_ `double GetTagCooldownEndTime(FGameplayTag CooldownTag) const;` — `UFUNCTION(BlueprintCallable, Category = "AI|Logic")` — @return the cooldown tag end time, 0.0f if CooldownTag is not found
- L276 _public prototype_ `void AddCooldownTagDuration(FGameplayTag CooldownTag, float CooldownDuration, bool bAddToExistingDuration);` — `UFUNCTION(BlueprintCallable, Category = "AI|Logic")` — add to the cooldown tag's duration
- L280 _public prototype_ `virtual void SetDynamicSubtree(FGameplayTag InjectTag, UBehaviorTree* BehaviorAsset);` — `UFUNCTION(BlueprintCallable, Category="AI|Logic")` — assign subtree to RunBehaviorDynamic task specified by tag.
- L283 _public prototype_ `virtual void SetDynamicSubtree(FGameplayTag InjectTag, UBehaviorTree* BehaviorAsset, UBTCompositeNode* OptionalStartingNode);` — assign subtree to RunBehaviorDynamic task specified by tag. Optional Starting Node can be given if the location in the tree is known to avoid parsing the whole tree.
- L286 _public prototype_ `void ForEachChildTask(TFunctionRef<void (UBTTaskNode&, const FBehaviorTreeInstance&, int32 InstanceIndex)> Functor);` — Will call the given functor on each task node in the current instance stacks.
- L289 _public prototype_ `void ForEachChildTask(UBTCompositeNode& StartNode, int32 InstanceIndex, TFunctionRef<void(UBTTaskNode&, const FBehaviorTreeInstance&, int32 InstanceIndex)> Functor);` — Will call the given functor on each child node from the given start node. InstanceIndex can be found using FindInstanceContainingNode.
- L292 _public prototype_ `static void EndFrame();`
- L296 _public prototype_ `virtual void DescribeSelfToVisLog(struct FVisualLogEntry* Snapshot) const override;`
- L301 _public function_ `void SetCSVTickStatName(const char* InCSVTickStatName)` — Set a custom CSV tick stat name, must point to a static string
- L304 _public prototype_ `static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);`
- L308 _protected member_ `TArray<FBehaviorTreeInstance> InstanceStack;` — stack of behavior tree instances
- L311 _protected member_ `TArray<FBehaviorTreeInstanceId> KnownInstances;` — list of known subtree instances
- L315 _protected member_ `TArray<TObjectPtr<UBTNode>> NodeInstances;` — `UPROPERTY(transient)` — instanced nodes
- L318 _protected member_ `FBehaviorTreeSearchData SearchData;` — search data being currently used
- L321 _protected member_ `FBTNodeExecutionInfo ExecutionRequest;` — execution request, search will be performed when current task finish execution/aborting
- L324 _protected member_ `FBTPendingExecutionInfo PendingExecution;` — result of ExecutionRequest, will be applied when current task finish aborting
- L346 _protected member_ `EBTBranchAction SuspendedBranchActions;` — Type of suspended branch action
- L349 _protected member_ `TArray<FBranchActionInfo> PendingBranchActionRequests;` — list of all pending branch action requests
- L352 _protected member_ `FBTTreeStartInfo TreeStartInfo;` — stored data for starting new tree, waits until previously running finishes aborting
- L355 _protected member_ `TMultiMap<FBTNodeIndex,FAIMessageObserverHandle> TaskMessageObservers;` — message observers mapped by instance & execution index
- L358 _protected member_ `TMap<FGameplayTag, double> CooldownTagsMap;` — behavior cooldowns mapped by tag to last time it was set
- L362 _protected member_ `mutable TArray<TArray<FBehaviorTreeDebuggerInstance::FNodeFlowData> > CurrentSearchFlow;` — search flow for debugger
- L363 _protected member_ `mutable TArray<TArray<FBehaviorTreeDebuggerInstance::FNodeFlowData> > CurrentRestarts;`
- L364 _protected member_ `mutable TMap<FName, FString> SearchStartBlackboard;`
- L365 _protected member_ `mutable TArray<FBehaviorTreeDebuggerInstance> RemovedInstances;`
- L368 _protected member_ `mutable TArray<FBehaviorTreeExecutionStep> DebuggerSteps;` — debugger's recorded data
- L371 _protected member_ `static int32 ActiveDebuggerCounter;` — set when at least one debugger window is opened
- L376 _protected member_ `static bool bAddedEndFrameCallback;`
- L377 _protected member_ `static double FrameSearchTime;`
- L378 _protected member_ `static int32 NumSearchTimeCalls;`
- L382 _protected member_ `uint16 ActiveInstanceIdx;` — index of last active instance on stack
- L385 _protected member_ `uint8 bLoopExecution : 1;` — loops tree execution
- L388 _protected member_ `uint8 bWaitingForLatentAborts : 1;` — set when execution is waiting for tasks to finish their latent abort (current or parallel's main)
- L391 _protected member_ `uint8 bRequestedFlowUpdate : 1;` — set when execution update is scheduled for next tick
- L394 _protected member_ `uint8 bRequestedStop : 1;` — set when tree stop was called
- L397 _protected member_ `uint8 bIsRunning : 1;` — if set, tree execution is allowed
- L400 _protected member_ `uint8 bIsPaused : 1;` — if set, execution requests will be postponed
- L404 _protected prototype_ `bool PushInstance(UBehaviorTree& TreeAsset);` — push behavior tree instance on execution stack @NOTE: should never be called out-side of BT execution, meaning only BT tasks can push another BT instance!
- L407 _protected prototype_ `uint8 UpdateInstanceId(UBehaviorTree* TreeAsset, const UBTNode* OriginNode, int32 OriginInstanceIdx);` — add unique Id of newly created subtree to KnownInstances list and return its index
- L410 _protected prototype_ `void RemoveAllInstances();` — remove instanced nodes, known subtree instances and safely clears their persistent memory
- L413 _protected prototype_ `void CopyInstanceMemoryToPersistent();` — copy memory block from running instances to persistent memory
- L416 _protected prototype_ `void CopyInstanceMemoryFromPersistent();` — copy memory block from persistent memory to running instances (rollback)
- L419 _protected prototype_ `virtual void OnTreeFinished();` — called when tree runs out of nodes to execute
- L422 _protected prototype_ `void ApplySearchData(UBTNode* NewActiveNode);` — apply pending node updates from SearchData
- L425 _protected prototype_ `void ApplyDiscardedSearch();` — apply pending node updates required for discarded search
- L429 _protected prototype_ `void ApplySearchUpdates(const TArray<FBehaviorTreeSearchUpdate>& UpdateList, int32 NewNodeExecutionIndex, bool bPostUpdate = false);` — `UE_DEPRECATED(5.4, "This function is deprecated. Please use ApplyAllSearchUpdates instead.")` — apply updates from specific list
- L436 _protected prototype_ `void ApplyAllSearchUpdates(const TArray<FBehaviorTreeSearchUpdate>& UpdateList, int32 NewNodeExecutionIndex, bool bDoPostUpdate = true, bool bAllowTaskUpdates = true);` — Apply updates and post update from specified UpdateList. @param bDoPostUpdate if true the post updates will also be processed. @param bAllowTaskUpdates If false Task node updates will not be processed from the UpdateList.
- L439 _protected prototype_ `void AbortCurrentTask();` — abort currently executed task
- L442 _protected prototype_ `void ExecuteTask(UBTTaskNode* TaskNode);` — execute new task
- L445 _protected prototype_ `bool DeactivateUpTo(const UBTCompositeNode* Node, uint16 NodeInstanceIdx, EBTNodeResult::Type& NodeResult, int32& OutLastDeactivatedChildIndex);` — deactivate all nodes up to requested one
- L448 _protected prototype_ `bool TrackPendingLatentAborts();` — returns true if execution was waiting on latent aborts and they are all finished;
- L451 _protected prototype_ `void TrackNewLatentAborts();` — tracks if there are new tasks using latent abort in progress
- L454 _protected prototype_ `bool HasActiveLatentAborts() const;` — return true if the current or any parallel task has a latent abort in progress
- L457 _protected prototype_ `void ProcessPendingExecution();` — apply pending execution from last task search
- L460 _protected prototype_ `void ProcessPendingInitialize();` — apply pending tree initialization
- L463 _protected prototype_ `void RollbackSearchChanges();` — restore state of tree to state before search
- L466 _protected prototype_ `void StoreDebuggerExecutionStep(EBTExecutionSnap::Type SnapType);` — make a snapshot for debugger
- L469 _protected prototype_ `void StoreDebuggerInstance(FBehaviorTreeDebuggerInstance& InstanceInfo, uint16 InstanceIdx, EBTExecutionSnap::Type SnapType) const;` — make a snapshot for debugger from given subtree instance
- L470 _protected prototype_ `void StoreDebuggerRemovedInstance(uint16 InstanceIdx) const;`
- L473 _protected prototype_ `void StoreDebuggerSearchStep(const UBTNode* Node, uint16 InstanceIdx, EBTNodeResult::Type NodeResult) const;` — store search step for debugger
- L474 _protected prototype_ `void StoreDebuggerSearchStep(const UBTNode* Node, uint16 InstanceIdx, bool bPassed) const;`
- L477 _protected prototype_ `void StoreDebuggerRestart(const UBTNode* Node, uint16 InstanceIdx, bool bAllowed);` — store restarting node for debugger
- L480 _protected prototype_ `void StoreDebuggerBlackboard(TMap<FName, FString>& BlackboardValueDesc) const;` — describe blackboard's key values
- L483 _protected prototype_ `void StoreDebuggerRuntimeValues(TArray<FString>& RuntimeDescriptions, UBTNode* RootNode, uint16 InstanceIdx) const;` — gather nodes runtime descriptions
- L486 _protected prototype_ `void UpdateDebuggerAfterExecution(const UBTTaskNode* TaskNode, uint16 InstanceIdx) const;` — update runtime description of given task node in latest debugger's snapshot
- L489 _protected prototype_ `static bool IsDebuggerActive();` — check if debugger is currently running and can gather data
- L492 _protected prototype_ `EBTNodeRelativePriority CalculateRelativePriority(const UBTNode* NodeA, const UBTNode* NodeB) const;` — Return NodeA's relative priority in regards to NodeB
- L495 _protected prototype_ `void EvaluateBranch(EBTNodeResult::Type LastResult);` — Evaluate a branch as current active node is finished
- L498 _protected prototype_ `void EvaluateBranch(const UBTDecorator& RequestedBy);` — Evaluate a branch as the decorator conditions have changed
- L501 _protected prototype_ `void ActivateBranch(const UBTDecorator& RequestedBy, bool bRequestEvenIfNotExecuting);` — Activate a branch as the decorator conditions are now passing
- L504 _protected prototype_ `void DeactivateBranch(const UBTDecorator& RequestedBy);` — Deactivate a branch as the decorator conditions are not passing anymore
- L507 _protected prototype_ `void SuspendBranchActions(EBTBranchAction BranchActions = EBTBranchAction::All);` — Suspend any branch actions and queue them to be processed later by ResumeBranchActions()
- L510 _protected prototype_ `void ResumeBranchActions();` — Resume branch actions and execute all the queued up ones
- L513 _protected function_ `void SuspendBranchDeactivation()` — `UE_DEPRECATED(5.1, "This function is deprecated. Please use SuspendBranchActions instead.")`
- L516 _protected function_ `void ResumeBranchDeactivation()` — `UE_DEPRECATED(5.1, "This function is deprecated. Please use ResumeBranchActions instead.")`
- L532 _protected prototype_ `void TickNewlyAddedAuxNodesHelper();`
- L535 _protected typedef_ `typedef FBTSuspendBranchActionsScoped FBTSuspendBranchDeactivationScoped;` — `UE_DEPRECATED(5.1, "This struct is deprecated. Please use FBTSuspendBranchActionsScoped instead.")`
- L547 _private prototype_ `void ApplySearchUpdatesImpl(const TArray<FBehaviorTreeSearchUpdate>& UpdateList, int32 NewNodeExecutionIndex, bool bPostUpdate, bool bAllowTaskUpdates);` — Please don't call this function directly instead call ApplyAllSearchUpdates
- L552 _protected member_ `TObjectPtr<UBehaviorTree> DefaultBehaviorTreeAsset;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = AI)` — data asset defining the tree
- L555 _protected member_ `bool bTickedOnce = false;` — Used to tell tickmanager that we want interval ticking
- L558 _protected member_ `float NextTickDeltaTime = 0.f;` — Predicted next DeltaTime
- L561 _protected member_ `float AccumulatedTickDeltaTime = 0.f;` — Accumulated DeltaTime if ticked more than predicted next delta time
- L564 _protected member_ `float CurrentFrameDeltaTime = 0.f;` — Current frame DeltaTime
- L567 _protected member_ `double LastRequestedDeltaTimeGameTime = 0;` — GameTime of the last DeltaTime request, used for debugging to output warnings about ticking
- L571 _protected member_ `const char* CSVTickStatName = "Be` — CSV tick stat name. Can be changed but must point to a static string
- L578 _function_ `inline UBehaviorTree* UBehaviorTreeComponent::GetCurrentTree() const`
- L583 _function_ `inline UBehaviorTree* UBehaviorTreeComponent::GetRootTree() const`
- L588 _function_ `inline const UBTNode* UBehaviorTreeComponent::GetActiveNode() const`
- L593 _function_ `inline uint16 UBehaviorTreeComponent::GetActiveInstanceIdx() const`
- L598 _function_ `inline bool UBehaviorTreeComponent::IsRestartPending() const`
- L603 _function_ `inline bool UBehaviorTreeComponent::IsAbortPending() const`

#### struct `UBehaviorTreeComponent::FBranchActionInfo`  
`struct FBranchActionInfo`  
_L326-343_
- L328 _public function_ `FBranchActionInfo(const EBTBranchAction InAction) : Action(InAction)`
- L331 _public function_ `FBranchActionInfo(const UBTNode* InNode, const EBTBranchAction InAction) : Node(InNode) , Action(InAction)`
- L335 _public function_ `FBranchActionInfo(const UBTNode* InNode, EBTNodeResult::Type InContinueWithResult, const EBTBranchAction InAction) : Node(InNode) , ContinueWithResult(InContinueWithResult) , Action(InAction)`
- L340 _public member_ `TObjectPtr<const UBTNode> Node = nullptr;`
- L341 _public member_ `EBTNodeResult::Type ContinueWithResult = EBTNodeResult::Succeeded;`
- L342 _public member_ `EBTBranchAction Action;`

#### struct `UBehaviorTreeComponent::FBTSuspendBranchActionsScoped`  
`struct FBTSuspendBranchActionsScoped`  
_L518-530_
- L520 _public function_ `FBTSuspendBranchActionsScoped(UBehaviorTreeComponent& InBTComp, EBTBranchAction BranchActions = EBTBranchAction::All) : BTComp(InBTComp)`
- L525 _public function_ `~FBTSuspendBranchActionsScoped()`
- L529 _public member_ `UBehaviorTreeComponent& BTComp;`

#### Free symbols / members of external scopes

- L101 _prototype_ `ENUM_CLASS_FLAGS(EBTBranchAction);`

### `Source/Runtime/AIModule/Classes/BehaviorTree/BehaviorTreeManager.h` (Public)


#### struct `FBehaviorTreeTemplateInfo`  
`struct FBehaviorTreeTemplateInfo`  
_L16-30_
- reflection: `USTRUCT()`
- L22 _public member_ `TObjectPtr<UBehaviorTree> Asset = nullptr;` — `UPROPERTY()` — behavior tree asset
- L26 _public member_ `TObjectPtr<UBTCompositeNode> Template = nullptr;` — `UPROPERTY(transient)` — initialized template
- L29 _public member_ `uint16 InstanceMemorySize;` — size required for instance memory

#### class `UBehaviorTreeManager`  
`class UBehaviorTreeManager : public UObject`  
_L33-77_
- reflection: `UCLASS(config=Engine, Transient, MinimalAPI)`
- inherits: `UObject`
- L39 _private member_ `int32 MaxDebuggerSteps;` — `UPROPERTY(config)` — limit for recording execution steps for debugger
- L42 _private prototype_ `bool LoadTree(UBehaviorTree& Asset, UBTCompositeNode*& Root, uint16& InstanceMemorySize);` — get behavior tree template for given blueprint
- L45 _private prototype_ `static uint16 GetAlignedDataSize(uint16 Size);` — get aligned memory size
- L48 _private prototype_ `static void InitializeMemoryHelper(const TArray<UBTDecorator*>& Nodes, TArray<uint16>& MemoryOffsets, int32& MemorySize, bool bForceInstancing = false);` — helper function for sorting and aligning node memory
- L51 _private prototype_ `virtual void FinishDestroy() override;` — cleanup hooks for map loading
- L53 _private prototype_ `void DumpUsageStats() const;`
- L56 _private prototype_ `void AddActiveComponent(UBehaviorTreeComponent& Component);` — register new behavior tree component for tracking
- L59 _private prototype_ `void RemoveActiveComponent(UBehaviorTreeComponent& Component);` — unregister behavior tree component from tracking
- L61 _private prototype_ `static UBehaviorTreeManager* GetCurrent(UWorld* World);`
- L62 _private prototype_ `static UBehaviorTreeManager* GetCurrent(UObject* WorldContextObject);`
- L64 _private function_ `TConstArrayView<TObjectPtr<UBehaviorTreeComponent>> GetActiveComponents() const`
- L73 _protected member_ `TArray<FBehaviorTreeTemplateInfo> LoadedTemplates;` — `UPROPERTY()` — initialized tree templates
- L76 _protected member_ `TArray<TObjectPtr<UBehaviorTreeComponent>> ActiveComponents;` — `UPROPERTY()`

### `Source/Runtime/AIModule/Classes/BehaviorTree/BehaviorTreeTypes.h` (Public)


#### struct `TIsValidVariadicFunctionArg`  
`template <> struct TIsValidVariadicFunctionArg<FBlackboard::FKey>`  
_L48-51_

#### enum `TIsValidVariadicFunctionArg::(anonymous)`  
`enum`  
_L50-50_

#### enum `EBlackboardNotificationResult`  
`enum class EBlackboardNotificationResult : uint8`  
_L61-65_
- L63 _public enumerator_ `RemoveObserver`
- L64 _public enumerator_ `ContinueObserving`

#### enum `EBTNodeResult::Type`  
`enum Type : int`  
_L86-96_
- desc: keep in sync with DescribeNodeResult()
- L89 _public enumerator_ `Succeeded` — finished as success
- L91 _public enumerator_ `Failed` — finished as failure
- L93 _public enumerator_ `Aborted` — finished aborting = failure
- L95 _public enumerator_ `InProgress` — not finished yet

#### enum `EBTExecutionMode::Type`  
`enum Type`  
_L101-105_
- L103 _public enumerator_ `SingleRun`
- L104 _public enumerator_ `Looped`

#### enum `EBTStopMode::Type`  
`enum Type`  
_L110-114_
- L112 _public enumerator_ `Safe`
- L113 _public enumerator_ `Forced`

#### enum `EBTRestartMode`  
`enum class EBTRestartMode : uint8`  
_L117-121_
- L119 _public enumerator_ `ForceReevaluateRootNode` — (Default) will just request a new execution on the root node and any active nodes that gets re-added will not get CeaseRelevant/BecomeRelevant notification
- L120 _public enumerator_ `CompleteRestart` — essentially equivalent to calling StopTree and then StartTree. Every active node is going to be removed and the execution started from the root

#### enum `EBTMemoryInit::Type`  
`enum Type`  
_L125-129_
- L127 _public enumerator_ `Initialize` — first time initialization
- L128 _public enumerator_ `RestoreSubtree` — loading saved data on reentering subtree

#### enum `EBTMemoryClear::Type`  
`enum Type`  
_L134-138_
- L136 _public enumerator_ `Destroy` — final clear
- L137 _public enumerator_ `StoreSubtree` — saving data on leaving subtree

#### enum `EBTFlowAbortMode::Type`  
`enum Type : int`  
_L146-152_
- L148 _public enumerator_ `None UMETA(DisplayName="Nothing")`
- L149 _public enumerator_ `LowerPriority UMETA(DisplayName="Lower Priority")`
- L150 _public enumerator_ `Self UMETA(DisplayName="Self")`
- L151 _public enumerator_ `Both UMETA(DisplayName="Both")`

#### enum `EBTActiveNode::Type`  
`enum Type`  
_L158-164_
- desc: keep in sync with DescribeActiveNode()
- L160 _public enumerator_ `Composite`
- L161 _public enumerator_ `ActiveTask`
- L162 _public enumerator_ `AbortingTask`
- L163 _public enumerator_ `InactiveTask`

#### enum `EBTTaskStatus::Type`  
`enum Type`  
_L170-175_
- desc: keep in sync with DescribeTaskStatus()
- L172 _public enumerator_ `Active`
- L173 _public enumerator_ `Aborting`
- L174 _public enumerator_ `Inactive`

#### enum `EBTNodeUpdateMode::Type`  
`enum Type`  
_L181-186_
- desc: keep in sync with DescribeNodeUpdateMode()
- L183 _public enumerator_ `Unknown`
- L184 _public enumerator_ `Add` — add node
- L185 _public enumerator_ `Remove` — remove node

#### struct `FBehaviorTreeParallelTask`  
`struct FBehaviorTreeParallelTask`  
_L190-203_
- desc: wrapper struct for holding a parallel task node and its status
- L193 _public member_ `TObjectPtr<const UBTTaskNode> TaskNode;` — worker object
- L196 _public member_ `EBTTaskStatus::Type Status;` — additional mode data used for context switching
- L198 _public function_ `FBehaviorTreeParallelTask() : TaskNode(nullptr)`
- L199 _public function_ `FBehaviorTreeParallelTask(const UBTTaskNode* InTaskNode, EBTTaskStatus::Type InStatus) : TaskNode(InTaskNode), Status(InStatus)`
- L201 _public function_ `bool operator==(const FBehaviorTreeParallelTask& Other) const`
- L202 _public function_ `bool operator==(const UBTTaskNode* OtherTask) const`

#### enum `EBTExecutionSnap::Type`  
`enum Type`  
_L207-211_
- L209 _public enumerator_ `Regular`
- L210 _public enumerator_ `OutOfNodes`

#### enum `EBTDescriptionVerbosity::Type`  
`enum Type`  
_L216-220_
- L218 _public enumerator_ `Basic`
- L219 _public enumerator_ `Detailed`

#### enum `EBTNodeRelativePriority`  
`enum class EBTNodeRelativePriority : uint8`  
_L223-228_
- L225 _public enumerator_ `Lower`
- L226 _public enumerator_ `Same`
- L227 _public enumerator_ `Higher`

#### struct `FBehaviorTreeDebuggerInstance`  
`struct FBehaviorTreeDebuggerInstance`  
_L231-264_
- desc: debugger data about subtree instance
- L243 _public function_ `FBehaviorTreeDebuggerInstance() : TreeAsset(nullptr), RootNode(nullptr)`
- L246 _public member_ `UBehaviorTree* TreeAsset;` — behavior tree asset
- L249 _public member_ `TWeakObjectPtr<UBTCompositeNode> RootNode;` — root node in template
- L252 _public member_ `TArray<uint16> ActivePath;` — execution indices of active nodes
- L255 _public member_ `TArray<uint16> AdditionalActiveNodes;` — execution indices of active nodes
- L258 _public member_ `TArray<FNodeFlowData> PathFromPrevious;` — search flow from previous state
- L261 _public member_ `TArray<FString> RuntimeDesc;` — runtime descriptions for each execution index
- L263 _public function_ `inline bool IsValid() const`

#### struct `FBehaviorTreeDebuggerInstance::FNodeFlowData`  
`struct FNodeFlowData`  
_L233-241_
- L235 _public member_ `uint16 ExecutionIndex;`
- L236 _public member_ `uint16 bPassed : 1;`
- L237 _public member_ `uint16 bTrigger : 1;`
- L238 _public member_ `uint16 bDiscardedTrigger : 1;`
- L240 _public function_ `FNodeFlowData() : ExecutionIndex(INDEX_NONE), bPassed(0), bTrigger(0), bDiscardedTrigger(0)`

#### struct `FBehaviorTreeExecutionStep`  
`struct FBehaviorTreeExecutionStep`  
_L267-287_
- desc: debugger data about current execution step
- L269 _public function_ `FBehaviorTreeExecutionStep() : TimeStamp(0.), ExecutionStepId(InvalidExecutionId)`
- L272 _public member_ `TArray<FBehaviorTreeDebuggerInstance> InstanceStack;` — subtree instance stack
- L275 _public member_ `TMap<FName, FString> BlackboardValues;` — blackboard snapshot: value descriptions
- L278 _public member_ `double TimeStamp;` — Game world's time stamp of this step
- L280 _public member_ `inline static constexpr int32 InvalidExecutionId = -1;`
- L283 _public member_ `int32 ExecutionStepId;` — Id of execution step
- L286 _public member_ `bool bIsExecutionPaused = false;` — If true, the behavior was paused in this execution step.

#### struct `FBehaviorTreeInstanceId`  
`struct FBehaviorTreeInstanceId`  
_L290-313_
- desc: identifier of subtree instance
- L293 _public member_ `TObjectPtr<UBehaviorTree> TreeAsset;` — behavior tree asset
- L296 _public member_ `TObjectPtr<UBTCompositeNode> RootNode;` — root node in template for cleanup purposes
- L299 _public member_ `TArray<uint16> Path;` — execution index path from root
- L302 _public member_ `TArray<uint8> InstanceMemory;` — persistent instance memory
- L305 _public member_ `int32 FirstNodeInstance;` — index of first node instance (BehaviorTreeComponent.NodeInstances)
- L307 _public function_ `FBehaviorTreeInstanceId() : TreeAsset(0), RootNode(0), FirstNodeInstance(-1)`
- L309 _public function_ `bool operator==(const FBehaviorTreeInstanceId& Other) const`

#### struct `FBehaviorTreeInstance`  
`struct FBehaviorTreeInstance`  
_L319-447_
- desc: data required for instance of single subtree
- L322 _public member_ `TObjectPtr<UBTCompositeNode> RootNode;` — root node in template
- L325 _public member_ `TObjectPtr<UBTNode> ActiveNode;` — active node in template
- L328 _public member_ `TArray<TObjectPtr<UBTAuxiliaryNode>> ActiveAuxNodes;` — active auxiliary nodes
- L331 _public member_ `TArray<FBehaviorTreeParallelTask> ParallelTasks;` — active parallel tasks
- L334 _public member_ `TArray<uint8> InstanceMemory;` — memory: instance
- L337 _public member_ `uint8 InstanceIdIndex;` — index of identifier (BehaviorTreeComponent.KnownInstances)
- L340 _public member_ `TEnumAsByte<EBTActiveNode::Type> ActiveNodeType;` — active node type
- L343 _public member_ `FBTInstanceDeactivation DeactivationNotify;` — delegate sending a notify when tree instance is removed from active stack
- L345 _public prototype_ `FBehaviorTreeInstance();`
- L348 _public prototype_ `FBehaviorTreeInstance(const FBehaviorTreeInstance& Other);` — `UE_DEPRECATED(5.2, "Copying FBehaviorTreeInstance constructor has been deprecated in favor of move-constructor")`
- L351 _public prototype_ `FBehaviorTreeInstance& operator=(const FBehaviorTreeInstance& Other) = default;` — `UE_DEPRECATED(5.2, "Copying FBehaviorTreeInstance assignement operator has been deprecated in favor of move assignement operator")`
- L353 _public prototype_ `FBehaviorTreeInstance(FBehaviorTreeInstance&& Other);`
- L354 _public prototype_ `FBehaviorTreeInstance& operator=(FBehaviorTreeInstance&& Other);`
- L356 _public prototype_ `FBehaviorTreeInstance(int32 MemorySize);`
- L357 _public prototype_ `~FBehaviorTreeInstance();`
- L360 _public prototype_ `void IncMemoryStats() const;`
- L361 _public prototype_ `void DecMemoryStats() const;`
- L362 _public prototype_ `uint32 GetAllocatedSize() const;`
- L364 _public function_ `inline uint32 GetAllocatedSize() const`
- L365 _public function_ `inline void IncMemoryStats() const`
- L366 _public function_ `inline void DecMemoryStats() const`
- L370 _public prototype_ `void Initialize(UBehaviorTreeComponent& OwnerComp, UBTCompositeNode& Node, int32& InstancedIndex, EBTMemoryInit::Type InitType);` — initialize memory and create node instances
- L373 _public prototype_ `void Cleanup(UBehaviorTreeComponent& OwnerComp, EBTMemoryClear::Type CleanupType);` — cleanup node instances
- L376 _public prototype_ `bool HasActiveNode(uint16 TestExecutionIndex) const;` — check if instance has active node with given execution index
- L379 _public prototype_ `void DeactivateNodes(FBehaviorTreeSearchData& SearchData, uint16 InstanceIndex);` — deactivate all active aux nodes and remove their requests from SearchData
- L382 _public function_ `TArrayView<UBTAuxiliaryNode* const> GetActiveAuxNodes() const` — get list of all active auxiliary nodes
- L385 _public prototype_ `void AddToActiveAuxNodes(UBTAuxiliaryNode* AuxNode);` — `UE_DEPRECATED(5.4, "This function is deprecated. Please use version that takes UBehaviorTreeComponent.")`
- L388 _public prototype_ `void AddToActiveAuxNodes(UBehaviorTreeComponent& OwnerComp, UBTAuxiliaryNode* AuxNode);` — add specified node to the active nodes list
- L391 _public prototype_ `void RemoveFromActiveAuxNodes(UBTAuxiliaryNode* AuxNode);` — `UE_DEPRECATED(5.4, "This function is deprecated. Please use version that takes UBehaviorTreeComponent.")`
- L394 _public prototype_ `void RemoveFromActiveAuxNodes(UBehaviorTreeComponent& OwnerComp, UBTAuxiliaryNode* AuxNode);` — remove specified node from the active nodes list
- L397 _public prototype_ `void ResetActiveAuxNodes();` — remove all auxiliary nodes from active nodes list
- L400 _public prototype_ `void ExecuteOnEachAuxNode(TFunctionRef<void(const UBTAuxiliaryNode&)> ExecFunc);` — iterate on auxiliary nodes and call ExecFunc on each of them. Nodes can not be added or removed during the iteration
- L403 _public function_ `TArrayView<const FBehaviorTreeParallelTask> GetParallelTasks() const` — get list of all active parallel tasks
- L406 _public prototype_ `void AddToParallelTasks(FBehaviorTreeParallelTask&& ParallelTask);` — add new parallel task
- L409 _public prototype_ `void RemoveParallelTaskAt(int32 TaskIndex);` — remove parallel task at given index
- L412 _public prototype_ `void MarkParallelTaskAsAbortingAt(int32 TaskIndex);` — mark parallel task at given index as pending abort
- L415 _public function_ `bool IsValidParallelTaskIndex(const int32 Index) const` — indicates if the provided index is a valid parallel task index
- L418 _public prototype_ `void ExecuteOnEachParallelTask(TFunctionRef<void(const FBehaviorTreeParallelTask&, const int32)> ExecFunc);` — iterate on parallel tasks and call ExecFunc on each of them. Supports removing the iterated task while processed
- L421 _public prototype_ `void SetInstanceMemory(const TArray<uint8>& Memory);` — set instance memory
- L424 _public function_ `TArrayView<const uint8> GetInstanceMemory() const` — get instance memory
- L429 _protected prototype_ `void CleanupNodes(UBehaviorTreeComponent& OwnerComp, UBTCompositeNode& Node, EBTMemoryClear::Type CleanupType);` — worker for updating all nodes
- L432 _private prototype_ `void AddToActiveAuxNodesImpl(UBTAuxiliaryNode* AuxNode);`
- L433 _private prototype_ `void RemoveFromActiveAuxNodesImpl(UBTAuxiliaryNode* AuxNode);`
- L438 _private member_ `bool bIteratingNodes = false;` — debug flag to detect modifications to the array of nodes while iterating through it
- L445 _private member_ `int32 ParallelTaskIndex = INDEX_NONE;` — debug flag to detect forbidden modifications to the array of parallel tasks while iterating through it the only allowed modification is to unregister the task on which the exec function is executed @see ExecuteOnEachParallelTask

#### struct `FBTNodeIndex`  
`struct FBTNodeIndex`  
_L449-470_
- L451 _public member_ `static constexpr uint16 InvalidIndex = TNumericLimits<uint16>::Max();` — (This is also the same as INDEX_NONE assigned to IndexType!)
- L454 _public member_ `uint16 InstanceIndex;` — index of instance of stack
- L457 _public member_ `uint16 ExecutionIndex;` — execution index within instance
- L459 _public function_ `FBTNodeIndex() : InstanceIndex(InvalidIndex), ExecutionIndex(InvalidIndex)`
- L460 _public function_ `FBTNodeIndex(uint16 InInstanceIndex, uint16 InExecutionIndex) : InstanceIndex(InInstanceIndex), ExecutionIndex(InExecutionIndex)`
- L462 _public prototype_ `bool TakesPriorityOver(const FBTNodeIndex& Other) const;`
- L463 _public function_ `bool IsSet() const`
- L465 _public function_ `inline bool operator==(const FBTNodeIndex& Other) const`
- L466 _public function_ `inline bool operator!=(const FBTNodeIndex& Other) const`
- L469 _public function_ `inline FString Describe() const`

#### struct `FBTNodeIndexRange`  
`struct FBTNodeIndexRange`  
_L472-493_
- L475 _public member_ `FBTNodeIndex FromIndex;` — first node index
- L478 _public member_ `FBTNodeIndex ToIndex;` — last node index
- L480 _public function_ `FBTNodeIndexRange(const FBTNodeIndex& From, const FBTNodeIndex& To) : FromIndex(From), ToIndex(To)`
- L482 _public function_ `bool IsSet() const`
- L484 _public function_ `bool operator==(const FBTNodeIndexRange& Other) const`
- L485 _public function_ `bool operator!=(const FBTNodeIndexRange& Other) const`
- L487 _public function_ `bool Contains(const FBTNodeIndex& Index) const`
- L492 _public function_ `FString Describe() const`

#### struct `FBehaviorTreeSearchUpdate`  
`struct FBehaviorTreeSearchUpdate`  
_L496-520_
- desc: node update data
- L498 _public member_ `TObjectPtr<UBTAuxiliaryNode> AuxNode;`
- L499 _public member_ `TObjectPtr<UBTTaskNode> TaskNode;`
- L501 _public member_ `uint16 InstanceIndex;`
- L503 _public member_ `TEnumAsByte<EBTNodeUpdateMode::Type> Mode;`
- L506 _public member_ `uint8 bPostUpdate : 1;` — if set, this entry will be applied AFTER other are processed
- L509 _public member_ `mutable uint8 bApplySkipped : 1;` — if set the action was unnecessary (Remove and was already inactive, Add and was already active)
- L511 _public function_ `FBehaviorTreeSearchUpdate() : AuxNode(0), TaskNode(0), InstanceIndex(0), Mode(EBTNodeUpdateMode::Unknown), bPostUpdate(false), bApplySkipped(false)`
- L514 _public function_ `FBehaviorTreeSearchUpdate(const UBTAuxiliaryNode* InAuxNode, uint16 InInstanceIndex, EBTNodeUpdateMode::Type InMode) : AuxNode((UBTAuxiliaryNode*)InAuxNode), TaskNode(0), InstanceIndex(InInstanceIndex), Mode(InMode), bPostUpdate(false), bApplySkipped(false)`
- L517 _public function_ `FBehaviorTreeSearchUpdate(const UBTTaskNode* InTaskNode, uint16 InInstanceIndex, EBTNodeUpdateMode::Type InMode) : AuxNode(0), TaskNode((UBTTaskNode*)InTaskNode), InstanceIndex(InInstanceIndex), Mode(InMode), bPostUpdate(false), bApplySkipped(false)`

#### struct `FBehaviorTreeSearchUpdateNotify`  
`struct FBehaviorTreeSearchUpdateNotify`  
_L523-530_
- desc: instance notify data
- L525 _public member_ `uint16 InstanceIndex;`
- L526 _public member_ `TEnumAsByte<EBTNodeResult::Type> NodeResult;`
- L528 _public function_ `FBehaviorTreeSearchUpdateNotify() : InstanceIndex(0), NodeResult(EBTNodeResult::Succeeded)`
- L529 _public function_ `FBehaviorTreeSearchUpdateNotify(uint16 InInstanceIndex, EBTNodeResult::Type InNodeResult) : InstanceIndex(InInstanceIndex), NodeResult(InNodeResult)`

#### struct `FBehaviorTreeSearchData`  
`struct FBehaviorTreeSearchData`  
_L533-606_
- desc: node search data
- L536 _public member_ `UBehaviorTreeComponent& OwnerComp;` — BT component
- L540 _public member_ `TArray<FBehaviorTreeSearchUpdate> PendingUpdates;` — requested updates of additional nodes (preconditions, services, parallels) buffered during search to prevent instant add & remove pairs
- L543 _public member_ `TArray<FBehaviorTreeSearchUpdateNotify> PendingNotifies;` — notifies for tree instances
- L546 _public member_ `FBTNodeIndex SearchRootNode;` — node under which the search was performed
- L549 _public member_ `FBTNodeIndex SearchStart;` — first node allowed in search
- L552 _public member_ `FBTNodeIndex SearchEnd;` — last node allowed in search
- L555 _public member_ `int32 SearchId;` — search unique number
- L558 _public member_ `int32 RollbackInstanceIdx;` — active instance index to rollback to
- L561 _public member_ `FBTNodeIndex DeactivatedBranchStart;` — start index of the deactivated branch
- L564 _public member_ `FBTNodeIndex DeactivatedBranchEnd;` — end index of the deactivated branch
- L567 _public member_ `FBTNodeIndex RollbackDeactivatedBranchStart;` — saved start index of the deactivated branch for rollback
- L570 _public member_ `FBTNodeIndex RollbackDeactivatedBranchEnd;` — saved end index of the deactivated branch for rollback
- L573 _public member_ `uint32 bFilterOutRequestFromDeactivatedBranch : 1;` — if set, execution request from node in the deactivated branch will be skipped
- L576 _public member_ `uint32 bPostponeSearch : 1;` — if set, current search will be restarted in next tick
- L579 _public member_ `uint32 bSearchInProgress : 1;` — set when task search is in progress
- L582 _public member_ `uint32 bPreserveActiveNodeMemoryOnRollback : 1;` — if set, active node state/memory won't be rolled back
- L585 _public prototype_ `void AddUniqueUpdate(const FBehaviorTreeSearchUpdate& UpdateInfo);` — adds update info to PendingUpdates array, removing all previous updates for this node
- L588 _public prototype_ `void AssignSearchId();` — assign unique Id number
- L591 _public prototype_ `void Reset();` — clear state of search
- L593 _public function_ `FBehaviorTreeSearchData(UBehaviorTreeComponent& InOwnerComp) : OwnerComp(InOwnerComp), RollbackInstanceIdx(INDEX_NONE) , bFilterOutRequestFromDeactivatedBranch(false) , bPostponeSearch(false) , bSearchInProgress(false) , bPreserveActiveNodeMemoryOnRollback(false)`
- L601 _public prototype_ `FBehaviorTreeSearchData() = delete;`
- L605 _private member_ `static int32 NextSearchId;`

#### struct `FBehaviorTreePropertyMemory`  
`struct FBehaviorTreePropertyMemory`  
_L609-618_
- desc: property block in blueprint defined nodes
- L611 _public member_ `uint16 Offset;`
- L612 _public member_ `uint16 BlockSize;`
- L614 _public function_ `FBehaviorTreePropertyMemory()`
- L615 _public function_ `FBehaviorTreePropertyMemory(int32 Value) : Offset((uint32)Value >> 16), BlockSize((uint32)Value & 0xFFFF)`
- L617 _public function_ `int32 Pack() const`

#### struct `FBlackboardKeySelector`  
`struct FBlackboardKeySelector`  
_L623-693_
- reflection: `USTRUCT(BlueprintType)`
- desc: helper struct for defining types of allowed blackboard entries (e.g. only entries holding points and objects derived form actor class)
- L627 _public function_ `FBlackboardKeySelector() : SelectedKeyID(FBlackboard::InvalidKey), bNoneIsAllowedValue(false)`
- L633 _public member_ `TArray<TObjectPtr<UBlackboardKeyType>> AllowedTypes;` — `UPROPERTY(transient, EditAnywhere, BlueprintReadWrite, Category = Blackboard)` — array of allowed types with additional properties (e.g. uobject's base class) EditAnywhere is required for FBlackboardSelectorDetails::CacheBlackboardData()
- L637 _public member_ `FName SelectedKeyName;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = Blackboard)` — name of selected key
- L641 _public member_ `TSubclassOf<UBlackboardKeyType> SelectedKeyType;` — `UPROPERTY(transient, EditInstanceOnly, BlueprintReadWrite, Category = Blackboard)` — class of selected key
- L646 _protected member_ `int32 SelectedKeyID;` — `UPROPERTY(transient, EditInstanceOnly, BlueprintReadWrite, Category = Blackboard, meta = (ClampMin = "0", UIMin = "0"))` — ID of selected key
- L650 _protected member_ `uint32 bNoneIsAllowedValue:1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Blackboard, Meta = (Tooltip = ""))` — Requires BlueprintReadWrite so that blueprint creators (using MakeBlackboardKeySelector) can specify whether or not None is Allowed.
- L653 _protected prototype_ `void InitSelection(const UBlackboardData& BlackboardAsset);` — find initial selection. Called when None is not a valid option for this key selector
- L657 _public prototype_ `void ResolveSelectedKey(const UBlackboardData& BlackboardAsset);` — find ID and class of selected key
- L659 _public function_ `void AllowNoneAsValue(bool bAllow)`
- L661 _public function_ `inline FBlackboard::FKey GetSelectedKeyID() const`
- L664 _public prototype_ `void AddObjectFilter(UObject* Owner, FName PropertyName, TSubclassOf<UObject> AllowedClass);` — helper functions for setting basic filters
- L665 _public prototype_ `void AddClassFilter(UObject* Owner, FName PropertyName, TSubclassOf<UObject> AllowedClass);`
- L666 _public prototype_ `void AddEnumFilter(UObject* Owner, FName PropertyName, UEnum* AllowedEnum);`
- L667 _public prototype_ `void AddNativeEnumFilter(UObject* Owner, FName PropertyName, const FString& AllowedEnumName);`
- L668 _public prototype_ `void AddIntFilter(UObject* Owner, FName PropertyName);`
- L669 _public prototype_ `void AddFloatFilter(UObject* Owner, FName PropertyName);`
- L670 _public prototype_ `void AddBoolFilter(UObject* Owner, FName PropertyName);`
- L671 _public prototype_ `void AddVectorFilter(UObject* Owner, FName PropertyName);`
- L672 _public prototype_ `void AddRotatorFilter(UObject* Owner, FName PropertyName);`
- L673 _public prototype_ `void AddStringFilter(UObject* Owner, FName PropertyName);`
- L674 _public prototype_ `void AddNameFilter(UObject* Owner, FName PropertyName);`
- L675 _public prototype_ `void AddStructFilter(UObject* Owner, FName PropertyName, const UScriptStruct* AllowedStruct);`
- L678 _public function_ `template<typename T> void AddStructFilter(UObject* Owner, FName PropertyName)`
- L683 _public function_ `inline bool IsNone() const`
- L684 _public function_ `inline bool IsSet() const`
- L685 _public function_ `inline bool NeedsResolving() const`
- L686 _public function_ `inline void InvalidateResolvedKey()`
- L689 _public prototype_ `void PreSave(const UObject* Outer, const UBlackboardData& Blackboard, FName PropertyName);`

#### class `UBehaviorTreeTypes`  
`class UBehaviorTreeTypes : public UObject`  
_L696-720_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UObject`
- L700 _private member_ `static FString BTLoggingContext;`
- L704 _public prototype_ `static FString DescribeNodeHelper(const UBTNode* Node);`
- L706 _public prototype_ `static FString DescribeNodeResult(EBTNodeResult::Type NodeResult);`
- L707 _public prototype_ `static FString DescribeFlowAbortMode(EBTFlowAbortMode::Type FlowAbortMode);`
- L708 _public prototype_ `static FString DescribeActiveNode(EBTActiveNode::Type ActiveNodeType);`
- L709 _public prototype_ `static FString DescribeTaskStatus(EBTTaskStatus::Type TaskStatus);`
- L710 _public prototype_ `static FString DescribeNodeUpdateMode(EBTNodeUpdateMode::Type UpdateMode);`
- L713 _public prototype_ `static FString GetShortTypeName(const UObject* Ob);` — returns short name of object's class (BTTaskNode_Wait -> Wait)
- L715 _public function_ `static FString GetBTLoggingContext()`
- L719 _public prototype_ `static void SetBTLoggingContext(const UBTNode* NewBTLoggingContext);` — @param NewBTLoggingContext the object which name's will be added to some of the BT logging pass nullptr to clear

#### struct `FScopedBTLoggingContext`  
`struct FScopedBTLoggingContext`  
_L723-735_
- desc: Helper struct to push a node as the new logging context and automatically reset the context on destruction.
- L725 _public prototype_ `FScopedBTLoggingContext() = delete;`
- L726 _public function_ `explicit FScopedBTLoggingContext(const UBTNode* Context)`
- L731 _public function_ `~FScopedBTLoggingContext()`

#### Free symbols / members of external scopes

- L28 _macro_ `#define BT_VLOG(Context, Verbosity, Format, ...) UE_VLOG(Context->OwnerComp.IsValid() ? Context->OwnerComp->GetOwner() : NULL, LogBehaviorTree, Verbosity, Format, ##__VA_ARGS__)` — Visual logging helper
- L29 _macro_ `#define BT_SEARCHLOG(SearchData, Verbosity, Format, ...) UE_VLOG(SearchData.OwnerComp.GetOwner(), LogBehaviorTree, Verbosity, Format, ##__VA_ARGS__)`
- L32 _macro_ `#define USE_BEHAVIORTREE_DEBUGGER (1 && WITH_EDITORONLY_DATA)` — Behavior tree debugger in editor
- L34 _delegate_ `DECLARE_STATS_GROUP(TEXT("Behavior Tree"), STATGROUP_AIBehaviorTree, STATC`
- L36 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("BT Tick"),STAT_AI_BehaviorTree_Tick,STATGROUP_AIBehaviorT`
- L37 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("BT Load Time"),STAT_AI_BehaviorTree_LoadTime,STATGROUP_AIBeha`
- L38 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("BT Search Time"),STAT_AI_BehaviorTree_SearchTime,STATGROUP_AIBe`
- L39 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("BT Execution Time"),STAT_AI_BehaviorTree_ExecutionTime,STATGROUP_A`
- L40 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("BT Auxiliary Update Time"),STAT_AI_BehaviorTree_AuxUpdateTime,STAT`
- L41 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("BT Cleanup Time"), STAT_AI_BehaviorTree_Cleanup, STATGROUP_AIB`
- L42 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("BT Stop Tree Time"), STAT_AI_BehaviorTree_StopTree, STATGROUP_A`
- L43 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("Num Templates"),STAT_AI_BehaviorTree_NumTemplates,STATGROUP_AIBeh`
- L44 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("Num Instances"),STAT_AI_BehaviorTree_NumInstances,STATGROUP_AIBeh`
- L45 _delegate_ `DECLARE_MEMORY_STAT_EXTERN(TEXT("Instance memory"),STAT_AI_BehaviorTree_InstanceMemory,STATGROUP_AIBehaviorTree,`
- L50 _enumerator_ `enum { Value = true };` (scope `TIsValidVariadicFunctionArg::__anoneecb639f0103`)
- L55 _namespace_ `namespace UE`
- L55 _namespace_ `namespace BehaviorTree` (scope `UE`)
- L55 _namespace_ `namespace Messages` (scope `UE::BehaviorTree`)
- L57 _externvar_ `extern FText BlackboardNotSet;` (scope `UE::BehaviorTree::Messages`)
- L68 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnBlackboardChange, const UBlackboardComponent&, FBlackboard::FKey );` — delegate defines
- L68 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnBlackboardChange, const UBlackboardComponent&, FBlackboard::FKey );` — delegate defines
- L72 _typedef_ `using FOnBlackboardChangeNotification = TDelegate<EBlackboardNotificationResult(const UBlackboardComponent&, FBlackboard::FKey keyID), FNotThreadSafeNotCheckedDelegateUserPolicy>;` — using "not checked" user policy (means race detection is disabled) because this delegate is stored in a TMultiMap and causes its reallocation from inside delegate's execution. This is incompatible with race detection that needs to access the delegate instance after its execution
- L74 _namespace_ `namespace BTSpecialChild`
- L76 _variable_ `inline constexpr int32 NotInitialized = -1;` (scope `BTSpecialChild`) — special value for child indices: needs to be initialized
- L77 _variable_ `inline constexpr int32 ReturnToParent = -2;` (scope `BTSpecialChild`) — special value for child indices: return to parent node
- L79 _variable_ `inline constexpr uint8 OwnedByComposite = MAX_uint8;` (scope `BTSpecialChild`) — special value for aux node's child index: owned by composite node instead of a task
- L83 _namespace_ `namespace EBTNodeResult`
- L99 _namespace_ `namespace EBTExecutionMode`
- L108 _namespace_ `namespace EBTStopMode`
- L123 _namespace_ `namespace EBTMemoryInit`
- L132 _namespace_ `namespace EBTMemoryClear`
- L142 _namespace_ `namespace EBTFlowAbortMode`
- L155 _namespace_ `namespace EBTActiveNode`
- L167 _namespace_ `namespace EBTTaskStatus`
- L178 _namespace_ `namespace EBTNodeUpdateMode`
- L205 _namespace_ `namespace EBTExecutionSnap`
- L214 _namespace_ `namespace EBTDescriptionVerbosity`
- L316 _delegate_ `DECLARE_DELEGATE_TwoParams(FBTInstanceDeactivation, UBehaviorTreeComponent&, EBTNodeResult::Type);`
- L316 _prototype_ `DECLARE_DELEGATE_TwoParams(FBTInstanceDeactivation, UBehaviorTreeComponent&, EBTNodeResult::Type);`
- L467 _function_ `inline friend uint32 GetTypeHash(const FBTNodeIndex& Other)`

### `Source/Runtime/AIModule/Classes/BehaviorTree/Blackboard/BlackboardKey.h` (Public)


#### struct `FBlackboard::FKey`  
`struct FKey`  
_L17-31_
- desc: the default BB key size is now 16
- L19 _public prototype_ `constexpr FKey() = default;`
- L20 _public function_ `FKey(int32 InKey)`
- L21 _public function_ `constexpr FKey(uint16 InKey) : Key(InKey)`
- L22 _public prototype_ `constexpr FKey(uint8 InKey) = delete;`
- L23 _public function_ `constexpr operator int32() const`
- L24 _public function_ `constexpr operator uint16() const`
- L25 _public prototype_ `constexpr operator uint8() const = delete;`
- L26 _public function_ `constexpr bool operator==(const FKey& Other) const`
- L27 _public function_ `constexpr bool operator!=(const FKey& Other) const`
- L30 _private member_ `uint16 Key = static_cast<uint16>(-1);`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace FBlackboard`
- L9 _externvar_ `extern const FName KeySelf;` (scope `FBlackboard`)
- L13 _typedef_ `using FKey = uint8;` (scope `FBlackboard`) — this is the legacy BB key size. Add AI_BLACKBOARD_KEY_SIZE_8 to your *.target.cs to enable it.
- L14 _variable_ `inline constexpr FKey InvalidKey = FKey(-1);` (scope `FBlackboard`)
- L33 _variable_ `inline constexpr FKey InvalidKey = FKey();` (scope `FBlackboard`)
- L35 _function_ `inline uint32 GetTypeHash(const FKey& Key)` (scope `FBlackboard`)

### `Source/Runtime/AIModule/Classes/BehaviorTree/Blackboard/BlackboardKeyAllTypes.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/AIModule/Classes/BehaviorTree/Blackboard/BlackboardKeyEnums.h` (Public)


#### enum `EBlackboardCompare::Type`  
`enum Type`  
_L9-16_
- L11 _public enumerator_ `Less = -1`
- L12 _public enumerator_ `Equal = 0`
- L13 _public enumerator_ `Greater = 1`
- L15 _public enumerator_ `NotEqual = 1` — important, do not change

#### enum `EBlackboardKeyOperation::Type`  
`enum Type`  
_L21-26_
- L23 _public enumerator_ `Basic`
- L24 _public enumerator_ `Arithmetic`
- L25 _public enumerator_ `Text`

#### enum `EBasicKeyOperation::Type`  
`enum Type : int`  
_L32-36_
- L34 _public enumerator_ `Set UMETA(DisplayName="Is Set")`
- L35 _public enumerator_ `NotSet UMETA(DisplayName="Is Not Set")`

#### enum `EArithmeticKeyOperation::Type`  
`enum Type : int`  
_L42-50_
- L44 _public enumerator_ `Equal UMETA(DisplayName="Is Equal To")`
- L45 _public enumerator_ `NotEqual UMETA(DisplayName="Is Not Equal To")`
- L46 _public enumerator_ `Less UMETA(DisplayName="Is Less Than")`
- L47 _public enumerator_ `LessOrEqual UMETA(DisplayName="Is Less Than Or Equal To")`
- L48 _public enumerator_ `Greater UMETA(DisplayName="Is Greater Than")`
- L49 _public enumerator_ `GreaterOrEqual UMETA(DisplayName="Is Greater Than Or Equal To")`

#### enum `ETextKeyOperation::Type`  
`enum Type : int`  
_L56-62_
- L58 _public enumerator_ `Equal UMETA(DisplayName="Is Equal To")`
- L59 _public enumerator_ `NotEqual UMETA(DisplayName="Is Not Equal To")`
- L60 _public enumerator_ `Contain UMETA(DisplayName="Contains")`
- L61 _public enumerator_ `NotContain UMETA(DisplayName="Not Contains")`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace EBlackboardCompare`
- L19 _namespace_ `namespace EBlackboardKeyOperation`
- L30 _namespace_ `namespace EBasicKeyOperation`
- L40 _namespace_ `namespace EArithmeticKeyOperation`
- L54 _namespace_ `namespace ETextKeyOperation`

### `Source/Runtime/AIModule/Classes/BehaviorTree/Blackboard/BlackboardKeyType.h` (Public)


#### struct `FBlackboardInstancedKeyMemory`  
`struct FBlackboardInstancedKeyMemory`  
_L16-20_
- L19 _public member_ `int32 KeyIdx;` — index of instanced key in UBlackboardComponent::InstancedKeys

#### class `UBlackboardKeyType`  
`class UBlackboardKeyType : public UObject`  
_L23-164_
- reflection: `UCLASS(EditInlineNew, Abstract, CollapseCategories, AutoExpandCategories=(Blackboard), MinimalAPI)`
- inherits: `UObject`
- L28 _private prototype_ `virtual void PreInitialize(UBlackboardComponent& OwnerComp);` — handle dynamic data size
- L31 _private prototype_ `void InitializeKey(UBlackboardComponent& OwnerComp, FBlackboard::FKey KeyID);` — handle instancing if needed
- L34 _private prototype_ `virtual bool IsAllowedByFilter(UBlackboardKeyType* FilterOb) const;` — does it match settings in filter?
- L37 _private prototype_ `bool WrappedGetLocation(const UBlackboardComponent& OwnerComp, const uint8* MemoryBlock, FVector& Location) const;` — extract location from entry, supports instanced keys
- L40 _private prototype_ `bool WrappedGetRotation(const UBlackboardComponent& OwnerComp, const uint8* MemoryBlock, FRotator& Rotation) const;` — extract rotation from entry, supports instanced keys
- L43 _private prototype_ `void WrappedFree(UBlackboardComponent& OwnerComp, uint8* MemoryBlock);` — free value before removing from blackboard, supports instanced keys
- L46 _private prototype_ `void WrappedClear(const UBlackboardComponent& OwnerComp, uint8* MemoryBlock) const;` — sets value to the default, supports instanced keys
- L49 _private prototype_ `bool WrappedIsEmpty(const UBlackboardComponent& OwnerComp, const uint8* MemoryBlock) const;` — check if key has stored value, supports instanced keys
- L52 _private prototype_ `bool WrappedTestBasicOperation(const UBlackboardComponent& OwnerComp, const uint8* MemoryBlock, EBasicKeyOperation::Type Op) const;` — various value testing, used by decorators, supports instanced keys
- L53 _private prototype_ `bool WrappedTestArithmeticOperation(const UBlackboardComponent& OwnerComp, const uint8* MemoryBlock, EArithmeticKeyOperation::Type Op, int32 OtherIntValue, float OtherFloatValue) const;`
- L54 _private prototype_ `bool WrappedTestTextOperation(const UBlackboardComponent& OwnerComp, const uint8* MemoryBlock, ETextKeyOperation::Type Op, const FString& OtherString) const;`
- L57 _private prototype_ `virtual FString DescribeArithmeticParam(int32 IntValue, float FloatValue) const;` — describe params of arithmetic test
- L60 _private prototype_ `FString WrappedDescribeValue(const UBlackboardComponent& OwnerComp, const uint8* MemoryBlock) const;` — convert value to text, supports instanced keys
- L63 _private prototype_ `virtual FString DescribeSelf() const;` — description of params for property view
- L66 _private prototype_ `virtual UBlackboardKeyType* UpdateDeprecatedKey();` — create replacement key for deprecated data
- L69 _private prototype_ `const UBlackboardKeyType* GetKeyInstance(const UBlackboardComponent& OwnerComp, const uint8* MemoryBlock) const;` — @return key instance if bCreateKeyInstance was set
- L70 _private prototype_ `UBlackboardKeyType* GetKeyInstance(UBlackboardComponent& OwnerComp, const uint8* MemoryBlock) const;`
- L73 _private prototype_ `virtual EBlackboardCompare::Type CompareValues(const UBlackboardComponent& OwnerComp, const uint8* MemoryBlock, const UBlackboardKeyType* OtherKeyOb, const uint8* OtherMemoryBlock) const;` — compares two values
- L77 _private prototype_ `bool HasInstance() const;` — @return true if key wants to be instanced
- L80 _private prototype_ `bool IsInstanced() const;` — @return true if this object is instanced key
- L83 _private prototype_ `uint16 GetValueSize() const;` — get ValueSize
- L86 _private prototype_ `EBlackboardKeyOperation::Type GetTestOperation() const;` — get test supported by this type
- L91 _protected member_ `uint16 ValueSize;` — size of value for this type
- L94 _protected member_ `TEnumAsByte<EBlackboardKeyOperation::Type> SupportedOp;` — decorator operation supported with this type
- L97 _protected member_ `uint8 bIsInstanced : 1;` — set automatically for node instances
- L100 _protected member_ `uint8 bCreateKeyInstance : 1;` — if set, key will be instanced instead of using memory block
- L104 _protected function_ `template<typename T> static T GetValueFromMemory(const uint8* MemoryBlock)` — helper function for reading typed data from memory block
- L111 _protected function_ `template<typename T> static bool SetValueInMemory(uint8* MemoryBlock, const T& Value)` — helper function for writing typed data to memory block, returns true if value has changed
- L121 _protected function_ `template<typename T> static bool SetWeakObjectInMemory(uint8* MemoryBlock, const TWeakObjectPtr<T>& Value)` — helper function for witting weak object data to memory block, returns true if value has changed
- L137 _protected prototype_ `virtual void CopyValues(UBlackboardComponent& OwnerComp, uint8* MemoryBlock, const UBlackboardKeyType* SourceKeyOb, const uint8* SourceBlock);` — copy value from other key, works directly on provided memory/properties
- L140 _protected prototype_ `virtual void InitializeMemory(UBlackboardComponent& OwnerComp, uint8* MemoryBlock);` — initialize memory, works directly on provided memory/properties
- L143 _protected prototype_ `virtual void FreeMemory(UBlackboardComponent& OwnerComp, uint8* MemoryBlock);` — free value before removing from blackboard, works directly on provided memory/properties
- L146 _protected prototype_ `virtual bool GetLocation(const UBlackboardComponent& OwnerComp, const uint8* MemoryBlock, FVector& Location) const;` — extract location from entry, works directly on provided memory/properties
- L149 _protected prototype_ `virtual bool GetRotation(const UBlackboardComponent& OwnerComp, const uint8* MemoryBlock, FRotator& Rotation) const;` — extract rotation from entry, works directly on provided memory/properties
- L152 _protected prototype_ `virtual void Clear(UBlackboardComponent& OwnerComp, uint8* MemoryBlock);` — sets value to the default, works directly on provided memory/properties
- L155 _protected prototype_ `virtual bool IsEmpty(const UBlackboardComponent& OwnerComp, const uint8* MemoryBlock) const;` — check if key has stored value, works directly on provided memory/properties
- L158 _protected prototype_ `virtual bool TestBasicOperation(const UBlackboardComponent& OwnerComp, const uint8* MemoryBlock, EBasicKeyOperation::Type Op) const;` — various value testing, works directly on provided memory/properties
- L159 _protected prototype_ `virtual bool TestArithmeticOperation(const UBlackboardComponent& OwnerComp, const uint8* MemoryBlock, EArithmeticKeyOperation::Type Op, int32 OtherIntValue, float OtherFloatValue) const;`
- L160 _protected prototype_ `virtual bool TestTextOperation(const UBlackboardComponent& OwnerComp, const uint8* MemoryBlock, ETextKeyOperation::Type Op, const FString& OtherString) const;`
- L163 _protected prototype_ `virtual FString DescribeValue(const UBlackboardComponent& OwnerComp, const uint8* MemoryBlock) const;` — convert value to text, works directly on provided memory/properties
- L169 _function_ `inline uint16 UBlackboardKeyType::GetValueSize() const`
- L174 _function_ `inline EBlackboardKeyOperation::Type UBlackboardKeyType::GetTestOperation() const`
- L179 _function_ `inline bool UBlackboardKeyType::HasInstance() const`
- L184 _function_ `inline bool UBlackboardKeyType::IsInstanced() const`

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogBlackboard, Log, All);`
- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogBlackboard, Log, All);`

### `Source/Runtime/AIModule/Classes/BehaviorTree/Blackboard/BlackboardKeyType_Bool.h` (Public)


#### class `UBlackboardKeyType_Bool`  
`class UBlackboardKeyType_Bool : public UBlackboardKeyType`  
_L12-32_
- reflection: `UCLASS(EditInlineNew, meta=(DisplayName="Bool"), MinimalAPI)`
- inherits: `UBlackboardKeyType`
- L16 _private typedef_ `typedef bool FDataType;`
- L17 _private member_ `static const FDataType InvalidValue;`
- L19 _private prototype_ `static bool GetValue(const UBlackboardKeyType_Bool* KeyOb, const uint8* RawData);`
- L20 _private prototype_ `static bool SetValue(UBlackboardKeyType_Bool* KeyOb, uint8* RawData, bool bValue);`
- L22 _private prototype_ `virtual EBlackboardCompare::Type CompareValues(const UBlackboardComponent& OwnerComp, const uint8* MemoryBlock, const UBlackboardKeyType* OtherKeyOb, const uint8* OtherMemoryBlock) const override;`
- L26 _private member_ `bool bDefaultValue = InvalidValue;` — `UPROPERTY(Category = Blackboard, EditDefaultsOnly)`
- L29 _protected prototype_ `virtual void InitializeMemory(UBlackboardComponent& OwnerComp, uint8* MemoryBlock) override;`
- L30 _protected prototype_ `virtual FString DescribeValue(const UBlackboardComponent& OwnerComp, const uint8* RawData) const override;`
- L31 _protected prototype_ `virtual bool TestBasicOperation(const UBlackboardComponent& OwnerComp, const uint8* MemoryBlock, EBasicKeyOperation::Type Op) const override;`

### `Source/Runtime/AIModule/Classes/BehaviorTree/Blackboard/BlackboardKeyType_Class.h` (Public)


#### class `UBlackboardKeyType_Class`  
`class UBlackboardKeyType_Class : public UBlackboardKeyType`  
_L12-39_
- reflection: `UCLASS(EditInlineNew, meta=(DisplayName="Class"), MinimalAPI)`
- inherits: `UBlackboardKeyType`
- L16 _private typedef_ `typedef UClass* FDataType;`
- L17 _private member_ `static const FDataType InvalidValue;`
- L20 _private member_ `TObjectPtr<UClass> BaseClass;` — `UPROPERTY(Category=Blackboard, EditDefaultsOnly, NoClear, meta=(AllowAbstract="1"))`
- L23 _private member_ `TObjectPtr<UClass> DefaultValue;` — `UPROPERTY(Category=Blackboard, EditDefaultsOnly)`
- L25 _private prototype_ `static UClass* GetValue(const UBlackboardKeyType_Class* KeyOb, const uint8* RawData);`
- L26 _private prototype_ `static bool SetValue(UBlackboardKeyType_Class* KeyOb, uint8* RawData, UClass* Value);`
- L28 _private prototype_ `virtual EBlackboardCompare::Type CompareValues(const UBlackboardComponent& OwnerComp, const uint8* MemoryBlock, const UBlackboardKeyType* OtherKeyOb, const uint8* OtherMemoryBlock) const override;`
- L31 _private prototype_ `virtual FString DescribeSelf() const override;`
- L32 _private prototype_ `virtual bool IsAllowedByFilter(UBlackboardKeyType* FilterOb) const override;`
- L34 _private prototype_ `virtual void InitializeMemory(UBlackboardComponent& OwnerComp, uint8* MemoryBlock) override;`
- L37 _protected prototype_ `virtual FString DescribeValue(const UBlackboardComponent& OwnerComp, const uint8* RawData) const override;`
- L38 _protected prototype_ `virtual bool TestBasicOperation(const UBlackboardComponent& OwnerComp, const uint8* MemoryBlock, EBasicKeyOperation::Type Op) const override;`

### `Source/Runtime/AIModule/Classes/BehaviorTree/Blackboard/BlackboardKeyType_Enum.h` (Public)


#### class `UBlackboardKeyType_Enum`  
`class UBlackboardKeyType_Enum : public UBlackboardKeyType`  
_L12-53_
- reflection: `UCLASS(EditInlineNew, meta=(DisplayName="Enum"), MinimalAPI)`
- inherits: `UBlackboardKeyType`
- L16 _private typedef_ `typedef uint8 FDataType;`
- L17 _private member_ `static const FDataType InvalidValue;`
- L20 _private member_ `TObjectPtr<UEnum> EnumType;` — `UPROPERTY(Category=Blackboard, EditDefaultsOnly)`
- L24 _private member_ `FString EnumName;` — `UPROPERTY(Category=Blackboard, EditDefaultsOnly)` — name of enum defined in c++ code, will take priority over asset from EnumType property
- L27 _private member_ `uint8 DefaultValue = 0;` — `UPROPERTY(Category=Blackboard, EditDefaultsOnly)`
- L31 _private member_ `uint32 bIsEnumNameValid : 1;` — `UPROPERTY(Category = Blackboard, VisibleDefaultsOnly)` — set when EnumName override is valid and active
- L33 _private prototype_ `static FDataType GetValue(const UBlackboardKeyType_Enum* KeyOb, const uint8* RawData);`
- L34 _private prototype_ `static bool SetValue(UBlackboardKeyType_Enum* KeyOb, uint8* RawData, FDataType Value);`
- L36 _private prototype_ `virtual EBlackboardCompare::Type CompareValues(const UBlackboardComponent& OwnerComp, const uint8* MemoryBlock, const UBlackboardKeyType* OtherKeyOb, const uint8* OtherMemoryBlock) const override;`
- L39 _private prototype_ `virtual FString DescribeSelf() const override;`
- L40 _private prototype_ `virtual FString DescribeArithmeticParam(int32 IntValue, float FloatValue) const override;`
- L41 _private prototype_ `virtual bool IsAllowedByFilter(UBlackboardKeyType* FilterOb) const override;`
- L43 _private prototype_ `virtual void InitializeMemory(UBlackboardComponent& OwnerComp, uint8* MemoryBlock) override;`
- L47 _protected prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L48 _protected prototype_ `static bool ValidateEnum(const UEnum& EnumType);`
- L51 _protected prototype_ `virtual FString DescribeValue(const UBlackboardComponent& OwnerComp, const uint8* RawData) const override;`
- L52 _protected prototype_ `virtual bool TestArithmeticOperation(const UBlackboardComponent& OwnerComp, const uint8* MemoryBlock, EArithmeticKeyOperation::Type Op, int32 OtherIntValue, float OtherFloatValue) const override;`

### `Source/Runtime/AIModule/Classes/BehaviorTree/Blackboard/BlackboardKeyType_Float.h` (Public)


#### class `UBlackboardKeyType_Float`  
`class UBlackboardKeyType_Float : public UBlackboardKeyType`  
_L12-34_
- reflection: `UCLASS(EditInlineNew, meta=(DisplayName="Float"), MinimalAPI)`
- inherits: `UBlackboardKeyType`
- L16 _private typedef_ `typedef float FDataType;`
- L17 _private member_ `static const FDataType InvalidValue;`
- L19 _private prototype_ `static float GetValue(const UBlackboardKeyType_Float* KeyOb, const uint8* RawData);`
- L20 _private prototype_ `static bool SetValue(UBlackboardKeyType_Float* KeyOb, uint8* RawData, float Value);`
- L22 _private prototype_ `virtual EBlackboardCompare::Type CompareValues(const UBlackboardComponent& OwnerComp, const uint8* MemoryBlock, const UBlackboardKeyType* OtherKeyOb, const uint8* OtherMemoryBlock) const override;`
- L25 _private prototype_ `virtual FString DescribeArithmeticParam(int32 IntValue, float FloatValue) const override;`
- L28 _private member_ `float DefaultValue = InvalidValue;` — `UPROPERTY(EditDefaultsOnly, Category=Blackboard)`
- L31 _protected prototype_ `virtual void InitializeMemory(UBlackboardComponent& OwnerComp, uint8* MemoryBlock) override;`
- L32 _protected prototype_ `virtual FString DescribeValue(const UBlackboardComponent& OwnerComp, const uint8* RawData) const override;`
- L33 _protected prototype_ `virtual bool TestArithmeticOperation(const UBlackboardComponent& OwnerComp, const uint8* MemoryBlock, EArithmeticKeyOperation::Type Op, int32 OtherIntValue, float OtherFloatValue) const override;`

### `Source/Runtime/AIModule/Classes/BehaviorTree/Blackboard/BlackboardKeyType_Int.h` (Public)


#### class `UBlackboardKeyType_Int`  
`class UBlackboardKeyType_Int : public UBlackboardKeyType`  
_L12-33_
- reflection: `UCLASS(EditInlineNew, meta=(DisplayName="Int"), MinimalAPI)`
- inherits: `UBlackboardKeyType`
- L16 _private typedef_ `typedef int32 FDataType;`
- L17 _private member_ `static const FDataType InvalidValue;`
- L19 _private prototype_ `static int32 GetValue(const UBlackboardKeyType_Int* KeyOb, const uint8* RawData);`
- L20 _private prototype_ `static bool SetValue(UBlackboardKeyType_Int* KeyOb, uint8* RawData, int32 Value);`
- L22 _private prototype_ `virtual FString DescribeArithmeticParam(int32 IntValue, float FloatValue) const override;`
- L23 _private prototype_ `virtual EBlackboardCompare::Type CompareValues(const UBlackboardComponent& OwnerComp, const uint8* MemoryBlock, const UBlackboardKeyType* OtherKeyOb, const uint8* OtherMemoryBlock) const override;`
- L27 _private member_ `int32 DefaultValue = InvalidValue;` — `UPROPERTY(EditDefaultsOnly, Category = Blackboard)`
- L30 _protected prototype_ `virtual void InitializeMemory(UBlackboardComponent& OwnerComp, uint8* MemoryBlock) override;`
- L31 _protected prototype_ `virtual FString DescribeValue(const UBlackboardComponent& OwnerComp, const uint8* RawData) const override;`
- L32 _protected prototype_ `virtual bool TestArithmeticOperation(const UBlackboardComponent& OwnerComp, const uint8* MemoryBlock, EArithmeticKeyOperation::Type Op, int32 OtherIntValue, float OtherFloatValue) const override;`

### `Source/Runtime/AIModule/Classes/BehaviorTree/Blackboard/BlackboardKeyType_Name.h` (Public)


#### class `UBlackboardKeyType_Name`  
`class UBlackboardKeyType_Name : public UBlackboardKeyType`  
_L12-32_
- reflection: `UCLASS(EditInlineNew, meta=(DisplayName="Name"), MinimalAPI)`
- inherits: `UBlackboardKeyType`
- L16 _private typedef_ `typedef FName FDataType;`
- L17 _private member_ `static const FDataType InvalidValue;`
- L19 _private prototype_ `static FName GetValue(const UBlackboardKeyType_Name* KeyOb, const uint8* RawData);`
- L20 _private prototype_ `static bool SetValue(UBlackboardKeyType_Name* KeyOb, uint8* RawData, const FName& Value);`
- L22 _private prototype_ `virtual EBlackboardCompare::Type CompareValues(const UBlackboardComponent& OwnerComp, const uint8* MemoryBlock, const UBlackboardKeyType* OtherKeyOb, const uint8* OtherMemoryBlock) const override;`
- L26 _private member_ `FName DefaultValue = InvalidValue;` — `UPROPERTY(EditDefaultsOnly, Category = Blackboard)`
- L29 _protected prototype_ `virtual void InitializeMemory(UBlackboardComponent& OwnerComp, uint8* MemoryBlock) override;`
- L30 _protected prototype_ `virtual FString DescribeValue(const UBlackboardComponent& OwnerComp, const uint8* RawData) const override;`
- L31 _protected prototype_ `virtual bool TestTextOperation(const UBlackboardComponent& OwnerComp, const uint8* MemoryBlock, ETextKeyOperation::Type Op, const FString& OtherString) const override;`

### `Source/Runtime/AIModule/Classes/BehaviorTree/Blackboard/BlackboardKeyType_NativeEnum.h` (Public)


#### class `UBlackboardKeyType_NativeEnum`  
`class UBlackboardKeyType_NativeEnum : public UBlackboardKeyType`  
_L13-30_
- reflection: `UCLASS(NotEditInlineNew, HideDropDown, MinimalAPI)`
- inherits: `UBlackboardKeyType`
- L17 _private typedef_ `typedef uint8 FDataType;`
- L18 _private member_ `static const FDataType InvalidValue;`
- L21 _private member_ `FString EnumName;` — `UPROPERTY(Category=Blackboard, EditDefaultsOnly)`
- L24 _private member_ `TObjectPtr<UEnum> EnumType;` — `UPROPERTY()`
- L26 _private prototype_ `virtual UBlackboardKeyType* UpdateDeprecatedKey() override;`
- L28 _private prototype_ `static uint8 GetValue(const UBlackboardKeyType_NativeEnum* KeyOb, const uint8* RawData);`
- L29 _private prototype_ `static bool SetValue(UBlackboardKeyType_NativeEnum* KeyOb, uint8* RawData, uint8 Value);`

### `Source/Runtime/AIModule/Classes/BehaviorTree/Blackboard/BlackboardKeyType_Object.h` (Public)


#### class `UBlackboardKeyType_Object`  
`class UBlackboardKeyType_Object : public UBlackboardKeyType`  
_L12-41_
- reflection: `UCLASS(EditInlineNew, meta=(DisplayName="Object"), MinimalAPI)`
- inherits: `UBlackboardKeyType`
- L16 _private typedef_ `typedef UObject* FDataType;`
- L17 _private member_ `static const FDataType InvalidValue;`
- L20 _private member_ `TObjectPtr<UClass> BaseClass;` — `UPROPERTY(Category=Blackboard, EditDefaultsOnly, NoClear, meta=(AllowAbstract="1"))`
- L23 _private member_ `TObjectPtr<UObject> DefaultValue;` — `UPROPERTY(Category=Blackboard, EditDefaultsOnly)`
- L25 _private prototype_ `static UObject* GetValue(const UBlackboardKeyType_Object* KeyOb, const uint8* RawData);`
- L26 _private prototype_ `static bool SetValue(UBlackboardKeyType_Object* KeyOb, uint8* RawData, UObject* Value);`
- L28 _private prototype_ `virtual EBlackboardCompare::Type CompareValues(const UBlackboardComponent& OwnerComp, const uint8* MemoryBlock, const UBlackboardKeyType* OtherKeyOb, const uint8* OtherMemoryBlock) const override;`
- L31 _private prototype_ `virtual FString DescribeSelf() const override;`
- L32 _private prototype_ `virtual bool IsAllowedByFilter(UBlackboardKeyType* FilterOb) const override;`
- L34 _private prototype_ `virtual void InitializeMemory(UBlackboardComponent& OwnerComp, uint8* MemoryBlock) override;`
- L37 _protected prototype_ `virtual FString DescribeValue(const UBlackboardComponent& OwnerComp, const uint8* RawData) const override;`
- L38 _protected prototype_ `virtual bool GetLocation(const UBlackboardComponent& OwnerComp, const uint8* RawData, FVector& Location) const override;`
- L39 _protected prototype_ `virtual bool GetRotation(const UBlackboardComponent& OwnerComp, const uint8* MemoryBlock, FRotator& Rotation) const override;`
- L40 _protected prototype_ `virtual bool TestBasicOperation(const UBlackboardComponent& OwnerComp, const uint8* MemoryBlock, EBasicKeyOperation::Type Op) const override;`

### `Source/Runtime/AIModule/Classes/BehaviorTree/Blackboard/BlackboardKeyType_Rotator.h` (Public)


#### class `UBlackboardKeyType_Rotator`  
`class UBlackboardKeyType_Rotator : public UBlackboardKeyType`  
_L12-39_
- reflection: `UCLASS(EditInlineNew, meta=(DisplayName="Rotator"), MinimalAPI)`
- inherits: `UBlackboardKeyType`
- L16 _private typedef_ `typedef FRotator FDataType;`
- L17 _private member_ `static const FDataType InvalidValue;`
- L19 _private prototype_ `static FRotator GetValue(const UBlackboardKeyType_Rotator* KeyOb, const uint8* RawData);`
- L20 _private prototype_ `static bool SetValue(UBlackboardKeyType_Rotator* KeyOb, uint8* RawData, const FRotator& Value);`
- L22 _private prototype_ `virtual EBlackboardCompare::Type CompareValues(const UBlackboardComponent& OwnerComp, const uint8* MemoryBlock, const UBlackboardKeyType* OtherKeyOb, const uint8* OtherMemoryBlock) const override;`
- L27 _private member_ `FRotator DefaultValue = FRotator::ZeroRotator;` — `UPROPERTY(EditDefaultsOnly, Category = Blackboard, meta = (EditCondition = "bUseDefaultValue"))` — If not set, will default to  FAISystem::InvalidRotation
- L30 _private member_ `bool bUseDefaultValue = false;` — `UPROPERTY()`
- L33 _protected prototype_ `virtual void InitializeMemory(UBlackboardComponent& OwnerComp, uint8* RawData) override;`
- L34 _protected prototype_ `virtual FString DescribeValue(const UBlackboardComponent& OwnerComp, const uint8* RawData) const override;`
- L35 _protected prototype_ `virtual bool GetRotation(const UBlackboardComponent& OwnerComp, const uint8* RawData, FRotator& Rotation) const override;`
- L36 _protected prototype_ `virtual bool IsEmpty(const UBlackboardComponent& OwnerComp, const uint8* RawData) const override;`
- L37 _protected prototype_ `virtual void Clear(UBlackboardComponent& OwnerComp, uint8* RawData) override;`
- L38 _protected prototype_ `virtual bool TestBasicOperation(const UBlackboardComponent& OwnerComp, const uint8* MemoryBlock, EBasicKeyOperation::Type Op) const override;`

### `Source/Runtime/AIModule/Classes/BehaviorTree/Blackboard/BlackboardKeyType_String.h` (Public)


#### class `UBlackboardKeyType_String`  
`class UBlackboardKeyType_String : public UBlackboardKeyType`  
_L12-38_
- reflection: `UCLASS(EditInlineNew, meta=(DisplayName="String"), MinimalAPI)`
- inherits: `UBlackboardKeyType`
- L16 _private typedef_ `typedef FString FDataType;`
- L17 _private member_ `static const FDataType InvalidValue;`
- L19 _private prototype_ `static FString GetValue(const UBlackboardKeyType_String* KeyOb, const uint8* RawData);`
- L20 _private prototype_ `static bool SetValue(UBlackboardKeyType_String* KeyOb, uint8* RawData, const FString& Value);`
- L22 _private prototype_ `virtual EBlackboardCompare::Type CompareValues(const UBlackboardComponent& OwnerComp, const uint8* MemoryBlock, const UBlackboardKeyType* OtherKeyOb, const uint8* OtherMemoryBlock) const override;`
- L26 _private member_ `FString StringValue;` — `UPROPERTY()`
- L29 _private member_ `FString DefaultValue = InvalidValue;` — `UPROPERTY(EditDefaultsOnly, Category = Blackboard)`
- L32 _protected prototype_ `virtual void InitializeMemory(UBlackboardComponent& OwnerComp, uint8* MemoryBlock) override;`
- L33 _protected prototype_ `virtual FString DescribeValue(const UBlackboardComponent& OwnerComp, const uint8* RawData) const override;`
- L34 _protected prototype_ `virtual bool TestTextOperation(const UBlackboardComponent& OwnerComp, const uint8* MemoryBlock, ETextKeyOperation::Type Op, const FString& OtherString) const override;`
- L35 _protected prototype_ `virtual void Clear(UBlackboardComponent& OwnerComp, uint8* MemoryBlock) override;`
- L36 _protected prototype_ `virtual bool IsEmpty(const UBlackboardComponent& OwnerComp, const uint8* MemoryBlock) const override;`
- L37 _protected prototype_ `virtual void CopyValues(UBlackboardComponent& OwnerComp, uint8* MemoryBlock, const UBlackboardKeyType* SourceKeyOb, const uint8* SourceBlock) override;`

### `Source/Runtime/AIModule/Classes/BehaviorTree/Blackboard/BlackboardKeyType_Struct.h` (Public)


#### class `UBlackboardKeyType_Struct`  
`class UBlackboardKeyType_Struct : public UBlackboardKeyType`  
_L15-56_
- reflection: `UCLASS(EditInlineNew, MinimalAPI, meta = (DisplayName = "Struct"))`
- inherits: `UBlackboardKeyType`
- L20 _public typedef_ `using FDataType = FConstStructView;`
- L21 _public member_ `static const FDataType InvalidValue;`
- L23 _public prototype_ `UBlackboardKeyType_Struct(const FObjectInitializer& ObjectInitializer);`
- L25 _public prototype_ `static FConstStructView GetValue(UBlackboardKeyType_Struct* KeyOb, const uint8* RawData);`
- L26 _public prototype_ `static bool SetValue(UBlackboardKeyType_Struct* KeyOb, uint8* RawData, FConstStructView Value);`
- L28 _public prototype_ `virtual EBlackboardCompare::Type CompareValues(const UBlackboardComponent& OwnerComp, const uint8* MemoryBlock, const UBlackboardKeyType* OtherKeyOb, const uint8* OtherMemoryBlock) const override;`
- L29 _public prototype_ `virtual void CopyValues(UBlackboardComponent& OwnerComp, uint8* MemoryBlock, const UBlackboardKeyType* SourceKeyOb, const uint8* SourceBlock) override;`
- L31 _public prototype_ `virtual FString DescribeSelf() const override;`
- L32 _public prototype_ `virtual bool IsAllowedByFilter(UBlackboardKeyType* FilterOb) const override;`
- L34 _public prototype_ `virtual void InitializeMemory(UBlackboardComponent& OwnerComp, uint8* MemoryBlock) override;`
- L35 _public prototype_ `virtual void FreeMemory(UBlackboardComponent& OwnerComp, uint8* MemoryBlock) override;`
- L36 _public prototype_ `virtual void Clear(UBlackboardComponent& OwnerComp, uint8* MemoryBlock) override;`
- L38 _public prototype_ `virtual void PostLoad() override;`
- L41 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L45 _public member_ `FInstancedStruct DefaultValue;` — `UPROPERTY(Category = Blackboard, EditDefaultsOnly, DisplayName = DefaultValue)`
- L50 _protected member_ `FInstancedStruct Value;` — `UPROPERTY(Transient)` — Runtime value of the key if it is instanced otherwise is empty.
- L52 _protected prototype_ `void UpdateNeedsInstance();`
- L54 _protected prototype_ `virtual FString DescribeValue(const UBlackboardComponent& OwnerComp, const uint8* RawData) const override;`
- L55 _protected prototype_ `virtual bool TestBasicOperation(const UBlackboardComponent& OwnerComp, const uint8* MemoryBlock, EBasicKeyOperation::Type Op) const override;`

### `Source/Runtime/AIModule/Classes/BehaviorTree/Blackboard/BlackboardKeyType_Vector.h` (Public)


#### class `UBlackboardKeyType_Vector`  
`class UBlackboardKeyType_Vector : public UBlackboardKeyType`  
_L12-39_
- reflection: `UCLASS(EditInlineNew, meta=(DisplayName="Vector"), MinimalAPI)`
- inherits: `UBlackboardKeyType`
- L16 _private typedef_ `typedef FVector FDataType;`
- L17 _private member_ `static const FDataType InvalidValue;`
- L19 _private prototype_ `static FVector GetValue(const UBlackboardKeyType_Vector* KeyOb, const uint8* RawData);`
- L20 _private prototype_ `static bool SetValue(UBlackboardKeyType_Vector* KeyOb, uint8* RawData, const FVector& Value);`
- L22 _private prototype_ `virtual EBlackboardCompare::Type CompareValues(const UBlackboardComponent& OwnerComp, const uint8* MemoryBlock, const UBlackboardKeyType* OtherKeyOb, const uint8* OtherMemoryBlock) const override;`
- L27 _private member_ `FVector DefaultValue = FVector::ZeroVector;` — `UPROPERTY(EditDefaultsOnly, Category = Blackboard, meta = (EditCondition = "bUseDefaultValue"))` — If not set, will default to  FAISystem::InvalidLocation
- L30 _private member_ `bool bUseDefaultValue = false;` — `UPROPERTY()`
- L33 _protected prototype_ `virtual void InitializeMemory(UBlackboardComponent& OwnerComp, uint8* RawData) override;`
- L34 _protected prototype_ `virtual FString DescribeValue(const UBlackboardComponent& OwnerComp, const uint8* RawData) const override;`
- L35 _protected prototype_ `virtual bool GetLocation(const UBlackboardComponent& OwnerComp, const uint8* RawData, FVector& Location) const override;`
- L36 _protected prototype_ `virtual bool IsEmpty(const UBlackboardComponent& OwnerComp, const uint8* MemoryBlock) const override;`
- L37 _protected prototype_ `virtual void Clear(UBlackboardComponent& OwnerComp, uint8* MemoryBlock) override;`
- L38 _protected prototype_ `virtual bool TestBasicOperation(const UBlackboardComponent& OwnerComp, const uint8* MemoryBlock, EBasicKeyOperation::Type Op) const override;`

### `Source/Runtime/AIModule/Classes/BehaviorTree/BlackboardAssetProvider.h` (Public)


#### class `UBlackboardAssetProvider`  
`class UBlackboardAssetProvider : public UInterface`  
_L16-19_
- reflection: `UINTERFACE(BlueprintType, MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`
- desc: Helper interface to allow FBlackboardKeySelector properties on DataAssets (and more). Used by FBlackboardSelectorDetails to access the related Blackboard based on UObject hierarchy. The asset containing the Blackboard should broadcast OnBlackboardOwnerChanged when ever the asset ptr changes.

#### class `IBlackboardAssetProvider`  
`class IBlackboardAssetProvider`  
_L21-33_
- L27 _private prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FBlackboardOwnerChanged, UObject* , UBlackboardData* );` — Delegate to be called by class implementing IBlackboardAssetProvider when the property containing the returned BlackboardData is changed (i.e. on PostEditChangeProperty).
- L28 _private member_ `static FBlackboardOwnerChanged OnBlackboardOwnerChanged;`
- L32 _private prototype_ `virtual UBlackboardData* GetBlackboardAsset() const PURE_VIRTUAL(IBlackboardAssetProvider::GetBlackboardAsset, return nullptr; );` — `UFUNCTION(BlueprintCallable, Category = GameplayTags)` — Returns BlackboardData referenced by the owner object.

#### Free symbols / members of external scopes

- L27 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FBlackboardOwnerChanged, UObject* , UBlackboardData* );` — Delegate to be called by class implementing IBlackboardAssetProvider when the property containing the returned BlackboardData is changed (i.e. on PostEditChangeProperty).

### `Source/Runtime/AIModule/Classes/BehaviorTree/BlackboardComponent.h` (Public)


#### enum `EBlackboardDescription::Type`  
`enum Type`  
_L31-37_
- L33 _public enumerator_ `OnlyValue`
- L34 _public enumerator_ `KeyWithValue`
- L35 _public enumerator_ `DetailedKeyWithValue`
- L36 _public enumerator_ `Full`

#### class `UBlackboardComponent`  
`class UBlackboardComponent : public UActorComponent`  
_L42-311_
- reflection: `UCLASS(ClassGroup = AI, meta = (BlueprintSpawnableComponent), hidecategories = (Sockets, Collision), MinimalAPI)`
- inherits: `UActorComponent`
- L47 _public prototype_ `UBlackboardComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L50 _public prototype_ `virtual void InitializeComponent() override;` — BEGIN UActorComponent overrides
- L51 _public prototype_ `virtual void UninitializeComponent() override;`
- L55 _public prototype_ `FName GetKeyName(FBlackboard::FKey KeyID) const;` — @return name of key
- L58 _public prototype_ `FBlackboard::FKey GetKeyID(const FName& KeyName) const;` — @return key ID from name
- L61 _public prototype_ `TSubclassOf<UBlackboardKeyType> GetKeyType(FBlackboard::FKey KeyID) const;` — @return class of value for given key
- L64 _public prototype_ `bool IsKeyInstanceSynced(FBlackboard::FKey KeyID) const;` — @return true if the key is marked as instance synced
- L67 _public prototype_ `int32 GetNumKeys() const;` — @return number of entries in data asset
- L70 _public prototype_ `bool HasValidAsset() const;` — @return true if blackboard have valid data asset
- L73 _public prototype_ `FDelegateHandle RegisterObserver(FBlackboard::FKey KeyID, const UObject* NotifyOwner, FOnBlackboardChangeNotification ObserverDelegate);` — register observer for blackboard key
- L76 _public prototype_ `void UnregisterObserver(FBlackboard::FKey KeyID, FDelegateHandle ObserverHandle);` — unregister observer from blackboard key
- L79 _public prototype_ `void UnregisterObserversFrom(const UObject* NotifyOwner);` — unregister all observers associated with given owner
- L82 _public prototype_ `void PauseObserverNotifications();` — pause observer change notifications, any new ones will be added to a queue
- L85 _public prototype_ `void ResumeObserverNotifications(bool bSendQueuedObserverNotifications);` — resume observer change notifications and, optionally, process the queued observation list
- L88 _public prototype_ `UBrainComponent* GetBrainComponent() const;` — @return associated behavior tree component
- L91 _public prototype_ `UBlackboardData* GetBlackboardAsset() const;` — @return blackboard data asset
- L94 _public prototype_ `void CacheBrainComponent(UBrainComponent& BrainComponent);` — caches UBrainComponent pointer to be used in communication
- L97 _public prototype_ `bool InitializeBlackboard(UBlackboardData& NewAsset);` — setup component for using given blackboard asset, returns true if blackboard is properly initialized for specified blackboard data
- L100 _public prototype_ `virtual bool IsCompatibleWith(const UBlackboardData* TestAsset) const;` — @return true if component can be used with specified blackboard asset
- L103 _public prototype_ `UObject* GetValueAsObject(const FName& KeyName) const;` — `UFUNCTION(BlueprintCallable, Category="AI|Components|Blackboard")`
- L106 _public prototype_ `UClass* GetValueAsClass(const FName& KeyName) const;` — `UFUNCTION(BlueprintCallable, Category="AI|Components|Blackboard")`
- L109 _public prototype_ `uint8 GetValueAsEnum(const FName& KeyName) const;` — `UFUNCTION(BlueprintCallable, Category="AI|Components|Blackboard")`
- L112 _public prototype_ `int32 GetValueAsInt(const FName& KeyName) const;` — `UFUNCTION(BlueprintCallable, Category="AI|Components|Blackboard")`
- L115 _public prototype_ `float GetValueAsFloat(const FName& KeyName) const;` — `UFUNCTION(BlueprintCallable, Category="AI|Components|Blackboard")`
- L118 _public prototype_ `bool GetValueAsBool(const FName& KeyName) const;` — `UFUNCTION(BlueprintCallable, Category="AI|Components|Blackboard")`
- L121 _public prototype_ `FString GetValueAsString(const FName& KeyName) const;` — `UFUNCTION(BlueprintCallable, Category="AI|Components|Blackboard")`
- L124 _public prototype_ `FName GetValueAsName(const FName& KeyName) const;` — `UFUNCTION(BlueprintCallable, Category="AI|Components|Blackboard")`
- L127 _public prototype_ `FVector GetValueAsVector(const FName& KeyName) const;` — `UFUNCTION(BlueprintCallable, Category="AI|Components|Blackboard")`
- L130 _public prototype_ `FRotator GetValueAsRotator(const FName& KeyName) const;` — `UFUNCTION(BlueprintCallable, Category="AI|Components|Blackboard")`
- L133 _public prototype_ `void SetValueAsObject(const FName& KeyName, UObject* ObjectValue);` — `UFUNCTION(BlueprintCallable, Category="AI|Components|Blackboard")`
- L136 _public prototype_ `void SetValueAsClass(const FName& KeyName, UClass* ClassValue);` — `UFUNCTION(BlueprintCallable, Category="AI|Components|Blackboard")`
- L139 _public prototype_ `void SetValueAsEnum(const FName& KeyName, uint8 EnumValue);` — `UFUNCTION(BlueprintCallable, Category="AI|Components|Blackboard")`
- L142 _public prototype_ `void SetValueAsInt(const FName& KeyName, int32 IntValue);` — `UFUNCTION(BlueprintCallable, Category="AI|Components|Blackboard")`
- L145 _public prototype_ `void SetValueAsFloat(const FName& KeyName, float FloatValue);` — `UFUNCTION(BlueprintCallable, Category="AI|Components|Blackboard")`
- L148 _public prototype_ `void SetValueAsBool(const FName& KeyName, bool BoolValue);` — `UFUNCTION(BlueprintCallable, Category="AI|Components|Blackboard")`
- L151 _public prototype_ `void SetValueAsString(const FName& KeyName, FString StringValue);` — `UFUNCTION(BlueprintCallable, Category="AI|Components|Blackboard")`
- L154 _public prototype_ `void SetValueAsName(const FName& KeyName, FName NameValue);` — `UFUNCTION(BlueprintCallable, Category="AI|Components|Blackboard")`
- L157 _public prototype_ `void SetValueAsVector(const FName& KeyName, FVector VectorValue);` — `UFUNCTION(BlueprintCallable, Category="AI|Components|Blackboard")`
- L160 _public prototype_ `void SetValueAsRotator(const FName& KeyName, FRotator VectorValue);` — `UFUNCTION(BlueprintCallable, Category = "AI|Components|Blackboard")`
- L164 _public prototype_ `bool IsVectorValueSet(const FName& KeyName) const;` — `UFUNCTION(BlueprintCallable, Category="AI|Components|Blackboard", Meta=( Tooltip="If the vector value has been set (and not cleared), this function returns true (indicating that the value should be valid). If it's not set, the vector value is invalid and this function will return false. (Also returns false if the key specified does not hold a vector.)"))`
- L165 _public prototype_ `bool IsVectorValueSet(FBlackboard::FKey KeyID) const;`
- L169 _public prototype_ `bool GetLocationFromEntry(const FName& KeyName, FVector& ResultLocation) const;` — `UFUNCTION(BlueprintCallable, Category="AI|Components|Blackboard")` — return false if call failed (most probably no such entry in BB)
- L170 _public prototype_ `bool GetLocationFromEntry(FBlackboard::FKey KeyID, FVector& ResultLocation) const;`
- L174 _public prototype_ `bool GetRotationFromEntry(const FName& KeyName, FRotator& ResultRotation) const;` — `UFUNCTION(BlueprintCallable, Category="AI|Components|Blackboard")` — return false if call failed (most probably no such entry in BB)
- L175 _public prototype_ `bool GetRotationFromEntry(FBlackboard::FKey KeyID, FRotator& ResultRotation) const;`
- L178 _public prototype_ `void ClearValue(const FName& KeyName);` — `UFUNCTION(BlueprintCallable, Category = "AI|Components|Blackboard")`
- L179 _public prototype_ `void ClearValue(FBlackboard::FKey KeyID);`
- L182 _public prototype_ `bool CopyKeyValue(FBlackboard::FKey SourceKeyID, FBlackboard::FKey DestinationID);` — Copy content from SourceKeyID to DestinationID and return true if it worked
- L185 _public prototype_ `template<class TDataClass> bool IsKeyOfType(const FName& KeyName) const;`
- L188 _public prototype_ `template<class TDataClass> bool IsKeyOfType(FBlackboard::FKey KeyID) const;`
- L191 _public prototype_ `template<class TDataClass> bool SetValue(const FName& KeyName, typename TDataClass::FDataType Value);`
- L194 _public prototype_ `template<class TDataClass> bool SetValue(FBlackboard::FKey KeyID, typename TDataClass::FDataType Value);`
- L197 _public prototype_ `template<class TDataClass> typename TDataClass::FDataType GetValue(const FName& KeyName) const;`
- L200 _public prototype_ `template<class TDataClass> typename TDataClass::FDataType GetValue(FBlackboard::FKey KeyID) const;`
- L203 _public function_ `inline uint8* GetKeyRawData(const FName& KeyName)` — get pointer to raw data for given key
- L204 _public function_ `inline uint8* GetKeyRawData(FBlackboard::FKey KeyID)`
- L206 _public function_ `inline const uint8* GetKeyRawData(const FName& KeyName) const`
- L207 _public function_ `inline const uint8* GetKeyRawData(FBlackboard::FKey KeyID) const`
- L210 _public function_ `inline bool IsValidKey(FBlackboard::FKey KeyID) const`
- L214 _public prototype_ `EBlackboardCompare::Type CompareKeyValues(TSubclassOf<UBlackboardKeyType> KeyType, FBlackboard::FKey KeyA, FBlackboard::FKey KeyB) const;` — compares blackboard's values under specified keys
- L216 _public prototype_ `FString GetDebugInfoString(EBlackboardDescription::Type Mode) const;`
- L219 _public prototype_ `FString DescribeKeyValue(const FName& KeyName, EBlackboardDescription::Type Mode) const;` — get description of value under given key
- L220 _public prototype_ `FString DescribeKeyValue(FBlackboard::FKey KeyID, EBlackboardDescription::Type Mode) const;`
- L224 _public prototype_ `virtual void DescribeSelfToVisLog(struct FVisualLogEntry* Snapshot) const;` — prepare blackboard snapshot for logs
- L231 _protected member_ `TObjectPtr<UBrainComponent> BrainComp;` — `UPROPERTY(transient)` — cached behavior tree component
- L237 _protected member_ `TObjectPtr<UBlackboardData> DefaultBlackboardAsset;` — `UPROPERTY(EditDefaultsOnly, Category = AI)` — data asset defining entries. Will be used as part of InitializeComponent call provided BlackboardAsset hasn't been already set (via a InitializeBlackboard call).
- L242 _protected member_ `TObjectPtr<UBlackboardData> BlackboardAsset;` — `UE_DEPRECATED_FORGAME(4.26, "Directly accessing BlackboardAsset is not longer supported. Use DefaultBlackboardAsset or InitializeBlackboard to set it and GetBlackboardAsset to retrieve it")` — `UPROPERTY(transient)` — internal use, current BB asset being used. Will be made private in the future
- L245 _protected member_ `TArray<uint8> ValueMemory;` — memory block holding all values
- L248 _protected member_ `TArray<uint16> ValueOffsets;` — offsets in ValueMemory for each key
- L252 _protected member_ `TArray<TObjectPtr<UBlackboardKeyType>> KeyInstances;` — `UPROPERTY(transient)` — instanced keys with custom data allocations
- L255 _protected member_ `bool bBlackboardMemoryInitialized = false;` — tracks whether memory used to store values in the blackboard has been fully initialized
- L276 _protected member_ `mutable int32 NotifyObserversRecursionCount = 0;` — Count of re-entrant observer notifications
- L279 _protected member_ `mutable int32 ObserversToRemoveCount = 0;` — Count of observers to remove
- L282 _protected member_ `mutable TMultiMap<FBlackboard::FKey, FOnBlackboardChangeNotificationInfo> Observers;` — observers registered for blackboard keys
- L285 _protected member_ `mutable TMultiMap<const UObject*, FDelegateHandle> ObserverHandles;` — observers registered from owner objects
- L288 _protected member_ `mutable TArray<FBlackboard::FKey> QueuedUpdates;` — queued key change notification, will be processed on ResumeUpdates call
- L291 _protected member_ `uint32 bPausedNotifies : 1;` — set when observation notifies are paused and shouldn't be passed to observers
- L294 _protected member_ `uint32 bSynchronizedKeyPopulated : 1;` — reset to false every time a new BB asset is assigned to this component
- L297 _protected prototype_ `void NotifyObservers(FBlackboard::FKey KeyID) const;` — notifies behavior tree decorators about change in blackboard
- L300 _protected prototype_ `void InitializeParentChain(UBlackboardData* NewAsset);` — initializes parent chain in asset
- L303 _protected prototype_ `void DestroyValues();` — destroy allocated values
- L306 _protected prototype_ `void PopulateSynchronizedKeys();` — populates BB's synchronized entries
- L308 _protected prototype_ `bool ShouldSyncWithBlackboard(UBlackboardComponent& OtherBlackboardComponent) const;`
- L318 _function_ `inline bool UBlackboardComponent::HasValidAsset() const`
- L324 _function_ `template<class TDataClass> bool UBlackboardComponent::IsKeyOfType(const FName& KeyName) const`
- L331 _function_ `template<class TDataClass> bool UBlackboardComponent::IsKeyOfType(FBlackboard::FKey KeyID) const`
- L338 _function_ `template<class TDataClass> bool UBlackboardComponent::SetValue(const FName& KeyName, typename TDataClass::FDataType Value)`
- L345 _function_ `template<class TDataClass> bool UBlackboardComponent::SetValue(FBlackboard::FKey KeyID, typename TDataClass::FDataType Value)`
- L392 _function_ `template<class TDataClass> typename TDataClass::FDataType UBlackboardComponent::GetValue(const FName& KeyName) const`
- L399 _function_ `template<class TDataClass> typename TDataClass::FDataType UBlackboardComponent::GetValue(FBlackboard::FKey KeyID) const`

#### struct `UBlackboardComponent::FOnBlackboardChangeNotificationInfo`  
`struct FOnBlackboardChangeNotificationInfo`  
_L258-272_
- L260 _public function_ `FOnBlackboardChangeNotificationInfo(const FOnBlackboardChangeNotification& InDelegateHandle) : DelegateHandle(InDelegateHandle)`
- L265 _public function_ `FDelegateHandle GetHandle() const`
- L270 _public member_ `FOnBlackboardChangeNotification DelegateHandle;`
- L271 _public member_ `bool bToBeRemoved = false;`

#### struct `FBBKeyCachedAccessor`  
`template<typename TBlackboardKey> struct FBBKeyCachedAccessor`  
_L442-495_
- desc: A helper type that improved performance of reading data from BB It's meant for a specific use-case: 1.	you have a logical property you want to use both in C++ code as well as being reflected in the BB 2.	you only ever set this property in native code If those two are true then add a member variable of type FBlackboardCachedAccessor like so: FBlackboardCachedAccessor<UBlackboardKeyType_Bool> BBEnemyInMeleeRangeKey; and from this point on whenever you set or read the value use this variable. This will make reading almost free. Before you use the variable you need to initialize it with appropriate BB asset. This is best done in AAIController::InitializeBlackboard override, like so: const FBlackboard::FKey EnemyInMeleeRangeKey = BlackboardAsset.GetKeyID(TEXT("EnemyInMeleeRange")); BBEnemyInMeleeRangeKey = FBlackboardCachedAccessor<UBlackboardKeyType_Bool>(BlackboardComp, EnemyInMeleeRangeKey); Best used with numerical and boolean types. No guarantees made when using pointer types. @note does not automatically support BB component or asset change
- L445 _private member_ `FBlackboard::FKey BBKey;`
- L446 _private typedef_ `typedef typename TBlackboardKey::FDataType FStoredType;`
- L447 _private member_ `FStoredType CachedValue;`
- L449 _public function_ `FBBKeyCachedAccessor() : BBKey(FBlackboard::InvalidKey), CachedValue(TBlackboardKey::InvalidValue)`
- L452 _public function_ `FBBKeyCachedAccessor(const UBlackboardComponent& BBComponent, FBlackboard::FKey InBBKey)`
- L463 _public function_ `template<typename T2> inline bool SetValue(UBlackboardComponent& BBComponent, const T2 InValue)`
- L469 _public function_ `inline bool SetValue(UBlackboardComponent& BBComponent, const FStoredType InValue)` — @return True is value has changed
- L481 _public function_ `inline const FStoredType& Get() const`
- L488 _public function_ `template<typename T2> inline T2 Get() const`
- L494 _public function_ `bool IsValid() const`

#### Free symbols / members of external scopes

- L29 _namespace_ `namespace EBlackboardDescription`

### `Source/Runtime/AIModule/Classes/BehaviorTree/BlackboardData.h` (Public)


#### struct `FBlackboardEntry`  
`struct FBlackboardEntry`  
_L14-42_
- reflection: `USTRUCT()`
- desc: blackboard entry definition
- L19 _public member_ `FName EntryName;` — `UPROPERTY(EditAnywhere, Category=Blackboard)`
- L23 _public member_ `FString EntryDescription;` — `UPROPERTY(EditAnywhere, Category=Blackboard, Meta=(ToolTip="Optional description to explain what this blackboard entry does."))`
- L26 _public member_ `FName EntryCategory;` — `UPROPERTY(EditAnywhere, Category=Blackboard)`
- L31 _public member_ `TObjectPtr<UBlackboardKeyType> KeyType;` — `UPROPERTY(EditAnywhere, Instanced, Category = Blackboard, meta = (AllowEditInlineCustomization))` — key type and additional properties
- L35 _public member_ `uint32 bInstanceSynced : 1;` — `UPROPERTY(EditAnywhere, Category=Blackboard)` — if set to true then this field will be synchronized across all instances of this blackboard
- L37 _public function_ `FBlackboardEntry() : KeyType(nullptr), bInstanceSynced(0)`
- L41 _public prototype_ `bool operator==(const FBlackboardEntry& Other) const;`

#### class `UBlackboardData`  
`class UBlackboardData : public UDataAsset`  
_L45-182_
- reflection: `UCLASS(BlueprintType, AutoExpandCategories=(Blackboard), MinimalAPI)`
- inherits: `UDataAsset`
- L48 _private prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FKeyUpdate, UBlackboardData* );`
- L52 _private member_ `TObjectPtr<UBlackboardData> Parent;` — `UPROPERTY(EditAnywhere, Category=Parent)` — parent blackboard (keys can be overridden)
- L57 _private member_ `TArray<FBlackboardEntry> ParentKeys;` — `UPROPERTY(VisibleDefaultsOnly, Transient, Category=Parent)` — all keys inherited from parent chain
- L62 _private member_ `TArray<FBlackboardEntry> Keys;` — `UPROPERTY(EditAnywhere, Category=Blackboard)` — blackboard keys
- L66 _private member_ `uint32 bHasSynchronizedKeys : 1;` — `UPROPERTY()`
- L70 _public function_ `inline bool HasSynchronizedKeys() const`
- L73 _public prototype_ `bool IsKeyInstanceSynced(FBlackboard::FKey KeyID) const;` — @return true if the key is instance synced
- L76 _public prototype_ `FBlackboard::FKey GetKeyID(const FName& KeyName) const;` — @return key ID from name
- L79 _public prototype_ `FName GetKeyName(FBlackboard::FKey KeyID) const;` — @return name of key
- L82 _public prototype_ `TSubclassOf<UBlackboardKeyType> GetKeyType(FBlackboard::FKey KeyID) const;` — @return class of value for given key
- L85 _public prototype_ `int32 GetNumKeys() const;` — @return number of defined keys, including parent chain
- L87 _public function_ `inline FBlackboard::FKey GetFirstKeyID() const`
- L89 _public function_ `bool IsValidKey(FBlackboard::FKey KeyID) const`
- L92 _public prototype_ `const FBlackboardEntry* GetKey(FBlackboard::FKey KeyID) const;` — @return key data
- L94 _public function_ `const TArray<FBlackboardEntry>& GetKeys() const`
- L96 _public prototype_ `virtual void PostInitProperties() override;`
- L97 _public prototype_ `virtual void PostLoad() override;`
- L99 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L101 _public prototype_ `void PropagateKeyChangesToDerivedBlackboardAssets();`
- L104 _public prototype_ `bool IsValid() const;` — @return true if blackboard keys are not conflicting with parent key chain
- L110 _public function_ `template<class T> T* UpdatePersistentKey(const FName& KeyName)` — updates persistent key with given name, depending on currently defined entries and parent chain @return key type of newly created entry for further setup
- L140 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FBlackboardDataChanged, UBlackboardData* );` — A delegate called on PostEditChangeProperty. Can be used in editor to react to asset changes.
- L141 _public member_ `static FBlackboardDataChanged OnBlackboardDataChanged;`
- L146 _public member_ `static FKeyUpdate OnUpdateKeys;` — delegate called for every loaded blackboard asset meant for adding game specific persistent keys
- L149 _public prototype_ `void UpdateParentKeys();` — updates parent key cache for editor
- L152 _public prototype_ `void UpdateKeyIDs();` — forces update of FirstKeyID, which depends on parent chain
- L154 _public prototype_ `void UpdateIfHasSynchronizedKeys();`
- L157 _public prototype_ `void UpdateDeprecatedKeys();` — fix entries with deprecated key types
- L160 _public prototype_ `bool IsChildOf(const UBlackboardData& OtherAsset) const;` — returns true if OtherAsset is somewhere up the parent chain of this asset. Node that it will return false if *this == OtherAsset
- L163 _public function_ `bool IsRelatedTo(const UBlackboardData& OtherAsset) const` — returns true if OtherAsset is equal to *this, or is it's parent, or *this is OtherAsset's parent
- L178 _protected member_ `FBlackboard::FKey FirstKeyID;` — @return first ID for keys of this asset (parent keys goes first)
- L181 _protected prototype_ `FBlackboard::FKey InternalGetKeyID(const FName& KeyName, EKeyLookupMode LookupMode) const;` — @return key ID from name

#### enum `UBlackboardData::EKeyLookupMode`  
`enum EKeyLookupMode`  
_L171-175_
- L173 _public enumerator_ `CheckParentKeys`
- L174 _public enumerator_ `DontCheckParentKeys`

#### Free symbols / members of external scopes

- L48 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FKeyUpdate, UBlackboardData* );`
- L140 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FBlackboardDataChanged, UBlackboardData* );` — A delegate called on PostEditChangeProperty. Can be used in editor to react to asset changes.

### `Source/Runtime/AIModule/Classes/BehaviorTree/Composites/BTComposite_Selector.h` (Public)


#### class `UBTComposite_Selector`  
`class UBTComposite_Selector: public UBTCompositeNode`  
_L15-24_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBTCompositeNode`
- desc: Selector composite node. Selector Nodes execute their children from left to right, and will stop executing its children when one of their children succeeds. If a Selector's child succeeds, the Selector succeeds. If all the Selector's children fail, the Selector fails.
- L19 _private prototype_ `virtual int32 GetNextChildHandler(struct FBehaviorTreeSearchData& SearchData, int32 PrevChild, EBTNodeResult::Type LastResult) const override;`
- L22 _private prototype_ `virtual FName GetNodeIconName() const override;`

### `Source/Runtime/AIModule/Classes/BehaviorTree/Composites/BTComposite_Sequence.h` (Public)


#### class `UBTComposite_Sequence`  
`class UBTComposite_Sequence : public UBTCompositeNode`  
_L15-25_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBTCompositeNode`
- desc: Sequence composite node. Sequence Nodes execute their children from left to right, and will stop executing its children when one of their children fails. If a child fails, then the Sequence fails. If all the Sequence's children succeed, then the Sequence succeeds.
- L19 _private prototype_ `virtual int32 GetNextChildHandler(struct FBehaviorTreeSearchData& SearchData, int32 PrevChild, EBTNodeResult::Type LastResult) const override;`
- L22 _private prototype_ `virtual bool CanAbortLowerPriority() const override;`
- L23 _private prototype_ `virtual FName GetNodeIconName() const override;`

### `Source/Runtime/AIModule/Classes/BehaviorTree/Composites/BTComposite_SimpleParallel.h` (Public)


#### enum `EBTParallelChild::Type`  
`enum Type`  
_L12-16_
- L14 _public enumerator_ `MainTask`
- L15 _public enumerator_ `BackgroundTree`

#### enum `EBTParallelMode::Type`  
`enum Type : int`  
_L24-28_
- L26 _public enumerator_ `AbortBackground UMETA(DisplayName="Immediate" , ToolTip="When main task finishes, immediately abort background tree.")`
- L27 _public enumerator_ `WaitForBackground UMETA(DisplayName="Delayed" , ToolTip="When main task finishes, wait for background tree to finish.")`

#### struct `FBTParallelMemory`  
`struct FBTParallelMemory : public FBTCompositeMemory`  
_L31-47_
- inherits: `FBTCompositeMemory`
- L34 _public member_ `int32 LastSearchId;` — last Id of search, detect infinite loops when there isn't any valid task in background tree
- L37 _public member_ `TEnumAsByte<EBTNodeResult::Type> MainTaskResult;` — finish result of main task
- L40 _public member_ `uint8 bMainTaskIsActive : 1;` — set when main task is running
- L43 _public member_ `uint8 bForceBackgroundTree : 1;` — try running background tree task even if main task has finished
- L46 _public member_ `uint8 bRepeatMainTask : 1;` — set when main task needs to be repeated

#### class `UBTComposite_SimpleParallel`  
`class UBTComposite_SimpleParallel : public UBTCompositeNode`  
_L54-84_
- reflection: `UCLASS(HideCategories=(Composite), MinimalAPI)`
- inherits: `UBTCompositeNode`
- desc: Simple Parallel composite node. Allows for running two children: one which must be a single task node (with optional decorators), and the other of which can be a complete subtree.
- L60 _private member_ `TEnumAsByte<EBTParallelMode::Type> FinishMode;` — `UPROPERTY(EditInstanceOnly, Category = Parallel)` — how background tree should be handled when main task finishes execution
- L63 _private prototype_ `virtual int32 GetNextChildHandler(FBehaviorTreeSearchData& SearchData, int32 PrevChild, EBTNodeResult::Type LastResult) const override;` — handle child updates
- L65 _private prototype_ `virtual void NotifyChildExecution(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, int32 ChildIdx, EBTNodeResult::Type& NodeResult) const override;`
- L66 _private prototype_ `virtual void NotifyNodeDeactivation(FBehaviorTreeSearchData& SearchData, EBTNodeResult::Type& NodeResult) const override;`
- L67 _private prototype_ `virtual bool CanNotifyDecoratorsOnDeactivation(FBehaviorTreeSearchData& SearchData, int32 ChildIdx, EBTNodeResult::Type& NodeResult) const override;`
- L68 _private prototype_ `virtual bool CanPushSubtree(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, int32 ChildIdx) const override;`
- L69 _private prototype_ `virtual void SetChildOverride(FBehaviorTreeSearchData& SearchData, int8 Index) const override;`
- L70 _private prototype_ `virtual uint16 GetInstanceMemorySize() const override;`
- L71 _private prototype_ `virtual void InitializeMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryInit::Type InitType) const override;`
- L72 _private prototype_ `virtual void CleanupMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryClear::Type CleanupType) const override;`
- L73 _private prototype_ `virtual FString GetStaticDescription() const override;`
- L74 _private prototype_ `virtual void DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const override;`
- L77 _private prototype_ `static FString DescribeFinishMode(EBTParallelMode::Type Mode);` — helper for showing values of EBTParallelMode enum
- L80 _private prototype_ `virtual bool CanAbortLowerPriority() const override;`
- L81 _private prototype_ `virtual bool CanAbortSelf() const override;`
- L82 _private prototype_ `virtual FName GetNodeIconName() const override;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace EBTParallelChild`
- L20 _namespace_ `namespace EBTParallelMode`

### `Source/Runtime/AIModule/Classes/BehaviorTree/Decorators/BTDecorator_Blackboard.h` (Public)


#### enum `EBTBlackboardRestart::Type`  
`enum Type : int`  
_L24-28_
- L26 _public enumerator_ `ValueChange UMETA(DisplayName="On Value Change", ToolTip="Restart on every change of observed blackboard value")`
- L27 _public enumerator_ `ResultChange UMETA(DisplayName="On Result Change", ToolTip="Restart only when result of evaluated condition is changed")`

#### class `UBTDecorator_Blackboard`  
`class UBTDecorator_Blackboard : public UBTDecorator_BlackboardBase`  
_L36-105_
- reflection: `UCLASS(HideCategories=(Condition), MinimalAPI)`
- inherits: `UBTDecorator_BlackboardBase`
- desc: Blackboard decorator node. A decorator node that bases its condition on a Blackboard key.
- L40 _private prototype_ `virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;`
- L41 _private prototype_ `virtual EBlackboardNotificationResult OnBlackboardKeyValueChange(const UBlackboardComponent& Blackboard, FBlackboard::FKey ChangedKeyID) override;`
- L42 _private prototype_ `virtual void DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const override;`
- L43 _private prototype_ `virtual FString GetStaticDescription() const override;`
- L49 _protected member_ `int32 IntValue;` — `UPROPERTY(Category=Blackboard, EditAnywhere, meta=(DisplayName="Key Value"))` — value for arithmetic operations
- L53 _protected member_ `float FloatValue;` — `UPROPERTY(Category=Blackboard, EditAnywhere, meta=(DisplayName="Key Value"))` — value for arithmetic operations
- L57 _protected member_ `FString StringValue;` — `UPROPERTY(Category=Blackboard, EditAnywhere, meta=(DisplayName="Key Value"))` — value for string operations
- L61 _protected member_ `FString CachedDescription;` — `UPROPERTY()` — cached description
- L65 _protected member_ `uint8 OperationType;` — `UPROPERTY()` — operation type
- L69 _protected member_ `TEnumAsByte<EBTBlackboardRestart::Type> NotifyObserver;` — `UPROPERTY(Category=FlowControl, EditAnywhere)` — when observer can try to request abort?
- L74 _protected member_ `TEnumAsByte<EBasicKeyOperation::Type> BasicOperation;` — `UPROPERTY(Category=Blackboard, EditAnywhere, meta=(DisplayName="Key Query"))`
- L77 _protected member_ `TEnumAsByte<EArithmeticKeyOperation::Type> ArithmeticOperation;` — `UPROPERTY(Category=Blackboard, EditAnywhere, meta=(DisplayName="Key Query"))`
- L80 _protected member_ `TEnumAsByte<ETextKeyOperation::Type> TextOperation;` — `UPROPERTY(Category=Blackboard, EditAnywhere, meta=(DisplayName="Key Query"))`
- L87 _public prototype_ `virtual void BuildDescription();` — describe decorator and cache it
- L89 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L92 _protected prototype_ `virtual void InitializeFromAsset(UBehaviorTree& Asset) override;`
- L99 _protected prototype_ `void RefreshEnumBasedDecorator(const FBlackboardEntry& Entry);` — decorator using enum based key requires to synchronize 'StringValue' used for storage with 'IntValue' used for runtime evaluation. @note using custom serialization version was not possible since we require blackboard and used types (e.g. UserDefinedEnumerations) to be loaded and keys to be resolved (i.e. InitializeFromAsset).
- L102 _protected prototype_ `bool EvaluateOnBlackboard(const UBlackboardComponent& BlackboardComp) const;` — take blackboard value and evaluate decorator's condition

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace EBTBlackboardRestart`

### `Source/Runtime/AIModule/Classes/BehaviorTree/Decorators/BTDecorator_BlackboardBase.h` (Public)


#### class `UBTDecorator_BlackboardBase`  
`class UBTDecorator_BlackboardBase : public UBTDecorator`  
_L15-45_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UBTDecorator`
- L20 _private prototype_ `virtual void InitializeFromAsset(UBehaviorTree& Asset) override;` — initialize any asset related data
- L23 _private prototype_ `virtual EBlackboardNotificationResult OnBlackboardKeyValueChange(const UBlackboardComponent& Blackboard, FBlackboard::FKey ChangedKeyID);` — notify about change in blackboard keys
- L26 _private prototype_ `virtual FName GetNodeIconName() const override;`
- L27 _private prototype_ `virtual FString GetErrorMessage() const override;`
- L32 _public prototype_ `FName GetSelectedBlackboardKey() const;` — get name of selected blackboard key
- L38 _protected member_ `FBlackboardKeySelector BlackboardKey;` — `UPROPERTY(EditAnywhere, Category=Blackboard)` — blackboard key selector
- L41 _protected prototype_ `virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;` — called when execution flow controller becomes active
- L44 _protected prototype_ `virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;` — called when execution flow controller becomes inactive
- L50 _function_ `inline FName UBTDecorator_BlackboardBase::GetSelectedBlackboardKey() const`

### `Source/Runtime/AIModule/Classes/BehaviorTree/Decorators/BTDecorator_BlueprintBase.h` (Public)


#### class `UBTDecorator_BlueprintBase`  
`class UBTDecorator_BlueprintBase : public UBTDecorator`  
_L33-228_
- reflection: `UCLASS(Abstract, Blueprintable, MinimalAPI)`
- inherits: `UBTDecorator`
- L38 _public prototype_ `UBTDecorator_BlueprintBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L41 _public prototype_ `void InitializeProperties();` — initialize data about blueprint defined properties
- L44 _public prototype_ `virtual void PostInitProperties() override;` — setup node name
- L45 _public prototype_ `virtual void PostLoad() override;`
- L48 _public prototype_ `EBlackboardNotificationResult OnBlackboardKeyValueChange(const UBlackboardComponent& Blackboard, FBlackboard::FKey ChangedKeyID);` — notify about changes in blackboard
- L50 _public prototype_ `virtual FString GetStaticDescription() const override;`
- L51 _public prototype_ `virtual void DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const override;`
- L52 _public prototype_ `virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;`
- L53 _public prototype_ `virtual void OnInstanceDestroyed(UBehaviorTreeComponent& OwnerComp) override;`
- L54 _public prototype_ `virtual void InitializeFromAsset(UBehaviorTree& Asset) override;`
- L65 _public prototype_ `EAbortType EvaluateAbortType(UBehaviorTreeComponent& OwnerComp) const;` — return this decorator abort type in current circumstances
- L68 _public function_ `bool GetShouldAbort(UBehaviorTreeComponent& OwnerComp) const` — `UE_DEPRECATED(5.2, "Use GetShouldAbortType instead")`
- L73 _public prototype_ `virtual void SetOwner(AActor* ActorOwner) override;`
- L76 _public prototype_ `virtual FName GetNodeIconName() const override;`
- L77 _public prototype_ `virtual bool UsesBlueprint() const override;`
- L83 _protected member_ `TObjectPtr<AAIController> AIOwner;` — `UPROPERTY(Transient)` — Cached AIController owner of BehaviorTreeComponent.
- L87 _protected member_ `TObjectPtr<AActor> ActorOwner;` — `UPROPERTY(Transient)` — Cached AIController owner of BehaviorTreeComponent.
- L91 _protected member_ `TArray<FName> ObservedKeyNames;` — `UPROPERTY()` — blackboard key names that should be observed
- L94 _protected member_ `TArray<FProperty*> PropertyData;` — properties with runtime values, stored only in class default object
- L98 _protected member_ `FString CustomDescription;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Description)`
- L103 _protected member_ `uint32 bShowPropertyDetails : 1;` — `UPROPERTY(EditInstanceOnly, Category=Description)` — show detailed information about properties
- L109 _protected member_ `uint32 bCheckConditionOnlyBlackBoardChanges : 1;` — `UPROPERTY(EditDefaultsOnly, Category = "FlowControl", AdvancedDisplay)` — Applies only if Decorator has any FBlackboardKeySelector property and if decorator is set to abort BT flow. Is set to true ReceiveConditionCheck will be called only on changes to observed BB keys. If false or no BB keys observed ReceiveConditionCheck will be called every tick
- L112 _protected member_ `uint32 bIsObservingBB : 1;` — gets set to true if decorator declared BB keys it can potentially observe
- L115 _protected member_ `uint32 ReceiveTickImplementations : 2;` — set if ReceiveTick is implemented by blueprint
- L118 _protected member_ `uint32 ReceiveExecutionStartImplementations : 2;` — set if ReceiveExecutionStart is implemented by blueprint
- L121 _protected member_ `uint32 ReceiveExecutionFinishImplementations : 2;` — set if ReceiveExecutionFinish is implemented by blueprint
- L124 _protected member_ `uint32 ReceiveObserverActivatedImplementations : 2;` — set if ReceiveObserverActivated is implemented by blueprint
- L127 _protected member_ `uint32 ReceiveObserverDeactivatedImplementations : 2;` — set if ReceiveObserverDeactivated is implemented by blueprint
- L130 _protected member_ `uint32 PerformConditionCheckImplementations : 2;` — set if ReceiveConditionCheck is implemented by blueprint
- L132 _protected prototype_ `virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L133 _protected prototype_ `virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L134 _protected prototype_ `virtual void OnNodeActivation(FBehaviorTreeSearchData& SearchData) override;`
- L135 _protected prototype_ `virtual void OnNodeDeactivation(FBehaviorTreeSearchData& SearchData, EBTNodeResult::Type NodeResult) override;`
- L136 _protected prototype_ `virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;`
- L142 _protected prototype_ `void ReceiveTick(AActor* OwnerActor, float DeltaSeconds);` — `UFUNCTION(BlueprintImplementableEvent)` — tick function @Note that if both generic and AI event versions are implemented only the more suitable one will be called, meaning the AI version if called for AI, generic one otherwise
- L148 _protected prototype_ `void ReceiveExecutionStart(AActor* OwnerActor);` — `UFUNCTION(BlueprintImplementableEvent)` — called on execution of underlying node @Note that if both generic and AI event versions are implemented only the more suitable one will be called, meaning the AI version if called for AI, generic one otherwise
- L154 _protected prototype_ `void ReceiveExecutionFinish(AActor* OwnerActor, enum EBTNodeResult::Type NodeResult);` — `UFUNCTION(BlueprintImplementableEvent)` — called when execution of underlying node is finished @Note that if both generic and AI event versions are implemented only the more suitable one will be called, meaning the AI version if called for AI, generic one otherwise
- L160 _protected prototype_ `void ReceiveObserverActivated(AActor* OwnerActor);` — `UFUNCTION(BlueprintImplementableEvent)` — called when observer is activated (flow controller) @Note that if both generic and AI event versions are implemented only the more suitable one will be called, meaning the AI version if called for AI, generic one otherwise
- L166 _protected prototype_ `void ReceiveObserverDeactivated(AActor* OwnerActor);` — `UFUNCTION(BlueprintImplementableEvent)` — called when observer is deactivated (flow controller) @Note that if both generic and AI event versions are implemented only the more suitable one will be called, meaning the AI version if called for AI, generic one otherwise
- L172 _protected prototype_ `bool PerformConditionCheck(AActor* OwnerActor);` — `UFUNCTION(BlueprintImplementableEvent)` — called when testing if underlying node can be executed, must call FinishConditionCheck @Note that if both generic and AI event versions are implemented only the more suitable one will be called, meaning the AI version if called for AI, generic one otherwise
- L179 _protected prototype_ `void ReceiveTickAI(AAIController* OwnerController, APawn* ControlledPawn, float DeltaSeconds);` — `UFUNCTION(BlueprintImplementableEvent, Category = AI)` — Alternative AI version of ReceiveTick @see ReceiveTick for more details @Note that if both generic and AI event versions are implemented only the more suitable one will be called, meaning the AI version if called for AI, generic one otherwise
- L186 _protected prototype_ `void ReceiveExecutionStartAI(AAIController* OwnerController, APawn* ControlledPawn);` — `UFUNCTION(BlueprintImplementableEvent, Category = AI)` — Alternative AI version of ReceiveExecutionStart @see ReceiveExecutionStart for more details @Note that if both generic and AI event versions are implemented only the more suitable one will be called, meaning the AI version if called for AI, generic one otherwise
- L193 _protected prototype_ `void ReceiveExecutionFinishAI(AAIController* OwnerController, APawn* ControlledPawn, enum EBTNodeResult::Type NodeResult);` — `UFUNCTION(BlueprintImplementableEvent, Category = AI)` — Alternative AI version of ReceiveExecutionFinish @see ReceiveExecutionFinish for more details @Note that if both generic and AI event versions are implemented only the more suitable one will be called, meaning the AI version if called for AI, generic one otherwise
- L200 _protected prototype_ `void ReceiveObserverActivatedAI(AAIController* OwnerController, APawn* ControlledPawn);` — `UFUNCTION(BlueprintImplementableEvent, Category = AI)` — Alternative AI version of ReceiveObserverActivated @see ReceiveObserverActivated for more details @Note that if both generic and AI event versions are implemented only the more suitable one will be called, meaning the AI version if called for AI, generic one otherwise
- L207 _protected prototype_ `void ReceiveObserverDeactivatedAI(AAIController* OwnerController, APawn* ControlledPawn);` — `UFUNCTION(BlueprintImplementableEvent, Category = AI)` — Alternative AI version of ReceiveObserverDeactivated @see ReceiveObserverDeactivated for more details @Note that if both generic and AI event versions are implemented only the more suitable one will be called, meaning the AI version if called for AI, generic one otherwise
- L214 _protected prototype_ `bool PerformConditionCheckAI(AAIController* OwnerController, APawn* ControlledPawn);` — `UFUNCTION(BlueprintImplementableEvent, Category = AI)` — Alternative AI version of ReceiveConditionCheck @see ReceiveConditionCheck for more details @Note that if both generic and AI event versions are implemented only the more suitable one will be called, meaning the AI version if called for AI, generic one otherwise
- L218 _protected prototype_ `bool IsDecoratorExecutionActive() const;` — `UFUNCTION(BlueprintCallable, Category="AI|BehaviorTree")` — check if decorator is part of currently active branch
- L222 _protected prototype_ `bool IsDecoratorObserverActive() const;` — `UFUNCTION(BlueprintCallable, Category="AI|BehaviorTree")` — check if decorator's observer is currently active
- L224 _protected function_ `inline bool GetNeedsTickForConditionChecking() const`
- L227 _protected prototype_ `void RequestAbort(UBehaviorTreeComponent& OwnerComp, const EAbortType Type);` — Handle abort request calls from the specified abort type

#### enum `UBTDecorator_BlueprintBase::EAbortType`  
`enum class EAbortType : uint8`  
_L56-62_
- L58 _public enumerator_ `NoAbort`
- L59 _public enumerator_ `ActivateBranch`
- L60 _public enumerator_ `DeactivateBranch`
- L61 _public enumerator_ `Unknown`

### `Source/Runtime/AIModule/Classes/BehaviorTree/Decorators/BTDecorator_CheckGameplayTagsOnActor.h` (Public)


#### class `UBTDecorator_CheckGameplayTagsOnActor`  
`class UBTDecorator_CheckGameplayTagsOnActor : public UBTDecorator`  
_L19-51_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBTDecorator`
- desc: GameplayTag decorator node. A decorator node that bases its condition on whether the specified Actor (in the blackboard) has a Gameplay Tag or Tags specified.
- L23 _private prototype_ `virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;`
- L24 _private prototype_ `virtual void DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const override;`
- L25 _private prototype_ `virtual FString GetStaticDescription() const override;`
- L31 _protected member_ `struct FBlackboardKeySelector ActorToCheck;` — `UPROPERTY(EditAnywhere, Category=GameplayTagCheck, Meta=(ToolTips="Which Actor (from the blackboard) should be checked for these gameplay tags?"))`
- L34 _protected member_ `EGameplayContainerMatchType TagsToMatch;` — `UPROPERTY(EditAnywhere, Category=GameplayTagCheck)`
- L37 _protected member_ `FGameplayTagContainer GameplayTags;` — `UPROPERTY(EditAnywhere, Category=GameplayTagCheck)`
- L41 _protected member_ `FString CachedDescription;` — `UPROPERTY()` — cached description
- L45 _protected prototype_ `virtual void BuildDescription();` — describe decorator and cache it
- L46 _protected prototype_ `virtual FString GetErrorMessage() const override;`
- L47 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L50 _protected prototype_ `virtual void InitializeFromAsset(UBehaviorTree& Asset) override;`

### `Source/Runtime/AIModule/Classes/BehaviorTree/Decorators/BTDecorator_CompareBBEntries.h` (Public)


#### enum `EBlackBoardEntryComparison::Type`  
`enum Type : int`  
_L18-22_
- L20 _public enumerator_ `Equal UMETA(DisplayName="Is Equal To")`
- L21 _public enumerator_ `NotEqual UMETA(DisplayName="Is Not Equal To")`

#### class `UBTDecorator_CompareBBEntries`  
`class UBTDecorator_CompareBBEntries : public UBTDecorator`  
_L30-63_
- reflection: `UCLASS(HideCategories=(Condition), MinimalAPI)`
- inherits: `UBTDecorator`
- desc: Blackboard comparison decorator node. A decorator node that bases its condition on a comparison between two Blackboard keys.
- L38 _protected member_ `TEnumAsByte<EBlackBoardEntryComparison::Type> Operator;` — `UPROPERTY(EditAnywhere, Category=Blackboard)` — operation type
- L42 _protected member_ `FBlackboardKeySelector BlackboardKeyA;` — `UPROPERTY(EditAnywhere, Category=Blackboard)` — blackboard key selector
- L46 _protected member_ `FBlackboardKeySelector BlackboardKeyB;` — `UPROPERTY(EditAnywhere, Category=Blackboard)` — blackboard key selector
- L50 _public prototype_ `virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;`
- L51 _public prototype_ `virtual FString GetStaticDescription() const override;`
- L53 _public prototype_ `virtual void InitializeFromAsset(UBehaviorTree& Asset) override;`
- L55 _public prototype_ `virtual EBlackboardNotificationResult OnBlackboardKeyValueChange(const UBlackboardComponent& Blackboard, FBlackboard::FKey ChangedKeyID);`
- L56 _public prototype_ `virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L57 _public prototype_ `virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L60 _public prototype_ `virtual FName GetNodeIconName() const override;`
- L61 _public prototype_ `virtual FString GetErrorMessage() const override;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace EBlackBoardEntryComparison`

### `Source/Runtime/AIModule/Classes/BehaviorTree/Decorators/BTDecorator_ConditionalLoop.h` (Public)


#### struct `FBTConditionalLoopDecoratorMemory`  
`struct FBTConditionalLoopDecoratorMemory`  
_L13-16_
- L15 _public member_ `int32 SearchId;`

#### class `UBTDecorator_ConditionalLoop`  
`class UBTDecorator_ConditionalLoop : public UBTDecorator_Blackboard`  
_L23-38_
- reflection: `UCLASS(HideCategories=(FlowControl), MinimalAPI)`
- inherits: `UBTDecorator_Blackboard`
- desc: Conditional loop decorator node. A decorator node that loops execution as long as condition is satisfied.
- L27 _private prototype_ `virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;`
- L28 _private prototype_ `virtual EBlackboardNotificationResult OnBlackboardKeyValueChange(const UBlackboardComponent& Blackboard, FBlackboard::FKey ChangedKeyID) override;`
- L29 _private prototype_ `virtual void OnNodeDeactivation(FBehaviorTreeSearchData& SearchData, EBTNodeResult::Type NodeResult) override;`
- L31 _private prototype_ `virtual uint16 GetInstanceMemorySize() const override;`
- L32 _private prototype_ `virtual void InitializeMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryInit::Type InitType) const override;`
- L33 _private prototype_ `virtual void CleanupMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryClear::Type CleanupType) const override;`
- L36 _private prototype_ `virtual FName GetNodeIconName() const override;`

### `Source/Runtime/AIModule/Classes/BehaviorTree/Decorators/BTDecorator_ConeCheck.h` (Public)


#### struct `FBTConeCheckDecoratorMemory`  
`struct FBTConeCheckDecoratorMemory`  
_L16-19_
- L18 _public member_ `bool bLastRawResult;`

#### class `UBTDecorator_ConeCheck`  
`class UBTDecorator_ConeCheck : public UBTDecorator`  
_L26-72_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBTDecorator`
- desc: Cone check decorator node. A decorator node that bases its condition on a cone check, using Blackboard entries to form the parameters of the check.
- L30 _private typedef_ `typedef FBTConeCheckDecoratorMemory TNodeInstanceMemory;`
- L34 _private member_ `FValueOrBBKey_Float ConeHalfAngle;` — `UPROPERTY(Category=Decorator, EditAnywhere)` — Angle between cone direction and code cone edge, or a half of the total cone angle
- L38 _private member_ `FBlackboardKeySelector ConeOrigin;` — `UPROPERTY(EditAnywhere, Category=Blackboard)` — blackboard key selector
- L42 _private member_ `FBlackboardKeySelector ConeDirection;` — `UPROPERTY(EditAnywhere, Category=Blackboard)` — "None" means "use ConeOrigin's direction"
- L46 _private member_ `FBlackboardKeySelector Observed;` — `UPROPERTY(EditAnywhere, Category=Blackboard)` — blackboard key selector
- L48 _private prototype_ `virtual void InitializeFromAsset(UBehaviorTree& Asset) override;`
- L49 _private prototype_ `virtual uint16 GetInstanceMemorySize() const override;`
- L50 _private prototype_ `virtual void InitializeMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryInit::Type InitType) const override;`
- L51 _private prototype_ `virtual void CleanupMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryClear::Type CleanupType) const override;`
- L52 _private prototype_ `virtual void DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const override;`
- L53 _private prototype_ `virtual FString GetStaticDescription() const override;`
- L56 _private prototype_ `virtual FName GetNodeIconName() const override;`
- L57 _private prototype_ `virtual FString GetErrorMessage() const override;`
- L61 _protected prototype_ `float GetConeHalfAngleDot(const UBehaviorTreeComponent& OwnerComp) const;`
- L62 _protected prototype_ `virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;`
- L63 _protected prototype_ `virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L64 _protected prototype_ `void OnBlackboardChange(const UBlackboardComponent& Blackboard, FBlackboard::FKey ChangedKeyID);`
- L66 _protected prototype_ `virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;`
- L68 _protected prototype_ `bool CalculateDirection(const UBlackboardComponent* BlackboardComp, const FBlackboardKeySelector& Origin, const FBlackboardKeySelector& End, FVector& Direction) const;`
- L71 _private prototype_ `bool CalcConditionImpl(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;`

### `Source/Runtime/AIModule/Classes/BehaviorTree/Decorators/BTDecorator_Cooldown.h` (Public)


#### struct `FBTCooldownDecoratorMemory`  
`struct FBTCooldownDecoratorMemory`  
_L11-15_
- L13 _public member_ `double LastUseTimestamp;`
- L14 _public member_ `uint8 bRequestedRestart : 1;`

#### class `UBTDecorator_Cooldown`  
`class UBTDecorator_Cooldown : public UBTDecorator`  
_L22-49_
- reflection: `UCLASS(HideCategories=(Condition), MinimalAPI)`
- inherits: `UBTDecorator`
- desc: Cooldown decorator node. A decorator node that bases its condition on whether a cooldown timer has expired.
- L28 _private member_ `FValueOrBBKey_Float CoolDownTime;` — `UPROPERTY(Category=Decorator, EditAnywhere)` — max allowed time for execution of underlying node
- L31 _private prototype_ `virtual void PostLoad() override;`
- L34 _private prototype_ `virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;`
- L35 _private prototype_ `virtual void InitializeMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryInit::Type InitType) const override;`
- L36 _private prototype_ `virtual void CleanupMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryClear::Type CleanupType) const override;`
- L37 _private prototype_ `virtual uint16 GetInstanceMemorySize() const override;`
- L38 _private prototype_ `virtual void DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const override;`
- L39 _private prototype_ `virtual FString GetStaticDescription() const override;`
- L42 _private prototype_ `virtual FName GetNodeIconName() const override;`
- L47 _protected prototype_ `virtual void OnNodeDeactivation(FBehaviorTreeSearchData& SearchData, EBTNodeResult::Type NodeResult) override;`
- L48 _protected prototype_ `virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;`

### `Source/Runtime/AIModule/Classes/BehaviorTree/Decorators/BTDecorator_DoesPathExist.h` (Public)


#### enum `EPathExistanceQueryType::Type`  
`enum Type : int`  
_L19-24_
- L21 _public enumerator_ `NavmeshRaycast2D UMETA(ToolTip = "Really Fast")`
- L22 _public enumerator_ `HierarchicalQuery UMETA(ToolTip = "Fast")`
- L23 _public enumerator_ `RegularPathFinding UMETA(ToolTip = "Slow")`

#### class `UBTDecorator_DoesPathExist`  
`class UBTDecorator_DoesPathExist : public UBTDecorator`  
_L32-67_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBTDecorator`
- desc: Does Path Exist decorator node. A decorator node that bases its condition on whether a path exists between two points from the Blackboard.
- L40 _protected member_ `FBlackboardKeySelector BlackboardKeyA;` — `UPROPERTY(EditAnywhere, Category=Condition)` — blackboard key selector
- L44 _protected member_ `FBlackboardKeySelector BlackboardKeyB;` — `UPROPERTY(EditAnywhere, Category=Condition)` — blackboard key selector
- L50 _public member_ `uint32 bUseSelf:1;` — `UPROPERTY()` — deprecated, set value of blackboard key A on initialization
- L53 _public member_ `FValueOrBBKey_Enum PathQueryType;` — `UPROPERTY(EditAnywhere, Category=Condition)`
- L57 _public member_ `FValueOrBBKey_Class FilterClass = TSubclassOf<UNavigationQueryFilter>();` — `UPROPERTY(Category=Node, EditAnywhere)` — "None" will result in default filter being used
- L59 _public prototype_ `virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;`
- L60 _public prototype_ `virtual FString GetStaticDescription() const override;`
- L61 _public prototype_ `virtual void InitializeFromAsset(UBehaviorTree& Asset) override;`
- L64 _public prototype_ `virtual FName GetNodeIconName() const override;`
- L65 _public prototype_ `virtual FString GetErrorMessage() const override;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace EPathExistanceQueryType`

### `Source/Runtime/AIModule/Classes/BehaviorTree/Decorators/BTDecorator_ForceSuccess.h` (Public)


#### class `UBTDecorator_ForceSuccess`  
`class UBTDecorator_ForceSuccess : public UBTDecorator`  
_L20-31_
- reflection: `UCLASS(HideCategories=(Condition), MinimalAPI)`
- inherits: `UBTDecorator`
- L26 _protected prototype_ `virtual void OnNodeProcessed(struct FBehaviorTreeSearchData& SearchData, EBTNodeResult::Type& NodeResult) override;`
- L29 _protected prototype_ `virtual FName GetNodeIconName() const override;`

### `Source/Runtime/AIModule/Classes/BehaviorTree/Decorators/BTDecorator_IsAtLocation.h` (Public)


#### class `UBTDecorator_IsAtLocation`  
`class UBTDecorator_IsAtLocation : public UBTDecorator_BlackboardBase`  
_L18-54_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBTDecorator_BlackboardBase`
- desc: Is At Location decorator node. A decorator node that checks if AI controlled pawn is at given location.
- L24 _private member_ `float AcceptableRadius;` — `UPROPERTY(EditAnywhere, Category = Condition, meta = (ClampMin = "0.0", EditCondition = "!bUseParametrizedRadius"))` — distance threshold to accept as being at location
- L27 _private member_ `FAIDataProviderFloatValue ParametrizedAcceptableRadius;` — `UPROPERTY(EditAnywhere, Category = Condition, meta = (EditCondition = "bUseParametrizedRadius"))`
- L30 _private member_ `FAIDistanceType GeometricDistanceType;` — `UPROPERTY(EditAnywhere, Category = Condition, meta = (EditCondition = "!bPathFindingBasedTest"))`
- L33 _private member_ `uint32 bUseParametrizedRadius : 1;` — `UPROPERTY()`
- L37 _private member_ `FValueOrBBKey_Bool bUseNavAgentGoalLocation;` — `UPROPERTY(EditAnywhere, Category = Condition, DisplayName = UseNavAgentGoalLocation, meta = (EditCondition = "bPathFindingBasedTest"))` — if moving to an actor and this actor is a nav agent, then we will move to their nav agent location
- L42 _private member_ `FValueOrBBKey_Bool bPathFindingBasedTest;` — `UPROPERTY(EditAnywhere, Category = Condition, DisplayName = PathFindingBasedTest)` — If true the result will be consistent with tests done while following paths. Set to false to use geometric distance as configured with DistanceType
- L44 _private prototype_ `virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;`
- L46 _private prototype_ `virtual FString GetStaticDescription() const override;`
- L49 _private prototype_ `virtual FName GetNodeIconName() const override;`
- L53 _protected prototype_ `FVector::FReal GetGeometricDistanceSquared(const FVector& A, const FVector& B) const;`

### `Source/Runtime/AIModule/Classes/BehaviorTree/Decorators/BTDecorator_IsBBEntryOfClass.h` (Public)


#### class `UBTDecorator_IsBBEntryOfClass`  
`class UBTDecorator_IsBBEntryOfClass : public UBTDecorator_BlackboardBase`  
_L18-35_
- reflection: `UCLASS(HideCategories=(Condition), MinimalAPI)`
- inherits: `UBTDecorator_BlackboardBase`
- L23 _public prototype_ `UBTDecorator_IsBBEntryOfClass(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L28 _protected member_ `FValueOrBBKey_Class TestClass = TSubclassOf<UObject>();` — `UPROPERTY(Category = Blackboard, EditAnywhere)`
- L31 _protected prototype_ `virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;`
- L32 _protected prototype_ `virtual EBlackboardNotificationResult OnBlackboardKeyValueChange(const UBlackboardComponent& Blackboard, FBlackboard::FKey ChangedKeyID) override;`
- L33 _protected prototype_ `virtual void DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const override;`
- L34 _protected prototype_ `virtual FString GetStaticDescription() const override;`

### `Source/Runtime/AIModule/Classes/BehaviorTree/Decorators/BTDecorator_KeepInCone.h` (Public)


#### struct `FBTKeepInConeDecoratorMemory`  
`struct FBTKeepInConeDecoratorMemory`  
_L14-17_
- L16 _public member_ `FVector InitialDirection;`

#### class `UBTDecorator_KeepInCone`  
`class UBTDecorator_KeepInCone : public UBTDecorator`  
_L24-70_
- reflection: `UCLASS(HideCategories=(Condition), MinimalAPI)`
- inherits: `UBTDecorator`
- desc: Keep In Cone decorator node. A decorator node that bases its condition on whether the observed position is still inside a cone. The cone's direction is calculated when the node first becomes relevant.
- L28 _private typedef_ `typedef FBTKeepInConeDecoratorMemory TNodeInstanceMemory;`
- L32 _private member_ `FValueOrBBKey_Float ConeHalfAngle;` — `UPROPERTY(Category=Decorator, EditAnywhere)` — max allowed time for execution of underlying node
- L36 _private member_ `FBlackboardKeySelector ConeOrigin;` — `UPROPERTY(EditAnywhere, Category=Blackboard)` — blackboard key selector
- L40 _private member_ `FBlackboardKeySelector Observed;` — `UPROPERTY(EditAnywhere, Category=Blackboard)` — blackboard key selector
- L44 _private member_ `uint32 bUseSelfAsOrigin:1;` — `UPROPERTY()` — deprecated, set value of ConeOrigin on initialization
- L48 _private member_ `uint32 bUseSelfAsObserved:1;` — `UPROPERTY()` — deprecated, set value of Observed on initialization
- L50 _private prototype_ `float GetConeHalfAngleDot(const UBehaviorTreeComponent& OwnerComp) const;`
- L52 _private prototype_ `virtual void InitializeFromAsset(UBehaviorTree& Asset) override;`
- L53 _private prototype_ `virtual uint16 GetInstanceMemorySize() const override;`
- L54 _private prototype_ `virtual void InitializeMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryInit::Type InitType) const override;`
- L55 _private prototype_ `virtual void CleanupMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryClear::Type CleanupType) const override;`
- L56 _private prototype_ `virtual void DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const override;`
- L57 _private prototype_ `virtual FString GetStaticDescription() const override;`
- L60 _private prototype_ `virtual FName GetNodeIconName() const override;`
- L61 _private prototype_ `virtual FString GetErrorMessage() const override;`
- L66 _protected prototype_ `virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L67 _protected prototype_ `virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;`
- L69 _protected prototype_ `bool CalculateCurrentDirection(const UBehaviorTreeComponent& OwnerComp, FVector& Direction) const;`

### `Source/Runtime/AIModule/Classes/BehaviorTree/Decorators/BTDecorator_Loop.h` (Public)


#### struct `FBTLoopDecoratorMemory`  
`struct FBTLoopDecoratorMemory`  
_L10-15_
- L12 _public member_ `int32 SearchId;`
- L13 _public member_ `uint8 RemainingExecutions;`
- L14 _public member_ `double TimeStarted;`

#### class `UBTDecorator_Loop`  
`class UBTDecorator_Loop : public UBTDecorator`  
_L22-51_
- reflection: `UCLASS(HideCategories=(Condition), MinimalAPI)`
- inherits: `UBTDecorator`
- desc: Loop decorator node. A decorator node that bases its condition on whether its loop counter has been exceeded.
- L28 _private member_ `FValueOrBBKey_Int32 NumLoops;` — `UPROPERTY(Category=Decorator, EditAnywhere, meta=(EditCondition="!bInfiniteLoop", ClampMin="1", ClampMax="255"))` — number of executions
- L32 _private member_ `bool bInfiniteLoop;` — `UPROPERTY(Category = Decorator, EditAnywhere)` — infinite loop
- L36 _private member_ `FValueOrBBKey_Float InfiniteLoopTimeoutTime;` — `UPROPERTY(Category = Decorator, EditAnywhere, meta = (EditCondition = "bInfiniteLoop"))` — timeout (when looping infinitely, when we finish a loop we will check whether we have spent this time looping, if we have we will stop looping). A negative value means loop forever.
- L38 _private prototype_ `virtual uint16 GetInstanceMemorySize() const override;`
- L39 _private prototype_ `virtual void InitializeMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryInit::Type InitType) const override;`
- L40 _private prototype_ `virtual void CleanupMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryClear::Type CleanupType) const override;`
- L41 _private prototype_ `virtual void DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const override;`
- L42 _private prototype_ `virtual FString GetStaticDescription() const override;`
- L45 _private prototype_ `virtual FName GetNodeIconName() const override;`
- L50 _protected prototype_ `virtual void OnNodeActivation(FBehaviorTreeSearchData& SearchData) override;`

### `Source/Runtime/AIModule/Classes/BehaviorTree/Decorators/BTDecorator_LoopUntil.h` (Public)


#### struct `FBTLoopUntilDecoratorMemory`  
`struct FBTLoopUntilDecoratorMemory`  
_L11-14_
- L13 _public member_ `int32 SearchId = 0;`

#### class `UBTDecorator_LoopUntil`  
`class UBTDecorator_LoopUntil : public UBTDecorator`  
_L21-45_
- reflection: `UCLASS(HideCategories=(FlowControl, Condition), MinimalAPI)`
- inherits: `UBTDecorator`
- desc: Loop until decorator node. A decorator node that loops execution until the child execution returns the required result
- L26 _public prototype_ `UBTDecorator_LoopUntil(const FObjectInitializer& ObjectInitializer);`
- L29 _private prototype_ `virtual void OnNodeDeactivation(FBehaviorTreeSearchData& SearchData, EBTNodeResult::Type NodeResult) override;`
- L31 _private prototype_ `virtual uint16 GetInstanceMemorySize() const override;`
- L32 _private prototype_ `virtual void InitializeMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryInit::Type InitType) const override;`
- L33 _private prototype_ `virtual void CleanupMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryClear::Type CleanupType) const override;`
- L36 _private prototype_ `virtual FString GetErrorMessage() const;`
- L37 _private prototype_ `virtual FName GetNodeIconName() const override;`
- L38 _private prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L40 _private prototype_ `void SetNodeName();`
- L44 _protected member_ `FValueOrBBKey_Enum RequiredResult = EBTNodeResult::Succeeded;` — `UPROPERTY(EditAnywhere, Category=Decorator)`

### `Source/Runtime/AIModule/Classes/BehaviorTree/Decorators/BTDecorator_ReachedMoveGoal.h` (Public)


#### class `UBTDecorator_ReachedMoveGoal`  
`class UBTDecorator_ReachedMoveGoal : public UBTDecorator`  
_L15-24_
- reflection: `UCLASS(meta = (DeprecatedNode, DeprecationMessage = "Please use IsAtLocation decorator instead."), MinimalAPI)`
- inherits: `UBTDecorator`
- desc: Reached Move Goal decorator node. A decorator node that bases its condition on whether the AI controller's path following component returns that it has reached its goal.
- L19 _private prototype_ `virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;`
- L22 _private prototype_ `virtual FName GetNodeIconName() const override;`

### `Source/Runtime/AIModule/Classes/BehaviorTree/Decorators/BTDecorator_SetTagCooldown.h` (Public)


#### class `UBTDecorator_SetTagCooldown`  
`class UBTDecorator_SetTagCooldown : public UBTDecorator`  
_L17-41_
- reflection: `UCLASS(HideCategories=(Condition), MinimalAPI)`
- inherits: `UBTDecorator`
- desc: Set tag cooldown decorator node. A decorator node that sets a gameplay tag cooldown.
- L23 _private member_ `FGameplayTag CooldownTag;` — `UPROPERTY(Category = Decorator, EditAnywhere)` — Gameplay tag that will be used for the cooldown.
- L27 _private member_ `FValueOrBBKey_Float CooldownDuration;` — `UPROPERTY(Category = Decorator, EditAnywhere)` — Value we will add or set to the Cooldown tag when this task runs.
- L31 _private member_ `FValueOrBBKey_Bool bAddToExistingDuration;` — `UPROPERTY(Category = Decorator, EditAnywhere, DisplayName = AddToExistingDuration)` — True if we are adding to any existing duration, false if we are setting the duration (potentially invalidating an existing end time).
- L33 _private prototype_ `virtual FString GetStaticDescription() const override;`
- L36 _private prototype_ `virtual FName GetNodeIconName() const override;`
- L40 _protected prototype_ `virtual void OnNodeDeactivation(FBehaviorTreeSearchData& SearchData, EBTNodeResult::Type NodeResult) override;`

### `Source/Runtime/AIModule/Classes/BehaviorTree/Decorators/BTDecorator_TagCooldown.h` (Public)


#### struct `FBTTagCooldownDecoratorMemory`  
`struct FBTTagCooldownDecoratorMemory`  
_L12-15_
- L14 _public member_ `uint8 bRequestedRestart : 1;`

#### class `UBTDecorator_TagCooldown`  
`class UBTDecorator_TagCooldown : public UBTDecorator`  
_L22-64_
- reflection: `UCLASS(HideCategories=(Condition), MinimalAPI)`
- inherits: `UBTDecorator`
- desc: Cooldown decorator node. A decorator node that bases its condition on whether a cooldown timer based on a gameplay tag has expired.
- L28 _private member_ `FGameplayTag CooldownTag;` — `UPROPERTY(Category = Decorator, EditAnywhere)` — Gameplay tag that will be used for the cooldown.
- L32 _private member_ `FValueOrBBKey_Float CooldownDuration;` — `UPROPERTY(Category = Decorator, EditAnywhere, meta = (EditCondition = "bActivatesCooldown"))` — Value we will add or set to the Cooldown tag when this node is deactivated.
- L36 _private member_ `FValueOrBBKey_Bool bAddToExistingDuration;` — `UPROPERTY(Category = Decorator, EditAnywhere, DisplayName = AddToExistingDuration, meta = (EditCondition = "bActivatesCooldown"))` — True if we are adding to any existing duration, false if we are setting the duration (potentially invalidating an existing end time).
- L40 _private member_ `FValueOrBBKey_Bool bActivatesCooldown;` — `UPROPERTY(Category = Decorator, EditAnywhere, meta = (DisplayName = "Adds/Sets Cooldown on Deactivation"))` — Whether or not we are adding/setting to the cooldown tag's value when the decorator deactivates.
- L43 _private prototype_ `virtual void PostLoad() override;`
- L46 _private prototype_ `virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;`
- L47 _private prototype_ `virtual void InitializeMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryInit::Type InitType) const override;`
- L48 _private prototype_ `virtual void CleanupMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryClear::Type CleanupType) const override;`
- L49 _private prototype_ `virtual uint16 GetInstanceMemorySize() const override;`
- L50 _private prototype_ `virtual void DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const override;`
- L51 _private prototype_ `virtual FString GetStaticDescription() const override;`
- L54 _private prototype_ `virtual FName GetNodeIconName() const override;`
- L59 _protected prototype_ `virtual void OnNodeDeactivation(FBehaviorTreeSearchData& SearchData, EBTNodeResult::Type NodeResult) override;`
- L60 _protected prototype_ `virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;`
- L63 _private prototype_ `bool HasCooldownFinished(const UBehaviorTreeComponent& OwnerComp) const;`

### `Source/Runtime/AIModule/Classes/BehaviorTree/Decorators/BTDecorator_TimeLimit.h` (Public)


#### class `UBTDecorator_TimeLimit`  
`class UBTDecorator_TimeLimit : public UBTDecorator`  
_L15-38_
- reflection: `UCLASS(HideCategories=(Condition), MinimalAPI)`
- inherits: `UBTDecorator`
- desc: Time Limit decorator node. A decorator node that bases its condition on whether a timer has exceeded a specified value. The timer is reset each time the node becomes relevant.
- L21 _private member_ `FValueOrBBKey_Float TimeLimit;` — `UPROPERTY(Category=Decorator, EditAnywhere)` — max allowed time for execution of underlying node
- L23 _private prototype_ `virtual void DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const override;`
- L24 _private prototype_ `virtual FString GetStaticDescription() const override;`
- L27 _private prototype_ `virtual FName GetNodeIconName() const override;`
- L31 _protected prototype_ `virtual void InitializeMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryInit::Type InitType) const override;`
- L32 _protected prototype_ `virtual void CleanupMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryClear::Type CleanupType) const override;`
- L33 _protected prototype_ `virtual uint16 GetInstanceMemorySize() const override;`
- L34 _protected prototype_ `virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L35 _protected prototype_ `virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L36 _protected prototype_ `virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;`
- L37 _protected prototype_ `virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;`

### `Source/Runtime/AIModule/Classes/BehaviorTree/Services/BTService_BlackboardBase.h` (Public)


#### class `UBTService_BlackboardBase`  
`class UBTService_BlackboardBase : public UBTService`  
_L12-31_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UBTService`
- L17 _private prototype_ `virtual void InitializeFromAsset(UBehaviorTree& Asset) override;` — initialize any asset related data
- L20 _private prototype_ `FName GetSelectedBlackboardKey() const;` — get name of selected blackboard key
- L25 _protected prototype_ `virtual FString GetErrorMessage() const override;`
- L30 _protected member_ `struct FBlackboardKeySelector BlackboardKey;` — `UPROPERTY(EditAnywhere, Category=Blackboard)` — blackboard key selector
- L36 _function_ `inline FName UBTService_BlackboardBase::GetSelectedBlackboardKey() const`

### `Source/Runtime/AIModule/Classes/BehaviorTree/Services/BTService_BlueprintBase.h` (Public)


#### class `UBTService_BlueprintBase`  
`class UBTService_BlueprintBase : public UBTService`  
_L24-138_
- reflection: `UCLASS(Abstract, Blueprintable, MinimalAPI)`
- inherits: `UBTService`
- L28 _private prototype_ `virtual void DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const override;`
- L29 _private prototype_ `virtual void OnInstanceDestroyed(UBehaviorTreeComponent& OwnerComp) override;`
- L30 _private prototype_ `virtual void InitializeFromAsset(UBehaviorTree& Asset) override;`
- L32 _private prototype_ `virtual void SetOwner(AActor* ActorOwner) override;`
- L35 _private prototype_ `virtual bool UsesBlueprint() const override;`
- L41 _protected member_ `TObjectPtr<AAIController> AIOwner;` — `UPROPERTY(Transient)` — Cached AIController owner of BehaviorTreeComponent.
- L45 _protected member_ `TObjectPtr<AActor> ActorOwner;` — `UPROPERTY(Transient)` — Cached actor owner of BehaviorTreeComponent.
- L48 _protected prototype_ `virtual FString GetStaticServiceDescription() const override;` — Gets the description for our service
- L51 _protected member_ `TArray<FProperty*> PropertyData;` — properties with runtime values, stored only in class default object
- L55 _protected member_ `FString CustomDescription;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Description)`
- L60 _protected member_ `uint32 bShowPropertyDetails : 1;` — `UPROPERTY(EditInstanceOnly, Category=Description)` — show detailed information about properties
- L64 _protected member_ `uint32 bShowEventDetails : 1;` — `UPROPERTY(EditInstanceOnly, Category = Description)` — show detailed information about implemented events
- L67 _protected member_ `uint32 ReceiveTickImplementations : 2;` — set if ReceiveTick is implemented by blueprint
- L70 _protected member_ `uint32 ReceiveActivationImplementations : 2;` — set if ReceiveActivation is implemented by blueprint
- L73 _protected member_ `uint32 ReceiveDeactivationImplementations : 2;` — set if ReceiveDeactivation is implemented by blueprint
- L76 _protected member_ `uint32 ReceiveSearchStartImplementations : 2;` — set if ReceiveSearchStart is implemented by blueprint
- L78 _protected prototype_ `virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L79 _protected prototype_ `virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L80 _protected prototype_ `virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;`
- L81 _protected prototype_ `virtual void OnSearchStart(FBehaviorTreeSearchData& SearchData) override;`
- L87 _protected prototype_ `void ReceiveTick(AActor* OwnerActor, float DeltaSeconds);` — `UFUNCTION(BlueprintImplementableEvent)` — tick function @Note that if both generic and AI event versions are implemented only the more suitable one will be called, meaning the AI version if called for AI, generic one otherwise
- L93 _protected prototype_ `void ReceiveSearchStart(AActor* OwnerActor);` — `UFUNCTION(BlueprintImplementableEvent)` — task search enters branch of tree @Note that if both generic and AI event versions are implemented only the more suitable one will be called, meaning the AI version if called for AI, generic one otherwise
- L99 _protected prototype_ `void ReceiveActivation(AActor* OwnerActor);` — `UFUNCTION(BlueprintImplementableEvent)` — service became active @Note that if both generic and AI event versions are implemented only the more suitable one will be called, meaning the AI version if called for AI, generic one otherwise
- L105 _protected prototype_ `void ReceiveDeactivation(AActor* OwnerActor);` — `UFUNCTION(BlueprintImplementableEvent)` — service became inactive @Note that if both generic and AI event versions are implemented only the more suitable one will be called, meaning the AI version if called for AI, generic one otherwise
- L112 _protected prototype_ `void ReceiveTickAI(AAIController* OwnerController, APawn* ControlledPawn, float DeltaSeconds);` — `UFUNCTION(BlueprintImplementableEvent, Category = AI)` — Alternative AI version of ReceiveTick function. @see ReceiveTick for more details @Note that if both generic and AI event versions are implemented only the more suitable one will be called, meaning the AI version if called for AI, generic one otherwise
- L119 _protected prototype_ `void ReceiveSearchStartAI(AAIController* OwnerController, APawn* ControlledPawn);` — `UFUNCTION(BlueprintImplementableEvent, Category = AI)` — Alternative AI version of ReceiveSearchStart function. @see ReceiveSearchStart for more details @Note that if both generic and AI event versions are implemented only the more suitable one will be called, meaning the AI version if called for AI, generic one otherwise
- L126 _protected prototype_ `void ReceiveActivationAI(AAIController* OwnerController, APawn* ControlledPawn);` — `UFUNCTION(BlueprintImplementableEvent, Category = AI)` — Alternative AI version of ReceiveActivation function. @see ReceiveActivation for more details @Note that if both generic and AI event versions are implemented only the more suitable one will be called, meaning the AI version if called for AI, generic one otherwise
- L133 _protected prototype_ `void ReceiveDeactivationAI(AAIController* OwnerController, APawn* ControlledPawn);` — `UFUNCTION(BlueprintImplementableEvent, Category = AI)` — Alternative AI version of ReceiveDeactivation function. @see ReceiveDeactivation for more details @Note that if both generic and AI event versions are implemented only the more suitable one will be called, meaning the AI version if called for AI, generic one otherwise
- L137 _protected prototype_ `bool IsServiceActive() const;` — `UFUNCTION(BlueprintCallable, Category="AI|BehaviorTree")` — check if service is currently being active

### `Source/Runtime/AIModule/Classes/BehaviorTree/Services/BTService_DefaultFocus.h` (Public)


#### struct `FBTFocusMemory`  
`struct FBTFocusMemory`  
_L15-27_
- L17 _public member_ `AActor* FocusActorSet;`
- L18 _public member_ `FVector FocusLocationSet;`
- L19 _public member_ `bool bActorSet;`
- L21 _public function_ `void Reset()`

#### class `UBTService_DefaultFocus`  
`class UBTService_DefaultFocus : public UBTService_BlackboardBase`  
_L34-58_
- reflection: `UCLASS(hidecategories=(Service), MinimalAPI)`
- inherits: `UBTService_BlackboardBase`
- desc: Default Focus service node. A service node that automatically sets the AI controller's focus when it becomes active.
- L41 _protected member_ `uint8 FocusPriority;` — `UPROPERTY()` — not exposed to users on purpose. Here to make reusing focus-setting mechanics by derived classes possible
- L43 _protected prototype_ `UBTService_DefaultFocus(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L45 _protected function_ `virtual uint16 GetInstanceMemorySize() const override`
- L46 _protected prototype_ `virtual void InitializeMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryInit::Type InitType) const override;`
- L47 _protected prototype_ `virtual void CleanupMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryClear::Type CleanupType) const override;`
- L48 _protected prototype_ `virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L49 _protected prototype_ `virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L51 _protected prototype_ `virtual FString GetStaticDescription() const override;`
- L53 _protected prototype_ `EBlackboardNotificationResult OnBlackboardKeyValueChange(const UBlackboardComponent& Blackboard, FBlackboard::FKey ChangedKeyID);`
- L56 _protected prototype_ `virtual FName GetNodeIconName() const override;`

### `Source/Runtime/AIModule/Classes/BehaviorTree/Services/BTService_RunEQS.h` (Public)


#### struct `FBTEQSServiceMemory`  
`struct FBTEQSServiceMemory`  
_L14-18_
- L17 _public member_ `int32 RequestID;` — Query request ID

#### class `UBTService_RunEQS`  
`class UBTService_RunEQS : public UBTService_BlackboardBase`  
_L21-53_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBTService_BlackboardBase`
- L27 _protected member_ `FEQSParametrizedQueryExecutionRequest EQSRequest;` — `UPROPERTY(Category = EQS, EditAnywhere)`
- L30 _protected member_ `bool bUpdateBBOnFail = false;` — `UPROPERTY(Category = EQS, EditAnywhere)`
- L32 _protected member_ `FQueryFinishedSignature QueryFinishedDelegate;`
- L35 _public prototype_ `UBTService_RunEQS(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L37 _public prototype_ `virtual void InitializeFromAsset(UBehaviorTree& Asset) override;`
- L38 _public prototype_ `virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;`
- L39 _public prototype_ `virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L40 _public prototype_ `virtual void InitializeMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryInit::Type InitType) const override;`
- L41 _public prototype_ `virtual void CleanupMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryClear::Type CleanupType) const override;`
- L42 _public function_ `virtual uint16 GetInstanceMemorySize() const override`
- L44 _public prototype_ `virtual FString GetStaticDescription() const override;`
- L48 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;` — prepare query params
- L52 _protected prototype_ `void OnQueryFinished(TSharedPtr<FEnvQueryResult> Result);`

### `Source/Runtime/AIModule/Classes/BehaviorTree/Tasks/BTTask_BlackboardBase.h` (Public)


#### class `UBTTask_BlackboardBase`  
`class UBTTask_BlackboardBase : public UBTTaskNode`  
_L13-32_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UBTTaskNode`
- L18 _private prototype_ `virtual void InitializeFromAsset(UBehaviorTree& Asset) override;` — initialize any asset related data
- L21 _private prototype_ `FName GetSelectedBlackboardKey() const;` — get name of selected blackboard key
- L26 _protected prototype_ `virtual FString GetErrorMessage() const override;`
- L31 _protected member_ `struct FBlackboardKeySelector BlackboardKey;` — `UPROPERTY(EditAnywhere, Category=Blackboard)` — blackboard key selector
- L37 _function_ `inline FName UBTTask_BlackboardBase::GetSelectedBlackboardKey() const`

### `Source/Runtime/AIModule/Classes/BehaviorTree/Tasks/BTTask_BlueprintBase.h` (Public)


#### class `UBTTask_BlueprintBase`  
`class UBTTask_BlueprintBase : public UBTTaskNode`  
_L24-153_
- reflection: `UCLASS(Abstract, Blueprintable, MinimalAPI)`
- inherits: `UBTTaskNode`
- L28 _private prototype_ `virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L29 _private prototype_ `virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L31 _private prototype_ `virtual FString GetStaticDescription() const override;`
- L32 _private prototype_ `virtual void DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const override;`
- L33 _private prototype_ `virtual void OnInstanceDestroyed(UBehaviorTreeComponent& OwnerComp) override;`
- L34 _private prototype_ `virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;`
- L35 _private prototype_ `virtual void InitializeFromAsset(UBehaviorTree& Asset) override;`
- L37 _private prototype_ `virtual void SetOwner(AActor* ActorOwner) override;`
- L40 _private prototype_ `virtual bool UsesBlueprint() const override;`
- L46 _protected member_ `TObjectPtr<AAIController> AIOwner;` — `UPROPERTY(Transient)` — Cached AIController owner of BehaviorTreeComponent.
- L50 _protected member_ `TObjectPtr<AActor> ActorOwner;` — `UPROPERTY(Transient)` — Cached actor owner of BehaviorTreeComponent.
- L55 _protected member_ `FIntervalCountdown TickInterval;` — `UPROPERTY(EditAnywhere, Category = Task)` — If any of the Tick functions is implemented, how often should they be ticked. Values < 0 mean 'every tick'.
- L58 _protected member_ `mutable TEnumAsByte<EBTNodeResult::Type> CurrentCallResult;` — temporary variable for ReceiveExecute(Abort)-FinishExecute(Abort) chain
- L61 _protected member_ `TArray<FProperty*> PropertyData;` — properties that should be copied
- L65 _protected member_ `FString CustomDescription;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Description)`
- L70 _protected member_ `uint32 bShowPropertyDetails : 1;` — `UPROPERTY(EditInstanceOnly, Category=Description)` — show detailed information about properties
- L73 _protected member_ `uint32 ReceiveTickImplementations : 2;` — set if ReceiveTick is implemented by blueprint
- L76 _protected member_ `uint32 ReceiveExecuteImplementations : 2;` — set if ReceiveExecute is implemented by blueprint
- L79 _protected member_ `uint32 ReceiveAbortImplementations : 2;` — set if ReceiveAbort is implemented by blueprint
- L82 _protected member_ `uint32 bIsAborting : 1;` — set when task enters Aborting state
- L86 _protected member_ `mutable uint32 bStoreFinishResult : 1;` — if set, execution is inside blueprint's ReceiveExecute(Abort) event FinishExecute(Abort) function should store their result in CurrentCallResult variable
- L92 _protected prototype_ `void ReceiveExecute(AActor* OwnerActor);` — `UFUNCTION(BlueprintImplementableEvent)` — entry point, task will stay active until FinishExecute is called. @Note that if both generic and AI event versions are implemented only the more suitable one will be called, meaning the AI version if called for AI, generic one otherwise
- L98 _protected prototype_ `void ReceiveAbort(AActor* OwnerActor);` — `UFUNCTION(BlueprintImplementableEvent)` — if blueprint graph contains this event, task will stay active until FinishAbort is called @Note that if both generic and AI event versions are implemented only the more suitable one will be called, meaning the AI version if called for AI, generic one otherwise
- L104 _protected prototype_ `void ReceiveTick(AActor* OwnerActor, float DeltaSeconds);` — `UFUNCTION(BlueprintImplementableEvent)` — tick function @Note that if both generic and AI event versions are implemented only the more suitable one will be called, meaning the AI version if called for AI, generic one otherwise
- L111 _protected prototype_ `void ReceiveExecuteAI(AAIController* OwnerController, APawn* ControlledPawn);` — `UFUNCTION(BlueprintImplementableEvent, Category = AI)` — Alternative AI version of ReceiveExecute @see ReceiveExecute for more details @Note that if both generic and AI event versions are implemented only the more suitable one will be called, meaning the AI version if called for AI, generic one otherwise
- L118 _protected prototype_ `void ReceiveAbortAI(AAIController* OwnerController, APawn* ControlledPawn);` — `UFUNCTION(BlueprintImplementableEvent, Category = AI)` — Alternative AI version of ReceiveAbort @see ReceiveAbort for more details @Note that if both generic and AI event versions are implemented only the more suitable one will be called, meaning the AI version if called for AI, generic one otherwise
- L125 _protected prototype_ `void ReceiveTickAI(AAIController* OwnerController, APawn* ControlledPawn, float DeltaSeconds);` — `UFUNCTION(BlueprintImplementableEvent, Category = AI)` — Alternative AI version of tick function. @see ReceiveTick for more details @Note that if both generic and AI event versions are implemented only the more suitable one will be called, meaning the AI version if called for AI, generic one otherwise
- L129 _protected prototype_ `void FinishExecute(bool bSuccess);` — `UFUNCTION(BlueprintCallable, Category="AI|BehaviorTree")` — finishes task execution with Success or Fail result
- L133 _protected prototype_ `void FinishAbort();` — `UFUNCTION(BlueprintCallable, Category="AI|BehaviorTree")` — aborts task execution
- L137 _protected prototype_ `void SetFinishOnMessage(FName MessageName);` — `UFUNCTION(BlueprintCallable, Category="AI|BehaviorTree")` — task execution will be finished (with result 'Success') after receiving specified message
- L141 _protected prototype_ `void SetFinishOnMessageWithId(FName MessageName, int32 RequestID = -1);` — `UFUNCTION(BlueprintCallable, Category="AI|BehaviorTree")` — task execution will be finished (with result 'Success') after receiving specified message with indicated ID
- L145 _protected prototype_ `bool IsTaskExecuting() const;` — `UFUNCTION(BlueprintCallable, Category="AI|BehaviorTree")` — check if task is currently being executed
- L149 _protected prototype_ `bool IsTaskAborting() const;` — `UFUNCTION(BlueprintCallable, Category = "AI|BehaviorTree")` — check if task is currently being aborted
- L152 _protected prototype_ `virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;` — ticks this task

### `Source/Runtime/AIModule/Classes/BehaviorTree/Tasks/BTTask_FinishWithResult.h` (Public)


#### class `UBTTask_FinishWithResult`  
`class UBTTask_FinishWithResult : public UBTTaskNode`  
_L12-25_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBTTaskNode`
- desc: Instantly finishes with given result
- L17 _public prototype_ `UBTTask_FinishWithResult(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L19 _public prototype_ `virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L20 _public prototype_ `virtual FString GetStaticDescription() const override;`
- L24 _protected member_ `FValueOrBBKey_Enum Result = EBTNodeResult::Type::Succeeded;` — `UPROPERTY(Category = Result, EditAnywhere)`

### `Source/Runtime/AIModule/Classes/BehaviorTree/Tasks/BTTask_GameplayTaskBase.h` (Public)


#### struct `FBTGameplayTaskMemory`  
`struct FBTGameplayTaskMemory`  
_L11-15_
- L13 _public member_ `TWeakObjectPtr<UAITask> Task;`
- L14 _public member_ `uint8 bObserverCanFinishTask : 1;`

#### class `UBTTask_GameplayTaskBase`  
`class UBTTask_GameplayTaskBase : public UBTTaskNode`  
_L27-49_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UBTTaskNode`
- desc: Base class for managing gameplay tasks Since AITask doesn't have any kind of success/failed results, default implemenation will only return EBTNode::Succeeded In your ExecuteTask: - use NewBTAITask() helper to create task - initialize task with values if needed - use StartGameplayTask() helper to execute and get node result
- L31 _private prototype_ `virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L32 _private prototype_ `virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;`
- L33 _private prototype_ `virtual void OnGameplayTaskDeactivated(UGameplayTask& Task) override;`
- L34 _private prototype_ `virtual uint16 GetInstanceMemorySize() const override;`
- L35 _private prototype_ `virtual void InitializeMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryInit::Type InitType) const override;`
- L36 _private prototype_ `virtual void CleanupMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryClear::Type CleanupType) const override;`
- L42 _protected member_ `FValueOrBBKey_Bool bWaitForGameplayTask;` — `UPROPERTY(EditAnywhere, Category = Task, AdvancedDisplay, DisplayName = WaitForGameplayTask)` — if set, behavior tree task will wait until gameplay tasks finishes
- L45 _protected prototype_ `EBTNodeResult::Type StartGameplayTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, UAITask& Task);` — start task and initialize FBTGameplayTaskMemory memory block
- L48 _protected prototype_ `virtual EBTNodeResult::Type DetermineGameplayTaskResult(UAITask& Task) const;` — get finish result from task

### `Source/Runtime/AIModule/Classes/BehaviorTree/Tasks/BTTask_MakeNoise.h` (Public)


#### class `UBTTask_MakeNoise`  
`class UBTTask_MakeNoise : public UBTTaskNode`  
_L16-29_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBTTaskNode`
- desc: Make Noise task node. A task node that calls MakeNoise() on this Pawn when executed.
- L22 _private member_ `FValueOrBBKey_Float Loudnes;` — `UPROPERTY(Category=Node, EditAnywhere, meta=(ClampMin = "0", ClampMax = "1", UIMin = "0", UIMax = "1"), DisplayName = Loudness)` — Loudness of generated noise
- L24 _private prototype_ `virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L27 _private prototype_ `virtual FName GetNodeIconName() const override;`

### `Source/Runtime/AIModule/Classes/BehaviorTree/Tasks/BTTask_MoveDirectlyToward.h` (Public)


#### class `UBTTask_MoveDirectlyToward`  
`class UBTTask_MoveDirectlyToward : public UBTTask_MoveTo`  
_L17-24_
- reflection: `UCLASS(config=Game, MinimalAPI)`
- inherits: `UBTTask_MoveTo`
- desc: Move Directly Toward task node. Moves the AI pawn toward the specified Actor or Location (Vector) blackboard entry in a straight line, without regard to any navigation system. If you need the AI to navigate, use the "Move To" node instead.
- L22 _private prototype_ `virtual FName GetNodeIconName() const override;`

### `Source/Runtime/AIModule/Classes/BehaviorTree/Tasks/BTTask_MoveTo.h` (Public)


#### struct `FBTMoveToTaskMemory`  
`struct FBTMoveToTaskMemory`  
_L18-29_
- L21 _public member_ `FAIRequestID MoveRequestID;` — Move request ID
- L23 _public member_ `FDelegateHandle BBObserverDelegateHandle;`
- L24 _public member_ `FVector PreviousGoalLocation;`
- L26 _public member_ `TWeakObjectPtr<UAITask_MoveTo> Task;`
- L28 _public member_ `uint8 bObserverCanFinishTask : 1;`

#### class `UBTTask_MoveTo`  
`class UBTTask_MoveTo : public UBTTask_BlackboardBase`  
_L36-115_
- reflection: `UCLASS(config=Game, MinimalAPI)`
- inherits: `UBTTask_BlackboardBase`
- desc: Move To task node. Moves the AI pawn toward the specified Actor or Location blackboard entry using the navigation system.
- L42 _private member_ `FValueOrBBKey_Float AcceptableRadius;` — `UPROPERTY(config, Category = Node, EditAnywhere, meta=(ClampMin = "0.0", UIMin="0.0"))` — fixed distance added to threshold between AI and goal location in destination reach test
- L46 _private member_ `FValueOrBBKey_Class FilterClass = TSubclassOf<UNavigationQueryFilter>();` — `UPROPERTY(Category = Node, EditAnywhere)` — "None" will result in default filter being used
- L52 _private member_ `FValueOrBBKey_Float ObservedBlackboardValueTolerance;` — `UPROPERTY(Category = Blackboard, EditAnywhere, meta = (EditCondition = "bObserveBlackboardValue", ClampMin = "1", UIMin = "1"))` — if task is expected to react to changes to location represented by BB key this property can be used to tweak sensitivity of the mechanism. Value is recommended to be less than AcceptableRadius
- L55 _private member_ `FValueOrBBKey_Bool bAllowStrafe;` — `UPROPERTY(Category = Node, EditAnywhere, DisplayName = AllowStrafe)`
- L59 _private member_ `FValueOrBBKey_Bool bAllowPartialPath;` — `UPROPERTY(Category = Node, EditAnywhere, AdvancedDisplay, DisplayName = AllowPartialPath)` — if set, use incomplete path when goal can't be reached
- L63 _private member_ `FValueOrBBKey_Bool bTrackMovingGoal;` — `UPROPERTY(Category = Node, EditAnywhere, AdvancedDisplay, DisplayName = TrackMovingGoal)` — if set, path to goal actor will update itself when actor moves
- L67 _private member_ `FValueOrBBKey_Bool bRequireNavigableEndLocation;` — `UPROPERTY(Category = Node, EditAnywhere, AdvancedDisplay, DisplayName = RequireNavigableEndLocation)` — if set, the goal location will need to be navigable
- L71 _private member_ `FValueOrBBKey_Bool bProjectGoalLocation;` — `UPROPERTY(Category = Node, EditAnywhere, AdvancedDisplay, DisplayName = ProjectGoalLocation)` — if set, goal location will be projected on navigation data (navmesh) before using
- L75 _private member_ `FValueOrBBKey_Bool bReachTestIncludesAgentRadius;` — `UPROPERTY(Category = Node, EditAnywhere, DisplayName = ReachTestIncludesAgentRadius)` — if set, radius of AI's capsule will be added to threshold between AI and goal location in destination reach test
- L79 _private member_ `FValueOrBBKey_Bool bReachTestIncludesGoalRadius;` — `UPROPERTY(Category = Node, EditAnywhere, DisplayName = ReachTestIncludesGoalRadius)` — if set, radius of goal's capsule will be added to threshold between AI and goal location in destination reach test
- L83 _private member_ `FValueOrBBKey_Bool bStartFromPreviousPath;` — `UPROPERTY(Category = Node, EditAnywhere, DisplayName = StartFromPreviousPath)` — if set, the path request will start from the end of the previous path (if any), and the generated path will be merged with the remaining points of the previous path
- L86 _private member_ `uint32 bUsePathfinding : 1;` — if set, move will use pathfinding. Not exposed on purpose, please use BTTask_MoveDirectlyToward
- L89 _private member_ `uint32 bObserveBlackboardValue : 1;` — `UPROPERTY()`
- L91 _private prototype_ `virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L92 _private prototype_ `virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L93 _private prototype_ `virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;`
- L94 _private prototype_ `virtual uint16 GetInstanceMemorySize() const override;`
- L95 _private prototype_ `virtual void InitializeMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryInit::Type InitType) const override;`
- L96 _private prototype_ `virtual void CleanupMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryClear::Type CleanupType) const override;`
- L98 _private prototype_ `virtual void OnGameplayTaskDeactivated(UGameplayTask& Task) override;`
- L99 _private prototype_ `virtual void OnMessage(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, FName Message, int32 RequestID, bool bSuccess) override;`
- L100 _private prototype_ `EBlackboardNotificationResult OnBlackboardValueChange(const UBlackboardComponent& Blackboard, FBlackboard::FKey ChangedKeyID);`
- L102 _private prototype_ `virtual void DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const override;`
- L103 _private prototype_ `virtual FString GetStaticDescription() const override;`
- L106 _private prototype_ `virtual FName GetNodeIconName() const override;`
- L111 _protected prototype_ `virtual EBTNodeResult::Type PerformMoveTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);`
- L114 _protected prototype_ `virtual UAITask_MoveTo* PrepareMoveTask(UBehaviorTreeComponent& OwnerComp, UAITask_MoveTo* ExistingTask, FAIMoveRequest& MoveRequest);` — prepares move task for activation

### `Source/Runtime/AIModule/Classes/BehaviorTree/Tasks/BTTask_PlayAnimation.h` (Public)


#### class `UBTTask_PlayAnimation`  
`class UBTTask_PlayAnimation : public UBTTaskNode`  
_L21-59_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBTTaskNode`
- desc: Play indicated AnimationAsset on Pawn controlled by BT Note that this node is generic and is handing multiple special cases, If you want a more efficient solution you'll need to implement it yourself (or wait for our BTTask_PlayCharacterAnimation)
- L27 _private member_ `FValueOrBBKey_Object AnimationToPlay = TObjectPtr<UAnimationAsset>();` — `UPROPERTY(Category = Node, EditAnywhere)` — Animation asset to play. Note that it needs to match the skeleton of pawn this BT is controlling
- L30 _private member_ `FValueOrBBKey_Bool bLooping = false;` — `UPROPERTY(Category = Node, EditAnywhere, DisplayName = Looping)`
- L34 _private member_ `FValueOrBBKey_Bool bNonBlocking = false;` — `UPROPERTY(Category = Node, EditAnywhere, DisplayName = NonBlocking)` — if true the task will just trigger the animation and instantly finish. Fire and Forget.
- L37 _private member_ `TObjectPtr<UBehaviorTreeComponent> MyOwnerComp;` — `UPROPERTY()`
- L40 _private member_ `TObjectPtr<USkeletalMeshComponent> CachedSkelMesh;` — `UPROPERTY()`
- L42 _private member_ `EAnimationMode::Type PreviousAnimationMode;`
- L44 _private member_ `FTimerDelegate TimerDelegate;`
- L45 _private member_ `FTimerHandle TimerHandle;`
- L47 _private prototype_ `virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L48 _private prototype_ `virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L49 _private prototype_ `virtual FString GetStaticDescription() const override;`
- L51 _private prototype_ `void OnAnimationTimerDone();`
- L54 _private prototype_ `virtual FName GetNodeIconName() const override;`
- L58 _protected prototype_ `void CleanUp(UBehaviorTreeComponent& OwnerComp);`

### `Source/Runtime/AIModule/Classes/BehaviorTree/Tasks/BTTask_PlaySound.h` (Public)


#### class `UBTTask_PlaySound`  
`class UBTTask_PlaySound : public UBTTaskNode`  
_L19-33_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBTTaskNode`
- desc: Play Sound task node. Plays the specified sound when executed.
- L25 _private member_ `FValueOrBBKey_Object SoundToPlay = TObjectPtr<USoundCue>();` — `UPROPERTY(Category=Node, EditAnywhere)` — CUE to play
- L27 _private prototype_ `virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L28 _private prototype_ `virtual FString GetStaticDescription() const override;`
- L31 _private prototype_ `virtual FName GetNodeIconName() const override;`

### `Source/Runtime/AIModule/Classes/BehaviorTree/Tasks/BTTask_RotateToFaceBBEntry.h` (Public)


#### class `UBTTask_RotateToFaceBBEntry`  
`class UBTTask_RotateToFaceBBEntry : public UBTTask_BlackboardBase`  
_L18-43_
- reflection: `UCLASS(config = Game, MinimalAPI)`
- inherits: `UBTTask_BlackboardBase`
- L25 _protected member_ `FValueOrBBKey_Float Precision;` — `UPROPERTY(config, Category = Node, EditAnywhere, meta = (ClampMin = "0.0"))` — Success condition precision in degrees
- L29 _public prototype_ `virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L30 _public prototype_ `virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;`
- L31 _public prototype_ `virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L32 _public prototype_ `virtual void DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const override;`
- L33 _public prototype_ `virtual FString GetStaticDescription() const override;`
- L35 _public function_ `virtual uint16 GetInstanceMemorySize() const override`
- L36 _public prototype_ `virtual void InitializeMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryInit::Type InitType) const override;`
- L37 _public prototype_ `virtual void CleanupMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryClear::Type CleanupType) const override;`
- L41 _protected prototype_ `float GetPrecisionDot(const UBehaviorTreeComponent& OwnerComp) const;`
- L42 _protected prototype_ `void CleanUp(AAIController& AIController, uint8* NodeMemory);`

### `Source/Runtime/AIModule/Classes/BehaviorTree/Tasks/BTTask_RunBehavior.h` (Public)


#### class `UBTTask_RunBehavior`  
`class UBTTask_RunBehavior : public UBTTaskNode`  
_L23-49_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBTTaskNode`
- L27 _private prototype_ `virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L28 _private prototype_ `virtual FString GetStaticDescription() const override;`
- L31 _private prototype_ `virtual FName GetNodeIconName() const override;`
- L32 _private prototype_ `virtual const UObject* GetAssociatedAsset(TOptional<FBehaviorTreeNodeDebugContext> DebugContext) const override;`
- L36 _private prototype_ `int32 GetInjectedNodesCount() const;` — @returns number of injected nodes
- L39 _private prototype_ `UBehaviorTree* GetSubtreeAsset() const;` — @returns subtree asset
- L45 _protected member_ `TObjectPtr<UBehaviorTree> BehaviorAsset;` — `UPROPERTY(Category = Node, EditAnywhere, BlueprintReadOnly)` — behavior to run
- L48 _protected prototype_ `virtual void OnSubtreeDeactivated(UBehaviorTreeComponent& OwnerComp, EBTNodeResult::Type NodeResult);` — called when subtree is removed from active stack
- L54 _function_ `inline UBehaviorTree* UBTTask_RunBehavior::GetSubtreeAsset() const`
- L59 _function_ `inline int32 UBTTask_RunBehavior::GetInjectedNodesCount() const`

### `Source/Runtime/AIModule/Classes/BehaviorTree/Tasks/BTTask_RunBehaviorDynamic.h` (Public)


#### class `UBTTask_RunBehaviorDynamic`  
`class UBTTask_RunBehaviorDynamic : public UBTTaskNode`  
_L21-62_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBTTaskNode`
- L25 _private prototype_ `virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L26 _private prototype_ `virtual void OnInstanceCreated(UBehaviorTreeComponent& OwnerComp) override;`
- L27 _private prototype_ `virtual FString GetStaticDescription() const override;`
- L28 _private prototype_ `virtual void DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const override;`
- L31 _private prototype_ `virtual FName GetNodeIconName() const override;`
- L32 _private prototype_ `virtual const UObject* GetAssociatedAsset(TOptional<FBehaviorTreeNodeDebugContext> DebugContext) const override;`
- L35 _private prototype_ `UBehaviorTree* GetBehaviorAssetFromRuntimeValue(const FString& RuntimeValue) const;` — `UE_DEPRECATED(5.6, "GetBehaviorAssetFromRuntimeValue has been replaced with the more generic GetAssociatedAsset.")`
- L39 _private prototype_ `bool HasMatchingTag(const FGameplayTag& Tag) const;`
- L40 _private prototype_ `const FGameplayTag& GetInjectionTag() const;`
- L41 _private prototype_ `bool SetBehaviorAsset(UBehaviorTree* NewBehaviorAsset);`
- L44 _private prototype_ `UBehaviorTree* GetDefaultBehaviorAsset() const;` — @returns default subtree asset
- L50 _protected member_ `FGameplayTag InjectionTag;` — `UPROPERTY(Category=Node, EditAnywhere)` — Gameplay tag that will identify this task for subtree injection
- L54 _protected member_ `TObjectPtr<UBehaviorTree> DefaultBehaviorAsset;` — `UPROPERTY(Category=Node, EditAnywhere, BlueprintReadOnly)` — default behavior to run
- L58 _protected member_ `TObjectPtr<UBehaviorTree> BehaviorAsset;` — `UPROPERTY(BlueprintReadOnly, Category = Node)` — current subtree
- L61 _protected prototype_ `virtual void OnSubtreeDeactivated(UBehaviorTreeComponent& OwnerComp, EBTNodeResult::Type NodeResult);` — called when subtree is removed from active stack
- L67 _function_ `inline bool UBTTask_RunBehaviorDynamic::HasMatchingTag(const FGameplayTag& Tag) const`
- L72 _function_ `inline UBehaviorTree* UBTTask_RunBehaviorDynamic::GetDefaultBehaviorAsset() const`
- L77 _function_ `inline const FGameplayTag& UBTTask_RunBehaviorDynamic::GetInjectionTag() const`

### `Source/Runtime/AIModule/Classes/BehaviorTree/Tasks/BTTask_RunEQSQuery.h` (Public)


#### struct `FBTEnvQueryTaskMemory`  
`struct FBTEnvQueryTaskMemory`  
_L14-18_
- L17 _public member_ `int32 RequestID;` — Query request ID

#### class `UBTTask_RunEQSQuery`  
`class UBTTask_RunEQSQuery : public UBTTask_BlackboardBase`  
_L25-63_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBTTask_BlackboardBase`
- desc: Run Environment Query System Query task node. Runs the specified environment query when executed.
- L30 _private member_ `bool bUseBBKey;` — `UPROPERTY(EditAnywhere, Category=Node, meta=(InlineEditConditionToggle))`
- L33 _private member_ `FEQSParametrizedQueryExecutionRequest EQSRequest;` — `UPROPERTY(Category = EQS, EditAnywhere)`
- L36 _private member_ `bool bUpdateBBOnFail = false;` — `UPROPERTY(Category = EQS, EditAnywhere)`
- L38 _private member_ `FQueryFinishedSignature QueryFinishedDelegate;`
- L40 _private prototype_ `virtual void InitializeFromAsset(UBehaviorTree& Asset) override;`
- L41 _private prototype_ `virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L42 _private prototype_ `virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L44 _private prototype_ `virtual void DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const override;`
- L45 _private prototype_ `virtual FString GetStaticDescription() const override;`
- L46 _private prototype_ `virtual uint16 GetInstanceMemorySize() const override;`
- L47 _private prototype_ `virtual void InitializeMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryInit::Type InitType) const override;`
- L48 _private prototype_ `virtual void CleanupMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryClear::Type CleanupType) const override;`
- L51 _private prototype_ `void OnQueryFinished(TSharedPtr<FEnvQueryResult> Result);` — finish task
- L55 _private prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;` — prepare query params
- L56 _private prototype_ `virtual FName GetNodeIconName() const override;`
- L62 _protected prototype_ `void CollectKeyFilters();` — gather all filters from existing EnvQueryItemTypes

### `Source/Runtime/AIModule/Classes/BehaviorTree/Tasks/BTTask_SetKeyValue.h` (Public)


#### class `UBTTask_SetKeyValueBool`  
`class UBTTask_SetKeyValueBool : public UBTTask_BlackboardBase`  
_L10-23_
- reflection: `UCLASS(DisplayName = "Set Bool Key")`
- inherits: `UBTTask_BlackboardBase`
- L15 _public prototype_ `UBTTask_SetKeyValueBool(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L17 _public prototype_ `virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L18 _public prototype_ `virtual FString GetStaticDescription() const override;`
- L22 _private member_ `FValueOrBBKey_Bool Value;` — `UPROPERTY(EditAnywhere, Category = Blackboard)`

#### class `UBTTask_SetKeyValueClass`  
`class UBTTask_SetKeyValueClass : public UBTTask_BlackboardBase`  
_L26-46_
- reflection: `UCLASS(DisplayName = "Set Class Key")`
- inherits: `UBTTask_BlackboardBase`
- L31 _public prototype_ `UBTTask_SetKeyValueClass(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L33 _public prototype_ `virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L34 _public prototype_ `virtual FString GetStaticDescription() const override;`
- L36 _public prototype_ `virtual void PostLoad() override;`
- L38 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L42 _private member_ `TSubclassOf<UObject> BaseClass = UObject::StaticClass();` — `UPROPERTY(EditAnywhere, Category = Blackboard, meta = (AllowAbstract = "true", NoClear, ForceRebuildProperty="Value"))`
- L45 _private member_ `FValueOrBBKey_Class Value;` — `UPROPERTY(EditAnywhere, Category = Blackboard)`

#### class `UBTTask_SetKeyValueEnum`  
`class UBTTask_SetKeyValueEnum : public UBTTask_BlackboardBase`  
_L49-69_
- reflection: `UCLASS(DisplayName = "Set Enum Key")`
- inherits: `UBTTask_BlackboardBase`
- L54 _public prototype_ `UBTTask_SetKeyValueEnum(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L56 _public prototype_ `virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L57 _public prototype_ `virtual FString GetStaticDescription() const override;`
- L59 _public prototype_ `virtual void PostLoad() override;`
- L61 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L65 _private member_ `TObjectPtr<UEnum> EnumType;` — `UPROPERTY(EditAnywhere, Category = Blackboard, meta = (AllowAbstract = "true", NoClear, ForceRebuildProperty = "Value"))`
- L68 _private member_ `FValueOrBBKey_Enum Value;` — `UPROPERTY(EditAnywhere, Category = Blackboard)`

#### class `UBTTask_SetKeyValueInt32`  
`class UBTTask_SetKeyValueInt32 : public UBTTask_BlackboardBase`  
_L72-85_
- reflection: `UCLASS(DisplayName = "Set Int Key")`
- inherits: `UBTTask_BlackboardBase`
- L77 _public prototype_ `UBTTask_SetKeyValueInt32(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L79 _public prototype_ `virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L80 _public prototype_ `virtual FString GetStaticDescription() const override;`
- L84 _private member_ `FValueOrBBKey_Int32 Value;` — `UPROPERTY(EditAnywhere, Category = Blackboard)`

#### class `UBTTask_SetKeyValueFloat`  
`class UBTTask_SetKeyValueFloat : public UBTTask_BlackboardBase`  
_L88-101_
- reflection: `UCLASS(DisplayName = "Set Float Key")`
- inherits: `UBTTask_BlackboardBase`
- L93 _public prototype_ `UBTTask_SetKeyValueFloat(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L95 _public prototype_ `virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L96 _public prototype_ `virtual FString GetStaticDescription() const override;`
- L100 _private member_ `FValueOrBBKey_Float Value;` — `UPROPERTY(EditAnywhere, Category = Blackboard)`

#### class `UBTTask_SetKeyValueName`  
`class UBTTask_SetKeyValueName : public UBTTask_BlackboardBase`  
_L104-117_
- reflection: `UCLASS(DisplayName = "Set Name Key")`
- inherits: `UBTTask_BlackboardBase`
- L109 _public prototype_ `UBTTask_SetKeyValueName(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L111 _public prototype_ `virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L112 _public prototype_ `virtual FString GetStaticDescription() const override;`
- L116 _private member_ `FValueOrBBKey_Name Value;` — `UPROPERTY(EditAnywhere, Category = Blackboard)`

#### class `UBTTask_SetKeyValueString`  
`class UBTTask_SetKeyValueString : public UBTTask_BlackboardBase`  
_L120-133_
- reflection: `UCLASS(DisplayName = "Set String Key")`
- inherits: `UBTTask_BlackboardBase`
- L125 _public prototype_ `UBTTask_SetKeyValueString(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L127 _public prototype_ `virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L128 _public prototype_ `virtual FString GetStaticDescription() const override;`
- L132 _private member_ `FValueOrBBKey_String Value;` — `UPROPERTY(EditAnywhere, Category = Blackboard)`

#### class `UBTTask_SetKeyValueObject`  
`class UBTTask_SetKeyValueObject : public UBTTask_BlackboardBase`  
_L136-156_
- reflection: `UCLASS(DisplayName = "Set Object Key")`
- inherits: `UBTTask_BlackboardBase`
- L141 _public prototype_ `UBTTask_SetKeyValueObject(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L143 _public prototype_ `virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L144 _public prototype_ `virtual FString GetStaticDescription() const override;`
- L146 _public prototype_ `virtual void PostLoad() override;`
- L148 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L152 _private member_ `TSubclassOf<UObject> BaseClass = UObject::StaticClass();` — `UPROPERTY(EditAnywhere, Category = Blackboard, meta = (AllowAbstract = "true", NoClear, ForceRebuildProperty = "Value"))`
- L155 _private member_ `FValueOrBBKey_Object Value;` — `UPROPERTY(EditAnywhere, Category = Blackboard)`

#### class `UBTTask_SetKeyValueRotator`  
`class UBTTask_SetKeyValueRotator : public UBTTask_BlackboardBase`  
_L159-172_
- reflection: `UCLASS(DisplayName = "Set Rotator Key")`
- inherits: `UBTTask_BlackboardBase`
- L164 _public prototype_ `UBTTask_SetKeyValueRotator(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L166 _public prototype_ `virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L167 _public prototype_ `virtual FString GetStaticDescription() const override;`
- L171 _private member_ `FValueOrBBKey_Rotator Value;` — `UPROPERTY(EditAnywhere, Category = Blackboard)`

#### class `UBTTask_SetKeyValueStruct`  
`class UBTTask_SetKeyValueStruct : public UBTTask_BlackboardBase`  
_L175-195_
- reflection: `UCLASS(DisplayName = "Set Struct Key")`
- inherits: `UBTTask_BlackboardBase`
- L180 _public prototype_ `UBTTask_SetKeyValueStruct(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L182 _public prototype_ `virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L183 _public prototype_ `virtual FString GetStaticDescription() const override;`
- L185 _public prototype_ `virtual void PostLoad() override;`
- L187 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L191 _private member_ `TObjectPtr<UScriptStruct> StructType;` — `UPROPERTY(EditAnywhere, Category = Blackboard, meta = (ForceRebuildProperty = "Value"))`
- L194 _private member_ `FValueOrBBKey_Struct Value;` — `UPROPERTY(EditAnywhere, Category = Blackboard)`

#### class `UBTTask_SetKeyValueVector`  
`class UBTTask_SetKeyValueVector : public UBTTask_BlackboardBase`  
_L198-211_
- reflection: `UCLASS(DisplayName = "Set Vector Key")`
- inherits: `UBTTask_BlackboardBase`
- L203 _public prototype_ `UBTTask_SetKeyValueVector(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L205 _public prototype_ `virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L206 _public prototype_ `virtual FString GetStaticDescription() const override;`
- L210 _private member_ `FValueOrBBKey_Vector Value;` — `UPROPERTY(EditAnywhere, Category = Blackboard)`

### `Source/Runtime/AIModule/Classes/BehaviorTree/Tasks/BTTask_SetTagCooldown.h` (Public)


#### class `UBTTask_SetTagCooldown`  
`class UBTTask_SetTagCooldown : public UBTTaskNode`  
_L16-38_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBTTaskNode`
- desc: Cooldown task node. Sets a cooldown tag value.  Use with cooldown tag decorators to prevent behavior tree execution.
- L22 _private member_ `FGameplayTag CooldownTag;` — `UPROPERTY(Category = Cooldown, EditAnywhere)` — Gameplay tag that will be used for the cooldown.
- L26 _private member_ `FValueOrBBKey_Bool bAddToExistingDuration;` — `UPROPERTY(Category = Cooldown, EditAnywhere, DisplayName = AddToExistingDuration)` — True if we are adding to any existing duration, false if we are setting the duration (potentially invalidating an existing end time).
- L30 _private member_ `FValueOrBBKey_Float CooldownDuration;` — `UPROPERTY(Category = Cooldown, EditAnywhere)` — Value we will add or set to the Cooldown tag when this task runs.
- L32 _private prototype_ `virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L33 _private prototype_ `virtual FString GetStaticDescription() const override;`
- L36 _private prototype_ `virtual FName GetNodeIconName() const override;`

### `Source/Runtime/AIModule/Classes/BehaviorTree/Tasks/BTTask_Wait.h` (Public)


#### struct `FBTWaitTaskMemory`  
`struct FBTWaitTaskMemory`  
_L10-12_

#### class `UBTTask_Wait`  
`class UBTTask_Wait : public UBTTaskNode`  
_L19-42_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBTTaskNode`
- desc: Wait task node. Wait for the specified time when executed.
- L25 _private member_ `FValueOrBBKey_Float WaitTime;` — `UPROPERTY(Category = Wait, EditAnywhere, meta = (ClampMin = "0.0", UIMin = "0.0"))` — wait time in seconds
- L29 _private member_ `FValueOrBBKey_Float RandomDeviation;` — `UPROPERTY(Category = Wait, EditAnywhere, meta = (UIMin = 0, ClampMin = 0))` — allows adding random time to wait time
- L31 _private prototype_ `virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L32 _private prototype_ `virtual void DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const override;`
- L33 _private prototype_ `virtual FString GetStaticDescription() const override;`
- L36 _private prototype_ `virtual FName GetNodeIconName() const override;`
- L41 _protected prototype_ `virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;`

### `Source/Runtime/AIModule/Classes/BehaviorTree/Tasks/BTTask_WaitBlackboardTime.h` (Public)


#### class `UBTTask_WaitBlackboardTime`  
`class UBTTask_WaitBlackboardTime : public UBTTask_Wait`  
_L17-37_
- reflection: `UCLASS(hidecategories=Wait, hidden, MinimalAPI)`
- inherits: `UBTTask_Wait`
- desc: DEPRECATED Replace with UBTTask_Wait that now accepts blackboard keys Wait task node. Wait for the time specified by a Blackboard key when executed.
- L21 _private prototype_ `virtual void InitializeFromAsset(UBehaviorTree& Asset) override;`
- L24 _private prototype_ `FName GetSelectedBlackboardKey() const;` — get name of selected blackboard key
- L30 _protected prototype_ `virtual FString GetErrorMessage() const override;`
- L35 _protected member_ `struct FBlackboardKeySelector BlackboardKey;` — `UPROPERTY(EditAnywhere, Category=Blackboard)` — blackboard key selector
- L42 _function_ `inline FName UBTTask_WaitBlackboardTime::GetSelectedBlackboardKey() const`

### `Source/Runtime/AIModule/Classes/BehaviorTree/ValueOrBBKey.h` (Public)


#### struct `FValueOrBlackboardKeyBase`  
`struct FValueOrBlackboardKeyBase`  
_L82-121_
- reflection: `USTRUCT(BlueprintType)`
- desc: Base struct to simplify edition in the editor, shouldn't be used elsewhere
- L87 _public prototype_ `virtual ~FValueOrBlackboardKeyBase() = default;`
- L90 _public function_ `virtual bool IsCompatibleType(const UBlackboardKeyType* KeyType) const`
- L91 _public prototype_ `void PreSave(const UObject* Outer, const UBlackboardData& Blackboard, FName PropertyName);`
- L94 _public function_ `virtual FString ToString() const`
- L96 _public function_ `const FName& GetKey() const`
- L97 _public function_ `void SetKey(FName NewKey)`
- L99 _public prototype_ `FBlackboard::FKey GetKeyId(const UBehaviorTreeComponent& OwnerComp) const;`
- L103 _protected function_ `template <typename T> FString ToStringInternal(const T& DefaultValue) const`
- L115 _protected prototype_ `FString ToStringKeyName() const;`
- L118 _protected member_ `FName Key;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Value")`
- L120 _protected member_ `mutable FBlackboard::FKey KeyId = FBlackboard::InvalidKey;`

#### struct `FValueOrBBKey_Bool`  
`struct FValueOrBBKey_Bool : public FValueOrBlackboardKeyBase`  
_L124-149_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FValueOrBlackboardKeyBase`
- L128 _public function_ `FValueOrBBKey_Bool(bool Default = false) : DefaultValue(Default)`
- L130 _public prototype_ `bool GetValue(const UBehaviorTreeComponent& BehaviorComp) const;`
- L131 _public prototype_ `bool GetValue(const UBehaviorTreeComponent* BehaviorComp) const;`
- L132 _public prototype_ `bool GetValue(const UBlackboardComponent& Blackboard) const;`
- L133 _public prototype_ `bool GetValue(const UBlackboardComponent* Blackboard) const;`
- L136 _public prototype_ `virtual bool IsCompatibleType(const UBlackboardKeyType* KeyType) const override;`
- L139 _public prototype_ `bool SerializeFromMismatchedTag(const FPropertyTag& Tag, FStructuredArchive::FSlot Slot);`
- L141 _public function_ `FString ToString() const override`
- L144 _public function_ `operator bool() const` — `UE_DEPRECATED_FORGAME(5.5, "Implicit conversion will be removed next version. Call GetValue instead")`
- L148 _protected member_ `bool DefaultValue = false;` — `UPROPERTY(EditAnywhere, Category = "Value")`

#### struct `FValueOrBBKey_Class`  
`struct FValueOrBBKey_Class : public FValueOrBlackboardKeyBase`  
_L152-212_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FValueOrBlackboardKeyBase`
- L158 _public prototype_ `FValueOrBBKey_Class() = default;`
- L161 _public function_ `template <typename T> FValueOrBBKey_Class(TSubclassOf<T> Default) : DefaultValue(Default), BaseClass(T::StaticClass())`
- L165 _public function_ `template <typename T> TSubclassOf<T> GetValue(const UBehaviorTreeComponent& BehaviorComp) const`
- L171 _public function_ `template <typename T> TSubclassOf<T> GetValue(const UBehaviorTreeComponent* BehaviorComp) const`
- L177 _public function_ `template <typename T> TSubclassOf<T> GetValue(const UBlackboardComponent& BlackboardComp) const`
- L183 _public function_ `template <typename T> TSubclassOf<T> GetValue(const UBlackboardComponent* BlackboardComp) const`
- L188 _public prototype_ `UClass* GetValue(const UBehaviorTreeComponent& BehaviorComp) const;`
- L189 _public prototype_ `UClass* GetValue(const UBehaviorTreeComponent* BehaviorComp) const;`
- L190 _public prototype_ `UClass* GetValue(const UBlackboardComponent& Blackboard) const;`
- L191 _public prototype_ `UClass* GetValue(const UBlackboardComponent* Blackboard) const;`
- L193 _public prototype_ `bool SerializeFromMismatchedTag(const FPropertyTag& Tag, FStructuredArchive::FSlot Slot);`
- L196 _public prototype_ `virtual bool IsCompatibleType(const UBlackboardKeyType* KeyType) const override;`
- L199 _public prototype_ `FString ToString() const override;`
- L202 _public function_ `operator UClass*() const` — `UE_DEPRECATED_FORGAME(5.5, "Implicit conversion will be removed next version. Call GetValue instead")`
- L204 _public prototype_ `void SetBaseClass(UClass* NewBaseClass);`
- L208 _protected member_ `TObjectPtr<UClass> DefaultValue = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Value")`
- L211 _protected member_ `TObjectPtr<UClass> BaseClass = UObject::StaticClass();` — `UPROPERTY(EditDefaultsOnly, Category = "Value", meta = (AllowAbstract = "1"))`

#### struct `FValueOrBBKey_Enum`  
`struct FValueOrBBKey_Enum : public FValueOrBlackboardKeyBase`  
_L215-279_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FValueOrBlackboardKeyBase`
- L221 _public prototype_ `FValueOrBBKey_Enum() = default;`
- L224 _public function_ `template <typename T> FValueOrBBKey_Enum(T Default) : DefaultValue(static_cast<uint8>(Default)), EnumType(StaticEnum<T>()), NativeEnumTypeName(GetNameSafe(EnumType))`
- L228 _public function_ `template <typename T> T GetValue(const UBehaviorTreeComponent& BehaviorComp) const`
- L234 _public function_ `template <typename T> T GetValue(const UBehaviorTreeComponent* BehaviorComp) const`
- L240 _public function_ `template <typename T> T GetValue(const UBlackboardComponent& BlackboardComp) const`
- L246 _public function_ `template <typename T> T GetValue(const UBlackboardComponent* BlackboardComp) const`
- L251 _public prototype_ `uint8 GetValue(const UBehaviorTreeComponent& BehaviorComp) const;`
- L252 _public prototype_ `uint8 GetValue(const UBehaviorTreeComponent* BehaviorComp) const;`
- L253 _public prototype_ `uint8 GetValue(const UBlackboardComponent& Blackboard) const;`
- L254 _public prototype_ `uint8 GetValue(const UBlackboardComponent* Blackboard) const;`
- L256 _public prototype_ `bool SerializeFromMismatchedTag(const FPropertyTag& Tag, FStructuredArchive::FSlot Slot);`
- L259 _public prototype_ `virtual bool IsCompatibleType(const UBlackboardKeyType* KeyType) const override;`
- L262 _public prototype_ `FString ToString() const override;`
- L265 _public function_ `operator uint8() const` — `UE_DEPRECATED_FORGAME(5.5, "Implicit conversion will be removed next version. Call GetValue instead")`
- L267 _public prototype_ `void SetEnumType(UEnum* NewEnumType);`
- L271 _protected member_ `uint8 DefaultValue = 0;` — `UPROPERTY(EditAnywhere, Category = "Value")`
- L274 _protected member_ `TObjectPtr<UEnum> EnumType = nullptr;` — `UPROPERTY(EditDefaultsOnly, Category = "Value")`
- L278 _protected member_ `FString NativeEnumTypeName;` — `UPROPERTY(EditDefaultsOnly, Category = "Value")` — Name of enum type defined in C++ code, will take priority over asset from EnumType property

#### struct `FValueOrBBKey_Float`  
`struct FValueOrBBKey_Float : public FValueOrBlackboardKeyBase`  
_L282-308_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FValueOrBlackboardKeyBase`
- L286 _public function_ `FValueOrBBKey_Float(float Default = 0.f) : DefaultValue(Default)`
- L288 _public prototype_ `float GetValue(const UBehaviorTreeComponent& BehaviorComp) const;`
- L289 _public prototype_ `float GetValue(const UBehaviorTreeComponent* BehaviorComp) const;`
- L290 _public prototype_ `float GetValue(const UBlackboardComponent& Blackboard) const;`
- L291 _public prototype_ `float GetValue(const UBlackboardComponent* Blackboard) const;`
- L293 _public prototype_ `bool SerializeFromMismatchedTag(const FPropertyTag& Tag, FStructuredArchive::FSlot Slot);`
- L296 _public prototype_ `virtual bool IsCompatibleType(const UBlackboardKeyType* KeyType) const override;`
- L299 _public prototype_ `FString ToString() const override;`
- L300 _public prototype_ `bool IsBoundOrNonZero() const;`
- L303 _public function_ `operator float() const` — `UE_DEPRECATED_FORGAME(5.5, "Implicit conversion will be removed next version. Call GetValue instead")`
- L307 _protected member_ `float DefaultValue = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Value")`

#### struct `FValueOrBBKey_Int32`  
`struct FValueOrBBKey_Int32 : public FValueOrBlackboardKeyBase`  
_L311-335_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FValueOrBlackboardKeyBase`
- L314 _public function_ `FValueOrBBKey_Int32(int32 Default = 0) : DefaultValue(Default)`
- L316 _public prototype_ `int32 GetValue(const UBehaviorTreeComponent& BehaviorComp) const;`
- L317 _public prototype_ `int32 GetValue(const UBehaviorTreeComponent* BehaviorComp) const;`
- L318 _public prototype_ `int32 GetValue(const UBlackboardComponent& Blackboard) const;`
- L319 _public prototype_ `int32 GetValue(const UBlackboardComponent* Blackboard) const;`
- L321 _public prototype_ `bool SerializeFromMismatchedTag(const FPropertyTag& Tag, FStructuredArchive::FSlot Slot);`
- L324 _public prototype_ `virtual bool IsCompatibleType(const UBlackboardKeyType* KeyType) const override;`
- L327 _public function_ `FString ToString() const override`
- L330 _public function_ `operator int32() const` — `UE_DEPRECATED_FORGAME(5.5, "Implicit conversion will be removed next version. Call GetValue instead")`
- L334 _protected member_ `int32 DefaultValue = 0;` — `UPROPERTY(EditAnywhere, Category = "Value")`

#### struct `FValueOrBBKey_Name`  
`struct FValueOrBBKey_Name : public FValueOrBlackboardKeyBase`  
_L338-363_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FValueOrBlackboardKeyBase`
- L342 _public function_ `FValueOrBBKey_Name(FName Default = FName()) : DefaultValue(Default)`
- L344 _public prototype_ `FName GetValue(const UBehaviorTreeComponent& BehaviorComp) const;`
- L345 _public prototype_ `FName GetValue(const UBehaviorTreeComponent* BehaviorComp) const;`
- L346 _public prototype_ `FName GetValue(const UBlackboardComponent& Blackboard) const;`
- L347 _public prototype_ `FName GetValue(const UBlackboardComponent* Blackboard) const;`
- L349 _public prototype_ `bool SerializeFromMismatchedTag(const FPropertyTag& Tag, FStructuredArchive::FSlot Slot);`
- L352 _public prototype_ `virtual bool IsCompatibleType(const UBlackboardKeyType* KeyType) const override;`
- L355 _public prototype_ `FString ToString() const override;`
- L358 _public function_ `operator FName() const` — `UE_DEPRECATED_FORGAME(5.5, "Implicit conversion will be removed next version. Call GetValue instead")`
- L362 _protected member_ `FName DefaultValue;` — `UPROPERTY(EditAnywhere, Category = "Value")`

#### struct `FValueOrBBKey_String`  
`struct FValueOrBBKey_String : public FValueOrBlackboardKeyBase`  
_L366-391_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FValueOrBlackboardKeyBase`
- L370 _public function_ `FValueOrBBKey_String(FString Default = FString()) : DefaultValue(MoveTemp(Default))`
- L372 _public prototype_ `FString GetValue(const UBehaviorTreeComponent& BehaviorComp) const;`
- L373 _public prototype_ `FString GetValue(const UBehaviorTreeComponent* BehaviorComp) const;`
- L374 _public prototype_ `FString GetValue(const UBlackboardComponent& Blackboard) const;`
- L375 _public prototype_ `FString GetValue(const UBlackboardComponent* Blackboard) const;`
- L377 _public prototype_ `bool SerializeFromMismatchedTag(const FPropertyTag& Tag, FStructuredArchive::FSlot Slot);`
- L380 _public prototype_ `virtual bool IsCompatibleType(const UBlackboardKeyType* KeyType) const override;`
- L384 _public function_ `operator FString() const` — `UE_DEPRECATED_FORGAME(5.5, "Implicit conversion will be removed next version. Call GetValue instead")`
- L386 _public function_ `FString ToString() const override`
- L390 _protected member_ `FString DefaultValue;` — `UPROPERTY(EditAnywhere, Category = "Value")`

#### struct `FValueOrBBKey_Object`  
`struct FValueOrBBKey_Object : public FValueOrBlackboardKeyBase`  
_L394-453_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FValueOrBlackboardKeyBase`
- L399 _public prototype_ `FValueOrBBKey_Object() = default;`
- L402 _public function_ `template <typename T> FValueOrBBKey_Object(TObjectPtr<T> Default) : DefaultValue(Default), BaseClass(T::StaticClass())`
- L406 _public function_ `template <typename T> T* GetValue(const UBehaviorTreeComponent& BehaviorComp) const`
- L412 _public function_ `template <typename T> T* GetValue(const UBehaviorTreeComponent* BehaviorComp) const`
- L418 _public function_ `template <typename T> T* GetValue(const UBlackboardComponent& BlackboardComp) const`
- L424 _public function_ `template <typename T> T* GetValue(const UBlackboardComponent* BlackboardComp) const`
- L429 _public prototype_ `UObject* GetValue(const UBehaviorTreeComponent& BehaviorComp) const;`
- L430 _public prototype_ `UObject* GetValue(const UBehaviorTreeComponent* BehaviorComp) const;`
- L431 _public prototype_ `UObject* GetValue(const UBlackboardComponent& Blackboard) const;`
- L432 _public prototype_ `UObject* GetValue(const UBlackboardComponent* Blackboard) const;`
- L434 _public prototype_ `bool SerializeFromMismatchedTag(const FPropertyTag& Tag, FStructuredArchive::FSlot Slot);`
- L437 _public prototype_ `virtual bool IsCompatibleType(const UBlackboardKeyType* KeyType) const override;`
- L440 _public prototype_ `FString ToString() const override;`
- L443 _public function_ `operator UObject*() const` — `UE_DEPRECATED_FORGAME(5.5, "Implicit conversion will be removed next version. Call GetValue instead")`
- L445 _public prototype_ `void SetBaseClass(UClass* NewBaseClass);`
- L449 _protected member_ `TObjectPtr<UObject> DefaultValue = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Value")`
- L452 _protected member_ `TObjectPtr<UClass> BaseClass = UObject::StaticClass();` — `UPROPERTY(EditDefaultsOnly, Category = "Value", meta = (AllowAbstract = "1"))`

#### struct `FValueOrBBKey_Rotator`  
`struct FValueOrBBKey_Rotator : public FValueOrBlackboardKeyBase`  
_L456-481_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FValueOrBlackboardKeyBase`
- L460 _public function_ `FValueOrBBKey_Rotator(FRotator Default = FRotator::ZeroRotator) : DefaultValue(MoveTemp(Default))`
- L462 _public prototype_ `FRotator GetValue(const UBehaviorTreeComponent& BehaviorComp) const;`
- L463 _public prototype_ `FRotator GetValue(const UBehaviorTreeComponent* BehaviorComp) const;`
- L464 _public prototype_ `FRotator GetValue(const UBlackboardComponent& Blackboard) const;`
- L465 _public prototype_ `FRotator GetValue(const UBlackboardComponent* Blackboard) const;`
- L467 _public prototype_ `bool SerializeFromMismatchedTag(const FPropertyTag& Tag, FStructuredArchive::FSlot Slot);`
- L470 _public prototype_ `virtual bool IsCompatibleType(const UBlackboardKeyType* KeyType) const override;`
- L473 _public prototype_ `FString ToString() const override;`
- L476 _public function_ `operator FRotator() const` — `UE_DEPRECATED_FORGAME(5.5, "Implicit conversion will be removed next version. Call GetValue instead")`
- L480 _protected member_ `FRotator DefaultValue;` — `UPROPERTY(EditAnywhere, Category = "Value")`

#### struct `FValueOrBBKey_Vector`  
`struct FValueOrBBKey_Vector : public FValueOrBlackboardKeyBase`  
_L484-509_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FValueOrBlackboardKeyBase`
- L488 _public function_ `FValueOrBBKey_Vector(FVector Default = FVector::ZeroVector) : DefaultValue(MoveTemp(Default))`
- L490 _public prototype_ `FVector GetValue(const UBehaviorTreeComponent& BehaviorComp) const;`
- L491 _public prototype_ `FVector GetValue(const UBehaviorTreeComponent* BehaviorComp) const;`
- L492 _public prototype_ `FVector GetValue(const UBlackboardComponent& Blackboard) const;`
- L493 _public prototype_ `FVector GetValue(const UBlackboardComponent* Blackboard) const;`
- L495 _public prototype_ `bool SerializeFromMismatchedTag(const FPropertyTag& Tag, FStructuredArchive::FSlot Slot);`
- L498 _public prototype_ `virtual bool IsCompatibleType(const UBlackboardKeyType* KeyType) const override;`
- L501 _public prototype_ `FString ToString() const override;`
- L504 _public function_ `operator FVector() const` — `UE_DEPRECATED_FORGAME(5.5, "Implicit conversion will be removed next version. Call GetValue instead")`
- L508 _protected member_ `FVector DefaultValue;` — `UPROPERTY(EditAnywhere, Category = "Value")`

#### struct `FValueOrBBKey_Struct`  
`struct FValueOrBBKey_Struct : public FValueOrBlackboardKeyBase`  
_L512-578_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FValueOrBlackboardKeyBase`
- L518 _public function_ `template <typename T> FValueOrBBKey_Struct(const T& Value)`
- L522 _public prototype_ `FValueOrBBKey_Struct() = default;`
- L525 _public prototype_ `virtual bool IsCompatibleType(const UBlackboardKeyType* KeyType) const override;`
- L528 _public prototype_ `FString ToString() const override;`
- L531 _public function_ `template <typename T> const T& GetValue(const UBehaviorTreeComponent& BehaviorComp) const`
- L538 _public function_ `template <typename T> const T& GetValue(const UBehaviorTreeComponent* BehaviorComp) const`
- L545 _public function_ `template <typename T> const T& GetValue(const UBlackboardComponent& BlackboardComp) const`
- L552 _public function_ `template <typename T> const T& GetValue(const UBlackboardComponent* BlackboardComp) const`
- L558 _public prototype_ `bool SerializeFromMismatchedTag(const FPropertyTag& Tag, FStructuredArchive::FSlot Slot);`
- L560 _public prototype_ `FConstStructView GetValue(const UBehaviorTreeComponent& BehaviorComp) const;`
- L561 _public prototype_ `FConstStructView GetValue(const UBehaviorTreeComponent* BehaviorComp) const;`
- L562 _public prototype_ `FConstStructView GetValue(const UBlackboardComponent& Blackboard) const;`
- L563 _public prototype_ `FConstStructView GetValue(const UBlackboardComponent* Blackboard) const;`
- L565 _public prototype_ `void SetStructType(UScriptStruct* NewStructType);`
- L571 _protected member_ `FInstancedStruct DefaultValue;` — `UPROPERTY(EditAnywhere, Category = Value)`
- L576 _protected member_ `bool bCanEditDefaultValueType = false;` — `UPROPERTY(EditDefaultsOnly, Category = Value)` — Exist to give a way for the details to know if the DefaultValue type can be edited.

#### struct `TStructOpsTypeTraits`  
`template <> struct TStructOpsTypeTraits<FValueOrBBKey_Bool> : public TStructOpsTypeTraitsBase2<FValueOrBBKey_Bool>`  
_L581-587_
- inherits: `TStructOpsTypeTraitsBase2<FValueOrBBKey_Bool>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L584-586_

#### struct `TStructOpsTypeTraits`  
`template <> struct TStructOpsTypeTraits<FValueOrBBKey_Class> : public TStructOpsTypeTraitsBase2<FValueOrBBKey_Class>`  
_L590-596_
- inherits: `TStructOpsTypeTraitsBase2<FValueOrBBKey_Class>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L593-595_

#### struct `TStructOpsTypeTraits`  
`template <> struct TStructOpsTypeTraits<FValueOrBBKey_Enum> : public TStructOpsTypeTraitsBase2<FValueOrBBKey_Enum>`  
_L599-605_
- inherits: `TStructOpsTypeTraitsBase2<FValueOrBBKey_Enum>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L602-604_

#### struct `TStructOpsTypeTraits`  
`template <> struct TStructOpsTypeTraits<FValueOrBBKey_Float> : public TStructOpsTypeTraitsBase2<FValueOrBBKey_Float>`  
_L608-614_
- inherits: `TStructOpsTypeTraitsBase2<FValueOrBBKey_Float>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L611-613_

#### struct `TStructOpsTypeTraits`  
`template <> struct TStructOpsTypeTraits<FValueOrBBKey_Int32> : public TStructOpsTypeTraitsBase2<FValueOrBBKey_Int32>`  
_L617-623_
- inherits: `TStructOpsTypeTraitsBase2<FValueOrBBKey_Int32>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L620-622_

#### struct `TStructOpsTypeTraits`  
`template <> struct TStructOpsTypeTraits<FValueOrBBKey_Name> : public TStructOpsTypeTraitsBase2<FValueOrBBKey_Name>`  
_L626-632_
- inherits: `TStructOpsTypeTraitsBase2<FValueOrBBKey_Name>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L629-631_

#### struct `TStructOpsTypeTraits`  
`template <> struct TStructOpsTypeTraits<FValueOrBBKey_String> : public TStructOpsTypeTraitsBase2<FValueOrBBKey_String>`  
_L635-641_
- inherits: `TStructOpsTypeTraitsBase2<FValueOrBBKey_String>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L638-640_

#### struct `TStructOpsTypeTraits`  
`template <> struct TStructOpsTypeTraits<FValueOrBBKey_Object> : public TStructOpsTypeTraitsBase2<FValueOrBBKey_Object>`  
_L644-650_
- inherits: `TStructOpsTypeTraitsBase2<FValueOrBBKey_Object>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L647-649_

#### struct `TStructOpsTypeTraits`  
`template <> struct TStructOpsTypeTraits<FValueOrBBKey_Rotator> : public TStructOpsTypeTraitsBase2<FValueOrBBKey_Rotator>`  
_L653-659_
- inherits: `TStructOpsTypeTraitsBase2<FValueOrBBKey_Rotator>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L656-658_

#### struct `TStructOpsTypeTraits`  
`template <> struct TStructOpsTypeTraits<FValueOrBBKey_Struct> : public TStructOpsTypeTraitsBase2<FValueOrBBKey_Struct>`  
_L662-668_
- inherits: `TStructOpsTypeTraitsBase2<FValueOrBBKey_Struct>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L665-667_

#### struct `TStructOpsTypeTraits`  
`template <> struct TStructOpsTypeTraits<FValueOrBBKey_Vector> : public TStructOpsTypeTraitsBase2<FValueOrBBKey_Vector>`  
_L671-677_
- inherits: `TStructOpsTypeTraitsBase2<FValueOrBBKey_Vector>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L674-676_

#### Free symbols / members of external scopes

- L34 _namespace_ `namespace FBlackboard`
- L37 _function_ `template <typename T> TOptional<typename T::FDataType> TryGetBlackboardKeyValue(const UBlackboardComponent& Blackboard, const FName& Name, FBlackboard::FKey& InOutCachedKey)` (scope `FBlackboard`)
- L51 _function_ `template <typename T> typename T::FDataType GetValue(const UBlackboardComponent& Blackboard, const FName& Name, FBlackboard::FKey& InOutCachedKey, const typename T::FDataType& DefaultValue)` (scope `FBlackboard`)
- L64 _function_ `template <typename T> typename T::FDataType GetValue(const UBehaviorTreeComponent& BehaviorComp, const FName& Name, FBlackboard::FKey& InOutCachedKey, const typename T::FDataType& DefaultValue)` (scope `FBlackboard`)
- L73 _prototype_ `FConstStructView TryGetBlackboardKeyStruct(const UBlackboardComponent& Blackboard, const FName& Name, FBlackboard::FKey& InOutCachedKey, const UScriptStruct* TargetStruct);` (scope `FBlackboard`)
- L75 _prototype_ `FConstStructView GetStructValue(const UBlackboardComponent& Blackboard, const FName& Name, FBlackboard::FKey& InOutCachedKey, const FConstStructView& DefaultValue);` (scope `FBlackboard`)
- L77 _prototype_ `FConstStructView GetStructValue(const UBehaviorTreeComponent& BehaviorComp, const FName& Name, FBlackboard::FKey& InOutCachedKey, const FConstStructView& DefaultValue);` (scope `FBlackboard`)
- L585 _enumerator_ `WithStructuredSerializeFromMismatchedTag = true` (scope `TStructOpsTypeTraits::__anon099968350103`)
- L594 _enumerator_ `WithStructuredSerializeFromMismatchedTag = true` (scope `TStructOpsTypeTraits::__anon099968350203`)
- L603 _enumerator_ `WithStructuredSerializeFromMismatchedTag = true` (scope `TStructOpsTypeTraits::__anon099968350303`)
- L612 _enumerator_ `WithStructuredSerializeFromMismatchedTag = true` (scope `TStructOpsTypeTraits::__anon099968350403`)
- L621 _enumerator_ `WithStructuredSerializeFromMismatchedTag = true` (scope `TStructOpsTypeTraits::__anon099968350503`)
- L630 _enumerator_ `WithStructuredSerializeFromMismatchedTag = true` (scope `TStructOpsTypeTraits::__anon099968350603`)
- L639 _enumerator_ `WithStructuredSerializeFromMismatchedTag = true` (scope `TStructOpsTypeTraits::__anon099968350703`)
- L648 _enumerator_ `WithStructuredSerializeFromMismatchedTag = true` (scope `TStructOpsTypeTraits::__anon099968350803`)
- L657 _enumerator_ `WithStructuredSerializeFromMismatchedTag = true` (scope `TStructOpsTypeTraits::__anon099968350903`)
- L666 _enumerator_ `WithStructuredSerializeFromMismatchedTag = true` (scope `TStructOpsTypeTraits::__anon099968350a03`)
- L675 _enumerator_ `WithStructuredSerializeFromMismatchedTag = true` (scope `TStructOpsTypeTraits::__anon099968350b03`)

### `Source/Runtime/AIModule/Classes/Blueprint/AIAsyncTaskBlueprintProxy.h` (Public)


#### class `UAIAsyncTaskBlueprintProxy`  
`class UAIAsyncTaskBlueprintProxy : public UObject`  
_L17-43_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L22 _private member_ `FOAISimpleDelegate OnSuccess;` — `UPROPERTY(BlueprintAssignable)`
- L25 _private member_ `FOAISimpleDelegate OnFail;` — `UPROPERTY(BlueprintAssignable)`
- L29 _public prototype_ `void OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type MovementResult);` — `UFUNCTION()`
- L31 _public prototype_ `void OnNoPath();`
- L32 _public prototype_ `void OnAtGoal();`
- L35 _public prototype_ `virtual void BeginDestroy() override;`
- L38 _public member_ `TWeakObjectPtr<AAIController> AIController;`
- L39 _public member_ `FAIRequestID MoveRequestId;`
- L40 _public member_ `TWeakObjectPtr<UWorld> MyWorld;`
- L42 _public member_ `FTimerHandle TimerHandle_OnInstantFinish;`

#### Free symbols / members of external scopes

- L14 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOAISimpleDelegate, EPathFollowingResult::Type, MovementResult);`
- L14 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOAISimpleDelegate, EPathFollowingResult::Type, MovementResult);`

### `Source/Runtime/AIModule/Classes/Blueprint/AIBlueprintHelperLibrary.h` (Public)


#### class `UAIBlueprintHelperLibrary`  
`class UAIBlueprintHelperLibrary : public UBlueprintFunctionLibrary`  
_L26-99_
- reflection: `UCLASS(meta=(ScriptName="AIHelperLibrary"), MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- L31 _private prototype_ `static UAIAsyncTaskBlueprintProxy* CreateMoveToProxyObject(UObject* WorldContextObject, APawn* Pawn, FVector Destination, AActor* TargetActor = NULL, float AcceptanceRadius = 5.f, bool bStopOnOverlap = false);` — `UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly = "TRUE"))`
- L34 _private prototype_ `static void SendAIMessage(APawn* Target, FName Message, UObject* MessageSource, bool bSuccess = true);` — `UFUNCTION(BlueprintCallable, Category="AI", meta=(DefaultToSelf="MessageSource"))`
- L45 _private prototype_ `static APawn* SpawnAIFromClass(UObject* WorldContextObject, TSubclassOf<APawn> PawnClass, UBehaviorTree* BehaviorTree, FVector Location, FRotator Rotation = FRotator::ZeroRotator, bool bNoCollisionFail = false, AActor* Owner = nullptr);` — `UFUNCTION(BlueprintCallable, Category="AI", meta=(WorldContext="WorldContextObject", UnsafeDuringActorConstruction="true", AdvancedDisplay = "Owner"))` — Spawns AI agent of a given class. The PawnClass needs to have AIController set for the function to spawn a controller as well. @param BehaviorTree if set, and the function has successfully spawned and AI controller, this BehaviorTree asset will be assigned to the AI controller, and run. @param Owner lets you spawn the AI in a sublevel rather than in the persistent level (which is the default behavior).
- L50 _private prototype_ `static AAIController* GetAIController(AActor* ControlledActor);` — `UFUNCTION(BlueprintPure, Category = "AI", meta = (DefaultToSelf = "ControlledObject"))` — The way it works exactly is if the actor passed in is a pawn, then the function retrieves pawn's controller cast to AIController. Otherwise the function returns actor cast to AIController.
- L53 _private prototype_ `static UBlackboardComponent* GetBlackboard(AActor* Target);` — `UFUNCTION(BlueprintPure, Category="AI", meta=(DefaultToSelf="Target"))`
- L57 _private prototype_ `static void LockAIResourcesWithAnimation(UAnimInstance* AnimInstance, bool bLockMovement, bool LockAILogic);` — `UFUNCTION(BlueprintCallable, Category = "Animation", BlueprintAuthorityOnly, meta = (DefaultToSelf = "AnimInstance"))` — locks indicated AI resources of animated pawn
- L61 _private prototype_ `static void UnlockAIResourcesWithAnimation(UAnimInstance* AnimInstance, bool bUnlockMovement, bool UnlockAILogic);` — `UFUNCTION(BlueprintCallable, Category = "Animation", BlueprintAuthorityOnly, meta = (DefaultToSelf = "AnimInstance"))` — unlocks indicated AI resources of animated pawn. Will unlock only animation-locked resources
- L64 _private prototype_ `static bool IsValidAILocation(FVector Location);` — `UFUNCTION(BlueprintPure, Category = "AI")`
- L67 _private prototype_ `static bool IsValidAIDirection(FVector DirectionVector);` — `UFUNCTION(BlueprintPure, Category = "AI")`
- L70 _private prototype_ `static bool IsValidAIRotation(FRotator Rotation);` — `UFUNCTION(BlueprintPure, Category = "AI")`
- L77 _private prototype_ `static UNavigationPath* GetCurrentPath(AController* Controller);` — `UFUNCTION(BlueprintPure, Category = "AI", meta = (UnsafeDuringActorConstruction = "true"))` — Returns a NEW UOBJECT that is a COPY of navigation path given controller is currently using. The result being a copy means you won't be able to influence agent's pathfollowing by manipulating received path. Please use GetCurrentPathPoints if you only need the array of path points.
- L81 _private prototype_ `static const TArray<FVector> GetCurrentPathPoints(AController* Controller);` — `UFUNCTION(BlueprintPure, Category = "AI", meta = (UnsafeDuringActorConstruction = "true"))` — Returns an array of navigation path points given controller is currently using.
- L85 _private prototype_ `static int32 GetCurrentPathIndex(const AController* Controller);` — `UFUNCTION(BlueprintPure, Category = "AI", meta = (UnsafeDuringActorConstruction = "true"))` — Return the path index the given controller is currently at. Returns INDEX_NONE if no path.
- L89 _private prototype_ `static int32 GetNextNavLinkIndex(const AController* Controller);` — `UFUNCTION(BlueprintPure, Category = "AI", meta = (UnsafeDuringActorConstruction = "true"))` — Return the path index of the next nav link for the current path of the given controller. Returns INDEX_NONE if no path or no incoming nav link.
- L92 _private prototype_ `static void SimpleMoveToActor(AController* Controller, const AActor* Goal);` — `UFUNCTION(BlueprintCallable, Category = "AI|Navigation")`
- L95 _private prototype_ `static void SimpleMoveToLocation(AController* Controller, const FVector& Goal);` — `UFUNCTION(BlueprintCallable, Category = "AI|Navigation")`
- L98 _private prototype_ `static UPathFollowingComponent* GetPathComp(const AController* Controller);`

### `Source/Runtime/AIModule/Classes/BrainComponent.h` (Public)


#### struct `FAIMessage`  
`struct FAIMessage`  
_L26-66_
- L35 _public member_ `FName MessageName;` — type of message
- L38 _public member_ `FWeakObjectPtr Sender;` — message source
- L41 _public member_ `FAIRequestID RequestID;` — message param: ID
- L44 _public member_ `TEnumAsByte<EStatus> Status;` — message param: status
- L47 _public member_ `uint8 MessageFlags;` — message param: custom flags
- L49 _public function_ `FAIMessage() : MessageName(NAME_None), Sender(nullptr), RequestID(0), Status(FAIMessage::Success), MessageFlags(0)`
- L50 _public function_ `FAIMessage(FName InMessage, UObject* InSender) : MessageName(InMessage), Sender(InSender), RequestID(0), Status(FAIMessage::Success), MessageFlags(0)`
- L51 _public function_ `FAIMessage(FName InMessage, UObject* InSender, FAIRequestID InID, EStatus InStatus) : MessageName(InMessage), Sender(InSender), RequestID(InID), Status(InStatus), MessageFlags(0)`
- L52 _public function_ `FAIMessage(FName InMessage, UObject* InSender, FAIRequestID InID, bool bSuccess) : MessageName(InMessage), Sender(InSender), RequestID(InID), Status(bSuccess ? Success : Failure), MessageFlags(0)`
- L53 _public function_ `FAIMessage(FName InMessage, UObject* InSender, EStatus InStatus) : MessageName(InMessage), Sender(InSender), RequestID(0), Status(InStatus), MessageFlags(0)`
- L54 _public function_ `FAIMessage(FName InMessage, UObject* InSender, bool bSuccess) : MessageName(InMessage), Sender(InSender), RequestID(0), Status(bSuccess ? Success : Failure), MessageFlags(0)`
- L56 _public function_ `void SetFlags(uint8 Flags)`
- L57 _public function_ `void SetFlag(uint8 Flag)`
- L58 _public function_ `void ClearFlag(uint8 Flag)`
- L59 _public function_ `bool HasFlag(uint8 Flag) const`
- L61 _public prototype_ `static void Send(AController* Controller, const FAIMessage& Message);`
- L62 _public prototype_ `static void Send(APawn* Pawn, const FAIMessage& Message);`
- L63 _public prototype_ `static void Send(UBrainComponent* BrainComp, const FAIMessage& Message);`
- L65 _public prototype_ `static void Broadcast(UObject* WorldContextObject, const FAIMessage& Message);`

#### enum `FAIMessage::EStatus`  
`enum EStatus`  
_L28-32_
- L30 _public enumerator_ `Failure`
- L31 _public enumerator_ `Success`

#### struct `FAIMessageObserver`  
`struct FAIMessageObserver : public TSharedFromThis<FAIMessageObserver>`  
_L70-114_
- inherits: `TSharedFromThis<FAIMessageObserver>`
- L73 _public prototype_ `FAIMessageObserver();`
- L75 _public prototype_ `static FAIMessageObserverHandle Create(AController* Controller, FName MessageType, FOnAIMessage const& Delegate);`
- L76 _public prototype_ `static FAIMessageObserverHandle Create(AController* Controller, FName MessageType, FAIRequestID MessageID, FOnAIMessage const& Delegate);`
- L78 _public prototype_ `static FAIMessageObserverHandle Create(APawn* Pawn, FName MessageType, FOnAIMessage const& Delegate);`
- L79 _public prototype_ `static FAIMessageObserverHandle Create(APawn* Pawn, FName MessageType, FAIRequestID MessageID, FOnAIMessage const& Delegate);`
- L81 _public prototype_ `static FAIMessageObserverHandle Create(UBrainComponent* BrainComp, FName MessageType, FOnAIMessage const& Delegate);`
- L82 _public prototype_ `static FAIMessageObserverHandle Create(UBrainComponent* BrainComp, FName MessageType, FAIRequestID MessageID, FOnAIMessage const& Delegate);`
- L84 _public prototype_ `~FAIMessageObserver();`
- L86 _public prototype_ `void OnMessage(const FAIMessage& Message);`
- L87 _public prototype_ `FString DescribeObservedMessage() const;`
- L89 _public function_ `inline FName GetObservedMessageType() const`
- L90 _public function_ `inline FAIRequestID GetObservedMessageID() const`
- L91 _public function_ `inline bool IsObservingMessageID() const`
- L95 _private prototype_ `void Register(UBrainComponent* OwnerComp);`
- L96 _private prototype_ `void Unregister();`
- L99 _private member_ `FName MessageType;` — observed message type
- L102 _private member_ `FAIRequestID MessageID;` — filter: message ID
- L103 _private member_ `bool bFilterByID;`
- L106 _private member_ `FOnAIMessage ObserverDelegate;` — delegate to call
- L109 _private member_ `TWeakObjectPtr<UBrainComponent> Owner;` — brain component owning this observer
- L112 _private prototype_ `FAIMessageObserver(const FAIMessageObserver&);` — Non-copyable
- L113 _private prototype_ `FAIMessageObserver& operator=(const FAIMessageObserver&);`

#### class `UBrainComponent`  
`class UBrainComponent : public UActorComponent, public IAIResourceInterface`  
_L117-222_
- reflection: `UCLASS(ClassGroup = AI, BlueprintType, hidecategories = (Sockets, Collision), MinimalAPI)`
- inherits: `UActorComponent,IAIResourceInterface`
- L124 _protected member_ `TObjectPtr<UBlackboardComponent> BlackboardComp;` — `UPROPERTY(transient)` — blackboard component
- L127 _protected member_ `TObjectPtr<AAIController> AIOwner;` — `UPROPERTY(transient)`
- L131 _protected member_ `TArray<FAIMessage> MessagesToProcess;` — @TODO this is a temp contraption to implement delayed messages delivering until proper AI messaging is implemented
- L134 _public function_ `virtual FString GetDebugInfoString() const`
- L139 _public prototype_ `void RequestLogicRestartOnUnlock();` — To be called in case we want to restart AI logic while it's still being locked. On subsequent ResumeLogic instead RestartLogic will be called. @note this call does nothing if logic is not locked at the moment of call
- L143 _public prototype_ `virtual void StartLogic();` — `UFUNCTION(BlueprintCallable, Category = "AI|Logic")` — Starts brain logic. If brain is already running, will not do anything.
- L147 _public prototype_ `virtual void RestartLogic();` — `UFUNCTION(BlueprintCallable, Category = "AI|Logic")` — Restarts currently running or previously ran brain logic.
- L151 _public prototype_ `virtual void StopLogic(const FString& Reason);` — `UFUNCTION(BlueprintCallable, Category = "AI|Logic")` — Stops currently running brain logic.
- L154 _public function_ `virtual void Cleanup()` — AI logic won't be needed anymore, stop all activity and run cleanup
- L157 _public function_ `virtual void PauseLogic(const FString& Reason)` — Pause logic and blackboard updates.
- L163 _public prototype_ `virtual EAILogicResuming::Type ResumeLogic(const FString& Reason);` — Resumes paused brain logic. MUST be called by child implementations! @return indicates whether child class' ResumeLogic should be called (true) or has it been handled in a different way and no other actions are required (false)
- L167 _public prototype_ `virtual bool IsRunning() const;` — `UFUNCTION(BlueprintPure, Category = "AI|Logic")`
- L170 _public prototype_ `virtual bool IsPaused() const;` — `UFUNCTION(BlueprintPure, Category = "AI|Logic")`
- L173 _public prototype_ `virtual void DescribeSelfToVisLog(struct FVisualLogEntry* Snapshot) const;`
- L177 _public prototype_ `virtual void LockResource(EAIRequestPriority::Type LockSource) override;` — IAIResourceInterface begin
- L178 _public prototype_ `virtual void ClearResourceLock(EAIRequestPriority::Type LockSource) override;`
- L179 _public prototype_ `virtual void ForceUnlockResource() override;`
- L180 _public prototype_ `virtual bool IsResourceLocked() const override;`
- L183 _public prototype_ `virtual void HandleMessage(const FAIMessage& Message);`
- L186 _public prototype_ `virtual void InitializeComponent() override;` — BEGIN UActorComponent overrides
- L187 _public prototype_ `virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;`
- L188 _public prototype_ `virtual void OnRegister() override;`
- L192 _public prototype_ `void CacheBlackboardComponent(UBlackboardComponent* BBComp);` — caches BlackboardComponent's pointer to be used with this brain component
- L195 _public prototype_ `UBlackboardComponent* GetBlackboardComponent();` — @return blackboard used with this component
- L198 _public prototype_ `const UBlackboardComponent* GetBlackboardComponent() const;` — @return blackboard used with this component
- L200 _public function_ `inline AAIController* GetAIOwner() const`
- L205 _protected member_ `TArray<FAIMessageObserver*> MessageObservers;` — active message observers
- L211 _protected member_ `FAIResourceLock ResourceLock;` — used to keep track of which subsystem requested this AI resource be locked
- L214 _private member_ `uint32 bDoLogicRestartOnUnlock : 1;`
- L219 _public member_ `static const FName AIMessage_MoveFinished;` — static names to be used with SendMessage. Fell free to define game-specific messages anywhere you want
- L220 _public member_ `static const FName AIMessage_RepathFailed;`
- L221 _public member_ `static const FName AIMessage_QueryFinished;`
- L227 _function_ `inline UBlackboardComponent* UBrainComponent::GetBlackboardComponent()`
- L232 _function_ `inline const UBlackboardComponent* UBrainComponent::GetBlackboardComponent() const`

#### Free symbols / members of external scopes

- L22 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnAIMessage, UBrainComponent*, const FAIMessage&);`
- L22 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnAIMessage, UBrainComponent*, const FAIMessage&);`
- L24 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogBrain, Warning, All);`
- L24 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogBrain, Warning, All);`
- L68 _typedef_ `typedef TSharedPtr<struct FAIMessageObserver> FAIMessageObserverHandle;`

### `Source/Runtime/AIModule/Classes/DataProviders/AIDataProvider.h` (Public)


#### struct `FAIDataProviderValue`  
`struct FAIDataProviderValue`  
_L25-71_
- reflection: `USTRUCT()`
- L31 _private member_ `mutable FProperty* CachedProperty;` — cached uproperty of provider
- L36 _public member_ `TObjectPtr<UAIDataProvider> DataBinding;` — `UPROPERTY(EditAnywhere, Instanced, Category = Value)` — (optional) provider for dynamic data binding
- L40 _public member_ `FName DataField;` — `UPROPERTY(EditAnywhere, Category = Value)` — name of provider's value property
- L43 _public prototype_ `virtual FString ValueToString() const;` — describe default data
- L44 _public prototype_ `FString ToString() const;`
- L47 _public prototype_ `virtual bool IsMatchingType(FProperty* PropType) const;` — filter for provider's properties
- L50 _public prototype_ `void GetMatchingProperties(TArray<FName>& MatchingProperties) const;` — find all properties of provider that are matching filter
- L54 _public function_ `template<typename T> T* GetRawValuePtr() const` — return raw data from provider's property
- L60 _public prototype_ `void BindData(const UObject* Owner, int32 RequestId) const;` — bind data in provider and cache property for faster access
- L62 _public function_ `inline bool IsDynamic() const`
- L64 _public function_ `FAIDataProviderValue() : CachedProperty(nullptr), DataBinding(nullptr)`
- L70 _public prototype_ `virtual ~FAIDataProviderValue() = default;`

#### struct `FAIDataProviderTypedValue`  
`struct FAIDataProviderTypedValue : public FAIDataProviderValue`  
_L74-93_
- reflection: `USTRUCT()`
- inherits: `FAIDataProviderValue`
- L78 _public function_ `FAIDataProviderTypedValue() : PropertyType_DEPRECATED(nullptr) , PropertyType(nullptr)`
- L85 _public member_ `TObjectPtr<UClass> PropertyType_DEPRECATED;` — `UPROPERTY()` — type of value
- L86 _public member_ `FFieldClass* PropertyType;`
- L89 _public prototype_ `virtual bool IsMatchingType(FProperty* PropType) const override;` — filter for provider's properties
- L92 _public prototype_ `bool Serialize(FArchive& Ar);` — Implementing Serialize to convert UClass to FFieldClass

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FAIDataProviderTypedValue> : public TStructOpsTypeTraitsBase2<FAIDataProviderTypedValue>`  
_L96-102_
- inherits: `TStructOpsTypeTraitsBase2<FAIDataProviderTypedValue>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L99-101_

#### struct `FAIDataProviderStructValue`  
`struct FAIDataProviderStructValue : public FAIDataProviderValue`  
_L105-113_
- reflection: `USTRUCT()`
- inherits: `FAIDataProviderValue`
- L110 _public member_ `FString StructName;` — name of UStruct type
- L112 _public prototype_ `virtual bool IsMatchingType(FProperty* PropType) const override;`

#### struct `FAIDataProviderIntValue`  
`struct FAIDataProviderIntValue : public FAIDataProviderTypedValue`  
_L116-126_
- reflection: `USTRUCT()`
- inherits: `FAIDataProviderTypedValue`
- L119 _public prototype_ `FAIDataProviderIntValue();`
- L122 _public member_ `int32 DefaultValue;` — `UPROPERTY(EditAnywhere, Category = Value)`
- L124 _public prototype_ `int32 GetValue() const;`
- L125 _public prototype_ `virtual FString ValueToString() const override;`

#### struct `FAIDataProviderFloatValue`  
`struct FAIDataProviderFloatValue : public FAIDataProviderTypedValue`  
_L129-139_
- reflection: `USTRUCT()`
- inherits: `FAIDataProviderTypedValue`
- L132 _public prototype_ `FAIDataProviderFloatValue();`
- L135 _public member_ `float DefaultValue;` — `UPROPERTY(EditAnywhere, Category = Value)`
- L137 _public prototype_ `float GetValue() const;`
- L138 _public prototype_ `virtual FString ValueToString() const override;`

#### struct `FAIDataProviderBoolValue`  
`struct FAIDataProviderBoolValue : public FAIDataProviderTypedValue`  
_L142-152_
- reflection: `USTRUCT()`
- inherits: `FAIDataProviderTypedValue`
- L145 _public prototype_ `FAIDataProviderBoolValue();`
- L148 _public member_ `bool DefaultValue;` — `UPROPERTY(EditAnywhere, Category = Value)`
- L150 _public prototype_ `bool GetValue() const;`
- L151 _public prototype_ `virtual FString ValueToString() const override;`

#### class `UAIDataProvider`  
`class UAIDataProvider : public UObject`  
_L155-161_
- reflection: `UCLASS(EditInlineNew, Abstract, CollapseCategories, AutoExpandCategories=(Provider), MinimalAPI)`
- inherits: `UObject`
- L159 _private prototype_ `virtual void BindData(const UObject& Owner, int32 RequestId);`
- L160 _private prototype_ `virtual FString ToString(FName PropName) const;`

#### Free symbols / members of external scopes

- L100 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anon920b13310103`)

### `Source/Runtime/AIModule/Classes/DataProviders/AIDataProvider_QueryParams.h` (Public)


#### class `UAIDataProvider_QueryParams`  
`class UAIDataProvider_QueryParams : public UAIDataProvider`  
_L19-39_
- reflection: `UCLASS(EditInlineNew, meta=(DisplayName="Query Params"), MinimalAPI)`
- inherits: `UAIDataProvider`
- L24 _public prototype_ `virtual void BindData(const UObject& Owner, int32 RequestId) override;`
- L25 _public prototype_ `virtual FString ToString(FName PropName) const override;`
- L29 _public member_ `FName ParamName;` — `UPROPERTY(EditAnywhere, Category = Provider)` — Arbitrary name this query parameter will be exposed as to outside world (like BT nodes)
- L32 _public member_ `float FloatValue;` — `UPROPERTY()`
- L35 _public member_ `int32 IntValue;` — `UPROPERTY()`
- L38 _public member_ `bool BoolValue;` — `UPROPERTY()`

### `Source/Runtime/AIModule/Classes/DataProviders/AIDataProvider_Random.h` (Public)


#### class `UAIDataProvider_Random`  
`class UAIDataProvider_Random : public UAIDataProvider_QueryParams`  
_L9-28_
- reflection: `UCLASS(EditInlineNew, meta = (DisplayName = "Random number"))`
- inherits: `UAIDataProvider_QueryParams`
- L15 _protected member_ `float Min;` — `UPROPERTY(EditAnywhere, Category = AI)`
- L18 _protected member_ `float Max;` — `UPROPERTY(EditAnywhere, Category = AI)`
- L21 _protected member_ `uint8 bInteger : 1;` — `UPROPERTY(EditAnywhere, Category = AI)`
- L24 _public prototype_ `UAIDataProvider_Random(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L26 _public prototype_ `virtual void BindData(const UObject& Owner, int32 RequestId) override;`
- L27 _public prototype_ `virtual FString ToString(FName PropName) const override;`

### `Source/Runtime/AIModule/Classes/DetourCrowdAIController.h` (Public)


#### class `ADetourCrowdAIController`  
`class ADetourCrowdAIController : public AAIController`  
_L14-19_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `AAIController`
- L18 _public prototype_ `ADetourCrowdAIController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API AIMODULE_API`

### `Source/Runtime/AIModule/Classes/EnvironmentQuery/Contexts/EnvQueryContext_BlueprintBase.h` (Public)


#### class `UEnvQueryContext_BlueprintBase`  
`class UEnvQueryContext_BlueprintBase : public UEnvQueryContext`  
_L15-46_
- reflection: `UCLASS(MinimalAPI, Abstract, Blueprintable)`
- inherits: `UEnvQueryContext`
- L28 _private member_ `ECallMode CallMode;`
- L31 _private prototype_ `virtual UWorld* GetWorld() const override;` — We need to implement GetWorld() so that blueprint functions which use a hidden WorldContextObject* will work properly.
- L33 _private prototype_ `virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;`
- L36 _private prototype_ `void ProvideSingleActor(UObject* QuerierObject, AActor* QuerierActor, AActor*& ResultingActor) const;` — `UFUNCTION(BlueprintImplementableEvent)`
- L39 _private prototype_ `void ProvideSingleLocation(UObject* QuerierObject, AActor* QuerierActor, FVector& ResultingLocation) const;` — `UFUNCTION(BlueprintImplementableEvent)`
- L42 _private prototype_ `void ProvideActorsSet(UObject* QuerierObject, AActor* QuerierActor, TArray<AActor*>& ResultingActorsSet) const;` — `UFUNCTION(BlueprintImplementableEvent)`
- L45 _private prototype_ `void ProvideLocationsSet(UObject* QuerierObject, AActor* QuerierActor, TArray<FVector>& ResultingLocationSet) const;` — `UFUNCTION(BlueprintImplementableEvent)`

#### enum `UEnvQueryContext_BlueprintBase::ECallMode`  
`enum ECallMode`  
_L19-26_
- L21 _public enumerator_ `InvalidCallMode`
- L22 _public enumerator_ `SingleActor`
- L23 _public enumerator_ `SingleLocation`
- L24 _public enumerator_ `ActorSet`
- L25 _public enumerator_ `LocationSet`

### `Source/Runtime/AIModule/Classes/EnvironmentQuery/Contexts/EnvQueryContext_Item.h` (Public)


#### class `UEnvQueryContext_Item`  
`class UEnvQueryContext_Item : public UEnvQueryContext`  
_L11-14_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEnvQueryContext`

### `Source/Runtime/AIModule/Classes/EnvironmentQuery/Contexts/EnvQueryContext_NavigationData.h` (Public)


#### class `UEnvQueryContext_NavigationData`  
`class UEnvQueryContext_NavigationData : public UEnvQueryContext`  
_L15-27_
- reflection: `UCLASS(MinimalAPI, Abstract, Blueprintable)`
- inherits: `UEnvQueryContext`
- L20 _private prototype_ `virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;` — Return the NavigationData setup in NavAgentProperties
- L26 _protected member_ `FNavAgentProperties NavAgentProperties;` — `UPROPERTY(EditDefaultsOnly, Category = "NavigationData")` — NavAgentProperties used to find a NavigationData Override

### `Source/Runtime/AIModule/Classes/EnvironmentQuery/Contexts/EnvQueryContext_Querier.h` (Public)


#### class `UEnvQueryContext_Querier`  
`class UEnvQueryContext_Querier : public UEnvQueryContext`  
_L14-19_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEnvQueryContext`
- L18 _private prototype_ `virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;`

### `Source/Runtime/AIModule/Classes/EnvironmentQuery/EQSQueryResultSourceInterface.h` (Public)


#### class `UEQSQueryResultSourceInterface`  
`class UEQSQueryResultSourceInterface : public UInterface`  
_L11-14_
- reflection: `UINTERFACE(MinimalAPI, meta=(CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`

#### class `IEQSQueryResultSourceInterface`  
`class IEQSQueryResultSourceInterface`  
_L16-27_
- L20 _private function_ `virtual const struct FEnvQueryResult* GetQueryResult() const`
- L21 _private function_ `virtual const struct FEnvQueryInstance* GetQueryInstance() const`
- L24 _private function_ `virtual bool GetShouldDebugDrawLabels() const` — debugging
- L25 _private function_ `virtual bool GetShouldDrawFailedItems() const`
- L26 _private function_ `virtual float GetHighlightRangePct() const`

### `Source/Runtime/AIModule/Classes/EnvironmentQuery/EQSRenderingComponent.h` (Public)


#### class `FEQSSceneProxy`  
`class FEQSSceneProxy final : public FDebugRenderSceneProxy`  
_L17-41_
- inherits: `FDebugRenderSceneProxy`
- L21 _public prototype_ `virtual SIZE_T GetTypeHash() const override;`
- L23 _public prototype_ `explicit FEQSSceneProxy(const UPrimitiveComponent& InComponent, const FString& ViewFlagName = TEXT("DebugAI"), const TArray<FSphere>& Spheres = TArray<FSphere>(), const TArray<FText3d>& Texts = TArray<FText`
- L25 _public prototype_ `virtual FPrimitiveViewRelevance GetViewRelevance(const FSceneView* View) const override;`
- L28 _public prototype_ `static void CollectEQSData(const UPrimitiveComponent* InComponent, const IEQSQueryResultSourceInterface* QueryDataSource, TArray<FSphere>& Spheres, TArray<FText3d>& Texts, TArray<EQSDebug::FDebugHelper>& DebugItems);`
- L29 _public prototype_ `static void CollectEQSData(const FEnvQueryResult* ResultItems, const FEnvQueryInstance* QueryInstance, float HighlightRangePct, bool ShouldDrawFailedItems, TArray<FSphere>& Spheres, TArray<FText3d>& Texts, TArray<EQSDebug::FDebugHelper>& DebugItems);`
- L32 _private member_ `FEnvQueryResult QueryResult;`
- L34 _private member_ `AActor* ActorOwner;` — can be 0
- L35 _private member_ `const IEQSQueryResultSourceInterface* QueryDataSource;`
- L36 _private member_ `uint32 bDrawOnlyWhenSelected : 1;`
- L38 _private member_ `static const FVector3f ItemDrawRadius;`
- L40 _private prototype_ `bool SafeIsActorSelected() const;`

#### class `FEQSRenderingDebugDrawDelegateHelper`  
`class FEQSRenderingDebugDrawDelegateHelper : public FDebugDrawDelegateHelper`  
_L44-76_
- inherits: `FDebugDrawDelegateHelper`
- L46 _private typedef_ `typedef FDebugDrawDelegateHelper Super;`
- L49 _public function_ `FEQSRenderingDebugDrawDelegateHelper() : ActorOwner(nullptr) , QueryDataSource(nullptr) , bDrawOnlyWhenSelected(false)`
- L56 _public function_ `void SetupFromProxy(const FEQSSceneProxy* InSceneProxy)`
- L63 _public function_ `void Reset()`
- L69 _protected prototype_ `virtual void DrawDebugLabels(UCanvas* Canvas, APlayerController*) override;`
- L73 _private member_ `AActor* ActorOwner;` — can be 0
- L74 _private member_ `const IEQSQueryResultSourceInterface* QueryDataSource;`
- L75 _private member_ `uint32 bDrawOnlyWhenSelected : 1;`

#### class `UEQSRenderingComponent`  
`class UEQSRenderingComponent : public UDebugDrawComponent`  
_L80-104_
- reflection: `UCLASS(ClassGroup = Debug, MinimalAPI)`
- inherits: `UDebugDrawComponent`
- L84 _private member_ `FString DrawFlagName;`
- L85 _private member_ `uint32 bDrawOnlyWhenSelected : 1;`
- L87 _private prototype_ `void ClearStoredDebugData();`
- L89 _private prototype_ `void StoreDebugData(const EQSDebug::FQueryData& DebugData);`
- L93 _protected prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform &LocalToWorld) const override;`
- L96 _protected prototype_ `virtual FDebugRenderSceneProxy* CreateDebugSceneProxy() override;`
- L97 _protected function_ `virtual FDebugDrawDelegateHelper& GetDebugDrawDelegateHelper() override`
- L98 _protected member_ `FEQSRenderingDebugDrawDelegateHelper EQSRenderingDebugDrawDelegateHelper;`
- L102 _protected member_ `TArray<FDebugRenderSceneProxy::FSphere> DebugDataSolidSpheres;` — EQSDebug::FQueryData DebugData;
- L103 _protected member_ `TArray<FDebugRenderSceneProxy::FText3d> DebugDataTexts;`

### `Source/Runtime/AIModule/Classes/EnvironmentQuery/EQSTestingPawn.h` (Public)


#### enum `EEnvQueryHightlightMode`  
`enum class EEnvQueryHightlightMode : uint8`  
_L17-22_
- reflection: `UENUM()`
- L19 _public enumerator_ `All`
- L20 _public enumerator_ `Best5Pct UMETA(DisplayName = "Best 5%")`
- L21 _public enumerator_ `Best25Pct UMETA(DisplayName = "Best 25%")`

#### class `AEQSTestingPawn`  
`class AEQSTestingPawn : public ACharacter, public IEQSQueryResultSourceInterface`  
_L25-132_
- reflection: `UCLASS(hidedropdown, hidecategories=(Advanced, Attachment, Mesh, Animation, Clothing, Physics, Rendering, Lighting, Activation, CharacterMovement, AgentPhysics, Avoidance, MovementComponent, Velocity, Shape, Camera, Input, Layers, SkeletalMesh, Optimization, Pawn, Replication, Actor), MinimalAPI)`
- inherits: `ACharacter,IEQSQueryResultSourceInterface`
- L30 _private member_ `TObjectPtr<UEnvQuery> QueryTemplate;` — `UPROPERTY(Category=EQS, EditAnywhere)`
- L35 _private member_ `TArray<FEnvNamedValue> QueryParams;` — `UE_DEPRECATED_FORGAME(5.0, "QueryParams has been deprecated for a long while now. Will be removed in the next engine version.")` — `UPROPERTY()` — optional parameters for query
- L38 _private member_ `TArray<FAIDynamicParam> QueryConfig;` — `UPROPERTY(Category=EQS, EditAnywhere)`
- L41 _private member_ `float TimeLimitPerStep;` — `UPROPERTY(Category=EQS, EditAnywhere)`
- L44 _private member_ `int32 StepToDebugDraw;` — `UPROPERTY(Category=EQS, EditAnywhere)`
- L47 _private member_ `EEnvQueryHightlightMode HighlightMode;` — `UPROPERTY(Category = EQS, EditAnywhere)`
- L50 _private member_ `uint32 bDrawLabels:1;` — `UPROPERTY(Category = EQS, EditAnywhere)`
- L53 _private member_ `uint32 bDrawFailedItems:1;` — `UPROPERTY(Category=EQS, EditAnywhere)`
- L56 _private member_ `uint32 bReRunQueryOnlyOnFinishedMove:1;` — `UPROPERTY(Category=EQS, EditAnywhere)`
- L59 _private member_ `uint32 bShouldBeVisibleInGame:1;` — `UPROPERTY(Category=EQS, EditAnywhere)`
- L62 _private member_ `uint32 bTickDuringGame : 1;` — `UPROPERTY(Category = EQS, EditAnywhere)`
- L65 _private member_ `uint32 bRunQueryOnSelectionChanged : 1;` — `UPROPERTY(Category = EQS, EditAnywhere)`
- L68 _private member_ `TEnumAsByte<EEnvQueryRunMode::Type> QueryingMode;` — `UPROPERTY(Category=EQS, EditAnywhere)`
- L71 _private member_ `FNavAgentProperties NavAgentProperties;` — `UPROPERTY(Category = EQS, EditAnywhere)`
- L77 _private member_ `TObjectPtr<UEQSRenderingComponent> EdRenderComp;` — `UPROPERTY(Transient)` — Editor Preview
- L81 _protected member_ `TSharedPtr<FEnvQueryInstance> QueryInstance;`
- L84 _protected member_ `TArray<FEnvQueryInstance> StepResults;` — `UPROPERTY(Transient)`
- L88 _public prototype_ `virtual void TickActor( float DeltaTime, enum ELevelTick TickType, FActorTickFunction& ThisTickFunction ) override;` — This pawn class spawns its controller in PostInitProperties to have it available in editor mode
- L89 _public prototype_ `virtual void PostLoad() override;`
- L92 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L93 _public prototype_ `virtual void PostEditMove(bool bFinished) override;`
- L94 _public prototype_ `virtual void PostTransacted(const FTransactionObjectEvent& TransactionEvent) override;`
- L95 _public prototype_ `void OnPropertyChanged(const FName PropName);`
- L99 _public prototype_ `static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);`
- L103 _public prototype_ `virtual const FEnvQueryResult* GetQueryResult() const override;` — IEQSQueryResultSourceInterface start
- L104 _public prototype_ `virtual const FEnvQueryInstance* GetQueryInstance() const override;`
- L106 _public function_ `virtual bool GetShouldDebugDrawLabels() const override`
- L107 _public function_ `virtual bool GetShouldDrawFailedItems() const override`
- L108 _public prototype_ `virtual float GetHighlightRangePct() const override;`
- L112 _public prototype_ `virtual const FNavAgentProperties& GetNavAgentPropertiesRef() const override;` — INavAgentInterface begin
- L115 _public prototype_ `void RunEQSQuery();`
- L118 _protected prototype_ `void Reset() override;`
- L119 _protected prototype_ `void MakeOneStep();`
- L121 _protected prototype_ `void UpdateDrawing();`
- L124 _protected prototype_ `static void OnEditorSelectionChanged(UObject* NewSelection);`
- L130 _public function_ `UEQSRenderingComponent* GetEdRenderComp()` — Returns EdRenderComp subobject

### `Source/Runtime/AIModule/Classes/EnvironmentQuery/EnvQuery.h` (Public)


#### class `UEnvQuery`  
`class UEnvQuery : public UDataAsset`  
_L19-68_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UDataAsset`
- L26 _private member_ `TObjectPtr<UEdGraph> EdGraph;` — `UPROPERTY()` — Graph for query
- L33 _protected member_ `FName QueryName;` — `UPROPERTY()`
- L36 _protected member_ `TArray<TObjectPtr<UEnvQueryOption>> Options;` — `UPROPERTY()`
- L41 _public member_ `uint8 bStripFromClientBuilds : 1 = false;` — `UPROPERTY(EditAnywhere, Category=Query)` — Set to true to not cook this query into client builds. Useful for server-only AI queries.
- L44 _public prototype_ `void CollectQueryParams(UObject& QueryOwner, TArray<FAIDynamicParam>& NamedValues) const;` — Gather all required named params
- L46 _public prototype_ `virtual void PostInitProperties() override;`
- L49 _public prototype_ `virtual void PostLoad() override;` — QueryName patching up
- L51 _public prototype_ `virtual void PostRename(UObject* OldOuter, const FName OldName) override;`
- L52 _public prototype_ `virtual void PostDuplicate(bool bDuplicateForPIE) override;`
- L55 _public function_ `virtual bool NeedsLoadForClient() const override`
- L59 _public function_ `virtual bool NeedsLoadForEditorGame() const override`
- L64 _public function_ `FName GetQueryName() const`
- L66 _public function_ `TArray<TObjectPtr<UEnvQueryOption>>& GetOptionsMutable()`
- L67 _public function_ `const TArray<UEnvQueryOption*>& GetOptions() const`

### `Source/Runtime/AIModule/Classes/EnvironmentQuery/EnvQueryContext.h` (Public)


#### class `UEnvQueryContext`  
`class UEnvQueryContext : public UObject`  
_L14-19_
- reflection: `UCLASS(Abstract, EditInlineNew, MinimalAPI)`
- inherits: `UObject`
- L18 _private prototype_ `virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const;`

### `Source/Runtime/AIModule/Classes/EnvironmentQuery/EnvQueryDebugHelpers.h` (Public)


#### struct `EQSDebug::FItemData`  
`struct FItemData`  
_L24-32_
- L26 _public member_ `FString Desc;`
- L27 _public member_ `int32 ItemIdx;`
- L28 _public member_ `float TotalScore;`
- L30 _public member_ `TArray<float> TestValues;`
- L31 _public member_ `TArray<float> TestScores;`

#### struct `EQSDebug::FTestData`  
`struct FTestData`  
_L34-38_
- L36 _public member_ `FString ShortName;`
- L37 _public member_ `FString Detailed;`

#### struct `EQSDebug::FDebugHelper`  
`struct FDebugHelper`  
_L41-52_
- desc: struct filled while collecting data (to store additional debug data needed to display per rendered item)
- L43 _public function_ `FDebugHelper() : Location(FVector::ZeroVector), Radius(0), FailedTestIndex(INDEX_NONE)`
- L44 _public function_ `FDebugHelper(FVector Loc, float R) : Location(Loc), Radius(R), FailedTestIndex(INDEX_NONE)`
- L45 _public function_ `FDebugHelper(FVector Loc, float R, const FString& Desc) : Location(Loc), Radius(R), FailedTestIndex(INDEX_NONE), AdditionalInformation(Desc)`
- L47 _public member_ `FVector Location;`
- L48 _public member_ `float Radius;`
- L49 _public member_ `int32 FailedTestIndex;`
- L50 _public member_ `float FailedScore;`
- L51 _public member_ `FString AdditionalInformation;`

#### struct `EQSDebug::FQueryData`  
`struct FQueryData`  
_L54-82_
- L56 _public member_ `TArray<FItemData> Items;`
- L57 _public member_ `TArray<FTestData> Tests;`
- L58 _public member_ `TArray<FDebugRenderSceneProxy::FSphere> SolidSpheres;`
- L59 _public member_ `TArray<FDebugRenderSceneProxy::FText3d> Texts;`
- L60 _public member_ `TArray<FDebugHelper> RenderDebugHelpers;`
- L61 _public member_ `TArray<FString> Options;`
- L62 _public member_ `int32 UsedOption;`
- L63 _public member_ `int32 NumValidItems;`
- L64 _public member_ `int32 Id;`
- L65 _public member_ `FString Name;`
- L66 _public member_ `double Timestamp;`
- L68 _public function_ `void Reset()`

#### class `UEnvQueryDebugHelpers`  
`class UEnvQueryDebugHelpers : public UObject`  
_L158-176_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UObject`
- L163 _public prototype_ `static void QueryToDebugData(FEnvQueryInstance& Query, EQSDebug::FQueryData& EQSLocalData, int32 MaxItemsToStore = 10);`
- L164 _public prototype_ `static void QueryToBlobArray(FEnvQueryInstance& Query, TArray<uint8>& BlobArray, bool bUseCompression = false);`
- L165 _public prototype_ `static void DebugDataToBlobArray(EQSDebug::FQueryData& QueryData, TArray<uint8>& BlobArray, bool bUseCompression = false);`
- L166 _public prototype_ `static void BlobArrayToDebugData(const TArray<uint8>& BlobArray, EQSDebug::FQueryData& EQSLocalData, bool bUseCompression = false);`
- L170 _public prototype_ `static void LogQuery(FEnvQueryInstance& Query, const FLogCategoryBase& Category, ELogVerbosity::Type Verbosity);`
- L171 _public prototype_ `static void LogQuery(FEnvQueryInstance& Query, const FName& CategoryName, ELogVerbosity::Type Verbosity);`
- L174 _private prototype_ `static void LogQueryInternal(FEnvQueryInstance& Query, const FName& CategoryName, ELogVerbosity::Type Verbosity, double TimeSeconds, FVisualLogEntry *CurrentEntry);`
- L179 _function_ `inline void UEnvQueryDebugHelpers::LogQuery(FEnvQueryInstance& Query, const FLogCategoryBase& Category, ELogVerbosity::Type Verbosity)`
- L185 _function_ `inline void UEnvQueryDebugHelpers::LogQuery(FEnvQueryInstance& Query, const FName& CategoryName, ELogVerbosity::Type Verbosity)`

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace EQSDebug`
- L86 _function_ `FArchive& operator<<(FArchive& Ar, FDebugRenderSceneProxy::FSphere& Data)`
- L95 _function_ `FArchive& operator<<(FArchive& Ar, FDebugRenderSceneProxy::FText3d& Data)`
- L104 _function_ `FArchive& operator<<(FArchive& Ar, EQSDebug::FItemData& Data)`
- L115 _function_ `FArchive& operator<<(FArchive& Ar, EQSDebug::FTestData& Data)`
- L123 _function_ `FArchive& operator<<(FArchive& Ar, EQSDebug::FDebugHelper& Data)`
- L133 _function_ `FArchive& operator<<(FArchive& Ar, EQSDebug::FQueryData& Data)`
- L152 _macro_ `# define UE_VLOG_EQS(Query, Category, Verbosity) UEnvQueryDebugHelpers::LogQuery(Query, Category, ELogVerbosity::Verbosity);`
- L154 _macro_ `# define UE_VLOG_EQS(Query, CategoryName, Verbosity)`

### `Source/Runtime/AIModule/Classes/EnvironmentQuery/EnvQueryGenerator.h` (Public)


#### class `UEnvQueryGenerator`  
`class UEnvQueryGenerator : public UEnvQueryNode`  
_L22-57_
- reflection: `UCLASS(EditInlineNew, Abstract, meta = (Category = "Generators"), MinimalAPI)`
- inherits: `UEnvQueryNode`
- L27 _private member_ `FString OptionName;` — `UPROPERTY(EditDefaultsOnly, Category=Option)`
- L31 _private member_ `TSubclassOf<UEnvQueryItemType> ItemType;` — `UPROPERTY()` — type of generated items
- L35 _private member_ `uint32 bAutoSortTests : 1;` — `UPROPERTY(EditDefaultsOnly, Category = Option, AdvancedDisplay)` — if set, tests will be automatically sorted for best performance before running query
- L37 _private function_ `virtual void GenerateItems(FEnvQueryInstance& QueryInstance) const`
- L38 _private function_ `virtual bool IsValidGenerator() const`
- L39 _private function_ `bool CanRunAsync() const`
- L40 _private prototype_ `EEnvQueryResultNormalizationOption GetNormalizationOption() const;`
- L42 _private prototype_ `virtual void PostLoad() override;`
- L43 _private prototype_ `void UpdateNodeVersion() override;`
- L48 _protected member_ `uint32 bCanRunAsync : 1;` — `UPROPERTY(EditDefaultsOnly, Category = Option, AdvancedDisplay)` — To be overwritten by MassEnvQueryGenerators to indicate that they will run asynchronously.
- L56 _protected member_ `EEnvQueryResultNormalizationOption EnvQueryResultNormalizationOption = EEnvQueryResultNormalizationOption::Default;` — `UPROPERTY(EditDefaultsOnly, Category = Option, AdvancedDisplay)` — Should the scores be normalized or not before returning the result. If set to UEnvQueryResultNormalizationOption::Default, only runmode EEnvQueryRunMode::AllMatching is normalized and the other modes are not If set to UEnvQueryResultNormalizationOption::Normalized, all run modes will be normalized. If set to UEnvQueryResultNormalizationOption::Unaltered, all run modes will NOT be normalized.

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace EnvQueryGeneratorVersion`
- L15 _variable_ `inline const int32 Initial = 0;` (scope `EnvQueryGeneratorVersion`)
- L16 _variable_ `inline const int32 DataProviders = 1;` (scope `EnvQueryGeneratorVersion`)
- L18 _variable_ `inline const int32 Latest = DataProviders;` (scope `EnvQueryGeneratorVersion`)

### `Source/Runtime/AIModule/Classes/EnvironmentQuery/EnvQueryInstanceBlueprintWrapper.h` (Public)


#### class `UEnvQueryInstanceBlueprintWrapper`  
`class UEnvQueryInstanceBlueprintWrapper : public UObject, public IEQSQueryResultSourceInterface`  
_L19-95_
- reflection: `UCLASS(Blueprintable, BlueprintType, meta = (DisplayName = "EQS Query Instance"), MinimalAPI)`
- inherits: `UObject,IEQSQueryResultSourceInterface`
- L24 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FEQSQueryDoneSignature, UEnvQueryInstanceBlueprintWrapper*, QueryInstance, EEnvQueryStatus::Type, QueryStatus);`
- L27 _public function_ `virtual const FEnvQueryResult* GetQueryResult() const` — IEQSQueryResultSourceInterface function. Returns the Query Result.
- L30 _public function_ `virtual const FEnvQueryInstance* GetQueryInstance() const` — IEQSQueryResultSourceInterface function. Returns the Query Instance.
- L34 _protected member_ `int32 QueryID;` — `UPROPERTY(BlueprintReadOnly, Category = "EQS")`
- L36 _protected member_ `EEnvQueryRunMode::Type RunMode;`
- L38 _protected member_ `TSharedPtr<FEnvQueryResult> QueryResult;`
- L39 _protected member_ `TSharedPtr<FEnvQueryInstance> QueryInstance;`
- L42 _protected member_ `TSubclassOf<UEnvQueryItemType> ItemType;` — `UPROPERTY(BlueprintReadOnly, Category = "EQS")`
- L46 _protected member_ `int32 OptionIndex;` — `UPROPERTY(BlueprintReadOnly, Category = "EQS")` — index of query option, that generated items
- L49 _protected member_ `FEQSQueryDoneSignature OnQueryFinishedEvent;` — `UPROPERTY(BlueprintAssignable, Category = "AI|EQS", meta = (DisplayName = "OnQueryFinished"))`
- L52 _protected member_ `FWeakObjectPtr Instigator;`
- L56 _public prototype_ `UEnvQueryInstanceBlueprintWrapper(const FObjectInitializer& ObjectInitializer);`
- L58 _public prototype_ `void RunQuery(const EEnvQueryRunMode::Type InRunMode, FEnvQueryRequest& QueryRequest);`
- L61 _public prototype_ `float GetItemScore(int32 ItemIndex) const;` — `UFUNCTION(BlueprintPure, Category = "AI|EQS")`
- L65 _public prototype_ `bool GetQueryResultsAsActors(TArray<AActor*>& ResultActors) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = "AI|EQS")` — Outputs an array filled with resulting actors.  Note that it makes sense only if ItemType is a EnvQueryItemType_ActorBase-derived type.  Returns false if there is no valid result.
- L69 _public prototype_ `bool GetQueryResultsAsLocations(TArray<FVector>& ResultLocations) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = "AI|EQS")` — Outputs an array of locations generated by the query. If the query generated Actors the the array is filled with their locations.  Returns false if there is no valid result.
- L74 _public prototype_ `TArray<AActor*> GetResultsAsActors() const;` — `UFUNCTION(BlueprintPure, Category = "AI|EQS", Meta=(DeprecatedFunction, DeprecationMessage="Use GetQueryResultsAsActors instead, which is more efficient itself and protects against very bad perf issues in some blueprints."))` — DEPRECATED!  Use GetQueryResultsAsActors instead.  Returns an array filled with resulting actors. Note that it makes sense only if ItemType is a EnvQueryItemType_ActorBase-derived type.
- L79 _public prototype_ `TArray<FVector> GetResultsAsLocations() const;` — `UFUNCTION(BlueprintPure, Category = "AI|EQS", Meta=(DeprecatedFunction, DeprecationMessage="GetQueryResultsAsLocations instead, which is more efficient itself and protects against very bad perf issues in some blueprints."))` — DEPRECATED!  Use GetQueryResultsAsLocations instead.  Returns an array of locations generated by the query. If the query generated Actors the the array is filled with their locations.
- L82 _public prototype_ `void SetNamedParam(FName ParamName, float Value);` — `UFUNCTION(BlueprintCallable, Category = "AI|EQS")`
- L84 _public prototype_ `void SetInstigator(const UObject* Object);`
- L87 _public function_ `inline EEnvQueryRunMode::Type GetRunMode() const` — Used in UMassEQSBlueprintLibrary::GetEnviromentQueryResultAsEntityInfo
- L89 _public function_ `FEQSQueryDoneSignature& GetOnQueryFinishedEvent()`
- L92 _protected prototype_ `void OnQueryFinished(TSharedPtr<FEnvQueryResult> Result);`
- L94 _protected prototype_ `virtual bool IsSupportedForNetworking() const override;`

#### Free symbols / members of external scopes

- L24 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FEQSQueryDoneSignature, UEnvQueryInstanceBlueprintWrapper*, QueryInstance, EEnvQueryStatus::Type, QueryStatus);`

### `Source/Runtime/AIModule/Classes/EnvironmentQuery/EnvQueryManager.h` (Public)


#### struct `FEnvQueryManagerConfig`  
`struct FEnvQueryManagerConfig`  
_L28-66_
- reflection: `USTRUCT()`
- desc: Wrapper to hold config variables
- L36 _public member_ `float MaxAllowedTestingTime = 0.003f;` — `UPROPERTY(config)` — how long are we allowed to test per update, in seconds.
- L42 _public member_ `bool bTestQueriesUsingBreadth = false;` — `UPROPERTY(config)` — whether we update EQS queries based on: running a test on one query and move to the next (breadth) - default behavior, or test an entire query before moving to the next one (depth).
- L46 _public member_ `int32 QueryCountWarningThreshold = 200;` — `UPROPERTY(config)` — if greater than zero, we will warn once when the number of queries is greater than or equal to this number, and log the queries out
- L50 _public member_ `double QueryCountWarningInterval = 60.0f;` — `UPROPERTY(config)` — how often (in seconds) we will warn about the number of queries (allows us to catch multiple occurrences in a session)
- L54 _public member_ `double ExecutionTimeWarningSeconds = 0.025f;` — `UPROPERTY(config)` — Maximum EQS execution duration (in seconds) before a warning is reported.
- L58 _public member_ `double HandlingResultTimeWarningSeconds = 0.025f;` — `UPROPERTY(config)` — Maximum EQS Query FinishDelegate duration (in seconds) before a warning is reported.
- L62 _public member_ `double GenerationTimeWarningSeconds = 0.01f;` — `UPROPERTY(config)` — Maximum EQS Generator duration (in seconds) before a warning is reported.
- L65 _public prototype_ `FString ToString() const;`

#### struct `FEnvQueryRequest`  
`struct FEnvQueryRequest`  
_L70-126_
- reflection: `USTRUCT()`
- desc: wrapper for easy query execution
- L74 _public function_ `FEnvQueryRequest() : QueryTemplate(NULL), Owner(NULL), World(NULL)`
- L77 _public function_ `FEnvQueryRequest(const UEnvQuery* Query) : QueryTemplate(Query), Owner(NULL), World(NULL)` — basic constructor: owner will be taken from finish delegate bindings
- L80 _public function_ `FEnvQueryRequest(const UEnvQuery* Query, UObject* RequestOwner) : QueryTemplate(Query), Owner(RequestOwner), World(NULL)` — use when owner is different from finish delegate binding
- L84 _public prototype_ `FEnvQueryRequest& SetDynamicParam(const FAIDynamicParam& Param, const UBlackboardComponent* BlackboardComponent = nullptr);` — set names param indicated by Param. If Param is configured to read values from a blackboard then BlackboardComponent is expected to be non-null (the function will fail a check otherwise).
- L87 _public function_ `inline FEnvQueryRequest& SetFloatParam(FName ParamName, float Value)` — set named params
- L88 _public function_ `inline FEnvQueryRequest& SetIntParam(FName ParamName, int32 Value)`
- L89 _public function_ `inline FEnvQueryRequest& SetBoolParam(FName ParamName, bool Value)`
- L90 _public function_ `inline FEnvQueryRequest& SetNamedParam(const FEnvNamedValue& ParamData)`
- L91 _public prototype_ `FEnvQueryRequest& SetNamedParams(const TArray<FEnvNamedValue>& Params);`
- L94 _public function_ `inline FEnvQueryRequest& SetWorldOverride(UWorld* InWorld)` — set world (for accessing query manager) when owner can't provide it
- L97 _public function_ `template< class UserClass > inline int32 Execute(EEnvQueryRunMode::Type Mode, UserClass* InObj, typename FQueryFinishedSignature::TMethodPtr< UserClass > InMethod)`
- L102 _public function_ `template< class UserClass > inline int32 Execute(EEnvQueryRunMode::Type Mode, UserClass* InObj, typename FQueryFinishedSignature::TConstMethodPtr< UserClass > InMethod)`
- L106 _public prototype_ `int32 Execute(EEnvQueryRunMode::Type RunMode, FQueryFinishedSignature const& FinishDelegate);`
- L112 _protected member_ `TObjectPtr<const UEnvQuery> QueryTemplate;` — `UPROPERTY()` — query to run
- L116 _protected member_ `TObjectPtr<UObject> Owner;` — `UPROPERTY()` — querier
- L120 _protected member_ `TObjectPtr<UWorld> World;` — `UPROPERTY()` — world
- L123 _protected member_ `TMap<FName, float> NamedParams;` — list of named params

#### struct `FEnvQueryInstanceCache`  
`struct FEnvQueryInstanceCache`  
_L130-144_
- reflection: `USTRUCT()`
- desc: cache of instances with sorted tests
- L136 _public member_ `TObjectPtr<UEnvQuery> Template = nullptr;` — `UPROPERTY()` — query template, duplicated in manager's world
- L140 _public member_ `FEnvQueryInstance Instance;` — `UPROPERTY(Transient)` — instance to duplicate
- L143 _public member_ `FName AssetName;` — the name of the source query

#### struct `FEQSDebugger`  
`struct FEQSDebugger`  
_L147-196_
- L181 _public prototype_ `void StoreStats(const FEnvQueryInstance& QueryInstance);`
- L182 _public prototype_ `void StoreTickTime(const FEnvQueryInstance& QueryInstance, double TickTime, double MaxTickTime);`
- L183 _public prototype_ `void StoreQuery(const TSharedPtr<FEnvQueryInstance>& QueryInstance);`
- L185 _public prototype_ `static void SaveStats(const FString& FileName);`
- L186 _public prototype_ `static void LoadStats(const FString& FileName);`
- L188 _public prototype_ `const TArray<FEnvQueryInfo>& GetAllQueriesForOwner(const UObject* Owner);`
- L191 _public member_ `TMap<FName, FStatsInfo> StoredStats;` — map query name with profiler data
- L195 _protected member_ `TMap<FObjectKey, TArray<FEnvQueryInfo>> StoredQueries;` — maps owner to performed queries

#### struct `FEQSDebugger::FEnvQueryInfo`  
`struct FEnvQueryInfo`  
_L149-153_
- L151 _public member_ `TSharedPtr<FEnvQueryInstance> Instance;`
- L152 _public member_ `double Timestamp;`

#### struct `FEQSDebugger::FStatsInfo`  
`struct FStatsInfo`  
_L155-179_
- L158 _public member_ `FEnvQueryDebugProfileData MostExpensive;` — most expensive run
- L159 _public member_ `double MostExpensiveDuration;`
- L162 _public member_ `FEnvQueryDebugProfileData TotalAvgData;` — average run (sum of all runs, divide by TotalAvgCount to get values)
- L163 _public member_ `double TotalAvgDuration;`
- L164 _public member_ `int32 TotalAvgCount;`
- L167 _public member_ `TArray<uint8> TickPct;` — EQS tick load
- L168 _public member_ `double LastTickTime;`
- L169 _public member_ `uint64 LastTickFrame;`
- L170 _public member_ `uint16 FirstTickEntry;`
- L171 _public member_ `uint16 LastTickEntry;`
- L173 _public function_ `FStatsInfo() : MostExpensiveDuration(0.0f), TotalAvgDuration(0.0f), TotalAvgCount(0), LastTickTime(0.0f), LastTickFrame(0), FirstTickEntry(MAX_uint16), LastTickEntry(0)`

#### class `UEnvQueryManager`  
`class UEnvQueryManager : public UAISubsystem, public FSelfRegisteringExec`  
_L207-389_
- reflection: `UCLASS(config = Game, defaultconfig, Transient, MinimalAPI)`
- inherits: `UAISubsystem,FSelfRegisteringExec`
- L213 _private prototype_ `virtual void PostLoad() override;` — makes sure we don't have any UEnvQueryManager instances serialized in. Any loaded instance will get marked as PendingKill
- L214 _private prototype_ `virtual void PostInitProperties() override;`
- L217 _private prototype_ `virtual void Tick(float DeltaTime) override;` — FTickableGameObject begin
- L218 _private prototype_ `virtual TStatId GetStatId() const override;`
- L219 _private function_ `virtual bool IsTickableInEditor() const override`
- L223 _private prototype_ `int32 RunQuery(const FEnvQueryRequest& Request, EEnvQueryRunMode::Type RunMode, FQueryFinishedSignature const& FinishDelegate);` — execute query
- L224 _private prototype_ `int32 RunQuery(const TSharedPtr<FEnvQueryInstance>& QueryInstance, FQueryFinishedSignature const& FinishDelegate);`
- L228 _private function_ `void SilentlyRemoveAllQueriesByQuerier(const UObject& Querier)` — Removed all active queries asked by Querier. No "on finished" notifications are being sent, call this function when you no longer care about Querier's queries, like when it's "dead"
- L233 _private prototype_ `void RemoveAllQueriesByQuerier(const UObject& Querier, bool bExecuteFinishDelegate);`
- L238 _private prototype_ `TSharedPtr<FEnvQueryResult> RunInstantQuery(const FEnvQueryRequest& Request, EEnvQueryRunMode::Type RunMode);` — alternative way to run queries. Do not use for anything other than testing or when you know exactly what you're doing! Bypasses all EQS perf controlling and time slicing mechanics.
- L239 _private prototype_ `void RunInstantQuery(const TSharedPtr<FEnvQueryInstance>& QueryInstance);`
- L242 _private prototype_ `TSharedPtr<FEnvQueryInstance> PrepareQueryInstance(const FEnvQueryRequest& Request, EEnvQueryRunMode::Type RunMode);` — Creates a query instance configured for execution
- L246 _private prototype_ `UEnvQuery* FindQueryTemplate(const FString& QueryName) const;` — finds UEnvQuery matching QueryName by first looking at instantiated queries (from InstanceCache) falling back to looking up all UEnvQuery and testing their name
- L249 _private prototype_ `UEnvQueryContext* PrepareLocalContext(TSubclassOf<UEnvQueryContext> ContextClass);` — creates local context object
- L252 _private prototype_ `float FindNamedParam(int32 QueryId, FName ParamName) const;` — find value of named param stored with active query
- L255 _private prototype_ `bool AbortQuery(int32 RequestID);` — aborts specific query
- L258 _private prototype_ `void PrintActiveQueryInfo() const;` — outputs active queries to log
- L261 _private prototype_ `virtual void OnWorldCleanup();` — fail all running queries on cleaning the world
- L264 _private prototype_ `virtual void FinishDestroy() override;` — cleanup hooks for map loading
- L267 _private prototype_ `void RegisterExternalQuery(const TSharedPtr<FEnvQueryInstance>& QueryInstance);` — add information for data providers about query instance run independently
- L270 _private prototype_ `void UnregisterExternalQuery(const TSharedPtr<FEnvQueryInstance>& QueryInstance);` — clear information about query instance run independently
- L273 _private member_ `static TArray<TSubclassOf<UEnvQueryItemType> > RegisteredItemTypes;` — list of all known item types
- L275 _private prototype_ `static UEnvQueryManager* GetCurrent(UWorld* World);`
- L276 _private prototype_ `static UEnvQueryManager* GetCurrent(const UObject* WorldContextObject);`
- L279 _private prototype_ `static UEnvQueryInstanceBlueprintWrapper* RunEQSQuery(UObject* WorldContextObject, UEnvQuery* QueryTemplate, UObject* Querier, TEnumAsByte<EEnvQueryRunMode::Type> RunMode, TSubclassOf<UEnvQueryInstanceBlueprintWrapper> WrapperClass);` — `UFUNCTION(BlueprintCallable, Category = "AI|EQS", meta = (WorldContext = "WorldContextObject", AdvancedDisplay = "WrapperClass"))`
- L281 _private prototype_ `void RegisterActiveWrapper(UEnvQueryInstanceBlueprintWrapper& Wrapper);`
- L282 _private prototype_ `void UnregisterActiveWrapper(UEnvQueryInstanceBlueprintWrapper& Wrapper);`
- L284 _private prototype_ `static void SetAllowTimeSlicing(bool bAllowTimeSlicing);`
- L287 _private prototype_ `void Configure(const FEnvQueryManagerConfig& NewConfig);` — Configure config variables during runtime
- L291 _protected prototype_ `virtual bool Exec_Dev(UWorld* Inworld,const TCHAR* Cmd,FOutputDevice& Ar) override;`
- L295 _protected prototype_ `TSharedPtr<FEnvQueryInstance> FindQueryInstance(const int32 QueryID);`
- L299 _public prototype_ `static void NotifyAssetUpdate(UEnvQuery* Query);`
- L300 _public member_ `static TMap<FName, FEQSDebugger::FStatsInfo> DebuggerStats;`
- L302 _public function_ `FEQSDebugger& GetDebugger()`
- L305 _protected member_ `FEQSDebugger EQSDebugger;`
- L311 _protected member_ `TArray<TSharedPtr<FEnvQueryInstance> > RunningQueries;` — currently running queries
- L314 _protected member_ `int32 NumRunningQueriesAbortedSinceLastUpdate;` — count of queries aborted since last update, to be removed.
- L317 _protected member_ `TMap<int32, TWeakPtr<FEnvQueryInstance>> ExternalQueries;` — queries run independently from manager, mapped here for data providers
- L321 _protected member_ `TArray<FEnvQueryInstanceCache> InstanceCache;` — `UPROPERTY(transient)` — cache of instances
- L325 _protected member_ `TArray<TObjectPtr<UEnvQueryContext>> LocalContexts;` — `UPROPERTY(transient)` — local cache of context objects for managing BP based objects
- L328 _protected member_ `TArray<TObjectPtr<UEnvQueryInstanceBlueprintWrapper>> GCShieldedWrappers;` — `UPROPERTY()`
- L331 _protected member_ `TMap<FName, UEnvQueryContext*> LocalContextMap;` — local contexts mapped by class names
- L334 _protected member_ `int32 NextQueryID;` — next ID for running query
- L337 _protected prototype_ `TSharedPtr<FEnvQueryInstance> CreateQueryInstance(const UEnvQuery* Template, EEnvQueryRunMode::Type RunMode);` — create new instance, using cached data is possible
- L341 _protected member_ `float MaxAllowedTestingTime;` — `UPROPERTY(config)` — how long are we allowed to test per update, in seconds.
- L347 _protected member_ `bool bTestQueriesUsingBreadth;` — `UPROPERTY(config)` — whether we update EQS queries based on: running a test on one query and move to the next (breadth) - default behavior, or test an entire query before moving to the next one (depth).
- L351 _protected member_ `int32 QueryCountWarningThreshold;` — `UPROPERTY(config)` — if greater than zero, we will warn once when the number of queries is greater than or equal to this number, and log the queries out
- L355 _protected member_ `double QueryCountWarningInterval;` — `UPROPERTY(config)` — how often (in seconds) we will warn about the number of queries (allows us to catch multiple occurrences in a session)
- L359 _protected member_ `double ExecutionTimeWarningSeconds = 0.025f;` — `UPROPERTY(config)` — Maximum EQS execution duration (in seconds) before a warning is reported.
- L363 _protected member_ `double HandlingResultTimeWarningSeconds = 0.025f;` — `UPROPERTY(config)` — Maximum EQS Query FinishDelegate duration (in seconds) before a warning is reported.
- L367 _protected member_ `double GenerationTimeWarningSeconds = 0.01f;` — `UPROPERTY(config)` — Maximum EQS Generator duration (in seconds) before a warning is reported.
- L371 _private prototype_ `void CreateOptionInstance(UEnvQueryOption* OptionTemplate, int32 SourceOptionIndex, const TArray<UEnvQueryTest*>& SortedTests, FEnvQueryInstance& Instance);` — create and bind delegates in instance
- L374 _private member_ `static bool bAllowEQSTimeSlicing;`
- L377 _private member_ `mutable double LastQueryCountWarningThresholdTime;`
- L379 _private prototype_ `void CheckQueryCount() const;`
- L380 _private prototype_ `void LogQueryInfo(bool bDisplayThresholdWarning) const;`
- L384 _private member_ `FDelegateHandle OnBlueprintCompiledHandle;`
- L387 _private prototype_ `void OnBlueprintCompiled();` — used to reset LocalContextMap in case we had BP contexts stored

#### Free symbols / members of external scopes

- L198 _prototype_ `FArchive& operator<<(FArchive& Ar, FEQSDebugger::FStatsInfo& Data);`
- L200 _function_ `inline bool operator== (const FEQSDebugger::FEnvQueryInfo & Left, const FEQSDebugger::FEnvQueryInfo & Right)`

### `Source/Runtime/AIModule/Classes/EnvironmentQuery/EnvQueryNode.h` (Public)


#### class `UEnvQueryNode`  
`class UEnvQueryNode : public UObject`  
_L14-37_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UObject`
- L20 _private member_ `int32 VerNum;` — `UPROPERTY()` — Versioning for updating deprecated properties
- L22 _private prototype_ `virtual void UpdateNodeVersion();`
- L24 _private prototype_ `virtual FText GetDescriptionTitle() const;`
- L25 _private prototype_ `virtual FText GetDescriptionDetails() const;`
- L32 _private function_ `virtual inline bool IsCurrentlyRunningAsync() const` — To be extended by any Node who offloads its work to another thread. Returns false by default, unless overridden. If overridden, will return whether or not this Node is currently being processed asynchronously.
- L35 _private prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`

### `Source/Runtime/AIModule/Classes/EnvironmentQuery/EnvQueryOption.h` (Public)


#### class `UEnvQueryOption`  
`class UEnvQueryOption : public UObject`  
_L14-26_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L19 _private member_ `TObjectPtr<UEnvQueryGenerator> Generator;` — `UPROPERTY()`
- L22 _private member_ `TArray<TObjectPtr<UEnvQueryTest>> Tests;` — `UPROPERTY()`
- L24 _private prototype_ `FText GetDescriptionTitle() const;`
- L25 _private prototype_ `FText GetDescriptionDetails() const;`

### `Source/Runtime/AIModule/Classes/EnvironmentQuery/EnvQueryTest.h` (Public)


#### enum `EEQSNormalizationType`  
`enum class EEQSNormalizationType : uint8`  
_L22-28_
- reflection: `UENUM()`
- L25 _public enumerator_ `Absolute` — Use 0 as the base of normalization range.
- L27 _public enumerator_ `RelativeToScores` — Use lowest item score as the base of normalization range.

#### struct `FEnvQueryTestScoringPreview`  
`struct FEnvQueryTestScoringPreview`  
_L40-57_
- L48 _public member_ `TArray<float> Samples;`
- L49 _public member_ `float FilterLow;`
- L50 _public member_ `float FilterHigh;`
- L51 _public member_ `float ClampMin;`
- L52 _public member_ `float ClampMax;`
- L53 _public member_ `uint32 bShowFilterLow : 1;`
- L54 _public member_ `uint32 bShowFilterHigh : 1;`
- L55 _public member_ `uint32 bShowClampMin : 1;`
- L56 _public member_ `uint32 bShowClampMax : 1;`

#### enum `FEnvQueryTestScoringPreview::(anonymous)`  
``  
_L43-46_

#### class `UEnvQueryTest`  
`class UEnvQueryTest : public UEnvQueryNode`  
_L61-227_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UEnvQueryNode`
- L67 _private member_ `int32 TestOrder;` — `UPROPERTY()` — Number of test as defined in data asset
- L71 _private member_ `TEnumAsByte<EEnvTestPurpose::Type> TestPurpose;` — `UPROPERTY(EditDefaultsOnly, Category=Test)` — The purpose of this test.  Should it be used for filtering possible results, scoring them, or both?
- L76 _private member_ `FString TestComment;` — `UPROPERTY(EditDefaultsOnly, Category=Test)` — Optional comment or explanation about what this test is for.  Useful when the purpose of tests may not be clear, especially when there are multiple tests of the same type.
- L80 _private member_ `TEnumAsByte<EEnvTestFilterOperator::Type> MultipleContextFilterOp;` — `UPROPERTY(EditDefaultsOnly, Category=Filter, AdvancedDisplay)` — Determines filtering operator when context returns multiple items
- L84 _private member_ `TEnumAsByte<EEnvTestScoreOperator::Type> MultipleContextScoreOp;` — `UPROPERTY(EditDefaultsOnly, Category = Score, AdvancedDisplay)` — Determines scoring operator when context returns multiple items
- L88 _private member_ `TEnumAsByte<EEnvTestFilterType::Type> FilterType;` — `UPROPERTY(EditDefaultsOnly, Category=Filter)` — Does this test filter out results that are below a lower limit, above an upper limit, or both?  Or does it just look for a matching value?
- L92 _private member_ `FAIDataProviderBoolValue BoolValue;` — `UPROPERTY(EditDefaultsOnly, Category=Filter)` — Desired boolean value of the test for scoring to occur or filtering test to pass.
- L96 _private member_ `FAIDataProviderFloatValue FloatValueMin;` — `UPROPERTY(EditDefaultsOnly, Category=Filter)` — Minimum limit (inclusive) of valid values for the raw test value. Lower values will be discarded as invalid.
- L100 _private member_ `FAIDataProviderFloatValue FloatValueMax;` — `UPROPERTY(EditDefaultsOnly, Category=Filter)` — Maximum limit (inclusive) of valid values for the raw test value. Higher values will be discarded as invalid.
- L103 _private member_ `TEnumAsByte<EEnvTestCost::Type> Cost;` — Cost of test
- L107 _private member_ `TEnumAsByte<EEnvTestScoreEquation::Type> ScoringEquation;` — `UPROPERTY(EditDefaultsOnly, Category=Score)` — The shape of the curve equation to apply to the normalized score before multiplying by factor.
- L112 _private member_ `TEnumAsByte<EEnvQueryTestClamping::Type> ClampMinType;` — `UPROPERTY(EditDefaultsOnly, Category=Score)` — How should the lower bound for normalization of the raw test value before applying the scoring formula be determined? Should it use the lowest value found (tested), the lower threshold for filtering, or a separate specified normalization minimum?
- L117 _private member_ `TEnumAsByte<EEnvQueryTestClamping::Type> ClampMaxType;` — `UPROPERTY(EditDefaultsOnly, Category=Score)` — How should the upper bound for normalization of the raw test value before applying the scoring formula be determined? Should it use the highest value found (tested), the upper threshold for filtering, or a separate specified normalization maximum?
- L121 _private member_ `EEQSNormalizationType NormalizationType;` — `UPROPERTY(EditDefaultsOnly, Category = Score)` — Specifies how to determine value span used to normalize scores
- L125 _private member_ `FAIDataProviderFloatValue ScoreClampMin;` — `UPROPERTY(EditDefaultsOnly, Category=Score)` — Minimum value to use to normalize the raw test value before applying scoring formula.
- L129 _private member_ `FAIDataProviderFloatValue ScoreClampMax;` — `UPROPERTY(EditDefaultsOnly, Category=Score)` — Maximum value to use to normalize the raw test value before applying scoring formula.
- L133 _private member_ `FAIDataProviderFloatValue ScoringFactor;` — `UPROPERTY(EditDefaultsOnly, Category=Score, Meta=(ClampMin="0.001", UIMin="0.001"))` — The weight (factor) by which to multiply the normalized score after the scoring equation is applied.
- L139 _private member_ `FAIDataProviderFloatValue ReferenceValue;` — `UPROPERTY(EditDefaultsOnly, Category = Score, Meta=(EditCondition = "bDefineReferenceValue"))` — When specified gets used to normalize test's results in such a way that the closer a value is to ReferenceValue the higher normalized result it will produce. Value farthest from ReferenceValue will be normalized to 0, and all the other values in between will get normalized linearly with the distance to ReferenceValue.
- L143 _private member_ `bool bDefineReferenceValue;` — `UPROPERTY(EditDefaultsOnly, Category = Score, meta=(InlineEditConditionToggle))` — When set to true enables usage of ReferenceValue. It's false by default
- L146 _private member_ `TSubclassOf<UEnvQueryItemType> ValidItemType;` — Validation: item type that can be used with this test
- L150 _private member_ `FEnvQueryTestScoringPreview PreviewData;` — samples of scoring function to show on graph in editor
- L153 _private prototype_ `void SetWorkOnFloatValues(bool bWorkOnFloats);`
- L154 _private function_ `inline bool GetWorkOnFloatValues() const`
- L156 _private function_ `inline bool CanRunAsFinalCondition() const`
- L167 _private member_ `uint32 bWorkOnFloatValues : 1;` — `UPROPERTY()` — When set, test operates on float values (e.g. distance, with AtLeast, UpTo conditions), otherwise it will accept bool values (e.g. visibility, with Equals condition)
- L172 _public function_ `virtual void RunTest(FEnvQueryInstance& QueryInstance) const` — Function that does the actual work
- L175 _public prototype_ `bool IsSupportedItem(TSubclassOf<UEnvQueryItemType> ItemType) const;` — check if test supports item type
- L178 _public prototype_ `bool IsContextPerItem(TSubclassOf<UEnvQueryContext> CheckContext) const;` — check if context needs to be updated for every item
- L181 _public prototype_ `FVector GetItemLocation(FEnvQueryInstance& QueryInstance, int32 ItemIndex) const;` — helper: get location of item
- L184 _public function_ `inline FVector GetItemLocation(FEnvQueryInstance& QueryInstance, const FEnvQueryInstance::ItemIterator& Iterator) const` — helper: get location of item
- L190 _public prototype_ `FRotator GetItemRotation(FEnvQueryInstance& QueryInstance, int32 ItemIndex) const;` — helper: get location of item
- L193 _public function_ `inline FRotator GetItemRotation(FEnvQueryInstance& QueryInstance, const FEnvQueryInstance::ItemIterator& Iterator) const` — helper: get location of item
- L199 _public prototype_ `AActor* GetItemActor(FEnvQueryInstance& QueryInstance, int32 ItemIndex) const;` — helper: get actor from item
- L202 _public function_ `inline AActor* GetItemActor(FEnvQueryInstance& QueryInstance, const FEnvQueryInstance::ItemIterator& Iterator) const` — helper: get actor from item
- L208 _public prototype_ `void NormalizeItemScores(FEnvQueryInstance& QueryInstance);` — normalize scores in range
- L210 _public function_ `inline bool IsScoring() const`
- L211 _public function_ `inline bool IsFiltering() const`
- L213 _public prototype_ `FText DescribeFloatTestParams() const;`
- L214 _public prototype_ `FText DescribeBoolTestParams(const FString& ConditionDesc) const;`
- L216 _public prototype_ `virtual void PostLoad() override;`
- L219 _public prototype_ `virtual void UpdateNodeVersion() override;` — update to latest version after spawning
- L222 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L226 _public prototype_ `void UpdatePreviewData();` — update preview list
- L232 _function_ `inline bool UEnvQueryTest::IsSupportedItem(TSubclassOf<UEnvQueryItemType> ItemType) const`

#### Free symbols / members of external scopes

- L30 _namespace_ `namespace EnvQueryTestVersion`
- L32 _variable_ `inline const int32 Initial = 0;` (scope `EnvQueryTestVersion`)
- L33 _variable_ `inline const int32 DataProviders = 1;` (scope `EnvQueryTestVersion`)
- L34 _variable_ `inline const int32 ReferenceValueFix = 2;` (scope `EnvQueryTestVersion`)
- L36 _variable_ `inline const int32 Latest = ReferenceValueFix;` (scope `EnvQueryTestVersion`)
- L45 _enumerator_ `DefaultSamplesCount = 21` (scope `FEnvQueryTestScoringPreview::__anon52de7a740103`) — used for built-in functions (@see EEnvTestScoreEquation)

### `Source/Runtime/AIModule/Classes/EnvironmentQuery/EnvQueryTypes.h` (Public)


#### enum `EEnvTestPurpose::Type`  
`enum Type : int`  
_L60-65_
- L62 _public enumerator_ `Filter UMETA(DisplayName="Filter Only")`
- L63 _public enumerator_ `Score UMETA(DisplayName="Score Only")`
- L64 _public enumerator_ `FilterAndScore UMETA(DisplayName="Filter and Score")`

#### enum `EEnvTestFilterType::Type`  
`enum Type : int`  
_L71-81_
- L74 _public enumerator_ `Minimum` — For numeric tests.
- L76 _public enumerator_ `Maximum` — For numeric tests.
- L78 _public enumerator_ `Range` — For numeric tests.
- L80 _public enumerator_ `Match` — For Boolean tests.

#### enum `EEnvTestScoreEquation::Type`  
`enum Type : int`  
_L87-106_
- L89 _public enumerator_ `Linear`
- L90 _public enumerator_ `Square`
- L91 _public enumerator_ `InverseLinear`
- L92 _public enumerator_ `SquareRoot`
- L94 _public enumerator_ `Constant`

#### enum `EEnvTestWeight::Type`  
`enum Type : int`  
_L112-120_
- L114 _public enumerator_ `None`
- L115 _public enumerator_ `Square`
- L116 _public enumerator_ `Inverse`
- L117 _public enumerator_ `Unused UMETA(Hidden)`
- L118 _public enumerator_ `Constant`
- L119 _public enumerator_ `Skip UMETA(DisplayName = "Do not weight")`

#### enum `EEnvTestCost::Type`  
`enum Type : int`  
_L126-134_
- L129 _public enumerator_ `Low` — Reading data, math operations (e.g. distance).
- L131 _public enumerator_ `Medium` — Processing data from multiple sources (e.g. fire tickets).
- L133 _public enumerator_ `High` — Really expensive calls (e.g. visibility traces, pathfinding).

#### enum `EEnvTestFilterOperator::Type`  
`enum Type : int`  
_L140-144_
- L142 _public enumerator_ `AllPass UMETA(Tooltip = "All contexts must pass condition")`
- L143 _public enumerator_ `AnyPass UMETA(Tooltip = "At least one context must pass condition")`

#### enum `EEnvTestScoreOperator::Type`  
`enum Type : int`  
_L150-156_
- L152 _public enumerator_ `AverageScore UMETA(Tooltip = "Use average score from all contexts")`
- L153 _public enumerator_ `MinScore UMETA(Tooltip = "Use minimum score from all contexts")`
- L154 _public enumerator_ `MaxScore UMETA(Tooltip = "Use maximum score from all contexts")`
- L155 _public enumerator_ `Multiply UMETA(Tooltip = "Multiply scores from all contexts")`

#### enum `EEnvItemStatus::Type`  
`enum Type`  
_L161-165_
- L163 _public enumerator_ `Passed`
- L164 _public enumerator_ `Failed`

#### enum `EEnvQueryStatus::Type`  
`enum Type : int`  
_L171-179_
- L173 _public enumerator_ `Processing`
- L174 _public enumerator_ `Success`
- L175 _public enumerator_ `Failed`
- L176 _public enumerator_ `Aborted`
- L177 _public enumerator_ `OwnerLost`
- L178 _public enumerator_ `MissingParam`

#### enum `EEnvQueryRunMode::Type`  
`enum Type : int`  
_L185-191_
- L187 _public enumerator_ `SingleResult UMETA(Tooltip="Pick first item with the best score", DisplayName="Single Best Item")`
- L188 _public enumerator_ `RandomBest5Pct UMETA(Tooltip="Pick random item with score 95% .. 100% of max", DisplayName="Single Random Item from Best 5%")`
- L189 _public enumerator_ `RandomBest25Pct UMETA(Tooltip="Pick random item with score 75% .. 100% of max", DisplayName="Single Random Item from Best 25%")`
- L190 _public enumerator_ `AllMatching UMETA(Tooltip="Get all items that match conditions")`

#### enum `EEnvQueryResultNormalizationOption`  
`enum class EEnvQueryResultNormalizationOption : uint8`  
_L195-200_
- reflection: `UENUM()`
- L197 _public enumerator_ `Default`
- L198 _public enumerator_ `Normalized`
- L199 _public enumerator_ `Unaltered`

#### enum `EEnvQueryParam::Type`  
`enum Type : int`  
_L205-210_
- L207 _public enumerator_ `Float`
- L208 _public enumerator_ `Int`
- L209 _public enumerator_ `Bool`

#### enum `EAIParamType`  
`enum class EAIParamType : uint8`  
_L214-220_
- reflection: `UENUM()`
- L216 _public enumerator_ `Float`
- L217 _public enumerator_ `Int`
- L218 _public enumerator_ `Bool`
- L219 _public enumerator_ `MAX UMETA(Hidden)`

#### enum `EEnvQueryTrace::Type`  
`enum Type : int`  
_L225-232_
- L227 _public enumerator_ `None`
- L228 _public enumerator_ `Navigation`
- L229 _public enumerator_ `GeometryByChannel`
- L230 _public enumerator_ `GeometryByProfile`
- L231 _public enumerator_ `NavigationOverLedges`

#### enum `EEnvTraceShape::Type`  
`enum Type : int`  
_L238-244_
- L240 _public enumerator_ `Line`
- L241 _public enumerator_ `Box`
- L242 _public enumerator_ `Sphere`
- L243 _public enumerator_ `Capsule`

#### enum `EEnvOverlapShape::Type`  
`enum Type : int`  
_L250-255_
- L252 _public enumerator_ `Box`
- L253 _public enumerator_ `Sphere`
- L254 _public enumerator_ `Capsule`

#### enum `EEnvDirection::Type`  
`enum Type : int`  
_L261-265_
- L263 _public enumerator_ `TwoPoints UMETA(DisplayName="Two Points",ToolTip="Direction from location of one context to another.")`
- L264 _public enumerator_ `Rotation UMETA(ToolTip="Context's rotation will be used as a direction.")`

#### enum `EEnvQueryTestClamping::Type`  
`enum Type : int`  
_L271-278_
- L273 _public enumerator_ `None`
- L275 _public enumerator_ `SpecifiedValue` — Clamp to value specified in test.
- L277 _public enumerator_ `FilterThreshold` — Clamp to test's filter threshold.

#### struct `FEnvNamedValue`  
`struct FEnvNamedValue`  
_L282-298_
- reflection: `USTRUCT(BlueprintType)`
- L287 _public member_ `FName ParamName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Param)`
- L290 _public member_ `EAIParamType ParamType;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Param)`
- L293 _public member_ `float Value;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Param)`
- L295 _public function_ `FEnvNamedValue() : ParamType(EAIParamType::Float), Value(0.f)`

#### struct `FEnvDirection`  
`struct FEnvDirection`  
_L301-322_
- reflection: `USTRUCT()`
- L307 _public member_ `TSubclassOf<UEnvQueryContext> LineFrom;` — `UPROPERTY(EditDefaultsOnly, Category=Direction)` — line: start context
- L311 _public member_ `TSubclassOf<UEnvQueryContext> LineTo;` — `UPROPERTY(EditDefaultsOnly, Category=Direction)` — line: finish context
- L315 _public member_ `TSubclassOf<UEnvQueryContext> Rotation;` — `UPROPERTY(EditDefaultsOnly, Category=Direction)` — rotation: direction context
- L319 _public member_ `TEnumAsByte<EEnvDirection::Type> DirMode = EEnvDirection::Type::TwoPoints;` — `UPROPERTY(EditDefaultsOnly, Category=Direction, meta=(DisplayName="Mode"))` — defines direction of second line used by test
- L321 _public prototype_ `FText ToText() const;`

#### struct `FEnvTraceData`  
`struct FEnvTraceData`  
_L325-422_
- reflection: `USTRUCT()`
- L335 _public prototype_ `FEnvTraceData();`
- L339 _public member_ `int32 VersionNum;` — `UPROPERTY()` — version number for updates
- L343 _public member_ `TSubclassOf<UNavigationQueryFilter> NavigationFilter;` — `UPROPERTY(EditDefaultsOnly, Category=Trace)` — navigation filter for tracing
- L347 _public member_ `float ProjectDown;` — `UPROPERTY(EditDefaultsOnly, Category=Trace, meta=(UIMin=0, ClampMin=0))` — search height: below point
- L351 _public member_ `float ProjectUp;` — `UPROPERTY(EditDefaultsOnly, Category=Trace, meta=(UIMin=0, ClampMin=0))` — search height: above point
- L355 _public member_ `float ExtentX;` — `UPROPERTY(EditDefaultsOnly, Category=Trace, meta=(UIMin=0, ClampMin=0))` — shape parameter for trace
- L359 _public member_ `float ExtentY;` — `UPROPERTY(EditDefaultsOnly, Category=Trace, meta=(UIMin=0, ClampMin=0))` — shape parameter for trace
- L363 _public member_ `float ExtentZ;` — `UPROPERTY(EditDefaultsOnly, Category=Trace, meta=(UIMin=0, ClampMin=0))` — shape parameter for trace
- L370 _public member_ `float PostProjectionVerticalOffset;` — `UPROPERTY(EditDefaultsOnly, Category=Trace)` — this value will be added to resulting location's Z axis. Can be useful when projecting points to navigation since navmesh is just an approximation of level geometry and items may end up being under collide-able geometry which would for example falsify visibility tests.
- L382 _public member_ `FName TraceProfileName;` — `UPROPERTY(EditDefaultsOnly, Category = Trace)` — geometry trace profile
- L386 _public member_ `TEnumAsByte<EEnvTraceShape::Type> TraceShape;` — `UPROPERTY(EditDefaultsOnly, Category=Trace)` — shape used for geometry tracing
- L390 _public member_ `TEnumAsByte<EEnvQueryTrace::Type> TraceMode;` — `UPROPERTY(EditDefaultsOnly, Category=Trace)` — shape used for geometry tracing
- L394 _public member_ `uint32 bTraceComplex : 1;` — `UPROPERTY(EditDefaultsOnly, Category=Trace, AdvancedDisplay)` — if set, trace will run on complex collisions
- L398 _public member_ `uint32 bOnlyBlockingHits : 1;` — `UPROPERTY(EditDefaultsOnly, Category=Trace, AdvancedDisplay)` — if set, trace will look only for blocking hits
- L402 _public member_ `uint32 bCanTraceOnNavMesh : 1;` — `UPROPERTY(EditDefaultsOnly, Category=Trace)` — if set, editor will allow picking navmesh trace
- L406 _public member_ `uint32 bCanTraceOnGeometry : 1;` — `UPROPERTY(EditDefaultsOnly, Category=Trace)` — if set, editor will allow picking geometry trace
- L410 _public member_ `uint32 bCanDisableTrace : 1;` — `UPROPERTY(EditDefaultsOnly, Category=Trace)` — if set, editor will allow
- L414 _public member_ `uint32 bCanProjectDown : 1;` — `UPROPERTY(EditDefaultsOnly, Category=Trace)` — if set, editor show height up/down properties for projection
- L416 _public prototype_ `FText ToText(EDescriptionMode DescMode) const;`
- L418 _public prototype_ `void SetGeometryOnly();`
- L419 _public prototype_ `void SetNavmeshOnly();`
- L421 _public prototype_ `void OnPostLoad();`

#### enum `FEnvTraceData::EDescriptionMode`  
`enum EDescriptionMode`  
_L329-333_
- L331 _public enumerator_ `Brief`
- L332 _public enumerator_ `Detailed`

#### struct `FEnvOverlapData`  
`struct FEnvOverlapData`  
_L425-477_
- reflection: `USTRUCT()`
- L429 _public function_ `FEnvOverlapData() : ExtentX(10.0f), ExtentY(10.0f), ExtentZ(10.0f), ShapeOffset(FVector::ZeroVector), OverlapChannel(ECC_WorldStatic), OverlapShape(EEnvOverlapShape::Box), bOnlyBlockingHits(true), bOverlapComplex(false), bSkipOverlapQuerier(false)`
- L444 _public member_ `float ExtentX;` — `UPROPERTY(EditDefaultsOnly, Category = Trace, meta = (UIMin = 0, ClampMin = 0))` — shape parameter for overlap
- L448 _public member_ `float ExtentY;` — `UPROPERTY(EditDefaultsOnly, Category = Trace, meta = (UIMin = 0, ClampMin = 0))` — shape parameter for overlap
- L452 _public member_ `float ExtentZ;` — `UPROPERTY(EditDefaultsOnly, Category = Trace, meta = (UIMin = 0, ClampMin = 0))` — shape parameter for overlap
- L456 _public member_ `FVector ShapeOffset;` — `UPROPERTY(EditDefaultsOnly, Category = Trace, AdvancedDisplay, Meta = (Tooltip="Offset from the item location at which to test the overlap. For example, you may need to offset vertically to avoid overlaps with flat ground."))`
- L464 _public member_ `TEnumAsByte<EEnvOverlapShape::Type> OverlapShape;` — `UPROPERTY(EditDefaultsOnly, Category = Overlap)` — shape used for geometry overlap
- L468 _public member_ `uint32 bOnlyBlockingHits : 1;` — `UPROPERTY(EditDefaultsOnly, Category = Overlap, AdvancedDisplay)` — if set, overlap will look only for blocking hits
- L472 _public member_ `uint32 bOverlapComplex : 1;` — `UPROPERTY(EditDefaultsOnly, Category = Overlap, AdvancedDisplay)` — if set, overlap will run on complex collisions
- L476 _public member_ `uint32 bSkipOverlapQuerier : 1;` — `UPROPERTY(EditDefaultsOnly, Category = Overlap, AdvancedDisplay)` — if set, overlap will skip querier context hits

#### struct `FEnvQueryItem`  
`struct FEnvQueryItem`  
_L482-511_
- L485 _public member_ `float Score;` — total score of item
- L488 _public member_ `int32 DataOffset:31;` — raw data offset
- L491 _public member_ `uint32 bIsDiscarded:1;` — has this item been discarded?
- L493 _public function_ `inline bool IsValid() const`
- L494 _public function_ `inline void Discard()`
- L496 _public function_ `bool operator<(const FEnvQueryItem& Other) const`
- L509 _public function_ `FEnvQueryItem() : Score(0.0f), DataOffset(-1), bIsDiscarded(false)`
- L510 _public function_ `FEnvQueryItem(int32 InOffset) : Score(0.0f), DataOffset(InOffset), bIsDiscarded(false)`

#### enum `TIsZeroConstructType::(anonymous)`  
`template <> struct TIsZeroConstructType<FEnvQueryItem>`  
_L513-513_

#### struct `TIsZeroConstructType`  
`template <> struct TIsZeroConstructType<FEnvQueryItem>`  
_L513-513_

#### struct `FEnvQueryResult`  
`struct FEnvQueryResult`  
_L516-587_
- reflection: `USTRUCT(BlueprintType)`
- L520 _public member_ `TArray<FEnvQueryItem> Items;`
- L524 _public member_ `TSubclassOf<UEnvQueryItemType> ItemType;` — `UPROPERTY(BlueprintReadOnly, Category = "EQS")` — type of generated items
- L527 _public member_ `TArray<uint8> RawData;` — raw data of items
- L531 _private member_ `EEnvQueryStatus::Type Status;` — query status
- L536 _public member_ `int32 OptionIndex;` — `UPROPERTY(BlueprintReadOnly, Category = "EQS")` — index of query option, that generated items
- L540 _public member_ `int32 QueryID;` — `UPROPERTY(BlueprintReadOnly, Category = "EQS")` — instance ID
- L543 _public member_ `TWeakObjectPtr<UObject> Owner;` — instance owner. Mind that it doesn't have to be the query's "Querier". This is just the object that is responsible for this query instance.
- L545 _public function_ `inline float GetItemScore(int32 Index) const`
- L548 _public prototype_ `AActor* GetItemAsActor(int32 Index) const;` — item accessors for basic types
- L549 _public prototype_ `FVector GetItemAsLocation(int32 Index) const;`
- L552 _public function_ `template<typename TItemType> const typename TItemType::FValueType& GetItemAsTypeChecked(const int32 Index) const`
- L562 _public prototype_ `void GetAllAsActors(TArray<AActor*>& OutActors) const;` — note that this function does not strip out the null-actors to not mess up results of GetItemScore(Index) calls
- L563 _public prototype_ `void GetAllAsLocations(TArray<FVector>& OutLocations) const;`
- L565 _public function_ `const uint8* GetItemRawMemory(const int32 Index) const`
- L571 _public function_ `FEnvQueryResult() : ItemType(NULL), Status(EEnvQueryStatus::Processing), OptionIndex(0), QueryID(0)`
- L572 _public function_ `FEnvQueryResult(const EEnvQueryStatus::Type& InStatus) : ItemType(NULL), Status(InStatus), OptionIndex(0), QueryID(0)`
- L574 _public function_ `inline bool IsFinished() const`
- L575 _public function_ `inline bool IsAborted() const`
- L576 _public function_ `inline bool IsSuccessful() const`
- L577 _public function_ `inline void MarkAsMissingParam()`
- L578 _public function_ `inline void MarkAsAborted()`
- L579 _public function_ `inline void MarkAsFailed()`
- L580 _public function_ `inline void MarkAsFinishedWithoutIssues()`
- L581 _public function_ `inline void MarkAsOwnerLost()`
- L583 _public function_ `inline EEnvQueryStatus::Type GetRawStatus() const`
- L586 _public function_ `inline bool IsSuccsessful() const` — `UE_DEPRECATED(5.0, "FEnvQueryResult::IsSuccsessful is deprecated. Use FEnvQueryResult::IsSuccessful instead.")`

#### struct `FEnvQuerySpatialData`  
`struct FEnvQuerySpatialData`  
_L595-599_
- L597 _public member_ `FVector Location;`
- L598 _public member_ `FRotator Rotation;`

#### struct `FEnvQueryItemDetails`  
`struct FEnvQueryItemDetails`  
_L602-635_
- desc: Detailed information about item, used by tests
- L605 _public member_ `TArray<float> TestResults;` — Results assigned by option's tests, before any modifications
- L609 _public member_ `TArray<float> TestWeightedScores;` — Results assigned by option's tests, after applying modifiers, normalization and weight
- L611 _public member_ `int32 FailedTestIndex;`
- L612 _public member_ `int32 ItemIndex;`
- L613 _public member_ `FString FailedDescription;`
- L616 _public function_ `FEnvQueryItemDetails()`
- L617 _public function_ `FEnvQueryItemDetails(int32 NumTests, int32 InItemIndex)`
- L627 _public function_ `inline uint32 GetAllocatedSize() const`

#### struct `FEnvQueryContextData`  
`struct FEnvQueryContextData`  
_L638-657_
- reflection: `USTRUCT()`
- L644 _public member_ `TSubclassOf<UEnvQueryItemType> ValueType;` — `UPROPERTY(Transient)` — type of context values
- L647 _public member_ `int32 NumValues;` — number of stored values
- L650 _public member_ `TArray<uint8> RawData;` — data of stored values
- L652 _public function_ `FEnvQueryContextData() : NumValues(0)`
- L656 _public function_ `inline uint32 GetAllocatedSize() const`

#### struct `FEnvQueryOptionInstance`  
`struct FEnvQueryOptionInstance`  
_L660-686_
- reflection: `USTRUCT()`
- L666 _public member_ `TObjectPtr<UEnvQueryGenerator> Generator;` — `UPROPERTY(transient)` — generator object
- L670 _public member_ `TArray<TObjectPtr<UEnvQueryTest>> Tests;` — `UPROPERTY(transient)` — test objects
- L673 _public member_ `int32 SourceOptionIndex;` — index of option in source asset
- L677 _public member_ `TSubclassOf<UEnvQueryItemType> ItemType;` — `UPROPERTY(transient)` — type of generated items
- L680 _public member_ `uint32 bHasNavLocations : 1;` — if set, items will be shuffled after tests
- L682 _public function_ `uint32 GetAllocatedSize() const`

#### struct `FEnvQueryDebugProfileData`  
`struct FEnvQueryDebugProfileData`  
_L694-729_
- L725 _public member_ `TArray<FOptionStat> OptionStats;`
- L726 _public member_ `TArray<FOptionData> OptionData;`
- L728 _public prototype_ `void Add(const FEnvQueryDebugProfileData& Other);`

#### struct `FEnvQueryDebugProfileData::FStep`  
`struct FStep`  
_L696-702_
- L698 _public member_ `float ExecutionTime;`
- L699 _public member_ `int32 NumProcessedItems;`
- L701 _public function_ `FStep() : ExecutionTime(0.0f), NumProcessedItems(0)`

#### struct `FEnvQueryDebugProfileData::FOptionStat`  
`struct FOptionStat`  
_L705-711_
- desc: runtime stats, can be merged
- L707 _public member_ `TArray<FStep> StepData;`
- L708 _public member_ `int32 NumRuns;`
- L710 _public function_ `FOptionStat() : NumRuns(0)`

#### struct `FEnvQueryDebugProfileData::FOptionData`  
`struct FOptionData`  
_L714-723_
- desc: setup data
- L716 _public member_ `int32 NumGenerators;`
- L717 _public member_ `TArray<FName> GeneratorNames;`
- L719 _public member_ `int32 OptionIdx;`
- L720 _public member_ `TArray<int32> TestIndices;`
- L722 _public function_ `FOptionData() : NumGenerators(1), OptionIdx(INDEX_NONE)`

#### struct `FEnvQueryDebugData`  
`struct FEnvQueryDebugData : public FEnvQueryDebugProfileData`  
_L736-753_
- inherits: `FEnvQueryDebugProfileData`
- L738 _public member_ `TArray<FEnvQueryItem> DebugItems;`
- L739 _public member_ `TArray<FEnvQueryItemDetails> DebugItemDetails;`
- L740 _public member_ `TArray<uint8> RawData;`
- L741 _public member_ `TArray<FString> PerformedTestNames;`
- L744 _public member_ `uint32 bSingleItemResult : 1;` — indicates the query was run in a single-item mode and that it has been found
- L747 _public member_ `int32 CurrentOptionGeneratorIdx = INDEX_NONE;` — composite generator can be counted correctly
- L749 _public function_ `FEnvQueryDebugData() : bSingleItemResult(false)`
- L751 _public prototype_ `void Store(const FEnvQueryInstance& QueryInstance, const float ExecutionTime, const bool bStepDone);`
- L752 _public prototype_ `void PrepareOption(const FEnvQueryInstance& QueryInstance, const TArray<UEnvQueryGenerator*>& Generators, const int32 NumTests);`

#### struct `FEQSQueryDebugData`  
`struct FEQSQueryDebugData : public FEnvQueryDebugData`  
_L756-758_
- inherits: `FEnvQueryDebugData`
- desc: This struct is now deprecated, please use FEnvQueryDebugData instead.

#### class `UEnvQueryTypes`  
`class UEnvQueryTypes : public UObject`  
_L761-774_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UObject`
- L767 _public member_ `static const float SkippedItemValue;` — special test value assigned to items skipped by condition check
- L770 _public member_ `static float UnlimitedStepTime;` — special value used for executing query steps to prevent them from being time sliced
- L772 _public prototype_ `static FText GetShortTypeName(const UObject* Ob);`
- L773 _public prototype_ `static FText DescribeContext(TSubclassOf<UEnvQueryContext> ContextClass);`

#### struct `FEnvQueryInstanceContextCacheItem`  
`struct FEnvQueryInstanceContextCacheItem`  
_L777-786_
- reflection: `USTRUCT()`
- L782 _public member_ `TObjectPtr<UClass> Class;` — `UPROPERTY(transient)`
- L785 _public member_ `FEnvQueryContextData ContextData;` — `UPROPERTY(transient)`

#### struct `FEnvQueryInstance`  
`struct FEnvQueryInstance : public FEnvQueryResult`  
_L789-1325_
- reflection: `USTRUCT()`
- inherits: `FEnvQueryResult`
- L793 _public typedef_ `typedef float FNamedParamValueType;`
- L796 _public member_ `FString QueryName;` — short name of query template - friendly name for debugging
- L799 _public member_ `FName UniqueName;` — unique name of query template - object name
- L803 _public member_ `TObjectPtr<UWorld> World;` — `UPROPERTY(transient)` — world owning this query instance
- L806 _public member_ `FQueryFinishedSignature FinishDelegate;` — observer's delegate
- L809 _public member_ `TMap<FName, FNamedParamValueType> NamedParams;` — execution params
- L813 _public member_ `TArray<FEnvQueryInstanceContextCacheItem> ContextCache;` — `UPROPERTY(transient)` — contexts in use
- L817 _public member_ `TArray<FEnvQueryOptionInstance> Options;` — `UPROPERTY(transient)` — list of options
- L820 _public member_ `int32 CurrentTest;` — currently processed test (-1 = generator)
- L824 _public member_ `int32 CurrentTestStartingItem;` — non-zero if test run last step has been stopped mid-process. This indicates index of the first item that needs processing when resumed
- L827 _public member_ `TArray<FEnvQueryItemDetails> ItemDetails;` — list of item details
- L830 _public member_ `int32 NumValidItems;` — number of valid items on list
- L833 _public member_ `uint16 ValueSize;` — size of current value
- L837 _public member_ `int32 NumProcessedItems;` — number of items processed in current step
- L840 _public member_ `uint8 bStoreDebugInfo : 1;` — set to true to store additional debug info
- L844 _public member_ `uint8 bFoundSingleResult : 1;` — used to breaking from item iterator loops
- L847 _public member_ `uint8 bPassOnSingleResult : 1;` — set when testing final condition of an option
- L850 _public member_ `uint8 bHasLoggedTimeLimitWarning : 1;` — true if this query has logged a warning that it overran the time limit
- L853 _public member_ `uint8 bIsCurrentlyRunningAsync : 1;` — true if current Generator or Test is running asynchronously
- L856 _public member_ `double StartTime;` — timestamp of creating query instance
- L859 _public member_ `double TotalExecutionTime;` — time spent executing this query
- L862 _public member_ `double CurrentStepTimeLimit;` — if > 0 then it's how much time query has for performing current step
- L866 _public member_ `double GenerationTimeWarningSeconds = 0.01f;` — Maximum EQS Generator duration (in seconds) before a warning is reported in non-shipping build.
- L870 _public member_ `EEnvQueryRunMode::Type Mode;` — run mode
- L874 _public member_ `TObjectPtr<UEnvQueryItemType_VectorBase> ItemTypeVectorCDO;` — `UPROPERTY(transient)` — item type's CDO for location tests
- L878 _public member_ `TObjectPtr<UEnvQueryItemType_ActorBase> ItemTypeActorCDO;` — `UPROPERTY(transient)` — item type's CDO for actor tests
- L880 _public prototype_ `FEnvQueryInstance();`
- L881 _public prototype_ `FEnvQueryInstance(const FEnvQueryInstance& Other);`
- L882 _public prototype_ `~FEnvQueryInstance();`
- L885 _public prototype_ `void ExecuteOneStep(double TimeLimit);` — execute single step of query
- L888 _public prototype_ `bool PrepareContext(UClass* Context, FEnvQueryContextData& ContextData);` — update context cache
- L891 _public prototype_ `bool PrepareContext(UClass* Context, TArray<FEnvQuerySpatialData>& Data);` — helpers for reading spatial data from context
- L892 _public prototype_ `bool PrepareContext(UClass* Context, TArray<FVector>& Data);`
- L893 _public prototype_ `bool PrepareContext(UClass* Context, TArray<FRotator>& Data);`
- L895 _public prototype_ `bool PrepareContext(UClass* Context, TArray<AActor*>& Data);` — helpers for reading actor data from context
- L897 _public function_ `bool IsInSingleItemFinalSearch() const`
- L899 _public function_ `bool CanBatchTest() const` — check if current test can batch its calculations
- L901 _public function_ `bool IsCurrentlyRunningAsync() const`
- L904 _public prototype_ `void ReserveItemData(int32 NumAdditionalItems);` — raw data operations
- L907 _public function_ `template<typename TypeItem> void AddItemData(typename TypeItem::FValueType ItemValue)`
- L925 _public function_ `template<typename TypeItem> void AddItemData(TArray<typename TypeItem::FValueType>& ItemCollection)` — AddItemData specialization for arrays if values
- L951 _public function_ `template<typename TypeItem, typename TypeValue> void AddItemData(TypeValue ItemValue)`
- L957 _public function_ `template<typename TypeItem, typename TypeValue> void AddItemData(TArray<TypeValue>& ItemCollection)`
- L968 _protected prototype_ `void FinalizeGeneration();` — prepare item data after generator has finished
- L971 _protected prototype_ `void FinalizeTest();` — update costs and flags after test has finished
- L974 _protected prototype_ `void FinalizeQuery();` — final pass on items of finished query
- L977 _protected prototype_ `void NormalizeScores();` — normalize total score in range 0..1
- L980 _protected prototype_ `void SortScores();` — sort all scores, from highest to lowest
- L983 _protected prototype_ `void PickRandomItemOfScoreAtLeast(float MinScore);` — pick one of items with score equal or higher than specified
- L986 _protected prototype_ `void PickSingleItem(int32 ItemIndex);` — discard all items but one
- L991 _public prototype_ `void StripRedundantData();` — removes all runtime data that can be used for debugging (not a part of actual query result)
- L994 _public function_ `inline void IncStats()`
- L1000 _public function_ `inline void DecStats()`
- L1006 _public prototype_ `uint32 GetAllocatedSize() const;`
- L1007 _public prototype_ `uint32 GetContextAllocatedSize() const;`
- L1009 _public function_ `inline uint32 GetAllocatedSize() const`
- L1010 _public function_ `inline uint32 GetContextAllocatedSize() const`
- L1016 _public prototype_ `void Log(const FString Msg) const;`
- L1035 _public prototype_ `FString GetExecutionTimeDescription() const;` — describe for logging purposes what the query spent time on
- L1309 _public typedef_ `typedef FItemIterator ItemIterator;`
- L1316 _public member_ `FEnvQueryDebugData DebugData;`
- L1317 _public member_ `static bool bDebuggingInfoEnabled;`
- L1321 _public member_ `TStatId StatId;`
- L1324 _public prototype_ `FBox GetBoundingBox() const;`

#### struct `FEnvQueryInstance::FConstItemIterator`  
`struct FConstItemIterator`  
_L1040-1086_
- desc: Note that this iterator is for read-only purposes. Please use FItemIterator for regular item iteration while performing EQS testing and scoring
- L1042 _public function_ `FConstItemIterator(FEnvQueryInstance& QueryInstance, int32 StartingItemIndex = INDEX_NONE) : Instance(QueryInstance) , CurrentItem(StartingItemIndex != INDEX_NONE ? StartingItemIndex : QueryInstance.CurrentTestStartingItem)`
- L1060 _public function_ `uint8* GetItemData()`
- L1065 _public function_ `int32 GetIndex() const`
- L1070 _public function_ `inline explicit operator bool() const`
- L1075 _public function_ `void operator++()`
- L1084 _protected member_ `FEnvQueryInstance& Instance;`
- L1085 _protected member_ `int32 CurrentItem;`

#### struct `FEnvQueryInstance::FItemIterator`  
`struct FItemIterator : public FConstItemIterator`  
_L1088-1308_
- inherits: `FConstItemIterator`
- L1090 _public prototype_ `FItemIterator(const UEnvQueryTest* QueryTest, FEnvQueryInstance& QueryInstance, int32 StartingItemIndex = INDEX_NONE);`
- L1092 _public function_ `~FItemIterator()`
- L1102 _public function_ `void SetScore(EEnvTestPurpose::Type TestPurpose, EEnvTestFilterType::Type FilterType, float Score, float FilterMin, float FilterMax)` — Filter and score an item - used by tests working on float values (can be called multiple times for single item when processing contexts with multiple entries) NOTE: The Score is the raw score, before clamping, normalizing, and multiplying by weight.  The FilterMin and FilterMax values are ONLY used for filtering (if any).
- L1154 _public function_ `void SetScore(EEnvTestPurpose::Type TestPurpose, EEnvTestFilterType::Type FilterType, bool bScore, bool bExpected)` — Filter and score an item - used by tests working on bool values (can be called multiple times for single item when processing contexts with multiple entries)
- L1205 _public function_ `void ForceItemState(const EEnvItemStatus::Type InStatus, const float Score = UEnvQueryTypes::SkippedItemValue)` — Force state and score of item Any following SetScore calls for current item will be ignored
- L1213 _public function_ `FItemIterator& IgnoreTimeLimit()` — Disables time slicing for this iterator, use with caution!
- L1219 _public function_ `inline explicit operator bool() const`
- L1224 _public function_ `void operator++()`
- L1236 _protected member_ `double Deadline;`
- L1237 _protected member_ `float ItemScore;`
- L1238 _protected member_ `int16 NumPassedForItem;`
- L1239 _protected member_ `int16 NumTestsForItem;`
- L1240 _protected member_ `uint8 CachedFilterOp;`
- L1241 _protected member_ `uint8 CachedScoreOp;`
- L1242 _protected member_ `uint8 bPassed : 1;`
- L1243 _protected member_ `uint8 bForced : 1;`
- L1244 _protected member_ `uint8 bIsFiltering : 1;`
- L1246 _protected function_ `void InitItemScore()`
- L1255 _protected prototype_ `void HandleFailedTestResult();`
- L1256 _protected prototype_ `void StoreTestResult();`
- L1258 _protected function_ `inline void SetScoreInternal(float Score)`
- L1286 _protected function_ `inline void CheckItemPassed()`

#### struct `FAIDynamicParam`  
`struct FAIDynamicParam`  
_L1333-1364_
- reflection: `USTRUCT(BlueprintType)`
- L1338 _public member_ `FName ParamName;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EQS)`
- L1341 _public member_ `EAIParamType ParamType;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EQS)`
- L1344 _public member_ `uint8 bAllowBBKey : 1;` — `UPROPERTY(BlueprintReadWrite, Category = EQS)`
- L1347 _public member_ `float Value;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EQS)`
- L1350 _public member_ `FBlackboardKeySelector BBKey;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EQS, meta=(EditCondition="bAllowBBKey", EditConditionHides))`
- L1353 _public function_ `FAIDynamicParam()`
- L1361 _public prototype_ `void ConfigureBBKey(UObject &QueryOwner);`
- L1363 _public prototype_ `static void GenerateConfigurableParamsFromNamedValues(UObject &QueryOwner, TArray<FAIDynamicParam>& OutQueryConfig, TArray<FEnvNamedValue>& InQueryParams);`

#### struct `FEQSParametrizedQueryExecutionRequest`  
`struct FEQSParametrizedQueryExecutionRequest`  
_L1367-1401_
- reflection: `USTRUCT()`
- L1371 _public prototype_ `FEQSParametrizedQueryExecutionRequest();`
- L1374 _public member_ `TObjectPtr<UEnvQuery> QueryTemplate;` — `UPROPERTY(Category = Node, EditAnywhere, meta = (EditCondition = "!bUseBBKeyForQueryTemplate"))`
- L1377 _public member_ `TArray<FAIDynamicParam> QueryConfig;` — `UPROPERTY(Category = Node, EditAnywhere)`
- L1381 _public member_ `FBlackboardKeySelector EQSQueryBlackboardKey;` — `UPROPERTY(EditAnywhere, Category = Blackboard, meta = (EditCondition = "bUseBBKeyForQueryTemplate"))` — blackboard key storing an EQS query template
- L1385 _public member_ `TEnumAsByte<EEnvQueryRunMode::Type> RunMode;` — `UPROPERTY(Category = Node, EditAnywhere)` — determines which item will be stored (All = only first matching)
- L1388 _public member_ `uint32 bUseBBKeyForQueryTemplate : 1;` — `UPROPERTY(Category = Node, EditAnywhere, meta=(InlineEditConditionToggle))`
- L1390 _public member_ `uint32 bInitialized : 1;`
- L1392 _public prototype_ `void InitForOwnerAndBlackboard(UObject& Owner, UBlackboardData* BBAsset);`
- L1394 _public function_ `bool IsValid() const`
- L1396 _public prototype_ `int32 Execute(UObject& QueryOwner, const UBlackboardComponent* BlackboardComponent, FQueryFinishedSignature& QueryFinishedDelegate);`
- L1399 _public prototype_ `void PostEditChangeProperty(UObject& Owner, struct FPropertyChangedEvent& PropertyChangedEvent);`

#### Free symbols / members of external scopes

- L29 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogEQS, Display, All);`
- L33 _macro_ `#define USE_EQS_DEBUGGER (1 && !(UE_BUILD_SHIPPING || UE_BUILD_TEST))`
- L37 _macro_ `#define USE_EQS_TICKLOADDATA (1 && USE_EQS_DEBUGGER && WITH_EDITOR)` — If set, execution stats will also gather EQS tick load data (16k memory for each query record)
- L39 _delegate_ `DECLARE_STATS_GROUP(TEXT("Environment Query"), STATGROUP_AI_EQS, S`
- L41 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Tick"),STAT_AI_EQS_Tick,STATGROUP_AI_EQS`
- L42 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Tick - EQS work"), STAT_AI_EQS_TickWork, STATG`
- L43 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Tick - OnFinished delegates"), STAT_AI_EQS_TickNot`
- L44 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Tick - Removal of completed queries"), STAT_AI_EQS_Tick`
- L45 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Load Time"),STAT_AI_EQS_LoadTime,STATGROUP_A`
- L46 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Execute One Step Time"),STAT_AI_EQS_ExecuteOneStep`
- L47 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Generator Time"),STAT_AI_EQS_GeneratorTime,STATGR`
- L48 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Test Time"),STAT_AI_EQS_TestTime,STATGROUP_A`
- L49 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("EQS Debug StoreQuery"), STAT_AI_EQS_Debug_StoreQuery,`
- L50 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("EQS Debug StoreTickTime"), STAT_AI_EQS_Debug_StoreTickTim`
- L51 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("EQS Debug StoreStats"), STAT_AI_EQS_Debug_StoreStats,`
- L52 _delegate_ `DECLARE_DWORD_COUNTER_STAT_EXTERN(TEXT("Num Instances"),STAT_AI_EQS_NumInstances,STATGRO`
- L53 _delegate_ `DECLARE_DWORD_COUNTER_STAT_EXTERN(TEXT("Num Items"),STAT_AI_EQS_NumItems,STATGROUP_A`
- L54 _delegate_ `DECLARE_MEMORY_STAT_EXTERN(TEXT("Instance memory"),STAT_AI_EQS_InstanceMemory,STATGROUP_AI_EQS,`
- L55 _delegate_ `DECLARE_FLOAT_COUNTER_STAT_EXTERN(TEXT("Avg Instance Response Time (ms)"), STAT_AI_EQS_AvgInstanceRes`
- L58 _namespace_ `namespace EEnvTestPurpose`
- L69 _namespace_ `namespace EEnvTestFilterType`
- L85 _namespace_ `namespace EEnvTestScoreEquation`
- L110 _namespace_ `namespace EEnvTestWeight`
- L124 _namespace_ `namespace EEnvTestCost`
- L138 _namespace_ `namespace EEnvTestFilterOperator`
- L148 _namespace_ `namespace EEnvTestScoreOperator`
- L159 _namespace_ `namespace EEnvItemStatus`
- L169 _namespace_ `namespace EEnvQueryStatus`
- L183 _namespace_ `namespace EEnvQueryRunMode`
- L203 _namespace_ `namespace EEnvQueryParam`
- L223 _namespace_ `namespace EEnvQueryTrace`
- L236 _namespace_ `namespace EEnvTraceShape`
- L248 _namespace_ `namespace EEnvOverlapShape`
- L259 _namespace_ `namespace EEnvDirection`
- L269 _namespace_ `namespace EEnvQueryTestClamping`
- L513 _enumerator_ `template <> struct TIsZeroConstructType<FEnvQueryItem> { enum { Value = true }; }; USTRUCT(BlueprintType) struct FEnvQueryResult { GENERATED_USTRUCT_BODY() TArray<FEnvQueryItem> Items;` (scope `TIsZeroConstructType::__anondd1790c90103`)
- L593 _delegate_ `DECLARE_DELEGATE_OneParam(FQueryFinishedSignature, TSharedPtr<FEnvQueryResult>);`
- L593 _prototype_ `DECLARE_DELEGATE_OneParam(FQueryFinishedSignature, TSharedPtr<FEnvQueryResult>);`
- L689 _macro_ `#define EQSHEADERLOG(...)`
- L691 _macro_ `#define EQSHEADERLOG(msg) Log(msg)`
- L731 _prototype_ `FArchive& operator<<(FArchive& Ar, FEnvQueryDebugProfileData::FStep& Data);`
- L732 _prototype_ `FArchive& operator<<(FArchive& Ar, FEnvQueryDebugProfileData::FOptionStat& Data);`
- L733 _prototype_ `FArchive& operator<<(FArchive& Ar, FEnvQueryDebugProfileData::FOptionData& Data);`
- L734 _prototype_ `FArchive& operator<<(FArchive& Ar, FEnvQueryDebugProfileData& Data);`
- L1020 _macro_ `# define UE_EQS_DBGMSG(Condition, Format, ...) \`
- L1026 _macro_ `# define UE_EQS_LOG(CategoryName, Verbosity, Format, ...) \`
- L1030 _macro_ `# define UE_EQS_DBGMSG(Condition, Format, ...)`
- L1031 _macro_ `# define UE_EQS_LOG(CategoryName, Verbosity, Format, ...) UE_LOG(CategoryName, Verbosity, Format, ##__VA_ARGS__);`
- L1327 _namespace_ `namespace FEQSHelpers`
- L1329 _prototype_ `const ANavigationData* FindNavigationDataForQuery(FEnvQueryInstance& QueryInstance, TSubclassOf<UEnvQueryContext> NavDataOverrideContext = nullptr);` (scope `FEQSHelpers`)

### `Source/Runtime/AIModule/Classes/EnvironmentQuery/Generators/EnvQueryGenerator_ActorsOfClass.h` (Public)


#### class `UEnvQueryGenerator_ActorsOfClass`  
`class UEnvQueryGenerator_ActorsOfClass : public UEnvQueryGenerator`  
_L15-41_
- reflection: `UCLASS(meta = (DisplayName = "Actors Of Class"), MinimalAPI)`
- inherits: `UEnvQueryGenerator`
- L20 _private member_ `TSubclassOf<AActor> SearchedActorClass;` — `UPROPERTY(EditDefaultsOnly, Category=Generator, meta=(AllowAbstract))`
- L24 _private member_ `FAIDataProviderBoolValue GenerateOnlyActorsInRadius;` — `UPROPERTY(EditDefaultsOnly, Category=Generator)` — If true, this will only returns actors of the specified class within the SearchRadius of the SearchCenter context.  If false, it will return ALL actors of the specified class in the world.
- L30 _private member_ `FAIDataProviderFloatValue SearchRadius;` — `UPROPERTY(EditDefaultsOnly, Category=Generator)` — Max distance of path between point and context.  NOTE: Zero and negative values will never return any results if UseRadius is true.  "Within" requires Distance < Radius.  Actors ON the circle (Distance == Radius) are excluded.
- L34 _private member_ `TSubclassOf<UEnvQueryContext> SearchCenter;` — `UPROPERTY(EditAnywhere, Category=Generator)` — context
- L36 _private prototype_ `virtual void GenerateItems(FEnvQueryInstance& QueryInstance) const override;`
- L37 _private function_ `virtual void ProcessItems(FEnvQueryInstance& QueryInstance, TArray<AActor*>& MatchingActors) const`
- L39 _private prototype_ `virtual FText GetDescriptionTitle() const override;`
- L40 _private prototype_ `virtual FText GetDescriptionDetails() const override;`

### `Source/Runtime/AIModule/Classes/EnvironmentQuery/Generators/EnvQueryGenerator_BlueprintBase.h` (Public)


#### class `UEnvQueryGenerator_BlueprintBase`  
`class UEnvQueryGenerator_BlueprintBase : public UEnvQueryGenerator`  
_L17-70_
- reflection: `UCLASS(Abstract, Blueprintable, MinimalAPI)`
- inherits: `UEnvQueryGenerator`
- L23 _private member_ `FText GeneratorsActionDescription;` — `UPROPERTY(EditAnywhere, Category = Generator)` — A short description of what test does, like "Generate pawn named Joe"
- L27 _private member_ `TSubclassOf<UEnvQueryContext> Context;` — `UPROPERTY(EditAnywhere, Category = Generator)` — context
- L33 _private member_ `TSubclassOf<UEnvQueryItemType> GeneratedItemType;` — `UPROPERTY(EditDefaultsOnly, Category = Generator)` — @todo this should show up only in the generator's BP, but due to the way EQS editor is generating widgets it's there as well It's a bug and we'll fix it
- L35 _private prototype_ `virtual void PostInitProperties() override;`
- L36 _private prototype_ `virtual UWorld* GetWorld() const override;`
- L39 _private prototype_ `void DoItemGeneration(const TArray<FVector>& ContextLocations) const;` — `UFUNCTION(BlueprintImplementableEvent, Category = Generator)`
- L42 _private prototype_ `void DoItemGenerationFromActors(const TArray<AActor*>& ContextActors) const;` — `UFUNCTION(BlueprintImplementableEvent, Category = Generator)`
- L44 _private prototype_ `virtual void GenerateItems(FEnvQueryInstance& QueryInstance) const override;`
- L46 _private prototype_ `virtual FText GetDescriptionTitle() const override;`
- L47 _private prototype_ `virtual FText GetDescriptionDetails() const override;`
- L50 _private prototype_ `void AddGeneratedVector(FVector GeneratedVector) const;` — `UFUNCTION(BlueprintCallable, Category = "EQS")`
- L53 _private prototype_ `void AddGeneratedActor(AActor* GeneratedActor) const;` — `UFUNCTION(BlueprintCallable, Category = "EQS")`
- L56 _private prototype_ `UObject* GetQuerier() const;` — `UFUNCTION(BlueprintCallable, Category = "EQS")`
- L67 _private member_ `mutable FEnvQueryInstance* CachedQueryInstance;` — this is valid and set only within GenerateItems call
- L69 _private member_ `ECallMode CallMode = ECallMode::Invalid;`

#### enum `UEnvQueryGenerator_BlueprintBase::ECallMode`  
`enum class ECallMode`  
_L59-64_
- L61 _public enumerator_ `Invalid`
- L62 _public enumerator_ `FromVectors`
- L63 _public enumerator_ `FromActors`

### `Source/Runtime/AIModule/Classes/EnvironmentQuery/Generators/EnvQueryGenerator_Composite.h` (Public)


#### class `UEnvQueryGenerator_Composite`  
`class UEnvQueryGenerator_Composite : public UEnvQueryGenerator`  
_L16-46_
- reflection: `UCLASS(meta = (DisplayName = "Composite"), MinimalAPI)`
- inherits: `UEnvQueryGenerator`
- L21 _private member_ `TArray<TObjectPtr<UEnvQueryGenerator>> Generators;` — `UPROPERTY(EditDefaultsOnly, Instanced, Category = Generator)`
- L32 _private member_ `uint32 bAllowDifferentItemTypes : 1;` — `UPROPERTY(EditDefaultsOnly, Category = Generator, AdvancedDisplay)` — allow generators with different item types, use at own risk! WARNING: generator will use ForcedItemType for raw data, you MUST ensure proper memory layout child generators will be writing to memory block through their own item types: - data must fit info block allocated by ForcedItemType - tests will read item location/properties through ForcedItemType
- L35 _private member_ `uint32 bHasMatchingItemType : 1;` — `UPROPERTY()`
- L38 _private member_ `TSubclassOf<UEnvQueryItemType> ForcedItemType;` — `UPROPERTY(EditDefaultsOnly, Category = Generator, AdvancedDisplay)`
- L40 _private prototype_ `void VerifyItemTypes();`
- L43 _protected prototype_ `virtual void GenerateItems(FEnvQueryInstance& QueryInstance) const override;`
- L44 _protected prototype_ `virtual FText GetDescriptionTitle() const override;`
- L45 _protected prototype_ `virtual bool IsValidGenerator() const override;`

### `Source/Runtime/AIModule/Classes/EnvironmentQuery/Generators/EnvQueryGenerator_Cone.h` (Public)


#### class `UEnvQueryGenerator_Cone`  
`class UEnvQueryGenerator_Cone : public UEnvQueryGenerator_ProjectedPoints`  
_L15-61_
- reflection: `UCLASS(meta = (DisplayName = "Points: Cone"), MinimalAPI)`
- inherits: `UEnvQueryGenerator_ProjectedPoints`
- L19 _public prototype_ `UEnvQueryGenerator_Cone(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L24 _public prototype_ `void BindDataToDataProviders(FEnvQueryInstance& QueryInstance) const;` — Binds data to data providers @param QueryInstance - the instance of the query
- L26 _public prototype_ `virtual void GenerateItems(FEnvQueryInstance& QueryInstance) const override;`
- L29 _public prototype_ `virtual FText GetDescriptionTitle() const override;` — Returns the title of the generator on the corresponding node in the EQS Editor window
- L32 _public prototype_ `virtual FText GetDescriptionDetails() const override;` — Returns the details of the generator on the corresponding node in the EQS Editor window
- L37 _protected member_ `FAIDataProviderFloatValue AlignedPointsDistance;` — `UPROPERTY(EditDefaultsOnly, Category = Generator)` — Distance between each point of the same angle
- L41 _protected member_ `FAIDataProviderFloatValue ConeDegrees;` — `UPROPERTY(EditDefaultsOnly, Category = Generator)` — Maximum degrees of the generated cone
- L47 _protected member_ `FAIDataProviderFloatValue AngleStep;` — `UPROPERTY(EditDefaultsOnly, Category = Generator)` — The step of the angle increase. Angle step must be >=1 Smaller values generate less items
- L51 _protected member_ `FAIDataProviderFloatValue Range;` — `UPROPERTY(EditDefaultsOnly, Category = Generator)` — Generation distance
- L55 _protected member_ `TSubclassOf<UEnvQueryContext> CenterActor;` — `UPROPERTY(EditAnywhere, Category = Generator)` — The actor (or actors) that will generate a cone in their facing direction
- L60 _protected member_ `uint8 bIncludeContextLocation : 1;` — `UPROPERTY(EditAnywhere, Category = Generator)` — Whether to include CenterActors' locations when generating items. Note that this option skips the MinAngledPointsDistance parameter.

### `Source/Runtime/AIModule/Classes/EnvironmentQuery/Generators/EnvQueryGenerator_CurrentLocation.h` (Public)


#### class `UEnvQueryGenerator_CurrentLocation`  
`class UEnvQueryGenerator_CurrentLocation : public UEnvQueryGenerator_ProjectedPoints`  
_L15-32_
- reflection: `UCLASS(meta = (DisplayName = "Current Location"), MinimalAPI)`
- inherits: `UEnvQueryGenerator_ProjectedPoints`
- L22 _protected member_ `TSubclassOf<UEnvQueryContext> QueryContext;` — `UPROPERTY(EditDefaultsOnly, Category = Generator)` — context
- L26 _public prototype_ `UEnvQueryGenerator_CurrentLocation(const FObjectInitializer& ObjectInitializer);`
- L28 _public prototype_ `virtual void GenerateItems(FEnvQueryInstance& QueryInstance) const override;`
- L30 _public prototype_ `virtual FText GetDescriptionTitle() const override;`
- L31 _public prototype_ `virtual FText GetDescriptionDetails() const override;`

### `Source/Runtime/AIModule/Classes/EnvironmentQuery/Generators/EnvQueryGenerator_Donut.h` (Public)


#### class `UEnvQueryGenerator_Donut`  
`class UEnvQueryGenerator_Donut : public UEnvQueryGenerator_ProjectedPoints`  
_L14-75_
- reflection: `UCLASS(meta = (DisplayName = "Points: Donut"), MinimalAPI)`
- inherits: `UEnvQueryGenerator_ProjectedPoints`
- L20 _private member_ `FAIDataProviderFloatValue InnerRadius;` — `UPROPERTY(EditDefaultsOnly, Category = Generator)` — min distance between point and context
- L24 _private member_ `FAIDataProviderFloatValue OuterRadius;` — `UPROPERTY(EditDefaultsOnly, Category = Generator)` — max distance between point and context
- L28 _private member_ `FAIDataProviderIntValue NumberOfRings;` — `UPROPERTY(EditDefaultsOnly, Category = Generator)` — number of rings to generate
- L32 _private member_ `EEnvQueryPointSpacingMethod PointOnRingSpacingMethod;` — `UPROPERTY(EditDefaultsOnly, Category = Generator)` — how we are choosing where the points are in the ring
- L36 _private member_ `FAIDataProviderFloatValue SpaceBetweenPoints;` — `UPROPERTY(EditDefaultsOnly, Category = Generator, meta = (EditCondition = "PointOnRingSpacingMethod == EEnvQueryPointSpacingMethod::BySpaceBetween", EditConditionHides))` — items will be generated on a ring this much apart
- L40 _private member_ `FAIDataProviderIntValue PointsPerRing;` — `UPROPERTY(EditDefaultsOnly, Category = Generator, meta = (EditCondition = "PointOnRingSpacingMethod == EEnvQueryPointSpacingMethod::ByNumberOfPoints", EditConditionHides))` — number of items to generate for each ring
- L44 _private member_ `FEnvDirection ArcDirection;` — `UPROPERTY(EditDefaultsOnly, Category = Generator, meta = (EditCondition = "bDefineArc"))` — If you generate items on a piece of circle you define direction of Arc cut here
- L48 _private member_ `FAIDataProviderFloatValue ArcAngle;` — `UPROPERTY(EditDefaultsOnly, Category = Generator)` — If you generate items on a piece of circle you define angle of Arc cut here
- L53 _private member_ `bool bUseSpiralPattern;` — `UPROPERTY(EditDefaultsOnly, Category = Generator)` — If true, the rings of the wheel will be rotated in a spiral pattern.  If false, they will all be at a zero rotation, looking more like the spokes on a wheel.
- L57 _private member_ `TSubclassOf<class UEnvQueryContext> Center;` — `UPROPERTY(EditAnywhere, Category = Generator)` — context
- L60 _private member_ `uint32 bDefineArc : 1;` — `UPROPERTY(EditAnywhere, Category = Generator, meta=(InlineEditConditionToggle))`
- L62 _private prototype_ `virtual void GenerateItems(FEnvQueryInstance& QueryInstance) const override;`
- L64 _private prototype_ `virtual FText GetDescriptionTitle() const override;`
- L65 _private prototype_ `virtual FText GetDescriptionDetails() const override;`
- L68 _private prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L72 _protected prototype_ `FVector::FReal GetArcBisectorAngle(FEnvQueryInstance& QueryInstance) const;`
- L73 _protected prototype_ `bool IsAngleAllowed(FVector::FReal TestAngleRad, FVector::FReal BisectAngleDeg, FVector::FReal AngleRangeDeg, bool bConstrainAngle) const;`
- L74 _protected prototype_ `bool GenerateDonutNavPoints(const TArray<FVector>& CenterPoints, TArray<FNavLocation>& Points, FEnvQueryInstance& QueryInstance) const;`

### `Source/Runtime/AIModule/Classes/EnvironmentQuery/Generators/EnvQueryGenerator_OnCircle.h` (Public)


#### enum `EPointOnCircleSpacingMethod`  
`enum class UE_DEPRECATED(5.8, "Use EEnvQueryPointSpacingMethod instead") EPointOnCircleSpacingMethod :uint8`  
_L15-21_
- L18 _public enumerator_ `BySpaceBetween` — Use the SpaceBetween value to determine how far apart points should be.
- L20 _public enumerator_ `ByNumberOfPoints` — Use a fixed number of points

#### class `UEnvQueryGenerator_OnCircle`  
`class UEnvQueryGenerator_OnCircle : public UEnvQueryGenerator_ProjectedPoints`  
_L24-96_
- reflection: `UCLASS(meta = (DisplayName = "Points: Circle"), MinimalAPI)`
- inherits: `UEnvQueryGenerator_ProjectedPoints`
- L30 _private member_ `FAIDataProviderFloatValue CircleRadius;` — `UPROPERTY(EditDefaultsOnly, Category=Generator)` — max distance of path between point and context
- L34 _private member_ `EEnvQueryPointSpacingMethod PointOnCircleSpacingMethod;` — `UPROPERTY(EditDefaultsOnly, Category = Generator)` — how we are choosing where the points are in the circle
- L38 _private member_ `FAIDataProviderFloatValue SpaceBetween;` — `UPROPERTY(EditDefaultsOnly, Category = Generator, meta = (EditCondition = "PointOnCircleSpacingMethod == EEnvQueryPointSpacingMethod::BySpaceBetween", EditConditionHides))` — items will be generated on a circle this much apart
- L42 _private member_ `FAIDataProviderIntValue NumberOfPoints;` — `UPROPERTY(EditDefaultsOnly, Category = Generator, meta = (EditCondition = "PointOnCircleSpacingMethod == EEnvQueryPointSpacingMethod::ByNumberOfPoints", EditConditionHides))` — this many items will be generated on a circle
- L46 _private member_ `FEnvDirection ArcDirection;` — `UPROPERTY(EditDefaultsOnly, Category=Generator, meta=(EditCondition="bDefineArc"))` — If you generate items on a piece of circle you define direction of Arc cut here
- L50 _private member_ `FAIDataProviderFloatValue ArcDirectionOffsetDegrees;` — `UPROPERTY(EditDefaultsOnly, Category=Generator)` — Offsets the ArcDirection and starts generating points this many degrees clock-wise around the vertical axis
- L54 _private member_ `FAIDataProviderFloatValue ArcAngle;` — `UPROPERTY(EditDefaultsOnly, Category=Generator)` — If you generate items on a piece of circle you define angle of Arc cut here
- L58 _private member_ `TSubclassOf<class UEnvQueryContext> CircleCenter;` — `UPROPERTY(EditAnywhere, Category=Generator)` — context
- L62 _private member_ `bool bIgnoreAnyContextActorsWhenGeneratingCircle;` — `UPROPERTY(EditDefaultsOnly, Category = Generator)` — ignore tracing into context actors when generating the circle
- L66 _private member_ `FAIDataProviderFloatValue CircleCenterZOffset;` — `UPROPERTY(EditAnywhere, Category = Generator)` — context offset
- L70 _private member_ `FEnvTraceData TraceData;` — `UPROPERTY(EditAnywhere, Category=Generator)` — horizontal trace for nearest obstacle
- L73 _private member_ `uint32 bDefineArc:1;` — `UPROPERTY(EditAnywhere, Category=Generator, meta=(InlineEditConditionToggle))`
- L75 _private prototype_ `virtual void PostLoad() override;`
- L77 _private prototype_ `virtual void GenerateItems(FEnvQueryInstance& QueryInstance) const override;`
- L79 _private prototype_ `virtual FText GetDescriptionTitle() const override;`
- L80 _private prototype_ `virtual FText GetDescriptionDetails() const override;`
- L83 _private prototype_ `virtual void PostEditChangeProperty( struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L87 _protected prototype_ `FVector CalcDirection(FEnvQueryInstance& QueryInstance) const;`
- L89 _protected prototype_ `void GenerateItemsForCircle(uint8* ContextRawData, UEnvQueryItemType* ContextItemType, const FVector& CenterLocation, const FVector& StartDirection, const TArray<AActor*>& IgnoredActors, int32 StepsCount, float AngleStep, FEnvQueryInstance& OutQueryInstance) const;`
- L94 _protected prototype_ `virtual void AddItemDataForCircle(uint8* ContextRawData, UEnvQueryItemType* ContextItemType, const TArray<FNavLocation>& Locations, FEnvQueryInstance& OutQueryInstance) const;`

### `Source/Runtime/AIModule/Classes/EnvironmentQuery/Generators/EnvQueryGenerator_PathingGrid.h` (Public)


#### class `UEnvQueryGenerator_PathingGrid`  
`class UEnvQueryGenerator_PathingGrid : public UEnvQueryGenerator_SimpleGrid`  
_L19-36_
- reflection: `UCLASS(meta = (DisplayName = "Points: Pathing Grid"), MinimalAPI)`
- inherits: `UEnvQueryGenerator_SimpleGrid`
- L25 _private member_ `FAIDataProviderBoolValue PathToItem;` — `UPROPERTY(EditDefaultsOnly, Category = Generator)` — pathfinding direction
- L29 _private member_ `TSubclassOf<UNavigationQueryFilter> NavigationFilter;` — `UPROPERTY(EditDefaultsOnly, Category = Generator)` — navigation filter to use in pathfinding
- L33 _private member_ `FAIDataProviderFloatValue ScanRangeMultiplier;` — `UPROPERTY(EditDefaultsOnly, Category = Pathfinding, AdvancedDisplay)` — multiplier for max distance between point and context
- L35 _private prototype_ `virtual void ProjectAndFilterNavPoints(TArray<FNavLocation>& Points, FEnvQueryInstance& QueryInstance) const override;`

### `Source/Runtime/AIModule/Classes/EnvironmentQuery/Generators/EnvQueryGenerator_PerceivedActors.h` (Public)


#### class `UEnvQueryGenerator_PerceivedActors`  
`class UEnvQueryGenerator_PerceivedActors : public UEnvQueryGenerator`  
_L13-46_
- reflection: `UCLASS(meta = (DisplayName = "Perceived Actors"), MinimalAPI)`
- inherits: `UEnvQueryGenerator`
- desc: Gathers actors perceived by context
- L20 _protected member_ `TSubclassOf<AActor> AllowedActorClass;` — `UPROPERTY(EditDefaultsOnly, Category=Generator)` — If set will be used to filter results
- L24 _protected member_ `FAIDataProviderFloatValue SearchRadius;` — `UPROPERTY(EditDefaultsOnly, Category=Generator)` — Additional distance limit imposed on the items generated. Perception's range limit still applies.
- L28 _protected member_ `TSubclassOf<UEnvQueryContext> ListenerContext;` — `UPROPERTY(EditAnywhere, Category=Generator)` — The perception listener to use as a source of information
- L32 _protected member_ `TSubclassOf<UAISense> SenseToUse;` — `UPROPERTY(EditAnywhere, Category=Generator)` — If set will be used to filter gathered results so that only actors perceived with a given sense are considered
- L40 _protected member_ `bool bIncludeKnownActors = true;` — `UPROPERTY(EditAnywhere, Category=Generator)` — Indicates whether to include all actors known via perception (TRUE) or just the ones actively being perceived at the moment (example "currently visible" as opposed to "seen and the perception stimulus haven't expired yet"). @see FAIStimulus.bExpired
- L42 _protected prototype_ `virtual void GenerateItems(FEnvQueryInstance& QueryInstance) const override;`
- L44 _protected prototype_ `virtual FText GetDescriptionTitle() const override;`
- L45 _protected prototype_ `virtual FText GetDescriptionDetails() const override;`

### `Source/Runtime/AIModule/Classes/EnvironmentQuery/Generators/EnvQueryGenerator_ProjectedPoints.h` (Public)


#### enum `EEnvQueryPointSpacingMethod`  
`enum class EEnvQueryPointSpacingMethod :uint8`  
_L17-23_
- reflection: `UENUM()`
- L20 _public enumerator_ `BySpaceBetween` — Use the SpaceBetween value to determine how far apart points should be.
- L22 _public enumerator_ `ByNumberOfPoints` — Use a fixed number of points

#### class `UEnvQueryGenerator_ProjectedPoints`  
`class UEnvQueryGenerator_ProjectedPoints : public UEnvQueryGenerator`  
_L26-57_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UEnvQueryGenerator`
- L32 _private member_ `FEnvTraceData ProjectionData;` — `UPROPERTY(EditDefaultsOnly, Category = Generator)` — trace params
- L47 _private prototype_ `virtual void ProjectAndFilterNavPoints(TArray<FNavLocation>& Points, FEnvQueryInstance& QueryInstance) const;` — project all points in array and remove those outside navmesh
- L50 _private prototype_ `virtual void StoreNavPoints(const TArray<FNavLocation>& Points, FEnvQueryInstance& QueryInstance) const;` — store points as generator's result
- L52 _private prototype_ `virtual void PostLoad() override;`
- L56 _private member_ `TSubclassOf<UEnvQueryContext> NavDataOverrideContext;` — `UPROPERTY(EditDefaultsOnly, Category = "Generator")` — Navigation Data Override

#### struct `UEnvQueryGenerator_ProjectedPoints::FSortByHeight`  
`struct FSortByHeight`  
_L34-44_
- L36 _public member_ `FVector::FReal OriginalZ;`
- L38 _public function_ `FSortByHeight(const FVector& OriginalPt) : OriginalZ(OriginalPt.Z)`
- L40 _public function_ `inline bool operator()(const FNavLocation& A, const FNavLocation& B) const`

### `Source/Runtime/AIModule/Classes/EnvironmentQuery/Generators/EnvQueryGenerator_SimpleGrid.h` (Public)


#### class `UEnvQueryGenerator_SimpleGrid`  
`class UEnvQueryGenerator_SimpleGrid : public UEnvQueryGenerator_ProjectedPoints`  
_L18-38_
- reflection: `UCLASS(meta = (DisplayName = "Points: Grid"), MinimalAPI)`
- inherits: `UEnvQueryGenerator_ProjectedPoints`
- L24 _private member_ `FAIDataProviderFloatValue GridSize;` — `UPROPERTY(EditDefaultsOnly, Category=Generator, meta=(DisplayName="GridHalfSize"))` — half of square's extent, like a radius
- L28 _private member_ `FAIDataProviderFloatValue SpaceBetween;` — `UPROPERTY(EditDefaultsOnly, Category=Generator)` — generation density
- L32 _private member_ `TSubclassOf<UEnvQueryContext> GenerateAround;` — `UPROPERTY(EditDefaultsOnly, Category=Generator)` — context
- L34 _private prototype_ `virtual void GenerateItems(FEnvQueryInstance& QueryInstance) const override;`
- L36 _private prototype_ `virtual FText GetDescriptionTitle() const override;`
- L37 _private prototype_ `virtual FText GetDescriptionDetails() const override;`

### `Source/Runtime/AIModule/Classes/EnvironmentQuery/Items/EnvQueryAllItemTypes.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/AIModule/Classes/EnvironmentQuery/Items/EnvQueryItemType.h` (Public)


#### class `UEnvQueryItemType`  
`class UEnvQueryItemType : public UObject`  
_L15-60_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UObject`
- L23 _public typedef_ `typedef void FValueType;` — every EQS item type needs to speficy data type it's using. Default is void which should trigger a compilation error if it's not set in a defived class
- L25 _public prototype_ `UEnvQueryItemType(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L28 _public function_ `inline uint16 GetValueSize() const` — get ValueSize
- L31 _public prototype_ `virtual void AddBlackboardFilters(FBlackboardKeySelector& KeySelector, UObject* FilterOwner) const;` — add filters for blackboard key selector
- L34 _public prototype_ `virtual bool StoreInBlackboard(FBlackboardKeySelector& KeySelector, UBlackboardComponent* Blackboard, const uint8* RawData) const;` — store value in blackboard entry
- L37 _public prototype_ `virtual void FinishDestroy() override;` — unregister from known types in EnvQueryManager
- L40 _public prototype_ `virtual FString GetDescription(const uint8* RawData) const;` — describe item
- L44 _public function_ `template<typename T> static const T& GetValueFromMemory(const uint8* MemoryBlock)` — helper function for reading typed data from memory block
- L52 _protected member_ `uint16 ValueSize;` — size of value for this type
- L56 _protected function_ `template<typename T> static void SetValueInMemory(uint8* MemoryBlock, const T& Value)` — helper function for writing typed data to memory block

### `Source/Runtime/AIModule/Classes/EnvironmentQuery/Items/EnvQueryItemType_Actor.h` (Public)


#### class `UEnvQueryItemType_Actor`  
`class UEnvQueryItemType_Actor : public UEnvQueryItemType_ActorBase`  
_L16-37_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEnvQueryItemType_ActorBase`
- L20 _public typedef_ `typedef const FWeakObjectPtr& FValueType;`
- L22 _public prototype_ `UEnvQueryItemType_Actor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L24 _public prototype_ `static AActor* GetValue(const uint8* RawData);`
- L25 _public prototype_ `static void SetValue(uint8* RawData, const FWeakObjectPtr& Value);`
- L27 _public prototype_ `static void SetContextHelper(FEnvQueryContextData& ContextData, const AActor* SingleActor);`
- L28 _public prototype_ `static void SetContextHelper(FEnvQueryContextData& ContextData, const TArray<const AActor*>& MultipleActors);`
- L29 _public prototype_ `static void SetContextHelper(FEnvQueryContextData& ContextData, const TArray<AActor*>& MultipleActors);`
- L32 _public prototype_ `static void AddEditorSelectedActors(FEnvQueryContextData& ContextData);` — In editor, outside a PIE session, will add all currently selected actors to the context data.
- L34 _public prototype_ `virtual FVector GetItemLocation(const uint8* RawData) const override;`
- L35 _public prototype_ `virtual FRotator GetItemRotation(const uint8* RawData) const override;`
- L36 _public prototype_ `virtual AActor* GetActor(const uint8* RawData) const override;`

### `Source/Runtime/AIModule/Classes/EnvironmentQuery/Items/EnvQueryItemType_ActorBase.h` (Public)


#### class `UEnvQueryItemType_ActorBase`  
`class UEnvQueryItemType_ActorBase : public UEnvQueryItemType_VectorBase`  
_L15-25_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UEnvQueryItemType_VectorBase`
- L20 _public prototype_ `virtual AActor* GetActor(const uint8* RawData) const;`
- L22 _public prototype_ `virtual void AddBlackboardFilters(FBlackboardKeySelector& KeySelector, UObject* FilterOwner) const override;`
- L23 _public prototype_ `virtual bool StoreInBlackboard(FBlackboardKeySelector& KeySelector, UBlackboardComponent* Blackboard, const uint8* RawData) const override;`
- L24 _public prototype_ `virtual FString GetDescription(const uint8* RawData) const override;`

### `Source/Runtime/AIModule/Classes/EnvironmentQuery/Items/EnvQueryItemType_Direction.h` (Public)


#### class `UEnvQueryItemType_Direction`  
`class UEnvQueryItemType_Direction : public UEnvQueryItemType_VectorBase`  
_L14-35_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEnvQueryItemType_VectorBase`
- L18 _public typedef_ `typedef FVector FValueType;`
- L20 _public prototype_ `UEnvQueryItemType_Direction(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L22 _public prototype_ `static FVector GetValue(const uint8* RawData);`
- L23 _public prototype_ `static void SetValue(uint8* RawData, const FVector& Value);`
- L25 _public prototype_ `static FRotator GetValueRot(const uint8* RawData);`
- L26 _public prototype_ `static void SetValueRot(uint8* RawData, const FRotator& Value);`
- L28 _public prototype_ `static void SetContextHelper(FEnvQueryContextData& ContextData, const FVector& SingleDirection);`
- L29 _public prototype_ `static void SetContextHelper(FEnvQueryContextData& ContextData, const FRotator& SingleRotation);`
- L30 _public prototype_ `static void SetContextHelper(FEnvQueryContextData& ContextData, const TArray<FVector>& MultipleDirections);`
- L31 _public prototype_ `static void SetContextHelper(FEnvQueryContextData& ContextData, const TArray<FRotator>& MultipleRotations);`
- L33 _public prototype_ `virtual FRotator GetItemRotation(const uint8* RawData) const override;`
- L34 _public prototype_ `virtual FString GetDescription(const uint8* RawData) const override;`

### `Source/Runtime/AIModule/Classes/EnvironmentQuery/Items/EnvQueryItemType_Point.h` (Public)


#### class `UEnvQueryItemType_Point`  
`class UEnvQueryItemType_Point : public UEnvQueryItemType_VectorBase`  
_L14-33_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEnvQueryItemType_VectorBase`
- L18 _public typedef_ `typedef const FNavLocation FValueType;`
- L20 _public prototype_ `UEnvQueryItemType_Point(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L22 _public prototype_ `static FNavLocation GetValue(const uint8* RawData);`
- L23 _public prototype_ `static void SetValue(uint8* RawData, const FNavLocation& Value);`
- L25 _public prototype_ `static void SetContextHelper(FEnvQueryContextData& ContextData, const FVector& SinglePoint);`
- L26 _public prototype_ `static void SetContextHelper(FEnvQueryContextData& ContextData, const TArray<FVector>& MultiplePoints);`
- L28 _public prototype_ `virtual FVector GetItemLocation(const uint8* RawData) const override;`
- L29 _public prototype_ `virtual FNavLocation GetItemNavLocation(const uint8* RawData) const;`
- L32 _public prototype_ `virtual void SetItemNavLocation(uint8* RawData, const FNavLocation& Value) const;` — Update location data in existing item

#### Free symbols / members of external scopes

- L37 _prototype_ `template<> void FEnvQueryInstance::AddItemData<UEnvQueryItemType_Point, FVector>(FVector ItemValue);` (scope `FEnvQueryInstance`) — a specialization to support saving locations with navigation data already gathered

### `Source/Runtime/AIModule/Classes/EnvironmentQuery/Items/EnvQueryItemType_VectorBase.h` (Public)


#### class `UEnvQueryItemType_VectorBase`  
`class UEnvQueryItemType_VectorBase : public UEnvQueryItemType`  
_L14-25_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UEnvQueryItemType`
- L19 _public prototype_ `virtual FVector GetItemLocation(const uint8* RawData) const;`
- L20 _public prototype_ `virtual FRotator GetItemRotation(const uint8* RawData) const;`
- L22 _public prototype_ `virtual void AddBlackboardFilters(FBlackboardKeySelector& KeySelector, UObject* FilterOwner) const override;`
- L23 _public prototype_ `virtual bool StoreInBlackboard(FBlackboardKeySelector& KeySelector, UBlackboardComponent* Blackboard, const uint8* RawData) const override;`
- L24 _public prototype_ `virtual FString GetDescription(const uint8* RawData) const override;`

### `Source/Runtime/AIModule/Classes/GenericTeamAgentInterface.h` (Public)


#### enum `ETeamAttitude::Type`  
`enum Type : int`  
_L14-19_
- L16 _public enumerator_ `Friendly`
- L17 _public enumerator_ `Neutral`
- L18 _public enumerator_ `Hostile`

#### struct `FGenericTeamId`  
`struct FGenericTeamId`  
_L23-73_
- reflection: `USTRUCT(BlueprintType)`
- L37 _protected member_ `uint8 TeamID;` — `UPROPERTY(Category = "TeamID", EditAnywhere, BlueprintReadWrite)`
- L40 _public function_ `FGenericTeamId(uint8 InTeamID = NoTeamId) : TeamID(InTeamID)`
- L43 _public function_ `inline operator uint8() const`
- L45 _public function_ `inline uint8 GetId() const`
- L48 _public prototype_ `static FGenericTeamId GetTeamIdentifier(const AActor* TeamMember);`
- L49 _public prototype_ `static ETeamAttitude::Type GetAttitude(const AActor* A, const AActor* B);`
- L50 _public function_ `static ETeamAttitude::Type GetAttitude(FGenericTeamId TeamA, FGenericTeamId TeamB)`
- L55 _public typedef_ `typedef TFunction<ETeamAttitude::Type(FGenericTeamId, FGenericTeamId)> FAttitudeSolverFunction;`
- L57 _public prototype_ `static void SetAttitudeSolver(const FAttitudeSolverFunction& Solver);`
- L58 _public prototype_ `static void ResetAttitudeSolver();`
- L64 _protected member_ `static FAttitudeSolverFunction AttitudeSolverImpl;` — the default implementation makes all teams hostile @note that for consistency IGenericTeamAgentInterface should be using the same function (by default it does)
- L67 _public member_ `static const FGenericTeamId NoTeam;`

#### enum `FGenericTeamId::EPredefinedId`  
`enum EPredefinedId`  
_L28-33_
- L32 _public enumerator_ `NoTeamId = 255`

#### class `UGenericTeamAgentInterface`  
`class UGenericTeamAgentInterface : public UInterface`  
_L76-79_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IGenericTeamAgentInterface`  
`class IGenericTeamAgentInterface`  
_L81-98_
- L86 _private function_ `virtual void SetGenericTeamId(const FGenericTeamId& TeamID)` — Assigns Team Agent to given TeamID
- L89 _private function_ `virtual FGenericTeamId GetGenericTeamId() const` — Retrieve team identifier in form of FGenericTeamId
- L92 _private function_ `virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const` — Retrieved owner attitude toward given Other object

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace ETeamAttitude`
- L69 _function_ `friend inline uint32 GetTypeHash(const FGenericTeamId Value)`

### `Source/Runtime/AIModule/Classes/GridPathAIController.h` (Public)


#### class `AGridPathAIController`  
`class AGridPathAIController : public AAIController`  
_L9-14_
- reflection: `UCLASS(Experimental)`
- inherits: `AAIController`
- L13 _public prototype_ `AGridPathAIController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`

### `Source/Runtime/AIModule/Classes/HotSpots/AIHotSpotManager.h` (Public)


#### class `UAIHotSpotManager`  
`class UAIHotSpotManager : public UObject`  
_L10-13_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`

### `Source/Runtime/AIModule/Classes/Navigation/CrowdAgentInterface.h` (Public)


#### class `UCrowdAgentInterface`  
`class UCrowdAgentInterface : public UInterface`  
_L12-15_
- reflection: `UINTERFACE(MinimalAPI, meta=(CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`

#### class `ICrowdAgentInterface`  
`class ICrowdAgentInterface`  
_L17-41_
- L22 _private function_ `virtual FVector GetCrowdAgentLocation() const` — @return current location of crowd agent
- L25 _private function_ `virtual FVector GetCrowdAgentVelocity() const` — @return current velocity of crowd agent
- L28 _private function_ `virtual void GetCrowdAgentCollisions(float& CylinderRadius, float& CylinderHalfHeight) const` — fills information about agent's collision cylinder
- L31 _private function_ `virtual float GetCrowdAgentMaxSpeed() const` — @return max speed of crowd agent
- L34 _private function_ `virtual int32 GetCrowdAgentAvoidanceGroup() const` — Group mask for this agent
- L37 _private function_ `virtual int32 GetCrowdAgentGroupsToAvoid() const` — Will avoid other agents if they are in one of specified groups
- L40 _private function_ `virtual int32 GetCrowdAgentGroupsToIgnore() const` — Will NOT avoid other agents if they are in one of specified groups, higher priority than GroupsToAvoid

### `Source/Runtime/AIModule/Classes/Navigation/CrowdFollowingComponent.h` (Public)


#### enum `ECrowdAvoidanceQuality::Type`  
`enum Type`  
_L21-27_
- L23 _public enumerator_ `Low`
- L24 _public enumerator_ `Medium`
- L25 _public enumerator_ `Good`
- L26 _public enumerator_ `High`

#### enum `ECrowdSimulationState`  
`enum class ECrowdSimulationState : uint8`  
_L30-35_
- L32 _public enumerator_ `Enabled`
- L33 _public enumerator_ `ObstacleOnly` — Disabled, avoided by others
- L34 _public enumerator_ `Disabled` — Disabled, ignored by others

#### class `UCrowdFollowingComponent`  
`class UCrowdFollowingComponent : public UPathFollowingComponent, public ICrowdAgentInterface`  
_L38-249_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UPathFollowingComponent,ICrowdAgentInterface`
- L42 _private prototype_ `virtual void BeginDestroy() override;`
- L45 _private prototype_ `virtual FVector GetCrowdAgentLocation() const override;` — ICrowdAgentInterface BEGIN
- L46 _private prototype_ `virtual FVector GetCrowdAgentVelocity() const override;`
- L47 _private prototype_ `virtual void GetCrowdAgentCollisions(float& CylinderRadius, float& CylinderHalfHeight) const override;`
- L48 _private prototype_ `virtual float GetCrowdAgentMaxSpeed() const override;`
- L49 _private prototype_ `virtual int32 GetCrowdAgentAvoidanceGroup() const override;`
- L50 _private prototype_ `virtual int32 GetCrowdAgentGroupsToAvoid() const override;`
- L51 _private prototype_ `virtual int32 GetCrowdAgentGroupsToIgnore() const override;`
- L55 _private prototype_ `virtual void Initialize() override;` — PathFollowingComponent BEGIN
- L56 _private prototype_ `virtual void Cleanup() override;`
- L57 _private prototype_ `virtual void AbortMove(const UObject& Instigator, FPathFollowingResultFlags::Type AbortFlags, FAIRequestID RequestID = FAIRequestID::CurrentRequest, EPathFollowingVelocityMode VelocityMode = EPathFollowingVelocityMode::Reset) override;`
- L58 _private prototype_ `virtual void PauseMove(FAIRequestID RequestID = FAIRequestID::CurrentRequest, EPathFollowingVelocityMode VelocityMode = EPathFollowingVelocityMode::Reset) override;`
- L59 _private prototype_ `virtual void ResumeMove(FAIRequestID RequestID = FAIRequestID::CurrentRequest) override;`
- L60 _private prototype_ `virtual FVector GetMoveFocus(bool bAllowStrafe) const override;`
- L61 _private prototype_ `virtual void OnLanded() override;`
- L62 _private prototype_ `virtual void FinishUsingCustomLink(INavLinkCustomInterface* CustomNavLink) override;`
- L63 _private prototype_ `virtual void OnPathFinished(const FPathFollowingResult& Result) override;`
- L64 _private prototype_ `virtual void OnPathUpdated() override;`
- L65 _private prototype_ `virtual void OnPathfindingQuery(FPathFindingQuery& Query) override;`
- L66 _private function_ `virtual int32 GetCurrentPathElement() const override`
- L67 _private prototype_ `virtual void OnNavigationInitDone() override;`
- L71 _private prototype_ `void UpdateCrowdAgentParams() const;` — update params in crowd manager
- L74 _private prototype_ `virtual void ApplyCrowdAgentVelocity(const FVector& NewVelocity, const FVector& DestPathCorner, bool bTraversingLink, bool bIsNearEndOfPath);` — pass agent velocity to movement component
- L77 _private prototype_ `virtual void ApplyCrowdAgentPosition(const FVector& NewPosition);` — pass desired position to movement component (after resolving collisions between crowd agents)
- L81 _private prototype_ `virtual void SuspendCrowdSteering(bool bSuspend);` — `UFUNCTION(BlueprintCallable, Category = "Crowd")` — main switch for crowd steering & avoidance
- L84 _private prototype_ `virtual void SetCrowdSimulationState(ECrowdSimulationState NewState);` — switch between crowd simulation and parent implementation (following path segments)
- L87 _private prototype_ `virtual void OnNavNodeChanged(NavNodeRef NewPolyRef, NavNodeRef PrevPolyRef, int32 CorridorSize);` — called when agent moved to next nav node (poly)
- L89 _private prototype_ `void SetCrowdAnticipateTurns(bool bEnable, bool bUpdateAgent = true);`
- L90 _private prototype_ `void SetCrowdObstacleAvoidance(bool bEnable, bool bUpdateAgent = true);`
- L91 _private prototype_ `void SetCrowdSeparation(bool bEnable, bool bUpdateAgent = true);`
- L92 _private prototype_ `void SetCrowdOptimizeVisibility(bool bEnable, bool bUpdateAgent = true);`
- L93 _private prototype_ `void SetCrowdOptimizeTopology(bool bEnable, bool bUpdateAgent = true);`
- L94 _private prototype_ `void SetCrowdPathOffset(bool bEnable, bool bUpdateAgent = true);`
- L95 _private prototype_ `void SetCrowdSlowdownAtGoal(bool bEnable, bool bUpdateAgent = true);`
- L96 _private prototype_ `void SetCrowdSeparationWeight(float Weight, bool bUpdateAgent = true);`
- L97 _private prototype_ `void SetCrowdCollisionQueryRange(float Range, bool bUpdateAgent = true);`
- L98 _private prototype_ `void SetCrowdPathOptimizationRange(float Range, bool bUpdateAgent = true);`
- L99 _private prototype_ `void SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Type Quality, bool bUpdateAgent = true);`
- L100 _private prototype_ `void SetCrowdAvoidanceRangeMultiplier(float Multiplier, bool bUpdateAgent = true);`
- L101 _private prototype_ `void SetCrowdAffectFallingVelocity(bool bEnable);`
- L102 _private prototype_ `void SetCrowdRotateToVelocity(bool bEnable);`
- L103 _private prototype_ `void SetAvoidanceGroup(int32 GroupFlags, bool bUpdateAgent = true);`
- L104 _private prototype_ `void SetGroupsToAvoid(int32 GroupFlags, bool bUpdateAgent = true);`
- L105 _private prototype_ `void SetGroupsToIgnore(int32 GroupFlags, bool bUpdateAgent = true);`
- L107 _private function_ `inline bool IsCrowdSimulationEnabled() const`
- L108 _private function_ `inline bool IsCrowdSimulatioSuspended() const`
- L109 _private function_ `inline bool IsCrowdAnticipateTurnsEnabled() const`
- L110 _private function_ `inline bool IsCrowdObstacleAvoidanceEnabled() const`
- L111 _private function_ `inline bool IsCrowdSeparationEnabled() const`
- L112 _private function_ `inline bool IsCrowdOptimizeVisibilityEnabled() const`
- L113 _private function_ `inline bool IsCrowdOptimizeTopologyEnabled() const`
- L114 _private function_ `inline bool IsCrowdPathOffsetEnabled() const`
- L115 _private function_ `inline bool IsCrowdSlowdownAtGoalEnabled() const`
- L116 _private function_ `inline bool IsCrowdAffectFallingVelocityEnabled() const`
- L117 _private function_ `inline bool IsCrowdRotateToVelocityEnabled() const`
- L119 _private function_ `inline ECrowdSimulationState GetCrowdSimulationState() const`
- L120 _private function_ `inline bool IsCrowdSimulationActive() const`
- L122 _private function_ `inline bool IsCrowdAnticipateTurnsActive() const` — checks if bEnableAnticipateTurns is set to true, and if crowd simulation is not suspended
- L124 _private function_ `inline bool IsCrowdObstacleAvoidanceActive() const` — checks if bEnableObstacleAvoidance is set to true, and if crowd simulation is not suspended
- L126 _private function_ `inline bool IsCrowdSeparationActive() const` — checks if bEnableSeparation is set to true, and if crowd simulation is not suspended
- L128 _private function_ `inline bool IsCrowdOptimizeTopologyActive() const` — checks if bEnableOptimizeTopology is set to true, and if crowd simulation is not suspended
- L130 _private function_ `inline float GetCrowdSeparationWeight() const`
- L131 _private function_ `inline float GetCrowdCollisionQueryRange() const`
- L132 _private function_ `inline float GetCrowdPathOptimizationRange() const`
- L133 _private function_ `inline ECrowdAvoidanceQuality::Type GetCrowdAvoidanceQuality() const`
- L134 _private function_ `inline float GetCrowdAvoidanceRangeMultiplier() const`
- L135 _private prototype_ `int32 GetAvoidanceGroup() const;`
- L136 _private prototype_ `int32 GetGroupsToAvoid() const;`
- L137 _private prototype_ `int32 GetGroupsToIgnore() const;`
- L139 _private prototype_ `virtual void GetDebugStringTokens(TArray<FString>& Tokens, TArray<EPathFollowingDebugTokens::Type>& Flags) const override;`
- L141 _private prototype_ `virtual void DescribeSelfToVisLog(struct FVisualLogEntry* Snapshot) const override;`
- L145 _private function_ `virtual void ApplyCrowdAgentVelocity(const FVector& NewVelocity, const FVector& DestPathCorner, bool bTraversingLink)` — `UE_DEPRECATED_FORGAME(4.16, "Use ApplyCrowdAgentVelocity function with bIsNearEndOfPath param instead.")`
- L147 _private prototype_ `void UpdateDestinationForMovingGoal(const FVector& NewDestination);`
- L151 _protected member_ `TWeakInterfacePtr<IRVOAvoidanceInterface> AvoidanceInterface;`
- L155 _public member_ `FVector CrowdAgentMoveDirection;` — `UPROPERTY()`
- L161 _protected member_ `FNavAvoidanceMask AvoidanceGroup_DEPRECATED;` — `UPROPERTY()` — DEPRECATED: Group mask for this agent - use IRVOAvoidanceInterface instead
- L165 _protected member_ `FNavAvoidanceMask GroupsToAvoid_DEPRECATED;` — `UPROPERTY()` — DEPRECATED: Will avoid other agents if they are in one of specified groups - use IRVOAvoidanceInterface instead
- L169 _protected member_ `FNavAvoidanceMask GroupsToIgnore_DEPRECATED;` — `UPROPERTY()` — DEPRECATED: Will NOT avoid other agents if they are in one of specified groups, higher priority than GroupsToAvoid - use IRVOAvoidanceInterface instead
- L173 _protected member_ `uint8 bAffectFallingVelocity : 1;` — if set, velocity will be updated even if agent is falling
- L176 _protected member_ `uint8 bRotateToVelocity : 1;` — if set, move focus will match velocity direction
- L179 _protected member_ `uint8 bUpdateDirectMoveVelocity : 1;` — if set, move velocity will be updated in every tick
- L182 _protected member_ `uint8 bRegisteredWithCrowdSimulation : 1;` — set when agent is registered in crowd simulation (either controlled or an obstacle)
- L185 _protected member_ `uint8 bSuspendCrowdSimulation : 1;` — if set, avoidance and steering will be suspended (used for direct move requests)
- L187 _protected member_ `uint8 bEnableAnticipateTurns : 1;`
- L188 _protected member_ `uint8 bEnableObstacleAvoidance : 1;`
- L189 _protected member_ `uint8 bEnableSeparation : 1;`
- L190 _protected member_ `uint8 bEnableOptimizeVisibility : 1;`
- L191 _protected member_ `uint8 bEnableOptimizeTopology : 1;`
- L192 _protected member_ `uint8 bEnablePathOffset : 1;`
- L193 _protected member_ `uint8 bEnableSlowdownAtGoal : 1;`
- L196 _protected member_ `uint8 bFinalPathPart : 1;` — if set, agent if moving on final path part, skip further updates (runtime flag)
- L199 _protected member_ `uint8 bCanCheckMovingTooFar : 1;` — if set, destination overshot can be tested
- L202 _protected member_ `uint8 bCanUpdatePathPartInTick : 1;` — if set, path parts can be switched in UpdatePathSegment, based on distance
- L205 _protected member_ `uint8 bCheckMovementAngle : 1;` — if set, movement will be finished when velocity is opposite to path direction (runtime flag)
- L207 _protected member_ `uint8 bEnableSimulationReplanOnResume : 1;`
- L209 _protected member_ `uint8 bIsTraversingLink: 1;`
- L211 _protected member_ `TEnumAsByte<ECrowdAvoidanceQuality::Type> AvoidanceQuality;`
- L212 _protected member_ `ECrowdSimulationState SimulationState;`
- L214 _protected member_ `float SeparationWeight;`
- L215 _protected member_ `float CollisionQueryRange;`
- L216 _protected member_ `float PathOptimizationRange;`
- L219 _protected member_ `float AvoidanceRangeMultiplier;` — multiplier for avoidance samples during detection, doesn't affect actual velocity
- L222 _protected member_ `int32 PathStartIndex;` — start index of current path part
- L225 _protected member_ `int32 LastPathPolyIndex;` — last visited poly on path
- L228 _protected prototype_ `virtual int32 DetermineStartingPathPoint(const FNavigationPath* ConsideredPath) const override;` — PathFollowingComponent BEGIN
- L229 _protected prototype_ `virtual void SetMoveSegment(int32 SegmentStartIndex) override;`
- L230 _protected prototype_ `virtual void UpdatePathSegment() override;`
- L231 _protected prototype_ `virtual void FollowPathSegment(float DeltaTime) override;`
- L232 _protected prototype_ `virtual bool ShouldCheckPathOnResume() const override;`
- L233 _protected prototype_ `virtual bool IsOnPath() const override;`
- L234 _protected prototype_ `virtual bool UpdateMovementComponent(bool bForce) override;`
- L235 _protected prototype_ `virtual void Reset() override;`
- L236 _protected prototype_ `virtual bool IsFollowingNavLink() const override;`
- L239 _protected prototype_ `void SwitchToNextPathPart();`
- L240 _protected prototype_ `bool ShouldSwitchPathPart(int32 CorridorSize) const;`
- L241 _protected prototype_ `bool HasMovedDuringPause() const;`
- L242 _protected prototype_ `void UpdateCachedDirections(const FVector& NewVelocity, const FVector& NextPathCorner, bool bTraversingLink);`
- L244 _protected prototype_ `virtual bool ShouldTrackMovingGoal(FVector& OutGoalLocation) const;`
- L246 _protected prototype_ `void RegisterCrowdAgent();`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace ECrowdAvoidanceQuality`

### `Source/Runtime/AIModule/Classes/Navigation/CrowdManager.h` (Public)


#### struct `FCrowdAvoidanceConfig`  
`struct FCrowdAvoidanceConfig`  
_L69-121_
- reflection: `USTRUCT()`
- L74 _public member_ `float VelocityBias;` — `UPROPERTY(EditAnywhere, Category=Crowd)`
- L77 _public member_ `float DesiredVelocityWeight;` — `UPROPERTY(EditAnywhere, Category=Crowd)`
- L80 _public member_ `float CurrentVelocityWeight;` — `UPROPERTY(EditAnywhere, Category=Crowd)`
- L83 _public member_ `float SideBiasWeight;` — `UPROPERTY(EditAnywhere, Category=Crowd)`
- L86 _public member_ `float ImpactTimeWeight;` — `UPROPERTY(EditAnywhere, Category=Crowd)`
- L89 _public member_ `float ImpactTimeRange;` — `UPROPERTY(EditAnywhere, Category=Crowd)`
- L93 _public member_ `float SideBiasThreshold;` — `UPROPERTY(EditAnywhere, Category=Crowd, meta=(ClampMin="0.001", ClampMax="1.0"))` — Threshold for side selection, larger values widen the dead zone for head-on encounters
- L97 _public member_ `float RightSideBias;` — `UPROPERTY(EditAnywhere, Category=Crowd, meta=(ClampMin="0.0"))` — Weight for preferring right-side passing, reduces oscillation (0 = disabled)
- L101 _public member_ `uint8 CustomPatternIdx;` — `UPROPERTY(EditAnywhere, Category=Crowd)` — index in SamplingPatterns array or 0xff for adaptive sampling
- L105 _public member_ `uint8 AdaptiveDivisions;` — `UPROPERTY(EditAnywhere, Category=Crowd)` — adaptive sampling: number of divisions per ring
- L109 _public member_ `uint8 AdaptiveRings;` — `UPROPERTY(EditAnywhere, Category=Crowd)` — adaptive sampling: number of rings
- L113 _public member_ `uint8 AdaptiveDepth;` — `UPROPERTY(EditAnywhere, Category=Crowd)` — adaptive sampling: number of iterations at best velocity
- L115 _public function_ `FCrowdAvoidanceConfig() : VelocityBias(0.4f), DesiredVelocityWeight(2.0f), CurrentVelocityWeight(0.75f), SideBiasWeight(0.75f), ImpactTimeWeight(2.5f), ImpactTimeRange(2.5f), SideBiasThreshold(0.01f), RightSideBias(0.0f), CustomPatternIdx(0xff), AdaptiveDivisions(7), AdaptiveRings(2), AdaptiveDepth(5)`

#### struct `FCrowdAvoidanceSamplingPattern`  
`struct FCrowdAvoidanceSamplingPattern`  
_L124-136_
- reflection: `USTRUCT()`
- L129 _public member_ `TArray<float> Angles;` — `UPROPERTY(EditAnywhere, Category=Crowd)`
- L132 _public member_ `TArray<float> Radii;` — `UPROPERTY(EditAnywhere, Category = Crowd)`
- L134 _public prototype_ `void AddSample(float AngleInDegrees, float NormalizedRadius);`
- L135 _public prototype_ `void AddSampleWithMirror(float AngleInDegrees, float NormalizedRadius);`

#### struct `FCrowdAgentData`  
`struct FCrowdAgentData`  
_L138-164_
- L142 _public member_ `TSharedPtr<dtQuerySpecialLinkFilter> LinkFilter;` — special filter for checking offmesh links
- L146 _public member_ `NavNodeRef PrevPoly;` — poly ref that agent is standing on from previous update
- L149 _public member_ `int32 AgentIndex;` — index of agent in detour crowd
- L152 _public member_ `float PathOptRemainingTime;` — remaining time for next path optimization
- L155 _public member_ `uint32 bIsSimulated : 1;` — is this agent fully simulated by crowd?
- L158 _public member_ `uint32 bWantsPathOptimization : 1;` — if set, agent wants path optimizations
- L160 _public function_ `FCrowdAgentData() : PrevPoly(0), AgentIndex(-1), PathOptRemainingTime(0), bIsSimulated(false), bWantsPathOptimization(false)`
- L162 _public function_ `bool IsValid() const`
- L163 _public prototype_ `void ClearFilter();`

#### struct `FCrowdTickHelper`  
`struct FCrowdTickHelper : FTickableGameObject`  
_L166-176_
- inherits: `FTickableGameObject`
- L168 _public member_ `TWeakObjectPtr<UCrowdManager> Owner;`
- L170 _public function_ `FCrowdTickHelper() : Owner(NULL)`
- L171 _public prototype_ `virtual void Tick(float DeltaTime);`
- L172 _public function_ `virtual bool IsTickable() const`
- L173 _public function_ `virtual bool IsTickableInEditor() const`
- L174 _public function_ `virtual bool IsTickableWhenPaused() const`
- L175 _public prototype_ `virtual TStatId GetStatId() const;`

#### class `UCrowdManager`  
`class UCrowdManager : public UCrowdManagerBase`  
_L179-401_
- reflection: `UCLASS(config = Engine, defaultconfig, MinimalAPI)`
- inherits: `UCrowdManagerBase`
- L184 _public prototype_ `UCrowdManager(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L186 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L187 _public prototype_ `virtual void BeginDestroy() override;`
- L190 _public prototype_ `void RegisterAgent(ICrowdAgentInterface* Agent);` — adds new agent to crowd
- L193 _public prototype_ `void UnregisterAgent(const ICrowdAgentInterface* Agent);` — removes agent from crowd
- L196 _public prototype_ `void UpdateAgentParams(const ICrowdAgentInterface* Agent) const;` — updates agent data
- L199 _public prototype_ `void UpdateAgentState(const ICrowdAgentInterface* Agent) const;` — refresh agent state
- L202 _public prototype_ `void OnAgentFinishedCustomLink(const ICrowdAgentInterface* Agent) const;` — update agent after using custom link
- L205 _public prototype_ `bool SetAgentMoveTarget(const UCrowdFollowingComponent* AgentComponent, const FVector& MoveTarget, FSharedConstNavQueryFilter Filter) const;` — sets move target for crowd agent (only for fully simulated)
- L208 _public prototype_ `bool SetAgentMoveDirection(const UCrowdFollowingComponent* AgentComponent, const FVector& MoveDirection) const;` — sets move direction for crowd agent (only for fully simulated)
- L211 _public prototype_ `bool SetAgentMovePath(const UCrowdFollowingComponent* AgentComponent, const FNavMeshPath* Path, int32 PathSectionStart, int32 PathSectionEnd, const FVector& PathSectionEndLocation) const;` — sets move target using path (only for fully simulated)
- L214 _public prototype_ `void ClearAgentMoveTarget(const UCrowdFollowingComponent* AgentComponent) const;` — clears move target for crowd agent (only for fully simulated)
- L217 _public prototype_ `void PauseAgent(const UCrowdFollowingComponent* AgentComponent) const;` — switch agent to waiting state
- L220 _public prototype_ `void ResumeAgent(const UCrowdFollowingComponent* AgentComponent, bool bForceReplanPath = true) const;` — resumes agent movement
- L223 _public prototype_ `bool IsAgentValid(const UCrowdFollowingComponent* AgentComponent) const;` — check if object is a valid crowd agent
- L224 _public prototype_ `bool IsAgentValid(const ICrowdAgentInterface* Agent) const;`
- L227 _public prototype_ `int32 GetNumNearbyAgents(const ICrowdAgentInterface* Agent) const;` — returns number of nearby agents
- L230 _public prototype_ `int32 GetNearbyAgentLocations(const ICrowdAgentInterface* Agent, TArray<FVector>& OutLocations) const;` — returns a list of locations of nearby agents
- L233 _public prototype_ `bool GetAvoidanceConfig(int32 Idx, FCrowdAvoidanceConfig& Data) const;` — reads existing avoidance config or returns false
- L236 _public prototype_ `bool SetAvoidanceConfig(int32 Idx, const FCrowdAvoidanceConfig& Data);` — updates existing avoidance config or returns false
- L239 _public prototype_ `void SetOffmeshConnectionPruning(bool bRemoveFromCorridor);` — remove started offmesh connections from corridor
- L242 _public prototype_ `void SetSingleAreaVisibilityOptimization(bool bEnable);` — block path visibility raycasts when crossing different nav areas
- L245 _public prototype_ `void AdjustAgentPathStart(const UCrowdFollowingComponent* AgentComponent, const FNavMeshPath* Path, int32& PathStartIdx) const;` — adjust current position in path's corridor, starting test from PathStartIdx
- L248 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L250 _public prototype_ `void DebugTick() const;`
- L254 _public prototype_ `void OnNavMeshUpdate();` — notify called when detour navmesh is changed
- L258 _public prototype_ `virtual bool IsSuitableNavData(const ANavigationData& NavData) const;` — Tests if NavData is a suitable nav data type to be used by this CrowdManager instance.
- L263 _public prototype_ `virtual void OnNavDataRegistered(ANavigationData& NavData) override;` — Called by the nav system when a new navigation data instance is registered. If the CrowdManager instance had no nav data cached it will consider this NavDataInstance and update if necesary.
- L268 _public prototype_ `virtual void OnNavDataUnregistered(ANavigationData& NavData) override;` — Called by the nav system when a navigation data instance is removed. The crowd manager will see if it's the nav data being used by it an if so try to find another one. If there's none the crowd manager will stop working.
- L270 _public function_ `virtual void CleanUp(float DeltaTime) override`
- L272 _public function_ `const ANavigationData* GetNavData() const`
- L274 _public prototype_ `UWorld* GetWorld() const override;`
- L276 _public prototype_ `static UCrowdManager* GetCurrent(UObject* WorldContextObject);`
- L277 _public prototype_ `static UCrowdManager* GetCurrent(UWorld* World);`
- L282 _protected member_ `TObjectPtr<ANavigationData> MyNavData;` — `UPROPERTY(transient)`
- L286 _protected member_ `TArray<FCrowdAvoidanceConfig> AvoidanceConfig;` — `UPROPERTY(config, EditAnywhere, Category = Config)` — obstacle avoidance params
- L290 _protected member_ `TArray<FCrowdAvoidanceSamplingPattern> SamplingPatterns;` — `UPROPERTY(config, EditAnywhere, Category = Config)` — obstacle avoidance params
- L294 _protected member_ `int32 MaxAgents;` — `UPROPERTY(config, EditAnywhere, Category = Config)` — max number of agents supported by crowd
- L298 _protected member_ `float MaxAgentRadius;` — `UPROPERTY(config, EditAnywhere, Category = Config)` — max radius of agent that can be added to crowd
- L302 _protected member_ `int32 MaxAvoidedAgents;` — `UPROPERTY(config, EditAnywhere, Category = Config)` — max number of neighbor agents for velocity avoidance
- L306 _protected member_ `int32 MaxAvoidedWalls;` — `UPROPERTY(config, EditAnywhere, Category = Config)` — max number of wall segments for velocity avoidance
- L310 _protected member_ `float NavmeshCheckInterval;` — `UPROPERTY(config, EditAnywhere, Category = Config)` — how often should agents check their position after moving off navmesh?
- L314 _protected member_ `float PathOptimizationInterval;` — `UPROPERTY(config, EditAnywhere, Category = Config)` — how often should agents try to optimize their paths?
- L318 _protected member_ `float SeparationDirClamp;` — `UPROPERTY(config, EditAnywhere, Category = Config)` — clamp separation force to left/right when neighbor is behind (dot between forward and dirToNei, -1 = disabled)
- L322 _protected member_ `float PathOffsetRadiusMultiplier;` — `UPROPERTY(config, EditAnywhere, Category = Config)` — agent radius multiplier for offsetting path around corners
- L324 _protected member_ `uint32 bPruneStartedOffmeshConnections : 1;`
- L325 _protected member_ `uint32 bSingleAreaVisibilityOptimization : 1;`
- L326 _protected member_ `uint32 bEarlyReachTestOptimization : 1;`
- L327 _protected member_ `uint32 bAllowPathReplan : 1;`
- L331 _protected member_ `uint32 bResolveCollisions : 1;` — `UPROPERTY(config, EditAnywhere, Category = Config)` — should crowd simulation resolve collisions between agents? if not, this will be handled by their movement components
- L334 _protected member_ `TMap<ICrowdAgentInterface*, FCrowdAgentData> ActiveAgents;` — agents registered in crowd manager
- L337 _protected member_ `TArray<uint8> AgentFlags;` — temporary flags for crowd agents
- L341 _protected member_ `dtCrowd* DetourCrowd;` — crowd manager
- L344 _protected member_ `dtCrowdAgentDebugInfo* DetourAgentDebug;` — debug data
- L345 _protected member_ `dtObstacleAvoidanceDebugData* DetourAvoidanceDebug;`
- L349 _protected member_ `FCrowdTickHelper* TickHelper;`
- L353 _protected prototype_ `virtual void UpdateNavData();` — try to initialize nav data from already existing ones
- L356 _protected prototype_ `virtual void UpdateAvoidanceConfig();` — setup params of crowd avoidance
- L359 _protected prototype_ `virtual void PostProximityUpdate();` — called from tick, just after updating agents proximity data
- L362 _protected prototype_ `virtual void PostMovePointUpdate();` — called from tick, after move points were updated, before any steering/avoidance
- L367 _protected prototype_ `void SetNavData(ANavigationData* NavData, const bool bFindNewNavDataIfNull = true);` — Sets NavData as MyNavData. If Null and bFindNewNavDataIfNull is true then the manager will search for a new NavData instance that meets the IsSuitableNavData() condition.
- L370 _protected prototype_ `void AddAgent(const ICrowdAgentInterface* Agent, FCrowdAgentData& AgentData) const;`
- L371 _protected prototype_ `void RemoveAgent(const ICrowdAgentInterface* Agent, FCrowdAgentData* AgentData) const;`
- L372 _protected prototype_ `void GetAgentParams(const ICrowdAgentInterface* Agent, dtCrowdAgentParams& AgentParams) const;`
- L375 _protected prototype_ `void PrepareAgentStep(const ICrowdAgentInterface* Agent, FCrowdAgentData& AgentData, float DeltaTime) const;` — prepare agent for next step of simulation
- L378 _protected prototype_ `virtual void ApplyVelocity(UCrowdFollowingComponent* AgentComponent, int32 AgentIndex) const;` — pass new velocity to movement components
- L381 _protected prototype_ `void UpdateAgentPaths();` — check changes in crowd simulation and adjust UE specific properties (smart links, poly updates)
- L384 _protected prototype_ `void UpdateSelectedDebug(const ICrowdAgentInterface* Agent, int32 AgentIndex) const;` — switch debugger to object selected in PIE
- L386 _protected prototype_ `void CreateCrowdManager();`
- L387 _protected prototype_ `void DestroyCrowdManager();`
- L390 _protected prototype_ `UWorld* GetDebugDrawingWorld() const;`
- L391 _protected prototype_ `void DrawDebugCorners(const dtCrowdAgent* CrowdAgent) const;`
- L392 _protected prototype_ `void DrawDebugCollisionSegments(const dtCrowdAgent* CrowdAgent) const;`
- L393 _protected prototype_ `void DrawDebugPath(const dtCrowdAgent* CrowdAgent) const;`
- L394 _protected prototype_ `void DrawDebugVelocityObstacles(const dtCrowdAgent* CrowdAgent) const;`
- L395 _protected prototype_ `void DrawDebugPathOptimization(const dtCrowdAgent* CrowdAgent) const;`
- L396 _protected prototype_ `void DrawDebugNeighbors(const dtCrowdAgent* CrowdAgent) const;`
- L397 _protected prototype_ `void DrawDebugSharedBoundary() const;`

#### Free symbols / members of external scopes

- L36 _typedef_ `typedef TSharedPtr<const FNavigationQueryFilter, ESPMode::ThreadSafe> FSharedConstNavQueryFilter;`

### `Source/Runtime/AIModule/Classes/Navigation/GeneratedNavLinksProxy.h` (Public)


#### class `UGeneratedNavLinksProxy`  
`class UGeneratedNavLinksProxy : public UBaseGeneratedNavLinksProxy`  
_L18-40_
- reflection: `UCLASS(Blueprintable, BlueprintType, MinimalAPI)`
- inherits: `UBaseGeneratedNavLinksProxy`
- desc: Experimental Blueprintable class used to handle generated links as custom links.
- L22 _private prototype_ `virtual UWorld* GetWorld() const override;`
- L25 _private prototype_ `virtual bool OnLinkMoveStarted(class UObject* PathComp, const FVector& DestPoint) override;` — BEGIN INavLinkCustomInterface
- L33 _private prototype_ `void ReceiveSmartLinkReached(AActor* Agent, const FVector Destination);` — `UFUNCTION(BlueprintImplementableEvent)` — Called when agent reaches smart link during path following.
- L36 _protected prototype_ `void NotifySmartLinkReached(UObject* PathingAgent, const FVector DestPoint);`
- L39 _protected member_ `FLinkReachedSignature OnSmartLinkReached;` — `UPROPERTY(BlueprintAssignable)`

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FLinkReachedSignature, AActor*, MovingActor, const FVector, DestinationPoint);`
- L11 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FLinkReachedSignature, AActor*, MovingActor, const FVector, DestinationPoint);`

### `Source/Runtime/AIModule/Classes/Navigation/GridPathFollowingComponent.h` (Public)


#### class `UGridPathFollowingComponent`  
`class UGridPathFollowingComponent : public UPathFollowingComponent`  
_L21-65_
- reflection: `UCLASS(BlueprintType, Experimental, MinimalAPI)`
- inherits: `UPathFollowingComponent`
- desc: Path following augmented with local navigation grids Keeps track of nearby grids and use them instead of navigation path when agent is inside. Once outside grid, regular path following is resumed. This allows creating dynamic navigation obstacles with fully static navigation (e.g. static navmesh), as long as they are minor modifications for path. Not recommended for blocking off entire corridors. Does not replace proper avoidance for dynamic obstacles!
- L26 _public prototype_ `virtual void Initialize() override;`
- L27 _public prototype_ `virtual void UpdatePathSegment() override;`
- L28 _public prototype_ `virtual void Reset() override;`
- L29 _public prototype_ `virtual void ResumeMove(FAIRequestID RequestID = FAIRequestID::CurrentRequest) override;`
- L30 _public prototype_ `virtual void OnPathUpdated();`
- L32 _public function_ `bool HasActiveGrid() const`
- L33 _public function_ `int32 GetActiveGridIdx() const`
- L35 _public function_ `const TArray<FVector>& GetGridPathPoints() const`
- L36 _public function_ `int32 GetNextGridPathIndex() const`
- L40 _protected prototype_ `void UpdateActiveGrid(const FVector& CurrentLocation);`
- L43 _protected member_ `TObjectPtr<UNavLocalGridManager> GridManager;` — `UPROPERTY(Transient)`
- L46 _protected member_ `int32 ActiveGridIdx;` — index of current grid
- L49 _protected member_ `int32 ActiveGridId;` — Id of current grid
- L52 _protected member_ `uint32 bIsPathEndInsideGrid : 1;` — set when end of followed Path ends inside current grid
- L55 _protected member_ `uint32 bHasGridPath : 1;` — set when grid path is valid
- L58 _protected member_ `TArray<FVector> GridPathPoints;` — path points for moving through grid
- L61 _protected member_ `int32 GridMoveSegmentEndIndex;` — index of current destination grid path point
- L64 _protected member_ `int32 MoveSegmentStartIndexOffGrid;` — expected start of path segment after leaving grid

### `Source/Runtime/AIModule/Classes/Navigation/MetaNavMeshPath.h` (Public)


#### enum `EMetaPathUpdateReason`  
`enum class EMetaPathUpdateReason : uint8`  
_L14-18_
- L16 _public enumerator_ `PathFinished`
- L17 _public enumerator_ `MoveTick`

#### struct `FMetaPathWayPoint`  
`struct FMetaPathWayPoint : public FVector`  
_L20-33_
- inherits: `FVector`
- L22 _public member_ `uint32 UserFlags;`
- L24 _public function_ `FMetaPathWayPoint() : FVector() , UserFlags(0)`
- L29 _public function_ `FMetaPathWayPoint(const FVector& Location, const uint32 InUserFlags = 0) : FVector(Location) , UserFlags(InUserFlags)`

#### struct `FMetaNavMeshPath`  
`struct FMetaNavMeshPath : public FNavMeshPath`  
_L46-132_
- inherits: `FNavMeshPath`
- desc: FMetaNavMeshPath allows creating hierarchical or guided navmesh paths Waypoints array defines list of locations that will be used to create actual FNavMeshPath data during path following. On path following start and upon reaching waypoint, path will request update from owning navmesh with following parameters: - start location set to agent location - end location set to target waypoint (or goal actor for last one) - goal actor set only for last section Since path updates itself for moving agent it really shouldn't be reused by others.
- L48 _public typedef_ `typedef FNavMeshPath Super;`
- L49 _public member_ `static const FNavPathType Type;`
- L51 _public prototype_ `FMetaNavMeshPath();`
- L52 _public prototype_ `FMetaNavMeshPath(const TArray<FMetaPathWayPoint>& InWaypoints, const ANavigationData& NavData);`
- L53 _public prototype_ `FMetaNavMeshPath(const TArray<FMetaPathWayPoint>& InWaypoints, const AController& Owner);`
- L54 _public prototype_ `FMetaNavMeshPath(const TArray<FVector>& InWaypoints, const ANavigationData& NavData);`
- L55 _public prototype_ `FMetaNavMeshPath(const TArray<FVector>& InWaypoints, const AController& Owner);`
- L58 _public prototype_ `virtual void Initialize(const FVector& AgentLocation);` — initialize path for path following
- L61 _public prototype_ `virtual bool ConditionalMoveToNextSection(const FVector& AgentLocation, EMetaPathUpdateReason Reason);` — try switching to next waypoint, depends on WaypointSwitchRadius
- L64 _public prototype_ `bool ForceMoveToNextSection(const FVector& AgentLocation);` — force switching to next waypoint
- L67 _public prototype_ `virtual bool UpdatePath(const FVector& AgentLocation);` — updates underlying navmesh path for current target waypoint
- L70 _public prototype_ `virtual void CopyFrom(const FMetaNavMeshPath& Other);` — copy properties of other meta path
- L73 _public function_ `bool IsLastSection() const` — returns true if path at last waypoint
- L76 _public function_ `int32 GetTargetWaypointIndex() const` — returns index of current target waypoint
- L79 _public function_ `int32 GetNumWaypoints() const` — returns number of waypoints
- L82 _public function_ `const TArray<FMetaPathWayPoint>& GetWaypointArray() const` — returns waypoint array
- L85 _public function_ `AActor* GetMetaPathGoal() const` — returns cached path goal
- L88 _public prototype_ `bool SetWaypoints(const TArray<FMetaPathWayPoint>& InWaypoints);` — tries to set waypoints, fails when path is ready being followed
- L91 _public prototype_ `bool SetWaypoints(const TArray<FVector>& InWaypoints);` — tries to set waypoints, fails when path is ready being followed
- L94 _public function_ `float GetWaypointSwitchRadius() const` — returns radius for switching to next waypoint during path following
- L97 _public function_ `void SetWaypointSwitchRadius(float InSwitchRadius)` — sets radius for switching to next waypoint during path following
- L100 _public prototype_ `virtual FVector::FReal GetLengthFromPosition(FVector SegmentStart, uint32 NextPathPointIndex) const override;` — returns approximate length of path, ignores parameters
- L103 _public prototype_ `virtual FVector::FReal GetCostFromIndex(int32 PathPointIndex) const override;` — returns approximate cost of path, ignores parameter
- L106 _public prototype_ `virtual void DescribeSelfToVisLog(FVisualLogEntry* Snapshot) const override;`
- L108 _public prototype_ `virtual void DebugDraw(const ANavigationData* NavData, const FColor PathColor, UCanvas* Canvas, const bool bPersistent, const float LifeTime, const uint32 NextPathPointIndex = 0) const override;`
- L113 _protected member_ `TArray<FMetaPathWayPoint> Waypoints;` — list of waypoints, including start and end of path
- L116 _protected member_ `FVector::FReal ApproximateLength;` — sum of 3D distance along waypoints, used for approximating length of path
- L119 _protected member_ `float WaypointSwitchRadius;` — update navmesh path when this close to target waypoint
- L122 _protected member_ `int32 TargetWaypointIdx;` — current target of path following
- L125 _protected member_ `TWeakObjectPtr<AActor> PathGoal;` — stored goal actor
- L128 _protected member_ `float PathGoalTetherDistance;` — stored goal actor's tether distance
- L131 _protected prototype_ `bool MoveToNextSection(const FVector& AgentLocation);` — switch to next waypoint

### `Source/Runtime/AIModule/Classes/Navigation/NavFilter_AIControllerDefault.h` (Public)


#### class `UNavFilter_AIControllerDefault`  
`class UNavFilter_AIControllerDefault : public UNavigationQueryFilter`  
_L13-20_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UNavigationQueryFilter`
- L17 _public prototype_ `UNavFilter_AIControllerDefault(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L19 _public prototype_ `virtual TSubclassOf<UNavigationQueryFilter> GetSimpleFilterForAgent(const UObject& Querier) const;`

### `Source/Runtime/AIModule/Classes/Navigation/NavLinkProxy.h` (Public)


#### class `ANavLinkProxy`  
`class ANavLinkProxy : public AActor, public INavLinkHostInterface, public INavRelevantInterface`  
_L34-156_
- reflection: `UCLASS(Blueprintable, autoCollapseCategories=(SmartLink, Actor), hideCategories=(Input), MinimalAPI)`
- inherits: `AActor,INavLinkHostInterface,INavRelevantInterface`
- desc: ANavLinkProxy connects areas of Navmesh that don't have a direct navigation path. It directly supports Simple Links (see PointLinks array). There can be multiple Simple links per ANavLinkProxy instance. Simple links are designed to statically link areas of Navmesh and are associated with a particular area class that the link provides. Smart Link functionality is provided via UNavLinkCustomComponent, see SmartLinkComp. They are designed to be able to be dynamically toggled between enabled and disabled and provide different area classes for both cases. The area classes can be dynamically modified without navmesh rebuilds. There can only be at most one smart link per ANavLinkProxy instance. Both simple and smart links on a single ANavLinkProxy instance, can be set / enabled at once, as well as either or neither of them.
- L40 _private member_ `TArray<FNavigationLink> PointLinks;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=SimpleLink)` — Navigation links (point to point) added to navigation data
- L45 _private member_ `TArray<FNavigationSegmentLink> SegmentLinks;` — `UPROPERTY()` — Navigation links (segment to segment) added to navigation data @todo hidden from use until we fix segment links. Not really working now
- L50 _private member_ `TObjectPtr<UNavLinkCustomComponent> SmartLinkComp;` — `UPROPERTY(VisibleAnywhere, Category=SmartLink)` — Smart link: can affect path following
- L55 _public member_ `bool bSmartLinkIsRelevant;` — `UPROPERTY(EditAnywhere, Category=SmartLink)` — Smart link: toggle relevancy
- L61 _private member_ `TObjectPtr<UNavLinkRenderingComponent> EdRenderComp;` — `UPROPERTY()` — Editor Preview
- L64 _private member_ `TObjectPtr<UBillboardComponent> SpriteComponent;` — `UPROPERTY()`
- L69 _public prototype_ `virtual void GetNavigationData(FNavigationRelevantData& Data) const override;` — BEGIN INavRelevantInterface
- L70 _public prototype_ `virtual FBox GetNavigationBounds() const override;`
- L71 _public prototype_ `virtual bool IsNavigationRelevant() const override;`
- L75 _public prototype_ `virtual bool GetNavigationLinksClasses(TArray<TSubclassOf<UNavLinkDefinition> >& OutClasses) const override;` — BEGIN INavLinkHostInterface
- L76 _public prototype_ `virtual bool GetNavigationLinksArray(TArray<FNavigationLink>& OutLink, TArray<FNavigationSegmentLink>& OutSegments) const override;`
- L80 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L81 _public prototype_ `virtual void PostEditUndo() override;`
- L82 _public prototype_ `virtual void PostEditImport() override;`
- L84 _public prototype_ `virtual void PostInitProperties() override;`
- L85 _public prototype_ `virtual void BeginDestroy() override;`
- L87 _public prototype_ `virtual void PostRegisterAllComponents() override;`
- L88 _public prototype_ `virtual void PostLoad() override;`
- L92 _protected prototype_ `virtual void BeginPlay() override;`
- L96 _public prototype_ `virtual FBox GetComponentsBoundingBox(bool bNonColliding = false, bool bIncludeFromChildActors = false) const override;`
- L103 _public prototype_ `void ReceiveSmartLinkReached(AActor* Agent, const FVector& Destination);` — `UFUNCTION(BlueprintImplementableEvent)` — called when agent reaches smart link during path following, use ResumePathFollowing() to give control back
- L107 _public prototype_ `void ResumePathFollowing(AActor* Agent);` — `UFUNCTION(BlueprintCallable, Category="AI|Navigation")` — resume normal path following
- L111 _public prototype_ `bool IsSmartLinkEnabled() const;` — `UFUNCTION(BlueprintCallable, Category="AI|Navigation")` — check if smart link is enabled
- L115 _public prototype_ `void SetSmartLinkEnabled(bool bEnabled);` — `UFUNCTION(BlueprintCallable, Category="AI|Navigation")` — change state of smart link
- L119 _public prototype_ `bool HasMovingAgents() const;` — `UFUNCTION(BlueprintCallable, Category="AI|Navigation")` — check if any agent is moving through smart link right now
- L126 _public prototype_ `void CopyEndPointsFromSimpleLinkToSmartLink();` — `UFUNCTION(CallInEditor, Category = SmartLink, meta = (DisplayName="CopyEndPointsFromSimpleLink"))` — Copies navlink end points from the first entry in PointLinks array. This function is a helper function making up for smart links not drawing the FVector widgets in the editor.
- L132 _protected member_ `FSmartLinkReachedSignature OnSmartLinkReached;` — `UPROPERTY(BlueprintAssignable)`
- L134 _protected prototype_ `void NotifySmartLinkReached(UNavLinkCustomComponent* LinkComp, UObject* PathingAgent, const FVector& DestPoint);`
- L137 _protected prototype_ `void OnNavAreaRegistered(const UWorld& World, const UClass* NavAreaClass);`
- L138 _protected prototype_ `void OnNavAreaUnregistered(const UWorld& World, const UClass* NavAreaClass);`
- L143 _public function_ `UNavLinkCustomComponent* GetSmartLinkComp() const` — Returns SmartLinkComp subobject
- L146 _public function_ `UNavLinkRenderingComponent* GetEdRenderComp() const` — Returns EdRenderComp subobject
- L148 _public function_ `UBillboardComponent* GetSpriteComponent() const` — Returns SpriteComponent subobject
- L153 _protected member_ `FDelegateHandle OnNavAreaRegisteredDelegateHandle;`
- L154 _protected member_ `FDelegateHandle OnNavAreaUnregisteredDelegateHandle;`

#### Free symbols / members of external scopes

- L21 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FSmartLinkReachedSignature, AActor*, MovingActor, const FVector&, DestinationPoint );`
- L21 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FSmartLinkReachedSignature, AActor*, MovingActor, const FVector&, DestinationPoint );`

### `Source/Runtime/AIModule/Classes/Navigation/NavLocalGridData.h` (Public)


#### struct `FNavLocalGridData`  
`struct FNavLocalGridData : public TSimpleCellGrid<uint8, MAX_uint8>`  
_L23-117_
- inherits: `TSimpleCellGrid<uint8,MAX_uint8>`
- desc: Local navigation grid - simple 2D grid used for navigation. Cell can be either free or marked as obstacle, connected with 8 neighbors (no walls in between) When used as source for UNavLocalGridManager, each obstacle should define its own grid data. Corresponding category in gameplay debugger is hidden by default, please adjust project configs to change that. TODO: helpers for marking different basic shapes TODO: serialization (with maps?) TODO: FNavigationPath support?
- L25 _public function_ `FNavLocalGridData() : GridId(0)`
- L26 _public prototype_ `FNavLocalGridData(const FVector& Center, float Extent2D);`
- L27 _public prototype_ `FNavLocalGridData(const FVector& Center, const FVector2D& Extent2D);`
- L28 _public prototype_ `FNavLocalGridData(const TArray<FNavLocalGridData>& SourceGrids);`
- L31 _public prototype_ `void MarkPointObstacle(const FVector& Center);` — mark single cell as obstacle
- L34 _public prototype_ `void MarkBoxObstacle(const FVector& Center, const FVector& Extent, const FQuat& Quat = FQuat::Identity);` — mark box (AABB or rotated) shape as obstacle
- L37 _public prototype_ `void MarkCapsuleObstacle(const FVector& Center, float Radius, float HalfHeight);` — mark capsule shape as obstacle
- L40 _public prototype_ `void SetHeight(float ExtentZ);` — set height of bounds, if not set: ProjectCells will use height of default query box
- L43 _public function_ `const int32 GetGridId() const` — get unique Id of grid
- L49 _public function_ `bool HasObstacleUnsafe(int32 LocationX, int32 LocationY) const` — check if there's an obstacle at cell coords
- L55 _public function_ `FIntVector GetGlobalCoords(int32 CellIdx) const` — convert cell index to global world coords with origin in (0,0,0)
- L61 _public prototype_ `int32 GetCellIndexFromGlobalCoords2D(const FIntVector& WorldCoords) const;` — convert global world coords to cell index, return -1 if outside
- L64 _public function_ `FVector GetProjectedCellCenter(int32 CellIdx) const` — convert cell index to world location using projected heights
- L70 _public function_ `FVector GetProjectedCellCenter(int32 LocationX, int32 LocationY) const` — convert cell coords on grid to world location using projected heights
- L83 _public prototype_ `void FindPathForMovingAgent(const FNavigationPath& SourcePath, const FVector& EntryLocation, int32 EntrySegmentStart, TArray<FVector>& PathPointsInside, int32& NextSegmentStart) const;` — creates path points from navigation path going through grid @param SourcePath - [in] full navigation path @param EntryLocation - [in] location of agent @param EntrySegmentStart - [in] current move segment on path @param PathPointsInside - [out] points inside grid @param NextSegmentStart - [out] next move segment on path after leaving grid or -1 if path ends inside
- L86 _public prototype_ `bool FindPath(const FIntVector& StartCoords, const FIntVector& EndCoords, TArray<FIntVector>& PathCoords) const;` — create path points from StartCoords to EndCoord, returns false when failed
- L89 _public prototype_ `void ProjectCells(const ANavigationData& NavData);` — project cells on navigation data and marks failed ones as obstacles
- L93 _public typedef_ `typedef int32 FNodeRef;` — FGraphAStar: TGraph
- L95 _public function_ `int32 GetNeighbourCount(FNodeRef NodeRef) const`
- L96 _public function_ `bool IsValidRef(FNodeRef NodeRef) const`
- L97 _public prototype_ `FNodeRef GetNeighbour(const FNodeRef NodeRef, const int32 NeiIndex) const;`
- L102 _protected member_ `TArray<FVector::FReal> CellZ;`
- L103 _protected member_ `double LastAccessTime;`
- L106 _protected prototype_ `void PostProcessPath(const FIntVector& StartCoords, const FIntVector& EndCoords, const TArray<int32>& PathIndices, TArray<FIntVector>& PathCoords) const;` — convert PathIndices into pruned PathCoords
- L109 _protected prototype_ `bool IsLineObstructed(const FIntVector& StartCoords, const FIntVector& EndCoords) const;` — check if line trace between local coords on grid hits any obstacles, doesn't validate coords!
- L112 _protected prototype_ `void SetGridId(int32 NewId);` — set unique Id of grid
- L115 _private member_ `int32 GridId;`
- L116 _private member_ `FIntVector OriginWorldCoord;`

### `Source/Runtime/AIModule/Classes/Navigation/NavLocalGridManager.h` (Public)


#### struct `FCombinedNavGridData`  
`struct FCombinedNavGridData : public FNavLocalGridData`  
_L11-17_
- inherits: `FNavLocalGridData`
- L13 _public member_ `TArray<int32> SourceIds;`
- L15 _public function_ `FCombinedNavGridData()`
- L16 _public function_ `FCombinedNavGridData(const TArray<FNavLocalGridData>& SourceGrids) : FNavLocalGridData(SourceGrids)`

#### class `UNavLocalGridManager`  
`class UNavLocalGridManager : public UObject`  
_L27-130_
- reflection: `UCLASS(Experimental, MinimalAPI)`
- inherits: `UObject`
- L33 _public prototype_ `int32 AddGridData(const FNavLocalGridData& GridData, bool bUpdate = true);` — adds new grid
- L36 _public prototype_ `void RemoveGridData(int32 GridId, bool bUpdate = true);` — removes grid
- L39 _public prototype_ `void RebuildGrids();` — rebuild overlapping grids if needed
- L42 _public prototype_ `bool FindPath(const FVector& Start, const FVector& End, TArray<FVector>& PathPoints) const;` — tries to find a path using grids, returns false when start and end locations are not on the same grid
- L45 _public prototype_ `bool SetCellSize(float CellSize);` — set shared size of grid cell, allowed only when there's no grid added
- L48 _public function_ `static float GetCellSize()` — get shared size of grid cell, static but there's only one active manager
- L51 _public prototype_ `void SetMaxActiveSources(int32 NumActiveSources);` — set limit of source grids, 0 or negative means unlimited
- L54 _public function_ `int32 GetMaxActiveSources() const` — get limit of source grids
- L57 _public function_ `bool HasSourceGridLimit() const` — check if source grid limit is set
- L60 _public prototype_ `void UpdateAccessTime(int32 CombinedGridIdx);` — updates LastAccessTime in all source grids
- L63 _public function_ `int32 GetNumSources() const` — get number of known source grids
- L66 _public function_ `int32 GetNumGrids() const` — get number of combined, non overlapping grids
- L69 _public function_ `const FNavLocalGridData& GetSourceData(int32 SourceIdx) const` — get source grid by index
- L72 _public function_ `const FNavLocalGridData& GetGridData(int32 GridIdx) const` — get combined, non overlapping grid by index
- L75 _public prototype_ `uint8 GetGridValueAt(const FVector& WorldLocation) const;` — find combined grid value at world location
- L78 _public prototype_ `int32 GetGridIndex(const FVector& WorldLocation) const;` — find combined grid at location
- L81 _public function_ `int32 GetVersion() const` — get version of grid data, incremented with each rebuild
- L84 _public prototype_ `static bool SetLocalNavigationGridDensity(UObject* WorldContextObject, float CellSize);` — `UFUNCTION(BlueprintCallable, Category = "AI|Navigation", meta = (WorldContext = "WorldContextObject"))`
- L88 _public prototype_ `static int32 AddLocalNavigationGridForPoint(UObject* WorldContextObject, const FVector& Location, const int32 Radius2D = 5, const float Height = 100.0f, bool bRebuildGrids = true);` — `UFUNCTION(BlueprintCallable, Category = "AI|Navigation", meta = (WorldContext = "WorldContextObject"))` — creates new grid data for single point
- L92 _public prototype_ `static int32 AddLocalNavigationGridForPoints(UObject* WorldContextObject, const TArray<FVector>& Locations, const int32 Radius2D = 5, const float Height = 100.0f, bool bRebuildGrids = true);` — `UFUNCTION(BlueprintCallable, Category = "AI|Navigation", meta = (WorldContext = "WorldContextObject"))` — creates single grid data for set of points
- L95 _public prototype_ `static int32 AddLocalNavigationGridForBox(UObject* WorldContextObject, const FVector& Location, FVector Extent = FVector(1,1,1), FRotator Rotation = FRotator::ZeroRotator, const int32 Radius2D = 5, const float Height = 100.0f, bool bRebuildGrids = true);` — `UFUNCTION(BlueprintCallable, Category = "AI|Navigation", meta = (WorldContext = "WorldContextObject"))`
- L98 _public prototype_ `static int32 AddLocalNavigationGridForCapsule(UObject* WorldContextObject, const FVector& Location, float CapsuleRadius, float CapsuleHalfHeight, const int32 Radius2D = 5, const float Height = 100.0f, bool bRebuildGrids = true);` — `UFUNCTION(BlueprintCallable, Category = "AI|Navigation", meta = (WorldContext = "WorldContextObject"))`
- L101 _public prototype_ `static void RemoveLocalNavigationGrid(UObject* WorldContextObject, int32 GridId, bool bRebuildGrids = true);` — `UFUNCTION(BlueprintCallable, Category = "AI|Navigation", meta = (WorldContext = "WorldContextObject"))`
- L104 _public prototype_ `static bool FindLocalNavigationGridPath(UObject* WorldContextObject, const FVector& Start, const FVector& End, TArray<FVector>& PathPoints);` — `UFUNCTION(BlueprintCallable, Category = "AI|Navigation", meta = (WorldContext = "WorldContextObject"))`
- L106 _public prototype_ `static UNavLocalGridManager* GetCurrent(UWorld* World);`
- L107 _public prototype_ `static UNavLocalGridManager* GetCurrent(const UObject* WorldContextObject);`
- L110 _public prototype_ `virtual UWorld* GetWorld() const override;`
- L115 _protected member_ `TArray<FCombinedNavGridData> CombinedGrids;`
- L116 _protected member_ `TArray<FNavLocalGridData> SourceGrids;`
- L118 _protected member_ `static float GridCellSize;`
- L120 _protected member_ `int32 VersionNum;`
- L121 _protected member_ `int32 NextGridId;`
- L122 _protected member_ `int32 MaxActiveSourceGrids;`
- L123 _protected member_ `uint32 bNeedsRebuilds : 1;`
- L126 _protected prototype_ `virtual void ProjectGrids(const TArray<int32>& GridIndices);` — projects combined grids to navigation data
- L129 _protected prototype_ `bool UpdateSourceGrids();` — ensures limit of source grids, removing oldest entries (LastAccessTime)

### `Source/Runtime/AIModule/Classes/Navigation/PathFollowingComponent.h` (Public)


#### enum `EPathFollowingStatus::Type`  
`enum Type : int`  
_L36-49_
- L39 _public enumerator_ `Idle` — No requests
- L42 _public enumerator_ `Waiting` — Request with incomplete path, will start after UpdateMove()
- L45 _public enumerator_ `Paused` — Request paused, will continue after ResumeMove()
- L48 _public enumerator_ `Moving` — Following path

#### enum `EPathFollowingResult::Type`  
`enum Type : int`  
_L55-74_
- L58 _public enumerator_ `Success` — Reached destination
- L61 _public enumerator_ `Blocked` — Movement was blocked
- L64 _public enumerator_ `OffPath` — Agent is not on path
- L67 _public enumerator_ `Aborted` — Aborted and stopped (failure)
- L70 _public enumerator_ `Skipped_DEPRECATED UMETA(Hidden)` — DEPRECATED, use Aborted result instead
- L73 _public enumerator_ `Invalid` — Request was invalid

#### struct `FPathFollowingResult`  
`struct FPathFollowingResult`  
_L121-137_
- L123 _public member_ `FPathFollowingResultFlags::Type Flags;`
- L124 _public member_ `TEnumAsByte<EPathFollowingResult::Type> Code;`
- L126 _public function_ `FPathFollowingResult() : Flags(0), Code(EPathFollowingResult::Invalid)`
- L127 _public prototype_ `FPathFollowingResult(FPathFollowingResultFlags::Type InFlags);`
- L128 _public prototype_ `FPathFollowingResult(EPathFollowingResult::Type ResultCode, FPathFollowingResultFlags::Type ExtraFlags);`
- L130 _public function_ `bool HasFlag(FPathFollowingResultFlags::Type Flag) const`
- L132 _public function_ `bool IsSuccess() const`
- L133 _public function_ `bool IsFailure() const`
- L134 _public function_ `bool IsInterrupted() const`
- L136 _public prototype_ `FString ToString() const;`

#### enum `EPathFollowingAction::Type`  
`enum Type : int`  
_L143-150_
- L145 _public enumerator_ `Error`
- L146 _public enumerator_ `NoMove`
- L147 _public enumerator_ `DirectMove`
- L148 _public enumerator_ `PartialPath`
- L149 _public enumerator_ `PathToGoal`

#### enum `EPathFollowingRequestResult::Type`  
`enum Type : int`  
_L156-161_
- L158 _public enumerator_ `Failed`
- L159 _public enumerator_ `AlreadyAtGoal`
- L160 _public enumerator_ `RequestSuccessful`

#### struct `FPathFollowingRequestResult`  
`struct FPathFollowingRequestResult`  
_L164-171_
- L166 _public member_ `FAIRequestID MoveId;`
- L167 _public member_ `TEnumAsByte<EPathFollowingRequestResult::Type> Code;`
- L169 _public function_ `FPathFollowingRequestResult() : MoveId(FAIRequestID::InvalidRequest), Code(EPathFollowingRequestResult::Failed)`
- L170 _public function_ `operator EPathFollowingRequestResult::Type() const`

#### enum `EPathFollowingDebugTokens::Type`  
`enum Type : int`  
_L175-181_
- L177 _public enumerator_ `Description`
- L178 _public enumerator_ `ParamName`
- L179 _public enumerator_ `FailedValue`
- L180 _public enumerator_ `PassedValue`

#### enum `EPathFollowingMessage::Type`  
`enum Type : int`  
_L187-191_
- L189 _public enumerator_ `NoPath`
- L190 _public enumerator_ `OtherRequest`

#### enum `EPathFollowingVelocityMode`  
`enum class EPathFollowingVelocityMode : uint8`  
_L194-198_
- L196 _public enumerator_ `Reset`
- L197 _public enumerator_ `Keep`

#### enum `EPathFollowingReachMode`  
`enum class EPathFollowingReachMode : uint8`  
_L200-213_
- L203 _public enumerator_ `ExactLocation` — reach test uses only AcceptanceRadius
- L206 _public enumerator_ `OverlapAgent` — reach test uses AcceptanceRadius increased by modified agent radius
- L209 _public enumerator_ `OverlapGoal` — reach test uses AcceptanceRadius increased by goal actor radius
- L212 _public enumerator_ `OverlapAgentAndGoal` — reach test uses AcceptanceRadius increased by modified agent radius AND goal actor radius

#### class `UPathFollowingComponent`  
`class UPathFollowingComponent : public UActorComponent, public IAIResourceInterface, public IPathFollowingAgentInterface`  
_L216-757_
- reflection: `UCLASS(config=Engine, MinimalAPI)`
- inherits: `UActorComponent,IAIResourceInterface,IPathFollowingAgentInterface`
- L220 _private prototype_ `DECLARE_DELEGATE_TwoParams(FPostProcessMoveSignature, UPathFollowingComponent* , FVector& );`
- L221 _private prototype_ `DECLARE_DELEGATE_OneParam(FRequestCompletedSignature, EPathFollowingResult::Type );`
- L222 _private prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FMoveCompletedSignature, FAIRequestID , EPathFollowingResult::Type );`
- L223 _private prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FMoveComplete, FAIRequestID , const FPathFollowingResult& );`
- L226 _private member_ `FPostProcessMoveSignature PostProcessMove;` — delegate for modifying path following velocity
- L229 _private member_ `FMoveComplete OnRequestFinished;` — delegate for move completion notify
- L232 _private prototype_ `virtual void OnRegister() override;`
- L233 _private prototype_ `virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;`
- L237 _private prototype_ `virtual void Initialize();` — initialize component to use
- L240 _private prototype_ `virtual void Cleanup();` — cleanup component before destroying
- L243 _private prototype_ `virtual void UpdateCachedComponents();` — updates cached pointers to relevant owner's components
- L248 _private prototype_ `virtual FAIRequestID RequestMove(const FAIMoveRequest& RequestData, FNavPathSharedPtr InPath);` — start movement along path @return MoveId of requested move
- L251 _private prototype_ `virtual void AbortMove(const UObject& Instigator, FPathFollowingResultFlags::Type AbortFlags, FAIRequestID RequestID = FAIRequestID::CurrentRequest, EPathFollowingVelocityMode VelocityMode = EPathFollowingVelocityMode::Reset);` — aborts following path
- L256 _private prototype_ `FAIRequestID RequestMoveWithImmediateFinish(EPathFollowingResult::Type Result, EPathFollowingVelocityMode VelocityMode = EPathFollowingVelocityMode::Reset);` — create new request and finish it immediately (e.g. already at goal) @return MoveId of requested (and already finished) move
- L260 _private prototype_ `virtual void PauseMove(FAIRequestID RequestID = FAIRequestID::CurrentRequest, EPathFollowingVelocityMode VelocityMode = EPathFollowingVelocityMode::Reset);` — pause path following @param RequestID - request to pause, FAIRequestID::CurrentRequest means pause current request, regardless of its ID
- L264 _private prototype_ `virtual void ResumeMove(FAIRequestID RequestID = FAIRequestID::CurrentRequest);` — resume path following @param RequestID - request to resume, FAIRequestID::CurrentRequest means restor current request, regardless of its ID
- L267 _private prototype_ `virtual void OnPathFinished(const FPathFollowingResult& Result);` — notify about finished movement
- L269 _private function_ `inline void OnPathFinished(EPathFollowingResult::Type ResultCode, uint16 ExtraResultFlags)`
- L272 _private prototype_ `virtual void OnSegmentFinished();` — notify about finishing move along current path segment
- L275 _private prototype_ `virtual void OnPathUpdated();` — notify about changing current path: new pointer or update from path event
- L283 _private prototype_ `virtual void SetMovementComponent(UNavMovementComponent* MoveComp) final;` — `UE_DEPRECATED(5.5, "SetMovementComponent(UNavMovementComponent* MoveComp) is deprecated, please use SetNavMoveInterface(INavMoveInterface* NavMoveInterface) instead.")` — set associated movement component. Note: This function is deprecated and was marked final to purposely alert users that this function should no longer be overriden Users should instead override SetNavMovementInterface(INavMovementInterface* NavMovementInterface)!
- L286 _private prototype_ `virtual void SetNavMovementInterface(INavMovementInterface* NavMoveInterface);` — set associated nav movement interface
- L289 _private prototype_ `virtual FVector GetMoveFocus(bool bAllowStrafe) const;` — get current focal point of movement
- L296 _private prototype_ `bool HasReached(const FVector& TestPoint, EPathFollowingReachMode ReachMode, float AcceptanceRadius = UPathFollowingComponent::DefaultAcceptanceRadius) const;` — simple test for stationary agent (used as early finish condition), check if reached given point @param TestPoint - point to test @param AcceptanceRadius - allowed 2D distance @param ReachMode - modifiers for AcceptanceRadius
- L304 _private prototype_ `bool HasReached(const AActor& TestGoal, EPathFollowingReachMode ReachMode, float AcceptanceRadius = UPathFollowingComponent::DefaultAcceptanceRadius, bool bUseNavAgentGoalLocation = true) const;` — simple test for stationary agent (used as early finish condition), check if reached given goal @param TestGoal - actor to test @param AcceptanceRadius - allowed 2D distance @param ReachMode - modifiers for AcceptanceRadius @param bUseNavAgentGoalLocation - true: if the goal is a nav agent, we will use their nav agent location rather than their actual location
- L307 _private prototype_ `bool HasReached(const FAIMoveRequest& MoveRequest) const;` — simple test for stationary agent (used as early finish condition), check if reached target specified in move request
- L310 _private prototype_ `void SetBlockDetectionState(bool bEnable);` — update state of block detection
- L313 _private function_ `bool IsBlockDetectionActive() const` — @returns state of block detection
- L316 _private prototype_ `void SetBlockDetection(float DistanceThreshold, float Interval, int32 NumSamples);` — set block detection params
- L319 _private function_ `bool IsDecelerating() const` — Returns true if pathfollowing is doing deceleration at the end of the path.
- L322 _private function_ `inline bool IsStopMovementOnFinishActive() const` — @returns state of movement stopping on finish
- L325 _private function_ `inline void SetStopMovementOnFinish(bool bEnable)` — set whether movement is stopped on finish of move.
- L328 _private prototype_ `void SetPreciseReachThreshold(float AgentRadiusMultiplier, float AgentHalfHeightMultiplier);` — set threshold for precise reach tests in intermediate goals (minimal test radius)
- L331 _private prototype_ `void SetLastMoveAtGoal(bool bFinishedAtGoal);` — set status of last requested move, works only in Idle state
- L335 _private prototype_ `FVector::FReal GetRemainingPathCost() const;` — @returns estimated cost of unprocessed path segments @NOTE 0 means, that component is following final path segment or doesn't move
- L338 _private prototype_ `FNavLocation GetCurrentNavLocation() const;` — Returns current location on navigation data
- L340 _private function_ `inline EPathFollowingStatus::Type GetStatus() const`
- L346 _private function_ `inline float GetAcceptanceRadius() const`
- L347 _private function_ `inline float GetDefaultAcceptanceRadius() const`
- L348 _private prototype_ `void SetAcceptanceRadius(const float InAcceptanceRadius);`
- L349 _private function_ `inline AActor* GetMoveGoal() const`
- L350 _private function_ `inline bool HasPartialPath() const`
- L351 _private function_ `inline bool DidMoveReachGoal() const`
- L358 _private function_ `inline FAIRequestID GetCurrentRequestId() const`
- L359 _private function_ `inline uint32 GetCurrentPathIndex() const`
- L360 _private function_ `inline uint32 GetNextPathIndex() const`
- L361 _private function_ `inline UObject* GetCurrentCustomLinkOb() const`
- L362 _private function_ `inline FVector GetCurrentTargetLocation() const`
- L363 _private function_ `inline FBasedPosition GetCurrentTargetLocationBased() const`
- L364 _private function_ `inline FVector GetMoveGoalLocationOffset() const`
- L365 _private function_ `bool HasStartedNavLinkMove() const`
- L366 _private prototype_ `bool IsCurrentSegmentNavigationLink() const;`
- L367 _private prototype_ `FVector GetCurrentDirection() const;`
- L369 _private function_ `FVector GetCurrentMoveInput() const` — note that CurrentMoveInput is only valid if MovementComp->UseAccelerationForPathFollowing() == true
- L372 _private function_ `inline bool HasMovementAuthority() const` — check if path following has authority over movement (e.g. not falling) and can update own state
- L374 _private function_ `inline const FNavPathSharedPtr GetPath() const`
- L375 _private function_ `inline bool HasValidPath() const`
- L376 _private prototype_ `bool HasDirectPath() const;`
- L379 _private prototype_ `FString GetStatusDesc() const;` — readable name of current status
- L381 _private prototype_ `FString GetResultDesc(EPathFollowingResult::Type Result) const;` — readable name of result enum
- L383 _private prototype_ `void SetDestinationActor(const AActor* InDestinationActor);`
- L387 _private function_ `virtual int32 GetCurrentPathElement() const` — returns index of the currently followed element of path. Depending on the actual path it may represent different things, like a path point or navigation corridor index
- L389 _private prototype_ `virtual void GetDebugStringTokens(TArray<FString>& Tokens, TArray<EPathFollowingDebugTokens::Type>& Flags) const;`
- L390 _private prototype_ `virtual FString GetDebugString() const;`
- L392 _private prototype_ `virtual void DisplayDebug(UCanvas* Canvas, const FDebugDisplayInfo& DebugDisplay, float& YL, float& YPos) const;`
- L394 _private prototype_ `virtual void DescribeSelfToVisLog(struct FVisualLogEntry* Snapshot) const;`
- L399 _private prototype_ `virtual void OnActorBump(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);` — `UFUNCTION()` — called when moving agent collides with another actor
- L402 _private prototype_ `virtual void OnUnableToMove(const UObject& Instigator) override;`
- L403 _private prototype_ `virtual void OnStartedFalling() override;`
- L404 _private function_ `virtual void OnLanded() override`
- L405 _private prototype_ `virtual bool IsFollowingNavLink() const override;`
- L409 _private prototype_ `virtual bool IsPathFollowingAllowed() const;` — Check if path following can be activated
- L412 _private prototype_ `virtual void FinishUsingCustomLink(INavLinkCustomInterface* CustomNavLink);` — call when moving agent finishes using custom nav link, returns control back to path following
- L415 _private function_ `virtual void OnPathfindingQuery(FPathFindingQuery& Query)` — called when owner is preparing new pathfinding request
- L418 _private prototype_ `virtual void LockResource(EAIRequestPriority::Type LockSource) override;`
- L419 _private prototype_ `virtual void ClearResourceLock(EAIRequestPriority::Type LockSource) override;`
- L420 _private prototype_ `virtual void ForceUnlockResource() override;`
- L421 _private prototype_ `virtual bool IsResourceLocked() const override;`
- L425 _private prototype_ `void OnPathEvent(FNavigationPath* InPath, ENavPathEvent::Type Event);` — path observer
- L428 _private prototype_ `static void LogPathHelper(const AActor* LogOwner, FNavPathSharedPtr InLogPath, const AActor* LogGoalActor);` — helper function for sending a path for visual log
- L429 _private prototype_ `static void LogPathHelper(const AActor* LogOwner, FNavigationPath* InLogPath, const AActor* LogGoalActor);`
- L432 _private prototype_ `EPathFollowingAction::Type GetPathActionType() const;` — `UFUNCTION(BlueprintCallable, Category="AI|Components|PathFollowing", meta = (DeprecatedFunction, DeprecationMessage = "This function is now deprecated, please use AIController.GetMoveStatus instead"))`
- L435 _private prototype_ `FVector GetPathDestination() const;` — `UFUNCTION(BlueprintCallable, Category="AI|Components|PathFollowing", meta = (DeprecatedFunction, DeprecationMessage = "This function is now deprecated, please use AIController.GetImmediateMoveDestination instead"))`
- L439 _private member_ `FMoveCompletedSignature OnMoveFinished_DEPRECATED;` — This delegate is now deprecated, please use OnRequestFinished instead
- L444 _protected prototype_ `void SetStatus(EPathFollowingStatus::Type InStatus);` — Sets the current status and activates/deactivates the component if necessary
- L449 _protected member_ `TObjectPtr<UNavMovementComponent> MovementComp;` — `UE_DEPRECATED(5.5, "MovementComp is deprecated, please use NavMovementComp and the INavMoveInterface instead.")` — `UPROPERTY(transient, meta = (DeprecatedProperty, DeprecationMessage = "MovementComp is deprecated, please use NavMovementInterface and the INavMoveInterface instead."))` — deprecated associated movement component
- L452 _protected member_ `TWeakInterfacePtr<INavMovementInterface> NavMovementInterface;` — associated movement interface
- L455 _protected member_ `FWeakObjectPtr CurrentCustomLinkOb;` — currently traversed custom nav link
- L458 _protected member_ `FWeakObjectPtr MoveSegmentCustomLinkOb;` — the custom link for the next segment if there is one
- L462 _protected member_ `TObjectPtr<ANavigationData> MyNavData;` — `UPROPERTY(transient)` — navigation data for agent described in movement component
- L465 _protected member_ `FNavPathSharedPtr Path;` — requested path
- L468 _protected member_ `FSharedConstNavQueryFilter NavigationFilter;` — Navigation query filter of the current move request
- L471 _protected member_ `float MyDefaultAcceptanceRadius;` — value based on navigation agent's properties that's used for AcceptanceRadius when DefaultAcceptanceRadius is requested
- L478 _protected member_ `float AcceptanceRadius;` — min distance to destination to consider request successful. If following a partial path movement request will finish when the original goal gets within AcceptanceRadius or pathfollowing agent gets within MyDefaultAcceptanceRadius of the end of the path
- L481 _protected member_ `float CurrentAcceptanceRadius;` — min distance to end of current path segment to consider segment finished
- L484 _protected member_ `float MinAgentRadiusPct;` — part of agent radius used as min acceptance radius
- L487 _protected member_ `float MinAgentHalfHeightPct;` — part of agent height used as min acceptable height difference
- L490 _protected member_ `float WaitingTimeout;` — timeout for Waiting state, negative value = infinite
- L493 _protected member_ `FCustomMoveSharedPtr GameData;` — game specific data
- L496 _protected member_ `TWeakObjectPtr<AActor> DestinationActor;` — destination actor. Use SetDestinationActor to set this
- L499 _protected member_ `const INavAgentInterface* DestinationAgent;` — cached DestinationActor cast to INavAgentInterface. Use SetDestinationActor to set this
- L502 _protected member_ `FBasedPosition CurrentDestination;` — destination for current path segment
- L505 _protected member_ `FVector CurrentMoveInput;` — last MoveInput calculated and passed over to MovementComponent. Valid only if MovementComp->UseAccelerationForPathFollowing() == true
- L508 _protected member_ `FVector MoveOffset;` — relative offset from goal actor's location to end of path
- L511 _protected member_ `FVector LocationWhenPaused;` — agent location when movement was paused
- L517 _protected member_ `FVector OriginalMoveRequestGoalLocation;` — This is needed for partial paths when trying to figure out if following a path should finish before reaching path end, due to reaching requested acceptance radius away from original move goal Is being set for non-partial paths as well
- L520 _protected member_ `double PathTimeWhenPaused;` — timestamp of path update when movement was paused
- L525 _protected member_ `int32 PreciseAcceptanceRadiusCheckStartNodeIndex;` — Indicates a path node index at which precise "is at goal" tests are going to be performed every frame, in regards to acceptance radius
- L529 _protected member_ `TEnumAsByte<EPathFollowingStatus::Type> Status;` — current status
- L532 _protected member_ `uint8 bReachTestIncludesAgentRadius : 1;` — increase acceptance radius with agent's radius
- L535 _protected member_ `uint8 bReachTestIncludesGoalRadius : 1;` — increase acceptance radius with goal's radius
- L538 _protected member_ `uint8 bMoveToGoalOnLastSegment : 1;` — if set, target location will be constantly updated to match goal actor while following last segment of full path
- L543 _protected member_ `uint8 bMoveToGoalClampedToNavigation : 1;` — Whether to clamp the goal location to reachable navigation data when trying to track the goal actor (Only used when bMoveToGoalOnLastSegment is true) False: (default) while following the last segment, the path is allowed to adjust through obstacles and off navigation data without checks. True: the last segment's destination will be clamped at the furthest reachable location towards the goal actor.
- L546 _protected member_ `uint8 bUseBlockDetection : 1;` — if set, movement block detection will be used
- L549 _protected member_ `uint8 bCollidedWithGoal : 1;` — set when agent collides with goal actor
- L552 _protected member_ `uint8 bLastMoveReachedGoal : 1;` — set when last move request was finished at goal
- L555 _protected member_ `uint8 bStopMovementOnFinish : 1;` — if set, movement will be stopped on finishing path
- L558 _protected member_ `uint8 bIsUsingMetaPath : 1;` — if set, path following is using FMetaNavMeshPath
- L561 _protected member_ `uint8 bWalkingNavLinkStart : 1;` — gets set when agent starts following a navigation link. Cleared after agent starts falling or changes segment to a non-link one
- L564 _protected member_ `uint8 bIsDecelerating : 1;` — True if pathfollowing is doing deceleration at the end of the path. @see FollowPathSegment().
- L567 _protected member_ `uint8 bMoveSegmentIsUsingCustomLinkReachCondition : 1;` — True if the next segment is a custom link that has its own reach conditions.
- L573 _protected member_ `uint8 bTickComponentOnlyWhenMoving : 1;` — Indicates if the component activation/ticking is controlled by setting the Status (Moving --> Activated, other --> Deactivated) Note that this optimization is not used for any derived classes since those might need to tick in other cases.
- L576 _protected member_ `float BlockDetectionDistance;` — detect blocked movement when distance between center of location samples and furthest one (centroid radius) is below threshold
- L579 _protected member_ `float BlockDetectionInterval;` — interval for collecting location samples
- L582 _protected member_ `int32 BlockDetectionSampleCount;` — number of samples required for block detection
- L585 _protected member_ `double LastSampleTime;` — timestamp of last location sample
- L588 _protected member_ `int32 NextSampleIdx;` — index of next location sample in array
- L591 _protected member_ `TArray<FBasedPosition> LocationSamples;` — location samples for stuck detection
- L594 _protected member_ `int32 MoveSegmentStartIndex;` — index of path point being current move beginning
- L597 _protected member_ `int32 MoveSegmentEndIndex;` — index of path point being current move target
- L600 _protected member_ `NavNodeRef MoveSegmentStartRef;` — reference of node at segment start
- L603 _protected member_ `NavNodeRef MoveSegmentEndRef;` — reference of node at segment end
- L606 _protected member_ `FVector MoveSegmentDirection;` — direction of current move segment
- L609 _protected member_ `float CachedBrakingDistance;` — braking distance for acceleration driven path following
- L612 _protected member_ `float CachedBrakingMaxSpeed;` — max speed used for CachedBrakingDistance
- L615 _protected member_ `int32 DecelerationSegmentIndex;` — index of path point for starting deceleration
- L618 _protected prototype_ `FSharedConstNavQueryFilter ExtractNavigationFilter(const FAIMoveRequest& RequestData, FNavPathSharedPtr InPath) const;` — extract the navigation filter that should be used based on the provided MoveRequest and NavPath
- L621 _protected prototype_ `virtual void Reset();` — reset path following data
- L625 _protected prototype_ `virtual void OnNewPawn(APawn* NewPawn);` — Called if owning Controller possesses new pawn or ends up pawn-less. Doesn't get called if owner is not an AContoller
- L628 _protected prototype_ `virtual bool ShouldCheckPathOnResume() const;` — should verify if agent if still on path ater movement has been resumed?
- L631 _protected prototype_ `virtual void SetMoveSegment(int32 SegmentStartIndex);` — sets variables related to current move segment
- L634 _protected prototype_ `virtual void FollowPathSegment(float DeltaTime);` — follow current path segment
- L637 _protected prototype_ `virtual void UpdatePathSegment();` — check state of path following, update move segment if needed
- L640 _protected prototype_ `virtual void StartUsingCustomLink(INavLinkCustomInterface* CustomNavLink, const FVector& DestPoint);` — next path segment if custom nav link, try passing control to it
- L643 _protected prototype_ `virtual bool UpdateBlockDetection();` — update blocked movement detection, @returns true if new sample was added
- L646 _protected prototype_ `virtual void UpdateDecelerationData();` — updates braking distance and deceleration segment
- L649 _protected prototype_ `virtual bool HasReachedDestination(const FVector& CurrentLocation) const;` — check if move is completed
- L652 _protected prototype_ `virtual bool HasReachedCurrentTarget(const FVector& CurrentLocation) const;` — check if segment is completed
- L655 _protected prototype_ `bool HasReachedInternal(const FVector& GoalLocation, float GoalRadius, float GoalHalfHeight, const FVector& AgentLocation, float RadiusThreshold, float AgentRadiusMultiplier) const;` — check if moving agent has reached goal defined by cylinder
- L658 _protected prototype_ `void ResetMoveSegmentCustomLinkCache();` — reset the cached information about CustomLinks on the next MoveSegment
- L661 _protected prototype_ `virtual bool IsOnPath() const;` — check if agent is on path
- L664 _protected prototype_ `bool IsBlocked() const;` — check if movement is blocked
- L667 _protected function_ `inline void SetNextMoveSegment()` — switch to next segment on path
- L670 _protected function_ `inline void StoreRequestId()` — assign new request Id
- L672 _protected function_ `inline static uint32 GetNextRequestId()`
- L678 _protected prototype_ `virtual int32 DetermineStartingPathPoint(const FNavigationPath* ConsideredPath) const;` — Checks if this PathFollowingComponent is already on path, and if so determines index of next path point @return what PathFollowingComponent thinks should be next path point. INDEX_NONE if given path is invalid @note this function does not set MoveSegmentEndIndex
- L681 _protected prototype_ `virtual int32 DetermineCurrentTargetPathPoint(int32 StartIndex);` — @return index of path point, that should be target of current move segment
- L685 _protected prototype_ `virtual bool UpdateMovementComponent(bool bForce = false);` — check if movement component is valid or tries to grab one from owner @param bForce results in looking for owner's movement component even if pointer to one is already cached
- L689 _protected prototype_ `virtual bool HandlePathUpdateEvent();` — called after receiving update event from current path @return false if path was not accepted and move request needs to be aborted
- L692 _protected prototype_ `virtual void OnWaitingPathTimeout();` — called from timer if component spends too much time in Waiting state
- L695 _protected prototype_ `void ResetBlockDetectionData();` — clears Block Detection stored data effectively resetting the mechanism
- L698 _protected prototype_ `void ForceBlockDetectionUpdate();` — force creating new location sample for block detection
- L701 _protected prototype_ `virtual void UpdateMoveFocus();` — set move focus in AI owner
- L704 _protected prototype_ `virtual bool ShouldStopMovementOnPathFinished() const;` — defines if the agent should reset his velocity when the path is finished
- L709 _protected prototype_ `int32 FindPreciseAcceptanceRadiusTestsStartNodeIndex(const FNavigationPath& PathInstance, const FVector& GoalLocation) const;` — For given path finds a path node at which PathfollowingComponent should start doing precise is-goal-in-acceptance-radius  tests
- L714 _protected prototype_ `float GetFinalAcceptanceRadius(const FNavigationPath& PathInstance, const FVector OriginalGoalLocation, const FVector* PathEndOverride = nullptr) const;` — Based on Path's properties, original move goal location and requested AcceptanceRadius this function calculates actual acceptance radius to apply when testing if the agent has successfully reached requested goal's vicinity
- L717 _protected prototype_ `void DebugReachTest(float& CurrentDot, float& CurrentDistance, float& CurrentHeight, uint8& bDotFailed, uint8& bDistanceFailed, uint8& bHeightFailed) const;` — debug point reach test values
- L721 _protected prototype_ `virtual void OnNavigationInitDone();` — called when NavigationSystem finishes initial navigation data registration. This is usually required by AI agents hand-placed on levels to find MyNavData
- L727 _protected prototype_ `void OnNavDataRegistered(ANavigationData* NavData);` — `UFUNCTION()` — called when NavigationSystem registers new navigation data type while this component instance has empty MyNavData. This is usually the case for AI agents hand-placed on levels.
- L731 _protected member_ `FAIResourceLock ResourceLock;` — used to keep track of which subsystem requested this AI resource be locked
- L734 _protected member_ `FTimerHandle WaitingForPathTimer;` — timer handle for OnWaitingPathTimeout function
- L740 _private member_ `static uint32 NextRequestId;` — used for debugging purposes to be able to identify which logged information results from which request, if there was multiple ones during one frame
- L741 _private member_ `FAIRequestID CurrentRequestId;`
- L746 _private member_ `mutable FNavLocation CurrentNavLocation;` — Current location on navigation data.  Lazy-updated, so read this via GetCurrentNavLocation(). Since it makes conceptual sense for GetCurrentNavLocation() to be const but we may need to update the cached value, CurrentNavLocation is mutable.
- L752 _public member_ `static const float DefaultAcceptanceRadius;` — special float constant to symbolize "use default value". This does not contain value to be used, it's used to detect the fact that it's requested, and appropriate value from querier/doer will be pulled
- L755 _public member_ `uint8 DEBUG_bMovingDirectlyToGoal : 1;`

#### Free symbols / members of external scopes

- L25 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPathFollowing, Warning, All);`
- L34 _namespace_ `namespace EPathFollowingStatus`
- L53 _namespace_ `namespace EPathFollowingResult`
- L77 _namespace_ `namespace FPathFollowingResultFlags`
- L79 _typedef_ `typedef uint16 Type;` (scope `FPathFollowingResultFlags`)
- L81 _variable_ `inline const Type None = 0;` (scope `FPathFollowingResultFlags`)
- L84 _variable_ `inline const Type Success = (1 << 0);` (scope `FPathFollowingResultFlags`) — Reached destination (EPathFollowingResult::Success)
- L87 _variable_ `inline const Type Blocked = (1 << 1);` (scope `FPathFollowingResultFlags`) — Movement was blocked (EPathFollowingResult::Blocked)
- L90 _variable_ `inline const Type OffPath = (1 << 2);` (scope `FPathFollowingResultFlags`) — Agent is not on path (EPathFollowingResult::OffPath)
- L93 _variable_ `inline const Type UserAbort = (1 << 3);` (scope `FPathFollowingResultFlags`) — Aborted (EPathFollowingResult::Aborted)
- L96 _variable_ `inline const Type OwnerFinished = (1 << 4);` (scope `FPathFollowingResultFlags`) — Abort details: owner no longer wants to move
- L99 _variable_ `inline const Type InvalidPath = (1 << 5);` (scope `FPathFollowingResultFlags`) — Abort details: path is no longer valid
- L102 _variable_ `inline const Type MovementStop = (1 << 6);` (scope `FPathFollowingResultFlags`) — Abort details: unable to move
- L105 _variable_ `inline const Type NewRequest = (1 << 7);` (scope `FPathFollowingResultFlags`) — Abort details: new movement request was received
- L108 _variable_ `inline const Type ForcedScript = (1 << 8);` (scope `FPathFollowingResultFlags`) — Abort details: blueprint MoveTo function was called
- L111 _variable_ `inline const Type AlreadyAtGoal = (1 << 9);` (scope `FPathFollowingResultFlags`) — Finish details: never started, agent was already at goal
- L114 _variable_ `inline const Type FirstGameplayFlagShift = 10;` (scope `FPathFollowingResultFlags`) — Can be used to create project specific reasons
- L116 _variable_ `inline const Type UserAbortFlagMask = ~(Success | Blocked | OffPath);` (scope `FPathFollowingResultFlags`)
- L118 _prototype_ `FString ToString(uint16 Value);` (scope `FPathFollowingResultFlags`)
- L141 _namespace_ `namespace EPathFollowingAction`
- L154 _namespace_ `namespace EPathFollowingRequestResult`
- L173 _namespace_ `namespace EPathFollowingDebugTokens`
- L185 _namespace_ `namespace EPathFollowingMessage`
- L220 _delegate_ `DECLARE_DELEGATE_TwoParams(FPostProcessMoveSignature, UPathFollowingComponent* , FVector& );`
- L221 _delegate_ `DECLARE_DELEGATE_OneParam(FRequestCompletedSignature, EPathFollowingResult::Type );`
- L222 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FMoveCompletedSignature, FAIRequestID , EPathFollowingResult::Type );`
- L223 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FMoveComplete, FAIRequestID , const FPathFollowingResult& );`

### `Source/Runtime/AIModule/Classes/Navigation/PathFollowingManager.h` (Public)


#### class `UPathFollowingManager`  
`class UPathFollowingManager : public UObject, public IPathFollowingManagerInterface`  
_L13-21_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,IPathFollowingManagerInterface`
- L17 _public prototype_ `UPathFollowingManager(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L19 _public prototype_ `static void StopMovement(const AController& Controller);`
- L20 _public prototype_ `static bool IsFollowingAPath(const AController& Controller);`

### `Source/Runtime/AIModule/Classes/Navigation/RecastGraphAStar.h` (Public)


#### struct `FRecastGraphPolicy`  
`struct FRecastGraphPolicy`  
_L14-20_
- L16 _public member_ `static const int32 NodePoolSize = 2048;`
- L17 _public member_ `static const int32 OpenSetSize = 2048;`
- L18 _public member_ `static const int32 FatalPathLength = 10000;`
- L19 _public member_ `static const bool bReuseNodePoolInSubsequentSearches = false;`

#### struct `FRecastNeighbour`  
`struct FRecastNeighbour`  
_L36-54_
- L41 _public function_ `inline operator dtPolyRef() const`
- L47 _protected function_ `inline FRecastNeighbour(dtPolyRef InNodeRef, unsigned char InSide = 0) : NodeRef`
- L52 _public member_ `dtPolyRef NodeRef;`
- L53 _public member_ `unsigned char Side;`

#### struct `FRecastAStarResult`  
`struct FRecastAStarResult : public dtQueryResult`  
_L56-68_
- inherits: `dtQueryResult`
- L58 _public function_ `void Reset(const int32 PathLength)`
- L62 _public function_ `void AddZeroed(const int32 PathLength)`
- L67 _public prototype_ `dtPolyRef SetPathInfo(const int32 Index, const FRecastAStarSearchNode& SearchNode);`

#### struct `FRecastGraphWrapper`  
`struct FRecastGraphWrapper`  
_L72-120_
- reflection: `USTRUCT()`
- L77 _public function_ `FRecastGraphWrapper()`
- L81 _public prototype_ `void Initialize(const ARecastNavMesh* InRecastNavMeshActor);` — Initialization of the wrapper from the RecastNavMesh pointer
- L84 _public prototype_ `dtStatus ConvertToRecastStatus(const FRecastAStar& Algo, const FRecastGraphAStarFilter& Filter, const EGraphAStarResult AStarResult) const;` — Implementation that converts EGraphAStarResult into a dtStatus
- L88 _public typedef_ `typedef dtPolyRef FNodeRef;` — FGraphAStar: TGraph
- L90 _public function_ `inline bool IsValidRef(const dtPolyRef& NodeRef) const`
- L94 _public prototype_ `FRecastNeighbour GetNeighbour(const FRecastAStarSearchNode& Node, const int32 NeighbourIndex) const;`
- L97 _public function_ `inline const dtNavMeshQuery& GetRecastQuery() const`
- L104 _protected function_ `inline const ARecastNavMesh* GetRecastNavMeshActor() const`
- L105 _protected function_ `inline const dtNavMesh* GetDetourNavMesh() const`
- L106 _protected prototype_ `void BindFilter(FRecastGraphAStarFilter& AStarFilter);`
- L111 _private member_ `TObjectPtr<const ARecastNavMesh> RecastNavMeshActor = nullptr;` — `UPROPERTY(Transient)`
- L114 _private member_ `const dtNavMesh* DetourNavMesh = nullptr;`
- L116 _private member_ `dtNavMeshQuery RecastQuery;`
- L118 _private member_ `mutable unsigned int CachedNextLink = DT_NULL_LINK;`

#### struct `FRecastAStarSearchNode`  
`struct FRecastAStarSearchNode : public FGraphAStarDefaultNode<FRecastGraphWrapper>`  
_L123-165_
- inherits: `FGraphAStarDefaultNode<FRecastGraphWrapper>`
- L125 _public typedef_ `typedef FGraphAStarDefaultNode<FRecastGraphWrapper> Super;`
- L127 _public function_ `inline FRecastAStarSearchNode(const dtPolyRef InNodeRef = INVALID_NAVNODEREF, FVector InPosition = FVector(TNumericLimits<FVector::FReal>::Max(), TNumericLimits<FVector::FReal>::Max(), TNumericLimits<FVector::FReal>::Max()) ) : Super(InNodeRef) , Tile`
- L134 _public prototype_ `FRecastAStarSearchNode(const FRecastAStarSearchNode& Other) = default;`
- L135 _public prototype_ `FGraphAStarDefaultNode& operator=(const FGraphAStarDefaultNode& Other) = delete;`
- L137 _public member_ `mutable const dtMeshTile* Tile;`
- L138 _public member_ `mutable const dtPoly* Poly;`
- L139 _public member_ `mutable FVector::FReal Position[3];` — Position in Recast World coordinate system
- L141 _public function_ `inline operator dtPolyRef() const`
- L146 _public function_ `inline void Initialize(const FRecastGraphWrapper& RecastGraphWrapper) const`
- L151 _public function_ `inline bool HasValidCacheInfo() const`
- L156 _public function_ `inline void CacheInfo(const FRecastGraphWrapper& RecastGraphWrapper, const FRecastAStarSearchNode& FromNode) const`

#### struct `FRecastAStar`  
`struct FRecastAStar : public FGraphAStar<FRecastGraphWrapper, FRecastGraphPolicy, FRecastAStarSearchNode>`  
_L167-173_
- inherits: `FGraphAStar<FRecastGraphWrapper,FRecastGraphPolicy,FRecastAStarSearchNode>`
- L169 _public typedef_ `typedef FGraphAStar<FRecastGraphWrapper, FRecastGraphPolicy, FRecastAStarSearchNode> Super;`
- L170 _public function_ `FRecastAStar(const FRecastGraphWrapper& Graph) : Super(Graph)`

#### struct `FRecastGraphAStarFilter`  
`struct FRecastGraphAStarFilter`  
_L175-254_
- L177 _public prototype_ `FRecastGraphAStarFilter(FRecastGraphWrapper& InRecastGraphWrapper, const FRecastQueryFilter& InFilter, uint32 InMaxSearchNodes, const FVector::FReal InCostLimit, const UObject* Owner);`
- L179 _public function_ `inline bool WantsPartialSolution() const`
- L183 _public function_ `inline FVector::FReal GetHeuristicScale() const`
- L188 _public function_ `inline FVector::FReal GetHeuristicCost(const FRecastAStarSearchNode& StartNode, const FRecastAStarSearchNode& EndNode) const`
- L197 _public function_ `inline FVector::FReal GetTraversalCost(const FRecastAStarSearchNode& StartNode, const FRecastAStarSearchNode& EndNode) const`
- L209 _public function_ `inline bool IsTraversalAllowed(const dtPolyRef& NodeA, const FRecastNeighbour& NodeB) const`
- L221 _public function_ `inline bool ShouldIgnoreClosedNodes() const`
- L226 _public function_ `inline bool ShouldIncludeStartNodeInPath() const`
- L231 _public function_ `inline uint32 GetMaxSearchNodes() const`
- L236 _public function_ `inline FVector::FReal GetCostLimit() const`
- L245 _protected function_ `inline const FRecastQueryFilter& GetFilter() const`
- L246 _protected function_ `inline FRecastSpeciaLinkFilter& GetLinkFilter()`
- L249 _private member_ `const FRecastQueryFilter& Filter;`
- L250 _private member_ `FRecastSpeciaLinkFilter LinkFilter;`
- L251 _private member_ `const FRecastGraphWrapper& RecastGraphWrapper;`
- L252 _private member_ `uint32 MaxSearchNodes;`
- L253 _private member_ `FVector::FReal CostLimit;`

#### Free symbols / members of external scopes

- L28 _typedef_ `typedef uint64 dtPolyRef;`
- L29 _typedef_ `typedef unsigned int dtStatus;`

### `Source/Runtime/AIModule/Classes/Perception/AIPerceptionComponent.h` (Public)


#### struct `FActorPerceptionUpdateInfo`  
`struct FActorPerceptionUpdateInfo`  
_L27-45_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Sensed Actor's Update Data"))`
- L33 _public member_ `int32 TargetId = -1;` — `UPROPERTY(BlueprintReadWrite, Category = "AI|Perception")` — Id of to the stimulus source
- L37 _public member_ `TWeakObjectPtr<AActor> Target;` — `UPROPERTY(BlueprintReadWrite, Category = "AI|Perception")` — Actor associated to the stimulus (can be null)
- L41 _public member_ `FAIStimulus Stimulus;` — `UPROPERTY(BlueprintReadWrite, Category = "AI|Perception")` — Updated stimulus
- L43 _public prototype_ `FActorPerceptionUpdateInfo() = default;`
- L44 _public prototype_ `FActorPerceptionUpdateInfo(const int32 TargetId, const TWeakObjectPtr<AActor>& Target, const FAIStimulus& Stimulus);`

#### struct `FActorPerceptionInfo`  
`struct FActorPerceptionInfo`  
_L49-179_
- L51 _public member_ `TWeakObjectPtr<AActor> Target;`
- L53 _public member_ `TArray<FAIStimulus> LastSensedStimuli;`
- L57 _public member_ `FAISenseID DominantSense;` — if != MAX indicates the sense that takes precedence over other senses when it comes to determining last stimulus location
- L60 _public member_ `uint32 bIsHostile : 1;` — indicates whether this Actor is hostile to perception holder
- L63 _public member_ `uint32 bIsFriendly : 1;` — indicates whether this Actor is friendly to perception holder
- L65 _public function_ `explicit FActorPerceptionInfo(AActor* InTarget = nullptr) : Target(InTarget), DominantSense(FAISenseID::InvalidID()), bIsHostile(false), bIsFriendly(false)`
- L73 _public function_ `FVector GetLastStimulusLocation(float* OptionalAge = nullptr) const` — Retrieves last known location. Active (last reported as "successful") stimuli are preferred.
- L108 _public function_ `bool HasAnyKnownStimulus() const` — it includes both currently live (visible) stimulus, as well as "remembered" ones
- L123 _public function_ `bool HasAnyCurrentStimulus() const` — Indicates currently live (visible) stimulus from any sense
- L142 _public function_ `inline FVector GetStimulusLocation(const FAISenseID Sense) const` — Retrieves location of the last sensed stimuli for a given sense @param Sense	The AISenseID of the sense @return Location of the last sensed stimuli or FAISystem::InvalidLocation if given sense has never registered related Target actor or if last stimuli has expired.
- L152 _public function_ `inline FVector GetReceiverLocation(const FAISenseID Sense) const` — Retrieves receiver location of the last sense stimuli for a given sense @param Sense	The AISenseID of the sense @return Location of the receiver for the last sensed stimuli or FAISystem::InvalidLocation if given sense has never registered related Target actor or last stimuli has expired.
- L162 _public function_ `inline bool HasKnownStimulusOfSense(const FAISenseID Sense) const` — Indicates a currently active or "remembered" stimuli for a given sense @param Sense	The AISenseID of the sense @return True if a target has been registered (even if not currently sensed) for the given sense and the stimuli is not expired.
- L172 _public function_ `inline bool IsSenseActive(const FAISenseID Sense) const` — Indicates a currently active stimuli for a given sense @param Sense	The AISenseID of the sense @return True if a target is still sensed for the given sense and the stimuli is not expired.
- L178 _public prototype_ `void Merge(const FActorPerceptionInfo& Other);` — takes all "newer" info from Other and absorbs it

#### struct `FActorPerceptionBlueprintInfo`  
`struct FActorPerceptionBlueprintInfo`  
_L182-201_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Sensed Actor's Data"))`
- L187 _public member_ `TObjectPtr<AActor> Target;` — `UPROPERTY(BlueprintReadWrite, Category = "AI|Perception")`
- L190 _public member_ `TArray<FAIStimulus> LastSensedStimuli;` — `UPROPERTY(BlueprintReadWrite, Category = "AI|Perception")`
- L193 _public member_ `uint32 bIsHostile : 1;` — `UPROPERTY(BlueprintReadWrite, Category = "AI|Perception")`
- L196 _public member_ `uint32 bIsFriendly : 1;` — `UPROPERTY(BlueprintReadWrite, Category = "AI|Perception")`
- L198 _public function_ `FActorPerceptionBlueprintInfo() : Target(nullptr), bIsHostile(false), bIsFriendly(false)`
- L200 _public prototype_ `FActorPerceptionBlueprintInfo(const FActorPerceptionInfo& Info);`

#### class `UAIPerceptionComponent`  
`class UAIPerceptionComponent : public UActorComponent`  
_L208-467_
- reflection: `UCLASS(ClassGroup=AI, HideCategories=(Activation, Collision), meta=(BlueprintSpawnableComponent), config=Game, MinimalAPI)`
- inherits: `UActorComponent`
- desc: AIPerceptionComponent is used to register as stimuli listener in AIPerceptionSystem and gathers registered stimuli. UpdatePerception is called when component gets new stimuli (batched)
- L212 _private member_ `static const int32 InitialStimuliToProcessArraySize;`
- L214 _private typedef_ `typedef TMap<TObjectKey<AActor>, FActorPerceptionInfo> TActorPerceptionContainer;`
- L215 _private typedef_ `typedef TActorPerceptionContainer FActorPerceptionContainer;`
- L219 _protected member_ `TArray<TObjectPtr<UAISenseConfig>> SensesConfig;` — `UPROPERTY(EditDefaultsOnly, Instanced, Category = "AI Perception")`
- L224 _protected member_ `TSubclassOf<UAISense> DominantSense;` — `UPROPERTY(EditDefaultsOnly, Category = "AI Perception")` — Indicated sense that takes precedence over other senses when determining sensed actor's location. Should be set to one of the senses configured in SensesConfig, or None.
- L226 _protected member_ `FAISenseID DominantSenseID;`
- L229 _protected member_ `TObjectPtr<AAIController> AIOwner;` — `UPROPERTY(Transient)`
- L232 _protected member_ `FPerceptionChannelAllowList PerceptionFilter;` — @todo this field is misnamed. It's an allow list.
- L235 _private member_ `FPerceptionListenerID PerceptionListenerId;`
- L236 _private member_ `FActorPerceptionContainer PerceptualData;`
- L251 _protected member_ `TArray<FStimulusToProcess> StimuliToProcess;`
- L254 _protected member_ `TArray<float> MaxActiveAge;` — max age of stimulus to consider it "active" (e.g. target is visible)
- L260 _private member_ `uint32 bForgetStaleActors : 1;` — Determines whether all knowledge of previously sensed actors will be removed or not when they become stale. That is, when they are no longer perceived and have exceeded the max age of the sense.
- L262 _private member_ `uint32 bCleanedUp : 1;`
- L266 _public prototype_ `virtual void PostInitProperties() override;`
- L267 _public prototype_ `virtual void BeginDestroy() override;`
- L268 _public prototype_ `virtual void OnRegister() override;`
- L269 _public prototype_ `virtual void OnUnregister() override;`
- L272 _public prototype_ `void OnOwnerEndPlay(AActor* Actor, EEndPlayReason::Type EndPlayReason);` — `UFUNCTION()`
- L274 _public prototype_ `void GetLocationAndDirection(FVector& Location, FVector& Direction) const;`
- L275 _public prototype_ `const AActor* GetBodyActor() const;`
- L276 _public prototype_ `AActor* GetMutableBodyActor();`
- L278 _public function_ `inline FPerceptionChannelAllowList GetPerceptionFilter() const`
- L280 _public prototype_ `FGenericTeamId GetTeamIdentifier() const;`
- L281 _public function_ `inline FPerceptionListenerID GetListenerId() const`
- L283 _public prototype_ `FVector GetActorLocation(const AActor& Actor) const;`
- L284 _public function_ `inline const FActorPerceptionInfo* GetActorInfo(const AActor& Actor) const`
- L285 _public function_ `inline FActorPerceptionContainer::TIterator GetPerceptualDataIterator()`
- L286 _public function_ `inline FActorPerceptionContainer::TConstIterator GetPerceptualDataConstIterator() const`
- L288 _public prototype_ `virtual void GetHostileActors(TArray<AActor*>& OutActors) const;`
- L290 _public prototype_ `void GetHostileActorsBySense(TSubclassOf<UAISense> SenseToFilterBy, TArray<AActor*>& OutActors) const;`
- L295 _public prototype_ `bool GetFilteredActors(const TFunctionRef<bool(const FActorPerceptionInfo&)>& Predicate, TArray<AActor*>& OutActors) const;` — Retrieves all actors in PerceptualData matching the predicate. @return whether dead data (invalid actors) have been found while iterating over PerceptualData
- L298 _public prototype_ `const FActorPerceptionInfo* GetFreshestTrace(const FAISenseID Sense) const;` — @note Will stop on first age 0 stimulus
- L300 _public prototype_ `void SetDominantSense(TSubclassOf<UAISense> InDominantSense);`
- L301 _public function_ `inline FAISenseID GetDominantSenseID() const`
- L302 _public function_ `inline TSubclassOf<UAISense> GetDominantSense() const`
- L303 _public prototype_ `UAISenseConfig* GetSenseConfig(const FAISenseID& SenseID);`
- L304 _public prototype_ `const UAISenseConfig* GetSenseConfig(const FAISenseID& SenseID) const;`
- L307 _public function_ `template<typename T, typename = std::enable_if_t<std::is_base_of_v<UAISenseConfig, T>>> T* GetSenseConfig() const`
- L319 _public prototype_ `void ConfigureSense(UAISenseConfig& SenseConfig);`
- L321 _public typedef_ `typedef TArray<UAISenseConfig*>::TConstIterator TAISenseConfigConstIterator;`
- L322 _public prototype_ `TAISenseConfigConstIterator GetSensesConfigIterator() const;`
- L326 _public prototype_ `void RequestStimuliListenerUpdate();` — `UFUNCTION(BlueprintCallable, Category="AI|Perception")` — Notifies AIPerceptionSystem to update properties for this "stimuli listener"
- L329 _public prototype_ `void UpdatePerceptionAllowList(const FAISenseID Channel, const bool bNewValue);` — Allows toggling senses on and off
- L332 _public function_ `void UpdatePerceptionWhitelist(const FAISenseID Channel, const bool bNewValue)` — `UE_DEPRECATED(5.0, "Use UpdatePerceptionAllowList instead")`
- L338 _public prototype_ `void RegisterStimulus(AActor* Source, const FAIStimulus& Stimulus);`
- L339 _public prototype_ `void ProcessStimuli();`
- L341 _public prototype_ `bool AgeStimuli(const float ConstPerceptionAgingRate);` — Returns true if, as result of stimuli aging, this listener needs an update (like if some stimuli expired)
- L342 _public prototype_ `void ForgetActor(AActor* ActorToForget);`
- L346 _public prototype_ `void ForgetAll();` — `UFUNCTION(BlueprintCallable, Category = "AI|Perception")` — basically cleans up PerceptualData, resulting in loss of all previous perception
- L348 _public prototype_ `float GetYoungestStimulusAge(const AActor& Source) const;`
- L349 _public prototype_ `bool HasAnyActiveStimulus(const AActor& Source) const;`
- L350 _public prototype_ `bool HasAnyCurrentStimulus(const AActor& Source) const;`
- L351 _public prototype_ `bool HasActiveStimulus(const AActor& Source, const FAISenseID Sense) const;`
- L354 _public prototype_ `virtual void DescribeSelfToGameplayDebugger(FGameplayDebuggerCategory* DebuggerCategory) const;`
- L358 _public prototype_ `virtual void DescribeSelfToVisLog(FVisualLogEntry* Snapshot) const;`
- L365 _public prototype_ `void GetPerceivedHostileActors(TArray<AActor*>& OutActors) const;` — `UFUNCTION(BlueprintCallable, Category = "AI|Perception")`
- L368 _public prototype_ `void GetPerceivedHostileActorsBySense(const TSubclassOf<UAISense> SenseToUse, TArray<AActor*>& OutActors) const;` — `UFUNCTION(BlueprintCallable, Category = "AI|Perception")`
- L372 _public prototype_ `void GetCurrentlyPerceivedActors(TSubclassOf<UAISense> SenseToUse, TArray<AActor*>& OutActors) const;` — `UFUNCTION(BlueprintCallable, Category = "AI|Perception")` — If SenseToUse is none all actors currently perceived in any way will get fetched
- L376 _public prototype_ `void GetKnownPerceivedActors(TSubclassOf<UAISense> SenseToUse, TArray<AActor*>& OutActors) const;` — `UFUNCTION(BlueprintCallable, Category = "AI|Perception")` — If SenseToUse is none all actors ever perceived in any way (and not forgotten yet) will get fetched
- L380 _public prototype_ `bool GetActorsPerception(AActor* Actor, FActorPerceptionBlueprintInfo& Info);` — `UFUNCTION(BlueprintCallable, Category = "AI|Perception")` — Retrieves whatever has been sensed about given actor
- L385 _public prototype_ `void SetSenseEnabled(TSubclassOf<UAISense> SenseClass, const bool bEnable);` — `UFUNCTION(BlueprintCallable, Category = "AI|Perception")` — Note that this works only if given sense has been already configured for this component instance
- L390 _public prototype_ `bool IsSenseEnabled(TSubclassOf<UAISense> SenseClass) const;` — `UFUNCTION(BlueprintCallable, Category = "AI|Perception")` — Returns if a sense is active. Note that this works only if given sense has been already configured for this component instance
- L396 _public member_ `FPerceptionUpdatedDelegate OnPerceptionUpdated;` — `UPROPERTY(BlueprintAssignable)`
- L408 _public member_ `FActorPerceptionForgetUpdatedDelegate OnTargetPerceptionForgotten;` — `UPROPERTY(BlueprintAssignable)` — Notifies all bound delegates that the perception info has been forgotten for a given target. The notification gets broadcast when all stimuli of a given target expire or the target was explicitly forgotten. @note The target forgetting functionality must be enabled through the AIPerceptionSystem.bForgetStaleActors flag from Project Settings. @param	SourceActor	Actor associated to the stimulus (can not be null) @param	Stimulus	Updated stimulus @see ForgetActor, ForgetAll
- L423 _public member_ `FActorPerceptionUpdatedDelegate OnTargetPerceptionUpdated;` — `UPROPERTY(BlueprintAssignable)` — Notifies all bound objects that perception info has been updated for a given target. The notification is broadcast for any received stimulus or on change of state according to the stimulus configuration. Note - This delegate will not be called if source actor is no longer valid by the time a stimulus gets processed. Use OnTargetPerceptionInfoUpdated providing a source id to handle those cases. @param	SourceActor	Actor associated to the stimulus (can not be null) @param	Stimulus	Updated stimulus
- L436 _public member_ `FActorPerceptionInfoUpdatedDelegate OnTargetPerceptionInfoUpdated;` — `UPROPERTY(BlueprintAssignable)` — Notifies all bound objects that perception info has been updated for a given target. The notification is broadcast for any received stimulus or on change of state according to the stimulus configuration. Note - This delegate will be called even if source actor is no longer valid by the time a stimulus gets processed so it is better to use source id for bookkeeping. @param	UpdateInfo	Data structure providing information related to the updated perceptual data
- L439 _protected function_ `FActorPerceptionContainer& GetPerceptualData()`
- L440 _protected function_ `const FActorPerceptionContainer& GetPerceptualData() const`
- L443 _protected prototype_ `virtual void CleanUp();` — called to clean up on owner's end play or destruction
- L445 _protected prototype_ `void RemoveDeadData();`
- L449 _protected prototype_ `virtual void RefreshStimulus(FAIStimulus& StimulusStore, const FAIStimulus& NewStimulus) final;` — `UE_DEPRECATED(5.6, "RefreshStimulus is deprecated. Use ConditionallyStoreSuccessfulStimulus() instead.")` — Updates the stimulus entry in StimulusStore, if NewStimulus is more recent or stronger
- L456 _protected prototype_ `virtual bool ConditionallyStoreSuccessfulStimulus(FAIStimulus& StimulusStore, const FAIStimulus& NewStimulus);` — Updates the stimulus entry in StimulusStore, if NewStimulus is more recent or stronger @return whether the detected change in stimulus values should be considered a "perception change" (and, in consequence, emit appropriate notifications) - defaults to `false`
- L459 _protected prototype_ `virtual void HandleExpiredStimulus(FAIStimulus& StimulusStore);` — @note no need to call super implementation, it's there just for some validity checking
- L464 _private prototype_ `void RegisterSenseConfig(const UAISenseConfig& SenseConfig, UAIPerceptionSystem& AIPerceptionSys);`
- L465 _private function_ `void StoreListenerId(const FPerceptionListenerID InListenerId)`
- L466 _private prototype_ `void SetMaxStimulusAge(const FAISenseID SenseId, float MaxAge);`

#### struct `UAIPerceptionComponent::FStimulusToProcess`  
`struct FStimulusToProcess`  
_L239-249_
- L241 _public member_ `TObjectKey<AActor> Source;`
- L242 _public member_ `FAIStimulus Stimulus;`
- L244 _public function_ `FStimulusToProcess(AActor* InSource, const FAIStimulus& InStimulus) : Source(InSource), Stimulus(InStimulus)`

#### Free symbols / members of external scopes

- L22 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPerceptionUpdatedDelegate, const TArray<AActor*>&, UpdatedActors);`
- L22 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPerceptionUpdatedDelegate, const TArray<AActor*>&, UpdatedActors);`
- L23 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FActorPerceptionUpdatedDelegate, AActor*, Actor, FAIStimulus, Stimulus);`
- L23 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FActorPerceptionUpdatedDelegate, AActor*, Actor, FAIStimulus, Stimulus);`
- L24 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FActorPerceptionForgetUpdatedDelegate, AActor*, Actor);`
- L24 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FActorPerceptionForgetUpdatedDelegate, AActor*, Actor);`
- L47 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FActorPerceptionInfoUpdatedDelegate, const FActorPerceptionUpdateInfo&, UpdateInfo);`
- L47 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FActorPerceptionInfoUpdatedDelegate, const FActorPerceptionUpdateInfo&, UpdateInfo);`

### `Source/Runtime/AIModule/Classes/Perception/AIPerceptionListenerInterface.h` (Public)


#### class `UAIPerceptionListenerInterface`  
`class UAIPerceptionListenerInterface : public UInterface`  
_L13-16_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IAIPerceptionListenerInterface`  
`class IAIPerceptionListenerInterface`  
_L18-23_
- L22 _private function_ `virtual UAIPerceptionComponent* GetPerceptionComponent()`

### `Source/Runtime/AIModule/Classes/Perception/AIPerceptionStimuliSourceComponent.h` (Public)


#### class `UAIPerceptionStimuliSourceComponent`  
`class UAIPerceptionStimuliSourceComponent : public UActorComponent`  
_L15-53_
- reflection: `UCLASS(ClassGroup = AI, HideCategories = (Activation, Collision), meta = (BlueprintSpawnableComponent), config = Game, MinimalAPI)`
- inherits: `UActorComponent`
- desc: Gives owning actor a way to auto-register as perception system's sense stimuli source
- L21 _protected member_ `uint32 bAutoRegisterAsSource : 1;` — `UPROPERTY(EditAnywhere, Category = "AI Perception", BlueprintReadOnly, config)`
- L23 _protected member_ `uint32 bSuccessfullyRegistered : 1;`
- L26 _protected member_ `TArray<TSubclassOf<UAISense> > RegisterAsSourceForSenses;` — `UPROPERTY(EditAnywhere, Category = "AI Perception", BlueprintReadOnly)`
- L28 _protected prototype_ `virtual void OnRegister() override;`
- L31 _public prototype_ `UAIPerceptionStimuliSourceComponent(const FObjectInitializer& ObjectInitializer);`
- L34 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L40 _public prototype_ `void RegisterWithPerceptionSystem();` — `UFUNCTION(BlueprintCallable, Category = "AI|Perception")` — Registers owning actor as source of stimuli for senses specified in RegisterAsSourceForSenses. Note that you don't have to do it if bAutoRegisterAsSource == true
- L44 _public prototype_ `void RegisterForSense(TSubclassOf<UAISense> SenseClass);` — `UFUNCTION(BlueprintCallable, Category = "AI|Perception")` — Registers owning actor as source for specified sense class
- L48 _public prototype_ `void UnregisterFromPerceptionSystem();` — `UFUNCTION(BlueprintCallable, Category = "AI|Perception")` — Unregister owning actor from being a source of sense stimuli
- L52 _public prototype_ `void UnregisterFromSense(TSubclassOf<UAISense> SenseClass);` — `UFUNCTION(BlueprintCallable, Category = "AI|Perception")` — Unregisters owning actor from sources list of a specified sense class

### `Source/Runtime/AIModule/Classes/Perception/AIPerceptionSystem.h` (Public)


#### class `UAIPerceptionSystem`  
`class UAIPerceptionSystem : public UAISubsystem`  
_L30-213_
- reflection: `UCLASS(ClassGroup=AI, config=Game, defaultconfig, MinimalAPI)`
- inherits: `UAISubsystem`
- desc: AI Subsystem managing AI Perception through registered AI Senses between Listeners and Stimuli Sources
- L36 _public prototype_ `UAIPerceptionSystem(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L39 _public prototype_ `virtual void Tick(float DeltaTime) override;` — FTickableGameObject begin
- L40 _public prototype_ `virtual TStatId GetStatId() const override;`
- L44 _protected member_ `AIPerception::FListenerMap ListenerContainer;`
- L47 _protected member_ `TArray<TObjectPtr<UAISense>> Senses;` — `UPROPERTY()`
- L50 _protected member_ `float PerceptionAgingRate;` — `UPROPERTY(config, EditAnywhere, Category = Perception)`
- L52 _protected member_ `FActorEndPlaySignature::FDelegate StimuliSourceEndPlayDelegate;`
- L55 _protected member_ `TMap<const AActor*, FPerceptionStimuliSource> RegisteredStimuliSources;` — not a UPROPERTY on purpose so that we have a control over when stuff gets removed from the map
- L57 _protected member_ `uint32 bHandlePawnNotification : 1;`
- L67 _protected member_ `TArray<FDelayedStimulus> DelayedStimuli;`
- L83 _protected member_ `TArray<FPerceptionSourceRegistration> SourcesToRegister;`
- L87 _public function_ `inline bool IsSenseInstantiated(const FAISenseID& SenseID) const`
- L90 _public prototype_ `void UpdateListener(UAIPerceptionComponent& Listener);` — Registers listener if not registered
- L91 _public prototype_ `void UnregisterListener(UAIPerceptionComponent& Listener);`
- L94 _public function_ `template<typename FEventClass, typename FSenseClass = typename FEventClass::FSenseClass> void OnEvent(const FEventClass& Event)`
- L105 _public function_ `template<typename FEventClass, typename FSenseClass = typename FEventClass::FSenseClass> void OnEventsBatch(const TArray<FEventClass>& Events)`
- L119 _public function_ `template<typename FEventClass, typename FSenseClass = typename FEventClass::FSenseClass> static void OnEvent(UWorld* World, const FEventClass& Event)`
- L129 _public prototype_ `void ReportEvent(UAISenseEvent* PerceptionEvent);` — `UFUNCTION(BlueprintCallable, Category = "AI|Perception")`
- L132 _public prototype_ `static void ReportPerceptionEvent(UObject* WorldContextObject, UAISenseEvent* PerceptionEvent);` — `UFUNCTION(BlueprintCallable, Category = "AI|Perception", meta = (WorldContext="WorldContextObject"))`
- L136 _public prototype_ `template<typename FSenseClass> void RegisterSource(AActor& SourceActor);` — Registers a source of given sense's stimuli
- L139 _public prototype_ `void RegisterSource(AActor& SourceActor);` — Registers given actor as a source for all registered senses
- L141 _public prototype_ `void RegisterSourceForSenseClass(TSubclassOf<UAISense> Sense, AActor& Target);`
- L147 _public prototype_ `void UnregisterSource(AActor& SourceActor, const TSubclassOf<UAISense> Sense = {});` — unregisters given actor from the list of active stimuli sources @param Sense if null will result in removing SourceActor from all the senses
- L149 _public prototype_ `void OnListenerForgetsActor(const UAIPerceptionComponent& Listener, AActor& ActorToForget);`
- L150 _public prototype_ `void OnListenerForgetsAll(const UAIPerceptionComponent& Listener);`
- L151 _public prototype_ `void OnListenerConfigUpdated(FAISenseID SenseID, const UAIPerceptionComponent& Listener);`
- L153 _public prototype_ `void RegisterDelayedStimulus(FPerceptionListenerID ListenerId, float Delay, AActor* Instigator, const FAIStimulus& Stimulus);`
- L155 _public prototype_ `static UAIPerceptionSystem* GetCurrent(UObject* WorldContextObject);`
- L156 _public prototype_ `static UAIPerceptionSystem* GetCurrent(UWorld& World);`
- L158 _public prototype_ `static void MakeNoiseImpl(AActor* NoiseMaker, float Loudness, APawn* NoiseInstigator, const FVector& NoiseLocation, float MaxRange, FName Tag);`
- L161 _public prototype_ `static bool RegisterPerceptionStimuliSource(UObject* WorldContextObject, TSubclassOf<UAISense> Sense, AActor* Target);` — `UFUNCTION(BlueprintCallable, Category = "AI|Perception", meta = (WorldContext="WorldContextObject"))`
- L163 _public prototype_ `FAISenseID RegisterSenseClass(TSubclassOf<UAISense> SenseClass);`
- L166 _public prototype_ `static TSubclassOf<UAISense> GetSenseClassForStimulus(UObject* WorldContextObject, const FAIStimulus& Stimulus);` — `UFUNCTION(BlueprintCallable, Category = "AI|Perception", meta = (WorldContext="WorldContextObject"))`
- L169 _public prototype_ `virtual void DescribeSelfToGameplayDebugger(FGameplayDebuggerCategory& DebuggerCategory) const;`
- L175 _protected prototype_ `void OnPerceptionStimuliSourceEndPlay(AActor* Actor, EEndPlayReason::Type EndPlayReason);` — `UFUNCTION()`
- L178 _protected prototype_ `void RegisterSource(FAISenseID SenseID, AActor& SourceActor);` — requests registration of a given actor as a perception data source for specified sense
- L182 _protected prototype_ `virtual void RegisterAllPawnsAsSourcesForSense(FAISenseID SenseID);` — iterates over all pawns and registeres them as a source for sense indicated by SenseID. Note that this will be performed only for senses that request that (see UAISense.bAutoRegisterAllPawnsAsSources).
- L191 _protected prototype_ `bool DeliverDelayedStimuli(EDelayedStimulusSorting Sorting);` — sorts DelayedStimuli and delivers all the ones that are no longer "in the future" @return true if any stimuli has become "current" stimuli (meaning being no longer in future)
- L192 _protected prototype_ `void OnNewListener(const FPerceptionListener& NewListener);`
- L193 _protected prototype_ `void OnListenerUpdate(const FPerceptionListener& UpdatedListener);`
- L194 _protected prototype_ `void OnListenerRemoved(const FPerceptionListener& UpdatedListener);`
- L195 _protected prototype_ `void PerformSourceRegistration();`
- L199 _protected prototype_ `bool AgeStimuli(const float Amount);` — Returns true if aging resulted in tagging any of the listeners to process its stimuli (@see MarkForStimulusProcessing)
- L202 _protected function_ `inline AIPerception::FListenerMap& GetListenersMap()`
- L205 _protected prototype_ `virtual void OnNewPawn(APawn& Pawn);`
- L206 _protected prototype_ `virtual void StartPlay();`
- L209 _protected member_ `double NextStimuliAgingTick;` — Timestamp of the next stimuli aging
- L212 _private member_ `double CurrentTime;` — cached world's timestamp
- L217 _function_ `template<typename FSenseClass> void UAIPerceptionSystem::RegisterSource(AActor& SourceActor)`

#### struct `UAIPerceptionSystem::FDelayedStimulus`  
`struct FDelayedStimulus`  
_L59-65_
- L61 _public member_ `double DeliveryTimestamp;`
- L62 _public member_ `FPerceptionListenerID ListenerId;`
- L63 _public member_ `TWeakObjectPtr<AActor> Instigator;`
- L64 _public member_ `FAIStimulus Stimulus;`

#### struct `UAIPerceptionSystem::FPerceptionSourceRegistration`  
`struct FPerceptionSourceRegistration`  
_L69-82_
- L71 _public member_ `FAISenseID SenseID;`
- L72 _public member_ `TWeakObjectPtr<AActor> Source;`
- L74 _public function_ `FPerceptionSourceRegistration(FAISenseID InSenseID, AActor* SourceActor) : SenseID(InSenseID), Source(SourceActor)`
- L78 _public function_ `inline bool operator==(const FPerceptionSourceRegistration& Other) const`

#### enum `UAIPerceptionSystem::EDelayedStimulusSorting`  
`enum EDelayedStimulusSorting`  
_L184-188_
- L186 _public enumerator_ `RequiresSorting`
- L187 _public enumerator_ `NoNeedToSort`

#### Free symbols / members of external scopes

- L22 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAIPerception, Warning, All);`

### `Source/Runtime/AIModule/Classes/Perception/AIPerceptionTypes.h` (Public)


#### struct `FAISenseCounter`  
`struct FAISenseCounter : FAIBasicCounter<uint8>`  
_L15-16_
- inherits: `FAIBasicCounter<uint8>`

#### struct `FPerceptionListenerCounter`  
`struct FPerceptionListenerCounter : FAIBasicCounter<uint32>`  
_L20-21_
- inherits: `FAIBasicCounter<uint32>`

#### enum `EAISenseNotifyType`  
`enum class EAISenseNotifyType : uint8`  
_L27-33_
- reflection: `UENUM()`
- L30 _public enumerator_ `OnEveryPerception` — Continuous update whenever target is perceived.
- L32 _public enumerator_ `OnPerceptionChange` — From "visible" to "not visible" or vice versa.

#### struct `FPerceptionChannelAllowList`  
`struct FPerceptionChannelAllowList`  
_L35-126_
- L37 _public typedef_ `typedef int32 FFlagsContainer;`
- L39 _public member_ `FFlagsContainer AcceptedChannelsMask;`
- L42 _public function_ `FPerceptionChannelAllowList() : AcceptedChannelsMask()` — by default accept all
- L45 _public function_ `void Clear()`
- L50 _public function_ `bool IsEmpty() const`
- L55 _public function_ `inline FPerceptionChannelAllowList& FilterOutChannel(FAISenseID Channel)`
- L61 _public function_ `inline FPerceptionChannelAllowList& AcceptChannel(FAISenseID Channel)`
- L67 _public function_ `inline bool ShouldRespondToChannel(FAISenseID Channel) const`
- L72 _public function_ `inline FPerceptionChannelAllowList& MergeFilterIn(const FPerceptionChannelAllowList& OtherFilter)`
- L78 _public function_ `inline FFlagsContainer GetAcceptedChannelsMask() const`

#### struct `FPerceptionChannelAllowList::FConstIterator`  
`struct FConstIterator`  
_L83-125_
- L86 _private member_ `FFlagsContainer RemainingChannelsToTest;`
- L87 _private member_ `const FPerceptionChannelAllowList& AllowList;`
- L88 _private member_ `int32 CurrentIndex;`
- L91 _public function_ `FConstIterator(const FPerceptionChannelAllowList& InAllowList) : RemainingChannelsToTest((FFlagsContainer)-1) , AllowList(InAllowList) , CurrentIndex(INDEX_NONE)`
- L99 _public function_ `inline void FindNextAcceptedChannel()`
- L109 _public function_ `inline explicit operator bool() const`
- L114 _public function_ `inline int32 operator*() const`
- L119 _public function_ `inline void operator++()`

#### struct `FAIStimulus`  
`struct FAIStimulus`  
_L129-203_
- reflection: `USTRUCT(BlueprintType)`
- L133 _public member_ `static const float NeverHappenedAge;`
- L143 _protected member_ `float Age;` — `UPROPERTY(BlueprintReadWrite, Category = "AI|Perception")`
- L146 _protected member_ `float ExpirationAge;` — `UPROPERTY(BlueprintReadWrite, Category = "AI|Perception")`
- L149 _public member_ `float Strength;` — `UPROPERTY(BlueprintReadWrite, Category = "AI|Perception")`
- L151 _public member_ `FVector StimulusLocation;` — `UPROPERTY(BlueprintReadWrite, Category = "AI|Perception")`
- L153 _public member_ `FVector ReceiverLocation;` — `UPROPERTY(BlueprintReadWrite, Category = "AI|Perception")`
- L155 _public member_ `FName Tag;` — `UPROPERTY(BlueprintReadWrite, Category = "AI|Perception")`
- L157 _public member_ `FAISenseID Type;`
- L160 _protected member_ `uint32 bWantsToNotifyOnlyOnValueChange : 1;`
- L163 _protected member_ `uint32 bSuccessfullySensed:1;` — `UPROPERTY(BlueprintReadWrite, Category = "AI|Perception")` — currently used only for marking failed sight tests
- L167 _protected member_ `uint32 bExpired:1;` — this means the stimulus was originally created with a "time limit" and this time has passed. Expiration also results in calling MarkNoLongerSensed
- L172 _public prototype_ `FAIStimulus(const UAISense& Sense, float StimulusStrength, const FVector& InStimulusLocation, const FVector& InReceiverLocation, FResult Result = SensingSucceeded, FName InStimulusTag = NAME_None);` — this is the recommended constructor. Use others if you know what you're doing.
- L175 _public function_ `FAIStimulus() : Age(NeverHappenedAge), ExpirationAge(NeverHappenedAge), Strength(-1.f), StimulusLocation(FAISystem::InvalidLocation) , ReceiverLocation(FAISystem::InvalidLocation), Tag(NAME_None), Type(FAISenseID::InvalidID()), bWantsToNotifyOnlyOnValueChange(false) , bSuccessfullySensed(false), bExpired(false)` — default constructor
- L181 _public function_ `FAIStimulus& SetExpirationAge(float InExpirationAge)`
- L182 _public function_ `FAIStimulus& SetStimulusAge(float StimulusAge)`
- L183 _public function_ `FAIStimulus& SetWantsNotifyOnlyOnValueChange(bool InEnable)`
- L185 _public function_ `inline float GetAge() const`
- L187 _public function_ `inline bool AgeStimulus(float ConstPerceptionAgingRate)` — @return false when this stimulus is no longer valid, when it is Expired
- L192 _public function_ `inline bool WasSuccessfullySensed() const`
- L193 _public function_ `inline bool IsExpired() const`
- L194 _public function_ `inline void MarkNoLongerSensed()`
- L195 _public function_ `inline void MarkExpired()`
- L196 _public function_ `inline bool IsActive() const`
- L197 _public function_ `inline bool WantsToNotifyOnlyOnPerceptionChange() const`
- L198 _public function_ `inline bool IsValid() const`
- L201 _public prototype_ `FString GetDebugDescription() const;`

#### enum `FAIStimulus::FResult`  
`enum FResult`  
_L135-139_
- L137 _public enumerator_ `SensingSucceeded`
- L138 _public enumerator_ `SensingFailed`

#### struct `FAISenseAffiliationFilter`  
`struct FAISenseAffiliationFilter`  
_L206-243_
- reflection: `USTRUCT(BlueprintType)`
- L210 _public prototype_ `FAISenseAffiliationFilter() = default;`
- L212 _public function_ `FAISenseAffiliationFilter(bool bInDetectEnemies, bool bInDetectNeutrals, bool bInDetectFriendlies) : bDetectEnemies(bInDetectEnemies) , bDetectNeutrals(bInDetectNeutrals) , bDetectFriendlies(bInDetectFriendlies)`
- L218 _public member_ `uint32 bDetectEnemies : 1 = false;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sense")`
- L221 _public member_ `uint32 bDetectNeutrals : 1 = false;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sense")`
- L224 _public member_ `uint32 bDetectFriendlies : 1 = false;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sense")`
- L226 _public function_ `uint8 GetAsFlags() const`
- L227 _public function_ `inline bool ShouldDetectAll() const`
- L229 _public function_ `static inline uint8 DetectAllFlags()`
- L231 _public function_ `static bool ShouldSenseTeam(FGenericTeamId TeamA, FGenericTeamId TeamB, uint8 AffiliationFlags)`
- L237 _public function_ `static bool ShouldSenseTeam(const IGenericTeamAgentInterface* TeamAgent, const AActor& TargetActor, uint8 AffiliationFlags)`

#### struct `FPerceptionListener`  
`struct FPerceptionListener`  
_L246-297_
- desc: Should contain only cached information common to all senses. Sense-specific data needs to be stored by senses themselves
- L248 _public member_ `TWeakObjectPtr<UAIPerceptionComponent> Listener;`
- L250 _public member_ `FPerceptionChannelAllowList Filter;`
- L252 _public member_ `FVector CachedLocation;`
- L253 _public member_ `FVector CachedDirection;`
- L255 _public member_ `FGenericTeamId TeamIdentifier;`
- L258 _private member_ `uint32 bHasStimulusToProcess : 1;`
- L260 _private member_ `FPerceptionListenerID ListenerID;`
- L262 _private prototype_ `FPerceptionListener();`
- L264 _public prototype_ `FPerceptionListener(UAIPerceptionComponent& InListener);`
- L266 _public prototype_ `void UpdateListenerProperties(UAIPerceptionComponent& Listener);`
- L268 _public function_ `bool operator==(const UAIPerceptionComponent* Other) const`
- L269 _public function_ `bool operator==(const FPerceptionListener& Other) const`
- L271 _public prototype_ `void CacheLocation();`
- L273 _public prototype_ `void RegisterStimulus(AActor* Source, const FAIStimulus& Stimulus);`
- L275 _public function_ `inline bool HasAnyNewStimuli() const`
- L276 _public prototype_ `void ProcessStimuli();`
- L278 _public function_ `inline bool HasSense(FAISenseID SenseID) const`
- L281 _public member_ `static const FPerceptionListener NullListener;` — used to remove "dead" listeners
- L283 _public function_ `inline FPerceptionListenerID GetListenerID() const`
- L285 _public prototype_ `FName GetBodyActorName() const;`
- L286 _public prototype_ `uint32 GetBodyActorUniqueID() const;`
- L289 _public prototype_ `const AActor* GetBodyActor() const;` — Returns pointer to the actor representing this listener's physical body
- L291 _public prototype_ `const IGenericTeamAgentInterface* GetTeamAgent() const;`
- L295 _private function_ `inline void SetListenerID(FPerceptionListenerID InListenerID)`
- L296 _private function_ `inline void MarkForStimulusProcessing()`

#### struct `FPerceptionStimuliSource`  
`struct FPerceptionStimuliSource`  
_L299-303_
- L301 _public member_ `TWeakObjectPtr<AActor> SourceActor;`
- L302 _public member_ `FPerceptionChannelAllowList RelevantSenses;`

#### Free symbols / members of external scopes

- L17 _typedef_ `typedef FAINamedID<FAISenseCounter> FAISenseID;`
- L22 _typedef_ `typedef FAIGenericID<FPerceptionListenerCounter> FPerceptionListenerID;`
- L305 _namespace_ `namespace AIPerception`
- L307 _typedef_ `typedef TMap<FPerceptionListenerID, FPerceptionListener> FListenerMap;` (scope `AIPerception`)

### `Source/Runtime/AIModule/Classes/Perception/AISense.h` (Public)


#### class `UAISense`  
`class UAISense : public UObject`  
_L20-146_
- reflection: `UCLASS(ClassGroup = AI, abstract, config = Engine, MinimalAPI)`
- inherits: `UObject`
- L24 _private member_ `static const float SuspendNextUpdate;`
- L28 _protected member_ `EAISenseNotifyType NotifyType;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI Perception", config)`
- L33 _protected member_ `uint32 bWantsNewPawnNotification : 1;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI Perception", config)` — whether this sense is interested in getting notified about new Pawns being spawned this can be used for example for automated sense sources registration
- L37 _protected member_ `uint32 bAutoRegisterAllPawnsAsSources : 1;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI Perception", config)` — If true all newly spawned pawns will get auto registered as source for this sense.
- L41 _protected member_ `uint32 bNeedsForgettingNotification : 1;` — this sense has some internal logic that requires it to be notified when a listener wants to forget an actor
- L45 _private member_ `TObjectPtr<UAIPerceptionSystem> PerceptionSystemInstance;` — `UPROPERTY()`
- L48 _private member_ `float TimeUntilNextUpdate;` — then this count reaches 0 sense will be updated
- L50 _private member_ `FAISenseID SenseID;`
- L54 _protected member_ `FOnPerceptionListenerUpdateDelegate OnNewListenerDelegate;` — Called when a new FPerceptionListener registers with AIPerceptionSystem
- L57 _protected member_ `FOnPerceptionListenerUpdateDelegate OnListenerUpdateDelegate;` — Called when a registered FPerceptionListener changes
- L60 _protected member_ `FOnPerceptionListenerUpdateDelegate OnListenerRemovedDelegate;` — Called when a FPerceptionListener is removed from AIPerceptionSystem
- L64 _public prototype_ `virtual UWorld* GetWorld() const override;`
- L67 _public prototype_ `static void HardcodeSenseID(TSubclassOf<UAISense> SenseClass, FAISenseID HardcodedID);` — use with caution! Needs to be called before any senses get instantiated or listeners registered. DOES NOT update any perceptions system instances
- L69 _public function_ `static FAISenseID GetSenseID(const TSubclassOf<UAISense> SenseClass)`
- L71 _public function_ `template<typename TSense> static FAISenseID GetSenseID()`
- L75 _public function_ `inline FAISenseID GetSenseID() const`
- L77 _public function_ `inline bool WantsUpdateOnlyOnPerceptionValueChange() const`
- L79 _public prototype_ `virtual void PostInitProperties() override;`
- L84 _public function_ `bool ProgressTime(float DeltaSeconds)` — @return should this sense be ticked now
- L90 _public function_ `void Tick()`
- L99 _public function_ `virtual void RegisterSource(AActor& SourceActors)` — virtual void RegisterSources(TArray<AActor&> SourceActors) {}
- L100 _public function_ `virtual void UnregisterSource(AActor& SourceActors)`
- L102 _public prototype_ `virtual void RegisterWrappedEvent(UAISenseEvent& PerceptionEvent);`
- L103 _public prototype_ `virtual FAISenseID UpdateSenseID();`
- L105 _public function_ `bool NeedsNotificationOnForgetting() const`
- L106 _public function_ `virtual void OnListenerForgetsActor(const FPerceptionListener& Listener, AActor& ActorToForget)`
- L107 _public function_ `virtual void OnListenerForgetsAll(const FPerceptionListener& Listener)`
- L109 _public function_ `inline void OnNewListener(const FPerceptionListener& NewListener)`
- L110 _public function_ `inline void OnListenerUpdate(const FPerceptionListener& UpdatedListener)`
- L111 _public function_ `inline void OnListenerRemoved(const FPerceptionListener& RemovedListener)`
- L112 _public function_ `virtual void OnListenerConfigUpdated(const FPerceptionListener& UpdatedListener)`
- L114 _public function_ `bool WantsNewPawnNotification() const`
- L115 _public function_ `bool ShouldAutoRegisterAllPawnsAsSources() const`
- L118 _public prototype_ `virtual void DescribeSelfToGameplayDebugger(const UAIPerceptionSystem& PerceptionSystem, FGameplayDebuggerCategory& DebuggerCategory) const;`
- L125 _protected prototype_ `virtual void OnNewPawn(APawn& NewPawn);` — gets called when perception system gets notified about new spawned pawn. @Note: do not call super implementation. It's used to detect when subclasses don't override it
- L128 _protected function_ `virtual float Update()` — @return time until next update
- L131 _protected function_ `inline void RequestImmediateUpdate()` — will result in updating as soon as possible
- L134 _protected function_ `inline void RequestUpdateInSeconds(float UpdateInSeconds)` — will result in updating in specified number of seconds
- L136 _protected function_ `inline UAIPerceptionSystem* GetPerceptionSystem()`
- L138 _protected prototype_ `void SetSenseID(FAISenseID Index);`
- L142 _protected prototype_ `AIPerception::FListenerMap* GetListeners();` — returning pointer rather then a reference to prevent users from accidentally creating copies by creating non-reference local vars
- L145 _protected prototype_ `void ForceSenseID(FAISenseID SenseID);` — To be called only for BP-generated classes

#### Free symbols / members of external scopes

- L17 _delegate_ `DECLARE_DELEGATE_OneParam(FOnPerceptionListenerUpdateDelegate, const FPerceptionListener&);`
- L17 _prototype_ `DECLARE_DELEGATE_OneParam(FOnPerceptionListenerUpdateDelegate, const FPerceptionListener&);`

### `Source/Runtime/AIModule/Classes/Perception/AISenseBlueprintListener.h` (Public)


#### class `UAISenseBlueprintListener`  
`class UAISenseBlueprintListener : public UUserDefinedStruct`  
_L9-12_
- reflection: `UCLASS(ClassGroup=AI, MinimalAPI)`
- inherits: `UUserDefinedStruct`

### `Source/Runtime/AIModule/Classes/Perception/AISenseConfig.h` (Public)


#### class `UAISenseConfig`  
`class UAISenseConfig : public UObject`  
_L18-63_
- reflection: `UCLASS(ClassGroup = AI, abstract, EditInlineNew, config=Game, MinimalAPI)`
- inherits: `UObject`
- L24 _protected member_ `FColor DebugColor;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Sense, AdvancedDisplay)`
- L31 _protected member_ `float MaxAge;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Sense, meta = (ClampMin = "0.0", UIMin = "0.0", Units="Seconds"))` — Specifies age limit after stimuli generated by this sense become expired. 0 means "never" Whether stimuli expiring affects given listener's memory of the target actor and triggers the Forget event is controlled by AIPerceptionSystem.bForgetStaleActors flag in Project Settings.
- L35 _protected member_ `uint32 bStartsEnabled : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Sense)` — determines whether given sense starts in an enabled state
- L38 _protected member_ `mutable FString CachedSenseName;` — name of sense
- L41 _public prototype_ `UAISenseConfig(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L43 _public prototype_ `virtual TSubclassOf<UAISense> GetSenseImplementation() const;`
- L45 _public prototype_ `FAISenseID GetSenseID() const;`
- L46 _public prototype_ `FString GetSenseName() const;`
- L47 _public function_ `FColor GetDebugColor() const`
- L48 _public function_ `void SetMaxAge(const float NewMaxAge)`
- L49 _public function_ `float GetMaxAge() const`
- L52 _public function_ `bool IsEnabled() const` — `UE_DEPRECATED(5.4, "Use GetStartsEnabled instead")`
- L54 _public function_ `bool GetStartsEnabled() const`
- L58 _public function_ `void SetStartsEnabled(bool bEnabled)` — Changes whether the given sense starts off enabled. Note that calling the function after given sense config has already been registered won't have any effect
- L61 _public prototype_ `virtual void DescribeSelfToGameplayDebugger(const UAIPerceptionComponent* PerceptionComponent, FGameplayDebuggerCategory* DebuggerCategory) const;`

### `Source/Runtime/AIModule/Classes/Perception/AISenseConfig_Blueprint.h` (Public)


#### class `UAISenseConfig_Blueprint`  
`class UAISenseConfig_Blueprint : public UAISenseConfig`  
_L15-24_
- reflection: `UCLASS(Blueprintable, Abstract, hidedropdown, MinimalAPI)`
- inherits: `UAISenseConfig`
- L21 _public member_ `TSubclassOf<UAISense_Blueprint> Implementation;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sense", NoClear, config)`
- L23 _public prototype_ `virtual TSubclassOf<UAISense> GetSenseImplementation() const override;`

### `Source/Runtime/AIModule/Classes/Perception/AISenseConfig_Damage.h` (Public)


#### class `UAISenseConfig_Damage`  
`class UAISenseConfig_Damage : public UAISenseConfig`  
_L14-23_
- reflection: `UCLASS(meta = (DisplayName = "AI Damage sense config"), MinimalAPI)`
- inherits: `UAISenseConfig`
- L20 _public member_ `TSubclassOf<UAISense_Damage> Implementation;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sense", NoClear, config)`
- L22 _public prototype_ `virtual TSubclassOf<UAISense> GetSenseImplementation() const override;`

### `Source/Runtime/AIModule/Classes/Perception/AISenseConfig_Hearing.h` (Public)


#### class `UAISenseConfig_Hearing`  
`class UAISenseConfig_Hearing : public UAISenseConfig`  
_L18-45_
- reflection: `UCLASS(meta = (DisplayName = "AI Hearing config"), MinimalAPI)`
- inherits: `UAISenseConfig`
- L24 _public member_ `TSubclassOf<UAISense_Hearing> Implementation;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sense", NoClear, config)`
- L27 _public member_ `float HearingRange;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sense", meta = (UIMin = 0.0, ClampMin = 0.0, Units="Centimeters"))`
- L31 _public member_ `float LoSHearingRange;` — `UE_DEPRECATED(5.2, "LoSHearingRange is deprecated. Use HearingRange instead.")` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sense", meta = (UIMin = 0.0, ClampMin = 0.0, Units="Centimeters", EditCondition = "bUseLoSHearing"))`
- L35 _public member_ `uint32 bUseLoSHearing : 1;` — `UE_DEPRECATED(5.2, "bUseLoSHearing is deprecated.")` — `UPROPERTY(EditAnywhere, Category = "Sense", meta = (InlineEditConditionToggle))`
- L38 _public member_ `FAISenseAffiliationFilter DetectionByAffiliation;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sense", config)`
- L40 _public prototype_ `virtual TSubclassOf<UAISense> GetSenseImplementation() const override;`
- L43 _public prototype_ `virtual void DescribeSelfToGameplayDebugger(const UAIPerceptionComponent* PerceptionComponent, FGameplayDebuggerCategory* DebuggerCategory) const override;`

### `Source/Runtime/AIModule/Classes/Perception/AISenseConfig_Prediction.h` (Public)


#### class `UAISenseConfig_Prediction`  
`class UAISenseConfig_Prediction : public UAISenseConfig`  
_L13-18_
- reflection: `UCLASS(meta = (DisplayName = "AI Prediction sense config"), MinimalAPI)`
- inherits: `UAISenseConfig`
- L17 _public prototype_ `virtual TSubclassOf<UAISense> GetSenseImplementation() const override;`

### `Source/Runtime/AIModule/Classes/Perception/AISenseConfig_Sight.h` (Public)


#### class `UAISenseConfig_Sight`  
`class UAISenseConfig_Sight : public UAISenseConfig`  
_L18-64_
- reflection: `UCLASS(meta = (DisplayName = "AI Sight config"), MinimalAPI)`
- inherits: `UAISenseConfig`
- L24 _public member_ `TSubclassOf<UAISense_Sight> Implementation;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sense", NoClear, config)`
- L28 _public member_ `float SightRadius;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sense", config, meta = (UIMin = 0.0, ClampMin = 0.0, Units="Centimeters"))` — Maximum sight distance to notice a target.
- L32 _public member_ `float LoseSightRadius;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sense", config, meta = (UIMin = 0.0, ClampMin = 0.0, Units="Centimeters"))` — Maximum sight distance to see target that has been already seen.
- L37 _public member_ `float PeripheralVisionAngleDegrees;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sense", config, meta=(UIMin = 0.0, ClampMin = 0.0, UIMax = 180.0, ClampMax = 180.0, DisplayName="Peripheral Vision Half Angle", Units="Degrees"))` — How far to the side AI can see, in degrees. Use SetPeripheralVisionAngle to change the value at runtime. The value represents the angle measured in relation to the forward vector, not the whole range.
- L41 _public member_ `FAISenseAffiliationFilter DetectionByAffiliation;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sense", config)`
- L45 _public member_ `float AutoSuccessRangeFromLastSeenLocation;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sense", config, meta = (Units="Centimeters"))` — If not an InvalidRange (which is the default), we will always be able to see the target that has already been seen if they are within this range of their last seen location.
- L49 _public member_ `float PointOfViewBackwardOffset;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sense", config, meta = (UIMin = 0.0, ClampMin = 0.0, Units="Centimeters"))` — Point of view move back distance for cone calculation. In conjunction with near clipping distance, this will act as a close by awareness and peripheral vision.
- L53 _public member_ `float NearClippingRadius;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sense", config, meta = (UIMin = 0.0, ClampMin = 0.0, Units="Centimeters"))` — Near clipping distance, to be used with point of view backward offset. Will act as a close by awareness and peripheral vision
- L55 _public prototype_ `virtual TSubclassOf<UAISense> GetSenseImplementation() const override;`
- L58 _public prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L62 _public prototype_ `virtual void DescribeSelfToGameplayDebugger(const UAIPerceptionComponent* PerceptionComponent, FGameplayDebuggerCategory* DebuggerCategory) const override;`

### `Source/Runtime/AIModule/Classes/Perception/AISenseConfig_Team.h` (Public)


#### class `UAISenseConfig_Team`  
`class UAISenseConfig_Team : public UAISenseConfig`  
_L14-19_
- reflection: `UCLASS(meta = (DisplayName = "AI Team sense config"), MinimalAPI)`
- inherits: `UAISenseConfig`
- L18 _public function_ `virtual TSubclassOf<UAISense> GetSenseImplementation() const override`

### `Source/Runtime/AIModule/Classes/Perception/AISenseConfig_Touch.h` (Public)


#### class `UAISenseConfig_Touch`  
`class UAISenseConfig_Touch : public UAISenseConfig`  
_L13-22_
- reflection: `UCLASS(meta = (DisplayName = "AI Touch config"), MinimalAPI)`
- inherits: `UAISenseConfig`
- L19 _public member_ `FAISenseAffiliationFilter DetectionByAffiliation = {true, true, true};` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sense", config)`
- L21 _public prototype_ `virtual TSubclassOf<UAISense> GetSenseImplementation() const override;`

### `Source/Runtime/AIModule/Classes/Perception/AISenseEvent.h` (Public)


#### class `UAISenseEvent`  
`class UAISenseEvent : public UObject`  
_L13-25_
- reflection: `UCLASS(ClassGroup = AI, abstract, EditInlineNew, config = Game, MinimalAPI)`
- inherits: `UObject`
- L18 _public prototype_ `virtual FAISenseID GetSenseID() const PURE_VIRTUAL(UAISenseEvent::GetSenseID, return FAISenseID::InvalidID(););`
- L21 _public function_ `virtual void DrawToVLog(UObject& LogOwner) const`
- L23 _public function_ `void DrawToVLog(UObject& LogOwner) const`

### `Source/Runtime/AIModule/Classes/Perception/AISenseEvent_Damage.h` (Public)


#### class `UAISenseEvent_Damage`  
`class UAISenseEvent_Damage : public UAISenseEvent`  
_L12-27_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAISenseEvent`
- L18 _public member_ `FAIDamageEvent Event;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sense")`
- L20 _public prototype_ `virtual FAISenseID GetSenseID() const override;`
- L22 _public function_ `inline FAIDamageEvent GetDamageEvent()`

### `Source/Runtime/AIModule/Classes/Perception/AISenseEvent_Hearing.h` (Public)


#### class `UAISenseEvent_Hearing`  
`class UAISenseEvent_Hearing : public UAISenseEvent`  
_L13-30_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAISenseEvent`
- L19 _protected member_ `FAINoiseEvent Event;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sense")`
- L22 _public prototype_ `UAISenseEvent_Hearing(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L23 _public prototype_ `virtual FAISenseID GetSenseID() const override;`
- L25 _public function_ `inline FAINoiseEvent GetNoiseEvent()`

### `Source/Runtime/AIModule/Classes/Perception/AISense_Blueprint.h` (Public)


#### class `UAISense_Blueprint`  
`class UAISense_Blueprint : public UAISense`  
_L18-83_
- reflection: `UCLASS(ClassGroup = AI, Abstract, Blueprintable, hidedropdown, MinimalAPI)`
- inherits: `UAISense`
- L24 _protected member_ `TSubclassOf<UUserDefinedStruct> ListenerDataType;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Sense")`
- L27 _protected member_ `TArray<TObjectPtr<UAIPerceptionComponent>> ListenerContainer;` — `UPROPERTY(BlueprintReadOnly, Category = "Sense")`
- L30 _protected member_ `TArray<TObjectPtr<UAISenseEvent>> UnprocessedEvents;` — `UPROPERTY()`
- L33 _public prototype_ `UAISense_Blueprint(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L40 _public prototype_ `float OnUpdate(const TArray<UAISenseEvent*>& EventsToProcess);` — `UFUNCTION(BlueprintImplementableEvent)` — returns requested amount of time to pass until next frame. Return 0 to get update every frame (WARNING: hits performance)
- L46 _public prototype_ `void OnListenerRegistered(AActor* ActorListener, UAIPerceptionComponent* PerceptionComponent);` — `UFUNCTION(BlueprintImplementableEvent)` — @param PerceptionComponent is ActorListener's AIPerceptionComponent instance
- L52 _public prototype_ `void OnListenerUpdated(AActor* ActorListener, UAIPerceptionComponent* PerceptionComponent);` — `UFUNCTION(BlueprintImplementableEvent)` — @param PerceptionComponent is ActorListener's AIPerceptionComponent instance
- L58 _public prototype_ `void OnListenerUnregistered(AActor* ActorListener, UAIPerceptionComponent* PerceptionComponent);` — `UFUNCTION(BlueprintImplementableEvent)` — called when a listener unregistered from this sense. Most often this is called due to actor's death @param PerceptionComponent is ActorListener's AIPerceptionComponent instance
- L61 _public prototype_ `void GetAllListenerActors(TArray<AActor*>& ListenerActors) const;` — `UFUNCTION(BlueprintCallable, Category = "AI|Perception")`
- L64 _public prototype_ `void GetAllListenerComponents(TArray<UAIPerceptionComponent*>& ListenerComponents) const;` — `UFUNCTION(BlueprintCallable, Category = "AI|Perception")`
- L68 _public prototype_ `void K2_OnNewPawn(APawn* NewPawn);` — `UFUNCTION(BlueprintImplementableEvent, DisplayName="OnNewPawn", meta=(ScriptName="OnNewPawn"))` — called when sense's instance gets notified about new pawn that has just been spawned
- L70 _public prototype_ `virtual FAISenseID UpdateSenseID() override;`
- L71 _public prototype_ `virtual void RegisterWrappedEvent(UAISenseEvent& PerceptionEvent) override;`
- L74 _protected prototype_ `virtual void OnNewPawn(APawn& NewPawn) override;`
- L75 _protected prototype_ `virtual float Update() override;`
- L77 _protected prototype_ `void OnNewListenerImpl(const FPerceptionListener& NewListener);`
- L78 _protected prototype_ `void OnListenerUpdateImpl(const FPerceptionListener& UpdatedListener);`
- L79 _protected prototype_ `void OnListenerRemovedImpl(const FPerceptionListener& UpdatedListener);`
- L82 _private member_ `static TMap<FNameEntryId, FAISenseID> BPSenseToSenseID;`

### `Source/Runtime/AIModule/Classes/Perception/AISense_Damage.h` (Public)


#### struct `FAIDamageEvent`  
`struct FAIDamageEvent`  
_L14-57_
- reflection: `USTRUCT(BlueprintType)`
- L18 _public typedef_ `typedef class UAISense_Damage FSenseClass;`
- L23 _public member_ `float Amount;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sense")` — Damage taken by DamagedActor. @Note 0-damage events do not get ignored
- L28 _public member_ `FVector Location;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sense")` — Event's "Location", or what will be later treated as the perceived location for this sense. If not set, HitLocation will be used, if that is unset too DamagedActor's location
- L33 _public member_ `FVector HitLocation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sense")` — Event's additional spatial information @TODO document
- L37 _public member_ `TObjectPtr<AActor> DamagedActor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sense")` — Damaged actor
- L41 _public member_ `TObjectPtr<AActor> Instigator;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sense")` — Actor that instigated damage. Can be None
- L45 _public member_ `FName Tag;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sense")` — Optional named identifier for the damage.
- L47 _public prototype_ `FAIDamageEvent();`
- L48 _public prototype_ `FAIDamageEvent(AActor* InDamagedActor, AActor* InInstigator, float DamageAmount, const FVector& EventLocation, const FVector& InHitLocation = FAISystem::InvalidLocation, FName InTag = NAME_None);`
- L49 _public prototype_ `void Compile();`
- L51 _public function_ `bool IsValid() const`
- L56 _public prototype_ `IAIPerceptionListenerInterface* GetDamagedActorAsPerceptionListener() const;`

#### class `UAISense_Damage`  
`class UAISense_Damage : public UAISense`  
_L60-77_
- reflection: `UCLASS(ClassGroup=AI, MinimalAPI)`
- inherits: `UAISense`
- L65 _private member_ `TArray<FAIDamageEvent> RegisteredEvents;` — `UPROPERTY()`
- L68 _public prototype_ `void RegisterEvent(const FAIDamageEvent& Event);`
- L69 _public prototype_ `virtual void RegisterWrappedEvent(UAISenseEvent& PerceptionEvent) override;`
- L73 _public prototype_ `static void ReportDamageEvent(UObject* WorldContextObject, AActor* DamagedActor, AActor* Instigator, float DamageAmount, FVector EventLocation, FVector HitLocation, FName Tag = NAME_None);` — `UFUNCTION(BlueprintCallable, Category = "AI|Perception", meta = (WorldContext="WorldContextObject", AdvancedDisplay="HitLocation"))` — EventLocation will be reported as Instigator's location at the moment of event happening
- L76 _protected prototype_ `virtual float Update() override;`

### `Source/Runtime/AIModule/Classes/Perception/AISense_Hearing.h` (Public)


#### struct `FAINoiseEvent`  
`struct FAINoiseEvent`  
_L15-61_
- reflection: `USTRUCT(BlueprintType)`
- L19 _public typedef_ `typedef class UAISense_Hearing FSenseClass;`
- L21 _public member_ `float Age;`
- L25 _public member_ `FVector NoiseLocation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sense")` — if not set Instigator's location will be used
- L33 _public member_ `float Loudness;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sense", meta = (UIMin = 0, ClampMin = 0))` — Loudness modifier of the sound. If MaxRange is non-zero, this modifies the range (by multiplication). If there is no MaxRange, then if Square(DistanceToSound) <= Square(HearingRange * Loudness), the sound is heard, false otherwise.
- L40 _public member_ `float MaxRange;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sense", meta = (UIMin = 0, ClampMin = 0))` — Max range at which the sound can be heard. Multiplied by Loudness. A value of 0 indicates that there is no range limit, though listeners are still limited by their own hearing range.
- L46 _public member_ `TObjectPtr<AActor> Instigator;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sense")` — Actor triggering the sound.
- L52 _public member_ `FName Tag;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sense")` — Named identifier for the noise.
- L54 _public member_ `FGenericTeamId TeamIdentifier;`
- L56 _public prototype_ `FAINoiseEvent();`
- L57 _public prototype_ `FAINoiseEvent(AActor* InInstigator, const FVector& InNoiseLocation, float InLoudness = 1.f, float InMaxRange = 0.f, FName Tag = NAME_None);`
- L60 _public prototype_ `void Compile();` — Verifies and calculates derived data

#### class `UAISense_Hearing`  
`class UAISense_Hearing : public UAISense`  
_L64-115_
- reflection: `UCLASS(ClassGroup=AI, Config=Game, MinimalAPI)`
- inherits: `UAISense`
- L70 _protected member_ `TArray<FAINoiseEvent> NoiseEvents;` — `UPROPERTY()`
- L75 _protected member_ `float SpeedOfSoundSq;` — `UPROPERTY(config)` — Defaults to 0 to have instant notification. Setting to > 0 will result in delaying when AI hears the sound based on the distance from the source
- L85 _protected member_ `TMap<FPerceptionListenerID, FDigestedHearingProperties> DigestedProperties;`
- L88 _public prototype_ `void RegisterEvent(const FAINoiseEvent& Event);`
- L89 _public prototype_ `void RegisterEventsBatch(const TArray<FAINoiseEvent>& Events);`
- L91 _public prototype_ `virtual void PostInitProperties() override;`
- L94 _public prototype_ `virtual void RegisterWrappedEvent(UAISenseEvent& PerceptionEvent) override;` — part of BP interface. Translates PerceptionEvent to FAINoiseEvent and call RegisterEvent(const FAINoiseEvent& Event)
- L106 _public prototype_ `static void ReportNoiseEvent(UObject* WorldContextObject, FVector NoiseLocation, float Loudness = 1.f, AActor* Instigator = nullptr, float MaxRange = 0.f, FName Tag = NAME_None);` — `UFUNCTION(BlueprintCallable, Category = "AI|Perception", meta = (WorldContext="WorldContextObject"))` — Report a noise event. @param NoiseLocation Location of the noise. @param Loudness Loudness of the noise. If MaxRange is non-zero, modifies MaxRange, otherwise modifies the squared distance of the sensor's range. @param Instigator Actor that triggered the noise. @param MaxRange Max range at which the sound can be heard, multiplied by Loudness. Values <= 0 mean no limit (still limited by listener's range however). @param Tag Identifier for the event.
- L109 _protected prototype_ `virtual float Update() override;`
- L110 _protected prototype_ `virtual void RegisterMakeNoiseDelegate();`
- L112 _protected prototype_ `void OnNewListenerImpl(const FPerceptionListener& NewListener);`
- L113 _protected prototype_ `void OnListenerUpdateImpl(const FPerceptionListener& UpdatedListener);`
- L114 _protected prototype_ `void OnListenerRemovedImpl(const FPerceptionListener& RemovedListener);`

#### struct `UAISense_Hearing::FDigestedHearingProperties`  
`struct FDigestedHearingProperties`  
_L77-84_
- L79 _public member_ `float HearingRangeSq;`
- L80 _public member_ `uint8 AffiliationFlags;`
- L82 _public prototype_ `FDigestedHearingProperties(const UAISenseConfig_Hearing& SenseConfig);`
- L83 _public prototype_ `FDigestedHearingProperties();`

### `Source/Runtime/AIModule/Classes/Perception/AISense_Prediction.h` (Public)


#### struct `FAIPredictionEvent`  
`struct FAIPredictionEvent`  
_L15-35_
- reflection: `USTRUCT()`
- L19 _public typedef_ `typedef UAISense_Prediction FSenseClass;`
- L22 _public member_ `TObjectPtr<AActor> Requestor;` — `UPROPERTY()`
- L25 _public member_ `TObjectPtr<AActor> PredictedActor;` — `UPROPERTY()`
- L27 _public member_ `float TimeToPredict;`
- L29 _public function_ `FAIPredictionEvent() : Requestor(nullptr), PredictedActor(nullptr)`
- L31 _public function_ `FAIPredictionEvent(AActor* InRequestor, AActor* InPredictedActor, float PredictionTime) : Requestor(InRequestor), PredictedActor(InPredictedActor), TimeToPredict(PredictionTime)`

#### class `UAISense_Prediction`  
`class UAISense_Prediction : public UAISense`  
_L38-60_
- reflection: `UCLASS(ClassGroup=AI, MinimalAPI)`
- inherits: `UAISense`
- L43 _private member_ `TArray<FAIPredictionEvent> RegisteredEvents;` — `UPROPERTY()`
- L46 _public prototype_ `void RegisterEvent(const FAIPredictionEvent& Event);`
- L51 _public prototype_ `static void RequestControllerPredictionEvent(AAIController* Requestor, AActor* PredictedActor, float PredictionTime);` — `UFUNCTION(BlueprintCallable, Category = "AI|Perception")` — Asks perception system to supply Requestor with PredictedActor's predicted location in PredictionTime seconds Location is being predicted based on PredicterActor's current location and velocity
- L56 _public prototype_ `static void RequestPawnPredictionEvent(APawn* Requestor, AActor* PredictedActor, float PredictionTime);` — `UFUNCTION(BlueprintCallable, Category = "AI|Perception")` — Asks perception system to supply Requestor with PredictedActor's predicted location in PredictionTime seconds Location is being predicted based on PredicterActor's current location and velocity
- L59 _protected prototype_ `virtual float Update() override;`

### `Source/Runtime/AIModule/Classes/Perception/AISense_Sight.h` (Public)


#### enum `ESightPerceptionEventName::Type`  
`enum Type`  
_L19-24_
- L21 _public enumerator_ `Undefined`
- L22 _public enumerator_ `GainedSight`
- L23 _public enumerator_ `LostSight`

#### struct `FAISightEvent`  
`struct FAISightEvent`  
_L28-49_
- reflection: `USTRUCT()`
- L32 _public typedef_ `typedef UAISense_Sight FSenseClass;`
- L34 _public member_ `float Age;`
- L35 _public member_ `ESightPerceptionEventName::Type EventType;`
- L38 _public member_ `TObjectPtr<AActor> SeenActor;` — `UPROPERTY()`
- L41 _public member_ `TObjectPtr<AActor> Observer;` — `UPROPERTY()`
- L43 _public function_ `FAISightEvent() : SeenActor(nullptr), Observer(nullptr)`
- L45 _public function_ `FAISightEvent(AActor* InSeenActor, AActor* InObserver, ESightPerceptionEventName::Type InEventType) : Age(0.f), EventType(InEventType), SeenActor(InSeenActor), Observer(InObserver)`

#### struct `FAISightTarget`  
`struct FAISightTarget`  
_L51-73_
- L53 _public typedef_ `typedef uint32 FTargetId;`
- L54 _public member_ `static const FTargetId InvalidTargetId;`
- L56 _public member_ `TWeakObjectPtr<AActor> Target;`
- L57 _public member_ `TWeakInterfacePtr<IAISightTargetInterface> WeakSightTargetInterface;`
- L58 _public member_ `FGenericTeamId TeamId;`
- L59 _public member_ `FTargetId TargetId;`
- L62 _public member_ `IAISightTargetInterface* SightTargetInterface = nullptr;` — `UE_DEPRECATED_FORGAME(5.5, "SightTargetInterface is deprecated. Use WeakSightTargetInterface instead.")`
- L64 _public prototype_ `FAISightTarget(AActor* InTarget = NULL, FGenericTeamId InTeamId = FGenericTeamId::NoTeam);`
- L66 _public function_ `inline FVector GetLocationSimple() const`
- L72 _public function_ `inline const AActor* GetTargetActor() const`

#### struct `FAISightQuery`  
`struct FAISightQuery`  
_L75-183_
- L77 _public member_ `FPerceptionListenerID ObserverId;`
- L78 _public member_ `FAISightTarget::FTargetId TargetId;`
- L80 _public member_ `float Score;`
- L81 _public member_ `float Importance;`
- L83 _public member_ `FVector LastSeenLocation;`
- L86 _public member_ `mutable int32 UserData;` — User data that can be used inside the IAISightTargetInterface::CanBeSeenFrom method to store a persistence state
- L118 _public function_ `FAISightQuery(FPerceptionListenerID ListenerId = FPerceptionListenerID::InvalidID(), FAISightTarget::FTargetId Target = FAISightTarget::InvalidTargetId) : ObserverId(ListenerId), TargetId(Target), Score(0), Importance(0), LastSeenLocation(FAISystem::InvalidLocation), UserData(0)`
- L128 _public function_ `float GetAge() const` — Note: This should only be called on queries that are queued up for later processing (in SightQueriesOutOfRange or SightQueriesOutOfRange)
- L136 _public function_ `void RecalcScore()` — Note: This should only be called on queries that are queued up for later processing (in SightQueriesOutOfRange or SightQueriesOutOfRange)
- L141 _public function_ `void OnProcessed()`
- L146 _public function_ `void ForgetPreviousResult()`
- L152 _public function_ `bool GetLastResult() const`
- L157 _public function_ `void SetLastResult(const bool bValue)`
- L165 _public function_ `void SetTraceInfo(const FTraceHandle& TraceHandle)` — Note: This only be called for pending queries because it will erase the LastProcessedFrameNumber value

#### union `FAISightQuery::(anonymous)`  
``  
_L89-116_

#### struct `FAISightQuery::__anon3762f069010a::(anonymous)`  
``  
_L100-103_

#### struct `FAISightQuery::__anon3762f069010a::(anonymous)`  
``  
_L111-115_

#### class `FAISightQuery::FSortPredicate`  
`class FSortPredicate`  
_L172-182_
- L175 _public function_ `FSortPredicate()`
- L178 _public function_ `bool operator()(const FAISightQuery& A, const FAISightQuery& B) const`

#### struct `FAISightQueryID`  
`struct FAISightQueryID`  
_L185-199_
- L187 _public member_ `FPerceptionListenerID ObserverId;`
- L188 _public member_ `FAISightTarget::FTargetId TargetId;`
- L190 _public function_ `FAISightQueryID(FPerceptionListenerID ListenerId = FPerceptionListenerID::InvalidID(), FAISightTarget::FTargetId Target = FAISightTarget::InvalidTargetId) : ObserverId(ListenerId), TargetId(Target)`
- L195 _public function_ `FAISightQueryID(const FAISightQuery& Query) : ObserverId(Query.ObserverId), TargetId(Query.TargetId)`

#### class `UAISense_Sight`  
`class UAISense_Sight : public UAISense`  
_L204-340_
- reflection: `UCLASS(ClassGroup=AI, config=Game, MinimalAPI)`
- inherits: `UAISense`
- L230 _public typedef_ `typedef TMap<FAISightTarget::FTargetId, FAISightTarget> FTargetsContainer;`
- L231 _public member_ `FTargetsContainer ObservedTargets;`
- L232 _public member_ `TMap<FPerceptionListenerID, FDigestedSightProperties> DigestedProperties;`
- L237 _public member_ `int32 NextOutOfRangeIndex = 0;` — In the majority of the cases most of the queries are out of range, so the sort time is greatly reduced as we only sort the in range queries
- L238 _public member_ `bool bSightQueriesOutOfRangeDirty = true;`
- L239 _public member_ `TArray<FAISightQuery> SightQueriesOutOfRange;`
- L240 _public member_ `TArray<FAISightQuery> SightQueriesInRange;`
- L241 _public member_ `TArray<FAISightQuery> SightQueriesPending;`
- L245 _protected member_ `int32 MaxTracesPerTick;` — `UPROPERTY(EditDefaultsOnly, Category = "AI Perception", config)`
- L249 _protected member_ `int32 MaxAsyncTracesPerTick;` — `UPROPERTY(EditDefaultsOnly, Category = "AI Perception", config)` — Maximum number of asynchronous traces that can be requested in a single update call
- L252 _protected member_ `int32 MinQueriesPerTimeSliceCheck;` — `UPROPERTY(EditDefaultsOnly, Category = "AI Perception", config)`
- L255 _protected member_ `double MaxTimeSlicePerTick;` — `UPROPERTY(EditDefaultsOnly, Category = "AI Perception", config)`
- L258 _protected member_ `float HighImportanceQueryDistanceThreshold;` — `UPROPERTY(EditDefaultsOnly, Category = "AI Perception", config)`
- L260 _protected member_ `float HighImportanceDistanceSquare;`
- L263 _protected member_ `float MaxQueryImportance;` — `UPROPERTY(EditDefaultsOnly, Category = "AI Perception", config)`
- L266 _protected member_ `float SightLimitQueryImportance;` — `UPROPERTY(EditDefaultsOnly, Category = "AI Perception", config)`
- L273 _protected member_ `float PendingQueriesBudgetReductionRatio;` — `UPROPERTY(EditDefaultsOnly, Category = "AI Perception", config)` — Defines the amount of async trace queries to prevent based on the number of pending queries at the start of an update. 1 means that the async trace budget is slashed by the pending queries count 0 means that the async trace budget is not impacted by the pending queries
- L277 _protected member_ `bool bUseAsynchronousTraceForDefaultSightQueries;` — `UPROPERTY(EditDefaultsOnly, Category = "AI Perception", config)` — Defines if we are allowed to use asynchronous trace queries when there is no IAISightTargetInterface for a Target
- L279 _protected member_ `ECollisionChannel DefaultSightCollisionChannel;`
- L281 _protected member_ `FOnPendingVisibilityQueryProcessedDelegate OnPendingCanBeSeenQueryProcessedDelegate;`
- L282 _protected member_ `FTraceDelegate OnPendingTraceQueryProcessedDelegate;`
- L284 _protected prototype_ `UE_MT_DECLARE_TS_RW_ACCESS_DETECTOR(QueriesListAccessDetector);`
- L288 _public prototype_ `virtual void PostInitProperties() override;`
- L290 _public prototype_ `void RegisterEvent(const FAISightEvent& Event);`
- L292 _public prototype_ `virtual void RegisterSource(AActor& SourceActors) override;`
- L293 _public prototype_ `virtual void UnregisterSource(AActor& SourceActor) override;`
- L295 _public prototype_ `virtual void OnListenerForgetsActor(const FPerceptionListener& Listener, AActor& ActorToForget) override;`
- L296 _public prototype_ `virtual void OnListenerForgetsAll(const FPerceptionListener& Listener) override;`
- L299 _public prototype_ `virtual void DescribeSelfToGameplayDebugger(const UAIPerceptionSystem& PerceptionSystem, FGameplayDebuggerCategory& DebuggerCategory) const override;`
- L303 _protected prototype_ `virtual float Update() override;`
- L305 _protected prototype_ `EVisibilityResult ComputeVisibility(UWorld* World, FAISightQuery& SightQuery, FPerceptionListener& Listener, const AActor* ListenerActor, FAISightTarget& Target, AActor* TargetActor, const FDigestedSightProperties& PropDigest, float& OutStimulusStrength, FVector& OutSeenLocation, int32& OutNumberOfLoSChecksPerformed, int32& OutNumberOfAsyncLosCheckRequested) const;`
- L306 _protected prototype_ `virtual bool ShouldAutomaticallySeeTarget(const FDigestedSightProperties& PropDigest, FAISightQuery* SightQuery, FPerceptionListener& Listener, AActor* TargetActor, float& OutStimulusStrength) const;`
- L309 _protected prototype_ `void UpdateQueryVisibilityStatus(FAISightQuery& SightQuery, FPerceptionListener& Listener, const bool bIsVisible, const FVector& SeenLocation, const float StimulusStrength, AActor* TargetActor, const FVector& TargetLocation) const;` — `UE_DEPRECATED(5.3, "Please use the UpdateQueryVisibilityStatus version which takes an Actor& instead.")`
- L310 _protected prototype_ `void UpdateQueryVisibilityStatus(FAISightQuery& SightQuery, FPerceptionListener& Listener, const bool bIsVisible, const FVector& SeenLocation, const float StimulusStrength, AActor& TargetActor, const FVector& TargetLocation) const;`
- L312 _protected prototype_ `void OnPendingCanBeSeenQueryProcessed(const FAISightQueryID& QueryID, const bool bIsVisible, const float StimulusStrength, const FVector& SeenLocation, const TOptional<int32>& UserData);`
- L313 _protected prototype_ `void OnPendingTraceQueryProcessed(const FTraceHandle& TraceHandle, FTraceDatum& TraceDatum);`
- L314 _protected prototype_ `void OnPendingQueryProcessed(const int32 SightQueryIndex, const bool bIsVisible, const float StimulusStrength, const FVector& SeenLocation, const TOptional<int32>& UserData, const TOptional<AActor*> InTargetActor = NullOpt);`
- L316 _protected prototype_ `void OnNewListenerImpl(const FPerceptionListener& NewListener);`
- L317 _protected prototype_ `void OnListenerUpdateImpl(const FPerceptionListener& UpdatedListener);`
- L318 _protected prototype_ `void OnListenerRemovedImpl(const FPerceptionListener& RemovedListener);`
- L319 _protected prototype_ `virtual void OnListenerConfigUpdated(const FPerceptionListener& UpdatedListener) override;`
- L321 _protected prototype_ `void GenerateQueriesForListener(const FPerceptionListener& Listener, const FDigestedSightProperties& PropertyDigest, const TFunction<void(FAISightQuery&)>& OnAddedFunc = nullptr);`
- L323 _protected prototype_ `void RemoveAllQueriesByListener(const FPerceptionListener& Listener, const TFunction<void(const FAISightQuery&)>& OnRemoveFunc = nullptr);`
- L324 _protected prototype_ `void RemoveAllQueriesToTarget(const FAISightTarget::FTargetId& TargetId, const TFunction<void(const FAISightQuery&)>& OnRemoveFunc = nullptr);`
- L326 _protected prototype_ `void RemoveAllQueriesToTarget_Internal(const FAISightTarget::FTargetId& TargetId, const TFunction<void(const FAISightQuery&)>& OnRemoveFunc = nullptr);` — RemoveAllQueriesToTarget version that need to already have a write access on QueriesListAccessDetector
- L329 _protected prototype_ `bool RegisterTarget(AActor& TargetActor, const TFunction<void(FAISightQuery&)>& OnAddedFunc = nullptr);` — returns information whether new LoS queries have been added
- L331 _protected prototype_ `float CalcQueryImportance(const FPerceptionListener& Listener, const FVector& TargetLocation, const float SightRadiusSq) const;`
- L332 _protected prototype_ `bool RegisterNewQuery(const FPerceptionListener& Listener, const IGenericTeamAgentInterface* ListenersTeamAgent, const AActor& TargetActor, const FAISightTarget::FTargetId& TargetId, const FVector& TargetLocation, const FDigestedSightProperties& PropDigest, const TFunction<void(FAISightQuery&)>& OnAddedFunc);`

#### struct `UAISense_Sight::FDigestedSightProperties`  
`struct FDigestedSightProperties`  
_L209-221_
- L211 _public member_ `float PeripheralVisionAngleCos;`
- L212 _public member_ `float SightRadiusSq;`
- L213 _public member_ `float AutoSuccessRangeSqFromLastSeenLocation;`
- L214 _public member_ `float LoseSightRadiusSq;`
- L215 _public member_ `float PointOfViewBackwardOffset;`
- L216 _public member_ `float NearClippingRadiusSq;`
- L217 _public member_ `uint8 AffiliationFlags;`
- L219 _public prototype_ `FDigestedSightProperties();`
- L220 _public prototype_ `FDigestedSightProperties(const UAISenseConfig_Sight& SenseConfig);`

#### enum `UAISense_Sight::EVisibilityResult`  
`enum class EVisibilityResult`  
_L223-228_
- L225 _public enumerator_ `Visible`
- L226 _public enumerator_ `NotVisible`
- L227 _public enumerator_ `Pending`

#### enum `UAISense_Sight::FQueriesOperationPostProcess`  
`enum FQueriesOperationPostProcess`  
_L335-339_
- L337 _public enumerator_ `DontSort`
- L338 _public enumerator_ `Sort`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace ESightPerceptionEventName`
- L101 _member_ `uint64 bLastResult:1;` (scope `FAISightQuery::__anon3762f069010a::__anon3762f0690208`)
- L102 _member_ `uint64 LastProcessedFrameNumber:63;` (scope `FAISightQuery::__anon3762f069010a::__anon3762f0690208`)
- L103 _member_ `} FrameInfo;` (scope `FAISightQuery::__anon3762f069010a`)
- L112 _member_ `uint32 bLastResult:1;` (scope `FAISightQuery::__anon3762f069010a::__anon3762f0690308`)
- L113 _member_ `uint32 Index:31;` (scope `FAISightQuery::__anon3762f069010a::__anon3762f0690308`)
- L114 _member_ `uint32 FrameNumber;` (scope `FAISightQuery::__anon3762f069010a::__anon3762f0690308`)
- L115 _member_ `} TraceInfo;` (scope `FAISightQuery::__anon3762f069010a`)
- L201 _delegate_ `DECLARE_DELEGATE_FiveParams(FOnPendingVisibilityQueryProcessedDelegate, const FAISightQueryID&, const bool, const float, const FVector&, const TOptional<int32>&);`
- L201 _prototype_ `DECLARE_DELEGATE_FiveParams(FOnPendingVisibilityQueryProcessedDelegate, const FAISightQueryID&, const bool, const float, const FVector&, const TOptional<int32>&);`

### `Source/Runtime/AIModule/Classes/Perception/AISense_Team.h` (Public)


#### struct `FAITeamStimulusEvent`  
`struct FAITeamStimulusEvent`  
_L14-47_
- reflection: `USTRUCT()`
- L18 _public typedef_ `typedef UAISense_Team FSenseClass;`
- L20 _public member_ `FVector LastKnowLocation;`
- L22 _private member_ `FVector BroadcastLocation;`
- L24 _public member_ `float RangeSq;`
- L25 _public member_ `float InformationAge;`
- L26 _public member_ `FGenericTeamId TeamIdentifier;`
- L27 _public member_ `float Strength;`
- L30 _private member_ `TObjectPtr<AActor> Broadcaster;` — `UPROPERTY()`
- L33 _public member_ `TObjectPtr<AActor> Enemy;` — `UPROPERTY()`
- L35 _public function_ `FAITeamStimulusEvent() : Broadcaster(nullptr), Enemy(nullptr)`
- L36 _public prototype_ `FAITeamStimulusEvent(AActor* InBroadcaster, AActor* InEnemy, const FVector& InLastKnowLocation, float EventRange, float PassedInfoAge = 0.f, float InStrength = 1.f);`
- L38 _public function_ `inline void CacheBroadcastLocation()`
- L43 _public function_ `inline const FVector& GetBroadcastLocation() const`

#### class `UAISense_Team`  
`class UAISense_Team : public UAISense`  
_L50-62_
- reflection: `UCLASS(ClassGroup=AI, MinimalAPI)`
- inherits: `UAISense`
- L55 _private member_ `TArray<FAITeamStimulusEvent> RegisteredEvents;` — `UPROPERTY()`
- L58 _public prototype_ `void RegisterEvent(const FAITeamStimulusEvent& Event);`
- L61 _protected prototype_ `virtual float Update() override;`

### `Source/Runtime/AIModule/Classes/Perception/AISense_Touch.h` (Public)


#### struct `FAITouchEvent`  
`struct FAITouchEvent`  
_L15-40_
- reflection: `USTRUCT()`
- L19 _public typedef_ `typedef UAISense_Touch FSenseClass;`
- L21 _public member_ `FVector Location = FVector::ZeroVector;`
- L24 _public member_ `TObjectPtr<AActor> TouchReceiver;` — `UPROPERTY()`
- L27 _public member_ `TObjectPtr<AActor> OtherActor;` — `UPROPERTY()`
- L29 _public member_ `FGenericTeamId TeamIdentifier = FGenericTeamId::NoTeam;`
- L31 _public prototype_ `FAITouchEvent() = default;`
- L33 _public function_ `FAITouchEvent(AActor* InTouchReceiver, AActor* InOtherActor, const FVector& EventLocation) : Location(EventLocation), TouchReceiver(InTouchReceiver), OtherActor(InOtherActor)`
- L39 _public prototype_ `IAIPerceptionListenerInterface* GetTouchedActorAsPerceptionListener() const;`

#### class `UAISense_Touch`  
`class UAISense_Touch : public UAISense`  
_L43-73_
- reflection: `UCLASS(ClassGroup=AI, MinimalAPI)`
- inherits: `UAISense`
- L48 _private member_ `TArray<FAITouchEvent> RegisteredEvents;` — `UPROPERTY()`
- L51 _public prototype_ `void RegisterEvent(const FAITouchEvent& Event);`
- L54 _public prototype_ `static void ReportTouchEvent(UObject* WorldContextObject, AActor* TouchReceiver, AActor* OtherActor, FVector Location);` — `UFUNCTION(BlueprintCallable, Category = "AI|Perception", meta = (WorldContext = "WorldContextObject"))`
- L65 _protected member_ `TMap<FPerceptionListenerID, FDigestedTouchProperties> DigestedProperties;`
- L68 _protected prototype_ `virtual float Update() override;`
- L70 _protected prototype_ `void OnNewListenerImpl(const FPerceptionListener& NewListener);`
- L71 _protected prototype_ `void OnListenerUpdateImpl(const FPerceptionListener& UpdatedListener);`
- L72 _protected prototype_ `void OnListenerRemovedImpl(const FPerceptionListener& RemovedListener);`

#### struct `UAISense_Touch::FDigestedTouchProperties`  
`struct FDigestedTouchProperties`  
_L58-64_
- L60 _public member_ `uint8 AffiliationFlags;`
- L62 _public prototype_ `FDigestedTouchProperties(const UAISenseConfig_Touch& SenseConfig);`
- L63 _public prototype_ `FDigestedTouchProperties();`

### `Source/Runtime/AIModule/Classes/Perception/AISightTargetInterface.h` (Public)


#### class `UAISightTargetInterface`  
`class UAISightTargetInterface : public UInterface`  
_L14-17_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### struct `FCanBeSeenFromContext`  
`struct FCanBeSeenFromContext`  
_L19-29_
- L22 _public member_ `FAISightQueryID SightQueryID;` — The query identifier used by the delegate call to find the appropriate query
- L24 _public member_ `FVector ObserverLocation;` — The location of the observer
- L26 _public member_ `const AActor* IgnoreActor = nullptr;` — The actor to ignore when doing test
- L28 _public member_ `const bool* bWasVisible = nullptr;` — If available, it is the previous visibility state

#### class `IAISightTargetInterface`  
`class IAISightTargetInterface`  
_L31-73_
- L47 _private function_ `virtual UAISense_Sight::EVisibilityResult CanBeSeenFrom(const FCanBeSeenFromContext& Context, FVector& OutSeenLocation, int32& OutNumberOfLoSChecksPerformed, int32& OutNumberOfAsyncLosCheckRequested, float& OutSightStrength, int32* UserData = nullptr, const FOnPendingVisibilityQueryProcessedDelegate* Delegate = nullptr)` — The method needs to check whether the implementer is visible from given observer's location. This version allows an asynchronous answer by returning Pending and using the provided Delegate when the information is computed @param Context								Struct containing all the information required to perform the query @param OutSeenLocation						The first visible target location @param OutNumberOfLoSChecksPerformed			The number of synchronous queries done. This is used to stop the perception tick sooner when too many LoS checks are done @param OutNumberOfAsyncLosCheckRequested		The number of asynchronous queries done. This is used to stop the perception tick sooner when too many asynchronous LoS checks are done @param OutSightStrength						The sight strength for how well the target is seen @param UserData								If available, it is a data passed between visibility tests for the users to store whatever they want @param Delegate								If available, the delegate to call later on, if the result needed asynchronous checks. Calling this delegate within the CanBeSeenFrom call will ensure @return										Undefined to indicate that we need to try another CanBeSeenFrom implementation, Visible/NotVisible if visible/not visible from the observer's location, Pending if the check is not finished
- L67 _private function_ `virtual bool CanBeSeenFrom(const FVector& ObserverLocation, FVector& OutSeenLocation, int32& NumberOfLoSChecksPerformed, float& OutSightStrength, const AActor* IgnoreActor = nullptr, const bool* bWasVisible = nullptr, int32* UserData = nullptr) const` — `UE_DEPRECATED(5.2, "This function is deprecated. Use the new CanBeSeenFrom method signature")` — The method needs to check whether the implementer is visible from given observer's location. @param ObserverLocation	The location of the observer @param OutSeenLocation	The first visible target location @param OutSightStrength	The sight strength for how well the target is seen @param IgnoreActor		The actor to ignore when doing test @param bWasVisible		If available, it is the previous visibility state @param UserData			If available, it is a data passed between visibility tests for the users to store whatever they want @return	True if visible from the observer's location

### `Source/Runtime/AIModule/Classes/Perception/PawnSensingComponent.h` (Public)


#### class `UPawnSensingComponent`  
`class UPawnSensingComponent : public UActorComponent`  
_L22-185_
- reflection: `UE_DEPRECATED_FORGAME(5.5, "Pawn sensing is deprecated. AI Perception should be used instead.")`
- reflection: `UCLASS(ClassGroup=AI, HideCategories=(Activation, "Components|Activation", Collision), meta=(BlueprintSpawnableComponent), MinimalAPI)`
- inherits: `UActorComponent`
- desc: SensingComponent encapsulates sensory (ie sight and hearing) settings and functionality for an Actor, allowing the actor to see/hear Pawns in the world. It does nothing on network clients.
- L26 _private prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FSeePawnDelegate, APawn*, Pawn );`
- L27 _private prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams( FHearNoiseDelegate, APawn*, Instigator, const FVector&, Location, float, Volume);`
- L31 _private member_ `float HearingThreshold;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=AI)` — Max distance at which a makenoise(1.0) loudness sound can be heard, regardless of occlusion
- L35 _private member_ `float LOSHearingThreshold;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=AI)` — Max distance at which a makenoise(1.0) loudness sound can be heard if unoccluded (LOSHearingThreshold should be > HearingThreshold)
- L39 _private member_ `float SightRadius;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=AI)` — Maximum sight distance.
- L43 _private member_ `float SensingInterval;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=AI)` — Amount of time between pawn sensing updates. Use SetSensingInterval() to adjust this at runtime. A value <= 0 prevents any updates.
- L47 _private member_ `float HearingMaxSoundAge;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=AI)` — Max age of sounds we can hear. Should be greater than SensingInterval, or you might miss hearing some sounds!
- L57 _public prototype_ `virtual void SetSensingInterval(const float NewSensingInterval);` — `UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category="AI|Components|PawnSensing")` — Changes the SensingInterval. If we are currently waiting for an interval, this can either extend or shorten that interval. A value <= 0 prevents any updates.
- L61 _public prototype_ `virtual void SetSensingUpdatesEnabled(const bool bEnabled);` — `UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category="AI|Components|PawnSensing")` — Enables or disables sensing updates. The timer is reset in either case.
- L65 _public prototype_ `virtual void SetPeripheralVisionAngle(const float NewPeripheralVisionAngle);` — `UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category="AI|Components|PawnSensing")` — Sets PeripheralVisionAngle. Calculates PeripheralVisionCosine from PeripheralVisionAngle
- L68 _public prototype_ `float GetPeripheralVisionAngle() const;` — `UFUNCTION(BlueprintCallable, Category="AI|Components|PawnSensing")`
- L71 _public prototype_ `float GetPeripheralVisionCosine() const;` — `UFUNCTION(BlueprintCallable, Category="AI|Components|PawnSensing")`
- L75 _public member_ `uint32 bEnableSensingUpdates:1;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=AI)` — If true, component will perform sensing updates. At runtime change this using SetSensingUpdatesEnabled().
- L79 _public member_ `uint32 bOnlySensePlayers:1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=AI)` — If true, will only sense player-controlled pawns in the world. Default: true
- L83 _public member_ `uint32 bSeePawns:1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=AI)` — If true, we will perform visibility tests and will trigger notifications when a Pawn is visible. Default: true
- L90 _public member_ `uint32 bHearNoises:1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=AI)` — If true, we will perform audibility tests and will be notified when a Pawn makes a noise that can be heard. Default: true IMPORTANT NOTE: If we can see pawns (bSeePawns is true), and the pawn is visible, noise notifications are not triggered.
- L93 _public prototype_ `virtual bool IsSensorActor(const AActor* Actor) const;` — Is the given actor our owner? Used to ensure that we are not trying to sense our self / our owner.
- L96 _public prototype_ `virtual bool CanSenseAnything() const;` — Are we capable of sensing anything (and do we have any callbacks that care about sensing)? If so UpdateAISensing() will be called every sensing interval.
- L99 _public prototype_ `virtual bool ShouldCheckVisibilityOf(APawn* Pawn) const;` — Returns true if we should check whether the given Pawn is visible (because we can see things, the Pawn is not hidden, and if the Pawn is a player and we only see players)
- L106 _public prototype_ `virtual bool CouldSeePawn(const APawn* Other, bool bMaySkipChecks = false) const;` — Chance of seeing other pawn decreases with increasing distance or angle in peripheral vision @param bMaySkipChecks if true allows checks to be sometimes skipped if target is far away (used by periodic automatic visibility checks) @return true if the specified pawn Other is potentially visible (within peripheral vision, etc.) - still need to do LineOfSightTo() check to see if actually visible.
- L109 _public prototype_ `virtual bool ShouldCheckAudibilityOf(APawn* Pawn) const;` — Returns true if we should check whether we can hear the given Pawn (because we are able to hear, and the Pawn has the correct team relationship to us)
- L117 _public prototype_ `virtual bool HasLineOfSightTo(const AActor* Other) const;` — Check line to other actor. @param Other is the actor whose visibility is being checked. @param ViewPoint is eye position visibility is being checked from. @return true if controller's pawn can see Other actor.
- L123 _public prototype_ `bool IsNoiseRelevant(const APawn& Pawn, const UPawnNoiseEmitterComponent& NoiseEmitterComponent, bool bSourceWithinNoiseEmitter) const;` — Test whether the noise is loud enough and recent enough to care about.  bSourceWithinNoiseEmitter is true iff the noise was made by the pawn itself or within close proximity (its collision volume).  Otherwise the noise was made at significant distance from the pawn.
- L126 _public prototype_ `virtual bool CanHear(const FVector& NoiseLoc, float Loudness, bool bFailedLOS) const;` — @Returns true if sensor can hear this noise. Only executed if the noise has been determined to be relevant (via IsNoiseRelevant)
- L129 _public prototype_ `virtual void InitializeComponent() override;`
- L133 _public prototype_ `virtual FVector GetSensorLocation() const;` — Get position where hearing/seeing occurs (i.e. ear/eye position).  If we ever need different positions for hearing/seeing, we'll deal with that then!
- L136 _public prototype_ `virtual FRotator GetSensorRotation() const;` — Get the rotation of this sensor. We need this for the sight component
- L141 _protected prototype_ `virtual void SensePawn(APawn& Pawn);` — See if there are interesting sounds and sights that we want to detect, and respond to them if so.
- L144 _protected prototype_ `virtual void OnTimer();` — Update function called on timer intervals.
- L147 _protected member_ `FTimerHandle TimerHandle_OnTimer;` — Handle for efficient management of OnTimer timer
- L150 _protected prototype_ `virtual void SetTimer(const float TimeDelay);` — Modify the timer to fire in TimeDelay seconds. A value <= 0 disables the timer.
- L153 _protected prototype_ `virtual void UpdateAISensing();` — Calls SensePawn on any Pawns that we are allowed to sense.
- L155 _protected prototype_ `AActor* GetSensorActor() const;` — Get the actor used as the actual sensor location is derived from this actor.
- L156 _protected prototype_ `AController* GetSensorController() const;` — Get the controller of the sensor actor.
- L161 _public member_ `FSeePawnDelegate OnSeePawn;` — `UPROPERTY(BlueprintAssignable)` — Delegate to execute when we see a Pawn.
- L165 _public member_ `FHearNoiseDelegate OnHearNoise;` — `UPROPERTY(BlueprintAssignable)` — Delegate to execute when we hear a noise from a Pawn's PawnNoiseEmitterComponent.
- L170 _protected prototype_ `virtual void BroadcastOnSeePawn(APawn& Pawn);` — Broadcasts notification that our sensor sees a Pawn, using the OnSeePawn delegates.
- L173 _protected prototype_ `virtual void BroadcastOnHearLocalNoise(APawn& Instigator, const FVector& Location, float Volume);` — Broadcasts notification that our sensor hears a noise made local to a Pawn's position, using the OnHearNoise delegates.
- L176 _protected prototype_ `virtual void BroadcastOnHearRemoteNoise(APawn& Instigator, const FVector& Location, float Volume);` — Broadcasts notification that our sensor hears a noise made remotely from a Pawn's position, using the OnHearNoise delegates.
- L180 _protected member_ `float PeripheralVisionAngle;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=AI)` — How far to the side AI can see, in degrees. Use SetPeripheralVisionAngle to change the value at runtime.
- L184 _protected member_ `float PeripheralVisionCosine;` — `UPROPERTY()` — Cosine of limits of peripheral vision. Computed from PeripheralVisionAngle.
- L189 _function_ `inline float UPawnSensingComponent::GetPeripheralVisionAngle() const`
- L194 _function_ `inline float UPawnSensingComponent::GetPeripheralVisionCosine() const`

#### Free symbols / members of external scopes

- L26 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FSeePawnDelegate, APawn*, Pawn );`
- L27 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams( FHearNoiseDelegate, APawn*, Instigator, const FVector&, Location, float, Volume);`

### `Source/Runtime/AIModule/Classes/Tasks/AITask.h` (Public)


#### enum `EAITaskPriority`  
`enum class EAITaskPriority : uint8`  
_L14-21_
- reflection: `UENUM()`
- L16 _public enumerator_ `Lowest = 0`
- L17 _public enumerator_ `Low = 64` — FGameplayTasks::DefaultPriority / 2,
- L18 _public enumerator_ `AutonomousAI = 127` — FGameplayTasks::DefaultPriority,
- L19 _public enumerator_ `High = 192` — (1.5 * FGameplayTasks::DefaultPriority),
- L20 _public enumerator_ `Ultimate = 254`

#### class `UAITask`  
`class UAITask : public UGameplayTask`  
_L24-87_
- reflection: `UCLASS(Abstract, BlueprintType, MinimalAPI)`
- inherits: `UGameplayTask`
- L30 _protected member_ `TObjectPtr<AAIController> OwnerController;` — `UPROPERTY(BlueprintReadOnly, Category="AI|Tasks")`
- L32 _protected prototype_ `virtual void Activate() override;`
- L35 _public prototype_ `UAITask(const FObjectInitializer& ObjectInitializer);`
- L37 _public prototype_ `static AAIController* GetAIControllerForActor(AActor* Actor);`
- L38 _public function_ `AAIController* GetAIController() const`
- L40 _public prototype_ `void InitAITask(AAIController& AIOwner, IGameplayTaskOwnerInterface& InTaskOwner, uint8 InPriority);`
- L41 _public prototype_ `void InitAITask(AAIController& AIOwner, IGameplayTaskOwnerInterface& InTaskOwner);`
- L44 _public prototype_ `void RequestAILogicLocking();` — effectively adds UAIResource_Logic to the set of Claimed resources
- L47 _public function_ `template <class T> static T* NewAITask(AAIController& AIOwner, IGameplayTaskOwnerInterface& InTaskOwner, FName InstanceName = FName())`
- L53 _public function_ `template <class T> static T* NewAITask(AAIController& AIOwner, IGameplayTaskOwnerInterface& InTaskOwner, EAITaskPriority InPriority, FName InstanceName = FName())`
- L59 _public function_ `template <class T> static T* NewAITask(AAIController& AIOwner, FName InstanceName = FName())`
- L65 _public function_ `template <class T> static T* NewAITask(AAIController& AIOwner, EAITaskPriority InPriority, FName InstanceName = FName())`
- L71 _public function_ `template <class T> static T* NewAITask(const UClass& Class, AAIController& AIOwner, IGameplayTaskOwnerInterface& InTaskOwner, FName InstanceName = FName())`
- L80 _public function_ `template <class T> static T* NewAITask(const UClass& Class, AAIController& AIOwner, IGameplayTaskOwnerInterface& InTaskOwner, EAITaskPriority InPriority, FName InstanceName = FName())`

### `Source/Runtime/AIModule/Classes/Tasks/AITask_LockLogic.h` (Public)


#### class `UAITask_LockLogic`  
`class UAITask_LockLogic : public UAITask`  
_L11-14_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAITask`
- desc: Locks AI logic until removed by external trigger

### `Source/Runtime/AIModule/Classes/Tasks/AITask_MoveTo.h` (Public)


#### class `UAITask_MoveTo`  
`class UAITask_MoveTo : public UAITask`  
_L18-115_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAITask`
- L23 _public prototype_ `UAITask_MoveTo(const FObjectInitializer& ObjectInitializer);`
- L26 _public prototype_ `void ConditionalPerformMove();` — tries to start move request and handles retry timer
- L29 _public prototype_ `void SetUp(AAIController* Controller, const FAIMoveRequest& InMoveRequest);` — prepare move task for activation
- L31 _public function_ `EPathFollowingResult::Type GetMoveResult() const`
- L32 _public function_ `bool WasMoveSuccessful() const`
- L33 _public function_ `bool WasMovePartial() const`
- L41 _public prototype_ `static UAITask_MoveTo* AIMoveTo(AAIController* Controller, FVector GoalLocation, AActor* GoalActor = nullptr, float AcceptanceRadius = -1.f, EAIOptionFlag::Type StopOnOverlap = EAIOptionFlag::Default, EAIOptionFlag::Type AcceptPartialPath = EAIOptionFlag::Default, bool bUsePathfinding = true, bool bLockAILogic = true, bool bUseContinuousGoalTracking = false, EAIOptionFlag::Type ProjectGoalOnNavigation = EAIOptionFlag::Default, EAIOptionFlag::Type RequireNavigableEndLocation = EAIOptionFlag::Default);` — `UFUNCTION(BlueprintCallable, Category = "AI|Tasks", meta = (AdvancedDisplay = "AcceptanceRadius,StopOnOverlap,AcceptPartialPath,bUsePathfinding,bUseContinuousGoalTracking,ProjectGoalOnNavigation,RequireNavigableEndLocation", DefaultToSelf = "Controller", BlueprintInternalUseOnly = "TRUE", DisplayName = "Move To Location or Actor"))` — Move to a location or an actor @param ProjectGoalOnNavigation Try to move the goal to the navigation surface before requesting the move, fails if it can't. @param RequireNavigableEndLocation Set to No to allow pursuing the request even if no navigation surface is found at the goal location.
- L48 _public function_ `FAIMoveRequest& GetMoveRequestRef()` — Allows custom move request tweaking. Note that all MoveRequest need to be performed before PerformMove is called.
- L51 _public prototype_ `void SetContinuousGoalTracking(bool bEnable);` — Switch task into continuous tracking mode: keep restarting move toward goal actor. Only pathfinding failure or external cancel will be able to stop this task.
- L53 _public member_ `FMoveTaskFinishedSignature OnMoveTaskFinished;`
- L56 _protected member_ `FGenericGameplayTaskDelegate OnRequestFailed;` — `UPROPERTY(BlueprintAssignable)`
- L59 _protected member_ `FMoveTaskCompletedSignature OnMoveFinished;` — `UPROPERTY(BlueprintAssignable)`
- L63 _protected member_ `FAIMoveRequest MoveRequest;` — `UPROPERTY()` — parameters of move request
- L66 _protected member_ `FDelegateHandle PathFinishDelegateHandle;` — handle of path following's OnMoveFinished delegate
- L69 _protected member_ `FDelegateHandle PathUpdateDelegateHandle;` — handle of path's update event delegate
- L72 _protected member_ `FTimerHandle MoveRetryTimerHandle;` — handle of active ConditionalPerformMove timer
- L75 _protected member_ `FTimerHandle PathRetryTimerHandle;` — handle of active ConditionalUpdatePath timer
- L78 _protected member_ `FAIRequestID MoveRequestID;` — request ID of path following's request
- L81 _protected member_ `FNavPathSharedPtr Path;` — currently followed path
- L83 _protected member_ `TEnumAsByte<EPathFollowingResult::Type> MoveResult;`
- L84 _protected member_ `uint8 bUseContinuousTracking : 1;`
- L86 _protected prototype_ `virtual void Activate() override;`
- L87 _protected prototype_ `virtual void OnDestroy(bool bOwnerFinished) override;`
- L89 _protected prototype_ `virtual void Pause() override;`
- L90 _protected prototype_ `virtual void Resume() override;`
- L93 _protected prototype_ `void FinishMoveTask(EPathFollowingResult::Type InResult);` — finish task
- L96 _protected prototype_ `void SetObservedPath(FNavPathSharedPtr InPath);` — stores path and starts observing its events
- L99 _protected prototype_ `virtual void ResetObservers();` — remove all delegates
- L102 _protected prototype_ `virtual void ResetTimers();` — remove all timers
- L105 _protected prototype_ `void ConditionalUpdatePath();` — tries to update invalidated path and handles retry timer
- L108 _protected prototype_ `virtual void PerformMove();` — start move request
- L111 _protected prototype_ `virtual void OnPathEvent(FNavigationPath* InPath, ENavPathEvent::Type Event);` — event from followed path
- L114 _protected prototype_ `virtual void OnRequestFinished(FAIRequestID RequestID, const FPathFollowingResult& Result);` — event from path following

#### Free symbols / members of external scopes

- L14 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMoveTaskCompletedSignature, TEnumAsByte<EPathFollowingResult::Type>, Result, AAIController*, AIController);`
- L14 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMoveTaskCompletedSignature, TEnumAsByte<EPathFollowingResult::Type>, Result, AAIController*, AIController);`
- L15 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FMoveTaskFinishedSignature, TEnumAsByte<EPathFollowingResult::Type>, AAIController*);`
- L15 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FMoveTaskFinishedSignature, TEnumAsByte<EPathFollowingResult::Type>, AAIController*);`

### `Source/Runtime/AIModule/Classes/Tasks/AITask_RunEQS.h` (Public)


#### class `UAITask_RunEQS`  
`class UAITask_RunEQS : public UAITask`  
_L15-37_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAITask`
- L20 _public prototype_ `UAITask_RunEQS(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L23 _public prototype_ `static UAITask_RunEQS* RunEQS(AAIController* Controller, UEnvQuery* QueryTemplate);` — `UFUNCTION(BlueprintCallable, Category = "AI|Tasks", meta = (DefaultToSelf = "Controller", BlueprintInternalUseOnly = "TRUE"))`
- L25 _public function_ `void SetQueryTemplate(UEnvQuery& InQueryTemplate)`
- L26 _public function_ `void SetNotificationDelegate(const FQueryFinishedSignature& InNotificationDelegate)`
- L29 _protected prototype_ `virtual void Activate() override;`
- L31 _protected prototype_ `void OnEQSRequestFinished(TSharedPtr<FEnvQueryResult> Result);`
- L33 _protected member_ `FEQSParametrizedQueryExecutionRequest EQSRequest;`
- L34 _protected member_ `FQueryFinishedSignature EQSFinishedDelegate;`
- L35 _protected member_ `FQueryFinishedSignature NotificationDelegate;`
- L36 _protected member_ `TSharedPtr<FEnvQueryResult> QueryResult;`

### `Source/Runtime/AIModule/Classes/VisualLoggerExtension.h` (Public)


#### class `FVisualLoggerExtension`  
`class FVisualLoggerExtension : public FVisualLogExtensionInterface`  
_L26-42_
- inherits: `FVisualLogExtensionInterface`
- L29 _public prototype_ `virtual void ResetData(IVisualLoggerEditorInterface* EdInterface) override;`
- L30 _public prototype_ `virtual void DrawData(IVisualLoggerEditorInterface* EdInterface, UCanvas* Canvas) override;`
- L31 _public prototype_ `virtual void OnItemsSelectionChanged(IVisualLoggerEditorInterface* EdInterface) override;`
- L32 _public prototype_ `virtual void OnLogLineSelectionChanged(IVisualLoggerEditorInterface* EdInterface, TSharedPtr<struct FLogEntryItem> SelectedItem, int64 UserData) override;`
- L35 _private prototype_ `void DrawData(UWorld* InWorld, class UEQSRenderingComponent* EQSRenderingComponent, UCanvas* Canvas, AActor* HelperActor, const FName& TagName, const FVisualLogDataBlock& DataBlock, double Timestamp);`
- L36 _private prototype_ `void DisableEQSRendering(AActor* HelperActor);`
- L39 _protected member_ `int32 SelectedEQSId = INDEX_NONE;`
- L40 _protected member_ `float CurrentTimestamp = FLT_MIN;`
- L41 _protected member_ `TArray<TWeakObjectPtr<class UEQSRenderingComponent> > EQSRenderingComponents;`

#### class `UVisualLoggerExtension`  
`class UVisualLoggerExtension : public UObject`  
_L46-49_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UObject`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace EVisLogTags`
- L18 _variable_ `const FString TAG_EQS = "Lo` (scope `EVisLogTags`)

### `Source/Runtime/AIModule/Private/AIModuleLog.h` (Private)


#### Free symbols / members of external scopes

- L24 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAINavigation, Warning, All);`
- L24 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAINavigation, Warning, All);`
- L25 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogCrowdFollowing, Warning, All);`
- L25 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogCrowdFollowing, Warning, All);`
- L26 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAIModuleGameplayDebugger, Log, All);`
- L26 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAIModuleGameplayDebugger, Log, All);`

### `Source/Runtime/AIModule/Private/BehaviorTree/ValueOrBBKeyBlueprintUtility.h` (Private)


#### class `UValueOrBBKeyBlueprintUtility`  
`class UValueOrBBKeyBlueprintUtility : public UBlueprintFunctionLibrary`  
_L21-57_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L26 _public prototype_ `static bool GetBool(const FValueOrBBKey_Bool& Value, const UBehaviorTreeComponent* BehaviorTreeComp);` — `UFUNCTION(BlueprintPure, Category = Blackboard)`
- L29 _public prototype_ `static UClass* GetClass(const FValueOrBBKey_Class& Value, const UBehaviorTreeComponent* BehaviorTreeComp);` — `UFUNCTION(BlueprintPure, Category = Blackboard)`
- L32 _public prototype_ `static uint8 GetEnum(const FValueOrBBKey_Enum& Value, const UBehaviorTreeComponent* BehaviorTreeComp);` — `UFUNCTION(BlueprintPure, Category = Blackboard)`
- L35 _public prototype_ `static float GetFloat(const FValueOrBBKey_Float& Value, const UBehaviorTreeComponent* BehaviorTreeComp);` — `UFUNCTION(BlueprintPure, Category = Blackboard)`
- L38 _public prototype_ `static int32 GetInt32(const FValueOrBBKey_Int32& Value, const UBehaviorTreeComponent* BehaviorTreeComp);` — `UFUNCTION(BlueprintPure, Category = Blackboard)`
- L41 _public prototype_ `static FName GetName(const FValueOrBBKey_Name& Value, const UBehaviorTreeComponent* BehaviorTreeComp);` — `UFUNCTION(BlueprintPure, Category = Blackboard)`
- L44 _public prototype_ `static FString GetString(const FValueOrBBKey_String& Value, const UBehaviorTreeComponent* BehaviorTreeComp);` — `UFUNCTION(BlueprintPure, Category = Blackboard)`
- L47 _public prototype_ `static UObject* GetObject(const FValueOrBBKey_Object& Value, const UBehaviorTreeComponent* BehaviorTreeComp);` — `UFUNCTION(BlueprintPure, Category = Blackboard)`
- L50 _public prototype_ `static FRotator GetRotator(const FValueOrBBKey_Rotator& Value, const UBehaviorTreeComponent* BehaviorTreeComp);` — `UFUNCTION(BlueprintPure, Category = Blackboard)`
- L53 _public prototype_ `static FVector GetVector(const FValueOrBBKey_Vector& Value, const UBehaviorTreeComponent* BehaviorTreeComp);` — `UFUNCTION(BlueprintPure, Category = Blackboard)`
- L56 _public prototype_ `static FInstancedStruct GetStruct(const FValueOrBBKey_Struct& Value, const UBehaviorTreeComponent* BehaviorTreeComp);` — `UFUNCTION(BlueprintPure, Category = Blackboard)`

### `Source/Runtime/AIModule/Private/EnvironmentQuery/EnvQueryTraceHelpers.h` (Private)


#### enum `FEQSHelpers::ETraceMode`  
`enum class ETraceMode : uint8`  
_L19-23_
- L21 _public enumerator_ `Keep`
- L22 _public enumerator_ `Discard`

#### struct `FEQSHelpers::FBatchTrace`  
`struct FBatchTrace`  
_L25-83_
- L27 _public member_ `UWorld* World;`
- L28 _public member_ `const FVector Extent;`
- L29 _public member_ `const FCollisionQueryParams QueryParams;`
- L30 _public member_ `FCollisionResponseParams ResponseParams;`
- L31 _public member_ `enum ECollisionChannel Channel;`
- L32 _public member_ `ETraceMode TraceMode;`
- L33 _public member_ `TArray<uint8> TraceHits;`
- L35 _public function_ `FBatchTrace(UWorld* InWorld, enum ECollisionChannel InChannel, const FCollisionQueryParams& InParams, const FVector& InExtent, ETraceMode InTraceMode) : World(InWorld), Extent(InExtent), QueryParams(InParams), Channel(InChannel), TraceMode(InTraceMode)`
- L42 _public function_ `FBatchTrace(UWorld* InWorld, const FEnvTraceData& TraceData, const FCollisionQueryParams& InParams, const FVector& InExtent, ETraceMode InTraceMode) : World(InWorld), Extent(InExtent), QueryParams(InParams), TraceMode(InTraceMode)`
- L56 _public prototype_ `bool RunLineTrace(const FVector& StartPos, const FVector& EndPos, FVector& HitPos) const;`
- L58 _public prototype_ `bool RunSphereTrace(const FVector& StartPos, const FVector& EndPos, FVector& HitPos) const;`
- L60 _public prototype_ `bool RunCapsuleTrace(const FVector& StartPos, const FVector& EndPos, FVector& HitPos) const;`
- L62 _public prototype_ `bool RunBoxTrace(const FVector& StartPos, const FVector& EndPos, FVector& HitPos) const;`
- L65 _public function_ `template<EEnvTraceShape::Type TraceType> void DoSingleSourceMultiDestinations(const FVector& Source, TArray<FNavLocation>& Points)`
- L73 _public function_ `template<EEnvTraceShape::Type TraceType> void DoMultiSourceMultiDestinations2D(const TArray<FRayStartEnd>& Rays, TArray<FNavLocation>& OutPoints)` — note that this function works slightly different in terms of discarding items. "Accepted" items get added to the OutPoints array
- L79 _public function_ `template<EEnvTraceShape::Type TraceType> void DoProject(TArray<FNavLocation>& Points, float StartOffsetZ, float EndOffsetZ, float HitOffsetZ)`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace FEQSHelpers`
- L85 _prototype_ `void RunNavRaycasts(const ANavigationData& NavData, const UObject& Querier, const FEnvTraceData& TraceData, const FVector& SourcePt, TArray<FNavLocation>& Points, const ETraceMode TraceMode = ETraceMode::Keep);` (scope `FEQSHelpers`)
- L86 _prototype_ `void RunNavProjection(const ANavigationData& NavData, const UObject& Querier, const FEnvTraceData& TraceData, TArray<FNavLocation>& Points, const ETraceMode TraceMode = ETraceMode::Discard);` (scope `FEQSHelpers`)
- L87 _prototype_ `void RunPhysRaycasts(UWorld* World, const FEnvTraceData& TraceData, const FVector& SourcePt, TArray<FNavLocation>& Points, const TArray<AActor*>& IgnoredActors, const ETraceMode TraceMode = ETraceMode::Keep);` (scope `FEQSHelpers`)
- L88 _prototype_ `void RunPhysProjection(UWorld* World, const FEnvTraceData& TraceData, TArray<FNavLocation>& Points, const ETraceMode TraceMode = ETraceMode::Discard);` (scope `FEQSHelpers`)
- L89 _prototype_ `void RunPhysProjection(UWorld* World, const FEnvTraceData& TraceData, TArray<FNavLocation>& Points, TArray<uint8>& TraceHits);` (scope `FEQSHelpers`)
- L93 _prototype_ `void RunRaycastsOnNavHitOnlyWalls(const ANavigationData& NavData, const UObject& Querier, const FEnvTraceData& TraceData, const FVector& SourcePt, TArray<FNavLocation>& Points, const TArray<AActor*>& IgnoredActors, const ETraceMode TraceMode = ETraceMode::Keep);` (scope `FEQSHelpers`) — Does initial raycast on navmesh, just like, RunNavRaycasts but once it hits navmesh edge it does a geometry trace to determine whether it hit a wall or a ledge (empty space).
- L98 _prototype_ `void RunNavRaycasts(const ANavigationData& NavData, const FEnvTraceData& TraceData, const FVector& SourcePt, TArray<FNavLocation>& Points, ETraceMode TraceMode = ETraceMode::Keep);` (scope `FEQSHelpers`) — `UE_DEPRECATED_FORGAME(4.12, "This function is now deprecated, please use version with Querier argument instead.")`
- L101 _prototype_ `void RunNavProjection(const ANavigationData& NavData, const FEnvTraceData& TraceData, TArray<FNavLocation>& Points, ETraceMode TraceMode = ETraceMode::Discard);` (scope `FEQSHelpers`) — `UE_DEPRECATED_FORGAME(4.12, "This function is now deprecated, please use version with Querier argument instead.")`

### `Source/Runtime/AIModule/Public/AIConfig.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace FAIConfig`
- L10 _namespace_ `namespace Navigation` (scope `FAIConfig`)
- L13 _externvar_ `extern float FocalPointDistance;` (scope `FAIConfig::Navigation`) — distance to focal point along current velocity vector

### `Source/Runtime/AIModule/Public/AIHelpers.h` (Public)


#### Free symbols / members of external scopes

- L16 _namespace_ `namespace FAISystem`
- L18 _prototype_ `FVector FindClosestLocation(const FVector& Origin, const TArray<FVector>& Locations);` (scope `FAISystem`)
- L51 _prototype_ `bool CheckIsTargetInSightCone(const FVector& StartLocation, const FVector& ConeDirectionNormal, float PeripheralVisionAngleCos, float ConeDirectionBackwardOffset, float NearClippingRadiusSq, float const FarClippingRadiusSq, const FVector& TargetLocation);` (scope `FAISystem`)
- L55 _namespace_ `namespace UE`
- L55 _namespace_ `namespace AI` (scope `UE`)
- L62 _prototype_ `extern TOptional<float> GetYawFromVector(const FVector& Vector);` (scope `UE::AI`) — `UE_DEPRECATED(5.2, "Deprecated as returning float instead of FVector::FReal. Use FVector::ToOrientationRotator()::Yaw etc.")` — This method will extract the yaw radian from the specified vector (The vector does not need to be normalized) if it is not possible to compute yaw, the function will return an invalid value	 *
- L69 _prototype_ `extern TOptional<float> GetYawFromRotator(const FRotator& Rotator);` (scope `UE::AI`) — `UE_DEPRECATED(5.2, "Deprecated as returning float instead of FVector::FReal. Use FRotator::Yaw etc.")` — This method will extract the yaw radian from the specified rotator if it is not possible to compute yaw, the function will not return an invalid value
- L76 _prototype_ `extern TOptional<float> GetYawFromQuaternion(const FQuat& Quaternion);` (scope `UE::AI`) — `UE_DEPRECATED(5.2, "Deprecated as returning float instead of FVector::FReal. Use FQuat::Rotator()::Yaw etc.")` — This method will extract the yaw radian from the specified quaternion if it is not possible to compute yaw, the function will not return an invalid value
- L79 _prototype_ `extern void GetActorClassDefaultComponents(const TSubclassOf<AActor>& ActorClass, TArray<UActorComponent*>& OutComponents, const TSubclassOf<UActorComponent>& InComponentClass = TSubclassOf<UActorComponent>());` (scope `UE::AI`) — `UE_DEPRECATED(5.3, "Please use UE::BlueprintTools::GetActorClassDefaultComponents() instead")`

### `Source/Runtime/AIModule/Public/AIModule.h` (Public)


#### class `IAIModule`  
`class IAIModule : public IAISystemModule`  
_L15-45_
- inherits: `IAISystemModule`
- desc: The public interface to this module
- L26 _public function_ `static inline IAIModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L36 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L43 _public prototype_ `virtual EAssetTypeCategories::Type GetAIAssetCategoryBit() const = 0;` — `UE_DEPRECATED(5.3, "Should use a UAssetDefinitionDefault and return EAssetCategoryPaths::AI instead.")`

### `Source/Runtime/AIModule/Public/BVTree.h` (Public)


#### struct `TBVTree`  
`template<typename InElementType, typename InAllocator = FDefaultAllocator> struct TBVTree`  
_L20-223_
- desc: BVTree - Bounding Volumes Tree A binary search tree where each node has a Bounding Volume which is either an element (leaf nodes) or a volume encompassing all of its children (non-leaf nodes). It provides fast gathering of all bounding volumes overlapping a given FBox (see GetOverlapping). Users are expected to provide an implementation of CalcElementBounds for ElementType: static FBox CalcElementBounds(const FElement& Element) const
- L22 _public typedef_ `typedef InElementType FElement;`
- L36 _public function_ `TBVTree()`
- L38 _public function_ `TBVTree(const TArray<FElement>& InElements)`
- L43 _public function_ `TBVTree(TArray<FElement>&& InElements)`
- L50 _public function_ `void RecreateTree()` — Recreate the tree based on the current content of Elements. Callers are expected to have filled the GetElements() array before calling this function.
- L57 _public function_ `void RecreateTree(const TArray<FElement>& InElements)`
- L63 _public function_ `void RecreateTree(TArray<FElement>&& InElements)`
- L69 _public function_ `void GetOverlapping(const FBox& Box, TArray<FElement>& OutOverlappingElements) const`
- L89 _public function_ `const TArray<int16, InAllocator>& GetNodes() const`
- L90 _public function_ `const TArray<FBox, InAllocator>& GetBoundingBoxes() const`
- L91 _public function_ `const TArray<FElement>& GetElements() const`
- L92 _public function_ `TArray<FElement>& GetElements()`
- L94 _public function_ `bool IsEmpty() const`
- L97 _protected function_ `void Subdivide(TArray<FElementBox>& ElementBBoxes, const int StartIndex, const int LimitIndex, int& CurrentNode)`
- L147 _protected function_ `void Reset()`
- L154 _protected function_ `void Create(const TArray<FElement>& InElements)`
- L162 _protected function_ `void Create(TArray<FElement>&& InElements)`
- L170 _protected function_ `void CreateCommonInternal()` — assumes Elements has been set up
- L194 _protected function_ `static FBox CalcNodeBounds(const TArray<FElementBox>& ElementBBoxes, const int StartIndex, const int LimitIndex)`
- L204 _protected function_ `static int GetLongestAxis(const FBox& NodeBounds)`
- L216 _protected prototype_ `static FBox CalcElementBounds(const FElement& );` — you have to supply this yourself
- L220 _private member_ `TArray<int16, InAllocator> Nodes;`
- L221 _private member_ `TArray<FBox, InAllocator> NodeBoundingBoxes;`
- L222 _private member_ `TArray<FElement> Elements;`

#### struct `TBVTree::FElementBox`  
`struct FElementBox : public FBox`  
_L24-34_
- inherits: `FBox`
- L27 _public member_ `int ElementIndex;` — index to TBVTree.Elements
- L29 _public function_ `FElementBox() : FBox(ForceInit), ElementIndex(-1)`
- L32 _public function_ `FElementBox(const FBox& Box) : FBox(Box), ElementIndex(-1)`

#### struct `TBVTree::Subdivide::FAxisSort`  
`struct FAxisSort`  
_L125-134_
- L127 _public member_ `const int Axis;`
- L128 _public function_ `FAxisSort(const int InAxis) : Axis(InAxis)`
- L130 _public function_ `bool operator()(const FElementBox& A, const FElementBox& B) const`

### `Source/Runtime/AIModule/Public/BehaviorTreeDelegates.h` (Public)


#### struct `FBehaviorTreeDelegates`  
`struct FBehaviorTreeDelegates`  
_L12-28_
- L15 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnTreeStarted, const UBehaviorTreeComponent&, const UBehaviorTree& );` — delegate type for tree execution events (Params: const UBehaviorTreeComponent* OwnerComp, const UBehaviorTree* TreeAsset)
- L18 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTreeDebugTool, const APawn*);` — delegate type for locking AI debugging tool on pawn
- L21 _public member_ `static FOnTreeStarted OnTreeStarted;` — Called when the behavior tree starts execution.
- L24 _public member_ `static FOnTreeDebugTool OnDebugSelected;` — Called when the AI debug tool highlights a pawn.
- L27 _public member_ `static FOnTreeDebugTool OnDebugLocked;` — Called when the AI debug tool locks on pawn.

#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnTreeStarted, const UBehaviorTreeComponent&, const UBehaviorTree& );` — delegate type for tree execution events (Params: const UBehaviorTreeComponent* OwnerComp, const UBehaviorTree* TreeAsset)
- L18 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTreeDebugTool, const APawn*);` — delegate type for locking AI debugging tool on pawn

### `Source/Runtime/AIModule/Public/BehaviorTreeNodeInitializationData.h` (Public)


#### struct `FBehaviorTreeNodeInitializationData`  
`struct FBehaviorTreeNodeInitializationData`  
_L9-36_
- L11 _public member_ `UBTNode* Node;`
- L12 _public member_ `UBTCompositeNode* ParentNode;`
- L13 _public member_ `uint16 ExecutionIndex;`
- L14 _public member_ `uint16 DataSize;`
- L15 _public member_ `uint16 SpecialDataSize;`
- L16 _public member_ `uint8 TreeDepth;`
- L18 _public function_ `FBehaviorTreeNodeInitializationData()`
- L19 _public function_ `FBehaviorTreeNodeInitializationData(UBTNode* InNode, UBTCompositeNode* InParentNode, uint16 InExecutionIndex, uint8 InTreeDepth, uint16 NodeMemory, uint16 SpecialNodeMemory = 0) : Node(InNode), ParentNode(InParentNode), ExecutionIndex(InExecutionIndex), TreeDepth(InTreeDepth)`

#### struct `FBehaviorTreeNodeInitializationData::FMemorySort`  
`struct FMemorySort`  
_L29-35_
- L31 _public function_ `inline bool operator()(const FBehaviorTreeNodeInitializationData& A, const FBehaviorTreeNodeInitializationData& B) const`

### `Source/Runtime/AIModule/Public/BlueprintNodeHelpers.h` (Public)


#### Free symbols / members of external scopes

- L14 _namespace_ `namespace BlueprintNodeHelpers`
- L16 _prototype_ `FString CollectPropertyDescription(const UObject* Ob, const UClass* StopAtClass, const TArray<FProperty*>& InPropertiesToSkip);` (scope `BlueprintNodeHelpers`)
- L17 _prototype_ `FString CollectPropertyDescription(const UObject* Ob, const UClass* StopAtClass, TFunctionRef<bool(FProperty* )> ShouldSkipProperty);` (scope `BlueprintNodeHelpers`)
- L18 _prototype_ `void CollectPropertyData(const UObject* Ob, const UClass* StopAtClass, TArray<FProperty*>& PropertyData);` (scope `BlueprintNodeHelpers`)
- L19 _prototype_ `uint16 GetPropertiesMemorySize(const TArray<FProperty*>& PropertyData);` (scope `BlueprintNodeHelpers`)
- L21 _prototype_ `void CollectBlackboardSelectors(const UObject* Ob, const UClass* StopAtClass, TArray<FName>& KeyNames);` (scope `BlueprintNodeHelpers`)
- L22 _prototype_ `void ResolveBlackboardSelectors(UObject& Ob, const UClass& StopAtClass, const UBlackboardData& BlackboardAsset);` (scope `BlueprintNodeHelpers`)
- L23 _prototype_ `bool HasAnyBlackboardSelectors(const UObject* Ob, const UClass* StopAtClass);` (scope `BlueprintNodeHelpers`)
- L25 _prototype_ `FString DescribeProperty(const FProperty* Prop, const uint8* PropertyAddr);` (scope `BlueprintNodeHelpers`)
- L26 _prototype_ `void DescribeRuntimeValues(const UObject* Ob, const TArray<FProperty*>& PropertyData, TArray<FString>& RuntimeValues);` (scope `BlueprintNodeHelpers`)
- L28 _prototype_ `void CopyPropertiesToContext(const TArray<FProperty*>& PropertyData, uint8* ObjectMemory, uint8* ContextMemory);` (scope `BlueprintNodeHelpers`)
- L29 _prototype_ `void CopyPropertiesFromContext(const TArray<FProperty*>& PropertyData, uint8* ObjectMemory, uint8* ContextMemory);` (scope `BlueprintNodeHelpers`)
- L31 _prototype_ `bool FindNodeOwner(AActor* OwningActor, UBTNode* Node, UBehaviorTreeComponent*& OwningComp, int32& OwningInstanceIdx);` (scope `BlueprintNodeHelpers`)
- L33 _prototype_ `void AbortLatentActions(UActorComponent& OwnerOb, const UObject& Ob);` (scope `BlueprintNodeHelpers`)
- L35 _function_ `inline bool HasBlueprintFunction(FName FuncName, const UObject& Object, const UClass& StopAtClass)` (scope `BlueprintNodeHelpers`)
- L42 _function_ `inline FString GetNodeName(const UObject& NodeObject)` (scope `BlueprintNodeHelpers`)

### `Source/Runtime/AIModule/Public/DefaultManagerInstanceTracker.h` (Public)


#### struct `TDefaultManagerInstanceTracker`  
`template<typename FManager> struct TDefaultManagerInstanceTracker`  
_L12-65_
- L14 _public member_ `TMap<UWorld*, FManager*> WorldToInstanceMap;`
- L15 _public member_ `bool bCreateIfMissing = false;`
- L18 _public function_ `TDefaultManagerInstanceTracker()` — `UE_DEPRECATED(5.1, "TDefaultManagerInstanceTracker is deprecated and will be removed. Consider inheriting from a subsystem instead.")`
- L23 _public function_ `FManager* GetManagerInstance(UWorld& World)` — `UE_DEPRECATED(5.1, "TDefaultManagerInstanceTracker is deprecated and will be removed. Consider inheriting from a subsystem instead.")`
- L56 _public function_ `void OnPostWorldCleanup(UWorld* World, bool , bool )`

#### Free symbols / members of external scopes

- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogManagerInstanceTracker, Warning, All);`

### `Source/Runtime/AIModule/Public/GameplayDebugger/GameplayDebuggerCategory_AI.h` (Public)


#### class `FGameplayDebuggerCategory_AI`  
`class FGameplayDebuggerCategory_AI : public FGameplayDebuggerCategory`  
_L20-92_
- inherits: `FGameplayDebuggerCategory`
- L23 _public prototype_ `FGameplayDebuggerCategory_AI();`
- L25 _public prototype_ `virtual void CollectData(APlayerController* OwnerPC, AActor* DebugActor) override;`
- L26 _public prototype_ `virtual void OnDataPackReplicated(int32 DataPackId) override;`
- L27 _public prototype_ `virtual void DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext) override;`
- L28 _public prototype_ `virtual FDebugRenderSceneProxy* CreateDebugSceneProxy(const UPrimitiveComponent* InComponent, FDebugDrawDelegateHelper*& OutDelegateHelper) override;`
- L30 _public prototype_ `static TSharedRef<FGameplayDebuggerCategory> MakeInstance();`
- L33 _protected prototype_ `void CollectPathData(AAIController* DebugAI);`
- L34 _protected prototype_ `void DrawPath(UWorld* World);`
- L35 _protected prototype_ `void DrawPawnIcons(UWorld* World, AActor* DebugActor, APawn* SkipPawn, FGameplayDebuggerCanvasContext& CanvasContext);`
- L36 _protected prototype_ `void DrawOverheadInfo(AActor& DebugActor, FGameplayDebuggerCanvasContext& CanvasContext);`
- L70 _protected member_ `FRepData DataPack;`
- L85 _protected member_ `FRepDataPath PathDataPack;`
- L86 _protected member_ `int32 PathDataPackId;`
- L90 _private member_ `FNavigationPath* RawLastPath;` — do NOT read from this pointer, it's only for validating if path has changed and can be invalid!
- L91 _private member_ `double LastPathUpdateTime;`

#### struct `FGameplayDebuggerCategory_AI::FRepData`  
`struct FRepData`  
_L38-69_
- L40 _public member_ `FString ControllerName;`
- L41 _public member_ `FString PawnName;`
- L42 _public member_ `FString MovementBaseInfo;`
- L43 _public member_ `FString MovementModeInfo;`
- L44 _public member_ `FString PathFollowingInfo;`
- L45 _public member_ `int32 NextPathPointIndex;`
- L46 _public member_ `FVector PathGoalLocation;`
- L47 _public member_ `FString CurrentAITask;`
- L48 _public member_ `FString CurrentAIState;`
- L49 _public member_ `FString CurrentAIAssets;`
- L50 _public member_ `FString NavDataInfo;`
- L51 _public member_ `FString MontageInfo;`
- L52 _public member_ `FString TaskQueueInfo;`
- L53 _public member_ `FString TickingTaskInfo;`
- L54 _public member_ `int16 NumTasksInQueue;`
- L55 _public member_ `int16 NumTickingTasks;`
- L56 _public member_ `uint32 bHasController : 1;`
- L57 _public member_ `uint32 bPathHasGoalActor : 1;`
- L58 _public member_ `uint32 bIsUsingPathFollowing : 1;`
- L59 _public member_ `uint32 bIsUsingCharacter : 1;`
- L60 _public member_ `uint32 bIsUsingBehaviorTree : 1;`
- L61 _public member_ `uint32 bIsUsingGameplayTasks : 1;`
- L63 _public function_ `FRepData() : NextPathPointIndex(0), NumTasksInQueue(0), NumTickingTasks(0), bHasController(false), bPathHasGoalActor(false), bIsUsingPathFollowing(false), bIsUsingCharacter(false), bIsUsingBehaviorTree(false), bIsUsingGameplayTasks(false)`
- L68 _public prototype_ `void Serialize(FArchive& Ar);`

#### struct `FGameplayDebuggerCategory_AI::FRepDataPath`  
`struct FRepDataPath`  
_L72-84_
- L80 _public member_ `TArray<FPoly> PathCorridor;`
- L81 _public member_ `TArray<FVector> PathPoints;`
- L83 _public prototype_ `void Serialize(FArchive& Ar);`

#### struct `FGameplayDebuggerCategory_AI::FRepDataPath::FPoly`  
`struct FPoly`  
_L74-78_
- L76 _public member_ `TArray<FVector> Points;`
- L77 _public member_ `FColor Color;`

### `Source/Runtime/AIModule/Public/GameplayDebugger/GameplayDebuggerCategory_BehaviorTree.h` (Public)


#### class `FGameplayDebuggerCategory_BehaviorTree`  
`class FGameplayDebuggerCategory_BehaviorTree : public FGameplayDebuggerCategory`  
_L13-47_
- inherits: `FGameplayDebuggerCategory`
- L16 _public prototype_ `FGameplayDebuggerCategory_BehaviorTree();`
- L18 _public prototype_ `virtual void CollectData(APlayerController* OwnerPC, AActor* DebugActor) override;`
- L19 _public prototype_ `virtual void DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext) override;`
- L21 _public prototype_ `static TSharedRef<FGameplayDebuggerCategory> MakeInstance();`
- L32 _protected member_ `FRepData DataPack;`
- L37 _private prototype_ `void ScrollUp();` — Bound on Shift- decrease the blackboard display starting index
- L40 _private prototype_ `void ScrollDown();` — Bound on Shift+ increase the blackboard display starting index
- L43 _private member_ `int32 DisplayStartingIndex = 0;` — Current blackboard display starting index
- L46 _private member_ `static constexpr int32 PagingOffset = 5;` — Offset used to move up or down the paging

#### struct `FGameplayDebuggerCategory_BehaviorTree::FRepData`  
`struct FRepData`  
_L24-31_
- L26 _public member_ `FString CompName;`
- L27 _public member_ `FString TreeDesc;`
- L28 _public member_ `FString BlackboardDesc;`
- L30 _public prototype_ `void Serialize(FArchive& Ar);`

### `Source/Runtime/AIModule/Public/GameplayDebugger/GameplayDebuggerCategory_EQS.h` (Public)


#### class `FGameplayDebuggerCategory_EQS`  
`class FGameplayDebuggerCategory_EQS : public FGameplayDebuggerCategory`  
_L15-52_
- inherits: `FGameplayDebuggerCategory`
- L18 _public prototype_ `FGameplayDebuggerCategory_EQS();`
- L20 _public prototype_ `virtual void CollectData(APlayerController* OwnerPC, AActor* DebugActor) override;`
- L21 _public prototype_ `virtual void OnDataPackReplicated(int32 DataPackId) override;`
- L22 _public prototype_ `virtual void DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext) override;`
- L23 _public prototype_ `virtual FDebugRenderSceneProxy* CreateDebugSceneProxy(const UPrimitiveComponent* InComponent, FDebugDrawDelegateHelper*& OutDelegateHelper) override;`
- L25 _public prototype_ `static TSharedRef<FGameplayDebuggerCategory> MakeInstance();`
- L35 _protected member_ `FRepData DataPack;`
- L37 _protected prototype_ `int32 DrawLookedAtItem(const EQSDebug::FQueryData& QueryData, APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext) const;`
- L38 _protected prototype_ `void DrawDetailedItemTable(const EQSDebug::FQueryData& QueryData, int32 LookedAtItemIndex, FGameplayDebuggerCanvasContext& CanvasContext) const;`
- L39 _protected prototype_ `void DrawDetailedItemRow(const EQSDebug::FItemData& ItemData, const TArray<uint8>& TestRelevancy, float MaxScore, FGameplayDebuggerCanvasContext& CanvasContext) const;`
- L42 _protected prototype_ `void CycleShownQueries();`
- L43 _protected prototype_ `void ToggleDetailView();`
- L45 _protected member_ `uint32 bDrawLabels : 1;`
- L46 _protected member_ `uint32 bDrawFailedItems : 1;`
- L47 _protected member_ `uint32 bShowDetails : 1;`
- L49 _protected member_ `int32 MaxItemTableRows;`
- L50 _protected member_ `int32 MaxQueries;`
- L51 _protected member_ `int32 ShownQueryIndex;`

#### struct `FGameplayDebuggerCategory_EQS::FRepData`  
`struct FRepData`  
_L29-34_
- L31 _public member_ `TArray<EQSDebug::FQueryData> QueryDebugData;`
- L33 _public prototype_ `void Serialize(FArchive& Ar);`

### `Source/Runtime/AIModule/Public/GameplayDebugger/GameplayDebuggerCategory_NavLocalGrid.h` (Public)


#### class `FGameplayDebuggerCategory_NavLocalGrid`  
`class FGameplayDebuggerCategory_NavLocalGrid : public FGameplayDebuggerCategory`  
_L12-54_
- inherits: `FGameplayDebuggerCategory`
- L15 _public prototype_ `FGameplayDebuggerCategory_NavLocalGrid();`
- L17 _public prototype_ `virtual void CollectData(APlayerController* OwnerPC, AActor* DebugActor) override;`
- L18 _public prototype_ `virtual void DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext) override;`
- L19 _public prototype_ `virtual FDebugRenderSceneProxy* CreateDebugSceneProxy(const UPrimitiveComponent* InComponent, FDebugDrawDelegateHelper*& OutDelegateHelper) override;`
- L20 _public prototype_ `virtual void OnDataPackReplicated(int32 DataPackId) override;`
- L22 _public prototype_ `static TSharedRef<FGameplayDebuggerCategory> MakeInstance();`
- L52 _protected member_ `FRepData DataPack;`
- L53 _protected member_ `FRepAgentData AgentDataPack;`

#### struct `FGameplayDebuggerCategory_NavLocalGrid::FRepData`  
`struct FRepData`  
_L24-41_
- L35 _public member_ `TArray<FGridData> Grids;`
- L36 _public member_ `int32 NumSources;`
- L37 _public member_ `int32 VersionNum;`
- L39 _public function_ `FRepData() : NumSources(0), VersionNum(0)`
- L40 _public prototype_ `void Serialize(FArchive& Ar);`

#### struct `FGameplayDebuggerCategory_NavLocalGrid::FRepData::FGridData`  
`struct FGridData`  
_L26-33_
- L28 _public member_ `FBox Bounds;`
- L29 _public member_ `float CellSize;`
- L30 _public member_ `int32 NumRows;`
- L31 _public member_ `int32 NumCols;`
- L32 _public member_ `TArray<uint8> Cells;`

#### struct `FGameplayDebuggerCategory_NavLocalGrid::FRepAgentData`  
`struct FRepAgentData`  
_L43-49_
- L45 _public member_ `TArray<int32> PathCells;`
- L46 _public member_ `int32 GridIdx;`
- L48 _public prototype_ `void Serialize(FArchive& Ar);`

### `Source/Runtime/AIModule/Public/GameplayDebugger/GameplayDebuggerCategory_Navmesh.h` (Public)


#### class `FGameplayDebuggerCategory_Navmesh`  
`class FGameplayDebuggerCategory_Navmesh : public FGameplayDebuggerCategory`  
_L14-76_
- inherits: `FGameplayDebuggerCategory`
- L17 _public prototype_ `FGameplayDebuggerCategory_Navmesh();`
- L19 _public prototype_ `virtual void CollectData(APlayerController* OwnerPC, AActor* DebugActor) override;`
- L20 _public prototype_ `virtual void DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext) override;`
- L21 _public prototype_ `virtual FDebugRenderSceneProxy* CreateDebugSceneProxy(const UPrimitiveComponent* InComponent, FDebugDrawDelegateHelper*& OutDelegateHelper) override;`
- L22 _public prototype_ `virtual void OnDataPackReplicated(int32 DataPackId) override;`
- L24 _public prototype_ `static TSharedRef<FGameplayDebuggerCategory> MakeInstance();`
- L28 _protected prototype_ `void CycleNavData();`
- L29 _protected prototype_ `void CycleActorReference();`
- L30 _protected prototype_ `void ToggleLockedReferenceLocation();`
- L34 _protected prototype_ `virtual void CollectNavigationData(const UNavigationSystemV1* NavSys, const ANavigationData* NavData, const APawn* RefPawn);` — Called on the server to collect data for the specified navigation data relative to RefPawn. RefPawn will be used to define the location where we need to collect the data and then call CollectNavigationData's version that receive a location as parameter.
- L36 _protected prototype_ `virtual void CollectNavigationData(const UNavigationSystemV1* NavSys, const ANavigationData* NavData, const FVector& RefLocation);` — Called on the server to collect data for the specified navigation data around a location.
- L37 _protected prototype_ `void RetrieveRelativeTilesToDisplay(TArray<FIntPoint>& OutTileDelta);`
- L60 _protected member_ `FNavMeshSceneProxyData NavmeshRenderData;`
- L61 _protected member_ `FRepData DataPack;`
- L69 _protected member_ `EActorReferenceMode ActorReferenceMode = EActorReferenceMode::DebugActor;`
- L71 _protected member_ `int32 NavDataIndexToDisplay = INDEX_NONE;`
- L72 _protected member_ `bool bSwitchToNextNavigationData = false;`
- L73 _protected member_ `TWeakObjectPtr<const APawn> PrevDebugActorReference;`
- L74 _protected member_ `bool bToggleLockedReferenceLocation = false;`
- L75 _protected member_ `TOptional<FVector> LockedReferenceLocation;`

#### struct `FGameplayDebuggerCategory_Navmesh::FRepData`  
`struct FRepData`  
_L39-58_
- L41 _public prototype_ `void Serialize(FArchive& Ar);`
- L43 _public member_ `FString NavDataName;`
- L44 _public member_ `FString NavBuildLockStatusDesc;`
- L45 _public member_ `FString SupportedAgents;`
- L46 _public member_ `FVector LockedReferenceLocation = FNavigationSystem::InvalidLocation;`
- L47 _public member_ `int32 NumDirtyAreas = 0;`
- L48 _public member_ `int32 NumSuspendedDirtyAreas = 0;`
- L49 _public member_ `int32 NumRunningTasks = 0;`
- L50 _public member_ `int32 NumRemainingTasks = 0;`
- L51 _public member_ `bool bCanChangeReference = false;`
- L52 _public member_ `bool bCanCycleNavigationData = false;`
- L53 _public member_ `bool bIsUsingPlayerActor = false;`
- L54 _public member_ `bool bReferenceTooFarFromNavData = false;`
- L55 _public member_ `bool bIsNavBuildLocked = false;`
- L56 _public member_ `bool bIsNavOctreeLocked = false;`
- L57 _public member_ `bool bIsNavDataRebuildingSuspended = false;`

#### enum `FGameplayDebuggerCategory_Navmesh::EActorReferenceMode`  
`enum class EActorReferenceMode : uint8`  
_L63-68_
- L65 _public enumerator_ `PlayerActorOnly`
- L66 _public enumerator_ `PlayerActor`
- L67 _public enumerator_ `DebugActor`

### `Source/Runtime/AIModule/Public/GameplayDebugger/GameplayDebuggerCategory_Perception.h` (Public)


#### class `FGameplayDebuggerCategory_Perception`  
`class FGameplayDebuggerCategory_Perception : public FGameplayDebuggerCategory`  
_L13-21_
- inherits: `FGameplayDebuggerCategory`
- L16 _public prototype_ `FGameplayDebuggerCategory_Perception();`
- L18 _public prototype_ `virtual void CollectData(APlayerController* OwnerPC, AActor* DebugActor) override;`
- L20 _public prototype_ `static TSharedRef<FGameplayDebuggerCategory> MakeInstance();`

### `Source/Runtime/AIModule/Public/GameplayDebugger/GameplayDebuggerCategory_PerceptionSystem.h` (Public)


#### class `FGameplayDebuggerCategory_PerceptionSystem`  
`class FGameplayDebuggerCategory_PerceptionSystem : public FGameplayDebuggerCategory`  
_L11-20_
- inherits: `FGameplayDebuggerCategory`
- L14 _public prototype_ `FGameplayDebuggerCategory_PerceptionSystem();`
- L16 _public prototype_ `static TSharedRef<FGameplayDebuggerCategory> MakeInstance();`
- L19 _protected prototype_ `virtual void CollectData(APlayerController* OwnerPC, AActor* DebugActor) override;`

### `Source/Runtime/AIModule/Public/GeomUtils.h` (Public)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace AI` (scope `UE`)
- L13 _function_ `inline FVector::FReal Cross2D(const FVector& A, const FVector& B)` (scope `UE::AI`) — @return 2D cross product. Using X and Y components of 3D vectors.
- L19 _function_ `inline FVector2D::FReal Cross2D(const FVector2D& A, const FVector2D& B)` (scope `UE::AI`) — @return 2D cross product.
- L25 _function_ `inline FVector::FReal TriArea2D(const FVector& A, const FVector& B, const FVector& C)` (scope `UE::AI`) — @return 2D area of triangle. Using X and Y components of 3D vectors.
- L33 _function_ `inline FVector2D::FReal TriArea2D(const FVector2D& A, const FVector2D& B, const FVector2D& C)` (scope `UE::AI`) — @return 2D area of triangle.
- L41 _function_ `inline FVector2D::FReal ProjectPointOnSegment2D(const FVector Point, const FVector Start, const FVector End)` (scope `UE::AI`) — @return value in range [0..1] of the 'Point' project on segment 'Start-End'. Using X and Y components of 3D vectors.
- L43 _typedef_ `using FReal = FVector::FReal;` (scope `UE::AI::ProjectPointOnSegment2D`)
- L63 _function_ `inline FVector::FReal ProjectPointOnLine2D(const FVector Point, const FVector Start, const FVector End)` (scope `UE::AI`) — @return value of the 'Point' project on infinite line defined by segment 'Start-End'. Using X and Y components of 3D vectors.
- L65 _typedef_ `using FReal = FVector::FReal;` (scope `UE::AI::ProjectPointOnLine2D`)
- L75 _function_ `inline FVector::FReal SignedDistancePointLine2D(const FVector Point, const FVector Start, const FVector End)` (scope `UE::AI`) — @return signed distance of the 'Point' to infinite line defined by segment 'Start-End'. Using X and Y components of 3D vectors.
- L77 _typedef_ `using FReal = FVector::FReal;` (scope `UE::AI::SignedDistancePointLine2D`)
- L97 _function_ `inline bool IntersectLineLine2D(const FVector& StartA, const FVector& EndA, const FVector& StartB, const FVector& EndB, FVector2D::FReal& OutTA, FVector2D::FReal& OutTB)` (scope `UE::AI`) — Intersects infinite lines defined by segments A and B in 2D. Using X and Y components of 3D vectors. @param StartA start point of segment A @param EndA end point of segment A @param StartB start point of segment B @param EndB end point of segment B @param OutTA intersection value along segment A @param OutTB intersection value along segment B @return if segments A and B intersect in 2D
- L99 _typedef_ `using FReal = FVector::FReal;` (scope `UE::AI::IntersectLineLine2D`)
- L130 _prototype_ `extern bool IntersectSegmentPoly2D(const FVector& Start, const FVector& End, TConstArrayView<FVector> Poly, FVector2D::FReal& OutTMin, FVector2D::FReal& OutTMax, int32& OutSegMin, int32& OutSegMax);` (scope `UE::AI`) — Calculates intersection of segment Start-End with convex polygon Poly in 2D. Using X and Y components of 3D vectors. @param Start start point of the segment @param End end point of the segment @param Poly convex polygon @param OutTMin value along the segment of the first intersection point [0..1] @param OutTMax value along the segment of the second intersection point [0..1] @param OutSegMin index of the polygon segment of the first intersection point @param OutSegMax index of the polygon segment of the second intersection point @return true if the segment inside or intersects with the polygon.
- L142 _function_ `inline FVector Bilinear(const FVector2D UV, const FVector VertexA, const FVector VertexB, const FVector VertexC, const FVector VertexD)` (scope `UE::AI`) — Interpolates bilinear patch A,B,C,D. U interpolates from A->B, and C->D, and V interpolates from AB->CD. @param UV interpolation coordinates [0..1] range @param VertexA first corner @param VertexB second corner @param VertexC third corner @param VertexD fourth corner @return interpolated value.
- L158 _prototype_ `extern FVector2D InvBilinear2D(const FVector Point, const FVector VertexA, const FVector VertexB, const FVector VertexC, const FVector VertexD);` (scope `UE::AI`) — Finds the UV coordinates of the 'Point' on bilinear patch A,B,C,D. U interpolates from A->B, and C->D, and V interpolates from AB->CD. @param Point location inside or close to the bilinear patch @param VertexA first corner @param VertexB second corner @param VertexC third corner @param VertexD fourth corner @return UV interpolation coordinates of the 'Point'.
- L170 _function_ `inline FVector2D InvBilinear2DClamped(const FVector Point, const FVector VertexA, const FVector VertexB, const FVector VertexC, const FVector VertexD)` (scope `UE::AI`) — Finds the UV coordinates of the 'Point' on bilinear patch A,B,C,D. U interpolates from A->B, and C->D, and V interpolates from AB->CD. The UV coordinate is clamped to [0..1] range after inversion. @param Point location inside or close to the bilinear patch @param VertexA first corner @param VertexB second corner @param VertexC third corner @param VertexD fourth corner @return UV interpolation coordinates of the 'Point' in [0..1] range.

### `Source/Runtime/AIModule/Public/GraphAStar.h` (Public)


#### struct `FGraphAStarDefaultPolicy`  
`struct FGraphAStarDefaultPolicy`  
_L7-13_
- L9 _public member_ `static const int32 NodePoolSize = 64;`
- L10 _public member_ `static const int32 OpenSetSize = 64;`
- L11 _public member_ `static const int32 FatalPathLength = 10000;`
- L12 _public member_ `static const bool bReuseNodePoolInSubsequentSearches = false;`

#### enum `EGraphAStarResult`  
`enum EGraphAStarResult`  
_L15-21_
- L17 _public enumerator_ `SearchFail`
- L18 _public enumerator_ `SearchSuccess`
- L19 _public enumerator_ `GoalUnreachable`
- L20 _public enumerator_ `InfiniteLoop`

#### struct `FGraphAStarDefaultNode`  
`template<typename TGraph> struct FGraphAStarDefaultNode`  
_L38-68_
- desc: Default A* node class. Extend this class and pass as a parameter to FGraphAStar for additional functionality
- L40 _public typedef_ `typedef typename TGraph::FNodeRef FGraphNodeRef;`
- L42 _public member_ `const FGraphNodeRef NodeRef;`
- L43 _public member_ `FGraphNodeRef ParentRef;`
- L44 _public member_ `FVector::FReal TraversalCost;`
- L45 _public member_ `FVector::FReal TotalCost;`
- L46 _public member_ `int32 SearchNodeIndex;`
- L47 _public member_ `int32 ParentNodeIndex;`
- L48 _public member_ `uint8 bIsOpened : 1;`
- L49 _public member_ `uint8 bIsClosed : 1;`
- L51 _public function_ `inline FGraphAStarDefaultNode(const FGraphNodeRef& InNodeRef) : NodeRef(InNodeRef) , ParentRef(TIsPointer<FGraphNodeRef>::Value ? (FGraphNodeRef)0 : (FGraphNodeRef)INDEX_NONE) , TraversalCost(TNumericLimits<FVector::FReal>::Max()) , TotalCost(TNumericLimits<FVector::FReal>::Max()) , SearchNodeIndex(INDEX_NONE) , ParentNodeIndex(INDEX_NONE) , bIsOpened(false) , bIsClosed(false)`
- L62 _public function_ `inline void MarkOpened()`
- L63 _public function_ `inline void MarkNotOpened()`
- L64 _public function_ `inline void MarkClosed()`
- L65 _public function_ `inline void MarkNotClosed()`
- L66 _public function_ `inline bool IsOpened() const`
- L67 _public function_ `inline bool IsClosed() const`

#### class `FRangeChecklessAllocator`  
`template<bool DoRangeCheck> class FRangeChecklessAllocator : public FDefaultAllocator`  
_L149-155_
- inherits: `FDefaultAllocator`

#### enum `FRangeChecklessAllocator::(anonymous)`  
`enum`  
_L154-154_
- desc: Set to false if you don't want to lose performance on range checks in performance-critical pathfinding code.

#### struct `TAllocatorTraits`  
`template <> struct TAllocatorTraits<FRangeChecklessAllocator<true>> : TAllocatorTraits<FDefaultAllocator>`  
_L156-156_
- inherits: `TAllocatorTraits<FDefaultAllocator>`

#### struct `TAllocatorTraits`  
`template <> struct TAllocatorTraits<FRangeChecklessAllocator<true>> : TAllocatorTraits<FDefaultAllocator>`  
_L157-157_
- inherits: `TAllocatorTraits<FDefaultAllocator>`

#### struct `FGraphAStar`  
`template<typename TGraph, typename Policy = FGraphAStarDefaultPolicy, typename TSearchNode = FGraphAStarDefaultNode<TGraph>, bool DoRangeCheck = false > struct FGraphAStar`  
_L190-651_
- desc: Generic graph A* implementation TGraph holds graph representation. Needs to implement functions: bool IsValidRef(FNodeRef NodeRef) const;															- returns whether given node identyfication is correct FNodeRef GetNeighbour(const FSearchNode& NodeRef, const int32 NeighbourIndex) const;				- returns neighbour ref it also needs to specify node type FNodeRef		- type used as identification of nodes in the graph TQueryFilter (FindPath's parameter) filter class is what decides which graph edges can be used and at what cost. It needs to implement following functions: FVector::FReal GetHeuristicScale() const;															- used as GetHeuristicCost's multiplier FVector::FReal GetHeuristicCost(const FSearchNode& StartNode, const FSearchNode& EndNode) const;	- estimate of cost from StartNode to EndNode from a search node FVector::FReal GetTraversalCost(const FSearchNode& StartNode, const FSearchNode& EndNode) const;	- real cost of traveling from StartNode directly to EndNode from a search node bool IsTraversalAllowed(const FNodeRef NodeA, const FNodeRef NodeB) const;							- whether traversing given edge is allowed from a NodeRef bool WantsPartialSolution() const;																	- whether to accept solutions that do not reach the goal // Backward compatible methods, please use the FSearchNode version. If the FSearchNode version are implemented, these methods will not be called at all. FNodeRef GetNeighbour(const FNodeRef NodeRef, const int32 NeighbourIndex) const;					- returns 
- L192 _public typedef_ `typedef typename TGraph::FNodeRef FGraphNodeRef;`
- L193 _public typedef_ `typedef TSearchNode FSearchNode;`
- L195 _public typedef_ `using FNodeArray = TArray<FSearchNode, FRangeChecklessAllocator<DoRangeCheck>>;`
- L196 _public typedef_ `using FRangeChecklessSetAllocator = TSetAllocator<TSparseArrayAllocator<FRangeChecklessAllocator<DoRangeCheck>, TInlineAllocator<4, FRangeChecklessAllocator<DoRangeCheck>>>, TInlineAllocator<1, FRangeChecklessAllocator<DoRangeCheck>>>;`
- L197 _public typedef_ `using FNodeMap = TMap<FGraphNodeRef, int32, FRangeChecklessSetAllocator>;`
- L198 _public typedef_ `using FIndexArray = TArray<int32, FRangeChecklessAllocator<DoRangeCheck>>;`
- L320 _public member_ `const TGraph& Graph;`
- L321 _public member_ `FNodePool NodePool;`
- L322 _public member_ `FNodeSorter NodeSorter;`
- L323 _public member_ `FOpenList OpenList;`
- L327 _public prototype_ `DECLARE_OPTIONALLY_IMPLEMENTED_TEMPLATE_CLASS_FUNCTION_1PARAM_CONST(int32, GetNeighbourCount, const FGraphNodeRef, NO_COUNT);` — TGraph optionally implemented wrapper methods
- L334 _public prototype_ `DECLARE_OPTIONALLY_IMPLEMENTED_TEMPLATE_CLASS_FUNCTION_CONST(bool, ShouldIgnoreClosedNodes, false);`
- L335 _public prototype_ `DECLARE_OPTIONALLY_IMPLEMENTED_TEMPLATE_CLASS_FUNCTION_CONST(bool, ShouldIncludeStartNodeInPath, false);`
- L336 _public prototype_ `DECLARE_OPTIONALLY_IMPLEMENTED_TEMPLATE_CLASS_FUNCTION_CONST(bool, ShouldFailOnInvalidEndNode, true);`
- L337 _public prototype_ `DECLARE_OPTIONALLY_IMPLEMENTED_TEMPLATE_CLASS_FUNCTION_CONST(FVector::FReal, GetCostLimit, TNumericLimits<FVector::FReal>::Max());`
- L343 _public prototype_ `DECLARE_OPTIONALLY_IMPLEMENTED_TEMPLATE_CLASS_FUNCTION_2PARAMS(FGraphNodeRef, SetPathInfo, const int32, const FSearchNode&, Obj[Param1] = Param2.NodeRef);` — TResultPathInfo optionally implemented wrapper methods
- L345 _public function_ `FGraphAStar(const TGraph& InGraph) : Graph`
- L357 _public function_ `inline bool ProcessSingleNode(const FSearchNode& EndNode, const bool bIsBound, const TQueryFilter& Filter, int32& OutBestNodeIndex, float& OutBestNodeCost)` — `UE_DEPRECATED(5.1, "Please use ProcessSingleNode() taking FVector::FReal& OutBestNodeCost instead!")`
- L371 _public function_ `template<typename TQueryFilter> inline bool ProcessSingleNode(const FSearchNode& EndNode, const bool bIsBound, const TQueryFilter& Filter, int32& OutBestNodeIndex, FVector::FReal& OutBestNodeCost)` — Single run of A* loop: get node from open set and process neighbors returns true if loop should be continued
- L504 _public function_ `template<typename TQueryFilter, typename TResultPathInfo = TArray<FGraphNodeRef> > EGraphAStarResult FindPath(const FSearchNode& StartNode, const FSearchNode& EndNode, const TQueryFilter& Filter, TResultPathInfo& OutPath)` — Performs the actual search. @param [OUT] OutPath - on successful search contains a sequence of graph nodes representing solution optimal within given constraints
- L609 _public function_ `template<typename TQueryFilter> EGraphAStarResult FloodFrom(const FSearchNode& StartNode, const TQueryFilter& Filter)` — Floods node pool until running out of either free nodes or open set
- L647 _public function_ `template<typename TQueryFilter> bool HasReachMaxSearchNodes(const TQueryFilter& Filter) const`

#### struct `FGraphAStar::FNodeSorter`  
`struct FNodeSorter`  
_L200-212_
- L202 _public member_ `const FNodeArray& NodePool;`
- L204 _public function_ `FNodeSorter(const FNodeArray& InNodePool) : NodePool(InNodePool)`
- L208 _public function_ `inline bool operator()(const int32 A, const int32 B) const`

#### struct `FGraphAStar::FNodePool`  
`struct FNodePool : FNodeArray`  
_L214-270_
- inherits: `FNodeArray`
- L216 _public typedef_ `typedef FNodeArray Super;`
- L217 _public member_ `FNodeMap NodeMap;`
- L219 _public function_ `FNodePool()`
- L225 _public function_ `inline FSearchNode& Add(const FSearchNode& SearchNode)`
- L233 _public function_ `inline FSearchNode& FindOrAdd(const FGraphNodeRef NodeRef)`
- L251 _public function_ `inline FSearchNode* Find(const FGraphNodeRef NodeRef)`
- L257 _public function_ `inline void Reset()`
- L263 _public function_ `inline void ReinitNodes()`

#### struct `FGraphAStar::FOpenList`  
`struct FOpenList : FIndexArray`  
_L272-318_
- inherits: `FIndexArray`
- L274 _public typedef_ `typedef FIndexArray Super;`
- L275 _public member_ `FNodeArray& NodePool;`
- L276 _public member_ `const FNodeSorter& NodeSorter;`
- L278 _public function_ `FOpenList(FNodeArray& InNodePool, const FNodeSorter& InNodeSorter) : NodePool`
- L284 _public function_ `void Push(FSearchNode& SearchNode)`
- L290 _public function_ `void Modify(FSearchNode& SearchNode)`
- L303 _public function_ `int32 PopIndex()`
- L314 _public function_ `inline int32 PopIndex(bool bAllowShrinking)` — `UE_DEPRECATED(5.4, "PopIndex with a boolean bAllowShrinking has been deprecated - please use the version without parameter")`

#### Free symbols / members of external scopes

- L23 _variable_ `inline const int32 NO_COUNT = INT_MAX;`
- L26 _macro_ `#define ENABLE_GRAPH_ASTAR_LOGGING 0` — To get AStar Graph tracing, enable this define
- L28 _macro_ `#define UE_GRAPH_ASTAR_LOG(Verbosity, Format, ...) UE_LOG(LogAStar, Verbosity, Format, __VA_ARGS__)`
- L30 _macro_ `#define UE_GRAPH_ASTAR_LOG(...)`
- L70 _macro_ `#define DECLARE_OPTIONALLY_IMPLEMENTED_TEMPLATE_CLASS_FUNCTION_IMPL( TemplateClass, TemplateClassParameter, ConditionalReturnType, ConditionalFunctionName, DefaultImpl ) \`
- L87 _macro_ `#define DECLARE_OPTIONALLY_IMPLEMENTED_TEMPLATE_CLASS_FUNCTION( ConditionalReturnType, ConditionalFunctionName, DefaultImpl ) DECLARE_OPTIONALLY_IMPLEMENTED_TEMPLATE_CLASS_FUNCTION_IMPL( TemplateClass, TemplateClass, ConditionalReturnType, `
- L88 _macro_ `#define DECLARE_OPTIONALLY_IMPLEMENTED_TEMPLATE_CLASS_FUNCTION_CONST( ConditionalReturnType, ConditionalFunctionName, DefaultImpl ) DECLARE_OPTIONALLY_IMPLEMENTED_TEMPLATE_CLASS_FUNCTION_IMPL( TemplateClass, const TemplateClass, Conditional`
- L90 _macro_ `#define DECLARE_OPTIONALLY_IMPLEMENTED_TEMPLATE_CLASS_FUNCTION_1PARAM_IMPL( TemplateClass, TemplateClassParameter, ConditionalReturnType, ConditionalFunctionName, ConditionalParamType1, DefaultImpl) \`
- L107 _macro_ `#define DECLARE_OPTIONALLY_IMPLEMENTED_TEMPLATE_CLASS_FUNCTION_1PARAM( ConditionalReturnType, ConditionalFunctionName, ConditionalParamType1, DefaultImpl) DECLARE_OPTIONALLY_IMPLEMENTED_TEMPLATE_CLASS_FUNCTION_1PARAM_IMPL( TemplateClass, Te`
- L108 _macro_ `#define DECLARE_OPTIONALLY_IMPLEMENTED_TEMPLATE_CLASS_FUNCTION_1PARAM_CONST( ConditionalReturnType, ConditionalFunctionName, ConditionalParamType1, DefaultImpl) DECLARE_OPTIONALLY_IMPLEMENTED_TEMPLATE_CLASS_FUNCTION_1PARAM_IMPL( TemplateCla`
- L110 _macro_ `#define DECLARE_OPTIONALLY_IMPLEMENTED_TEMPLATE_CLASS_FUNCTION_2PARAMS_IMPL( TemplateClass, TemplateClassParameter, ConditionalReturnType, ConditionalFunctionName, ConditionalParamType1, ConditionalParamType2, DefaultImpl) \`
- L127 _macro_ `#define DECLARE_OPTIONALLY_IMPLEMENTED_TEMPLATE_CLASS_FUNCTION_2PARAMS( ConditionalReturnType, ConditionalFunctionName, ConditionalParamType1, ConditionalParamType2, DefaultImpl) DECLARE_OPTIONALLY_IMPLEMENTED_TEMPLATE_CLASS_FUNCTION_2PARAM`
- L128 _macro_ `#define DECLARE_OPTIONALLY_IMPLEMENTED_TEMPLATE_CLASS_FUNCTION_2PARAMS_CONST( ConditionalReturnType, ConditionalFunctionName, ConditionalParamType1, ConditionalParamType2, DefaultImpl) DECLARE_OPTIONALLY_IMPLEMENTED_TEMPLATE_CLASS_FUNCTION_`
- L130 _macro_ `#define DECLARE_OPTIONALLY_IMPLEMENTED_TEMPLATE_CLASS_FUNCTION_CUSTOM( ConditionalFunctionName, QueryReturnType, QueryFunctionName, QueryParam, QueryDefaultImpl, QueryImpl) \`
- L154 _enumerator_ `enum { RequireRangeCheck = DoRangeCheck };` (scope `FRangeChecklessAllocator::__anon424eced90103`) — Set to false if you don't want to lose performance on range checks in performance-critical pathfinding code.

### `Source/Runtime/AIModule/Public/HierarchicalHashGrid2D.h` (Public)


#### class `THierarchicalHashGrid2D`  
`template <int32 InNumLevels = 3, int32 InLevelRatio = 4, typename InItemIDType = uint32> class THierarchicalHashGrid2D`  
_L35-636_
- desc: LWC_TODO_AI Note we are using int32 here for X and Y which does mean that we could overflow the limit of an int for LWCoords unless fairly large grid cell sizes are used.As WORLD_MAX is currently in flux until we have a better idea of what we are going to be able to support its probably not worth investing time in this potential issue right now.
- L39 _public typedef_ `typedef InItemIDType ItemIDType;`
- L40 _public member_ `static const int32 NumLevels = InNumLevels;`
- L41 _public member_ `static const int32 LevelRatio = InLevelRatio;` — static const int32 NumLevels = InNumLevels;		  Number of grid levels in the grid.
- L56 _public function_ `friend uint32 GetTypeHash(const FCell& Cell)` — Returns hash based on cell location. The hash function is called a lot, favor speed over quality.
- L125 _public function_ `THierarchicalHashGrid2D(const float InCellSize = 500.f) : SpillList(INDEX_NONE)` — Constructor, initializes the grid for specific cell size. @param InCellSize - new finest level cell size of the grid
- L147 _public function_ `void Initialize(const float InCellSize)` — Resets and initializes the grid for specific cell size. @param InCellSize - new finest level cell size of the grid
- L163 _public function_ `void Reset()` — Reset the grid to empty.
- L180 _public function_ `FCellLocation Add(const ItemIDType ID, const FBox& Bounds)` — Adds item to the grid. @param ID - External ID used to identify the item. @param Bounds - Bounding box of the item. @return Cell location of the item, can be used later to remove the item.
- L192 _public function_ `void Add(const ItemIDType ID, const FCellLocation& Location)` — Adds item to the grid. @param ID - External ID used to identify the item. @param Location - Cell location where the item should be added. @return Cell location of the item, can be used later to remove the item.
- L231 _public function_ `void Remove(const ItemIDType ID, const FBox& OldBounds)` — Removes item based on the bounding box it was added with. @param ID - External ID used to identify the item. @param OldBounds - The same bounding box the item was previously added or moved with.
- L241 _public function_ `void Remove(const ItemIDType ID, const FCellLocation& OldLocation)` — Removes item based on the cell location it was added with. @param ID - External ID used to identify the item. @param OldLocation - The same cell location the item was previously added or moved with.
- L313 _public function_ `FCellLocation Move(const ItemIDType ID, const FBox& OldBounds, const FBox& NewBounds)` — Moves item based on previous bounding box and new bounding box. @param ID - External ID used to identify the item. @param OldBounds - The same bounding box the item was previously added or moved with. @param NewBounds - New bounds of the item @return The cell location where the item was added to.
- L325 _public function_ `FCellLocation Move(const ItemIDType ID, const FCellLocation& OldLocation, const FBox& NewBounds)` — Moves item based on previous cell location and new bounding box. @param ID - External ID used to identify the item. @param OldLocation - The same cell location the item was previously added or moved with. @param NewBounds - New bounds of the item @return The cell location where the item was added to.
- L342 _public function_ `template <typename OutT> void QuerySmall(const FBox& Bounds, OutT& OutResults) const` — Returns items that potentially touch the bounds. Operates on grid level, can have false positives. This can be faster than Query() for small query box sizes (i.e. max dimension CellSize*4) due to simpler logic. @param Bounds - Query bounding box. @param OutResults - Result of the query, IDs of potentially overlapping items.
- L384 _public function_ `template <typename OutT> void Query(const FBox& Bounds, OutT& OutResults) const` — Returns items that potentially touch the bounds. Operates on grid level, can have false positives. @param Bounds - Query bounding box. @param OutResults - Result of the query, IDs of potentially overlapping items.
- L476 _public function_ `FCellRect CalcQueryBounds(const FBox& Bounds, const int32 Level) const` — Calculates cell based query rectangle. The bounds are expanded by half grid cell size because the items are stored for only one cell based on their center and side. For that reason the items can overlap the neighbor cells by half the cell size. @param Bounds - Query bounding box to quantize. @param Level - Which level of the tree the to calculate the bounds for @return Quantized rectangle representing the cell bounds at specific level of the tree, coordinates inclusive.
- L491 _public function_ `FCellRect IntersectRect(const FCellRect& Left, const FCellRect& Right) const` — Returns intersection of the two cell bounding rectangles. @param Left - left hand side rectangle @param Right - right hand side rectangle @return Intersecting are between left and right.
- L505 _public function_ `static int32 LevelDown(int32 X)` — Levels down a coordinate using floor rounding. @param X - Coordinate to level down @return Coordinate at coarser level.
- L515 _public function_ `FCellLocation CalcCellLocation(const FBox& Bounds) const` — Finds grid level where the bounds fit inside a cell. @param Bounds - Bounding box of the item. @return Returns cell location of the item, or location at Level == INDEX_NONE if the item cannot fit in the grid.
- L548 _public function_ `FBox CalcCellBounds(const FCellLocation& CellLocation) const` — Finds the world box from a cell. @params CellLocation - Cell location. @return Returns the bounds of the cell.
- L562 _public function_ `FCell& FindOrAddCell(const int X, const int Y, const int Level)` — Returns a cell for specific location and level, creates new cell if it does not exist. @param X - Cell X coordinate. @param Y - Cell Y coordinate. @param Level - Grid Level. @return Reference to cell at specified location.
- L581 _public function_ `FCell* FindCellMutable(const int X, const int Y, const int Level)` — Returns a cell for specific location and level. @param X - Cell X coordinate. @param Y - Cell Y coordinate. @param Level - Grid Level. @return Pointer to cell at specified location, or return nullptr if the cell does not exist.
- L594 _public function_ `const FCell* FindCell(const int X, const int Y, const int Level) const` — Returns a cell for specific location and level. @param X - Cell X coordinate. @param Y - Cell Y coordinate. @param Level - Grid Level. @return Pointer to cell at specified location, or return nullptr if the cell does not exist.
- L602 _public function_ `float GetCellSize(const int32 Level) const` — @return Cell size at specific grid level.
- L605 _public function_ `float GetInvCellSize(const int32 Level) const` — @return 1/cellSize at specific grid level.
- L608 _public function_ `int32 GetLevelItemCount(const int32 Level) const` — @return Array containing all the items.
- L611 _public function_ `const TSet<FCell>& GetCells() const` — @return Set containing all the cells.
- L614 _public function_ `const TSparseArray<FItem>& GetItems() const` — @return Sparse array containing all the items.
- L617 _public function_ `int32 GetFirstSpillListItem() const` — @return Index in items of the first item on the spill list.
- L622 _protected function_ `static constexpr int32 ClampInt32(const int64 Value)` — @return given int64 clamped in int32 range.
- L630 _protected member_ `TStaticArray<float, NumLevels> CellSize;`
- L631 _protected member_ `TStaticArray<float, NumLevels> InvCellSize;` — TStaticArray<float, NumLevels> CellSize;		  Lowest level cell size
- L632 _protected member_ `TStaticArray<int32, NumLevels> LevelItemCount;` — TStaticArray<float, NumLevels> InvCellSize;		  1 / CellSize
- L633 _protected member_ `TSet<FCell> Cells;` — TStaticArray<int32, NumLevels> LevelItemCount;	  Number items per level, can be used to skip certain levels.
- L634 _protected member_ `TSparseArray<FItem> Items;` — TSet<FCell> Cells;								  TSet uses hash buckets to locate items.
- L635 _protected member_ `int32 SpillList = INDEX_NONE;` — TSparseArray<FItem> Items;						  TSparseArray uses freelist to recycled used items.

#### struct `THierarchicalHashGrid2D::FCell`  
`struct FCell`  
_L46-69_
- desc: Cells are located based on their hash. Each cell stores linked list of items at that location and how many children are under the same location in the finer grid levels.
- L48 _public function_ `FCell() : X(0), Y(0), Level(0)`
- L49 _public function_ `FCell(const int32 InX, const int32 InY, const int32 InLevel) : X(InX), Y(InY), Level(InLevel)`
- L51 _public member_ `int32 X, Y, Level;`
- L51 _public member_ `int32 X, Y, Level;`
- L51 _public member_ `int32 X, Y, Level;`
- L52 _public member_ `int32 First = INDEX_NONE;` — int32 X, Y, Level;			  Location of the cell
- L53 _public member_ `int32 ChildItemCount = 0;` — int32 First = INDEX_NONE;	  First item in the item linked list. (index to Items array, or INDEX_NONE)
- L65 _public function_ `bool operator==(const FCell& RHS) const` — Need for TSet<>

#### struct `THierarchicalHashGrid2D::FCellLocation`  
`struct FCellLocation`  
_L72-90_
- desc: Specifies cell location within the grid at specific level.
- L74 _public prototype_ `FCellLocation() = default;`
- L75 _public function_ `FCellLocation(const int32 InX, const int32 InY, const int32 InLevel) : X(InX), Y(InY), Level(InLevel)`
- L77 _public function_ `bool operator==(const FCellLocation& RHS) const`
- L82 _public function_ `bool operator!=(const FCellLocation& RHS) const`
- L87 _public member_ `int32 X = 0;`
- L88 _public member_ `int32 Y = 0;`
- L89 _public member_ `int32 Level = INDEX_NONE;`

#### struct `THierarchicalHashGrid2D::FItem`  
`struct FItem`  
_L93-97_
- desc: Item stored in a grid cell.
- L95 _public member_ `ItemIDType ID = 0;`
- L96 _public member_ `int32 Next = INDEX_NONE;` — ItemIDType ID = 0;			  External item ID

#### struct `THierarchicalHashGrid2D::FCellRect`  
`struct FCellRect`  
_L100-109_
- desc: Rectangle bounds, coordinates inclusive.
- L102 _public prototype_ `FCellRect() = default;`
- L103 _public function_ `FCellRect(const int32 InMinX, const int32 InMinY, const int32 InMaxX, const int32 InMaxY) : MinX(InMinX), MinY(InMinY), MaxX(InMaxX), MaxY(InMaxY)`
- L105 _public member_ `int32 MinX = 0;`
- L106 _public member_ `int32 MinY = 0;`
- L107 _public member_ `int32 MaxX = 0;`
- L108 _public member_ `int32 MaxY = 0;`

#### struct `THierarchicalHashGrid2D::FCellRectIterator`  
`struct FCellRectIterator`  
_L112-119_
- desc: Iterator state over a rectangle
- L115 _public member_ `int64 X = 0;` — Use int64 to prevent overflow when FCellRect::MaxX or FCellRect::MaxY are equal to the maximum value of int32.
- L116 _public member_ `int64 Y = 0;` — int64 X = 0;		  Current X
- L117 _public member_ `int32 Level = 0;` — int64 Y = 0;		  Current Y
- L118 _public member_ `FCellRect Rect;` — int32 Level = 0;	  Current level

### `Source/Runtime/AIModule/Public/IndexedHandle.h` (Public)


#### struct `FSimpleIndexedHandleBase`  
`struct FSimpleIndexedHandleBase`  
_L22-72_
- reflection: `USTRUCT()`
- desc: Index based handle that doesn't use a serial number. For fast access in to index based data structures when we don't expect handles to be able to be stale
- L26 _public prototype_ `FSimpleIndexedHandleBase() = default;`
- L29 _public function_ `FSimpleIndexedHandleBase(int32 InIndex) : Index(InIndex)` — @param InIndex - passing INDEX_NONE will make this handle Invalid
- L33 _public function_ `bool operator==(const FSimpleIndexedHandleBase& Other) const`
- L38 _public function_ `bool operator!=(const FSimpleIndexedHandleBase& Other) const`
- L44 _public function_ `int32 GetIndex() const` — @return INDEX_NONE if invalid or >=0 for a potentially valid handle
- L47 _public function_ `bool IsValid() const` — @return true if this handle is valid, this doesn't check that it's in the correct range for the underlying resource it's providing a handle for
- L54 _public function_ `operator bool() const` — boolean operator useful when embedding declaration in if statement @return same as IsValid() @see IsValid
- L57 _public function_ `void Invalidate()` — Makes the handle Invalid
- L60 _public function_ `void SetIndex(int32 InIndex)` — @param InIndex - passing INDEX_NONE will make this handle Invalid
- L71 _protected member_ `int32 Index = INDEX_NONE;`

#### struct `FIndexedHandleBase`  
`struct FIndexedHandleBase : public FSimpleIndexedHandleBase`  
_L76-112_
- reflection: `USTRUCT()`
- inherits: `FSimpleIndexedHandleBase`
- desc: Index based handle that has a serial number to verify stale handles. For fast safe access in to index based data structures
- L80 _public prototype_ `FIndexedHandleBase() = default;`
- L83 _public function_ `FIndexedHandleBase(int32 InIndex, uint32 InSerialNumber) : FSimpleIndexedHandleBase(InIndex), SerialNumber(InSerialNumber)` — @note passing INDEX_NONE as index will make this handle Invalid
- L87 _public function_ `bool operator==(const FIndexedHandleBase& Other) const`
- L92 _public function_ `bool operator!=(const FIndexedHandleBase& Other) const`
- L97 _public function_ `uint32 GetSerialNumber() const`
- L98 _public function_ `void SetSerialNumber(uint32 InSerialNumber)`
- L106 _protected member_ `uint32 SerialNumber = 0;`
- L110 _public member_ `uint32 ManagerID = 0;`

#### struct `FCompactIndexedHandleBase`  
`struct FCompactIndexedHandleBase`  
_L116-180_
- reflection: `USTRUCT()`
- desc: Compact Index based handle that has a serial number to verify stale handles. For fast safe access in to index based data structures.
- L120 _public prototype_ `FCompactIndexedHandleBase() = default;`
- L123 _public function_ `FCompactIndexedHandleBase(const int32 InIndex, const uint32 InSerialNumber)` — @note passing INDEX_NONE as index will make this handle Invalid
- L132 _public function_ `bool operator==(const FCompactIndexedHandleBase& Other) const`
- L137 _public function_ `bool operator!=(const FCompactIndexedHandleBase& Other) const`
- L143 _public function_ `int16 GetIndex() const` — @return INDEX_NONE if invalid or >=0 for a potentially valid handle
- L146 _public function_ `bool IsValid() const` — @return true if this handle is valid, this doesn't check that it's in the correct range for the underlying resource it's providing a handle for
- L153 _public function_ `operator bool() const` — boolean operator useful when embedding declaration in if statement @return same as IsValid() @see IsValid
- L156 _public function_ `void Invalidate()` — Makes the handle Invalid
- L159 _public function_ `void SetIndex(int16 InIndex)` — @param InIndex - passing INDEX_NONE will make this handle Invalid
- L164 _public function_ `uint16 GetSerialNumber() const`
- L165 _public function_ `void SetSerialNumber(int16 InSerialNumber)`
- L173 _protected member_ `int16 Index = INDEX_NONE;`
- L174 _protected member_ `uint16 SerialNumber = 0;`
- L178 _public member_ `uint32 ManagerID = 0;`

#### struct `FIndexedHandleManagerBase`  
`template<typename TIndexedHandle, typename TIndexType, typename TSerialType, bool bOptimizeHandleReuse = false> struct FIndexedHandleManagerBase`  
_L188-321_
- desc: Handle Manager meant for FIndexedHandleBase and FCompactIndexedHandleBase derived classes, handles are given out from a freelist and are zero based and consecutive in nature, so ideal for being used as indices in to arrays. Using bOptimizeHandleReuse performance impact on releasing a handle. Because new handles will always use the smallest index, this will help greatly the compaction code(ShrinkHandles) and reduce the total number of handles. This is very useful when you need to iterate through every valid handles often.
- L191 _protected typedef_ `typedef TArray<TIndexedHandle> FHandleArray;`
- L194 _public function_ `FIndexedHandleManagerBase()`
- L201 _public function_ `TIndexedHandle GetNextHandle()`
- L227 _public function_ `bool RemoveHandle(TIndexedHandle IndexedHandle)`
- L253 _public function_ `bool IsValidHandle(TIndexedHandle IndexedHandle) const`
- L267 _public function_ `const TArray<TIndexedHandle>& GetHandles() const`
- L270 _public function_ `int32 CalcNumUsedHandles() const` — returns the number of used handles, will be greater than or equal to zero
- L273 _public prototype_ `FIndexedHandleManagerBase(const FIndexedHandleManagerBase& Other) = default;` — Defaulted copy constructor, but it acts differently from the copy assignment operator - notably, doesn't allocate a new ManagerID.
- L275 _public function_ `FIndexedHandleManagerBase& operator=(const FIndexedHandleManagerBase& Other)`
- L291 _public function_ `int32 ShrinkHandles()` — Attempts to shrink the Handles array if there are contiguous free slots at the end of the Array @return the new Num items in the handles array
- L302 _public function_ `void Reset()`
- L311 _protected member_ `FHandleArray Handles;` — Handles stored as a free list sparse array, Handle entries that are free will have a GetIndex() == INDEX_NONE
- L312 _protected member_ `TArray<TIndexType> FreeHandleIndices;`
- L314 _protected member_ `static std::atomic<TSerialType> SerialNumberCounter;`
- L318 _protected member_ `static std::atomic<uint32> ManagerIDCounter;` — ID used in non shipping / test builds to ensure the same manager that is used to create handles is also used to remove them
- L319 _protected member_ `uint32 ManagerID = 0;`

#### struct `FIndexedHandleManager`  
`template<typename TIndexedHandle, bool bOptimizeHandleReuse = false> struct FIndexedHandleManager : public FIndexedHandleManagerBase<TIndexedHandle, int32, uint32, bOptimizeHandleReuse>`  
_L332-334_
- inherits: `FIndexedHandleManagerBase<TIndexedHandle,int32,uint32,bOptimizeHandleReuse>`

#### struct `FCompactIndexedHandleManager`  
`template<typename TIndexedHandle, bool bOptimizeHandleReuse = false> struct FCompactIndexedHandleManager : public FIndexedHandleManagerBase<TIndexedHandle, int16, uint16, bOptimizeHandleReuse>`  
_L337-339_
- inherits: `FIndexedHandleManagerBase<TIndexedHandle,int16,uint16,bOptimizeHandleReuse>`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_DO_INDEXED_HANDLE_MANAGER_ID 1`
- L13 _macro_ `#define UE_DO_INDEXED_HANDLE_MANAGER_ID 0`
- L65 _function_ `friend uint32 GetTypeHash(const FSimpleIndexedHandleBase& Handle)`
- L100 _function_ `friend uint32 GetTypeHash(const FIndexedHandleBase& Handle)`
- L167 _function_ `friend uint32 GetTypeHash(const FCompactIndexedHandleBase& Handle)`
- L236 _function_ `const int32 InsertPosition = Algo::LowerBound(FreeHandleIndices, Idx, [](const TIndexType& Lhs, const TIndexType& Rhs) {return Lhs > Rhs;});` (scope `FIndexedHandleManagerBase::RemoveHandle`)
- L324 _member_ `template<typename TIndexedHandle, typename TIndexType, typename TSerialType, bool bOptimizeHandleReuse> std::atomic<TSerialType> FIndexedHandleManagerBase<TIndexedHandle, TIndexType, TSerialType, bOptimizeHandleReuse>::SerialNumberCounter = { 0 };` (scope `FIndexedHandleManagerBase<TIndexedHandle, TIndexType, TSerialType, bOptimizeHandleReuse>`)
- L328 _member_ `template<typename TIndexedHandle, typename TIndexType, typename TSerialType, bool bOptimizeHandleReuse> std::atomic<uint32> FIndexedHandleManagerBase<TIndexedHandle, TIndexType, TSerialType, bOptimizeHandleReuse>::ManagerIDCounter = { 0 };` (scope `FIndexedHandleManagerBase<TIndexedHandle, TIndexType, TSerialType, bOptimizeHandleReuse>`)

### `Source/Runtime/AIModule/Public/SequentialID.h` (Public)


#### struct `FSequentialIDBase`  
`struct FSequentialIDBase`  
_L8-35_
- reflection: `USTRUCT()`
- L12 _public prototype_ `FSequentialIDBase() = default;`
- L14 _public function_ `explicit FSequentialIDBase(uint32 InID) : Value(InID)`
- L16 _public function_ `bool operator==(const FSequentialIDBase& Other) const`
- L17 _public function_ `bool operator!=(const FSequentialIDBase& Other) const`
- L19 _public function_ `bool IsValid() const`
- L20 _public function_ `bool IsInvalid() const`
- L22 _public function_ `void Invalidate()`
- L24 _public function_ `uint32 GetValue() const`
- L26 _public function_ `FString Describe() const`
- L31 _protected member_ `static constexpr uint32 InvalidID = 0;`
- L34 _protected member_ `uint32 Value = InvalidID;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L28 _function_ `friend uint32 GetTypeHash(const FSequentialIDBase& SequentialID)`

### `Source/Runtime/AIModule/Public/SimpleCellGrid.h` (Public)


#### struct `FGridSize2D`  
`struct FGridSize2D`  
_L9-23_
- L11 _public member_ `uint32 Width;`
- L12 _public member_ `uint32 Height;`
- L14 _public function_ `explicit FGridSize2D(uint32 InWidth = 0, uint32 InHeight = 0) : Width(InWidth), Height(InHeight)`
- L19 _public function_ `bool operator==(const FGridSize2D& Other) const`

#### struct `TSimpleCellGrid`  
`template<typename CellType, int InvalidCellValue = 0> struct TSimpleCellGrid`  
_L27-387_
- desc: No virtuals on purpose
- L29 _public typedef_ `typedef CellType FCellType;`
- L31 _public member_ `float GridCellSize;`
- L32 _public member_ `FBox WorldBounds;`
- L33 _public member_ `FVector Origin;`
- L34 _public member_ `FVector BoundsSize;`
- L35 _public member_ `FGridSize2D GridSize;`
- L38 _protected member_ `TArray<FCellType> Cells;`
- L41 _public function_ `TSimpleCellGrid() : GridCellSize(0.0f) , WorldBounds(ForceInitToZero) , Origin(FLT_MAX) , BoundsSize(0)`
- L54 _public function_ `bool Init(const float InCellSize, const FBox& Bounds)` — Initialize the grid from a bounding box @param InCellSize Size of a cell @param Bounds Bounding box the grid needs to encapsulate @return True if the grid was initialized properly
- L84 _public function_ `bool Init(const float InCellSize, const FGridSize2D& InGridSize, const FVector& InOrigin, const float VerticalBoundSize)` — Initialize the grid @param InCellSize Size of a cell @param InGridSize Amount of cells needed in each direction @param InOrigin World location of the grid @param VerticalBoundSize Size of the grid above and under the Origin @return True if the grid was initialized properly
- L106 _public function_ `void SetVerticalInterval(const FFloatInterval& VerticalInterval)` — Change the vertical position of the grid by providing an interval
- L116 _public function_ `void UpdateWorldBounds()`
- L121 _public function_ `inline bool IsValid() const`
- L126 _public function_ `inline bool IsValidIndex(const int32 CellIndex) const`
- L131 _public function_ `inline bool IsValidCoord(int32 LocationX, int32 LocationY) const`
- L136 _public function_ `inline bool IsValidCoord(const FIntVector& CellCoords) const`
- L141 _public function_ `inline uint32 GetAllocatedSize() const`
- L147 _public function_ `inline FIntVector GetCellCoordsUnsafe(const FVector& WorldLocation) const` — Convert world location to (X,Y) coords on grid, result can be outside grid
- L156 _public function_ `FIntVector GetCellCoords(const FVector& WorldLocation) const` — Convert world location to (X,Y) coords on grid, result is clamped to grid
- L163 _public function_ `inline int32 GetCellCoordX(int32 CellIndex) const` — Convert cell index to coord X on grid, result can be invalid
- L169 _public function_ `inline int32 GetCellCoordY(int32 CellIndex) const` — Convert cell index to coord Y on grid, result can be invalid
- L175 _public function_ `inline FIntVector GetCellCoords(int32 CellIndex) const` — Convert cell index to (X,Y) coords on grid
- L181 _public function_ `int32 GetCellIndexUnsafe(const FVector& WorldLocation) const` — Convert world location to cell index, result can be invalid
- L188 _public function_ `inline int32 GetCellIndexUnsafe(const FIntVector& CellCoords) const` — Convert (X,Y) coords on grid to cell index, result can be invalid
- L194 _public function_ `inline int32 GetCellIndexUnsafe(int32 LocationX, int32 LocationY) const` — Convert (X,Y) coords on grid to cell index, result can be invalid
- L200 _public function_ `inline int32 GetCellIndex(int32 LocationX, int32 LocationY) const` — Convert (X,Y) coords on grid to cell index, returns -1 for position outside grid
- L206 _public function_ `int32 GetCellIndex(const FVector& WorldLocation) const` — Convert world location to cell index, returns -1 for position outside grid
- L213 _public function_ `inline FBox GetWorldCellBox(int32 CellIndex) const` — Return the bounding box of a cell.
- L219 _public function_ `inline FBox GetWorldCellBox(int32 LocationX, int32 LocationY) const` — Return the bounding box of a cell.
- L228 _public function_ `inline FBox2D GetWorldCellBox2D(int32 CellIndex) const` — Return the 2D bounding box of a cell.
- L234 _public function_ `inline FBox2D GetWorldCellBox2D(int32 LocationX, int32 LocationY) const` — Return the 2D bounding box of a cell.
- L243 _public function_ `inline FBox GetWorldCellRectangleBox(const FIntRect& CellRect) const` — Return the world bounding box of all cells included in the given rectangle.
- L252 _public function_ `inline FIntRect GetCellRectangleFromBox(const FBox& WorldBox) const` — Compute a rectangle of cells overlapping the given WorldBox.
- L265 _public function_ `inline FIntRect GetGridRectangle() const` — Return an IntRect that includes all the cells of the grid. Max is inclusive.
- L270 _public function_ `inline FVector GetWorldCellCenter(int32 CellIndex) const`
- L275 _public function_ `inline FVector GetWorldCellCenter(int32 LocationX, int32 LocationY) const`
- L280 _public function_ `const FCellType& GetCellAtWorldLocationUnsafe(const FVector& WorldLocation) const`
- L286 _public function_ `const FCellType& GetCellAtWorldLocation(const FVector& WorldLocation) const`
- L293 _public function_ `inline FCellType& operator[](int32 CellIndex)`
- L294 _public function_ `inline const FCellType& operator[](int32 CellIndex) const`
- L296 _public function_ `inline FCellType& GetCellAtIndexUnsafe(int32 CellIndex)`
- L297 _public function_ `inline const FCellType& GetCellAtIndexUnsafe(int32 CellIndex) const`
- L299 _public function_ `FCellType& GetCellAtCoordsUnsafe(int32 LocationX, int32 LocationY)`
- L300 _public function_ `const FCellType& GetCellAtCoordsUnsafe(int32 LocationX, int32 LocationY) const`
- L302 _public function_ `inline int32 GetCellsCount() const`
- L307 _public function_ `inline int32 Num() const`
- L312 _public function_ `void Serialize(FArchive& Ar)`
- L365 _public function_ `void AllocateMemory()`
- L370 _public function_ `void FreeMemory()`
- L375 _public function_ `void Zero()`
- L381 _public function_ `void CleanUp()`
