# Plugins / MassActors

- module root: `Plugins/Runtime/MassGameplay/Source/MassActors`
- headers: 14; symbols: 344
- symbol kinds: class=22, delegate=4, enum=6, enumerator=22, function=44, macro=9, member=67, namespace=7, prototype=138, struct=23, typedef=1, variable=1
- PrivateDependencyModuleNames: EditorFramework, UnrealEd
- PublicDependencyModuleNames: AIModule, Core, CoreUObject, Engine, MassCommon, MassCore, MassEntity, MassMovement, MassReplication, MassSignals, MassSimulation, MassSpawner, NetCore

### `Plugins/Runtime/MassGameplay/Source/MassActors/Public/IMassActorsModule.h` (Public)


#### class `IMassActorsModule`  
`class IMassActorsModule : public IModuleInterface`  
_L14-39_
- inherits: `IModuleInterface`
- desc: The public interface to this module.  In most cases, this interface is only public to sibling modules within this plugin.
- L25 _public function_ `static inline IMassActorsModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L35 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Plugins/Runtime/MassGameplay/Source/MassActors/Public/MassActorHelper.h` (Public)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MassActor` (scope `UE`)
- L16 _prototype_ `bool AddEntityTagToActor(const AActor& Actor, const UScriptStruct& TagType);` (scope `UE::MassActor`) — Finds the entity associated with Actor and adds TagType to it, @return true if successful, false otherwise (see log for details)
- L23 _function_ `template<typename TagType> bool AddEntityTagToActor(const AActor& Actor)` (scope `UE::MassActor`) — Finds the entity associated with Actor and adds TagType to it, @return true if successful, false otherwise (see log for details)
- L33 _prototype_ `bool RemoveEntityTagFromActor(const AActor& Actor, const UScriptStruct& TagType);` (scope `UE::MassActor`) — Finds the entity associated with Actor and remove TagType from its composition @return true if successful, false otherwise (see log for details)
- L40 _function_ `template<typename TagType> bool RemoveEntityTagFromActor(const AActor& Actor)` (scope `UE::MassActor`) — Finds the entity associated with Actor and remove TagType from its composition @return true if successful, false otherwise (see log for details)

### `Plugins/Runtime/MassGameplay/Source/MassActors/Public/MassActorPoolableInterface.h` (Public)


#### class `UMassActorPoolableInterface`  
`class UMassActorPoolableInterface : public UInterface`  
_L11-14_
- reflection: `UINTERFACE(MinimalAPI, Blueprintable)`
- inherits: `UInterface`

#### class `IMassActorPoolableInterface`  
`class IMassActorPoolableInterface : public IInterface`  
_L16-30_
- inherits: `IInterface`
- L23 _public prototype_ `bool CanBePooled();` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Mass|Actor Pooling")`
- L26 _public prototype_ `void PrepareForPooling();` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Mass|Actor Pooling")`
- L29 _public prototype_ `void PrepareForGame();` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Mass|Actor Pooling")`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MASSACTORS_API`

### `Plugins/Runtime/MassGameplay/Source/MassActors/Public/MassActorSpawnerSubsystem.h` (Public)


#### struct `FMassActorSpawnRequestHandle`  
`struct FMassActorSpawnRequestHandle : public FIndexedHandleBase`  
_L29-39_
- reflection: `USTRUCT()`
- inherits: `FIndexedHandleBase`
- desc: Handle for an actor spawning request
- L33 _public prototype_ `FMassActorSpawnRequestHandle() = default;`
- L36 _public function_ `FMassActorSpawnRequestHandle(const int32 InIndex, const uint32 InSerialNumber) : FIndexedHandleBase(InIndex, InSerialNumber)` — @note passing INDEX_NONE as index will make this handle Invalid

#### enum `EMassActorSpawnRequestAction`  
`enum class EMassActorSpawnRequestAction : uint8`  
_L46-50_
- L48 _public enumerator_ `Keep` — Will leave spawning request in the queue and it will be users job to call RemoveActorSpawnRequest
- L49 _public enumerator_ `Remove` — Will remove the spawning request from the queue once the callback ends

#### enum `ESpawnRequestStatus`  
`enum class ESpawnRequestStatus : uint8`  
_L54-62_
- reflection: `UENUM()`
- L56 _public enumerator_ `None` — Not in the queue to be spawn
- L57 _public enumerator_ `Pending` — Still in the queue to be spawn
- L58 _public enumerator_ `Processing` — in the process of spawning the actor
- L59 _public enumerator_ `Succeeded` — Successfully spawned the actor
- L60 _public enumerator_ `Failed` — Error while spawning the actor
- L61 _public enumerator_ `RetryPending` — Failed spawn request that are being retried (lower priority)

#### struct `FMassActorSpawnRequest`  
`struct FMassActorSpawnRequest`  
_L68-124_
- reflection: `USTRUCT()`
- desc: Base class for all spawn request
- L73 _public member_ `FMassEntityHandle MassAgent;` — The actual mass agent handle corresponding to the actor to spawn
- L77 _public member_ `TSubclassOf<AActor> Template;` — `UPROPERTY(Transient)` — The template BP actor to spawn
- L80 _public member_ `FTransform Transform;` — The location of where to spawn that actor
- L83 _public member_ `float Priority = MAX_FLT;` — Priority of this spawn request in comparison with the others, the lower the value is, the higher the priority is
- L86 _public member_ `FMassActorPreSpawnDelegate ActorPreSpawnDelegate;` — Delegate that will be called just before the spawning an actor, giving the chance to the processor to prepare it
- L92 _public member_ `FMassActorPostSpawnDelegate ActorPostSpawnDelegate;` — Delegate that will be called once the spawning is done. Note that it will be called regardless of whether the spawning was successful.
- L95 _public member_ `ESpawnRequestStatus SpawnStatus = ESpawnRequestStatus::None;` — The current status of the spawn request
- L99 _public member_ `TObjectPtr<AActor> SpawnedActor = nullptr;` — `UPROPERTY(Transient)` — The pointer to the actor once it is spawned
- L102 _public member_ `uint32 SerialNumber = 0;` — Internal request serial number (used to cycle through next spawning request)
- L105 _public member_ `double RequestedTime = 0.;` — Requested world time seconds
- L108 _public member_ `FGuid Guid;` — If set, will be used to name the spawned character
- L110 _public function_ `void Reset()`
- L123 _public function_ `bool IsFinished() const`

