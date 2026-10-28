# Plugins / WorldMetricsCore

- module root: `Plugins/WorldMetrics/Source/WorldMetricsCore`
- headers: 7; symbols: 121
- symbol kinds: class=6, function=28, member=17, prototype=67, struct=2, typedef=1
- PrivateDependencyModuleNames: Core, Engine
- PublicDependencyModuleNames: CoreUObject

### `Plugins/WorldMetrics/Source/WorldMetricsCore/Public/WorldMetricCollection.h` (Public)


#### struct `FWorldMetricCollection`  
`struct FWorldMetricCollection`  
_L27-290_
- reflection: `USTRUCT()`
- desc: World metric's collection A class representing a collection of world metrics. This class allows instantiating and running an arbitrary set of metrics together. The collection observes one instance of per metric class and depends on the World Metric's Subsystem to run the metrics. For this reason, the collection requires initialization. Users are responsible for ensuring both their lifetime and that of the World Metric's Subsystem in their world object.
- L32 _public prototype_ `FWorldMetricCollection() = default;`
- L33 _public prototype_ `~FWorldMetricCollection();`
- L35 _public function_ `[[nodiscard]] const UWorldMetricInterface* operator[](int32 Index) const`
- L40 _public function_ `[[nodiscard]] UWorldMetricInterface* operator[](int32 Index)`
- L49 _public prototype_ `void Initialize(UObject* InOuter);` — Initializes the collection. Initializing a container with a valid object resets the current collection. @param InOuter: the object that must provide a valid World Metrics Subsystem through its world object.
- L58 _public prototype_ `bool Enable(bool bEnable);` — Enables or disables the collection. When enabled, the collection adds all contained metrics to the World Metric Subsystem. When disabled, all contained metrics are removed from it. @param bEnable True for enabling the collection and false otherwise. @return True if the enable state was changed to reflect the desired state.
- L63 _public function_ `[[nodiscard]] bool IsEnabled() const` — @return True if the collection is enabled, and thus the contained metrics are running, or false otherwise.
- L74 _public prototype_ `[[nodiscard]] UWorldMetricInterface* Get( const TSubclassOf<UWorldMetricInterface>& InMetricClass) const;` — Gets the metric instance from the parameter class if it has been previously added. @param InMetricClass The class of the metric to be retrieved. @return A valid pointer to the metric if found, and nullptr otherwise.
- L86 _public function_ `template <typename MetricType> requires(std::is_base_of_v<UWorldMetricInterface, MetricType>) [[nodiscard]] MetricType* Get() const` — Gets the metric instance from the type parameter class if it has been previously added. @tparam MetricType The class of the metric to be retrieved. Constrained to be a class derived from UWorldMetricInterface. @return A valid pointer to the metric if found, and nullptr otherwise.
- L97 _public prototype_ `[[nodiscard]] bool Contains(const TSubclassOf<UWorldMetricInterface>& InMetricClass) const;` — Checks if the parameter metric class has been added. @param InMetricClass The class of the metric to be retrieved. @return True if the parameter metric class is registered and false otherwise.
- L107 _public function_ `template <typename MetricType> requires(std::is_base_of_v<UWorldMetricInterface, MetricType>) [[nodiscard]] bool Contains() const` — Checks if the type parameter metric class has been added. @tparam MetricType The UWorldMetricInterface's subclass of the metric to query. @return True if the parameter metric class is registered and false otherwise.
- L118 _public prototype_ `bool Add(const TSubclassOf<UWorldMetricInterface>& InMetricClass);` — Adds a metric instance of the parameter class unless a metric of the same class already exists. @param InMetricClass The class of the metric to add. @return True if a metric of the parameter metric class is added and false otherwise.
- L122 _public function_ `template <typename MetricType> requires(std::is_base_of_v<UWorldMetricInterface, MetricType>) bool Add()`
- L133 _public prototype_ `[[nodiscard]] UWorldMetricInterface* GetOrAdd(const TSubclassOf<UWorldMetricInterface>& InMetricClass);` — Gets the metric instance of the parameter class or adds a new one if missing. @param InMetricClass The class of the metric to add or get. @return The added or previously existing instance of the parameter class.
- L137 _public function_ `template <typename MetricType> requires(std::is_base_of_v<UWorldMetricInterface, MetricType>) [[nodiscard]] MetricType* GetOrAdd()`
- L149 _public prototype_ `bool Remove(const TSubclassOf<UWorldMetricInterface>& InMetricClass);` — Removes the metric matching the parameter class from the collection. The metric object gets automatically garbage-collected unless another system holds a hard-reference to it. @param InMetricClass The class corresponding to the metric to remove. @return True if a metric matching the parameter class is removed and false otherwise.
- L160 _public function_ `template <typename MetricType> requires(std::is_base_of_v<UWorldMetricInterface, MetricType>) bool Remove()` — Removes the metric matching the type parameter class from the collection. The metric object gets automatically garbage-collected unless another system holds a hard-reference to it. @tparam MetricType The UWorldMetricInterface's subclass of the metric to remove. @return True if a metric matching the type parameter class is removed and false otherwise.
- L172 _public function_ `template <typename FuncType> requires(std::is_invocable_r_v<bool, std::decay_t<FuncType>, const UWorldMetricInterface*>) void ForEach(FuncType&& Func) const` — Invokes the parameter function on each of the metrics contained by the collection. @param Func The function which will be invoked for each metric. The function should return true to continue execution, or false otherwise.
- L185 _public function_ `template <typename FuncType> requires(std::is_invocable_r_v<bool, std::decay_t<FuncType>, UWorldMetricInterface*>) void ForEach(FuncType&& Func)`
- L205 _public function_ `void ForEach(FuncType&& Func) const`
- L223 _public function_ `void ForEach(FuncType&& Func)`
- L240 _public prototype_ `void Reset();` — Removes all contained metrics from the World Metric Subsystem, and removes it from the collection.
- L245 _public prototype_ `[[nodiscard]] int32 Num() const;` — @return The number of metrics currently contained by the collection.
- L250 _public prototype_ `[[nodiscard]] bool IsEmpty() const;` — @return True if the collection is empty and contains no metrics.
- L257 _public prototype_ `void AddReferencedObjects(FReferenceCollector& Collector);` — Collects the references held by this collection. Use this method for non UPROPERTY collection instances to prevent the metric objects from being GC. @param Collector the destination reference collector.
- L262 _private member_ `TArray<TObjectPtr<UWorldMetricInterface>> Metrics;` — `UPROPERTY(Transient)` — List of metrics objects.
- L266 _private member_ `TWeakObjectPtr<UWorldMetricsSubsystem> Subsystem;` — `UPROPERTY(Transient)` — World Metric's Subsystem provided by the outer object.
- L270 _private member_ `bool bIsEnabled = false;` — `UPROPERTY(Transient)` — Flag indicating whether the contained metrics are enabled and running in the World Metric's Subsystem.
- L275 _private prototype_ `[[nodiscard]] bool ValidateSubsystem(const UWorldMetricsSubsystem* InSubsystem, const ANSICHAR* CallingFunctionName) const;` — @return True if the subsystem is valid.
- L281 _private prototype_ `[[nodiscard]] bool ValidateClass(const UClass* InClass, const ANSICHAR* CallingFunctionName) const;` — @return True if the class is valid and complete.
- L289 _private prototype_ `[[nodiscard]] int32 GetMetricIndex(const UClass* InMetricClass) const;` — Returns the live world metric list index corresponding to the parameter metric class. @param InMetricClass: the class type of the world metric. @return a valid index value or INDEX_NONE if not matching metric exists.

