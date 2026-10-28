# Plugins / MassGameplayDebug

- module root: `Plugins/Runtime/MassGameplay/Source/MassGameplayDebug`
- headers: 9; symbols: 118
- symbol kinds: class=8, delegate=1, enum=2, enumerator=7, function=18, macro=6, member=31, namespace=6, prototype=31, struct=8
- PrivateDependencyModuleNames: UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, Engine, InputCore, MassActors, MassCommon, MassCore, MassEntity, MassEntityEditor, MassLOD, MassMovement, MassRepresentation, MassSimulation, MassSmartObjects, MassSpawner, NavigationSystem, StateTreeModule

### `Plugins/Runtime/MassGameplay/Source/MassGameplayDebug/Public/AssignDebugVisProcessor.h` (Public)


#### class `UAssignDebugVisProcessor`  
`class UAssignDebugVisProcessor : public UMassObserverProcessor`  
_L20-33_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassObserverProcessor`
- L24 _public prototype_ `UAssignDebugVisProcessor();`
- L27 _public prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L28 _public prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L31 _protected member_ `FMassEntityQuery EntityQuery;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MASSGAMEPLAYDEBUG_API`

### `Plugins/Runtime/MassGameplay/Source/MassGameplayDebug/Public/DebugVisLocationProcessor.h` (Public)


#### class `UDebugVisLocationProcessor`  
`class UDebugVisLocationProcessor : public UMassProcessor`  
_L16-31_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassProcessor`
- L21 _public prototype_ `UDebugVisLocationProcessor();`
- L25 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L26 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L28 _protected member_ `FMassEntityQuery EntityQuery;`
- L29 _protected member_ `FMassEntityQuery AllLocationEntitiesQuery;`

#### class `UMassProcessor_UpdateDebugVis`  
`class UMassProcessor_UpdateDebugVis : public UMassProcessor`  
_L37-50_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassProcessor`
- desc: Processor gathering debug data from entities to push debug shapes to the MassDebugger subsystem
- L41 _public prototype_ `UMassProcessor_UpdateDebugVis();`
- L44 _public prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L45 _public prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L48 _protected member_ `FMassEntityQuery EntityQuery;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MASSGAMEPLAYDEBUG_API`

### `Plugins/Runtime/MassGameplay/Source/MassGameplayDebug/Public/IMassGameplayDebugModule.h` (Public)


#### class `IMassGameplayDebugModule`  
`class IMassGameplayDebugModule : public IModuleInterface`  
_L14-39_
- inherits: `IModuleInterface`
- desc: The public interface to this module.  In most cases, this interface is only public to sibling modules within this plugin.
- L25 _public function_ `static inline IMassGameplayDebugModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L35 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Plugins/Runtime/MassGameplay/Source/MassGameplayDebug/Public/MassDebugDrawHelpers.h` (Public)


#### struct `UE::Mass::Debug::FLineBatcher`  
`struct FLineBatcher`  
_L12-52_
- L14 _public function_ `static FLineBatcher MakeLineBatcher(const UWorld* InWorld, bool bPersistentLines = false, float LifeTime = -1.f)`
- L24 _public function_ `FLineBatcher(TNotNull<ULineBatchComponent*> InLineBatcherInstance, float InLifeTime = -1.f) : LineBatcherInstance(InLineBatcherInstance), LifeTime(InLifeTime)`
- L29 _public function_ `inline void DrawSolidBox(const FVector& Center, const FVector& Extent, FColor const& Color) const`
- L35 _public function_ `inline void DrawWireBox(const FVector& Center, const FVector& Extent, FColor const& Color) const`
- L40 _public function_ `inline void DrawSphere(const FVector& Center, const float Radius, FLinearColor const& Color) const`
- L45 _public function_ `inline void DrawArrow(const FTransform& Transform, const float Length, FColor const& Color) const`
- L50 _public member_ `TNotNull<ULineBatchComponent* const> LineBatcherInstance;`
- L51 _public member_ `float LifeTime = -1.f;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Mass` (scope `UE`)
- L10 _namespace_ `namespace Debug` (scope `UE::Mass`)

### `Plugins/Runtime/MassGameplay/Source/MassGameplayDebug/Public/MassDebugVisualizationComponent.h` (Public)


#### class `UMassDebugVisualizationComponent`  
`class UMassDebugVisualizationComponent : public UActorComponent`  
_L17-43_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UActorComponent`
- desc: meant to be created procedurally and owned by an AMassDebugVisualizer instance. Will ensure if placed on a different type of actor
- L23 _public prototype_ `void ConditionallyConstructVisualComponent();` — will create Owner's "visual components" only it they're missing or out of sync with VisualDataTable
- L24 _public prototype_ `void DirtyVisuals();`
- L25 _public prototype_ `int32 AddDebugVisInstance(const uint16 VisualType, const FTransformFragment& Transform = FTransformFragment(FTransform::Identity));`
- L27 _public prototype_ `uint16 AddDebugVisType(const FAgentDebugVisualization& Data);` — returns index to the newly created VisualDataTable entry
- L28 _public function_ `TArrayView<UInstancedStaticMeshComponent* const> GetVisualDataISMCs()`
- L30 _public prototype_ `void Clear();`
- L32 _protected prototype_ `virtual void PostInitProperties() override;`
- L33 _protected prototype_ `void ConstructVisualComponent();`
- L38 _protected member_ `TArray<FAgentDebugVisualization> VisualDataTable;` — `UPROPERTY(Transient)`
- L41 _protected member_ `TArray<TObjectPtr<UInstancedStaticMeshComponent>> VisualDataISMCs;` — `UPROPERTY(Transient)`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MASSGAMEPLAYDEBUG_API`

### `Plugins/Runtime/MassGameplay/Source/MassGameplayDebug/Public/MassDebugVisualizationTrait.h` (Public)


#### class `UMassDebugVisualizationTrait`  
`class UMassDebugVisualizationTrait : public UMassEntityTraitBase`  
_L13-25_
- reflection: `UCLASS(MinimalAPI, meta = (DisplayName = "Debug Visualization"))`
- inherits: `UMassEntityTraitBase`
- L19 _protected prototype_ `virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;`
- L23 _protected member_ `FAgentDebugVisualization DebugShape;` — `UPROPERTY(EditAnywhere, Category = "Mass|Spawn")`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MASSGAMEPLAYDEBUG_API`

