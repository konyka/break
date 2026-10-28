# Plugins / MassSmartObjects

- module root: `Plugins/Runtime/MassGameplay/Source/MassSmartObjects`
- headers: 11; symbols: 251
- symbol kinds: class=16, delegate=1, enum=5, enumerator=9, function=21, macro=7, member=81, namespace=15, prototype=66, struct=26, variable=4
- PrivateDependencyModuleNames: MassActors
- PublicDependencyModuleNames: Core, CoreUObject, Engine, GameplayTags, MassCommon, MassCore, MassEntity, MassGameplayExternalTraits, MassLOD, MassMovement, MassSignals, MassSimulation, MassSpawner, SmartObjectsModule, ZoneGraph, ZoneGraphAnnotations

### `Plugins/Runtime/MassGameplay/Source/MassSmartObjects/Public/IMassSmartObjectsModule.h` (Public)


#### class `IMassSmartObjectsModule`  
`class IMassSmartObjectsModule : public IModuleInterface`  
_L14-39_
- inherits: `IModuleInterface`
- desc: The public interface to this module.  In most cases, this interface is only public to sibling modules within this plugin.
- L25 _public function_ `static inline IMassSmartObjectsModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L35 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Plugins/Runtime/MassGameplay/Source/MassSmartObjects/Public/MassSmartObjectBehaviorDefinition.h` (Public)


#### struct `FMassBehaviorEntityContext`  
`struct FMassBehaviorEntityContext`  
_L22-33_
- desc: Struct to pass around the required set of information to activate a mass behavior definition on a given entity. Context must be created on stack and not kept around since EntityView validity is not guaranteed.
- L24 _public prototype_ `FMassBehaviorEntityContext() = delete;`
- L26 _public function_ `FMassBehaviorEntityContext(FMassEntityView&& InEntityView, USmartObjectSubsystem& InSubsystem) : EntityView(MoveTemp(InEntityView)) , SmartObjectSubsystem(InSubsystem)`
- L31 _public member_ `const FMassEntityView EntityView;`
- L32 _public member_ `USmartObjectSubsystem& SmartObjectSubsystem;`

