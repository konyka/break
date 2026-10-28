# Plugins / SmartObjectsModule

- module root: `Plugins/Runtime/SmartObjects/Source/SmartObjectsModule`
- headers: 40; symbols: 1427
- symbol kinds: class=30, delegate=10, enum=26, enumerator=87, externvar=5, function=282, macro=28, member=342, namespace=18, prototype=514, struct=72, typedef=12, variable=1
- PrivateDependencyModuleNames: InputCore, RenderCore
- PublicDependencyModuleNames: AIModule, BlueprintGraph, Core, CoreUObject, DeveloperSettings, Engine, GameplayAbilities, GameplayTags, MassCore, MassEntity, NavigationSystem, PropertyBindingUtils, RHI, TargetingSystem, UnrealEd, WorldConditions

### `Plugins/Runtime/SmartObjects/Source/SmartObjectsModule/Private/SmartObjectPropertyHelpers.h` (Private)


#### struct `FSmartObjectEditPropertyPath`  
`struct FSmartObjectEditPropertyPath`  
_L13-132_
- desc: Helper class to deal with relative property paths in PostEditChangeChainProperty(). @todo: Make this more widely available, this is copy from State Tree.
- L32 _public prototype_ `FSmartObjectEditPropertyPath() = default;`
- L35 _public function_ `explicit FSmartObjectEditPropertyPath(const UStruct* BaseStruct, const FString& InPath)` — Makes property path relative to BaseStruct. Checks if the path is not part of the type.
- L73 _public function_ `explicit FSmartObjectEditPropertyPath(const FPropertyChangedChainEvent& PropertyChangedEvent)` — Makes property path from property change event.
- L89 _public function_ `bool ContainsPath(const FSmartObjectEditPropertyPath& InPath) const` — @return true if the property path contains specified path.
- L107 _public function_ `bool IsPathExact(const FSmartObjectEditPropertyPath& InPath) const` — @return true if the property path is exactly the specified path.
- L125 _public function_ `int32 GetPropertyArrayIndex(const FSmartObjectEditPropertyPath& InPath) const` — @return array index at specified property, or INDEX_NONE, if the property is not array or property not found.
- L131 _private member_ `TArray<FStateTreeEditPropertySegment> Path;`

#### struct `FSmartObjectEditPropertyPath::FStateTreeEditPropertySegment`  
`struct FStateTreeEditPropertySegment`  
_L16-29_
- L18 _public prototype_ `FStateTreeEditPropertySegment() = default;`
- L19 _public function_ `FStateTreeEditPropertySegment(const FProperty* InProperty, const FName InPropertyName, const int32 InArrayIndex = INDEX_NONE) : Property(InProperty) , PropertyName(InPropertyName) , ArrayIndex(InArrayIndex)`
- L26 _public member_ `const FProperty* Property = nullptr;`
- L27 _public member_ `FName PropertyName = FName();`
- L28 _public member_ `int32 ArrayIndex = INDEX_NONE;`

### `Plugins/Runtime/SmartObjects/Source/SmartObjectsModule/Private/SmartObjectSubsystemRenderingActor.h` (Private)


#### class `USmartObjectSubsystemRenderingComponent`  
`class USmartObjectSubsystemRenderingComponent : public USmartObjectDebugRenderingComponent`  
_L12-32_
- reflection: `UCLASS(MinimalAPI, ClassGroup = Debug, NotBlueprintable, NotPlaceable)`
- inherits: `USmartObjectDebugRenderingComponent`
- desc: Rendering component for SmartObjectRendering actor.
- L17 _public function_ `explicit USmartObjectSubsystemRenderingComponent(const FObjectInitializer& ObjectInitializer) : USmartObjectDebugRenderingComponent(ObjectInitializer)`
- L26 _protected prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;`
- L29 _protected prototype_ `virtual void DebugDraw(FDebugRenderSceneProxy* DebugProxy) override;`
- L30 _protected prototype_ `virtual void DebugDrawCanvas(UCanvas* Canvas, APlayerController*) override;`

#### class `ASmartObjectSubsystemRenderingActor`  
`class ASmartObjectSubsystemRenderingActor : public AActor`  
_L35-50_
- reflection: `UCLASS(MinimalAPI, Transient, NotBlueprintable, NotPlaceable)`
- inherits: `AActor`
- L40 _public prototype_ `ASmartObjectSubsystemRenderingActor();`
- L43 _public function_ `virtual bool ShouldExport() override`
- L44 _public function_ `virtual bool CanDeleteSelectedActor(FText& OutReason) const override`
- L49 _private member_ `TObjectPtr<USmartObjectSubsystemRenderingComponent> RenderingComponent;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SMARTOBJECTSMODULE_API`

### `Plugins/Runtime/SmartObjects/Source/SmartObjectsModule/Private/SmartObjectTestingActor.h` (Private)


#### class `USmartObjectTest`  
`class USmartObjectTest : public UObject`  
_L15-87_
- reflection: `UCLASS(MinimalAPI, Abstract, EditInlineNew)`
- inherits: `UObject`
- desc: Base class for SmartObject tests.
- L24 _public prototype_ `bool RunTest();` — Calls 'Run' method if both Testing actor and SmartObject subsystem are valid. @return True if a redraw is required; false otherwise
- L30 _public prototype_ `bool ResetTest();` — Calls 'Reset' method if both Testing actor and SmartObject subsystem are valid. @return True if a redraw is required; false otherwise.
- L36 _public prototype_ `FBox CalcTestBounds() const;` — Calls 'CalcBounds' method if both Testing actor and SmartObject subsystem are valid. @return The box representing the bounds encapsulating all elements of the test.
- L39 _public prototype_ `void DebugDraw(FDebugRenderSceneProxy* DebugProxy) const;`
- L40 _public prototype_ `void DebugDrawCanvas(UCanvas* Canvas, APlayerController*) const;`
- L44 _protected prototype_ `virtual void PostInitProperties() override;`
- L51 _protected function_ `virtual bool Run(ASmartObjectTestingActor& TestingActor)` — Method to override to perform a test. @param TestingActor A testing actor that will provide a valid SmartObjectSubsystem (i.e. safe to call GetSubsystemRef) @return True if a redraw is required (e.g. results have changed); false otherwise.
- L58 _protected function_ `virtual bool Reset(ASmartObjectTestingActor& TestingActor)` — Method to override to reset results of the test. @param TestingActor A testing actor that will provide a valid SmartObjectSubsystem (i.e. safe to call GetSubsystemRef)* @return True if a redraw is required (e.g. cleared some results); false otherwise.
- L65 _protected function_ `virtual FBox CalcBounds(ASmartObjectTestingActor& TestingActor) const` — Method to override to provide the bounds of the test, if any. @param TestingActor A testing actor that will provide a valid SmartObjectSubsystem (i.e. safe to call GetSubsystemRef)* @return The box representing the bounds encapsulating all elements of the test, if any.
- L73 _protected function_ `virtual void DebugDraw(ASmartObjectTestingActor& TestingActor, FDebugRenderSceneProxy* DebugProxy) const` — Method to override to add element to the debug render scene. @param TestingActor A testing actor that will provide a valid SmartObjectSubsystem (i.e. safe to call GetSubsystemRef)* @param DebugProxy Scene proxy in which debug shapes can be added.
- L81 _protected function_ `virtual void DebugDrawCanvas(ASmartObjectTestingActor& TestingActor, UCanvas* Canvas, APlayerController* PlayerController) const` — Method to override to add element to the 2D canvas. @param TestingActor A testing actor that will provide a valid SmartObjectSubsystem (i.e. safe to call GetSubsystemRef)* @param Canvas Canvas where debug text can be added. @param PlayerController Player controller associated to the debug draw canvas.
- L86 _private member_ `TObjectPtr<ASmartObjectTestingActor> SmartObjectTestingActor;` — `UPROPERTY(Transient)`

#### class `USmartObjectSimpleQueryTest`  
`class USmartObjectSimpleQueryTest : public USmartObjectTest`  
_L92-110_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USmartObjectTest`
- desc: Simple test to run a query and draw the results.
- L97 _protected prototype_ `virtual bool Run(ASmartObjectTestingActor& TestingActor) override;`
- L98 _protected prototype_ `virtual bool Reset(ASmartObjectTestingActor& TestingActor) override;`
- L99 _protected prototype_ `virtual FBox CalcBounds(ASmartObjectTestingActor& TestingActor) const override;`
- L102 _protected prototype_ `virtual void DebugDraw(ASmartObjectTestingActor& TestingActor, FDebugRenderSceneProxy* DebugProxy) const override;`
- L106 _protected member_ `FSmartObjectRequest Request;` — `UPROPERTY(EditAnywhere, Category = Test)`
- L109 _protected member_ `TArray<FSmartObjectRequestResult> Results;` — `UPROPERTY(VisibleAnywhere, Category = Test, Transient)`

#### class `USmartObjectTestRenderingComponent`  
`class USmartObjectTestRenderingComponent : public USmartObjectDebugRenderingComponent`  
_L115-126_
- reflection: `UCLASS(MinimalAPI, ClassGroup = Debug, NotPlaceable)`
- inherits: `USmartObjectDebugRenderingComponent`
- desc: Debug rendering component for SmartObject tests.
- L119 _protected prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;`
- L120 _protected prototype_ `virtual void PostInitProperties() override;`
- L123 _protected prototype_ `virtual void DebugDraw(FDebugRenderSceneProxy* DebugProxy) override;`
- L124 _protected prototype_ `virtual void DebugDrawCanvas(UCanvas* Canvas, APlayerController*) override;`

#### class `ASmartObjectTestingActor`  
`class ASmartObjectTestingActor : public AActor`  
_L131-180_
- reflection: `UCLASS(MinimalAPI, HideCategories = (Activation, Actor, AssetUserData, Collision, Cooking, DataLayers, HLOD, Input, Lighting, LOD, Mobile, Mobility, Navigation, Physics, RayTracing, Rendering, Replication, Tags, TextureStreaming, WorldPartition))`
- inherits: `AActor`
- desc: Debug actor to test SmartObjects.
- L135 _public prototype_ `explicit ASmartObjectTestingActor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L137 _public prototype_ `FBox CalcTestsBounds() const;`
- L138 _public function_ `USmartObjectSubsystem* GetSubsystem() const`
- L139 _public function_ `USmartObjectSubsystem& GetSubsystemRef() const`
- L141 _public prototype_ `void ExecuteOnEachTest(TFunctionRef<void(USmartObjectTest&)> ExecFunc);`
- L142 _public prototype_ `void ExecuteOnEachTest(TFunctionRef<void(const USmartObjectTest&)> ExecFunc) const;`
- L147 _protected prototype_ `virtual void PostEditMove(bool bFinished) override;`
- L148 _protected prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L152 _protected prototype_ `void DebugInitializeSubsystemRuntime();` — `UFUNCTION(CallInEditor, Category = SmartObject, meta = (DisplayName = "Initialize Runtime"))` — Can be used in Editor world to initialize SmartObject runtime with running the simulation
- L156 _protected prototype_ `void DebugCleanupSubsystemRuntime();` — `UFUNCTION(CallInEditor, Category = SmartObject, meta = (DisplayName = "Cleanup Runtime"))` — Can be used in Editor world to cleanup SmartObject runtime after using debug initialization
- L159 _protected prototype_ `virtual void PostRegisterAllComponents() override;`
- L160 _protected prototype_ `virtual bool ShouldTickIfViewportsOnly() const override;`
- L161 _protected prototype_ `virtual void Tick(float DeltaTime) override;`
- L164 _protected prototype_ `void RunTests();` — `UFUNCTION(BlueprintCallable, CallInEditor, Category = Test)`
- L167 _protected prototype_ `void ResetTests();` — `UFUNCTION(BlueprintCallable, CallInEditor, Category = Test)`
- L170 _protected member_ `TArray<TObjectPtr<USmartObjectTest>> Tests;` — `UPROPERTY(EditAnywhere, Category = Test, Instanced)`
- L173 _protected member_ `TObjectPtr<USmartObjectTestRenderingComponent> RenderingComponent;` — `UPROPERTY(Transient)`
- L176 _protected member_ `TObjectPtr<USmartObjectSubsystem> SmartObjectSubsystem = nullptr;` — `UPROPERTY(Transient)`
- L179 _protected member_ `bool bRunTestsEachFrame = false;` — `UPROPERTY(EditAnywhere, Category = Test)`

### `Plugins/Runtime/SmartObjects/Source/SmartObjectsModule/Public/Annotations/SmartObjectAnnotation_SlotUserCollision.h` (Public)


#### struct `FSmartObjectAnnotation_SlotUserCollision`  
`struct FSmartObjectAnnotation_SlotUserCollision : public FSmartObjectSlotAnnotation`  
_L15-37_
- reflection: `USTRUCT(meta = (DisplayName="Slot User Collision"))`
- inherits: `FSmartObjectSlotAnnotation`
- desc: Annotation to check if a smart object user can stand on the slot without overlaps. Uses validation filter to get the user capsule for collisions testing, or use specific capsule defined in the annotation.
- L20 _public prototype_ `virtual void DrawVisualization(FSmartObjectVisualizationContext& VisContext) const override;`
- L21 _public prototype_ `virtual void DrawVisualizationHUD(FSmartObjectVisualizationContext& VisContext) const override;`
- L24 _public prototype_ `virtual void GetColliders(const FSmartObjectUserCapsuleParams& UserCapsule, const FTransform& SlotTransform, TArray<FSmartObjectAnnotationCollider>& OutColliders) const;`
- L27 _public prototype_ `virtual void CollectDataForGameplayDebugger(FSmartObjectAnnotationGameplayDebugContext& DebugContext) const override;`
- L32 _public member_ `bool bUseUserCapsuleSize = true;` — `UPROPERTY(EditAnywhere, Category = "Default")` — If true, the user capsule size is got from validation filter and used for testing.
- L36 _public member_ `FSmartObjectUserCapsuleParams Capsule;` — `UPROPERTY(EditAnywhere, Category="Default", meta = (EditCondition = "bUseUserCapsuleSize == false", EditConditionHides))` — Dimensions of the capsule to test at the slot location.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SMARTOBJECTSMODULE_API`

### `Plugins/Runtime/SmartObjects/Source/SmartObjectsModule/Public/Annotations/SmartObjectSlotEntranceAnnotation.h` (Public)


#### enum `ESmartObjectEntrancePriority`  
`enum class ESmartObjectEntrancePriority : uint8`  
_L24-38_
- reflection: `UENUM(BlueprintType)`
- desc: Enum used to define a entrance selection priority. Highest priority is preferred, but when the priority is the same the selection method (distance) is used to decide which entrance is chosen.
- L26 _public enumerator_ `Lowest`
- L27 _public enumerator_ `Lower`
- L28 _public enumerator_ `Low`
- L29 _public enumerator_ `BelowNormal`
- L30 _public enumerator_ `Normal`
- L31 _public enumerator_ `AboveNormal`
- L32 _public enumerator_ `High`
- L33 _public enumerator_ `Higher`
- L34 _public enumerator_ `Highest`
- L36 _public enumerator_ `MIN = Lowest UMETA(Hidden)`
- L37 _public enumerator_ `MAX = Highest UMETA(Hidden)`

#### struct `FSmartObjectSlotEntranceAnnotation`  
`struct FSmartObjectSlotEntranceAnnotation : public FSmartObjectSlotAnnotation`  
_L45-136_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName="Entrance"))`
- inherits: `FSmartObjectSlotAnnotation`
- desc: Annotation to define a entrance locations for a Smart Object Slot. This can be used to add multiple entry points to a slot, or to validate the entries against navigation data.
- L51 _public function_ `FSmartObjectSlotEntranceAnnotation() : bIsEntry(true) , bIsExit(true) , bTraceGroundLocation(true) , bCheckTransitionTrajectory(false)` — Macro needed to avoid deprecation errors with "Tag" being copied or created in the default methods
- L58 _public prototype_ `FSmartObjectSlotEntranceAnnotation(const FSmartObjectSlotEntranceAnnotation&) = default;`
- L59 _public prototype_ `FSmartObjectSlotEntranceAnnotation(FSmartObjectSlotEntranceAnnotation&&) = default;`
- L60 _public prototype_ `FSmartObjectSlotEntranceAnnotation& operator=(const FSmartObjectSlotEntranceAnnotation&) = default;`
- L61 _public prototype_ `FSmartObjectSlotEntranceAnnotation& operator=(FSmartObjectSlotEntranceAnnotation&&) = default;`
- L65 _public prototype_ `virtual void DrawVisualization(FSmartObjectVisualizationContext& VisContext) const override;`
- L66 _public prototype_ `virtual void DrawVisualizationHUD(FSmartObjectVisualizationContext& VisContext) const override;`
- L67 _public prototype_ `virtual void AdjustWorldTransform(const FTransform& SlotTransform, const FVector& DeltaTranslation, const FRotator& DeltaRotation) override;`
- L70 _public function_ `virtual bool HasTransform() const override`
- L71 _public prototype_ `virtual FTransform GetAnnotationWorldTransform(const FTransform& SlotTransform) const override;`
- L72 _public prototype_ `virtual FVector GetWorldLocation(const FTransform& SlotTransform) const;`
- L73 _public prototype_ `virtual FRotator GetWorldRotation(const FTransform& SlotTransform) const;`
- L76 _public prototype_ `virtual void GetTrajectoryColliders(const FTransform& SlotTransform, TArray<FSmartObjectAnnotationCollider>& OutColliders) const;` — @returns array of colliders that should free of collisions with world for this entrance to be used.
- L79 _public prototype_ `void PostSerialize(const FArchive& Ar);`
- L83 _public prototype_ `virtual void CollectDataForGameplayDebugger(FSmartObjectAnnotationGameplayDebugContext& DebugContext) const override;`
- L88 _public member_ `FVector3f Offset = FVector3f(0.f);` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Default")` — Local space offset of the entry.
- L92 _public member_ `FRotator3f Rotation = FRotator3f(0.f);` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Default")` — Local space rotation of the entry.
- L98 _public member_ `FGameplayTag Tag_DEPRECATED;` — `UE_DEPRECATED(all, "This property has been deprecated. Use EntranceTags instead.")` — `UPROPERTY()` — Tag that can be used to identify the entry.
- L103 _public member_ `FGameplayTagContainer Tags;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Default")` — Tags that can be used to identify the entry.
- L107 _public member_ `uint8 bIsEntry : 1;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Default")` — Set to true if the entry can be used to enter the slot.
- L111 _public member_ `uint8 bIsExit : 1;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Default")` — Set to true if the entry can be used to exit the slot.
- L115 _public member_ `uint8 bTraceGroundLocation : 1;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Default")` — If set to true, ground location will be adjusted using a line trace.
- L119 _public member_ `uint8 bCheckTransitionTrajectory : 1;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Default")` — If set to true, collisions will be checked between the transition from navigation location and slot location.
- L123 _public member_ `ESmartObjectEntrancePriority SelectionPriority = ESmartObjectEntrancePriority::Normal;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Default")` — During entrance selection, the highest priority entrance is selected. If multiple entrances share same priority, then the selection method is used (e.g. based on distance).
- L127 _public member_ `float TrajectoryStartHeightOffset = 80.0f;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Default", meta = (EditCondition = "bCheckTransitionTrajectory"))` — Height offset at start of the transition collision check.
- L131 _public member_ `float TrajectorySlotHeightOffset = 40.0f;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Default", meta = (EditCondition = "bCheckTransitionTrajectory"))` — Height offset at slot location of the transition collision check.
- L135 _public member_ `float TransitionCheckRadius = 10.0f;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Default", meta = (EditCondition = "bCheckTransitionTrajectory"))` — Radius of the transition trajectory check.

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FSmartObjectSlotEntranceAnnotation> : public TStructOpsTypeTraitsBase2<FSmartObjectSlotEntranceAnnotation>`  
_L140-146_
- inherits: `TStructOpsTypeTraitsBase2<FSmartObjectSlotEntranceAnnotation>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L143-145_

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API SMARTOBJECTSMODULE_API`
- L144 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anond1533b4c0103`)
- L151 _namespace_ `namespace UE`
- L151 _namespace_ `namespace SmartObject` (scope `UE`)
- L151 _namespace_ `namespace Annotations` (scope `UE::SmartObject`)
- L156 _prototype_ `extern const ANavigationData* GetNavDataForActor(const UWorld& World, const AActor* UserActor);` (scope `UE::SmartObject::Annotations`) — @returns navigation data for a specific actor. Similar to FNavigationSystem::GetNavDataForActor() but allows to pass custom world.
- L168 _prototype_ `extern bool ProjectNavigationLocation(const ANavigationData& NavData, const FVector Location, const FBox& SearchBounds, const FSharedConstNavQueryFilter& NavigationFilter, const AActor* InstigatorActor, FNavLocation& OutNavLocation);` (scope `UE::SmartObject::Annotations`) — Projects given location on nearest navigable surface. @param NavData navigation data to use for projection. @param Location location to project @param SearchBounds the bounds where the result must be contained @param NavigationFilter navigation filter to use to projection test @param InstigatorActor actor requesting the projection (optional) @param OutNavLocation resulting nav location @return true if a navigable location is found within SearchBounds.
- L180 _prototype_ `extern bool TraceGroundLocation(const UWorld& World, const FVector Location, const FBox& SearchBounds, const FSmartObjectTraceParams& TraceParameters, const FCollisionQueryParams& CollisionQueryParams, FVector& OutGroundLocation);` (scope `UE::SmartObject::Annotations`) — Traces location down to find ground within SearchBounds. @param World world to use for the trace @param Location location to trace down @param SearchBounds the bounds where the result must be contained @param TraceParameters Smart Object trace parameters for the trace, defines if the trace is done by channel, profile or object type @param CollisionQueryParams Collision Query Params for the trace @param OutGroundLocation resulting ground location @return true if valid ground location found within SearchBounds.
- L190 _prototype_ `extern bool TestCollidersOverlap(const UWorld& World, TConstArrayView<FSmartObjectAnnotationCollider> Colliders, const FSmartObjectTraceParams& TraceParameters, const FCollisionQueryParams& CollisionQueryParams);` (scope `UE::SmartObject::Annotations`) — Checks for overlap of given colliders. @param World world used for the overlap test @param Colliders array of colliders to test @param TraceParameters Smart Object trace parameters for the overlap test, defines if the trace is done by channel, profile or object type @param CollisionQueryParams Collision Query Params for the overlap test @return true if any of the colliders overlap.

### `Plugins/Runtime/SmartObjects/Source/SmartObjectsModule/Public/Annotations/SmartObjectSlotLinkAnnotation.h` (Public)


#### struct `FSmartObjectSlotLinkAnnotation`  
`struct FSmartObjectSlotLinkAnnotation : public FSmartObjectSlotAnnotation`  
_L15-32_
- reflection: `USTRUCT(meta = (DisplayName="Slot Link"))`
- inherits: `FSmartObjectSlotAnnotation`
- desc: Annotation to allow to find slots based on a Gameplay Tag. This can be used to reuse same behavior on different slots, allowing to use a tag to identify a related slot.
- L18 _public prototype_ `virtual ~FSmartObjectSlotLinkAnnotation() override = default;`
- L21 _public prototype_ `virtual void DrawVisualization(FSmartObjectVisualizationContext& VisContext) const override;`
- L22 _public prototype_ `virtual void DrawVisualizationHUD(FSmartObjectVisualizationContext& VisContext) const override;`
- L27 _public member_ `FGameplayTag Tag;` — `UPROPERTY(EditAnywhere, Category="Default")` — Tag to identify this slot.
- L31 _public member_ `FSmartObjectSlotReference LinkedSlot;` — `UPROPERTY(EditAnywhere, Category="Default", meta = (NoBinding))` — The slot the annotation points at.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SMARTOBJECTSMODULE_API`

### `Plugins/Runtime/SmartObjects/Source/SmartObjectsModule/Public/BlackboardKeyType_SOClaimHandle.h` (Public)


#### class `UBlackboardKeyType_SOClaimHandle`  
`class UBlackboardKeyType_SOClaimHandle : public UBlackboardKeyType`  
_L18-43_
- reflection: `UCLASS(MinimalAPI, EditInlineNew, meta=(DisplayName="SO Claim Handle"))`
- inherits: `UBlackboardKeyType`
- desc: Blackboard key type that holds a SmartObject claim handle
- L22 _public prototype_ `explicit UBlackboardKeyType_SOClaimHandle(const FObjectInitializer& ObjectInitializer);`
- L24 _public typedef_ `typedef FSmartObjectClaimHandle FDataType;`
- L25 _public member_ `static const FDataType InvalidValue;`
- L28 _public member_ `FSmartObjectClaimHandle Handle;` — `UPROPERTY(Category=Blackboard, EditDefaultsOnly)`
- L30 _public prototype_ `static FSmartObjectClaimHandle GetValue(const UBlackboardKeyType_SOClaimHandle* KeyOb, const uint8* MemoryBlock);`
- L31 _public prototype_ `static bool SetValue(UBlackboardKeyType_SOClaimHandle* KeyOb, uint8* MemoryBlock, const FSmartObjectClaimHandle& Value);`
- L34 _protected prototype_ `virtual EBlackboardCompare::Type CompareValues(const UBlackboardComponent& OwnerComp, const uint8* MemoryBlock, const UBlackboardKeyType* OtherKeyOb, const uint8* OtherMemoryBlock) const override;`
- L39 _protected prototype_ `virtual void InitializeMemory(UBlackboardComponent& OwnerComp, uint8* MemoryBlock) override;`
- L40 _protected prototype_ `virtual void Clear(UBlackboardComponent& OwnerComp, uint8* MemoryBlock) override;`
- L41 _protected prototype_ `virtual FString DescribeValue(const UBlackboardComponent& OwnerComp, const uint8* MemoryBlock) const override;`
- L42 _protected prototype_ `virtual bool TestBasicOperation(const UBlackboardComponent& OwnerComp, const uint8* MemoryBlock, EBasicKeyOperation::Type Op) const override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API SMARTOBJECTSMODULE_API`

### `Plugins/Runtime/SmartObjects/Source/SmartObjectsModule/Public/EnvQueryGenerator_SmartObjects.h` (Public)


#### class `UEnvQueryGenerator_SmartObjects`  
`class UEnvQueryGenerator_SmartObjects : public UEnvQueryGenerator`  
_L12-40_
- reflection: `UCLASS(MinimalAPI, meta = (DisplayName = "Smart Objects"))`
- inherits: `UEnvQueryGenerator`
- desc: Fetches Smart Object slots within QueryBoxExtent from locations given by QueryOriginContext, that match SmartObjectRequestFilter
- L17 _public prototype_ `UEnvQueryGenerator_SmartObjects();`
- L20 _protected prototype_ `virtual void GenerateItems(FEnvQueryInstance& QueryInstance) const override;`
- L22 _protected prototype_ `virtual FText GetDescriptionTitle() const override;`
- L23 _protected prototype_ `virtual FText GetDescriptionDetails() const override;`
- L27 _protected member_ `TSubclassOf<UEnvQueryContext> QueryOriginContext;` — `UPROPERTY(EditAnywhere, Category=Generator)` — The context indicating the locations to be used as query origins
- L31 _protected member_ `FSmartObjectRequestFilter SmartObjectRequestFilter;` — `UPROPERTY(EditAnywhere, Category=Generator)` — If set will be used to filter gathered results
- L35 _protected member_ `FVector QueryBoxExtent;` — `UPROPERTY(EditAnywhere, Category = Generator)` — Combined with generator's origin(s) (as indicated by QueryOriginContext) determines query's volume
- L39 _protected member_ `bool bOnlyClaimable = true;` — `UPROPERTY(EditAnywhere, Category = Generator)` — Determines whether only currently claimable slots are allowed

### `Plugins/Runtime/SmartObjects/Source/SmartObjectsModule/Public/EnvQueryItemType_SmartObject.h` (Public)


#### struct `FSmartObjectSlotEQSItem`  
`struct FSmartObjectSlotEQSItem`  
_L11-27_
- L13 _public member_ `FVector Location;`
- L14 _public member_ `FSmartObjectHandle SmartObjectHandle;`
- L15 _public member_ `FSmartObjectSlotHandle SlotHandle;`
- L17 _public function_ `FSmartObjectSlotEQSItem(const FVector InLocation, const FSmartObjectHandle InSmartObjectHandle, const FSmartObjectSlotHandle InSlotHandle) : Location(InLocation), SmartObjectHandle(InSmartObjectHandle), SlotHandle(InSlotHandle)`
- L21 _public function_ `inline operator FVector() const`
- L23 _public function_ `bool operator==(const FSmartObjectSlotEQSItem& Other) const`

#### class `UEnvQueryItemType_SmartObject`  
`class UEnvQueryItemType_SmartObject : public UEnvQueryItemType_VectorBase`  
_L31-43_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEnvQueryItemType_VectorBase`
- L35 _public typedef_ `typedef FSmartObjectSlotEQSItem FValueType;`
- L37 _public prototype_ `UEnvQueryItemType_SmartObject();`
- L39 _public prototype_ `static const FSmartObjectSlotEQSItem& GetValue(const uint8* RawData);`
- L40 _public prototype_ `static void SetValue(uint8* RawData, const FSmartObjectSlotEQSItem& Value);`
- L42 _public prototype_ `virtual FVector GetItemLocation(const uint8* RawData) const override;`

### `Plugins/Runtime/SmartObjects/Source/SmartObjectsModule/Public/GameplayDebuggerCategory_SmartObject.h` (Public)


#### class `FGameplayDebuggerCategory_SmartObject`  
`class FGameplayDebuggerCategory_SmartObject : public FGameplayDebuggerCategory`  
_L14-40_
- inherits: `FGameplayDebuggerCategory`
- L17 _public prototype_ `FGameplayDebuggerCategory_SmartObject();`
- L19 _public prototype_ `static TSharedRef<FGameplayDebuggerCategory> MakeInstance();`
- L22 _protected prototype_ `virtual void CollectData(APlayerController* OwnerPC, AActor* DebugActor) override;`
- L23 _protected prototype_ `virtual void DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext) override;`
- L26 _private prototype_ `void ToggleInstanceTags();`
- L27 _private prototype_ `void ToggleSlotDetails();`
- L28 _private prototype_ `void ToggleAnnotations();`
- L39 _private member_ `FReplicationData DataPack;`

#### struct `FGameplayDebuggerCategory_SmartObject::FReplicationData`  
`struct FReplicationData`  
_L30-37_
- L32 _public prototype_ `void Serialize(FArchive& Ar);`
- L34 _public member_ `bool bDisplayInstanceTags = false;`
- L35 _public member_ `bool bDisplaySlotDetails = false;`
- L36 _public member_ `bool bDisplayAnnotations = false;`

### `Plugins/Runtime/SmartObjects/Source/SmartObjectsModule/Public/GenericSmartObject.h` (Public)


#### class `AGenericSmartObject`  
`class AGenericSmartObject : public AActor`  
_L15-33_
- reflection: `UCLASS(MinimalAPI, hidecategories = (Input))`
- inherits: `AActor`
- L19 _public prototype_ `AGenericSmartObject(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L22 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L27 _protected member_ `TObjectPtr<USmartObjectComponent> SOComponent;` — `UPROPERTY(EditAnywhere, Category = SmartObject, NoClear)`
- L31 _protected member_ `TObjectPtr<USmartObjectRenderingComponent> RenderingComponent;` — `UPROPERTY(NoClear)`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SMARTOBJECTSMODULE_API`

### `Plugins/Runtime/SmartObjects/Source/SmartObjectsModule/Public/SmartObjectAnnotation.h` (Public)


#### struct `FSmartObjectSlotAnnotation`  
`struct FSmartObjectSlotAnnotation : public FSmartObjectDefinitionData`  
_L18-54_
- reflection: `USTRUCT(BlueprintType, meta=(Hidden))`
- inherits: `FSmartObjectDefinitionData`
- desc: Base class for Smart Object Slot annotations. Annotation is a specific type of slot definition data that has methods to visualize it.
- L21 _public prototype_ `virtual ~FSmartObjectSlotAnnotation() override = default;`
- L27 _public function_ `virtual void DrawVisualization(FSmartObjectVisualizationContext& VisContext) const` — Methods to override to draw 3D visualization of the annotation.
- L30 _public function_ `virtual void DrawVisualizationHUD(FSmartObjectVisualizationContext& VisContext) const` — Methods to override to draw canvas visualization of the annotation.
- L38 _public function_ `virtual void AdjustWorldTransform(const FTransform& SlotTransform, const FVector& DeltaTranslation, const FRotator& DeltaRotation)` — Called in editor to adjust the transform of the annotation. @param SlotTransform World space transform of the slot. @param DeltaTranslation World space delta translation to apply. @param DeltaRotation World space delta rotation to apply.
- L42 _public function_ `virtual bool HasTransform() const` — @return true if the annotation has transform. Annotations with transforms can be selected and edited in the editor viewport.
- L49 _public function_ `virtual FTransform GetAnnotationWorldTransform(const FTransform& SlotTransform) const` — Returns the world space transform of the annotation. @param SlotTransform World space transform of the slot. @return World space transform of the annotation.
- L52 _public function_ `virtual void CollectDataForGameplayDebugger(FSmartObjectAnnotationGameplayDebugContext& DebugContext) const`

#### struct `FSmartObjectAnnotationGameplayDebugContext`  
`struct FSmartObjectAnnotationGameplayDebugContext`  
_L59-74_
- desc: Context passed to CollectDataForGameplayDebugger to show gameplay debugger information.
- L61 _public function_ `explicit FSmartObjectAnnotationGameplayDebugContext(FGameplayDebuggerCategory& InCategory, const USmartObjectDefinition& InDefinition) : Category(InCategory) , Definition(InDefinition)`
- L67 _public member_ `FGameplayDebuggerCategory& Category;`
- L68 _public member_ `const USmartObjectDefinition& Definition;`
- L69 _public member_ `const AActor* SmartObjectOwnerActor = nullptr;`
- L70 _public member_ `const AActor* DebugActor = nullptr;`
- L71 _public member_ `FTransform SlotTransform;`
- L72 _public member_ `FVector ViewLocation;`
- L73 _public member_ `FVector ViewDirection;`

