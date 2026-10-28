# Plugins / AudioMotorSimStandardComponents

- module root: `Plugins/Runtime/AudioMotorSim/Source/AudioMotorSimStandardComponents`
- headers: 9; symbols: 114
- symbol kinds: class=8, delegate=6, member=72, prototype=26, struct=2
- PublicDependencyModuleNames: AudioMotorSim, Core, CoreUObject, Engine

### `Plugins/Runtime/AudioMotorSim/Source/AudioMotorSimStandardComponents/Public/BoostMotorSimComponent.h` (Public)


#### class `UBoostMotorSimComponent`  
`class UBoostMotorSimComponent : public UAudioMotorSimComponent`  
_L10-48_
- reflection: `UCLASS(ClassGroup = "AudioMotorSim", meta = (BlueprintSpawnableComponent))`
- inherits: `UAudioMotorSimComponent`
- desc: Uses Boost input to momentarily scale throttle input and pitch output
- L17 _public member_ `float ThrottleScale = 5.f;` — `UPROPERTY(EditAnywhere, Category = "Throttle", meta = (ClampMin = "0.1"))` — Scale the engine torque by this value when boost is active
- L21 _public member_ `float InterpExp = 4.f;` — `UPROPERTY(EditAnywhere, Category = "Throttle", meta = (ClampMin = "0.1"))` — controls shape of the scaling
- L25 _public member_ `float InterpTime = 2.f;` — `UPROPERTY(EditAnywhere, Category = "Throttle", meta = (ClampMin = "0.1"))` — How fast the torque scales when starting to boost
- L29 _public member_ `bool ScaleThrottleWithBoostStrength = false;` — `UPROPERTY(EditAnywhere, Category = "Throttle", meta = (ClampMin = "0.1"))` — whether to use the boost strength to scale ThrottleScale, or just check if it is > 0 to apply the throttle scalar
- L33 _public member_ `bool bModifyPitch = true;` — `UPROPERTY(EditAnywhere, Category = "Pitch")` — whether scale the overall pitch by the boost strength
- L37 _public member_ `float PitchModifierInterpSpeed = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Pitch", meta = (EditCondition = "bModifyPitch = true"))` — Speed at which pitch approaches its target value
- L41 _public member_ `FRuntimeFloatCurve BoostToPitchCurve;` — `UPROPERTY(EditAnywhere, Category = "Pitch", meta = (EditCondition = "bModifyPitch = true"))` — Curve to derive final pitch value (in playback speed) from boost strength
- L43 _public prototype_ `virtual void Update(FAudioMotorSimInputContext& Input, FAudioMotorSimRuntimeContext& RuntimeInfo) override;`
- L44 _public prototype_ `virtual void Reset() override;`
- L47 _private member_ `float ActiveTime = 0.f;`

### `Plugins/Runtime/AudioMotorSim/Source/AudioMotorSimStandardComponents/Public/MotorPhysicsSimComponent.h` (Public)


