# Plugins / MassZoneGraphNavigation

- module root: `Plugins/AI/MassAI/Source/MassZoneGraphNavigation`
- headers: 6; symbols: 101
- symbol kinds: class=5, function=14, macro=3, member=52, namespace=2, prototype=17, struct=8
- PrivateDependencyModuleNames: EditorFramework, UnrealEd
- PublicDependencyModuleNames: AIModule, Core, CoreUObject, DeveloperSettings, Engine, MassCommon, MassCore, MassEntity, MassGameplayExternalTraits, MassLOD, MassMovement, MassNavigation, MassSignals, MassSimulation, MassSpawner, ZoneGraph, ZoneGraphAnnotations

### `Plugins/AI/MassAI/Source/MassZoneGraphNavigation/Public/IMassZoneGraphNavigationModule.h` (Public)


#### class `IMassZoneGraphNavigationModule`  
`class IMassZoneGraphNavigationModule : public IModuleInterface`  
_L14-39_
- inherits: `IModuleInterface`
- desc: The public interface to this module.  In most cases, this interface is only public to sibling modules within this plugin.
- L25 _public function_ `static inline IMassZoneGraphNavigationModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L35 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Plugins/AI/MassAI/Source/MassZoneGraphNavigation/Public/MassZoneGraphNavigationFragments.h` (Public)


#### struct `FMassZoneGraphNavigationParameters`  
`struct FMassZoneGraphNavigationParameters : public FMassConstSharedFragment`  
_L16-27_
- reflection: `USTRUCT()`
- inherits: `FMassConstSharedFragment`
- L22 _public member_ `FZoneGraphTagFilter LaneFilter;` — `UPROPERTY(EditAnywhere, Category="Navigation")` — Filter describing which lanes can be used when spawned.
- L26 _public member_ `float QueryRadius = 500.0f;` — `UPROPERTY(EditAnywhere, Category="Navigation", meta = (UIMin = 0.0, ClampMin = 0.0, ForceUnits="cm"))` — Query radius when trying to find nearest lane when spawned.

#### struct `FMassZoneGraphPathRequestFragment`  
`struct FMassZoneGraphPathRequestFragment : public FMassFragment`  
_L32-39_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- desc: Stores path request associated to a new movement action. This is used to replicate actions.
- L38 _public member_ `FZoneGraphShortPathRequest PathRequest;` — `UPROPERTY(Transient)` — Short path request Handle to current lane.

#### struct `FMassZoneGraphLaneLocationFragment`  
`struct FMassZoneGraphLaneLocationFragment : public FMassFragment`  
_L43-55_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- desc: Describes current location on ZoneGraph
- L48 _public member_ `FZoneGraphLaneHandle LaneHandle;` — Handle to current lane.
- L51 _public member_ `float DistanceAlongLane = 0.0f;` — Distance along current lane.
- L54 _public member_ `float LaneLength = 0.0f;` — Cached lane length, used for clamping and testing if at end of lane.

