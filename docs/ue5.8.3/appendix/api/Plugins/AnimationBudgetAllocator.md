# Plugins / AnimationBudgetAllocator

- module root: `Plugins/Runtime/AnimationBudgetAllocator/Source/AnimationBudgetAllocator`
- headers: 8; symbols: 217
- symbol kinds: class=6, delegate=3, externvar=20, function=16, macro=7, member=92, namespace=1, prototype=70, struct=2
- PrivateDependencyModuleNames: Core, CoreUObject, Engine

### `Plugins/Runtime/AnimationBudgetAllocator/Source/AnimationBudgetAllocator/Private/AnimationBudgetAllocator.h` (Private)


#### struct `FAnimBudgetAllocatorComponentData`  
`struct FAnimBudgetAllocatorComponentData`  
_L35-143_
- desc: Data for a single component
- L37 _public function_ `FAnimBudgetAllocatorComponentData() : Component(nullptr) , RootPrerequisite(nullptr) , Significance(0.0f) , AccumulatedDeltaTime(0.0f) , GameThreadLastTickTimeMs(0.0f) , GameThreadLastCompletionTimeMs(0.0f) #if ENABLE_DRAW_DEBUG , PrevFrameGameThreadLastCompletionTimeMs(0.0f) #endif , FrameOffset(0) , DesiredTickRate(0) , TickRate(0) , SkippedTicks(0) , StateChangeThrottle(0) , bTickEnabled(false) , bAlwaysTick(false) , bTickEvenIfNotRendered(false) , bInterpolate(false) , bReducedWork(false) , bReducedWorkDueToOffscreen(false) , bAllowReducedWork(false) , bAutoCalculateSignificance(false) , bOnScreen(false) , bWasOffScreenPrevTick(false) , bNeverThrottle(true)`
- L65 _public prototype_ `FAnimBudgetAllocatorComponentData(USkeletalMeshComponentBudgeted* InComponent, float InGameThreadLastTickTimeMs, int32 InStateChangeThrottle);`
- L67 _public function_ `bool operator==(const FAnimBudgetAllocatorComponentData& InOther) const`
- L74 _public member_ `TObjectPtr<USkeletalMeshComponentBudgeted> Component;` — The component that we are tracking
- L77 _public member_ `TObjectPtr<USkeletalMeshComponentBudgeted> RootPrerequisite;` — The root skeletal mesh component of this component's prerequisite graph, used for synchronizing ticks
- L80 _public member_ `float Significance;` — Significance of this component
- L83 _public member_ `float AccumulatedDeltaTime;` — Delta time accumulated between ticks we miss
- L86 _public member_ `float GameThreadLastTickTimeMs;` — Tracks the time in MS it took to tick this component on the game thread
- L89 _public member_ `float GameThreadLastCompletionTimeMs;` — Tracks the time in MS it took to complete this component on the game thread
- L93 _public member_ `float PrevFrameGameThreadLastCompletionTimeMs;` — Keep prev frame GameThreadLastCompletionTimeMs for debug use
- L97 _public member_ `uint32 FrameOffset;` — Frame offset used to distribute ticks
- L100 _public member_ `uint8 DesiredTickRate;` — The tick rate we calculated for this component
- L103 _public member_ `uint8 TickRate;` — The tick rate we are using for this component
- L106 _public member_ `uint8 SkippedTicks;` — The current number of skipped ticks, used for determining interpolation alpha
- L109 _public member_ `int8 StateChangeThrottle;` — Counter used to prevent state changes from happening too often
- L112 _public member_ `uint8 bTickEnabled : 1;` — Whether we ever tick
- L115 _public member_ `uint8 bAlwaysTick : 1;` — Whether we should never skip the tick of this component, e.g. for player pawns
- L118 _public member_ `uint8 bTickEvenIfNotRendered : 1;` — Whether we should always try to tick this component offscreen, e.g. for meshes with important audio notifies
- L121 _public member_ `uint8 bInterpolate : 1;` — Whether we should interpolate
- L124 _public member_ `uint8 bReducedWork : 1;` — Whether this component is running 'reduced work'
- L127 _public member_ `uint8 bReducedWorkDueToOffscreen : 1;` — Whether this component is running 'reduced work' due to being non-rendered offscreen
- L130 _public member_ `uint8 bAllowReducedWork : 1;` — Whether this component allows 'reduced work'
- L133 _public member_ `uint8 bAutoCalculateSignificance : 1;` — Whether this component auto-calculates its significance (as opposed to it being pushed via SetComponentSignificance()
- L136 _public member_ `uint8 bOnScreen : 1;` — Whether this component is on screen. This is updated each tick.
- L139 _public member_ `uint8 bWasOffScreenPrevTick : 1;` — Whether this component was off screen prev tick.
- L142 _public member_ `uint8 bNeverThrottle : 1;` — Whether we are allowing interpolation on this component (i.e. we dont just reduce tick rate). This is intended to allow higher-quality animation.

#### class `FAnimationBudgetAllocator`  
`class FAnimationBudgetAllocator : public IAnimationBudgetAllocator, public FGCObject`  
_L145-339_
- inherits: `IAnimationBudgetAllocator,FGCObject`
- L148 _public prototype_ `FAnimationBudgetAllocator(UWorld* InWorld);`
- L149 _public prototype_ `~FAnimationBudgetAllocator();`
- L152 _public prototype_ `virtual void RegisterComponent(USkeletalMeshComponentBudgeted* InComponent) override;` — IAnimationBudgetAllocator interface
- L153 _public prototype_ `virtual void UnregisterComponent(USkeletalMeshComponentBudgeted* InComponent) override;`
- L154 _public prototype_ `virtual void UnregisterAllComponents() override;`
- L155 _public prototype_ `virtual void UpdateComponentTickPrerequsites(USkeletalMeshComponentBudgeted* InComponent) override;`
- L156 _public prototype_ `virtual void SetComponentSignificance(USkeletalMeshComponentBudgeted* Component, float Significance, bool bNeverSkip = false, bool bTickEvenIfNotRendered = false, bool bAllowReducedWork = true, bool bForceInterpolate = false) override;`
- L157 _public prototype_ `virtual void SetComponentTickEnabled(USkeletalMeshComponentBudgeted* Component, bool bShouldTick) override;`
- L158 _public prototype_ `virtual bool IsComponentTickEnabled(USkeletalMeshComponentBudgeted* Component) const override;`
- L159 _public prototype_ `virtual void SetGameThreadLastTickTimeMs(int32 InManagerHandle, float InGameThreadLastTickTimeMs) override;`
- L160 _public prototype_ `virtual void SetGameThreadLastCompletionTimeMs(int32 InManagerHandle, float InGameThreadLastCompletionTimeMs) override;`
- L161 _public prototype_ `virtual void SetIsRunningReducedWork(USkeletalMeshComponentBudgeted* Component, bool bInReducedWork) override;`
- L162 _public prototype_ `virtual void Update(float DeltaSeconds) override;`
- L163 _public prototype_ `virtual void SetEnabled(bool bInEnabled) override;`
- L164 _public prototype_ `virtual bool GetEnabled() const override;`
- L165 _public prototype_ `virtual void SetParameters(const FAnimationBudgetAllocatorParameters& InParameters) override;`
- L166 _public prototype_ `virtual void ForceNextTickThisFrame(USkeletalMeshComponentBudgeted* Component) override;`
- L167 _public prototype_ `virtual void AddExternalAnimationTimeSpentThisFrame(float TimeSpent) override;`
- L170 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L171 _public function_ `virtual FString GetReferencerName() const override`
- L177 _public prototype_ `void RegisterComponentDeferred(USkeletalMeshComponentBudgeted* InComponent);` — Registers a component for deferred registration (post begin play)
- L180 _public function_ `bool HasBegunPlay() const` — Checks whether this allocator's world has begun play
- L184 _protected prototype_ `void OnWorldPreActorTick(UWorld* InWorld, ELevelTick InLevelTick, float InDeltaSeconds);` — We tick before all actors in the world using this delegate
- L187 _protected prototype_ `void RemoveDeadComponents();` — Remove dead components backwards, readjusting indices
- L190 _protected prototype_ `void HandleGarbageCollectStarted();` — Clean up dead components at the start of GC, but before Lock.
- L193 _protected prototype_ `void HandlePostGarbageCollect();` — Clean up dead components post GC
- L196 _protected prototype_ `void HandleWorldBeginPlay();` — Handle when a world begins play
- L199 _protected prototype_ `void QueueSortedComponentIndices(float InDeltaSeconds);` — First pass of the Update(). Queues component indices that want to tick into AllSortedComponentData.
- L205 _protected prototype_ `int32 CalculateWorkDistributionAndQueue(float InDeltaSeconds, float& OutAverageTickRate);` — Second pass of the Update(). Looks at average time taken per unit of work (i.e. a component tick & completion task) and determines appropriate tick rates to suit the requested time budget.
- L208 _protected prototype_ `void RemoveHelper(int32 Index, USkeletalMeshComponentBudgeted* InExpectedComponent);` — Helper function for keeping handle indices in sync
- L211 _protected prototype_ `void TickEnableHelper(USkeletalMeshComponent* InComponent, bool bInEnable);` — Helper function to enable/disable ticks
- L214 _protected prototype_ `void SetParametersFromCVars();` — Initializes internal parameters from CVars.
- L217 _protected prototype_ `void CheckAndPropagateUpdateStatusChange();` — check for change in update status and set component external tick states to match
- L221 _protected prototype_ `void OnHUDPostRender(AHUD* HUD, UCanvas* Canvas);` — Debug support function
- L226 _protected member_ `FAnimationBudgetAllocatorParameters Parameters;` — All of the parameters we use
- L229 _protected member_ `TObjectPtr<UWorld> World;` — World we are linked to
- L232 _protected member_ `TArray<FAnimBudgetAllocatorComponentData> AllComponentData;` — All component data
- L239 _protected member_ `TArray<int32> AllSortedComponentData;` — All currently tickable component indices sorted by significance, updated each tick. Note that this array is not managed, so components can be deleted underneath it. Therefore usage outside of Tick() is not recommended.
- L242 _protected member_ `TArray<FAnimBudgetAllocatorComponentData*> AllSortedComponentDataDebug;`
- L246 _protected member_ `TArray<int32> DisabledTickingComponentDataForDebugDraw;`
- L247 _protected member_ `TArray<int32> NonRenderedNotSignificantComponentDataForDebugDraw;`
- L251 _protected member_ `TArray<int32> ReducedWorkComponentData;` — All components that have reduced work that might want to tick (and hence might not want to do reduced work)
- L254 _protected member_ `TArray<int32> DisallowedReducedWorkComponentData;` — All components that have reduced work that must now tick
- L257 _protected member_ `TArray<int32> NonRenderedComponentData;` — All non-rendered components we might tick
- L260 _protected member_ `TArray<USkeletalMeshComponentBudgeted*> DeferredRegistrations;` — Component registrations for our world before beginplay was called
- L264 _protected member_ `TArray<FVector2D> DebugTimes;` — Recorded debug times
- L265 _protected member_ `TArray<FVector2D> DebugTimesSmoothed;`
- L269 _protected member_ `float AverageWorkUnitTimeMs;` — Average time for a work unit in milliseconds (smoothed). Updated each tick.
- L272 _protected member_ `int32 NumComponentsToNotSkip;` — The number of components that we need to tick very frame. Updated each tick.
- L275 _protected member_ `int32 NumComponentsToNotThrottle;` — The number of components that we should not throttle (i.e. interpolate). Updated each tick.
- L278 _protected member_ `float TotalEstimatedTickTimeMs;` — The total estimated tick time for queued ticks this frame. Updated each tick.
- L281 _protected member_ `float NumWorkUnitsForAverage;` — The number of work units queued for tick this frame, used to calculate target AverageWorkUnitTimeMs. Updated each tick
- L284 _protected member_ `float SmoothedBudgetPressure;` — Budget pressure value, smoothed to reduce noise in 'reduced work' calculations
- L288 _protected member_ `float DebugTotalTime;` — Track total time this tick for debug display
- L291 _protected member_ `float CurrentDebugTimeDisplay;` — Display time for debug graph
- L294 _protected member_ `float DebugSmoothedTotalTime;` — Display scale for debug graph
- L298 _protected member_ `int32 ReducedComponentWorkCounter;` — Throttle counter for delaying reduced work
- L301 _protected member_ `FDelegateHandle GarbageCollectStartedHandle;` — Handle used to track start of garbage collection
- L304 _protected member_ `FDelegateHandle PostGarbageCollectHandle;` — Handle used to track post-garbage collection
- L307 _protected member_ `FDelegateHandle OnWorldPreActorTickHandle;` — Handle used for ticking
- L310 _protected member_ `FDelegateHandle OnCVarParametersChangedHandle;` — Handle used for CVar parameter changes
- L313 _protected member_ `FDelegateHandle OnHUDPostRenderHandle;` — Handle used for debug drawing
- L316 _protected member_ `FDelegateHandle OnWorldBeginPlayHandle;` — Handle used to handle world begin play
- L319 _protected member_ `uint32 CurrentFrameOffset;` — Offset used to distribute component ticks
- L322 _protected member_ `bool bEnabled;` — Local enabled flag that allows us to disable even if the CVar is enabled
- L325 _protected member_ `static bool bCachedEnabled;` — Cached enabled flag that is copied from the CVar each tick
- L328 _protected member_ `bool bCurrentlyUpdating;` — Flag to indicate allocator is currently updating (ie cvar enabled and local enabled both true)
- L331 _protected member_ `bool bHasBegunPlay;` — Flag to indidcate whether begin play has been called for this allocator's world
- L334 _protected member_ `float ExternalAnimationTimeSpent = 0.0f;` — External animation time spent by sources not captured in ABA but that should reduce avaialbe ABA budget for the frame
- L337 _protected member_ `bool bEmergencyReducedWorkActive = false;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API ANIMATIONBUDGETALLOCATOR_API`
- L13 _delegate_ `DECLARE_STATS_GROUP(TEXT("Animation Budget Allocator"), STATGROUP_AnimationBudgetAll`
- L15 _macro_ `#define WITH_TICK_DEBUG 0`
- L18 _macro_ `#define WITH_EXTRA_BUDGET_CSV_STATS WITH_TICK_DEBUG` — Enable this define to output more dense CSV stats about the budgeter
- L21 _macro_ `#define BUDGET_CSV_STAT(Category,StatName,Value,Op) CSV_CUSTOM_STAT(Category,StatName,Value,Op)`
- L23 _macro_ `#define BUDGET_CSV_STAT(Category,StatName,Value,Op)`

### `Plugins/Runtime/AnimationBudgetAllocator/Source/AnimationBudgetAllocator/Private/AnimationBudgetAllocatorCVars.h` (Private)


#### Free symbols / members of external scopes

- L10 _externvar_ `extern int32 GAnimationBudgetEnabled;` — Enabled/disabled flag
- L12 _externvar_ `extern int32 GAnimationBudgetMaintainReduceWorkWhenOffScreen;`
- L14 _externvar_ `extern int32 GAnimationBudgetComponentsWithZeroSigAreNonRendered;`
- L16 _externvar_ `extern int32 GAnimationBudgetForceTickWhenComponentExitsOffScreen;`
- L19 _externvar_ `extern int32 GAnimationBudgetEmergencyReduceWorkDisabled;` — Controls whether the emergency reduce work option is disabled.
- L24 _externvar_ `extern int32 GAnimationBudgetDebugEnabled;` — Debug rendering flag
- L27 _externvar_ `extern int32 GAnimationBudgetDebugDisableGraph;` — Controls whether debug rendering of perf graph is disabled or not.
- L30 _externvar_ `extern int32 GAnimationBudgetDebugShowAddresses;` — Controls whether debug rendering shows addresses of component data for debugging
- L33 _externvar_ `extern int32 GAnimationBudgetDebugVerboseActive;` — Controls whether debug rendering is in verbose mode and shows a lot of extra information
- L36 _externvar_ `extern int32 GAnimationBudgetDebugVerboseShowNames;` — In Verbose Mode - Controls whether debug rendering shows names of components for debugging.
- L39 _externvar_ `extern int32 GAnimationBudgetDebugVerboseShowActorNames;` — In Verbose Mode - Controls whether debug rendering shows actor names for debugging.
- L42 _externvar_ `extern int32 GAnimationBudgetDebugVerboseShowNonTicking;` — In Verbose Mode - Controls whether debug rendering shows non ticking component datas.
- L45 _externvar_ `extern int32 GAnimationBudgetDebugVerboseOnCanvas;` — In Verbose Mode - Controls whether debug rendering should be shown as 2D on canvas or not.
- L52 _externvar_ `extern int32 GAnimationBudgetDebugForce;` — Parameters used to force state for debugging
- L53 _externvar_ `extern int32 GAnimationBudgetDebugForceExcludeAlwaysTicked;`
- L54 _externvar_ `extern int32 GAnimationBudgetDebugForceRate;`
- L55 _externvar_ `extern int32 GAnimationBudgetDebugForceInterpolation;`
- L56 _externvar_ `extern int32 GAnimationBudgetDebugForceReducedWork;`
- L61 _externvar_ `extern FAnimationBudgetAllocatorParameters GBudgetParameters;` — CVar-driven parameter block
- L64 _externvar_ `extern FSimpleMulticastDelegate GOnCVarParametersChanged;` — Delegate broadcast when parameter block changes

### `Plugins/Runtime/AnimationBudgetAllocator/Source/AnimationBudgetAllocator/Private/AnimationBudgetAllocatorModule.h` (Private)


#### class `FAnimationBudgetAllocatorModule`  
`class FAnimationBudgetAllocatorModule : public IAnimationBudgetAllocatorModule, public FGCObject`  
_L13-43_
- inherits: `IAnimationBudgetAllocatorModule,FGCObject`
- L17 _public prototype_ `virtual IAnimationBudgetAllocator* GetBudgetAllocatorForWorld(UWorld* World) override;` — IAnimationBudgetAllocatorModule interface
- L20 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface interface
- L21 _public prototype_ `virtual void ShutdownModule() override;`
- L24 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L25 _public function_ `virtual FString GetReferencerName() const override`
- L32 _private prototype_ `void HandleWorldInit(UWorld* World, const UWorld::InitializationValues IVS);` — Handle world initialization
- L35 _private prototype_ `void HandleWorldCleanup(UWorld* World, bool bSessionEnded, bool bCleanupResources);` — Handle world cleanup
- L38 _private member_ `FDelegateHandle PreWorldInitializationHandle;` — Delegate handles for hooking into UWorld lifetimes
- L39 _private member_ `FDelegateHandle PostWorldCleanupHandle;`
- L42 _private member_ `TMap<TObjectPtr<UWorld>, FAnimationBudgetAllocator*> WorldAnimationBudgetAllocators;` — Map of world->budgeter

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API ANIMATIONBUDGETALLOCATOR_API`

### `Plugins/Runtime/AnimationBudgetAllocator/Source/AnimationBudgetAllocator/Private/AnimationBudgetBlueprintLibrary.h` (Private)


#### class `UAnimationBudgetBlueprintLibrary`  
`class UAnimationBudgetBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L14-31_
- reflection: `UCLASS(meta = (ScriptName = "AnimationBudget"))`
- inherits: `UBlueprintFunctionLibrary`
- desc: Function library to expose the budget allocator to Blueprints
- L23 _private prototype_ `static void EnableAnimationBudget(UObject* WorldContextObject, bool bEnabled);` — `UFUNCTION(BlueprintCallable, Category = "Animation Budget", meta=(WorldContext="WorldContextObject"))` — Enable/disable the animation budgeting system. Note that the system can also be disabled globally via CVar, which overrides this setting.
- L30 _private prototype_ `static void SetAnimationBudgetParameters(UObject* WorldContextObject, const FAnimationBudgetAllocatorParameters& InParameters);` — `UFUNCTION(BlueprintCallable, Category = "Animation Budget", meta=(WorldContext="WorldContextObject"))` — Set the parameters of the animation budgeting system. Note that the parameters can also be set globally via CVar.

### `Plugins/Runtime/AnimationBudgetAllocator/Source/AnimationBudgetAllocator/Public/AnimationBudgetAllocatorParameters.h` (Public)


#### struct `FAnimationBudgetAllocatorParameters`  
`struct FAnimationBudgetAllocatorParameters`  
_L9-167_
- reflection: `USTRUCT(BlueprintType)`
- desc: Parameter block used to control the behavior of the budget allocator
- L19 _public member_ `float BudgetInMs = 1.0f;` — `UPROPERTY(BlueprintReadWrite, Category = "Parameters")` — Values > 0.1. The time in milliseconds that we allocate for skeletal mesh work to be performed. When overbudget various other parameters come into play, such as AlwaysTickFalloffAggression and InterpolationFalloffAggression.
- L27 _public member_ `float MinQuality = 0.0f;` — `UPROPERTY(BlueprintReadWrite, Category = "Parameters")` — Values [0.0, 1.0]. The minimum quality metric allowed. Quality is determined simply by NumComponentsTickingThisFrame / NumComponentsThatWeNeedToTick. If this is anything other than 0.0 then we can potentially go over our time budget.
- L34 _public member_ `int32 MaxTickRate = 10;` — `UPROPERTY(BlueprintReadWrite, Category = "Parameters")` — Values >= 1. The maximum tick rate we allow. If this is set then we can potentially go over budget, but keep quality of individual meshes to a reasonable level.
- L41 _public member_ `float WorkUnitSmoothingSpeed = 5.0f;` — `UPROPERTY(BlueprintReadWrite, Category = "Parameters")` — Values > 0.1. The speed at which the average work unit converges on the measured amount.
- L49 _public member_ `float AlwaysTickFalloffAggression = 0.8f;` — `UPROPERTY(BlueprintReadWrite, Category = "Parameters")` — Range [0.1, 0.9]. Controls the rate at which 'always ticked' components falloff under load. Higher values mean that we reduce the number of always ticking components by a larger amount when the allocated time budget is exceeded.
- L58 _public member_ `float InterpolationFalloffAggression = 0.4f;` — `UPROPERTY(BlueprintReadWrite, Category = "Parameters")` — Range [0.1, 0.9]. Controls the rate at which interpolated components falloff under load. Higher values mean that we reduce the number of interpolated components by a larger amount when the allocated time budget is exceeded. Components are only interpolated when the time budget is exceeded.
- L65 _public member_ `int32 InterpolationMaxRate = 6;` — `UPROPERTY(BlueprintReadWrite, Category = "Parameters")` — Values > 1. Controls the rate at which ticks happen when interpolating.
- L72 _public member_ `int32 MaxInterpolatedComponents = 16;` — `UPROPERTY(BlueprintReadWrite, Category = "Parameters")` — Range >= 0. Max number of components to interpolate before we start throttling.
- L79 _public member_ `float InterpolationTickMultiplier = 0.75f;` — `UPROPERTY(BlueprintReadWrite, Category = "Parameters")` — Range [0.1, 0.9]. Controls the expected value an amortized interpolated tick will take compared to a 'normal' tick.
- L87 _public member_ `float InitialEstimatedWorkUnitTimeMs = 0.08f;` — `UPROPERTY(BlueprintReadWrite, Category = "Parameters")` — Values > 0.0. Controls the time in milliseconds we expect, on average, for a skeletal mesh component to execute. The value only applies for the first tick of a component, after which we use the real time the tick takes.
- L94 _public member_ `int32 MaxTickedOffsreenComponents = 4;` — `UPROPERTY(BlueprintReadWrite, Category = "Parameters")` — Values >= 1 The maximum number of offscreen components we tick (most significant first)
- L101 _public member_ `int32 StateChangeThrottleInFrames = 30;` — `UPROPERTY(BlueprintReadWrite, Category = "Parameters")` — Range [1, 128] Prevents throttle values from changing too often due to system and load noise.
- L108 _public member_ `float BudgetFactorBeforeReducedWork = 1.5f;` — `UPROPERTY(BlueprintReadWrite, Category = "Parameters")` — Range > 1 Reduced work will be delayed until budget pressure goes over this amount.
- L115 _public member_ `float BudgetFactorBeforeReducedWorkEpsilon = 0.25f;` — `UPROPERTY(BlueprintReadWrite, Category = "Parameters")` — Range > 0.0. Increased work will be delayed until budget pressure goes under BudgetFactorBeforeReducedWork minus this amount.
- L122 _public member_ `float BudgetPressureSmoothingSpeed = 3.0f;` — `UPROPERTY(BlueprintReadWrite, Category = "Parameters")` — Range > 0.0. How much to smooth the budget pressure value used to throttle reduced work.
- L129 _public member_ `int32 ReducedWorkThrottleMinInFrames = 2;` — `UPROPERTY(BlueprintReadWrite, Category = "Parameters")` — Range [1, 255]. Prevents reduced work from changing too often due to system and load noise. Min value used when over budget pressure (i.e. aggressive reduction).
- L136 _public member_ `int32 ReducedWorkThrottleMaxInFrames = 20;` — `UPROPERTY(BlueprintReadWrite, Category = "Parameters")` — Range [1, 255]. Prevents reduced work from changing too often due to system and load noise. Max value used when under budget pressure.
- L143 _public member_ `float BudgetFactorBeforeAggressiveReducedWork = 2.0f;` — `UPROPERTY(BlueprintReadWrite, Category = "Parameters")` — Range > 1. Reduced work will be applied more rapidly when budget pressure goes over this amount.
- L150 _public member_ `int32 ReducedWorkThrottleMaxPerFrame = 4;` — `UPROPERTY(BlueprintReadWrite, Category = "Parameters")` — Range [1, 255]. Controls the max number of components that are switched to/from reduced work per tick.
- L157 _public member_ `float BudgetPressureBeforeEmergencyReducedWork = 2.5f;` — `UPROPERTY(BlueprintReadWrite, Category = "Parameters")` — Range > 0.0. Controls the budget pressure where emergency reduced work (applied to all components except those that are bAlwaysTick).
- L165 _public member_ `float AutoCalculatedSignificanceMaxDistance = 30000.0f;` — `UPROPERTY(BlueprintReadWrite, Category = "Parameters")` — Range > 1.0. Controls the distance at which auto-calculated significance for budgeted components bottoms out. Components within the distance 1 -> Max will have significance mapped 1 -> 0, outside of MaxDistance significance will be zero.
- L166 _public member_ `float AutoCalculatedSignificanceMaxDistanceSqr = 30000.0f * 30000.0f;`

### `Plugins/Runtime/AnimationBudgetAllocator/Source/AnimationBudgetAllocator/Public/IAnimationBudgetAllocator.h` (Public)


#### class `IAnimationBudgetAllocator`  
`class IAnimationBudgetAllocator`  
_L14-89_
- desc: Dynamically manages skeletal mesh component tick rates to try to maintain a specified budget.
- L18 _public prototype_ `static IAnimationBudgetAllocator* Get(UWorld* InWorld);` — Get the budgeter for the specified world
- L27 _public prototype_ `virtual void RegisterComponent(USkeletalMeshComponentBudgeted* InComponent) = 0;` — Register a component with the budgeter system. If the component is already registered this function does nothing. Once this is called: - Default tick function will be disabled - URO will be disabled - Parallel anim tasks will be re-routed to the budgeter
- L36 _public prototype_ `virtual void UnregisterComponent(USkeletalMeshComponentBudgeted* InComponent) = 0;` — Unregister a component from the budgeter system. If the component is not registered this function does nothing. Once this is called: - Default tick function will be re-enabled - URO will be re-enabled - Parallel anim tasks will be re-routed back to internal functions
- L41 _public prototype_ `virtual void UnregisterAllComponents() = 0;` — Calls UnregisterComponent on all components currently registered with the allocator.
- L46 _public prototype_ `virtual void UpdateComponentTickPrerequsites(USkeletalMeshComponentBudgeted* InComponent) = 0;` — Update the prerequisites of this component. Should be called when prerequisites may have changed externally.
- L52 _public prototype_ `virtual void SetComponentSignificance(USkeletalMeshComponentBudgeted* Component, float Significance, bool bNeverSkip = false, bool bTickEvenIfNotRendered = false, bool bAllowReducedWork = true, bool bForceInterpolate = false) = 0;` — Set the significance and other flags for the specified component. This information is used to dynamically control the tick rate of the component.
- L55 _public prototype_ `virtual void SetComponentTickEnabled(USkeletalMeshComponentBudgeted* Component, bool bShouldTick) = 0;` — Set the specified component to tick or not. If the budgeter is disabled then this calls Component->SetComponentTickEnabled(bShouldTick).
- L58 _public prototype_ `virtual bool IsComponentTickEnabled(USkeletalMeshComponentBudgeted* Component) const = 0;` — Get whether the specified component is set to tick or not
- L61 _public prototype_ `virtual void SetIsRunningReducedWork(USkeletalMeshComponentBudgeted* Component, bool bInReducedWork) = 0;` — Inform that we reduced work for a component
- L64 _public prototype_ `virtual void SetGameThreadLastTickTimeMs(int32 InManagerHandle, float InGameThreadLastTickTimeMs) = 0;` — Set the tick time
- L67 _public prototype_ `virtual void SetGameThreadLastCompletionTimeMs(int32 InManagerHandle, float InGameThreadLastCompletionTimeMs) = 0;` — Set the completion task time
- L70 _public prototype_ `virtual void Update(float DeltaSeconds) = 0;` — Tick the system per-frame
- L73 _public prototype_ `virtual void SetEnabled(bool bInEnabled) = 0;` — Set whether this budget allocator is enabled
- L76 _public prototype_ `virtual bool GetEnabled() const = 0;` — Get whether this budget allocator is enabled
- L79 _public prototype_ `virtual void SetParameters(const FAnimationBudgetAllocatorParameters& InParameters) = 0;` — Set the various parameters
- L82 _public prototype_ `virtual void ForceNextTickThisFrame(USkeletalMeshComponentBudgeted* Component) = 0;` — Force component to tick this frame regardless of tick rate
- L88 _public prototype_ `virtual void AddExternalAnimationTimeSpentThisFrame(float TimeSpent) = 0;` — Add external time spent on animation that should come out of the Animation Budget but is not accounted for in the ABA update. TimeSpent is accumulated and spent each frame, it is reset to 0 each time it is used.

### `Plugins/Runtime/AnimationBudgetAllocator/Source/AnimationBudgetAllocator/Public/IAnimationBudgetAllocatorModule.h` (Public)


#### class `IAnimationBudgetAllocatorModule`  
`class IAnimationBudgetAllocatorModule : public FDefaultGameModuleImpl`  
_L11-26_
- inherits: `FDefaultGameModuleImpl`
- L18 _public prototype_ `virtual IAnimationBudgetAllocator* GetBudgetAllocatorForWorld(UWorld* World) = 0;` — Get a budgeter for a specific world. Adds it if it is not already created. Budgeters are only created for game worlds.
- L21 _public function_ `inline static IAnimationBudgetAllocator* Get(UWorld* World)` — Get a budgeter for a specific world. Fairly expensive as it calls into module manager and performs a map lookup.

### `Plugins/Runtime/AnimationBudgetAllocator/Source/AnimationBudgetAllocator/Public/SkeletalMeshComponentBudgeted.h` (Public)


#### class `USkeletalMeshComponentBudgeted`  
`class USkeletalMeshComponentBudgeted : public USkeletalMeshComponent`  
_L23-112_
- reflection: `UCLASS(MinimalAPI, meta=(BlueprintSpawnableComponent))`
- inherits: `USkeletalMeshComponent`
- desc: A skeletal mesh component that has its tick rate governed by a global animation budget
- L30 _public prototype_ `USkeletalMeshComponentBudgeted(const FObjectInitializer& ObjectInitializer);`
- L33 _public prototype_ `virtual void SetComponentTickEnabled(bool bEnabled) override;` — UActorComponent interface
- L36 _public prototype_ `void SetComponentSignificance(float Significance, bool bNeverSkip = false, bool bTickEvenIfNotRendered = false, bool bAllowReducedWork = true, bool bForceInterpolate = false);` — Updates significance budget if this component has been registered with a AnimationBudgetAllocator
- L40 _public function_ `void SetAutoRegisterWithBudgetAllocator(bool bInAutoRegisterWithBudgetAllocator)` — `UFUNCTION(BlueprintSetter)` — Set this component to automatically register with the budget allocator
- L43 _public function_ `void SetAutoCalculateSignificance(bool bInAutoCalculateSignificance)` — Set this component to automatically calculate its significance
- L46 _public function_ `bool GetAutoCalculateSignificance() const` — Check whether this component auto-calculates its significance
- L49 _public function_ `FOnReduceWork& OnReduceWork()` — Get delegate called to increase/decrease the amount of work a component performs
- L52 _public function_ `static FOnCalculateSignificance& OnCalculateSignificance()` — Get delegate called to calculate significance if bAutoCalculateSignificance = true
- L54 _public function_ `bool GetShouldUseActorRenderedFlag() const`
- L56 _public function_ `void SetShouldUseActorRenderedFlag(bool value)`
- L61 _protected prototype_ `virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;` — USkeletalMeshComponent interface
- L62 _protected prototype_ `virtual void CompleteParallelAnimationEvaluation(bool bDoPostAnimEvaluation) override;`
- L65 _protected prototype_ `virtual void BeginPlay() override;` — UActorComponent interface
- L66 _protected prototype_ `virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;`
- L71 _private function_ `int32 GetAnimationBudgetHandle() const` — Get the handle used to identify this component to the allocator
- L74 _private function_ `void SetAnimationBudgetHandle(int32 InHandle)` — Set the handle used to identify this component to the allocator
- L77 _private function_ `void SetAnimationBudgetAllocator(IAnimationBudgetAllocator* InAnimationBudgetAllocator)` — Set the budget allocator that is tracking us
- L80 _private prototype_ `void HandleWorldBeginPlay();` — Handles self-registration after actors have begun play
- L83 _private prototype_ `float GetDefaultSignificance() const;` — Gets the default significance value based on distance
- L87 _private member_ `FOnReduceWork OnReduceWorkDelegate;` — Delegate called to increase/decrease the amount of work a component performs
- L90 _private member_ `static FOnCalculateSignificance OnCalculateSignificanceDelegate;` — Delegate called to calculate significance if bAutoCalculateSignificance = true
- L93 _private member_ `IAnimationBudgetAllocator* AnimationBudgetAllocator = nullptr;` — Owning animation budget allocator
- L96 _private member_ `int32 AnimationBudgetHandle = INDEX_NONE;` — Handle used for identification
- L99 _private member_ `float AutoCalculatedSignificance = 1.0f;` — Cached calculated significance
- L103 _private member_ `uint8 bAutoRegisterWithBudgetAllocator : 1;` — `UPROPERTY(EditAnywhere, BlueprintSetter=SetAutoRegisterWithBudgetAllocator, Category = Budgeting)` — Whether this component should automatically register with the budget allocator in OnRegister/OnUnregister
- L107 _private member_ `uint8 bAutoCalculateSignificance : 1;` — `UPROPERTY(EditAnywhere, Category = Budgeting)` — Whether this component should automatically calculate its significance (rather than some external system pushing the significance to it)
- L111 _private member_ `uint8 bShouldUseActorRenderedFlag : 1;` — `UPROPERTY(EditAnywhere, Category = Budgeting, AdvancedDisplay)` — Whether this component should use its owning actor's rendered state to determine visibility. If this is not set then the component's visibility will be used

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ANIMATIONBUDGETALLOCATOR_API`
- L10 _namespace_ `namespace EEndPlayReason`
- L16 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnReduceWork, USkeletalMeshComponentBudgeted* , bool );` — Delegate called to increase/decrease the amount of work a component performs
- L16 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnReduceWork, USkeletalMeshComponentBudgeted* , bool );` — Delegate called to increase/decrease the amount of work a component performs
- L19 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(float, FOnCalculateSignificance, USkeletalMeshComponentBudgeted* );` — Delegate called to calculate significance if bAutoCalculateSignificance = true
- L19 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(float, FOnCalculateSignificance, USkeletalMeshComponentBudgeted* );` — Delegate called to calculate significance if bAutoCalculateSignificance = true
