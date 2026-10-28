# Plugins / TargetingSystem

- module root: `Plugins/Experimental/GameplayTargetingSystem/Source/GameplayTargetingSystem`
- headers: 20; symbols: 377
- symbol kinds: class=16, delegate=7, enum=4, enumerator=16, externvar=7, function=47, macro=13, member=90, namespace=2, prototype=162, struct=13
- PrivateDependencyModuleNames: DeveloperSettings
- PublicDependencyModuleNames: Core, CoreUObject, Engine, GameplayAbilities, GameplayTags, GameplayTasks

### `Plugins/Experimental/GameplayTargetingSystem/Source/GameplayTargetingSystem/Public/AbilityTasks/AbilityTask_PerformTargeting.h` (Public)


#### class `UAbilityTask_PerformTargeting`  
`class UAbilityTask_PerformTargeting : public UAbilityTask`  
_L18-50_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAbilityTask`
- L25 _public member_ `FTargetReadyDelegate OnTargetReady;` — `UPROPERTY(BlueprintAssignable)` — Called when the targeting request has been completed and results are ready
- L27 _public prototype_ `virtual void Activate() override;`
- L31 _public prototype_ `static UAbilityTask_PerformTargeting* PerformTargetingRequest(UGameplayAbility* OwningAbility, UTargetingPreset* InTargetingPreset, bool bAllowAsync);` — `UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))` — Performs a targeting request based on a Targeting Preset from a GameplayAbility
- L35 _public prototype_ `static UAbilityTask_PerformTargeting* PerformFilteringRequest(UGameplayAbility* OwningAbility, UTargetingPreset* TargetingPreset, const TArray<AActor*> InTargets, bool bAllowAsync);` — `UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))` — Performs a target filtering request based on a Targeting Preset from a GameplayAbility
- L39 _private prototype_ `void SetupInitialTargetsForRequest(FTargetingRequestHandle RequestHandle) const;` — Helper function to push the InitialTargets array to the DataStore for Filtering requests
- L43 _protected member_ `TObjectPtr<UTargetingPreset> TargetingPreset;` — Targeting Preset to request
- L46 _protected member_ `TArray<AActor*> InitialTargets;` — Initial Targets to pass into the request (only populated for Filtering Requests)
- L49 _protected member_ `bool bPerformAsync;` — Whether to perform this request immediately or async

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TARGETINGSYSTEM_API`
- L15 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTargetReadyDelegate, FTargetingRequestHandle, TargetingRequestHandle);`
- L15 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTargetReadyDelegate, FTargetingRequestHandle, TargetingRequestHandle);`

### `Plugins/Experimental/GameplayTargetingSystem/Source/GameplayTargetingSystem/Public/Async/AsyncAction_PerformTargeting.h` (Public)


#### class `UAsyncAction_PerformTargeting`  
`class UAsyncAction_PerformTargeting : public UBlueprintAsyncActionBase`  
_L22-66_
- reflection: `UCLASS(BlueprintType, meta = (ExposedAsyncProxy = "AsyncTaskRef"))`
- inherits: `UBlueprintAsyncActionBase`
- desc: @class UAsyncAction_PerformTargeting
- L28 _public prototype_ `static UAsyncAction_PerformTargeting* PerformTargetingRequest(AActor* SourceActor, UTargetingPreset* TargetingPreset, bool bUseAsyncTargeting);` — `UFUNCTION(BlueprintCallable, meta = (DefaultToSelf = "SourceActor", BlueprintInternalUseOnly = "true", DisplayName = "Perform Targeting Async Action"))`
- L31 _public prototype_ `static UAsyncAction_PerformTargeting* PerformFilteringRequest(AActor* SourceActor, UTargetingPreset* TargetingPreset, bool bUseAsyncTargeting, const TArray<AActor*> InTargets);` — `UFUNCTION(BlueprintCallable, meta = (DefaultToSelf = "SourceActor", BlueprintInternalUseOnly = "true", DisplayName = "Perform Filtering Async Action"))`
- L34 _public function_ `FTargetingRequestHandle GetTargetingHandle() const` — `UFUNCTION(BlueprintPure, Category = "Targeting")`
- L36 _public prototype_ `virtual void Activate() override;`
- L40 _public member_ `FPerformTargetingReady Targeted;` — `UPROPERTY(BlueprintAssignable)`
- L44 _private prototype_ `void SetupInitialTargetsForRequest() const;` — Method to seed the targeting request w/ the initial set of targets
- L49 _private member_ `TObjectPtr<UTargetingPreset> TargetingPreset = nullptr;` — `UPROPERTY()` — The targeting preset to use for targeting
- L53 _private member_ `TWeakObjectPtr<AActor> WeakSourceActor;` — `UPROPERTY()` — The actor this task is running for
- L57 _private member_ `TArray<TObjectPtr<AActor>> InitialTargets;` — `UPROPERTY()` — A set of targets to pre-seed the targeting request with (great for filtering targets without the needs for selection)
- L61 _private member_ `FTargetingRequestHandle TargetingHandle;` — `UPROPERTY()` — Targeting Handle created for this Async targeting task
- L65 _private member_ `uint8 bUseAsyncTargeting : 1;` — `UPROPERTY()` — Flag to indicate we should be using async targeting (default is immediate execution)