### `Plugins/Runtime/MassGameplay/Source/MassGameplayDebug/Public/MassDebugVisualizer.h` (Public)


#### class `AMassDebugVisualizer`  
`class AMassDebugVisualizer : public AActor`  
_L12-26_
- reflection: `UCLASS(MinimalAPI, NotPlaceable, Transient)`
- inherits: `AActor`
- L16 _public prototype_ `AMassDebugVisualizer();`
- L20 _public function_ `class UMassDebugVisualizationComponent& GetDebugVisComponent() const` — If this function is callable we guarantee the debug vis component to exist
- L24 _protected member_ `TObjectPtr<class UMassDebugVisualizationComponent> DebugVisComponent;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MASSGAMEPLAYDEBUG_API`

### `Plugins/Runtime/MassGameplay/Source/MassGameplayDebug/Public/MassDebuggerSubsystem.h` (Public)


#### class `UMassDebuggerSubsystem`  
`class UMassDebuggerSubsystem : public UMassSubsystemBase`  
_L18-115_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassSubsystemBase`
- L36 _public function_ `bool IsCollectingData() const` — Methods to optimize the collection of data to only when category is enabled
- L41 _public function_ `void SetCollectingData()`
- L46 _public function_ `void DataCollected()`
- L51 _public function_ `void AddShape(EMassEntityDebugShape Shape, const FVector& Location, const float Size)`
- L57 _public prototype_ `void ForEachShape(EMassEntityDebugShape Shape, const TFunctionRef<void(const FShapeDesc&)> Function) const;`
- L60 _public function_ `const TArray<FShapeDesc>* GetShapes() const` — `UE_DEPRECATED(5.8, "Use ForEachShape instead.")`
- L65 _public prototype_ `void ResetDebugShapes();`
- L67 _public prototype_ `void SetSelectedEntity(const FMassEntityHandle InSelectedEntity);`
- L68 _public function_ `FMassEntityHandle GetSelectedEntity() const`
- L74 _public prototype_ `void AppendSelectedEntityInfo(const FString& Info);`
- L75 _public function_ `const FString& GetSelectedEntityInfo() const`
- L82 _public prototype_ `UMassDebugVisualizationComponent* GetVisualizationComponent();` — Fetches the UMassDebugVisualizationComponent owned by lazily created DebugVisualizer
- L85 _public prototype_ `AMassDebugVisualizer& GetOrSpawnDebugVisualizer(UWorld& InWorld);`
- L90 _protected prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L91 _protected prototype_ `virtual void Deinitialize() override;`
- L94 _protected prototype_ `void OnEntitySelected(const FMassEntityManager& EntityManager, const FMassEntityHandle EntityHandle);`
- L96 _protected member_ `TArray<FShapeDesc> Shapes[static_cast<uint8>(EMassEntityDebugShape::MAX)];`
- L98 _protected member_ `FMassEntityHandle SelectedEntity;`
- L99 _protected member_ `FString SelectedEntityDetails;`
- L101 _protected member_ `uint64 UpdateFrameNumber = INDEX_NONE;`
- L103 _protected member_ `FDelegateHandle OnEntitySelectedHandle;`
- L105 _protected prototype_ `UE_MT_DECLARE_TS_RW_ACCESS_DETECTOR(MTDetector);`
- L107 _protected member_ `bool bCollectingData = false;`
- L111 _protected member_ `TObjectPtr<UMassDebugVisualizationComponent> VisualizationComponent;` — `UPROPERTY(Transient)`
- L114 _protected member_ `TObjectPtr<AMassDebugVisualizer> DebugVisualizer;` — `UPROPERTY(Transient)`

#### struct `UMassDebuggerSubsystem::FShapeDesc`  
`struct FShapeDesc`  
_L26-33_
- L28 _public member_ `FVector Location = {};` — no init on purpose, value will come from constructor
- L29 _public member_ `float Size = {};`
- L30 _public function_ `FShapeDesc(const FVector& InLocation, const float InSize) : Location(InLocation), Size(InSize)`

#### struct `TMassExternalSubsystemTraits`  
`template<> struct TMassExternalSubsystemTraits<UMassDebuggerSubsystem> final`  
_L118-125_

#### enum `TMassExternalSubsystemTraits::(anonymous)`  
``  
_L121-124_

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MASSGAMEPLAYDEBUG_API`
- L122 _enumerator_ `GameThreadOnly = false` (scope `TMassExternalSubsystemTraits::__anoncaed37330103`)
- L123 _enumerator_ `ThreadSafeWrite = false` (scope `TMassExternalSubsystemTraits::__anoncaed37330103`)

