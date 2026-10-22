# Plugins / MassNavMeshNavigation

- module root: `Plugins/AI/MassAI/Source/MassNavMeshNavigation`
- headers: 7; symbols: 63
- symbol kinds: class=4, enum=2, enumerator=4, function=4, macro=4, member=24, namespace=2, prototype=14, struct=5
- PublicDependencyModuleNames: AIModule, Core, CoreUObject, Engine, MassCommon, MassCore, MassEntity, MassLOD, MassMovement, MassNavigation, MassSignals, MassSpawner, NavCorridor

### `Plugins/AI/MassAI/Source/MassNavMeshNavigation/Public/IMassNavMeshNavigationModule.h` (Public)


#### class `IMassNavMeshNavigationModule`  
`class IMassNavMeshNavigationModule : public IModuleInterface`  
_L13-38_
- inherits: `IModuleInterface`
- desc: The public interface to this module.  In most cases, this interface is only public to sibling modules within this plugin.
- L24 _public function_ `static inline IMassNavMeshNavigationModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L34 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Plugins/AI/MassAI/Source/MassNavMeshNavigation/Public/MassNavMeshNavigationBoundaryProcessor.h` (Public)


#### class `UMassNavMeshNavigationBoundaryProcessor`  
`class UMassNavMeshNavigationBoundaryProcessor : public UMassProcessor`  
_L13-26_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassProcessor`
- desc: Fills FMassNavigationEdgesFragment using FMassNavMeshShortPathFragment.
- L18 _public prototype_ `UMassNavMeshNavigationBoundaryProcessor();`
- L21 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L22 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L25 _private member_ `FMassEntityQuery EntityQuery;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MASSNAVMESHNAVIGATION_API`

### `Plugins/AI/MassAI/Source/MassNavMeshNavigation/Public/MassNavMeshNavigationFragments.h` (Public)


#### struct `FMassNavMeshPathPoint`  
`struct FMassNavMeshPathPoint`  
_L18-36_
- reflection: `USTRUCT()`
- desc: Navmesh path point data
- L23 _public member_ `FVector Left = FVector::ZeroVector;` — Portal left limit.
- L26 _public member_ `FVector Right = FVector::ZeroVector;` — Portal right limit.
- L29 _public member_ `FVector Position = FVector::ZeroVector;` — Position of the path.
- L32 _public member_ `FMassSnorm8Vector2D Tangent;` — Tangent direction of the path.
- L35 _public member_ `FMassInt16Real Distance = FMassInt16Real(0.f);` — Distance along the path from first point.

#### struct `FMassNavMeshShortPathFragment`  
`struct FMassNavMeshShortPathFragment : public FMassFragment`  
_L40-95_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- desc: Short path used for navmesh navigation
- L44 _public prototype_ `FMassNavMeshShortPathFragment() = default;`
- L47 _public member_ `static constexpr uint8 MaxPoints = 8;` — Maximum number of points on the short path
- L50 _public member_ `static constexpr uint8 NumPointsBeyondUpdate = 3;` — Number of points beyond the update point
- L52 _public function_ `void Reset()`
- L64 _public function_ `bool IsDone() const` — Returns true if we are done progressing on the short path.
- L70 _public prototype_ `bool RequestShortPath(const TSharedPtr<FNavCorridor>& InCorridor, const int32 InNavCorridorStartIndex, const uint8 InNumLeadingPoints, const float InEndReachedDistance);` — Fill Points from Corridor.
- L73 _public member_ `TStaticArray<FMassNavMeshPathPoint, MaxPoints> Points;` — Portal points
- L76 _public member_ `float MoveTargetProgressDistance = 0.f;` — Current progress distance along the short path.
- L79 _public member_ `float EndReachedDistance = 20.f;` — Distance from the end of path used to confirm that the destination is reached.
- L82 _public member_ `uint8 NumPoints = 0;` — Number of points on path.
- L85 _public member_ `EMassMovementAction EndOfPathIntent = EMassMovementAction::Stand;` — Intent at the end of the path.
- L88 _public member_ `uint8 bPartialResult : 1 = false;` — True if the path was partial.
- L91 _public member_ `uint8 bDone : 1 = false;` — True when path follow is completed.
- L94 _public member_ `uint8 bInitialized : 1 = false;` — True when the path has been initalized.

#### enum `EMassNavigationPathSource`  
`enum class EMassNavigationPathSource : uint8`  
_L97-102_
- L99 _public enumerator_ `NavMesh`
- L100 _public enumerator_ `Spline`
- L101 _public enumerator_ `Unset`

#### struct `FMassNavMeshCachedPathFragment`  
`struct FMassNavMeshCachedPathFragment : public FMassFragment`  
_L106-124_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- desc: Current navmesh path
- L111 _public member_ `FNavPathSharedPtr NavPath;` — Reference to a FNavigationPath.
- L114 _public member_ `TSharedPtr<FNavCorridor> Corridor;` — Reference to an FNavCorridor. Built out of a navigation path.
- L117 _public member_ `uint16 NavPathNextStartIndex = 0;` — Index used to keep track of progression on the navmesh path.
- L120 _public member_ `EMassNavigationPathSource PathSource = EMassNavigationPathSource::Unset;` — Source of the path, navmesh or else.
- L123 _public member_ `static constexpr uint8 NumLeadingPoints = 1;` — Number of points before the starting point.

#### struct `TMassFragmentTraits`  
`template<> struct TMassFragmentTraits<FMassNavMeshCachedPathFragment> final`  
_L127-133_

#### enum `TMassFragmentTraits::(anonymous)`  
``  
_L130-132_

#### struct `FMassNavMeshBoundaryFragment`  
`struct FMassNavMeshBoundaryFragment : public FMassFragment`  
_L136-142_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- L141 _public member_ `FVector LastUpdatePosition = FVector::ZeroVector;` — MovementTarget position when UMassNavMeshNavigationBoundaryProcessor was last updated. Used to identify when a new update is needed.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MASSNAVMESHNAVIGATION_API`
- L131 _enumerator_ `AuthorAcceptsItsNotTriviallyCopyable = true` (scope `TMassFragmentTraits::__anona5e92c330103`)