#### class `USmartObjectMassBehaviorDefinition`  
`class USmartObjectMassBehaviorDefinition : public USmartObjectBehaviorDefinition`  
_L40-57_
- reflection: `UCLASS(MinimalAPI, EditInlineNew)`
- inherits: `USmartObjectBehaviorDefinition`
- desc: Base class for MassAIBehavior definitions. This is the type of definitions that MassEntity queries will look for. Definition subclass can parameterized its associated behavior by overriding method Activate.
- L46 _public prototype_ `virtual void Activate(FMassCommandBuffer& CommandBuffer, const FMassBehaviorEntityContext& EntityContext) const;` — This virtual method allows subclasses to configure the MassEntity based on their parameters (e.g. Add fragments)
- L49 _public prototype_ `virtual void Deactivate(FMassCommandBuffer& CommandBuffer, const FMassBehaviorEntityContext& EntityContext) const;` — This virtual method allows subclasses to update the MassEntity on interaction deactivation (e.g. Remove fragments)
- L56 _public member_ `float UseTime;` — `UPROPERTY(EditDefaultsOnly, Category = SmartObject)` — Indicates the amount of time the Massentity will execute its behavior when reaching the smart object.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MASSSMARTOBJECTS_API`

### `Plugins/Runtime/MassGameplay/Source/MassSmartObjects/Public/MassSmartObjectFragments.h` (Public)


#### struct `FMassSmartObjectUserFragment`  
`struct FMassSmartObjectUserFragment : public FMassFragment`  
_L15-37_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- desc: Fragment used by an entity to be able to interact with smart objects
- L21 _public member_ `FGameplayTagContainer UserTags;` — `UPROPERTY(Transient)` — Tags describing the smart object user.
- L25 _public member_ `FSmartObjectClaimHandle InteractionHandle;` — `UPROPERTY(Transient)` — Claim handle for the currently active smart object interaction.
- L29 _public member_ `EMassSmartObjectInteractionStatus InteractionStatus = EMassSmartObjectInteractionStatus::Unset;` — `UPROPERTY(Transient)` — Status of the current active smart object interaction.
- L36 _public member_ `double InteractionCooldownEndTime = 0.;` — `UPROPERTY(Transient)` — World time in seconds before which the user is considered in cooldown and won't look for new interactions (value of 0 indicates no cooldown).

#### struct `TMassFragmentTraits`  
`template<> struct TMassFragmentTraits<FMassSmartObjectUserFragment> final`  
_L40-46_

#### enum `TMassFragmentTraits::(anonymous)`  
``  
_L43-45_

#### struct `FMassSmartObjectTimedBehaviorFragment`  
`struct FMassSmartObjectTimedBehaviorFragment : public FMassFragment`  
_L50-56_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- desc: Fragment used to process time based smartobject interactions
- L55 _public member_ `float UseTime = 0.f;` — `UPROPERTY(Transient)`

#### struct `UE::Mass::SmartObject::FMRUSlotsFragment`  
`struct FMRUSlotsFragment : public FMassFragment`  
_L63-69_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- desc: Fragment used to track most recently used slots for a given smart object user
- L68 _public member_ `FMRUSlots Slots;` — `UPROPERTY(Transient)`

#### Free symbols / members of external scopes

- L44 _enumerator_ `AuthorAcceptsItsNotTriviallyCopyable = true` (scope `TMassFragmentTraits::__anon92035b3e0103`)
- L58 _namespace_ `namespace UE`
- L58 _namespace_ `namespace Mass` (scope `UE`)
- L58 _namespace_ `namespace SmartObject` (scope `UE::Mass`)

### `Plugins/Runtime/MassGameplay/Source/MassSmartObjects/Public/MassSmartObjectHandler.h` (Public)


#### struct `FMassSmartObjectHandler`  
`struct FMassSmartObjectHandler`  
_L26-144_
- desc: Mediator struct that encapsulates communication between SmartObjectSubsystem and Mass. This object is meant to be created and used in method scope to guarantee subsystems validity.
- L34 _public function_ `FMassSmartObjectHandler(FMassExecutionContext& InExecutionContext, USmartObjectSubsystem& InSmartObjectSubsystem, UMassSignalSubsystem& InSignalSubsystem) : ExecutionContext(InExecutionContext) , SmartObjectSubsystem(InSmartObjectSubsystem) , SignalSubsystem(InSignalSubsystem)` — FMassSmartObjectHandler constructor @param InExecutionContext is the current execution context of the entity subsystem @param InSmartObjectSubsystem is the smart object subsystem @param InSignalSubsystem is the mass signal subsystem to use to send signal to affected entities
- L42 _public function_ `FMassSmartObjectHandler(FMassEntityManager& InEntityManager, FMassExecutionContext& InExecutionContext, USmartObjectSubsystem& InSmartObjectSubsystem, UMassSignalSubsystem& InSignalSubsystem) : FMassSmartObjectHandler(InExecutionContext, InSmartObjectSubsystem, InSignalSubsystem)` — `UE_DEPRECATED(5.6, "Use the other constructor that doesn't require MassEntityManager")`
- L56 _public prototype_ `[[nodiscard]] FMassSmartObjectRequestID FindCandidatesAsync(const FMassEntityHandle RequestingEntity, const FGameplayTagContainer& UserTags, const FGameplayTagQuery& ActivityRequirements, const FVector& Location) const;` — `UE_DEPRECATED(5.7, "Use the overload taking FFindCandidatesParameters instead")` — Creates an async request to build a list of compatible smart objects around the provided location. The caller must poll using the request id to know when the reservation can be done. @param RequestingEntity Entity requesting the candidates list @param Location The center of the query @return Request identifier that can be used to try claiming a result once available
- L67 _public prototype_ `[[nodiscard]] FMassSmartObjectRequestID FindCandidatesAsync(const FMassEntityHandle RequestingEntity, const FGameplayTagContainer& UserTags, const FGameplayTagQuery& ActivityRequirements, const FZoneGraphCompactLaneLocation& LaneLocation) const;` — `UE_DEPRECATED(5.7, "Use the overload taking FFindCandidatesParameters instead")` — Creates an async request to build a list of compatible smart objects around the provided lane location. The caller must poll using the request id to know when the reservation can be done. @param RequestingEntity Entity requesting the candidates list @param LaneLocation The lane location as reference for the query @return Request identifier that can be used to try claiming a result once available
- L77 _public prototype_ `[[nodiscard]] FMassSmartObjectRequestID FindCandidatesAsync(const FMassEntityHandle RequestingEntity, UE::Mass::SmartObject::FFindCandidatesParameters&& Parameters) const;` — Creates an async request to build a list of compatible smart objects using the provided set of parameters. The caller must poll using the request id to know when the reservation can be done. @param RequestingEntity Entity requesting the candidates list @param Parameters All parameters of the query @return Request identifier that can be used to try claiming a result once available
- L85 _public prototype_ `[[nodiscard]] const FMassSmartObjectCandidateSlots* GetRequestCandidates(const FMassSmartObjectRequestID& RequestID) const;` — Provides the result of a previously created request from FindCandidatesAsync to indicate if it has been processed and the results can be used by ClaimCandidate. @param RequestID A valid request identifier (method will ensure otherwise) @return The current request's result, nullptr if request not ready yet.
- L91 _public prototype_ `void RemoveRequest(const FMassSmartObjectRequestID& RequestID) const;` — Deletes the request associated to the specified identifier @param RequestID A valid request identifier (method will ensure otherwise)
- L101 _public prototype_ `[[nodiscard]] FSmartObjectClaimHandle ClaimCandidate(const FMassEntityHandle Entity, FMassSmartObjectUserFragment& User, const FMassSmartObjectCandidateSlots& Candidates, ESmartObjectClaimPriority ClaimPriority = ESmartObjectClaimPriority::Normal) const;` — Claims the first available smart object from the provided candidates. @param Entity MassEntity associated to the user fragment @param User Fragment of the user claiming @param Candidates Candidate slots to choose from. @param ClaimPriority Claim priority, a slot claimed at lower priority can be claimed by higher priority (unless already in use). @return Whether the slot has been successfully claimed or not
- L112 _public prototype_ `[[nodiscard]] FSmartObjectClaimHandle ClaimSmartObject(const FMassEntityHandle Entity, FMassSmartObjectUserFragment& User, const FSmartObjectRequestResult& RequestResult, ESmartObjectClaimPriority ClaimPriority = ESmartObjectClaimPriority::Normal) const;` — Claims the first available slot holding any type of USmartObjectMassBehaviorDefinition in the smart object associated to the provided identifier. @param Entity MassEntity associated to the user fragment @param User Fragment of the user claiming @param RequestResult A valid smart object request result (method will ensure otherwise) @param ClaimPriority Claim priority, a slot claimed at lower priority can be claimed by higher priority (unless already in use). @return Whether the slot has been successfully claimed or not
- L122 _public prototype_ `bool StartUsingSmartObject(const FMassEntityHandle Entity, FMassSmartObjectUserFragment& User, const FSmartObjectClaimHandle ClaimHandle) const;` — Activates the mass gameplay behavior associated to the previously claimed smart object. @param Entity MassEntity associated to the user fragment @param User Fragment of the user claiming @param ClaimHandle claimed smart object slot to use. @param Transform Fragment holding the transform of the user claiming @return Whether the slot has been successfully claimed or not
- L130 _public prototype_ `void StopUsingSmartObject(const FMassEntityHandle Entity, FMassSmartObjectUserFragment& User, const EMassSmartObjectInteractionStatus NewStatus) const;` — Deactivates the mass gameplay behavior started using StartUsingSmartObject. @param Entity MassEntity associated to the user fragment @param User Fragment of the user claiming @param NewStatus Reason of the deactivation.
- L138 _public prototype_ `void ReleaseSmartObject(const FMassEntityHandle Entity, FMassSmartObjectUserFragment& User, const FSmartObjectClaimHandle ClaimHandle) const;` — Releases a claimed/in-use smart object and update user fragment. @param Entity MassEntity associated to the user fragment @param User Fragment of the user claiming @param ClaimHandle claimed smart object slot to release.
- L141 _private member_ `FMassExecutionContext& ExecutionContext;`
- L142 _private member_ `USmartObjectSubsystem& SmartObjectSubsystem;`
- L143 _private member_ `UMassSignalSubsystem& SignalSubsystem;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MASSSMARTOBJECTS_API`

### `Plugins/Runtime/MassGameplay/Source/MassSmartObjects/Public/MassSmartObjectProcessor.h` (Public)


#### class `UMassSmartObjectCandidatesFinderProcessor`  
`class UMassSmartObjectCandidatesFinderProcessor : public UMassProcessor`  
_L17-37_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassProcessor`
- desc: Processor that builds a list of candidates objects for each users.
- L22 _public prototype_ `UMassSmartObjectCandidatesFinderProcessor();`
- L25 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L26 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L30 _protected member_ `float SearchExtents = 5000.f;` — `UPROPERTY(EditDefaultsOnly, Category = SmartObject, config)` — Extents used to perform the spatial query in the octree for world location queries.
- L33 _protected member_ `FMassEntityQuery WorldRequestQuery;` — Query to fetch and process requests to find smart objects using spacial query around a given world location.
- L36 _protected member_ `FMassEntityQuery LaneRequestQuery;` — Query to fetch and process requests to find smart objects on zone graph lanes.