### `Plugins/Runtime/MassGameplay/Source/MassGameplayDebug/Public/MassGameplayDebugTypes.h` (Public)


#### struct `FSimDebugDataRow`  
`struct FSimDebugDataRow : public FTableRowBase`  
_L42-54_
- reflection: `USTRUCT()`
- inherits: `FTableRowBase`
- L47 _public member_ `TObjectPtr<UStaticMesh> Mesh = nullptr;` — `UPROPERTY(EditAnywhere, Category = Debug)`
- L50 _public member_ `TObjectPtr<UMaterialInterface> MaterialOverride = nullptr;` — `UPROPERTY(EditAnywhere, Category = Debug)`
- L53 _public member_ `float Scale = 1.f;` — `UPROPERTY(EditAnywhere, Category = Debug)`

#### struct `FSimDebugVisFragment`  
`struct FSimDebugVisFragment : public FMassFragment`  
_L57-62_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- L60 _public member_ `int32 InstanceIndex = INDEX_NONE;`
- L61 _public member_ `int16 VisualType = INDEX_NONE;`

#### enum `EMassEntityDebugShape`  
`enum class EMassEntityDebugShape : uint8`  
_L65-72_
- reflection: `UENUM()`
- L67 _public enumerator_ `Box`
- L68 _public enumerator_ `Cone`
- L69 _public enumerator_ `Cylinder`
- L70 _public enumerator_ `Capsule`
- L71 _public enumerator_ `MAX`

#### struct `FDataFragment_DebugVis`  
`struct FDataFragment_DebugVis : public FMassFragment`  
_L75-80_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- L79 _public member_ `EMassEntityDebugShape Shape = EMassEntityDebugShape::Box;` — `UPROPERTY(EditAnywhere, Category = Debug)`

#### struct `FMassDebuggableTag`  
`struct FMassDebuggableTag : public FMassTag`  
_L83-86_
- reflection: `USTRUCT()`
- inherits: `FMassTag`

#### struct `FAgentDebugVisualization`  
`struct FAgentDebugVisualization : public FTableRowBase`  
_L89-110_
- reflection: `USTRUCT()`
- inherits: `FTableRowBase`
- L94 _public member_ `TObjectPtr<UStaticMesh> Mesh = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Mass|Debug")`
- L97 _public member_ `TObjectPtr<UMaterialInterface> MaterialOverride = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Mass|Debug")`
- L101 _public member_ `uint32 VisualNearCullDistance = 5000;` — `UPROPERTY(EditAnywhere, Category = "Mass|Debug")` — Near cull distance to override default value for that agent type
- L105 _public member_ `uint32 VisualFarCullDistance = 7500;` — `UPROPERTY(EditAnywhere, Category = "Mass|Debug")` — Far cull distance to override default value for that agent type
- L109 _public member_ `EMassEntityDebugShape WireShape = EMassEntityDebugShape::Box;` — `UPROPERTY(EditAnywhere, Category = "Mass|Debug")` — If Mesh is not set this WireShape will be used for debug drawing via GameplayDebugger

#### Free symbols / members of external scopes

- L21 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMassDebug, Warning, All);`
- L21 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMassDebug, Warning, All);`
- L30 _namespace_ `namespace UE`
- L30 _namespace_ `namespace Mass` (scope `UE`)
- L30 _namespace_ `namespace Debug` (scope `UE::Mass`)
- L36 _prototype_ `extern void GetDebugEntitiesAndLocations(const FMassEntityManager& EntityManager, TArray<FMassEntityHandle>& OutEntities, TArray<FVector>& OutLocations);` (scope `UE::Mass::Debug`) — Fetches entity handles and their locations for entities indicated by index range as set by mass.debug.SetDebugEntityRange or mass.debug.DebugEntity console commands.
- L37 _prototype_ `extern FMassEntityHandle ConvertEntityIndexToHandle(const FMassEntityManager& EntityManager, const int32 EntityIndex);` (scope `UE::Mass::Debug`)
