# Plugins / MassMovement

- module root: `Plugins/Runtime/MassGameplay/Source/MassMovement`
- headers: 12; symbols: 129
- symbol kinds: class=13, delegate=1, externvar=3, function=7, macro=4, member=49, namespace=8, prototype=31, struct=13
- PrivateDependencyModuleNames: EditorFramework, UnrealEd
- PublicDependencyModuleNames: AIModule, Core, CoreUObject, Engine, MassCommon, MassCore, MassEntity, MassLOD, MassSignals, MassSpawner, NavigationSystem, ZoneGraph, ZoneGraphAnnotations

### `Plugins/Runtime/MassGameplay/Source/MassMovement/Public/Example/MassSimpleMovementTrait.h` (Public)


#### struct `FMassSimpleMovementTag`  
`struct FMassSimpleMovementTag : public FMassTag`  
_L15-18_
- reflection: `USTRUCT()`
- inherits: `FMassTag`

#### class `UMassSimpleMovementTrait`  
`class UMassSimpleMovementTrait : public UMassEntityTraitBase`  
_L22-28_
- reflection: `UCLASS(MinimalAPI, meta = (DisplayName = "Simple Movement"))`
- inherits: `UMassEntityTraitBase`
- L27 _protected prototype_ `virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;`

#### class `UMassSimpleMovementProcessor`  
`class UMassSimpleMovementProcessor : public UMassProcessor`  
_L32-43_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassProcessor`
- L36 _public prototype_ `UMassSimpleMovementProcessor();`
- L39 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L40 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L42 _protected member_ `FMassEntityQuery EntityQuery;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MASSMOVEMENT_API`

### `Plugins/Runtime/MassGameplay/Source/MassMovement/Public/Example/MassVelocityRandomizerTrait.h` (Public)


#### class `UMassVelocityRandomizerTrait`  
`class UMassVelocityRandomizerTrait : public UMassEntityTraitBase`  
_L16-33_
- reflection: `UCLASS(MinimalAPI, meta = (DisplayName = "Velocity Randomizer"))`
- inherits: `UMassEntityTraitBase`
- L21 _protected prototype_ `virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;`
- L25 _protected member_ `float MinSpeed = 0.f;` — `UPROPERTY(Category = "Velocity", EditAnywhere, meta = (UIMin = 0.0, ClampMin = 0.0))` — The speed is expressed in UnrealUnits per second, which usually translates to 0.01m/s
- L29 _protected member_ `float MaxSpeed = 200.f;` — `UPROPERTY(Category = "Velocity", EditAnywhere, meta = (UIMin = 1.0, ClampMin = 1.0))` — The speed is expressed in UnrealUnits per second, which usually translates to 0.01m/s
- L32 _protected member_ `bool bSetZComponent = false;` — `UPROPERTY(Category = "Velocity", EditAnywhere)`

#### class `UMassRandomVelocityInitializer`  
`class UMassRandomVelocityInitializer : public UMassObserverProcessor`  
_L37-61_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassObserverProcessor`
- L41 _public prototype_ `UMassRandomVelocityInitializer();`
- L43 _public prototype_ `void SetParameters(const float InMinSpeed, const float InMaxSpeed, const bool bInSetZComponent);`
- L46 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L47 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L49 _protected member_ `FMassEntityQuery EntityQuery;`
- L52 _protected member_ `float MinSpeed = 0.f;` — `UPROPERTY()`
- L56 _protected member_ `float MaxSpeed = 0.f;` — `UPROPERTY()` — The default max is set to 0 to enforce explicit configuration via SetParameters call.
- L59 _protected member_ `bool bSetZComponent = false;` — `UPROPERTY()`
- L60 _protected member_ `FRandomStream RandomStream;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MASSMOVEMENT_API`

### `Plugins/Runtime/MassGameplay/Source/MassMovement/Public/IMassMovementModule.h` (Public)


