# Plugins / MoverExamples

- module root: `Plugins/Experimental/MoverExamples/Source/MoverExamples`
- headers: 10; symbols: 185
- symbol kinds: class=12, enum=6, enumerator=11, function=28, member=61, namespace=1, prototype=57, struct=8, variable=1
- PublicDependencyModuleNames: CableComponent, Core, CoreUObject, Engine, EnhancedInput, InputCore, Mover

### `Plugins/Experimental/MoverExamples/Source/MoverExamples/Public/CharacterVariants/AbilityInputs.h` (Public)


#### struct `FMoverExampleAbilityInputs`  
`struct FMoverExampleAbilityInputs : public FMoverDataStructBase`  
_L11-105_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FMoverDataStructBase`
- desc: Data block containing extended ability inputs used by MoverExamples characters
- L16 _public member_ `bool bIsDashJustPressed = false;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mover)`
- L19 _public member_ `bool bIsAimPressed = false;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mover)`
- L22 _public member_ `bool bIsVaultJustPressed = false;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mover)`
- L25 _public member_ `bool bWantsToStartZiplining = false;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mover)`
- L28 _public member_ `bool bWantsToBeCrouched = false;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mover)`
- L31 _public function_ `virtual bool ShouldReconcile(const FMoverDataStructBase& AuthorityState) const override` — Implementation of FMoverDataStructBase
- L41 _public function_ `virtual void Interpolate(const FMoverDataStructBase& From, const FMoverDataStructBase& To, float LerpFactor) override`
- L59 _public function_ `virtual void Merge(const FMoverDataStructBase& From) override`
- L71 _public function_ `virtual FMoverDataStructBase* Clone() const override` — @return newly allocated copy of this FMoverExampleAbilityInputs. Must be overridden by child classes
- L78 _public function_ `virtual bool NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess) override`
- L92 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L94 _public function_ `virtual void ToString(FAnsiStringBuilderBase& Out) const override`
- L104 _public function_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override`

#### class `UMoverExampleAbilityInputsLibrary`  
`class UMoverExampleAbilityInputsLibrary : public UBlueprintFunctionLibrary`  
_L108-123_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L114 _public function_ `static FMoverExampleAbilityInputs GetMoverExampleAbilityInputs(const FMoverDataCollection& FromCollection)` — `UFUNCTION(BlueprintCallable, Category = "Mover|Input")`

### `Plugins/Experimental/MoverExamples/Source/MoverExamples/Public/CharacterVariants/Ziplining/ZiplineInterface.h` (Public)


#### class `UZipline`  
`class UZipline : public UInterface`  
_L12-15_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IZipline`  
`class IZipline`  
_L20-30_
- desc: Interface that can be implemented on an object supporting simple zipline traversal between 2 points, represented as Scene Components.
- L26 _public prototype_ `USceneComponent* GetStartComponent();` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Zipline")`
- L29 _public prototype_ `USceneComponent* GetEndComponent();` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Zipline")`

### `Plugins/Experimental/MoverExamples/Source/MoverExamples/Public/CharacterVariants/Ziplining/ZipliningMode.h` (Public)


#### class `UZipliningMode`  
`class UZipliningMode : public UBaseMovementMode`  
_L18-29_
- reflection: `UCLASS(Blueprintable, BlueprintType)`
- inherits: `UBaseMovementMode`
- desc: ZipliningMode: movement mode that traverses an actor implementing the IZipline interface
- L23 _public prototype_ `virtual void GenerateMove_Implementation(const FMoverSimContext& SimContext, const FMoverTickStartData& StartState, const FMoverTimeStep& TimeStep, FProposedMove& OutProposedMove) const override;`
- L24 _public prototype_ `virtual void SimulationTick_Implementation(const FSimulationTickParams& Params, FMoverTickEndData& OutputState) override;`
- L28 _public member_ `float MaxSpeed = 1000.0f;` — `UPROPERTY(EditAnywhere, Category = "Ziplining", meta = (ClampMin = "1", UIMin = "1", ForceUnits = "cm/s"))` — Maximum speed