#### struct `FMassZoneGraphCachedLaneFragment`  
`struct FMassZoneGraphCachedLaneFragment : public FMassFragment`  
_L59-183_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- desc: Describes part of a ZoneGraph lane.
- L63 _public member_ `static constexpr uint8 MaxPoints = 5;`
- L65 _public function_ `void Reset()`
- L74 _public prototype_ `void CacheLaneData(const FZoneGraphStorage& ZoneGraphStorage, const FZoneGraphLaneHandle CurrentLaneHandle, const float CurrentDistanceAlongLane, const float TargetDistanceAlongLane, const float InflateDistance);` — Caches portion of a lane from ZoneGraph.
- L77 _public function_ `int32 FindSegmentIndexAtDistance(const float DistanceAlongPath) const`
- L92 _public function_ `float GetInterpolationTimeOnSegment(const int32 SegmentIndex, const float DistanceAlongPath) const`
- L102 _public function_ `void InterpolatePointAndTangentOnSegment(const int32 SegmentIndex, const float DistanceAlongPath, FVector& OutPoint, FVector& OutTangent) const`
- L109 _public function_ `FVector InterpolatePointOnSegment(const int32 SegmentIndex, const float DistanceAlongPath) const`
- L115 _public function_ `void GetPointAndTangentAtDistance(const float DistanceAlongPath, FVector& OutPoint, FVector& OutTangent) const`
- L134 _public function_ `FVector GetPointAtDistance(const float DistanceAlongPath) const`
- L149 _public function_ `bool IsDistanceAtLaneExtrema(const float Distance) const`
- L155 _public member_ `FZoneGraphLaneHandle LaneHandle;`
- L158 _public member_ `TStaticArray<FVector, MaxPoints> LanePoints;` — Lane points
- L161 _public member_ `float LaneLength = 0.0f;` — Cached length of the lane.
- L164 _public member_ `TStaticArray<FMassSnorm8Vector2D, MaxPoints> LaneTangentVectors;` — Lane tangents
- L167 _public member_ `TStaticArray<FMassInt16Real10, MaxPoints> LanePointProgressions;` — lane Advance distances
- L170 _public member_ `FMassInt16Real LaneWidth = FMassInt16Real(0.0f);` — Cached width of the lane.
- L173 _public member_ `FMassInt16Real LaneLeftSpace = FMassInt16Real(0.0f);` — Additional space left of the lane
- L176 _public member_ `FMassInt16Real LaneRightSpace = FMassInt16Real(0.0f);` — Additional space right of the lane
- L179 _public member_ `uint16 CacheID = 0;` — ID incremented each time the cache is updated.
- L182 _public member_ `uint8 NumPoints = 0;` — Number of points on path.

#### struct `FMassZoneGraphPathPoint`  
`struct FMassZoneGraphPathPoint`  
_L186-207_
- reflection: `USTRUCT()`
- L191 _public member_ `FVector Position = FVector::ZeroVector;` — Position of the path.
- L194 _public member_ `FMassSnorm8Vector2D Tangent;` — Tangent direction of the path.
- L197 _public member_ `FMassInt16Real10 DistanceAlongLane = FMassInt16Real10(0.0f);` — Position of the point along the original path. (Could potentially be uint16 at 10cm accuracy)
- L200 _public member_ `FMassInt16Real Distance = FMassInt16Real(0.0f);` — Distance along the offset path from first point. (Could potentially be uint16 at 10cm accuracy)
- L203 _public member_ `uint8 bOffLane : 1;` — True if this point is assumed to be off lane.
- L206 _public member_ `uint8 bIsLaneExtrema : 1;` — True if this point is lane start or end point.

#### struct `FMassZoneGraphShortPathFragment`  
`struct FMassZoneGraphShortPathFragment : public FMassFragment`  
_L214-280_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- desc: @todo MassMovement: it should be possible to prune this down to 64bytes - remove debug lane handle, and replace other with index - see if we can remove move tangent?
- L218 _public prototype_ `FMassZoneGraphShortPathFragment() = default;`
- L220 _public member_ `static constexpr uint8 MaxPoints = 3;`
- L222 _public function_ `void Reset()`
- L238 _public prototype_ `bool RequestPath(const FMassZoneGraphCachedLaneFragment& CachedLane, const FZoneGraphShortPathRequest& Request, const float CurrentDistanceAlongLane, const float AgentRadius);` — Requests path along the current lane
- L241 _public prototype_ `bool RequestStand(const FMassZoneGraphCachedLaneFragment& CachedLane, const float CurrentDistanceAlongLane, const FVector& CurrentPosition);` — Requests path to stand at current position.
- L243 _public function_ `bool IsDone() const`
- L251 _public member_ `FZoneGraphLaneHandle DebugLaneHandle;` — Current lane handle, for debug
- L255 _public member_ `FZoneGraphLaneHandle NextLaneHandle;` — If valid, the this lane will be set as current lane after the path follow is completed.
- L258 _public member_ `float ProgressDistance = 0.0f;` — Current progress distance along the lane.
- L261 _public member_ `TStaticArray<FMassZoneGraphPathPoint, MaxPoints> Points;` — Path points
- L264 _public member_ `EZoneLaneLinkType NextExitLinkType = EZoneLaneLinkType::None;` — If next lane is set, this is how to reach the lane from current lane.
- L267 _public member_ `uint8 NumPoints = 0;` — Number of points on path.
- L270 _public member_ `EMassMovementAction EndOfPathIntent = EMassMovementAction::Stand;` — Intent at the end of the path.
- L273 _public member_ `uint8 bMoveReverse : 1;` — True if we're moving reverse
- L276 _public member_ `uint8 bPartialResult : 1;` — True if the path was partial.
- L279 _public member_ `uint8 bDone : 1;` — True when path follow is completed.