#### class `UMassSmartObjectTimedBehaviorProcessor`  
`class UMassSmartObjectTimedBehaviorProcessor : public UMassProcessor`  
_L41-52_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassProcessor`
- desc: Processor for time based user's behavior that waits x seconds then releases its claim on the object
- L45 _public prototype_ `UMassSmartObjectTimedBehaviorProcessor();`
- L48 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L49 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L51 _protected member_ `FMassEntityQuery EntityQuery;`

#### class `UMassSmartObjectUserFragmentDeinitializer`  
`class UMassSmartObjectUserFragmentDeinitializer : public UMassObserverProcessor`  
_L56-67_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassObserverProcessor`
- desc: Deinitializer processor to unregister slot invalidation callback when SmartObjectUser fragment gets removed
- L60 _private prototype_ `UMassSmartObjectUserFragmentDeinitializer();`
- L63 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L64 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L66 _protected member_ `FMassEntityQuery EntityQuery;`

#### class `UE::Mass::SmartObject::UMRUSlotsProcessor`  
`class UMRUSlotsProcessor : public UMassProcessor`  
_L73-85_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassProcessor`
- desc: Processor to decay smart object MRU slots
- L78 _public prototype_ `UMRUSlotsProcessor();`
- L81 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L82 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L84 _protected member_ `FMassEntityQuery EntityQuery;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MASSSMARTOBJECTS_API`
- L68 _namespace_ `namespace UE`
- L68 _namespace_ `namespace Mass` (scope `UE`)
- L68 _namespace_ `namespace SmartObject` (scope `UE::Mass`)

### `Plugins/Runtime/MassGameplay/Source/MassSmartObjects/Public/MassSmartObjectRegistration.h` (Public)


#### struct `FMassInActiveSmartObjectsRangeTag`  
`struct FMassInActiveSmartObjectsRangeTag : public FMassTag`  
_L15-18_
- reflection: `USTRUCT()`
- inherits: `FMassTag`
- desc: Mass Tag applied on entities with FFSmartObjectRegistrationFragment that need to create smart objects

#### struct `FSmartObjectRegistrationFragment`  
`struct FSmartObjectRegistrationFragment : public FMassFragment`  
_L22-31_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- desc: Mass Fragment storing the handle associated to the created smart object
- L27 _public member_ `TWeakObjectPtr<USmartObjectDefinition> Asset;` — `UPROPERTY()`
- L30 _public member_ `FSmartObjectHandle Handle;` — `UPROPERTY()`

#### class `UMassSmartObjectInitializerBase`  
`class UMassSmartObjectInitializerBase : public UMassObserverProcessor`  
_L40-52_
- reflection: `UCLASS(Abstract)`
- inherits: `UMassObserverProcessor`
- desc: Processor that signals entities with FSmartObjectRegistration and FMassActorInstanceFragment fragments when the a given tag or fragment is added to an entity. @see FSmartObjectRegistrationFragment @see FMassActorInstanceFragment
- L44 _public prototype_ `UMassSmartObjectInitializerBase();`
- L47 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L48 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L50 _protected member_ `FMassEntityQuery EntityQuery;`
- L51 _protected member_ `FName Signal;`

#### class `UMassSmartObjectDeinitializerBase`  
`class UMassSmartObjectDeinitializerBase : public UMassObserverProcessor`  
_L61-73_
- reflection: `UCLASS(Abstract)`
- inherits: `UMassObserverProcessor`
- desc: Processor that signals entities with FSmartObjectRegistration and FMassActorInstanceFragment fragments when the a given tag or fragment is removed from an entity. @see FSmartObjectRegistrationFragment @see FMassActorInstanceFragment
- L65 _public prototype_ `UMassSmartObjectDeinitializerBase();`
- L68 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L69 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L71 _protected member_ `FMassEntityQuery EntityQuery;`
- L72 _protected member_ `FName Signal;`

#### class `UMassActiveSmartObjectInitializer`  
`class UMassActiveSmartObjectInitializer : public UMassSmartObjectInitializerBase`  
_L79-84_
- reflection: `UCLASS()`
- inherits: `UMassSmartObjectInitializerBase`
- desc: Signals entities with UE::Mass::Signals::SmartObjectActivationChanged when 'FMassInActiveSmartObjectsRangeTag' is added.
- L83 _public prototype_ `UMassActiveSmartObjectInitializer();`

#### class `UMassActiveSmartObjectDeinitializer`  
`class UMassActiveSmartObjectDeinitializer : public UMassSmartObjectDeinitializerBase`  
_L90-96_
- reflection: `UCLASS()`
- inherits: `UMassSmartObjectDeinitializerBase`
- desc: Signals entities with UE::Mass::Signals::SmartObjectActivationChanged when 'FMassInActiveSmartObjectsRangeTag' is removed.
- L95 _public prototype_ `UMassActiveSmartObjectDeinitializer();`

#### class `UMassActorInstanceHandleInitializer`  
`class UMassActorInstanceHandleInitializer : public UMassSmartObjectInitializerBase`  
_L102-107_
- reflection: `UCLASS()`
- inherits: `UMassSmartObjectInitializerBase`
- desc: Signals entities with UE::Mass::Signals::ActorInstanceHandleChanged when 'FMassActorInstanceFragment' is added.
- L106 _public prototype_ `UMassActorInstanceHandleInitializer();`

#### class `UMassActorInstanceHandleDeinitializer`  
`class UMassActorInstanceHandleDeinitializer : public UMassSmartObjectDeinitializerBase`  
_L113-119_
- reflection: `UCLASS()`
- inherits: `UMassSmartObjectDeinitializerBase`
- desc: Signals entities with UE::Mass::Signals::ActorInstanceHandleChanged when 'FMassActorInstanceFragment' is removed.
- L118 _public prototype_ `UMassActorInstanceHandleDeinitializer();`

#### class `UMassActiveSmartObjectSignalProcessor`  
`class UMassActiveSmartObjectSignalProcessor : public UMassSignalProcessorBase`  
_L130-145_
- reflection: `UCLASS()`
- inherits: `UMassSignalProcessorBase`
- desc: Signal based processor that creates and destroys the smart object instance associated to an entity based on valid FSmartObjectRegistration and FMassActorInstance fragments. The registration is processed on the following events: UE::Mass::Signals::ActorInstanceHandleChanged UE::Mass::Signals::SmartObjectActivationChanged @see FFSmartObjectRegistrationFragment
- L135 _public prototype_ `UMassActiveSmartObjectSignalProcessor();`
- L138 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L139 _protected prototype_ `virtual void InitializeInternal(UObject& Owner, const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L140 _protected prototype_ `virtual void SignalEntities(FMassEntityManager& EntityManager, FMassExecutionContext& Context, FMassSignalNameLookup& ) override;`
- L143 _private member_ `FMassEntityQuery InsideSmartObjectActiveRangeQuery;`
- L144 _private member_ `FMassEntityQuery OutsideSmartObjectActiveRangeQuery;`

### `Plugins/Runtime/MassGameplay/Source/MassSmartObjects/Public/MassSmartObjectRequest.h` (Public)


#### struct `FSmartObjectCandidateSlot`  
`struct FSmartObjectCandidateSlot`  
_L20-32_
- reflection: `USTRUCT()`
- desc: Structure that represents a potential smart object slot for a MassEntity during the search
- L24 _public prototype_ `FSmartObjectCandidateSlot() = default;`
- L25 _public function_ `FSmartObjectCandidateSlot(const FSmartObjectRequestResult InResult, const float InCost) : Result(InResult), Cost(InCost)`
- L28 _public member_ `FSmartObjectRequestResult Result;` — `UPROPERTY(VisibleAnywhere, Category = SmartObject, transient)`
- L31 _public member_ `float Cost = 0.f;` — `UPROPERTY(VisibleAnywhere, Category = SmartObject, transient)`

#### struct `FMassSmartObjectRequestID`  
`struct FMassSmartObjectRequestID`  
_L39-54_
- reflection: `USTRUCT()`
- desc: Identifier associated to a request for smart object candidates. We use a 1:1 match with an FMassEntityHandle since all requests are batched together using the EntitySubsystem.
- L43 _public prototype_ `FMassSmartObjectRequestID() = default;`
- L44 _public function_ `explicit FMassSmartObjectRequestID(const FMassEntityHandle InEntity) : Entity(InEntity)`
- L46 _public function_ `bool IsSet() const`
- L47 _public function_ `void Reset()`
- L49 _public function_ `explicit operator FMassEntityHandle() const`
- L53 _private member_ `FMassEntityHandle Entity;` — `UPROPERTY(Transient)`

#### struct `FMassSmartObjectCandidateSlots`  
`struct FMassSmartObjectCandidateSlots`  
_L60-77_
- reflection: `USTRUCT(BlueprintType)`
- desc: Struct that holds status and results of a candidate finder request
- L64 _public function_ `void Reset()`
- L70 _public prototype_ `bool ExportTextItem(FString& ValueStr, const FMassSmartObjectCandidateSlots& DefaultValue, UObject* Parent, int32 PortFlags, UObject* ExportRootScope) const;`
- L72 _public member_ `static constexpr uint32 MaxNumCandidates = 4;`
- L73 _public member_ `TStaticArray<FSmartObjectCandidateSlot, MaxNumCandidates> Slots;`
- L76 _public member_ `uint8 NumSlots = 0;` — `UPROPERTY(Transient, VisibleAnywhere, Category = SmartObject)`
- L79 _function_ `inline bool FMassSmartObjectCandidateSlots::ExportTextItem(FString& ValueStr, const FMassSmartObjectCandidateSlots& DefaultValue, UObject* Parent, const int32 PortFlags, UObject* ExportRootScope) const`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FMassSmartObjectCandidateSlots> : TStructOpsTypeTraitsBase2<FMassSmartObjectCandidateSlots>`  
_L92-98_
- inherits: `TStructOpsTypeTraitsBase2<FMassSmartObjectCandidateSlots>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L95-97_

#### struct `FMassSmartObjectRequestResultFragment`  
`struct FMassSmartObjectRequestResultFragment : public FMassFragment`  
_L104-113_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- desc: Fragment that holds the result of a request to find candidates.
- L109 _public member_ `FMassSmartObjectCandidateSlots Candidates;` — `UPROPERTY(Transient)`
- L112 _public member_ `bool bProcessed = false;` — `UPROPERTY(Transient)`

#### struct `FMassSmartObjectWorldLocationRequestFragment`  
`struct FMassSmartObjectWorldLocationRequestFragment : public FMassFragment`  
_L121-136_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- desc: Fragment used to build a list potential smart objects to use. Once added to an entity this will be processed by the candidates finder processor to fill a SmartObjectCandidates fragment that could then be processed by the reservation processor
- L126 _public member_ `FVector SearchOrigin = FVector::ZeroVector;` — `UPROPERTY(Transient)`
- L129 _public member_ `FMassEntityHandle RequestingEntity;` — `UPROPERTY(Transient)`
- L132 _public member_ `FGameplayTagContainer UserTags;` — `UPROPERTY(Transient)`
- L135 _public member_ `FGameplayTagQuery ActivityRequirements;` — `UPROPERTY(Transient)`

#### struct `TMassFragmentTraits`  
`template<> struct TMassFragmentTraits<FMassSmartObjectWorldLocationRequestFragment> final`  
_L139-145_

#### enum `TMassFragmentTraits::(anonymous)`  
``  
_L142-144_

#### struct `FMassSmartObjectLaneLocationRequestFragment`  
`struct FMassSmartObjectLaneLocationRequestFragment : public FMassFragment`  
_L153-167_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- desc: Fragment used to build a list potential smart objects to use. Once added to an entity this will be processed by the candidates finder processor to fill a SmartObjectCandidates fragment that could then be processed by the reservation processor
- L157 _public member_ `FZoneGraphCompactLaneLocation CompactLaneLocation;`
- L160 _public member_ `FMassEntityHandle RequestingEntity;` — `UPROPERTY(Transient)`
- L163 _public member_ `FGameplayTagContainer UserTags;` — `UPROPERTY(Transient)`
- L166 _public member_ `FGameplayTagQuery ActivityRequirements;` — `UPROPERTY(Transient)`

#### struct `TMassFragmentTraits`  
`template<> struct TMassFragmentTraits<FMassSmartObjectLaneLocationRequestFragment> final`  
_L170-176_

#### enum `TMassFragmentTraits::(anonymous)`  
``  
_L173-175_

#### struct `FMassSmartObjectCompletedRequestTag`  
`struct FMassSmartObjectCompletedRequestTag : public FMassTag`  
_L182-185_
- reflection: `USTRUCT()`
- inherits: `FMassTag`
- desc: Special tag to mark processed requests

#### struct `UE::Mass::SmartObject::FFindCandidatesParameters`  
`struct FFindCandidatesParameters`  
_L194-212_
- reflection: `USTRUCT()`
- desc: Struct used to store parameters for FindCandidatesAsync requests
- L199 _public member_ `FGameplayTagContainer UserTags;` — `UPROPERTY(Transient)`
- L202 _public member_ `FGameplayTagQuery ActivityRequirements;` — `UPROPERTY(Transient)`
- L205 _public member_ `FZoneGraphCompactLaneLocation LaneLocation;` — `UPROPERTY(Transient)`
- L208 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(Transient)`
- L211 _public member_ `FMRUSlots MRUSlots;` — `UPROPERTY(Transient)`

#### Free symbols / members of external scopes

- L96 _enumerator_ `WithExportTextItem = true` (scope `TStructOpsTypeTraits::__anon9e1976200103`)
- L143 _enumerator_ `AuthorAcceptsItsNotTriviallyCopyable = true` (scope `TMassFragmentTraits::__anon9e1976200203`)
- L174 _enumerator_ `AuthorAcceptsItsNotTriviallyCopyable = true` (scope `TMassFragmentTraits::__anon9e1976200303`)
- L187 _namespace_ `namespace UE`
- L187 _namespace_ `namespace Mass` (scope `UE`)
- L187 _namespace_ `namespace SmartObject` (scope `UE::Mass`)

### `Plugins/Runtime/MassGameplay/Source/MassSmartObjects/Public/MassSmartObjectSettings.h` (Public)


#### class `UMassSmartObjectSettings`  
`class UMassSmartObjectSettings : public UMassModuleSettings`  
_L20-73_
- reflection: `UCLASS(MinimalAPI, config = Plugins, defaultconfig, DisplayName = "Mass SmartObject")`
- inherits: `UMassModuleSettings`
- desc: Settings for the MassSmartObject module.
- L26 _public member_ `mutable FOnAnnotationSettingsChanged OnAnnotationSettingsChanged;`
- L31 _public member_ `FZoneGraphTag SmartObjectTag;` — `UPROPERTY(EditDefaultsOnly, Category = ZoneGraph, config)` — Tag used to indicate that smart objects are associated to a lane for queries using lanes.
- L35 _public member_ `float SearchExtents = 500.f;` — `UPROPERTY(EditDefaultsOnly, Category = ZoneGraph, config)` — Extents used to find precomputed entry points to reach a smart object from a zone graph lane.
- L48 _public member_ `int32 MRUSlotsMaxCount = 0;` — `UPROPERTY(EditDefaultsOnly, Category = SmartObject, config, meta = (UIMin = "0", ClampMin = "0", UIMax = "4", ClampMax = "4", DisplayName = ""))`
- L57 _public member_ `bool bUseCooldownForMRUSlots = false;` — `UPROPERTY(config, EditAnywhere, Category = SmartObject, meta = (EditCondition = "MRUSlotsMaxCount > 0", EditConditionHides))` — Set this flag to allow the most recently used slots to be considered again after the period of time specified by MRUSlotsCooldown This option requires MRUSlotsMaxCount to be a non-zero value @see MRUSlotsCooldown @see MRUSlotsMaxCount
- L66 _public member_ `float MRUSlotsCooldown = 0.f;` — `UPROPERTY(EditDefaultsOnly, Category = SmartObject, config, meta = (UIMin = "0", ClampMin = "0", EditCondition = "MRUSlotsMaxCount > 0 && bUseCooldownForMRUSlots", EditConditionHides))` — Period of time during which a given slot will not be considered after being used This option requires 'bUseCooldownForMRUSlots' to be true and 'MRUSlotsMaxCount' to be a non-zero value @see bUseCooldownForMRUSlots @see MRUSlotsMaxCount
- L71 _protected prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MASSSMARTOBJECTS_API`
- L13 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnAnnotationSettingsChanged);` — Called when annotation tag settings changed.
- L13 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnAnnotationSettingsChanged);` — Called when annotation tag settings changed.