#### struct `FZipliningState`  
`struct FZipliningState : public FMoverDataStructBase`  
_L34-52_
- reflection: `USTRUCT()`
- inherits: `FMoverDataStructBase`
- desc: Data block containing ziplining state info, used while ZipliningMode is active
- L38 _public member_ `TObjectPtr<AActor> ZiplineActor;`
- L39 _public member_ `bool bIsMovingAtoB;`
- L41 _public function_ `FZipliningState() : bIsMovingAtoB(true)`
- L46 _public prototype_ `virtual FMoverDataStructBase* Clone() const override;`
- L47 _public prototype_ `virtual bool NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess) override;`
- L48 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L49 _public prototype_ `virtual void ToString(FAnsiStringBuilderBase& Out) const override;`
- L50 _public prototype_ `virtual bool ShouldReconcile(const FMoverDataStructBase& AuthorityState) const override;`
- L51 _public prototype_ `virtual void Interpolate(const FMoverDataStructBase& From, const FMoverDataStructBase& To, float Pct) override;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits< FZipliningState > : public TStructOpsTypeTraitsBase2< FZipliningState >`  
_L55-61_
- inherits: `TStructOpsTypeTraitsBase2<FZipliningState>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L58-60_

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace ExtendedModeNames`
- L12 _variable_ `const FName Ziplining = TEXT("Zip` (scope `ExtendedModeNames`)
- L59 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anon2f7ca4f60103`) — Needed for copying non-uproperty members

### `Plugins/Experimental/MoverExamples/Source/MoverExamples/Public/CharacterVariants/Ziplining/ZipliningTransitions.h` (Public)


#### class `UZiplineStartTransition`  
`class UZiplineStartTransition : public UBaseMovementModeTransition`  
_L14-23_
- reflection: `UCLASS(Blueprintable, BlueprintType)`
- inherits: `UBaseMovementModeTransition`
- desc: Transition that handles starting ziplining based on input. Character must be airborne to catch the zipline, regardless of input.
- L19 _public prototype_ `virtual FTransitionEvalResult Evaluate_Implementation(const FSimulationTickParams& Params) const override;`
- L22 _public member_ `FName ZipliningModeName = ExtendedModeNames::Ziplining;` — `UPROPERTY(EditAnywhere, Category = "Ziplining")`

#### class `UZiplineEndTransition`  
`class UZiplineEndTransition : public UBaseMovementModeTransition`  
_L29-40_
- reflection: `UCLASS(Blueprintable, BlueprintType)`
- inherits: `UBaseMovementModeTransition`
- desc: Transition that handles exiting ziplining based on input
- L34 _public prototype_ `virtual FTransitionEvalResult Evaluate_Implementation(const FSimulationTickParams& Params) const override;`
- L35 _public prototype_ `virtual void Trigger_Implementation(const FSimulationTickParams& Params) override;`
- L39 _public member_ `FName AutoExitToMode = DefaultModeNames::Falling;` — `UPROPERTY(EditAnywhere, Category = "Ziplining")` — Mode to enter when exiting the zipline

### `Plugins/Experimental/MoverExamples/Source/MoverExamples/Public/MovementBases/FollowPathMode.h` (Public)


#### enum `EFollowPathRotationType`  
`enum class EFollowPathRotationType : uint8`  
_L16-25_
- reflection: `UENUM(BlueprintType)`
- desc: Controls how rotation is handled during pathing
- L19 _public enumerator_ `Fixed` — Maintain original actor orientation
- L21 _public enumerator_ `AlignWithPathTangents` — Orient moving actor by intepolating between path tangents
- L23 _public enumerator_ `AlignWithPath` — Orient moving actor to the path

#### class `UFollowPathMode`  
`class UFollowPathMode : public UBaseMovementMode`  
_L33-92_
- reflection: `UCLASS(Blueprintable, BlueprintType)`
- inherits: `UBaseMovementMode`
- desc: FollowPathMode: This mode performs simple movement of the associated actor, attempting to interpolate through a series of locations. There are variety of settings that affect behavior, such as speed and looping.
- L39 _public prototype_ `virtual void GenerateMove_Implementation(const FMoverSimContext& SimContext, const FMoverTickStartData& StartState, const FMoverTimeStep& TimeStep, FProposedMove& OutProposedMove) const override;`
- L40 _public prototype_ `virtual void SimulationTick_Implementation(const FSimulationTickParams& Params, FMoverTickEndData& OutputState) override;`
- L42 _public prototype_ `virtual void Activate(const FMoverEventContext& Context, FName PrevModeName, const FMoverSimContext& SimContext, const FMoverTickStartData& StartState, FMoverSyncState* OutSyncState, FMoverAuxStateContext* OutAuxState) override;`
- L46 _public member_ `TArray<FInterpControlPoint> ControlPoints;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pathing)` — List of ordered path locations to visit
- L50 _public member_ `EInterpToBehaviourType BehaviourType;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pathing)` — Method of path-following
- L54 _public member_ `EFollowPathRotationType RotationType;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pathing)` — Method of rotating the actor during path-following
- L58 _public member_ `float Duration = 5.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pathing, meta = (UIMin = 0.1f, ClampMin = 0.1f, ForceUnits=s))` — Time (in seconds) required to move from the first point to the last (or vice versa)
- L64 _protected prototype_ `virtual void UpdateControlPoints(bool InForceUpdate);` — Update the control points. Adjusts the positions of there are any actor control points as well as updating the spline type
- L67 _protected prototype_ `float CalculateNewPathPct(float InPathPct, float InDirectionMod, float InDeltaSecs, bool& OutStopped, float& OutTimeRemainder, float& OutNewDirectionMod) const;` — Based on current path pct + direction + time step, find the next path pct, possibly stopping or changing direction mid-step
- L70 _protected prototype_ `FVector ComputeMoveDelta(const FVector CurrentPos, const FVector BaseLocation, const float TargetPathPos) const;` — Find the necessary move delta to get onto path at a certain pct, based on current location
- L72 _protected prototype_ `FRotator ComputeMoveOrientation(const float TargetPathPos, const FVector& BaseLocation, FRotator DefaultOrientation) const;`
- L74 _protected prototype_ `FVector ComputeInterpolatedTangentFromPathPct(const float PathPct) const;`
- L76 _protected prototype_ `FVector ComputeTangentFromPathPct(const float PathPct, const FVector& BaseLocation) const;`
- L80 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L87 _private member_ `float TotalDistance;` — Cached distance summed between all control points
- L88 _private member_ `float TimeMultiplier;` — Converts seconds to path position percent
- L90 _private member_ `TArray<FVector> ControlPointPathTangents;`

#### struct `FFollowPathState`  
`struct FFollowPathState : public FMoverDataStructBase`  
_L97-161_
- reflection: `USTRUCT()`
- inherits: `FMoverDataStructBase`
- desc: Data block containing path-following state info
- L101 _public member_ `FVector BaseLocation;` — Starting point of this pathing, used for relative pathing
- L102 _public member_ `float CurrentPathPos;` — [0.0, 1.0] to indicate a position on the path, as a percent from start to finish.
- L103 _public member_ `float CurrentDirectionMod;` — typically 1 or -1 to indicate direction we're traveling on the path
- L107 _public function_ `FFollowPathState() : BaseLocation(FVector::ZeroVector) , CurrentPathPos(-1.0f) , CurrentDirectionMod(1.0f)`
- L114 _public function_ `bool HasValidPathState() const`
- L116 _public prototype_ `virtual FMoverDataStructBase* Clone() const override;`
- L119 _public function_ `virtual bool NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess) override`
- L131 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L133 _public function_ `virtual void ToString(FAnsiStringBuilderBase& Out) const override`
- L142 _public function_ `virtual bool ShouldReconcile(const FMoverDataStructBase& AuthorityState) const override`
- L151 _public function_ `virtual void Interpolate(const FMoverDataStructBase& From, const FMoverDataStructBase& To, float Pct) override`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FFollowPathState> : public TStructOpsTypeTraitsBase2<FFollowPathState>`  
_L164-170_
- inherits: `TStructOpsTypeTraitsBase2<FFollowPathState>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L167-169_

#### Free symbols / members of external scopes

- L168 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anon54a2bd430103`) — Necessary so that non-uproperty members get copied