#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPerformTargetingReady, FTargetingRequestHandle, TargetingHandle);`
- L15 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPerformTargetingReady, FTargetingRequestHandle, TargetingHandle);`

### `Plugins/Experimental/GameplayTargetingSystem/Source/GameplayTargetingSystem/Public/TargetingSystem/TargetingPreset.h` (Public)


#### class `UTargetingPreset`  
`class UTargetingPreset : public UDataAsset`  
_L27-41_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UDataAsset`
- desc: @class UTargetingPreset This object is used when a data asset is preferred for task setup. Tasks will be processed in the order they are setup in the task set. It is recommended that selection tasks happen first before any filtering and sorting.
- L32 _public prototype_ `UTargetingPreset(const FObjectInitializer& ObjectInitializer);`
- L35 _public function_ `inline const FTargetingTaskSet* GetTargetingTaskSet() const` — Get the set of tasks defined for this targeting preset
- L36 _public function_ `inline FTargetingTaskSet& GetMutableTargetingTaskSet()`
- L40 _public member_ `FTargetingTaskSet TargetingTaskSet;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting", meta = (ShowOnlyInnerProperties))` — The tasks that make up this targeting preset

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TARGETINGSYSTEM_API`

### `Plugins/Experimental/GameplayTargetingSystem/Source/GameplayTargetingSystem/Public/TargetingSystem/TargetingSubsystem.h` (Public)


#### struct `FTargetingDebugInfo`  
`struct FTargetingDebugInfo`  
_L28-46_
- desc: @struct FTargetingDebugInfo
- L30 _public function_ `FTargetingDebugInfo()`
- L35 _public member_ `class UCanvas* Canvas;`
- L37 _public member_ `bool bPrintToLog;`
- L39 _public member_ `float XPos;`
- L40 _public member_ `float YPos;`
- L41 _public member_ `float OriginalX;`
- L42 _public member_ `float OriginalY;`
- L43 _public member_ `float MaxY;`
- L44 _public member_ `float NewColumnYPadding;`
- L45 _public member_ `float YL;`

#### class `UTargetingSubsystem`  
`class UTargetingSubsystem : public UGameInstanceSubsystem, public FTickableGameObject, public FSelfRegisteringExec`  
_L79-237_
- reflection: `UCLASS(MinimalAPI, DisplayName = "Targeting Subsystem")`
- inherits: `UGameInstanceSubsystem,FTickableGameObject,FSelfRegisteringExec`
- desc: @class UTargetingSubsystem The Targeting Subsystem is the entry point for users to initiate targeting requests. The entry point to the system is the target request handle. The handle is used to interface with the targeting data stores. Data stores are templated classes around generic data structs that the system and tasks use to accomplish a targeting request. The targeting system has 3 mandatory data stores and 1 required for async targeting request. These data stores are required to be set up before the system can properly run a targeting request. The mandatory 3 data stores are FTargetingRequestData, FTargetingTaskSet, and FTargetingSourceContext. FTargetingAsyncTaskData is implicitly setup when an async targeting request is initiated. Users can do all the pieces manually in C++ by setting up the required data stores themselves, or, to have it a bit more automated, the user can use the APIs that utilize UTargetingPreset data asset. For immediate targeting requests users will call the Execute methods. These functions perform all the tasks till completion. The system will not go latent. For async targeting requests users will call the Start Async methods. The system will queue up a targeting request and as each task is processed the system can run through all the tasks to completion or stop processing until the next frame while it waits for a task to complete. Note about Targeting Handles, when a targeting handle is created it will not implicitly release the handle. It is up
- L85 _public prototype_ `static UTargetingSubsystem* Get(const UWorld* World);` — Method to get the mesh network events subsystem
- L86 _public prototype_ `static UTargetingSubsystem* GetTargetingSubsystem(const UObject* WorldContextObject);`
- L89 _public prototype_ `static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);` — Implemented to emit references from the global data stores
- L92 _private prototype_ `UTargetingSubsystem();`
- L95 _private prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L96 _private prototype_ `virtual void Deinitialize() override;`
- L100 _private prototype_ `virtual bool Exec_Runtime(UWorld* Inworld, const TCHAR* Cmd, FOutputDevice& Ar) override;` — FSelfRegisteringExec implementation
- L104 _private prototype_ `virtual void Tick(float DeltaTime) override;` — FTickableGameObject interface
- L105 _private prototype_ `virtual bool IsTickable() const override;`
- L106 _private function_ `virtual ETickableTickType GetTickableTickType() const override`
- L107 _private function_ `virtual TStatId GetStatId() const override`
- L108 _private function_ `virtual UWorld* GetTickableGameObjectWorld() const override`
- L117 _public prototype_ `static FTargetingRequestHandle CreateTargetRequestHandle();` — Method to create a basic target request handle (nothing will be setup for any targeting requests) The request data store, task set data store, and source context data store will have to be setup manually by caller.
- L120 _public prototype_ `static FTargetingRequestHandle MakeTargetRequestHandle(const UTargetingPreset* TargetingPreset, const FTargetingSourceContext& InSourceContext);` — Method to create and setup a target request handle given a targeting preset and source context
- L123 _public prototype_ `static void ReleaseTargetRequestHandle(FTargetingRequestHandle& Handle);` — Method to release a target handle (Note: Unless flagged via AsyncTaskData or ImmediateTaskData this will not release implicitly)
- L129 _public prototype_ `void ExecuteTargetingRequestWithHandle(FTargetingRequestHandle TargetingHandle, FTargetingRequestDelegate CompletionDelegate = FTargetingRequestDelegate(), FTargetingRequestDynamicDelegate CompletionDynamicDelegate = FTargetingRequestDynamicDelegate());` — Method to execute an immediate targeting request with a given targeting handle.
- L133 _public prototype_ `void ExecuteTargetingRequest(const UTargetingPreset* TargetingPreset, const FTargetingSourceContext& InSourceContext, FTargetingRequestDynamicDelegate CompletionDynamicDelegate);` — `UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = "Targeting System | Instant Request")` — Method to execute an immediate targeting request based on a gameplay targeting preset.
- L136 _public prototype_ `void StartAsyncTargetingRequestWithHandle(FTargetingRequestHandle TargetingHandle, FTargetingRequestDelegate CompletionDelegate = FTargetingRequestDelegate(), FTargetingRequestDynamicDelegate CompletionDynamicDelegate = FTargetingRequestDynamicDelegate());` — Method to queue an async targeting request with a given targeting handle.
- L140 _public prototype_ `void RemoveAsyncTargetingRequestWithHandle(UPARAM(ref) FTargetingRequestHandle& TargetingHandle);` — `UFUNCTION(BlueprintCallable, Category = "Targeting System | Async Request")` — Method to remove an async targeting request with a given targeting handle
- L144 _public prototype_ `FTargetingRequestHandle StartAsyncTargetingRequest(const UTargetingPreset* TargetingPreset, const FTargetingSourceContext& InSourceContext, FTargetingRequestDynamicDelegate CompletionDynamicDelegate);` — `UFUNCTION(BlueprintCallable, Category = "Targeting System | Async Request")` — Method to queue an async targeting request based on a gameplay targeting preset.
- L148 _private prototype_ `void ExecuteTargetingRequestWithHandleInternal(FTargetingRequestHandle TargetingHandle, FTargetingRequestDelegate CompletionDelegate, FTargetingRequestDynamicDelegate CompletionDynamicDelegate);` — Internal method to handle running an immediate targeting request
- L151 _private prototype_ `void StartAsyncTargetingRequestWithHandleInternal(FTargetingRequestHandle TargetingHandle, FTargetingRequestDelegate CompletionDelegate, FTargetingRequestDynamicDelegate CompletionDynamicDelegate);` — Internal method to hanlde queuing up an async targeting request
- L154 _private prototype_ `void ProcessTargetingRequestTasks(FTargetingRequestHandle& TargetingHandle, float& TimeLeft);` — Internal method to process the tasks for a given targeting request
- L157 _private prototype_ `UTargetingTask* FindCurrentExecutingTask(FTargetingRequestHandle Handle) const;` — Method to find the currect executing task for the given handle
- L160 _private prototype_ `void OnFinishedTickingAsyncRequests();` — Called when we set bTickingAsyncRequests to false, at this point it's safe to perform any queued operations on the Async Requests Array
- L163 _private prototype_ `void ClearAsyncRequests();` — Internal method to clear all async requests and release all references
- L166 _private prototype_ `void HandlePreLoadMap(const FString& MapName);` — Called when switching maps. Allows to release references that would otherwise prevent cleaning up an old world
- L171 _private member_ `TArray<FTargetingRequestHandle> AsyncTargetingRequests;` — `UPROPERTY(Transient)` — The set of target requests queued up for async processing
- L174 _private member_ `bool bTickingAsycnRequests = false;` — Flag indicating the targeting system is currently in its tick processing targeting tasks for async request
- L177 _private member_ `TSortedMap<FTargetingRequestHandle, FTargetingRequestData> PendingTargetingRequests;` — While we're processing targeting requests, we add any incoming requests to this array to prevent memory stomps
- L180 _private member_ `TSortedMap<FTargetingRequestHandle, FTargetingRequestData> PendingAsyncTargetingRequests;` — (Version for Async Requests) While we're processing targeting requests, we add any incoming requests to this array to prevent memory stomps
- L188 _public prototype_ `FTargetingSourceContext GetTargetingSourceContext(FTargetingRequestHandle TargetingHandle) const;` — `UFUNCTION(BlueprintCallable, Category = "Targeting System | Targeting Types")` — Returns the targeting source context for the targeting request handle
- L192 _public prototype_ `void GetTargetingResultsActors(FTargetingRequestHandle TargetingHandle, TArray<AActor*>& Targets) const;` — `UFUNCTION(BlueprintCallable, Category = "Targeting System | Targeting Results")` — Method to get the actor targets from a given targeting request handle
- L196 _public prototype_ `void GetTargetingResults(FTargetingRequestHandle TargetingHandle, TArray<FHitResult>& OutTargets) const;` — `UFUNCTION(BlueprintCallable, Category = "Targeting System | Targeting Results")` — Helper method to get the set of hit results for a given targeting handle
- L200 _public prototype_ `static void OverrideCollisionQueryTaskData(FTargetingRequestHandle TargetingHandle, const FCollisionQueryTaskData& CollisionQueryDataOverride);` — `UFUNCTION(BlueprintCallable, Category = "Targeting System | Data Stores")` — Function that lets you set a data store from a certain Targeting Handle to add some Collision Query Param Overrides
- L209 _public prototype_ `static bool IsTargetingDebugEnabled();` — Helper method to indicate if the debugging feature is enabled
- L212 _public prototype_ `static float GetOverrideTargetingLifeTime();` — Helper method to overrides the life time of the shapes drawn
- L215 _public prototype_ `static void OnShowDebugInfo(AHUD* HUD, UCanvas* Canvas, const FDebugDisplayInfo& DisplayInfo, float& YL, float& YPos);` — Callback to handle OnShowDebugInfo to check if the TargetingSystem has been enabled
- L218 _public prototype_ `void DebugLine(struct FTargetingDebugInfo& Info, FString Str, float XOffset, float YOffset, int32 MinTextRowsToAdvance = 0);` — Helper methd to write a debug line when the ShowDebug TargetingSystem is active
- L221 _private prototype_ `void DisplayDebug(class UCanvas* Canvas, const class FDebugDisplayInfo& DebugDisplay, float& YL, float& YPos);`
- L222 _private prototype_ `void Debug_Internal(struct FTargetingDebugInfo& Info);`
- L223 _private prototype_ `void DebugForHandle_Internal(FTargetingRequestHandle& Handle, struct FTargetingDebugInfo& Info);`
- L224 _private prototype_ `void AccumulateScreenPos(FTargetingDebugInfo& Info);`
- L226 _private prototype_ `void AddDebugTrackedImmediateTargetRequests(FTargetingRequestHandle TargetingHandle) const;`
- L227 _private prototype_ `void AddDebugTrackedAsyncTargetRequests(FTargetingRequestHandle TargetingHandle) const;`
- L229 _private member_ `mutable TArray<FTargetingRequestHandle> DebugTrackedImmediateTargetRequests;`
- L230 _private member_ `mutable int32 CurrentImmediateRequestIndex = 0;`
- L232 _private member_ `mutable TArray<FTargetingRequestHandle> DebugTrackedAsyncTargetRequests;`
- L233 _private member_ `mutable int32 CurrentAsyncRequestIndex = 0;`

### `Plugins/Experimental/GameplayTargetingSystem/Source/GameplayTargetingSystem/Public/TargetingSystemModule.h` (Public)


#### class `FTargetingSystemModule`  
`class FTargetingSystemModule : public IModuleInterface`  
_L10-16_
- inherits: `IModuleInterface`
- L14 _public prototype_ `virtual void StartupModule() override;`
- L15 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Experimental/GameplayTargetingSystem/Source/GameplayTargetingSystem/Public/Tasks/CollisionQueryTaskData.h` (Public)


