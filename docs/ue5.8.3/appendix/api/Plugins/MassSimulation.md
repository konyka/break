# Plugins / MassSimulation

- module root: `Plugins/Runtime/MassGameplay/Source/MassSimulation`
- headers: 3; symbols: 67
- symbol kinds: class=3, delegate=3, function=9, macro=1, member=19, prototype=32
- PrivateDependencyModuleNames: MassEntityEditor, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, Engine, MassCommon, MassCore, MassEntity, NavigationSystem

### `Plugins/Runtime/MassGameplay/Source/MassSimulation/Public/IMassSimulationModule.h` (Public)


#### class `IMassSimulationModule`  
`class IMassSimulationModule : public IModuleInterface`  
_L14-39_
- inherits: `IModuleInterface`
- desc: The public interface to this module.  In most cases, this interface is only public to sibling modules within this plugin.
- L25 _public function_ `static inline IMassSimulationModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L35 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Plugins/Runtime/MassGameplay/Source/MassSimulation/Public/MassSimulationSettings.h` (Public)


#### class `UMassSimulationSettings`  
`class UMassSimulationSettings : public UMassModuleSettings`  
_L16-49_
- reflection: `UCLASS(MinimalAPI, config = Mass, defaultconfig, DisplayName = "Mass Simulation")`
- inherits: `UMassModuleSettings`
- desc: Implements the settings for MassSimulation
- L23 _public member_ `double DesiredActorSpawningTimeSlicePerTick = 0.0015;` — `UPROPERTY(EditDefaultsOnly, Category = "Runtime", config)` — The desired budget in seconds allowed to do actor spawning per frame
- L27 _public member_ `double DesiredActorDestructionTimeSlicePerTick = 0.0005;` — `UPROPERTY(EditDefaultsOnly, Category = "Runtime", config)` — The desired budget in seconds allowed to do actor destruction per frame
- L36 _public member_ `bool bEntityCompactionEnabled = true;` — `UPROPERTY(EditDefaultsOnly, Category = "Runtime", config)` — Whether the Entity Compaction is allowed. When enabled all the archetypes will be processed on a regular basis and the entities will be moved around to optimize archetype chunk memory utilization. Note that this might not be desired if your set up results in individual chunks being often not compatible due to the number and value of chunk and shared fragments.
- L40 _public member_ `double DesiredEntityCompactionTimeSlicePerTick = 0.005;` — `UPROPERTY(EditDefaultsOnly, Category = "Runtime", config)` — The desired budget in seconds allowed to do entity compaction per frame
- L44 _public member_ `float DesiredActorFailedSpawningRetryTimeInterval = 5.0f;` — `UPROPERTY(EditDefaultsOnly, Category = "Runtime", config)` — The time to wait before retrying to spawn an actor that previously failed, default 10 seconds
- L48 _public member_ `float DesiredActorFailedSpawningRetryMoveDistance = 500.0f;` — `UPROPERTY(EditDefaultsOnly, Category = "Runtime", config)` — The distance a failed spawned actor needs to move before we retry, default 10 meters

#### Free symbols / members of external scopes