#### class `UMassActorSpawnerSubsystem`  
`class UMassActorSpawnerSubsystem : public UMassSubsystemBase`  
_L130-331_
- reflection: `UCLASS(MinimalAPI, transient)`
- inherits: `UMassSubsystemBase`
- desc: A subsystem managing spawning of actors for all mass subsystems
- L136 _protected prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;` — USubsystem BEGIN
- L137 _protected prototype_ `virtual void Deinitialize() override;`
- L141 _public prototype_ `static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);`
- L149 _public function_ `template< typename T, typename = typename TEnableIf<TIsDerivedFrom<typename TRemoveReference<T>::Type, FMassActorSpawnRequest>::IsDerived, void>::Type > FMassActorSpawnRequestHandle RequestActorSpawn(const T& InSpawnRequest)` — Request an actor to spawn Note: If you do not provide a spawn delegate, the requester is responsible to remove the request by hand. It will be auto removed after the execution of the spawn delegate. @param InSpawnRequest the spawn request parameters, You can provide any type of UStruct as long at it derives from FMassActorSpawnRequest. This let you add more spawning information.
- L160 _public prototype_ `[[nodiscard]] ESpawnRequestStatus ProcessSpawnRequest(const FMassActorSpawnRequestHandle SpawnRequestHandle);` — Process a valid spawn request indicated by given handle. Can be used to force instant-spawn of an actor provided a valid handle is obtained by calling RequestActorSpawn first. @return indicates the status of processed spawn request, with ESpawnRequestStatus::None indicating that "something went wrong" and spawning request has not been processed.
- L165 _public prototype_ `[[nodiscard]] ESpawnRequestStatus ProcessSpawnRequest(const FMassActorSpawnRequestHandle SpawnRequestHandle, FStructView SpawnRequestView, FMassActorSpawnRequest& SpawnRequest);` — Similar to the other ProcessSpawnRequest flavor, but with SpawnRequestView and SpawnRequest already provided.
- L170 _public prototype_ `void RetryActorSpawnRequest(const FMassActorSpawnRequestHandle SpawnRequestHandle);` — Retries a failed spawn request @param SpawnRequestHandle the spawn request handle to retry
- L179 _public prototype_ `bool RemoveActorSpawnRequest(FMassActorSpawnRequestHandle& SpawnRequestHandle);` — Removes a spawn request The only time a spawn request cannot be removed is when its state is processing Also spawn requests are auto removed if you provided a spawn delegate after it was being executed. @param SpawnRequestHandle [IN/OUT] the spawn request handle to remove @return true if successfully removed the request
- L187 _public function_ `template<typename T> const T& GetSpawnRequest(const FMassActorSpawnRequestHandle SpawnRequestHandle) const` — Returns the stored spawn request from the handle, useful to update the transform @param SpawnRequestHandle the spawn request handle to get the request from @return The spawn request cast in the provided template argument
- L200 _public function_ `template<typename T> T& GetMutableSpawnRequest(const FMassActorSpawnRequestHandle SpawnRequestHandle)` — Returns the stored spawn request from the handle, useful to update the transform @param SpawnRequestHandle the spawn request handle to get the request from @return The spawn request cast in the provided template argument
- L207 _public function_ `bool IsSpawnRequestHandleValid(const FMassActorSpawnRequestHandle SpawnRequestHandle) const`
- L217 _public function_ `bool IsHandleReleased(const FMassActorSpawnRequestHandle SpawnRequestHandle) const` — Checks whether the given handle has already been released. Note that the function will return `false` for invalid handles - the function is intended to check whether a given "valid" handle that the caller has access to has already been released.
- L229 _public prototype_ `virtual void DestroyActor(AActor* Actor, bool bImmediate = false);` — Destroy an actor @param Actor to destroy @param bImmediate to do the destruction immediately, otherwise will be queued up for later
- L231 _public prototype_ `void EnableActorPooling();`
- L232 _public prototype_ `void DisableActorPooling();`
- L233 _public prototype_ `bool IsActorPoolingEnabled();`
- L235 _public prototype_ `void ReleaseAllResources();`
- L242 _protected prototype_ `static void ConditionalDestroyActor(UWorld& World, AActor& ActorToDestroy);` — Provides consistent way of conditional destroying Actor within World. The actual destruction depends on Actor's state and whether it belongs to World
- L245 _protected prototype_ `void OnPrePhysicsPhaseStarted(const float DeltaSeconds);` — Called at the start of the PrePhysics mass processing phase and calls ProcessPendingSpawningRequest
- L248 _protected prototype_ `void OnPrePhysicsPhaseFinished(const float DeltaSeconds);` — Called at the end of the PrePhysics mass processing phase and calls ProcessPendingDestruction
- L259 _protected prototype_ `virtual FMassActorSpawnRequestHandle GetNextRequestToSpawn(int32& InOutHandleIndex) const;` — Retrieve what would be the next best spawning request to spawn, can be overridden to have different logic Default implementation is the first valid request in the list, no interesting logic yet @param InOutHandleIndex used to start the search in subsequent locations. Also the index ensures the same handle won't get returned twice in a row. InOutHandleIndex being INDEX_NONE indicates this is the first run, so all handles are to be considered. If it's a  valid index then we iterate all but one to not even consider the handle indicated by InOutHandleIndex. @return the next best handle to spawn.
- L271 _protected prototype_ `[[nodiscard]] ESpawnRequestStatus ProcessSpawnRequestImpl(const FSpawnArgs& Args);`
- L272 _protected prototype_ `virtual ESpawnRequestStatus SpawnOrRetrieveFromPool(const FSpawnArgs& Args);`
- L275 _protected function_ `virtual ESpawnRequestStatus SpawnOrRetrieveFromPool(FConstStructView SpawnRequestView, TObjectPtr<AActor>& OutSpawnedActor) final` — `UE_DEPRECATED(5.8, "Use the overload that accepts FSpawnArgs. OutSpawnedActor is equivalent to Args.Request.SpawnedActor")`
- L281 _protected prototype_ `virtual ESpawnRequestStatus SpawnActor(const FSpawnArgs& Args, FActorSpawnParameters& InOutSpawnParameters) const;` — Actual code that will spawn the actor, overridable by subclass if need to be.
- L284 _protected function_ `virtual ESpawnRequestStatus SpawnActor(FConstStructView SpawnRequestView, TObjectPtr<AActor>& OutSpawnedActor, FActorSpawnParameters& InOutSpawnParameters) const final` — `UE_DEPRECATED(5.8, "Use the overload that accepts FSpawnArgs. OutSpawnedActor is equivalent to Args.Request.SpawnedActor")`
- L289 _protected prototype_ `TObjectPtr<AActor> FindActorByName(const FName ActorName, ULevel* OverrideLevel) const;`
- L293 _protected prototype_ `void ProcessPendingSpawningRequest(const double MaxTimeSlicePerTick);` — Go through the spawning request and spawn them until we reach the budget @param MaxTimeSlicePerTick is the budget in seconds allowed to do spawning
- L297 _protected prototype_ `void ProcessPendingDestruction(const double MaxTimeSlicePerTick);` — Go through the queued actors to destroy and destroy them until we reach the budget @param MaxTimeSlicePerTick is the budget in seconds allowed to do destruction
- L302 _protected prototype_ `virtual bool ReleaseActorToPool(AActor* Actor);` — Try releasing this actor to pool if possible @param Actor to release to the pool @return true if the actor was actually released to the pool
- L306 _protected prototype_ `FMassActorSpawnRequestHandle RequestActorSpawnInternal(const FConstStructView SpawnRequest);` — Internal generic request actor spawn to make sure the request derives from FMassActorSpawnRequest @param SpawnRequest the spawn request parameters, We are allowing any type of spawn request, let's store it internally as a FInstancedStruct. This parameter is the FStructView over provide user struct
- L311 _protected member_ `TArray<FInstancedStruct> SpawnRequests;` — `UPROPERTY()`
- L314 _protected member_ `TArray<TObjectPtr<AActor>> ActorsToDestroy;` — `UPROPERTY()`
- L317 _protected member_ `TArray<TObjectPtr<AActor>> DeactivatedActorsToDestroy;` — `UPROPERTY()`
- L319 _protected member_ `bool bActorPoolingEnabled = true;`
- L321 _protected member_ `TMap<FObjectKey, TArray<TObjectPtr<AActor>>> PooledActors;`
- L323 _protected member_ `FMassEntityHandleManager_ActorSpawnRequest SpawnRequestHandleManager;`
- L325 _protected member_ `std::atomic<uint32> RequestSerialNumberCounter;`
- L327 _protected member_ `mutable int32 NumActorSpawned = 0;`
- L328 _protected member_ `mutable int32 NumActorPooled = 0;`
- L330 _protected member_ `int32 StartingHandleIndex = INDEX_NONE;`

#### struct `UMassActorSpawnerSubsystem::FSpawnArgs`  
`struct FSpawnArgs`  
_L261-269_
- L263 _public member_ `TNotNull<UWorld*> World;`
- L264 _public member_ `FMassEntityManager& EntityManager;`
- L266 _public member_ `FMassActorSpawnRequestHandle RequestHandle;`
- L267 _public member_ `FStructView RequestView;`
- L268 _public member_ `FMassActorSpawnRequest& Request;`

#### Free symbols / members of external scopes

- L42 _typedef_ `typedef FIndexedHandleManager<FMassActorSpawnRequestHandle, true > FMassEntityHandleManager_ActorSpawnRequest;` — Managing class of spawning requests handles
- L45 _delegate_ `DECLARE_DELEGATE_TwoParams(FMassActorPreSpawnDelegate, const FMassActorSpawnRequestHandle& SpawnRequestHandle, FConstStructView SpawnRequest);`
- L45 _prototype_ `DECLARE_DELEGATE_TwoParams(FMassActorPreSpawnDelegate, const FMassActorSpawnRequestHandle& SpawnRequestHandle, FConstStructView SpawnRequest);`
- L51 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(EMassActorSpawnRequestAction, FMassActorPostSpawnDelegate, const FMassActorSpawnRequestHandle& SpawnRequestHandle, FConstStructView SpawnRequest);`
- L51 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(EMassActorSpawnRequestAction, FMassActorPostSpawnDelegate, const FMassActorSpawnRequestHandle& SpawnRequestHandle, FConstStructView SpawnRequest);`

### `Plugins/Runtime/MassGameplay/Source/MassActors/Public/MassActorSubsystem.h` (Public)


#### struct `FMassGuidFragment`  
`struct FMassGuidFragment : public FObjectWrapperFragment`  
_L23-34_
- reflection: `USTRUCT()`
- inherits: `FObjectWrapperFragment`
- L27 _public function_ `bool operator==(const FMassGuidFragment& Other) const`
- L33 _public member_ `FGuid Guid;` — `UPROPERTY()`

#### struct `FMassActorInstanceFragment`  
`struct FMassActorInstanceFragment : public FMassFragment`  
_L40-52_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- desc: Fragment to store the instanced actor handle of a mass entity if it needs one.
- L44 _public prototype_ `FMassActorInstanceFragment() = default;`
- L45 _public function_ `explicit FMassActorInstanceFragment(const FActorInstanceHandle& InHandle) : Handle(InHandle)`
- L51 _public member_ `FActorInstanceHandle Handle;` — `UPROPERTY()`

#### struct `TMassFragmentTraits`  
`template<> struct TMassFragmentTraits<FMassActorInstanceFragment> final`  
_L55-61_

#### enum `TMassFragmentTraits::(anonymous)`  
``  
_L58-60_

#### struct `FMassActorFragment`  
`struct FMassActorFragment : public FObjectWrapperFragment`  
_L73-140_
- reflection: `USTRUCT()`
- inherits: `FObjectWrapperFragment`
- desc: Fragment to save the actor pointer of a mass entity if it exists
- L90 _public prototype_ `void SetAndUpdateHandleMap(const FMassEntityHandle MassAgent, AActor* InActor, const bool bInIsOwnedByMass);` — Set the actor associated to a mass agent, will also keep the map back in MassActorSubsystem up to date. @param MassAgent to associated with the actor @param InActor the actor associated with the mass agent @param bInIsOwnedByMass tell whether the actors was spawned by mass(MassVisualization) or externally(ReplicatedActors)
- L97 _public prototype_ `void ResetAndUpdateHandleMap(UMassActorSubsystem* CachedActorSubsystem = nullptr);` — Resets the actor pointed by this fragment, will also keep the map back in UMassActorSubsystem up to date @param CachedActorSubsystem if provided will be used directly, otherwise an instance of UMassActorSubsystem will be deduced from Actor's world (at additional runtime cost)
- L107 _public prototype_ `void SetNoHandleMapUpdate(const FMassEntityHandle MassAgent, AActor* InActor, const bool bInIsOwnedByMass);` — Set the actor associated to a mass agent, will NOT keep map back in MassActorSubsystem up to date. The user needs to do the map update by hand. Useful in multithreaded environment, to queue the update of the map inside a deferred command @param MassAgent to associated with the actor @param InActor the actor associated with the mass agent @param bInIsOwnedByMass tell whether the actors was spawned by mass(MassVisualization) or externally(ReplicatedActors)
- L113 _public prototype_ `void ResetNoHandleMapUpdate();` — Resets the actor pointed by this fragment, will NOT keep map back in MassActorSubsystem up to date. The user needs to do the map update by hand. Useful in multithreaded environment, to queue the update of the map inside a deferred command
- L117 _public function_ `inline AActor* GetMutable()` — @return none const pointer to the actor
- L118 _public prototype_ `AActor* GetMutable(EActorAccess Access);`
- L121 _public function_ `inline AActor* GetOwnedByMassMutable()` — @return none const pointer to the actor	only if owned by mass
- L124 _public function_ `inline const AActor* Get() const` — @return none const pointer to the actor	only if owned by mass
- L125 _public prototype_ `const AActor* Get(EActorAccess Access) const;`
- L128 _public function_ `inline bool IsOwnedByMass() const` — @return if the actor is owned by mass
- L131 _public function_ `inline bool IsValid() const` — @return if the actor is a valid pointer
- L136 _private member_ `TWeakObjectPtr<AActor> Actor;` — `UPROPERTY(VisibleAnywhere, Category="Mass", Transient)` — made visible for debugging purposes. It will show up in Mass's gameplay debugger category when viewing fragment details
- L139 _private member_ `bool bIsOwnedByMass = false;` — Ownership of the actor

#### enum `FMassActorFragment::EActorAccess`  
`enum class EActorAccess`  
_L77-82_
- L79 _public enumerator_ `OnlyWhenAlive` — Only return an actor pointer if the actor is alive. This is the default.
- L80 _public enumerator_ `IncludePendingKill` — Return an actor pointer even if the actor is marked for destruction.
- L81 _public enumerator_ `IncludeUnreachable` — Return an actor pointer even if the actor is unreachable. This implies it's being destroyed.

#### struct `FMassActorManager`  
`struct FMassActorManager : public TSharedFromThis<FMassActorManager>`  
_L142-182_
- inherits: `TSharedFromThis<FMassActorManager>`
- L145 _public prototype_ `explicit FMassActorManager(const TSharedPtr<FMassEntityManager>& EntityManager, UObject* InOwner = nullptr);`
- L148 _public prototype_ `FMassEntityHandle GetEntityHandleFromActor(const TObjectKey<const AActor> Actor);` — Get mass handle from an actor
- L151 _public prototype_ `void SetHandleForActor(const TObjectKey<const AActor> Actor, const FMassEntityHandle Handle);` — Set the mass handle associated to an actor
- L154 _public prototype_ `void RemoveHandleForActor(const TObjectKey<const AActor> Actor);` — Remove entry associated to an actor
- L157 _public prototype_ `AActor* GetActorFromHandle(const FMassEntityHandle Handle, FMassActorFragment::EActorAccess Access = FMassActorFragment::EActorAccess::OnlyWhenAlive) const;` — Get an actor pointer from a mass handle
- L164 _public prototype_ `void DisconnectActor(const TObjectKey<const AActor> Actor, const FMassEntityHandle Handle);` — Removes the connection between Actor and the given entity. Does all the required book keeping (as opposed to straight up RemoveHandleForActor call). If the Handle doesn't match Actor no action is taken.
- L167 _public function_ `int32 DebugGetRegisteredActorCount() const` — @return The number of actors with their associated entity registered in the manager
- L175 _protected member_ `TMap<TObjectKey<const AActor>, FMassEntityHandle> ActorHandleMap;`
- L176 _protected prototype_ `UE_MT_DECLARE_RW_ACCESS_DETECTOR(ActorHandleMapDetector);`
- L178 _protected member_ `TSharedPtr<FMassEntityManager> EntityManager;`
- L181 _protected member_ `TWeakObjectPtr<UObject> Owner;` — Points at an UObject hosting this instance of the FMassActorManager. It's fine for this to be null.

#### class `UMassActorSubsystem`  
`class UMassActorSubsystem : public UMassSubsystemBase`  
_L188-222_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassSubsystemBase`
- desc: A subsystem managing communication between Actors and Mass
- L194 _public prototype_ `inline FMassEntityHandle GetEntityHandleFromActor(const TObjectKey<const AActor> Actor);` — Get mass handle from an actor
- L197 _public prototype_ `inline void SetHandleForActor(const TObjectKey<const AActor> Actor, const FMassEntityHandle Handle);` — Set the mass handle associated to an actor
- L200 _public prototype_ `inline void RemoveHandleForActor(const TObjectKey<const AActor> Actor);` — Remove entry associated to an actor
- L203 _public prototype_ `inline AActor* GetActorFromHandle(const FMassEntityHandle Handle, FMassActorFragment::EActorAccess Access = FMassActorFragment::EActorAccess::OnlyWhenAlive) const;` — Get an actor pointer from a mass handle
- L210 _public prototype_ `inline void DisconnectActor(const TObjectKey<const AActor> Actor, const FMassEntityHandle Handle);` — Removes the connection between Actor and the given entity. Does all the required book keeping (as opposed to straight up RemoveHandleForActor call). If the Handle doesn't match Actor no action is taken.
- L213 _public prototype_ `inline int32 DebugGetRegisteredActorCount() const;` — @return The number of actors with their associated entity registered in the subsystem
- L217 _protected prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;` — USubsystem BEGIN
- L218 _protected prototype_ `virtual void Deinitialize() override;`
- L221 _protected member_ `TSharedPtr<FMassActorManager> ActorManager;`
- L237 _function_ `FMassEntityHandle UMassActorSubsystem::GetEntityHandleFromActor(const TObjectKey<const AActor> Actor)`
- L242 _function_ `void UMassActorSubsystem::SetHandleForActor(const TObjectKey<const AActor> Actor, const FMassEntityHandle Handle)`
- L247 _function_ `void UMassActorSubsystem::RemoveHandleForActor(const TObjectKey<const AActor> Actor)`
- L252 _function_ `AActor* UMassActorSubsystem::GetActorFromHandle(const FMassEntityHandle Handle, FMassActorFragment::EActorAccess Access) const`
- L258 _function_ `void UMassActorSubsystem::DisconnectActor(const TObjectKey<const AActor> Actor, const FMassEntityHandle Handle)`
- L263 _function_ `int32 UMassActorSubsystem::DebugGetRegisteredActorCount() const`

#### struct `TMassExternalSubsystemTraits`  
`template<> struct TMassExternalSubsystemTraits<UMassActorSubsystem> final`  
_L225-232_

#### enum `TMassExternalSubsystemTraits::(anonymous)`  
``  
_L228-231_

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API MASSACTORS_API`
- L59 _enumerator_ `AuthorAcceptsItsNotTriviallyCopyable = true` (scope `TMassFragmentTraits::__anon417c809c0103`)
- L63 _namespace_ `namespace UE`
- L63 _namespace_ `namespace Mass` (scope `UE`)
- L63 _namespace_ `namespace Signals` (scope `UE::Mass`)
- L66 _variable_ `const FName ActorInstanceHandleChanged = FName(TEXT("Acto` (scope `UE::Mass::Signals`) — Signal use when the actor instance handle is set or cleared in the associated fragment.
- L229 _enumerator_ `GameThreadOnly = false` (scope `TMassExternalSubsystemTraits::__anon417c809c0203`)
- L230 _enumerator_ `ThreadSafeWrite = false` (scope `TMassExternalSubsystemTraits::__anon417c809c0203`)

