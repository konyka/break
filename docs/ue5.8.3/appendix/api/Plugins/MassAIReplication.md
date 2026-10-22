# Plugins / MassAIReplication

- module root: `Plugins/AI/MassAI/Source/MassAIReplication`
- headers: 2; symbols: 44
- symbol kinds: class=3, function=10, macro=1, member=15, prototype=14, struct=1
- PrivateDependencyModuleNames: EditorFramework, UnrealEd
- PublicDependencyModuleNames: AIModule, Core, CoreUObject, Engine, MassCommon, MassCore, MassEntity, MassLOD, MassNavigation, MassReplication, MassSimulation, MassSpawner, MassZoneGraphNavigation, NetCore, ZoneGraph

### `Plugins/AI/MassAI/Source/MassAIReplication/Public/IMassAIReplicationModule.h` (Public)


#### class `IMassAIReplicationModule`  
`class IMassAIReplicationModule : public IModuleInterface`  
_L14-39_
- inherits: `IModuleInterface`
- desc: The public interface to this module.  In most cases, this interface is only public to sibling modules within this plugin.
- L25 _public function_ `static inline IMassAIReplicationModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L35 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Plugins/AI/MassAI/Source/MassAIReplication/Public/MassReplicationPathHandlers.h` (Public)


#### struct `FReplicatedAgentPathData`  
`struct FReplicatedAgentPathData`  
_L22-70_
- reflection: `USTRUCT()`
- desc: To replicate path following make a member variable of this class in your FReplicatedAgentBase derived class. In the FReplicatedAgentBase derived class you must also provide an accessor function FReplicatedAgentPathData& GetReplicatedPathDataMutable().
- L28 _public prototype_ `FReplicatedAgentPathData() = default;`
- L29 _public prototype_ `explicit FReplicatedAgentPathData(const FMassZoneGraphPathRequestFragment& RequestFragment, const FMassMoveTargetFragment& MoveTargetFragment, const FMassZoneGraphLaneLocationFragment& LaneLocationFragment);`
- L33 _public prototype_ `void InitEntity(const UWorld& InWorld, const FMassEntityView& InEntityView, FMassZoneGraphLaneLocationFragment& OutLaneLocation, FMassMoveTargetFragment& OutMoveTarget, FMassZoneGraphPathRequestFragment& OutActionRequest) const;`
- L39 _public prototype_ `void ApplyToEntity(const UWorld& InWorld, const FMassEntityView& InEntityView) const;`
- L42 _public member_ `mutable FZoneGraphShortPathRequest PathRequest;` — `UPROPERTY(Transient)`
- L46 _public member_ `FZoneGraphLaneHandle LaneHandle;` — `UPROPERTY(Transient)` — Handle to current lane.
- L50 _public member_ `double ActionServerStartTime = 0.;` — `UPROPERTY(Transient)` — Server time in seconds when the action started.
- L54 _public member_ `float DistanceAlongLane = 0.0f;` — `UPROPERTY(Transient)` — Distance along current lane.
- L58 _public member_ `float LaneLength = 0.0f;` — `UPROPERTY(Transient)` — Cached lane length, used for clamping and testing if at end of lane.
- L62 _public member_ `FMassInt16Real DesiredSpeed = FMassInt16Real(0.0f);` — `UPROPERTY(Transient)` — Requested movement speed.
- L65 _public member_ `uint16 ActionID = 0;` — `UPROPERTY(Transient)`
- L69 _public member_ `EMassMovementAction Action = EMassMovementAction::Move;` — `UPROPERTY(Transient)` — Current movement action.

