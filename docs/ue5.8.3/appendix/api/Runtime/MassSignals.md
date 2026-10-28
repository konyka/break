# Runtime / MassSignals

- module root: `Source/Runtime/Mass/MassSignals`
- headers: 4; symbols: 67
- symbol kinds: class=3, delegate=2, enum=1, enumerator=2, function=5, macro=1, member=22, namespace=2, prototype=24, struct=5
- PrivateDependencyModuleNames: EditorFramework, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, Engine, MassCore, MassEntity

### `Source/Runtime/Mass/MassSignals/Public/IMassSignalsModule.h` (Public)


#### class `IMassSignalsModule`  
`class IMassSignalsModule : public IModuleInterface`  
_L14-39_
- inherits: `IModuleInterface`
- desc: The public interface to this module.  In most cases, this interface is only public to sibling modules within this plugin.
- L25 _public function_ `static inline IMassSignalsModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L35 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Source/Runtime/Mass/MassSignals/Public/MassSignalProcessorBase.h` (Public)


#### class `UMassSignalProcessorBase`  
`class UMassSignalProcessorBase : public UMassProcessor`  
_L22-107_
- reflection: `UCLASS(MinimalAPI, abstract)`
- inherits: `UMassProcessor`
- desc: Processor for executing signals on each targeted entities The derived classes only need to implement the method SignalEntities to actually received the raised signals for the entities they subscribed to
- L27 _public prototype_ `UMassSignalProcessorBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L30 _protected prototype_ `virtual void BeginDestroy() override;`
- L33 _protected function_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>&) override` — Configure the owned FMassEntityQuery instances to express processor queries requirements
- L41 _protected prototype_ `virtual void SignalEntities(FMassEntityManager& EntityManager, FMassExecutionContext& Context, FMassSignalNameLookup& EntitySignals) PURE_VIRTUAL(UMassSignalProcessorBase::SignalEntities, );` — Actual method that derived class needs to implement to act on a signal that is raised for that frame @param EntitySubsystem is the system to execute the lambdas on each entity chunk @param Context is the execution context to be passed when executing the lambdas @param EntitySignals Look up to retrieve for each entities their raised signal via GetSignalsForEntity
- L48 _protected prototype_ `virtual void OnSignalReceived(FName SignalName, TConstArrayView<FMassEntityHandle> Entities);` — Callback that is being called when new signal is raised @param SignalName is the name of the signal being raised @param Entities are the targeted entities for this signal
- L55 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;` — Execution method for this processor @param EntitySubsystem is the system to execute the lambdas on each entity chunk @param Context is the execution context to be passed when executing the lambdas
- L61 _protected function_ `virtual bool ShouldAllowQueryBasedPruning(const bool bRuntimeMode = true) const override` — We don't want signaling processors to be pruned by default, since that can mess up signal processing just after processor's creation (might miss some signals initially).
- L68 _protected prototype_ `void SubscribeToSignal(UMassSignalSubsystem& SignalSubsystem, const FName SignalName);` — To receive notification about a particular signal, you need to subscribe to it. @param SignalName is the name of the signal to receive notification about
- L70 _protected member_ `FMassEntityQuery EntityQuery;`
- L92 _private member_ `static constexpr int BuffersCount = 2;`
- L95 _private member_ `TStaticArray<FFrameReceivedSignals, BuffersCount> FrameReceivedSignals;` — Double buffer frame received signal as we can receive new signals as we are processing them
- L98 _private member_ `int32 CurrentFrameBufferIndex = 0;` — Current frame buffer index of FrameReceivedSignals
- L101 _private member_ `FMassSignalNameLookup SignalNameLookup;` — Lookup used to store and retrieve signals per entity, only used during processing
- L104 _private member_ `TArray<FName> RegisteredSignals;` — List of all the registered signal names
- L106 _private member_ `FTransactionallySafeRWLock ReceivedSignalLock;`

#### struct `UMassSignalProcessorBase::FEntitySignalRange`  
`struct FEntitySignalRange`  
_L75-81_
- desc: Stores a range of indices in the SignaledEntities TArray of Entities and the associated signal name
- L77 _public member_ `FName SignalName;`
- L78 _public member_ `int32 Begin = 0;`
- L79 _public member_ `int32 End = 0;`
- L80 _public member_ `bool bProcessed = false;`

#### struct `UMassSignalProcessorBase::FFrameReceivedSignals`  
`struct FFrameReceivedSignals`  
_L83-90_
- L86 _public member_ `TArray<FEntitySignalRange> ReceivedSignalRanges;` — Received signals are double buffered as we can receive new one while processing them
- L89 _public member_ `TArray<FMassEntityHandle> SignaledEntities;` — the list of all signaled entities, can contain duplicates

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MASSSIGNALS_API`

