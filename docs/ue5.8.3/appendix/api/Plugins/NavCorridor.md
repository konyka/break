# Plugins / NavCorridor

- module root: `Plugins/Runtime/NavCorridor/Source/NavCorridor`
- headers: 3; symbols: 78
- symbol kinds: class=3, function=4, macro=2, member=40, prototype=25, struct=4
- PublicDependencyModuleNames: AIModule, Core, CoreUObject, Engine, NavigationSystem

### `Plugins/Runtime/NavCorridor/Source/NavCorridor/Public/NavCorridor.h` (Public)


#### struct `FNavCorridorParams`  
`struct FNavCorridorParams`  
_L15-69_
- reflection: `USTRUCT(BlueprintType)`
- L20 _public function_ `void SetFromWidth(const float InWidth)` — Sets good default values for the params based on corridor width.
- L29 _public member_ `TArray<int32, TInlineAllocator<8>> PinnedPointsIndices;` — Points along the path which we want to visit instead of string pulling the location on the shortest path.
- L33 _public member_ `float Width = 200.0f;` — `UPROPERTY(EditAnywhere, Category = "Pathfinding", meta=(ClampMin="10.0"))` — Width of the corridor to build
- L37 _public member_ `float PathOffsetFromBoundaries = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Pathfinding", meta = (ClampMin = "0.0"))` — Distance to maintain between the path and the corridor boundaries. If the corridor is too tight, the offset will be reduced to the available space.
- L41 _public member_ `float ObstacleTaperAngle = 30.0f;` — `UPROPERTY(EditAnywhere, Category = "Pathfinding", meta=(ClampMin="10.0", ClampMax="45.0"))` — How much the outer edges of obstacles are tapered out. This prevents small sectors and local traps.
- L45 _public member_ `float SmallSectorThreshold = 60.0f;` — `UPROPERTY(EditAnywhere, Category = "Pathfinding", meta=(ClampMin="0.0"))` — Attempt to remove sectors narrower than this from the corridor.
- L49 _public member_ `float LargeSectorThreshold = 200.0f;` — `UPROPERTY(EditAnywhere, Category = "Pathfinding", meta=(ClampMin="0.0"))` — Simplification is skipped if two neighbour sectors combined are longer than this. This ensures that long sectors do not lose volume due to simplification.
- L53 _public member_ `float SimplifyEdgeThreshold = 20.0f;` — `UPROPERTY(EditAnywhere, Category = "Pathfinding", meta=(ClampMin="0.0"))` — Corridor edge max simplification distance.
- L57 _public member_ `bool bSimplifyFlipPortals = true;` — `UPROPERTY(EditAnywhere, Category = "Pathfinding")` — If true do flip portals simplification.
- L61 _public member_ `bool bSimplifyConvexPortals = true;` — `UPROPERTY(EditAnywhere, Category = "Pathfinding")` — If true do convex portals simplification.
- L65 _public member_ `bool bSimplifyConcavePortals = true;` — `UPROPERTY(EditAnywhere, Category = "Pathfinding")` — If true do concave portals simplification.
- L68 _public prototype_ `FString ToString() const;` — Returns a string of the corridor parameters.

#### struct `FNavCorridorPortal`  
`struct FNavCorridorPortal`  
_L74-93_
- desc: Portal of a section of the corridor.
- L77 _public member_ `FVector Left = FVector::ZeroVector;` — Left side of the portal
- L80 _public member_ `FVector Right = FVector::ZeroVector;` — Righ side of the portal
- L83 _public member_ `FVector Location = FVector::ZeroVector;` — Path location at the portal
- L86 _public member_ `int16 PathPointIndex = 0;` — Path point index of the original path
- L89 _public member_ `bool bIsPathCorner : 1 = false;` — True if the portal is at original path point corner.
- L92 _public member_ `bool bIsPinnedLocation : 1 = false;` — When true, the string pulling will be forced to visit the original location at this portal, unless that location is outside the corridor (eg: too close to an obstacle).