### `Plugins/Runtime/MassGameplay/Source/MassSmartObjects/Public/MassSmartObjectTypes.h` (Public)


#### enum `EMassSmartObjectInteractionStatus`  
`enum class EMassSmartObjectInteractionStatus : uint8`  
_L23-30_
- reflection: `UENUM()`
- L25 _public enumerator_ `Unset`
- L26 _public enumerator_ `InProgress` — Claimed and Behavior activated
- L27 _public enumerator_ `BehaviorCompleted` — Behavior is completed but task still running (not updated yet)
- L28 _public enumerator_ `TaskCompleted` — Task has been notified that behavior is completed and completes
- L29 _public enumerator_ `Aborted` — Task and Behavior were aborted

#### struct `FSmartObjectMassEntityUserData`  
`struct FSmartObjectMassEntityUserData`  
_L64-73_
- reflection: `USTRUCT()`
- desc: Struct that can be used to pass data to the find or filtering methods. Properties will be used as external data to fill values expected by the world condition schema specified by the smart object definition. e.g. FilterSlotsBySelectionConditions(SlotHandles, FConstStructView::Make(FSmartObjectMassEntityUserData(Entity))); It can be inherited from to provide additional data to another world condition schema inheriting from USmartObjectWorldConditionSchema. e.g. UCLASS() class USmartObjectWorldConditionExtendedSchema : public USmartObjectWorldConditionSchema { ... USmartObjectWorldConditionExtendedSchema(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) { OtherEntityRef = AddContextDataDesc(TEXT("OtherEntity"), FMassEntityHandle::StaticStruct(), EWorldConditionContextDataType::Dynamic); } FWorldConditionContextDataRef OtherEntityRef; }; USTRUCT() struct FSmartObjectMassEntityExtendedUserData : public FSmartObjectMassEntityUserData { UPROPERTY() FMassEntityHandle OtherEntity; } The struct can also be used to be added to a Smart Object slot when it gets claimed. e.g. Claim(SlotHandle, FConstStructView::Make(FSmartObjectMassEntityUserData(Entity)));
- L68 _public prototype_ `FSmartObjectMassEntityUserData() = default;`
- L69 _public function_ `explicit FSmartObjectMassEntityUserData(const FMassEntityHandle InEntityHandle) : UserEntity(InEntityHandle)`
- L72 _public member_ `FMassEntityHandle UserEntity;` — `UPROPERTY()`

