# Plugins / ZoneGraphAnnotations

- module root: `Plugins/Runtime/ZoneGraphAnnotations/Source/ZoneGraphAnnotations`
- headers: 7; symbols: 197
- symbol kinds: class=11, enum=2, enumerator=4, function=32, macro=6, member=73, prototype=59, struct=10
- PrivateDependencyModuleNames: EditorFramework, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, Engine, MassCore, MassEntity, RHI, ZoneGraph, ZoneGraphDebug

### `Plugins/Runtime/ZoneGraphAnnotations/Source/ZoneGraphAnnotations/Public/Annotations/ZoneGraphDisturbanceAnnotation.h` (Public)


#### struct `FZoneGraphDisturbanceArea`  
`struct FZoneGraphDisturbanceArea : public FZoneGraphAnnotationEventBase`  
_L18-37_
- reflection: `USTRUCT()`
- inherits: `FZoneGraphAnnotationEventBase`
- desc: Event for indicating an area of disturbance.
- L24 _public member_ `FVector Position = FVector::ZeroVector;` — `UPROPERTY()` — Center of the area.
- L28 _public member_ `float Radius = 0.0f;` — `UPROPERTY()` — Radius of the effect.
- L32 _public member_ `float Duration = 0.0f;` — `UPROPERTY()` — Duration of the danger.
- L36 _public member_ `uint32 InstigatorID = 0;` — `UPROPERTY()` — ID of the instigator of this event, events from the same instigator are combined.

#### enum `EZoneGraphObstacleDisturbanceAreaAction`  
`enum class EZoneGraphObstacleDisturbanceAreaAction : uint8`  
_L41-45_
- reflection: `UENUM()`
- desc: Actions for disturbances.
- L43 _public enumerator_ `Add` — Add
- L44 _public enumerator_ `Remove` — Remove

#### struct `FZoneGraphObstacleDisturbanceArea`  
`struct FZoneGraphObstacleDisturbanceArea : public FZoneGraphAnnotationEventBase`  
_L49-73_
- reflection: `USTRUCT()`
- inherits: `FZoneGraphAnnotationEventBase`
- desc: Event for indicating an obstacle.
- L53 _public function_ `bool operator==(const FZoneGraphObstacleDisturbanceArea& Other) const`
- L57 _public member_ `FVector Position = FVector::ZeroVector;` — `UPROPERTY()` — Center of the obstacle.
- L61 _public member_ `float Radius = 0.f;` — `UPROPERTY()` — Radius of the effect of the disturbance.
- L65 _public member_ `float ObstacleRadius = 0.f;` — `UPROPERTY()` — Radius of the obstacle.
- L68 _public member_ `FMassLaneObstacleID ObstacleID;` — ID.
- L72 _public member_ `EZoneGraphObstacleDisturbanceAreaAction Action = EZoneGraphObstacleDisturbanceAreaAction::Add;` — `UPROPERTY()` — Disturbance event action (ex: add/remove).

#### struct `FZoneGraphEscapeLaneSpan`  
`struct FZoneGraphEscapeLaneSpan`  
_L76-96_
- desc: Instructions how to escape from one half of a lane.
- L79 _public member_ `FVector Position = FVector::ZeroVector;` — Representative position of the action, used during graph calculation and debug drawing.
- L81 _public member_ `FVector Direction = FVector::ZeroVector;` — Lane direction, used for debug drawing.
- L83 _public member_ `float SplitDistance = 0.0f;` — Distance along the lane where lane is split in 2 spans.
- L85 _public member_ `float Danger = 0.0f;` — Max danger value from all danger locations.
- L87 _public member_ `float EscapeCost = 0.0f;` — Disturbance cost value, lower the value leads to safety.
- L89 _public member_ `int32 ExitLaneIndex = INDEX_NONE;` — Index to exit lane within current ZoneGraph data
- L91 _public member_ `bool bReverseLaneDirection = false;` — True if the Disturbance action should move backwards along the lane.
- L93 _public member_ `bool bLeadsToExit = false;` — True if the action leads to exit
- L95 _public member_ `EZoneLaneLinkType ExitLinkType = EZoneLaneLinkType::None;` — Describes what type of linked lane to follow.