#### class `IMassMovementModule`  
`class IMassMovementModule : public IModuleInterface`  
_L14-39_
- inherits: `IModuleInterface`
- desc: The public interface to this module.  In most cases, this interface is only public to sibling modules within this plugin.
- L25 _public function_ `static inline IMassMovementModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L35 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Plugins/Runtime/MassGameplay/Source/MassMovement/Public/MassMovementDelegates.h` (Public)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MassMovement` (scope `UE`)
- L11 _namespace_ `namespace Delegates` (scope `UE::MassMovement`)
- L15 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnMassMovementNamesChanged);` — Called when movement names have changed (UI update).
- L15 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnMassMovementNamesChanged);` (scope `UE::MassMovement::Delegates`) — Called when movement names have changed (UI update).
- L16 _externvar_ `extern FOnMassMovementNamesChanged OnMassMovementNamesChanged;` (scope `UE::MassMovement::Delegates`)

### `Plugins/Runtime/MassGameplay/Source/MassMovement/Public/MassMovementFragments.h` (Public)


#### struct `FMassVelocityFragment`  
`struct FMassVelocityFragment : public FMassFragment`  
_L19-28_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- desc: This represents the actual physical velocity of the mass entity in the world For agents with an actor representation, this is the velocity of the movement component
- L23 _public member_ `FVector Value = FVector::ZeroVector;`
- L26 _public member_ `FVector DebugPreviousValue = FVector::ZeroVector;`

#### struct `FMassDesiredMovementFragment`  
`struct FMassDesiredMovementFragment : public FMassFragment`  
_L35-43_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- desc: This is the output of all processors that intend to affect movement It is the input to the movement system (e.g. mover, animation etc.)
- L39 _public member_ `FVector DesiredVelocity = FVector::ZeroVector;`
- L40 _public member_ `FQuat DesiredFacing = FQuat::Identity;`
- L42 _public member_ `float DesiredMaxSpeedOverride = FLT_MAX;`

#### struct `FMassForceFragment`  
`struct FMassForceFragment : public FMassFragment`  
_L47-52_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- desc: Accumulator for steering / avoidance forces to apply to the desired velocity
- L51 _public member_ `FVector Value = FVector::ZeroVector;`

#### struct `FMassCodeDrivenMovementTag`  
`struct FMassCodeDrivenMovementTag : public FMassTag`  
_L64-67_
- reflection: `USTRUCT()`
- inherits: `FMassTag`
- desc: The presence of this tag indicates that this mass agent's velocity should be controlled by the FMassDesiredMovementFragment. For code driven displacement, we want the desired velocity to affect the velocity directly, which is then applied to the character mover. For e.g. Root Motion driven displacement, we just need to pipe the DesiredVelocity to the animation system and let it do the test.

#### struct `FMassCustomMovementTag`  
`struct FMassCustomMovementTag : public FMassTag`  
_L75-78_
- reflection: `USTRUCT()`
- inherits: `FMassTag`
- desc: The presence of this tag indicates that a custom movement processor handles this entity's position updates. Default movement processors (UMassApplyMovementProcessor, USpringApplyMovementProcessor) will skip entities with this tag.

#### struct `FMassMovementParameters`  
`struct FMassMovementParameters : public FMassConstSharedFragment`  
_L82-151_
- reflection: `USTRUCT()`
- inherits: `FMassConstSharedFragment`
- desc: Parameters describing how this mass agent should move
- L86 _public function_ `FMassMovementParameters GetValidated() const`
- L94 _public prototype_ `void Update();` — Updates internal values for faster desired speed generation.
- L97 _public function_ `float GenerateDesiredSpeed(const FMassMovementStyleRef& Style, const int32 UniqueId) const` — Generates desired speed based on style and unique id. The id is used deterministically assign a specific speed range.
- L126 _public member_ `float MaxSpeed = 200.f;` — `UPROPERTY(EditAnywhere, Category = "Movement", meta = (ClampMin = "0", ForceUnits="cm/s"))` — Maximum speed (cm/s).
- L130 _public member_ `float MaxAcceleration = 250.f;` — `UPROPERTY(config, EditAnywhere, Category = "Movement", meta = (UIMin = 0.0, ClampMin = 0.0, ForceUnits="cm/s^2"))` — 200..600 Smaller steering maximum acceleration makes the steering more \"calm\" but less opportunistic, may not find solution, or gets stuck.
- L134 _public member_ `float DefaultDesiredSpeed = 140.f;` — `UPROPERTY(EditAnywhere, Category = "Movement", meta = (ClampMin = "0", ForceUnits="cm/s"))` — Default desired speed (cm/s).
- L138 _public member_ `float DefaultDesiredSpeedVariance = 0.1f;` — `UPROPERTY(EditAnywhere, Category = "Movement", meta = (ClampMin = "0", ClampMax = "1"))` — How much default desired speed is varied randomly.
- L142 _public member_ `float HeightSmoothingTime = 0.2f;` — `UPROPERTY(EditAnywhere, Category = "Movement", meta = (ClampMin = "0.0", ForceUnits="s"))` — The time it takes the entity position to catchup to the requested height.
- L146 _public member_ `TArray<FMassMovementStyleParameters> MovementStyles;` — `UPROPERTY(EditAnywhere, Category = "Movement")` — List of supported movement styles for this configuration.
- L150 _public member_ `bool bIsCodeDrivenMovement = true;` — `UPROPERTY(EditAnywhere, Category = "Movement")` — Indicate whether mass AI has direct control over the mass agent's velocity. If true, desired velocity will be written directly to velocity every frame

#### Free symbols / members of external scopes

- L103 _function_ `` (scope `FMassMovementParameters::GenerateDesiredSpeed`)

### `Plugins/Runtime/MassGameplay/Source/MassMovement/Public/MassMovementSettings.h` (Public)


#### class `UMassMovementSettings`  
`class UMassMovementSettings : public UMassModuleSettings`  
_L13-36_
- reflection: `UCLASS(MinimalAPI, config = Mass, defaultconfig, meta = (DisplayName = "Mass Movement"))`
- inherits: `UMassModuleSettings`
- L18 _public prototype_ `UMassMovementSettings(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L20 _public function_ `static const UMassMovementSettings* Get()`
- L25 _public function_ `TConstArrayView<FMassMovementStyle> GetMovementStyles() const`
- L26 _public prototype_ `const FMassMovementStyle* GetMovementStyleByID(const FGuid ID) const;`
- L31 _private prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L35 _private member_ `TArray<FMassMovementStyle> MovementStyles;` — `UPROPERTY(EditAnywhere, config, Category = Movement)`

### `Plugins/Runtime/MassGameplay/Source/MassMovement/Public/MassMovementTypes.h` (Public)


#### struct `FMassMovementStyleRef`  
`struct FMassMovementStyleRef`  
_L21-30_
- reflection: `USTRUCT()`
- desc: Reference to movement style in MassMovementSettings.
- L26 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, Category = "Movement")`
- L29 _public member_ `FGuid ID;` — `UPROPERTY(EditAnywhere, Category = "Movement", meta = (IgnoreForMemberInitializationTest, EditCondition = "false", EditConditionHides))`

#### struct `FMassMovementStyle`  
`struct FMassMovementStyle`  
_L34-43_
- reflection: `USTRUCT()`
- desc: Describes movement style name.
- L39 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, Category = "Movement")`
- L42 _public member_ `FGuid ID;` — `UPROPERTY(EditAnywhere, Category = "Movement", meta = (IgnoreForMemberInitializationTest, EditCondition = "false", EditConditionHides))`

