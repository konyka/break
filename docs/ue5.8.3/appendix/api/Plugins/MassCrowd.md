# Plugins / MassCrowd

- module root: `Plugins/AI/MassCrowd/Source/MassCrowd`
- headers: 24; symbols: 346
- symbol kinds: class=26, delegate=3, enum=6, enumerator=14, function=29, macro=15, member=108, namespace=4, prototype=111, struct=24, typedef=6
- PublicDependencyModuleNames: AIModule, Core, CoreUObject, Engine, MassAIBehavior, MassAIReplication, MassActors, MassCommon, MassCore, MassEntity, MassLOD, MassMovement, MassNavigation, MassReplication, MassRepresentation, MassSignals, MassSimulation, MassSpawner, MassZoneGraphNavigation, NetCore, StateTreeModule, ZoneGraph, ZoneGraphAnnotations, ZoneGraphDebug

### `Plugins/AI/MassCrowd/Source/MassCrowd/Public/IMassCrowdModule.h` (Public)


#### class `IMassCrowdModule`  
`class IMassCrowdModule : public IModuleInterface`  
_L14-39_
- inherits: `IModuleInterface`
- desc: The public interface to this module.  In most cases, this interface is only public to sibling modules within this plugin.
- L25 _public function_ `static inline IMassCrowdModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L35 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Plugins/AI/MassCrowd/Source/MassCrowd/Public/MassCrowdBubble.h` (Public)


#### class `FMassCrowdClientBubbleHandler`  
`class FMassCrowdClientBubbleHandler : public TClientBubbleHandlerBase<FCrowdFastArrayItem>`  
_L17-53_
- inherits: `TClientBubbleHandlerBase<FCrowdFastArrayItem>`
- L20 _public typedef_ `typedef TClientBubbleHandlerBase<FCrowdFastArrayItem> Super;`
- L21 _public typedef_ `typedef TMassClientBubblePathHandler<FCrowdFastArrayItem> FMassClientBubblePathHandler;`
- L22 _public typedef_ `typedef TMassClientBubbleTransformHandler<FCrowdFastArrayItem> FMassClientBubbleTransformHandler;`
- L24 _public function_ `FMassCrowdClientBubbleHandler() : PathHandler(*this) , TransformHandler(*this)`
- L30 _public function_ `const FMassClientBubblePathHandler& GetPathHandler() const`
- L31 _public function_ `FMassClientBubblePathHandler& GetPathHandlerMutable()`
- L33 _public function_ `const FMassClientBubbleTransformHandler& GetTransformHandler() const`
- L34 _public function_ `FMassClientBubbleTransformHandler& GetTransformHandlerMutable()`
- L40 _protected prototype_ `virtual void PostReplicatedAdd(const TArrayView<int32> AddedIndices, int32 FinalSize) override;`
- L41 _protected prototype_ `virtual void PostReplicatedChange(const TArrayView<int32> ChangedIndices, int32 FinalSize) override;`
- L43 _protected prototype_ `void PostReplicatedChangeEntity(const FMassEntityView& EntityView, const FReplicatedCrowdAgent& Item) const;`
- L47 _protected prototype_ `virtual void DebugValidateBubbleOnServer() override;`
- L48 _protected prototype_ `virtual void DebugValidateBubbleOnClient() override;`
- L51 _protected member_ `FMassClientBubblePathHandler PathHandler;`
- L52 _protected member_ `FMassClientBubbleTransformHandler TransformHandler;`

#### struct `FMassCrowdClientBubbleSerializer`  
`struct FMassCrowdClientBubbleSerializer : public FMassClientBubbleSerializerBase`  
_L57-80_
- reflection: `USTRUCT()`
- inherits: `FMassClientBubbleSerializerBase`
- desc: Mass client bubble, there will be one of these per client and it will handle replicating the fast array of Agents between the server and clients
- L61 _public function_ `FMassCrowdClientBubbleSerializer()`
- L66 _public function_ `bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParams)`
- L72 _public member_ `FMassCrowdClientBubbleHandler Bubble;`
- L79 _protected member_ `TArray<FCrowdFastArrayItem> Crowd;` — `UPROPERTY(Transient)` — Fast Array of Agents for efficient replication. Maintained as a freelist on the server, to keep index consistency as indexes are used as Handles into the Array Note array order is not guaranteed between server and client so handles will not be consistent between them, FMassNetworkID will be.

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FMassCrowdClientBubbleSerializer> : public TStructOpsTypeTraitsBase2<FMassCrowdClientBubbleSerializer>`  
_L83-90_
- inherits: `TStructOpsTypeTraitsBase2<FMassCrowdClientBubbleSerializer>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L86-89_