#### struct `FZoneGraphEscapeLaneAction`  
`struct FZoneGraphEscapeLaneAction`  
_L99-129_
- desc: Data describing how to Disturbance a lane, the lane is split in half and each half has its' own Disturbance action and direction.
- L101 _public prototype_ `FZoneGraphEscapeLaneAction() = default;`
- L102 _public function_ `FZoneGraphEscapeLaneAction(const int32 InLaneIndex) : LaneIndex(InLaneIndex)`
- L104 _public member_ `static constexpr uint8 MaxSpans = 8;`
- L107 _public function_ `uint8 FindSpanIndex(const float Distance) const` — Finds a span based on the split distances.
- L120 _public member_ `int32 LaneIndex = 0;` — Lane Index the data belongs to.
- L122 _public member_ `float LaneLength = 0.0f;` — Cached lane length from ZoneGraph.
- L124 _public member_ `FZoneGraphTagMask Tags;` — Disturbance annotation tags
- L126 _public member_ `FZoneGraphEscapeLaneSpan Spans[MaxSpans];` — Disturbance actions for Start (0), and End (1) spans of the lane.
- L128 _public member_ `uint8 SpanCount = 0;` — Number of spans on this lane

#### struct `FZoneGraphDataEscapeGraph`  
`struct FZoneGraphDataEscapeGraph`  
_L132-147_
- desc: PerZoneGraphData escape graph.
- L135 _public member_ `FZoneGraphDataHandle DataHandle;` — Handle of the data this Disturbance data relates to
- L137 _public member_ `bool bInUse = false;` — True, if this entry is in use.
- L140 _public member_ `TArray<FZoneGraphEscapeLaneAction> LanesToEscape;` — Array of lanes to avoid.
- L142 _public member_ `TArray<int32> PreviousLanes;` — Array of previous lanes that were marked.
- L144 _public member_ `TMap<int32, int32> LanesToEscapeLookup;` — Lookup from ZoneGraph Lane index to index in LanesToEscape
- L146 _public member_ `float MaxEscapeCost = 0.0f;` — Max escape cost, used for visualization

