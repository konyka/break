# Plugins / MassNavigation

- module root: `Plugins/AI/MassAI/Source/MassNavigation`
- headers: 17; symbols: 296
- symbol kinds: class=15, enum=6, enumerator=11, function=44, macro=8, member=118, namespace=8, prototype=54, struct=26, typedef=3, variable=3
- PrivateDependencyModuleNames: EditorFramework, UnrealEd
- PublicDependencyModuleNames: AIModule, Core, CoreUObject, DeveloperSettings, Engine, MassCommon, MassCore, MassEntity, MassLOD, MassMovement, MassSignals, MassSimulation, MassSpawner

### `Plugins/AI/MassAI/Source/MassNavigation/Public/Avoidance/MassAvoidanceFragments.h` (Public)


#### struct `FMassMovingAvoidanceParameters`  
`struct FMassMovingAvoidanceParameters : public FMassConstSharedFragment`  
_L14-115_
- reflection: `USTRUCT()`
- inherits: `FMassConstSharedFragment`
- L18 _public function_ `FMassMovingAvoidanceParameters GetValidated() const`
- L36 _public member_ `float ObstacleDetectionDistance = 400.f;` — `UPROPERTY(EditAnywhere, Category = "General", meta = (ClampMin = "0.0", ForceUnits="cm"))` — The distance at which obstacle are detected. Range: 200...600
- L40 _public member_ `float StartOfPathDuration = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "General", meta = (ClampMin = "0", ForceUnits="s"))` — The time the agent is considered to be near the start of the path when starting to move. Range: 0..3
- L44 _public member_ `float EndOfPathDuration = 0.5f;` — `UPROPERTY(EditAnywhere, Category = "General", meta = (ClampMin = "0", ForceUnits="s"))` — The time the agent is considered to be near the end of the path when approaching end. Range: 0..3
- L48 _public member_ `float StartOfPathAvoidanceScale = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "General", meta = (ClampMin = "0", ForceUnits="x"))` — How much to tune down the avoidance at the start of the path. Range: 0..1.
- L52 _public member_ `float EndOfPathAvoidanceScale = 0.1f;` — `UPROPERTY(EditAnywhere, Category = "General", meta = (ClampMin = "0", ForceUnits="x"))` — How much to tune down the avoidance towards the end of the path. Range: 0..1
- L56 _public member_ `float StandingObstacleAvoidanceScale = 0.65f;` — `UPROPERTY(EditAnywhere, Category = "General", meta = (ClampMin = "0", ForceUnits="x"))` — How much to tune down the avoidance when an obstacle is standing. This allows the agents to pass through standing agents more easily. Range: 0..1
- L60 _public member_ `float StaticObstacleClearanceScale = 0.7f;` — `UPROPERTY(EditAnywhere, Category = "General", meta = (ClampMin = "0", ForceUnits="x"))` — Agent radius scale for avoiding static obstacles near wall. If the clarance between obstacle and wall is less than the scaled radius, the agent will not try to move through the gap. Range: 0..1
- L64 _public member_ `float SeparationRadiusScale = 0.9f;` — `UPROPERTY(EditAnywhere, Category = "Separation", meta = (ClampMin = "0", ForceUnits="x"))` — Agent radius scale for separation. Making it smaller makes the separation softer. Range: 0.8..1
- L69 _public member_ `float ObstacleSeparationStiffness = 250.f;` — `UPROPERTY(EditAnywhere, Category = "Separation", meta = (ClampMin = "0"))` — Separation force stiffness between agents and obstacles. Range: 100..500 N/cm
- L73 _public member_ `float ObstacleSeparationDistance = 75.f;` — `UPROPERTY(EditAnywhere, Category = "Separation", meta = (ClampMin = "0", ForceUnits="cm"))` — Separation force effect distance. The actual observed separation distance will be smaller. Range: 0..100
- L77 _public member_ `float EnvironmentSeparationStiffness = 500.f;` — `UPROPERTY(EditAnywhere, Category = "Separation", meta = (ClampMin = "0"))` — Environment separation force stiffness between agents and walls. Range: 200..1000 N/cm
- L81 _public member_ `float EnvironmentSeparationDistance = 50.f;` — `UPROPERTY(EditAnywhere, Category = "Separation", meta = (ClampMin = "0", ForceUnits="cm"))` — Environment separation force effect distance. The actual observed separation distance will be smaller. Range: 0..200
- L85 _public member_ `float EnvironmentSeparationBehindEdgeDistanceScale = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Separation", meta = (ClampMin = "0", ForceUnits="x"))` — Environment separation distance behind edge where separation force is applied. The scale is applied to AgentRadius. Range: 1..2
- L90 _public member_ `float PredictiveAvoidanceTime = 2.5f;` — `UPROPERTY(EditAnywhere, Category = "Predictive Avoidance", meta = (ClampMin = "0.1", ForceUnits="s"))` — How far in the future the agent reacts to collisions. Range: 1..3, Indoor humans 1.4, outdoor humans 2.4 (seconds).
- L94 _public member_ `float EnvironmentPredictiveAvoidanceTime = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Predictive Avoidance", meta = (ClampMin = "0.1", ForceUnits="s"))` — How far in the future the agent reacts to environment collisions.
- L98 _public member_ `float PredictiveAvoidanceRadiusScale = 0.65f;` — `UPROPERTY(EditAnywhere, Category = "Predictive Avoidance", meta = (ClampMin = "0", ForceUnits="x"))` — Agent radius scale for anticipatory avoidance. Making the scale smaller makes the agent more eager to squeeze through other agents. Range: 0.5..1
- L102 _public member_ `float PredictiveAvoidanceDistance = 75.f;` — `UPROPERTY(EditAnywhere, Category = "Predictive Avoidance", meta = (ClampMin = "0", ForceUnits="cm"))` — Predictive avoidance force effect distance. The avoidance force is applied at the point in future where the agents are closest. The actual observed separation distance will be smaller. Range: 0..200
- L106 _public member_ `float EnvironmentPredictiveAvoidanceDistance = 30.f;` — `UPROPERTY(EditAnywhere, Category = "Predictive Avoidance", meta = (ClampMin = "0", ForceUnits="cm"))` — Predictive environment avoidance force effect distance. The avoidance force is applied at the point in future where the agents are closest. The actual observed separation distance will be smaller. Range: 0..100
- L110 _public member_ `float ObstaclePredictiveAvoidanceStiffness = 700.f;` — `UPROPERTY(EditAnywhere, Category = "Predictive Avoidance", meta = (ClampMin = "0"))` — Predictive avoidance force stiffness between agents and obstacles. Range: 400..1000 N/cm
- L114 _public member_ `float EnvironmentPredictiveAvoidanceStiffness = 200.f;` — `UPROPERTY(EditAnywhere, Category = "Predictive Avoidance", meta = (ClampMin = "0"))` — Predictive avoidance force stiffness between agents and walls. Range: 400..1000 N/cm