### `Plugins/Runtime/MassGameplay/Source/MassActors/Public/MassActorTypes.h` (Public)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMassActor, Warning, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMassActor, Warning, All);`

### `Plugins/Runtime/MassGameplay/Source/MassActors/Public/MassAgentComponent.h` (Public)


#### enum `EAgentComponentState`  
`enum class EAgentComponentState : uint8`  
_L15-29_
- reflection: `UENUM()`
- L17 _public enumerator_ `None` — Default starting state
- L20 _public enumerator_ `EntityPendingCreation` — States of actors needing mass entity creation
- L21 _public enumerator_ `EntityCreated` — Actor with a created entity
- L24 _public enumerator_ `PuppetPendingInitialization` — States are for Actor driven by Mass (puppet) needing fragments initialization
- L25 _public enumerator_ `PuppetInitialized` — Puppet actor with all initialized fragments
- L26 _public enumerator_ `PuppetPaused` — Puppet actor with all fragments removed
- L27 _public enumerator_ `PuppetPendingReplication` — Replicated puppet actor waiting for NetID
- L28 _public enumerator_ `PuppetReplicatedOrphan` — Replicated puppet actor not associated to a MassAgent

#### class `UMassAgentComponent`  
`class UMassAgentComponent : public UActorComponent`  
_L43-163_
- reflection: `UCLASS(MinimalAPI, Blueprintable, ClassGroup = Mass, meta = (BlueprintSpawnableComponent), hidecategories = (Sockets, Collision))`
- inherits: `UActorComponent`
- desc: There are two primary use cases for this component: 1. If placed on an AActor blueprint it lets the user specify additional fragments that will be created for entities spawned based on this given blueprint. 2. If present on an actor in the world it makes it communicate with the MassSimulation which will create an entity representing given actor. Use case 1) will also be applicable in this case. The component is unregistered by default and requires manual enabling via a 'Enable' call. @todo use case 2) is currently sitting in a shelved CL of mine. Will be worked on next.
- L49 _public prototype_ `UMassAgentComponent();`
- L52 _protected prototype_ `virtual void OnRegister() override;`
- L53 _protected prototype_ `virtual void OnUnregister() override;`
- L56 _protected prototype_ `virtual void PostInitProperties() override;`
- L57 _protected prototype_ `virtual void PostLoad() override;`
- L58 _protected prototype_ `virtual void PostDuplicate(const bool bDuplicateForPIE) override;`
- L59 _protected prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L64 _public prototype_ `void RegisterWithAgentSubsystem();` — Support poolable mass agents going into stasis
- L65 _public prototype_ `void UnregisterWithAgentSubsystem();`
- L66 _public prototype_ `bool IsReadyForPooling() const;`
- L71 _public function_ `FMassEntityHandle GetEntityHandle() const` — Methods handling the state for actors that needs mass entity creation
- L72 _public prototype_ `void SetEntityHandle(const FMassEntityHandle NewHandle);`
- L73 _public prototype_ `void ClearEntityHandle();`
- L74 _public prototype_ `void EntityCreationPending();`
- L75 _public prototype_ `void EntityCreationAborted();`
- L76 _public function_ `bool IsEntityPendingCreation() const`
- L79 _public prototype_ `void SetPuppetHandle(const FMassEntityHandle NewHandle);` — Methods handling the state of puppet actors that needs fragments initialization
- L80 _public prototype_ `void PuppetInitializationPending();`
- L81 _public prototype_ `void PuppetInitializationDone();`
- L82 _public prototype_ `void PuppetInitializationAborted();`
- L84 _public prototype_ `void PuppetReplicationAborted();` — Called when a puppet actor is destroyed before its NetID was replicated (e.g., Iris relevancy).
- L85 _public prototype_ `void PuppetUnregistrationDone();`
- L86 _public function_ `bool IsPuppetPendingInitialization() const`
- L87 _public function_ `bool IsPuppetReplicationPending() const`
- L88 _public function_ `bool IsPuppet() const`
- L94 _public prototype_ `void PausePuppet(const bool bPause);` — Re-adds/Removes all puppet fragments added on the mass agent This is only supported in Puppet flow @param bPause true to pause or false to unpause
- L96 _public function_ `bool IsPuppetPaused() const` — @return boolean whether this component was paused via PausePuppet method
- L99 _public prototype_ `void PuppetReplicationPending();` — Methods handling the state of a server replicated puppet
- L100 _public prototype_ `void SetReplicatedPuppetHandle(FMassEntityHandle NewHandle);`
- L101 _public prototype_ `void ClearReplicatedPuppetHandle();`
- L102 _public prototype_ `void MakePuppetAReplicatedOrphan();`
- L104 _public function_ `FMassEntityTemplateID GetTemplateID() const`
- L106 _public function_ `const FMassEntityConfig& GetEntityConfig() const`
- L107 _public prototype_ `void SetEntityConfig(const FMassEntityConfig& InEntityConfig);`
- L109 _public function_ `const FMassArchetypeCompositionDescriptor& GetPuppetSpecificAddition() const`
- L110 _public function_ `FMassArchetypeCompositionDescriptor& GetMutablePuppetSpecificAddition()`
- L114 _public prototype_ `void Enable();` — `UFUNCTION(BlueprintCallable, Category = Mass)` — Registers the component with the owner effectively turning it on. Calling it multiple times won't break anything
- L118 _public prototype_ `void Disable();` — `UFUNCTION(BlueprintCallable, Category = Mass)` — Registers the component with the owner effectively turning it off
- L121 _public prototype_ `void KillEntity(const bool bDestroyActor);` — `UFUNCTION(BlueprintCallable, Category = Mass)`
- L124 _public prototype_ `virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;`
- L127 _public function_ `FMassNetworkID GetNetID() const`
- L133 _public prototype_ `virtual void OnRep_NetID();` — `UFUNCTION()`
- L137 _protected prototype_ `void SwitchToState(EAgentComponentState NewState);`
- L138 _protected prototype_ `virtual void SetEntityHandleInternal(const FMassEntityHandle NewHandle);`
- L139 _protected prototype_ `void ClearEntityHandleInternal();`
- L140 _protected prototype_ `void DebugCheckStateConsistency();`
- L146 _protected member_ `FMassArchetypeCompositionDescriptor PuppetSpecificAddition;` — Contains all the fragments added to the entity during puppet's initialization. Required for clean up when despawning puppet while the entity remains alive.
- L149 _protected member_ `FMassEntityConfig EntityConfig;` — `UPROPERTY(EditAnywhere, Category = "Mass")`
- L151 _protected member_ `FMassEntityHandle AgentHandle;`
- L152 _protected member_ `FMassEntityTemplateID TemplateID;`
- L154 _protected member_ `EAgentComponentState State;`
- L157 _protected member_ `FMassNetworkID NetID;` — `UPROPERTY(replicatedUsing = OnRep_NetID)`
- L161 _protected member_ `uint32 bAutoRegisterInEditorMode : 1;` — `UPROPERTY(EditAnywhere, Category = "Mass")`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MASSACTORS_API`

### `Plugins/Runtime/MassGameplay/Source/MassActors/Public/MassAgentSubsystem.h` (Public)


#### struct `FMassAgentInitializationQueue`  
`struct FMassAgentInitializationQueue`  
_L30-36_
- reflection: `USTRUCT()`
- L35 _public member_ `TArray<TObjectPtr<UMassAgentComponent>> AgentComponents;` — `UPROPERTY()`

#### class `UMassAgentSubsystem`  
`class UMassAgentSubsystem : public UMassSubsystemBase`  
_L42-151_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassSubsystemBase`
- desc: A subsystem managing communication between Actors and Mass
- L48 _protected prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;` — USubsystem BEGIN
- L49 _protected prototype_ `virtual void Deinitialize() override;`
- L55 _public prototype_ `FMassEntityTemplateID RegisterAgentComponent(UMassAgentComponent& AgentComp);` — Registers given AgentComp with the Mass Simulation, including creation of a FMassEntityHandle using UMassAgentComponent.LWComponentList to determine the Archetype to use.
- L60 _public prototype_ `void UpdateAgentComponent(const UMassAgentComponent& AgentComp);` — Called for AgentComp that has already been registered with the Agent Manager to notify it that AgentComp's Mass-relevant properties had changed, most notably its fragment composition. The Agent Manager will update the information on Mass side potentially reallocating the associated entity to a different archetype
- L67 _public prototype_ `void UnregisterAgentComponent(UMassAgentComponent& AgentComp);` — Removes given AgentComp instance from the system. If there's an entity created with the AgentComp instance then it will be destroyed. @param AgentComp the component to unregister from the system
- L73 _public prototype_ `void ShutdownAgentComponent(UMassAgentComponent& AgentComp);` — Same as UnregisterAgentComponent, but on top of that it tells the system it will never register again @param AgentComp the component to shutdown from the system
- L76 _public prototype_ `void MakePuppet(UMassAgentComponent& AgentComp);` — lets the system know given agent is a puppet (an unreal-side representation of a mass entity)
- L82 _public prototype_ `void NotifyMassAgentComponentReplicated(UMassAgentComponent& AgentComp);` — Notifies that this MassAgentComponent is now replicated with a valid NetID @param AgentComp that is now replicated
- L88 _public prototype_ `void NotifyMassAgentComponentEntityAssociated(const UMassAgentComponent& AgentComp) const;` — Notifies that this MassAgentComponent is now associated to a mass entity @param AgentComp that is now associated to a mass entity
- L94 _public prototype_ `void NotifyMassAgentComponentEntityDetaching(const UMassAgentComponent& AgentComp) const;` — Notifies that this MassAgentComponent is now detaching from its mass entity @param AgentComp that is detaching from its mass entity
- L99 _public function_ `UE::MassActor::FMassAgentComponentDelegate& GetOnMassAgentComponentEntityAssociated()` — @return The delegate of when MassAgentComponent gets associated to a mass entity
- L107 _public function_ `UE::MassActor::FMassAgentComponentDelegate& GetOnMassAgentComponentEntityDetaching()` — @return The delegate of when MassAgentComponent is detaching from its mass entity
- L117 _protected prototype_ `void HandlePendingInitialization();` — Processes PendingAgentEntities to initialize fragments of recently created agent entities and PendingPuppets to create and initialize puppet-specific fragments
- L120 _protected prototype_ `void OnProcessingPhaseStarted(const float DeltaSeconds, const EMassProcessingPhase Phase);` — Bound to UMassSimulationSubsystem.OnProcessingPhaseStartedDelegate and called before every processing phase start
- L123 _protected prototype_ `void OnMassAgentAddedToReplication(FMassNetworkID NetID, FMassEntityHandle Entity);` — Callback registered to the replication manager when a mass agent is added to the replication (client only)
- L126 _protected prototype_ `void OnMassAgentRemovedFromReplication(FMassNetworkID NetID, FMassEntityHandle Entity);` — Callback registered to the replication manager when a mass agent is removed from the replication (client only)
- L129 _protected member_ `TSharedPtr<FMassEntityManager> EntityManager;`
- L132 _protected member_ `TObjectPtr<UMassSpawnerSubsystem> SpawnerSystem;` — `UPROPERTY()`
- L135 _protected member_ `TObjectPtr<UMassSimulationSubsystem> SimulationSystem;` — `UPROPERTY()`
- L138 _protected member_ `TMap<FMassEntityTemplateID, FMassAgentInitializationQueue> PendingAgentEntities;` — `UPROPERTY()`
- L141 _protected member_ `TMap<FMassEntityTemplateID, FMassAgentInitializationQueue> PendingPuppets;` — `UPROPERTY()`
- L144 _protected member_ `TObjectPtr<UMassReplicationSubsystem> ReplicationSubsystem;` — `UPROPERTY()`
- L147 _protected member_ `TMap<FMassNetworkID, TObjectPtr<UMassAgentComponent>> ReplicatedAgentComponents;` — `UPROPERTY()`
- L149 _protected member_ `UE::MassActor::FMassAgentComponentDelegate OnMassAgentComponentEntityAssociated;`
- L150 _protected member_ `UE::MassActor::FMassAgentComponentDelegate OnMassAgentComponentEntityDetaching;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MASSACTORS_API`
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace MassActor` (scope `UE`)
- L25 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FMassAgentComponentDelegate, const UMassAgentComponent& );`
- L25 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FMassAgentComponentDelegate, const UMassAgentComponent& );` (scope `UE::MassActor`)