#### struct `FMassMovementStyleSpeedParameters`  
`struct FMassMovementStyleSpeedParameters`  
_L50-68_
- reflection: `USTRUCT()`
- desc: Movement style consists of multiple speeds which are assigned to agents based on agents unique ID. Same speed is assigned consistently for the same ID.
- L56 _public member_ `float Speed = 140.0f;` — `UPROPERTY(EditAnywhere, Category = "Movement Style", meta = (UIMin = 0.0, ClampMin = 0.0, ForceUnits="cm/s"))` — Desired speed
- L60 _public member_ `float Variance = 0.1f;` — `UPROPERTY(EditAnywhere, Category = "Movement Style", meta = (ClampMin = 0.0, ClampMax = 1.0))` — How much default desired speed is varied randomly.
- L64 _public member_ `float Probability = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Movement Style", meta = (UIMin = 1, ClampMin = 1, UIMax = 100, ClampMax = 100))` — Probability to assign this speed.
- L67 _public member_ `float ProbabilityThreshold = 0.0f;` — Probability threshold for this style, used to faster lookup. Update via FMassMovementConfig::Update().

#### struct `FMassMovementStyleParameters`  
`struct FMassMovementStyleParameters`  
_L72-83_
- reflection: `USTRUCT()`
- desc: Movement style parameters. A movement style abstracts movement properties for specific style. Behaviors can refer to specific styles when handling speeds.
- L78 _public member_ `FMassMovementStyleRef Style;` — `UPROPERTY(EditAnywhere, Category = "Movement Style")` — Style of the movement
- L82 _public member_ `TArray<FMassMovementStyleSpeedParameters> DesiredSpeeds;` — `UPROPERTY(EditAnywhere, Category = "Movement Style")` — Array of desired speeds (cm/s) assigned to agents based on probability.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Mass` (scope `UE`)
- L9 _namespace_ `namespace ProcessorGroupNames` (scope `UE::Mass`)
- L11 _externvar_ `extern const FName SpringMovement;` (scope `UE::Mass::ProcessorGroupNames`)
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MassMovement` (scope `UE`)
- L16 _externvar_ `extern int32 bFreezeMovement;` (scope `UE::MassMovement`)