#### struct `FNavCorridorLocation`  
`struct FNavCorridorLocation`  
_L98-115_
- desc: Location along the path through the corridor.
- L100 _public function_ `bool IsValid() const`
- L102 _public function_ `void Reset()`
- L108 _public member_ `FVector Location;` — Location on the path
- L111 _public member_ `int32 PortalIndex = INDEX_NONE;` — Index of the start portal in the section where the location lies.
- L114 _public member_ `float T = 0.0f;` — Interpolation value representing the point between PortalIndex and PortalIndex+1

#### struct `FNavCorridor`  
`struct FNavCorridor : public TSharedFromThis<FNavCorridor>`  
_L121-163_
- inherits: `TSharedFromThis<FNavCorridor>`
- desc: Navigation corridor defines free space around path. It is expanded from a string pulled path. The corridor is represented as an array of portals, which leaves convex sectors in between them.
- L124 _public function_ `bool IsValid() const` — @return true if the corridor is valid (has portals).
- L127 _public prototype_ `void Reset();` — Resets and empties the corridor.
- L130 _public prototype_ `void BuildFromPath(const FNavigationPath& Path, FSharedConstNavQueryFilter NavQueryFilter, const FNavCorridorParams& Params);` — Builds the corridor from a given Path.
- L133 _public prototype_ `void BuildFromPathPoints(const FNavigationPath& Path, TConstArrayView<FNavPathPoint> PathPoints, const int32 PathPointBaseIndex, FSharedConstNavQueryFilter NavQueryFilter, const FNavCorridorParams& Params);` — Builds the corridor from a given array of Path points
- L136 _public prototype_ `void OffsetPathLocationsFromWalls(const float Offset, bool bOffsetFirst = false, bool bOffsetLast = false);` — Offsets the path locations away from walls.
- L139 _public prototype_ `FNavCorridorLocation FindNearestLocationOnPath(const FVector Location) const;` — Finds nearest location on path going through the corridor.
- L142 _public prototype_ `FNavCorridorLocation AdvancePathLocation(const FNavCorridorLocation& PathLocation, const FVector::FReal AdvanceDistance) const;` — Advances path location along the path that goes through the corridor.
- L145 _public prototype_ `FVector::FReal GetDistanceToEndOfPath(const FNavCorridorLocation& PathLocation) const;` — @return distance to the end of the path starting from the given the path location.
- L148 _public prototype_ `FVector GetPathDirection(const FNavCorridorLocation& PathLocation) const;` — @return direction of the path at given path location.
- L151 _public prototype_ `FVector ConstrainVisibility(const FNavCorridorLocation& PathLocation, const FVector Source, const FVector Target, const float ForceLookAheadDistance = 0.0f) const;` — @return target vector that is visible from Source.
- L154 _public prototype_ `bool HitTest(const FVector SegmentStart, const FVector SegmentEnd, double& HitT);` — @return true if the segment hits the corridor boundary.
- L157 _public member_ `TArray<FNavCorridorPortal> Portals;` — Portal points defining the corridor.
- L162 _public member_ `const static FVector OverlappingPointTolerance;` — Tolerance used to remove overlappint points in path before building the corridor (arbitrary value used to fix common cases). @todo: Make corridor support overlapping points and remove this.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API NAVCORRIDOR_API`

### `Plugins/Runtime/NavCorridor/Source/NavCorridor/Public/NavCorridorModule.h` (Public)


#### class `FNavCorridorModule`  
`class FNavCorridorModule : public IModuleInterface`  
_L7-13_
- inherits: `IModuleInterface`
- L11 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L12 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Runtime/NavCorridor/Source/NavCorridor/Public/NavCorridorTestingComponent.h` (Public)