### `Plugins/Runtime/MassGameplay/Source/MassActors/Public/MassAgentTraits.h` (Public)


#### class `UMassAgentSyncTrait`  
`class UMassAgentSyncTrait : public UMassEntityTraitBase`  
_L15-26_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UMassEntityTraitBase`
- L20 _public function_ `EMassTranslationDirection GetSyncDirection() const`
- L21 _public function_ `void SetSyncDirection(const EMassTranslationDirection NewDirection)`
- L25 _protected member_ `EMassTranslationDirection SyncDirection = EMassTranslationDirection::BothWays;` — `UPROPERTY(EditAnywhere, Category = Mass)`

#### class `UMassAgentCapsuleCollisionSyncTrait`  
`class UMassAgentCapsuleCollisionSyncTrait : public UMassAgentSyncTrait`  
_L31-40_
- reflection: `UCLASS(MinimalAPI, BlueprintType, EditInlineNew, CollapseCategories, meta = (DisplayName = "Agent Capsule Collision Sync"))`
- inherits: `UMassAgentSyncTrait`
- desc: The trait initializes the entity with actor capsule component's radius. In addition, if bSyncTransform is true the trait keeps actor capsule component's and entity's transforms in sync.
- L36 _protected prototype_ `virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;`
- L39 _protected member_ `bool bSyncTransform = true;` — `UPROPERTY(EditAnywhere, Category = Mass)`

#### class `UMassAgentMovementSyncTrait`  
`class UMassAgentMovementSyncTrait : public UMassAgentSyncTrait`  
_L43-49_
- reflection: `UCLASS(MinimalAPI, BlueprintType, EditInlineNew, CollapseCategories, meta = (DisplayName = "Agent Movement Sync"))`
- inherits: `UMassAgentSyncTrait`
- L48 _protected prototype_ `virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;`

#### class `UMassAgentOrientationSyncTrait`  
`class UMassAgentOrientationSyncTrait : public UMassAgentSyncTrait`  
_L52-58_
- reflection: `UCLASS(MinimalAPI, BlueprintType, EditInlineNew, CollapseCategories, meta = (DisplayName = "Agent Orientation Sync"))`
- inherits: `UMassAgentSyncTrait`
- L57 _protected prototype_ `virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;`

#### class `UMassAgentFeetLocationSyncTrait`  
`class UMassAgentFeetLocationSyncTrait : public UMassAgentSyncTrait`  
_L61-67_
- reflection: `UCLASS(MinimalAPI, BlueprintType, EditInlineNew, CollapseCategories, meta = (DisplayName = "Agent Feet Location Sync"))`
- inherits: `UMassAgentSyncTrait`
- L66 _protected prototype_ `virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;`

### `Plugins/Runtime/MassGameplay/Source/MassActors/Public/Translators/MassCapsuleComponentTranslators.h` (Public)


#### struct `FCapsuleComponentWrapperFragment`  
`struct FCapsuleComponentWrapperFragment : public FObjectWrapperFragment`  
_L17-21_
- reflection: `USTRUCT()`
- inherits: `FObjectWrapperFragment`
- L20 _public member_ `TWeakObjectPtr<UCapsuleComponent> Component;`

#### struct `FMassCapsuleTransformCopyToMassTag`  
`struct FMassCapsuleTransformCopyToMassTag : public FMassTag`  
_L32-35_
- reflection: `USTRUCT()`
- inherits: `FMassTag`
- desc: @todo TBD I'm a bit on a fence regarding having separate tags per copy direction. My concern is that we can end up with a very dispersed entity population spread across multiple archetypes storing a small number of entities each. An alternative would be to have a property on the Wrapper fragment, but that doesn't sit well with me either, since that data would be essentially static, meaning it will (in most cases) never change for a given entity, and we could waste a lot of time iterating over fragments just to check that specific value.

#### class `UMassCapsuleTransformToMassTranslator`  
`class UMassCapsuleTransformToMassTranslator : public UMassTranslator`  
_L38-49_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassTranslator`
- L42 _public prototype_ `UMassCapsuleTransformToMassTranslator();`
- L45 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L46 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L48 _protected member_ `FMassEntityQuery EntityQuery;`