### `Plugins/Experimental/MoverExamples/Source/MoverExamples/Public/MovementBases/FollowSplineMode.h` (Public)


#### enum `ESplineOffsetUnit`  
`enum class ESplineOffsetUnit : uint8`  
_L18-23_
- reflection: `UENUM(Blueprintable, BlueprintType)`
- L20 _public enumerator_ `Percentage UMETA(DisplayName="Percentage")`
- L21 _public enumerator_ `DurationAbsoluteSeconds UMETA(DisplayName = "Duration Absolute(sec)")`
- L22 _public enumerator_ `DistanceAbsolute UMETA(DisplayName = "Distance Absolute")`

#### enum `EFollowSplineRotationType`  
`enum class EFollowSplineRotationType : uint8`  
_L26-30_
- reflection: `UENUM(BlueprintType)`
- L28 _public enumerator_ `FollowSplineTangent UMETA(DisplayName="Follow Spline Tangent")`
- L29 _public enumerator_ `NoRotation UMETA(DisplayName = "No Rotation")`

#### struct `FSplineOffsetRangeInput`  
`struct FSplineOffsetRangeInput`  
_L36-45_
- reflection: `USTRUCT(BlueprintType)`
- desc: Represents an input for Range based follow behavior
- L41 _public member_ `float Value = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inputs")`
- L44 _public member_ `ESplineOffsetUnit OffsetUnit = ESplineOffsetUnit::Percentage;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inputs")`