#### class `AMassCrowdClientBubbleInfo`  
`class AMassCrowdClientBubbleInfo : public AMassClientBubbleInfoBase`  
_L97-112_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `AMassClientBubbleInfoBase`
- desc: This class will allow us to replicate Mass data based on the fidelity required for each player controller. There is one AMassReplicationActor per PlayerController and which is also its owner.
- L102 _public prototype_ `AMassCrowdClientBubbleInfo(const FObjectInitializer& ObjectInitializer);`
- L104 _public function_ `FMassCrowdClientBubbleSerializer& GetCrowdSerializer()`
- L107 _protected prototype_ `virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;`
- L111 _protected member_ `FMassCrowdClientBubbleSerializer CrowdSerializer;` — `UPROPERTY(Replicated, Transient)`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MASSCROWD_API`
- L87 _enumerator_ `WithNetDeltaSerializer = true` (scope `TStructOpsTypeTraits::__anonfcb93aa70103`)
- L88 _enumerator_ `WithCopy = false` (scope `TStructOpsTypeTraits::__anonfcb93aa70103`)

### `Plugins/AI/MassCrowd/Source/MassCrowd/Public/MassCrowdFragments.h` (Public)


#### struct `FMassCrowdTag`  
`struct FMassCrowdTag : public FMassTag`  
_L15-18_
- reflection: `USTRUCT()`
- inherits: `FMassTag`
- desc: Special tag to differentiate the crowd from the rest of the other entities Should not contain any data, this is purely a tag

#### struct `FMassCrowdLaneTrackingFragment`  
`struct FMassCrowdLaneTrackingFragment : public FMassFragment`  
_L24-28_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- desc: Data fragment to store the last lane the agent was tracked on.
- L27 _public member_ `FZoneGraphLaneHandle TrackedLaneHandle;`

#### struct `FMassCrowdObstacleFragment`  
`struct FMassCrowdObstacleFragment : public FMassFragment`  
_L32-47_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- L37 _public member_ `FMassLaneObstacleID LaneObstacleID;` — Obstacle ID reported to the obstruction annotation.
- L40 _public member_ `FVector LastPosition = FVector::ZeroVector;` — Position of the obstacle when it last moved.
- L43 _public member_ `float TimeSinceStopped = 0.0f;` — Time since the obstacle has not moved based on speed tolerance.
- L46 _public member_ `bool bIsMoving = true;` — True of the current obstacle state is moving.

### `Plugins/AI/MassCrowd/Source/MassCrowd/Public/MassCrowdLaneClosingTest.h` (Public)


#### class `UZoneGraphCloseCrowdLaneTest`  
`class UZoneGraphCloseCrowdLaneTest : public UZoneLaneTest`  
_L12-33_
- reflection: `UCLASS()`
- inherits: `UZoneLaneTest`
- L17 _protected prototype_ `virtual void OnLaneLocationUpdated(const FZoneGraphLaneLocation& PrevLaneLocation, const FZoneGraphLaneLocation& NextLaneLocation) override;`
- L18 _protected prototype_ `virtual void Draw(FPrimitiveDrawInterface* PDI) const override;`
- L19 _protected prototype_ `virtual void OnOwnerSet() override;`
- L23 _private member_ `FZoneGraphLaneLocation LaneLocation;` — `UPROPERTY(Transient)`
- L26 _private member_ `TObjectPtr<UMassCrowdSubsystem> CrowdSubsystem;` — `UPROPERTY(Transient)`
- L29 _private member_ `ECrowdLaneState LaneState = ECrowdLaneState::Closed;` — `UPROPERTY(EditAnywhere, Category = Test)`
- L32 _private member_ `ECrowdLaneState PrevLaneState = ECrowdLaneState::Opened;` — `UPROPERTY(VisibleAnywhere, Transient, Category = Test)`

### `Plugins/AI/MassCrowd/Source/MassCrowd/Public/MassCrowdLaneDataRenderingComponent.h` (Public)


#### class `UMassCrowdLaneDataRenderingComponent`  
`class UMassCrowdLaneDataRenderingComponent : public UPrimitiveComponent`  
_L15-35_
- reflection: `UCLASS(MinimalAPI, editinlinenew, meta = (BlueprintSpawnableComponent), hidecategories = (Object, LOD, Lighting, VirtualTexture, Transform, HLOD, Collision, TextureStreaming, Mobile, Physics, Tags, AssetUserData, Activation, Cooking, Rendering, Navigation))`
- inherits: `UPrimitiveComponent`
- desc: Primitive component that can be used to render runtime state of zone graph lanes (e.g. Opened|Closed, Density, etc.) The component must be added on a ZoneGraphData actor.
- L20 _public prototype_ `UMassCrowdLaneDataRenderingComponent() = default;`
- L24 _private prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy() override;`
- L25 _private prototype_ `virtual void OnRegister() override;`
- L26 _private prototype_ `virtual void OnUnregister() override;`
- L27 _private prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;`
- L28 _private prototype_ `void DebugDrawOnCanvas(UCanvas* Canvas, APlayerController*) const;`
- L29 _private member_ `FDelegateHandle DebugTextDrawingDelegateHandle;`
- L30 _private member_ `FDelegateHandle OnLaneStateChangedDelegateHandle;`
- L32 _private member_ `FDelegateHandle OnLaneRenderSettingsChangedDelegateHandle;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MASSCROWD_API`

### `Plugins/AI/MassCrowd/Source/MassCrowd/Public/MassCrowdMemberTrait.h` (Public)


#### class `UMassCrowdMemberTrait`  
`class UMassCrowdMemberTrait : public UMassEntityTraitBase`  
_L14-20_
- reflection: `UCLASS(MinimalAPI, meta = (DisplayName = "CrowdMember"))`
- inherits: `UMassEntityTraitBase`
- desc: Trait to mark an entity with the crowd tag and add required fragments to track current lane
- L19 _protected prototype_ `virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MASSCROWD_API`

### `Plugins/AI/MassCrowd/Source/MassCrowd/Public/MassCrowdNavigationProcessor.h` (Public)


#### class `UMassCrowdLaneTrackingSignalProcessor`  
`class UMassCrowdLaneTrackingSignalProcessor : public UMassSignalProcessorBase`  
_L17-27_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassSignalProcessorBase`
- desc: Processor that monitors when entities change lane and notify the MassCrowd subsystem.
- L21 _public prototype_ `UMassCrowdLaneTrackingSignalProcessor();`
- L24 _protected prototype_ `virtual void InitializeInternal(UObject& Owner, const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L25 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L26 _protected prototype_ `virtual void SignalEntities(FMassEntityManager& EntityManager, FMassExecutionContext& Context, FMassSignalNameLookup& ) override;`

#### class `UMassCrowdLaneTrackingDestructor`  
`class UMassCrowdLaneTrackingDestructor : public UMassObserverProcessor`  
_L31-43_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassObserverProcessor`
- desc: Processors that cleans up the lane tracking on entity destruction.
- L36 _public prototype_ `UMassCrowdLaneTrackingDestructor();`
- L39 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L40 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L42 _protected member_ `FMassEntityQuery EntityQuery;`

#### class `UMassCrowdDynamicObstacleProcessor`  
`class UMassCrowdDynamicObstacleProcessor : public UMassProcessor`  
_L47-66_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassProcessor`
- L52 _public prototype_ `UMassCrowdDynamicObstacleProcessor();`
- L55 _protected prototype_ `virtual void InitializeInternal(UObject& Owner, const TSharedRef<FMassEntityManager>& EntityManager)override;`
- L56 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L57 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context);`
- L59 _protected prototype_ `void OnStop(FMassCrowdObstacleFragment& OutObstacle, const float Radius);`
- L60 _protected prototype_ `void OnMove(FMassCrowdObstacleFragment& OutObstacle);`
- L62 _protected member_ `FMassEntityQuery EntityQuery_Conditional;`
- L65 _protected member_ `TObjectPtr<UZoneGraphAnnotationSubsystem> ZoneGraphAnnotationSubsystem;` — `UPROPERTY(Transient)`