- L8 _macro_ `#define GET_MASSSIMULATION_CONFIG_VALUE(a) \`

### `Plugins/Runtime/MassGameplay/Source/MassSimulation/Public/MassSimulationSubsystem.h` (Public)


#### class `UMassSimulationSubsystem`  
`class UMassSimulationSubsystem : public UMassSubsystemBase`  
_L18-117_
- reflection: `UCLASS(config = Game, defaultconfig, MinimalAPI)`
- inherits: `UMassSubsystemBase`
- L22 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSimulationStarted, UWorld* );`
- L23 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSimulationPauseEvent, TNotNull<UMassSimulationSubsystem*> );`
- L25 _public prototype_ `UMassSimulationSubsystem(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L27 _public prototype_ `const FMassProcessingPhaseManager& GetPhaseManager() const;`
- L28 _public prototype_ `FMassProcessingPhaseManager& GetMutablePhaseManager();`
- L30 _public prototype_ `FMassProcessingPhase::FOnPhaseEvent& GetOnProcessingPhaseStarted(const EMassProcessingPhase Phase);`
- L31 _public prototype_ `FMassProcessingPhase::FOnPhaseEvent& GetOnProcessingPhaseFinished(const EMassProcessingPhase Phase);`
- L32 _public prototype_ `static FOnSimulationStarted& GetOnSimulationStarted();`
- L34 _public prototype_ `FOnSimulationPauseEvent& GetOnSimulationPaused();`
- L35 _public prototype_ `FOnSimulationPauseEvent& GetOnSimulationResumed();`
- L37 _public prototype_ `void RegisterDynamicProcessor(UMassProcessor& Processor);`
- L38 _public prototype_ `void UnregisterDynamicProcessor(UMassProcessor& Processor);`
- L40 _public prototype_ `bool IsSimulationStarted() const;`
- L43 _public prototype_ `bool IsDuringMassProcessing() const;` — @return whether hosted EntityManager is currently, actively being used for processing purposes. Equivalent to calling FMassEntityManager.IsProcessing()
- L46 _public prototype_ `static void HandleSimulationTickingEnabledCVarChange(IConsoleVariable*);` — Starts/stops simulation ticking for all worlds, based on new `mass.SimulationTickingEnabled` cvar value
- L56 _public prototype_ `bool IsSimulationPaused() const;` — Determine if this Simulation is currently paused. While paused, phases will transition as usual, but processors will not be executed. @return True if this Simulation is currently paused; else False
- L59 _public prototype_ `void PauseSimulation();` — Pause the simulation from executing processors during phase ticks
- L62 _public prototype_ `void ResumeSimulation();` — Resume the simulation executing processors during phase ticks
- L66 _protected prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;` — UWorldSubsystem BEGIN
- L67 _protected prototype_ `virtual void PostInitialize() override;`
- L68 _protected prototype_ `virtual void OnWorldBeginPlay(UWorld& InWorld) override;`
- L69 _protected prototype_ `virtual void Deinitialize() override;`
- L71 _protected prototype_ `virtual void BeginDestroy() override;` — UWorldSubsystem END
- L73 _protected prototype_ `void RebuildTickPipeline();`
- L75 _protected prototype_ `void StartSimulation(UWorld& InWorld);`
- L76 _protected prototype_ `void StopSimulation();`
- L78 _protected prototype_ `void OnProcessingPhaseStarted(const float DeltaSeconds, const EMassProcessingPhase Phase) const;`
- L81 _protected prototype_ `void OnPieBegin(const bool bIsSimulation);`
- L82 _protected prototype_ `void OnPieEnded(const bool bIsSimulation);`
- L83 _protected prototype_ `void OnMassEntitySettingsChange(const FPropertyChangedEvent& PropertyChangedEvent);`
- L87 _protected prototype_ `void ReleaseEventHandles();` — Called when it's time to clean up all the delegate handles. Override OnReleasingEventHandles to add more handles cleanup
- L90 _protected function_ `virtual void OnReleasingEventHandles()` — Override to add more handle cleanup. Will get automatically called by ReleaseEventHandles
- L94 _protected member_ `TSharedPtr<FMassEntityManager> EntityManager;`
- L96 _protected member_ `TSharedRef<FMassProcessingPhaseManager> PhaseManager;`
- L98 _protected member_ `static FOnSimulationStarted OnSimulationStarted;`
- L100 _protected member_ `FOnSimulationPauseEvent OnSimulationPaused;`
- L101 _protected member_ `FOnSimulationPauseEvent OnSimulationResumed;`
- L104 _protected member_ `FMassRuntimePipeline RuntimePipeline;` — `UPROPERTY()`
- L106 _protected member_ `float CurrentDeltaSeconds = 0.f;`
- L107 _protected member_ `bool bTickInProgress = false;`
- L108 _protected member_ `bool bSimulationStarted = false;`
- L109 _protected member_ `bool bSimulationPaused = false;`
- L112 _protected member_ `FDelegateHandle PieBeginEventHandle;`
- L113 _protected member_ `FDelegateHandle PieEndedEventHandle;`
- L115 _protected member_ `FDelegateHandle MassEntitySettingsChangeHandle;`
- L122 _function_ `inline UMassSimulationSubsystem::FOnSimulationPauseEvent& UMassSimulationSubsystem::GetOnSimulationPaused()`
- L127 _function_ `inline UMassSimulationSubsystem::FOnSimulationPauseEvent& UMassSimulationSubsystem::GetOnSimulationResumed()`
- L132 _function_ `inline bool UMassSimulationSubsystem::IsSimulationPaused() const`
- L137 _function_ `inline const FMassProcessingPhaseManager& UMassSimulationSubsystem::GetPhaseManager() const`
- L142 _function_ `inline FMassProcessingPhaseManager& UMassSimulationSubsystem::GetMutablePhaseManager()`
- L147 _function_ `inline bool UMassSimulationSubsystem::IsSimulationStarted() const`

#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMassSim, Log, All);`
- L15 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMassSim, Log, All);`
- L22 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSimulationStarted, UWorld* );`
- L23 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSimulationPauseEvent, TNotNull<UMassSimulationSubsystem*> );`