### `Plugins/WorldMetrics/Source/WorldMetricsCore/Public/WorldMetricInterface.h` (Public)


#### class `UWorldMetricInterface`  
`class UWorldMetricInterface : public UObject`  
_L15-58_
- reflection: `UCLASS(abstract, MinimalAPI, Within=WorldMetricsSubsystem)`
- inherits: `UObject`
- desc: World metric's interface This is the required interface class to implement world metrics.
- L24 _public prototype_ `[[nodiscard]] virtual SIZE_T GetAllocatedSize() const PURE_VIRTUAL(GetAllocatedSize, return 0;);` — Returns the amount of memory allocated by this class, not including sizeof(*this). @return the result size in bytes.
- L31 _public function_ `[[nodiscard]] UWorldMetricsSubsystem& GetOwner() const` — Returns the owning World Metrics Subsystem which is expected to be valid during this object's lifetime. @return a reference to the owning World Metrics Subsystem.
- L40 _private function_ `virtual void Initialize()` — Metric initialization method called by the World Metrics subsystem on metric addition.
- L47 _private function_ `virtual void Deinitialize()` — Metric initialization method called by the World Metrics subsystem before metric removal.
- L55 _private prototype_ `virtual void Update(float DeltaTimeInSeconds) PURE_VIRTUAL(Update, );` — The metric's update method called by the World Metrics subsystem when enabled. @param DeltaTimeInSeconds the delta time in seconds from the last update.