#### class `UMotorPhysicsSimComponent`  
`class UMotorPhysicsSimComponent : public UAudioMotorSimComponent`  
_L12-105_
- reflection: `UCLASS(ClassGroup = "AudioMotorSim", meta = (BlueprintSpawnableComponent))`
- inherits: `UAudioMotorSimComponent`
- desc: Uses throttle input to run a physics simulation to drive RPM and shift gears when needed
- L19 _public member_ `float Weight = 900.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Force", meta=(ClampMin = "0.0"))` — The weight of the vehicle, used to calculate the generated RPM. Heavier weight means a slower rpm increase due to weight resistance and ground friction
- L23 _public member_ `float EngineTorque = 2500.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Force", meta=(ClampMin = "0.0"))` — The force of the engine. Large values will accelerate the vehicle more quickly, but also apply more friction when engine braking
- L27 _public member_ `float BrakingHorsePower = 6000.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Force", meta=(ClampMin = "0.0"))` — The force applied when braking. Large values will slow down the vehicle more quickly
- L31 _public member_ `TArray<float> GearRatios = {3.5f, 2.f, 1.4f, 1.f, .7f};` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gears")` — How each gear responds to speed, expressed as a ratio. Higher number means a larger RPM range within that gear and quicker progression through the gear
- L35 _public member_ `float ClutchedGearRatio = 10.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gears", meta=(ClampMin = "0.0"))` — The gear ratio to apply when clutched
- L39 _public member_ `bool bUseInfiniteGears = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gears")` — If true, the model will keep upshifting past the last defined gear. Gear ratio will be defined by the InfiniteGearRatio param
- L43 _public member_ `bool bAlwaysDownshiftToZerothGear = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gears")` — If enabled, will always downshift to 0th gear when a downshift occurs
- L47 _public member_ `float InfiniteGearRatio = 0.9f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gears", meta=(ClampMin = "0.0"))` — how much to scale gear ratio per gear past the max gear
- L51 _public member_ `float UpShiftMaxRpm = 0.97f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gears", meta=(ClampMin = "0.0", ClampMax=1.0))` — The rpm at which an upshift occurs
- L55 _public member_ `float DownShiftStartRpm = 0.94f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gears", meta=(ClampMin = "0.0", ClampMax=1.0))` — The rpm at which a downshift occurs
- L59 _public member_ `float ClutchedForceModifier = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resistance", meta=(ClampMin = "0.0"))` — Engine Torque multiplier applied when clutched
- L63 _public member_ `float ClutchedDecelScale = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resistance", meta=(ClampMin = "0.0"))` — How much more quickly the engine decelerates off-throttle while clutched
- L68 _public member_ `float EngineGearRatio = 50.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resistance", meta=(ClampMin = "0.0"))` — The main gear ratio of the engine. Corresponds to a RPM value of 1 if the vehicle is going at this speed. Speed * GearRatio / EngineGearRatio = RPM
- L72 _public member_ `float EngineFriction = 0.66f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resistance", meta=(ClampMin = "0.0"))` — How much of the torque is lost due to engine friction
- L76 _public member_ `float GroundFriction = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resistance", meta=(ClampMin = "0.0"))` — Coefficient of Rolling Resistance
- L80 _public member_ `float WindResistancePerVelocity = 0.015f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resistance", meta=(ClampMin = "0.0"))` — Multiplier to apply to the velocity value to calculate wind resistance
- L84 _public member_ `float ThrottleInterpolationTime = 0.050f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PhysicsSim", meta=(ClampMin = "0.0"))`
- L88 _public member_ `float RpmInterpSpeed = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PhysicsSim", meta=(ClampMin = "0.0"))` — Interpolation value to when changing RPM
- L91 _public member_ `FOnGearChanged OnGearChangedEvent;` — `UPROPERTY(BlueprintAssignable, Category = "PhysicsSim")`
- L93 _public prototype_ `virtual void Update(FAudioMotorSimInputContext& Input, FAudioMotorSimRuntimeContext& RuntimeInfo) override;`
- L95 _public prototype_ `virtual void ConfigMotorSim(const FInstancedStruct& InConfigData) override;`
- L98 _private prototype_ `float CalcRpm(const float InGearRatio, const float InSpeed) const;`
- L100 _private prototype_ `float CalcVelocity(const float InGearRatio, const float InRpm) const;`
- L102 _private prototype_ `float GetGearRatio(const int32 InGear, const bool bInClutched) const;`
- L104 _private prototype_ `float InterpGearRatio(const int32 InGear) const;`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGearChanged, int32, NewGear);`
- L8 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGearChanged, int32, NewGear);`

### `Plugins/Runtime/AudioMotorSim/Source/AudioMotorSimStandardComponents/Public/ResistanceMotorSimComponent.h` (Public)