#### class `UMassCrowdDynamicObstacleInitializer`  
`class UMassCrowdDynamicObstacleInitializer : public UMassObserverProcessor`  
_L70-82_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassObserverProcessor`
- L75 _public prototype_ `UMassCrowdDynamicObstacleInitializer();`
- L78 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L79 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L81 _protected member_ `FMassEntityQuery EntityQuery;`

#### class `UMassCrowdDynamicObstacleDeinitializer`  
`class UMassCrowdDynamicObstacleDeinitializer : public UMassObserverProcessor`  
_L86-102_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassObserverProcessor`
- L91 _public prototype_ `UMassCrowdDynamicObstacleDeinitializer();`
- L94 _protected prototype_ `virtual void InitializeInternal(UObject& Owner, const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L95 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L96 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L99 _protected member_ `TObjectPtr<UZoneGraphAnnotationSubsystem> ZoneGraphAnnotationSubsystem;` — `UPROPERTY(Transient)`
- L101 _protected member_ `FMassEntityQuery EntityQuery;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MASSCROWD_API`

### `Plugins/AI/MassCrowd/Source/MassCrowd/Public/MassCrowdReplicatedAgent.h` (Public)


#### struct `FReplicatedCrowdAgent`  
`struct FReplicatedCrowdAgent : public FReplicatedAgentBase`  
_L13-33_
- reflection: `USTRUCT()`
- inherits: `FReplicatedAgentBase`
- desc: The data that is replicated specific to each Crowd agent
- L17 _public function_ `const FReplicatedAgentPathData& GetReplicatedPathData() const`
- L20 _public function_ `FReplicatedAgentPathData& GetReplicatedPathDataMutable()` — This function is required to be provided in FReplicatedAgentBase derived classes that use FReplicatedAgentPathData
- L22 _public function_ `const FReplicatedAgentPositionYawData& GetReplicatedPositionYawData() const`
- L25 _public function_ `FReplicatedAgentPositionYawData& GetReplicatedPositionYawDataMutable()` — This function is required to be provided in FReplicatedAgentBase derived classes that use FReplicatedAgentPositionYawData
- L29 _private member_ `FReplicatedAgentPathData Path;` — `UPROPERTY(Transient)`
- L32 _private member_ `FReplicatedAgentPositionYawData PositionYaw;` — `UPROPERTY(Transient)`

#### struct `FCrowdFastArrayItem`  
`struct FCrowdFastArrayItem : public FMassFastArrayItemBase`  
_L37-52_
- reflection: `USTRUCT()`
- inherits: `FMassFastArrayItemBase`
- desc: Fast array item for efficient agent replication. Remember to make this dirty if any FReplicatedCrowdAgent member variables are modified
- L41 _public prototype_ `FCrowdFastArrayItem() = default;`
- L42 _public function_ `FCrowdFastArrayItem(const FReplicatedCrowdAgent& InAgent, const FMassReplicatedAgentHandle InHandle) : FMassFastArrayItemBase(InHandle) , Agent(InAgent)`
- L48 _public typedef_ `typedef FReplicatedCrowdAgent FReplicatedAgentType;` — This typedef is required to be provided in FMassFastArrayItemBase derived classes (with the associated FReplicatedAgentBase derived class)
- L51 _public member_ `FReplicatedCrowdAgent Agent;` — `UPROPERTY()`

### `Plugins/AI/MassCrowd/Source/MassCrowd/Public/MassCrowdReplicator.h` (Public)


#### class `UMassCrowdReplicator`  
`class UMassCrowdReplicator : public UMassReplicatorBase`  
_L12-28_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassReplicatorBase`
- desc: Class that handles replication and only runs on the server. It queries Mass entity fragments and sets those values when appropriate using the MassClientBubbleHandler.
- L21 _public prototype_ `virtual void AddRequirements(FMassEntityQuery& EntityQuery) override;` — Overridden to add specific entity query requirements for replication. Usually we add replication processor handler requirements.
- L27 _public prototype_ `virtual void ProcessClientReplication(FMassExecutionContext& Context, FMassReplicationContext& ReplicationContext) override;` — Overridden to process the client replication. This methods should call CalculateClientReplication with the appropriate callback implementation.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MASSCROWD_API`

### `Plugins/AI/MassCrowd/Source/MassCrowd/Public/MassCrowdRepresentationActorManagement.h` (Public)


#### class `UMassCrowdRepresentationActorManagement`  
`class UMassCrowdRepresentationActorManagement : public UMassRepresentationActorManagement`  
_L15-54_
- reflection: `UCLASS(MinimalAPI, abstract)`
- inherits: `UMassRepresentationActorManagement`
- desc: Overridden representation processor to make it tied to the crowd via the requirements. It is also the base class for all the different type of crowd representation (Visualization & ServerSideRepresentation)
- L28 _protected prototype_ `virtual void SetActorEnabled(const EMassActorEnabledType EnabledType, AActor& Actor, const int32 EntityIdx, FMassCommandBuffer& CommandBuffer) const override;` — Enable/disable a spawned actor @param EnabledType is the type of enabling to do on this actor @param Actor is the actual actor to perform enabling type on @param EntityIdx is the entity index currently processing @param Context is the current Mass execution context
- L42 _protected prototype_ `virtual AActor* GetOrSpawnActor(UMassRepresentationSubsystem& RepresentationSubsystem, FMassEntityManager& EntityManager , const FMassEntityHandle MassAgent, const FTransform& Transform, const int16 TemplateActorIndex , FMassActorSpawnRequestHandle& SpawnRequestHandle, const float Priority) const override;` — Returns an actor of the template type and setup fragments values from it @param RepresentationSubsystem to use to get or spawn the actor @param EntitySubsystem associated to the mass agent @param MassAgent is the handle to the associated mass agent @param ActorInfo is the fragment where we are going to store the actor pointer @param Transform is the spatial information about where to spawn the actor @param TemplateActorIndex is the index of the type fetched with UMassRepresentationSubsystem::FindOrAddTemplateActor() @param SpawnRequestHandle (in/out) In: previously requested spawn Out: newly requested spawn @param Priority of this spawn request in comparison with the others, lower value means higher priority @return the actor spawned
- L53 _protected prototype_ `virtual void TeleportActor(const FTransform& Transform, AActor& Actor, FMassCommandBuffer& CommandBuffer) const override;` — Teleports the actor at the specified transform by preserving its velocity and without collision. The destination will be adjusted to fit an existing capsule. @param Transform is the new actor's transform @param Actor is the actual actor to teleport @param Context is the current Mass execution context

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MASSCROWD_API`

### `Plugins/AI/MassCrowd/Source/MassCrowd/Public/MassCrowdRepresentationSubsystem.h` (Public)


