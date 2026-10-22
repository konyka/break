# Plugins / CsvMetrics

- module root: `Plugins/WorldMetrics/Source/CsvMetrics`
- headers: 2; symbols: 23
- symbol kinds: class=2, function=1, member=6, prototype=14
- PrivateDependencyModuleNames: Core, Engine
- PublicDependencyModuleNames: CoreUObject, WorldMetricsCore

### `Plugins/WorldMetrics/Source/CsvMetrics/Public/CsvActorCountMetric.h` (Public)


#### class `UCsvActorCountMetric`  
`class UCsvActorCountMetric : public UWorldMetricInterface, public IWorldMetricsActorTrackerSubscriber`  
_L17-46_
- reflection: `UCLASS()`
- inherits: `UWorldMetricInterface,IWorldMetricsActorTrackerSubscriber`
- desc: World actor count metric This metrics provides a basic actor counter sorting the world's actors into categories. On update it writes the actor counts to CSV if the CSV profiler is available.
- L22 _private prototype_ `[[nodiscard]] virtual SIZE_T GetAllocatedSize() const override;` — UWorldMetricInterface interface.
- L24 _private function_ `[[nodiscard]] int32 NumActors() const`
- L29 _private prototype_ `[[nodiscard]] int32 NumActors(const FName& NativeClassName) const;`
- L33 _private member_ `TMap<FName, int32> ActorClassNameCounter;` — Map of Actor class names to instance counts
- L36 _private member_ `int32 TotalActorCount = 0;` — Count of total actors created
- L39 _private prototype_ `virtual void Initialize() override;` — UWorldMetricInterface interface.
- L40 _private prototype_ `virtual void Deinitialize() override;`
- L41 _private prototype_ `virtual void Update(float DeltaTimeInSeconds) override;`
- L44 _private prototype_ `virtual void OnActorRemoved(const AActor* Actor) ;` — IWorldMetricsActorTrackerSubscriber interface.
- L45 _private prototype_ `virtual void OnActorAdded(const AActor* Actor);`

### `Plugins/WorldMetrics/Source/CsvMetrics/Public/CsvMetricsSubsystem.h` (Public)


#### class `UCsvMetricsSubsystem`  
`class UCsvMetricsSubsystem final : public UWorldSubsystem`  
_L17-50_
- reflection: `UCLASS(MinimalAPI, Config = Engine, DefaultConfig)`
- inherits: `UWorldSubsystem`
- desc: Csv metrics subsystem This subsystem registers/unregisters its CSV metric collection whenever a CSV profiler capture is performed.
- L23 _public prototype_ `virtual bool ShouldCreateSubsystem(UObject* Outer) const override;`
- L24 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L25 _public prototype_ `virtual void Deinitialize() override;`
- L30 _public member_ `TArray<TSubclassOf<UWorldMetricInterface>> MetricClasses;` — `UPROPERTY(Config)` — The CSV metric collection to add/remove when a CSV profiler capture stats/ends.
- L36 _private member_ `TArray<UWorldMetricInterface*> Metrics;` — The collection of active metrics while a CSV profiler capture is running. We rely on the World Metrics Subsystem's ownership for these so we don't keep hard-references.
- L38 _private member_ `FDelegateHandle ProfileStartHandle;`
- L39 _private member_ `FDelegateHandle ProfileEndHandle;`
- L45 _private prototype_ `void BindProfilerCallbacks();` — Binds/Unbinds handles to OnCSVProfileStart and OnCSVProfileEnd in order register/unregister this system's CSV metric collection.
- L46 _private prototype_ `void UnbindProfilerCallbacks();`
- L48 _private prototype_ `void AddMetrics();`
- L49 _private prototype_ `void RemoveMetrics();`