### `Plugins/Runtime/MassGameplay/Source/MassMovement/Public/MassSpringMovementFragments.h` (Public)


#### struct `FSpringMovementSettings`  
`struct FSpringMovementSettings : public FMassConstSharedFragment`  
_L9-24_
- reflection: `USTRUCT()`
- inherits: `FMassConstSharedFragment`
- L15 _public member_ `float VelocitySmoothingTime = 0.1f;` — `UPROPERTY(EditAnywhere, Category=Smoothing)` — How long to smooth to target velocity
- L19 _public member_ `float FacingSmoothingTime = 0.1f;` — `UPROPERTY(EditAnywhere, Category=Smoothing)` — How long to smooth to target facing
- L23 _public member_ `float VelocityDeadzoneThreshold = 0.1f;` — `UPROPERTY(EditAnywhere, Category=Smoothing)` — Below this speed we set velocity to 0

#### struct `FSpringMovementRuntime`  
`struct FSpringMovementRuntime : public FMassFragment`  
_L27-39_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- L34 _public member_ `FVector CurrentPosition = FVector::ZeroVector;` — These are INTERNAL variables used for the spring damper Do not take for granted that next frame Position = Velocity * Dt Since this is used in a exponential damped spring with analytical solution (not Euler integrated)
- L35 _public member_ `FVector CurrentAccel = FVector::ZeroVector;`
- L36 _public member_ `FVector CurrentVelocity = FVector::ZeroVector;`
- L37 _public member_ `FQuat CurrentFacing = FQuat::Identity;`
- L38 _public member_ `FVector CurrentAngularVelocity = FVector::ZeroVector;`

### `Plugins/Runtime/MassGameplay/Source/MassMovement/Public/MassSpringMovementProcessors.h` (Public)


#### class `USpringUpdateProcessor`  
`class USpringUpdateProcessor : public UMassProcessor`  
_L17-30_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassProcessor`
- desc: This processor runs the spring damper to update FSpringMovementRuntime from desired movement input. It does NOT move the character — that is handled by USpringApplyMovementProcessor or a custom movement processor. Note:	applying this spring to the character's desired movement will introduce some latency between desired input and the resulting movement that can degrade the accuracy of the navigation systems
- L22 _public prototype_ `USpringUpdateProcessor();`
- L25 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L26 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L29 _private member_ `FMassEntityQuery EntityQuery;`

#### class `USpringApplyMovementProcessor`  
`class USpringApplyMovementProcessor : public UMassProcessor`  
_L35-48_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassProcessor`
- desc: This processor applies the spring runtime state (position, facing, velocity) to the entity transform. Skipped when FMassCustomMovementTag is present (a custom movement processor handles movement instead).
- L40 _public prototype_ `USpringApplyMovementProcessor();`
- L43 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L44 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L47 _private member_ `FMassEntityQuery EntityQuery;`