#### struct `FMassLaneCacheBoundaryFragment`  
`struct FMassLaneCacheBoundaryFragment : public FMassFragment`  
_L283-292_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- L288 _public member_ `FVector LastUpdatePosition = FVector::ZeroVector;` — Last update position.
- L291 _public member_ `uint16 LastUpdateCacheID = 0;` — Lane cached ID at last update.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MASSZONEGRAPHNAVIGATION_API`

### `Plugins/AI/MassAI/Source/MassZoneGraphNavigation/Public/MassZoneGraphNavigationProcessors.h` (Public)


#### class `UMassZoneGraphLocationInitializer`  
`class UMassZoneGraphLocationInitializer : public UMassObserverProcessor`  
_L19-31_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassObserverProcessor`
- desc: Processor for initializing nearest location on ZoneGraph.
- L24 _public prototype_ `UMassZoneGraphLocationInitializer();`
- L27 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L28 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L30 _protected member_ `FMassEntityQuery EntityQuery;`

#### class `UMassZoneGraphPathFollowProcessor`  
`class UMassZoneGraphPathFollowProcessor : public UMassProcessor`  
_L37-48_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassProcessor`
- desc: Processor for updating move target on ZoneGraph path.
- L42 _protected prototype_ `UMassZoneGraphPathFollowProcessor();`
- L44 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L45 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L47 _protected member_ `FMassEntityQuery EntityQuery_Conditional;`

#### class `UMassZoneGraphLaneCacheBoundaryProcessor`  
`class UMassZoneGraphLaneCacheBoundaryProcessor : public UMassProcessor`  
_L53-66_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassProcessor`
- desc: @todo MassMovement: Make this signal based.
- L58 _public prototype_ `UMassZoneGraphLaneCacheBoundaryProcessor();`
- L61 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L62 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L65 _private member_ `FMassEntityQuery EntityQuery;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MASSZONEGRAPHNAVIGATION_API`

### `Plugins/AI/MassAI/Source/MassZoneGraphNavigation/Public/MassZoneGraphNavigationTrait.h` (Public)