#### class `UMassCrowdRepresentationSubsystem`  
`class UMassCrowdRepresentationSubsystem : public UMassRepresentationSubsystem`  
_L14-22_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassRepresentationSubsystem`
- desc: Subsystem responsible for all visual of mass crowd agents, will handle actors spawning and static mesh instances
- L20 _protected prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;` — USubsystem BEGIN

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MASSCROWD_API`

### `Plugins/AI/MassCrowd/Source/MassCrowd/Public/MassCrowdServerRepresentationLODProcessor.h` (Public)


#### class `UMassCrowdServerRepresentationLODProcessor`  
`class UMassCrowdServerRepresentationLODProcessor : public UMassProcessor`  
_L16-44_
- reflection: `UCLASS(MinimalAPI, meta=(DisplayName="Crowd Simulation LOD"))`
- inherits: `UMassProcessor`
- L21 _public prototype_ `UMassCrowdServerRepresentationLODProcessor();`
- L25 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L26 _protected prototype_ `virtual void InitializeInternal(UObject& InOwner, const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L27 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L31 _protected member_ `float LODDistance[EMassLOD::Max];` — `UPROPERTY(EditAnywhere, Category = "Mass|LOD", config)` — Distance where each LOD becomes relevant
- L35 _protected member_ `float BufferHysteresisOnDistancePercentage = 10.0f;` — `UPROPERTY(EditAnywhere, Category = "Mass|LOD", meta = (ClampMin = "0.0", UIMin = "0.0"), config)` — Hysteresis percentage on delta between the LOD distances
- L39 _protected member_ `int32 LODMaxCount[EMassLOD::Max];` — `UPROPERTY(EditAnywhere, Category = "Mass|LOD", config)` — Maximum limit of entity per LOD
- L41 _protected member_ `TMassLODCalculator<FLODDefaultLogic> LODCalculator;`
- L43 _protected member_ `FMassEntityQuery EntityQuery;`

### `Plugins/AI/MassCrowd/Source/MassCrowd/Public/MassCrowdServerRepresentationProcessor.h` (Public)


#### class `UMassCrowdServerRepresentationProcessor`  
`class UMassCrowdServerRepresentationProcessor : public UMassRepresentationProcessor`  
_L15-24_
- reflection: `UCLASS(MinimalAPI, meta = (DisplayName = "Mass Crowd Server Representation"))`
- inherits: `UMassRepresentationProcessor`
- desc: Overridden representation processor to make it tied to the crowd on the server via the requirements It is the counter part of the crowd visualization processor on the client.
- L20 _public prototype_ `UMassCrowdServerRepresentationProcessor();`
- L23 _public prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;` — Configure the owned FMassEntityQuery instances to express processor's requirements

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MASSCROWD_API`

### `Plugins/AI/MassCrowd/Source/MassCrowd/Public/MassCrowdServerRepresentationTrait.h` (Public)


#### class `UMassCrowdServerRepresentationTrait`  
`class UMassCrowdServerRepresentationTrait : public UMassEntityTraitBase`  
_L15-32_
- reflection: `UCLASS(MinimalAPI, meta=(DisplayName="Crowd Server Representation"))`
- inherits: `UMassEntityTraitBase`
- L19 _private prototype_ `UMassCrowdServerRepresentationTrait();`
- L23 _protected prototype_ `virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;`
- L27 _protected member_ `TSubclassOf<AActor> TemplateActor;` — `UPROPERTY(EditAnywhere, Category = "Mass|Visual")` — Actor class of this agent when spawned on server
- L31 _protected member_ `FMassRepresentationParameters Params;` — `UPROPERTY(EditAnywhere, Category = "Mass|Visual")` — Configuration parameters for the representation processor

### `Plugins/AI/MassCrowd/Source/MassCrowd/Public/MassCrowdSettings.h` (Public)


#### struct `FMassCrowdLaneDensityDesc`  
`struct FMassCrowdLaneDensityDesc`  
_L24-46_
- reflection: `USTRUCT()`
- desc: Structure holding data to associate lane densities to weights so lane selection at intersection could use that to maintain overall density during the simulation
- L29 _public member_ `static constexpr float DefaultWeight = 1.0f;` — Default weight of a lane if it has no density tag
- L33 _public member_ `FZoneGraphTag Tag;` — `UPROPERTY(EditAnywhere, Category = "Lane Density")` — Tag representing the lane density.
- L42 _public member_ `float Weight = DefaultWeight;` — `UPROPERTY(EditAnywhere, Category = "Lane Density")` — Weight associated to the current lane density. This weight is used during lane selection at intersection and the random selection will consider the weight of each lane and the combined weight of all lanes.
- L45 _public member_ `FColor RenderColor = FColor::Silver;` — `UPROPERTY(EditAnywhere, Category = "Lane Density", meta = (HideAlphaChannel))`

#### class `UMassCrowdSettings`  
`class UMassCrowdSettings : public UMassModuleSettings`  
_L52-153_
- reflection: `UCLASS(MinimalAPI, config = Plugins, defaultconfig, DisplayName = "Mass Crowd", dontCollapseCategories)`
- inherits: `UMassModuleSettings`
- desc: Settings for the MassCrowd plugin.
- L57 _public function_ `const TArray<FMassCrowdLaneDensityDesc>& GetLaneDensities() const`
- L58 _public function_ `float GetMoveDistance() const`
- L64 _public member_ `mutable FOnMassCrowdLaneDataSettingsChanged OnMassCrowdLaneDataSettingsChanged;`
- L65 _public member_ `mutable FOnMassCrowdLaneRenderSettingsChanged OnMassCrowdLaneRenderSettingsChanged;`
- L70 _public member_ `float LaneBaseLineThickness = 5.0f;` — `UPROPERTY(EditAnywhere, config, meta = (ClampMin = "0.0", UIMin = "0.0"), Category = "Lane Debug Rendering")` — Base thickness used to render lane data specific to crowd.
- L74 _public member_ `float LaneRenderZOffset = 50.0f;` — `UPROPERTY(EditAnywhere, config, meta = (ClampMin = "0.0", UIMin = "0.0"), Category = "Lane Debug Rendering")` — Z offset used to render lane data specific to crowd over the actual zone graph.
- L78 _public member_ `float IntersectionLaneScaleFactor = 1.5f;` — `UPROPERTY(EditAnywhere, config, meta = (ClampMin = "1.0", UIMin = "1.0", ClampMax = "10.0", UIMax = "10.0"), Category = "Lane Debug Rendering")` — Scale factor applied on the base thickness to render intersection lanes data.
- L82 _public member_ `float LaneDensityScaleFactor = 1.5f;` — `UPROPERTY(EditAnywhere, config, meta = (ClampMin = "1.0", UIMin = "1.0", ClampMax = "10.0", UIMax = "10.0"), Category = "Lane Debug Rendering")` — Scale factor applied on the base or intersection thickness to render density outline.
- L86 _public member_ `FColor OpenedLaneColor = FColor::Green;` — `UPROPERTY(EditAnywhere, config, Category = "Lane Density", meta = (HideAlphaChannel))` — Color used to render crowd lane that are opened for navigation.
- L90 _public member_ `FColor ClosedLaneColor = FColor::Red;` — `UPROPERTY(EditAnywhere, config, Category = "Lane Density", meta = (HideAlphaChannel))` — Color used to render crowd lane that are closed to navigation.
- L94 _public member_ `FZoneGraphTag CrowdTag;` — `UPROPERTY(EditDefaultsOnly, config, Category = Lane)` — Tag required on a lane to build crowd related runtime data for it and render it.
- L98 _public member_ `FZoneGraphTag CrossingTag;` — `UPROPERTY(EditDefaultsOnly, config, Category = Lane)` — Tag required on a lane to build intersection crossing runtime data for it.
- L102 _public member_ `uint32 SlotSize = 50;` — `UPROPERTY(EditDefaultsOnly, config, Category = WaitArea)` — Distance reserved for each entity while waiting on an intersection lane.
- L106 _public member_ `float SlotOffset = 75;` — `UPROPERTY(EditDefaultsOnly, config, Category = WaitArea)` — Offset from the lane entry where the slots are created.
- L110 _public member_ `bool bDisplayTrackingData = true;` — `UPROPERTY(EditAnywhere, config, Category = Options)` — Text will be added on lanes with entity tracking or waiting area to indicate the current occupation
- L114 _public member_ `bool bDisplayStates = true;` — `UPROPERTY(EditAnywhere, config, Category = Options)` — Lanes will be displayed to indicates the current state. See MassCrowd settings for parameters.
- L118 _public member_ `bool bDisplayDensities = true;` — `UPROPERTY(EditAnywhere, config, Category = Options)` — Lanes will be displayed to represent their assigned densities. See MassCrowd settings for parameters.
- L122 _public member_ `float ObstacleStoppingSpeedTolerance = 5.0f;` — `UPROPERTY(EditAnywhere, config, Category = Obstacles, meta = (ClampMin = "0.0", UIMin = "0.0", ForceUnits = "cm/s"))` — An obstacle is considered being stopped when it's speed is less than the tolerance.
- L126 _public member_ `float ObstacleMovingDistanceTolerance = 10.0f;` — `UPROPERTY(EditAnywhere, config, Category = Obstacles, meta = (ClampMin = "0.0", UIMin = "0.0", ForceUnits = "cm"))` — An obstacle is considered moving when it has moved this much after being stationary.
- L130 _public member_ `float ObstacleTimeToStop = 0.3f;` — `UPROPERTY(EditAnywhere, config, Category = Obstacles, meta = (ClampMin = "0.0", UIMin = "0.0", ForceUnits = "s"))` — The time an obstacle needs to be not moving before it is reported as stopped.
- L134 _public member_ `float ObstacleEffectRadius = 1000.f;` — `UPROPERTY(EditAnywhere, config, Category = Obstacles, meta = (ClampMin = "0.0", UIMin = "0.0", ForceUnits = "cm"))` — The radius an obstacle has effects on navigation.
- L139 _protected prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L144 _protected member_ `float MoveDistance = 500.f;` — `UPROPERTY(EditDefaultsOnly, config, meta = (ClampMin = "0.0", UIMin = "0.0"), Category = Movement)` — Distance ahead of the current lane location for the next movement target location.
- L148 _protected member_ `float MoveDistanceRandomDeviation = 100.f;` — `UPROPERTY(EditDefaultsOnly, config, meta = (ClampMin = "0.0", UIMin = "0.0"), Category = Movement)` — Random deviation of the of the MoveDistance
- L152 _protected member_ `TArray<FMassCrowdLaneDensityDesc> LaneDensities;` — `UPROPERTY(EditAnywhere, config, Category = "Lane Density")` — List of all lane density descriptors.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MASSCROWD_API`
- L13 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnMassCrowdLaneDataSettingsChanged);` — Called when density settings change.
- L13 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnMassCrowdLaneDataSettingsChanged);` — Called when density settings change.
- L15 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnMassCrowdLaneRenderSettingsChanged);` — Called when rendering settings change.
- L15 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnMassCrowdLaneRenderSettingsChanged);` — Called when rendering settings change.

### `Plugins/AI/MassCrowd/Source/MassCrowd/Public/MassCrowdSpawnerSubsystem.h` (Public)


#### class `UMassCrowdSpawnerSubsystem`  
`class UMassCrowdSpawnerSubsystem : public UMassActorSpawnerSubsystem`  
_L12-15_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassActorSpawnerSubsystem`
- desc: A subsystem managing spawning of crowd