#### class `UFollowSplineMode`  
`class UFollowSplineMode : public UBaseMovementMode`  
_L53-130_
- reflection: `UCLASS(Blueprintable, BlueprintType)`
- inherits: `UBaseMovementMode`
- desc: FollowSplineMode: This mode performs movement of the associated actor, along a spline. Default settings will provide a follow from start to end of the Spline. However, the start and end offsets could make the actor trace intermediate paths along the spline.
- L58 _public prototype_ `virtual void GenerateMove_Implementation(const FMoverSimContext& SimContext, const FMoverTickStartData& StartState, const FMoverTimeStep& TimeStep, FProposedMove& OutProposedMove) const override;`
- L60 _public prototype_ `virtual void SimulationTick_Implementation(const FSimulationTickParams& Params, FMoverTickEndData& OutputState) override;`
- L63 _public prototype_ `void SetControlSpline(const AActor* SplineProviderActor, FSplineOffsetRangeInput Offset = FSplineOffsetRangeInput());` — `UFUNCTION(BlueprintCallable, Category = "Mover|Spline")`
- L67 _public member_ `EInterpToBehaviourType BehaviourType;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pathing)` — Follow Mode for Path Following
- L71 _public member_ `EFollowSplineRotationType RotationType;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pathing)` — Rotation Mode for Path Following
- L75 _public member_ `bool bOrientMoverToMovement = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pathing)` — Should Mover face in the direction of movement at all times
- L79 _public member_ `bool bConstantFollowVelocity = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pathing)` — Should Mover follow spline with constant velocity
- L83 _public member_ `bool StartReveresed = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pathing)` — Should the mover start following from the End
- L87 _public member_ `FSplineOffsetRangeInput StartOffset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pathing|Offsets")` — Optional starting offset to define ranged follow
- L91 _public member_ `FSplineOffsetRangeInput EndOffset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pathing|Offsets")` — Optional end offset to define ranged follow
- L95 _public member_ `float CustomDurationSecondsOverride = -1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pathing|Offsets", meta=(ForceUnits="sec"))` — If greater than zero, the follow motion would map the spline time to this duration.
- L99 _public member_ `TObjectPtr<UCurveFloat> InterpolationCurve;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pathing|Interpolation")` — Optional Interpolation curve to dictate the speed and position for follow
- L102 _protected prototype_ `virtual void OnRegistered(const FName ModeName, const FMoverSimContext& SimContext) override;`
- L104 _protected prototype_ `void ConfigureSplineData();`
- L105 _protected prototype_ `bool CanMove(float MeasuredSplineTime) const;`
- L107 _protected prototype_ `FTransform GetTransformAtTime(float MeasuredSplineTime, const FRotator& DefaultOrientation);`
- L109 _protected prototype_ `float ApplyBehaviorType(float MeasuredSplineTime);`
- L110 _protected prototype_ `float ApplyFollowDirection(float MeasuredSplineTime);`
- L112 _protected prototype_ `void UpdatePathState(FFollowSplineState& OutputPathState);`
- L116 _protected member_ `TObjectPtr<USplineComponent> ControlSpline;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pathing)`
- L119 _private member_ `int32 StartReversedMultiplier = 1;`
- L120 _private member_ `int32 FollowDirectionMultiplier = 1;`
- L121 _private member_ `int32 OrientationMultiplier = 1;`
- L124 _private member_ `float CurrentSplineTime = 0.0f;` — Local State Variables
- L125 _private member_ `float StartOffsetSeconds = 0.0f;`
- L126 _private member_ `float EndOffsetSeconds = 0.0f;`
- L127 _private member_ `float FollowDuration = 0.0f;`
- L129 _private member_ `bool bResetPingPong = false;`