#### struct `FCollisionQueryTaskData`  
`struct FCollisionQueryTaskData`  
_L11-23_
- reflection: `USTRUCT(BlueprintType)`
- desc: Data Store struct used to extend collision-based targeting tasks providing extra data from outside
- L15 _public function_ `FCollisionQueryTaskData()`
- L19 _public member_ `TArray<TObjectPtr<AActor>> IgnoredActors;` — `UPROPERTY(BlueprintReadWrite, Category = "Collision Query Task Overrides")` — Any extra actors we want to ignore. Note: Given that this is a globally-managed struct, we're manually adding refs to it in UTargetingSubsystem::AddReferencedObjects
- L22 _public prototype_ `void AddStructReferencedObjects(class FReferenceCollector& Collector);` — Called by the Targeting Subsystem to manually hang onto reference to object pointers in this struct given that it's globally-owned

### `Plugins/Experimental/GameplayTargetingSystem/Source/GameplayTargetingSystem/Public/Tasks/SimpleTargetingFilterTask.h` (Public)


#### class `USimpleTargetingFilterTask`  
`class USimpleTargetingFilterTask : public UTargetingFilterTask_BasicFilterTemplate`  
_L21-34_
- reflection: `UCLASS(MinimalAPI, EditInlineNew, Abstract, Blueprintable)`
- inherits: `UTargetingFilterTask_BasicFilterTemplate`
- desc: @class USimpleTargetingSelectionTask This is a blueprintable TargetingTask class made for filtering out Targets from the results list. Override the ShouldRemoveTarget Blueprint Function to define the rules for this filter.
- L27 _public prototype_ `virtual bool ShouldFilterTarget(const FTargetingRequestHandle& TargetingHandle, const FTargetingDefaultResultData& TargetData) const override;`
- L32 _public prototype_ `bool BP_ShouldFilterTarget(const FTargetingRequestHandle& TargetingHandle, const FTargetingDefaultResultData& TargetData) const;` — `UFUNCTION(BlueprintImplementableEvent, DisplayName=ShouldRemoveTarget)` — Returns true if a Target should be removed from the results of this TargetingRequest

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API TARGETINGSYSTEM_API`

### `Plugins/Experimental/GameplayTargetingSystem/Source/GameplayTargetingSystem/Public/Tasks/SimpleTargetingSelectionTask.h` (Public)


#### class `USimpleTargetingSelectionTask`  
`class USimpleTargetingSelectionTask : public UTargetingTask`  
_L22-52_
- reflection: `UCLASS(MinimalAPI, EditInlineNew, Abstract, Blueprintable)`
- inherits: `UTargetingTask`
- desc: @class USimpleTargetingSelectionTask This is a blueprintable TargetingTask class made for adding new Targets to the results list. Override the SelectTargets function and call AddTargetHitResult or AddTargetActor to select new targets.
- L28 _public prototype_ `virtual void Execute(const FTargetingRequestHandle& TargetingHandle) const override;` — Evaluation function called by derived classes to process the targeting request
- L31 _public prototype_ `void SelectTargets(const FTargetingRequestHandle& TargetingHandle, const FTargetingSourceContext& SourceContext) const;` — `UFUNCTION(BlueprintNativeEvent)`
- L33 _public function_ `virtual void SelectTargets_Implementation(const FTargetingRequestHandle& TargetingHandle, const FTargetingSourceContext& SourceContext) const`
- L43 _protected prototype_ `bool AddTargetActor(const FTargetingRequestHandle& TargetingHandle, AActor* Actor) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure=False, Category=Targeting)` — Adds a single Actor to the Targeting Results for a given TargetingRequestHandle. Returns false when the Actor was already in the list. NOTE: If you have a HitResult associated with this selection, please use AddHitResult instead.
- L50 _protected prototype_ `bool AddHitResult(const FTargetingRequestHandle& TargetingHandle, const FHitResult& HitResult) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure=False, Category=Targeting)` — Adds a HitResult to the Targeting Results for a given TargetingRequestHandle. Returns False when the Actor that was hit was already in the list

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API TARGETINGSYSTEM_API`

### `Plugins/Experimental/GameplayTargetingSystem/Source/GameplayTargetingSystem/Public/Tasks/SimpleTargetingSortTask.h` (Public)


#### class `USimpleTargetingSortTask`  
`class USimpleTargetingSortTask : public UTargetingSortTask_Base`  
_L21-33_
- reflection: `UCLASS(MinimalAPI, EditInlineNew, Abstract, Blueprintable)`
- inherits: `UTargetingSortTask_Base`
- desc: @class USimpleTargetingSortTask This is a blueprintable TargetingTask class made for reordering Targets in the results list. Override the GetScoreForTarget Blueprint Function to provide a score for each element and then Targets will be sorted by score.
- L27 _protected prototype_ `virtual float GetScoreForTarget(const FTargetingRequestHandle& TargetingHandle, const FTargetingDefaultResultData& TargetData) const override;` — Called on every target to get a Score for sorting. This score will be added to the Score float in FTargetingDefaultResultData
- L31 _protected prototype_ `float BP_GetScoreForTarget(const FTargetingRequestHandle& TargetingHandle, const FTargetingDefaultResultData& TargetData) const;` — `UFUNCTION(BlueprintImplementableEvent, DisplayName=GetScoreForTarget, Category=Targeting)` — Called on every target to get a Score for sorting. This score will be added to the Score float in FTargetingDefaultResultData

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API TARGETINGSYSTEM_API`

### `Plugins/Experimental/GameplayTargetingSystem/Source/GameplayTargetingSystem/Public/Tasks/TargetingFilterTask_ActorClass.h` (Public)


#### class `UTargetingFilterTask_ActorClass`  
`class UTargetingFilterTask_ActorClass : public UTargetingFilterTask_BasicFilterTemplate`  
_L17-35_
- reflection: `UCLASS(Blueprintable)`
- inherits: `UTargetingFilterTask_BasicFilterTemplate`
- desc: @class UTargetingFilterTask_ActorClass Simple filtering task where we check the targets class type against the required and ignored class types.
- L22 _public prototype_ `UTargetingFilterTask_ActorClass(const FObjectInitializer& ObjectInitializer);`
- L25 _public prototype_ `virtual bool ShouldFilterTarget(const FTargetingRequestHandle& TargetingHandle, const FTargetingDefaultResultData& TargetData) const override;` — Evaluation function called by derived classes to process the targeting request
- L30 _protected member_ `TArray<TObjectPtr<UClass>> RequiredActorClassFilters;` — `UPROPERTY(EditAnywhere, Category = "Targeting Filter | Class", Meta = (AllowAbstract=true))` — The set of required actor classes (must be one of these types to not be filtered out)
- L34 _protected member_ `TArray<TObjectPtr<UClass>> IgnoredActorClassFilters;` — `UPROPERTY(EditAnywhere, Category = "Targeting Filter | Class", Meta = (AllowAbstract = true))` — The set of ignored actor classes (must NOT be one of these types)

### `Plugins/Experimental/GameplayTargetingSystem/Source/GameplayTargetingSystem/Public/Tasks/TargetingFilterTask_BasicFilterTemplate.h` (Public)


#### class `UTargetingFilterTask_BasicFilterTemplate`  
`class UTargetingFilterTask_BasicFilterTemplate : public UTargetingTask`  
_L25-48_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UTargetingTask`
- desc: @class UTargetingFilterTask_BasicFilterTemplate A base class that has a basic setup struct that a majority of filtering tasks will find convenient.
- L30 _public prototype_ `UTargetingFilterTask_BasicFilterTemplate(const FObjectInitializer& ObjectInitializer);`
- L34 _private prototype_ `virtual void Execute(const FTargetingRequestHandle& TargetingHandle) const override;` — Evaluation function called by derived classes to process the targeting request
- L38 _protected prototype_ `virtual bool ShouldFilterTarget(const FTargetingRequestHandle& TargetingHandle, const FTargetingDefaultResultData& TargetData) const;` — Called against every target data to determine if the target should be filtered out
- L43 _private prototype_ `virtual void DrawDebug(UTargetingSubsystem* TargetingSubsystem, FTargetingDebugInfo& Info, const FTargetingRequestHandle& TargetingHandle, float XOffset, float YOffset, int32 MinTextRowsToAdvance) const override;`
- L44 _private prototype_ `void AddFilteredTarget(const FTargetingRequestHandle& TargetingHandle, const FTargetingDefaultResultData& TargetData) const;`
- L45 _private prototype_ `void ResetFilteredTarget(const FTargetingRequestHandle& TargetingHandle) const;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API TARGETINGSYSTEM_API`

### `Plugins/Experimental/GameplayTargetingSystem/Source/GameplayTargetingSystem/Public/Tasks/TargetingFilterTask_SortByDistance.h` (Public)