#### struct `FMassCapsuleTransformCopyToActorTag`  
`struct FMassCapsuleTransformCopyToActorTag : public FMassTag`  
_L52-55_
- reflection: `USTRUCT()`
- inherits: `FMassTag`

#### class `UMassTransformToActorCapsuleTranslator`  
`class UMassTransformToActorCapsuleTranslator : public UMassTranslator`  
_L58-69_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassTranslator`
- L62 _public prototype_ `UMassTransformToActorCapsuleTranslator();`
- L65 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L66 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L68 _protected member_ `FMassEntityQuery EntityQuery;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MASSACTORS_API`

### `Plugins/Runtime/MassGameplay/Source/MassActors/Public/Translators/MassCharacterMovementTranslators.h` (Public)


#### struct `FCharacterMovementComponentWrapperFragment`  
`struct FCharacterMovementComponentWrapperFragment : public FObjectWrapperFragment`  
_L16-20_
- reflection: `USTRUCT()`
- inherits: `FObjectWrapperFragment`
- L19 _public member_ `TWeakObjectPtr<UCharacterMovementComponent> Component;`

#### struct `FMassCharacterMovementCopyToMassTag`  
`struct FMassCharacterMovementCopyToMassTag : public FMassTag`  
_L23-26_
- reflection: `USTRUCT()`
- inherits: `FMassTag`

#### class `UMassCharacterMovementToMassTranslator`  
`class UMassCharacterMovementToMassTranslator : public UMassTranslator`  
_L29-41_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassTranslator`
- L34 _public prototype_ `UMassCharacterMovementToMassTranslator();`
- L37 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L38 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L40 _protected member_ `FMassEntityQuery EntityQuery;`