#### class `UResistanceMotorSimComponent`  
`class UResistanceMotorSimComponent : public UAudioMotorSimComponent`  
_L10-28_
- reflection: `UCLASS(ClassGroup = "AudioMotorSim", meta = (BlueprintSpawnableComponent))`
- inherits: `UAudioMotorSimComponent`
- desc: Applys additional surface friction based on the angle of the vehicle's velocity
- L17 _public member_ `float UpSpeedMaxFriction = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resistance")` — How much to increase surface friction when driving straight up. Scales linearly based on driving angle.
- L21 _public member_ `float MinSpeed = 100.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resistance", meta = (ClampMin = "1.0"))` — Minimum speed to apply this extra resistance
- L25 _public member_ `FRuntimeFloatCurve SideSpeedFrictionCurve;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resistance")` — Additional friction to add based on lateral speed
- L27 _public prototype_ `virtual void Update(FAudioMotorSimInputContext& Input, FAudioMotorSimRuntimeContext& RuntimeInfo) override;`

### `Plugins/Runtime/AudioMotorSim/Source/AudioMotorSimStandardComponents/Public/RevLimiterMotorSimComponent.h` (Public)


#### class `URevLimiterMotorSimComponent`  
`class URevLimiterMotorSimComponent : public UAudioMotorSimComponent`  
_L14-84_
- reflection: `UCLASS(ClassGroup = "AudioMotorSim", meta = (BlueprintSpawnableComponent))`
- inherits: `UAudioMotorSimComponent`
- desc: Temporarily cuts throttle and reduces RPM when drifting or in the air
- L20 _public member_ `float LimitTime = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RevLimiter", Meta=(ClampMin="0.0", ClampMax="5.0"))` — How long will the throttle be cut for when the limiter kicks in
- L23 _public member_ `float DecelScale = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RevLimiter", Meta=(EditCondition=false, EditConditionHides, DeprecatedProperty, DeprecationMessage="DecelScale is deprecated."))`
- L27 _public member_ `float AirMaxThrottleTime = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RevLimiter", Meta=(ClampMin="0.0", ClampMax="10.0"))` — How long should the rev limiter be enabled for while in air
- L31 _public member_ `float SideSpeedThreshold = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RevLimiter")` — The side speed needed to trigger the rev limiter
- L35 _public member_ `float LimiterMaxRpm = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RevLimiter", Meta=(ClampMin="0.0", ClampMax="1.0"))` — Ceiling RPM for the Rev Limiter
- L39 _public member_ `bool bShiftBackToZero = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RevLimiter")` — If the car should shift back to 0 when the rev limiter is engaged
- L43 _public member_ `bool bRevLimitOnClutchEngaged = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RevLimiter|Clutch")` — If enabled, rev limiter behavior will be triggered by having the clutch engaged
- L47 _public member_ `float ClutchedRecoverRPM = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RevLimiter|Clutch", Meta=(ClampMin="0.0", ClampMax="1.0", EditCondition="bRevLimitOnClutchEngaged"))` — When rev limiting on clutch, the RPM at which the throttle will be re-enabled
- L51 _public member_ `bool bRevLimitOnReverse = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RevLimiter|Reverse")` — If enabled, rev limiter behavior will be triggered when in reverse
- L55 _public member_ `float ReverseMaxRPM = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RevLimiter|Reverse", Meta=(ClampMin="0.0", ClampMax="1.0", EditCondition="bRevLimitOnReverse", EditConditionHides))` — The max RPM allowed when reversing
- L59 _public member_ `float ReverseRecoverRPM = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RevLimiter|Reverse", Meta=(ClampMin="0.0", ClampMax="1.0", EditCondition="bRevLimitOnReverse && !bHoldRPMInReverse", EditConditionHides))` — When rev limiting on reverse, the RPM at which the throttle will be re-enabled
- L63 _public member_ `bool bHoldRPMInReverse = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RevLimiter|Reverse", Meta=(EditCondition="bRevLimitOnReverse", EditConditionHides))` — Bypasses the limiter in reverse and holds the RPM at ReverseMaxRPM
- L66 _public member_ `FOnRevLimiterHit OnRevLimiterHit;` — `UPROPERTY(BlueprintAssignable)`
- L69 _public member_ `FOnRevLimiterStateChanged OnRevLimiterStateChanged;` — `UPROPERTY(BlueprintAssignable)`
- L72 _private prototype_ `void RevLimitToTarget(FAudioMotorSimInputContext& Input, FAudioMotorSimRuntimeContext& RuntimeInfo, const float LimitRPM, const float TargetRPM);`
- L73 _private prototype_ `void EngageClutchAndShiftBackToZero(FAudioMotorSimInputContext& Input, FAudioMotorSimRuntimeContext& RuntimeInfo) const;`
- L76 _private member_ `float TimeRemaining = 0.f;` — Time remaining where the limiter is forcing throttle down
- L77 _private member_ `float TimeInAir = 0.f;`
- L79 _private member_ `bool bActive = false;`
- L82 _public prototype_ `virtual void Update(FAudioMotorSimInputContext& Input, FAudioMotorSimRuntimeContext& RuntimeInfo) override;`
- L83 _public prototype_ `virtual void Reset() override;`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRevLimiterHit);`
- L8 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRevLimiterHit);`
- L10 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRevLimiterStateChanged, bool, bNewState);`
- L10 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRevLimiterStateChanged, bool, bNewState);`