#### class `UTargetingFilterTask_SortByDistance`  
`class UTargetingFilterTask_SortByDistance : public UTargetingSortTask_Base`  
_L26-47_
- reflection: `UCLASS(Blueprintable)`
- inherits: `UTargetingSortTask_Base`
- desc: @class UTargetingFilterTask_SortByDistance Simple sorting filter based on the distance to the source actor. Note: This filter will use the FTargetingDefaultResultsSet and use the Score factor defined for each target to store the distance and sort by that value.
- L31 _protected prototype_ `virtual float GetScoreForTarget(const FTargetingRequestHandle& TargetingHandle, const FTargetingDefaultResultData& TargetData) const override;`
- L35 _protected member_ `bool bUseDistanceToNearestBlockingCollider = false;` — `UPROPERTY(EditAnywhere, Category = "Target Sorting | Sort By Distance Data")` — Use the distance to the nearest blocking collision surface on each actor instead of the distance to the actor's location
- L42 _protected member_ `TEnumAsByte<ECollisionChannel> DistanceToCollisionChannel = ECollisionChannel::ECC_WorldDynamic;` — `UPROPERTY(EditAnywhere, Category = "Target Sorting | Sort By Distance Data", Meta=(EditCondition="bUseDistanceToNearestBlockingCollider "))` — Collision channel used to determine the closest point on a actor's collider. Colliders will only be considered if they block this channel
- L46 _private prototype_ `FVector GetSourceLocation(const FTargetingRequestHandle& TargetingHandle) const;` — Returns the Source location, whether that comes from the source actor or the Source location in the Source Context

### `Plugins/Experimental/GameplayTargetingSystem/Source/GameplayTargetingSystem/Public/Tasks/TargetingSelectionTask_AOE.h` (Public)


#### enum `ETargetingAOEShape`  
`enum class ETargetingAOEShape : uint8`  
_L27-34_
- reflection: `UENUM(BlueprintType)`
- desc: @enum ETargetingAOEShape
- L29 _public enumerator_ `Box`
- L30 _public enumerator_ `Cylinder`
- L31 _public enumerator_ `Sphere`
- L32 _public enumerator_ `Capsule`
- L33 _public enumerator_ `SourceComponent`