#### class `UZoneGraphDisturbanceAnnotation`  
`class UZoneGraphDisturbanceAnnotation : public UZoneGraphAnnotationComponent`  
_L154-231_
- reflection: `UCLASS(MinimalAPI, ClassGroup = AI, BlueprintType, meta = (BlueprintSpawnableComponent))`
- inherits: `UZoneGraphAnnotationComponent`
- desc: ZoneGraph Disturbance Annotation
- L159 _public prototype_ `UZoneGraphDisturbanceAnnotation(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L162 _public function_ `const FZoneGraphEscapeLaneAction* GetEscapeAction(const FZoneGraphLaneHandle LaneHandle) const` — @return Disturbance action for a specific lane, or null of the lane does not have Disturbance action.
- L171 _protected prototype_ `virtual void PostSubsystemsInitialized() override;`
- L173 _protected prototype_ `virtual FZoneGraphTagMask GetAnnotationTags() const override;`
- L175 _protected prototype_ `virtual void TickAnnotation(const float DeltaTime, FZoneGraphAnnotationTagContainer& AnnotationTagContainer) override;`
- L176 _protected prototype_ `virtual void HandleEvents(const FInstancedStructContainer& Events) override;`
- L178 _protected prototype_ `virtual void PostZoneGraphDataAdded(const AZoneGraphData& ZoneGraphData) override;`
- L179 _protected prototype_ `virtual void PreZoneGraphDataRemoved(const AZoneGraphData& ZoneGraphData) override;`
- L181 _protected prototype_ `void UpdateDangerLanes();`
- L182 _protected prototype_ `void UpdateAnnotationTags(FZoneGraphAnnotationTagContainer& AnnotationTagContainer);`
- L185 _protected prototype_ `virtual void DebugDraw(FZoneGraphAnnotationSceneProxy* DebugProxy) override;`
- L186 _protected prototype_ `virtual void DebugDrawCanvas(UCanvas* Canvas, APlayerController*) override;`
- L188 _protected member_ `FVector LastDebugDrawLocation = FVector::ZeroVector;`
- L191 _protected prototype_ `void CalculateEscapeGraph(FZoneGraphDataEscapeGraph& EscapeGraph);`
- L195 _protected member_ `FZoneGraphTag DangerAnnotationTag;` — `UPROPERTY(Category="Annotation", EditAnywhere)` — Tag to mark the lanes that should be fled.
- L199 _protected member_ `FZoneGraphTag ObstacleAnnotationTag;` — `UPROPERTY(Category="Annotation", EditAnywhere)` — Tag to mark the lanes influenced by an obstacle.
- L203 _protected member_ `FZoneGraphTagFilter AffectedLaneTags;` — `UPROPERTY(Category="Annotation", EditAnywhere)` — Filter specifying which lanes the Annotation is applied to.
- L207 _protected member_ `FZoneGraphTagFilter EscapeLaneTags;` — `UPROPERTY(Category="Annotation", EditAnywhere)` — Filter specifying which lanes can be used during Disturbance.
- L211 _protected member_ `float IdealSpanLength = 500.0f;` — `UPROPERTY(Category="Annotation", EditAnywhere)` — Ideal span length for lane subdivision. Each lane will have between 2 and 8 spans.
- L214 _protected member_ `TArray<FZoneGraphDisturbanceArea> Dangers;` — Array of currently active dangers.
- L217 _protected member_ `TArray<FZoneGraphObstacleDisturbanceArea> Obstacles;` — Array of obstacles.
- L220 _protected member_ `bool bDisturbancesChanged = false;` — Flag indicating if the event processing changed the dangers.
- L223 _protected member_ `TArray<FZoneGraphDataEscapeGraph> EscapeGraphs;` — Disturbance graph for each ZoneGraphData
- L226 _protected member_ `FZoneGraphTagMask PreviouslyAppliedTags = FZoneGraphTagMask::None;` — Combined mask of tags added in previous update (used for clearing previous state)
- L230 _protected member_ `TObjectPtr<UZoneGraphSubsystem> ZoneGraphSubsystem = nullptr;` — `UPROPERTY(Transient)` — Cached ZoneGraphSubsystem

#### class `UZoneGraphDisturbanceAnnotationTest`  
`class UZoneGraphDisturbanceAnnotationTest : public UZoneGraphAnnotationTest`  
_L237-261_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UZoneGraphAnnotationTest`
- desc: Test for Disturbance Annotation
- L244 _public prototype_ `virtual FBox CalcBounds(const FTransform& LocalToWorld) const override;`
- L245 _public prototype_ `virtual void DebugDraw(FDebugRenderSceneProxy* DebugProxy) override;`
- L249 _public prototype_ `virtual void Trigger() override;`
- L254 _protected member_ `FVector Offset;` — `UPROPERTY(EditAnywhere, Category = "Test")`
- L257 _protected member_ `float Duration = 10.0f;` — `UPROPERTY(EditAnywhere, Category = "Test")`
- L260 _protected member_ `float DangerRadius = 500.0f;` — `UPROPERTY(EditAnywhere, Category = "Test")`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API ZONEGRAPHANNOTATIONS_API`

### `Plugins/Runtime/ZoneGraphAnnotations/Source/ZoneGraphAnnotations/Public/Annotations/ZoneGraphDisturbanceAnnotationBPLibrary.h` (Public)


#### class `UZoneGraphDisturbanceAnnotationBPLibrary`  
`class UZoneGraphDisturbanceAnnotationBPLibrary : public UBlueprintFunctionLibrary`  
_L16-32_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Set of utilities for dealing with Disturbance Annotation.
- L30 _public prototype_ `static void TriggerDanger(UObject* WorldContextObject, const AActor* Instigator, const FVector Position, const float Radius, const float Duration);` — `UFUNCTION(BlueprintCallable, Category = "ZoneGraphAnnotations", meta = (WorldContext = "WorldContextObject"))` — Triggers Danger event at specific location. @param Instigator (optional) identifies this event coming from specific Instigator, only one danger will persist per instigator. @param Position Position of the danger. @param Radius Radius of the danger. @param Duration Duration of the danger.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API ZONEGRAPHANNOTATIONS_API`