### `Plugins/AI/MassCrowd/Source/MassCrowd/Public/MassCrowdSubsystem.h` (Public)


#### struct `FSelectLaneResult`  
`struct FSelectLaneResult`  
_L25-32_
- desc: Structure holding all pertinent data related to the selected lane.
- L28 _public member_ `FZoneGraphLaneHandle NextLaneHandle;` — The handle of the next lane selected from the available links.
- L31 _public member_ `TOptional<float> WaitDistance;` — The distance along the lane the entity should reach before stopping.

#### struct `FRegisteredCrowdLaneData`  
`struct FRegisteredCrowdLaneData`  
_L35-59_
- desc: Container for the crowd lane data associated to a specific registered ZoneGraph data.
- L37 _public function_ `void Reset()`
- L47 _public member_ `TArray<FZoneGraphCrowdLaneData> CrowdLaneDataArray;` — Per lane data; array size matches the ZoneGraph storage.
- L50 _public member_ `FZoneGraphDataHandle DataHandle;` — Handle of the storage the data was initialized from.
- L53 _public member_ `TMap<int32, FCrowdTrackingLaneData> LaneToTrackingDataLookup;` — Lane to entity tracking data lookup
- L56 _public member_ `TMap<int32, FCrowdBranchingLaneData> LaneToBranchingDataLookup;` — Lane to branching data lookup
- L58 _public member_ `TArray<FCrowdWaitAreaData> WaitAreas;`