#### class `UTargetingSelectionTask_AOE`  
`class UTargetingSelectionTask_AOE : public UTargetingTask`  
_L49-183_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UTargetingTask`
- desc: @class UTargetingSelectionTask_AOE Basic AOE based selection task. There are 4 shape types to choose from + a custom option. Box - Defined by a given half extent Cylinder - Defined by the half extent (box) + radius Sphere	- Defined by a given radius Capsule	- Defined by the radius + half height SourceComponent - Use a collision component with a specific component tag as the shape
- L54 _public prototype_ `UTargetingSelectionTask_AOE(const FObjectInitializer& ObjectInitializer);`
- L57 _public prototype_ `virtual void Execute(const FTargetingRequestHandle& TargetingHandle) const override;` — Evaluation function called by derived classes to process the targeting request
- L60 _public prototype_ `void DebugDrawBoundingVolume(const FTargetingRequestHandle& TargetingHandle, const FColor& Color, const FOverlapDatum* OverlapDatum = nullptr) const;` — Debug draws the outlines of the set shape type.
- L62 _public function_ `ETargetingAOEShape GetShapeType() const`
- L63 _public prototype_ `void SetShapeType(ETargetingAOEShape InShapeType);`
- L64 _public prototype_ `void SetHalfExtent(FVector InHalfExtent);`
- L65 _public prototype_ `void SetRadius(FScalableFloat InRadius);`
- L66 _public prototype_ `void SetHalfHeight(FScalableFloat InHalfHeight);`
- L70 _public prototype_ `FVector GetSourceLocation(const FTargetingRequestHandle& TargetingHandle) const;` — `UFUNCTION(BlueprintNativeEvent, Category = "Target AOE Selection")` — Native Event to get the source location for the AOE
- L74 _public prototype_ `FVector GetSourceOffset(const FTargetingRequestHandle& TargetingHandle) const;` — `UFUNCTION(BlueprintNativeEvent, Category = "Target AOE Selection")` — Native Event to get a source location offset for the AOE
- L78 _public prototype_ `FQuat GetSourceRotation(const FTargetingRequestHandle& TargetingHandle) const;` — `UFUNCTION(BlueprintNativeEvent, Category = "Target AOE Selection")` — Native event to get the source rotation for the AOE
- L82 _public prototype_ `FRotator GetSourceRotationOffset(const FTargetingRequestHandle& TargetingHandle) const;` — `UFUNCTION(BlueprintNativeEvent, Category = "Target AOE Selection")` — Native Event to get a source rotation offset for the AOE
- L85 _public prototype_ `FCollisionShape GetCollisionShape() const;` — Helper method to build the Collision Shape
- L87 _public function_ `bool GetUseRelativeOffset() const`
- L91 _private prototype_ `void ExecuteImmediateTrace(const FTargetingRequestHandle& TargetingHandle) const;` — Method to process the trace task immediately
- L94 _private prototype_ `void ExecuteAsyncTrace(const FTargetingRequestHandle& TargetingHandle) const;` — Method to process the trace task asynchronously
- L97 _private prototype_ `void HandleAsyncOverlapComplete(const FTraceHandle& InTraceHandle, FOverlapDatum& InOverlapDatum, FTargetingRequestHandle TargetingHandle) const;` — Callback for an async overlap
- L100 _private prototype_ `void ProcessOverlapResults(const FTargetingRequestHandle& TargetingHandle, const TArray<FOverlapResult>& Overlaps) const;` — Method to take the overlap results and store them in the targeting result data
- L104 _private prototype_ `const UPrimitiveComponent* GetCollisionComponent(const FTargetingRequestHandle& TargetingHandle) const;` — Helper method to find the custom component defined on the source actor
- L107 _private prototype_ `void InitCollisionParams(const FTargetingRequestHandle& TargetingHandle, FCollisionQueryParams& OutParams) const;` — Setup CollisionQueryParams for the AOE
- L112 _protected member_ `ETargetingAOEShape ShapeType = ETargetingAOEShape::Box;` — `UPROPERTY(EditAnywhere, Category = "Target AOE Selection | Data")` — The shape type to use for the AOE
- L116 _protected member_ `TEnumAsByte<ECollisionChannel> CollisionChannel;` — `UPROPERTY(EditAnywhere, Category = "Target AOE Selection | Data")` — The collision channel to use for the overlap check (as long as Collision Profile Name is not set)
- L120 _protected member_ `FCollisionProfileName CollisionProfileName;` — `UPROPERTY(EditAnywhere, Category = "Target AOE Selection | Data")` — The collision profile name to use for the overlap check
- L124 _protected member_ `TArray<TEnumAsByte<EObjectTypeQuery>> CollisionObjectTypes;` — `UPROPERTY(EditAnywhere, Category = "Target AOE Selection | Data")` — The collision profile name to use for the overlap check
- L128 _protected member_ `FVector DefaultSourceOffset = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = "Target AOE Selection | Data")` — The default source location offset used by GetSourceOffset
- L132 _protected member_ `FRotator DefaultSourceRotationOffset = FRotator::ZeroRotator;` — `UPROPERTY(EditAnywhere, Category = "Target AOE Selection | Data")` — The default source rotation offset used by GetSourceRotationOffset
- L136 _protected member_ `uint8 bUseRelativeOffset : 1;` — `UPROPERTY(EditAnywhere, Category = "Target AOE Selection | Data")` — Should we offset based on world or relative Source object transform?
- L140 _protected member_ `uint8 bIgnoreSourceActor : 1;` — `UPROPERTY(EditAnywhere, Category = "Target AOE Selection | Data")` — Indicates the trace should ignore the source actor
- L144 _protected member_ `uint8 bIgnoreInstigatorActor : 1;` — `UPROPERTY(EditAnywhere, Category = "Target AOE Selection | Data")` — Indicates the trace should ignore the source actor
- L148 _protected member_ `uint8 bTraceComplex : 1 = false;` — `UPROPERTY(EditAnywhere, Category = "Target AOE Selection | Data")` — When enabled, the trace will be performed against complex collision.
- L154 _protected member_ `FVector HalfExtent = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = "Target AOE Selection | Box and Cylinder")` — The half extent to use for box and cylinder For Cylinder the X component will be the radius and Z will be its height
- L158 _protected member_ `FScalableFloat Radius = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Target AOE Selection | Sphere and Capsule")` — The radius to use for sphere and capsule overlaps
- L162 _protected member_ `FScalableFloat HalfHeight = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Target AOE Selection | Capsule")` — The half height to use for capsule overlap checks
- L167 _protected member_ `FName ComponentTag = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Target AOE Selection | Custom Component")` — The component tag to use if a custom component is desired as the overlap shape. Use to look up the component on the source actor
- L171 _protected prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;`
- L172 _protected prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L178 _private prototype_ `virtual void DrawDebug(UTargetingSubsystem* TargetingSubsystem, FTargetingDebugInfo& Info, const FTargetingRequestHandle& TargetingHandle, float XOffset, float YOffset, int32 MinTextRowsToAdvance) const override;`
- L179 _private prototype_ `void BuildDebugString(const FTargetingRequestHandle& TargetingHandle, const TArray<FTargetingDefaultResultData>& TargetResults) const;`
- L180 _private prototype_ `void ResetDebugString(const FTargetingRequestHandle& TargetingHandle) const;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API TARGETINGSYSTEM_API`

### `Plugins/Experimental/GameplayTargetingSystem/Source/GameplayTargetingSystem/Public/Tasks/TargetingSelectionTask_SourceActor.h` (Public)


#### class `UTargetingSelectionTask_SourceActor`  
`class UTargetingSelectionTask_SourceActor : public UTargetingTask`  
_L23-41_
- reflection: `UCLASS()`
- inherits: `UTargetingTask`
- desc: @class UTargetingSelectionTask_SourceActor Simple targeting selection task that gets the source actor defined in the targeting source context.
- L28 _public prototype_ `UTargetingSelectionTask_SourceActor(const FObjectInitializer& ObjectInitializer);`
- L31 _public prototype_ `virtual void Execute(const FTargetingRequestHandle& TargetingHandle) const override;` — Evaluation function called by derived classes to process the targeting request
- L36 _private prototype_ `virtual void DrawDebug(UTargetingSubsystem* TargetingSubsystem, FTargetingDebugInfo& Info, const FTargetingRequestHandle& TargetingHandle, float XOffset, float YOffset, int32 MinTextRowsToAdvance) const override;`
- L37 _private prototype_ `void AddSourceActorDebugString(const FTargetingRequestHandle& TargetingHandle, const AActor* SourceActor) const;`
- L38 _private prototype_ `void ResetSourceActorDebugString(const FTargetingRequestHandle& TargetingHandle) const;`

### `Plugins/Experimental/GameplayTargetingSystem/Source/GameplayTargetingSystem/Public/Tasks/TargetingSelectionTask_Trace.h` (Public)


#### enum `ETargetingTraceType`  
`enum class ETargetingTraceType : uint8`  
_L27-34_
- reflection: `UENUM()`
- desc: @enum ETargetingTraceType determines the shape of the trace used.
- L29 _public enumerator_ `Line`
- L30 _public enumerator_ `Sphere`
- L32 _public enumerator_ `Capsule` — With zero rotation, the capsule length runs along the trace's up vector (the cross product of the trace's forward vector and the trace's forward vector flattened onto the XY plane and rotated 90 degrees around the Z vector).
- L33 _public enumerator_ `Box`

#### class `UTargetingSelectionTask_Trace`  
`class UTargetingSelectionTask_Trace : public UTargetingTask`  
_L43-191_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UTargetingTask`
- desc: @class UTargetingSelectionTask_Trace Selection task that can perform a synchronous or asynchronous trace (line/sweep) to find all targets up to the first blocking hit (or its end point).
- L48 _public prototype_ `UTargetingSelectionTask_Trace(const FObjectInitializer& ObjectInitializer);`
- L51 _public prototype_ `virtual void Execute(const FTargetingRequestHandle& TargetingHandle) const override;` — Evaluation function called by derived classes to process the targeting request
- L56 _protected prototype_ `FVector GetSourceLocation(const FTargetingRequestHandle& TargetingHandle) const;` — `UFUNCTION(BlueprintNativeEvent, Category = "Target Trace Selection")` — Native Event to get the source location for the Trace
- L60 _protected prototype_ `FVector GetSourceOffset(const FTargetingRequestHandle& TargetingHandle) const;` — `UFUNCTION(BlueprintNativeEvent, Category = "Target Trace Selection")` — Native Event to get a source location offset for the Trace
- L64 _protected prototype_ `FVector GetTraceDirection(const FTargetingRequestHandle& TargetingHandle) const;` — `UFUNCTION(BlueprintNativeEvent, Category = "Target Trace Selection")` — Native Event to get the direction for the Trace
- L68 _protected prototype_ `float GetTraceLength(const FTargetingRequestHandle& TargetingHandle) const;` — `UFUNCTION(BlueprintNativeEvent, Category = "Target Trace Selection")` — Native Event to get the length for the Trace
- L72 _protected prototype_ `float GetSweptTraceRadius(const FTargetingRequestHandle& TargetingHandle) const;` — `UFUNCTION(BlueprintNativeEvent, Category = "Target Trace Selection")` — Native Event to get the swept trace radius (only called if TraceType = ETargetingTraceType::Sphere or TraceType = ETargetingTraceType::Capsule)
- L76 _protected prototype_ `float GetSweptTraceCapsuleHalfHeight(const FTargetingRequestHandle& TargetingHandle) const;` — `UFUNCTION(BlueprintNativeEvent, Category = "Target Trace Selection")` — Native Event to get the swept trace capsule's half height (only called if  TraceType = ETargetingTraceType::Capsule)
- L80 _protected prototype_ `FVector GetSweptTraceBoxHalfExtents(const FTargetingRequestHandle& TargetingHandle) const;` — `UFUNCTION(BlueprintNativeEvent, Category = "Target Trace Selection")` — Native Event to get the swept box trace half extents (only called if TraceType = ETargetingTraceType::Box)
- L85 _protected prototype_ `FRotator GetSweptTraceRotation(const FTargetingRequestHandle& TargetingHandle) const;` — `UFUNCTION(BlueprintNativeEvent, Category = "Target Trace Selection")` — Native Event to get the swept trace rotation relative to trace direction (only called if TraceType = ETargetingTraceType::Capsule or TraceType = ETargetingTraceType::Box)
- L89 _protected prototype_ `void GetAdditionalActorsToIgnore(const FTargetingRequestHandle& TargetingHandle, TArray<AActor*>& OutAdditionalActorsToIgnore) const;` — `UFUNCTION(BlueprintNativeEvent, Category = "Target Trace Selection")` — Native Event to get additional actors the Trace should ignore
- L93 _private prototype_ `void ExecuteImmediateTrace(const FTargetingRequestHandle& TargetingHandle) const;` — Method to process the trace task immediately
- L96 _private prototype_ `void ExecuteAsyncTrace(const FTargetingRequestHandle& TargetingHandle) const;` — Method to process the trace task asynchronously
- L99 _private prototype_ `void HandleAsyncTraceComplete(const FTraceHandle& InTraceHandle, FTraceDatum& InTraceDatum, FTargetingRequestHandle TargetingHandle) const;` — Callback for an async trace
- L102 _private prototype_ `void ProcessHitResults(const FTargetingRequestHandle& TargetingHandle, const TArray<FHitResult>& Hits) const;` — Method to take the hit results and store them in the targeting result data
- L105 _private prototype_ `void InitCollisionParams(const FTargetingRequestHandle& TargetingHandle, FCollisionQueryParams& OutParams) const;` — Setup CollisionQueryParams for the trace
- L108 _private prototype_ `FQuat GetSweptTraceQuat(const FVector& TraceDirection, const FTargetingRequestHandle& TargetingHandle) const;` — For non-sphere shape traces, calculates the world rotation for that trace.
- L113 _protected member_ `ETargetingTraceType TraceType = ETargetingTraceType::Line;` — `UPROPERTY(EditAnywhere, Category = "Target Trace Selection | Collision Data")` — The trace type (i.e. shape) to use
- L117 _protected member_ `TEnumAsByte<ETraceTypeQuery> TraceChannel;` — `UPROPERTY(EditAnywhere, Category = "Target Trace Selection | Collision Data")` — The trace channel to use
- L121 _protected member_ `FCollisionProfileName CollisionProfileName;` — `UPROPERTY(EditAnywhere, Category = "Target Trace Selection | Collision Data")` — The collision profile name to use instead of trace channel (does not work for async traces)
- L125 _protected member_ `FScalableFloat DefaultSweptTraceRadius = 10.0f;` — `UPROPERTY(EditAnywhere, Category = "Target Trace Selection | Swept Data")` — The default swept trace radius used by GetSweptTraceRadius when the trace type is set to Sphere or Capsule
- L129 _protected member_ `FScalableFloat DefaultSweptTraceCapsuleHalfHeight = 10.0f;` — `UPROPERTY(EditAnywhere, Category = "Target Trace Selection | Swept Data")` — The default swept trace radius used by GetSweptTraceRadius when the trace type is set to Capsule
- L133 _protected member_ `FScalableFloat DefaultSweptTraceBoxHalfExtentX = 10.0f;` — `UPROPERTY(EditAnywhere, Category = "Target Trace Selection | Swept Data")` — The default swept extents used by GetSweptTraceExtents when the trace type is set to Box
- L137 _protected member_ `FScalableFloat DefaultSweptTraceBoxHalfExtentY = 10.0f;` — `UPROPERTY(EditAnywhere, Category = "Target Trace Selection | Swept Data")` — The default swept extents used by GetSweptTraceBoxHalfExtents when the trace type is set to Box
- L141 _protected member_ `FScalableFloat DefaultSweptTraceBoxHalfExtentZ = 10.0f;` — `UPROPERTY(EditAnywhere, Category = "Target Trace Selection | Swept Data")` — The default swept extents used by GetSweptTraceBoxHalfExtents when the trace type is set to Box
- L145 _protected member_ `FRotator DefaultSweptTraceRotation = FRotator::ZeroRotator;` — `UPROPERTY(EditAnywhere, Category = "Target Trace Selection | Swept Data")` — The default swept rotation (relative to the trace direction) used by GetSweptTraceRotation when the trace type is set to Capsule or Box
- L149 _protected member_ `FScalableFloat DefaultTraceLength = 10.0f;` — `UPROPERTY(EditAnywhere, Category = "Target Trace Selection | Trace Data")` — The default trace length to use if GetTraceLength is not overridden by a child
- L153 _protected member_ `FVector DefaultSourceOffset = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = "Target Trace Selection | Trace Data")` — The default source location offset used by GetSourceOffset
- L157 _protected member_ `FVector ExplicitTraceDirection = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = "Target Trace Selection | Trace Data")` — An explicit trace direction to use (default uses pawn control rotation or actor forward vector in GetTraceDirection)
- L161 _protected member_ `uint8 bComplexTrace : 1;` — `UPROPERTY(EditAnywhere, Category = "Target Trace Selection | Trace Data")` — Indicates the trace should perform a complex trace
- L165 _protected member_ `uint8 bMultiTrace : 1;` — `UPROPERTY(EditAnywhere, Category = "Target Trace Selection | Trace Data")` — Indicates whether the trace should be a multi trace or a single trace
- L169 _protected member_ `uint8 bIgnoreSourceActor : 1;` — `UPROPERTY(EditAnywhere, Category = "Target Trace Selection | Trace Data")` — Indicates the trace should ignore the source actor
- L173 _protected member_ `uint8 bIgnoreInstigatorActor : 1;` — `UPROPERTY(EditAnywhere, Category = "Target Trace Selection | Trace Data")` — Indicates the trace should ignore the source actor
- L177 _protected prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;`
- L183 _private prototype_ `virtual void DrawDebug(UTargetingSubsystem* TargetingSubsystem, FTargetingDebugInfo& Info, const FTargetingRequestHandle& TargetingHandle, float XOffset, float YOffset, int32 MinTextRowsToAdvance) const override;`
- L186 _private prototype_ `virtual void DrawDebugTrace(const FTargetingRequestHandle TargetingHandle, const FVector& StartLocation, const FVector& EndLocation, const FQuat& OrientationQuat, const bool bHit, const TArray<FHitResult>& Hits) const;` — Draw debug info showing the results of the shape trace used for targeting.
- L187 _private prototype_ `void BuildTraceResultsDebugString(const FTargetingRequestHandle& TargetingHandle, const TArray<FTargetingDefaultResultData>& TargetResults) const;`
- L188 _private prototype_ `void ResetTraceResultsDebugString(const FTargetingRequestHandle& TargetingHandle) const;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API TARGETINGSYSTEM_API`

### `Plugins/Experimental/GameplayTargetingSystem/Source/GameplayTargetingSystem/Public/Tasks/TargetingSortTask_Base.h` (Public)


#### class `UTargetingSortTask_Base`  
`class UTargetingSortTask_Base : public UTargetingTask`  
_L17-49_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UTargetingTask`
- desc: @class TargetingSortTask_Base A base class that has the basic setup for a sort task.
- L22 _public prototype_ `UTargetingSortTask_Base(const FObjectInitializer& ObjectInitializer);`
- L26 _protected prototype_ `virtual float GetScoreForTarget(const FTargetingRequestHandle& TargetingHandle, const FTargetingDefaultResultData& TargetData) const;` — Called on every target to get a Score for sorting. This score will be added to the Score float in FTargetingDefaultResultData
- L30 _private prototype_ `virtual void Execute(const FTargetingRequestHandle& TargetingHandle) const override;` — Evaluation function called by derived classes to process the targeting request
- L34 _protected member_ `uint8 bAscending : 1;` — `UPROPERTY(EditAnywhere, Category = "Target Sorting | Data")`
- L38 _protected member_ `uint8 bStableSort : 1;` — `UPROPERTY(EditAnywhere, Category = "Target Sorting | Data")` — Should this task use a (slightly slower) sorting algorithm that preserves the relative ordering of targets with equal scores?
- L43 _private prototype_ `virtual void DrawDebug(UTargetingSubsystem* TargetingSubsystem, FTargetingDebugInfo& Info, const FTargetingRequestHandle& TargetingHandle, float XOffset, float YOffset, int32 MinTextRowsToAdvance) const override;`
- L44 _private prototype_ `void BuildPreSortDebugString(const FTargetingRequestHandle& TargetingHandle, const TArray<FTargetingDefaultResultData>& TargetResults) const;`
- L45 _private prototype_ `void BuildPostSortDebugString(const FTargetingRequestHandle& TargetingHandle, const TArray<FTargetingDefaultResultData>& TargetResults) const;`
- L46 _private prototype_ `void ResetSortDebugStrings(const FTargetingRequestHandle& TargetingHandle) const;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API TARGETINGSYSTEM_API`