#### struct `FMassStandingAvoidanceParameters`  
`struct FMassStandingAvoidanceParameters : public FMassConstSharedFragment`  
_L118-180_
- reflection: `USTRUCT()`
- inherits: `FMassConstSharedFragment`
- L122 _public function_ `FMassStandingAvoidanceParameters GetValidated() const`
- L133 _public member_ `float GhostObstacleDetectionDistance = 300.f;` — `UPROPERTY(EditAnywhere, Category = "General", meta = (ClampMin = "0.0", ForceUnits="cm"))` — The distance at which neighbour agents are detected when updating the ghost.
- L137 _public member_ `float GhostToTargetMaxDeviation = 80.0f;` — `UPROPERTY(EditAnywhere, Category = "Ghost", meta = (ClampMin = "0", ForceUnits="cm"))` — How far the ghost can deviate from the target location.
- L141 _public member_ `float GhostSteeringReactionTime = 2.0f;` — `UPROPERTY(EditAnywhere, Category = "Ghost", meta = (ClampMin = "0", ForceUnits="s"))`
- L145 _public member_ `float GhostStandSlowdownRadius = 15.0f;` — `UPROPERTY(EditAnywhere, Category = "Ghost", meta = (ClampMin = "0", ForceUnits="cm"))` — The steering will slow down when the ghost is closer than this distance to the target. Range: 5..50
- L149 _public member_ `float GhostMaxSpeed = 250.0f;` — `UPROPERTY(EditAnywhere, Category = "Ghost", meta = (ClampMin = "0", ForceUnits="cm/s"))` — Mas speed the ghost can move.
- L153 _public member_ `float GhostMaxAcceleration = 300.0f;` — `UPROPERTY(EditAnywhere, Category = "Ghost", meta = (ClampMin = "0", ForceUnits="cm/s"))` — Max acceleration of the ghost. Making this larger than the agent speed will make the ghost react quickly.
- L157 _public member_ `float GhostVelocityDampingTime = 0.4f;` — `UPROPERTY(EditAnywhere, Category = "Ghost", meta = (ClampMin = "0", ForceUnits="s"))` — How quickly the ghost speed goes to zero. The smaller the value, the more the movement is dampened.
- L161 _public member_ `float GhostSeparationRadiusScale = 0.8f;` — `UPROPERTY(EditAnywhere, Category = "Ghost", meta = (ClampMin = "0", ForceUnits="x"))` — Agent radius scale for separation. Making it smaller makes the separation softer. Range: 0.8..1
- L164 _public member_ `float GhostSeparationDistance = 20.0f;` — `UPROPERTY(EditAnywhere, Category = "Ghost", meta = (ClampMin = "0", ForceUnits="cm"))`
- L167 _public member_ `float GhostSeparationStiffness = 200.0f;` — `UPROPERTY(EditAnywhere, Category = "Ghost", meta = (ClampMin = "0", ForceUnits="N/cm"))`
- L171 _public member_ `float MovingObstacleAvoidanceScale = 3.0f;` — `UPROPERTY(EditAnywhere, Category = "Ghost", meta = (ClampMin = "0", ForceUnits="x"))` — How much avoidance is scaled for moving obstacles. Range: 1..5.
- L175 _public member_ `float MovingObstacleDirectionalScale = 0.1f;` — `UPROPERTY(EditAnywhere, Category = "Ghost", meta = (ClampMin = "0", ForceUnits="x"))` — How much the ghost avoidance is tuned down when the moving obstacle is moving away from the ghost. Range: 0..1
- L179 _public member_ `float MovingObstaclePersonalSpaceScale = 3.0f;` — `UPROPERTY(EditAnywhere, Category = "Ghost", meta = (ClampMin = "0", ForceUnits="x"))` — How much extra space is preserved in front of moving obstacles (relative to their size). Range: 1..5

#### struct `FNavigationAvoidanceEdge`  
`struct FNavigationAvoidanceEdge`  
_L184-195_
- desc: Edge with normal
- L186 _public function_ `FNavigationAvoidanceEdge(const FVector InStart, const FVector InEnd)`
- L192 _public member_ `FVector Start = FVector::ZeroVector;`
- L193 _public member_ `FVector End = FVector::ZeroVector;`
- L194 _public member_ `FVector LeftDir = FVector::ZeroVector;`