#### class `UMassCrowdSubsystem`  
`class UMassCrowdSubsystem : public UMassSubsystemBase`  
_L66-252_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassSubsystemBase`
- desc: Subsystem that tracks mass entities that are wandering on the zone graph. It will create custom runtime lane data to allow branching decisions.
- L71 _public member_ `FDebugOnMassCrowdLaneStateChanged DebugOnMassCrowdLaneStateChanged;`
- L76 _public prototype_ `void RebuildLaneData();` — Clears and rebuilds all lane and intersection data for registered zone graphs using the current settings.
- L80 _public prototype_ `bool HasCrowdDataForZoneGraph(const FZoneGraphDataHandle DataHandle) const;` — @return true if the Crowd subsystem has lane data for specified graph.
- L88 _public prototype_ `const FRegisteredCrowdLaneData* GetCrowdData(const FZoneGraphDataHandle DataHandle) const;` — Returns the readonly runtime data associated to a given zone graph. @param DataHandle A valid handle of the zone graph used to retrieve the runtime crowd data @return Runtime data associated to the zone graph if available; nullptr otherwise @note Method will ensure if DataHandle is invalid or if associated data doesn't exist. Should call HasCrowdDataForZoneGraph first.
- L95 _public prototype_ `TOptional<FZoneGraphCrowdLaneData> GetCrowdLaneData(const FZoneGraphLaneHandle LaneHandle) const;` — Returns the readonly runtime data associated to a given zone graph lane. @param LaneHandle A valid lane handle used to retrieve the runtime data; ensure if handle is invalid @return Runtime data associated to the lane (if available)
- L102 _public prototype_ `const FCrowdTrackingLaneData* GetCrowdTrackingLaneData(const FZoneGraphLaneHandle LaneHandle) const;` — Returns the entity tracking runtime data associated to a given zone graph lane. @param LaneHandle A valid lane handle used to retrieve the associated tracking data; ensure if handle is invalid @return Runtime data associated to the lane (nullptr if provided handle is invalid or no data is associated to that lane)
- L109 _public prototype_ `const FCrowdBranchingLaneData* GetCrowdBranchingLaneData(const FZoneGraphLaneHandle LaneHandle) const;` — Returns the branching data associated to a given zone graph lane. @param LaneHandle A valid lane handle used to retrieve the associated data; ensure if handle is invalid @return Branching data associated to the lane (nullptr if provided handle is invalid or no data is associated to that lane)
- L116 _public prototype_ `const FCrowdWaitAreaData* GetCrowdWaitingAreaData(const FZoneGraphLaneHandle LaneHandle) const;` — Returns the waiting area runtime data associated to a given zone graph lane. @param LaneHandle A valid lane handle used to retrieve the associated intersection data; ensure if handle is invalid @return Runtime data associated to the lane (nullptr if provided handle is invalid or no data is associated to that lane)
- L123 _public prototype_ `ECrowdLaneState GetLaneState(const FZoneGraphLaneHandle LaneHandle) const;` — Return the current state of a lane. @param LaneHandle A valid lane handle used to retrieve the runtime data and change the lane state; ensure if handle is invalid @return The state of the lane
- L131 _public prototype_ `bool SetLaneState(const FZoneGraphLaneHandle LaneHandle, ECrowdLaneState NewState);` — Changes the state of a lane. @param LaneHandle A valid lane handle used to retrieve the runtime data and change the lane state; ensure if handle is invalid @param NewState The new state of the lane @return True if the state was successfully changed or was already in the right state; false if handle is invalid
- L134 _public function_ `FZoneGraphTagMask GetDensityMask() const` — @return Combined Tag mask that represents all possible lane density tags. Built from MassCrowdSettings.
- L145 _public prototype_ `int32 AcquireWaitingSlot(const FMassEntityHandle Entity, const FVector& EntityPosition, const FZoneGraphLaneHandle LaneHandle, FVector& OutSlotPosition, FVector& OutSlotDirection);` — Acquires a slot from a specified waiting lane. Nearest vacant slot to EntityPosition is returned. @param Entity Requesting entity @param EntityPosition Position of the entity. @param LaneHandle A handle to a lane with waiting data. @param OutSlotPosition Position associated to the acquired slot. @param OutSlotDirection Facing direction associated to the acquire slot. @return Index of the slot, or INDEX_NONE if no slots are available or if the lane is not a waiting lane.
- L154 _public prototype_ `void ReleaseWaitingSlot(const FMassEntityHandle Entity, const FZoneGraphLaneHandle LaneHandle, const int32 SlotIndex);` — Releases previously acquired slot from a specified waiting lane. @param Entity Requesting entity @param LaneHandle A handle to a lane with waiting data. @param SlotIndex Index of the previously acquired slot.
- L162 _public prototype_ `void OnEntityLaneChanged(const FMassEntityHandle Entity, const FZoneGraphLaneHandle PreviousLaneHandle, const FZoneGraphLaneHandle CurrentLaneHandle);` — Callback from the lane tracker processor to indicates a mass entity changing lane. @param Entity The mass entity @param PreviousLaneHandle Last frame lane handle (can be invalid) @param CurrentLaneHandle Current frame lane handle (can be invalid)
- L165 _public prototype_ `float GetDensityWeight(const FZoneGraphLaneHandle LaneHandle, const FZoneGraphTagMask LaneTagMask) const;` — Returns the weight for lane selection that is associated to the given lane based on its density tag.
- L172 _protected prototype_ `void UpdateDensityMask();`
- L175 _protected prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;` — USubsystem BEGIN
- L176 _protected prototype_ `virtual void PostInitialize() override;`
- L177 _protected prototype_ `virtual void Deinitialize() override;`
- L180 _protected prototype_ `void PostZoneGraphDataAdded(const AZoneGraphData* ZoneGraphData);`
- L181 _protected prototype_ `void PreZoneGraphDataRemoved(const AZoneGraphData* ZoneGraphData);`
- L188 _protected prototype_ `FZoneGraphCrowdLaneData* GetMutableCrowdLaneData(const FZoneGraphLaneHandle LaneHandle);` — Returns the modifiable runtime data associated to a given zone graph lane. @param LaneHandle A valid lane handle used to retrieve the runtime data; ensure if handle is invalid @return Runtime data associated to the lane if available; nullptr otherwise
- L195 _protected prototype_ `void BuildLaneData(FRegisteredCrowdLaneData& LaneData, const FZoneGraphStorage& Storage);` — Populates the crowd lane data array with all existing lane in the zone graph. Also creates some extra data for lanes that could be used to wait in case of temporarily closed lane (e.g. intersection crossings).
- L203 _protected prototype_ `void OnEnterTrackedLane(const FMassEntityHandle Entity, const int32 LaneIndex, FCrowdTrackingLaneData& TrackingData);` — Callback to keep count of entities currently on a given lane. @param Entity The entity entering the lane @param LaneIndex Index of the lane @param TrackingData Runtime state associated to the lane
- L211 _protected prototype_ `void OnExitTrackedLane(const FMassEntityHandle Entity, const int32 LaneIndex, FCrowdTrackingLaneData& TrackingData);` — Callback to keep count of entities currently on a given lane. @param Entity The entity exiting the lane @param LaneIndex Index of the lane @param TrackingData Runtime state associated to the lane
- L219 _protected prototype_ `FCrowdTrackingLaneData& CreateTrackingData(const int32 LaneIndex, const FZoneGraphStorage& ZoneGraphStorage);` — Creates and initializes the occupancy data of a lane. @param LaneIndex Index of the source zone graph lane @param ZoneGraphStorage ZoneGraph data storage to extract lane information from @return The newly created structure holding occupancy data associated to the zone graph lane
- L227 _protected prototype_ `FCrowdBranchingLaneData& CreateBranchingData(const int32 LaneIndex, const FZoneGraphStorage& ZoneGraphStorage);` — Creates dedicated structure to hold data of a branching lane. @param LaneIndex Index of the source zone graph lane @param ZoneGraphStorage ZoneGraph data storage to extract lane information from @return The newly created structure holding specific data of a branching lane
- L229 _protected prototype_ `void CreateWaitSlots(const int32 CrossingLaneIndex, FCrowdWaitAreaData& WaitArea, const FZoneGraphStorage& ZoneGraphStorage);`
- L232 _protected member_ `TObjectPtr<UZoneGraphSubsystem> ZoneGraphSubsystem = nullptr;` — `UPROPERTY(Transient)`
- L235 _protected member_ `TObjectPtr<UZoneGraphAnnotationSubsystem> ZoneGraphAnnotationSubsystem = nullptr;` — `UPROPERTY(Transient)`
- L238 _protected member_ `TObjectPtr<const UMassCrowdSettings> MassCrowdSettings = nullptr;` — `UPROPERTY(Transient)`
- L240 _protected member_ `FDelegateHandle OnPostZoneGraphDataAddedHandle;`
- L241 _protected member_ `FDelegateHandle OnPreZoneGraphDataRemovedHandle;`
- L243 _protected member_ `FDelegateHandle OnMassCrowdSettingsChangedHandle;`
- L244 _protected member_ `FDelegateHandle OnZoneGraphDataBuildDoneHandle;`
- L248 _protected member_ `TArray<FRegisteredCrowdLaneData> RegisteredLaneData;` — Per lane data for all registered ZoneGraph data.
- L251 _protected member_ `FZoneGraphTagMask DensityMask;` — Tag mask that represents all possible lane density tags. Built from MassCrowdSettings.

#### struct `TMassExternalSubsystemTraits`  
`template<> struct TMassExternalSubsystemTraits<UMassCrowdSubsystem> final`  
_L255-262_

#### enum `TMassExternalSubsystemTraits::(anonymous)`  
``  
_L258-261_

#### Free symbols / members of external scopes

- L21 _delegate_ `DECLARE_MULTICAST_DELEGATE(FDebugOnMassCrowdLaneStateChanged);` — Called when a lane changes state at runtime.
- L21 _prototype_ `DECLARE_MULTICAST_DELEGATE(FDebugOnMassCrowdLaneStateChanged);` — Called when a lane changes state at runtime.
- L259 _enumerator_ `GameThreadOnly = false` (scope `TMassExternalSubsystemTraits::__anona819ec4a0103`)
- L260 _enumerator_ `ThreadSafeWrite = false` (scope `TMassExternalSubsystemTraits::__anona819ec4a0103`)

### `Plugins/AI/MassCrowd/Source/MassCrowd/Public/MassCrowdTypes.h` (Public)


#### struct `FMassCrowdSimulationLODLogic`  
`struct FMassCrowdSimulationLODLogic : public FLODDefaultLogic`  
_L9-15_
- inherits: `FLODDefaultLogic`

#### enum `FMassCrowdSimulationLODLogic::(anonymous)`  
``  
_L12-14_

#### struct `FMassCrowdViewerLODLogic`  
`struct FMassCrowdViewerLODLogic : public FLODDefaultLogic`  
_L17-25_
- inherits: `FLODDefaultLogic`

#### enum `FMassCrowdViewerLODLogic::(anonymous)`  
``  
_L20-24_

#### struct `FMassCrowdCombinedLODLogic`  
`struct FMassCrowdCombinedLODLogic : public FLODDefaultLogic`  
_L27-36_
- inherits: `FLODDefaultLogic`

#### enum `FMassCrowdCombinedLODLogic::(anonymous)`  
``  
_L30-35_

#### enum `ECrowdLaneState`  
`enum class ECrowdLaneState : uint8`  
_L40-44_
- reflection: `UENUM()`
- desc: State of a given lane
- L42 _public enumerator_ `Opened` — Pedestrians can enter the lane
- L43 _public enumerator_ `Closed` — Pedestrians can not enter the lane