### `Plugins/WorldMetrics/Source/WorldMetricsCore/Public/WorldMetricsActorTracker.h` (Public)


#### class `UWorldMetricsActorTracker`  
`class UWorldMetricsActorTracker final : public UWorldMetricsExtension`  
_L23-72_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWorldMetricsExtension`
- desc: Actor tracker class This class provides a tracking context for actors added and removed from the world. For an actor to be considered added to the world, it must have all its components registered. This class provides two ways of usage: - Polling mode: accessible through ForEachActorInWorld. - Subscriber mode: this mode is enabled through acquire/release semantics. When acquired, the actor tracker subscribes to the world's PostRegisterAllActorComponents and PreUnregisterAllActorComponentsRegistered events tracking all unique actors. In addition, metrics implementing IWorldMetricsActorTrackerSubscriber receive actor addition and removal notifications.
- L29 _public prototype_ `[[nodiscard]] virtual SIZE_T GetAllocatedSize() const override;` — UWorldMetricsExtension
- L32 _private member_ `FDelegateHandle ActorAddedToWorldHandle;`
- L33 _private member_ `FDelegateHandle ActorRemovedFromWorldHandle;`
- L39 _private member_ `TArray<IWorldMetricsActorTrackerSubscriber*, TInlineAllocator<16>> Subscribers;` — Subscriber list. This list uses raw IWorldMetricsActorTrackerSubscriber pointers are used by design instead of TWeakInterfacePtr for performance purposes. This decision is possible because the UWorldMetricsSubsystem is the owner of both this extension and all its subscribers, guaranteeing the lifetime requirements.
- L40 _private member_ `bool bIsEnabled = false;`
- L43 _private prototype_ `virtual void Initialize() override;` — UWorldMetricsExtension
- L44 _private prototype_ `virtual void Deinitialize() override;`
- L45 _private prototype_ `virtual void OnAcquire(UObject* InOwner) override;`
- L46 _private prototype_ `virtual void OnRelease(UObject* InOwner) override;`
- L52 _private prototype_ `void BindWorldCallbacks();` — Binds/Unbinds handles to PostRegisterAllActorComponents and PreUnregisterAllActorComponents in order to account for actors being added/removed to/from the world.
- L53 _private prototype_ `void UnbindWorldCallbacks();`
- L59 _private prototype_ `void NotifyExistingActors(IWorldMetricsActorTrackerSubscriber* Subscriber);` — Notifies the parameter subscriber the addition of all actors in the world with all their components registered. @param Subscriber: the subscriber to notify.
- L65 _private prototype_ `void NotifyOnActorAdded(const AActor* Actor);` — Fires an addition notification event to all subscribers implementing IWorldMetricsActorTrackerSubscriber. @param the actor to notify.
- L71 _private prototype_ `void NotifyOnActorRemoved(const AActor* Actor);` — Fires a removal notification event to all subscribers implementing IWorldMetricsActorTrackerSubscriber. @param the actor to notify.

### `Plugins/WorldMetrics/Source/WorldMetricsCore/Public/WorldMetricsActorTrackerSubscriber.h` (Public)


#### class `UWorldMetricsActorTrackerSubscriber`  
`class UWorldMetricsActorTrackerSubscriber : public UInterface`  
_L10-13_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IWorldMetricsActorTrackerSubscriber`  
`class IWorldMetricsActorTrackerSubscriber`  
_L21-37_
- desc: Actor tracker subscriber interface This interface enables the implementing object class to subscribe to UWorldMetricsActorTracker and receive notifications whenever an actor is added and removed from the world.
- L30 _public prototype_ `virtual void OnActorAdded(const AActor* Actor) = 0;` — Triggers whenever a tracked actor is added. @param Actor: the actor pointer which is guaranteed to be valid until its corresponding OnActorRemoved event.
- L36 _public prototype_ `virtual void OnActorRemoved(const AActor* Actor) = 0;` — Triggers whenever a tracked actor is about to be removed. @param Actor: the actor pointer will no longer be valid after this event.

