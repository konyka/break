# Plugins / MoverMassIntegration

- module root: `Plugins/Experimental/MoverIntegrations/Source/MoverMassIntegration`
- headers: 6; symbols: 64
- symbol kinds: class=11, function=4, macro=5, member=12, prototype=25, struct=7
- PrivateDependencyModuleNames: CoreUObject, Engine, MassActors, MassCommon, MassCore, MassEntity, MassMovement, MassSpawner, Mover
- PublicDependencyModuleNames: Core

### `Plugins/Experimental/MoverIntegrations/Source/MoverMassIntegration/Public/MassMoverInputComponent.h` (Public)


#### class `UMassMoverInputComponent`  
`class UMassMoverInputComponent : public UActorComponent, public IMoverInputProducerInterface`  
_L14-33_
- reflection: `UCLASS(MinimalAPI, BlueprintType, meta = (BlueprintSpawnableComponent))`
- inherits: `UActorComponent,IMoverInputProducerInterface`
- desc: Bridges a Mass entity to a Mover-based character actor. Each tick it produces an FCharacterDefaultInputs frame (velocity + orientation intent), so this only works with Mover modes that consume FCharacterDefaultInputs (UCharacterMoverComponent and similar).
- L20 _public prototype_ `virtual void BeginPlay() override;`
- L22 _public function_ `const FVector& GetDesiredVelocity() const`
- L23 _public function_ `void SetDesiredVelocity(const FVector& NewDesiredVelocity)`
- L25 _public function_ `const FQuat& GetDesiredRotation() const`
- L26 _public function_ `void SetDesiredRotation(const FQuat& NewDesiredRotation)`
- L28 _public prototype_ `virtual void ProduceInput_Implementation(int32 SimTimeMs, FMoverInputCmdContext& InputCmdResult) override;`
- L31 _protected member_ `FVector DesiredVelocity = FVector::ZeroVector;`
- L32 _protected member_ `FQuat DesiredRotation = FQuat::Identity;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MOVERMASSINTEGRATION_API`

### `Plugins/Experimental/MoverIntegrations/Source/MoverMassIntegration/Public/MassMoverInputTranslator.h` (Public)


#### struct `FLightweightMoverInputWrapperFragment`  
`struct FLightweightMoverInputWrapperFragment : public FObjectWrapperFragment`  
_L17-22_
- reflection: `USTRUCT()`
- inherits: `FObjectWrapperFragment`
- L21 _public member_ `TWeakObjectPtr<UMassMoverInputComponent> MoverInputComponent;`

#### struct `FMoverWrapperFragment`  
`struct FMoverWrapperFragment : public FObjectWrapperFragment`  
_L25-30_
- reflection: `USTRUCT()`
- inherits: `FObjectWrapperFragment`
- L29 _public member_ `TWeakObjectPtr<UMoverComponent> MoverComponent;`

#### class `UMassToMoverInputTranslator`  
`class UMassToMoverInputTranslator : public UMassTranslator`  
_L35-47_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassTranslator`
- desc: Mass -> Mover translator. Reads the entity's velocity and transform fragments and pushes the values into the wrapped UMassMoverInputComponent so the Mover simulation produces the requested motion.
- L40 _public prototype_ `UMassToMoverInputTranslator();`
- L43 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L44 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L46 _protected member_ `FMassEntityQuery EntityQuery;`

#### class `UMoverInputToMassTranslator`  
`class UMoverInputToMassTranslator : public UMassTranslator`  
_L52-64_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassTranslator`
- desc: Mover -> Mass translator. Reads the wrapped UMoverComponent's velocity and updated transform back into the entity's velocity and transform fragments so downstream Mass processors see the simulation output.
- L57 _public prototype_ `UMoverInputToMassTranslator();`
- L60 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L61 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L63 _protected member_ `FMassEntityQuery EntityQuery;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MOVERMASSINTEGRATION_API`

### `Plugins/Experimental/MoverIntegrations/Source/MoverMassIntegration/Public/MoverInputTrait.h` (Public)


#### class `UMoverInputTrait`  
`class UMoverInputTrait : public UMassEntityTraitBase`  
_L14-20_
- reflection: `UCLASS(MinimalAPI, BlueprintType, EditInlineNew, CollapseCategories, meta = (DisplayName = "Mover Input Trait"))`
- inherits: `UMassEntityTraitBase`
- desc: Mass entity trait that wires a Mover-driven actor's input bridge into the entity. The trait adds the fragments needed to read/write the desired velocity and transform, and depending on the sync direction either captures the actor's current Mover transform or leaves the entity as the authority for movement.
- L19 _protected prototype_ `virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MOVERMASSINTEGRATION_API`

### `Plugins/Experimental/MoverIntegrations/Source/MoverMassIntegration/Public/MoverMassAgentTraits.h` (Public)