### `Plugins/Runtime/AudioMotorSim/Source/AudioMotorSimStandardComponents/Public/ReverseMotorSimComponent.h` (Public)


#### class `UReverseMotorSimComponent`  
`class UReverseMotorSimComponent : public UAudioMotorSimComponent`  
_L9-19_
- reflection: `UCLASS(ClassGroup = "AudioMotorSim", meta = (BlueprintSpawnableComponent))`
- inherits: `UAudioMotorSimComponent`
- desc: Scales engine friction when reversing
- L16 _public member_ `float ReverseEngineResistanceModifier = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reverse", Meta=(ClampMin="0.0"))` — How much to scale engine friction by when reversing
- L18 _public prototype_ `virtual void Update(FAudioMotorSimInputContext& Input, FAudioMotorSimRuntimeContext& RuntimeInfo) override;`

### `Plugins/Runtime/AudioMotorSim/Source/AudioMotorSimStandardComponents/Public/RpmCurveMotorSimComponent.h` (Public)


#### struct `FMotorSimGearCurve`  
`struct FMotorSimGearCurve`  
_L9-20_
- reflection: `USTRUCT(BlueprintType)`
- L15 _public member_ `FRuntimeFloatCurve RpmCurve;` — `UPROPERTY(EditAnywhere, Category = "Gears")` — normalized curve, 0-1, of the output RPM from the last gear's top speed to this one's
- L19 _public member_ `float SpeedTopThreshold = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Gears")` — Speed at which the next gear starts

#### class `URpmCurveMotorSimComponent`  
`class URpmCurveMotorSimComponent : public UAudioMotorSimComponent`  
_L26-47_
- reflection: `UCLASS(ClassGroup = "AudioMotorSim", meta = (BlueprintSpawnableComponent))`
- inherits: `UAudioMotorSimComponent`
- desc: Derives Gear and RPM directly from speed using hand drawn curves and gear thresholds
- L31 _public prototype_ `virtual void Update(FAudioMotorSimInputContext& Input, FAudioMotorSimRuntimeContext& RuntimeInfo) override;`
- L34 _public member_ `TArray<FMotorSimGearCurve> Gears;` — `UPROPERTY(EditAnywhere, Category = "Gears")`
- L37 _public member_ `float InterpSpeed = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gears", Meta=(ClampMin="0.0"))`
- L40 _public member_ `FOnGearChangedEvent OnUpShift;` — `UPROPERTY(BlueprintAssignable)`
- L43 _public member_ `FOnGearChangedEvent OnDownShift;` — `UPROPERTY(BlueprintAssignable)`
- L46 _private prototype_ `int32 GetDesiredGearForSpeed(const float Speed) const;`

#### Free symbols / members of external scopes

- L22 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGearChangedEvent, int32, NewGear);`
- L22 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGearChangedEvent, int32, NewGear);`

### `Plugins/Runtime/AudioMotorSim/Source/AudioMotorSimStandardComponents/Public/StandardAudioMotorSimConfigDataTypes.h` (Public)


