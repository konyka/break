# Plugins / MotionTrajectory

- module root: `Plugins/Experimental/Animation/MotionTrajectory/Source/MotionTrajectory`
- headers: 3; symbols: 59
- symbol kinds: class=2, delegate=1, macro=2, member=35, prototype=15, struct=4
- PublicDependencyModuleNames: AnimGraphRuntime, Core, CoreUObject, Engine, PoseSearch

### `Plugins/Experimental/Animation/MotionTrajectory/Source/MotionTrajectory/Public/CharacterTrajectoryComponent.h` (Public)


#### class `UCharacterTrajectoryComponent`  
`class UCharacterTrajectoryComponent : public UActorComponent`  
_L16-47_
- reflection: `UCLASS(MinimalAPI, Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent), Experimental)`
- inherits: `UActorComponent`
- desc: Component for generating trajectories usable by Motion Matching. This component generates trajectories from ACharacter. This is intended to provide an example and starting point for using Motion Matching with a common setup using the default UCharacterMovementComponent. It is expected work flow to extend or replace this component for projects that use a custom movement component or custom movement modes.
- L22 _public prototype_ `UCharacterTrajectoryComponent(const FObjectInitializer& ObjectInitializer);`
- L25 _public prototype_ `virtual void InitializeComponent() override;`
- L26 _public prototype_ `virtual void UninitializeComponent() override;`
- L27 _public prototype_ `virtual void BeginPlay() override;`
- L32 _protected prototype_ `void OnMovementUpdated(float DeltaSeconds, FVector OldLocation, FVector OldVelocity);` — `UFUNCTION()`
- L36 _protected member_ `FTransformTrajectory Trajectory;` — `UPROPERTY(Transient, BlueprintReadOnly, Category = "Trajectory")` — Trajectory stored in world space so it can be directly passed to Motion Matching.
- L39 _protected member_ `FTrajectorySamplingData SamplingData;` — `UPROPERTY(Transient, BlueprintReadOnly, Category = "Trajectory Settings")`
- L42 _protected member_ `FCharacterTrajectoryData CharacterTrajectoryData;` — `UPROPERTY(Transient, BlueprintReadOnly, Category = "Trajectory Settings")`
- L44 _protected member_ `TArray<FVector> TranslationHistory;`
- L46 _protected member_ `uint32 LastUpdateFrameNumber = 0;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MOTIONTRAJECTORY_API`

### `Plugins/Experimental/Animation/MotionTrajectory/Source/MotionTrajectory/Public/MotionTrajectory.h` (Public)


#### class `FMotionTrajectoryModule`  
`class FMotionTrajectoryModule : public IModuleInterface`  
_L15-21_
- inherits: `IModuleInterface`
- L19 _public prototype_ `virtual void StartupModule() override;`
- L20 _public prototype_ `virtual void ShutdownModule() override;`

#### struct `FMotionTrajectorySettings`  
`struct FMotionTrajectorySettings`  
_L25-32_
- reflection: `USTRUCT(BlueprintType, Category="Motion Trajectory")`
- desc: Specifies the chosen domain parameters for trajectory sample retention and creation
- L31 _public member_ `float Seconds = 2.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings", meta=(ClampMin="0.0"))` — Sample time horizon

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMotionTrajectory, Log, All);`
- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMotionTrajectory, Log, All);`

### `Plugins/Experimental/Animation/MotionTrajectory/Source/MotionTrajectory/Public/MotionTrajectoryLibrary.h` (Public)


#### struct `FTrajectorySamplingData`  
`struct FTrajectorySamplingData`  
_L15-44_
- reflection: `USTRUCT(BlueprintType)`
- L19 _public prototype_ `void Init();`
- L24 _public member_ `float HistoryLengthSeconds = 1.5f;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Trajectory Settings")` — This should generally match the longest history required by a Motion Matching Database in the project. Motion Matching will use extrapolation to generate samples if the history doesn't contain enough samples.
- L28 _public member_ `int32 HistorySamplesPerSecond = 5;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Trajectory Settings", meta = (ClampMin = "1", ClampMax = "120"))` — Higher values will cost more storage and processing time, but give higher accuracy.
- L33 _public member_ `float PredictionLengthSeconds = 1.5f;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Trajectory Settings")` — This should match the longest trajectory prediction required by a Motion Matching Database in the project. Motion Matching will use extrapolation to generate samples if the prediction doesn't contain enough samples.
- L37 _public member_ `int32 PredictionSamplesPerSecond = 5;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Trajectory Settings", meta = (ClampMin = "1", ClampMax = "120"))` — Higher values will cost more storage and processing time, but give higher accuracy.
- L39 _public member_ `int32 NumHistorySamples = 0;`
- L40 _public member_ `float SecondsPerHistorySample = 0.f;`
- L42 _public member_ `int32 NumPredictionSamples = 0;`
- L43 _public member_ `float SecondsPerPredictionSample = 0.f;`