### `Plugins/AI/MassAI/Source/MassNavMeshNavigation/Public/MassNavMeshNavigationProcessors.h` (Public)


#### class `UMassNavMeshPathFollowProcessor`  
`class UMassNavMeshPathFollowProcessor : public UMassProcessor`  
_L16-36_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassProcessor`
- desc: Processor for updating move target on a navmesh short path.
- L21 _protected prototype_ `UMassNavMeshPathFollowProcessor();`
- L23 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L24 _protected prototype_ `virtual void InitializeInternal(UObject& Owner, const TSharedRef<FMassEntityManager>& ) override;`
- L25 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L29 _private prototype_ `void CheckEndOfPathReached(FMassNavMeshShortPathFragment& ShortPath, const FVector& EntityLocation, const uint8 EndPointIndex, const FMassEntityHandle& Entity, bool bDisplayDebug);` — Check if entity reached end of path and mark as done if threshold is met.
- L32 _private member_ `FMassEntityQuery EntityQuery_Conditional;`
- L35 _private member_ `TObjectPtr<UMassSignalSubsystem> SignalSubsystem = nullptr;` — `UPROPERTY(Transient)`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MASSNAVMESHNAVIGATION_API`

### `Plugins/AI/MassAI/Source/MassNavMeshNavigation/Public/MassNavMeshNavigationTrait.h` (Public)


#### class `UMassNavMeshNavigationTrait`  
`class UMassNavMeshNavigationTrait : public UMassEntityTraitBase`  
_L11-17_
- reflection: `UCLASS(MinimalAPI, meta = (DisplayName = "NavMesh Navigation"))`
- inherits: `UMassEntityTraitBase`
- L16 _protected prototype_ `virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MASSNAVMESHNAVIGATION_API`

### `Plugins/AI/MassAI/Source/MassNavMeshNavigation/Public/MassNavMeshNavigationTypes.h` (Public)


#### Free symbols / members of external scopes

- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMassNavMeshNavigation, Warning, All);`

### `Plugins/AI/MassAI/Source/MassNavMeshNavigation/Public/MassNavMeshNavigationUtils.h` (Public)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MassNavigation` (scope `UE`)
- L14 _prototype_ `bool ActivateActionStand( const UObject* Requester, const FMassEntityHandle Entity, const float DesiredSpeed, FMassMoveTargetFragment& InOutMoveTarget, FMassNavMeshShortPathFragment& OutShortPath);` (scope `UE::MassNavigation`)
- L17 _prototype_ `bool ActivateActionAnimate( const UObject* Requester, const FMassEntityHandle Entity, FMassMoveTargetFragment& MoveTarget);` (scope `UE::MassNavigation`)