#### struct `FMotorPhysicsSimConfigData`  
`struct FMotorPhysicsSimConfigData : public FAudioMotorSimConfigData`  
_L11-26_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FAudioMotorSimConfigData`
- L17 _public member_ `float Weight = 900.f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Force")` — The weight of the vehicle, used to calculate the generated RPM. Heavier weight means a slower rpm increase due to weight resistance and ground friction
- L21 _public member_ `float EngineTorque = 2500.f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Force")` — The force of the engine. Large values will accelerate the vehicle more quickly, but also apply more friction when engine braking
- L25 _public member_ `float BrakingHorsePower = 6000.f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Force")` — The force applied when braking. Large values will slow down the vehicle more quickly

### `Plugins/Runtime/AudioMotorSim/Source/AudioMotorSimStandardComponents/Public/ThrottleStateMotorSimComponent.h` (Public)


#### class `UThrottleStateMotorSimComponent`  
`class UThrottleStateMotorSimComponent : public UAudioMotorSimComponent`  
_L12-38_
- reflection: `UCLASS(ClassGroup = "AudioMotorSim", meta = (BlueprintSpawnableComponent))`
- inherits: `UAudioMotorSimComponent`
- desc: Provides events for when the throttle changes state
- L18 _public member_ `FOnThrottleChanged OnThrottleEngaged;` — `UPROPERTY(BlueprintAssignable, Category = "ThrottleState")`
- L21 _public member_ `FOnThrottleChanged OnThrottleReleased;` — `UPROPERTY(BlueprintAssignable, Category = "ThrottleState")`
- L25 _public member_ `FOnEngineBlowoff OnEngineBlowoff;` — `UPROPERTY(BlueprintAssignable, Category = "ThrottleState")` — Fires when the throttle is released, keeping track of how long the throttle was held for
- L28 _public member_ `float BlowoffMinThrottleTime = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThrottleState", Meta=(ClampMin="0.0"))`
- L30 _public prototype_ `virtual void Update(FAudioMotorSimInputContext& Input, FAudioMotorSimRuntimeContext& RuntimeInfo) override;`
- L31 _public prototype_ `virtual void Reset() override;`
- L34 _private member_ `float FullThrottleTime = 0.f;`
- L36 _private member_ `bool bPrevCarAccelerating = false;`
- L37 _private member_ `bool bPrevCarIdling = true;`

#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEngineBlowoff, float, BlowoffStrength);`
- L7 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEngineBlowoff, float, BlowoffStrength);`
- L8 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnThrottleChanged);`
- L8 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnThrottleChanged);`

### `Plugins/Runtime/AudioMotorSim/Source/AudioMotorSimStandardComponents/Public/VelocitySyncMotorSimComponent.h` (Public)


#### class `UVelocitySyncMotorSimComponent`  
`class UVelocitySyncMotorSimComponent : public UAudioMotorSimComponent`  
_L10-40_
- reflection: `UCLASS(ClassGroup = "AudioMotorSim", meta = (BlueprintSpawnableComponent))`
- inherits: `UAudioMotorSimComponent`
- desc: Sets Rpm directly from speed using a curve, if under a speed threshold or if the throttle is released for a period of time
- L16 _public member_ `float NoThrottleTime = 0.1f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VelocitySync", Meta=(ClampMin="0.0"))`
- L20 _public member_ `float SpeedThreshold = 200.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VelocitySync", Meta=(ClampMin="0.0"))` — Speed below which gears will be ignored, and RPM will sync directly to velocity
- L23 _public member_ `FRuntimeFloatCurve SpeedToRpmCurve;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VelocitySync")`
- L26 _public member_ `float InterpSpeed = 3.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VelocitySync", Meta=(ClampMin="0.0"))`
- L29 _public member_ `float InterpTime = 0.1f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VelocitySync", Meta=(ClampMin="0.0"))`
- L32 _public member_ `float FirstGearThrottleThreshold = 0.5f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VelocitySync", Meta=(ClampMin="0.0"))`
- L34 _public prototype_ `virtual void Update(FAudioMotorSimInputContext& Input, FAudioMotorSimRuntimeContext& RuntimeInfo) override;`
- L35 _public prototype_ `virtual void Reset() override;`
- L38 _private member_ `float NoThrottleTimeElapsed = 0.f;`
- L39 _private member_ `float InterpTimeLeft = 0.f;`