### `Plugins/WorldMetrics/Source/WorldMetricsCore/Public/WorldMetricsExtension.h` (Public)


#### class `UWorldMetricsExtension`  
`class UWorldMetricsExtension : public UObject`  
_L20-67_
- reflection: `UCLASS(abstract, MinimalAPI, Within=WorldMetricsSubsystem)`
- inherits: `UObject`
- desc: Base class for an extension for the World Metrics subsystem. World Metrics subsystem extensions provide custom data/functionality to world metrics and other extensions (one to many) and have the following characteristics: 1. Unique: there can only be a single instance of each extension class. 2. Exclusively managed and owned by the  World Metrics subsystem.. These should never be created directly. 3. Implement acquired/release semantics. The World Metrics subsystem automatically initializes extensions on acquisition and deinitializes them on release. The subsystem may deallocate an extension that have no acquisitions.
- L29 _public prototype_ `[[nodiscard]] virtual SIZE_T GetAllocatedSize() const PURE_VIRTUAL(GetAllocatedSize, return 0;);` — Returns the amount of memory allocated by this class, not including sizeof(*this). @return the result size in bytes.
- L36 _public function_ `[[nodiscard]] UWorldMetricsSubsystem& GetOwner() const` — Returns the owning World Metrics Subsystem which is expected to be valid during this object's lifetime. @return a reference to the owning World Metrics Subsystem.
- L45 _private function_ `virtual void Initialize()` — Called by the World Metrics subsystem whenever a new extension is added.
- L52 _private function_ `virtual void Deinitialize()` — Called by the World Metrics subsystem whenever an extension is about to be removed.
- L57 _private function_ `virtual void OnAcquire(UObject* InOwner)` — Called by the World Metrics subsystem whenever an extension is acquired.
- L62 _private function_ `virtual void OnRelease(UObject* InOwner)` — Called by the World Metrics subsystem whenever an extension is released.

### `Plugins/WorldMetrics/Source/WorldMetricsCore/Public/WorldMetricsLog.h` (Public)


#### Free symbols / members of external scopes

- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogWorldMetrics, Log, All);`

### `Plugins/WorldMetrics/Source/WorldMetricsCore/Public/WorldMetricsSubsystem.h` (Public)


#### class `UWorldMetricsSubsystem`  
`class UWorldMetricsSubsystem final : public UWorldSubsystem`  
_L29-302_
- reflection: `UCLASS(MinimalAPI, Config = Engine, DefaultConfig)`
- inherits: `UWorldSubsystem`
- desc: World metrics subsystem This subsystem provides an interface to add and remove world metrics implementing the UWorldMetricInterface class. - Added metrics get automatically updated by the subsystem's ticker. - The subsystem becomes an owner of all added metrics. The user is responsible for removing them when no longer needed so they can be garbage collected. - Metrics can have extensions to add shared functionality. - Extensions implement the UWorldMetricsExtension class and use Acquire/Release semantics. They can be acquired by either metrics or extensions. Initialization and deinitialization are the ideal phases to do so. - The subsystem solely owns extensions and can automatically remove them for garbage collection whenever they are no longer acquired by any metric or extension.
- L34 _public prototype_ `[[nodiscard]] static bool CanHaveWorldMetrics(const UWorld* World);`
- L35 _public prototype_ `[[nodiscard]] static UWorldMetricsSubsystem* Get(const UWorld* World);`
- L38 _public prototype_ `virtual bool ShouldCreateSubsystem(UObject* Outer) const override;`
- L39 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L40 _public prototype_ `virtual void Deinitialize() override;`
- L44 _public prototype_ `static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);`
- L45 _public prototype_ `virtual void BeginDestroy() override;`
- L48 _public function_ `[[nodiscard]] bool IsEnabled() const`
- L60 _public prototype_ `void SetUpdateRateInSeconds(float InSeconds);` — Sets the subsystem update ticker rate in seconds. This method automatically restarts the subsystem if it's already enabled. Changing the update rate value on an enabled subsystem causes all metrics to be reinitialized. @requirement: parameter InSeconds value must be equal or greater than zero. @param InSeconds: the update rate value in seconds.
- L65 _public prototype_ `int32 NumMetrics() const;` — @return the number of metrics currently contained by the subsystem.
- L70 _public prototype_ `bool HasAnyMetric() const;` — @return true if the subsystem contains any metric.
- L75 _public prototype_ `int32 NumExtensions() const;` — @return the number of extensions currently contained by the subsystem.
- L80 _public prototype_ `bool HasAnyExtension() const;` — @return true if the subsystem contains any extension.
- L88 _public prototype_ `[[nodiscard]] UWorldMetricInterface* CreateMetric( const TSubclassOf<UWorldMetricInterface>& InMetricClass);` — Factory method to create world metric instances. @param InMetricClass: the class of the world metric to be retrieved. @return a valid pointer to a world metric if successfully created or nullptr otherwise.
- L92 _public function_ `template <typename MetricClass UE_REQUIRES(std::is_base_of_v<UWorldMetricInterface, MetricClass>)> [[nodiscard]] MetricClass* CreateMetric()`
- L101 _public prototype_ `bool ContainsMetric(UWorldMetricInterface* InMetric) const;` — @param InMetric: the metric instance to search. @return true if the parameter metric has been added or false otherwise.
- L109 _public prototype_ `[[nodiscard]] UWorldMetricInterface* AddMetric( const TSubclassOf<UWorldMetricInterface>& InMetricClass);` — Adds a new metric instance of the parameter class to the subsystem. @param InMetricClass: the class of the metric to add. @return true if a metric of the parameter metric class is added and false otherwise.
- L113 _public function_ `template <typename MetricClass UE_REQUIRES(std::is_base_of_v<UWorldMetricInterface, MetricClass>)> [[nodiscard]] MetricClass* AddMetric()`
- L125 _public prototype_ `bool AddMetric(UWorldMetricInterface* InMetric);` — Adds the parameter metric instance to the subsystem. The subsystem will hold a hard-reference to the added metric. The user is responsible for removing it when no longer needed so it can be garbage collected. @param InMetric: the metric instance to add. @return true if the parameter metric is valid and it wasn't previously added or false otherwise.
- L134 _public prototype_ `bool RemoveMetric(UWorldMetricInterface* InMetric);` — Removes the parameter metric instance if it was previously added. The subsystem releases the hard-reference of the metric removed so it can be garbage-collected. @param InMetric: the metric instance to remove. @return true if the parameter metric is removed or false otherwise.
- L141 _public prototype_ `void ForEachMetric(const TFunctionRef<bool(const UWorldMetricInterface*)>& Func) const;` — Const iteration method for each of the metrics added to the subsystem. @param Func The function which will be invoked for each metric. The function should return true to continue execution, or false otherwise.
- L149 _public function_ `template <typename MetricClass UE_REQUIRES(std::is_base_of_v<UWorldMetricInterface, MetricClass>)> void ForEachMetricOfClass(const TFunctionRef<bool(const MetricClass*)>& Func) const` — Const iteration method for each of the metrics added to the subsystem of the template argument class. @param Func The function which will be invoked for each metric. The function should return true to continue execution, or false otherwise.
- L171 _public prototype_ `UWorldMetricsExtension* AcquireExtension( UWorldMetricInterface* InOwner, const TSubclassOf<UWorldMetricsExtension>& InExtensionClass);` — Acquires an extension on behalf of a object. The extension will be created the first time it is acquired, and conversely it will be disabled once released by all owners. @param InOwner: The object acquiring the extension. @param InExtensionClass: The class of the desired extension. @return A pointer to the extension. The lifetime of the extension is managed by the subsystem.
- L176 _public function_ `template <class ExtensionClass UE_REQUIRES(std::is_base_of_v<UWorldMetricsExtension, ExtensionClass>)> ExtensionClass* AcquireExtension(UWorldMetricInterface* InMetricOwner)`
- L181 _public prototype_ `UWorldMetricsExtension* AcquireExtension( UWorldMetricsExtension* InOwner, const TSubclassOf<UWorldMetricsExtension>& InExtensionClass);`
- L186 _public function_ `template <class ExtensionClass UE_REQUIRES(std::is_base_of_v<UWorldMetricsExtension, ExtensionClass>)> ExtensionClass* AcquireExtension(UWorldMetricsExtension* InExtensionOwner)`
- L197 _public prototype_ `bool ReleaseExtension( UWorldMetricInterface* InOwner, const TSubclassOf<UWorldMetricsExtension>& InExtensionClass);` — Releases a metric's ownership of an extension. If this was the last reference the extension will be disabled. @param InOwner: The object whose ownership should be released. @param InExtensionClass: The class type of the extension.
- L201 _public prototype_ `bool ReleaseExtension( UWorldMetricsExtension* InOwner, const TSubclassOf<UWorldMetricsExtension>& InExtensionClass);`
- L206 _public function_ `template <class ExtensionClass UE_REQUIRES(std::is_base_of_v<UWorldMetricsExtension, ExtensionClass>)> bool ReleaseExtension(UWorldMetricInterface* InOwner)`
- L212 _public function_ `template <class ExtensionClass UE_REQUIRES(std::is_base_of_v<UWorldMetricsExtension, ExtensionClass>)> bool ReleaseExtension(UWorldMetricsExtension* InExtensionOwner)`
- L218 _private member_ `static constexpr int32 DefaultExtensionCapacity = 16;`
- L219 _private member_ `static constexpr int32 DefaultOwnerListCapacity = 32;`
- L221 _private member_ `FTSTicker::FDelegateHandle UpdateTickerHandle;`
- L224 _private member_ `TArray<TObjectPtr<UWorldMetricInterface>> Metrics;` — `UPROPERTY(Transient)`
- L226 _private typedef_ `using FOwnerList = TSet<UObject*, DefaultKeyFuncs<UObject*>, TInlineSetAllocator<DefaultOwnerListCapacity>>;`
- L235 _private member_ `TMap<TSubclassOf<UWorldMetricsExtension>, FExtension, TInlineSetAllocator<DefaultExtensionCapacity>> Extensions;` — Exposed to GC via AddReferencedObjects.
- L239 _public member_ `float UpdateRateInSeconds = 0.f;` — `UPROPERTY(Config)`
- L243 _public member_ `int32 WarmUpFrames = 8;` — `UPROPERTY(Config)` — The number of frames the subsystem waits to update added metrics after their initialization.
- L246 _private member_ `int32 PendingWarmUpFrames = 0;`
- L248 _private prototype_ `void InitializeMetrics();`
- L249 _private prototype_ `void DeinitializeMetrics();`
- L258 _private prototype_ `void Enable(bool bEnable);` — Enables or disables the subsystem. When enabled the subsystem uses an update ticker to update each of the added world metrics. All metrics are automatically initialized when the system is enabled and deinitialized when is disabled. The subsystem is automatically disabled on deinitialization. @param bEnable: true for enabling the system and false otherwise.
- L260 _private prototype_ `void OnUpdate(float DeltaTimeInSeconds);`
- L266 _private prototype_ `void RemoveAllMetrics();` — Removes all added metrics. The subsystem releases the hard-reference of the  metrics removed so they can be garbage-collected.
- L271 _private prototype_ `void Clear();` — Removes all existing metrics and extensions. Internal use only.
- L273 _private prototype_ `UWorldMetricsExtension* AcquireExtensionInternal( UObject* InOwner, const TSubclassOf<UWorldMetricsExtension>& InExtensionClass);`
- L277 _private prototype_ `UWorldMetricsExtension* AcquireExistingExtension( UObject* InOwner, const TSubclassOf<UWorldMetricsExtension>& InExtensionClass);`
- L281 _private prototype_ `UWorldMetricsExtension* AddExtension(UObject* InOwner, const TSubclassOf<UWorldMetricsExtension>& InExtensionClass);`
- L283 _private prototype_ `bool ReleaseExtensionInternal(UObject* InOwner, const TSubclassOf<UWorldMetricsExtension>& InExtensionClass);`
- L285 _private prototype_ `bool TryRemoveExtension(const TSubclassOf<UWorldMetricsExtension>& InExtensionClass);`
- L294 _private prototype_ `void VerifyMetricReleasedAllExtensions(UWorldMetricInterface* InMetric);` — Verifies the parameter metric has released any acquired extensions, releasing any pending ones. It's the metric's responsibility to release all previously acquired resources. This method logs all extensions owned by the parameter metric that hasn't been released. @param InMetric: the metric to verify.
- L301 _private prototype_ `void VerifyRemoveOrphanExtensions();` — Verifies there are no orphan extensions. These are extensions that are still alive without any live metric. This method logs and removes all orphan extensions, addressing the scenario where extensions that acquired other extensions didn't release them. Extensions, like metrics, are responsible for releasing acquired extensions.

#### struct `UWorldMetricsSubsystem::FExtension`  
`struct FExtension`  
_L228-232_
- L230 _public member_ `TObjectPtr<UWorldMetricsExtension> Instance;`
- L231 _public member_ `FOwnerList Owners;`