#### struct `FCharacterTrajectoryData`  
`struct FCharacterTrajectoryData`  
_L47-105_
- reflection: `USTRUCT(BlueprintType)`
- L52 _public prototype_ `void UpdateDataFromCharacter(float DeltaSeconds, const ACharacter* Character);`
- L54 _public prototype_ `FVector StepCharacterMovementGroundPrediction(float DeltaSeconds, const FVector& InVelocity, const FVector& InAcceleration) const;`
- L60 _public member_ `float RotateTowardsMovementSpeed = 10.f;` — `UPROPERTY(EditDefaultsOnly, Category = "Trajectory Settings")` — If the character is forward facing (i.e. bOrientRotationToMovement is true), this controls how quickly the trajectory will rotate to face acceleration. It's common for this to differ from the rotation rate of the character, because animations are often authored with different rotation speeds than the character. This is especially true in cases where the character rotation snaps to movement.
- L65 _public member_ `float MaxControllerYawRate = 70.f;` — `UPROPERTY(EditDefaultsOnly, Category = "Trajectory Settings")` — Maximum controller yaw  rate in degrees per second used to clamp the character owner controller desired yaw to generate the prediction trajectory. Negative values disable the clamping behavior
- L70 _public member_ `float BendVelocityTowardsAcceleration = 0.f;` — `UPROPERTY(EditDefaultsOnly, Category = "Trajectory Settings", meta = (ClampMin = "0", ClampMax = "1"))` — artificially bend character velocity towards acceleration direction to compute trajectory prediction, to get sharper turns 0: character velocity is used with no alteration, 1: the acceleration direction is used as velocity direction
- L73 _public member_ `bool bUseSpeedRemappingCurve = false;` — `UPROPERTY(EditDefaultsOnly, Category = "Trajectory Settings", meta = (InlineEditConditionToggle))`
- L76 _public member_ `FRuntimeFloatCurve SpeedRemappingCurve;` — `UPROPERTY(EditDefaultsOnly, Category = "Trajectory Settings", meta = (EditCondition = "bUseSpeedRemappingCurve"))`
- L79 _public member_ `bool bUseAccelerationRemappingCurve = false;` — `UPROPERTY(EditDefaultsOnly, Category = "Trajectory Settings", meta = (InlineEditConditionToggle))`
- L82 _public member_ `FRuntimeFloatCurve AccelerationRemappingCurve;` — `UPROPERTY(EditDefaultsOnly, Category = "Trajectory Settings", meta = (EditCondition = "bUseAccelerationRemappingCurve"))`
- L87 _public member_ `bool bEnableNonStandardGravity = false;` — `UPROPERTY(EditDefaultsOnly, Category = "Trajectory Settings")` — When enabled, controller yaw rate is computed as rotation around the character's up vector instead of world Z. Required for correct trajectory prediction on non-standard gravity surfaces (walls, ceilings, slopes).
- L89 _public member_ `float ControllerYawRate = 0.f;`
- L90 _public member_ `float ControllerYawRateClamped = 0.f;`
- L91 _public member_ `float DesiredControllerYawLastUpdate = 0.f;`
- L92 _public member_ `FQuat DesiredControllerRotationLastUpdate = FQuat::Identity;`
- L94 _public member_ `float MaxSpeed = 0.f;`
- L95 _public member_ `float BrakingDeceleration = 0.f;`
- L96 _public member_ `float Friction = 0.f;`
- L98 _public member_ `FVector Velocity = FVector::ZeroVector;`
- L99 _public member_ `FVector Acceleration = FVector::ZeroVector;`
- L101 _public member_ `FVector Position = FVector::ZeroVector;`
- L102 _public member_ `FQuat Facing = FQuat::Identity;`
- L103 _public member_ `FQuat MeshCompRelativeRotation = FQuat::Identity;`
- L104 _public member_ `bool bOrientRotationToMovement = false;`

#### struct `FMotionTrajectoryLibrary`  
`struct FMotionTrajectoryLibrary`  
_L111-129_
- desc: Set of functions to help populate a FPoseSearchQueryTrajectory for motion matching. UCharacterTrajectoryComponent uses these functions, but they can also be used by a UAnimInstance to avoid the component.
- L114 _public prototype_ `static void InitTrajectorySamples(FTransformTrajectory& Trajectory, const FTrajectorySamplingData& SamplingData, const FVector& Position, const FQuat& Facing);`
- L120 _public prototype_ `static void UpdateHistory_TransformHistory(FTransformTrajectory& Trajectory, TArrayView<FVector> TranslationHistory, const FCharacterTrajectoryData& CharacterTrajectoryData, const FTrajectorySamplingData& SamplingData, float DeltaSeconds);` — Update history by tracking offsets that result from character intent (e.g. movement component velocity) and applying that to the current world transform. This works well on moving platforms as it only stores a history of movement that results from character intent, not movement from platforms.
- L124 _public prototype_ `static void UpdatePrediction_SimulateCharacterMovement(FTransformTrajectory& Trajectory, const FCharacterTrajectoryData& CharacterTrajectoryData, const FTrajectorySamplingData& SamplingData);` — Update prediction by simulating the movement math for ground locomotion from UCharacterMovementComponent.
- L128 _private prototype_ `static FVector RemapVectorMagnitudeWithCurve(const FVector& Vector, bool bUseCurve, const FRuntimeFloatCurve& Curve);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MOTIONTRAJECTORY_API`