#### class `USpringMovementLODResyncObserver`  
`class USpringMovementLODResyncObserver : public UMassObserverProcessor`  
_L54-67_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassObserverProcessor`
- desc: Observes removal of FMassOffLODTag and resyncs spring internal state to the entity's current transform/velocity, preventing visual pops when entities transition back on-LOD.
- L59 _public prototype_ `USpringMovementLODResyncObserver();`
- L62 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L63 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L66 _private member_ `FMassEntityQuery EntityQuery;`

### `Plugins/Runtime/MassGameplay/Source/MassMovement/Public/MassSpringMovementTrait.h` (Public)


#### class `USpringMovementTrait`  
`class USpringMovementTrait : public UMassEntityTraitBase`  
_L33-42_
- reflection: `UCLASS(MinimalAPI, EditInlineNew, CollapseCategories, meta = (DisplayName = "Spring Movement"))`
- inherits: `UMassEntityTraitBase`
- desc: Adds spring-damped movement to this entity. The spring smoothly interpolates position and facing toward the desired movement input using a critically damped spring. Note: applying this spring to the character's desired movement will introduce some latency between desired input and the resulting movement that can degrade the accuracy of the navigation systems. Use care when tweaking the spring settings to ensure that avoidance and navigation perform as expected. Processor execution is split into two steps: - USpringUpdateProcessor: runs the spring damper to update FSpringMovementRuntime (runs for ALL spring entities regardless of other traits). - USpringApplyMovementProcessor: writes the spring state to the entity transform and velocity. Skipped when FMassCustomMovementTag is present (e.g. when UCharacterTrajectoryMovementTrait is active, trajectory movement takes over instead). Can be combined with: - UCharacterTrajectoryTrait: spring state is used to generate a smoothed trajectory for animation. - UCharacterTrajectoryTrait + UCharacterTrajectoryMovementTrait: spring update runs, trajectory is generated from spring state, and trajectory movement drives the entity (spring apply is skipped). The smoothing parameters (VelocitySmoothingTime, FacingSmoothingTime) are also used by USpringMovementToCharacterTrajectoryProcessor for trajectory prediction.
- L38 _protected prototype_ `virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;`
- L41 _protected member_ `FSpringMovementSettings SpringSettings;` — `UPROPERTY(Category = "Steering", EditAnywhere, meta = (EditInline))`

### `Plugins/Runtime/MassGameplay/Source/MassMovement/Public/Movement/MassMovementProcessors.h` (Public)


#### class `UMassApplyForceProcessor`  
`class UMassApplyForceProcessor : public UMassProcessor`  
_L16-29_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassProcessor`
- desc: Calculate desired movement based on input forces
- L21 _public prototype_ `UMassApplyForceProcessor();`
- L24 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L25 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L28 _private member_ `FMassEntityQuery EntityQuery;`

#### class `UMassApplyMovementProcessor`  
`class UMassApplyMovementProcessor : public UMassProcessor`  
_L38-55_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassProcessor`
- desc: Updates entities position based on desired velocity. Only required for agents that have code driven displacement Not applied on Off-LOD entities.
- L43 _public prototype_ `UMassApplyMovementProcessor();`
- L46 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L47 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L50 _private member_ `FMassEntityQuery EntityQuery;`
- L53 _private member_ `FMassEntityQuery DebugEntityQuery;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MASSMOVEMENT_API`

### `Plugins/Runtime/MassGameplay/Source/MassMovement/Public/Movement/MassMovementTrait.h` (Public)


#### class `UMassMovementTrait`  
`class UMassMovementTrait : public UMassEntityTraitBase`  
_L12-21_
- reflection: `UCLASS(MinimalAPI, meta = (DisplayName = "Movement"))`
- inherits: `UMassEntityTraitBase`
- L17 _protected prototype_ `virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;`
- L20 _protected member_ `FMassMovementParameters Movement;` — `UPROPERTY(Category="Movement", EditAnywhere)`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MASSMOVEMENT_API`