#### class `UMoverMassAgentTrait`  
`class UMoverMassAgentTrait : public UMassAgentSyncTrait`  
_L18-31_
- reflection: `UCLASS(MinimalAPI, BlueprintType, EditInlineNew, CollapseCategories, meta = (DisplayName = "Agent Mover Sync"))`
- inherits: `UMassAgentSyncTrait`
- desc: The trait initializes the entity with a NavMoverComponent so Mover and Mass can communicate movement intent and velocity. This trait also sets up necessary translators for these systems based off of Mass sync direction. Note: This trait requires a NavMoverComponent and a MoverComponent to work properly
- L23 _protected prototype_ `virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;`
- L30 _protected member_ `bool bSyncTransform = false;` — `UPROPERTY(EditAnywhere, Category = Mass)` — Whether this trait should sync the transform of actor<->entity (based on translation direction) TODO: Currently Mover doesn't like outside modification of rotation and may throw a warning if Mover's transform gets set from the entity. It may also cause a rollback.

#### class `UMoverMassAgentOrientationSyncTrait`  
`class UMoverMassAgentOrientationSyncTrait : public UMassAgentSyncTrait`  
_L37-43_
- reflection: `UCLASS(MinimalAPI, BlueprintType, EditInlineNew, CollapseCategories, meta = (DisplayName = "Agent Mover Orientation Sync"))`
- inherits: `UMassAgentSyncTrait`
- desc: This trait sets up required translators for orientation syncing between Mover and Mass based off of Mass sync direction
- L42 _protected prototype_ `virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MOVERMASSINTEGRATION_API`

### `Plugins/Experimental/MoverIntegrations/Source/MoverMassIntegration/Public/MoverMassIntegration.h` (Public)


#### class `FMoverMassIntegrationModule`  
`class FMoverMassIntegrationModule : public IModuleInterface`  
_L10-15_
- inherits: `IModuleInterface`
- desc: Module for Mover-Mass integrations such as Mover specific Mass translators and Mass traits
- L13 _public prototype_ `virtual void StartupModule() override;`
- L14 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Experimental/MoverIntegrations/Source/MoverMassIntegration/Public/MoverMassTranslators.h` (Public)


#### struct `FNavMoverComponentWrapperFragment`  
`struct FNavMoverComponentWrapperFragment : public FObjectWrapperFragment`  
_L16-20_
- reflection: `USTRUCT()`
- inherits: `FObjectWrapperFragment`
- L19 _public member_ `TWeakObjectPtr<UNavMoverComponent> Component;`

#### struct `FMassNavMoverCopyToMassTag`  
`struct FMassNavMoverCopyToMassTag : public FMassTag`  
_L23-26_
- reflection: `USTRUCT()`
- inherits: `FMassTag`

#### class `UMassNavMoverToMassTranslator`  
`class UMassNavMoverToMassTranslator : public UMassTranslator`  
_L33-45_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassTranslator`
- desc: Translator in charge of going from Mover->Mass Sets Mass fragments for keeping track of Location (feet location), Velocity and MaxSpeed
- L38 _public prototype_ `UMassNavMoverToMassTranslator();`
- L41 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L42 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L44 _protected member_ `FMassEntityQuery EntityQuery;`

#### struct `FMassCopyToNavMoverTag`  
`struct FMassCopyToNavMoverTag : public FMassTag`  
_L48-51_
- reflection: `USTRUCT()`
- inherits: `FMassTag`

#### class `UMassToNavMoverTranslator`  
`class UMassToNavMoverTranslator : public UMassTranslator`  
_L59-71_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassTranslator`
- desc: Translator in charge of going from Mass->Mover Uses the NavMoverWrapperFragment to get a NavMoverComponent and request movement similarly to the PathFollowingComponent See @UNavMoverComponent for details of how Mover consumes the move intent
- L64 _public prototype_ `UMassToNavMoverTranslator();`
- L67 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L68 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L70 _protected member_ `FMassEntityQuery EntityQuery;`

#### struct `FMassNavMoverActorOrientationCopyToMassTag`  
`struct FMassNavMoverActorOrientationCopyToMassTag : public FMassTag`  
_L74-77_
- reflection: `USTRUCT()`
- inherits: `FMassTag`

#### class `UMassNavMoverActorOrientationToMassTranslator`  
`class UMassNavMoverActorOrientationToMassTranslator : public UMassTranslator`  
_L84-96_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassTranslator`
- desc: Translator in charge of going from Mover->Mass for orientation Modifies the transform fragment based off of Mover's rotation
- L89 _public prototype_ `UMassNavMoverActorOrientationToMassTranslator();`
- L92 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L93 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L95 _protected member_ `FMassEntityQuery EntityQuery;`

#### struct `FMassOrientationCopyToNavMoverActorOrientationTag`  
`struct FMassOrientationCopyToNavMoverActorOrientationTag : public FMassTag`  
_L99-102_
- reflection: `USTRUCT()`
- inherits: `FMassTag`

#### class `UMassOrientationToNavMoverActorOrientationTranslator`  
`class UMassOrientationToNavMoverActorOrientationTranslator : public UMassTranslator`  
_L110-122_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassTranslator`
- desc: Translator in charge of going from Mass->Mover for orientation Modifies the UpdatedComponent of the NavMoverComponent based off of the entities transform fragment rotation TODO: Currently Mover doesn't like outside modification of rotation and may throw a warning. It may also cause a rollback.
- L115 _public prototype_ `UMassOrientationToNavMoverActorOrientationTranslator();`
- L118 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L119 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L121 _protected member_ `FMassEntityQuery EntityQuery;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MOVERMASSINTEGRATION_API`