### `Plugins/Experimental/GameplayTargetingSystem/Source/GameplayTargetingSystem/Public/Tasks/TargetingTask.h` (Public)


#### class `UTargetingTask`  
`class UTargetingTask : public UObject`  
_L46-85_
- reflection: `UCLASS(MinimalAPI, EditInlineNew, Abstract, Const, meta=(ShowWorldContextPin="true"))`
- inherits: `UObject`
- desc: @class UTargetingTask The base object type that all Targeting Tasks will derive from. The idea is the targeting system will take target requests that are collections of target tasks that will potentially generate/remove and perform operations on sets of targeting results data. Potential Task Implementations: Selection Tasks: Target selection tasks would be used to build up a collection of target request results. It is recommend they are added first in the targeting request. Things like ray casts, AOE shapes, actors under a reticle, etc are cases that generally fall under selection. Filtering Tasks: Target filtering tasks are used to reduce the target result data set to those targets that match a given criteria. Things like actor class, team distance, facing, etc. Sorting Tasks: Target sorting tasks would be useful to take the set and put them in an order the end user might prefer to make decisions on. Distance (min/max), score rating etc.
- L51 _public prototype_ `UTargetingTask(const FObjectInitializer& ObjectInitializer);`
- L54 _public prototype_ `virtual void Init(const FTargetingRequestHandle& TargetingHandle) const;` — Lifecycle function called when the task first begins
- L57 _public prototype_ `virtual void Execute(const FTargetingRequestHandle& TargetingHandle) const;` — Evaluation function called by derived classes to process the targeting request
- L60 _public prototype_ `virtual void CancelAsync() const;` — Lifecycle function called when the task was cancelled while in the Executing Async state
- L64 _protected prototype_ `bool IsAsyncTargetingRequest(const FTargetingRequestHandle& TargetingHandle) const;` — Helper method to check if this task is running in an async targeting request
- L67 _protected prototype_ `void SetTaskAsyncState(const FTargetingRequestHandle& TargetingHandle, ETargetingTaskAsyncState AsyncState) const;` — Helper method to set the async state for the task (as long as it is the currently running one)
- L70 _protected prototype_ `ETargetingTaskAsyncState GetTaskAsyncState(const FTargetingRequestHandle& TargetingHandle) const;` — Helper method to check if a task is currently executing an async operation
- L73 _protected prototype_ `UWorld* GetSourceContextWorld(const FTargetingRequestHandle& TargetingHandle) const;` — Helper method to get the world from the source context (if possible, returns nullptr if one cannot be found)
- L77 _protected prototype_ `UTargetingSubsystem* GetTargetingSubsystem(const FTargetingRequestHandle& TargetingHandle) const;` — `UFUNCTION(BlueprintPure, Category="Targeting")` — Helper method to get the Targeting Subsystem in TargetingTask Blueprint Types
- L82 _public function_ `virtual void DrawDebug(UTargetingSubsystem* TargetingSubsystem, FTargetingDebugInfo& Info, const FTargetingRequestHandle& TargetingHandle, float XOffset, float YOffset, int32 MinTextRowsToAdvance = 0) const`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TARGETINGSYSTEM_API`

### `Plugins/Experimental/GameplayTargetingSystem/Source/GameplayTargetingSystem/Public/Types/TargetingSystemDataStores.h` (Public)


#### struct `UE::TargetingSystem::TTargetingDataStore`  
`template<typename Type> struct TTargetingDataStore`  
_L26-55_
- desc: @struct TTargetingDataStore Templated struct to define targeting data stores. The goal is to provide a flexible way for targeting tasks to add/remove/update generic sets of data they wish to work with. This allows future growth in games to write tasks either new or extending off base framework archetypes to achieve the targeting goals they need.
- L28 _public function_ `TTargetingDataStore()`
- L33 _public function_ `~TTargetingDataStore()`
- L41 _public prototype_ `static Type& FindOrAdd(FTargetingRequestHandle Handle);`
- L42 _public prototype_ `static Type* Find(FTargetingRequestHandle Handle);`
- L43 _public prototype_ `static void OnTargetingRequestHandleReleased(FTargetingRequestHandle Handle);`
- L51 _private member_ `TSortedMap<FTargetingRequestHandle, Type> Items;` — The Items by handle stored for targeting requests
- L54 _private member_ `FDelegateHandle ReleaseDelegateHandle;` — Stores the register handle to the release delegate
- L64 _function_ `template<> inline FTargetingRequestData& TTargetingDataStore<FTargetingRequestData>::FindOrAdd(FTargetingRequestHandle Handle)`
- L70 _function_ `template<> inline FTargetingRequestData* TTargetingDataStore<FTargetingRequestData>::Find(FTargetingRequestHandle Handle)`
- L76 _function_ `template<> inline void TTargetingDataStore<FTargetingRequestData>::OnTargetingRequestHandleReleased(FTargetingRequestHandle Handle)`
- L86 _function_ `template<> inline const FTargetingTaskSet*& TTargetingDataStore<const FTargetingTaskSet*>::FindOrAdd(FTargetingRequestHandle Handle)`
- L92 _function_ `template<> inline const FTargetingTaskSet** TTargetingDataStore<const FTargetingTaskSet*>::Find(FTargetingRequestHandle Handle)`
- L98 _function_ `template<> inline void TTargetingDataStore<const FTargetingTaskSet*>::OnTargetingRequestHandleReleased(FTargetingRequestHandle Handle)`
- L108 _function_ `template<> inline FTargetingSourceContext& TTargetingDataStore<FTargetingSourceContext>::FindOrAdd(FTargetingRequestHandle Handle)`
- L114 _function_ `template<> inline FTargetingSourceContext* TTargetingDataStore<FTargetingSourceContext>::Find(FTargetingRequestHandle Handle)`
- L120 _function_ `template<> inline void TTargetingDataStore<FTargetingSourceContext>::OnTargetingRequestHandleReleased(FTargetingRequestHandle Handle)`
- L130 _function_ `template<> inline FTargetingDefaultResultsSet& TTargetingDataStore<FTargetingDefaultResultsSet>::FindOrAdd(FTargetingRequestHandle Handle)`
- L136 _function_ `template<> inline FTargetingDefaultResultsSet* TTargetingDataStore<FTargetingDefaultResultsSet>::Find(FTargetingRequestHandle Handle)`
- L142 _function_ `template<> inline void TTargetingDataStore<FTargetingDefaultResultsSet>::OnTargetingRequestHandleReleased(FTargetingRequestHandle Handle)`
- L152 _function_ `template<> inline FTargetingAsyncTaskData& TTargetingDataStore<FTargetingAsyncTaskData>::FindOrAdd(FTargetingRequestHandle Handle)`
- L158 _function_ `template<> inline FTargetingAsyncTaskData* TTargetingDataStore<FTargetingAsyncTaskData>::Find(FTargetingRequestHandle Handle)`
- L164 _function_ `template<> inline void TTargetingDataStore<FTargetingAsyncTaskData>::OnTargetingRequestHandleReleased(FTargetingRequestHandle Handle)`
- L173 _function_ `template<> inline FTargetingImmediateTaskData& TTargetingDataStore<FTargetingImmediateTaskData>::FindOrAdd(FTargetingRequestHandle Handle)`
- L179 _function_ `template<> inline FTargetingImmediateTaskData* TTargetingDataStore<FTargetingImmediateTaskData>::Find(FTargetingRequestHandle Handle)`
- L185 _function_ `template<> inline void TTargetingDataStore<FTargetingImmediateTaskData>::OnTargetingRequestHandleReleased(FTargetingRequestHandle Handle)`
- L196 _function_ `template<> inline FTargetingDebugData& TTargetingDataStore<FTargetingDebugData>::FindOrAdd(FTargetingRequestHandle Handle)`
- L202 _function_ `template<> inline FTargetingDebugData* TTargetingDataStore<FTargetingDebugData>::Find(FTargetingRequestHandle Handle)`
- L208 _function_ `template<> inline void TTargetingDataStore<FTargetingDebugData>::OnTargetingRequestHandleReleased(FTargetingRequestHandle Handle)`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L13 _namespace_ `namespace TargetingSystem` (scope `UE`)
- L61 _externvar_ `extern TTargetingDataStore<FTargetingRequestData> GTargetingRequestDataStore;` (scope `UE::TargetingSystem`) — FTargetingRequestData Data Store
- L83 _externvar_ `extern TTargetingDataStore<const FTargetingTaskSet*> GTargetingTaskSetDataStore;` (scope `UE::TargetingSystem`) — FTargetingTaskSet Data Store
- L105 _externvar_ `extern TTargetingDataStore<FTargetingSourceContext> GTargetingSourceDataStore;` (scope `UE::TargetingSystem`) — FTargetingSourceContext Data Store
- L127 _externvar_ `extern TTargetingDataStore<FTargetingDefaultResultsSet> GTargetingResultsDataStore;` (scope `UE::TargetingSystem`) — FTargetingDefaultResultsSet Data Store
- L149 _externvar_ `extern TTargetingDataStore<FTargetingAsyncTaskData> GTargetingAsyncTaskDataStore;` (scope `UE::TargetingSystem`) — FTargetingAsyncTaskData Data Store
- L170 _externvar_ `extern TTargetingDataStore<FTargetingImmediateTaskData> GTargetingImmediateTaskDataStore;` (scope `UE::TargetingSystem`) — FTargetingImmediateTaskData Data Store
- L193 _externvar_ `extern TTargetingDataStore<FTargetingDebugData> GTargetingDebugDataStore;` (scope `UE::TargetingSystem`) — FTargetingDefaultResults Data Store
- L239 _macro_ `#define DECLARE_TARGETING_DATA_STORE(DataType) namespace UE \` — Helper macros for creating custom data stores for the targeting system These data stores can be used to track information linked to a specific Targeting Request in TargetingTasks. To create a custom data store, place a DECLARE_TARGETING_DATA_STORE in a header file and a DEFINE_TARGETING_DATA_STORE in a source file, using the data type to be stored as the macro parameter. For example: A data store that holds a struct FCustomTargetingData would be declared as follows In CustomTargetingData.h: DECLARE_TARGETING_DATA_STORE(FCustomTargetingData) In CustomTargetingData.cpp DEFINE_TARGETING_DATA_STORE(FCustomTargetingData) This new Data Store could be accessed in a relevant TargetingTask like TTargetingDataStore<FCustomTargetingData>::FindOrAdd(Handle)
- L265 _macro_ `#define DEFINE_TARGETING_DATA_STORE(DataType) namespace UE \`

### `Plugins/Experimental/GameplayTargetingSystem/Source/GameplayTargetingSystem/Public/Types/TargetingSystemLogs.h` (Public)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_STATS_GROUP(TEXT("TargetingSystem"), STATGROUP_TargetingSystem, STA`
- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogTargetingSystem, Log, All);`
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogTargetingSystem, Log, All);`
- L11 _macro_ `#define TARGETING_LOG(Verbosity, Format, ...) UE_LOG(LogTargetingSystem, Verbosity, Format, ##__VA_ARGS__)`