#### class `UNavCorridorTestingComponent`  
`class UNavCorridorTestingComponent : public UDebugDrawComponent`  
_L20-93_
- reflection: `UCLASS(MinimalAPI, ClassGroup = Custom, hidecategories = (Physics, Collision, Rendering, Cooking, Lighting, Navigation, Tags, HLOD, Mobile, AssetUserData, Activation))`
- inherits: `UDebugDrawComponent`
- desc: Component for testing AI Locomotion functionality.
- L24 _public prototype_ `UNavCorridorTestingComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L27 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L28 _public prototype_ `virtual void PostLoad();`
- L31 _public prototype_ `virtual void OnRegister() override;`
- L32 _public prototype_ `virtual void OnUnregister() override;`
- L33 _public prototype_ `virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;`
- L35 _public prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;`
- L38 _public prototype_ `FDebugRenderSceneProxy* CreateDebugSceneProxy() override;`
- L41 _public prototype_ `void UpdateTests();`
- L44 _protected prototype_ `void UpdateNavData();`
- L47 _protected member_ `FNavAgentProperties NavAgentProps;` — `UPROPERTY(EditAnywhere, Category = "Test")`
- L50 _protected member_ `TSubclassOf<class UNavigationQueryFilter> FilterClass;` — `UPROPERTY(EditAnywhere, Category = "Test")`
- L54 _protected member_ `bool bFindCorridorToGoal = true;` — `UPROPERTY(EditAnywhere, Category = "Test")` — If true, finds path to Goal actor.
- L58 _protected member_ `bool bFollowPathOnGoalCorridor = false;` — `UPROPERTY(EditAnywhere, Category = "Test")` — If true, finds nearest path location on Goal actor corridor.
- L61 _protected member_ `float FollowLookAheadDistance = 200.0f;` — `UPROPERTY(EditAnywhere, Category = "Test")`
- L64 _protected member_ `TObjectPtr<AActor> GoalActor = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Test")`
- L67 _protected member_ `TObjectPtr<ANavigationData> NavData;` — `UPROPERTY(Transient)`
- L70 _protected member_ `FNavCorridorParams CorridorParams;` — `UPROPERTY(EditAnywhere, Category = "Test")`
- L73 _protected member_ `bool bUpdateParametersFromWidth = false;` — `UPROPERTY(EditAnywhere, Category = "Test")`
- L76 _protected member_ `float PathOffset = 40.0f;` — `UPROPERTY(EditAnywhere, Category = "Test")`
- L79 _protected member_ `float PathfindingTimeUs = 0.0f;` — `UPROPERTY(transient, VisibleAnywhere, BlueprintReadOnly, Category = "Profile")`
- L82 _protected member_ `float CorridorTimeUs = 0.0f;` — `UPROPERTY(transient, VisibleAnywhere, BlueprintReadOnly, Category = "Profile")`
- L84 _protected member_ `FNavPathSharedPtr Path;`
- L85 _protected member_ `FNavCorridor Corridor;`
- L88 _protected member_ `FVector LastTargetLocation;` — Location used to track of the target actor moves.
- L90 _protected member_ `FNavCorridorLocation NearestPathLocation;`
- L91 _protected member_ `FNavCorridorLocation LookAheadPathLocation;`
- L92 _protected member_ `FVector ClampedLookAheadLocation;`

#### class `ANavCorridorTestingActor`  
`class ANavCorridorTestingActor : public AActor`  
_L97-110_
- reflection: `UCLASS(MinimalAPI, hidecategories = (Actor, Input, Collision, Rendering, Replication, Partition, HLOD, Cooking))`
- inherits: `AActor`
- desc: Debug actor to visually test zone graph.
- L101 _public prototype_ `ANavCorridorTestingActor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L104 _public prototype_ `virtual void PostEditMove(bool bFinished) override;`
- L109 _protected member_ `TObjectPtr<UNavCorridorTestingComponent> DebugComp;` — `UPROPERTY(Category = Default, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API NAVCORRIDOR_API`