### `Plugins/Runtime/ZoneGraphAnnotations/Source/ZoneGraphAnnotations/Public/IZoneGraphAnnotationsModule.h` (Public)


#### class `IZoneGraphAnnotationsModule`  
`class IZoneGraphAnnotationsModule : public IModuleInterface`  
_L14-39_
- inherits: `IModuleInterface`
- desc: The public interface to this module.  In most cases, this interface is only public to sibling modules within this plugin.
- L25 _public function_ `static inline IZoneGraphAnnotationsModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L35 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Plugins/Runtime/ZoneGraphAnnotations/Source/ZoneGraphAnnotations/Public/ZoneGraphAnnotationComponent.h` (Public)


#### class `FZoneGraphAnnotationSceneProxy`  
`class FZoneGraphAnnotationSceneProxy final : public FDebugRenderSceneProxy`  
_L22-33_
- inherits: `FDebugRenderSceneProxy`
- L25 _public prototype_ `FZoneGraphAnnotationSceneProxy(const UPrimitiveComponent& InComponent, const EDrawType InDrawType = EDrawType::WireMesh);`
- L27 _public prototype_ `virtual SIZE_T GetTypeHash() const override;`
- L28 _public prototype_ `virtual FPrimitiveViewRelevance GetViewRelevance(const FSceneView* View) const override;`
- L29 _public prototype_ `virtual uint32 GetMemoryFootprint(void) const override;`
- L32 _private member_ `uint32 ViewFlagIndex = 0;`

#### class `UZoneGraphAnnotationComponent`  
`class UZoneGraphAnnotationComponent : public UDebugDrawComponent`  
_L38-103_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UDebugDrawComponent`
- L43 _public prototype_ `UZoneGraphAnnotationComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L46 _public prototype_ `virtual void PostSubsystemsInitialized();` — Called during OnRegister(), or after all subsystems have been initialized.
- L49 _public function_ `virtual void TickAnnotation(const float DeltaTime, FZoneGraphAnnotationTagContainer& AnnotationTagContainer)` — Ticks the Annotation and changes the tags in the container when needed.
- L52 _public function_ `virtual void HandleEvents(const FInstancedStructContainer& Events)` — Called when new events are ready to be processed
- L55 _public function_ `virtual FZoneGraphTagMask GetAnnotationTags() const` — @return Tags applied by the Annotation, used to lookup Annotations from tags.
- L58 _public function_ `virtual void PostZoneGraphDataAdded(const AZoneGraphData& ZoneGraphData)` — Called when new ZoneGraph data is added.
- L61 _public function_ `virtual void PreZoneGraphDataRemoved(const AZoneGraphData& ZoneGraphData)` — Called when new ZoneGraph data is removed.
- L65 _public prototype_ `void GetFirstViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;` — Returns first view point (player controller or debug camera)
- L68 _public prototype_ `float GetMaxDebugDrawDistance() const;` — Returns ZoneGraph max debug draw distance.
- L71 _public function_ `virtual void DebugDraw(FZoneGraphAnnotationSceneProxy* DebugProxy)` — Called when scene proxy is rebuilt.
- L74 _public function_ `virtual void DebugDrawCanvas(UCanvas* Canvas, APlayerController*)` — Called when it's time to draw to canvas.
- L79 _protected prototype_ `void OnPostZoneGraphDataAdded(const AZoneGraphData* ZoneGraphData);`
- L80 _protected prototype_ `void OnPreZoneGraphDataRemoved(const AZoneGraphData* ZoneGraphData);`
- L81 _protected prototype_ `void OnPostWorldInit(UWorld* World, const UWorld::InitializationValues);`
- L84 _protected prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L87 _protected prototype_ `virtual void OnRegister() override;`
- L88 _protected prototype_ `virtual void OnUnregister() override;`
- L90 _protected prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;`
- L92 _protected member_ `FDelegateHandle OnPostZoneGraphDataAddedHandle;`
- L93 _protected member_ `FDelegateHandle OnPreZoneGraphDataRemovedHandle;`
- L94 _protected member_ `FDelegateHandle OnPostWorldInitDelegateHandle;`
- L97 _protected prototype_ `virtual FDebugRenderSceneProxy* CreateDebugSceneProxy() override;`
- L98 _protected member_ `FDelegateHandle CanvasDebugDrawDelegateHandle;`
- L102 _protected member_ `bool bEnableDebugDrawing = false;` — `UPROPERTY(EditAnywhere, Category = Debug)`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API ZONEGRAPHANNOTATIONS_API`