#### struct `FCrowdTrackingLaneData`  
`struct FCrowdTrackingLaneData`  
_L48-59_
- reflection: `USTRUCT()`
- desc: Runtime data associated to lane that can be used to track count of entities on it.
- L56 _public member_ `int32 WaitAreaIndex = INDEX_NONE;` — Index of an associated waiting area. This will be valid for branching lanes leading to a crossing that requires agent to wait for incoming lane to open.
- L58 _public member_ `int32 NumEntitiesOnLane = 0;`

#### struct `FCrowdWaitSlot`  
`struct FCrowdWaitSlot`  
_L63-74_
- reflection: `USTRUCT()`
- desc: Runtime data associated to lane that can be used to wait another one to open.
- L67 _public member_ `FVector Position = FVector::Zero();`
- L69 _public member_ `FVector Forward = FVector::ForwardVector;`
- L71 _public member_ `float Radius = 0;`
- L73 _public member_ `bool bOccupied = false;`

#### struct `FCrowdWaitAreaData`  
`struct FCrowdWaitAreaData`  
_L78-98_
- reflection: `USTRUCT()`
- desc: Runtime data associated to entry to a lane that can be opened or closed.
- L82 _public function_ `void Reset()`
- L88 _public function_ `bool IsFull() const`
- L89 _public function_ `int32 GetNumSlots() const`
- L90 _public function_ `int32 GetNumFreeSlots() const`
- L91 _public function_ `int32 GetNumOccupiedSlots() const`
- L93 _public member_ `TArray<FCrowdWaitSlot> Slots;`
- L95 _public member_ `TArray<FZoneGraphLaneHandle> ConnectedLanes;`
- L97 _public member_ `int32 NumFreeSlots = 0;`

#### struct `FCrowdBranchingLaneData`  
`struct FCrowdBranchingLaneData`  
_L102-112_
- reflection: `USTRUCT()`
- desc: Runtime data associated to branching.
- L111 _public member_ `uint32 DensityMask = 0;` — Density mask extracted from the incoming lane. This is required since the intersection might split and reach different densities on connected shapes. We can't keep a single density for the whole polygon so we keep it per lane.

#### struct `FZoneGraphCrowdLaneData`  
`struct FZoneGraphCrowdLaneData`  
_L116-124_
- reflection: `USTRUCT()`
- desc: Structure holding runtime data associated to a zone graph lane to handle pedestrian navigation.
- L120 _public function_ `ECrowdLaneState GetState() const`
- L121 _public function_ `void SetState(ECrowdLaneState Value)`
- L123 _protected member_ `ECrowdLaneState State = ECrowdLaneState::Opened;`

#### Free symbols / members of external scopes

- L13 _enumerator_ `bDoVariableTickRate = true` (scope `FMassCrowdSimulationLODLogic::__anon073769900103`)
- L21 _enumerator_ `bDoVisibilityLogic = true` (scope `FMassCrowdViewerLODLogic::__anon073769900203`)
- L22 _enumerator_ `bCalculateLODSignificance = true` (scope `FMassCrowdViewerLODLogic::__anon073769900203`)
- L23 _enumerator_ `bLocalViewersOnly = true` (scope `FMassCrowdViewerLODLogic::__anon073769900203`)
- L31 _enumerator_ `bDoVariableTickRate = true` (scope `FMassCrowdCombinedLODLogic::__anon073769900303`)
- L32 _enumerator_ `bDoVisibilityLogic = true` (scope `FMassCrowdCombinedLODLogic::__anon073769900303`)
- L33 _enumerator_ `bCalculateLODSignificance = true` (scope `FMassCrowdCombinedLODLogic::__anon073769900303`)
- L34 _enumerator_ `bLocalViewersOnly = true` (scope `FMassCrowdCombinedLODLogic::__anon073769900303`)

### `Plugins/AI/MassCrowd/Source/MassCrowd/Public/MassCrowdVisualizationLODProcessor.h` (Public)


#### class `UMassCrowdVisualizationLODProcessor`  
`class UMassCrowdVisualizationLODProcessor : public UMassVisualizationLODProcessor`  
_L15-24_
- reflection: `UCLASS(MinimalAPI, meta=(DisplayName="Crowd visualization LOD"))`
- inherits: `UMassVisualizationLODProcessor`
- desc: Created a crowd version for parallelization of the crowd with the traffic
- L19 _public prototype_ `UMassCrowdVisualizationLODProcessor();`
- L22 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L23 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`

#### class `UMassCrowdLODCollectorProcessor`  
`class UMassCrowdLODCollectorProcessor : public UMassLODCollectorProcessor`  
_L30-38_
- reflection: `UCLASS(MinimalAPI, meta = (DisplayName = "Crowd LOD Collection "))`
- inherits: `UMassLODCollectorProcessor`
- desc: Created a crowd version for parallelization of the crowd with the traffic
- L34 _private prototype_ `UMassCrowdLODCollectorProcessor();`
- L37 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MASSCROWD_API`

### `Plugins/AI/MassCrowd/Source/MassCrowd/Public/MassCrowdVisualizationProcessor.h` (Public)


#### class `UMassCrowdVisualizationProcessor`  
`class UMassCrowdVisualizationProcessor : public UMassVisualizationProcessor`  
_L14-24_
- reflection: `UCLASS(MinimalAPI, meta = (DisplayName = "Mass Crowd Visualization"))`
- inherits: `UMassVisualizationProcessor`
- desc: Overridden visualization processor to make it tied to the crowd via the requirements
- L18 _public prototype_ `UMassCrowdVisualizationProcessor();`
- L23 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;` — Configure the owned FMassEntityQuery instances to express processor's requirements

#### class `UMassDebugCrowdVisualizationProcessor`  
`class UMassDebugCrowdVisualizationProcessor : public UMassProcessor`  
_L30-54_
- reflection: `UCLASS(MinimalAPI, meta = (DisplayName = "Mass Crowd Visualization"))`
- inherits: `UMassProcessor`
- desc: A custom visualization processor for debugging mass crowd
- L34 _public prototype_ `UMassDebugCrowdVisualizationProcessor();`
- L39 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;` — Configure the owned FMassEntityQuery instances to express processor's requirements
- L41 _protected prototype_ `virtual void InitializeInternal(UObject& Owner, const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L48 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;` — Execution method for this processor @param EntitySubsystem is the system to execute the lambdas on each entity chunk @param Context is the execution context to be passed when executing the lambdas
- L51 _protected member_ `TObjectPtr<UWorld> World;` — `UPROPERTY(Transient)`
- L53 _protected member_ `FMassEntityQuery EntityQuery;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MASSCROWD_API`

### `Plugins/AI/MassCrowd/Source/MassCrowd/Public/MassCrowdVisualizationTrait.h` (Public)


#### class `UMassCrowdVisualizationTrait`  
`class UMassCrowdVisualizationTrait : public UMassVisualizationTrait`  
_L11-18_
- reflection: `UCLASS(MinimalAPI, BlueprintType, EditInlineNew, CollapseCategories, meta=(DisplayName="Crowd Visualization"))`
- inherits: `UMassVisualizationTrait`
- L15 _public prototype_ `UMassCrowdVisualizationTrait();`
- L17 _public prototype_ `virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MASSCROWD_API`

### `Plugins/AI/MassCrowd/Source/MassCrowd/Public/Tasks/MassCrowdClaimWaitSlotTask.h` (Public)