#### struct `FMassCharacterMovementCopyToActorTag`  
`struct FMassCharacterMovementCopyToActorTag : public FMassTag`  
_L44-47_
- reflection: `USTRUCT()`
- inherits: `FMassTag`

#### class `UMassCharacterMovementToActorTranslator`  
`class UMassCharacterMovementToActorTranslator : public UMassTranslator`  
_L51-63_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassTranslator`
- L56 _public prototype_ `UMassCharacterMovementToActorTranslator();`
- L59 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L60 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L62 _protected member_ `FMassEntityQuery EntityQuery;`

#### struct `FMassCharacterOrientationCopyToMassTag`  
`struct FMassCharacterOrientationCopyToMassTag : public FMassTag`  
_L67-70_
- reflection: `USTRUCT()`
- inherits: `FMassTag`

#### class `UMassCharacterOrientationToMassTranslator`  
`class UMassCharacterOrientationToMassTranslator : public UMassTranslator`  
_L73-85_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassTranslator`
- L78 _public prototype_ `UMassCharacterOrientationToMassTranslator();`
- L81 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L82 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L84 _protected member_ `FMassEntityQuery EntityQuery;`

#### struct `FMassCharacterOrientationCopyToActorTag`  
`struct FMassCharacterOrientationCopyToActorTag : public FMassTag`  
_L88-91_
- reflection: `USTRUCT()`
- inherits: `FMassTag`