### `Plugins/Experimental/GameplayTargetingSystem/Source/GameplayTargetingSystem/Public/Types/TargetingSystemTypes.h` (Public)


#### struct `FTargetingRequestHandle`  
`struct FTargetingRequestHandle`  
_L29-64_
- reflection: `USTRUCT(BlueprintType)`
- desc: @struct FTargetingRequestHandle The handle that is created when a user wants to make a targeting request.
- L34 _public function_ `FTargetingRequestHandle() : Handle(0)`
- L38 _public function_ `FTargetingRequestHandle(const int32 InHandle) : Handle(InHandle)`
- L42 _public member_ `uint32 Handle;`
- L45 _public function_ `inline bool IsValid() const` — Checks handle validity
- L48 _public prototype_ `void Reset();` — Method to reset the handle
- L51 _public prototype_ `bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);` — We override NetSeralize because we should never be network serializing this handle
- L54 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTargetingRequestHandleReleased, FTargetingRequestHandle) static FOnTargetingRequestHandleReleased& GetReleaseHandleDelegate();` — The handle released delegate that fires right before a handle is release so all data stores can clean up their state
- L58 _public function_ `inline bool operator==(const FTargetingRequestHandle& InHandle) const` — overloaded operators
- L59 _public function_ `inline bool operator!=(const FTargetingRequestHandle& InHandle) const`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FTargetingRequestHandle> : public TStructOpsTypeTraitsBase2<FTargetingRequestHandle>`  
_L67-75_
- inherits: `TStructOpsTypeTraitsBase2<FTargetingRequestHandle>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L70-74_

#### struct `FTargetingTaskSet`  
`struct FTargetingTaskSet`  
_L84-96_
- reflection: `USTRUCT(MinimalAPI, BlueprintType)`
- desc: @struct FTargetingTaskSet A set of tasks to be used by targeting requests to find/processes targets
- L90 _public prototype_ `static const FTargetingTaskSet*& FindOrAdd(FTargetingRequestHandle Handle);` — Convenience method to make using the global data store easier
- L91 _public prototype_ `static const FTargetingTaskSet** Find(FTargetingRequestHandle Handle);`
- L95 _public member_ `TArray<TObjectPtr<UTargetingTask>> Tasks;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category="Targeting Task Set")` — The set of tasks that will be used to satisfy a targeting request

#### struct `FTargetingDefaultResultData`  
`struct FTargetingDefaultResultData`  
_L103-118_
- reflection: `USTRUCT(BlueprintType)`
- desc: @struct FTargetingDefaultResultData
- L108 _public function_ `FTargetingDefaultResultData()`
- L113 _public member_ `FHitResult HitResult;` — `UPROPERTY(BlueprintReadOnly, Category=Targeting)` — The hit result for this target
- L117 _public member_ `float Score = 0.0f;` — `UPROPERTY(BlueprintReadOnly, Category=Targeting)` — The score associated w/ this target

#### struct `FTargetingDefaultResultsSet`  
`struct FTargetingDefaultResultsSet`  
_L128-143_
- reflection: `USTRUCT()`
- desc: @struct FTargetingDefaultResultsSet The base targeting result data used by the tasks implemented at the framework level. Provides an array of data (hit result / score) that tasks can add/remove/sort/etc to complete a targeting request.
- L133 _public function_ `FTargetingDefaultResultsSet()`
- L137 _public prototype_ `static FTargetingDefaultResultsSet& FindOrAdd(FTargetingRequestHandle Handle);` — Convenience method to make using the global data store easier
- L138 _public prototype_ `static FTargetingDefaultResultsSet* Find(FTargetingRequestHandle Handle);`
- L142 _public member_ `TArray<FTargetingDefaultResultData> TargetResults;` — `UPROPERTY()` — The hit result for this target

#### struct `FTargetingSourceContext`  
`struct FTargetingSourceContext`  
_L152-180_
- reflection: `USTRUCT(BlueprintType)`
- desc: @struct FTargetingSourceContext Stores context information about a targeting request.
- L158 _public prototype_ `static FTargetingSourceContext& FindOrAdd(FTargetingRequestHandle Handle);` — Convenience method to make using the global data store easier
- L159 _public prototype_ `static FTargetingSourceContext* Find(FTargetingRequestHandle Handle);`
- L163 _public member_ `TObjectPtr<AActor> SourceActor = nullptr;` — `UPROPERTY(BlueprintReadWrite, Category = "Targeting Source Context")` — The optional actor the targeting request sources from (i.e. player/projectile/etc)
- L167 _public member_ `TObjectPtr<AActor> InstigatorActor = nullptr;` — `UPROPERTY(BlueprintReadWrite, Category = "Targeting Source Context")` — The optional instigator the targeting request is owned by (i.e. owner of a projectile)
- L171 _public member_ `FVector SourceLocation = FVector::ZeroVector;` — `UPROPERTY(BlueprintReadWrite, Category = "Targeting Source Context")` — The optional location the targeting request will source from (i.e. do AOE targeting at x/y/z location)
- L175 _public member_ `FName SourceSocketName = NAME_None;` — `UPROPERTY(BlueprintReadWrite, Category = "Targeting Source Context")` — The optional socket name to use on the source actor (if an actor is defined)
- L179 _public member_ `TObjectPtr<UObject> SourceObject = nullptr;` — `UPROPERTY(BlueprintReadWrite, Category = "Targeting Source Context")` — The optional reference to a source uobject to use in the context

#### struct `FTargetingRequestData`  
`struct FTargetingRequestData`  
_L194-225_
- reflection: `USTRUCT()`
- desc: @struct FTargetingRequestData General purpose targeting request data. Used for general knowledge about the state of the request.
- L199 _public function_ `FTargetingRequestData() : bComplete(false)`
- L204 _public prototype_ `static FTargetingRequestData& FindOrAdd(FTargetingRequestHandle Handle);` — Convenience method to make using the global data store easier
- L205 _public prototype_ `static FTargetingRequestData* Find(FTargetingRequestHandle Handle);`
- L208 _public prototype_ `void Initialize(FTargetingRequestDelegate CompletionDelegate, FTargetingRequestDynamicDelegate CompletionDynamicDelegate, UTargetingSubsystem* Subsystem);` — Initializes the targeting request data for async processing
- L211 _public prototype_ `void BroadcastTargetingRequestDelegate(FTargetingRequestHandle TargetingRequestHandle);` — Broadcasts the targeting request delegate
- L214 _public member_ `UTargetingSubsystem* TargetingSubsystem;` — Ref to the TargetingSubsystem object processing this request
- L217 _public member_ `uint8 bComplete : 1;` — Indicates this handle has completed all the targeting request
- L220 _public member_ `FTargetingRequestDelegate TargetingRequestDelegate;` — /
- L224 _public member_ `FTargetingRequestDynamicDelegate TargetingRequestDynamicDelegate;` — `UPROPERTY()` — The dynamic delegate (BP) that fires when the targeting request is complete

#### enum `ETargetingTaskAsyncState`  
`enum class ETargetingTaskAsyncState : uint8`  
_L229-235_
- desc: @enum ETargetingTaskAsyncState
- L231 _public enumerator_ `Unitialized` — indicates this task hasn't been started yet
- L232 _public enumerator_ `Initialized` — indicates this task has been init'ed and is ready to execute
- L233 _public enumerator_ `Executing` — indicates this task is currently processing targets
- L234 _public enumerator_ `Completed` — indicates this task is finished processing targets

#### struct `FTargetingAsyncTaskData`  
`struct FTargetingAsyncTaskData`  
_L243-275_
- reflection: `USTRUCT()`
- desc: @struct FTargetingAsyncTaskData The set of task book keeping data for async targeting requests.
- L248 _public function_ `FTargetingAsyncTaskData() : bAsyncRequest(false) , bReleaseOnCompletion(false) , bRequeueOnCompletion(false)`
- L255 _public prototype_ `static FTargetingAsyncTaskData& FindOrAdd(FTargetingRequestHandle Handle);` — Convenience method to make using the global data store easier
- L256 _public prototype_ `static FTargetingAsyncTaskData* Find(FTargetingRequestHandle Handle);`
- L259 _public prototype_ `void InitializeForAsyncProcessing();` — Initializes the targeting request data for async processing
- L262 _public member_ `int32 CurrentAsyncTaskIndex = INDEX_NONE;` — The current task index being processed for the targeting request
- L265 _public member_ `ETargetingTaskAsyncState CurrentAsyncTaskState = ETargetingTaskAsyncState::Unitialized;` — The current task's async state
- L268 _public member_ `uint8 bAsyncRequest : 1;` — Indicates the targeting request was an asynchronous request
- L271 _public member_ `uint8 bReleaseOnCompletion : 1;` — Indicates the targeting request should be released after completion
- L274 _public member_ `uint8 bRequeueOnCompletion : 1;` — Indicates the target request should be re-queued after completion

#### struct `FTargetingImmediateTaskData`  
`struct FTargetingImmediateTaskData`  
_L283-298_
- reflection: `USTRUCT()`
- desc: @struct FTargetingImmediateTaskData The set of task book keeping data for immediate targeting requests.
- L288 _public function_ `FTargetingImmediateTaskData() : bReleaseOnCompletion(false)`
- L293 _public prototype_ `static FTargetingImmediateTaskData& FindOrAdd(FTargetingRequestHandle Handle);` — Convenience method to make using the global data store easier
- L294 _public prototype_ `static FTargetingImmediateTaskData* Find(FTargetingRequestHandle Handle);`
- L297 _public member_ `uint8 bReleaseOnCompletion : 1;` — Indicates the targeting request was an asynchronous request

#### struct `FTargetingDebugData`  
`struct FTargetingDebugData`  
_L308-332_
- reflection: `USTRUCT()`
- desc: @struct FTargetingDebugData The set of task book keeping data for async targeting requests.
- L313 _public function_ `FTargetingDebugData()`
- L318 _public prototype_ `static FTargetingDebugData& FindOrAdd(FTargetingRequestHandle Handle);` — Convenience method to make using the global data store easier
- L319 _public prototype_ `static FTargetingDebugData* Find(FTargetingRequestHandle Handle);`
- L324 _public member_ `TObjectPtr<const UTargetingPreset> TargetingPreset = nullptr;` — `UPROPERTY()`
- L327 _public member_ `TMap<FString, FString> DebugScratchPadStrings;` — `UPROPERTY()`
- L330 _public member_ `TArray<FTargetingDefaultResultData> CachedTargetResults;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L54 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTargetingRequestHandleReleased, FTargetingRequestHandle) static FOnTargetingRequestHandleReleased& GetReleaseHandleDelegate();` — The handle released delegate that fires right before a handle is release so all data stores can clean up their state
- L60 _function_ `friend bool operator<(const FTargetingRequestHandle& Lhs, const FTargetingRequestHandle& Rhs)`
- L71 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anon6fc41bbd0103`)
- L72 _enumerator_ `WithNetSerializer = true` (scope `TStructOpsTypeTraits::__anon6fc41bbd0103`)
- L73 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anon6fc41bbd0103`)
- L184 _delegate_ `DECLARE_DELEGATE_OneParam(FTargetingRequestDelegate, FTargetingRequestHandle );` — Delegate used by async targeting requests
- L184 _prototype_ `DECLARE_DELEGATE_OneParam(FTargetingRequestDelegate, FTargetingRequestHandle );` — Delegate used by async targeting requests
- L185 _delegate_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FTargetingRequestDynamicDelegate, FTargetingRequestHandle, TargetingRequestHandle);`
- L185 _prototype_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FTargetingRequestDynamicDelegate, FTargetingRequestHandle, TargetingRequestHandle);`