### `Plugins/Runtime/SmartObjects/Source/SmartObjectsModule/Public/SmartObjectBindingCollection.h` (Public)


#### struct `FSmartObjectBindingCollection`  
`struct FSmartObjectBindingCollection : public FPropertyBindingBindingCollection`  
_L19-70_
- reflection: `USTRUCT()`
- inherits: `FPropertyBindingBindingCollection`
- desc: Representation of all property bindings in a SmartObjectDefinition
- L23 _public function_ `FSmartObjectDefinitionBindableStructDescriptor& AddBindableStruct(const FSmartObjectDefinitionBindableStructDescriptor& Descriptor)`
- L29 _public prototype_ `[[nodiscard]] TArray<FSmartObjectDefinitionPropertyBinding>&& ExtractBindings();` — Moves all bindings outside the collection
- L31 _public prototype_ `FPropertyBindingBindableStructDescriptor* GetMutableBindableStructDescriptorFromHandle(const FSmartObjectDefinitionDataHandle InSourceHandle);`
- L34 _public prototype_ `virtual int32 GetNumBindableStructDescriptors() const override;`
- L35 _public prototype_ `virtual const FPropertyBindingBindableStructDescriptor* GetBindableStructDescriptorFromHandle(FConstStructView InSourceHandleView) const override;`
- L37 _public prototype_ `virtual int32 GetNumBindings() const override;`
- L38 _public prototype_ `virtual void ForEachBinding(TFunctionRef<void(const FPropertyBindingBinding& Binding)> InFunction) const override;`
- L39 _public prototype_ `virtual void ForEachBinding(FPropertyBindingIndex16 InBegin, FPropertyBindingIndex16 InEnd, TFunctionRef<void(const FPropertyBindingBinding& Binding, const int32 BindingIndex)> InFunction) const override;`
- L40 _public prototype_ `virtual void ForEachMutableBinding(TFunctionRef<void(FPropertyBindingBinding& Binding)> InFunction) override;`
- L41 _public prototype_ `virtual void VisitBindings(TFunctionRef<EVisitResult(const FPropertyBindingBinding& Binding)> InFunction) const override;`
- L42 _public prototype_ `virtual void VisitBindings(FPropertyBindingIndex16 InBegin, FPropertyBindingIndex16 InEnd, TFunctionRef<EVisitResult(const FPropertyBindingBinding& Binding, const int32 BindingIndex)> InFunction) const override;`
- L43 _public prototype_ `virtual void VisitMutableBindings(TFunctionRef<EVisitResult(FPropertyBindingBinding& Binding)> InFunction) override;`
- L46 _protected prototype_ `virtual void VisitSourceStructDescriptorInternal(TFunctionRef<EVisitResult(const FPropertyBindingBindableStructDescriptor& Descriptor)> InFunction) const override;`
- L47 _protected prototype_ `virtual void OnReset() override;`
- L51 _public prototype_ `void AddSmartObjectBinding(FSmartObjectDefinitionPropertyBinding&& InBinding);`
- L54 _protected prototype_ `virtual FPropertyBindingBinding* AddBindingInternal(const FPropertyBindingPath& InSourcePath, const FPropertyBindingPath& InTargetPath) override;`
- L55 _protected prototype_ `virtual void RemoveBindingsInternal(TFunctionRef<bool(FPropertyBindingBinding&)> InPredicate) override;`
- L56 _protected prototype_ `virtual bool HasBindingInternal(TFunctionRef<bool(const FPropertyBindingBinding&)> InPredicate) const override;`
- L57 _protected prototype_ `virtual const FPropertyBindingBinding* FindBindingInternal(TFunctionRef<bool(const FPropertyBindingBinding&)> InPredicate) const override;`
- L65 _private member_ `TArray<FSmartObjectDefinitionBindableStructDescriptor> BindableStructs;` — `UPROPERTY(VisibleAnywhere, Category = "SmartObject")` — Array of structs descriptors that can be used in bindings.
- L69 _private member_ `TArray<FSmartObjectDefinitionPropertyBinding> PropertyBindings;` — `UPROPERTY(VisibleAnywhere, Category = "SmartObject")` — Array of property bindings, resolved into arrays of copies before use.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API SMARTOBJECTSMODULE_API`

### `Plugins/Runtime/SmartObjects/Source/SmartObjectsModule/Public/SmartObjectBlueprintFunctionLibrary.h` (Public)


#### class `USmartObjectBlueprintFunctionLibrary`  
`class USmartObjectBlueprintFunctionLibrary : public UBlueprintFunctionLibrary`  
_L19-321_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "SmartObjectLibrary"))`
- inherits: `UBlueprintFunctionLibrary`
- L24 _public prototype_ `static FSmartObjectClaimHandle GetValueAsSOClaimHandle(UBlackboardComponent* BlackboardComponent, const FName& KeyName);` — `UFUNCTION(BlueprintCallable, Category = "SmartObject", meta=(ReturnDisplayName="Claim Handle"))`
- L27 _public prototype_ `static void SetValueAsSOClaimHandle(UBlackboardComponent* BlackboardComponent, const FName& KeyName, FSmartObjectClaimHandle Value);` — `UFUNCTION(BlueprintCallable, Category = "SmartObject")`
- L30 _public function_ `static bool IsValidSmartObjectClaimHandle(const FSmartObjectClaimHandle Handle)` — `UFUNCTION(BlueprintCallable, Category = "SmartObject", meta=(DisplayName="Is Valid (Smart Object Claim Handle)", ReturnDisplayName="Is Valid"))`
- L34 _public prototype_ `static FSmartObjectClaimHandle SmartObjectClaimHandle_Invalid();` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "SmartObject", meta=(ReturnDisplayName="Invalid Claim Handle"))` — Returns the invalid smart object claim handle.
- L47 _public prototype_ `static bool AddOrRemoveSmartObject(UPARAM(DisplayName = "SmartObjectActor") AActor* SmartObject, UPARAM(DisplayName = "bAdd") c` — `UFUNCTION(BlueprintCallable, Category = "SmartObject", meta=(ReturnDisplayName="bSuccess"))` — Adds to the simulation all smart objects for an actor or removes them according to 'bAdd'. @param SmartObjectActor The actor containing the smart objects to add or remove from the simulation @param bAdd Whether the smart objects should be added or removed from the simulation @return True if the requested operation succeeded; false otherwise @note Removing a smart object from the simulation will interrupt all active interactions. If you simply need to make the object unavailable for queries consider using one of the SetSmartObjectEnabled functions so active interactions can be gracefully completed. @see SetSmartObjectEnabled, SetMultipleSmartObjectsEnabled
- L60 _public prototype_ `static bool AddOrRemoveMultipleSmartObjects(const TArray<AActor*>& SmartObjectActors, const bool bAdd);` — `UFUNCTION(BlueprintCallable, Category = "SmartObject", meta=(ReturnDisplayName="bSuccess"))` — Adds to the simulation all smart objects for multiple actors or removes them according to 'bAdd'. @param SmartObjectActors The actors containing the smart objects to add or remove from the simulation @param bAdd Whether the smart objects should be added or removed from the simulation @return True if all actors were valid and the requested operation succeeded; false otherwise @note Removing a smart object from the simulation will interrupt all active interactions. If you simply need to make the object unavailable for queries consider using one of the SetSmartObjectEnabled functions so active interactions can be gracefully completed. @see SetSmartObjectEnabled, SetMultipleSmartObjectsEnabled
- L68 _public prototype_ `static bool AddSmartObject(AActor* SmartObjectActor);` — `UFUNCTION(BlueprintCallable, Category = "SmartObject", meta=(ReturnDisplayName="bSuccess"))` — Adds to the simulation all smart objects for an actor. @param SmartObjectActor The actor containing the smart objects to add to the simulation @return True if the requested operation succeeded; false otherwise
- L76 _public prototype_ `static bool AddMultipleSmartObjects(const TArray<AActor*>& SmartObjectActors);` — `UFUNCTION(BlueprintCallable, Category = "SmartObject", meta=(ReturnDisplayName="bSuccess"))` — Adds to the simulation all smart objects for multiple actors. @param SmartObjectActors The actors containing the smart objects to add to the simulation @return True if the requested operation succeeded; false otherwise
- L88 _public prototype_ `static bool RemoveSmartObject(AActor* SmartObjectActor);` — `UFUNCTION(BlueprintCallable, Category = "SmartObject", meta=(ReturnDisplayName="bSuccess"))` — Removes from the simulation all smart objects for an actor. @param SmartObjectActor The actor containing the smart objects to add or remove from the simulation @return True if the requested operation succeeded; false otherwise @note Removing a smart object from the simulation will interrupt all active interactions. If you simply need to make the object unavailable for queries consider using one of the SetSmartObjectEnabled functions so active interactions can be gracefully completed. @see SetSmartObjectEnabled, SetMultipleSmartObjectsEnabled
- L100 _public prototype_ `static bool RemoveMultipleSmartObjects(const TArray<AActor*>& SmartObjectActors);` — `UFUNCTION(BlueprintCallable, Category = "SmartObject", meta=(ReturnDisplayName="bSuccess"))` — Removes from the simulation all smart objects for multiple actors. @param SmartObjectActors The actors containing the smart objects to remove from the simulation @return True if the requested operation succeeded; false otherwise @note Removing a smart object from the simulation will interrupt all active interactions. If you simply need to make the object unavailable for queries consider using one of the SetSmartObjectEnabled functions so active interactions can be gracefully completed. @see SetSmartObjectEnabled, SetMultipleSmartObjectsEnabled
- L114 _public prototype_ `static bool SetSmartObjectEnabled(AActor* SmartObjectActor, const bool bEnabled);` — `UFUNCTION(BlueprintCallable, Category = "SmartObject", meta=(ReturnDisplayName="bSuccess"))` — Marks all smart objects for an actor as enabled or not according to 'bEnabled'. A smart object marked as Enabled is available for queries. @param SmartObjectActor The actor containing the smart objects to enable/disable @param bEnabled Whether the smart objects should be enabled or not @return True if the requested operation succeeded; false otherwise @note Disabling a smart object will not interrupt active interactions, it will simply mark the object unavailable for new queries and broadcast an event that can be handled by the interacting agent to complete earlier. If the object should not be consider usable anymore and the interactions aborted then consider using one of the Add/RemoveSmartObject functions. @see AddOrRemoveSmartObject, AddOrRemoveMultipleSmartObjects, AddSmartObject, AddMultipleSmartObjects, RemoveSmartObject, RemoveMultipleSmartObjects
- L125 _public prototype_ `static FSmartObjectClaimHandle MarkSmartObjectSlotAsClaimed(UObject* WorldContextObject, const FSmartObjectSlotHandle SlotHandle, const AActor* UserActor = nullptr, ESmartObjectClaimPriority ClaimPriority = ESmartObjectClaimPriority::Normal);` — `UFUNCTION(BlueprintCallable, Category = "SmartObject", meta = (WorldContext = "WorldContextObject", ReturnDisplayName="Claim Handle"))` — Marks a smart object slot from a request result as claimed. @param WorldContextObject Object used to fetch the SmartObjectSubsystem of its associated world. @param SlotHandle Handle to a smart object slot. @param UserActor Actor claiming the smart object @param ClaimPriority Claim priority, a slot claimed at lower priority can be claimed by higher priority (unless already in use). @return A handle binding the claimed smart object, its slot and a user id.
- L135 _public prototype_ `static const USmartObjectBehaviorDefinition* MarkSmartObjectSlotAsOccupied(UObject* WorldContextObject, const FSmartObjectClaimHandle ClaimHandle, TSubclassOf<USmartObjectBehaviorDefinition> DefinitionClass);` — `UFUNCTION(BlueprintCallable, Category = "SmartObject", meta = (WorldContext = "WorldContextObject"))` — Marks a previously claimed smart object slot as occupied. @param WorldContextObject Object used to fetch the SmartObjectSubsystem of its associated world. @param ClaimHandle Handle to a claimed slot returned by any of the Claim methods. @param DefinitionClass The type of behavior definition the user wants to use. @return The base class pointer of the requested behavior definition class associated to the slot
- L144 _public prototype_ `static bool MarkSmartObjectSlotAsFree(UObject* WorldContextObject, const FSmartObjectClaimHandle ClaimHandle);` — `UFUNCTION(BlueprintCallable, Category = "SmartObject", meta = (WorldContext = "WorldContextObject", ReturnDisplayName="bSuccess"))` — Marks a claimed or occupied smart object as free. @param WorldContextObject Object used to fetch the SmartObjectSubsystem of its associated world. @param ClaimHandle Handle to a claimed slot returned by any of the Claim methods. @return Whether the claim was successfully released or not
- L157 _public prototype_ `static bool FindSmartObjectsInComponent(const FSmartObjectRequestFilter& Filter, USmartObjectComponent* SmartObjectComponent, TArray<FSmartObjectRequestResult>& OutResults, const AActor* UserActor = nullptr);` — `UFUNCTION(BlueprintCallable, BlueprintPure = False, Category = "SmartObject", Meta = (ReturnDisplayName = "bSuccess"))` — Search a given Smart Object Component for slot candidates respecting the request criteria and selection conditions. @param Filter Parameters defining the search area and criteria @param SmartObjectComponent The component to search @param OutResults List of smart object slot candidates found in range @param UserActor  Used to create additional data that could be provided to bind values in the conditions evaluation context @return True if at least one candidate was found.
- L170 _public prototype_ `static bool FindSmartObjectsInActor(const FSmartObjectRequestFilter& Filter, AActor* SearchActor, TArray<FSmartObjectRequestResult>& OutResults, const AActor* UserActor = nullptr);` — `UFUNCTION(BlueprintCallable, BlueprintPure = False, Category = "SmartObject", Meta = (ReturnDisplayName = "bSuccess"))` — Search a given Actor for slot candidates respecting the request criteria and selection conditions. @param Filter Parameters defining the search area and criteria @param SearchActor The actor to search @param OutResults List of smart object slot candidates found in range @param UserActor  Used to create additional data that could be provided to bind values in the conditions evaluation context @return True if at least one candidate was found.
- L184 _public prototype_ `static bool FindSmartObjectsInTargetingRequest(UObject* WorldContextObject, const FSmartObjectRequestFilter& Filter, const FTargetingRequestHandle TargetingHandle, TArray<FSmartObjectRequestResult>& OutResults, const AActor* UserActor = nullptr);` — `UFUNCTION(BlueprintCallable, BlueprintPure = False, Category = "SmartObject", Meta = (WorldContext="WorldContextObject", ReturnDisplayName = "bSuccess"))` — Search the results of the given targeting handle request for smart objects that match the request criteria @param WorldContextObject Object used to fetch the SmartObjectSubsystem of its associated world. @param Filter Parameters defining the search area and criteria @param TargetingHandle The targeting handle of the request that will have its results searched for smart objects @param OutResults List of smart object slot candidates found in range @param UserActor Used to create additional data that could be provided to bind values in the conditions evaluation context @return True if at least one candidate was found.
- L198 _public prototype_ `static bool FindSmartObjectsInList(UObject* WorldContextObject, const FSmartObjectRequestFilter& Filter, const TArray<AActor*>& ActorList, TArray<FSmartObjectRequestResult>& OutResults, const AActor* UserActor = nullptr);` — `UFUNCTION(BlueprintCallable, BlueprintPure = False, Category = "SmartObject", Meta = (WorldContext="WorldContextObject", ReturnDisplayName = "bSuccess"))` — Search list of specific actors (often from a physics query) for slot candidates respecting request criteria and selection conditions. @param WorldContextObject Object used to fetch the SmartObjectSubsystem of its associated world. @param Filter Parameters defining the search area and criteria @param ActorList Ordered list of actors to search @param OutResults List of smart object slot candidates found in range @param UserData Additional data that could be provided to bind values in the conditions evaluation context @return True if at least one candidate was found.
- L202 _public prototype_ `static FString Conv_SmartObjectClaimHandleToString(const FSmartObjectClaimHandle& Result);` — `UFUNCTION(BlueprintPure, Category = "Utilities|String", meta = (DisplayName = "To String (SmartObjectClaimHandle)", CompactNodeTitle = "->", BlueprintAutocast))` — Converts a SmartObjectClaimHandle value to a string
- L206 _public prototype_ `static FString Conv_SmartObjectRequestResultToString(const FSmartObjectRequestResult& Result);` — `UFUNCTION(BlueprintPure, Category = "Utilities|String", meta = (DisplayName = "To String (SmartObjectRequestResult)", CompactNodeTitle = "->", BlueprintAutocast))` — Converts a SmartObjectRequestResult value to a string
- L210 _public prototype_ `static FString Conv_SmartObjectDefinitionToString(const USmartObjectDefinition* Definition);` — `UFUNCTION(BlueprintPure, Category = "Utilities|String", meta = (DisplayName = "To String (SmartObjectDefinition)", CompactNodeTitle = "->", BlueprintAutocast))` — Converts a SmartObjectDefinition value to a string
- L218 _public prototype_ `static FString Conv_SmartObjectHandleToString(const FSmartObjectHandle& Handle);` — `UFUNCTION(BlueprintPure, Category = "Utilities|String", meta = (DisplayName = "To String (SmartObjectHandle)", CompactNodeTitle = "->", BlueprintAutocast))` — Converts a SmartObjectHandle value to a string
- L222 _public prototype_ `static bool NotEqual_SmartObjectHandleSmartObjectHandle(const FSmartObjectHandle& A, const FSmartObjectHandle& B);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "Not Equal (SmartObjectHandle)", CompactNodeTitle = "!=", ScriptMethod = "NotEqual", ScriptOperator = "!=", Keywords = "!= not equal"), Category = "SmartObjects")` — Returns true if SmartObjectHandle A is NOT equal to SmartObjectHandle B (A != B)
- L226 _public prototype_ `static bool Equal_SmartObjectHandleSmartObjectHandle(const FSmartObjectHandle& A, const FSmartObjectHandle& B);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "Equal (SmartObjectHandle)", CompactNodeTitle = "==", ScriptMethod = "Equals", ScriptOperator = "==", Keywords = "== equal"), Category = "SmartObjects")` — Returns true if SmartObjectHandle A is equal to SmartObjectHandle B (A == B)
- L230 _public prototype_ `static bool IsValidSmartObjectHandle(const FSmartObjectHandle& Handle);` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category="SmartObjects", meta=(DisplayName="Is Valid (Smart Object Handle)", ReturnDisplayName = "Is Valid"))` — Returns true if the given handle is valid
- L238 _public prototype_ `static FString Conv_SmartObjectSlotHandleToString(const FSmartObjectSlotHandle& Handle);` — `UFUNCTION(BlueprintPure, Category = "Utilities|String", meta = (DisplayName = "To String (SmartObjectSlotHandle)", CompactNodeTitle = "->", BlueprintAutocast))` — Converts a SmartObjectSlotHandle value to a string
- L242 _public prototype_ `static bool Equal_SmartObjectSlotHandleSmartObjectSlotHandle(const FSmartObjectSlotHandle& A, const FSmartObjectSlotHandle& B);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "Equal (SmartObjectSlotHandle)", CompactNodeTitle = "==", ScriptMethod = "Equals", ScriptOperator = "==", Keywords = "== equal"), Category = "SmartObjects")` — Returns true if SmartObjectSlotHandle A is equal to SmartObjectSlotHandle B (A == B)
- L246 _public prototype_ `static bool NotEqual_SmartObjectSlotHandleSmartObjectSlotHandle(const FSmartObjectSlotHandle& A, const FSmartObjectSlotHandle& B);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "Not Equal (SmartObjectSlotHandle)", CompactNodeTitle = "!=", ScriptMethod = "NotEqual", ScriptOperator = "!=", Keywords = "!= not equal"), Category = "SmartObjects")` — Returns true if SmartObjectSlotHandle A is NOT equal to SmartObjectSlotHandle B (A != B)
- L250 _public prototype_ `static bool IsValidSmartObjectSlotHandle(const FSmartObjectSlotHandle& Handle);` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category="SmartObjects", meta=(DisplayName="Is Valid (Smart Object Slot Handle)", ReturnDisplayName = "Is Valid"))` — Returns true if the given Smart Object Slot Handle is valid.
- L264 _public prototype_ `static bool SetMultipleSmartObjectsEnabled(const TArray<AActor*>& SmartObjectActors, const bool bEnabled);` — `UFUNCTION(BlueprintCallable, Category = "SmartObject", meta = (DisplayName = "SetMultipleSmartObjectsEnabled", ReturnDisplayName="bSuccess"))` — Marks all smart objects for a list of actors as enabled or not according to 'bEnabled'. A smart object marked as Enabled is available for queries. @param SmartObjectActors The actors containing the smart objects to enable/disable @param bEnabled Whether the smart objects should be in the simulation (added) or not (removed) @return True if all actors were valid and the requested operation succeeded; false otherwise @note Disabling a smart object will not interrupt active interactions, it will simply mark the object unavailable for new queries and broadcast an event that can be handled by the interacting agent to complete earlier. If the object should not be consider usable anymore and the interactions aborted then consider using one of the Add/RemoveSmartObject functions. @see AddOrRemoveSmartObject, AddOrRemoveMultipleSmartObjects, AddSmartObject, AddMultipleSmartObjects, RemoveSmartObject, RemoveMultipleSmartObjects
- L274 _public prototype_ `static int32 GetNumSlotEntrances(const USmartObjectDefinition* Definition, int32 SlotIndex);` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "SmartObject", meta = (DisplayName = "Get Num Slot Entrances", ReturnDisplayName = "Count", Keywords = "entrance entry count number"))` — Returns the number of entrance annotations on a slot. Use this to iterate entrances with GetSlotEntranceOffsetAndRotation. @param Definition The smart object definition to query @param SlotIndex Index of the slot to query @return The number of entrance annotations on the slot, or 0 if the definition or slot is invalid
- L286 _public prototype_ `static bool GetSlotEntranceOffsetAndRotation(const USmartObjectDefinition* Definition, int32 SlotIndex, int32 EntranceIndex, FVector& OutOffset, FRotator& OutRotation);` — `UFUNCTION(BlueprintCallable, Category = "SmartObject", meta = (DisplayName = "Get Slot Entrance Offset and Rotation", ReturnDisplayName = "bFound", Keywords = "entrance entry offset rotation approach navigation"))` — Returns the entrance offset and rotation for a specific entrance annotation on a slot. @param Definition The smart object definition to query @param SlotIndex Index of the slot to query @param EntranceIndex Index of the entrance annotation within the slot (0 for first entrance) @param OutOffset The local space offset of the entrance @param OutRotation The local space rotation of the entrance @return True if the entrance annotation was found at the given indices
- L298 _public prototype_ `static bool GetSlotEntranceTransform(const USmartObjectDefinition* Definition, int32 SlotIndex, int32 EntranceIndex, FTransform& OutTransform);` — `UFUNCTION(BlueprintCallable, Category = "SmartObject", meta = (DisplayName = "Get Slot Entrance Transform", ReturnDisplayName = "bFound", Keywords = "entrance entry transform offset rotation approach navigation"))` — Returns the entrance transform (offset and rotation combined) for a specific entrance annotation on a slot. This is equivalent to GetSlotEntranceOffsetAndRotation but returns the result as a single FTransform. @param Definition The smart object definition to query @param SlotIndex Index of the slot to query @param EntranceIndex Index of the entrance annotation within the slot (0 for first entrance) @param OutTransform The local space transform of the entrance (translation from Offset, rotation from Rotation, unit scale) @return True if the entrance annotation was found at the given indices
- L312 _public prototype_ `static bool GetSlotDefinitionDataByType(const USmartObjectDefinition* Definition, int32 SlotIndex, TArray<int32>& OutDefinitionData);` — `UFUNCTION(BlueprintCallable, CustomThunk, Category = "SmartObject", meta = (ArrayParm = "OutDefinitionData", DisplayName = "Get Slot Definition Data By Type", ReturnDisplayName = "bFound", Keywords = "definition data filter annotation slot struct type"))` — Returns all definition data entries of a specific struct type from a slot's DefinitionData. Set the output pin to the desired struct type (must inherit from FSmartObjectDefinitionData) to filter results. The returned array contains copies of all matching entries, safe for Blueprint read access. @note If the output type is a base class and the actual data is a derived type, only the base class fields will be copied (struct slicing). Use the most specific type you need for complete data. @param Definition The smart object definition to query @param SlotIndex Index of the slot to query @param OutDefinitionData Output array of matching definition data structs (type determined by pin connection) @return True if at least one matching entry was found
- L317 _public prototype_ `static void SetBlackboardValueAsSOClaimHandle(UBTNode* NodeOwner, const FBlackboardKeySelector& Key, const FSmartObjectClaimHandle& Value);` — `UFUNCTION(BlueprintCallable, Category = "AI|BehaviorTree", meta = (HidePin = "NodeOwner", DefaultToSelf = "NodeOwner", DisplayName = "Set Blackboard Value As Smart Object Claim Handle"))`
- L320 _public prototype_ `static FSmartObjectClaimHandle GetBlackboardValueAsSOClaimHandle(UBTNode* NodeOwner, const FBlackboardKeySelector& Key);` — `UFUNCTION(BlueprintPure, Category = "AI|BehaviorTree", meta = (HidePin = "NodeOwner", DefaultToSelf = "NodeOwner", DisplayName = "Get Blackboard Value As Smart Object Claim Handle"))`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SMARTOBJECTSMODULE_API`

### `Plugins/Runtime/SmartObjects/Source/SmartObjectsModule/Public/SmartObjectCollection.h` (Public)


#### class `ADEPRECATED_SmartObjectCollection`  
`class ADEPRECATED_SmartObjectCollection : public AActor`  
_L16-59_
- reflection: `UCLASS(MinimalAPI, Deprecated, NotBlueprintable, hidecategories = (Rendering, Replication, Collision, Input, HLOD, Actor, LOD, Cooking, WorldPartition), notplaceable, meta = (DeprecationMessage = "SmartObjectCollection class is deprecated. Please use SmartObjectPersistentCollection instead."))`
- inherits: `AActor`
- desc: Actor holding smart object persistent data
- L23 _protected prototype_ `explicit ADEPRECATED_SmartObjectCollection(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L25 _protected prototype_ `virtual void PostLoad() override;`
- L28 _protected prototype_ `void ClearCollection();` — Removes all entries from the collection.
- L31 _protected member_ `FBox Bounds = FBox(ForceInitToZero);` — `UPROPERTY(VisibleAnywhere, Category = SmartObject)`
- L34 _protected member_ `TArray<FSmartObjectCollectionEntry> CollectionEntries;` — `UPROPERTY(VisibleAnywhere, Category = SmartObject)`
- L37 _protected member_ `TMap<FSmartObjectHandle, FSoftObjectPath> RegisteredIdToObjectMap;` — `UPROPERTY()`
- L40 _protected member_ `TArray<TObjectPtr<const USmartObjectDefinition>> Definitions;` — `UPROPERTY(VisibleAnywhere, Category = SmartObject)`
- L42 _protected member_ `bool bRegistered = false;`
- L48 _private member_ `bool bBuildOnDemand_DEPRECATED = true;` — `UPROPERTY()` — This property used to be exposed to the UI editor. It was replaced with bBuildCollectionAutomatically for greater readability.
- L52 _protected member_ `bool bIgnoreLevelTesting = false;` — if set to true will result in letting the level-less SmartObjects to register. Required for smart object unit testing.
- L55 _protected member_ `bool bBuildCollectionAutomatically = false;` — `UPROPERTY(VisibleAnywhere, Category = SmartObject, AdvancedDisplay)`
- L57 _protected member_ `bool bBuildingForWorldPartition = false;`

### `Plugins/Runtime/SmartObjects/Source/SmartObjectsModule/Public/SmartObjectComponent.h` (Public)


#### enum `ESmartObjectRegistrationType`  
`enum class ESmartObjectRegistrationType : uint8`  
_L23-40_
- L26 _public enumerator_ `NotRegistered` — Not registered yet
- L33 _public enumerator_ `BindToExistingInstance` — Registered and bound to a SmartObject already created from a persistent collection entry or from method CreateSmartObject. Lifetime of the SmartObject is not bound to the component unregistration but by method UnregisterCollection in the case of a collection entry or by method DestroySmartObject when CreateSmartObject was used.
- L39 _public enumerator_ `Dynamic` — Component is registered and bound to a newly created SmartObject. The lifetime of the SmartObject is bound to the component unregistration will be unbound/destroyed by UnregisterSmartObject/RemoveSmartObject.

#### enum `ESmartObjectUnregistrationType`  
`enum class ESmartObjectUnregistrationType : uint8`  
_L42-51_
- L48 _public enumerator_ `RegularProcess` — Component bound to an existing instance (BindToExistingInstance) will be unbound from the simulation but its associated runtime data will persist. Otherwise (Dynamic), runtime data will also be destroyed.
- L50 _public enumerator_ `ForceRemove` — Component will be unbound from the simulation and its runtime data will be destroyed regardless of the registration type

#### class `USmartObjectComponent`  
`class USmartObjectComponent : public USceneComponent`  
_L54-285_
- reflection: `UCLASS(MinimalAPI, Blueprintable, ClassGroup = Gameplay, meta = (BlueprintSpawnableComponent), config = Game, HideCategories = (Activation, AssetUserData, Collision, Cooking, HLOD, Lighting, LOD, Mobile, Mobility, Navigation, Physics, RayTracing, Rendering, Tags, TextureStreaming))`
- inherits: `USceneComponent`
- L59 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSmartObjectComponentChanged, TNotNull<const USmartObjectComponent*> );`
- L61 _public prototype_ `explicit USmartObjectComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L63 _public prototype_ `FBox GetSmartObjectBounds() const;`
- L67 _public prototype_ `const USmartObjectDefinition* GetDefinition() const;` — `UFUNCTION(BlueprintGetter)` — @return Smart Object Definition with parameters applied.
- L70 _public prototype_ `const USmartObjectDefinition* GetBaseDefinition() const;` — @return Smart Object Definition without applied parameters.
- L74 _public prototype_ `void SetDefinition(USmartObjectDefinition* DefinitionAsset);` — `UFUNCTION(BlueprintSetter)` — Sets the Smart Object Definition.
- L76 _public function_ `bool GetCanBePartOfCollection() const`
- L81 _public function_ `ESmartObjectRegistrationType GetRegistrationType() const`
- L86 _public function_ `FSmartObjectHandle GetRegisteredHandle() const`
- L91 _public prototype_ `void SetRegisteredHandle(const FSmartObjectHandle Value, const ESmartObjectRegistrationType InRegistrationType);`
- L92 _public prototype_ `void InvalidateRegisteredHandle();`
- L94 _public prototype_ `void OnRuntimeInstanceBound(FSmartObjectRuntime& RuntimeInstance);`
- L95 _public prototype_ `void OnRuntimeInstanceUnbound(FSmartObjectRuntime& RuntimeInstance);`
- L103 _public prototype_ `bool SetSmartObjectEnabled(const bool bEnable) const;` — `UE_DEPRECATED(5.8, "Use other version that is not blueprint pure.")` — `UFUNCTION(BlueprintCallable, Category = "SmartObject", meta=(DisplayName="Set SmartObject Enabled (default reason: Gameplay)", ReturnDisplayName="Status changed", DeprecatedFunction="Note", DeprecationMessage="Use version that is not blueprint pure"))` — Enables or disables the smart object using the default reason (i.e. Gameplay). @return false if it was not possible to change the enabled state (i.e. if it's not registered or there is no smart object subsystem).
- L110 _public prototype_ `virtual bool K2_SetSmartObjectEnabled(const bool bEnable) const;` — `UFUNCTION(BlueprintCallable, Category = "SmartObject", BlueprintPure=false, meta=(DisplayName="Set SmartObject Enabled (default reason: Gameplay)", ReturnDisplayName="Status changed"))` — Enables or disables the smart object using the default reason (i.e. Gameplay). @return false if it was not possible to change the enabled state (i.e. if it's not registered or there is no smart object subsystem).
- L120 _public prototype_ `bool SetSmartObjectEnabledForReason(FGameplayTag ReasonTag, const bool bEnabled) const;` — `UE_DEPRECATED(5.8, "Use other version that is not blueprint pure.")` — `UFUNCTION(BlueprintCallable, Category = "SmartObject", meta=(DisplayName="Set SmartObject Enabled (specific reason)", ReturnDisplayName="Status changed", DeprecatedFunction="Note", DeprecationMessage="Use version that is not blueprint pure"))` — Enables or disables the smart object for the specified reason. @param ReasonTag Valid Tag to specify the reason for changing the enabled state of the object. Method will ensure if not valid (i.e. None). @param bEnabled If true enables the smart object, disables otherwise. @return false if it was not possible to change the enabled state (i.e. if it's not registered or there is no smart object subsystem).
- L129 _public prototype_ `bool K2_SetSmartObjectEnabledForReason(FGameplayTag ReasonTag, const bool bEnabled) const;` — `UFUNCTION(BlueprintCallable, Category = "SmartObject", BlueprintPure=false , meta=(DisplayName="Set SmartObject Enabled (specific reason)", ReturnDisplayName="Status changed"))` — Enables or disables the smart object for the specified reason. @param ReasonTag Valid Tag to specify the reason for changing the enabled state of the object. Method will ensure if not valid (i.e. None). @param bEnabled If true enables the smart object, disables otherwise. @return false if it was not possible to change the enabled state (i.e. if it's not registered or there is no smart object subsystem).
- L136 _public prototype_ `bool IsSmartObjectEnabled() const;` — `UFUNCTION(BlueprintCallable, Category = "SmartObject", meta=(DisplayName="Is SmartObject Enabled (for any reason)", ReturnDisplayName="Enabled"))` — Returns the enabled state of the smart object regardless of the disabled reason. @return True when associated smart object is set to be enabled. False otherwise.
- L144 _public prototype_ `bool IsSmartObjectEnabledForReason(FGameplayTag ReasonTag) const;` — `UFUNCTION(BlueprintCallable, Category = "SmartObject", meta=(DisplayName="Is SmartObject Enabled (for specific reason)", ReturnDisplayName="Enabled"))` — Returns the enabled state of the smart object based on a specific reason. @param ReasonTag Valid Tag to test if enabled for a specific reason. Method will ensure if not valid (i.e. None). @return True when associated smart object is set to be enabled. False otherwise.
- L146 _public function_ `FSmartObjectComponentEventNativeSignature& GetOnSmartObjectEventNative()`
- L153 _public function_ `bool IsBoundToSimulation() const` — `UFUNCTION(BlueprintCallable, Category = "SmartObject")` — Returns true if the Smart Object component is registered to the Smart Object subsystem. Depending on the update order, sometimes it is possible that the subsystem gets enabled after the component.
- L160 _public function_ `void ValidateGUIDForDeprecation()` — Conditionally updates the GUID if it was never set. Used for collection deprecation only.
- L165 _public function_ `static FOnSmartObjectComponentChanged& GetOnSmartObjectComponentChanged()`
- L171 _public function_ `const FSmartObjectDefinitionReference& GetDefinitionReference() const`
- L177 _public function_ `FSmartObjectDefinitionReference& GetMutableDefinitionReference()`
- L182 _public prototype_ `virtual void GetActorDescProperties(FPropertyPairsMap& PropertyPairsMap) const override;`
- L186 _public function_ `[[nodiscard]] FGuid GetComponentGuid() const` — Returns this component Guid
- L193 _protected prototype_ `virtual TStructOnScope<FActorComponentInstanceData> GetComponentInstanceData() const override;`
- L195 _protected prototype_ `virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;`
- L197 _protected prototype_ `void OnRuntimeEventReceived(const FSmartObjectEventData& Event);`
- L200 _protected member_ `FSmartObjectComponentEventSignature OnSmartObjectEvent;` — `UPROPERTY(BlueprintAssignable, Category = SmartObject, meta=(DisplayName = "OnSmartObjectEvent"))`
- L203 _protected member_ `FSmartObjectComponentEventNativeSignature OnSmartObjectEventNative;` — Native version of OnSmartObjectEvent.
- L206 _protected prototype_ `void ReceiveOnEvent(const FSmartObjectEventData& EventData, const AActor* Interactor);` — `UFUNCTION(BlueprintImplementableEvent, Category = SmartObject, meta=(DisplayName = "OnSmartObjectEventReceived"))`
- L208 _protected prototype_ `virtual void PostDuplicate(EDuplicateMode::Type DuplicateMode) override;`
- L209 _protected prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L211 _protected prototype_ `virtual void OnRegister() override;`
- L213 _protected prototype_ `virtual void BeginPlay() override;`
- L214 _protected prototype_ `virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;`
- L217 _protected prototype_ `virtual void OnUnregister() override;`
- L219 _protected prototype_ `virtual void PostEditImport() override;`
- L220 _protected prototype_ `virtual void PostEditUndo() override;`
- L221 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L222 _protected prototype_ `virtual void PreSave(FObjectPreSaveContext SaveContext) override;`
- L225 _protected prototype_ `void RegisterToSubsystem();`
- L226 _protected prototype_ `void UnregisterFromSubsystem(const ESmartObjectUnregistrationType UnregistrationType);`
- L230 _protected member_ `FGuid ComponentGuid;` — `UPROPERTY(VisibleAnywhere, Category = SmartObject)` — Unique ID used, along with the owner's ActorGuid to generate a SmartObjectHandle
- L234 _protected member_ `FSmartObjectDefinitionReference DefinitionRef;` — `UPROPERTY(EditAnywhere, Category = SmartObject, Replicated, meta = (DisplayName="Definition"))` — Reference to Smart Object Definition Asset with parameters.
- L238 _protected member_ `FSmartObjectHandle RegisteredHandle;` — `UPROPERTY(Transient, VisibleAnywhere, Category = SmartObject, BlueprintReadOnly, Replicated)` — RegisteredHandle != FSmartObjectHandle::Invalid when registered into a collection by SmartObjectSubsystem
- L240 _protected member_ `FDelegateHandle EventDelegateHandle;`
- L242 _protected member_ `ESmartObjectRegistrationType RegistrationType = ESmartObjectRegistrationType::NotRegistered;`
- L251 _protected member_ `bool bCanBePartOfCollection = false;` — `UPROPERTY(config, EditAnywhere, Category = SmartObject, AdvancedDisplay)` — Controls whether a given SmartObject can be aggregated in SmartObjectPersistentCollections. SOs in collections can be queried and reasoned about even while the actual Actor and its components are not streamed in. By default SmartObjects are not placed in collections and are active only as long as the owner-actor remains loaded and active (i.e. not streamed out).
- L254 _protected member_ `static FOnSmartObjectComponentChanged OnSmartObjectComponentChanged;`
- L259 _private prototype_ `void ValidateGUID();` — Conditionally updates the GUID if it was never set
- L262 _private prototype_ `void UpdateGUID();` — Assigns a new GUID to the component
- L267 _private member_ `mutable TObjectPtr<USmartObjectDefinition> CachedDefinitionAssetVariation = nullptr;` — `UPROPERTY(Transient, Category = SmartObject, BlueprintSetter = SetDefinition, BlueprintGetter = GetDefinition, meta = (DisplayName="Definition Asset"))`
- L270 _private member_ `FDelegateHandle OnSavingDefinitionDelegateHandle;`
- L273 _private prototype_ `bool ApplyDeprecation();` — return true if applied or false if already applied
- L276 _private prototype_ `bool ApplyParentDeprecation();` — return true if applied or  false if already applied
- L280 _private member_ `bool bDeprecationApplied = false;` — `UPROPERTY()` — flag to keep track of the deprecation status of the object
- L283 _private member_ `TObjectPtr<USmartObjectDefinition> DefinitionAsset_DEPRECATED;` — `UPROPERTY(Category = SmartObject, BlueprintSetter = SetDefinition, BlueprintGetter = GetDefinition, meta = (DeprecatedProperty, DisplayName="Deprecated Definition Asset", BlueprintPrivate))`

#### struct `FSmartObjectComponentInstanceData`  
`struct FSmartObjectComponentInstanceData : public FActorComponentInstanceData`  
_L290-318_
- reflection: `USTRUCT()`
- inherits: `FActorComponentInstanceData`
- desc: Used to store SmartObjectComponent data during RerunConstructionScripts
- L295 _public prototype_ `FSmartObjectComponentInstanceData() = default;`
- L297 _public function_ `explicit FSmartObjectComponentInstanceData(const TNotNull<const USmartObjectComponent*> SourceComponent) : FActorComponentInstanceData(SourceComponent) , SmartObjectDefinitionRef(SourceComponent->DefinitionRef) , OriginalGuid(SourceComponent->ComponentGuid)`
- L304 _public function_ `const FSmartObjectDefinitionReference& GetSmartObjectDefinitionReference() const`
- L310 _protected prototype_ `virtual bool ContainsData() const override;`
- L311 _protected prototype_ `virtual void ApplyToComponent(UActorComponent* Component, const ECacheApplyPhase CacheApplyPhase) override;`
- L314 _protected member_ `FSmartObjectDefinitionReference SmartObjectDefinitionRef;` — `UPROPERTY()`
- L317 _protected member_ `FGuid OriginalGuid;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API SMARTOBJECTSMODULE_API`
- L13 _namespace_ `namespace EEndPlayReason`
- L20 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSmartObjectComponentEventSignature, const FSmartObjectEventData&, EventData, const AActor*, Interactor);`
- L20 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSmartObjectComponentEventSignature, const FSmartObjectEventData&, EventData, const AActor*, Interactor);`
- L21 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FSmartObjectComponentEventNativeSignature, const FSmartObjectEventData& EventData, const AActor* Interactor);`
- L21 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FSmartObjectComponentEventNativeSignature, const FSmartObjectEventData& EventData, const AActor* Interactor);`
- L59 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSmartObjectComponentChanged, TNotNull<const USmartObjectComponent*> );`

### `Plugins/Runtime/SmartObjects/Source/SmartObjectsModule/Public/SmartObjectContainerRenderingComponent.h` (Public)


#### class `USmartObjectContainerRenderingComponent`  
`class USmartObjectContainerRenderingComponent : public UPrimitiveComponent`  
_L14-29_
- reflection: `UCLASS(MinimalAPI, hidecategories = (Object, LOD, Lighting, VirtualTexture, Transform, HLOD, Collision, TextureStreaming, Mobile, Physics, Tags, AssetUserData, Activation, Cooking, Rendering), editinlinenew, meta = (BlueprintSpawnableComponent))`
- inherits: `UPrimitiveComponent`
- L19 _public prototype_ `USmartObjectContainerRenderingComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L22 _public prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy() override;`
- L23 _public function_ `virtual bool ShouldRecreateProxyOnUpdateTransform() const override`
- L27 _public prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform &LocalToWorld) const override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SMARTOBJECTSMODULE_API`

### `Plugins/Runtime/SmartObjects/Source/SmartObjectsModule/Public/SmartObjectDebugRenderingComponent.h` (Public)


#### class `USmartObjectDebugRenderingComponent`  
`class USmartObjectDebugRenderingComponent : public UDebugDrawComponent`  
_L17-35_
- reflection: `UCLASS(MinimalAPI, ClassGroup = Debug, NotBlueprintable, NotPlaceable)`
- inherits: `UDebugDrawComponent`
- desc: Simple UDebugDrawComponent to inherit from to use a FSmartObjectDebugSceneProxy. Derived classes can set ViewFlagName at construction to control relevancy.
- L21 _public prototype_ `explicit USmartObjectDebugRenderingComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L25 _protected prototype_ `virtual void OnRegister() override;`
- L26 _protected prototype_ `virtual void OnUnregister() override;`
- L28 _protected prototype_ `virtual FDebugRenderSceneProxy* CreateDebugSceneProxy() override;`
- L29 _protected function_ `virtual void DebugDraw(FDebugRenderSceneProxy* DebugProxy)`
- L30 _protected function_ `virtual void DebugDrawCanvas(UCanvas* Canvas, APlayerController*)`
- L32 _protected member_ `FDelegateHandle CanvasDebugDrawDelegateHandle;`
- L33 _protected member_ `FString ViewFlagName;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SMARTOBJECTSMODULE_API`

### `Plugins/Runtime/SmartObjects/Source/SmartObjectsModule/Public/SmartObjectDebugSceneProxy.h` (Public)


#### class `FSmartObjectDebugSceneProxy`  
`class FSmartObjectDebugSceneProxy final : public FDebugRenderSceneProxy`  
_L13-23_
- inherits: `FDebugRenderSceneProxy`
- L16 _public prototype_ `explicit FSmartObjectDebugSceneProxy(const UPrimitiveComponent& InComponent, const EDrawType InDrawType = EDrawType::WireMesh, const TCHAR* InViewFlagName = nullptr);`
- L18 _public prototype_ `virtual FPrimitiveViewRelevance GetViewRelevance(const FSceneView* View) const override;`
- L19 _public prototype_ `virtual uint32 GetMemoryFootprint() const override;`
- L22 _private member_ `uint32 ViewFlagIndex = 0;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API SMARTOBJECTSMODULE_API`

### `Plugins/Runtime/SmartObjects/Source/SmartObjectsModule/Public/SmartObjectDefinition.h` (Public)


#### enum `ESmartObjectSlotShape`  
`enum class ESmartObjectSlotShape : uint8`  
_L55-59_
- reflection: `UENUM()`
- desc: Indicates how Tags from slots and parent object are combined to be evaluated by a TagQuery from a find request.
- L57 _public enumerator_ `Circle`
- L58 _public enumerator_ `Rectangle`

#### class `USmartObjectBehaviorDefinition`  
`class USmartObjectBehaviorDefinition : public UObject`  
_L66-69_
- reflection: `UCLASS(MinimalAPI, Abstract, NotBlueprintable, EditInlineNew, CollapseCategories, HideDropdown)`
- inherits: `UObject`
- desc: Abstract class that can be extended to bind a new type of behavior framework to the smart objects by defining the required definition.

#### struct `FSmartObjectDefinitionDataProxy`  
`struct FSmartObjectDefinitionDataProxy`  
_L73-97_
- reflection: `USTRUCT()`
- desc: Helper struct for definition data, which allows to identify items based on GUID in editor (even empty ones).
- L77 _public prototype_ `FSmartObjectDefinitionDataProxy() = default;`
- L80 _public function_ `template<typename T, typename = std::enable_if_t<std::is_base_of_v<FSmartObjectDefinitionData, std::decay_t<T>>>> static FSmartObjectDefinitionDataProxy Make(const T& Struct)`
- L91 _public member_ `TInstancedStruct<FSmartObjectDefinitionData> Data;` — `UPROPERTY(EditDefaultsOnly, Category = "Slot", meta = (ExcludeBaseStruct))`
- L95 _public member_ `FGuid ID;` — `UPROPERTY(EditDefaultsOnly, Category = "Slot", meta = (Hidden))`

#### struct `FSmartObjectSlotDefinition`  
`struct FSmartObjectSlotDefinition`  
_L103-226_
- reflection: `USTRUCT(BlueprintType)`
- desc: Persistent and sharable definition of a smart object slot.
- L109 _public prototype_ `FSmartObjectSlotDefinition() = default;` — Macro needed to avoid deprecation errors with "Data" being copied or created in the default methods
- L110 _public prototype_ `FSmartObjectSlotDefinition(const FSmartObjectSlotDefinition&) = default;`
- L111 _public prototype_ `FSmartObjectSlotDefinition(FSmartObjectSlotDefinition&&) = default;`
- L112 _public prototype_ `FSmartObjectSlotDefinition& operator=(const FSmartObjectSlotDefinition&) = default;`
- L113 _public prototype_ `FSmartObjectSlotDefinition& operator=(FSmartObjectSlotDefinition&&) = default;`
- L121 _public function_ `template<typename T> const T& GetDefinitionData() const` — Returns a reference to the definition data of the specified type. Method will fail a check if the slot definition doesn't contain the given type.
- L143 _public function_ `template<typename T> const T* GetDefinitionDataPtr() const` — Returns a pointer to the definition data of the specified type. Method will return null if the slot doesn't contain the given type.
- L162 _public member_ `FName Name;` — `UPROPERTY(EditDefaultsOnly, Category = "Slot")`
- L165 _public member_ `FColor DEBUG_DrawColor = FColor::Yellow;` — `UPROPERTY(EditAnywhere, Category = "Slot", meta = (DisplayName = "Color"))`
- L168 _public member_ `ESmartObjectSlotShape DEBUG_DrawShape = ESmartObjectSlotShape::Circle;` — `UPROPERTY(EditAnywhere, Category = "Slot", meta = (DisplayName = "Shape"))`
- L171 _public member_ `float DEBUG_DrawSize = 40.0f;` — `UPROPERTY(EditAnywhere, Category = "Slot", meta = (DisplayName = "Size"))`
- L174 _public member_ `FGuid ID;` — `UPROPERTY(EditAnywhere, Category = "Slot", meta = (Hidden))`
- L179 _public member_ `FVector3f Offset = FVector3f::ZeroVector;` — `UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Slot")` — Offset relative to the parent object where the slot is located.
- L183 _public member_ `FRotator3f Rotation = FRotator3f::ZeroRotator;` — `UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Slot")` — Rotation relative to the parent object.
- L187 _public member_ `bool bEnabled = true;` — `UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Slot")` — Whether the slot is enable initially.
- L191 _public member_ `FGameplayTagQuery UserTagFilter;` — `UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Slot")` — This slot is available only for users matching this query.
- L199 _public member_ `FGameplayTagContainer ActivityTags;` — `UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Slot")` — Tags identifying this slot's use case. Can be used while looking for slots supporting given activity. Depending on the tag filtering policy these tags can override the parent object's tags or be combined with them while applying filters from requests.
- L203 _public member_ `FGameplayTagContainer RuntimeTags;` — `UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Slot")` — Initial runtime tags.
- L207 _public member_ `FWorldConditionQueryDefinition SelectionPreconditions;` — `UPROPERTY(EditDefaultsOnly, Category = "Slot")` — Preconditions that must pass for the slot to be selected.
- L215 _public member_ `TArray<TObjectPtr<USmartObjectBehaviorDefinition>> BehaviorDefinitions;` — `UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Slot", Instanced)` — All available definitions associated to this slot. This allows multiple frameworks to provide their specific behavior definition to the slot. Note that there should be only one definition of each type since the first one will be selected.
- L219 _public member_ `TArray<FSmartObjectDefinitionDataProxy> DefinitionData;` — `UPROPERTY(EditDefaultsOnly, Category = "Slot")` — Custom definition data items (struct inheriting from SmartObjecDefinitionData) that can be added to the slot definition and accessed through a FSmartObjectSlotView
- L224 _public member_ `TArray<FInstancedStruct> Data_DEPRECATED;` — `UE_DEPRECATED(all, "Use DefinitionData instead.")` — `UPROPERTY()`

#### struct `FSmartObjectDefinitionPreviewData`  
`struct FSmartObjectDefinitionPreviewData`  
_L233-252_
- reflection: `USTRUCT(BlueprintType)`
- desc: Data used for previewing in the Smart Object editor.
- L239 _public member_ `TSoftClassPtr<AActor> ObjectActorClass;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Object Preview")` — Actor class used as the object for previewing the definition in the asset editor.
- L243 _public member_ `FSoftObjectPath ObjectMeshPath;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Object Preview", meta = (AllowedClasses = "/Script/Engine.StaticMesh"))` — Path of the static mesh used as the object for previewing the definition in the asset editor.
- L247 _public member_ `TSoftClassPtr<AActor> UserActorClass;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "User Preview")` — Actor class used for previewing the smart object user actor in the asset editor.
- L251 _public member_ `TSoftClassPtr<USmartObjectSlotValidationFilter> UserValidationFilterClass;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "User Preview")` — Validation filter used for previewing the smart object user in the asset editor.

#### class `USmartObjectDefinition`  
`class USmartObjectDefinition : public UDataAsset, public IPropertyBindingBindingCollectionOwner`  
_L258-653_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Blueprintable, CollapseCategories)`
- inherits: `UDataAsset,IPropertyBindingBindingCollectionOwner`
- desc: SmartObject definition asset. Contains sharable information that can be used by multiple SmartObject instances at runtime.
- L263 _public prototype_ `explicit USmartObjectDefinition(const FObjectInitializer& ObjectInitializer);`
- L274 _public prototype_ `const USmartObjectBehaviorDefinition* GetBehaviorDefinition(const int32 SlotIndex, const TSubclassOf<USmartObjectBehaviorDefinition>& DefinitionClass) const;` — Retrieves a specific type of behavior definition for a given slot. When the slot doesn't provide one or if the provided index is not valid the search will look in the object default definitions. @param SlotIndex			Index of the slot for which the definition is requested @param DefinitionClass	Type of the requested behavior definition @return The behavior definition found or null if none are available for the requested type.
- L277 _public function_ `const FWorldConditionQueryDefinition& GetPreconditions() const` — @return Preconditions that must pass for the object to be found/used.
- L280 _public function_ `FWorldConditionQueryDefinition& GetMutablePreconditions()` — @return mutable Preconditions that must pass for the object to be found/used.
- L283 _public function_ `TConstArrayView<FSmartObjectSlotDefinition> GetSlots() const` — @return a view on all the slot definitions
- L286 _public function_ `const FSmartObjectSlotDefinition& GetSlot(const int32 Index) const` — @return slot definition stored at a given index
- L290 _public function_ `FSmartObjectSlotDefinition& GetMutableSlot(const int32 Index)` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category="SmartObject")` — @return mutable slot definition stored at a given index
- L294 _public function_ `bool IsValidSlotIndex(const int32 SlotIndex) const` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category="SmartObject")` — @return True if specified slot index is valid.
- L297 _public function_ `const TArray<FSmartObjectSlotDefinition>& K2_GetSlots() const` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category="SmartObject", meta=(DisplayName="Get Smart Object Slot Definitions"))`
- L301 _public function_ `TArrayView<FSmartObjectSlotDefinition> GetMutableSlots()` — Returns a view on all the slot definitions
- L304 _public prototype_ `TSubclassOf<USmartObjectSlotValidationFilter> GetPreviewValidationFilterClass() const;` — @return validation filter class for preview.
- L307 _public prototype_ `int32 FindSlotByID(const FGuid ID) const;` — @return Index of the slot that has the specified ID, or INDEX_NONE if not found.
- L315 _public prototype_ `bool FindSlotAndDefinitionDataIndexByID(const FGuid ID, int32& OutSlotIndex, int32& OutDefinitionDataIndex) const;` — Returns slot and definition data indices the ID represents. @param ID ID of the slots or definition data to find @param OutSlotIndex Index of the slot the ID points to @param OutDefinitionDataIndex Index of the definition data the ID points to, or INDEX_NONE, if ID points directly to a slot. @return true if ID matches data in the definition.
- L317 _public prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;`
- L320 _public prototype_ `virtual void PostDuplicate(EDuplicateMode::Type DuplicateMode) override;`
- L324 _public prototype_ `FBox GetBounds() const;` — `UFUNCTION(BlueprintCallable, Category="SmartObject")` — Return bounds encapsulating all slots
- L327 _public function_ `FSmartObjectSlotDefinition& DebugAddSlot()` — Adds and returns a reference to a defaulted slot (used for testing purposes)
- L337 _public prototype_ `FTransform GetSlotWorldTransform(const int32 SlotIndex, const FTransform& OwnerTransform) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category="SmartObject")` — Returns the transform (in world space) of the given slot index. @param OwnerTransform Transform (in world space) of the slot owner. @param SlotIndex Index within the list of slots. @return Transform (in world space) of the slot associated to SlotIndex, or OwnerTransform if index is invalid. @note Method will ensure on invalid slot index.
- L345 _public prototype_ `void GetSlotActivityTags(const int32 SlotIndex, FGameplayTagContainer& OutActivityTags) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category="SmartObject", meta = (DisplayName="Get Slot Activity Tags (By Index)", ScriptName="GetSlotActivityTagsByIndex", AutoCreateRefTerm = "OutActivityTags"))` — Fills the provided GameplayTagContainer with the activity tags associated to the slot according to the tag merging policy. @param SlotIndex	Index of the slot for which the tags are requested @param OutActivityTags Tag container to fill with the activity tags associated to the slot
- L352 _public prototype_ `void GetSlotActivityTags(const FSmartObjectSlotDefinition& SlotDefinition, FGameplayTagContainer& OutActivityTags) const;` — Fills the provided GameplayTagContainer with the activity tags associated to the slot according to the tag merging policy. @param SlotDefinition Definition of the slot for which the tags are requested @param OutActivityTags Tag container to fill with the activity tags associated to the slot
- L356 _public function_ `const FGameplayTagQuery& GetUserTagFilter() const` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category="SmartObject")` — Returns the tag query to run on the user tags provided by a request to accept this definition
- L360 _public function_ `void SetUserTagFilter(const FGameplayTagQuery& InUserTagFilter)` — `UFUNCTION(BlueprintCallable, Category="SmartObject")` — Sets the tag query to run on the user tags provided by a request to accept this definition
- L364 _public function_ `const FGameplayTagContainer& GetActivityTags() const` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category="SmartObject")` — Returns the list of tags describing the activity associated to this definition
- L367 _public function_ `void SetActivityTags(const FGameplayTagContainer& InActivityTags)` — Sets the list of tags describing the activity associated to this definition
- L371 _public function_ `ESmartObjectTagFilteringPolicy GetUserTagsFilteringPolicy() const` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category="SmartObject")` — Returns the tag filtering policy that should be applied on User tags by this definition
- L374 _public function_ `void SetUserTagsFilteringPolicy(const ESmartObjectTagFilteringPolicy InUserTagsFilteringPolicy)` — Sets the tag filtering policy to apply on User tags by this definition
- L377 _public function_ `ESmartObjectTagMergingPolicy GetActivityTagsMergingPolicy() const` — Returns the tag merging policy to apply on Activity tags from this definition
- L380 _public function_ `void SetActivityTagsMergingPolicy(const ESmartObjectTagMergingPolicy InActivityTagsMergingPolicy)` — Sets the tag merging policy to apply on Activity tags from this definition
- L390 _public prototype_ `bool Validate(TArray<TPair<EMessageSeverity::Type, FText>>* ErrorsToReport = nullptr) const;` — Performs validation for the current definition. The method will return on the first error encountered by default but could go through all validations and report all errors (e.g. when saving the asset errors are reported to the user). An object using an invalid definition will not be registered in the simulation. The result of the validation is stored until next validation and can be retrieved using `IsDefinitionValid`. @param ErrorsToReport Optional list of error messages that could be provided to report them @return true if the definition is valid
- L410 _public function_ `bool HasBeenValidated() const` — Indicates if 'Validate' was called. Need to be called before calling 'IsDefinitionValid' to make the distinction between an invalid asset and one that hasn't been validated yet. @return true if 'Validate' was called, false otherwise @see Validate @see IsDefinitionValid
- L420 _public function_ `bool IsDefinitionValid() const` — Indicates the result of the last validation if 'Validate' was called. Need to call 'HasBeenValidated' before to make the distinction between an invalid asset and one that hasn't been validated yet. @returns result of the last validation if 'Validate' was called; false otherwise @see Validate @see HasBeenValidated
- L426 _public member_ `TSoftClassPtr<AActor> PreviewClass_DEPRECATED;` — `UE_DEPRECATED(all, "Use ObjectActorClass in PreviewData instead.")` — `UPROPERTY()` — Actor class used for previewing the definition in the asset editor.
- L431 _public member_ `FSoftObjectPath PreviewMeshPath_DEPRECATED;` — `UE_DEPRECATED(all, "Use ObjectMeshPath in PreviewData instead.")` — `UPROPERTY()` — Path of the static mesh used for previewing the definition in the asset editor.
- L435 _public member_ `FSmartObjectDefinitionPreviewData PreviewData;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SmartObject")` — Actor class used for previewing the user in the asset editor.
- L438 _public function_ `const USmartObjectWorldConditionSchema* GetWorldConditionSchema() const`
- L439 _public function_ `const TSubclassOf<USmartObjectWorldConditionSchema>& GetWorldConditionSchemaClass() const`
- L446 _public function_ `template<typename T> const T& GetDefinitionData() const` — Returns a reference to the definition data of the specified type. Method will fail a check if the slot definition doesn't contain the given type.
- L469 _public function_ `template<typename T> const T* GetDefinitionDataPtr() const` — Returns a pointer to the definition data of the specified type. Method will return null if the slot doesn't contain the given type.
- L487 _public function_ `const FInstancedPropertyBag& GetDefaultParameters() const` — @return reference to definition default parameters.
- L497 _public prototype_ `USmartObjectDefinition* GetAssetVariation(const FInstancedPropertyBag& Parameters, UWorld* World);` — Returns a variation of this asset with specified parameters applied. The variations are cached, and if a variation with same parameters is already in use, the existing asset is returned. @return Pointer to an asset variation.
- L503 _public prototype_ `static uint64 GetVariationParametersHash(const FInstancedPropertyBag& Parameters);` — Calculates hash of the parameters. @return hash calculated for the provided bag of parameters.
- L508 _protected prototype_ `virtual bool GetBindingDataView(const FPropertyBindingBinding& InBinding, EBindingSide InSide, FPropertyBindingDataView& OutDataView) override;`
- L511 _protected prototype_ `virtual bool GetBindingDataViewByID(const FGuid InStructID, FPropertyBindingDataView& OutDataView) const override;`
- L512 _protected prototype_ `virtual bool GetBindableStructByID(const FGuid InStructID, TInstancedStruct<FPropertyBindingBindableStructDescriptor>& OutDesc) const override;`
- L513 _protected prototype_ `virtual void GetBindableStructs(const FGuid InTargetStructID, TArray<TInstancedStruct<FPropertyBindingBindableStructDescriptor>>& OutStructDescs) const override;`
- L514 _protected prototype_ `virtual void CreateParametersForStruct(const FGuid InStructID, TArrayView<UE::PropertyBinding::FPropertyCreationDescriptor> InOutCreationDescs) override;`
- L515 _protected prototype_ `virtual void OnPropertyBindingChanged(const FPropertyBindingPath& InSourcePath, const FPropertyBindingPath& InTargetPath) override;`
- L516 _protected prototype_ `virtual FPropertyBindingBindingCollection* GetEditorPropertyBindings() override;`
- L517 _protected prototype_ `virtual const FPropertyBindingBindingCollection* GetEditorPropertyBindings() const override;`
- L518 _protected prototype_ `virtual FGuid GetFallbackStructID() const override;`
- L521 _protected prototype_ `void UpdateSlotReferences();`
- L524 _protected prototype_ `void UpdateBindingPaths();` — Updates the path for all bindings from the associated value and remove invalid ones.
- L531 _protected prototype_ `bool UpdateAndValidatePath(FPropertyBindingPath& Path) const;` — Updates a single path and returns whether it is still valid. @param Path The path to update and validate @return Whether the path has been updated successfully and still valid
- L533 _protected prototype_ `FSmartObjectDefinitionDataHandle GetDataHandleByID(const FGuid StructID);`
- L535 _protected prototype_ `virtual void GetPreloadDependencies(TArray<UObject*>& OutDeps) override;`
- L536 _protected prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L537 _protected prototype_ `virtual void PreSave(FObjectPreSaveContext SaveContext) override;`
- L538 _protected prototype_ `virtual void CollectSaveOverrides(FObjectCollectSaveOverridesContext SaveContext) override;`
- L539 _protected prototype_ `virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;`
- L542 _protected prototype_ `virtual void PostInitProperties() override;`
- L543 _protected prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L544 _protected prototype_ `virtual void PostLoad() override;`
- L550 _private prototype_ `static const USmartObjectBehaviorDefinition* GetBehaviorDefinitionByType(const TArray<USmartObjectBehaviorDefinition*>& BehaviorDefinitions, const TSubclassOf<USmartObjectBehaviorDefinition>& DefinitionClass);` — Finds first behavior definition of a given class in the provided list of definitions.
- L552 _private prototype_ `void ApplyParameters();`
- L553 _private prototype_ `bool GetDataView(const FSmartObjectDefinitionDataHandle DataHandle, FPropertyBindingDataView& OutDataView);`
- L556 _private prototype_ `void EnsureValidGuids();`
- L557 _private prototype_ `void UpdatePropertyBindings();`
- L579 _private member_ `TArray<FSmartObjectDefinitionAssetVariation> Variations;` — Variations of the asset based on provided parameters, created on demand via GetAssetVariation().
- L583 _private member_ `FInstancedPropertyBag Parameters;` — `UPROPERTY(EditDefaultsOnly, Category = "SmartObject", meta = (NoBinding))` — Parameters for the SmartObject definition
- L587 _private member_ `FGuid ParametersID;` — `UPROPERTY()` — Binding ID for the parameters.
- L591 _private member_ `FGuid RootID;` — `UPROPERTY()` — Binding ID for the whole asset.
- L595 _private member_ `FSmartObjectBindingCollection BindingCollection;` — `UPROPERTY(VisibleAnywhere, Category = "SmartObject", AdvancedDisplay)` — Property bindings.
- L602 _private member_ `TArray<FSmartObjectSlotDefinition> Slots;` — `UPROPERTY(EditDefaultsOnly, Category = "SmartObject")` — Where SmartObject's user needs to stay to be able to activate it. These will be used by AI to approach the object. Locations are relative to object's location.
- L606 _private member_ `TArray<TObjectPtr<USmartObjectBehaviorDefinition>> DefaultBehaviorDefinitions;` — `UPROPERTY(EditDefaultsOnly, Category = "SmartObject", Instanced)` — List of behavior definitions of different types provided to SO's user if the slot does not provide one.
- L610 _private member_ `FGameplayTagQuery UserTagFilter;` — `UPROPERTY(EditDefaultsOnly, Category = "SmartObject")` — This object is available if user tags match this query; always available if query is empty.
- L615 _private member_ `TArray<FSmartObjectDefinitionPropertyBinding> PropertyBindings_DEPRECATED;` — `UE_DEPRECATED(all, "Use BindingCollection instead.")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use BindingCollection instead."))`
- L620 _private member_ `FGameplayTagQuery ObjectTagFilter;` — `UE_DEPRECATED(all, "FWorldCondition_SmartObjectActorTagQuery or FSmartObjectWorldConditionObjectTagQuery used in Preconditions instead.")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use FWorldCondition_SmartObjectActorTagQuery or FSmartObjectWorldConditionObjectTagQuery in Preconditions instead."))` — This object is available if instance tags match this query; always available if query is empty.
- L625 _private member_ `FWorldConditionQueryDefinition Preconditions;` — `UPROPERTY(EditDefaultsOnly, Category = "SmartObject", meta = (NoBinding))` — Preconditions that must pass for the object to be found/used.
- L630 _private member_ `FGameplayTagContainer ActivityTags;` — `UPROPERTY(EditDefaultsOnly, Category = "SmartObject")` — Tags identifying this Smart Object's use case. Can be used while looking for objects supporting given activity
- L634 _private member_ `TArray<FSmartObjectDefinitionDataProxy> DefinitionData;` — `UPROPERTY(EditDefaultsOnly, Category = "SmartObject", meta=(DisallowedStructs="/Script/SmartObjectsModule.SmartObjectSlotAnnotation"))` — Custom definition data items (struct inheriting from SmartObjectDefinitionData) for the whole Smart Object.
- L637 _private member_ `TSubclassOf<USmartObjectWorldConditionSchema> WorldConditionSchemaClass;` — `UPROPERTY(EditDefaultsOnly, Category = "SmartObject", AdvancedDisplay, meta = (NoBinding))`
- L641 _private member_ `ESmartObjectTagMergingPolicy ActivityTagsMergingPolicy;` — `UPROPERTY(EditAnywhere, Category = "SmartObject", AdvancedDisplay, meta = (NoBinding))` — Indicates how Tags from slots and parent object are combined to be evaluated by a TagQuery from a find request.
- L645 _private member_ `ESmartObjectTagFilteringPolicy UserTagsFilteringPolicy;` — `UPROPERTY(EditAnywhere, Category = "SmartObject", AdvancedDisplay, meta = (NoBinding))` — Indicates how TagQueries from slots and parent object will be processed against User Tags from a find request.
- L647 _private member_ `mutable TOptional<bool> bValid;`