### `Source/Runtime/Mass/MassSignals/Public/MassSignalSubsystem.h` (Public)


#### class `UMassSignalSubsystem`  
`class UMassSignalSubsystem : public UMassTickableSubsystemBase`  
_L25-129_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassTickableSubsystemBase`
- desc: A subsystem for handling Signals in Mass
- L35 _public function_ `UE::MassSignal::FSignalDelegate& GetSignalDelegateByName(FName SignalName)` — Retrieve the delegate dispatcher from the signal name @param SignalName is the name of the signal to get the delegate dispatcher from
- L45 _public prototype_ `void SignalEntity(FName SignalName, const FMassEntityHandle Entity);` — Inform a single entity of a signal being raised @param SignalName is the name of the signal raised @param Entity entity that should be informed that signal 'SignalName' was raised
- L52 _public prototype_ `void SignalEntities(FName SignalName, TConstArrayView<FMassEntityHandle> Entities);` — Inform multiple entities of a signal being raised @param SignalName is the name of the signal raised @param Entities list of entities that should be informed that signal 'SignalName' was raised
- L60 _public prototype_ `void DelaySignalEntity(FName SignalName, const FMassEntityHandle Entity, const float DelayInSeconds);` — Inform a single entity of a signal being raised in a certain amount of seconds @param SignalName is the name of the signal raised @param Entity entity that should be informed that signal 'SignalName' was raised @param DelayInSeconds is the amount of time before signaling the entity
- L68 _public prototype_ `void DelaySignalEntities(FName SignalName, TConstArrayView<FMassEntityHandle> Entities, const float DelayInSeconds);` — Inform multiple entities of a signal being raised in a certain amount of seconds @param SignalName is the name of the signal raised @param Entities being informed of the raised signal @param DelayInSeconds is the amount of time before signaling the entities
- L76 _public prototype_ `void SignalEntityDeferred(FMassExecutionContext& Context, FName SignalName, const FMassEntityHandle Entity);` — Inform single entity of a signal being raised asynchronously using the Mass Command Buffer @param Context is the Entity System execution context to push the async command @param SignalName is the name of the signal raised @param Entity entity that should be informed that signal 'SignalName' was raised
- L84 _public prototype_ `void SignalEntitiesDeferred(FMassExecutionContext& Context, FName SignalName, TConstArrayView<FMassEntityHandle> Entities);` — Inform multiple entities of a signal being raised asynchronously using the Mass Command Buffer @param Context is the Entity System execution context to push the async command @param SignalName is the name of the signal raised @param Entities list of entities that should be informed that signal 'SignalName' was raised
- L93 _public prototype_ `void DelaySignalEntityDeferred(FMassExecutionContext& Context, FName SignalName, const FMassEntityHandle Entity, const float DelayInSeconds);` — Inform single entity of a signal being raised asynchronously using the Mass Command Buffer @param Context is the Entity System execution context to push the async command @param SignalName is the name of the signal raised @param Entity entity that should be informed that signal 'SignalName' was raised @param DelayInSeconds is the amount of time before signaling the entities
- L102 _public prototype_ `void DelaySignalEntitiesDeferred(FMassExecutionContext& Context, FName SignalName, TConstArrayView<FMassEntityHandle> Entities, const float DelayInSeconds);` — Inform multiple entities of a signal being raised asynchronously using the Mass Command Buffer @param Context is the Entity System execution context to push the async command @param SignalName is the name of the signal raised @param Entities being informed of that signal was raised @param DelayInSeconds is the amount of time before signaling the entities
- L106 _protected prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;` — USubsystem implementation Begin
- L107 _protected prototype_ `virtual void Deinitialize() override;`
- L110 _protected prototype_ `virtual void Tick(float DeltaTime) override;`
- L111 _protected prototype_ `virtual TStatId GetStatId() const override;`
- L114 _protected prototype_ `UE_MT_DECLARE_RW_ACCESS_DETECTOR(DelayedSignalsAccessDetector);` — Multithreading access detector to validate accesses to the list of delayed signals
- L116 _protected member_ `TMap<FName, UE::MassSignal::FSignalDelegate> NamedSignals;`
- L125 _protected member_ `TArray<FDelayedSignal> DelayedSignals;`
- L128 _protected member_ `TObjectPtr<UWorld> CachedWorld;` — `UPROPERTY(transient)`