#### struct `UE::Mass::SmartObject::FMRUSlot`  
`struct FMRUSlot`  
_L82-93_
- reflection: `USTRUCT()`
- desc: Struct holding data related to a single recently used smart object slot.
- L86 _public member_ `static constexpr float NoCoolDown = -1.f;`
- L89 _public member_ `FSmartObjectSlotHandle Slot;` — `UPROPERTY(VisibleAnywhere, Category = SmartObject, transient)`
- L92 _public member_ `float RemainingTime = NoCoolDown;` — `UPROPERTY(VisibleAnywhere, Category = SmartObject, transient)`

#### struct `UE::Mass::SmartObject::FMRUSlots`  
`struct FMRUSlots`  
_L99-119_
- reflection: `USTRUCT()`
- desc: Struct used as a container for the most recently used slots.
- L103 _public function_ `void Reset()`
- L108 _public prototype_ `void Push(const FSmartObjectSlotHandle& ClaimedSlot);`
- L109 _public prototype_ `void AppendTo(TArray<FSmartObjectSlotHandle>& OutSlots) const;`
- L112 _public member_ `static constexpr uint32 MaxNumSlots = 4;` — Using a fixed maximum number of slots to use fixed inline allocation in the fragments.
- L115 _public member_ `FMRUSlot Slots[MaxNumSlots];` — `UPROPERTY(Transient)`
- L118 _public member_ `uint8 NumSlots = 0;` — `UPROPERTY(Transient)`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MASSSMARTOBJECTS_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Mass` (scope `UE`)
- L14 _namespace_ `namespace Signals` (scope `UE::Mass`)
- L16 _variable_ `const FName SmartObjectRequestCandidates = FName(TEXT("Smar` (scope `UE::Mass::Signals`)
- L17 _variable_ `const FName SmartObjectCandidatesReady = FName(TEXT("Smar` (scope `UE::Mass::Signals`)
- L18 _variable_ `const FName SmartObjectInteractionDone = FName(TEXT("Smar` (scope `UE::Mass::Signals`)
- L19 _variable_ `const FName SmartObjectInteractionAborted = FName(TEXT("Smar` (scope `UE::Mass::Signals`)
- L75 _namespace_ `namespace UE`
- L75 _namespace_ `namespace Mass` (scope `UE`)
- L75 _namespace_ `namespace SmartObject` (scope `UE::Mass`)

### `Plugins/Runtime/MassGameplay/Source/MassSmartObjects/Public/MassSmartObjectUserTrait.h` (Public)


#### class `UMassSmartObjectUserTrait`  
`class UMassSmartObjectUserTrait : public UMassEntityTraitBase`  
_L15-25_
- reflection: `UCLASS(MinimalAPI, meta = (DisplayName = "SmartObject User"))`
- inherits: `UMassEntityTraitBase`
- desc: Trait to allow an entity to interact with SmartObjects
- L20 _protected prototype_ `virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;`
- L24 _protected member_ `FGameplayTagContainer UserTags;` — `UPROPERTY(EditAnywhere, Category = Parameter)` — Tags describing the SmartObject user. Used when searching smart objects.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MASSSMARTOBJECTS_API`

### `Plugins/Runtime/MassGameplay/Source/MassSmartObjects/Public/SmartObjectZoneAnnotations.h` (Public)


#### struct `FSmartObjectLaneLocation`  
`struct FSmartObjectLaneLocation`  
_L18-38_
- reflection: `USTRUCT()`
- desc: Struct to keep track of a SmartObject entry point on a given lane.
- L22 _public prototype_ `FSmartObjectLaneLocation() = default;`
- L23 _public function_ `FSmartObjectLaneLocation(const FSmartObjectHandle InObjectHandle, const int32 InLaneIndex, const float InDistanceAlongLane) : ObjectHandle(InObjectHandle) , LaneIndex(InLaneIndex) , DistanceAlongLane(InDistanceAlongLane)`
- L31 _public member_ `FSmartObjectHandle ObjectHandle;` — `UPROPERTY()`
- L34 _public member_ `int32 LaneIndex = INDEX_NONE;` — `UPROPERTY()`
- L37 _public member_ `float DistanceAlongLane = 0.0f;` — `UPROPERTY()`

#### struct `FSmartObjectLaneLocationIndices`  
`struct FSmartObjectLaneLocationIndices`  
_L45-51_
- reflection: `USTRUCT()`
- desc: Struct to store indices to all entry points on a given lane. Used as a container wrapper to be able to use in a TMap.
- L50 _public member_ `TArray<int32> SmartObjectLaneLocationIndices;` — `UPROPERTY(VisibleAnywhere, Category = SmartObject)`

#### struct `FSmartObjectAnnotationData`  
`struct FSmartObjectAnnotationData`  
_L55-89_
- reflection: `USTRUCT()`
- desc: Per ZoneGraphData smart object look up data.
- L60 _public function_ `bool IsValid() const` — @return True if this entry is valid (associated to a valid zone graph data), false otherwise.
- L63 _public function_ `void Reset()` — Reset all internal data.
- L74 _public member_ `FZoneGraphDataHandle DataHandle;` — `UPROPERTY(VisibleAnywhere, Category = SmartObject)` — Handle of the ZoneGraphData that this smart object annotation data is associated to
- L77 _public member_ `TArray<int32> AffectedLanes;` — `UPROPERTY(VisibleAnywhere, Category = SmartObject)`
- L80 _public member_ `TArray<FSmartObjectLaneLocation> SmartObjectLaneLocations;` — `UPROPERTY(VisibleAnywhere, Category = SmartObject)`
- L83 _public member_ `TMap<FSmartObjectHandle, int32> SmartObjectToLaneLocationIndexLookup;` — `UPROPERTY(VisibleAnywhere, Category = SmartObject)`
- L86 _public member_ `TMap<int32, FSmartObjectLaneLocationIndices> LaneToLaneLocationIndicesLookup;` — `UPROPERTY(VisibleAnywhere, Category = SmartObject)`
- L88 _public member_ `bool bInitialTaggingCompleted = false;`

#### class `USmartObjectZoneAnnotations`  
`class USmartObjectZoneAnnotations : public UZoneGraphAnnotationComponent`  
_L95-156_
- reflection: `UCLASS(MinimalAPI, ClassGroup = AI, BlueprintType, meta = (BlueprintSpawnableComponent))`
- inherits: `UZoneGraphAnnotationComponent`
- desc: ZoneGraph annotations for smart objects
- L100 _public prototype_ `const FSmartObjectAnnotationData* GetAnnotationData(FZoneGraphDataHandle DataHandle) const;`
- L101 _public prototype_ `TOptional<FSmartObjectLaneLocation> GetSmartObjectLaneLocation(const FZoneGraphDataHandle DataHandle, const FSmartObjectHandle SmartObjectHandle) const;`
- L102 _public prototype_ `void ApplyComponentInstanceData(FSmartObjectZoneAnnotationsInstanceData* InstanceData);`
- L104 _public function_ `TConstArrayView<FSmartObjectAnnotationData> GetSmartObjectAnnotations() const`
- L110 _protected prototype_ `virtual void PostSubsystemsInitialized() override;`
- L111 _protected prototype_ `virtual FZoneGraphTagMask GetAnnotationTags() const override;`
- L112 _protected prototype_ `virtual void TickAnnotation(const float DeltaTime, FZoneGraphAnnotationTagContainer& BehaviorTagContainer) override;`
- L114 _protected prototype_ `virtual TStructOnScope<FActorComponentInstanceData> GetComponentInstanceData() const override;`
- L116 _protected prototype_ `virtual void PostZoneGraphDataAdded(const AZoneGraphData& ZoneGraphData) override;`
- L117 _protected prototype_ `virtual void PreZoneGraphDataRemoved(const AZoneGraphData& ZoneGraphData) override;`
- L120 _protected prototype_ `virtual void DebugDraw(FZoneGraphAnnotationSceneProxy* DebugProxy) override;`
- L125 _protected member_ `FZoneGraphTagFilter AffectedLaneTags;` — `UPROPERTY(EditAnywhere, Category = SmartObject)` — Filter specifying which lanes the behavior is applied to.
- L129 _protected member_ `TArray<FSmartObjectAnnotationData> SmartObjectAnnotationDataArray;` — `UPROPERTY(VisibleAnywhere, Category = SmartObject)` — Entry points graph for each ZoneGraphData.
- L133 _protected member_ `FZoneGraphTag BehaviorTag;` — `UPROPERTY(VisibleAnywhere, Category = SmartObject)` — Tag to mark the lanes that offers smart objects.
- L136 _protected prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L137 _protected prototype_ `virtual void OnUnregister() override;`
- L139 _protected prototype_ `void RebuildForSingleGraph(FSmartObjectAnnotationData& Data, const FZoneGraphStorage& Storage);`
- L140 _protected prototype_ `void RebuildForAllGraphs();`
- L142 _protected member_ `FDelegateHandle OnAnnotationSettingsChangedHandle;`
- L143 _protected member_ `FDelegateHandle OnGraphDataChangedHandle;`
- L144 _protected member_ `FDelegateHandle OnMainCollectionChangedHandle;`
- L145 _protected member_ `FDelegateHandle OnMainCollectionDirtiedHandle;`
- L149 _protected prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L150 _protected member_ `bool bRebuildAllGraphsRequested = false;`
- L155 _protected member_ `TObjectPtr<USmartObjectSubsystem> SmartObjectSubsystem = nullptr;` — `UPROPERTY(Transient)` — Cached SmartObjectSubsystem

#### struct `FSmartObjectZoneAnnotationsInstanceData`  
`struct FSmartObjectZoneAnnotationsInstanceData : public FActorComponentInstanceData`  
_L160-190_
- reflection: `USTRUCT()`
- inherits: `FActorComponentInstanceData`
- desc: Used to store data that is considered modified by the UCS and not generically saved during RerunConstructionScripts
- L165 _public prototype_ `FSmartObjectZoneAnnotationsInstanceData() = default;`
- L166 _public function_ `FSmartObjectZoneAnnotationsInstanceData(const USmartObjectZoneAnnotations* SourceComponent) : FActorComponentInstanceData(SourceComponent) , SmartObjectAnnotations(SourceComponent->GetSmartObjectAnnotations())`
- L171 _public prototype_ `virtual ~FSmartObjectZoneAnnotationsInstanceData() = default;`
- L173 _public function_ `virtual bool ContainsData() const override`
- L178 _public function_ `virtual void ApplyToComponent(UActorComponent* Component, const ECacheApplyPhase CacheApplyPhase) override`
- L189 _public member_ `TArray<FSmartObjectAnnotationData> SmartObjectAnnotations;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MASSSMARTOBJECTS_API`