#### struct `USmartObjectDefinition::FSmartObjectDefinitionAssetVariation`  
`struct FSmartObjectDefinitionAssetVariation`  
_L561-576_
- desc: Used internally by USmartObjectDefinition to store a variation of a definition asset.
- L563 _public prototype_ `FSmartObjectDefinitionAssetVariation() = default;`
- L565 _public function_ `FSmartObjectDefinitionAssetVariation(USmartObjectDefinition* InDefinitionAsset, uint64 InParametersHash) : DefinitionAsset(InDefinitionAsset) , ParametersHash(InParametersHash)`
- L572 _public member_ `TWeakObjectPtr<USmartObjectDefinition> DefinitionAsset = nullptr;` — Pointer to the asset variation which has the parameters applied to it. Stored as weak pointer, so that we can prune variations which are not used anymore.
- L575 _public member_ `uint64 ParametersHash = 0;` — Hash of the variation properties.

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API SMARTOBJECTSMODULE_API`
- L25 _namespace_ `namespace EMessageSeverity`
- L30 _namespace_ `namespace UE`
- L30 _namespace_ `namespace SmartObject` (scope `UE`)
- L30 _namespace_ `namespace Delegates` (scope `UE::SmartObject`)
- L35 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnParametersChanged, const USmartObjectDefinition& );` — Called in editor when parameters for a specific SmartObjectDefinition changes.
- L35 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnParametersChanged, const USmartObjectDefinition& );` (scope `UE::SmartObject::Delegates`) — Called in editor when parameters for a specific SmartObjectDefinition changes.
- L36 _externvar_ `extern FOnParametersChanged OnParametersChanged;` (scope `UE::SmartObject::Delegates`)
- L39 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnGetAssetRegistryTags, const USmartObjectDefinition& , FAssetRegistryTagsContext );` — Delegate to retrieve Registry Tags for SmartObjectDefinition
- L39 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnGetAssetRegistryTags, const USmartObjectDefinition& , FAssetRegistryTagsContext );` (scope `UE::SmartObject::Delegates`) — Delegate to retrieve Registry Tags for SmartObjectDefinition
- L40 _externvar_ `extern FOnGetAssetRegistryTags OnGetAssetRegistryTags;` (scope `UE::SmartObject::Delegates`)
- L43 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnSlotDefinitionCreated, USmartObjectDefinition& , FSmartObjectSlotDefinition& );` — Called in editor when a new SmartObjectSlotDefinition is created (not called when duplicating an existing one).
- L43 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnSlotDefinitionCreated, USmartObjectDefinition& , FSmartObjectSlotDefinition& );` (scope `UE::SmartObject::Delegates`) — Called in editor when a new SmartObjectSlotDefinition is created (not called when duplicating an existing one).
- L44 _externvar_ `extern FOnSlotDefinitionCreated OnSlotDefinitionCreated;` (scope `UE::SmartObject::Delegates`)
- L47 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSavingDefinition, const USmartObjectDefinition& );` — Called in editor when a SmartObjectDefinition is about to be saved.
- L47 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSavingDefinition, const USmartObjectDefinition& );` (scope `UE::SmartObject::Delegates`) — Called in editor when a SmartObjectDefinition is about to be saved.
- L48 _externvar_ `extern FOnSavingDefinition OnSavingDefinition;` (scope `UE::SmartObject::Delegates`)
- L393 _function_ `friend FString LexToString(const USmartObjectDefinition& Definition)` — Provides a description of the definition

### `Plugins/Runtime/SmartObjects/Source/SmartObjectsModule/Public/SmartObjectDefinitionBindableStructDescriptor.h` (Public)


#### struct `FSmartObjectDefinitionBindableStructDescriptor`  
`struct FSmartObjectDefinitionBindableStructDescriptor : public FPropertyBindingBindableStructDescriptor`  
_L14-31_
- reflection: `USTRUCT()`
- inherits: `FPropertyBindingBindableStructDescriptor`
- desc: Descriptor for a struct or class that can be a binding source or target. e.g., Parameters, Slot, Slot Data, etc.
- L18 _public prototype_ `FSmartObjectDefinitionBindableStructDescriptor() = default;`
- L21 _public function_ `FSmartObjectDefinitionBindableStructDescriptor(const FName& InName, const UStruct* InStruct, const FGuid& InGuid, const FSmartObjectDefinitionDataHandle& DataHandle) : FPropertyBindingBindableStructDescriptor(InName, InStruct, InGuid) , DataHandle(DataHandle)`
- L30 _public member_ `FSmartObjectDefinitionDataHandle DataHandle = FSmartObjectDefinitionDataHandle::Invalid;` — `UPROPERTY(VisibleAnywhere, Category = "SmartObject")` — Handle allowing bindings to locate the structure in the definition that this descriptor represents.

### `Plugins/Runtime/SmartObjects/Source/SmartObjectsModule/Public/SmartObjectDefinitionPropertyBinding.h` (Public)


#### enum `ESmartObjectPropertyPathRetargetingStatus`  
`enum class ESmartObjectPropertyPathRetargetingStatus : uint8`  
_L15-20_
- reflection: `UENUM()`
- L17 _public enumerator_ `NoRetargeting`
- L18 _public enumerator_ `PickedPath`
- L19 _public enumerator_ `RetargetedPath`

#### struct `FSmartObjectDefinitionPropertyBinding`  
`struct FSmartObjectDefinitionPropertyBinding : public FPropertyBindingBinding`  
_L29-76_
- reflection: `USTRUCT()`
- inherits: `FPropertyBindingBinding`
- desc: Representation of a property binding used inside a FSmartObjectBindingCollection. This is an extension of FPropertyBindingBinding with source and target FSmartObjectDefinitionDataHandle allowing to refer to bindable structs in the SmartObjectDefinition (e.g., Parameters, Slots, etc.)
- L38 _protected function_ `virtual FConstStructView GetSourceDataHandleStruct() const override`
- L44 _protected member_ `FSmartObjectDefinitionDataHandle SourceDataHandle;` — `UPROPERTY(VisibleAnywhere, Category = "SmartObject")`
- L47 _protected member_ `FSmartObjectDefinitionDataHandle TargetDataHandle;` — `UPROPERTY(VisibleAnywhere, Category = "SmartObject")`
- L57 _public member_ `ESmartObjectPropertyPathRetargetingStatus TargetPathRetargetingStatus = ESmartObjectPropertyPathRetargetingStatus::NoRetargeting;` — `UPROPERTY(VisibleAnywhere, Category = "SmartObject")` — Bindings targeting properties inside FWorldConditionQueryDefinition (e.g., SelectionPreconditions) require an additional binding with a retarget path for runtime. For that reason we categorized them so we can get rid of the original picked path when cooking the content.
- L60 _public prototype_ `FSmartObjectDefinitionPropertyBinding(const FSmartObjectDefinitionPropertyBinding& Other) = default;`
- L61 _public prototype_ `FSmartObjectDefinitionPropertyBinding(FSmartObjectDefinitionPropertyBinding&& Other) = default;`
- L62 _public prototype_ `FSmartObjectDefinitionPropertyBinding& operator=(const FSmartObjectDefinitionPropertyBinding& Other) = default;`
- L64 _public prototype_ `void PostSerialize(const FArchive& Ar);`
- L69 _private member_ `FPropertyBindingPath SourcePath_DEPRECATED;` — `UE_DEPRECATED(all, "Use FPropertyBindingBinding::SourcePropertyPath instead.")` — `UPROPERTY()`
- L73 _private member_ `FPropertyBindingPath TargetPath_DEPRECATED;` — `UE_DEPRECATED(all, "Use FPropertyBindingBinding::TargetPropertyPath instead.")` — `UPROPERTY()`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FSmartObjectDefinitionPropertyBinding> : public TStructOpsTypeTraitsBase2<FSmartObjectDefinitionPropertyBinding>`  
_L80-86_
- inherits: `TStructOpsTypeTraitsBase2<FSmartObjectDefinitionPropertyBinding>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L83-85_

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SMARTOBJECTSMODULE_API`
- L84 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anon12ad93ab0103`)

### `Plugins/Runtime/SmartObjects/Source/SmartObjectsModule/Public/SmartObjectDefinitionReference.h` (Public)


#### struct `FSmartObjectDefinitionReference`  
`struct FSmartObjectDefinitionReference`  
_L16-117_
- reflection: `USTRUCT()`
- desc: Struct to hold reference to a SmartObjectDefinition asset along with values to parameterized it.
- L20 _public prototype_ `FSmartObjectDefinitionReference() = default;`
- L21 _public function_ `explicit FSmartObjectDefinitionReference(const USmartObjectDefinition* Definition) : SmartObjectDefinition(Definition)`
- L26 _public function_ `bool operator==(const FSmartObjectDefinitionReference& RHS) const`
- L33 _public function_ `bool operator!=(const FSmartObjectDefinitionReference& RHS) const`
- L39 _public function_ `bool IsValid() const` — @return true if the reference is set.
- L48 _public prototype_ `USmartObjectDefinition* GetAssetVariation(UWorld* World) const;` — Returns a variation of the USmartObjectDefinition based on the parameters defined in the reference. @return Pointer to an asset variation.
- L51 _public function_ `void SetSmartObjectDefinition(USmartObjectDefinition* NewSmartObjectDefinition)` — Sets the SmartObject Definition asset and synchronize parameters.
- L58 _public function_ `const USmartObjectDefinition* GetSmartObjectDefinition() const` — @return const pointer to the referenced SmartObject Definition asset.
- L64 _public function_ `const FInstancedPropertyBag& GetParameters() const` — @return reference to the parameters for the referenced SmartObject Definition asset.
- L71 _public function_ `FInstancedPropertyBag& GetMutableParameters()` — @return reference to the parameters for the referenced SmartObject Definition asset.
- L80 _public prototype_ `void SyncParameters();` — Enforce self parameters to be compatible with those exposed by the selected SmartObject Definition asset.
- L86 _public prototype_ `bool RequiresParametersSync() const;` — Indicates if current parameters are compatible with those available in the selected SmartObject Definition asset. @return true when parameters requires to be synced to be compatible with those available in the selected SmartObject Definition asset, false otherwise.
- L89 _public prototype_ `void ConditionallySyncParameters() const;` — Sync parameters to match the asset if required.
- L92 _public function_ `bool IsPropertyOverridden(const FGuid PropertyID) const` — @return true if the property of specified ID is overridden.
- L98 _public prototype_ `void SetPropertyOverridden(const FGuid PropertyID, const bool bIsOverridden);` — Sets the override status of specified property by ID.
- L100 _public prototype_ `bool SerializeFromMismatchedTag(const FPropertyTag& Tag, FStructuredArchive::FSlot Slot);`
- L107 _protected member_ `TObjectPtr<const USmartObjectDefinition> SmartObjectDefinition = nullptr;` — `UPROPERTY(EditAnywhere, Category = "")`
- L110 _protected member_ `FInstancedPropertyBag Parameters;` — `UPROPERTY(EditAnywhere, Category = "", meta = (FixedLayout))`
- L114 _protected member_ `TArray<FGuid> PropertyOverrides;` — `UPROPERTY(EditAnywhere, Category = "")` — Array of overridden properties. Non-overridden properties will inherit the values from the SmartObjectDefinition default parameters.

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FSmartObjectDefinitionReference> : public TStructOpsTypeTraitsBase2<FSmartObjectDefinitionReference>`  
_L120-126_
- inherits: `TStructOpsTypeTraitsBase2<FSmartObjectDefinitionReference>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L123-125_

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SMARTOBJECTSMODULE_API`
- L124 _enumerator_ `WithStructuredSerializeFromMismatchedTag = true` (scope `TStructOpsTypeTraits::__anonbb6cec1a0103`)