#### struct `UMassSignalSubsystem::FDelayedSignal`  
`struct FDelayedSignal`  
_L118-123_
- L120 _public member_ `FName SignalName;`
- L121 _public member_ `TArray<FMassEntityHandle> Entities;`
- L122 _public member_ `double TargetTimestamp;`

#### struct `TMassExternalSubsystemTraits`  
`template<> struct TMassExternalSubsystemTraits<UMassSignalSubsystem> final`  
_L132-141_

#### enum `TMassExternalSubsystemTraits::(anonymous)`  
``  
_L135-140_

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace MassSignal` (scope `UE`)
- L18 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FSignalDelegate, FName , TConstArrayView<FMassEntityHandle> );`
- L18 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FSignalDelegate, FName , TConstArrayView<FMassEntityHandle> );` (scope `UE::MassSignal`)
- L136 _enumerator_ `GameThreadOnly = false` (scope `TMassExternalSubsystemTraits::__anon175f96a50103`)
- L139 _enumerator_ `ThreadSafeWrite = false` (scope `TMassExternalSubsystemTraits::__anon175f96a50103`) — @todo this subsystem not being thread-safe when writing is an obstacle in parallelizing multiple processors

### `Source/Runtime/Mass/MassSignals/Public/MassSignalTypes.h` (Public)


#### struct `FMassSignalNameLookup`  
`struct FMassSignalNameLookup`  
_L17-51_
- desc: MassSignalNameLookup stores list of Signal names for each entity. The names are stored per entity as a bitmask, you can allocate new name using GetOrAddSignalName(). This limits the names to 64.
- L20 _public member_ `static constexpr int32 MaxSignalNames = 64;` — Max number of names each entity can contain
- L27 _public prototype_ `uint64 GetOrAddSignalName(const FName SignalName);` — Retrieve if it is already registered or adds new signal to the lookup and return the bitflag for that Signal @SignalName is the name of the signal to retrieve or add to the lookup. @return bitflag describing the name, or 0 if max names is reached.
- L34 _public prototype_ `void AddSignalToEntity(const FMassEntityHandle Entity, const uint64 SignalFlag);` — Adds specified Signal name bitflag to an entity @param Entity is the entity where the signal has been raised @param SignalFlag is the actual bitflag describing the signal
- L40 _public prototype_ `void GetSignalsForEntity(const FMassEntityHandle Entity, TArray<FName>& OutSignals) const;` — Retrieve for a specific entity the raised signal this frame @return Array of signal names raised for this entity
- L43 _public prototype_ `void Reset();` — Empties the name lookup and entity signals
- L47 _protected member_ `TArray<FName> SignalNames;` — Array of Signal names
- L50 _protected member_ `TMap<FMassEntityHandle, uint64> EntitySignals;` — Map from entity id to name bitmask

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMassSignals, Log, All) struct FMassSignalNameLookup { static constexpr int32 MaxSignalNames = 64; uint64 GetOrAddSignalName(const FName SignalName); void AddSignalToEntity(const FMassEntityHandle Entity, const uint64 SignalFlag); void GetSignalsForEntity(const FMassEntityHandle Entity, TArray<FName>& OutSignals) const; void Reset(); protected: TArray<FName> SignalNames; TMap<FMassEntityHandle, uint64> EntitySignals;`