#### class `TMassClientBubblePathHandler`  
`template<typename AgentArrayItem> class TMassClientBubblePathHandler`  
_L78-114_
- desc: To replicate path following make a member variable of this class in your TClientBubbleHandlerBase derived class. This class is a friend of TMassClientBubblePathHandler. It is meant to have access to the protected data declared there.
- L81 _public function_ `TMassClientBubblePathHandler(TClientBubbleHandlerBase<AgentArrayItem>& InOwnerHandler) : OwnerHandler(InOwnerHandler)`
- L87 _public prototype_ `void SetBubblePathData(const FMassReplicatedAgentHandle Handle, const FMassZoneGraphPathRequestFragment& PathRequest, const FMassMoveTargetFragment& MoveTargetFragment, const FMassZoneGraphLaneLocationFragment& LaneLocationFragment);` — Sets the path data in the client bubble on the server
- L98 _public prototype_ `static void AddRequirementsForSpawnQuery(FMassEntityQuery& InQuery);` — When entities are spawned in Mass by the replication system on the client, a spawn query is used to set the data on the spawned entities. The following functions are used to configure the query and then set that data for path following.
- L99 _public prototype_ `void CacheFragmentViewsForSpawnQuery(FMassExecutionContext& InExecContext);`
- L100 _public prototype_ `void ClearFragmentViewsForSpawnQuery();`
- L102 _public prototype_ `void SetSpawnedEntityData(const FMassEntityView& EntityView, const FReplicatedAgentPathData& ReplicatedPathData, const int32 EntityIdx) const;`
- L105 _public prototype_ `void SetModifiedEntityData(const FMassEntityView& EntityView, const FReplicatedAgentPathData& ReplicatedPathData) const;` — Call this when an Entity that has already been spawned is modified on the client
- L109 _protected member_ `TArrayView<FMassZoneGraphPathRequestFragment> PathRequestList;`
- L110 _protected member_ `TArrayView<FMassMoveTargetFragment> MoveTargetList;`
- L111 _protected member_ `TArrayView<FMassZoneGraphLaneLocationFragment> LaneLocationList;`
- L113 _protected member_ `TClientBubbleHandlerBase<AgentArrayItem>& OwnerHandler;`
- L118 _function_ `template<typename AgentArrayItem> void TMassClientBubblePathHandler<AgentArrayItem>::SetBubblePathData(const FMassReplicatedAgentHandle Handle, const FMassZoneGraphPathRequestFragment& PathRequestFragment, const FMassMoveTargetFragment& MoveTargetFragment, const FMassZoneGraphLaneLocationFragment& LaneLocationFragment)`
- L141 _function_ `template<typename AgentArrayItem> void TMassClientBubblePathHandler<AgentArrayItem>::AddRequirementsForSpawnQuery(FMassEntityQuery& InQuery)`
- L151 _function_ `template<typename AgentArrayItem> void TMassClientBubblePathHandler<AgentArrayItem>::CacheFragmentViewsForSpawnQuery(FMassExecutionContext& InExecContext)`
- L161 _function_ `template<typename AgentArrayItem> void TMassClientBubblePathHandler<AgentArrayItem>::ClearFragmentViewsForSpawnQuery()`
- L171 _function_ `template<typename AgentArrayItem> void TMassClientBubblePathHandler<AgentArrayItem>::SetSpawnedEntityData(const FMassEntityView& EntityView, const FReplicatedAgentPathData& ReplicatedPathData, const int32 EntityIdx) const`
- L181 _function_ `template<typename AgentArrayItem> void TMassClientBubblePathHandler<AgentArrayItem>::SetModifiedEntityData(const FMassEntityView& EntityView, const FReplicatedAgentPathData& ReplicatedPathData) const`

#### class `FMassReplicationProcessorPathHandler`  
`class FMassReplicationProcessorPathHandler`  
_L194-223_
- desc: Used to replicate path following by your UMassReplicationProcessorBase derived class. This class should only get used on the server. @todo add #if UE_REPLICATION_COMPILE_SERVER_CODE
- L198 _public prototype_ `static void AddRequirements(FMassEntityQuery& InQuery);` — Adds the requirements for the path following to the query.
- L201 _public prototype_ `void CacheFragmentViews(FMassExecutionContext& ExecContext);` — Cache any component views you want to, this will get called before we iterate through entities.
- L208 _public prototype_ `void AddEntity(const int32 EntityIdx, FReplicatedAgentPathData& InOUtReplicatedPathData) const;` — Set the replicated path data when we are adding an entity to the client bubble. @param EntityIdx the index of the entity in fragment views that have been cached. @param InOUtReplicatedPathData the data to set.
- L218 _public prototype_ `template<typename AgentArrayItem> void ModifyEntity(const FMassReplicatedAgentHandle Handle, const int32 EntityIdx, TMassClientBubblePathHandler<AgentArrayItem>& BubblePathHandler, bool bLastClient);` — Set the replicated path data when we are modifying an entity that already exists in the client bubble. @param Handle to the agent in the TMassClientBubbleHandler (that TMassClientBubblePathHandler is a member variable of). @param EntityIdx the index of the entity in fragment views that have been cached. @param BubblePathHandler handler to actually set the data in the client bubble @param bLastClient means it safe to reset any dirtiness
- L220 _public member_ `TArrayView<FMassZoneGraphPathRequestFragment> PathRequestList;`
- L221 _public member_ `TArrayView<FMassMoveTargetFragment> MoveTargetList;`
- L222 _public member_ `TArrayView<FMassZoneGraphLaneLocationFragment> LaneLocationList;`
- L226 _function_ `template<typename AgentArrayItem> void FMassReplicationProcessorPathHandler::ModifyEntity(const FMassReplicatedAgentHandle Handle, const int32 EntityIdx, TMassClientBubblePathHandler<AgentArrayItem>& BubblePathHandler, bool bLastClient)`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MASSAIREPLICATION_API`