### `Plugins/Runtime/SmartObjects/Source/SmartObjectsModule/Public/SmartObjectHashGrid.h` (Public)


#### struct `FSmartObjectHashGridEntryData`  
`struct FSmartObjectHashGridEntryData : public FSmartObjectSpatialEntryData`  
_L19-24_
- reflection: `USTRUCT()`
- inherits: `FSmartObjectSpatialEntryData`
- L23 _public member_ `FSmartObjectHashGrid2D::FCellLocation CellLoc;`

#### class `USmartObjectHashGrid`  
`class USmartObjectHashGrid : public USmartObjectSpacePartition`  
_L27-41_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USmartObjectSpacePartition`
- L32 _protected prototype_ `virtual void Add(const FSmartObjectHandle Handle, const FBox& Bounds, FInstancedStruct& OutHandle) override;`
- L33 _protected prototype_ `virtual void Remove(const FSmartObjectHandle Handle, FStructView EntryData) override;`
- L34 _protected prototype_ `virtual void Find(const FBox& QueryBox, TArray<FSmartObjectHandle>& OutResults) override;`
- L37 _protected prototype_ `virtual void Draw(FDebugRenderSceneProxy* DebugProxy) override;`
- L40 _private member_ `FSmartObjectHashGrid2D HashGrid;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SMARTOBJECTSMODULE_API`
- L16 _typedef_ `typedef THierarchicalHashGrid2D<2, 4, FSmartObjectHandle> FSmartObjectHashGrid2D;`

### `Plugins/Runtime/SmartObjects/Source/SmartObjectsModule/Public/SmartObjectOctree.h` (Public)


#### struct `FSmartObjectOctreeID`  
`struct FSmartObjectOctreeID : public TSharedFromThis<FSmartObjectOctreeID, ESPMode::ThreadSafe>`  
_L17-20_
- inherits: `TSharedFromThis<FSmartObjectOctreeID,ESPMode::ThreadSafe>`
- L19 _public member_ `FOctreeElementId2 ID;`

#### struct `FSmartObjectOctreeElement`  
`struct FSmartObjectOctreeElement`  
_L22-29_
- L24 _public member_ `FBoxCenterAndExtent Bounds;`
- L25 _public member_ `FSmartObjectHandle SmartObjectHandle;`
- L26 _public member_ `FSmartObjectOctreeIDSharedRef SharedOctreeID;`
- L28 _public prototype_ `FSmartObjectOctreeElement(const FBoxCenterAndExtent& Bounds, const FSmartObjectHandle SmartObjectHandle, const FSmartObjectOctreeIDSharedRef& SharedOctreeID);`

#### struct `FSmartObjectOctreeSemantics`  
`struct FSmartObjectOctreeSemantics`  
_L31-50_
- L37 _public typedef_ `typedef TInlineAllocator<MaxElementsPerLeaf> ElementAllocator;`
- L39 _public function_ `inline static const FBoxCenterAndExtent& GetBoundingBox(const FSmartObjectOctreeElement& Element)`
- L44 _public function_ `inline static bool AreElementsEqual(const FSmartObjectOctreeElement& A, const FSmartObjectOctreeElement& B)`
- L49 _public prototype_ `static void SetElementId(const FSmartObjectOctreeElement& Element, FOctreeElementId2 Id);`

#### enum `FSmartObjectOctreeSemantics::(anonymous)`  
`enum`  
_L33-33_

#### enum `FSmartObjectOctreeSemantics::(anonymous)`  
`enum`  
_L34-34_

#### enum `FSmartObjectOctreeSemantics::(anonymous)`  
`enum`  
_L35-35_

#### struct `FSmartObjectOctree`  
`struct FSmartObjectOctree : TOctree2<FSmartObjectOctreeElement, FSmartObjectOctreeSemantics>`  
_L52-67_
- inherits: `TOctree2<FSmartObjectOctreeElement,FSmartObjectOctreeSemantics>`
- L55 _public prototype_ `FSmartObjectOctree();`
- L56 _public prototype_ `FSmartObjectOctree(const FVector& Origin, FVector::FReal Radius);`
- L57 _public prototype_ `virtual ~FSmartObjectOctree();`
- L60 _public prototype_ `void AddNode(const FBoxCenterAndExtent& Bounds, const FSmartObjectHandle SmartObjectHandle, const FSmartObjectOctreeIDSharedRef& SharedOctreeID);` — Add new node and initialize using SmartObject runtime data
- L63 _public prototype_ `void UpdateNode(const FOctreeElementId2& Id, const FBox& NewBounds);` — Updates element bounds remove/add operation
- L66 _public prototype_ `void RemoveNode(const FOctreeElementId2& Id);` — Remove node

#### struct `FSmartObjectOctreeEntryData`  
`struct FSmartObjectOctreeEntryData : public FSmartObjectSpatialEntryData`  
_L70-77_
- reflection: `USTRUCT()`
- inherits: `FSmartObjectSpatialEntryData`
- L74 _public function_ `FSmartObjectOctreeEntryData() : SharedOctreeID(MakeShareable(new FSmartObjectOctreeID()))`
- L76 _public member_ `FSmartObjectOctreeIDSharedRef SharedOctreeID;`

#### class `USmartObjectOctree`  
`class USmartObjectOctree : public USmartObjectSpacePartition`  
_L80-92_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USmartObjectSpacePartition`
- L85 _protected prototype_ `virtual void Add(const FSmartObjectHandle Handle, const FBox& Bounds, FInstancedStruct& OutHandle) override;`
- L86 _protected prototype_ `virtual void Remove(const FSmartObjectHandle Handle, FStructView EntryData) override;`
- L87 _protected prototype_ `virtual void Find(const FBox& QueryBox, TArray<FSmartObjectHandle>& OutResults) override;`
- L88 _protected prototype_ `virtual void SetBounds(const FBox& Bounds) override;`
- L91 _private member_ `FSmartObjectOctree SmartObjectOctree;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API SMARTOBJECTSMODULE_API`
- L15 _typedef_ `typedef TSharedRef<struct FSmartObjectOctreeID, ESPMode::ThreadSafe> FSmartObjectOctreeIDSharedRef;`
- L33 _enumerator_ `enum { MaxElementsPerLeaf = 16 }; enum { MinInclusiveElementsPerNode = 7 }; enum { MaxNodeDepth = 12 }; typedef TInlineAllocator<MaxElementsPerLeaf> ElementAllocator; inline static const FBoxCenterAndExtent& GetBoundingBox(const FSmartObjectOctreeElement& Element) {` (scope `FSmartObjectOctreeSemantics::__anona42510240103`)
- L34 _enumerator_ `enum { MinInclusiveElementsPerNode = 7 }; enum { MaxNodeDepth = 12 }; typedef TInlineAllocator<MaxElementsPerLeaf> ElementAllocator; inline static const FBoxCenterAndExtent& GetBoundingBox(const FSmartObjectOctreeElement& Element) { return Element.Bounds;` (scope `FSmartObjectOctreeSemantics::__anona42510240203`)
- L35 _enumerator_ `enum { MaxNodeDepth = 12 }; typedef TInlineAllocator<MaxElementsPerLeaf> ElementAllocator; inline static const FBoxCenterAndExtent& GetBoundingBox(const FSmartObjectOctreeElement& Element) { return Element.Bounds; }` (scope `FSmartObjectOctreeSemantics::__anona42510240303`)

### `Plugins/Runtime/SmartObjects/Source/SmartObjectsModule/Public/SmartObjectPersistentCollection.h` (Public)


#### struct `FSmartObjectCollectionEntry`  
`struct FSmartObjectCollectionEntry`  
_L24-103_
- reflection: `USTRUCT()`
- desc: Struct representing a unique registered component in the collection actor
- L29 _public prototype_ `FSmartObjectCollectionEntry() = default;`
- L30 _public prototype_ `FSmartObjectCollectionEntry(const FSmartObjectCollectionEntry& Other) = default;`
- L31 _public prototype_ `FSmartObjectCollectionEntry(FSmartObjectCollectionEntry&& Other) = default;`
- L32 _public prototype_ `FSmartObjectCollectionEntry& operator=(const FSmartObjectCollectionEntry& Other) = default;`
- L33 _public prototype_ `FSmartObjectCollectionEntry& operator=(FSmartObjectCollectionEntry&& Other) = default;`
- L34 _public prototype_ `FSmartObjectCollectionEntry(const FSmartObjectHandle SmartObjectHandle, TNotNull<USmartObjectComponent*> SmartObjectComponent, const uint32 DefinitionIndex);`
- L37 _public function_ `const FSmartObjectHandle& GetHandle() const`
- L42 _public prototype_ `USmartObjectComponent* GetComponent() const;`
- L44 _public function_ `FTransform GetTransform() const`
- L49 _public function_ `const FBox& GetBounds() const`
- L54 _public function_ `FBox GetWorldBounds() const`
- L59 _public function_ `uint32 GetDefinitionIndex() const`
- L64 _public function_ `const FGameplayTagContainer& GetTags() const`
- L77 _protected function_ `void SetDefinitionIndex(const uint32 InDefinitionIndex)`
- L84 _protected member_ `FSoftObjectPath Path_DEPRECATED;` — `UE_DEPRECATED(all, "Use Component weak pointer instead.")` — `UPROPERTY()`
- L88 _protected member_ `FGameplayTagContainer Tags;` — `UPROPERTY(VisibleAnywhere, Category = SmartObject)`
- L90 _protected member_ `TWeakObjectPtr<USmartObjectComponent> Component;`
- L93 _protected member_ `FTransform Transform;` — `UPROPERTY()`
- L96 _protected member_ `FBox Bounds = FBox(ForceInitToZero);` — `UPROPERTY()`
- L99 _protected member_ `FSmartObjectHandle Handle;` — `UPROPERTY(VisibleAnywhere, Category = SmartObject, meta = (ShowOnlyInnerProperties))`
- L102 _protected member_ `uint32 DefinitionIdx = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category = SmartObject)`

#### struct `FSmartObjectContainer`  
`struct FSmartObjectContainer`  
_L107-207_
- reflection: `USTRUCT()`
- L111 _public prototype_ `explicit FSmartObjectContainer(UObject* InOwner = nullptr);`
- L112 _public prototype_ `~FSmartObjectContainer();`
- L114 _public prototype_ `FSmartObjectContainer& operator=(const FSmartObjectContainer& Other);`
- L115 _public prototype_ `FSmartObjectContainer& operator=(FSmartObjectContainer&& Other);`
- L123 _public prototype_ `FSmartObjectCollectionEntry* AddSmartObject(TNotNull<USmartObjectComponent*> SOComponent, bool& bOutAlreadyInCollection);` — Creates a new entry for a given component. @param SOComponent SmartObject Component for which a new entry must be created @param bOutAlreadyInCollection Output parameter to indicate if an existing entry was returned instead of a newly created one. @return Pointer to the created or existing entry. A nullptr value indicates a registration error.
- L125 _public prototype_ `bool RemoveSmartObject(TNotNull<USmartObjectComponent*> SOComponent);`
- L132 _public prototype_ `bool UpdateSmartObject(TNotNull<const USmartObjectComponent*> SOComponent);` — If SOComponent is already contained by this FSmartObjectContainer instance then data relating to it will get updated @return whether this container instance contains SOComponent
- L135 _public prototype_ `USmartObjectComponent* GetSmartObjectComponent(const FSmartObjectHandle SmartObjectHandle) const;`
- L137 _public prototype_ `const USmartObjectDefinition* GetDefinitionForEntry(const FSmartObjectCollectionEntry& Entry, TNotNull<UWorld*> World) const;`
- L139 _public function_ `TConstArrayView<FSmartObjectCollectionEntry> GetEntries() const`
- L144 _public function_ `void SetBounds(const FBox& InBounds)`
- L149 _public function_ `const FBox& GetBounds() const`
- L154 _public function_ `bool IsEmpty() const`
- L159 _public prototype_ `void Append(const FSmartObjectContainer& Other);`
- L160 _public prototype_ `int32 Remove(const FSmartObjectContainer& Other);`
- L162 _public prototype_ `void ValidateDefinitions();`
- L172 _protected prototype_ `FSmartObjectCollectionEntry* AddSmartObjectInternal(const FSmartObjectHandle Handle, TNotNull<USmartObjectComponent*> SOComponent);` — assumes SOComponent to not be part of the collection yet
- L175 _protected member_ `FBox Bounds = FBox(ForceInitToZero);` — `UPROPERTY(VisibleAnywhere, Category = SmartObject)`
- L178 _protected member_ `TArray<FSmartObjectCollectionEntry> CollectionEntries;` — `UPROPERTY(VisibleAnywhere, Category = SmartObject)`
- L181 _protected member_ `TMap<FSmartObjectHandle, TObjectPtr<USmartObjectComponent>> HandleToComponentMappings;` — `UPROPERTY()`
- L184 _protected member_ `TArray<FSmartObjectDefinitionReference> DefinitionReferences;` — `UPROPERTY(VisibleAnywhere, Category = SmartObject)`
- L188 _protected member_ `TObjectPtr<const UObject> Owner;` — `UPROPERTY()` — used for reporting and debugging
- L193 _protected member_ `TMap<FSmartObjectHandle, FSoftObjectPath> RegisteredIdToObjectMap_DEPRECATED;` — `UE_DEPRECATED(all, "Use HandleToComponentMappings instead.")` — `UPROPERTY()`
- L195 _protected function_ `FString GetFullName() const`
- L200 _protected prototype_ `void ConvertDeprecatedDefinitionsToReferences();`
- L201 _protected prototype_ `void ConvertDeprecatedEntries();`
- L205 _protected member_ `TArray<TObjectPtr<const USmartObjectDefinition>> Definitions_DEPRECATED;` — `UE_DEPRECATED(all, "Use DefinitionReferences instead.")` — `UPROPERTY()`