### `Plugins/Runtime/ZoneGraphAnnotations/Source/ZoneGraphAnnotations/Public/ZoneGraphAnnotationSubsystem.h` (Public)


#### struct `FZoneGraphDataAnnotationTags`  
`struct FZoneGraphDataAnnotationTags`  
_L23-28_
- desc: Struct holding combined tags for a specific ZoneGraphData.
- L25 _public member_ `TArray<FZoneGraphTagMask> LaneTags;` — Combined array of tags from all Annotations.
- L26 _public member_ `FZoneGraphDataHandle DataHandle;` — Handle of the data
- L27 _public member_ `bool bInUse = false;` — True, if this entry is in use.

#### struct `FZoneGraphAnnotationTagContainer`  
`struct FZoneGraphAnnotationTagContainer`  
_L33-45_
- desc: Annotation tags per zone graph data
- L35 _public function_ `TArrayView<FZoneGraphTagMask> GetMutableAnnotationTagsForData(const FZoneGraphDataHandle DataHandle)`
- L41 _public member_ `TArray<FZoneGraphDataAnnotationTags> DataAnnotationTags;`
- L44 _public member_ `FZoneGraphTagMask CombinedStaticTags;` — Mask combining all static tags used by any of the registered ZoneGraphData.

#### struct `FRegisteredZoneGraphAnnotation`  
`struct FRegisteredZoneGraphAnnotation`  
_L50-64_
- reflection: `USTRUCT()`
- desc: Struct representing registered ZoneGraph data in the subsystem.
- L54 _public function_ `void Reset()`
- L61 _public member_ `TObjectPtr<UZoneGraphAnnotationComponent> AnnotationComponent = nullptr;` — `UPROPERTY()`
- L63 _public member_ `FZoneGraphTagMask AnnotationTags = FZoneGraphTagMask::None;` — Combination of all registered Annotation tag masks.