#### class `UMassCharacterOrientationToActorTranslator`  
`class UMassCharacterOrientationToActorTranslator : public UMassTranslator`  
_L95-107_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassTranslator`
- L100 _public prototype_ `UMassCharacterOrientationToActorTranslator();`
- L103 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L104 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L106 _protected member_ `FMassEntityQuery EntityQuery;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MASSACTORS_API`

### `Plugins/Runtime/MassGameplay/Source/MassActors/Public/Translators/MassSceneComponentLocationTranslator.h` (Public)


#### struct `FMassSceneComponentWrapperFragment`  
`struct FMassSceneComponentWrapperFragment : public FObjectWrapperFragment`  
_L14-18_
- reflection: `USTRUCT()`
- inherits: `FObjectWrapperFragment`
- L17 _public member_ `TWeakObjectPtr<USceneComponent> Component;`

#### struct `FMassSceneComponentLocationCopyToMassTag`  
`struct FMassSceneComponentLocationCopyToMassTag : public FMassTag`  
_L21-24_
- reflection: `USTRUCT()`
- inherits: `FMassTag`

#### class `UMassSceneComponentLocationToMassTranslator`  
`class UMassSceneComponentLocationToMassTranslator : public UMassTranslator`  
_L27-39_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassTranslator`
- L32 _public prototype_ `UMassSceneComponentLocationToMassTranslator();`
- L35 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L36 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L38 _protected member_ `FMassEntityQuery EntityQuery;`