#### class `ASmartObjectPersistentCollection`  
`class ASmartObjectPersistentCollection : public AActor`  
_L212-319_
- reflection: `UCLASS(MinimalAPI, NotBlueprintable, hidecategories = (Rendering, Replication, Collision, Input, HLOD, Actor, LOD, Cooking, WorldPartition))`
- inherits: `AActor`
- desc: Actor holding smart object persistent data
- L217 _public function_ `const TArray<FSmartObjectCollectionEntry>& GetEntries() const`
- L222 _public function_ `void SetBounds(const FBox& InBounds)`
- L227 _public function_ `const FBox& GetBounds() const`
- L232 _public function_ `const FSmartObjectContainer& GetSmartObjectContainer() const`
- L237 _public function_ `FSmartObjectContainer& GetMutableSmartObjectContainer()`
- L242 _public function_ `bool IsEmpty() const`
- L248 _public prototype_ `void ResetCollection(const int32 ExpectedNumElements = 0);`
- L249 _public function_ `bool ShouldDebugDraw() const`
- L258 _protected prototype_ `explicit ASmartObjectPersistentCollection(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L260 _protected prototype_ `virtual void PostLoad() override;`
- L261 _protected prototype_ `virtual void PostActorCreated() override;`
- L262 _protected prototype_ `virtual void Destroyed() override;`
- L263 _protected prototype_ `virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;`
- L264 _protected prototype_ `virtual void PreRegisterAllComponents() override;`
- L265 _protected prototype_ `virtual void PostUnregisterAllComponents() override;`
- L268 _protected prototype_ `virtual void PostEditUndo() override;`
- L272 _protected prototype_ `void ClearCollection();` — `UFUNCTION(CallInEditor, Category = SmartObject)` — Removes all entries from the collection.
- L276 _protected prototype_ `void RebuildCollection();` — `UFUNCTION(CallInEditor, Category = SmartObject)` — Rebuild entries in the collection using all the SmartObjectComponents currently loaded in the level.
- L280 _protected prototype_ `void AppendToCollection(const TConstArrayView<USmartObjectComponent*> InComponents);` — Adds contents of InComponents to the stored SmartObjectContainer. Note that function does not clear out the existing contents of SmartObjectContainer. Call ClearCollection or RebuildCollection if that is required.
- L282 _protected prototype_ `void OnSmartObjectComponentChanged(TNotNull<const USmartObjectComponent*> Instance);`
- L285 _protected prototype_ `virtual bool RegisterWithSubsystem(const FString& Context);`
- L286 _protected prototype_ `virtual bool UnregisterWithSubsystem(const FString& Context);`
- L288 _protected prototype_ `void OnRegistered();`
- L289 _protected function_ `bool IsRegistered() const`
- L294 _protected prototype_ `void OnUnregistered();`
- L297 _protected member_ `FSmartObjectContainer SmartObjectContainer;` — `UPROPERTY(VisibleAnywhere, Category = SmartObject)`
- L301 _protected member_ `TObjectPtr<UBillboardComponent> SpriteComponent;` — `UPROPERTY(transient)`
- L304 _protected member_ `TObjectPtr<USmartObjectContainerRenderingComponent> RenderingComponent;` — `UPROPERTY(transient)`
- L307 _private member_ `FDelegateHandle OnSmartObjectChangedDelegateHandle;`
- L311 _protected member_ `bool bUpdateCollectionOnSmartObjectsChange = true;` — `UPROPERTY(EditAnywhere, Category = SmartObject, AdvancedDisplay)`
- L314 _protected member_ `bool bEnableDebugDrawing = true;` — `UPROPERTY(EditAnywhere, Category = SmartObject, AdvancedDisplay)`
- L318 _protected member_ `bool bRegistered = false;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SMARTOBJECTSMODULE_API`
- L11 _namespace_ `namespace EEndPlayReason`

### `Plugins/Runtime/SmartObjects/Source/SmartObjectsModule/Public/SmartObjectRenderingComponent.h` (Public)


#### class `USmartObjectRenderingComponent`  
`class USmartObjectRenderingComponent : public UPrimitiveComponent`  
_L14-32_
- reflection: `UCLASS(MinimalAPI, hidecategories = (Object, LOD, Lighting, VirtualTexture, Transform, HLOD, Collision, TextureStreaming, Mobile, Physics, Tags, AssetUserData, Activation, Cooking, Rendering), editinlinenew, meta = (BlueprintSpawnableComponent))`
- inherits: `UPrimitiveComponent`
- L18 _public prototype_ `USmartObjectRenderingComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L21 _public prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy() override;`
- L22 _public function_ `virtual bool ShouldRecreateProxyOnUpdateTransform() const override`
- L26 _public prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform &LocalToWorld) const override;`
- L30 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SMARTOBJECTSMODULE_API`

### `Plugins/Runtime/SmartObjects/Source/SmartObjectsModule/Public/SmartObjectRequestTypes.h` (Public)


#### enum `ESmartObjectDefinitionFilterRejection`  
`enum class ESmartObjectDefinitionFilterRejection : uint8`  
_L14-20_
- reflection: `UENUM()`
- desc: Reason a slot was rejected during FindMatchingSlotDefinitionIndicesInternal (definition-level filtering).
- L16 _public enumerator_ `BehaviorDefinitionMismatch`
- L17 _public enumerator_ `ActivityTagMismatch`
- L18 _public enumerator_ `UserTagMismatch`
- L19 _public enumerator_ `CombinedUserTagMismatch`

#### enum `ESmartObjectFilterRejection`  
`enum class ESmartObjectFilterRejection : uint8`  
_L24-30_
- reflection: `UENUM()`
- desc: Reason an entire SmartObject was rejected (all slots rejected together).
- L26 _public enumerator_ `SmartObjectDisabled`
- L27 _public enumerator_ `PredicateRejected`
- L28 _public enumerator_ `ObjectPreconditionsFailed`
- L29 _public enumerator_ `OutsideSpatialBounds`

#### enum `ESmartObjectSlotFilterRejection`  
`enum class ESmartObjectSlotFilterRejection : uint8`  
_L34-39_
- reflection: `UENUM()`
- desc: Reason an individual slot was rejected during FindSlotsInternal.
- L36 _public enumerator_ `SlotDisabled`
- L37 _public enumerator_ `SlotClaimedByHigherPriority`
- L38 _public enumerator_ `SlotPreconditionsFailed`

#### struct `FSmartObjectDebugDefinitionRejection`  
`struct FSmartObjectDebugDefinitionRejection`  
_L50-55_
- desc: Definition-level rejection record. Applies to all SOs using that definition. For per-slot rejections (BehaviorDefinitionMismatch, ActivityTagMismatch, UserTagMismatch), SlotIndex identifies the specific slot that failed. For CombinedUserTagMismatch, one record is emitted per slot since the parent tag filter rejects the entire definition.
- L52 _public member_ `TWeakObjectPtr<const USmartObjectDefinition> Definition;`
- L53 _public member_ `int32 SlotIndex = INDEX_NONE;`
- L54 _public member_ `ESmartObjectDefinitionFilterRejection Reason = ESmartObjectDefinitionFilterRejection::BehaviorDefinitionMismatch;`

#### struct `FSmartObjectDebugObjectRejection`  
`struct FSmartObjectDebugObjectRejection`  
_L58-62_
- desc: SmartObject-level rejection record. Identified by FSmartObjectHandle.
- L60 _public member_ `FSmartObjectHandle SmartObjectHandle;`
- L61 _public member_ `ESmartObjectFilterRejection Reason = ESmartObjectFilterRejection::SmartObjectDisabled;`

#### struct `FSmartObjectDebugSlotRejection`  
`struct FSmartObjectDebugSlotRejection`  
_L65-70_
- desc: Slot-level rejection record. Identified by FSmartObjectHandle + slot index.
- L67 _public member_ `FSmartObjectHandle SmartObjectHandle;`
- L68 _public member_ `int32 SlotIndex = INDEX_NONE;`
- L69 _public member_ `ESmartObjectSlotFilterRejection Reason = ESmartObjectSlotFilterRejection::SlotDisabled;`

#### struct `FSmartObjectDebugRejections`  
`struct FSmartObjectDebugRejections`  
_L73-78_
- desc: Container for all three levels of debug rejection data.
- L75 _public member_ `TArray<FSmartObjectDebugDefinitionRejection> DefinitionRejections;`
- L76 _public member_ `TArray<FSmartObjectDebugObjectRejection> ObjectRejections;`
- L77 _public member_ `TArray<FSmartObjectDebugSlotRejection> SlotRejections;`

#### struct `FSmartObjectRequestFilter`  
`struct FSmartObjectRequestFilter`  
_L86-125_
- reflection: `USTRUCT(BlueprintType)`
- desc: Struct that can be used to filter results of a smart object request when trying to find or claim a smart object
- L92 _public member_ `FGameplayTagContainer UserTags;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SmartObject)` — Gameplay tags of the Actor or Entity requesting the Smart Object slot.
- L96 _public member_ `ESmartObjectClaimPriority ClaimPriority = ESmartObjectClaimPriority::Normal;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SmartObject)` — The user's claim priority. The search will contain already claimed slots at lower priority.
- L100 _public member_ `FGameplayTagQuery ActivityRequirements;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SmartObject)` — Only return slots whose activity tags are matching this query.
- L104 _public member_ `TArray<TSubclassOf<USmartObjectBehaviorDefinition>> BehaviorDefinitionClasses;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SmartObject)` — If set, will filter out any SmartObject that uses different BehaviorDefinition classes.
- L108 _public member_ `bool bShouldEvaluateConditions = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SmartObject)` — If true, will evaluate the slot and object conditions, otherwise will skip them.
- L112 _public member_ `bool bShouldIncludeClaimedSlots = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SmartObject)` — If true, this search will contain claimed slots.
- L116 _public member_ `bool bShouldIncludeDisabledSlots = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SmartObject)` — If true, this search will contain disabled slots.
- L119 _public member_ `TFunction<bool(FSmartObjectHandle)> Predicate;` — Is set, will filter out any SmartObject that does not pass the predicate.
- L123 _public member_ `FSmartObjectDebugRejections* DebugRejections = nullptr;` — Optional debug output. If non-null, engine populates with rejection data at all pipeline stages.

#### struct `FSmartObjectRequest`  
`struct FSmartObjectRequest`  
_L131-148_
- reflection: `USTRUCT(BlueprintType)`
- desc: Struct used to find a smart object within a specific search range and with optional filtering
- L135 _public prototype_ `FSmartObjectRequest() = default;`
- L136 _public function_ `FSmartObjectRequest(const FBox& InQueryBox, const FSmartObjectRequestFilter& InFilter) : QueryBox(InQueryBox) , Filter(InFilter)`
- L143 _public member_ `FBox QueryBox = FBox(ForceInitToZero);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SmartObject)` — Box defining the search range
- L147 _public member_ `FSmartObjectRequestFilter Filter;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SmartObject)` — Struct used to filter out some results (all results allowed by default)

#### struct `FSmartObjectRequestResult`  
`struct FSmartObjectRequestResult`  
_L154-188_
- reflection: `USTRUCT(BlueprintType)`
- desc: Struct that holds the object and slot selected by processing a smart object request.
- L158 _public function_ `explicit FSmartObjectRequestResult(const FSmartObjectHandle InSmartObjectHandle, const FSmartObjectSlotHandle InSlotHandle = {}) : SmartObjectHandle(InSmartObjectHandle) , SlotHandle(InSlotHandle)`
- L163 _public prototype_ `FSmartObjectRequestResult() = default;`
- L165 _public function_ `bool IsValid() const`
- L167 _public function_ `bool operator==(const FSmartObjectRequestResult& Other) const`
- L173 _public function_ `bool operator!=(const FSmartObjectRequestResult& Other) const`
- L184 _public member_ `FSmartObjectHandle SmartObjectHandle;` — `UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category = SmartObject)`
- L187 _public member_ `FSmartObjectSlotHandle SlotHandle;` — `UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category = SmartObject)`

#### Free symbols / members of external scopes

- L178 _function_ `friend FString LexToString(const FSmartObjectRequestResult& Result)`

### `Plugins/Runtime/SmartObjects/Source/SmartObjectsModule/Public/SmartObjectRuntime.h` (Public)


#### enum `ESmartObjectSlotState`  
`enum class ESmartObjectSlotState : uint8`  
_L22-32_
- reflection: `UENUM()`
- desc: Enumeration to represent the runtime state of a slot
- L24 _public enumerator_ `Invalid`
- L26 _public enumerator_ `Free` — Slot is available
- L28 _public enumerator_ `Claimed` — Slot is claimed but interaction is not active yet
- L30 _public enumerator_ `Occupied` — Slot is claimed and interaction is active
- L31 _public enumerator_ `Disabled UE_DEPRECATED(all, "Use IsEnabled() instead.")`

#### enum `ETrySpawnActorIfDehydrated`  
`enum class ETrySpawnActorIfDehydrated : uint8`  
_L39-43_
- reflection: `UENUM()`
- desc: Indicates if the subsystem should try to spawn the actor associated to the smartobject if it is currently owned by an instanced actor.
- L41 _public enumerator_ `No`
- L42 _public enumerator_ `Yes`

#### struct `FSmartObjectClaimHandle`  
`struct FSmartObjectClaimHandle`  
_L49-104_
- reflection: `USTRUCT(BlueprintType)`
- desc: Struct describing a reservation between a user and a smart object slot.
- L53 _public function_ `FSmartObjectClaimHandle(const FSmartObjectHandle InSmartObjectHandle, const FSmartObjectSlotHandle InSlotHandle, const FSmartObjectUserHandle& InUser) : SmartObjectHandle(InSmartObjectHandle), SlotHandle(InSlotHandle), UserHandle(InUser)`
- L57 _public function_ `FSmartObjectClaimHandle()`
- L60 _public function_ `bool operator==(const FSmartObjectClaimHandle& Other) const`
- L67 _public function_ `bool operator!=(const FSmartObjectClaimHandle& Other) const`
- L77 _public function_ `void Invalidate()`
- L84 _public function_ `bool IsValid() const` — Indicates that the handle was properly assigned by a call to 'Claim' but doesn't guarantee that the associated object and slot are still registered in the simulation. This information requires a call to `USmartObjectSubsystem::IsClaimedObjectValid` using the handle.
- L91 _public member_ `static const FSmartObjectClaimHandle InvalidHandle;`
- L95 _public member_ `FSmartObjectHandle SmartObjectHandle;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Transient, Category="Default")` — Handle to the Smart Object where the claimed slot belongs to.
- L99 _public member_ `FSmartObjectSlotHandle SlotHandle;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Transient, Category="Default")` — Handle of the claimed slot.
- L103 _public member_ `FSmartObjectUserHandle UserHandle;` — `UPROPERTY(EditAnywhere, Transient, Category="Default")` — Handle describing the user which claimed the slot.

#### struct `FSmartObjectSlotTransform`  
`struct UE_DEPRECATED(all, "Transform is moved to FSmartObjectRuntimeSlot.") FSmartObjectSlotTransform : public FSmartObjectSlotStateData`  
_L107-120_
- reflection: `USTRUCT()`
- inherits: `FSmartObjectSlotStateData`
- L111 _public function_ `const FTransform& GetTransform() const`
- L112 _public function_ `FTransform& GetMutableTransform()`
- L114 _public function_ `void SetTransform(const FTransform& InTransform)`
- L119 _protected member_ `FTransform Transform;` — `UPROPERTY(Transient)`

#### struct `FSmartObjectRuntimeSlot`  
`struct FSmartObjectRuntimeSlot`  
_L130-242_
- reflection: `USTRUCT()`
- L137 _public function_ `FSmartObjectRuntimeSlot() : bSlotEnabled(true), bObjectEnabled(true)` — Also public to pass void 'UScriptStruct::TCppStructOps<FSmartObjectSlotState>::ConstructForTests(void *)'
- L139 _public function_ `FVector3f GetSlotOffset() const`
- L141 _public function_ `FRotator3f GetSlotRotation() const`
- L143 _public function_ `FTransform GetSlotLocalTransform() const`
- L148 _public function_ `FTransform GetSlotWorldTransform(const FTransform& OwnerTransform) const`
- L154 _public function_ `ESmartObjectSlotState GetState() const` — @return Current claim state of the slot.
- L160 _public function_ `bool CanBeClaimed(ESmartObjectClaimPriority ClaimPriority) const` — Sets the slot claimed. @param ClaimPriority Claim priority, a slot claimed at lower priority can be claimed by higher priority (unless already in use). @return True if the slot can be claimed.
- L169 _public function_ `const FGameplayTagContainer& GetTags() const` — @return the runtime gameplay tags of the slot.
- L172 _public function_ `bool IsEnabled() const` — @return true if both the slot and its parent smart object are enabled.
- L175 _public function_ `FConstStructView GetUserData() const` — @return User data struct that can be associated to the slot when claimed or used.
- L177 _public function_ `FInstancedStructContainer& GetMutableStateData()`
- L178 _public function_ `const FInstancedStructContainer& GetStateData() const`
- L181 _public function_ `bool ArePreconditionsInitialized() const` — Indicates if preconditions were successfully initialized.
- L191 _protected prototype_ `bool Claim(const FSmartObjectUserHandle& InUser, ESmartObjectClaimPriority ClaimPriority);`
- L192 _protected prototype_ `bool Release(const FSmartObjectClaimHandle& ClaimHandle, const bool bAborted);`
- L201 _protected member_ `FVector3f Offset = FVector3f::ZeroVector;` — `UPROPERTY(Transient, VisibleAnywhere, Category=SmartObjects)` — Offset of the slot relative to the Smart Object.
- L205 _protected member_ `FRotator3f Rotation = FRotator3f::ZeroRotator;` — `UPROPERTY(Transient, VisibleAnywhere, Category=SmartObjects)` — Rotation of the slot relative to the Smart Object.
- L209 _protected member_ `FGameplayTagContainer Tags;` — `UPROPERTY(Transient, VisibleAnywhere, Category=SmartObjects)` — Runtime tags associated with this slot.
- L212 _protected member_ `FInstancedStruct UserData;` — Struct used to store contextual data of the user when claiming or using a slot.
- L215 _protected member_ `FInstancedStructContainer StateData;` — Slot state data that can be added at runtime.
- L218 _protected member_ `FOnSlotInvalidated OnSlotInvalidatedDelegate;` — Delegate used to notify when a slot gets invalidated. See RegisterSlotInvalidationCallback
- L222 _protected member_ `FSmartObjectUserHandle User;` — `UPROPERTY(Transient, VisibleAnywhere, Category=SmartObjects)` — Handle to the user that reserves or uses the slot
- L226 _protected member_ `mutable FWorldConditionQueryState PreconditionState;` — `UPROPERTY(Transient)` — World condition runtime state.
- L230 _protected member_ `ESmartObjectSlotState State = ESmartObjectSlotState::Free;` — `UPROPERTY(Transient, VisibleAnywhere, Category=SmartObjects)` — Current availability state of the slot
- L233 _protected member_ `ESmartObjectClaimPriority ClaimedPriority = ESmartObjectClaimPriority::None;` — `UPROPERTY(Transient, VisibleAnywhere, Category=SmartObjects)`
- L237 _protected member_ `uint8 bSlotEnabled : 1;` — `UPROPERTY(Transient, VisibleAnywhere, Category=SmartObjects)` — True if the slot is enabled
- L241 _protected member_ `uint8 bObjectEnabled : 1;` — `UPROPERTY(Transient, VisibleAnywhere, Category=SmartObjects)` — True if the parent smart object is enabled

#### struct `FSmartObjectRuntime`  
`struct FSmartObjectRuntime`  
_L248-482_
- reflection: `USTRUCT()`
- desc: Struct to store and manage state of a runtime instance associated to a given smart object definition
- L255 _public function_ `FSmartObjectRuntime()` — Also public to pass void 'UScriptStruct::TCppStructOps<FSmartObjectRuntime>::ConstructForTests(void *)'
- L259 _public prototype_ `FSmartObjectRuntime(const FSmartObjectRuntime& Other) = default;`
- L260 _public prototype_ `FSmartObjectRuntime& operator=(const FSmartObjectRuntime& Other) = default;`
- L262 _public function_ `FSmartObjectRuntime(FSmartObjectRuntime&& Other) : PreconditionState(MoveTemp(Other.PreconditionState)) , Slots(MoveTemp(Other.Slots)) , Definition(MoveTemp(Other.Definition)) , OwnerComponent(MoveTemp(Other.OwnerComponent)) , OwnerData(MoveTemp(Other.OwnerData)) , Transform(MoveTemp(Other.Transform)) , Tags(MoveTemp(Other.Tags)) , OnEvent(MoveTemp(Other.OnEvent)) , RegisteredHandle(MoveTemp(Other.RegisteredHandle)) , SpatialEntryData(MoveTemp(Other.SpatialEntryData)) #if UE_ENABLE_DEBUG_DRAWING , Bounds(MoveTemp(Other.Bounds)) #endif`
- L280 _public function_ `FSmartObjectRuntime& operator=(FSmartObjectRuntime&& Other)`
- L303 _public function_ `FSmartObjectHandle GetRegisteredHandle() const`
- L308 _public function_ `const FTransform& GetTransform() const`
- L313 _public function_ `const USmartObjectDefinition& GetDefinition() const`
- L320 _public function_ `const FGameplayTagContainer& GetTags() const` — Returns all tags assigned to the smart object instance
- L326 _public function_ `const FOnSmartObjectEvent& GetEventDelegate() const` — @return reference to the Smart Object event delegate.
- L332 _public function_ `FOnSmartObjectEvent& GetMutableEventDelegate()` — @return mutable reference to the Smart Object event delegate.
- L341 _public function_ `bool IsEnabled() const` — Indicates if the Smart Object is enabled regardless of the reason. @return True of the Smart Object is enabled.
- L351 _public prototype_ `bool IsEnabledForReason(FGameplayTag ReasonTag) const;` — Indicates if the Smart Object is enabled based on a specific reason. @param ReasonTag Valid Tag to specify the reason for changing the enabled state of the object. Method will ensure if not valid (i.e. None). @return True of the Smart Object is enabled.
- L358 _public prototype_ `void SetEnabled(FGameplayTag ReasonTag, bool bEnabled);` — Enables or disables the entire smart object. @param ReasonTag Valid Tag to specify the reason for changing the enabled state of the object. Method will ensure if not valid (i.e. None). @param bEnabled Flag indicating if the object should be enabled or not.
- L366 _public prototype_ `AActor* GetOwnerActor(ETrySpawnActorIfDehydrated TrySpawnActorIfDehydrated = ETrySpawnActorIfDehydrated::No) const;` — Returns the actor associated to the smart object instance. @param TrySpawnActorIfDehydrated Indicates if the instance should try to spawn the actor/component associated to the smartobject if it is currently owned by an instanced actor. @return Pointer to owner actor if present.
- L374 _public prototype_ `USmartObjectComponent* GetOwnerComponent(ETrySpawnActorIfDehydrated TrySpawnActorIfDehydrated = ETrySpawnActorIfDehydrated::No) const;` — Returns the actor associated to the smart object instance. @param TrySpawnActorIfDehydrated Indicates if the instance should try to spawn the actor/component associated to the smartobject if it is currently owned by an instanced actor. @return Pointer to owning component if present.
- L377 _public function_ `const FSmartObjectRuntimeSlot& GetSlot(const int32 Index) const` — @return handle of the specified slot.
- L382 _public function_ `FSmartObjectRuntimeSlot& GetMutableSlot(const int32 Index)`
- L387 _public function_ `TConstArrayView<FSmartObjectRuntimeSlot> GetSlots() const`
- L393 _public function_ `bool ArePreconditionsInitialized() const` — Indicates if preconditions were successfully initialized.
- L399 _public prototype_ `FString DebugGetDisableFlagsString() const;`
- L406 _private prototype_ `explicit FSmartObjectRuntime(const USmartObjectDefinition& Definition);`
- L408 _private function_ `void SetTransform(const FTransform& Value)`
- L413 _private function_ `void SetRegisteredHandle(const FSmartObjectHandle Value)`
- L423 _private prototype_ `void SetEnabled(bool bEnabled, uint16 ReasonMask);` — Enables or disables the entire smart object using the bit mask from a reason tag. @param bEnabled Flag indicating if the object should be enabled or not. @param ReasonMask Bit mask associated to the reason for disabling the object.
- L429 _private prototype_ `bool ResolveOwnerActor() const;` — Creates full actor from instanced actor owner, if any. That actor will register its SmartObjectComponents that will then update OwnerComponent.
- L433 _private member_ `mutable FWorldConditionQueryState PreconditionState;` — `UPROPERTY(Transient)` — World condition runtime state.
- L437 _private member_ `TArray<FSmartObjectRuntimeSlot> Slots;` — `UPROPERTY(Transient)` — Runtime slots
- L441 _private member_ `TObjectPtr<const USmartObjectDefinition> Definition = nullptr;` — `UPROPERTY()` — Associated smart object definition
- L445 _private member_ `TWeakObjectPtr<USmartObjectComponent> OwnerComponent;` — `UPROPERTY()` — Component that owns the Smart Object. May be empty if the parent Actor is not loaded.
- L448 _private member_ `FInstancedStruct OwnerData;` — Struct used to store contextual data of the owner of that SmartObject.
- L452 _private member_ `FTransform Transform;` — `UPROPERTY(Transient, VisibleAnywhere, Category=SmartObjects)` — Instance specific transform
- L456 _private member_ `FGameplayTagContainer Tags;` — `UPROPERTY(Transient, VisibleAnywhere, Category=SmartObjects)` — Tags applied to the current instance
- L459 _private member_ `FOnSmartObjectEvent OnEvent;` — Delegate that is fired when the Smart Object changes.
- L463 _private member_ `FSmartObjectHandle RegisteredHandle;` — `UPROPERTY(Transient, VisibleAnywhere, Category=SmartObjects)` — RegisteredHandle != FSmartObjectHandle::Invalid when registered with SmartObjectSubsystem
- L467 _private member_ `FInstancedStruct SpatialEntryData;` — `UPROPERTY(EditDefaultsOnly, Category = "SmartObject", meta = (BaseStruct = "/Script/SmartObjectsModule.SmartObjectSpatialEntryData", ExcludeBaseStruct))` — Spatial representation data associated to the current instance
- L470 _private member_ `FBox Bounds = FBox(EForceInit::ForceInit);`
- L478 _private member_ `uint16 DisableFlags = 0;` — `UPROPERTY(Transient, VisibleAnywhere, Category=SmartObjects)` — Each slot has its own enabled state but the parent instance also have a more high level state that could be split into different reasons. Note: The enabled state is stored as disable bits to make it easier to check for "is the object disabled for a given or any reason".
- L481 _public member_ `static constexpr int32 MaxNumDisableFlags = sizeof(DisableFlags) * 8;`

#### struct `FConstSmartObjectView`  
`struct FConstSmartObjectView`  
_L485-549_
- reflection: `USTRUCT()`
- L490 _public prototype_ `FConstSmartObjectView() = default;`
- L492 _public function_ `bool IsValid() const`
- L503 _public function_ `const USmartObjectDefinition& GetSmartObjectDefinition() const` — Returns a reference to the definition of the instance's parent object. Method will fail a check if called on an invalid view. @note The definition fragment is always created and assigned when creating an entity associated to an instance so a valid view is guaranteed to be able to provide it.
- L513 _public function_ `bool IsEnabled() const` — @return true if the object is enabled. Method will fail a check if called on an invalid view
- L523 _public function_ `const FGameplayTagContainer& GetTags() const` — @return runtime gameplay tags of the instance. Method will fail a check if called on an invalid view
- L533 _public function_ `FTransform GetWorldTransform() const` — @return the world transform. Method will fail a check if called on an invalid view
- L542 _protected function_ `FConstSmartObjectView(const FSmartObjectHandle& InHandle, const FSmartObjectRuntime& InRuntime) : Handle(InHandle) , Runtime(&InRuntime)`
- L547 _protected member_ `FSmartObjectHandle Handle;`
- L548 _protected member_ `const FSmartObjectRuntime* Runtime = nullptr;`

#### struct `FConstSmartObjectSlotView`  
`struct FConstSmartObjectSlotView`  
_L552-736_
- reflection: `USTRUCT()`
- L557 _public prototype_ `FConstSmartObjectSlotView() = default;`
- L559 _public function_ `bool IsValid() const`
- L564 _public function_ `FSmartObjectSlotHandle GetSlotHandle() const`
- L574 _public function_ `template<typename T> const T& GetStateData() const` — Returns a reference to the slot state data of the specified type. Method will fail a check if the slot doesn't have the given type.
- L599 _public function_ `template<typename T> const T* GetStateDataPtr() const` — Returns a pointer to the slot state data of the specified type. Method will return null if the slot doesn't have the given type.
- L623 _public function_ `const USmartObjectDefinition& GetSmartObjectDefinition() const` — Returns a reference to the definition of the slot's parent object. Method will fail a check if called on an invalid SlotView. @note The definition fragment is always created and assigned when creating an entity associated to a slot so a valid SlotView is guaranteed to be able to provide it.
- L633 _public function_ `const FSmartObjectSlotDefinition& GetDefinition() const` — Returns a reference to the main definition of the slot. Method will fail a check if called on an invalid SlotView.
- L643 _public function_ `void GetActivityTags(FGameplayTagContainer& OutActivityTags) const` — Fills the provided GameplayTagContainer with the activity tags associated to the slot according to the tag filtering policy. Method will fail a check if called on an invalid SlotView.
- L653 _public function_ `template<typename T> const T& GetDefinitionData() const` — Returns a reference to the definition data of the specified type from the main slot definition. Method will fail a check if the slot definition doesn't contain the given type.
- L664 _public function_ `template<typename T> const T* GetDefinitionDataPtr() const` — Returns a pointer to the definition data of the specified type from the main slot definition. Method will return null if the slot doesn't contain the given type.
- L671 _public function_ `ESmartObjectSlotState GetState() const` — @return the claim state of the slot.
- L678 _public function_ `bool CanBeClaimed(ESmartObjectClaimPriority ClaimPriority) const` — @return true of the slot can be claimed.
- L685 _public function_ `bool IsEnabled() const` — @return true if the slot and the object is enabled.
- L692 _public function_ `const FGameplayTagContainer& GetTags() const` — @return runtime gameplay tags of the slot.
- L699 _public function_ `FSmartObjectHandle GetOwnerRuntimeObject() const` — @return handle to the owning Smart Object.
- L708 _public function_ `FConstStructView GetUserData() const` — Returns a struct view of the Slot's UserData Method will fail a check if called on an invalid SlotView
- L718 _public function_ `FTransform GetWorldTransform() const` — @return the world transform. Must be only called on valid slots. Method will fail a check if called on an invalid SlotView
- L727 _protected function_ `FConstSmartObjectSlotView(const FSmartObjectSlotHandle& InSlotHandle, const FSmartObjectRuntime& InRuntime, const FSmartObjectRuntimeSlot& InSlot) : SlotHandle(InSlotHandle) , Runtime(&InRuntime) , Slot(&InSlot)`
- L733 _protected member_ `FSmartObjectSlotHandle SlotHandle;`
- L734 _protected member_ `const FSmartObjectRuntime* Runtime = nullptr;`
- L735 _protected member_ `const FSmartObjectRuntimeSlot* Slot = nullptr;`

#### struct `FSmartObjectSlotView`  
`struct FSmartObjectSlotView : public FConstSmartObjectSlotView`  
_L739-791_
- reflection: `USTRUCT()`
- inherits: `FConstSmartObjectSlotView`
- L750 _public function_ `template<typename T> T& GetMutableStateData() const` — Returns a reference to the mutable slot state data of the specified type. Method will fail a check if the slot doesn't have the given type.
- L775 _public function_ `template<typename T> T* GetMutableStateDataPtr() const` — Returns a pointer to the mutable slot state data of the specified type. Method will return null if the slot doesn't have the given type.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SMARTOBJECTSMODULE_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace SmartObject` (scope `UE`)
- L15 _prototype_ `uint16 GetMaskForEnabledReasonTag(const FGameplayTag Tag);` (scope `UE::SmartObject`)
- L72 _function_ `friend FString LexToString(const FSmartObjectClaimHandle& Handle)`
- L123 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnSlotInvalidated, const FSmartObjectClaimHandle&, ESmartObjectSlotState );` — Delegate to notify when a given slot gets invalidated and the interaction must be aborted
- L123 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnSlotInvalidated, const FSmartObjectClaimHandle&, ESmartObjectSlotState );` — Delegate to notify when a given slot gets invalidated and the interaction must be aborted
- L194 _function_ `friend FString LexToString(const FSmartObjectRuntimeSlot& Slot)`

### `Plugins/Runtime/SmartObjects/Source/SmartObjectsModule/Public/SmartObjectSettings.h` (Public)


#### class `USmartObjectSettings`  
`class USmartObjectSettings : public UDeveloperSettings`  
_L12-42_
- reflection: `UCLASS(MinimalAPI, config = SmartObjects, defaultconfig, DisplayName = "SmartObject", AutoExpandCategories = "SmartObject")`
- inherits: `UDeveloperSettings`
- L22 _public member_ `ESmartObjectTagFilteringPolicy DefaultUserTagsFilteringPolicy = ESmartObjectTagFilteringPolicy::Override;` — `UPROPERTY(EditAnywhere, config, Category = "SmartObject")` — Default filtering policy to use for TagQueries applied on User Tags in newly created SmartObjectDefinitions. Indicates how TagQueries from slots and parent object will be processed against User Tags from a find request.
- L29 _public member_ `ESmartObjectTagMergingPolicy DefaultActivityTagsMergingPolicy = ESmartObjectTagMergingPolicy::Override;` — `UPROPERTY(EditAnywhere, config, Category = "SmartObject")` — Default merging policy to use for Activity Tags in newly created SmartObjectDefinitions. Indicates how Activity Tags from slots and parent object are combined to be evaluated by an Activity TagQuery from a find request.
- L33 _public member_ `TSubclassOf<USmartObjectWorldConditionSchema> DefaultWorldConditionSchemaClass = USmartObjectWorldConditionSchema::StaticClass();` — `UPROPERTY(EditAnywhere, config, Category = "SmartObject")` — Base world condition class for all new Smart Object definitions.
- L41 _public member_ `bool bShouldExcludePreConditionsOnDedicatedClient = false;` — `UPROPERTY(EditAnywhere, config, Category = "SmartObject")` — Indicates whether or not the pre-conditions should be excluded from serializing SmartObjectDefinitions for client builds. This can be useful for example if the preconditions are server only plugins. This allows to access the definition data on clients, while the logic is only handled on servers.

### `Plugins/Runtime/SmartObjects/Source/SmartObjectsModule/Public/SmartObjectSubsystem.h` (Public)


#### enum `FSmartObjectSlotEntrySelectionMethod`  
`enum class FSmartObjectSlotEntrySelectionMethod : uint8`  
_L58-65_
- reflection: `UENUM()`
- desc: Defines method for selecting slot entry from multiple candidates.
- L61 _public enumerator_ `First` — Return first entry location (in order defined in the slot definition).
- L64 _public enumerator_ `NearestToSearchLocation` — Return nearest entry to specified search location.

#### struct `FSmartObjectSlotEntranceHandle`  
`struct FSmartObjectSlotEntranceHandle`  
_L71-122_
- reflection: `USTRUCT(BlueprintType)`
- desc: Handle describing a specific entrance on a smart object slot.
- L75 _public prototype_ `FSmartObjectSlotEntranceHandle() = default;`
- L77 _public function_ `FSmartObjectSlotHandle GetSlotHandle() const`
- L82 _public function_ `bool IsValid() const`
- L87 _public function_ `bool operator==(const FSmartObjectSlotEntranceHandle& Other) const`
- L92 _public function_ `bool operator!=(const FSmartObjectSlotEntranceHandle& Other) const`
- L106 _private function_ `explicit FSmartObjectSlotEntranceHandle(const FSmartObjectSlotHandle InSlotHandle, const EType InType, const int32 InIndex = 0) : SlotHandle(InSlotHandle) , Type(InType)`
- L116 _private member_ `FSmartObjectSlotHandle SlotHandle;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SmartObject", meta = (AllowPrivateAccess = "true"))`
- L118 _private member_ `EType Type = EType::Invalid;`
- L119 _private member_ `uint8 Index = 0;`

#### enum `FSmartObjectSlotEntranceHandle::EType`  
`enum class EType : uint8`  
_L99-104_
- L101 _public enumerator_ `Invalid` — Handle is invalid
- L102 _public enumerator_ `Entrance` — The handle points to a specific entrance, index is slot data index.
- L103 _public enumerator_ `Slot` — The handle points to the slot itself.

#### struct `FSmartObjectSlotEntranceLocationRequest`  
`struct FSmartObjectSlotEntranceLocationRequest`  
_L138-197_
- reflection: `USTRUCT(BlueprintType)`
- desc: Struct used to request slot entry or exit location. When used with actor, it is generally enough to set the UserActor. In that case NavigationData, ValidationFilter, and UserCapsuleParams are queried via the INavAgentInterface and USmartObjectUserComponent on the actor if they are _not_ set. If the user actor is not available (e.g. with Mass), then ValidationFilter and UserCapsuleParams must be defined, and if bProjectNavigationLocation is set NavigationData must be valid. The location validation is done in following order: - navigation projection - trace ground location (uses altered location from navigation test if applicable) - check transition trajectory (test between unmodified navigation location and slow location)
- L144 _public member_ `TObjectPtr<const AActor> UserActor = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SmartObject")` — Actor that is using the smart object slot. (Optional)
- L148 _public member_ `TSubclassOf<USmartObjectSlotValidationFilter> ValidationFilter;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SmartObject")` — Filter to use for the validation. If not set and UserActor is valid, the filter is queried via USmartObjectUserComponent.
- L152 _public member_ `TObjectPtr<const ANavigationData> NavigationData = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SmartObject")` — Navigation data to use for the navigation queries. If not set and UserActor is valid, the navigation data is queried via INavAgentInterface.
- L156 _public member_ `FSmartObjectUserCapsuleParams UserCapsuleParams = FSmartObjectUserCapsuleParams::Invalid;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SmartObject")` — Size of the user of the smart object. If not set and UserActor is valid, the dimensions are queried via INavAgentInterface.
- L160 _public member_ `FVector SearchLocation = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SmartObject")` — Search location that may be used to select an entry from multiple candidates. (e.g. user actor location).
- L164 _public member_ `FSmartObjectSlotEntrySelectionMethod SelectMethod = FSmartObjectSlotEntrySelectionMethod::First;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SmartObject")` — How to select an entry when a slot has multiple entries.
- L168 _public member_ `ESmartObjectSlotNavigationLocationType LocationType = ESmartObjectSlotNavigationLocationType::Entry;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SmartObject")` — Enum indicating if we're looking for a location to enter or exit the smart object slot.
- L172 _public member_ `bool bProjectNavigationLocation = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SmartObject")` — If true, try to project the location on navigable area. If projection fails, an entry is discarded.
- L176 _public member_ `bool bTraceGroundLocation = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SmartObject")` — If true, try to trace the location on ground. If trace fails, an entry is discarded.
- L180 _public member_ `bool bCheckTransitionTrajectory = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SmartObject")` — If true, check collisions between navigation location and slot location. If collisions are found, an entry is discarded.
- L184 _public member_ `bool bCheckEntranceLocationOverlap = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SmartObject")` — If true, check user capsule collisions at the entrance location. Uses capsule dimensions set in the validation filter.
- L188 _public member_ `bool bCheckSlotLocationOverlap = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SmartObject")` — If true, check user capsule collisions at the slot location. Uses capsule dimensions set in an annotation on the slot.
- L192 _public member_ `bool bUseSlotLocationAsFallback = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SmartObject")` — If true, include slot location as a candidate if no navigation annotation is present.
- L196 _public member_ `bool bUseUpAxisLockedRotation = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SmartObject")` — If true, the result rotation will only contain rotation around the UP axis (i.e., Yaw only; Pitch and Roll set to 0).

#### struct `FSmartObjectSlotEntranceLocationResult`  
`struct FSmartObjectSlotEntranceLocationResult`  
_L203-257_
- reflection: `USTRUCT(BlueprintType)`
- desc: Validated result from FindEntranceLocationForSlot().
- L209 _public prototype_ `FSmartObjectSlotEntranceLocationResult() = default;` — Macro needed to avoid deprecation errors with "Tag_DEPRECATED" being copied or created in the default methods
- L210 _public prototype_ `FSmartObjectSlotEntranceLocationResult(const FSmartObjectSlotEntranceLocationResult&) = default;`
- L211 _public prototype_ `FSmartObjectSlotEntranceLocationResult(FSmartObjectSlotEntranceLocationResult&&) = default;`
- L212 _public prototype_ `FSmartObjectSlotEntranceLocationResult& operator=(const FSmartObjectSlotEntranceLocationResult&) = default;`
- L213 _public prototype_ `FSmartObjectSlotEntranceLocationResult& operator=(FSmartObjectSlotEntranceLocationResult&&) = default;`
- L217 _public function_ `FNavLocation GetNavLocation() const` — @returns entry as nav location.
- L223 _public function_ `bool HasNodeRef() const` — @returns true if the result contains valid navigation node reference.
- L230 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SmartObject")` — The location to enter the slot.
- L234 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SmartObject")` — The expected direction to enter the slot.
- L237 _public member_ `NavNodeRef NodeRef = INVALID_NAVNODEREF;` — Node reference in navigation data (if requested with bProjectNavigationLocation).
- L243 _public member_ `FGameplayTag Tag_DEPRECATED;` — `UE_DEPRECATED(all, "Use Tags instead.")` — `UPROPERTY()` — Gameplay tag associated with the entrance.
- L248 _public member_ `FGameplayTagContainer Tags;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SmartObject")` — Gameplay tags associated with the entrance.
- L252 _public member_ `FSmartObjectSlotEntranceHandle EntranceHandle;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SmartObject")` — Handle identifying the entrance that was found.
- L256 _public member_ `bool bIsValid = true;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SmartObject")` — True if the result has passed validation tests.