#### class `UZoneGraphAnnotationSubsystem`  
`class UZoneGraphAnnotationSubsystem : public UTickableWorldSubsystem`  
_L71-153_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTickableWorldSubsystem`
- desc: A subsystem managing Zonegraph Annotations.
- L76 _public prototype_ `UZoneGraphAnnotationSubsystem();`
- L79 _public prototype_ `void RegisterAnnotationComponent(UZoneGraphAnnotationComponent& Component);` — Registers Annotation component
- L82 _public prototype_ `void UnregisterAnnotationComponent(UZoneGraphAnnotationComponent& Component);` — Unregisters Annotation component
- L86 _public function_ `template <typename T> typename TEnableIf<TIsDerivedFrom<T, FZoneGraphAnnotationEventBase>::IsDerived, void>::Type SendEvent(const T& InRequest)` — Sends an event to the Annotations.
- L96 _public function_ `FZoneGraphTagMask GetAnnotationTags(const FZoneGraphLaneHandle LaneHandle) const` — @return bitmask of Annotation tags at given lane
- L104 _public function_ `UZoneGraphAnnotationComponent* GetFirstAnnotationForTag(const FZoneGraphTag AnnotationTag) const` — @return First Annotation matching a bit in the bitmask
- L111 _public prototype_ `void ReregisterTagsInEditor();`
- L116 _protected prototype_ `void PostZoneGraphDataAdded(const AZoneGraphData* ZoneGraphData);`
- L117 _protected prototype_ `void PreZoneGraphDataRemoved(const AZoneGraphData* ZoneGraphData);`
- L119 _protected prototype_ `void AddToAnnotationLookup(UZoneGraphAnnotationComponent& Annotation, const FZoneGraphTagMask AnnotationTags);`
- L120 _protected prototype_ `void RemoveFromAnnotationLookup(UZoneGraphAnnotationComponent& Annotation);`
- L122 _protected prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L123 _protected prototype_ `virtual void Deinitialize() override;`
- L124 _protected prototype_ `virtual void Tick(float DeltaTime) override;`
- L125 _protected prototype_ `virtual TStatId GetStatId() const override;`
- L129 _protected member_ `TArray<FRegisteredZoneGraphAnnotation> RegisteredComponents;` — `UPROPERTY(Transient)` — Array of registered components.
- L133 _protected member_ `FInstancedStructContainer Events[2];` — `UPROPERTY(Transient)` — Stream of events to be processed, double buffered.
- L134 _protected prototype_ `UE_MT_DECLARE_RW_ACCESS_DETECTOR(EventsDetector);`
- L135 _protected member_ `UE::FSpinLock EventsLock;`
- L139 _protected member_ `TArray<TObjectPtr<UZoneGraphAnnotationComponent>> TagToAnnotationLookup;` — `UPROPERTY(Transient)` — Lookup table from tag index to Annotation
- L142 _protected member_ `FZoneGraphAnnotationTagContainer AnnotationTagContainer;` — Combined tags for each ZoneGraphData. Each ZoneGraphData is indexed by it's data handle index, so there can be gaps in the array.
- L144 _protected member_ `FDelegateHandle OnPostZoneGraphDataAddedHandle;`
- L145 _protected member_ `FDelegateHandle OnPreZoneGraphDataRemovedHandle;`
- L152 _private member_ `int32 CurrentEventStream = 0;` — Index of the current event stream. It's marked as "private" to ensure the correctness of the assumptions regarding when it can change.

#### struct `TMassExternalSubsystemTraits`  
`template<> struct TMassExternalSubsystemTraits<UZoneGraphAnnotationSubsystem> final`  
_L156-163_

#### enum `TMassExternalSubsystemTraits::(anonymous)`  
``  
_L159-162_

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API ZONEGRAPHANNOTATIONS_API`
- L160 _enumerator_ `GameThreadOnly = false` (scope `TMassExternalSubsystemTraits::__anon4104afec0103`)
- L161 _enumerator_ `ThreadSafeWrite = false` (scope `TMassExternalSubsystemTraits::__anon4104afec0103`)

### `Plugins/Runtime/ZoneGraphAnnotations/Source/ZoneGraphAnnotations/Public/ZoneGraphAnnotationTestingActor.h` (Public)


#### class `UZoneGraphAnnotationTest`  
`class UZoneGraphAnnotationTest : public UObject`  
_L17-38_
- reflection: `UCLASS(MinimalAPI, Abstract, EditInlineNew)`
- inherits: `UObject`
- desc: Base class for ZoneGraph Annotation tests.
- L22 _public function_ `virtual void Trigger()`
- L25 _public function_ `virtual FBox CalcBounds(const FTransform& LocalToWorld) const`
- L26 _public function_ `virtual void DebugDraw(FDebugRenderSceneProxy* DebugProxy)`
- L27 _public function_ `virtual void DebugDrawCanvas(UCanvas* Canvas, APlayerController*)`
- L30 _public function_ `void SetOwner(UZoneGraphAnnotationTestingComponent* Owner)`
- L31 _public function_ `const UZoneGraphAnnotationTestingComponent* GetOwner() const`
- L34 _protected function_ `virtual void OnOwnerSet()`
- L37 _protected member_ `TObjectPtr<UZoneGraphAnnotationTestingComponent> OwnerComponent;` — `UPROPERTY()`