#### struct `FMassSceneComponentLocationCopyToActorTag`  
`struct FMassSceneComponentLocationCopyToActorTag : public FMassTag`  
_L43-46_
- reflection: `USTRUCT()`
- inherits: `FMassTag`

#### class `UMassSceneComponentLocationToActorTranslator`  
`class UMassSceneComponentLocationToActorTranslator : public UMassTranslator`  
_L49-61_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassTranslator`
- L54 _public prototype_ `UMassSceneComponentLocationToActorTranslator();`
- L57 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L58 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L60 _protected member_ `FMassEntityQuery EntityQuery;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MASSACTORS_API`

### `Plugins/Runtime/MassGameplay/Source/MassActors/Public/Translators/MassSceneComponentVelocityTranslator.h` (Public)


#### struct `FMassSceneComponentVelocityCopyToMassTag`  
`struct FMassSceneComponentVelocityCopyToMassTag : public FMassTag`  
_L12-15_
- reflection: `USTRUCT()`
- inherits: `FMassTag`

#### class `UMassSceneComponentVelocityToMassTranslator`  
`class UMassSceneComponentVelocityToMassTranslator : public UMassTranslator`  
_L18-30_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassTranslator`
- L23 _public prototype_ `UMassSceneComponentVelocityToMassTranslator();`
- L26 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L27 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L29 _protected member_ `FMassEntityQuery EntityQuery;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MASSACTORS_API`

### `Plugins/Runtime/MassGameplay/Source/MassActors/Public/Translators/MassTranslators_BehaviorTree.h` (Public)


#### struct `FDataFragment_BehaviorTreeComponentWrapper`  
`struct FDataFragment_BehaviorTreeComponentWrapper : public FObjectWrapperFragment`  
_L16-20_
- reflection: `USTRUCT()`
- inherits: `FObjectWrapperFragment`
- L19 _public member_ `TWeakObjectPtr<UBehaviorTreeComponent> Component;`

#### class `UMassTranslator_BehaviorTree`  
`class UMassTranslator_BehaviorTree : public UMassTranslator`  
_L23-35_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassTranslator`
- L28 _public prototype_ `UMassTranslator_BehaviorTree();`
- L31 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L32 _protected function_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override`
- L34 _protected member_ `FMassEntityQuery EntityQuery;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MASSACTORS_API`