#### enum `ESmartObjectCollectionRegistrationResult`  
`enum class ESmartObjectCollectionRegistrationResult : uint8`  
_L265-271_
- reflection: `UENUM()`
- desc: Result code indicating if the Collection was successfully registered or why it was not.
- L267 _public enumerator_ `Failed_InvalidCollection`
- L268 _public enumerator_ `Failed_AlreadyRegistered`
- L269 _public enumerator_ `Failed_NotFromPersistentLevel`
- L270 _public enumerator_ `Succeeded`

#### class `USmartObjectSubsystem`  
`class USmartObjectSubsystem : public UWorldSubsystem`  
_L295-1490_
- reflection: `UCLASS(MinimalAPI, config = SmartObjects, defaultconfig, Transient)`
- inherits: `UWorldSubsystem`
- desc: Subsystem that holds all registered smart object instances and offers the API for spatial queries and reservations. [Notes regarding thread safety] The subsystem is not thread-safe, but a first pass has been made to make it possible to perform a set of operations from multiple threads. To use this mode the following compiler switch is required: #define WITH_SMARTOBJECT_MT_INSTANCE_LOCK 1 Not safe: - runtime instance lifetime controlled from Registration/Unregistration (i.e., CreateSmartObject, RegisterCollection, UnregisterCollection, DestroySmartObject, etc.) - queries: to prevent locking for a long time it is still required to send queries from a single thread (e.g., async request pattern like MassSmartObject) Safe operation on a smart object instance or slot from an object or slot handle: - query and set Enable state - query and set Transform/Location - query and set Tags - update slot state (e.g., MarkSlotAsClaimed, MarkSlotAsReleased, etc.) - use a slot view using ReadSlotData/MutateSlotData
- L299 _public prototype_ `USmartObjectSubsystem();`
- L301 _public prototype_ `static USmartObjectSubsystem* GetCurrent(const UWorld* World);`
- L303 _public prototype_ `ESmartObjectCollectionRegistrationResult RegisterCollection(ASmartObjectPersistentCollection& InCollection);`
- L304 _public prototype_ `void UnregisterCollection(ASmartObjectPersistentCollection& InCollection);`
- L306 _public function_ `const FSmartObjectContainer& GetSmartObjectContainer() const`
- L311 _public function_ `FSmartObjectContainer& GetMutableSmartObjectContainer()`
- L324 _public prototype_ `bool SetEnabled(const FSmartObjectHandle Handle, const bool bEnabled);` — `UFUNCTION(BlueprintCallable, Category = "SmartObject", meta=(DisplayName="Set SmartObject Enabled (default reason: Gameplay)", ReturnDisplayName="Status changed"))` — Enables or disables the entire smart object represented by the provided handle using the default reason (i.e. Gameplay).. Delegate 'OnEvent' is broadcasted with ESmartObjectChangeReason::OnEnabled/ESmartObjectChangeReason::OnDisabled if state changed. @param Handle Handle to the smart object. @param bEnabled If true enables the smart object, disables otherwise. @return True when associated smart object is found and set (or already set) to desired state; false otherwise.
- L335 _public prototype_ `bool SetEnabledForReason(const FSmartObjectHandle Handle, FGameplayTag ReasonTag, const bool bEnabled);` — `UFUNCTION(BlueprintCallable, Category = "SmartObject", meta=(DisplayName="Set SmartObject Enabled (specific reason)", ReturnDisplayName="Status changed"))` — Enables or disables the entire smart object represented by the provided handle using the specified reason. Delegate 'OnEvent' is broadcasted with ESmartObjectChangeReason::OnEnabled/ESmartObjectChangeReason::OnDisabled if state changed. @param Handle Handle to the smart object. @param ReasonTag Valid Tag to specify the reason for changing the enabled state of the object. Method will ensure if not valid (i.e. None). @param bEnabled If true enables the smart object, disables otherwise. @return True when associated smart object is found and set (or already set) to desired state; false otherwise.
- L343 _public prototype_ `bool IsEnabled(const FSmartObjectHandle Handle) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category="SmartObject", meta=(DisplayName="Is SmartObject Enabled (for any reason)", ReturnDisplayName="Enabled"))` — Returns the enabled state of the smart object represented by the provided handle regardless of the disabled reason. @param Handle Handle to the smart object. @return True when associated smart object is found and set to be enabled. False otherwise.
- L352 _public prototype_ `bool IsEnabledForReason(const FSmartObjectHandle Handle, FGameplayTag ReasonTag) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category="SmartObject", meta=(DisplayName="Is SmartObject Enabled (for specific reason)", ReturnDisplayName="Enabled"))` — Returns the enabled state of the smart object represented by the provided handle based on a specific reason. @param Handle Handle to the smart object. @param ReasonTag Valid Tag to test if enabled for a specific reason. Method will ensure if not valid (i.e. None). @return True when associated smart object is found and set to be enabled. False otherwise.
- L361 _public prototype_ `bool SetSmartObjectActorEnabled(const AActor& SmartObjectActor, bool bEnabled);` — Enables or disables all smart objects associated to the provided actor (multiple components). @param SmartObjectActor Smart object(s) parent actor. @param bEnabled If true enables, disables otherwise. @return True if all (at least one) smart object components are found with their associated runtime and values set (or already set) to desired state; false otherwise.
- L368 _public prototype_ `bool RegisterSmartObjectActor(const AActor& SmartObjectActor);` — Registers to the runtime simulation all smart object components for a given actor. @param SmartObjectActor Actor owning the components to register @return true when components are found and all successfully registered, false otherwise
- L375 _public prototype_ `bool UnregisterSmartObjectActor(const AActor& SmartObjectActor);` — Unregisters from the simulation all smart object components for a given actor. @param SmartObjectActor Actor owning the components to unregister @return true when components are found and all successfully unregistered, false otherwise
- L382 _public prototype_ `bool RemoveSmartObjectActor(const AActor& SmartObjectActor);` — Removes all data associated to smart object components of a given actor from the simulation. @param SmartObjectActor Actor owning the components to delete @return whether components are found and all successfully deleted
- L389 _public prototype_ `bool RegisterSmartObject(TNotNull<USmartObjectComponent*> SmartObjectComponent);` — Registers a smart object components to the runtime simulation. @param SmartObjectComponent Smart object component to register @return true when component is successfully registered, false otherwise
- L398 _public prototype_ `FSmartObjectHandle CreateSmartObject(const USmartObjectDefinition& Definition, const FTransform& Transform, const FConstStructView OwnerData);` — Creates a new smart object runtime instance from an external system. @param Definition Smart object definition that the entry will use @param Transform World position where the entry will be initially located @param OwnerData Payload stored in the created runtime instance to identify the owner of the smart object @return Handle to the newly created smart object if the operation was successful.
- L407 _public prototype_ `bool UnregisterSmartObject(TNotNull<USmartObjectComponent*> SmartObjectComponent);` — Unregisters the component from the subsystem, unbinds it from the runtime simulation and handles the associated runtime data according to the component registration type (i.e. runtime data associated to components from persistent collections will remain in the simulation). @param SmartObjectComponent Smart object component to unregister @return true when component is successfully unregistered, false otherwise
- L414 _public prototype_ `bool RemoveSmartObject(TNotNull<USmartObjectComponent*> SmartObjectComponent);` — Unregisters the component from the subsystem, unbinds it from the runtime simulation and removes its runtime data. @param SmartObjectComponent Smart object component to remove @return whether smart object data has been successfully found and removed
- L421 _public prototype_ `bool DestroySmartObject(FSmartObjectHandle Handle);` — Removes the smart object runtime data from the simulation, destroys it and unbinds and unregister associated component if any. @param Handle Handle to the smart object to destroy @return True if the smart object data has been successfully found and destroyed, false otherwise.
- L429 _public prototype_ `bool UpdateSmartObjectTransform(const FSmartObjectHandle Handle, const FTransform& NewTransform);` — Updates the smart object transform. @param Handle Handle to the smart object to update. @param NewTransform New transform of the runtime smart object @return is transform was updated.
- L441 _public prototype_ `USmartObjectComponent* GetSmartObjectComponent(const FSmartObjectClaimHandle& ClaimHandle, ETrySpawnActorIfDehydrated TrySpawnActorIfDehydrated = ETrySpawnActorIfDehydrated::No) const;` — `UFUNCTION(BlueprintCallable, Category = "SmartObject")` — Returns the component associated to the claim handle if still accessible. In some scenarios the component may no longer exist but its smart object data could (e.g. streaming) @param ClaimHandle Handle to a claimed slot returned by any of the Claim methods. @param TrySpawnActorIfDehydrated Indicates if the subsystem should try to spawn the actor/component associated to the smart object if it is currently owned by an instanced actor. @return A pointer to the USmartObjectComponent* associated to the handle.
- L454 _public prototype_ `USmartObjectComponent* GetSmartObjectComponentByRequestResult(const FSmartObjectRequestResult& Result, ETrySpawnActorIfDehydrated TrySpawnActorIfDehydrated = ETrySpawnActorIfDehydrated::No) const;` — `UFUNCTION(BlueprintCallable, Category = "SmartObject")` — Returns the component associated to the  given request result In some scenarios the component may no longer exist but its smart object data could (e.g. streaming) @param Result A request result returned by any of the Find methods . @param TrySpawnActorIfDehydrated Indicates if the subsystem should try to spawn the actor/component associated to the smart object if it is currently owned by an instanced actor. @return A pointer to the USmartObjectComponent* associated to the handle.
- L464 _public prototype_ `[[nodiscard]] FSmartObjectRequestResult FindSmartObject(const FSmartObjectRequest& Request, const FConstStructView UserData) const;` — Spatial lookup for first slot in range respecting request criteria and selection conditions. @param Request Parameters defining the search area and criteria @param UserData Additional data that could be provided to bind values in the conditions evaluation context @return First valid smart object in range. Not the closest one, just the one that happens to be retrieved first from space partition
- L473 _public prototype_ `bool FindSmartObjects(const FSmartObjectRequest& Request, TArray<FSmartObjectRequestResult>& OutResults, const FConstStructView UserData) const;` — Spatial lookup for slot candidates respecting request criteria and selection conditions. @param Request Parameters defining the search area and criteria @param OutResults List of smart object slot candidates found in range @param UserData Additional data that could be provided to bind values in the conditions evaluation context @return True if at least one candidate was found.
- L484 _public prototype_ `bool FindSmartObjectsInList(const FSmartObjectRequestFilter& Filter, const TConstArrayView<AActor*> ActorList, TArray<FSmartObjectRequestResult>& OutResults, const FConstStructView UserData) const;` — Search list of specific actors (often from a physics query) for slot candidates respecting request criteria and selection conditions. @param Filter Parameters defining the search area and criteria @param ActorList Ordered list of actors to search @param OutResults List of smart object slot candidates found in range @param UserData Additional data that could be provided to bind values in the conditions evaluation context @return True if at least one candidate was found.
- L496 _public prototype_ `bool FindSmartObjectsInTargetingRequest(const FSmartObjectRequestFilter& Filter, const FTargetingRequestHandle TargetingHandle, TArray<FSmartObjectRequestResult>& OutResults, const FConstStructView UserData) const;` — Search the results of the given targeting request handle for smart objects that match the request criteria @param Filter Parameters defining the search area and criteria @param TargetingHandle The targeting handle of the request that will have its resulted searched for smart objects @param OutResults List of smart object slot candidates found in range @param UserData Additional data that could be provided to bind values in the conditions evaluation context @return True if at least one candidate was found.
- L506 _public prototype_ `FSmartObjectRequestResult FindSmartObject(const FSmartObjectRequest& Request, const AActor* UserActor = nullptr) const;` — `UFUNCTION(BlueprintCallable, Category = "SmartObject")` — Spatial lookup for first slot in range respecting request criteria and selection conditions. @param Request Parameters defining the search area and criteria @param UserActor Actor claiming the smart object used to evaluate selection conditions @return First valid smart object in range. Not the closest one, just the one that happens to be retrieved first from space partition
- L516 _public function_ `bool FindSmartObjects_BP(const FSmartObjectRequest& Request, TArray<FSmartObjectRequestResult>& OutResults, const AActor* UserActor = nullptr) const` — `UFUNCTION(BlueprintCallable, BlueprintPure = False, Category = "SmartObject", meta=(DisplayName="Find Smart Objects"))` — Blueprint function for spatial lookup for slot candidates respecting request criteria and selection conditions. @param Request Parameters defining the search area and criteria @param OutResults List of smart object slot candidates @param UserActor Actor claiming the smart object @return All valid smart objects in range.
- L528 _public prototype_ `void FindSlots(const FSmartObjectHandle Handle, const FSmartObjectRequestFilter& Filter, TArray<FSmartObjectSlotHandle>& OutSlots, const FConstStructView UserData = {}) const;` — Returns slots of a given smart object matching the filter. @param Handle Handle to the smart object. @param Filter Filter to apply on object and slots. @param OutSlots Available slots found that match the filter @param UserData Optional additional data that could be provided to bind values in the conditions evaluation context
- L536 _public prototype_ `void GetAllSlots(const FSmartObjectHandle Handle, TArray<FSmartObjectSlotHandle>& OutSlots) const;` — `UFUNCTION(BlueprintCallable, Category = "SmartObject")` — Return all slots of a given smart object. @param Handle Handle to the smart object. @param OutSlots All slots of the smart object
- L546 _public prototype_ `[[nodiscard]] TArray<FSmartObjectSlotHandle> FilterSlotsBySelectionConditions( const TConstArrayView<FSmartObjectSlotHandle>& SlotsToFilter, const FConstStructView UserData ) const;` — Evaluates conditions of each slot and add to the result array on success. Optional user data can be provided to bind parameters in evaluation context based on the schema used by the object definition. @param SlotsToFilter List of slot handles to apply selection conditions on @param UserData Additional data that could be provided to bind values in the conditions evaluation context @return List of slot handles that pass all their selection conditions
- L559 _public prototype_ `[[nodiscard]] TArray<FSmartObjectRequestResult> FilterResultsBySelectionConditions( const TConstArrayView<FSmartObjectRequestResult>& ResultsToFilter, const FConstStructView UserData ) const;` — Evaluates conditions of the slot specified by each request result and add to the result array on success. Optional user data can be provided to bind parameters in evaluation context based on the schema used by the object definition. @param ResultsToFilter List of request results to apply selection conditions on @param UserData The additional data that could be bound in the conditions evaluation context @return List of request results that pass all their selection conditions
- L572 _public prototype_ `[[nodiscard]] bool EvaluateSelectionConditions(const FSmartObjectSlotHandle& SlotHandle, const FConstStructView UserData) const;` — Evaluates conditions of the specified slot and its parent smart object. Optional user data can be provided to bind parameters in evaluation context based on the schema used by the object definition. @param SlotHandle Handle to the smart object slot @param UserData Additional data that could be provided to bind values in the conditions evaluation context @return True if all conditions are met; false otherwise
- L582 _public prototype_ `bool FindEntranceLocationForSlot(const FSmartObjectSlotHandle& SlotHandle, const FSmartObjectSlotEntranceLocationRequest& Request, FSmartObjectSlotEntranceLocationResult& Result) const;` — Finds entrance location for a specific slot. Each slot can be annotated with multiple entrance locations, and the request can be configured to also consider the slot location as one entry. Additionally, the entrance locations can be checked to be on navigable surface (does not check that the point is reachable, though), traced on ground, and without of collisions. @param SlotHandle Handle to the smart object slot. @param Request Request describing how to select the entry. @param Result Entry location result (in world space). @return True if valid entry found.
- L591 _public prototype_ `bool UpdateEntranceLocation(const FSmartObjectSlotEntranceHandle& EntranceHandle, const FSmartObjectSlotEntranceLocationRequest& Request, FSmartObjectSlotEntranceLocationResult& Result) const;` — Runs the same logic as FindEntranceLocationForSlot() but for a specific entrance location. The entrance handle can be get from entrance location result. @param EntranceHandle Handle to a specific smart object slot entrance. @param Request Request describing how to select the entry. @param Result Entry location result (in world space). @return True if result is valid.
- L605 _public prototype_ `static bool QueryAllValidatedEntranceLocations( const UWorld* World, const USmartObjectDefinition& SmartObjectDefinition, const FTransform& SmartObjectTransform, const AActor* SkipActor, const FSmartObjectSlotEntranceLocationRequest& Request, TArray<FSmartObjectSlotEntranceLocationResult>& Results );` — Runs the entrance validation logic for all the slots in the smart object definition and returns all validated locations. This method can be used to a smart object definition before it is added to the simulation, for example to show some UI visualization while placing an actor with smart object. The method is static so it can be used even if the smart object subsystem is not present. @param World World to use for validation tracing. @param SmartObjectDefinition Smart object definition to validate. @param SmartObjectTransform World transform of the smart object definition (e.g. smart object Component transform). @param SkipActor An actor to skip during validation (this could be an actor representing the smart object during placement). @param Request Request describing how to validate the entries. @param Results All entrance locations, FSmartObjectSlotEntranceLocationResult::bIsValid can be used to check if a specific result is valid. @return True if any entrances were found.
- L622 _public prototype_ `[[nodiscard]] bool CanBeClaimed(const FSmartObjectSlotHandle& SlotHandle, ESmartObjectClaimPriority ClaimPriority = ESmartObjectClaimPriority::Normal) const;` — Checks whether given slot is free and can be claimed (i.e. slot and its parent are both enabled) @note This methods doesn't evaluate the selection conditions. EvaluateSelectionConditions must be called separately. @param SlotHandle Handle to a smart object slot. @param ClaimPriority Claim priority, a slot claimed at lower priority can be claimed by higher priority (unless already in use). @return true if the indicated slot can be claimed, false otherwise @see EvaluateSelectionConditions
- L631 _public prototype_ `[[nodiscard]] FSmartObjectClaimHandle MarkSlotAsClaimed(const FSmartObjectSlotHandle& SlotHandle, ESmartObjectClaimPriority ClaimPriority, const FConstStructView UserData = {});` — Marks a smart object slot as claimed. @param SlotHandle Handle to a smart object slot. @param ClaimPriority Claim priority, a slot claimed at lower priority can be claimed by higher priority (unless already in use). @param UserData Instanced struct that represents the interacting agent. @return A handle binding the claimed smart object, its slot and a user id.
- L639 _public prototype_ `bool IsSmartObjectValid(const FSmartObjectHandle Handle) const;` — Indicates if the object referred to by the given handle is still accessible in the simulation. This should only be required when a handle is stored and used later. @param Handle Handle to the smart object. @return True if the handle is valid and its associated object is accessible; false otherwise.
- L648 _public prototype_ `bool IsClaimedSmartObjectValid(const FSmartObjectClaimHandle& ClaimHandle) const;` — Indicates if the object/slot referred to by the given handle are still accessible in the simulation. This should only be required when a handle is stored and later needed to access slot or object information (e.g. SlotView) Otherwise a valid ClaimHandle can be use directly after calling 'Claim'. @param ClaimHandle Handle to a claimed slot returned by any of the Claim methods. @return True if the claim handle is valid and its associated object is accessible; false otherwise.
- L657 _public prototype_ `bool IsSmartObjectSlotValid(const FSmartObjectSlotHandle& SlotHandle) const;` — Indicates if the slot referred to by the given handle is still accessible in the simulation. This should only be required when a handle is stored and later needed to access slot information (e.g. SlotView) Otherwise a valid SlotHandle can be use directly after calling any of the 'Find' or 'Claim' methods. @param SlotHandle Handle to a smart object slot. @return True if the handle is valid and its associated slot is accessible; false otherwise.
- L665 _public prototype_ `const USmartObjectBehaviorDefinition* MarkSlotAsOccupied(const FSmartObjectClaimHandle& ClaimHandle, TSubclassOf<USmartObjectBehaviorDefinition> DefinitionClass);` — Marks a previously claimed smart object slot as occupied. @param ClaimHandle Handle to a claimed slot returned by any of the Claim methods. @param DefinitionClass The type of behavior definition the user wants to use. @return The base class pointer of the requested behavior definition class associated to the slot
- L673 _public function_ `template <typename DefinitionType> const DefinitionType* MarkSlotAsOccupied(const FSmartObjectClaimHandle& ClaimHandle)` — Marks a previously claimed smart object slot as occupied. @param ClaimHandle Handle to a claimed slot returned by any of the Claim methods. @return The requested behavior definition class pointer associated to the slot
- L684 _public prototype_ `bool MarkSlotAsFree(const FSmartObjectClaimHandle& ClaimHandle);` — Marks a claimed or occupied smart object as free. @param ClaimHandle Handle to a claimed slot returned by any of the Claim methods. @return Whether the claim was successfully released or not
- L693 _public prototype_ `const USmartObjectBehaviorDefinition* GetBehaviorDefinition( const FSmartObjectClaimHandle& ClaimHandle, TSubclassOf<USmartObjectBehaviorDefinition> DefinitionClass );` — `UFUNCTION(BlueprintCallable, Category = "SmartObject", meta=(DeterminesOutputType = "DefinitionClass"))` — Return the behavior definition of a given type from a claimed object. @param ClaimHandle Handle to a claimed slot returned by any of the Claim methods. @param DefinitionClass The type of behavior definition. @return The base class pointer of the requested behavior definition class associated to the slotClaim handle
- L704 _public function_ `template <typename DefinitionType> const DefinitionType* GetBehaviorDefinition(const FSmartObjectClaimHandle& ClaimHandle)` — Return the behavior definition of a given type from a claimed object. @param ClaimHandle Handle to a claimed slot returned by any of the Claim methods. @return The requested behavior definition class pointer associated to the Claim handle
- L717 _public prototype_ `const USmartObjectBehaviorDefinition* GetBehaviorDefinitionByRequestResult( const FSmartObjectRequestResult& RequestResult, TSubclassOf<USmartObjectBehaviorDefinition> DefinitionClass );` — `UFUNCTION(BlueprintCallable, Category = "SmartObject", meta = (DeterminesOutputType = "DefinitionClass"))` — Return the behavior definition of a given type from a request result. @param RequestResult A request result returned by any of the Find methods. @param DefinitionClass The type of behavior definition. @return The base class pointer of the requested behavior definition class associated to the request result
- L728 _public function_ `template <typename DefinitionType> const DefinitionType* GetBehaviorDefinition(const FSmartObjectRequestResult& RequestResult)` — Return the behavior definition of a given type from a claimed object. @param RequestResult A request result returned by any of the Find methods. @return The requested behavior definition class pointer associated to the request result
- L742 _public prototype_ `bool ReadInstanceData(const FSmartObjectHandle& Handle, TFunctionRef<void(FConstSmartObjectView)> Function) const;` — Executes the provided function if a valid const view can be created for the provided handle. In a multithreaded scenario, the method will prevent the instance from being modified during the execution of the function. @param Handle Handle to a smart object. @param Function Function to execute if a valid view can be created @return Whether the instance was found, was valid, and the function was called
- L748 _public prototype_ `ESmartObjectSlotState GetSlotState(const FSmartObjectSlotHandle SlotHandle) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category="SmartObject")` — Returns the state of the given smart object Slot handle.
- L756 _public prototype_ `void AddSlotData(const FSmartObjectClaimHandle& ClaimHandle, FConstStructView InData);` — Adds state data to a slot instance. Data must be a struct that inherits from FSmartObjectSlotStateData and passed as a struct view (e.g. FConstStructView::Make(FSomeStruct)) @param ClaimHandle Handle to a claimed slot returned by any of the Claim methods. @param InData A view on the struct to add.
- L767 _public prototype_ `bool ReadSlotData(const FSmartObjectSlotHandle& SlotHandle, TFunctionRef<void(FConstSmartObjectSlotView)> Function) const;` — Executes the provided function if a valid const view can be created for the provided slot handle. In a multithreaded scenario, the method will prevent the slot from being modified during the execution of the function. @param SlotHandle Handle to a smart object slot. @param Function Function to execute if a valid view can be created @return Whether the slot was found, was valid, and the function was called @see MutateSlotData
- L778 _public prototype_ `bool MutateSlotData(const FSmartObjectSlotHandle& SlotHandle, TFunctionRef<void(const FSmartObjectSlotView&)> Function) const;` — Executes the provided function if a valid mutable view can be created for the provided slot handle. In a multithreaded scenario, the method will prevent the slot from being modified during the execution of the function. @param SlotHandle Handle to a smart object slot. @param Function Function to execute if a valid view can be created @return Whether the slot was found, was valid, and the function was called @see ReadSlotData
- L785 _public function_ `TOptional<FVector> GetSlotLocation(const FSmartObjectClaimHandle& ClaimHandle) const` — Returns the position (in world space) of the slot associated to the given claim handle. @param ClaimHandle Handle to a claimed slot returned by any of the Claim methods. @return Position (in world space) of the slot associated to ClaimHandle.
- L797 _public prototype_ `bool GetSlotLocation(const FSmartObjectClaimHandle& ClaimHandle, FVector& OutSlotLocation) const;` — `UFUNCTION(BlueprintCallable, Category = "SmartObject")` — Returns the position (in world space) of the slot associated to the given claim handle. @param ClaimHandle Handle to a claimed slot returned by any of the Claim methods. @param OutSlotLocation Position (in world space) of the slot associated to ClaimHandle. @return Whether the location was found and assigned to 'OutSlotLocation'
- L804 _public prototype_ `TOptional<FVector> GetSlotLocation(const FSmartObjectRequestResult& Result) const;` — Returns the position (in world space) of the slot associated to the given request result. @param Result A request result returned by any of the Find methods. @return Position (in world space) of the slot associated to Result.
- L811 _public prototype_ `TOptional<FVector> GetSlotLocation(const FSmartObjectSlotHandle& SlotHandle) const;` — Returns the position (in world space) of the slot represented by the provided slot handle. @param SlotHandle Handle to a smart object slot. @return Position (in world space) of the slot associated to SlotHandle.
- L818 _public function_ `TOptional<FTransform> GetSlotTransform(const FSmartObjectClaimHandle& ClaimHandle) const` — Returns the transform (in world space) of the slot associated to the given claim handle. @param ClaimHandle Handle to a claimed slot returned by any of the Claim methods. @return Transform (in world space) of the slot associated to ClaimHandle.
- L830 _public prototype_ `bool GetSlotTransform(const FSmartObjectClaimHandle& ClaimHandle, FTransform& OutSlotTransform) const;` — `UFUNCTION(BlueprintCallable, Category = "SmartObject")` — Returns the transform (in world space) of the slot associated to the given claim handle. @param ClaimHandle Handle to a claimed slot returned by any of the Claim methods. @param OutSlotTransform Transform (in world space) of the slot associated to ClaimHandle. @return Whether the transform was found and assigned to 'OutSlotTransform'
- L837 _public prototype_ `TOptional<FTransform> GetSlotTransform(const FSmartObjectRequestResult& Result) const;` — Returns the transform (in world space) of the slot associated to the given request result. @param Result A request result returned by any of the Find methods. @return Transform (in world space) of the slot associated to Result.
- L846 _public prototype_ `bool GetSlotTransformFromRequestResult(const FSmartObjectRequestResult& RequestResult, FTransform& OutSlotTransform) const;` — `UFUNCTION(BlueprintCallable, Category = "SmartObject")` — Returns the transform (in world space) of the slot associated to the given RequestResult. @param RequestResult Result returned by any of the FindSmartObject(s) methods. @param OutSlotTransform Transform (in world space) of the slot associated to the RequestResult. @return Whether the transform was found and assigned to 'OutSlotTransform'
- L853 _public prototype_ `TOptional<FTransform> GetSlotTransform(const FSmartObjectSlotHandle& SlotHandle) const;` — Returns the transform (in world space) of the slot represented by the provided slot handle. @param SlotHandle Handle to a smart object slot. @return Transform (in world space) of the slot associated to SlotHandle.
- L861 _public prototype_ `FTransform GetSlotTransformChecked(const FSmartObjectSlotHandle& SlotHandle) const;` — Similarly to GetSlotTransform fetches the transform (in world space) of the indicated slot, but assumes the slot handle is valid and that the EntityManager is known. The burden of ensuring that's the case is on the caller. @param SlotHandle Handle to a smart object slot. @return Transform (in world space) of the slot associated to SlotHandle.
- L870 _public prototype_ `FConstStructView GetOwnerData(const FSmartObjectHandle Handle) const;` — Returns a view on the owner data for the smart object instance represented by the provided handle. @param Handle Handle to the smart object. @return Unvalidated view of the smart object instance owner data. @note The returned view points to data that is only valid as long as the object is registered so it should be read immediately after calling this method or stored in an instances struct.
- L878 _public prototype_ `const FGameplayTagContainer& GetInstanceTags(const FSmartObjectHandle Handle) const;` — `UFUNCTION(BlueprintCallable, Category = "SmartObject")` — Returns the list of tags associated to the smart object instance represented by the provided handle. @param Handle Handle to the smart object. @return Container of tags associated to the smart object instance.
- L886 _public prototype_ `void AddTagToInstance(const FSmartObjectHandle Handle, const FGameplayTag& Tag);` — `UFUNCTION(BlueprintCallable, Category = "SmartObject")` — Adds a single tag to the smart object instance represented by the provided handle. @param Handle Handle to the smart object. @param Tag Tag to add to the smart object instance.
- L894 _public prototype_ `void RemoveTagFromInstance(const FSmartObjectHandle Handle, const FGameplayTag& Tag);` — `UFUNCTION(BlueprintCallable, Category = "SmartObject")` — Removes a single tag from the smart object instance represented by the provided handle. @param Handle Handle to the smart object. @param Tag Tag to remove from the smart object instance.
- L903 _public prototype_ `FOnSmartObjectEvent* GetEventDelegate(const FSmartObjectHandle SmartObjectHandle);` — Returns pointer to the smart object instance event delegate. @param SmartObjectHandle Handle to the smart object. @return Pointer to object's delegate, or nullptr if instance doesn't exists. @note The delegate can be broadcast from any thread so it is the responsibility of the caller to make sure that the operations executed are safe.
- L911 _public prototype_ `const FGameplayTagContainer& GetSlotTags(const FSmartObjectSlotHandle SlotHandle) const;` — `UFUNCTION(BlueprintCallable, Category = "SmartObject")` — Returns the list of tags associated to the smart object slot represented by the provided handle. @param SlotHandle Handle to the smart object slot. @return Container of tags associated to the smart object instance, or empty container if slot was not valid.
- L919 _public prototype_ `void AddTagToSlot(const FSmartObjectSlotHandle SlotHandle, const FGameplayTag& Tag);` — `UFUNCTION(BlueprintCallable, Category = "SmartObject")` — Adds a single tag to the smart object slot represented by the provided handle. @param SlotHandle Handle to the smart object slot. @param Tag Tag to add to the smart object slot.
- L928 _public prototype_ `bool RemoveTagFromSlot(const FSmartObjectSlotHandle SlotHandle, const FGameplayTag& Tag);` — `UFUNCTION(BlueprintCallable, Category = "SmartObject")` — Removes a single tag from the smart object slot represented by the provided handle. @param SlotHandle Handle to the smart object slot. @param Tag Tag to remove from the smart object slot. @return True if the tag was removed.
- L937 _public prototype_ `bool SetSlotEnabled(const FSmartObjectSlotHandle SlotHandle, const bool bEnabled);` — `UFUNCTION(BlueprintCallable, Category = "SmartObject")` — Enables or disables the smart object slot represented by the provided handle. @param SlotHandle Handle to the smart object slot. @param bEnabled If true enables the slot, if false, disables the slot. @return Previous enabled state.
- L946 _public prototype_ `bool SendSlotEvent(const FSmartObjectSlotHandle& SlotHandle, const FGameplayTag EventTag, const FConstStructView Payload = FConstStructView());` — Sends event to a smart object slot. @param SlotHandle Handle to the smart object slot. @param EventTag Gameplay Tag describing the event type. @param Payload Struct payload for the event. @return True if the event was successfully sent.
- L956 _public prototype_ `FOnSmartObjectEvent* GetSlotEventDelegate(const FSmartObjectSlotHandle& SlotHandle);` — Returns pointer to the smart object changed delegate associated to the provided handle. The delegate is shared for all slots so listeners must filter using 'Event.SlotHandle'. @param SlotHandle Handle to the smart object slot. @return Pointer to slot's delegate, or nullptr if slot does not exists. @note The delegate can be broadcast from any thread so it is the responsibility of the caller to make sure that the operations executed are safe.
- L963 _public prototype_ `void RegisterSlotInvalidationCallback(const FSmartObjectClaimHandle& ClaimHandle, const FOnSlotInvalidated& Callback);` — Register a callback to be notified if the claimed slot is no longer available and user need to perform cleanup. @param ClaimHandle Handle to a claimed slot returned by any of the Claim methods. @param Callback Delegate that will be called to notify that a slot gets invalidated and can no longer be used.
- L969 _public prototype_ `void UnregisterSlotInvalidationCallback(const FSmartObjectClaimHandle& ClaimHandle);` — Unregisters a callback to be notified if the claimed slot is no longer available and user need to perform cleanup. @param ClaimHandle Handle to a claimed slot returned by any of the Claim methods.
- L972 _public prototype_ `void DebugDraw(FDebugRenderSceneProxy* DebugProxy) const;`
- L973 _public function_ `void DebugDrawCanvas(UCanvas* Canvas, APlayerController* PlayerController) const`
- L984 _public prototype_ `static void CreatePersistentCollectionFromDeprecatedData(UWorld& World, const ADEPRECATED_SmartObjectCollection& DeprecatedCollection);` — Special-purpose function used to set up an instance of ASmartObjectPersistentCollection with data from a given instance of ADEPRECATED_SmartObjectCollection
- L986 _public function_ `TConstArrayView<TWeakObjectPtr<ASmartObjectPersistentCollection>> GetRegisteredCollections() const`
- L991 _public function_ `TArrayView<TWeakObjectPtr<ASmartObjectPersistentCollection>> GetMutableRegisteredCollections()`
- L998 _public member_ `mutable FOnMainCollectionEvent OnMainCollectionChanged;`
- L999 _public member_ `mutable FOnMainCollectionEvent OnMainCollectionDirtied;`
- L1005 _protected prototype_ `bool UnregisterSmartObjectInternal(TNotNull<USmartObjectComponent*> SmartObjectComponent, const bool bDestroyRuntimeState);`
- L1011 _protected prototype_ `virtual void OnWorldComponentsUpdated(UWorld& World) override;` — Callback overridden to gather loaded collections, spawn missing one and set the main collection. @note we use this method instead of `Initialize` or `PostInitialize` so active level is set and actors registered.
- L1017 _protected prototype_ `virtual void OnWorldBeginPlay(UWorld& World) override;` — BeginPlay will push all objects stored in the collection to the runtime simulation and initialize octree using collection bounds.
- L1020 _protected prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;` — USubsystem BEGIN
- L1021 _protected prototype_ `virtual void Deinitialize() override;`
- L1022 _protected prototype_ `virtual bool ShouldCreateSubsystem(UObject* Outer) const override;`
- L1026 _protected prototype_ `void InitializeRuntime();` — Creates all runtime data using main collection
- L1029 _protected prototype_ `virtual void CleanupRuntime();` — Removes all runtime data
- L1034 _protected function_ `FSmartObjectRuntime* GetRuntimeInstanceInternal(const FSmartObjectHandle SmartObjectHandle)` — Returns the runtime instance associated to the provided handle
- L1042 _protected function_ `const FSmartObjectRuntime* GetRuntimeInstanceInternal(const FSmartObjectHandle SmartObjectHandle) const` — Returns the const runtime instance associated to the provided handle
- L1054 _protected prototype_ `bool IsSlotValidVerbose(const FSmartObjectSlotHandle& SlotHandle, const ANSICHAR* CallingFunctionName) const;` — Indicates if the handle is set and the slot referred to is still accessible in the simulation. Log is produced for any failing condition using provided LogContext. @param SlotHandle Handle to a smart object slot. @param CallingFunctionName String describing the context in which the method is called (e.g. caller function name). @return True if the handle is valid and its associated slot is accessible; false otherwise.
- L1066 _protected prototype_ `bool GetValidatedRuntimeAndSlotInternal(const FSmartObjectSlotHandle& SlotHandle, const FSmartObjectRuntime*& OutSmartObjectRuntime, const FSmartObjectRuntimeSlot*& OutSlot, const ANSICHAR* CallingFunctionName) const;` — Returns the const runtime instance associated to the provided handle. Method produces log messages with provided context if provided handle is not set or associated instance can't be found. @param SlotHandle Handle to a smart object slot. @param OutSmartObjectRuntime Runtime instance matching the slot handle. @param OutSlot Slot runtime matching the slot handle. @param CallingFunctionName String describing the context in which the method is called (e.g. caller function name). @return true if a valid matching runtime instance and slot were found. @see ExecuteOnValidatedRuntimeAndSlot
- L1077 _protected prototype_ `bool ExecuteOnValidatedRuntimeAndSlot(const FSmartObjectSlotHandle& SlotHandle, TFunctionRef<void(const FSmartObjectRuntime&, const FSmartObjectRuntimeSlot&)> Function, const ANSICHAR* CallingFunctionName) const;` — Executes the provided function using the runtime instance associated to the provided handle. Method produces log messages with provided context if provided handle is not set or associated instance can't be found. Method provides a thread safe way to read information from a runtime instance or from its slots. @param SlotHandle Handle to a smart object slot. @param Function Function to execute if a valid view can be created. @param CallingFunctionName String describing the context in which the method is called (e.g. caller function name). @return Whether the runtime instance and slot were found, were valid, and the function was called
- L1084 _protected prototype_ `bool GetValidatedMutableRuntimeAndSlotInternal(const FSmartObjectSlotHandle& SlotHandle, FSmartObjectRuntime*& OutSmartObjectRuntime, FSmartObjectRuntimeSlot*& OutSlot, const ANSICHAR* CallingFunctionName) const;` — Returns the mutable runtime instance associated to the provided handle Method produces log messages with provided context if provided handle is not set or associated instance can't be found. @see ExecuteOnValidatedMutableRuntimeAndSlot
- L1095 _protected prototype_ `bool ExecuteOnValidatedMutableRuntimeAndSlot(const FSmartObjectSlotHandle& SlotHandle, TFunctionRef<void(FSmartObjectRuntime&, FSmartObjectRuntimeSlot&)> Function, const ANSICHAR* CallingFunctionName) const;` — Executes the provided function using the runtime instance associated to the provided handle. Method produces log messages with provided context if provided handle is not set or associated instance can't be found. Method provides a thread safe way to modify a runtime instance or its slots. @param SlotHandle Handle to a smart object slot. @param Function Function to execute if a valid view can be created. @param CallingFunctionName String describing the context in which the method is called (e.g. caller function name). @return Whether the runtime instance and slot were found, were valid, and the function was called
- L1102 _protected prototype_ `const FSmartObjectRuntime* GetValidatedRuntimeInternal(const FSmartObjectHandle Handle, const ANSICHAR* CallingFunctionName) const;` — Returns the const runtime instance associated to the provided handle. Method produces log messages with provided context if provided handle is not set or associated instance can't be found. @see ExecuteOnValidatedRuntime
- L1113 _protected prototype_ `bool ExecuteOnValidatedRuntime(const FSmartObjectHandle SlotHandle, TFunctionRef<void(const FSmartObjectRuntime&)> Function, const ANSICHAR* CallingFunctionName) const;` — Executes the provided function using the runtime instance associated to the provided handle. Method produces log messages with provided context if provided handle is not set or associated instance can't be found. Method provides a thread safe way to read information from a runtime instance. @param SlotHandle Handle to a smart object slot. @param Function Function to execute if a valid view can be created. @param CallingFunctionName String describing the context in which the method is called (e.g. caller function name). @return Whether the runtime instance was found, was valid, and the function was called
- L1120 _protected prototype_ `FSmartObjectRuntime* GetValidatedMutableRuntimeInternal(const FSmartObjectHandle Handle, const ANSICHAR* CallingFunctionName) const;` — Returns the mutable runtime instance associated to the provided handle Method produces log messages with provided context if provided handle is not set or associated instance can't be found. @see ExecuteOnValidatedMutableRuntime
- L1131 _protected prototype_ `bool ExecuteOnValidatedMutableRuntime(const FSmartObjectHandle SlotHandle, TFunctionRef<void(FSmartObjectRuntime&)> Function, const ANSICHAR* CallingFunctionName) const;` — Executes the provided function using the runtime instance associated to the provided handle. Method produces log messages with provided context if provided handle is not set or associated instance can't be found. Method provides a thread safe way to modify a runtime instance. @param SlotHandle Handle to a smart object slot. @param Function Function to execute if a valid view can be created. @param CallingFunctionName String describing the context in which the method is called (e.g. caller function name). @return Whether the runtime instance was found, was valid, and the function was called
- L1133 _protected prototype_ `static void AddTagToInstanceInternal(FSmartObjectRuntime& SmartObjectRuntime, const FGameplayTag& Tag);`
- L1135 _protected prototype_ `static void RemoveTagFromInstanceInternal(FSmartObjectRuntime& SmartObjectRuntime, const FGameplayTag& Tag);`
- L1137 _protected prototype_ `static void OnSlotChangedInternal( const FSmartObjectRuntime& SmartObjectRuntime, const FSmartObjectRuntimeSlot& Slot, const FSmartObjectSlotHandle& SlotHandle, const ESmartObjectChangeReason Reason, const FConstStructView Payload = {}, const FGameplayTag ChangedTag = FGameplayTag());`
- L1150 _protected prototype_ `void FindSlotsInternal( const FSmartObjectHandle Handle, const FSmartObjectRuntime& SmartObjectRuntime, const FSmartObjectRequestFilter& Filter, TArray<FSmartObjectSlotHandle>& OutResults, const FConstStructView UserData, UE::SmartObject::FDefinitionFilterCache* DefinitionFilterCache = nullptr, UE::SmartObject::FPropertyBindingCache* PropertyCache = nullptr) const;` — Goes through all defined slots of smart object represented by SmartObjectRuntime and finds the ones matching the filter. @param DefinitionFilterCache (optional) cache for definition filter results, keyed by Definition pointer. Avoids redundant FindMatchingSlotDefinitionIndicesInternal calls when multiple objects share the same definition. @param PropertyCache (optional) cache for property binding layouts, keyed by (UserData type, Schema). Avoids TFieldIterator reflection overhead when multiple objects use the same UserData struct.
- L1163 _protected prototype_ `static void FindMatchingSlotDefinitionIndicesInternal(const USmartObjectDefinition& Definition, const FSmartObjectRequestFilter& Filter, UE::SmartObject::FSlotIndicesArray& OutValidIndices);` — Applies filter on provided definition and fills OutValidIndices with indices of all valid slots. Per-slot rejection reasons are recorded to Filter.DebugRejections->DefinitionRejections if set (WITH_SMARTOBJECT_DEBUG only).
- L1166 _protected prototype_ `static void FindMatchingSlotDefinitionIndicesInternal(const USmartObjectDefinition& Definition, const FSmartObjectRequestFilter& Filter, TArray<int32>& OutValidIndices);` — `UE_DEPRECATED(5.8, "Use the version with UE::SmartObject::FSlotIndicesArray.")`
- L1168 _protected prototype_ `void ExecuteOnSlotFilteredBySelectionConditions( const TConstStridedView<FSmartObjectSlotHandle> SlotsToFilter, const FConstStructView UserData, TFunctionRef<void(const int32 )> Function) const;`
- L1173 _protected prototype_ `static const USmartObjectBehaviorDefinition* GetBehaviorDefinitionInternal( const FSmartObjectRuntime& SmartObjectRuntime, const FSmartObjectSlotHandle& SlotHandle, TSubclassOf<USmartObjectBehaviorDefinition> DefinitionClass);`
- L1178 _protected prototype_ `const USmartObjectBehaviorDefinition* MarkSlotAsOccupiedInternal( FSmartObjectRuntime& SmartObjectRuntime, const FSmartObjectClaimHandle& ClaimHandle, TSubclassOf<USmartObjectBehaviorDefinition> DefinitionClass);`
- L1183 _protected prototype_ `void AbortAllInternal(const FSmartObjectHandle Handle, FSmartObjectRuntime& SmartObjectRuntime) const;`
- L1186 _protected prototype_ `void RegisterCollectionInstances();` — Make sure that all SmartObjectCollection actors from our associated world are registered.
- L1188 _protected prototype_ `void AddContainerToSimulation(const FSmartObjectContainer& InSmartObjectContainer);`
- L1193 _protected prototype_ `FSmartObjectRuntime* AddCollectionEntryToSimulationInternal( const FSmartObjectCollectionEntry& Entry, const USmartObjectDefinition& Definition, USmartObjectComponent* OwnerComponent);` — Registers a collection entry to the simulation and creates its associated runtime instance.
- L1204 _protected prototype_ `FSmartObjectRuntime* CreateRuntimeInstance(const FSmartObjectHandle Handle, const USmartObjectDefinition& Definition, const FBox& Bounds, USmartObjectComponent* OwnerComponent = nullptr);` — Initializes preconditions, adds to the space partition structure using the specified bounds and broadcasts event. @param SmartObjectRuntime The runtime instance of the smart object to initialize @param Bounds Bounds used to register the object in the space partition structure @return Pointer to the created runtime or nullptr if an error occurs.
- L1211 _protected prototype_ `FSmartObjectRuntime* AddComponentToSimulationInternal(TNotNull<USmartObjectComponent*> SmartObjectComponent, const FSmartObjectCollectionEntry& CollectionEntry);` — Registers a collection entry to the simulation and creates its associated runtime instance. @param SmartObjectComponent The component to add to the simulation and for which a runtime entry might be created or an existing one found @param CollectionEntry The associated collection entry that got created to add the component to the simulation.
- L1219 _protected prototype_ `void BindComponentToSimulationInternal(TNotNull<USmartObjectComponent*> SmartObjectComponent, FSmartObjectRuntime& SmartObjectRuntime) const;` — Binds a smart object component to an existing instance in the simulation and notifies that it has been bound. If a given SmartObjectComponent has not been registered yet an ensure will trigger. @param SmartObjectComponent The component to add to the simulation and for which a runtime instance must exist @param SmartObjectRuntime Associated runtime structure
- L1227 _protected prototype_ `void UnbindComponentFromSimulationInternal(TNotNull<USmartObjectComponent*> SmartObjectComponent, FSmartObjectRuntime& SmartObjectRuntime) const;` — Unbinds a smart object component from the given FSmartObjectRuntime instance. Note that the component is still registered to the subsystem. @param SmartObjectComponent The component to remove from the simulation @param SmartObjectRuntime runtime data representing the component being removed
- L1234 _protected prototype_ `bool RemoveRuntimeInstanceFromSimulationInternal(FSmartObjectRuntime& SmartObjectRuntime, USmartObjectComponent* SmartObjectComponent = nullptr);` — Removes a runtime instance from the simulation. Note that the component is still registered to the subsystem. @return whether the removal was successful
- L1241 _protected prototype_ `bool RemoveCollectionEntryFromSimulation(const FSmartObjectCollectionEntry& Entry);` — Finds the runtime instance associated to the collection entry and removes it from the simulation. Note that if there is an associated component it is still registered to the subsystem. @return whether the removal was successful
- L1247 _protected prototype_ `void RemoveComponentFromSimulation(TNotNull<USmartObjectComponent*> SmartObjectComponent);` — Finds the runtime instance associated to the component and removes it from the simulation. Note that the component is still registered to the subsystem.
- L1250 _protected prototype_ `void DestroyRuntimeInstanceInternal(const FSmartObjectHandle Handle, FSmartObjectRuntime& SmartObjectRuntime);` — Destroy SmartObjectRuntime contents as Handle's representation.
- L1258 _protected prototype_ `bool ActivateObjectPreconditionsInternal(const FWorldConditionContextData& ContextData, const FSmartObjectRuntime& SmartObjectRuntime) const;` — Activate preconditions on the main object. @param ContextData The context data to use for conditions evaluation @param SmartObjectRuntime Runtime struct associated to the smart object @return True if conditions are successfully activated; false otherwise
- L1267 _protected prototype_ `bool ActivateSlotPreconditionsInternal(FWorldConditionContextData& ContextData, const FSmartObjectRuntimeSlot& Slot, const FSmartObjectSlotHandle& SlotHandle) const;` — Activate preconditions on the specified slot. @param ContextData The context data to fill and use for conditions evaluation @param Slot Runtime struct associated to the smart object slot @param SlotHandle Handle to the smart object slot @return True if all conditions are successfully activated; false otherwise
- L1275 _protected prototype_ `bool TryActivatePreconditionsInternal(const FSmartObjectRuntime& SmartObjectRuntime) const;` — Activate preconditions on the main object and all its slots. Currently the conditions require an actor so this method will try to fetch it if it is currently dehydrated. @param SmartObjectRuntime Runtime struct associated to the smart object @return True if all conditions are successfully activated; false otherwise
- L1282 _protected prototype_ `void SetupConditionContextCommonDataInternal(FWorldConditionContextData& ContextData, const FSmartObjectRuntime& SmartObjectRuntime) const;` — Fills the provided context data with the smart object actor and handle associated to 'SmartObjectRuntime' and the subsystem. @param ContextData The context data to fill @param SmartObjectRuntime The runtime instance of the smart object for which the context must be filled
- L1289 _protected prototype_ `void BindPropertiesFromStructInternal(FWorldConditionContextData& ContextData, const FConstStructView& UserData, UE::SmartObject::FPropertyBindingCache* PropertyCache = nullptr) const;` — Binds properties of the context data to property values of the user data struct when they match type and name. @param ContextData The context data to fill @param UserData Additional data that could be provided to bind values in the conditions evaluation context
- L1300 _protected prototype_ `[[nodiscard]] bool EvaluateSlotConditionsInternal( FWorldConditionContextData& ConditionContextData, const FSmartObjectRuntime& SmartObjectRuntime, const FSmartObjectSlotHandle& SlotHandle) const;` — Use the provided context data that is expected to be already filled by calling 'SetupConditionContextCommonData' and adds the slot related part. It then evaluates all conditions associated to the specified slot. @param ConditionContextData The context data to fill and use for conditions evaluation @param SmartObjectRuntime Runtime struct associated to the smart object slot @param SlotHandle Handle to the smart object slot @return True if all conditions are met; false otherwise @see SetupDefaultConditionsContext
- L1312 _protected prototype_ `[[nodiscard]] bool EvaluateObjectConditionsInternal(const FWorldConditionContextData& ConditionContextData, const FSmartObjectRuntime& SmartObjectRuntime) const;` — Use the provided context data that is expected to be already filled by calling 'SetupConditionContextCommonData' and evaluates all conditions associated to the specified object. @param ConditionContextData The context data to use for conditions evaluation @param SmartObjectRuntime Runtime data representing the smart object for which the conditions must be evaluated @return True if all conditions are met; false otherwise
- L1318 _protected prototype_ `[[nodiscard]] bool EvaluateConditionsForFilteringInternal( const FSmartObjectRuntime& SmartObjectRuntime, const FSmartObjectSlotHandle& SlotHandle, FWorldConditionContextData& ContextData, const FConstStructView UserData, TPair<const FSmartObjectRuntime*, bool>& LastEvaluatedRuntime) const;` — Internal helper for filter methods to build the list of accepted slots by reusing context data and schema as much as possible.
- L1334 _protected prototype_ `bool FindEntranceLocationInternal( const FSmartObjectSlotHandle& SlotHandle, const FSmartObjectSlotEntranceHandle& SlotEntranceHandle, const FSmartObjectSlotEntranceLocationRequest& Request, FSmartObjectSlotEntranceLocationResult& OutResult) const;` — Finds entrance location for a specific slot. Each slot can be annotated with multiple entrance locations, and the request can be configured to also consider the slot location as one entry. Additionally the entrance locations can be checked to be on navigable surface (does not check that the point is reachable, though), traced on ground, and without of collisions. @param SlotHandle Handle to the smart object slot. @param SlotEntranceHandle Handle to specific entrance if just one entrance should be checked. (Optional) @param Request Request describing how to select the entry. @param OutResult Entry location result (in world space). @return True if valid entry found.
- L1352 _protected prototype_ `static void QueryValidatedSlotEntranceLocationsInternal( const UWorld* World, FSmartObjectValidationContext& ValidationContext, const FSmartObjectSlotEntranceLocationRequest& Request, const FSmartObjectSlotHandle& SlotHandle, const FSmartObjectSlotDefinition& SlotDefinition, const FTransform& SlotTransform, const FSmartObjectSlotEntranceHandle& SlotEntranceHandle, TFunctionRef<bool(const FSmartObjectSlotEntranceLocationResult&)> ResultFunc);` — Validates entrance locations for a specific slot. Each slot can be annotated with multiple entrance locations, and the request can be configured to also consider the slot location as one entry. Additionally the entrance locations can be checked to be on navigable surface (does not check that the point is reachable, though), traced on ground, and without of collisions. @param World World to use for validation tracing. @param ValidationContext Valid validation context. @param Request Request describing how to validate the entries. @param SlotHandle Handle to the smart object slot (will be passed into the result). @param SlotDefinition Smart object slot definition to use for validation. @param SlotTransform Transform of the slot. @param SlotEntranceHandle Handle to specific entrance if just one entrance should be checked. (Optional) @param ResultFunc Callback called on each result
- L1369 _protected member_ `FSoftClassPath SpacePartitionClassName;` — `UPROPERTY(config, meta=(MetaClass="/Script/SmartObjectsModule.SmartObjectSpacePartition", DisplayName="Spatial Representation Structure Class"))` — Name of the Space partition class to use. Usage: [/Script/SmartObjectsModule.SmartObjectSubsystem] SpacePartitionClassName=/Script/SmartObjectsModule.<SpacePartitionClassName>
- L1372 _protected member_ `TSubclassOf<USmartObjectSpacePartition> SpacePartitionClass;` — `UPROPERTY()`
- L1375 _protected member_ `TObjectPtr<USmartObjectSpacePartition> SpacePartition;` — `UPROPERTY()`
- L1378 _protected member_ `TObjectPtr<ASmartObjectSubsystemRenderingActor> RenderingActor;` — `UPROPERTY()`
- L1381 _protected member_ `FSmartObjectContainer SmartObjectContainer;` — `UPROPERTY(Transient)`
- L1383 _protected member_ `TArray<TWeakObjectPtr<ASmartObjectPersistentCollection>> RegisteredCollections;`
- L1392 _protected member_ `TMap<FSmartObjectHandle, FSmartObjectRuntime> RuntimeSmartObjects;` — `UPROPERTY(Transient)` — A map of registered smart object handles to their associated runtime data. Client side smart object Subsystem's will only have runtime data for smart object Components who enable replication, but server subsystems will have all smart object data.
- L1396 _protected member_ `TArray<TObjectPtr<USmartObjectComponent>> RegisteredSOComponents;` — `UPROPERTY(Transient)` — List of registered components.
- L1400 _protected member_ `TArray<TObjectPtr<USmartObjectComponent>> PendingSmartObjectRegistration;` — `UPROPERTY(Transient)` — smart objects that attempted to register while no collection was being present
- L1403 _protected prototype_ `UE_MT_DECLARE_RW_FULLY_RECURSIVE_ACCESS_DETECTOR(RuntimeInstanceListAccessDetector);` — Multithreading access detector to validate accesses to the list of runtime smart object instances
- L1406 _protected prototype_ `UE_MT_DECLARE_RW_FULLY_RECURSIVE_ACCESS_DETECTOR(SingleRuntimeInstanceAccessDetector);` — Multithreading access detector to validate accesses to single smart object instance
- L1410 _protected member_ `mutable FTransactionallySafeCriticalSection RuntimeInstanceLock;` — Critical section used to protect read/write operations on a smart object instance and its slots
- L1413 _protected member_ `uint32 NextFreeUserID = 1;`
- L1415 _protected member_ `bool bRuntimeInitialized = false;`
- L1418 _protected prototype_ `bool IsRunningOnServer() const;` — Returns true if this subsystem is running on the server.
- L1421 _protected member_ `bool bAutoInitializeEditorInstances = true;`
- L1426 _protected member_ `bool bIsPartitionedWorld = false;` — Set in OnWorldComponentsUpdated and used to control special logic required to build collections in Editor mode
- L1430 _protected prototype_ `void PopulateCollection(ASmartObjectPersistentCollection& InCollection) const;`
- L1433 _protected prototype_ `void IterativelyBuildCollections();` — Iteratively adds items to registered collections. Expected to be called in World Partitined worlds.
- L1435 _protected prototype_ `int32 GetRegisteredSmartObjectsCompatibleWithCollection(const ASmartObjectPersistentCollection& InCollection, TArray<USmartObjectComponent*>& OutRelevantComponents) const;`
- L1441 _protected prototype_ `FBox ComputeBounds(const UWorld& World) const;` — Compute bounds from the given world @param World World from which the bounds must be computed
- L1446 _public function_ `uint32 DebugGetNumRuntimeObjects() const`
- L1451 _public function_ `const TMap<FSmartObjectHandle, FSmartObjectRuntime>& DebugGetRuntimeObjects() const`
- L1456 _public function_ `uint32 DebugGetNumRegisteredComponents() const`
- L1462 _public prototype_ `void DebugUnregisterAllSmartObjects();` — Debugging helper to remove all registered smart objects from the simulation
- L1465 _public prototype_ `void DebugRegisterAllSmartObjects();` — Debugging helpers to add all registered smart objects to the simulation
- L1468 _public prototype_ `void DebugInitializeRuntime();` — Debugging helper to emulate the start of the simulation to create all runtime data
- L1471 _public prototype_ `void DebugCleanupRuntime();` — Debugging helper to emulate the stop of the simulation to destroy all runtime data
- L1478 _public function_ `bool FindSmartObjects(const FSmartObjectRequest& Request, TArray<FSmartObjectRequestResult>& OutResults, const AActor* UserActor = nullptr) const` — `UFUNCTION(BlueprintCallable, Category = "SmartObject", meta=(DisplayName="Find Smart Objects (Pure)", DeprecatedFunction, DeprecationMessage="The pure version is deprecated, place a new Find Smart Objects node and connect the exec pin"))`
- L1484 _public function_ `bool Release(const FSmartObjectClaimHandle& ClaimHandle)` — `UFUNCTION(BlueprintCallable, Category = "SmartObject", meta = (DeprecatedFunction, DeprecationMessage = "Use MarkSmartObjectSlotAsFree instead."))`

#### struct `TMassExternalSubsystemTraits`  
`template<> struct TMassExternalSubsystemTraits<USmartObjectSubsystem> final`  
_L1493-1500_

#### enum `TMassExternalSubsystemTraits::(anonymous)`  
``  
_L1496-1499_

#### Free symbols / members of external scopes

- L16 _macro_ `#define WITH_SMARTOBJECT_MT_INSTANCE_LOCK 0`
- L42 _namespace_ `namespace UE`
- L42 _namespace_ `namespace SmartObject` (scope `UE`)
- L44 _typedef_ `using FSlotIndicesArray = TArray<int32, TInlineAllocator<16>>;` (scope `UE::SmartObject`)
- L45 _typedef_ `using FDefinitionFilterCache = TMap<const USmartObjectDefinition*, FSlotIndicesArray>;` (scope `UE::SmartObject`)
- L51 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnMainCollectionEvent);` — Called when an event related to the main collection occured.
- L51 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnMainCollectionEvent);` — Called when an event related to the main collection occured.
- L110 _typedef_ `using IndexType = decltype(Index);` (scope `FSmartObjectSlotEntranceHandle::FSmartObjectSlotEntranceHandle`)
- L259 _typedef_ `using FSmartObjectSlotNavigationLocationResult = FSmartObjectSlotEntranceLocationResult;`
- L1497 _enumerator_ `GameThreadOnly = false` (scope `TMassExternalSubsystemTraits::__anonb9b995d10103`)
- L1498 _enumerator_ `ThreadSafeWrite = true` (scope `TMassExternalSubsystemTraits::__anonb9b995d10103`)