#### class `UZoneGraphAnnotationTestingComponent`  
`class UZoneGraphAnnotationTestingComponent : public UDebugDrawComponent`  
_L43-73_
- reflection: `UCLASS(MinimalAPI, ClassGroup = Debug)`
- inherits: `UDebugDrawComponent`
- desc: Debug component to test Mass ZoneGraph Annotations. Handles tests and rendering.
- L47 _public prototype_ `UZoneGraphAnnotationTestingComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L49 _public prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;`
- L51 _public prototype_ `void Trigger();`
- L56 _protected prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L59 _protected prototype_ `virtual void OnRegister() override;`
- L60 _protected prototype_ `virtual void OnUnregister() override;`
- L64 _protected prototype_ `virtual FDebugRenderSceneProxy* CreateDebugSceneProxy() override;`
- L65 _protected prototype_ `virtual void DebugDraw(FDebugRenderSceneProxy* DebugProxy);`
- L66 _protected prototype_ `virtual void DebugDrawCanvas(UCanvas* Canvas, APlayerController*);`
- L68 _protected member_ `FDelegateHandle CanvasDebugDrawDelegateHandle;`
- L72 _protected member_ `TArray<TObjectPtr<UZoneGraphAnnotationTest>> Tests;` — `UPROPERTY(EditAnywhere, Category = "Test", Instanced)`

#### class `AZoneGraphAnnotationTestingActor`  
`class AZoneGraphAnnotationTestingActor : public AActor`  
_L78-98_
- reflection: `UCLASS(MinimalAPI, HideCategories = (Actor, Input, Collision, Rendering, Replication, Partition, HLOD, Cooking))`
- inherits: `AActor`
- desc: Debug actor to test Mass ZoneGraph Annotations.
- L82 _public prototype_ `AZoneGraphAnnotationTestingActor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L89 _public prototype_ `void Trigger();` — `UFUNCTION(BlueprintCallable, CallInEditor, Category = "Test")` — Simple trigger function to trigger something on the tests. Ideally this would be part of each test, but it does not work there.
- L93 _protected prototype_ `virtual void PostEditMove(bool bFinished) override;`
- L97 _protected member_ `TObjectPtr<UZoneGraphAnnotationTestingComponent> TestingComp;` — `UPROPERTY(Category = Default, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API ZONEGRAPHANNOTATIONS_API`

### `Plugins/Runtime/ZoneGraphAnnotations/Source/ZoneGraphAnnotations/Public/ZoneGraphAnnotationTypes.h` (Public)


#### struct `FZoneGraphAnnotationEventBase`  
`struct FZoneGraphAnnotationEventBase`  
_L14-17_
- reflection: `USTRUCT()`
- desc: Base structs for all events for UZoneGraphAnnotationSubsystem.

#### class `FMassLaneObstacleID`  
`class FMassLaneObstacleID`  
_L19-45_
- L22 _public function_ `FMassLaneObstacleID()`
- L24 _public member_ `static const FMassLaneObstacleID InvalidID;`
- L25 _public function_ `static FMassLaneObstacleID GetNextUniqueID()`
- L31 _public function_ `bool operator==(const FMassLaneObstacleID& Other) const`
- L36 _public function_ `uint64 GetValue() const`
- L38 _public function_ `bool IsValid() const`
- L41 _private member_ `static uint64 NextUniqueID;`
- L43 _private function_ `FMassLaneObstacleID(uint64 ID) : Value(ID)`
- L44 _private member_ `uint64 Value = MAX_uint64;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ZONEGRAPHANNOTATIONS_API`
- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogZoneGraphAnnotations, Warning, All);`
- L47 _function_ `inline uint32 GetTypeHash(const FMassLaneObstacleID& Obs)`