#### struct `FMassNavigationEdgesFragment`  
`struct FMassNavigationEdgesFragment : public FMassFragment`  
_L198-207_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- L202 _public member_ `static constexpr int MaxEdgesCount = 16;`
- L203 _public member_ `TArray<FNavigationAvoidanceEdge, TFixedAllocator<MaxEdgesCount>> AvoidanceEdges;`
- L206 _public member_ `bool bExtrudedEdges = false;` — Set to true if the edges already account for the agent radius.

#### struct `TMassFragmentTraits`  
`template<> struct TMassFragmentTraits<FMassNavigationEdgesFragment> final`  
_L210-216_

#### enum `TMassFragmentTraits::(anonymous)`  
``  
_L213-215_

#### struct `FMassAvoidanceEntitiesToIgnoreFragment`  
`struct FMassAvoidanceEntitiesToIgnoreFragment : public FMassFragment`  
_L219-225_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- L223 _public member_ `static constexpr int EntityCount = 4;`
- L224 _public member_ `TArray<FMassEntityHandle, TFixedAllocator<EntityCount>> EntitiesToIgnore;`

#### struct `TMassFragmentTraits`  
`template<> struct TMassFragmentTraits<FMassAvoidanceEntitiesToIgnoreFragment> final`  
_L228-234_

#### enum `TMassFragmentTraits::(anonymous)`  
``  
_L231-233_

#### Free symbols / members of external scopes

- L214 _enumerator_ `AuthorAcceptsItsNotTriviallyCopyable = true` (scope `TMassFragmentTraits::__anond65913220103`)
- L232 _enumerator_ `AuthorAcceptsItsNotTriviallyCopyable = true` (scope `TMassFragmentTraits::__anond65913220203`)

### `Plugins/AI/MassAI/Source/MassNavigation/Public/Avoidance/MassAvoidanceProcessors.h` (Public)


#### class `UMassMovingAvoidanceProcessor`  
`class UMassMovingAvoidanceProcessor : public UMassProcessor`  
_L20-33_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassProcessor`
- desc: Experimental: move using cumulative forces to avoid close agents
- L25 _public prototype_ `UMassMovingAvoidanceProcessor();`
- L28 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L29 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L32 _private member_ `FMassEntityQuery EntityQuery;`

#### class `UMassStandingAvoidanceProcessor`  
`class UMassStandingAvoidanceProcessor : public UMassProcessor`  
_L37-50_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassProcessor`
- desc: Avoidance while standing.
- L42 _public prototype_ `UMassStandingAvoidanceProcessor();`
- L45 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L46 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L49 _private member_ `FMassEntityQuery EntityQuery;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MASSNAVIGATION_API`
- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAvoidance, Warning, All);`
- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAvoidanceVelocities, Warning, All);`
- L13 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAvoidanceAgents, Warning, All);`
- L14 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAvoidanceObstacles, Warning, All);`

### `Plugins/AI/MassAI/Source/MassNavigation/Public/Avoidance/MassAvoidanceTrait.h` (Public)