### `Plugins/Runtime/SmartObjects/Source/SmartObjectsModule/Public/SmartObjectTypes.h` (Public)


#### enum `ESmartObjectTagMergingPolicy`  
`enum class ESmartObjectTagMergingPolicy : uint8`  
_L44-50_
- reflection: `UENUM()`
- desc: Indicates how Tags from slots and parent object are combined to be evaluated by a TagQuery from a find request.
- L47 _public enumerator_ `Combine` — Tags are combined (parent object and slot) and TagQuery from the request will be run against the combined list.
- L49 _public enumerator_ `Override` — Tags in slot (if any) will be used instead of the parent object Tags when running the TagQuery from a request. Empty Tags on a slot indicates no override.

#### enum `ESmartObjectTagFilteringPolicy`  
`enum class ESmartObjectTagFilteringPolicy : uint8`  
_L55-63_
- reflection: `UENUM()`
- desc: Indicates how TagQueries from slots and parent object will be processed against Tags from a find request.
- L58 _public enumerator_ `NoFilter` — TagQueries in the object and slot definitions are not used by the framework to filter results. Users can access them and perform its own filtering.
- L60 _public enumerator_ `Combine` — Both TagQueries (parent object and slot) will be applied to the Tags provided by a request.
- L62 _public enumerator_ `Override` — TagQuery in slot (if any) will be used instead of the parent object TagQuery to run against the Tags provided by a request. EmptyTagQuery on a slot indicates no override.

#### enum `ESmartObjectSlotNavigationLocationType`  
`enum class ESmartObjectSlotNavigationLocationType : uint8`  
_L69-76_
- reflection: `UENUM()`
- desc: Enum indicating if we're looking for a location to enter or exit the Smart Object slot.
- L72 _public enumerator_ `Entry` — Find a location to enter the slot.
- L75 _public enumerator_ `Exit` — Find a location to exit the slot.

#### enum `ESmartObjectClaimPriority`  
`enum class ESmartObjectClaimPriority : uint8`  
_L80-92_
- reflection: `UENUM(BlueprintType)`
- desc: Enum indicating the claim priority of a Smart Object slot.
- L82 _public enumerator_ `None UMETA(Hidden)`
- L84 _public enumerator_ `Low`
- L85 _public enumerator_ `BelowNormal`
- L86 _public enumerator_ `Normal`
- L87 _public enumerator_ `AboveNormal`
- L88 _public enumerator_ `High`
- L90 _public enumerator_ `MIN = None UMETA(Hidden)`
- L91 _public enumerator_ `MAX = High UMETA(Hidden)`

#### struct `FSmartObjectUserHandle`  
`struct FSmartObjectUserHandle`  
_L98-143_
- reflection: `USTRUCT()`
- desc: Handle to a smartobject user.
- L103 _public prototype_ `FSmartObjectUserHandle() = default;`
- L105 _public function_ `bool IsValid() const`
- L110 _public function_ `void Invalidate()`
- L115 _public function_ `bool operator==(const FSmartObjectUserHandle& Other) const`
- L120 _public function_ `bool operator!=(const FSmartObjectUserHandle& Other) const`
- L134 _private function_ `explicit FSmartObjectUserHandle(const uint32 InID) : ID(InID)`
- L139 _private member_ `uint32 ID = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category = SmartObject)`
- L142 _public member_ `static const FSmartObjectUserHandle Invalid;`