#### struct `FMassCrowdClaimWaitSlotTaskInstanceData`  
`struct FMassCrowdClaimWaitSlotTaskInstanceData`  
_L23-35_
- reflection: `USTRUCT()`
- desc: Claim wait slot and expose slot position for path follow.
- L28 _public member_ `FMassZoneGraphTargetLocation WaitSlotLocation;` — `UPROPERTY(EditAnywhere, Category = Output)`
- L31 _public member_ `int32 WaitingSlotIndex = INDEX_NONE;` — `UPROPERTY()`
- L34 _public member_ `FZoneGraphLaneHandle AcquiredLane;` — `UPROPERTY()`

#### struct `FMassCrowdClaimWaitSlotTask`  
`struct FMassCrowdClaimWaitSlotTask : public FMassStateTreeTaskBase`  
_L38-56_
- reflection: `USTRUCT(meta = (DisplayName = "Crowd Claim Wait Slot"))`
- inherits: `FMassStateTreeTaskBase`
- L42 _public typedef_ `using FInstanceDataType = FMassCrowdClaimWaitSlotTaskInstanceData;`
- L44 _public prototype_ `FMassCrowdClaimWaitSlotTask();`
- L47 _protected prototype_ `virtual bool Link(FStateTreeLinker& Linker) override;`
- L48 _protected function_ `virtual const UStruct* GetInstanceDataType() const override`
- L49 _protected prototype_ `virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;`
- L50 _protected prototype_ `virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;`
- L51 _protected prototype_ `virtual void GetDependencies(UE::MassBehavior::FStateTreeDependencyBuilder& Builder) const override;`
- L53 _protected member_ `TStateTreeExternalDataHandle<FMassZoneGraphLaneLocationFragment> LocationHandle;`
- L54 _protected member_ `TStateTreeExternalDataHandle<FMassMoveTargetFragment> MoveTargetHandle;`
- L55 _protected member_ `TStateTreeExternalDataHandle<UMassCrowdSubsystem> CrowdSubsystemHandle;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MASSCROWD_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MassBehavior` (scope `UE`)

### `Plugins/AI/MassCrowd/Source/MassCrowd/Public/Tasks/MassZoneGraphFindWanderTarget.h` (Public)


#### struct `FMassZoneGraphFindWanderTargetInstanceData`  
`struct FMassZoneGraphFindWanderTargetInstanceData`  
_L25-31_
- reflection: `USTRUCT()`
- desc: Updates TargetLocation to a wander target based on the agents current location on ZoneGraph.
- L30 _public member_ `FMassZoneGraphTargetLocation WanderTargetLocation;` — `UPROPERTY(EditAnywhere, Category = Output)`

#### struct `FMassZoneGraphFindWanderTarget`  
`struct FMassZoneGraphFindWanderTarget : public FMassStateTreeTaskBase`  
_L34-55_
- reflection: `USTRUCT(meta = (DisplayName = "ZG Find Wander Target"))`
- inherits: `FMassStateTreeTaskBase`
- L38 _public typedef_ `using FInstanceDataType = FMassZoneGraphFindWanderTargetInstanceData;`
- L40 _public prototype_ `FMassZoneGraphFindWanderTarget();`
- L43 _protected prototype_ `virtual bool Link(FStateTreeLinker& Linker) override;`
- L44 _protected function_ `virtual const UStruct* GetInstanceDataType() const override`
- L45 _protected prototype_ `virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;`
- L46 _protected prototype_ `virtual void GetDependencies(UE::MassBehavior::FStateTreeDependencyBuilder& Builder) const override;`
- L48 _protected member_ `TStateTreeExternalDataHandle<FMassZoneGraphLaneLocationFragment> LocationHandle;`
- L49 _protected member_ `TStateTreeExternalDataHandle<UZoneGraphSubsystem> ZoneGraphSubsystemHandle;`
- L50 _protected member_ `TStateTreeExternalDataHandle<UZoneGraphAnnotationSubsystem> ZoneGraphAnnotationSubsystemHandle;`
- L51 _protected member_ `TStateTreeExternalDataHandle<UMassCrowdSubsystem> MassCrowdSubsystemHandle;`
- L54 _protected member_ `FZoneGraphTagFilter AllowedAnnotationTags;` — `UPROPERTY(EditAnywhere, Category = Parameter)`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MASSCROWD_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace MassBehavior` (scope `UE`)

### `Plugins/AI/MassCrowd/Source/MassCrowd/Public/ZoneGraphCrowdLaneAnnotations.h` (Public)


#### struct `FZoneGraphCrowdLaneStateChangeEvent`  
`struct FZoneGraphCrowdLaneStateChangeEvent : public FZoneGraphAnnotationEventBase`  
_L15-30_
- reflection: `USTRUCT()`
- inherits: `FZoneGraphAnnotationEventBase`
- desc: Event indicating the new state of a lane.
- L19 _public prototype_ `FZoneGraphCrowdLaneStateChangeEvent() = default;`
- L20 _public function_ `FZoneGraphCrowdLaneStateChangeEvent(const FZoneGraphLaneHandle LaneHandle, const ECrowdLaneState NewState) : Lane(LaneHandle), State(NewState)`
- L25 _public member_ `FZoneGraphLaneHandle Lane;` — `UPROPERTY()` — Affected lane.
- L29 _public member_ `ECrowdLaneState State = ECrowdLaneState::Opened;` — `UPROPERTY()` — New state.

#### class `UZoneGraphCrowdLaneAnnotations`  
`class UZoneGraphCrowdLaneAnnotations : public UZoneGraphAnnotationComponent`  
_L36-68_
- reflection: `UCLASS(MinimalAPI, ClassGroup = AI, BlueprintType, meta = (BlueprintSpawnableComponent))`
- inherits: `UZoneGraphAnnotationComponent`
- desc: Zone graph blocking behavior
- L41 _protected prototype_ `virtual void PostSubsystemsInitialized() override;`
- L42 _protected prototype_ `virtual FZoneGraphTagMask GetAnnotationTags() const override;`
- L43 _protected prototype_ `virtual void HandleEvents(const FInstancedStructContainer& Events) override;`
- L44 _protected prototype_ `virtual void TickAnnotation(const float DeltaTime, FZoneGraphAnnotationTagContainer& AnnotationTagContainer) override;`
- L47 _protected prototype_ `virtual void DebugDraw(FZoneGraphAnnotationSceneProxy* DebugProxy) override;`
- L48 _protected prototype_ `virtual void DebugDrawCanvas(UCanvas* Canvas, APlayerController*) override;`
- L53 _protected member_ `FZoneGraphTag CloseLaneTag;` — `UPROPERTY(EditAnywhere, Category = CrowdLane)` — Annotation Tag to mark a closed lane.
- L57 _protected member_ `FZoneGraphTag WaitingLaneTag;` — `UPROPERTY(EditAnywhere, Category = CrowdLane)` — Annotation Tag to mark a waiting lane.
- L60 _protected member_ `bool bDisplayTags = false;` — `UPROPERTY(EditAnywhere, Category = Debug)`
- L63 _protected member_ `TArray<FZoneGraphCrowdLaneStateChangeEvent> StateChangeEvents;` — Array of queued events.
- L67 _protected member_ `TObjectPtr<UMassCrowdSubsystem> CrowdSubsystem = nullptr;` — `UPROPERTY(Transient)` — Cached ZoneGraphSubsystem

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MASSCROWD_API`