#### class `UMassObstacleAvoidanceTrait`  
`class UMassObstacleAvoidanceTrait : public UMassEntityTraitBase`  
_L12-25_
- reflection: `UCLASS(MinimalAPI, meta = (DisplayName = "Avoidance"))`
- inherits: `UMassEntityTraitBase`
- L18 _protected prototype_ `virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;`
- L21 _protected member_ `FMassMovingAvoidanceParameters MovingParameters;` — `UPROPERTY(EditAnywhere, Category="")`
- L24 _protected member_ `FMassStandingAvoidanceParameters StandingParameters;` — `UPROPERTY(EditAnywhere, Category="")`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MASSNAVIGATION_API`

### `Plugins/AI/MassAI/Source/MassNavigation/Public/Avoidance/MassNavigationObstacleTrait.h` (Public)


#### class `UMassNavigationObstacleTrait`  
`class UMassNavigationObstacleTrait : public UMassEntityTraitBase`  
_L11-18_
- reflection: `UCLASS(MinimalAPI, meta = (DisplayName = "Navigation Obstacle"))`
- inherits: `UMassEntityTraitBase`
- L16 _protected prototype_ `virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MASSNAVIGATION_API`

### `Plugins/AI/MassAI/Source/MassNavigation/Public/IMassNavigationModule.h` (Public)


#### class `IMassNavigationModule`  
`class IMassNavigationModule : public IModuleInterface`  
_L14-39_
- inherits: `IModuleInterface`
- desc: The public interface to this module.  In most cases, this interface is only public to sibling modules within this plugin.
- L25 _public function_ `static inline IMassNavigationModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L35 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Plugins/AI/MassAI/Source/MassNavigation/Public/MassNavigationDebug.h` (Public)


#### struct `UE::MassNavigation::Debug::FDebugContext`  
`struct FDebugContext`  
_L18-58_
- L20 _public function_ `FDebugContext(const FMassExecutionContext& Context, const UObject* InFallbackLogOwner, const FLogCategoryBase& InCategory, const UWorld* InWorld, const FMassEntityHandle InEntity, int32 InEntityIndex) : LogContext(Context, ShouldLogEverythingWhenRecording()) , FallbackLogOwner(InFallbackLogOwner) , Category(InCategory) , World(InWorld) , Entity(InEntity) , EntityIndex(InEntityIndex)`
- L29 _public function_ `FDebugContext(const FMassExecutionContext& Context, const UObject* InFallbackLogOwner, const FLogCategoryBase& InCategory, const FMassEntityHandle InEntity, int32 InEntityIndex) : LogContext(Context, ShouldLogEverythingWhenRecording()) , FallbackLogOwner(InFallbackLogOwner) , Category(InCategory) , World(Mass::Debug::GetDebugDrawWorld(Context)) , Entity(InEntity) , EntityIndex(InEntityIndex)`
- L38 _public function_ `const UObject* GetLogOwner() const`
- L43 _public function_ `bool ShouldLogEntity(FColor* OutEntityColor = nullptr) const`
- L48 _public member_ `const Mass::Debug::FLoggingContext LogContext;`
- L51 _public member_ `const UObject* FallbackLogOwner;` — If entity has no debug owner set, use this instead. Usually the mass processor
- L52 _public member_ `const FLogCategoryBase& Category;`
- L53 _public member_ `const UWorld* World;`
- L54 _public member_ `const FMassEntityHandle Entity;`
- L57 _public member_ `const int32 EntityIndex;` — EntityIndex is index in current chunk

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MassNavigation` (scope `UE`)
- L13 _namespace_ `namespace Debug` (scope `UE::MassNavigation`)
- L16 _prototype_ `bool ShouldLogEverythingWhenRecording();` (scope `UE::MassNavigation::Debug`) — If true, will log all debug draw events regardless of debug entity selection if the visual log recorder is activated
- L60 _prototype_ `bool UseDrawDebugHelper();` (scope `UE::MassNavigation::Debug`)
- L61 _prototype_ `bool DebugIsSelected(const FMassEntityHandle Entity);` (scope `UE::MassNavigation::Debug`)
- L63 _prototype_ `void DebugDrawLine(const FDebugContext& Context, const FVector& Start, const FVector& End, const FColor& Color, const float Thickness = 0.f, const bool bPersistent = false, const FString& Text = FString());` (scope `UE::MassNavigation::Debug`)
- L66 _prototype_ `void DebugDrawArrow(const FDebugContext& Context, const FVector& Start, const FVector& End, const FColor& Color, const float HeadSize = 8.f, const float Thickness = 1.5f, const FString& Text = FString());` (scope `UE::MassNavigation::Debug`)
- L69 _prototype_ `void DebugDrawSphere(const FDebugContext& Context, const FVector& Center, const FVector::FReal InRadius, const FColor& Color, const FString& Text = FString());` (scope `UE::MassNavigation::Debug`)
- L72 _prototype_ `void DebugDrawBox(const FDebugContext& Context, const FBox& Box, const FColor& Color, const FString& Text = FString());` (scope `UE::MassNavigation::Debug`)
- L74 _prototype_ `void DebugDrawCylinder(const FDebugContext& Context, const FVector& Bottom, const FVector& Top, const FVector::FReal InRadius, const FColor& Color, const FString& Text = FString());` (scope `UE::MassNavigation::Debug`)
- L77 _prototype_ `void DebugDrawCircle(const FDebugContext& Context, const FVector& Bottom, const FVector::FReal InRadius, const FColor& Color, const FString& Text = FString());` (scope `UE::MassNavigation::Debug`)
- L80 _function_ `inline FColor MixColors(const FColor ColorA, const FColor ColorB)` (scope `UE::MassNavigation::Debug`)

### `Plugins/AI/MassAI/Source/MassNavigation/Public/MassNavigationFragments.h` (Public)


#### struct `FMassMoveTargetFragment`  
`struct FMassMoveTargetFragment : public FMassFragment`  
_L18-91_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- desc: Move target.
- L22 _public function_ `FMassMoveTargetFragment() : bNetDirty(false), bOffBoundaries(false), bSteeringFallingBehind(false)`
- L25 _public prototype_ `void CreateNewAction(const EMassMovementAction InAction, const UWorld& InWorld);` — To setup current action from the authoritative world
- L28 _public prototype_ `void CreateReplicatedAction(const EMassMovementAction InAction, const uint16 InActionID, const double InWorldStartTime, const double InServerStartTime);` — To setup current action from replicated data
- L30 _public function_ `void MarkNetDirty()`
- L31 _public function_ `bool GetNetDirty() const`
- L32 _public function_ `void ResetNetDirty()`
- L35 _public prototype_ `FString ToString() const;`
- L37 _public function_ `EMassMovementAction GetPreviousAction() const`
- L38 _public function_ `EMassMovementAction GetCurrentAction() const`
- L39 _public function_ `double GetCurrentActionStartTime() const`
- L40 _public function_ `double GetCurrentActionServerStartTime() const`
- L41 _public function_ `uint16 GetCurrentActionID() const`
- L43 _public member_ `static const float UnsetDistance;`
- L46 _public member_ `FVector Center = FVector::ZeroVector;` — Center of the move target.
- L49 _public member_ `FVector Forward = FVector::ZeroVector;` — Forward direction of the movement target.
- L52 _public member_ `float DistanceToGoal = 0.0f;` — Distance remaining to the movement goal.
- L55 _public member_ `float EntityDistanceToGoal = UnsetDistance;` — Projected progress distance of the entity using the path.
- L58 _public member_ `float SlackRadius = 0.0f;` — Allowed deviation around the movement target.
- L62 _private member_ `double CurrentActionWorldStartTime = 0.0;` — World time in seconds when the action started.
- L65 _private member_ `double CurrentActionServerStartTime = 0.0;` — Server time in seconds when the action started.
- L68 _private member_ `uint16 CurrentActionID = 0;` — Number incremented each time new action (i.e move, stand, animation) is started.
- L72 _public member_ `FMassInt16Real DesiredSpeed = FMassInt16Real(0.0f);` — Requested movement speed.
- L75 _public member_ `EMassMovementAction IntentAtGoal = EMassMovementAction::Move;` — Intended movement action at the target.
- L79 _private member_ `EMassMovementAction CurrentAction = EMassMovementAction::Move;` — Current movement action.
- L82 _private member_ `EMassMovementAction PreviousAction = EMassMovementAction::Move;` — Previous movement action.
- L84 _private member_ `uint8 bNetDirty : 1;`
- L87 _public member_ `uint8 bOffBoundaries : 1;` — True if the movement target is assumed to be outside navigation boundaries.
- L90 _public member_ `uint8 bSteeringFallingBehind : 1;` — True if the movement target is assumed to be outside navigation boundaries.