#### struct `FFollowSplineState`  
`struct FFollowSplineState : public FMoverDataStructBase`  
_L135-194_
- reflection: `USTRUCT()`
- inherits: `FMoverDataStructBase`
- desc: Data block containing path-following state info
- L139 _public member_ `float CurrentSplineTime;` — Current Accumulated Time on the Spline
- L140 _public member_ `int32 CurrentDirectionMultiplier;` — typically 1 or -1 to indicate direction we're traveling on the path
- L142 _public function_ `FFollowSplineState() : CurrentSplineTime(-1.0f) , CurrentDirectionMultiplier(1)`
- L148 _public prototype_ `virtual FMoverDataStructBase* Clone() const override;`
- L150 _public function_ `virtual bool NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess) override`
- L161 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L163 _public function_ `virtual void ToString(FAnsiStringBuilderBase& Out) const override`
- L171 _public function_ `virtual bool ShouldReconcile(const FMoverDataStructBase& AuthorityState) const override`
- L179 _public function_ `virtual void Interpolate(const FMoverDataStructBase& From, const FMoverDataStructBase& To, float Pct) override`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FFollowSplineState> : public TStructOpsTypeTraitsBase2<FFollowSplineState>`  
_L197-203_
- inherits: `TStructOpsTypeTraitsBase2<FFollowSplineState>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L200-202_

#### Free symbols / members of external scopes

