# Plugins / MassAIDebug

- module root: `Plugins/AI/MassAI/Source/MassAIDebug`
- headers: 3; symbols: 92
- symbol kinds: class=3, delegate=1, enum=1, enumerator=4, function=14, macro=1, member=45, prototype=20, struct=1, typedef=2
- PrivateDependencyModuleNames: UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, Engine, InputCore, MassAIBehavior, MassAIReplication, MassActors, MassCommon, MassCore, MassEntity, MassEntityEditor, MassGameplayDebug, MassLOD, MassMovement, MassNavMeshNavigation, MassNavigation, MassRepresentation, MassSignals, MassSimulation, MassSmartObjects, MassSpawner, MassZoneGraphNavigation, NavigationSystem, SmartObjectsModule, StateTreeModule

### `Plugins/AI/MassAI/Source/MassAIDebug/Public/GameplayDebuggerCategory_Mass.h` (Public)


#### class `FGameplayDebuggerCategory_Mass`  
`class FGameplayDebuggerCategory_Mass : public FGameplayDebuggerCategory`  
_L23-174_
- inherits: `FGameplayDebuggerCategory`
- L25 _private typedef_ `using Super = FGameplayDebuggerCategory;`
- L27 _public prototype_ `FGameplayDebuggerCategory_Mass();`
- L28 _public prototype_ `virtual ~FGameplayDebuggerCategory_Mass();`
- L30 _public prototype_ `static TSharedRef<FGameplayDebuggerCategory> MakeInstance();`
- L33 _protected prototype_ `virtual void CollectData(APlayerController* OwnerPC, AActor* DebugActor) override;`
- L34 _protected prototype_ `virtual void DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext) override;`
- L36 _protected prototype_ `void SetCachedEntity(const FMassEntityHandle Entity, const FMassEntityManager& EntityManager);`
- L38 _protected function_ `void OnToggleArchetypes()`
- L43 _protected function_ `void OnToggleShapes()`
- L48 _protected function_ `void OnToggleAgentFragments()`
- L53 _protected function_ `void OnPickEntity()`
- L58 _protected function_ `void OnToggleEntityDetails()`
- L63 _protected function_ `void OnToggleNearEntityOverview()`
- L68 _protected function_ `void OnToggleNearEntityAvoidance()`
- L72 _protected function_ `void OnToggleNearEntityPath()`
- L77 _protected function_ `void OnToggleEntityLookAt()`
- L82 _protected function_ `void OnCycleEntityDescription()`
- L88 _protected prototype_ `void OnToggleDebugLocalEntityManager();`
- L89 _protected prototype_ `void OnIncreaseSearchRange();`
- L90 _protected prototype_ `void OnDecreaseSearchRange();`
- L91 _protected prototype_ `void OnTogglePickedActorAsViewer();`
- L92 _protected function_ `void OnToggleDrawViewers()`
- L97 _protected prototype_ `void OnClearActorViewers();`
- L99 _protected prototype_ `void PickEntity(const FVector& ViewLocation, const FVector& ViewDirection, const UWorld& World, FMassEntityManager& EntityManager, const bool bLimitAngle = true);`
- L102 _protected prototype_ `void PickEntity(const APlayerController& OwnerPC, const UWorld& World, FMassEntityManager& EntityManager, const bool bLimitAngle = true);` — `UE_DEPRECATED(5.3, "This flavor of PickEntity has been deprecated. Use the one getting ViewLocation and ViewDirection parameters instead.")`
- L104 _protected prototype_ `void OnEntitySelected(const FMassEntityManager& EntityManager, const FMassEntityHandle EntityHandle);`
- L105 _protected prototype_ `void ClearCachedEntity();`
- L116 _protected member_ `TWeakObjectPtr<AActor> CachedDebugActor;`
- L117 _protected member_ `FMassEntityHandle CachedEntity;`
- L118 _protected member_ `EEntityDescriptionVerbosity EntityDescriptionVerbosity = EEntityDescriptionVerbosity::Minimal;`
- L120 _protected member_ `bool bShowArchetypes;`
- L121 _protected member_ `bool bShowShapes;`
- L122 _protected member_ `bool bShowAgentFragments;`
- L123 _protected member_ `bool bPickEntity;`
- L124 _protected member_ `bool bShowEntityDetails;`
- L125 _protected member_ `bool bShowNearEntityOverview;`
- L126 _protected member_ `bool bShowNearEntityAvoidance;`
- L127 _protected member_ `bool bShowNearEntityPath;`
- L128 _protected member_ `bool bShowEntityLookAt;`
- L129 _protected member_ `bool bMarkEntityBeingDebugged;`
- L130 _protected member_ `bool bDebugLocalEntityManager;`
- L131 _protected member_ `bool bShowViewers;`
- L132 _protected member_ `int32 ToggleDebugLocalEntityManagerInputIndex = INDEX_NONE;`
- L133 _protected member_ `int32 TogglePickedActorAsViewerInputIndex = INDEX_NONE;`
- L134 _protected member_ `int32 ToggleDrawViewersInputIndex = INDEX_NONE;`
- L135 _protected member_ `int32 ClearViewersInputIndex = INDEX_NONE;`
- L136 _protected member_ `float SearchRange = 25000.f;`
- L147 _protected member_ `TArray<FEntityDescription> NearEntityDescriptions;`
- L149 _protected member_ `static TArray<FAutoConsoleCommandWithWorld> ConsoleCommands;`
- L150 _protected prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnConsoleCommandBroadcastDelegate, UWorld*);`
- L151 _protected member_ `static FOnConsoleCommandBroadcastDelegate OnToggleArchetypesBroadcast;`
- L152 _protected member_ `static FOnConsoleCommandBroadcastDelegate OnToggleShapesBroadcast;`
- L153 _protected member_ `static FOnConsoleCommandBroadcastDelegate OnToggleAgentFragmentsBroadcast;`
- L154 _protected member_ `static FOnConsoleCommandBroadcastDelegate OnPickEntityBroadcast;`
- L155 _protected member_ `static FOnConsoleCommandBroadcastDelegate OnToggleEntityDetailsBroadcast;`
- L156 _protected member_ `static FOnConsoleCommandBroadcastDelegate OnToggleNearEntityOverviewBroadcast;`
- L157 _protected member_ `static FOnConsoleCommandBroadcastDelegate OnToggleNearEntityAvoidanceBroadcast;`
- L158 _protected member_ `static FOnConsoleCommandBroadcastDelegate OnToggleNearEntityPathBroadcast;`
- L159 _protected member_ `static FOnConsoleCommandBroadcastDelegate OnToggleEntityLookAtBroadcast;`
- L160 _protected member_ `static FOnConsoleCommandBroadcastDelegate OnCycleEntityDescriptionBroadcast;`
- L161 _protected member_ `static FOnConsoleCommandBroadcastDelegate OnToggleDebugLocalEntityManagerBroadcast;`
- L162 _protected member_ `static FOnConsoleCommandBroadcastDelegate OnTogglePickedActorAsViewerBroadcast;`
- L163 _protected member_ `static FOnConsoleCommandBroadcastDelegate OnToggleDrawViewersBroadcast;`
- L164 _protected member_ `static FOnConsoleCommandBroadcastDelegate OnClearActorViewersBroadcast;`
- L166 _protected typedef_ `using FDelegateHandlePair = TPair<FOnConsoleCommandBroadcastDelegate*, FDelegateHandle>;`
- L167 _protected member_ `TArray<FDelegateHandlePair> ConsoleCommandHandles;`
- L169 _protected member_ `FDelegateHandle OnEntitySelectedHandle;`
- L171 _protected member_ `static constexpr float MaxSearchRange = 1000000.f;`
- L172 _protected member_ `static constexpr float MinSearchRange = 1.f;`
- L173 _protected member_ `static constexpr float SearchRangeChangeScale = 2.f;`

#### enum `FGameplayDebuggerCategory_Mass::EEntityDescriptionVerbosity`  
`enum class EEntityDescriptionVerbosity : uint8`  
_L108-114_
- L110 _public enumerator_ `Hidden`
- L111 _public enumerator_ `Minimal`
- L112 _public enumerator_ `Full`
- L113 _public enumerator_ `Max`

#### struct `FGameplayDebuggerCategory_Mass::FEntityDescription`  
`struct FEntityDescription`  
_L138-146_
- L140 _public prototype_ `FEntityDescription() = default;`
- L141 _public function_ `FEntityDescription(const float InScore, const FVector& InLocation, const FString& InDescription) : Score(InScore), Location(InLocation), Description(InDescription)`
- L143 _public member_ `float Score = 0.0f;`
- L144 _public member_ `FVector Location = FVector::ZeroVector;`
- L145 _public member_ `FString Description;`

#### Free symbols / members of external scopes

- L150 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnConsoleCommandBroadcastDelegate, UWorld*);`

### `Plugins/AI/MassAI/Source/MassAIDebug/Public/IMassAIDebugModule.h` (Public)


#### class `IMassAIDebugModule`  
`class IMassAIDebugModule : public IModuleInterface`  
_L14-39_
- inherits: `IModuleInterface`
- desc: The public interface to this module.  In most cases, this interface is only public to sibling modules within this plugin.
- L25 _public function_ `static inline IMassAIDebugModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L35 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Plugins/AI/MassAI/Source/MassAIDebug/Public/MassDebugStateTreeProcessor.h` (Public)


#### class `UMassDebugStateTreeProcessor`  
`class UMassDebugStateTreeProcessor : public UMassProcessor`  
_L16-27_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassProcessor`
- L21 _protected prototype_ `UMassDebugStateTreeProcessor();`
- L23 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L24 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L26 _protected member_ `FMassEntityQuery EntityQuery;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MASSAIDEBUG_API`