#### struct `FSmartObjectHandle`  
`struct FSmartObjectHandle`  
_L150-205_
- reflection: `USTRUCT(BlueprintType)`
- desc: Handle to a registered smartobject.
- L155 _public prototype_ `FSmartObjectHandle() = default;`
- L161 _public function_ `bool IsValid() const` — Indicates that the handle was properly assigned but doesn't guarantee that the associated object is still accessible. This information requires a call to `USmartObjectSubsystem::IsObjectValid` using the handle.
- L166 _public function_ `void Invalidate()`
- L176 _public prototype_ `bool operator==(const FSmartObjectHandle& Other) const = default;`
- L177 _public prototype_ `bool operator!=(const FSmartObjectHandle& Other) const = default;`
- L180 _public function_ `bool operator<(const FSmartObjectHandle& Other) const` — Has meaning only for sorting purposes (can't use default version since it is not available in FGuid)
- L194 _private function_ `explicit FSmartObjectHandle(const FGuid InID) : Guid(InID)`
- L199 _private member_ `FGuid Guid = InvalidID;` — `UPROPERTY(VisibleAnywhere, Category = SmartObject)`
- L201 _private member_ `static constexpr FGuid InvalidID = FGuid();`
- L204 _public member_ `static const FSmartObjectHandle Invalid;`

#### struct `FSmartObjectSlotHandle`  
`struct FSmartObjectSlotHandle`  
_L212-290_
- reflection: `USTRUCT(BlueprintType)`
- desc: Struct used to identify a runtime slot instance
- L217 _public prototype_ `FSmartObjectSlotHandle() = default;`
- L223 _public function_ `bool IsValid() const` — Indicates that the handle was properly assigned but doesn't guarantee that the associated slot is still accessible. This information requires a call to `USmartObjectSubsystem::IsSlotValid` using the handle.
- L228 _public function_ `void Invalidate()`
- L234 _public function_ `bool operator==(const FSmartObjectSlotHandle Other) const`
- L239 _public function_ `bool operator!=(const FSmartObjectSlotHandle Other) const`
- L245 _public function_ `bool operator<(const FSmartObjectSlotHandle Other) const` — Has meaning only for sorting purposes
- L264 _public function_ `FSmartObjectHandle GetSmartObjectHandle() const`
- L269 _public function_ `int32 GetSlotIndex() const`
- L279 _protected function_ `FSmartObjectSlotHandle(const FSmartObjectHandle InSmartObjectHandle, const int32 SlotIndex) : SmartObjectHandle(InSmartObjectHandle) , SlotIndex(SlotIndex)`
- L286 _protected member_ `FSmartObjectHandle SmartObjectHandle;` — `UPROPERTY(VisibleAnywhere, Category = SmartObject, transient)`
- L289 _protected member_ `int32 SlotIndex = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category = SmartObject, transient)`

#### struct `FSmartObjectDefinitionData`  
`struct FSmartObjectDefinitionData`  
_L297-301_
- reflection: `USTRUCT(BlueprintType, meta=(Hidden))`
- desc: This is the base struct to inherit from to store custom definition data within the main slot definition
- L300 _public prototype_ `virtual ~FSmartObjectDefinitionData() = default;`

#### struct `FSmartObjectSlotStateData`  
`struct FSmartObjectSlotStateData`  
_L307-310_
- reflection: `USTRUCT(meta=(Hidden))`
- desc: This is the base struct to inherit from to store custom state data associated to a slot

#### struct `FSmartObjectSpatialEntryData`  
`struct FSmartObjectSpatialEntryData`  
_L316-319_
- reflection: `USTRUCT()`
- desc: This is the base struct to inherit from to store some data associated to a specific entry in the spatial representation structure

#### class `USmartObjectSpacePartition`  
`class USmartObjectSpacePartition : public UObject`  
_L325-351_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UObject`
- desc: Base class for space partitioning structure that can be used to store smart object locations
- L330 _public function_ `virtual void SetBounds(const FBox& Bounds)`
- L334 _public function_ `virtual void Add(const FSmartObjectHandle Handle, const FBox& Bounds, FInstancedStruct& OutHandle)`
- L338 _public function_ `virtual void Remove(const FSmartObjectHandle Handle, FStructView EntryData)`
- L342 _public function_ `virtual void Find(const FBox& QueryBox, TArray<FSmartObjectHandle>& OutResults)`
- L347 _public function_ `virtual void Draw(FDebugRenderSceneProxy* DebugProxy)`

#### struct `FSmartObjectSlotIndex`  
`struct UE_DEPRECATED(all, "This type is deprecated and no longer being used.") FSmartObjectSlotIndex`  
_L358-394_
- reflection: `USTRUCT(BlueprintType)`
- desc: Helper struct to wrap basic functionalities to store the index of a slot in a SmartObject definition
- L362 _public function_ `explicit FSmartObjectSlotIndex(const int32 InSlotIndex = INDEX_NONE) : Index(InSlotIndex)`
- L366 _public function_ `bool IsValid() const`
- L371 _public function_ `void Invalidate()`
- L376 _public function_ `operator int32() const`
- L381 _public function_ `bool operator==(const FSmartObjectSlotIndex& Other) const`
- L393 _private member_ `int32 Index = INDEX_NONE;` — `UPROPERTY(Transient)`

#### struct `FSmartObjectSlotReference`  
`struct FSmartObjectSlotReference`  
_L401-446_
- reflection: `USTRUCT()`
- desc: Reference to a specific Smart Object slot in a Smart Object Definition. When placed on a slot definition data, the Index is resolved automatically when changed, on load and save.
- L405 _public member_ `static constexpr uint8 InvalidValue = 0xff;`
- L407 _public function_ `bool IsValid() const`
- L412 _public function_ `int32 GetIndex() const`
- L417 _public function_ `void SetIndex(const int32 InIndex)`
- L430 _public function_ `const FGuid& GetSlotID() const`
- L438 _private member_ `uint8 Index = InvalidValue;` — `UPROPERTY()`
- L442 _private member_ `FGuid SlotID;` — `UPROPERTY()`

#### enum `ESmartObjectTraceType`  
`enum class ESmartObjectTraceType : uint8`  
_L452-457_
- reflection: `UENUM()`
- desc: Indicates how TagQueries from slots and parent object will be processed against Tags from a find request.
- L454 _public enumerator_ `ByChannel`
- L455 _public enumerator_ `ByProfile`
- L456 _public enumerator_ `ByObjectTypes`

#### struct `FSmartObjectTraceParams`  
`struct FSmartObjectTraceParams`  
_L461-507_
- reflection: `USTRUCT()`
- desc: Struct used to define how traces should be handled.
- L465 _public prototype_ `FSmartObjectTraceParams() = default;`
- L467 _public function_ `explicit FSmartObjectTraceParams(const ETraceTypeQuery InTraceChanel) : Type(ESmartObjectTraceType::ByChannel) , TraceChannel(InTraceChanel)`
- L473 _public function_ `explicit FSmartObjectTraceParams(TConstArrayView<EObjectTypeQuery> InObjectTypes) : Type(ESmartObjectTraceType::ByObjectTypes)`
- L482 _public function_ `explicit FSmartObjectTraceParams(const FCollisionProfileName InCollisionProfileName) : Type(ESmartObjectTraceType::ByProfile) , CollisionProfile(InCollisionProfileName)`
- L490 _public member_ `ESmartObjectTraceType Type = ESmartObjectTraceType::ByChannel;` — `UPROPERTY(EditAnywhere, Category = "Default")` — Type of trace to use.
- L494 _public member_ `TEnumAsByte<ETraceTypeQuery> TraceChannel = ETraceTypeQuery::TraceTypeQuery1;` — `UPROPERTY(EditAnywhere, Category = "Default", meta = (EditCondition = "Type == ESmartObjectTraceType::ByChannel", EditConditionHides))` — Trace channel to use to determine collisions.
- L498 _public member_ `TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;` — `UPROPERTY(EditAnywhere, Category = "Default", meta = (EditCondition = "Type == ESmartObjectTraceType::ByObjectTypes", EditConditionHides))` — Object types to use to determine collisions.
- L502 _public member_ `FCollisionProfileName CollisionProfile;` — `UPROPERTY(EditAnywhere, Category = "Default", meta = (EditCondition = "Type == ESmartObjectTraceType::ByProfile", EditConditionHides))` — Collision profile to use to determine collisions.
- L506 _public member_ `bool bTraceComplex = false;` — `UPROPERTY(EditAnywhere, Category = "Default")` — Whether we should trace against complex collision

#### struct `FSmartObjectAnnotationCollider`  
`struct FSmartObjectAnnotationCollider`  
_L510-520_
- desc: Struct defining a collider in world space.
- L513 _public member_ `FVector Location = FVector::ZeroVector;` — Location of the collision shape.
- L516 _public member_ `FQuat Rotation = FQuat::Identity;` — Rotation of the collision shape.
- L519 _public member_ `FCollisionShape CollisionShape;` — Shape of the collider.

#### struct `FSmartObjectUserCapsuleParams`  
`struct FSmartObjectUserCapsuleParams`  
_L524-564_
- reflection: `USTRUCT(BlueprintType)`
- desc: Struct defining Smart Object user capsule size.
- L528 _public prototype_ `FSmartObjectUserCapsuleParams() = default;`
- L529 _public function_ `FSmartObjectUserCapsuleParams(const float InRadius, const float InHeight, const float InStepHeight) : Radius(InRadius) , Height(InHeight) , StepHeight(InStepHeight)`
- L537 _public member_ `static const FSmartObjectUserCapsuleParams Invalid;` — Invalid capsule.
- L539 _public function_ `bool IsValid() const`
- L551 _public prototype_ `FSmartObjectAnnotationCollider GetAsCollider(const FVector& Location, const FQuat& Rotation) const;` — Returns the capsule as an annotation collider at specified world location and rotation. The capsule is placed so that Z-axis of the rotation is considered up. The values specified in the struct will be constrained to create valid collider (and thus can differ from the set values). @param Location Location of the collider. @param Rotation Rotation of the collider. @return annotation collider representing the capsule.
- L555 _public member_ `float Radius = 35.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", meta = (ClampMin = "0.0"))` — Radius of the capsule
- L559 _public member_ `float Height = 180.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", meta = (ClampMin = "0.0"))` — Full height of the capsule
- L563 _public member_ `float StepHeight = 50.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", meta = (ClampMin = "0.0"))` — Step up height. This space is ignored when testing collisions.

#### struct `FSmartObjectSlotValidationParams`  
`struct FSmartObjectSlotValidationParams`  
_L570-654_
- reflection: `USTRUCT()`
- desc: Parameters for Smart Object navigation and collision validation.
- L576 _public function_ `TSubclassOf<UNavigationQueryFilter> GetNavigationFilter() const` — @return navigation filter class to be used for navigation checks.
- L582 _public function_ `FVector GetSearchExtents() const` — @return search extents used to define how far the validation can move the points.
- L588 _public function_ `const FSmartObjectTraceParams& GetGroundTraceParameters() const` — @return trace parameters for finding ground location.
- L594 _public function_ `const FSmartObjectTraceParams& GetTransitionTraceParameters() const` — @return trace parameters for testing if there are collision transitioning from navigation location to slot location.
- L600 _public function_ `const FSmartObjectUserCapsuleParams& GetUserCapsule() const` — @return reference to user capsule parameters.
- L609 _public prototype_ `const FSmartObjectUserCapsuleParams& GetUserCapsule(const FSmartObjectUserCapsuleParams& NavigationCapsule) const;` — Selects between specified NavigationCapsule size and capsule size defined in the params based on bUseNavigationCapsuleSize. @param NavigationCapsule Size of the navigation capsule. @return reference to selected capsule.
- L617 _public prototype_ `bool GetUserCapsuleForActor(const AActor& UserActor, FSmartObjectUserCapsuleParams& OutCapsule) const;` — Gets user capsule for a specified actor, if bUseNavigationCapsuleSize is specified uses INavAgentInterface to forward the values from navigation system. The method can fail if the navigation capsule is requested, but we fail to get the navigation properties from the actor. @param UserActor Actor used to look up navigation settings from. @param OutCapsule Dimensions of the user capsule. @return true operation succeeds.
- L625 _public prototype_ `bool GetPreviewUserCapsule(const UWorld& World, FSmartObjectUserCapsuleParams& OutCapsule) const;` — Gets default user capsule size used for preview when the user actor is now known. The method can fail if the navigation capsule is requested, but we fail to get the navigation properties from the world. @param World where to look for default navigation settings. @param OutCapsule Dimensions of the user capsule. @return true if operation succeeds.
- L630 _protected member_ `TSubclassOf<UNavigationQueryFilter> NavigationFilter;` — `UPROPERTY(EditAnywhere, Category = "Default")` — Navigation filter used to validate entrance locations.
- L634 _protected member_ `FVector SearchExtents = FVector(5.0f, 5.0f, 40.0f);` — `UPROPERTY(EditAnywhere, Category = "Default")` — How far we allow the validated location to be from the specified navigation location.
- L638 _protected member_ `FSmartObjectTraceParams GroundTraceParameters;` — `UPROPERTY(EditAnywhere, Category = "Default")` — Trace parameters used for finding navigation location on ground.
- L642 _protected member_ `FSmartObjectTraceParams TransitionTraceParameters;` — `UPROPERTY(EditAnywhere, Category = "Default")` — Trace parameters user for checking if the transition between navigation location and slot is unblocked.
- L646 _protected member_ `bool bUseNavigationCapsuleSize = false;` — `UPROPERTY(EditAnywhere, Category = "Default")` — If true, the capsule size is queried from the user actor via INavAgentInterface.
- L653 _protected member_ `FSmartObjectUserCapsuleParams UserCapsule;` — `UPROPERTY(EditAnywhere, Category = "Default")` — Dimensions of the capsule used for testing if user can fit into a specific location. If bUseNavigationCapsuleSize is set, the capsule size from the Actor navigation settings is used if the actor is present (otherwise we fallback to the UserCapsule).

#### class `USmartObjectSlotValidationFilter`  
`class USmartObjectSlotValidationFilter : public UObject`  
_L665-701_
- reflection: `UCLASS(MinimalAPI, Blueprintable, Abstract)`
- inherits: `UObject`
- desc: Class used to define settings for Smart Object navigation and collision validation. It is possible to specify two set of validation parameters. The one labeled "entry" is used for validating entry locations and other general collision validation. A separate set can be defined for checking exit locations. This allows the exit location checking to be relaxed. E.g. we might not allow to enter the SO on water area, but it is fine to exit on water. The values of the CDO are used, the users are expected to derive from this class to create custom settings.
- L672 _public function_ `const FSmartObjectSlotValidationParams& GetValidationParams(const ESmartObjectSlotNavigationLocationType LocationType) const` — @return validation parameters based on location type (enter & exit)
- L678 _public function_ `const FSmartObjectSlotValidationParams& GetEntryValidationParams() const` — @return validation parameters for entry validation, and general use.
- L684 _public function_ `const FSmartObjectSlotValidationParams& GetExitValidationParams() const` — @return validation parameters for exit validation.
- L692 _protected member_ `FSmartObjectSlotValidationParams EntryParameters;` — `UPROPERTY(EditAnywhere, Category = "Default")` — Parameters to use for validating entry locations or general collision validation.
- L696 _protected member_ `bool bUseEntryParametersForExit = true;` — `UPROPERTY(EditAnywhere, Category = "Default")` — If true, use separate settings for validating exit locations.
- L700 _protected member_ `FSmartObjectSlotValidationParams ExitParameters;` — `UPROPERTY(EditAnywhere, Category = "Default", meta = (EditCondition = "bUseEntryParametersForExit == false", EditConditionHides))` — Parameters to use for validating exit locations. The separate set allows to specify looser settings on exits.

#### enum `ESmartObjectChangeReason`  
`enum class ESmartObjectChangeReason : uint8`  
_L707-735_
- reflection: `UENUM(BlueprintType)`
- desc: Describes how Smart Object or slot was changed.
- L710 _public enumerator_ `None` — No Change.
- L712 _public enumerator_ `OnEvent` — External event sent.
- L714 _public enumerator_ `OnTagAdded` — A tag was added.
- L716 _public enumerator_ `OnTagRemoved` — A tag was removed.
- L718 _public enumerator_ `OnClaimed` — Slot was claimed.
- L720 _public enumerator_ `OnOccupied` — Slot is now occupied
- L722 _public enumerator_ `OnReleased` — Slot claim was released.
- L724 _public enumerator_ `OnSlotEnabled` — Slot was enabled.
- L726 _public enumerator_ `OnSlotDisabled` — Slot was disabled.
- L728 _public enumerator_ `OnObjectEnabled` — Object was enabled.
- L730 _public enumerator_ `OnObjectDisabled` — Object was disabled.
- L732 _public enumerator_ `OnComponentBound` — Related Smart Object Component is bound to simulation.
- L734 _public enumerator_ `OnComponentUnbound` — Related Smart Object Component is unbound from simulation.

#### struct `FSmartObjectEventData`  
`struct FSmartObjectEventData`  
_L741-768_
- reflection: `USTRUCT(BlueprintType)`
- desc: Struct describing a change in Smart Object or Slot.
- L747 _public member_ `FSmartObjectHandle SmartObjectHandle;` — `UPROPERTY(Transient, BlueprintReadOnly, Category = "SmartObject")` — Handle to the changed Smart Object.
- L751 _public member_ `FSmartObjectSlotHandle SlotHandle;` — `UPROPERTY(Transient, BlueprintReadOnly, Category = "SmartObject")` — Handle to the changed slot, if invalid, the event is for the object.
- L755 _public member_ `ESmartObjectChangeReason Reason = ESmartObjectChangeReason::None;` — `UPROPERTY(Transient, BlueprintReadOnly, Category = "SmartObject")` — Change reason.
- L759 _public member_ `FGameplayTag Tag;` — `UPROPERTY(Transient, BlueprintReadOnly, Category = "SmartObject")` — Added/Removed tag, or event tag, depending on Reason.
- L767 _public member_ `FConstStructView EventPayload;` — Event payload. For external event (i.e. SendSlotEvent) payload is provided by the caller. For internal event types (e.g. OnClaimed, OnReleased, etc.) payload is the user data struct provided on claim.

#### struct `FSmartObjectActorUserData`  
`struct FSmartObjectActorUserData`  
_L802-811_
- reflection: `USTRUCT()`
- desc: Struct that can be used to pass data to the find or filtering methods. Properties will be used as user data to fill values expected by the world condition schema specified by the smart object definition. e.g. FilterSlotsBySelectionConditions(SlotHandles, FConstStructView::Make(FSmartObjectActorUserData(Pawn))); It can be inherited from to provide additional data to another world condition schema inheriting from USmartObjectWorldConditionSchema. e.g. UCLASS() class USmartObjectWorldConditionExtendedSchema : public USmartObjectWorldConditionSchema { ... USmartObjectWorldConditionExtendedSchema(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) { OtherActorRef = AddContextDataDesc(TEXT("OtherActor"), AActor::StaticClass(), EWorldConditionContextDataType::Dynamic); } FWorldConditionContextDataRef OtherActorRef; }; USTRUCT() struct FSmartObjectActorExtendedUserData : public FSmartObjectActorUserData { UPROPERTY() TWeakObjectPtr<const AActor> OtherActor = nullptr; } The struct can also be used to be added to a Smart Object slot when it gets claimed. e.g. Claim(SlotHandle, FConstStructView::Make(FSmartObjectActorUserData(Pawn)));
- L806 _public prototype_ `FSmartObjectActorUserData() = default;`
- L807 _public prototype_ `explicit FSmartObjectActorUserData(const AActor* InUserActor);`
- L810 _public member_ `TWeakObjectPtr<const AActor> UserActor = nullptr;` — `UPROPERTY()`

#### struct `FSmartObjectActorOwnerData`  
`struct FSmartObjectActorOwnerData`  
_L818-832_
- reflection: `USTRUCT()`
- desc: Struct that can be used to pass data related to the owner of a created SmartObject. It identifies an instanced actor that could be in its lightweight representation or a normal actor.
- L822 _public prototype_ `FSmartObjectActorOwnerData() = default;`
- L823 _public function_ `explicit FSmartObjectActorOwnerData(AActor* Actor): Handle(Actor)`
- L826 _public function_ `explicit FSmartObjectActorOwnerData(const FActorInstanceHandle& Handle) : Handle(Handle)`
- L831 _public member_ `FActorInstanceHandle Handle;` — `UPROPERTY()`

#### struct `FSmartObjectHandleFactory`  
`struct FSmartObjectHandleFactory`  
_L837-855_
- desc: Struct used as a friend to FSmartObjectHandle that is the only caller allowed to create a handle from a Guid.
- L839 _public function_ `static FSmartObjectHandle CreateHandleFromGuid(const FGuid Guid)`
- L844 _public function_ `static FSmartObjectHandle CreateHandleForDynamicObject()`
- L849 _public function_ `static FSmartObjectHandle CreateHandleFromComponent(const TNotNull<const USmartObjectComponent*> Component)`
- L854 _public prototype_ `static FGuid CreateHandleGuidFromComponent(TNotNull<const USmartObjectComponent*> Component);`

#### struct `FSmartObjectDefinitionDataHandle`  
`struct FSmartObjectDefinitionDataHandle`  
_L862-943_
- reflection: `USTRUCT()`
- desc: Used internally by USmartObjectDefinition to refer to a specific piece of data like the definition itself, its parameters struct, slot data, etc.
- L866 _public member_ `static const FSmartObjectDefinitionDataHandle Invalid;`
- L867 _public member_ `static const FSmartObjectDefinitionDataHandle Root;`
- L868 _public member_ `static const FSmartObjectDefinitionDataHandle Parameters;`
- L870 _public prototype_ `FSmartObjectDefinitionDataHandle() = default;`
- L872 _public function_ `explicit FSmartObjectDefinitionDataHandle(const int32 InSlotIndex, const int32 InDataIndex = INDEX_NONE)`
- L880 _public function_ `FSmartObjectDefinitionDataHandle& operator=(const FSmartObjectDefinitionDataHandle& Other)`
- L887 _public function_ `bool operator==(const FSmartObjectDefinitionDataHandle& Other) const`
- L892 _public function_ `bool operator!=(const FSmartObjectDefinitionDataHandle& Other) const`
- L897 _public function_ `bool IsSlotValid() const`
- L902 _public function_ `bool IsDataValid() const`
- L907 _public function_ `bool IsRoot() const`
- L912 _public function_ `bool IsParameters() const`
- L917 _public function_ `int32 GetSlotIndex() const`
- L922 _public function_ `int32 GetDataIndex() const`
- L927 _public function_ `int32 GetIndex() const`
- L934 _protected member_ `static constexpr uint16 InvalidIndex = MAX_uint16;`
- L935 _protected member_ `static constexpr uint16 RootIndex = MAX_uint16 - 1;`
- L936 _protected member_ `static constexpr uint16 ParametersIndex = MAX_uint16 - 2;`
- L939 _protected member_ `uint16 SlotIndex = InvalidIndex;` — `UPROPERTY(VisibleAnywhere, Category = "SmartObject")`
- L942 _protected member_ `uint16 DataIndex = InvalidIndex;` — `UPROPERTY(VisibleAnywhere, Category = "SmartObject")`

#### Free symbols / members of external scopes

- L22 _macro_ `#define WITH_SMARTOBJECT_DEBUG (!(UE_BUILD_SHIPPING || UE_BUILD_SHIPPING_WITH_EDITOR) && 1)`
- L24 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSmartObject, Warning, All);`
- L27 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSmartObjectEvent, const FSmartObjectEventData& );` — Delegate called when Smart Object or Slot is changed.
- L27 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSmartObjectEvent, const FSmartObjectEventData& );` — Delegate called when Smart Object or Slot is changed.
- L30 _namespace_ `namespace UE`
- L30 _namespace_ `namespace SmartObject` (scope `UE`)
- L33 _variable_ `inline const FName WithSmartObjectTag = FName("Wit` (scope `UE::SmartObject`)
- L37 _namespace_ `namespace UE`
- L37 _namespace_ `namespace SmartObject` (scope `UE`)
- L37 _namespace_ `namespace EnabledReason` (scope `UE::SmartObject`)
- L39 _externvar_ `extern FGameplayTag Gameplay;` (scope `UE::SmartObject::EnabledReason`)
- L125 _function_ `friend FString LexToString(const FSmartObjectUserHandle& UserHandle)`
- L171 _function_ `friend FString LexToString(const FSmartObjectHandle Handle)`
- L185 _function_ `friend uint32 GetTypeHash(const FSmartObjectHandle Handle)`
- L254 _function_ `friend uint32 GetTypeHash(const FSmartObjectSlotHandle SlotHandle)`
- L259 _function_ `friend FString LexToString(const FSmartObjectSlotHandle SlotHandle)`
- L386 _function_ `friend FString LexToString(const FSmartObjectSlotIndex& SlotIndex)`

### `Plugins/Runtime/SmartObjects/Source/SmartObjectsModule/Public/SmartObjectUserComponent.h` (Public)


#### class `USmartObjectUserComponent`  
`class USmartObjectUserComponent : public UActorComponent`  
_L18-36_
- reflection: `UCLASS(MinimalAPI, Blueprintable, ClassGroup = Gameplay, meta = (BlueprintSpawnableComponent), config = Game, HideCategories = (Activation, AssetUserData, Collision, Cooking, HLOD, Lighting, LOD, Mobile, Mobility, Navigation, Physics, RayTracing, Rendering, Tags, TextureStreaming))`
- inherits: `UActorComponent`
- desc: Smart Object User Component defines common settings for a Smart Object user. The validation settings for entries and exits are separate to allow to have more lax exit settings. For example the entry settings might prevent to use Smart Object slots which are on water, but we could allow to exit in water.
- L23 _public prototype_ `explicit USmartObjectUserComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L26 _public function_ `TSubclassOf<USmartObjectSlotValidationFilter> GetValidationFilter() const` — @return validation filter to be used for entries.
- L35 _protected member_ `TSubclassOf<USmartObjectSlotValidationFilter> ValidationFilter;` — `UPROPERTY(EditAnywhere, Category = "SmartObject", BlueprintReadWrite)` — Validation filter used for entering testing entries for a Smart Object slot.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SMARTOBJECTSMODULE_API`

### `Plugins/Runtime/SmartObjects/Source/SmartObjectsModule/Public/SmartObjectVisualizationContext.h` (Public)


#### struct `FSmartObjectVisualizationContext`  
`struct FSmartObjectVisualizationContext`  
_L25-101_
- desc: Helper class used for Smart Object Annotation rendering.
- L27 _public prototype_ `explicit FSmartObjectVisualizationContext(const USmartObjectDefinition& InDefinition, const UWorld& InWorld);`
- L30 _public prototype_ `bool IsValidForDraw() const;` — @return true of the context is property set up for 2D drawing.
- L33 _public prototype_ `bool IsValidForDrawHUD() const;` — @return true of the context is property set up for HUD (2D) drawing.
- L36 _public prototype_ `void DrawString(const float StartX, const float StartY, const TCHAR* Text, const FLinearColor& Color, const FLinearColor& ShadowColor = FLinearColor::Black) const;` — Draws string on canvas at specified canvas location.
- L39 _public prototype_ `void DrawString(const FVector& Location, const TCHAR* Text, const FLinearColor& Color, const FLinearColor& ShadowColor = FLinearColor::Black) const;` — Draws string on canvas centered at specified world location.
- L49 _public prototype_ `void DrawArrow(const FVector& Start, const FVector& End, const FLinearColor& Color, const float ArrowHeadLength = 15.0f, const float EndLocationInset = 0.0f, const uint8 DepthPriorityGroup = 0, const float Thickness = 1.0f, const float DepthBias = 0.0f, bool bScreenSpace = false) const;` — Draws arrow from Start to End. @param Start arrow start location @param End arrow end location @param Color color of the arrow @param ArrowHeadLength length of the arrow head @param EndLocationInset how much the ends of the line are inset
- L52 _public prototype_ `FVector2D Project(const FVector& Location) const;` — Projects world location into canvas screen space.
- L55 _public prototype_ `bool IsLocationVisible(const FVector& Location) const;` — @return true of the location is in view frustum.
- L58 _public prototype_ `FVector::FReal GetDistanceToCamera(const FVector& Location) const;` — @return distance from location in world space, to the camera.
- L61 _public member_ `const USmartObjectDefinition& Definition;` — Pointer to the visualized Smart Object definition.
- L64 _public member_ `const UWorld& World;` — World associated with the drawing.
- L67 _public member_ `const AActor* PreviewActor = nullptr;` — Actor used for previewing the Smart Object.
- L70 _public member_ `TSubclassOf<USmartObjectSlotValidationFilter> PreviewValidationFilterClass;` — Validation filter class used for previewing.
- L73 _public member_ `int32 SlotIndex = INDEX_NONE;` — Index of the visualized slot, or invalid of the annotation is on the object.
- L76 _public member_ `int32 AnnotationIndex = INDEX_NONE;` — Index of the visualized annotation.
- L79 _public member_ `FTransform OwnerLocalToWorld;` — Transform of the owner object.
- L82 _public member_ `bool bIsSlotSelected = false;` — True, if the slot is currently selected
- L85 _public member_ `bool bIsAnnotationSelected = false;` — True, if the annotation is currently selected
- L88 _public member_ `const FSceneView* View = nullptr;` — Current view to draw to.
- L91 _public member_ `FPrimitiveDrawInterface* PDI = nullptr;` — Primitive draw interface to draw with during DrawVisualization().
- L94 _public member_ `FCanvas* Canvas = nullptr;` — Canvas to render to during DrawVisualizationHUD().
- L97 _public member_ `const UFont* Font = nullptr;` — Pointer to valid engine small font.
- L100 _public member_ `FLinearColor SelectedColor = FLinearColor::White;` — Color for a selection, cached from UEditorStyleSettings.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SMARTOBJECTSMODULE_API`

### `Plugins/Runtime/SmartObjects/Source/SmartObjectsModule/Public/SmartObjectsModule.h` (Public)


#### class `ISmartObjectsModule`  
`class ISmartObjectsModule : public IModuleInterface`  
_L10-35_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L21 _public function_ `static inline ISmartObjectsModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L31 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Plugins/Runtime/SmartObjects/Source/SmartObjectsModule/Public/WorldConditions/SmartObjectWorldConditionBase.h` (Public)


#### struct `FSmartObjectWorldConditionBase`  
`struct FSmartObjectWorldConditionBase : public FWorldConditionBase`  
_L12-15_
- reflection: `USTRUCT(meta=(Hidden))`
- inherits: `FWorldConditionBase`
- desc: Base struct for all conditions accepted by Smart Objects.

### `Plugins/Runtime/SmartObjects/Source/SmartObjectsModule/Public/WorldConditions/SmartObjectWorldConditionObjectTagQuery.h` (Public)


#### struct `FSmartObjectWorldConditionObjectTagQueryState`  
`struct FSmartObjectWorldConditionObjectTagQueryState`  
_L16-21_
- reflection: `USTRUCT()`
- L20 _public member_ `FDelegateHandle DelegateHandle;`

#### struct `FSmartObjectWorldConditionObjectTagQuery`  
`struct FSmartObjectWorldConditionObjectTagQuery : public FSmartObjectWorldConditionBase`  
_L24-49_
- reflection: `USTRUCT(meta=(DisplayName="Match Runtime Object Tags"))`
- inherits: `FSmartObjectWorldConditionBase`
- L28 _public typedef_ `using FStateType = FSmartObjectWorldConditionObjectTagQueryState;`
- L31 _protected prototype_ `virtual FText GetDescription() const override;`
- L32 _protected function_ `virtual TObjectPtr<const UStruct>* GetRuntimeStateType() const override`
- L37 _protected prototype_ `virtual bool Initialize(const UWorldConditionSchema& Schema) override;`
- L38 _protected prototype_ `virtual bool Activate(const FWorldConditionContext& Context) const override;`
- L39 _protected prototype_ `virtual FWorldConditionResult IsTrue(const FWorldConditionContext& Context) const override;`
- L40 _protected prototype_ `virtual void Deactivate(const FWorldConditionContext& Context) const override;`
- L42 _protected member_ `FWorldConditionContextDataRef SubsystemRef;`
- L43 _protected member_ `FWorldConditionContextDataRef ObjectHandleRef;`
- L48 _public member_ `FGameplayTagQuery TagQuery;` — `UPROPERTY(EditAnywhere, Category="Default")` — Smart Object's runtime tags needs to match this query for the condition to evaluate true.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SMARTOBJECTSMODULE_API`

### `Plugins/Runtime/SmartObjects/Source/SmartObjectsModule/Public/WorldConditions/SmartObjectWorldConditionSchema.h` (Public)


#### class `USmartObjectWorldConditionSchema`  
`class USmartObjectWorldConditionSchema : public UWorldConditionSchema`  
_L14-46_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWorldConditionSchema`
- desc: World Condition schema describing the data conditions and context data available for Smart Object conditions.
- L18 _public prototype_ `explicit USmartObjectWorldConditionSchema(const FObjectInitializer& ObjectInitializer);`
- L21 _public function_ `FWorldConditionContextDataRef GetUserActorRef() const` — Context data reference for accessing SmartObject request's UserActor.
- L24 _public function_ `FWorldConditionContextDataRef GetSmartObjectActorRef() const` — Context data reference for accessing SmartObject owner Actor.
- L27 _public function_ `FWorldConditionContextDataRef GetSmartObjectHandleRef() const` — Context data reference for accessing SmartObject handle.
- L30 _public function_ `FWorldConditionContextDataRef GetSlotHandleRef() const` — Context data reference for accessing SmartObject Slot handle.
- L33 _public function_ `FWorldConditionContextDataRef GetSubsystemRef() const` — Context data reference for accessing SmartObject subsystem.
- L37 _protected prototype_ `virtual bool IsStructAllowed(const UScriptStruct* InScriptStruct) const override;`
- L41 _private member_ `FWorldConditionContextDataRef UserActorRef;`
- L42 _private member_ `FWorldConditionContextDataRef SmartObjectActorRef;`
- L43 _private member_ `FWorldConditionContextDataRef SmartObjectHandleRef;`
- L44 _private member_ `FWorldConditionContextDataRef SlotHandleRef;`
- L45 _private member_ `FWorldConditionContextDataRef SubsystemRef;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SMARTOBJECTSMODULE_API`

### `Plugins/Runtime/SmartObjects/Source/SmartObjectsModule/Public/WorldConditions/SmartObjectWorldConditionSlotTagQuery.h` (Public)


#### struct `FSmartObjectWorldConditionSlotTagQueryState`  
`struct FSmartObjectWorldConditionSlotTagQueryState`  
_L16-23_
- reflection: `USTRUCT()`
- L20 _public member_ `FSmartObjectSlotHandle SlotHandle;`
- L22 _public member_ `FDelegateHandle DelegateHandle;`

#### struct `FSmartObjectWorldConditionSlotTagQuery`  
`struct FSmartObjectWorldConditionSlotTagQuery : public FSmartObjectWorldConditionBase`  
_L26-50_
- reflection: `USTRUCT(meta=(DisplayName="Match Runtime Slot Tags"))`
- inherits: `FSmartObjectWorldConditionBase`
- L30 _public typedef_ `using FStateType = FSmartObjectWorldConditionSlotTagQueryState;`
- L33 _protected prototype_ `virtual FText GetDescription() const override;`
- L34 _protected function_ `virtual TObjectPtr<const UStruct>* GetRuntimeStateType() const override`
- L39 _protected prototype_ `virtual bool Initialize(const UWorldConditionSchema& Schema) override;`
- L40 _protected prototype_ `virtual bool Activate(const FWorldConditionContext& Context) const override;`
- L41 _protected prototype_ `virtual FWorldConditionResult IsTrue(const FWorldConditionContext& Context) const override;`
- L42 _protected prototype_ `virtual void Deactivate(const FWorldConditionContext& Context) const override;`
- L44 _protected member_ `FWorldConditionContextDataRef SubsystemRef;`
- L45 _protected member_ `FWorldConditionContextDataRef SlotHandleRef;`
- L49 _protected member_ `FGameplayTagQuery TagQuery;` — `UPROPERTY(EditAnywhere, Category="Default")` — Smart Object Slot's runtime tags needs to match this query for the condition to evaluate true.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SMARTOBJECTSMODULE_API`

### `Plugins/Runtime/SmartObjects/Source/SmartObjectsModule/Public/WorldConditions/WorldCondition_SmartObjectActorTagQuery.h` (Public)


#### struct `FWorldCondition_SmartObjectActorTagQueryState`  
`struct FWorldCondition_SmartObjectActorTagQueryState`  
_L12-17_
- reflection: `USTRUCT()`
- L16 _public member_ `FDelegateHandle DelegateHandle;`

#### struct `FWorldCondition_SmartObjectActorTagQuery`  
`struct FWorldCondition_SmartObjectActorTagQuery : public FSmartObjectWorldConditionBase`  
_L23-49_
- reflection: `USTRUCT(meta=(DisplayName="Match Gameplay tags on SmartObject actor"))`
- inherits: `FSmartObjectWorldConditionBase`
- desc: World condition to match tags of the Smart Object's owning Actor (which must implement IGameplayTagAssetInterface or have an AbilitySystemComponent).
- L27 _public typedef_ `using FStateType = FWorldCondition_SmartObjectActorTagQueryState;`
- L30 _protected prototype_ `virtual FText GetDescription() const override;`
- L32 _protected function_ `virtual TObjectPtr<const UStruct>* GetRuntimeStateType() const override`
- L37 _protected prototype_ `virtual bool Initialize(const UWorldConditionSchema& Schema) override;`
- L38 _protected prototype_ `virtual bool Activate(const FWorldConditionContext& Context) const override;`
- L39 _protected prototype_ `virtual FWorldConditionResult IsTrue(const FWorldConditionContext& Context) const override;`
- L40 _protected prototype_ `virtual void Deactivate(const FWorldConditionContext& Context) const override;`
- L43 _protected member_ `FWorldConditionContextDataRef SmartObjectActorRef;` — Smart Object's owning actor for which the tags must match the query. The Actor must implement IGameplayTagAssetInterface or have an AbilitySystemComponent.
- L48 _public member_ `FGameplayTagQuery TagQuery;` — `UPROPERTY(EditAnywhere, Category="Default")` — Tags on the Smart Object's owning actor that need to match this query for the condition to evaluate true.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SMARTOBJECTSMODULE_API`