- L201 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anonfd99af010103`) — Necessary so that non-uproperty members get copied

### `Plugins/Experimental/MoverExamples/Source/MoverExamples/Public/MoverExamplesCharacter.h` (Public)


#### class `AMoverExamplesCharacter`  
`class AMoverExamplesCharacter : public APawn, public IMoverInputProducerInterface`  
_L21-135_
- reflection: `UCLASS(Abstract)`
- inherits: `APawn,IMoverInputProducerInterface`
- L27 _public prototype_ `AMoverExamplesCharacter(const FObjectInitializer& ObjectInitializer);` — Sets default values for this pawn's properties
- L32 _public prototype_ `virtual void Tick(float DeltaTime) override;` — Called every frame
- L34 _public prototype_ `virtual void BeginPlay() override;`
- L36 _public prototype_ `virtual void PostInitializeComponents() override;`
- L39 _public prototype_ `virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;` — Called to bind functionality to input
- L43 _public function_ `UCharacterMoverComponent* GetMoverComponent() const` — `UFUNCTION(BlueprintPure, Category = Mover)` — Accessor for the actor's movement component
- L47 _public function_ `virtual void RequestMoveByIntent(const FVector& DesiredIntent)` — `UFUNCTION(BlueprintCallable, Category=MoverExamples)` — Request the character starts moving with an intended directional magnitude. A length of 1 indicates maximum acceleration.
- L51 _public function_ `virtual void RequestMoveByVelocity(const FVector& DesiredVelocity)` — `UFUNCTION(BlueprintCallable, Category=MoverExamples)` — Request the character starts moving with a desired velocity. This will be used in lieu of any other input.
- L54 _public prototype_ `virtual FVector GetNavAgentLocation() const override;`
- L57 _public prototype_ `virtual void UpdateNavigationRelevance() override;`
- L61 _protected prototype_ `virtual void ProduceInput_Implementation(int32 SimTimeMs, FMoverInputCmdContext& InputCmdResult) override;` — Entry point for input production. Do not override. To extend in derived character types, override OnProduceInput for native types or implement "Produce Input" blueprint event
- L64 _protected prototype_ `virtual void OnProduceInput(float DeltaMs, FMoverInputCmdContext& InputCmdResult);` — Override this function in native class to author input for the next simulation frame. Consider also calling Super method.
- L68 _protected prototype_ `FMoverInputCmdContext OnProduceInputInBlueprint(float DeltaMs, FMoverInputCmdContext InputCmd);` — `UFUNCTION(BlueprintImplementableEvent, DisplayName="On Produce Input", meta = (ScriptName = "OnProduceInput"))` — Implement this event in Blueprints to author input for the next simulation frame. Consider also calling Parent event.
- L72 _protected member_ `TObjectPtr<UInputAction> MoveInputAction;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)` — Move Input Action
- L76 _protected member_ `TObjectPtr<UInputAction> LookInputAction;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)` — Look Input Action
- L80 _protected member_ `TObjectPtr<UInputAction> JumpInputAction;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)` — Jump Input Action
- L84 _protected member_ `TObjectPtr<UInputAction> FlyInputAction;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)` — Fly Input Action
- L89 _public member_ `bool bUseBaseRelativeMovement = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MoverExamples)` — Whether or not we author our movement inputs relative to whatever base we're standing on, or leave them in world space. Only applies if standing on a base of some sort.
- L95 _public member_ `bool bOrientRotationToMovement = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MoverExamples)` — If true, rotate the Character toward the direction the actor is moving
- L102 _public member_ `bool bMaintainLastInputOrientation = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MoverExamples)` — If true, the actor will continue orienting towards the last intended orientation (from input) even after movement intent input has ceased. This makes the character finish orienting after a quick stick flick from the player.  If false, character will not turn without input.
- L106 _protected member_ `TObjectPtr<UCharacterMoverComponent> CharacterMotionComponent;` — `UPROPERTY(Category = Movement, VisibleAnywhere, BlueprintReadOnly, Transient, meta = (AllowPrivateAccess = "true"))`
- L110 _protected member_ `TObjectPtr<UNavMoverComponent> NavMoverComponent;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient, Category="Nav Movement")` — Holds functionality for nav movement data and functions
- L113 _private member_ `FVector LastAffirmativeOrientationIntent = FVector::ZeroVector;` — Orientation direction at the last time we had one that wasn't zero
- L115 _private member_ `FVector CachedMoveInputIntent = FVector::ZeroVector;`
- L116 _private member_ `FVector CachedMoveInputVelocity = FVector::ZeroVector;`
- L118 _private member_ `FRotator CachedTurnInput = FRotator::ZeroRotator;`
- L119 _private member_ `FRotator CachedLookInput = FRotator::ZeroRotator;`
- L121 _private member_ `bool bIsJumpJustPressed = false;`
- L122 _private member_ `bool bIsJumpPressed = false;`
- L123 _private member_ `bool bIsFlyingActive = false;`
- L124 _private member_ `bool bShouldToggleFlying = false;`
- L126 _private prototype_ `void OnMoveTriggered(const FInputActionValue& Value);`
- L127 _private prototype_ `void OnMoveCompleted(const FInputActionValue& Value);`
- L128 _private prototype_ `void OnLookTriggered(const FInputActionValue& Value);`
- L129 _private prototype_ `void OnLookCompleted(const FInputActionValue& Value);`
- L130 _private prototype_ `void OnJumpStarted(const FInputActionValue& Value);`
- L131 _private prototype_ `void OnJumpReleased(const FInputActionValue& Value);`
- L132 _private prototype_ `void OnFlyTriggered(const FInputActionValue& Value);`
- L134 _private member_ `uint8 bHasProduceInputinBpFunc : 1;`

### `Plugins/Experimental/MoverExamples/Source/MoverExamples/Public/MoverExamplesGameMode.h` (Public)


#### class `AMoverExamplesGameMode`  
`class AMoverExamplesGameMode : public AGameMode`  
_L14-27_
- reflection: `UCLASS(BlueprintType)`
- inherits: `AGameMode`
- L18 _private prototype_ `AMoverExamplesGameMode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L20 _private function_ `virtual bool AllowCheats(APlayerController* P)`
- L23 _private prototype_ `virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;` — select best spawn point for player
- L26 _private prototype_ `bool CanPlayerPawnFit(const APlayerStart* SpawnPoint, const AController* Player) const;`

### `Plugins/Experimental/MoverExamples/Source/MoverExamples/Public/MoverExamplesGameState.h` (Public)


#### class `AMoverExamplesGameState`  
`class AMoverExamplesGameState : public AGameState`  
_L12-17_
- reflection: `UCLASS(BlueprintType)`
- inherits: `AGameState`
- L16 _private prototype_ `AMoverExamplesGameState() = default;`

### `Plugins/Experimental/MoverExamples/Source/MoverExamples/Public/MoverExamplesModule.h` (Public)


#### class `FMoverExamplesModule`  
`class FMoverExamplesModule : public IModuleInterface`  
_L8-15_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L14 _public prototype_ `virtual void ShutdownModule() override;`