#### struct `FMassGhostLocationFragment`  
`struct FMassGhostLocationFragment : public FMassFragment`  
_L95-112_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- desc: Ghost location used for standing navigation.
- L99 _public function_ `bool IsValid(const uint16 CurrentActionID) const`
- L105 _public member_ `uint16 LastSeenActionID = 0;` — The action ID the ghost was initialized for
- L108 _public member_ `FVector Location = FVector::ZeroVector;` — Location of the ghost
- L111 _public member_ `FVector Velocity = FVector::ZeroVector;` — Velocity of the ghost

#### struct `FMassNavigationObstacleGridCellLocationFragment`  
`struct FMassNavigationObstacleGridCellLocationFragment : public FMassFragment`  
_L116-120_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- desc: Cell location for dynamic obstacles
- L119 _public member_ `FNavigationObstacleHashGrid2D::FCellLocation CellLoc;`

#### enum `EMassColliderType`  
`enum class EMassColliderType : uint8`  
_L123-127_
- L125 _public enumerator_ `Circle`
- L126 _public enumerator_ `Pill`

#### struct `FMassCircleCollider`  
`struct FMassCircleCollider`  
_L129-134_
- L131 _public prototype_ `FMassCircleCollider() = default;`
- L132 _public function_ `FMassCircleCollider(const float Radius) : Radius(Radius)`
- L133 _public member_ `float Radius = 0.f;`

#### struct `FMassPillCollider`  
`struct FMassPillCollider`  
_L136-142_
- L138 _public prototype_ `FMassPillCollider() = default;`
- L139 _public function_ `FMassPillCollider(const float Radius, const float HalfLength) : Radius(Radius), HalfLength(HalfLength)`
- L140 _public member_ `float Radius = 0.f;`
- L141 _public member_ `float HalfLength = 0.f;`

#### struct `FMassAvoidanceColliderFragment`  
`struct FMassAvoidanceColliderFragment : public FMassFragment`  
_L146-185_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- desc: Fragment holding data for avoidance colliders
- L150 _public function_ `FMassAvoidanceColliderFragment()`
- L157 _public function_ `FMassAvoidanceColliderFragment(const FMassCircleCollider& Circle)`
- L164 _public function_ `FMassAvoidanceColliderFragment(const FMassPillCollider& Pill)`
- L171 _public function_ `FMassCircleCollider GetCircleCollider() const`
- L177 _public function_ `FMassPillCollider GetPillCollider() const`
- L183 _public member_ `float Data[2];`
- L184 _public member_ `EMassColliderType Type;`

#### struct `FMassInNavigationObstacleGridTag`  
`struct FMassInNavigationObstacleGridTag : public FMassTag`  
_L190-193_
- reflection: `USTRUCT()`
- inherits: `FMassTag`
- desc: Tag to tell if the entity is in the navigation obstacle grid

#### struct `FMassAvoidancePreventBackwardMovementTag`  
`struct FMassAvoidancePreventBackwardMovementTag : public FMassTag`  
_L197-200_
- reflection: `USTRUCT()`
- inherits: `FMassTag`
- desc: Tag used to prevent avoidance from generating backward movements

#### Free symbols / members of external scopes

- L202 _typedef_ `UE_DEPRECATED(5.8, "Renamed to FMassNavigationRelevantParameters.") typedef struct FNavigationRelevant`
- L203 _typedef_ `UE_DEPRECATED(5.8, "Renamed to FMassNavigationRelevantFragment") typedef struct FNavigationRelevan` — `UE_DEPRECATED(5.8, "Renamed to FMassNavigationRelevantParameters.")`

### `Plugins/AI/MassAI/Source/MassNavigation/Public/MassNavigationProcessors.h` (Public)


#### class `UMassOffLODNavigationProcessor`  
`class UMassOffLODNavigationProcessor : public UMassProcessor`  
_L18-31_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassProcessor`
- desc: Updates Off-LOD entities position to move targets position.
- L23 _public prototype_ `UMassOffLODNavigationProcessor();`
- L26 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L27 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L30 _private member_ `FMassEntityQuery EntityQuery_Conditional;`

#### class `UMassNavigationSmoothHeightProcessor`  
`class UMassNavigationSmoothHeightProcessor : public UMassProcessor`  
_L38-51_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassProcessor`
- desc: Updates entities height to move targets position smoothly. Does not update Off-LOD entities.
- L43 _public prototype_ `UMassNavigationSmoothHeightProcessor();`
- L46 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L47 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L50 _private member_ `FMassEntityQuery EntityQuery;`

#### class `UMassMoveTargetFragmentInitializer`  
`class UMassMoveTargetFragmentInitializer : public UMassObserverProcessor`  
_L57-68_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassObserverProcessor`
- desc: Initializes the move target's location to the agents initial position.
- L61 _public prototype_ `UMassMoveTargetFragmentInitializer();`
- L64 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L65 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L67 _protected member_ `FMassEntityQuery InitializerQuery;`

#### class `UMassNavigationObstacleGridProcessor`  
`class UMassNavigationObstacleGridProcessor : public UMassProcessor`  
_L72-87_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassProcessor`
- desc: Processor to update obstacle grid
- L77 _public prototype_ `UMassNavigationObstacleGridProcessor();`
- L80 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L81 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L84 _private member_ `FMassEntityQuery AddToGridEntityQuery;`
- L85 _private member_ `FMassEntityQuery UpdateGridEntityQuery;`
- L86 _private member_ `FMassEntityQuery RemoveFromGridEntityQuery;`

