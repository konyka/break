# Plugins / Locomotor

- module root: `Plugins/Experimental/Animation/Locomotor/Source/Locomotor`
- headers: 3; symbols: 298
- symbol kinds: class=1, enum=2, enumerator=6, function=34, member=188, prototype=41, struct=26
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: CoreUObject, Engine, Slate, SlateCore
- PublicDependencyModuleNames: ControlRig, Core, RigVM

### `Plugins/Experimental/Animation/Locomotor/Source/Locomotor/Public/Locomotor.h` (Public)


#### class `FLocomotorModule`  
`class FLocomotorModule : public IModuleInterface`  
_L7-14_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L13 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Experimental/Animation/Locomotor/Source/Locomotor/Public/LocomotorCore.h` (Public)


#### struct `FVectorDamper`  
`struct FVectorDamper`  
_L12-44_
- desc: Daniel Holden's "Exact Damper" described here https://theorangeduck.com/page/spring-roll-call
- L14 _public function_ `const FVector& Update(const FVector& TargetValue, const float DeltaTime, const float HalfLife=0.1f)`
- L25 _public function_ `static float FastNegExp(float x)`
- L31 _public function_ `void Reset(const FVector& InValue)`
- L36 _public function_ `FVector GetCurrentValue() const`
- L43 _private member_ `FVector CurrentValue;`

#### struct `FFloatSpring`  
`struct FFloatSpring`  
_L46-75_
- L48 _public prototype_ `FFloatSpring() = default;`
- L50 _public function_ `float Update(float DeltaTime, const float& TargetValue, const float Stiffness, const float Damping)`
- L60 _public function_ `void Reset(const float& InValue)`
- L66 _public function_ `float GetCurrent() const`
- L73 _private member_ `float CurrentValue;`
- L74 _private member_ `FFloatSpringState SpringState;`

#### struct `FVectorSpring`  
`struct FVectorSpring`  
_L77-106_
- L79 _public prototype_ `FVectorSpring() = default;`
- L81 _public function_ `FVector Update(float DeltaTime, const FVector& TargetValue, const float Stiffness, const float Damping)`
- L91 _public function_ `void Reset(const FVector& InValue)`
- L97 _public function_ `FVector GetCurrent() const`
- L104 _private member_ `FVector CurrentValue;`
- L105 _private member_ `FVectorSpringState SpringState;`

#### struct `FQuatSpring`  
`struct FQuatSpring`  
_L108-137_
- L111 _public prototype_ `FQuatSpring() = default;`
- L113 _public function_ `FQuat Update(float DeltaTime, const FQuat& Target, const float Stiffness, const float Damping)`
- L122 _public function_ `void Reset(const FQuat& InValue)`
- L128 _public function_ `FQuat GetCurrent() const`
- L135 _private member_ `FQuat Current;`
- L136 _private member_ `FQuaternionSpringState SpringState;`

#### enum `EMovementStyle`  
`enum class EMovementStyle : uint8`  
_L139-144_
- L141 _public enumerator_ `Walk`
- L142 _public enumerator_ `Trot`
- L143 _public enumerator_ `Gallop`

#### struct `FLocomotorMovementSettings`  
`struct FLocomotorMovementSettings`  
_L146-168_
- L149 _public member_ `float MinimumStepLength = 10.0f;` — the smallest step to make
- L151 _public member_ `float SpeedMax = 80.f;` — the maximum movement speed in cm/s
- L153 _public member_ `float SpeedMin = 50.f;` — the maximum movement speed in cm/s
- L155 _public member_ `float PhaseSpeedMax = 4.f;` — the maximum phase speed in cycles/s
- L157 _public member_ `float PhaseSpeedMin = 1.0f;` — the minimum phase speed in cycles/s
- L159 _public member_ `float Acceleration = 100.f;` — the acceleration in cm/s/s
- L161 _public member_ `float Deceleration = 30.f;` — the acceleration in cm/s/s
- L163 _public member_ `TArray<EMovementStyle> Styles;` — movement styles
- L165 _public member_ `bool bTeleport = false;` — teleportation

#### struct `FLocomotorStepSettings`  
`struct FLocomotorStepSettings`  
_L170-207_
- L176 _public member_ `float PercentOfStrideInAir = 0.35f;` — Default is 0.35. Range is 0.1 - 0.9. The percentage amount of the 0-1 stride phase where the foot is in the air. At the default (0.35), the foot will plant on the ground 35% through it's total phase. At lower values, the foot will spend more time on the ground as a percentage of the total stride time. At higher values, each foot will spend less time on the ground as a percentage of the total stride time.
- L181 _public member_ `float AirExtensionAtMaxSpeed = 0.2f;` — Default is 0.2. Range is 0.0 - 0.9. This value is added to the "PercentOfStrideInAir" to extend the air-time while at max speed. For example, if PercentOfStrideInAir is at 0.5, and the air extension is at 0.4 the foot will be in the air for 90% of the stride cycle. This value is gradually blended on as the Speed accelerates between SpeedMin and SpeedMax. The total "Stride In Air" is clamped internally at 95%
- L183 _public member_ `float StepHeight = 10.f;` — Default is 6. Range is 0-inf. The height to raise foot (in cm) at the peak of the largest stride
- L185 _public member_ `float StepEaseIn = 0.5f;` — Default is 0.5. Range is 0-1. How quickly the foot accelerates when lifting off the ground. At 0, it instantly moves, at 1 it eases in.
- L187 _public member_ `float StepEaseOut = 0.2f;` — Default is 0.2. Range is 0-1. How quickly the foot decelerates when planting. At 0, it instantly stops on contact, at 1 it eases into contact.
- L189 _public member_ `bool bEnableFootCollision = false;` — Default is true. When true, feet are treated as non-overlapping circles and will not overlap each other or cross over.
- L191 _public member_ `float FootCollisionGlobalScale = 1.0f;` — Default is 1.0. Range is 0-inf. Global scale multiplier for all foot collision radii.
- L193 _public member_ `bool bEnableGroundCollision = true;` — Default is true. When true, foot height is adjusted using sphere-casting against the world.
- L195 _public member_ `float MaxCollisionHeight = 30.0f;` — Default is 30. Range is 0-inf. The maximum height in cm to place foot on-top of collision geo (may move foot up or down by this amount).
- L197 _public member_ `TEnumAsByte<ETraceTypeQuery> TraceChannel;` — The 'channel' used to trace spheres into the physics world for collision detection. Determines which components to hit.
- L199 _public member_ `float OrientFootToGroundPitch = 0.8f;` — Default is 0.8. Range is 0-1. When Ground Collision is enabled, this will orient the pitch of the foot to match the slope of the ground.
- L201 _public member_ `float OrientFootToGroundRoll = 0.5f;` — Default is 0.8. Range is 0-1. When Ground Collision is enabled, this will orient the roll of the foot to match the slope of the ground.
- L203 _public member_ `const AActor* IgnoredActor = nullptr;` — actor and component to ignore in collision queries
- L204 _public member_ `const UActorComponent* IgnoredComponent = nullptr;`
- L206 _public member_ `const UWorld* World = nullptr;` — the world to collide against

#### struct `FLocomotorPelvisSettings`  
`struct FLocomotorPelvisSettings`  
_L209-234_
- L213 _public member_ `FTransform InputPelvisComponentSpace;` — this represents the current input pose of the skeleton coming from animation this allows the locomotor to adapt dynamically to changing animation
- L215 _public member_ `float PositionDampingHalfLife = 0.05f;` — Default is 0.05. Typical range is 0.05-1. The time (in seconds) it takes for the Pelvis to reach half way to it's position goal.
- L217 _public member_ `float RotationStiffness = 40.f;` — Default is 2.0. Typical range is 0-20. Higher values cause pelvis to rotate more rapidly towards goal orientation.
- L219 _public member_ `float RotationDamping = .9f;` — Default is 2.0. Typical range is 0-20. Higher values cause pelvis rotation to dampen quickly.
- L221 _public member_ `float LeadAmount = 3.f;` — Default is 3.0. Typical range is 1-3. Higher values cause pelvis to move further ahead of the feet.
- L223 _public member_ `float LeadDampingHalfLife = 0.1f;` — Default is 0.1. Typical range is 0.1-1. The time (in seconds) it takes for the Pelvis to reach half way to it's lead goal.
- L225 _public member_ `float BobOffset = -4.f;` — Default is -3.f. Range is -inf to -inf. The amount to lower the pelvis at the minimum height in the cycle.
- L227 _public member_ `float BobStiffness = 150.f;` — Default is 150.0. Typical range is 1-200. Higher values cause pelvis to bob more rapidly towards target height.
- L229 _public member_ `float BobDamping = 1.25f;` — Default is 0.9. Typical range is 0-2. Higher values cause pelvis bob to dampen quickly.
- L231 _public member_ `float OrientToGroundPitch = -0.3f;` — Default is -0.3. Typical range is -1 to 1. Pitch the pelvis up/down with ground. 0 is no effect, 1/-1 matches ground orientation. Use negative values for bipeds, positive for quadrupeds.
- L233 _public member_ `float OrientToGroundRoll = -0.3f;` — Default is -0.3. Typical range is -1 to 1. Roll the pelvis side-to-side with ground. 0 is no effect, 1/-1 matches ground orientation. Use negative values for bipeds, positive for quadrupeds.

#### struct `FLocomotorSpineSettings`  
`struct FLocomotorSpineSettings`  
_L236-244_
- L239 _public member_ `float LeanAngleMax = 30.0f;` — Default is 30. The maximum angle (in degrees) to lean the spine in the direction of travel.
- L241 _public member_ `float LeanStiffness = 150.f;` — Default is 150.0. Typical range is 1-200. Higher values cause spine to lean more rapidly towards target direction.
- L243 _public member_ `float LeanDamping = 0.9f;` — Default is 0.9. Typical range is 0-2. Higher values cause spine leaning to dampen quickly.

#### struct `FLocomotorHeadSettings`  
`struct FLocomotorHeadSettings`  
_L246-254_
- L249 _public member_ `float AngleMax = 30.0f;` — Default is 30. The maximum angle (in degrees) to rotate the head to look at the goal.
- L251 _public member_ `float Stiffness = 150.f;` — Default is 150.0. Typical range is 1-200. Higher values cause spine to lean more rapidly towards target direction.
- L253 _public member_ `float Damping = 0.9f;` — Default is 0.9. Typical range is 0-2. Higher values cause spine leaning to dampen quickly.

#### struct `FLocomotorFootSettings`  
`struct FLocomotorFootSettings`  
_L256-268_
- L259 _public member_ `float CollisionRadius = 10.f;` — the radius in cm to avoid feet penetrations
- L261 _public member_ `FVector MaxHeelPeel = FVector(0.f, 0.f, 50.f);` — Default is (0, 0, 50). The max rotation to peel the heel before lift off. This is in the local space of the ankle bone.
- L263 _public member_ `float StaticPhaseOffset = 0.f;` — either 0.0f or 0.5f depending on order in set (alternates Left/Right/Left/Right with values 0 / 0.5 / 0 / 0.5 etc...)
- L265 _public member_ `FVector StaticLocalOffset = FVector::ZeroVector;` — applies a static offset that shifts feet in the local space of the foot bone in the reference pose
- L267 _public member_ `int32 FootSetIndex = 0;` — the index of the set this foot belongs to

#### struct `FLocomotorInputSettings`  
`struct FLocomotorInputSettings`  
_L270-284_
- L273 _public member_ `FTransform CurrentWorldRootGoal;` — the current target goal location in world space
- L275 _public member_ `float DeltaTime = 0.16f;` — time in seconds since last update
- L277 _public member_ `FLocomotorMovementSettings Movement;` — all settings related to overall movement and strides
- L279 _public member_ `FLocomotorStepSettings Stepping;` — all settings related to steps
- L281 _public member_ `FLocomotorPelvisSettings Pelvis;` — pelvis settings
- L283 _public member_ `FLocomotorSpineSettings Spine;` — spine settings

#### struct `FPlaneConstraint`  
`struct FPlaneConstraint`  
_L286-292_
- L288 _public function_ `FPlaneConstraint() : Active(false), Normal(FVector::UpVector)`
- L290 _public member_ `bool Active;`
- L291 _public member_ `FVector Normal;`

#### struct `FLocomotorFoot`  
`struct FLocomotorFoot`  
_L294-355_
- L296 _public prototype_ `FLocomotorFoot( const FTransform& InitialWorldRootGoal, const FTransform& InitialWorldFoot, const FLocomotorFootSettings& InSettings);`
- L301 _public member_ `FLocomotorFootSettings Settings;`
- L304 _public member_ `float TargetPhase = 0.f;` — the current phase gradually approaches this value, we don't directly set the current phase to avoid foot popping
- L306 _public member_ `float CurrentPhase = 0.f;` — the current phase of this foot to use for animation
- L308 _public member_ `float FootPhaseWhenSwingEnds = 0.5f;` — the point in the foot's phase when the swing begins (variable with speed/frequency)
- L310 _public member_ `bool bAtRest = true;` — whether this foot is close enough to the final goal to stop animating
- L312 _public member_ `bool bInSwingPhase = false;` — current state of the foot (either swinging or planted)
- L314 _public member_ `bool bUnplantingThisTick = false;` — only true on the tick when this foot transitions to bInSwingPhase=true
- L316 _public member_ `bool bWantsToStep = false;` — does this foot currently have a target beyond the min step threshold?
- L318 _public member_ `FVector PrevToFinalTargetNorm;` — the distance from the planted location to the final target
- L319 _public member_ `float PrevToFinalTargetDistance;`
- L322 _public member_ `FTransform InitialRelativeToRootGoal;` — the initial transform relative to the initial root goal
- L324 _public member_ `FTransform InitialRelativeToBody;` — the initial transform relative to the initial body
- L326 _public member_ `FTransform InitialWorld;` — initial transform
- L329 _public member_ `float CurrentStrideHeight;` — the max height of the foot for the current stride (calculated once when unplanting)
- L331 _public member_ `FTransform StrideOriginWorld;` — the neutral location at the start of a step, may be different from the actual planted location
- L333 _public member_ `FTransform PlantedWorld;` — the prev foot plant in world space
- L335 _public member_ `FTransform CurrentTargetWorld;` — the current target location to step towards
- L337 _public member_ `FVectorSpring CurrentTargetSpring;` — a heavily damped spring for continuously updating target
- L339 _public member_ `FTransform FinalTargetWorld;` — the final destination location for foot
- L342 _public member_ `FVector CurrentWorldFlatPosition;` — the current world position of this foot with no height added
- L344 _public member_ `FVector CurrentWorldFlatPositionNoEase;` — the current world position of this foot with no height added and no ease in/out applied
- L346 _public member_ `FTransform CurrentWorld;` — the current world transform of this foot
- L348 _public member_ `FTransform PrevWorld;` — the world transform of this foot at the end of the previous tick
- L351 _public member_ `float CurrentHeightOffset;` — store current height offset for bobbing
- L354 _public member_ `FQuatSpring CurrentRotationSpring;` — rotation is smoothly blended through a spring

#### struct `FLocomotorFootSet`  
`struct FLocomotorFootSet`  
_L357-385_
- L359 _public function_ `FLocomotorFootSet(const float InPhaseOffset, int32 InSetIndex) : PhaseOffset(InPhaseOffset), SetIndex(InSetIndex)`
- L362 _public prototype_ `int32 AddFoot( const FTransform& InitialWorldRootGoal, const FTransform& InitialWorldFoot, const FLocomotorFootSettings& InSettings);` — add a foot, returns the index of the foot or -1 if no set found
- L368 _public function_ `TArray<FLocomotorFoot>& GetFeet()` — get access to the feet in this set
- L369 _public function_ `const TArray<FLocomotorFoot>& GetFeet() const`
- L372 _public function_ `int32 GetNumFeet() const` — get number of feet in this set
- L375 _public function_ `float GetPhaseOffset() const` — get the current offset of this set
- L380 _private member_ `float PhaseOffset = 0.f;` — the 0-1 phase offset for this set of feet (relative to the global phase)
- L382 _private member_ `TArray<FLocomotorFoot> Feet;` — the array of feet belonging to this set
- L384 _private member_ `int32 SetIndex = 0;` — the index of this set

#### struct `FLocomotorHead`  
`struct FLocomotorHead`  
_L387-399_
- L389 _public prototype_ `FLocomotorHead() = default;`
- L391 _public prototype_ `void Initialize(const FTransform& InInitialWorld);`
- L394 _public member_ `FTransform InitialWorld;` — the initial world transform of the head bone
- L395 _public member_ `FTransform CurrentWorld;`
- L396 _public member_ `FQuatSpring RotationSpring;`
- L398 _public member_ `bool bInitialized = false;`

#### struct `FLocomotorPelvis`  
`struct FLocomotorPelvis`  
_L401-431_
- L403 _public prototype_ `FLocomotorPelvis() = default;`
- L405 _public prototype_ `void Initialize(const TArray<FLocomotorFoot*>& AllFeet, const FTransform& InitialRootGoalWorld);`
- L407 _public prototype_ `void CalculateBodyTransform( const TArray<FLocomotorFoot*> AllFeet, const FTransform& RootGoal, FTransform& OutBodyTransform);`
- L413 _public member_ `FTransform InitialWorld;` — the initial world transform of the pelvis
- L414 _public member_ `FTransform InitialRelativeToRootGoal;`
- L415 _public member_ `FTransform CurrentWorld;`
- L419 _public member_ `FTransform InitialBodyWorld;` — the transform of the "body"; this is a separately maintained transform representing the center of mass which is different than the pelvis location which is usually far from the center of the body in quadrupeds
- L420 _public member_ `FTransform CurrentBodyWorld;`
- L421 _public member_ `FTransform PreviousBodyTargetWorld;`
- L422 _public member_ `FTransform CurrentBodyTargetWorld;`
- L423 _public member_ `FVector CurrentBodyLead;`
- L424 _public member_ `FVectorDamper BodyLeadDamper;`
- L425 _public member_ `FQuatSpring BodyRotationSpring;`
- L426 _public member_ `FVectorDamper PelvisPositionDamper;`
- L429 _public member_ `float CurrentHeightOffset;` — height offset (bob) is tracked separately and applied additively through a spring
- L430 _public member_ `FFloatSpring BobOffsetSpring;`

#### struct `FLocomotor`  
`struct FLocomotor`  
_L434-551_
- reflection: `USTRUCT()`
- L440 _public prototype_ `FLocomotor() = default;`
- L443 _public prototype_ `void Reset( const FTransform& InInitialRootGoalWorld, const FTransform& InInitialWorldPelvis);` — initialize all internal data structures (can be called multiple times)
- L448 _public prototype_ `int32 AddFootSet(const float PhaseOffset);` — add a set of feet, returns the foot set
- L451 _public prototype_ `int32 AddFootToSet( const int32 FootSetIndex, const FTransform& InitialWorldFoot, const FLocomotorFootSettings& InSettings);` — add a foot, returns the index of the foot or -1 if no set found
- L457 _public prototype_ `void SetHead(const FTransform& InitialWorldTransform);` — set the head transform and settings
- L460 _public prototype_ `void RunSimulation(const FLocomotorInputSettings& Settings);` — update the simulation state and generate new foot transforms
- L463 _public function_ `bool HasFeet() const` — must have at least one set of feet to progress
- L466 _public function_ `const TArray<FLocomotorFootSet>& GetFootSets() const` — read-only access to feet
- L469 _public function_ `const FTransform& GetPelvisCurrent() const` — read-only access to pelvis transform
- L472 _public function_ `const FTransform& GetBodyCurrent() const` — read-only access to body transform
- L475 _public function_ `const FTransform& GetBodyTarget() const` — read-only access to pelvis transform
- L478 _public prototype_ `float GetPhaseCurrent() const;` — get the current phase
- L481 _public function_ `const FLocomotorInputSettings& GetSettings() const` — read-only access to settings
- L484 _public prototype_ `void GetFeetCurrent(TArray<FTransform> OutTransforms) const;` — get final foot transforms
- L487 _public function_ `TArray<FLocomotorFoot*>& GetFeet()` — get access to all feet
- L488 _public function_ `const TArray<FLocomotorFoot*>& GetFeet() const`
- L492 _private prototype_ `void Simulate();`
- L493 _private prototype_ `bool Initialize();`
- L494 _private prototype_ `void UpdateWorldSpeedAndPhase();`
- L495 _private prototype_ `void UpdateFeetTargets();`
- L496 _private prototype_ `void AnimateFeet();`
- L497 _private prototype_ `void UpdateBody();`
- L498 _private prototype_ `void AnimatePelvis();`
- L499 _private prototype_ `void AnimateHead();`
- L501 _private prototype_ `void ResolveFootToFootCollision(FLocomotorFoot& Foot);`
- L502 _private prototype_ `void PushCirclesApartInFloorPlane( FVector& CenterA, FVector& CenterB, float RadiusA, float RadiusB, float InvMassA, float InvMassB);`
- L509 _private prototype_ `FVector ProjectToGroundWithSphereCast(const FLocomotorFoot& Foot, FTransform& TransformToProject);`
- L511 _private prototype_ `float EaseInOutNorm(const float Input, float EaseInAmount, float EaseOutAmount) const;`
- L512 _private prototype_ `static float WrapPhaseInRange(const float PhaseToWrap);`
- L513 _private prototype_ `static float BlendTowardsTargetPhase(const float CurrentPhase, const float TargetPhase, const float PhaseBlendRate);`
- L514 _private prototype_ `float GetPhaseOffsetForSetFromMovementStyle(int32 SetIndex);`
- L516 _private prototype_ `bool CastSphere(const FVector& Start, const FVector& End, float SphereRadius, FHitResult& OutHitResult);`
- L518 _private prototype_ `void CalcPitchRollFromNormal( const FVector& Fwd, const FVector& Up, const FVector& Normal, FVector& OutSide, FQuat& OutPitchRotation, FQuat& OutRollRotation);`
- L527 _private member_ `FLocomotorInputSettings Settings;` — the current settings (updated each frame)
- L529 _private member_ `FTransform InitialRootGoalWorld;` — the root goal in world space at the start of the simulation
- L531 _private member_ `TArray<FLocomotorFootSet> FootSets;` — current state of each foot being animated
- L533 _private member_ `TArray<FLocomotorFoot*> AllFeet;` — pointers to all feet in all sets (for convenience)
- L535 _private member_ `FLocomotorPelvis Pelvis;` — pelvis data
- L537 _private member_ `FLocomotorHead Head;` — head data
- L540 _private member_ `float CurrentGlobalPhase;` — global phase and movement speed (dynamically adjusted during simulation)
- L541 _private member_ `float CurrentPhaseSpeed;`
- L542 _private member_ `float CurrentSpeed;`
- L543 _private member_ `float CurrentPercentOfMaxSpeed;`
- L544 _private member_ `float CurrentStrideLength;`
- L545 _private member_ `bool bFullyAtRest = true;`
- L546 _private member_ `bool bAccelerating = true;`
- L547 _private member_ `float AccumulatedTimeToSimulate;`
- L550 _private member_ `bool bPostInitialized = false;` — whether the locomotor has cached it's internal state on first update

### `Plugins/Experimental/Animation/Locomotor/Source/Locomotor/Public/RigUnit_Locomotor.h` (Public)


#### struct `FLocomotorDebugSettings`  
`struct FLocomotorDebugSettings`  
_L12-63_
- reflection: `USTRUCT()`
- L16 _public function_ `FLocomotorDebugSettings() : bDrawDebug(true), bDrawBody(true), bDrawPhaseCircle(true), bDrawCurrentFeet(true), bDrawCurrentFeetFlat(true), bDrawCurrentFeetTarget(true), bDrawPrevFeetTarget(true), bDrawFinalFeetTarget(true), bDrawFeetCollision(true), Scale(25.0f), Thickness(0.5f)`
- L30 _public member_ `bool bDrawDebug;` — `UPROPERTY(meta = (Input))`
- L33 _public member_ `bool bDrawBody;` — `UPROPERTY(meta = (Input))`
- L36 _public member_ `bool bDrawPhaseCircle;` — `UPROPERTY(meta = (Input))`
- L39 _public member_ `bool bDrawCurrentFeet;` — `UPROPERTY(meta = (Input))`
- L42 _public member_ `bool bDrawCurrentFeetFlat;` — `UPROPERTY(meta = (Input))`
- L45 _public member_ `bool bDrawCurrentFeetTarget;` — `UPROPERTY(meta = (Input))`
- L48 _public member_ `bool bDrawPrevFeetTarget;` — `UPROPERTY(meta = (Input))`
- L51 _public member_ `bool bDrawFinalFeetTarget;` — `UPROPERTY(meta = (Input))`
- L54 _public member_ `bool bDrawFeetCollision;` — `UPROPERTY(meta = (Input))`
- L57 _public member_ `float Scale;` — `UPROPERTY(meta = (Input, ClampMin = "0.0", UIMin = "0.01", UIMax = "100.0"))`
- L60 _public member_ `float Thickness;` — `UPROPERTY(meta = (Input, ClampMin = "0.0", UIMin = "0.01", UIMax = "100.0"))`
- L62 _public prototype_ `void DrawDebug(FRigVMDrawInterface* DrawInterface, const FLocomotor& Locomotor, const FTransform& WorldToGlobal) const;`

#### enum `ELocomotorMovementStyle`  
`enum class ELocomotorMovementStyle : uint8`  
_L66-71_
- reflection: `UENUM()`
- L68 _public enumerator_ `Walk`
- L69 _public enumerator_ `Trot`
- L70 _public enumerator_ `Gallop`

#### struct `FMovementSettings`  
`struct FMovementSettings`  
_L74-126_
- reflection: `USTRUCT()`
- L78 _public function_ `FMovementSettings() : MinimumStepLength(10.f), SpeedMax(80.f), SpeedMin(50.f), Acceleration(100.f), Deceleration(30.f), GlobalTimeScale(1.f), bTeleport(false)`
- L89 _public member_ `float MinimumStepLength = 10.f;` — `UPROPERTY(meta = (Input))` — the length of the smallest step to take in cm
- L93 _public member_ `float SpeedMax = 80.f;` — `UPROPERTY(meta = (Input))` — the maximum movement speed in cm/s
- L97 _public member_ `float SpeedMin = 50.f;` — `UPROPERTY(meta = (Input))` — the minimum movement speed in cm/s
- L101 _public member_ `float PhaseSpeedMax = 4.f;` — `UPROPERTY(meta = (Input))` — the maximum phase speed in cycles/s
- L105 _public member_ `float PhaseSpeedMin = 1.0f;` — `UPROPERTY(meta = (Input))` — the minimum phase speed in cycles/s
- L109 _public member_ `float Acceleration = 100.f;` — `UPROPERTY(meta = (Input))` — the acceleration in cm/s/s (ie, how quickly the movement speed increases to reach the goal)
- L113 _public member_ `float Deceleration = 30.f;` — `UPROPERTY(meta = (Input))` — the acceleration in cm/s/s (ie, how quickly the movement speed decreases when approaching the goal)
- L117 _public member_ `float GlobalTimeScale = 1.f;` — `UPROPERTY(meta = (Input))` — adjust global speed of the simulation
- L121 _public member_ `bool bTeleport;` — `UPROPERTY(meta = (Input))` — reset the simulation. this can be used to teleport the locomotor.
- L125 _public member_ `TArray<ELocomotorMovementStyle> Styles;` — `UPROPERTY(meta = (Input))` — The the movement styles to cycle through based on speed

#### struct `FStepSettings`  
`struct FStepSettings`  
_L129-191_
- reflection: `USTRUCT()`
- L133 _public function_ `FStepSettings() : PercentOfStrideInAir(0.35f), AirExtensionAtMaxSpeed(0.2f), StepHeight(6.f), StepEaseIn(0.5f), StepEaseOut(0.2f), bEnableFootCollision(true), FootCollisionGlobalScale(1.0f), bEnableGroundCollision(true), MaxCollisionHeight(30.0f), TraceChannel(ETraceTypeQuery::TraceTypeQuery1), OrientFootToGroundPitch(0.8f), OrientFootToGroundRoll(0.5f)`
- L152 _public member_ `float PercentOfStrideInAir = 0.35f;` — `UPROPERTY(meta = (Input, UIMin = "0.1", UIMax=".9", ClampMin="0.1", ClampMax=".9"))` — Default is 0.35. Range is 0.1 - 0.9. The percentage amount of the 0-1 stride phase where the foot is in the air. At the default (0.35), the foot will plant on the ground 35% through it's total phase. At lower values, the foot will spend more time on the ground as a percentage of the total stride time. At higher values, each foot will spend less time on the ground as a percentage of the total stride time.
- L158 _public member_ `float AirExtensionAtMaxSpeed = 0.2f;` — `UPROPERTY(meta = (Input, UIMin = "0.1", UIMax=".9", ClampMin="0.1", ClampMax=".9"))` — Default is 0.2. Range is 0.0 - 0.9. This value is added to the "PercentOfStrideInAir" to extend the air-time while at max speed. For example, if PercentOfStrideInAir is at 0.5, and the air extension is at 0.4 the foot will be in the air for 90% of the stride cycle. This value is gradually blended on as the Speed accelerates between SpeedMin and SpeedMax. The total "Stride In Air" is clamped internally at 95%
- L162 _public member_ `float StepHeight = 6.f;` — `UPROPERTY(meta = (Input, UIMin = "0.1", UIMax="50"))` — Default is 6. Range is 0-inf. The height to raise foot (in cm) at the peak of the largest stride
- L165 _public member_ `float StepEaseIn = 0.5f;` — `UPROPERTY(meta = (Input, UIMin = "0", UIMax="1", ClampMin="0", ClampMax="1"))` — Default is 0.5. Range is 0-1. How quickly the foot accelerates when lifting off the ground. At 0, it instantly moves, at 1 it eases in.
- L168 _public member_ `float StepEaseOut = 0.2f;` — `UPROPERTY(meta = (Input, UIMin = "0", UIMax="1", ClampMin="0", ClampMax="1"))` — Default is 0.2. Range is 0-1. How quickly the foot decelerates when planting. At 0, it instantly stops on contact, at 1 it eases into contact.
- L172 _public member_ `bool bEnableFootCollision = true;` — `UPROPERTY(meta = (Input))` — Default is true. When true, feet are treated as non-overlapping circles and will not overlap each other or cross over.
- L175 _public member_ `float FootCollisionGlobalScale = 1.0f;` — `UPROPERTY(meta = (Input))` — Default is 1.0. Range is 0-inf. Global scale multiplier for all foot collision radii.
- L178 _public member_ `bool bEnableGroundCollision = true;` — `UPROPERTY(meta = (Input))` — Default is true. When true, foot height is adjusted using sphere-casting against the world.
- L181 _public member_ `float MaxCollisionHeight = 30.0f;` — `UPROPERTY(meta = (Input, UIMin = "0"))` — Default is 30. Range is 0-inf. The maximum height in cm to place foot on-top of collision geo (may move foot up or down by this amount).
- L184 _public member_ `TEnumAsByte<ETraceTypeQuery> TraceChannel = ETraceTypeQuery::TraceTypeQuery1;` — `UPROPERTY(meta = (Input))` — The 'channel' used to trace spheres into the physics world for collision detection. Determines which components to hit.
- L187 _public member_ `float OrientFootToGroundPitch = 0.8f;` — `UPROPERTY(meta = (Input, UIMin = "0", UIMax="1", ClampMin="0", ClampMax="1"))` — Default is 0.8. Range is 0-1. When Ground Collision is enabled, this will orient the pitch of the foot to match the slope of the ground.
- L190 _public member_ `float OrientFootToGroundRoll = 0.5f;` — `UPROPERTY(meta = (Input, UIMin = "0", UIMax="1", ClampMin="0", ClampMax="1"))` — Default is 0.8. Range is 0-1. When Ground Collision is enabled, this will orient the roll of the foot to match the slope of the ground.

#### struct `FPelvisSettings`  
`struct FPelvisSettings`  
_L194-249_
- reflection: `USTRUCT()`
- L198 _public function_ `FPelvisSettings() : PelvisBone(FRigElementKey(NAME_None, ERigElementType::Bone)), PositionDampingHalfLife(0.1f), RotationStiffness(40.0f), RotationDamping(0.9f), LeadAmount(2.0f), LeadDampingHalfLife(0.1f), BobOffset(-8.f), BobStiffness(40.f), BobDamping(.9f), OrientToGroundPitch(-0.3f), OrientToGroundRoll(-0.3f)`
- L213 _public member_ `FRigElementKey PelvisBone = FRigElementKey(NAME_None, ERigElementType::Bone);` — `UPROPERTY(meta = (Input))` — Usually the Pelvis or Hip bone. The bone that translates the whole body (not necessarily the root of the entire hierarchy).
- L217 _public member_ `float PositionDampingHalfLife = 0.1f;` — `UPROPERTY(meta = (Input, UIMin = "0.0", UIMax = "10.0"))` — Default is 0.1. Typical range is 0.1-1. The time (in seconds) it takes for the Pelvis to reach half way to it's goal.
- L221 _public member_ `float RotationStiffness = 40.f;` — `UPROPERTY(meta = (Input, UIMin = "0.1", UIMax = "100.0"))` — Default is 40.0. Typical range is 1-100. Higher values cause pelvis to rotate more rapidly towards goal orientation.
- L224 _public member_ `float RotationDamping = .9f;` — `UPROPERTY(meta = (Input, UIMin = "0.1", UIMax = "2.0"))` — Default is 2.0. Typical range is 0-2. Higher values cause pelvis rotation to dampen quickly.
- L228 _public member_ `float LeadAmount = 2.f;` — `UPROPERTY(meta = (Input, UIMin = "0.1", UIMax = "20.0"))` — Default is 2.0. Typical range is 1-3. Higher values cause pelvis to move further ahead of the feet.
- L231 _public member_ `float LeadDampingHalfLife = 0.1f;` — `UPROPERTY(meta = (Input, UIMin = "0.0", UIMax = "10.0"))` — Default is 0.1. Typical range is 0.1-1. The time (in seconds) it takes for the Pelvis to reach half way to it's lead goal.
- L235 _public member_ `float BobOffset = -8.f;` — `UPROPERTY(meta = (Input, UIMin = "0"))` — Default is 10.f. Range is 0-inf. The amount to lower the pelvis at the minimum height in the cycle.
- L238 _public member_ `float BobStiffness = 40.f;` — `UPROPERTY(meta = (Input, UIMin = "0.1", UIMax = "20.0"))` — Default is 40.0. Typical range is 1-100. Higher values cause pelvis to bob more rapidly towards target height.
- L241 _public member_ `float BobDamping = .9f;` — `UPROPERTY(meta = (Input, UIMin = "0.1", UIMax = "20.0"))` — Default is 0.9. Typical range is 0-2. Higher values cause pelvis bob to dampen quickly.
- L245 _public member_ `float OrientToGroundPitch = -0.3f;` — `UPROPERTY(meta = (Input, UIMin = "-1", UIMax = "1.0"))` — Default is -0.3. Typical range is -1 to 1. Pitch the pelvis up/down with ground. 0 is no effect, 1/-1 matches ground orientation. Use negative values for bipeds, positive for quadrupeds.
- L248 _public member_ `float OrientToGroundRoll = -0.3f;` — `UPROPERTY(meta = (Input, UIMin = "-1", UIMax = "1.0"))` — Default is -0.3. Typical range is -1 to 1. Roll the pelvis side-to-side with ground. 0 is no effect, 1/-1 matches ground orientation. Use negative values for bipeds, positive for quadrupeds.

#### struct `FSpineSettings`  
`struct FSpineSettings`  
_L252-277_
- reflection: `USTRUCT()`
- L256 _public function_ `FSpineSettings() : SpineBone(FRigElementKey(NAME_None, ERigElementType::Bone)), PitchAngleMax(30.0f), PitchStiffness(150.f), PitchDamping(0.9f)`
- L264 _public member_ `FRigElementKey SpineBone = FRigElementKey(NAME_None, ERigElementType::Bone);` — `UPROPERTY(meta = (Input))` — The base spine bone. Usually directly below the Pelvis bone. The bone that rotates to lean the whole spine.
- L268 _public member_ `float PitchAngleMax = 30.0f;` — `UPROPERTY(meta = (Input, UIMin = "0.1", UIMax = "180.0"))` — Default is 30. The maximum angle (in degrees) to lean the spine in the direction of travel.
- L272 _public member_ `float PitchStiffness = 150.f;` — `UPROPERTY(meta = (Input, UIMin = "0.1", UIMax = "200.0"))` — Default is 150.0. Typical range is 1-200. Higher values cause spine to lean more rapidly towards target direction.
- L276 _public member_ `float PitchDamping = 0.9f;` — `UPROPERTY(meta = (Input, UIMin = "0.1", UIMax = "20.0"))` — Default is 0.9. Typical range is 0-2. Higher values cause spine leaning to dampen quickly.

#### struct `FHeadSettings`  
`struct FHeadSettings`  
_L280-305_
- reflection: `USTRUCT()`
- L284 _public function_ `FHeadSettings() : HeadBone(FRigElementKey(NAME_None, ERigElementType::Bone)), AngleMax(30.0f), Stiffness(150.f), Damping(0.9f)`
- L292 _public member_ `FRigElementKey HeadBone = FRigElementKey(NAME_None, ERigElementType::Bone);` — `UPROPERTY(meta = (Input))` — The base spine bone. Usually directly below the Pelvis bone. The bone that rotates to lean the whole spine.
- L296 _public member_ `float AngleMax = 30.0f;` — `UPROPERTY(meta = (Input, UIMin = "0.1", UIMax = "180.0"))` — Default is 30. The maximum angle (in degrees) to rotate the head to look at the goal.
- L300 _public member_ `float Stiffness = 150.f;` — `UPROPERTY(meta = (Input, UIMin = "0.1", UIMax = "200.0"))` — Default is 150.0. Typical range is 1-200. Higher values cause spine to lean more rapidly towards target direction.
- L304 _public member_ `float Damping = 0.9f;` — `UPROPERTY(meta = (Input, UIMin = "0.1", UIMax = "20.0"))` — Default is 0.9. Typical range is 0-2. Higher values cause spine leaning to dampen quickly.

#### struct `FFootSettings`  
`struct FFootSettings`  
_L309-329_
- reflection: `USTRUCT()`
- L313 _public prototype_ `FFootSettings() = default;`
- L317 _public member_ `FRigElementKey AnkleBone;` — `UPROPERTY(meta = (Input))` — The bone at the END of the limb (typically the BALL of the foot). This is where the output goal originates.
- L320 _public member_ `float CollisionRadius = 10.f;` — `UPROPERTY(meta = (Input))`
- L324 _public member_ `FVector MaxHeelPeel = FVector(0.f, 0.f, 50.f);` — `UPROPERTY(meta = (Input))` — Default is (0, 0, 50). The max rotation to peel the heel before lift off. This is in the local space of the ankle bone.
- L328 _public member_ `FVector StaticLocalOffset = FVector::ZeroVector;` — `UPROPERTY(meta = (Input))` — applies a static offset that shifts feet in the local space of the foot bone in the reference pose

#### struct `FFootSet`  
`struct FFootSet`  
_L332-345_
- reflection: `USTRUCT()`
- L336 _public prototype_ `FFootSet() = default;`
- L340 _public member_ `TArray<FFootSettings> Feet;` — `UPROPERTY(meta = (Input))` — All the feet belonging to this set. Feet in this set alternate phases (ie Left/Right/Left/Right).
- L344 _public member_ `float PhaseOffset = 0.f;` — `UPROPERTY(meta = (Input, UIMin = "0.0", UIMax = "1.0"))` — the 0-1 phase offset for this set of feet (relative to the global phase)

#### struct `FRigUnit_Locomotor`  
`struct FRigUnit_Locomotor: public FRigUnit_HighlevelBaseMutable`  
_L351-408_
- reflection: `USTRUCT(meta=(DisplayName="Locomotor", Category="Simulation", Keywords="Walk Step Walker Walking Locomotion Procedural"))`
- inherits: `FRigUnit_HighlevelBaseMutable`
- desc: A node providing access to the locomotor functionality for foot step generation.
- L355 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L358 _public function_ `FRigUnit_Locomotor() : RootControl(NAME_None), CachedRootElement(FCachedRigElement())`
- L364 _public member_ `TArray<FTransform> FeetTransforms;` — `UPROPERTY(meta = (Output, DefaultArraySize = 2))` — list of limbs to walk on.
- L370 _public member_ `FName RootControl;` — `UPROPERTY(meta = (Input, CustomWidget = "ControlName" ))` — the target location and rotation, in world space the locomotor will generate steps to pull the character towards this location footsteps will be oriented match the root goal's final orientation
- L373 _public member_ `FCachedRigElement CachedRootElement;` — `UPROPERTY()` — Used to cache the root element
- L377 _public member_ `FMovementSettings Movement;` — `UPROPERTY(meta = (Input))` — the movement settings
- L381 _public member_ `TArray<FFootSet> FootSets;` — `UPROPERTY(meta = (Input, Constant))` — the set of feet belonging to the creature
- L385 _public member_ `FStepSettings Stepping;` — `UPROPERTY(meta = (Input))` — the global step settings
- L389 _public member_ `FPelvisSettings Pelvis;` — `UPROPERTY(meta = (Input))` — the Pelvis or Hip bone to move with the feet
- L403 _public member_ `FLocomotorDebugSettings Debug;` — `UPROPERTY(meta = (Input))` — adjust debug drawing.
- L407 _public member_ `FLocomotor Locomotor;` — `UPROPERTY(Transient)` — the locomotion simulator