#### class `UMassZoneGraphNavigationTrait`  
`class UMassZoneGraphNavigationTrait : public UMassEntityTraitBase`  
_L13-22_
- reflection: `UCLASS(MinimalAPI, meta = (DisplayName = "ZoneGraph Navigation"))`
- inherits: `UMassEntityTraitBase`
- L18 _protected prototype_ `virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;`
- L21 _protected member_ `FMassZoneGraphNavigationParameters NavigationParameters;` — `UPROPERTY(Category="Movement", EditAnywhere)`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MASSZONEGRAPHNAVIGATION_API`

### `Plugins/AI/MassAI/Source/MassZoneGraphNavigation/Public/MassZoneGraphNavigationTypes.h` (Public)


#### struct `FZoneGraphShortPathRequest`  
`struct FZoneGraphShortPathRequest`  
_L12-78_
- reflection: `USTRUCT()`
- desc: Describes path request along one ZoneGraph lane. If the NextLaneHandle is set, lane is changed when path finishes.
- L16 _public function_ `FZoneGraphShortPathRequest() : bMoveReverse(false) , bIsEndOfPathPositionSet(false) , bIsEndOfPathDirectionSet(false)`
- L23 _public function_ `FString ToString() const`
- L34 _public member_ `FVector StartPosition = FVector::ZeroVector;` — `UPROPERTY(Transient)` — Position used as the start of the path
- L38 _public member_ `FVector EndOfPathPosition = FVector::ZeroVector;` — `UPROPERTY(Transient)` — Optional specific point at the end of the path.
- L42 _public member_ `FZoneGraphLaneHandle NextLaneHandle;` — `UPROPERTY(Transient)` — If set, the lane will be switched when path finishes.
- L46 _public member_ `float TargetDistance = 0.0f;` — `UPROPERTY(Transient)` — Distance to move.
- L50 _public member_ `FMassSnorm8Vector EndOfPathDirection;` — `UPROPERTY(Transient)` — Optional specific direction at the end of the path. Used only if EndOfPathPosition is set.
- L54 _public member_ `FMassInt16Real AnticipationDistance = FMassInt16Real(50.f);` — `UPROPERTY(Transient)` — If start or end of path is off-lane, the distance along the lane is pushed forward/back along the lane to make smoother transition.
- L57 _public member_ `FMassInt16Real EndOfPathOffset = FMassInt16Real(0.0f);` — `UPROPERTY(Transient)`
- L61 _public member_ `EMassMovementAction EndOfPathIntent = EMassMovementAction::Stand;` — `UPROPERTY(Transient)` — Movement intent at the end of the path.
- L65 _public member_ `EZoneLaneLinkType NextExitLinkType = EZoneLaneLinkType::None;` — `UPROPERTY(Transient)` — How the NextLaneHandle links to current lane.
- L69 _public member_ `uint8 bMoveReverse : 1;` — `UPROPERTY(Transient)` — If true, move backwards along the lane.
- L73 _public member_ `uint8 bIsEndOfPathPositionSet : 1;` — `UPROPERTY(Transient)` — Indicates if the optional end of path position is set.
- L77 _public member_ `uint8 bIsEndOfPathDirectionSet : 1;` — `UPROPERTY(Transient)` — Indicates if the optional end of path direction is set. Used only if EndOfPathPosition is set.

### `Plugins/AI/MassAI/Source/MassZoneGraphNavigation/Public/MassZoneGraphNavigationUtils.h` (Public)


#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace MassNavigation` (scope `UE`)
- L22 _prototype_ `bool ActivateActionMove(const UWorld& World, const UObject* Requester, const FMassEntityHandle Entity, const UZoneGraphSubsystem& ZoneGraphSubsystem, const FMassZoneGraphLaneLocationFragment& LaneLocation, const FZoneGraphShortPathRequest& PathRequest, const float AgentRadius, const float DesiredSpeed, FMassMoveTargetFragment& InOutMoveTarget, FMassZoneGraphShortPathFragment& OutShortPath, FMassZoneGraphCachedLaneFragment& OutCachedLane);` (scope `UE::MassNavigation`)
- L34 _prototype_ `bool ActivateActionStand(const UWorld& World, const UObject* Requester, const FMassEntityHandle Entity, const UZoneGraphSubsystem& ZoneGraphSubsystem, const FMassZoneGraphLaneLocationFragment& LaneLocation, const float DesiredSpeed, FMassMoveTargetFragment& MoveTarget, FMassZoneGraphShortPathFragment& ShortPath, FMassZoneGraphCachedLaneFragment& CachedLane);` (scope `UE::MassNavigation`)
- L44 _prototype_ `bool ActivateActionAnimate(const UWorld& World, const UObject* Requester, const FMassEntityHandle Entity, FMassMoveTargetFragment& MoveTarget);` (scope `UE::MassNavigation`)