#### class `UMassNavigationObstacleRemoverProcessor`  
`class UMassNavigationObstacleRemoverProcessor : public UMassObserverProcessor`  
_L91-102_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassObserverProcessor`
- desc: Deinitializer processor to remove avoidance obstacles from the avoidance obstacle grid
- L95 _private prototype_ `UMassNavigationObstacleRemoverProcessor();`
- L98 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L99 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L101 _protected member_ `FMassEntityQuery EntityQuery;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MASSNAVIGATION_API`

### `Plugins/AI/MassAI/Source/MassNavigation/Public/MassNavigationSubsystem.h` (Public)


#### enum `EMassNavigationObstacleFlags`  
`enum class EMassNavigationObstacleFlags : uint8`  
_L15-19_
- reflection: `UENUM()`
- L17 _public enumerator_ `None = 0`
- L18 _public enumerator_ `HasColliderData = 1 << 0`

#### struct `FMassNavigationObstacleItem`  
`struct FMassNavigationObstacleItem`  
_L22-31_
- L24 _public function_ `bool operator==(const FMassNavigationObstacleItem& Other) const`
- L29 _public member_ `FMassEntityHandle Entity;`
- L30 _public member_ `EMassNavigationObstacleFlags ItemFlags = EMassNavigationObstacleFlags::None;`

#### class `UMassNavigationSubsystem`  
`class UMassNavigationSubsystem : public UMassSubsystemBase`  
_L36-52_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassSubsystemBase`
- L41 _public prototype_ `UMassNavigationSubsystem();`
- L43 _public function_ `const FNavigationObstacleHashGrid2D& GetObstacleGrid() const`
- L44 _public function_ `FNavigationObstacleHashGrid2D& GetObstacleGridMutable()`
- L48 _protected prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;` — USubsystem BEGIN
- L51 _protected member_ `FNavigationObstacleHashGrid2D AvoidanceObstacleGrid;`

#### struct `TMassExternalSubsystemTraits`  
`template<> struct TMassExternalSubsystemTraits<UMassNavigationSubsystem> final`  
_L55-62_

#### enum `TMassExternalSubsystemTraits::(anonymous)`  
``  
_L58-61_

#### Free symbols / members of external scopes

- L33 _typedef_ `typedef THierarchicalHashGrid2D<2, 4, FMassNavigationObstacleItem> FNavigationObstacleHashGrid2D;` — 2 levels of hierarchy, 4 ratio between levels
- L59 _enumerator_ `GameThreadOnly = false` (scope `TMassExternalSubsystemTraits::__anoncdf0b0170103`)
- L60 _enumerator_ `ThreadSafeWrite = false` (scope `TMassExternalSubsystemTraits::__anoncdf0b0170103`)

### `Plugins/AI/MassAI/Source/MassNavigation/Public/MassNavigationTypes.h` (Public)


#### enum `EMassMovementAction`  
`enum class EMassMovementAction : uint8`  
_L26-31_
- reflection: `UENUM()`
- L28 _public enumerator_ `Stand` — Stop and stand.
- L29 _public enumerator_ `Move` — Move or keep on moving.
- L30 _public enumerator_ `Animate` — Animation has control over the transform

#### struct `FMassTargetLocation`  
`struct FMassTargetLocation`  
_L35-57_
- reflection: `USTRUCT()`
- desc: Target location used by tasks
- L39 _public function_ `void Reset()`
- L48 _public member_ `TOptional<FVector> EndOfPathPosition;` — `UPROPERTY(VisibleAnywhere, Category = Navigation, transient)` — Optional end of path location.
- L52 _public member_ `TOptional<FQuat> EndOfPathRotation;` — `UPROPERTY(VisibleAnywhere, Category = Navigation, transient)` — Optional end of path rotation.
- L56 _public member_ `EMassMovementAction EndOfPathIntent = EMassMovementAction::Move;` — `UPROPERTY(VisibleAnywhere, Category = Navigation, transient)` — Movement intent at the end of the path

#### Free symbols / members of external scopes

- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMassNavigation, Warning, All);`
- L13 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMassNavigationObstacle, Warning, All);`
- L16 _macro_ `#define HACK_DISABLE_PATH_CHANGED_ON_LOWER_LOD 1` — @ todo remove optimization hack once we find a better way to filter out signals from LOD/listener on signals, as for now we only need this signal for look at in high and med LOD
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Mass` (scope `UE`)
- L18 _namespace_ `namespace Signals` (scope `UE::Mass`)
- L20 _variable_ `const FName FollowPointPathStart = FName(TEXT("Foll` (scope `UE::Mass::Signals`)
- L21 _variable_ `const FName FollowPointPathDone = FName(TEXT("Foll` (scope `UE::Mass::Signals`)
- L22 _variable_ `const FName CurrentLaneChanged = FName(TEXT("Curr` (scope `UE::Mass::Signals`)

### `Plugins/AI/MassAI/Source/MassNavigation/Public/MassNavigationUtils.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MassNavigation` (scope `UE`)
- L12 _function_ `inline FQuat::FReal GetYawFromQuat(const FQuat Rotation)` (scope `UE::MassNavigation`) — Calculates yaw angle from direction vector.
- L19 _function_ `inline FVector::FReal GetYawFromDirection(const FVector Direction)` (scope `UE::MassNavigation`)
- L25 _function_ `inline FVector::FReal WrapAngle(const FVector::FReal Angle)` (scope `UE::MassNavigation`) — Wraps and angle to range -PI..PI. Angle in radians.
- L34 _function_ `inline FVector::FReal LerpAngle(const FVector::FReal AngleA, const FVector::FReal AngleB, const FVector::FReal T)` (scope `UE::MassNavigation`) — Linearly interpolates between two angles (in Radians).
- L41 _function_ `inline FVector::FReal ExponentialSmoothingAngle(const FVector::FReal Angle, const FVector::FReal TargetAngle, const FVector::FReal DeltaTime, const FVector::FReal SmoothingTime)` (scope `UE::MassNavigation`) — Exponential smooth from current angle to target angle. Angles in radians.
- L54 _function_ `inline FVector ClampVector(const FVector Vec, const FVector::FReal Mag)` (scope `UE::MassNavigation`) — Clamps vectors magnitude to Mag.
- L64 _function_ `inline FVector::FReal ProjectPtSeg(const FVector2D Point, const FVector2D Start, const FVector2D End)` (scope `UE::MassNavigation`) — Projects a point to segment and returns the time interpolation value.
- L85 _function_ `inline float Smooth(const float X)` (scope `UE::MassNavigation`) — Returns the SmoothStep curve for X in range [0..1].
- L91 _function_ `inline double Smooth(const double X)` (scope `UE::MassNavigation`) — Returns the SmoothStep curve for X in range [0..1].
- L97 _function_ `inline FVector GetLeftDirection(const FVector Forward, const FVector Up)` (scope `UE::MassNavigation`) — Returns left direction from forward and up directions.
- L103 _function_ `inline FVector ComputeMiterNormal(const FVector NormalA, const FVector NormalB)` (scope `UE::MassNavigation`) — Computes miter normal in XY plane from two neighbour edge normals.

### `Plugins/AI/MassAI/Source/MassNavigation/Public/SmoothOrientation/MassSmoothOrientationFragments.h` (Public)


#### struct `FMassSmoothOrientationWeights`  
`struct FMassSmoothOrientationWeights : public FMassSharedFragment`  
_L13-30_
- reflection: `USTRUCT()`
- inherits: `FMassSharedFragment`
- L17 _public prototype_ `FMassSmoothOrientationWeights() = default;`
- L19 _public function_ `FMassSmoothOrientationWeights(const float InMoveTargetWeight, const float InVelocityWeight) : MoveTargetWeight(InMoveTargetWeight) , VelocityWeight(InVelocityWeight)`
- L26 _public member_ `float MoveTargetWeight = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Orientation", meta = (ClampMin = "0.0", ClampMax="1.0"))`
- L29 _public member_ `float VelocityWeight = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Orientation", meta = (ClampMin = "0.0", ClampMax="1.0"))`

#### struct `FMassSmoothOrientationParameters`  
`struct FMassSmoothOrientationParameters : public FMassConstSharedFragment`  
_L33-52_
- reflection: `USTRUCT()`
- inherits: `FMassConstSharedFragment`
- L39 _public member_ `float EndOfPathDuration = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Orientation", meta = (ClampMin = "0.0", ForceUnits="s"))` — The time it takes the orientation to catchup to the requested orientation.
- L43 _public member_ `float OrientationSmoothingTime = 0.3f;` — `UPROPERTY(EditAnywhere, Category = "Orientation", meta = (ClampMin = "0.0", ForceUnits="s"))` — The time it takes the orientation to catchup to the requested orientation.
- L47 _public member_ `FMassSmoothOrientationWeights Moving = FMassSmoothOrientationWeights( 0.4f, 0.6f);` — `UPROPERTY(EditAnywhere, Category = "Orientation")` — Orientation blending weights while moving.
- L51 _public member_ `FMassSmoothOrientationWeights Standing = FMassSmoothOrientationWeights( 0.95f, 0.05f);` — `UPROPERTY(EditAnywhere, Category = "Orientation")` — Orientation blending weights while standing.

### `Plugins/AI/MassAI/Source/MassNavigation/Public/SmoothOrientation/MassSmoothOrientationProcessors.h` (Public)


#### class `UMassSmoothOrientationProcessor`  
`class UMassSmoothOrientationProcessor : public UMassProcessor`  
_L15-29_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassProcessor`
- desc: Updates agent's orientation based on current movement.
- L20 _public prototype_ `UMassSmoothOrientationProcessor();`
- L23 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L24 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L27 _private member_ `FMassEntityQuery HighResEntityQuery;`
- L28 _private member_ `FMassEntityQuery LowResEntityQuery_Conditional;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MASSNAVIGATION_API`

### `Plugins/AI/MassAI/Source/MassNavigation/Public/SmoothOrientation/MassSmoothOrientationTrait.h` (Public)


#### class `UMassSmoothOrientationTrait`  
`class UMassSmoothOrientationTrait : public UMassEntityTraitBase`  
_L12-21_
- reflection: `UCLASS(MinimalAPI, meta = (DisplayName = "Smooth Orientation"))`
- inherits: `UMassEntityTraitBase`
- L17 _protected prototype_ `virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;`
- L20 _protected member_ `FMassSmoothOrientationParameters Orientation;` — `UPROPERTY(EditAnywhere, Category="")`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MASSNAVIGATION_API`

### `Plugins/AI/MassAI/Source/MassNavigation/Public/Steering/MassSteeringFragments.h` (Public)


#### struct `FMassSteeringFragment`  
`struct FMassSteeringFragment : public FMassFragment`  
_L16-27_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- desc: Steering fragment.
- L20 _public function_ `void Reset()`
- L26 _public member_ `FVector DesiredVelocity = FVector::ZeroVector;` — Cached desired velocity from steering. Note: not used for moving the entity.

#### struct `FMassStandingSteeringFragment`  
`struct FMassStandingSteeringFragment : public FMassFragment`  
_L31-49_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- desc: Standing steering.
- L36 _public member_ `FVector TargetLocation = FVector::ZeroVector;` — Selected steer target based on ghost, updates periodically.
- L39 _public member_ `float TrackedTargetSpeed = 0.0f;` — Used during target update to see when the target movement stops
- L42 _public member_ `float TargetSelectionCooldown = 0.0f;` — Cooldown between target updates
- L45 _public member_ `bool bIsUpdatingTarget = false;` — True if the target is being updated
- L48 _public member_ `bool bEnteredFromMoveAction = false;` — True if we just entered from move action

#### struct `FMassSteerToMoveTargetPreventSlowdownTag`  
`struct FMassSteerToMoveTargetPreventSlowdownTag : public FMassTag`  
_L53-56_
- reflection: `USTRUCT()`
- inherits: `FMassTag`
- desc: Tag used to prevent steering from generating a slowdown force.

#### struct `FMassMovingSteeringParameters`  
`struct FMassMovingSteeringParameters : public FMassConstSharedFragment`  
_L60-79_
- reflection: `USTRUCT()`
- inherits: `FMassConstSharedFragment`
- desc: Steering related movement parameters.
- L66 _public member_ `float ReactionTime = 0.3f;` — `UPROPERTY(config, EditAnywhere, Category = "Moving", meta = (ClampMin = "0.05", ForceUnits="s"))` — Steering reaction time in seconds.
- L70 _public member_ `float LookAheadTime = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Moving", meta = (ClampMin = "0", ForceUnits="s"))` — How much we look ahead when steering. Affects how steeply we steer towards the goal and when to start to slow down at the end of the path.
- L74 _public member_ `float SteeringPreventSlowdownAttenuationDistance = 50.f;` — `UPROPERTY(EditAnywhere, Category = "Moving", meta = (ClampMin = "0", ForceUnits="s"))` — When using FMassSteerToMoveTargetPreventSlowdownTag, maximum distance at which slowdown reduction is applied.
- L78 _public member_ `bool bAllowSpeedVariance = true;` — `UPROPERTY(EditAnywhere, Category = "Moving")` — Allow directional and catchup speed variance.

#### struct `FMassStandingSteeringParameters`  
`struct FMassStandingSteeringParameters : public FMassConstSharedFragment`  
_L82-111_
- reflection: `USTRUCT()`
- inherits: `FMassConstSharedFragment`
- L88 _public member_ `float TargetMoveThreshold = 15.0f;` — `UPROPERTY(EditAnywhere, Category = "Standing", meta = (ClampMin = "0.05", ForceUnits="cm"))` — How much the ghost should deviate from the target before updating the target.
- L91 _public member_ `float TargetMoveThresholdVariance = 0.1f;` — `UPROPERTY(EditAnywhere, Category = "Standing")`
- L95 _public member_ `float LowSpeedThreshold = 3.0f;` — `UPROPERTY(EditAnywhere, Category = "Movement", meta = (ClampMin = "0.0", ForceUnits="cm/s"))` — If the velocity is below this threshold, it is clamped to 0. This allows to prevent jittery movement when trying to be stationary.
- L99 _public member_ `float TargetSpeedHysteresisScale = 0.85f;` — `UPROPERTY(EditAnywhere, Category = "Standing", meta = (ClampMin = "0.05", ForceUnits="x"))` — How much the max speed can drop before we stop tracking it.
- L103 _public member_ `float TargetSelectionCooldown = 1.5f;` — `UPROPERTY(EditAnywhere, Category = "Standing", meta = (ClampMin = "0.05", ForceUnits="s"))` — Time between updates, varied randomly.
- L106 _public member_ `float TargetSelectionCooldownVariance = 0.5f;` — `UPROPERTY(EditAnywhere, Category = "Standing")`
- L110 _public member_ `float DeadZoneRadius = 15.0f;` — `UPROPERTY(EditAnywhere, Category = "Standing", meta = (ForceUnits="cm"))` — How much the target should deviate from the current location before updating the force on the agent.

### `Plugins/AI/MassAI/Source/MassNavigation/Public/Steering/MassSteeringProcessors.h` (Public)


#### class `UMassSteerToMoveTargetProcessor`  
`class UMassSteerToMoveTargetProcessor : public UMassProcessor`  
_L16-27_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassProcessor`
- desc: Processor for updating steering towards MoveTarget.
- L21 _protected prototype_ `UMassSteerToMoveTargetProcessor();`
- L23 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L24 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L26 _protected member_ `FMassEntityQuery EntityQuery;`

### `Plugins/AI/MassAI/Source/MassNavigation/Public/Steering/MassSteeringTrait.h` (Public)


#### class `UMassSteeringTrait`  
`class UMassSteeringTrait : public UMassEntityTraitBase`  
_L13-25_
- reflection: `UCLASS(MinimalAPI, meta = (DisplayName = "Steering"))`
- inherits: `UMassEntityTraitBase`
- L18 _protected prototype_ `virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;`
- L21 _protected member_ `FMassMovingSteeringParameters MovingSteering;` — `UPROPERTY(Category="Steering", EditAnywhere, meta=(EditInline))`
- L24 _protected member_ `FMassStandingSteeringParameters StandingSteering;` — `UPROPERTY(Category="Steering", EditAnywhere, meta=(EditInline))`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MASSNAVIGATION_API`
