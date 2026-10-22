# Runtime / ChaosVehiclesCore

- module root: `Source/Runtime/Experimental/ChaosVehicles/ChaosVehiclesCore`
- headers: 35; symbols: 1668
- symbol kinds: class=61, delegate=4, enum=23, enumerator=77, function=555, macro=23, member=547, namespace=30, prototype=253, struct=66, typedef=13, variable=16
- PublicDependencyModuleNames: Chaos, Core, CoreUObject

### `Source/Runtime/Experimental/ChaosVehicles/ChaosVehiclesCore/Public/AerodynamicsSystem.h` (Public)


#### struct `Chaos::FSimpleAerodynamicsConfig`  
`struct FSimpleAerodynamicsConfig`  
_L22-37_
- L24 _public function_ `FSimpleAerodynamicsConfig() : AreaMetresSquared(2.0f) , DragCoefficient(0.1f) , DownforceCoefficient(0.1f)`
- L33 _public member_ `float AreaMetresSquared;` — FVector Offet;				// local offset relative to CM
- L34 _public member_ `float DragCoefficient;` — always positive
- L35 _public member_ `float DownforceCoefficient;` — positive for downforce, negative lift

#### class `Chaos::FSimpleAerodynamicsSim`  
`class FSimpleAerodynamicsSim : public TVehicleSystem<FSimpleAerodynamicsConfig>`  
_L40-85_
- inherits: `TVehicleSystem<FSimpleAerodynamicsConfig>`
- L43 _public prototype_ `FSimpleAerodynamicsSim(const FSimpleAerodynamicsConfig* SetupIn);`
- L46 _public function_ `void SetDensityOfMedium(float DensityIn)` — set the density of the medium through which you are traveling Air/Water, etc
- L51 _public function_ `void SetDragCoefficient(float InCoeffient)`
- L57 _public function_ `void SetDownforceCoefficient(float InCoeffient)`
- L64 _public function_ `float GetDragForceFromVelocity(float VelocityIn)` — get the drag force generated at the given velocity
- L70 _public function_ `float GetLiftForceFromVelocity(float VelocityIn)` — get the lift/down-force generated at the given velocity
- L76 _public prototype_ `FVector GetCombinedForces(float VelocityIn);` — Get the drag and down forces combined in a 3D vector, drag on X-axis, down-force on Z-axis
- L79 _protected member_ `float DownforceCoefficient;`
- L80 _protected member_ `float DragCoefficient;`
- L81 _protected member_ `float DensityOfMedium;`
- L82 _protected member_ `float EffectiveDragConstant;`
- L83 _protected member_ `float EffectiveLiftConstant;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace Chaos`

### `Source/Runtime/Experimental/ChaosVehicles/ChaosVehiclesCore/Public/AerofoilSystem.h` (Public)


#### enum `Chaos::EAerofoilType`  
`enum class EAerofoilType : uint8`  
_L17-23_
- L19 _public enumerator_ `Fixed = 0`
- L20 _public enumerator_ `Wing`
- L21 _public enumerator_ `Rudder`
- L22 _public enumerator_ `Elevator`

#### struct `Chaos::FAerofoilConfig`  
`struct FAerofoilConfig`  
_L25-56_
- L27 _public function_ `FAerofoilConfig() : Offset(FVector(0.f, 0.f, 0.0f)) , UpAxis(FVector(0.f, 0.f, 1.f)) , Area(5.0f) , Camber(3.0f) , MaxControlAngle(1.f) , StallAngle(16.0f) , MaxCeiling(1E30f) , MinCeiling(-1E30f) , Type(EAerofoilType::Fixed) , LiftMultiplier(1.0f) , DragMultiplier(1.0f)`
- L43 _public member_ `FVector Offset;`
- L44 _public member_ `FVector UpAxis;`
- L45 _public member_ `float Area;`
- L46 _public member_ `float Camber;`
- L47 _public member_ `float MaxControlAngle;`
- L48 _public member_ `float StallAngle;`
- L50 _public member_ `float MaxCeiling;`
- L51 _public member_ `float MinCeiling;`
- L53 _public member_ `EAerofoilType Type;`
- L54 _public member_ `float LiftMultiplier;`
- L55 _public member_ `float DragMultiplier;`

#### class `Chaos::FAerofoil`  
`class FAerofoil : public TVehicleSystem<FAerofoilConfig>`  
_L58-127_
- inherits: `TVehicleSystem<FAerofoilConfig>`
- L61 _public function_ `FAerofoil()`
- L64 _public prototype_ `FAerofoil(const FAerofoilConfig* SetupIn);`
- L67 _public function_ `void SetAerofoilId(int Id)` — Set a debug Id so we can identify an individual aerofoil
- L72 _public function_ `void SetControlSurface(float CtrlSurfaceInput)`
- L77 _public function_ `void SetDensityOfMedium(float InDensity)`
- L82 _public function_ `FVector GetAxis()`
- L87 _public function_ `FVector GetOffset()`
- L92 _public prototype_ `FVector GetCenterOfLiftOffset();`
- L96 _public prototype_ `FVector GetForce(FTransform& BodyTransform, const FVector& v, float Altitude, float DeltaTime);` — returns the combined force of lift and drag at an aerofoil in world coordinates for direct application to the aircrafts rigid body.
- L104 _public prototype_ `float CalcDynamicPressure(float VelocitySqr, float InAltitude);` — Dynamic air pressure = 0.5 * AirDensity * Vsqr This function reduces the dynamic pressure in a linear fashion with altitude between MinCeiling & MaxCeiling in order to limit the aircrafts altitude with a 'natural feel' without having a hard limit
- L107 _public prototype_ `float CalcCentreOfLift();` — Center of lift moves fore/aft based on current AngleOfAttack
- L110 _public prototype_ `float CalcDragCoefficient(float InAngleOfAttack, float InControlSurfaceAngle);` — Returns drag coefficient for the current angle of attack of the aerofoil surface
- L116 _public prototype_ `float CalcLiftCoefficient(float InAngleOfAttack, float InControlSurfaceAngle);` — Returns lift coefficient for the current angle of attack of the aerofoil surface Cheating by making control surface part of entire aerofoil movement
- L119 _public prototype_ `float CalcAngleOfAttackDegrees(const FVector& UpAxis, const FVector& InAirflowVector);` — Angle of attack is the angle between the aerofoil and the airflow vector
- L122 _private member_ `float CurrentAirDensity;`
- L123 _private member_ `float AngleOfAttack;`
- L124 _private member_ `float ControlSurfaceAngle;`
- L125 _private member_ `FVector AirflowNormal;`
- L126 _private member_ `int AerofoilId;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace Chaos`

### `Source/Runtime/Experimental/ChaosVehicles/ChaosVehiclesCore/Public/ArcadeSystem.h` (Public)


#### struct `Chaos::FTorqueControlConfig`  
`struct FTorqueControlConfig`  
_L15-49_
- L18 _public member_ `bool Enabled;` — Torque Control Enabled
- L21 _public member_ `float YawTorqueScaling;` — Yaw Torque Scaling
- L23 _public member_ `float YawFromSteering;`
- L25 _public member_ `float YawFromRollTorqueScaling;`
- L28 _public member_ `float PitchTorqueScaling;` — Pitch Torque Scaling
- L31 _public member_ `float RollTorqueScaling;` — Roll Torque Scaling
- L33 _public member_ `float RollFromSteering;`
- L36 _public member_ `float RotationDamping;` — Rotation damping
- L38 _public function_ `void InitDefaults()`

#### struct `Chaos::FTargetRotationControlConfig`  
`struct FTargetRotationControlConfig`  
_L51-101_
- L54 _public member_ `bool Enabled;` — Rotation Control Enabled
- L56 _public member_ `bool bRollVsSpeedEnabled;`
- L58 _public member_ `float RollControlScaling;`
- L60 _public member_ `float RollMaxAngle;`
- L62 _public member_ `float PitchControlScaling;`
- L64 _public member_ `float PitchMaxAngle;`
- L67 _public member_ `float RotationStiffness;` — Rotation stiffness
- L70 _public member_ `float RotationDamping;` — Rotation damping
- L73 _public member_ `float MaxAccel;` — Rotation mac accel
- L75 _public member_ `float AutoCentreRollStrength;`
- L77 _public member_ `float AutoCentrePitchStrength;`
- L79 _public member_ `float AutoCentreYawStrength;`
- L82 _public function_ `void InitDefaults()`

#### struct `Chaos::FStabilizeControlConfig`  
`struct FStabilizeControlConfig`  
_L103-120_
- L107 _public member_ `bool Enabled;` — Torque Control Enabled
- L110 _public member_ `float AltitudeHoldZ;` — Yaw Torque Scaling
- L112 _public member_ `float PositionHoldXY;`
- L114 _public function_ `void InitDefaults()`

#### struct `Chaos::FArcadeControlConfig`  
`struct FArcadeControlConfig`  
_L122-131_
- L124 _public member_ `FTorqueControlConfig TorqueControl;`
- L127 _public member_ `FTargetRotationControlConfig TargetRotationControl;` — Arcade style direct control of vehicle rotation via torque force
- L130 _public member_ `FStabilizeControlConfig StabilizeControl;` — Arcade style control of vehicle

#### class `Chaos::FTorqueControlSim`  
`class FTorqueControlSim : public TVehicleSystem<FTorqueControlConfig>`  
_L134-142_
- inherits: `TVehicleSystem<FTorqueControlConfig>`
- L137 _public function_ `FTorqueControlSim()`
- L140 _public prototype_ `FTorqueControlSim(const FTorqueControlConfig* SetupIn);`

#### class `Chaos::FTargetRotationControlSim`  
`class FTargetRotationControlSim : public TVehicleSystem<FTargetRotationControlConfig>`  
_L145-153_
- inherits: `TVehicleSystem<FTargetRotationControlConfig>`
- L148 _public function_ `FTargetRotationControlSim()`
- L151 _public prototype_ `FTargetRotationControlSim(const FTargetRotationControlConfig* SetupIn);`

#### class `Chaos::FStabilizeControlSim`  
`class FStabilizeControlSim : public TVehicleSystem<FStabilizeControlConfig>`  
_L156-163_
- inherits: `TVehicleSystem<FStabilizeControlConfig>`
- L159 _public function_ `FStabilizeControlSim()`
- L162 _public prototype_ `FStabilizeControlSim(const FStabilizeControlConfig* SetupIn);`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace Chaos`

### `Source/Runtime/Experimental/ChaosVehicles/ChaosVehiclesCore/Public/ChaosVehiclesCoreModule.h` (Public)


#### class `FChaosVehiclesCoreModule`  
`class FChaosVehiclesCoreModule : public IModuleInterface`  
_L7-13_
- inherits: `IModuleInterface`
- L11 _public function_ `virtual void StartupModule() override`
- L12 _public function_ `virtual void ShutdownModule() override`

### `Source/Runtime/Experimental/ChaosVehicles/ChaosVehiclesCore/Public/EngineSystem.h` (Public)


#### struct `Chaos::FSimpleEngineConfig`  
`struct FSimpleEngineConfig`  
_L26-50_
- L28 _public function_ `FSimpleEngineConfig() : MaxTorque(0.f) , MaxRPM(6000) , EngineIdleRPM(1200) , EngineBrakeEffect(0.2f) , EngineRevUpMOI(1.0f) , EngineRevDownRate(1.0f)`
- L41 _public member_ `FNormalisedGraph TorqueCurve;` — #todo: want something like UCurveFloat / FRuntimeFloatCurve / FTorqueCurveEditor
- L42 _public member_ `float MaxTorque;` — [N.m] The peak torque Y value in the normalized torque graph
- L43 _public member_ `uint16 MaxRPM;` — [RPM] The absolute maximum RPM the engine can theoretically reach (last X value in the normalized torque graph)
- L44 _public member_ `uint16 EngineIdleRPM;` — [RPM] The RPM at which the throttle sits when the car is not moving
- L45 _public member_ `float EngineBrakeEffect;` — [0..1] How much the engine slows the vehicle when the throttle is released
- L47 _public member_ `float EngineRevUpMOI;` — Affects speed at which engine RPM increases
- L48 _public member_ `float EngineRevDownRate;` — Affects speed at which engine RPM decreases

#### class `Chaos::FSimpleEngineSim`  
`class FSimpleEngineSim : public TVehicleSystem<FSimpleEngineConfig>`  
_L52-166_
- inherits: `TVehicleSystem<FSimpleEngineConfig>`
- L56 _public prototype_ `FSimpleEngineSim(const FSimpleEngineConfig* StaticDataIn);`
- L59 _public function_ `void StartEngine()` — Start the engine
- L67 _public function_ `void StopEngine()` — Stop the engine
- L75 _public function_ `void SetThrottle(float InThrottle)` — Pass in the throttle position to the engine
- L85 _public function_ `void SetEngineRPM(bool FreeRunningIn, float InEngineRPM)` — When the wheels are in contact with the ground and clutch engaged then the load on the engine from the wheels determines the engine speed. With no clutch simulation just setting the engine RPM directly to match the wheel speed.
- L94 _public function_ `void SetMaxTorque(float InTorque)`
- L99 _public function_ `float GetEngineTorque()`
- L109 _public function_ `float GetEngineRevRate()`
- L114 _public function_ `float GetTorqueFromRPM(bool LimitToIdle = true)`
- L120 _public prototype_ `float GetTorqueFromRPM(float RPM, bool LimitToIdle = true);` — get torque value from torque curve based on input RPM
- L124 _public function_ `float GetEngineRPM() const` — get the Engine speed in Revolutions Per Minute
- L135 _public function_ `float GetEngineOmega() const` — get the Engine angular velocity
- L141 _public function_ `void SetEngineOmega( const float EngineOmega)` — Set the Engine angular velocity
- L149 _public prototype_ `void Simulate(float DeltaTime);` — Simulate - NOP at the moment
- L152 _protected member_ `float MaxTorque;` — [N.m] The peak torque Y value in the normalized torque graph
- L153 _protected member_ `float ThrottlePosition;` — [0..1 Normalized position]
- L154 _protected member_ `float TargetSpeed;` — target RPM
- L155 _protected member_ `float CurrentRPM;` — current RPM
- L156 _protected member_ `float DriveTorque;` — current torque [N.m]
- L158 _protected member_ `float EngineIdleSpeed;`
- L159 _protected member_ `float MaxEngineSpeed;`
- L160 _protected member_ `bool EngineStarted;` — is the engine turned off or has it been started
- L161 _protected member_ `bool FreeRunning;` — is engine in neutral with no load from the wheels/transmission
- L163 _protected member_ `float Omega;` — engine speed
- L164 _protected member_ `float RevRate;` — for debug rather than any practical purpose

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace Chaos`

### `Source/Runtime/Experimental/ChaosVehicles/ChaosVehiclesCore/Public/SimModule/AerofoilModule.h` (Public)


#### enum `Chaos::EAerofoil`  
`enum class EAerofoil : uint8`  
_L15-21_
- L17 _public enumerator_ `Fixed = 0`
- L18 _public enumerator_ `Wing`
- L19 _public enumerator_ `Rudder`
- L20 _public enumerator_ `Elevator`

#### struct `Chaos::FAerofoilOutputData`  
`struct FAerofoilOutputData : public FSimOutputData , public Chaos::TSimulationModuleTypeable<class FAerofoilSimModule, FAerofoilOutputData>`  
_L23-36_
- inherits: `FSimOutputData,Chaos::TSimulationModuleTypeable<classFAerofoilSimModule,FAerofoilOutputData>`
- L27 _public function_ `virtual FSimOutputData* MakeNewData() override`
- L28 _public function_ `static FSimOutputData* MakeNew()`
- L30 _public prototype_ `virtual void FillOutputState(const ISimulationModuleBase* SimModule) override;`
- L31 _public prototype_ `virtual void Lerp(const FSimOutputData& InCurrent, const FSimOutputData& InNext, float Alpha) override;`
- L34 _public prototype_ `virtual FString ToString() override;`

#### struct `Chaos::FAerofoilSettings`  
`struct FAerofoilSettings`  
_L38-68_
- L40 _public function_ `FAerofoilSettings() : Offset(FVector::ZeroVector) , ForceAxis(FVector(0.f, 0.f, 1.f)) , ControlRotationAxis(FVector(0.f, 1.f, 0.f)) , Area(5.0f) , Camber(3.0f) , MaxControlAngle(1.f) , StallAngle(16.0f) , Type(EAerofoil::Fixed) , LiftMultiplier(1.0f) , DragMultiplier(1.0f) , AnimationMagnitudeMultiplier(1.0f)`
- L55 _public member_ `FVector Offset;`
- L56 _public member_ `FVector ForceAxis;`
- L57 _public member_ `FVector ControlRotationAxis;`
- L58 _public member_ `float Area;`
- L59 _public member_ `float Camber;`
- L60 _public member_ `float MaxControlAngle;`
- L61 _public member_ `float StallAngle;`
- L63 _public member_ `EAerofoil Type;`
- L64 _public member_ `float LiftMultiplier;`
- L65 _public member_ `float DragMultiplier;`
- L66 _public member_ `float AnimationMagnitudeMultiplier;`

#### class `Chaos::FAerofoilSimModule`  
`class FAerofoilSimModule : public ISimulationModuleBase, public TSimModuleSettings<FAerofoilSettings>, public TSimulationModuleTypeable<FAerofoilSimModule>`  
_L70-137_
- inherits: `ISimulationModuleBase,TSimModuleSettings<FAerofoilSettings>,TSimulationModuleTypeable<FAerofoilSimModule>`
- L75 _public prototype_ `DEFINE_CHAOSSIMTYPENAME(FAerofoilSimModule);`
- L76 _public prototype_ `FAerofoilSimModule(const FAerofoilSettings& Settings);`
- L78 _public prototype_ `virtual ~FAerofoilSimModule() = default;`
- L80 _public function_ `virtual TSharedPtr<FModuleNetData> GenerateNetData(const int32 NodeArrayIndex) const override`
- L82 _public function_ `virtual FSimOutputData* GenerateOutputData() const override`
- L87 _public function_ `virtual const FString GetDebugName() const`
- L89 _public function_ `virtual bool IsBehaviourType(eSimModuleTypeFlags InType) const override`
- L91 _public prototype_ `virtual void Simulate(float DeltaTime, const FAllInputs& Inputs, FSimModuleTree& VehicleModuleSystem) override;`
- L93 _public prototype_ `virtual void Animate() override;`
- L95 _public function_ `void SetDensityOfMedium(float InDensity)`
- L100 _public function_ `void SetControlSurface(float CtrlSurfaceInput)`
- L105 _public prototype_ `FVector GetCenterOfLiftOffset();`
- L109 _public prototype_ `FVector GetForce(const FVector& v, float Altitude, float DeltaTime);` — returns the combined force of lift and drag at an aerofoil in local coordinates for direct application to the aircrafts rigid body.
- L114 _public prototype_ `float CalcDynamicPressure(float VelocitySqr, float InAltitude);` — Dynamic air pressure = 0.5 * AirDensity * Vsqr
- L117 _public prototype_ `float CalcCentreOfLift();` — Center of lift moves fore/aft based on current AngleOfAttack
- L120 _public prototype_ `float CalcDragCoefficient(float InAngleOfAttack, float InControlSurfaceAngle);` — Returns drag coefficient for the current angle of attack of the aerofoil surface
- L126 _public prototype_ `float CalcLiftCoefficient(float InAngleOfAttack, float InControlSurfaceAngle);` — Returns lift coefficient for the current angle of attack of the aerofoil surface Cheating by making control surface part of entire aerofoil movement
- L129 _public prototype_ `float CalcAngleOfAttackDegrees(const FVector& UpAxis, const FVector& InAirflowVector);` — Angle of attack is the angle between the aerofoil and the airflow vector
- L131 _public member_ `float CurrentAirDensity;`
- L132 _public member_ `float AngleOfAttack;`
- L133 _public member_ `float ControlSurfaceAngle;`
- L134 _public member_ `FVector AirflowNormal;`
- L135 _public member_ `int AerofoilId;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API CHAOSVEHICLESCORE_API`
- L10 _namespace_ `namespace Chaos`

### `Source/Runtime/Experimental/ChaosVehicles/ChaosVehiclesCore/Public/SimModule/AxleModule.h` (Public)


#### struct `Chaos::FAxleSettings`  
`struct FAxleSettings`  
_L18-27_
- desc: <summary> Axle settings </summary>
- L20 _public function_ `FAxleSettings() : AxleInertia(1.f)`
- L26 _public member_ `float AxleInertia;`

#### class `Chaos::FAxleSimModule`  
`class FAxleSimModule : public FTorqueSimModule, public TSimModuleSettings<FAxleSettings>, public TSimulationModuleTypeable<FAxleSimModule>`  
_L33-44_
- inherits: `FTorqueSimModule,TSimModuleSettings<FAxleSettings>,TSimulationModuleTypeable<FAxleSimModule>`
- desc: </summary>
- L36 _public prototype_ `DEFINE_CHAOSSIMTYPENAME(FAxleSimModule);`
- L37 _public prototype_ `FAxleSimModule(const FAxleSettings& Settings);`
- L39 _public function_ `virtual const FString GetDebugName() const`
- L41 _public prototype_ `virtual void Simulate(float DeltaTime, const FAllInputs& Inputs, FSimModuleTree& VehicleModuleSystem) override;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API CHAOSVEHICLESCORE_API`
- L10 _namespace_ `namespace Chaos`

### `Source/Runtime/Experimental/ChaosVehicles/ChaosVehiclesCore/Public/SimModule/ChassisModule.h` (Public)


#### struct `Chaos::FChassisSettings`  
`struct FChassisSettings`  
_L19-36_
- desc: <summary> Chassis settings </summary>
- L21 _public function_ `FChassisSettings() : AreaMetresSquared(2.0f) , DragCoefficient(0.5f) , DensityOfMedium(RealWorldConsts::AirDensity()) , XAxisMultiplier(1.0f) , YAxisMultiplier(1.0f) , AngularDamping(100000.0f)`
- L30 _public member_ `float AreaMetresSquared;` — [meters squared]
- L31 _public member_ `float DragCoefficient;` — always positive
- L32 _public member_ `float DensityOfMedium;`
- L33 _public member_ `float XAxisMultiplier;`
- L34 _public member_ `float YAxisMultiplier;`
- L35 _public member_ `float AngularDamping;`

#### class `Chaos::FChassisSimModule`  
`class FChassisSimModule : public ISimulationModuleBase, public TSimModuleSettings<FChassisSettings>, public TSimulationModuleTypeable<FChassisSimModule>`  
_L42-57_
- inherits: `ISimulationModuleBase,TSimModuleSettings<FChassisSettings>,TSimulationModuleTypeable<FChassisSimModule>`
- desc: </summary>
- L45 _public prototype_ `DEFINE_CHAOSSIMTYPENAME(FChassisSimModule);`
- L46 _public prototype_ `FChassisSimModule(const FChassisSettings& Settings);`
- L48 _public function_ `virtual TSharedPtr<FModuleNetData> GenerateNetData(const int32 NodeArrayIndex) const override`
- L50 _public function_ `virtual const FString GetDebugName() const`
- L52 _public function_ `virtual bool IsBehaviourType(eSimModuleTypeFlags InType) const override`
- L54 _public prototype_ `virtual void Simulate(float DeltaTime, const FAllInputs& Inputs, FSimModuleTree& VehicleModuleSystem) override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API CHAOSVEHICLESCORE_API`
- L11 _namespace_ `namespace Chaos`

### `Source/Runtime/Experimental/ChaosVehicles/ChaosVehiclesCore/Public/SimModule/ClutchModule.h` (Public)


#### struct `Chaos::FClutchSettings`  
`struct FClutchSettings`  
_L15-24_
- L17 _public function_ `FClutchSettings() : ClutchStrength(1.f)`
- L23 _public member_ `float ClutchStrength;`

#### struct `Chaos::FClutchSimModuleData`  
`struct FClutchSimModuleData : public FTorqueSimModuleData, public TSimulationModuleTypeable<class FClutchSimModule, FClutchSimModuleData>`  
_L27-47_
- inherits: `FTorqueSimModuleData,TSimulationModuleTypeable<classFClutchSimModule,FClutchSimModuleData>`
- L30 _public function_ `FClutchSimModuleData(int NodeArrayIndex, const FString& InDebugString) : FTorqueSimModuleData(NodeArrayIndex, InDebugString)`
- L35 _public function_ `virtual void FillSimState(ISimulationModuleBase* SimModule) override`
- L41 _public function_ `virtual void FillNetState(const ISimulationModuleBase* SimModule) override`

#### class `Chaos::FClutchSimModule`  
`class FClutchSimModule : public FTorqueSimModule, public TSimModuleSettings<FClutchSettings>, public TSimulationModuleTypeable<FClutchSimModule>`  
_L59-84_
- inherits: `FTorqueSimModule,TSimModuleSettings<FClutchSettings>,TSimulationModuleTypeable<FClutchSimModule>`
- desc: </summary>
- L62 _public prototype_ `DEFINE_CHAOSSIMTYPENAME(FClutchSimModule);`
- L63 _public prototype_ `FClutchSimModule(const FClutchSettings& Settings);`
- L65 _public function_ `virtual TSharedPtr<FModuleNetData> GenerateNetData(const int32 SimArrayIndex) const override`
- L75 _public function_ `virtual const FString GetDebugName() const`
- L77 _public prototype_ `virtual bool GetDebugString(FString& StringOut) const override;`
- L79 _public prototype_ `virtual void Simulate(float DeltaTime, const FAllInputs& Inputs, FSimModuleTree& VehicleModuleSystem);`
- L83 _private member_ `float ClutchValue;`

#### class `Chaos::FClutchSimFactory`  
`class FClutchSimFactory : public FSimFactoryModule<FClutchSimModuleData> , public TSimulationModuleTypeable<FClutchSimModule,FClutchSimFactory> , public TSimFactoryAutoRegister<FClutchSimFactory>`  
_L86-94_
- inherits: `FSimFactoryModule<FClutchSimModuleData>,TSimulationModuleTypeable<FClutchSimModule,FClutchSimFactory>,TSimFactoryAutoRegister<FClutchSimFactory>`
- L93 _public function_ `FClutchSimFactory() : FSimFactoryModule(TEXT("Clut`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API CHAOSVEHICLESCORE_API`
- L10 _namespace_ `namespace Chaos`

### `Source/Runtime/Experimental/ChaosVehicles/ChaosVehiclesCore/Public/SimModule/DeferredForcesModular.h` (Public)


#### enum `EForceFlags`  
`enum class EForceFlags : uint32`  
_L11-21_
- L13 _public enumerator_ `None = 0` — No flags.
- L15 _public enumerator_ `AllowSubstepping = 1 << 0`
- L16 _public enumerator_ `AccelChange = 1 << 1`
- L17 _public enumerator_ `VelChange = 1 << 2`
- L18 _public enumerator_ `IsLocalForce = 1 << 3`
- L19 _public enumerator_ `LevelSlope = 1 << 4`

#### class `FDeferredForcesModular`  
`class FDeferredForcesModular`  
_L27-242_
- L139 _public function_ `void Add(const FApplyForceData& ApplyForceDataIn)`
- L144 _public function_ `void Add(const FApplyForceAtPositionData& ApplyForceAtPositionDataIn)`
- L149 _public function_ `void AddCOM(const FApplyForceAtPositionData& ApplyForceAtPositionDataIn)`
- L154 _public function_ `void Add(const FAddTorqueInRadiansData& ApplyTorqueDataIn)`
- L159 _public function_ `void Add(const FAddImpulseData& ApplyImpulseDataIn)`
- L164 _public function_ `void Add(const FAddImpulseAtPositionData& ApplyImpulseAtPositionDataIn)`
- L169 _public prototype_ `Chaos::FPBDRigidParticleHandle* GetParticleFromUniqueIndex(int32 ParticleUniqueIdx, const TArray<Chaos::FPBDRigidParticleHandle*>& Particles) const;`
- L171 _public prototype_ `Chaos::FPBDRigidParticleHandle* GetParticle(FGeometryCollectionPhysicsProxy* Proxy , int TransformIndex , int32 ParticleIdx , const FVector& PositionalOffset , const TManagedArray<FTransform>& Transforms , const TManagedArray<FTransform>& CollectionMassToLocal , const TManagedArray<int32>& Parent , FTransform& TransformOut);`
- L180 _public prototype_ `Chaos::FPBDRigidParticleHandle* GetParticle(FGeometryCollectionPhysicsProxy* Proxy , int TransformIndex , int32 ParticleIdx , const FVector& PositionalOffset , const FTransform& Transform , const TManagedArray<FTransform>& CollectionMassToLocal , const TManagedArray<int32>& Parent , FTransform& TransformOut);`
- L189 _public prototype_ `Chaos::FPBDRigidParticleHandle* GetParticle(const FTransform& OffsetTransform , FGeometryCollectionPhysicsProxy* Proxy , int32 ParticleIdx , const FVector& PositionalOffset , FTransform& TransformOut);`
- L195 _public prototype_ `Chaos::FPBDRigidParticleHandle* GetParticle(const FTransform& OffsetTransform , TArray<Chaos::FPBDRigidParticleHandle*>& Particles , TArray<Chaos::FPBDRigidClusteredParticleHandle*>& ClusterParticles , int32 ParticleIdx , const FVector& PositionalOffset , FTransform& TransformOut);`
- L202 _public prototype_ `Chaos::FPBDRigidParticleHandle* GetClusterParticle(TArray<Chaos::FPBDRigidClusteredParticleHandle*>& ClusterParticles);`
- L204 _public prototype_ `void Apply(FGeometryCollectionPhysicsProxy* Proxy , const TManagedArray<FTransform>& Transforms , const TManagedArray<FTransform>& CollectionMassToLocal , const TManagedArray<int32>& Parent);`
- L209 _public prototype_ `void Apply(FGeometryCollectionPhysicsProxy* Proxy , const TManagedArray<FTransform3f>& Transforms , const TManagedArray<FTransform>& CollectionMassToLocal , const TManagedArray<int32>& Parent);`
- L214 _public prototype_ `void Apply(FGeometryCollectionPhysicsProxy* Proxy);`
- L216 _public prototype_ `void Apply(TArray<Chaos::FPBDRigidParticleHandle*>& Particles , TArray<Chaos::FPBDRigidClusteredParticleHandle*>& ClusterParticles);`
- L219 _public prototype_ `void Apply(Chaos::FPBDRigidParticleHandle* Particle);`
- L224 _private prototype_ `template<typename TransformType> void ApplyTemplate(FGeometryCollectionPhysicsProxy* Proxy , const TManagedArray<TransformType>& Transforms , const TManagedArray<FTransform>& CollectionMassToLocal , const TManagedArray<int32>& Parent);`
- L229 _private prototype_ `void AddForceAtPosition(Chaos::FPBDRigidParticleHandle* RigidHandle, const FApplyForceAtPositionData& DataIn, const FTransform& OffsetTransform);`
- L230 _private prototype_ `void AddTorque(Chaos::FPBDRigidParticleHandle* RigidHandle, const FAddTorqueInRadiansData& DataIn, const FTransform& OffsetTransform);`
- L231 _private prototype_ `void AddForce(Chaos::FPBDRigidParticleHandle* RigidHandle, const FApplyForceData& DataIn, const FTransform& OffsetTransform);`
- L232 _private prototype_ `void AddForceAtCOM(Chaos::FPBDRigidParticleHandle* RigidHandle, const FApplyForceAtPositionData& DataIn);`
- L234 _private member_ `TArray<FApplyForceData> ApplyForceDatas;`
- L235 _private member_ `TArray<FApplyForceAtPositionData> ApplyForceAtCOMDatas;`
- L236 _private member_ `TArray<FApplyForceAtPositionData> ApplyForceAtPositionDatas;`
- L237 _private member_ `TArray<FAddTorqueInRadiansData> ApplyTorqueDatas;`
- L238 _private member_ `TArray<FAddImpulseData> ApplyImpulseDatas;`
- L239 _private member_ `TArray<FAddImpulseAtPositionData> ApplyImpulseAtPositionDatas;`
- L241 _private member_ `FTransform ParticleOffsetTransform;` — Odd rotation coming through from CU physics bodies

#### struct `FDeferredForcesModular::FApplyForceData`  
`struct FApplyForceData`  
_L31-52_
- L33 _public function_ `FApplyForceData(const FTransform& OffsetTransformIn, int TransformIndexIn, int ParticleIndexIn, const FVector& ForceIn, bool bAllowSubsteppingIn, bool bAccelChangeIn, bool bLevelSlope, const FColor& ColorIn) : OffsetTransform(OffsetTransformIn) , TransformIndex(TransformIndexIn) , ParticleIdx(ParticleIndexIn) , Force(ForceIn) , Flags(EForceFlags::None) , DebugColor(ColorIn)`
- L46 _public member_ `FTransform OffsetTransform;`
- L47 _public member_ `int TransformIndex;`
- L48 _public member_ `int32 ParticleIdx;`
- L49 _public member_ `FVector Force;`
- L50 _public member_ `EForceFlags Flags;`
- L51 _public member_ `FColor DebugColor;`

#### struct `FDeferredForcesModular::FApplyForceAtPositionData`  
`struct FApplyForceAtPositionData`  
_L54-77_
- L56 _public function_ `FApplyForceAtPositionData(const FTransform& OffsetTransformIn, int TransformIndexIn, int ParticleIndexIn, const FVector& ForceIn, const FVector& PositionIn, bool bAllowSubsteppingIn, bool bIsLocalForceIn, bool bLevelSlope, const FColor& ColorIn) : OffsetTransform(OffsetTransformIn) , TransformIndex(TransformIndexIn) , ParticleIdx(ParticleIndexIn) , Force(ForceIn) , Position(PositionIn) , Flags(EForceFlags::None) , DebugColor(ColorIn)`
- L70 _public member_ `FTransform OffsetTransform;`
- L71 _public member_ `int TransformIndex;`
- L72 _public member_ `int32 ParticleIdx;`
- L73 _public member_ `FVector Force;`
- L74 _public member_ `FVector Position;`
- L75 _public member_ `EForceFlags Flags;`
- L76 _public member_ `FColor DebugColor;`

#### struct `FDeferredForcesModular::FAddTorqueInRadiansData`  
`struct FAddTorqueInRadiansData`  
_L79-99_
- L81 _public function_ `FAddTorqueInRadiansData(const FTransform& OffsetTransformIn, int TransformIndexIn, int ParticleIndexIn, const FVector& TorqueIn, bool bAllowSubsteppingIn, bool bAccelChangeIn, const FColor& ColorIn) : OffsetTransform(OffsetTransformIn) , TransformIndex(TransformIndexIn) , ParticleIdx(ParticleIndexIn) , Torque(TorqueIn) , Flags(EForceFlags::None) , DebugColor(ColorIn)`
- L93 _public member_ `FTransform OffsetTransform;`
- L94 _public member_ `int TransformIndex;`
- L95 _public member_ `int32 ParticleIdx;`
- L96 _public member_ `FVector Torque;`
- L97 _public member_ `EForceFlags Flags;`
- L98 _public member_ `FColor DebugColor;`

#### struct `FDeferredForcesModular::FAddImpulseData`  
`struct FAddImpulseData`  
_L101-118_
- L103 _public function_ `FAddImpulseData(const FTransform& OffsetTransformIn, int TransformIndexIn, int ParticleIndexIn, const FVector& ImpulseIn, const bool bVelChangeIn) : OffsetTransform(OffsetTransformIn) , TransformIndex(TransformIndexIn) , ParticleIdx(ParticleIndexIn) , Impulse(ImpulseIn) , Flags(EForceFlags::None)`
- L113 _public member_ `FTransform OffsetTransform;`
- L114 _public member_ `int TransformIndex;`
- L115 _public member_ `int32 ParticleIdx;`
- L116 _public member_ `FVector Impulse;`
- L117 _public member_ `EForceFlags Flags;`

#### struct `FDeferredForcesModular::FAddImpulseAtPositionData`  
`struct FAddImpulseAtPositionData`  
_L120-137_
- L122 _public function_ `FAddImpulseAtPositionData(const FTransform& OffsetTransformIn, int TransformIndexIn, int ParticleIndexIn, const FVector& ImpulseIn, const FVector& PositionIn) : OffsetTransform(OffsetTransformIn) , TransformIndex(TransformIndexIn) , ParticleIdx(ParticleIndexIn) , Impulse(ImpulseIn) , Position(PositionIn)`
- L132 _public member_ `FTransform OffsetTransform;`
- L133 _public member_ `int TransformIndex;`
- L134 _public member_ `int32 ParticleIdx;`
- L135 _public member_ `FVector Impulse;`
- L136 _public member_ `FVector Position;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CHAOSVEHICLESCORE_API`
- L22 _prototype_ `ENUM_CLASS_FLAGS(EForceFlags);`

### `Source/Runtime/Experimental/ChaosVehicles/ChaosVehiclesCore/Public/SimModule/EngineModule.h` (Public)


#### struct `Chaos::FEngineSimModuleData`  
`struct FEngineSimModuleData : public FTorqueSimModuleData , public Chaos::TSimulationModuleTypeable<class FEngineSimModule,FEngineSimModuleData>`  
_L15-37_
- inherits: `FTorqueSimModuleData,Chaos::TSimulationModuleTypeable<classFEngineSimModule,FEngineSimModuleData>`
- L20 _public function_ `FEngineSimModuleData(int NodeArrayIndex, const FString& InDebugString) : FTorqueSimModuleData(NodeArrayIndex, InDebugString)`
- L25 _public function_ `virtual void FillSimState(ISimulationModuleBase* SimModule) override`
- L31 _public function_ `virtual void FillNetState(const ISimulationModuleBase* SimModule) override`

#### struct `Chaos::FEngineOutputData`  
`struct FEngineOutputData : public FSimOutputData , public Chaos::TSimulationModuleTypeable<class FEngineSimModule,FEngineOutputData>`  
_L39-54_
- inherits: `FSimOutputData,Chaos::TSimulationModuleTypeable<classFEngineSimModule,FEngineOutputData>`
- L43 _public function_ `virtual FSimOutputData* MakeNewData() override`
- L44 _public function_ `static FSimOutputData* MakeNew()`
- L46 _public prototype_ `virtual void FillOutputState(const ISimulationModuleBase* SimModule) override;`
- L47 _public prototype_ `virtual void Lerp(const FSimOutputData& InCurrent, const FSimOutputData& InNext, float Alpha) override;`
- L49 _public prototype_ `virtual FString ToString() override;`
- L52 _public member_ `float RPM;`
- L53 _public member_ `float Torque;`

#### struct `Chaos::FEngineSettings`  
`struct FEngineSettings`  
_L56-86_
- L58 _public function_ `FEngineSettings() : MaxTorque(300.f) , MaxRPM(6000) , IdleRPM(1200) , EngineBrakeEffect(50.0f) , EngineInertia(100.0f)`
- L79 _public member_ `FNormalisedGraph TorqueCurve;`
- L80 _public member_ `float MaxTorque;` — [N.m] The peak torque Y value in the normalized torque graph
- L81 _public member_ `uint16 MaxRPM;` — [RPM] The absolute maximum RPM the engine can theoretically reach (last X value in the normalized torque graph)
- L82 _public member_ `uint16 IdleRPM;` — [RPM] The RPM at which the throttle sits when the car is not moving
- L83 _public member_ `float EngineBrakeEffect;` — [N.m] How much the engine slows the vehicle when the throttle is released
- L85 _public member_ `float EngineInertia;`

#### class `Chaos::FEngineSimModule`  
`class FEngineSimModule : public FTorqueSimModule, public TSimModuleSettings<FEngineSettings>, public TSimulationModuleTypeable<FEngineSimModule>`  
_L88-126_
- inherits: `FTorqueSimModule,TSimModuleSettings<FEngineSettings>,TSimulationModuleTypeable<FEngineSimModule>`
- L91 _public prototype_ `DEFINE_CHAOSSIMTYPENAME(FEngineSimModule);`
- L92 _public prototype_ `FEngineSimModule(const FEngineSettings& Settings);`
- L94 _public prototype_ `virtual ~FEngineSimModule() = default;`
- L96 _public function_ `virtual TSharedPtr<FModuleNetData> GenerateNetData(const int32 SimArrayIndex) const override`
- L105 _public function_ `virtual FSimOutputData* GenerateOutputData() const override`
- L110 _public function_ `virtual const FString GetDebugName() const`
- L112 _public prototype_ `virtual bool GetDebugString(FString& StringOut) const override;`
- L114 _public prototype_ `virtual void Simulate(float DeltaTime, const FAllInputs& Inputs, FSimModuleTree& VehicleModuleSystem) override;`
- L116 _public function_ `inline float GetEngineIdleSpeed() const`
- L117 _public prototype_ `inline float GetEngineTorque(float ThrottlePosition, float EngineRPM);`
- L118 _public prototype_ `inline float GetTorqueFromRPM(float RPM, bool LimitToIdle = true);`
- L122 _protected member_ `float EngineIdleSpeed;`
- L123 _protected member_ `float MaxEngineSpeed;`
- L124 _protected member_ `bool EngineStarted;` — is the engine turned off or has it been started

#### class `Chaos::FEngineSimFactory`  
`class FEngineSimFactory : public FSimFactoryModule<FEngineSimModuleData> , public TSimulationModuleTypeable<FEngineSimModule,FEngineSimFactory> , public TSimFactoryAutoRegister<FEngineSimFactory>`  
_L128-136_
- inherits: `FSimFactoryModule<FEngineSimModuleData>,TSimulationModuleTypeable<FEngineSimModule,FEngineSimFactory>,TSimFactoryAutoRegister<FEngineSimFactory>`
- L135 _public function_ `FEngineSimFactory() : FSimFactoryModule(TEXT("Engi`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API CHAOSVEHICLESCORE_API`
- L10 _namespace_ `namespace Chaos`

### `Source/Runtime/Experimental/ChaosVehicles/ChaosVehiclesCore/Public/SimModule/ModuleFactoryRegister.h` (Public)


#### class `Chaos::FModuleFactoryRegister`  
`class FModuleFactoryRegister`  
_L17-39_
- L20 _public prototype_ `static FModuleFactoryRegister& Get();`
- L22 _public prototype_ `void RegisterFactory(const FName TypeName, TWeakPtr<IFactoryModule> InFactory);`
- L23 _public prototype_ `void RegisterFactory(const uint32 TypeNameHash, TWeakPtr<IFactoryModule> InFactory);`
- L24 _public prototype_ `void RemoveFactory(TWeakPtr<IFactoryModule> InFactory);`
- L25 _public prototype_ `void Reset();`
- L26 _public prototype_ `bool ContainsFactory(const FName TypeName) const;`
- L27 _public prototype_ `bool ContainsFactory(const uint32 TypeNameHash) const;`
- L28 _public prototype_ `TSharedPtr<Chaos::FModuleNetData> GenerateNetData(const uint32 TypeNameHash, const int32 SimArrayIndex);`
- L30 _public function_ `static uint32 GetModuleHash(const FName TypeName)`
- L37 _protected prototype_ `FModuleFactoryRegister() = default;`
- L38 _protected member_ `TMap<int32, TWeakPtr<IFactoryModule>> RegisteredFactoriesByName;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CHAOSVEHICLESCORE_API`
- L11 _namespace_ `namespace Chaos`
- L45 _function_ `template<typename T, typename... Args> static bool RegisterFactoryHelper(Args... args)` (scope `Chaos`) — Static helper function to create and register a factory of the correct type. The returned Factory MUST be stored somewhere by the caller.

### `Source/Runtime/Experimental/ChaosVehicles/ChaosVehiclesCore/Public/SimModule/ModuleInput.h` (Public)


#### enum `EModuleInputQuantizationType`  
`enum class EModuleInputQuantizationType : uint8`  
_L15-19_
- reflection: `UENUM(BlueprintType)`
- L17 _public enumerator_ `Default_16Bits`
- L18 _public enumerator_ `Custom_8Bits`

#### enum `EModuleInputValueType`  
`enum class EModuleInputValueType : uint8`  
_L22-32_
- reflection: `UENUM(BlueprintType)`
- L24 _public enumerator_ `MBoolean UMETA(DisplayName = "Digital (bool)")`
- L25 _public enumerator_ `MAxis1D UMETA(DisplayName = "Axis1D (float)")`
- L26 _public enumerator_ `MAxis2D UMETA(DisplayName = "Axis2D (Vector2D)")`
- L27 _public enumerator_ `MAxis3D UMETA(DisplayName = "Axis3D (Vector)")`
- L28 _public enumerator_ `MInteger UMETA(DisplayName = "Digital (int32)")`

#### enum `EFunctionType`  
`enum class EFunctionType : uint8`  
_L36-41_
- reflection: `UENUM(BlueprintType)`
- desc: Input Options
- L38 _public enumerator_ `LinearFunction = 0`
- L39 _public enumerator_ `SquaredFunction`
- L40 _public enumerator_ `CustomCurve`

#### enum `EModuleInputBufferActionType`  
`enum class EModuleInputBufferActionType : uint8`  
_L44-54_
- reflection: `UENUM(BlueprintType)`
- L47 _public enumerator_ `Override = 0` — Replaces current value in buffer with new value
- L50 _public enumerator_ `Combine` — Adds new value to current value in buffer
- L53 _public enumerator_ `Average` — A running average of the inputs.

#### struct `ModularQuantize::TCompressedFloatDetails`  
`template<int32 MaxValue, uint32 NumBits> struct TCompressedFloatDetails`  
_L59-66_
- L62 _public member_ `static constexpr int32 MaxBitValue = (1 << (NumBits - 1)) - 1;` — NumBits = 8:
- L63 _public member_ `static constexpr int32 Bias = (1 << (NumBits - 1));` — 1000 0000 - Bias to pivot around (in order to support signed values)
- L64 _public member_ `static constexpr int32 SerIntMax = (1 << (NumBits - 0));` — 1 0000 0000 - What we pass into SerializeInt
- L65 _public member_ `static constexpr int32 MaxDelta = (1 << (NumBits - 0)) - 1;` — 1111 1111 - Max delta is

#### struct `FModuleInputValue`  
`struct FModuleInputValue`  
_L189-393_
- reflection: `USTRUCT(BlueprintType)`
- L194 _public typedef_ `using MAxis1D = double;` — #TODO: Axis1D (float) double or float? FVector2D and FVector are double
- L195 _public typedef_ `using MAxis2D = FVector2D;`
- L196 _public typedef_ `using MAxis3D = FVector;`
- L197 _public typedef_ `using MInteger = int32;`
- L200 _public prototype_ `FModuleInputValue() = default;` — Support all relevant default constructors (FModuleInputValue isn't movable)
- L201 _public prototype_ `FModuleInputValue(const FModuleInputValue&) = default;`
- L202 _public prototype_ `FModuleInputValue& operator= (const FModuleInputValue&) = default;`
- L206 _public function_ `FModuleInputValue(bool bInValue) : bHasValue(true), Value(FVector::ZeroVector), ValueInt(bInValue), ValueType(EModuleInputValueType::MBoolean)` — Specialized constructors for supported types Converting a value to a different type (e.g. Val = FVector(1, 1, 1); Val = true;) zeroes out any unused components to ensure getters continue to function correctly.
- L207 _public function_ `FModuleInputValue(MInteger InValue) : bHasValue(true), Value(FVector::ZeroVector), ValueInt(InValue), ValueType(EModuleInputValueType::MInteger)`
- L208 _public function_ `FModuleInputValue(MAxis1D InValue) : bHasValue(true), Value(InValue, 0.f, 0.f), ValueInt(0), ValueType(EModuleInputValueType::MAxis1D)`
- L209 _public function_ `FModuleInputValue(MAxis2D InValue) : bHasValue(true), Value(InValue.X, InValue.Y, 0.f), ValueInt(0), ValueType(EModuleInputValueType::MAxis2D)`
- L210 _public function_ `FModuleInputValue(MAxis3D InValue) : bHasValue(true), Value(InValue), ValueInt(0), ValueType(EModuleInputValueType::MAxis3D)`
- L212 _public prototype_ `FModuleInputValue ReturnQuantized(EModuleInputQuantizationType InInputQuantizationType) const;`
- L214 _public prototype_ `static void Quantize(double& InOutValue, EModuleInputQuantizationType InInputQuantizationType);`
- L216 _public prototype_ `static bool SerializeQuantized(double& InOutValue, FArchive& Ar, EModuleInputQuantizationType InInputQuantizationType);`
- L219 _public function_ `FModuleInputValue(EModuleInputValueType InValueType)` — Build a specific type with no value
- L227 _public function_ `void Reset()` — Resets Value without affecting ValueType
- L234 _public function_ `FModuleInputValue& operator+=(const FModuleInputValue& Rhs)`
- L253 _public function_ `FModuleInputValue& operator-=(const FModuleInputValue& Rhs)`
- L273 _public function_ `FModuleInputValue& operator*=(float Scalar)` — Scalar operators
- L292 _public function_ `static FModuleInputValue Clamp(const FModuleInputValue& InValue, const float InMin, const float InMax)`
- L311 _public function_ `template<typename T> inline T Get() const`
- L314 _public function_ `float operator[](int32 Index) const` — Read only index based value accessor, doesn't care about type. Expect 0 when accessing unused components.
- L316 _public function_ `bool IsQuantizedNonZero(EModuleInputQuantizationType InInputQuantizationType, float Tolerance = KINDA_SMALL_NUMBER) const`
- L317 _public prototype_ `bool IsNonZero(float Tolerance = KINDA_SMALL_NUMBER) const;`
- L320 _public function_ `FModuleInputValue& ConvertToType(EModuleInputValueType Type)` — In-place type conversion
- L329 _public function_ `FModuleInputValue& ConvertToType(const FModuleInputValue& Other)`
- L331 _public function_ `EModuleInputValueType GetValueType() const`
- L333 _public prototype_ `float GetMagnitudeSq() const;`
- L334 _public prototype_ `float GetMagnitude() const;`
- L335 _public prototype_ `int32 GetMagnitudeInt() const;`
- L338 _public prototype_ `void Serialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess, EModuleInputQuantizationType InInputQuantizationType);` — Serialize values
- L339 _public prototype_ `void NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess, EModuleInputQuantizationType InInputQuantizationType);`
- L340 _public prototype_ `void DeltaNetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess,const FModuleInputValue& PreviousInputValue, EModuleInputQuantizationType InInputQuantizationType);`
- L342 _public prototype_ `void Set(const FModuleInputValue& In);`
- L344 _public prototype_ `void Lerp(const FModuleInputValue& Min, const FModuleInputValue& Max, float Alpha);`
- L346 _public prototype_ `void Merge(const FModuleInputValue& From);`
- L347 _public prototype_ `void Combine(const FModuleInputValue& With);`
- L348 _public prototype_ `void Average(const FModuleInputValue& With);`
- L350 _public prototype_ `void Decay(const float DecayAmount);`
- L353 _public prototype_ `FString ToString() const;` — Type sensitive debug stringify
- L356 _public function_ `void SetApplyInputDecay(const bool bInApplyInputDecay)` — During physics resimulation, apply decay for this input while it's being extrapolated
- L357 _public function_ `bool ShouldApplyInputDecay() const`
- L360 _public function_ `void SetInverseInputDecay(const bool bInInverseInputDecay)` — During physics resimulation, if input is being decayed, inverse the decay value, this produces better results sometimes for some inputs like steering
- L361 _public function_ `bool ShouldInverseInputDecay() const`
- L364 _public function_ `void SetClearAfterConsumed(const bool bInClearAfterConsumed)` — After simulation first consumes the input, clear the value so that it  doesn't persist across multiple async physics ticks
- L365 _public function_ `bool ShouldClearAfterConsumed() const`
- L368 _protected prototype_ `void SetMagnitude(float NewSize);`
- L371 _protected member_ `bool bHasValue = false;` — `UPROPERTY(Transient)`
- L374 _protected member_ `FVector Value = FVector::ZeroVector;` — `UPROPERTY()`
- L377 _protected member_ `int32 ValueInt = 0;` — `UPROPERTY()`
- L380 _protected member_ `EModuleInputValueType ValueType = EModuleInputValueType::MBoolean;` — `UPROPERTY()`
- L384 _protected member_ `bool bApplyInputDecay = false;` — `UPROPERTY()` — During physics resimulation, apply decay for this input while it's being extrapolated
- L388 _protected member_ `bool bInverseInputDecay = false;` — `UPROPERTY()` — During physics resimulation, if input is being decayed, inverse the decay value, this produces better results sometimes for some inputs like steering
- L392 _protected member_ `bool bClearAfterConsumed = false;` — `UPROPERTY()` — After simulation first consumes the input, clear the value so that it doesn't persist across multiple async physics ticks
- L397 _function_ `template<> inline bool FModuleInputValue::Get() const` — Supported getter specializations
- L404 _function_ `template<> inline FModuleInputValue::MAxis1D FModuleInputValue::Get() const`
- L410 _function_ `template<> inline FModuleInputValue::MAxis2D FModuleInputValue::Get() const`
- L416 _function_ `template<> inline FModuleInputValue::MAxis3D FModuleInputValue::Get() const`
- L422 _function_ `template<> inline FModuleInputValue::MInteger FModuleInputValue::Get() const`

#### class `FModuleInputConversion`  
`class FModuleInputConversion`  
_L428-466_
- L432 _public function_ `static bool ToBool(FModuleInputValue& InValue)`
- L438 _public function_ `static float ToAxis1D(FModuleInputValue& InValue)`
- L444 _public function_ `static FVector2D ToAxis2D(FModuleInputValue& InValue)`
- L450 _public function_ `static FVector ToAxis3D(FModuleInputValue& InValue)`
- L456 _public function_ `static int32 ToInteger(FModuleInputValue& InValue)`
- L462 _public function_ `static FString ToString(FModuleInputValue& ActionValue)`

#### class `UDefaultModularVehicleInputModifier`  
`class UDefaultModularVehicleInputModifier : public UObject`  
_L470-511_
- reflection: `UCLASS(BlueprintType, Blueprintable, MinimalAPI)`
- inherits: `UObject`
- L475 _public function_ `UDefaultModularVehicleInputModifier(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) , RiseRate(5.0f), FallRate(5.0f), InputCurveFunction(EFunctionType::LinearFunction)`
- L479 _public function_ `virtual ~UDefaultModularVehicleInputModifier()`
- L487 _public member_ `float RiseRate;` — `UPROPERTY(EditAnywhere, Category = VehicleInputRate)` — Rate at which the input value rises
- L493 _public member_ `float FallRate;` — `UPROPERTY(EditAnywhere, Category = VehicleInputRate)` — Rate at which the input value falls
- L499 _public member_ `EFunctionType InputCurveFunction;` — `UPROPERTY(EditAnywhere, Category = VehicleInputRate)` — Controller input curve, various predefined options, linear, squared, or user can specify a custom curve function
- L509 _public prototype_ `virtual FModuleInputValue InterpInputValue(float DeltaTime, const FModuleInputValue& CurrentValue, const FModuleInputValue& NewValue) const;` — Change an output value using max rise and fall rates
- L510 _public prototype_ `virtual float CalcControlFunction(float InputValue);`

#### struct `FModuleInputSetup`  
`struct FModuleInputSetup`  
_L514-556_
- reflection: `USTRUCT(BlueprintType)`
- L518 _public function_ `FModuleInputSetup()`
- L526 _public function_ `FModuleInputSetup(const FName& InName, const EModuleInputValueType& InType) : Name(InName) , Type(InType) , bApplyInputDecay(false) , bInverseInputDecay(false) , bClearAfterConsumed(false)`
- L535 _public function_ `bool operator==(const FModuleInputSetup& Rhs) const`
- L541 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, Category = VehicleInput)`
- L544 _public member_ `EModuleInputValueType Type;` — `UPROPERTY(EditAnywhere, Category = VehicleInput)`
- L548 _public member_ `bool bApplyInputDecay;` — `UPROPERTY(EditAnywhere, Category = VehicleInput)` — During physics resimulation, apply decay for this input while it's being extrapolated
- L551 _public member_ `bool bInverseInputDecay;` — `UPROPERTY(EditAnywhere, Category = VehicleInput)`
- L555 _public member_ `bool bClearAfterConsumed;` — `UPROPERTY(EditAnywhere, Category = VehicleInput)` — After simulation first consumes the input, clear the value doesn't persist across multiple async physics ticks

#### class `FScopedModuleInputInitializer`  
`class FScopedModuleInputInitializer`  
_L558-577_
- L561 _public function_ `FScopedModuleInputInitializer(TArray<struct FModuleInputSetup>& InSetupData)`
- L566 _public function_ `~FScopedModuleInputInitializer()`
- L571 _public function_ `static bool HasSetup()`
- L572 _public function_ `static TArray<struct FModuleInputSetup>* GetSetup()`
- L576 _private member_ `static TArray<struct FModuleInputSetup>* InitSetupData;`

#### struct `FModuleInputContainer`  
`struct FModuleInputContainer`  
_L581-670_
- reflection: `USTRUCT()`
- L586 _public typedef_ `using FInputNameMap = TMap<FName, int>;`
- L587 _public typedef_ `using FInputValues = TArray<FModuleInputValue>;`
- L589 _public function_ `FModuleInputContainer()`
- L598 _public function_ `int GetNumInputs() const`
- L600 _public function_ `FModuleInputValue GetValueAtIndex(int Index) const`
- L602 _public function_ `void SetValueAtIndex(int Index, const FModuleInputValue& InValue, EModuleInputQuantizationType InInputQuantizationType, bool Quantize = true)`
- L614 _public function_ `void AverageValueAtIndex(int Index, const FModuleInputValue& InValue, EModuleInputQuantizationType InInputQuantizationType)`
- L618 _public function_ `void MergeValueAtIndex(int Index, const FModuleInputValue& InValue, EModuleInputQuantizationType InInputQuantizationType)`
- L623 _public function_ `void CombineValueAtIndex(int Index, const FModuleInputValue& InValue, EModuleInputQuantizationType InInputQuantizationType)`
- L628 _public function_ `FModuleInputContainer& operator=(const FModuleInputContainer& Other)`
- L642 _public prototype_ `void Initialize(TArray<FModuleInputSetup>& SetupData, FInputNameMap& NameMapOut);`
- L644 _public prototype_ `void ZeroValues();`
- L646 _public prototype_ `void Serialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess, EModuleInputQuantizationType InInputQuantizationType);`
- L648 _public prototype_ `int AddInput(EModuleInputValueType Type);`
- L650 _public prototype_ `void RemoveAllInputs();`
- L652 _public prototype_ `void Lerp(const FModuleInputContainer& Min, const FModuleInputContainer& Max, float Alpha);`
- L654 _public prototype_ `void Merge(const FModuleInputContainer& From);`
- L656 _public prototype_ `void Combine(const FModuleInputContainer& With);`
- L659 _public prototype_ `void Decay(const float DecayAmount);` — Decay input during resimulation by DecayAmount which increases over resimulation frames from 0.0 -> 1.0 when the input is being reused
- L662 _public prototype_ `void ClearConsumedInputs();` — Clear input once it has been consumed if input is marked as sutch. Prevents same input being fed into simulation when the PT tick is running multiple times per GT tick
- L664 _public function_ `TArray<FModuleInputValue>& AccessInputValues()`
- L668 _private member_ `TArray<FModuleInputValue> InputValues;` — `UPROPERTY()`

#### class `FInputInterface`  
`class FInputInterface`  
_L673-756_
- L677 _public typedef_ `using FInputNameMap = TMap<FName, int>;`
- L679 _public function_ `FInputInterface(const FInputNameMap& InNameMap, FModuleInputContainer& InValueContainer, EModuleInputQuantizationType InInputQuantizationType) : NameMap(InNameMap) , ValueContainer(InValueContainer) , InputQuantizationType(InInputQuantizationType)`
- L686 _public prototype_ `void SetValue(const FName& InName, const FModuleInputValue& InValue, bool Quantize = true);`
- L687 _public prototype_ `void CombineValue(const FName& InName, const FModuleInputValue& InValue);`
- L688 _public prototype_ `void AverageValue(const FName& InName, const FModuleInputValue& InValue);`
- L689 _public prototype_ `void MergeValue(const FName& InName, const FModuleInputValue& InValue);`
- L690 _public prototype_ `FModuleInputValue GetValue(const FName& InName) const;`
- L691 _public prototype_ `EModuleInputValueType GetValueType(const FName& InName) const;`
- L692 _public prototype_ `float GetMagnitude(const FName& InName) const;`
- L693 _public prototype_ `int32 GetMagnitudeInt(const FName& InName) const;`
- L694 _public prototype_ `bool InputsNonZero() const;`
- L697 _public function_ `bool GetBool(const FName& InName) const` — Quick Access to data type
- L702 _public function_ `int32 GetInteger(const FName& InName) const`
- L707 _public function_ `double GetFloat(const FName& InName) const`
- L712 _public function_ `FVector2D GetVector2D(const FName& InName) const`
- L717 _public function_ `FVector GetVector(const FName& InName) const`
- L723 _public function_ `void SetBool(const FName& InName, bool InBool)`
- L729 _public function_ `void SetInteger(const FName& InName, int32 InInteger)`
- L735 _public function_ `void SetFloat(const FName& InName, double InFloat, bool Quantize = false)`
- L741 _public function_ `void SetVector2D(const FName& InName, const FVector2D& InVector2D, bool Quantize = false)`
- L746 _public function_ `void SetVector(const FName& InName, const FVector& InVector, bool Quantize = false)`
- L753 _public member_ `const FInputNameMap& NameMap;` — per vehicle
- L754 _public member_ `FModuleInputContainer& ValueContainer;` — per vehicle instance
- L755 _public member_ `EModuleInputQuantizationType InputQuantizationType;`

#### class `UVehicleInputProducerBase`  
`class UVehicleInputProducerBase : public UObject`  
_L759-788_
- reflection: `UCLASS(Abstract, BlueprintType, Blueprintable, EditInlineNew, MinimalAPI)`
- inherits: `UObject`
- L764 _public typedef_ `using FInputNameMap = TMap<FName, int>;`
- L767 _public function_ `virtual void InitializeContainer(TArray<FModuleInputSetup>& SetupData, FInputNameMap& NameMapOut, EModuleInputQuantizationType InInputQuantizationType)` — initialize the input buffer container(s)
- L773 _public function_ `virtual void BufferInput(const FInputNameMap& InNameMap, const FName InName, const FModuleInputValue& InValue, EModuleInputBufferActionType BufferAction = EModuleInputBufferActionType::Override)` — capture input at game thread frequency
- L776 _public function_ `virtual void ProduceInput(int32 PhysicsStep, int32 NumSteps, const FInputNameMap& InNameMap, FModuleInputContainer& InOutContainer)` — produce input for PT simulation at PT frequency
- L779 _public function_ `virtual TArray<FModuleInputContainer>* GetTestInputBuffer()` — Special case override for providing test input straight onto the physics thread
- L782 _public function_ `virtual bool IsLoopingTestInputBuffer()` — Special case override for providing test input straight onto the physics thread
- L785 _public function_ `virtual int32 GetTestInputStartFrame()` — Special case override for providing test input straight onto the physics thread
- L787 _public member_ `EModuleInputQuantizationType InputQuantizationType;`

#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogModularInput, Log, All);`
- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogModularInput, Log, All);`
- L12 _macro_ `#define UE_API CHAOSVEHICLESCORE_API`
- L56 _namespace_ `namespace ModularQuantize`
- L69 _function_ `template<int32 MaxValue, uint32 NumBits, typename T UE_REQUIRES(std::is_floating_point_v<T>&& NumBits < 32)> bool ToCompressedFloat(const T InValue, uint32& OutCompressedFloat)` (scope `ModularQuantize`)
- L71 _typedef_ `using Details = ModularQuantize::TCompressedFloatDetails<MaxValue, NumBits>;` (scope `ModularQuantize::ToCompressedFloat`)
- L102 _function_ `template<int32 MaxValue, uint32 NumBits, typename T UE_REQUIRES(std::is_floating_point_v<T>&& NumBits < 32)> bool FromCompressedFloat(const uint32 InCompressed, T& OutValue )` (scope `ModularQuantize`)
- L104 _typedef_ `using Details = ModularQuantize::TCompressedFloatDetails<MaxValue, NumBits>;` (scope `ModularQuantize::FromCompressedFloat`)
- L127 _function_ `template<int32 MaxValue, uint32 NumBits, typename T UE_REQUIRES(std::is_floating_point_v<T>&& NumBits < 32)> bool WriteCompressedFloat(const T Value, FArchive& Ar)` (scope `ModularQuantize`)
- L129 _typedef_ `using Details = ModularQuantize::TCompressedFloatDetails<MaxValue, NumBits>;` (scope `ModularQuantize::WriteCompressedFloat`)
- L140 _function_ `template<int32 MaxValue, uint32 NumBits, typename T UE_REQUIRES(std::is_floating_point_v<T>&& NumBits < 32)> bool ReadCompressedFloat(T& Value, FArchive& Ar)` (scope `ModularQuantize`)
- L142 _typedef_ `using Details = ModularQuantize::TCompressedFloatDetails<MaxValue, NumBits>;` (scope `ModularQuantize::ReadCompressedFloat`)
- L154 _function_ `template<int32 MaxValue, uint32 NumBits> bool SerializeFixedFloat(double& InOutValue, FArchive& Ar)` (scope `ModularQuantize`) — Required because we seialize quantized vector in seperate parts depending on input type
- L168 _function_ `template<int32 MaxValue, uint32 NumBits, typename T UE_REQUIRES(std::is_floating_point_v<T>&& NumBits < 32)> void QuantizeValue(T& Value)` (scope `ModularQuantize`)
- L176 _function_ `template<int32 MaxValue, uint32 NumBits, typename T UE_REQUIRES(std::is_floating_point_v<T>&& NumBits < 32)> bool QuantizedIsNearlyEqual(const T& Left,const T& Right)` (scope `ModularQuantize`)
- L244 _function_ `friend FModuleInputValue operator+(const FModuleInputValue& Lhs, const FModuleInputValue& Rhs)`
- L263 _function_ `friend FModuleInputValue operator-(const FModuleInputValue& Lhs, const FModuleInputValue& Rhs)`
- L282 _function_ `friend FModuleInputValue operator*(const FModuleInputValue& Lhs, const float Rhs)`

### `Source/Runtime/Experimental/ChaosVehicles/ChaosVehiclesCore/Public/SimModule/MotorModule.h` (Public)


#### struct `Chaos::FMotorSettings`  
`struct FMotorSettings`  
_L17-29_
- desc: <summary> Motor settings </summary>
- L19 _public function_ `FMotorSettings() : MaxRPM(1.0f) , MaxTorque(100.0f) , EngineInertia(1.0f)`
- L26 _public member_ `float MaxRPM;`
- L27 _public member_ `float MaxTorque;`
- L28 _public member_ `float EngineInertia;`

#### class `Chaos::FMotorSimModule`  
`class FMotorSimModule : public FTorqueSimModule, public TSimModuleSettings<FMotorSettings>, public TSimulationModuleTypeable<FMotorSimModule>`  
_L35-47_
- inherits: `FTorqueSimModule,TSimModuleSettings<FMotorSettings>,TSimulationModuleTypeable<FMotorSimModule>`
- desc: <summary> A vehicle component that provides torque output based on a torque control input The output torque is based on a square function style curve, zero at 0.0 and MaxRPM, and 1.0 at mid RPM </summary>
- L38 _public prototype_ `DEFINE_CHAOSSIMTYPENAME(FMotorSimModule);`
- L39 _public prototype_ `FMotorSimModule(const FMotorSettings& Settings);`
- L41 _public function_ `virtual const FString GetDebugName() const`
- L43 _public prototype_ `virtual void Simulate(float DeltaTime, const FAllInputs& Inputs, FSimModuleTree& VehicleModuleSystem) override;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API CHAOSVEHICLESCORE_API`
- L9 _namespace_ `namespace Chaos`

### `Source/Runtime/Experimental/ChaosVehicles/ChaosVehiclesCore/Public/SimModule/SimModuleTree.h` (Public)


#### enum `ESimTreeProcessingOrder`  
`enum ESimTreeProcessingOrder : int8`  
_L17-23_
- reflection: `UENUM(BlueprintType)`
- L19 _public enumerator_ `ManualOverride = 0` — User calls simulate on the child modules
- L20 _public enumerator_ `LeafFirst = 1` — modules simulation from the leaf first
- L21 _public enumerator_ `RootFirst = 2` — modules simulate from the root first
- L22 _public enumerator_ `LeafFirstBFS = 3`

#### struct `Chaos::FPendingModuleAdds`  
`struct FPendingModuleAdds`  
_L32-39_
- L34 _public function_ `FPendingModuleAdds(int ParentIndexIn, ISimulationModuleBase* NewSimModuleIn) : ParentIndex(ParentIndexIn), NewSimModule(NewSimModuleIn)`
- L37 _public member_ `int ParentIndex;`
- L38 _public member_ `ISimulationModuleBase* NewSimModule;`

#### struct `Chaos::FPendingModuleDeletions`  
`struct FPendingModuleDeletions`  
_L41-45_
- L43 _public function_ `FPendingModuleDeletions(int GuidIn) : Guid(GuidIn)`
- L44 _public member_ `int Guid;`

#### class `Chaos::FSimTreeUpdates`  
`class FSimTreeUpdates`  
_L48-83_
- desc: Each update tree has it's own local tree hierarchy, this will be translated into the actual tree hierarchy.
- L51 _public function_ `int AddRoot(ISimulationModuleBase* NewSimModuleIn)`
- L57 _public function_ `int AddNodeBelow(int ParentIndex, ISimulationModuleBase* NewSimModuleIn)`
- L63 _public function_ `void RemoveNode(int Guid)`
- L68 _public function_ `void ClearUpdates()`
- L74 _public function_ `const TArray<FPendingModuleAdds>& GetNewModules() const`
- L75 _public function_ `const TArray<FPendingModuleDeletions>& GetDeletedModules() const`
- L77 _public function_ `TArray<FPendingModuleAdds>& AccessNewModules()`
- L78 _public function_ `TArray<FPendingModuleDeletions>& AccessDeletedModules()`
- L81 _private member_ `TArray<FPendingModuleAdds> NewModules;`
- L82 _private member_ `TArray<FPendingModuleDeletions> DeletedModules;`

#### struct `Chaos::FVehicleState`  
`struct FVehicleState`  
_L85-95_
- L87 _public member_ `float ForwardSpeedKmh;`
- L88 _public member_ `FVector Position;`
- L89 _public member_ `FQuat Rotation;`
- L90 _public member_ `FVector ForwardDir;`
- L91 _public member_ `FVector RightDir;`
- L92 _public member_ `FVector UpDir;`
- L93 _public member_ `FVector AngularVelocityRad;`
- L94 _public member_ `FVector LinearVelocity;`

#### class `Chaos::FSimModuleTree`  
`class FSimModuleTree`  
_L97-255_
- L120 _public function_ `FSimModuleTree()`
- L128 _public function_ `~FSimModuleTree()`
- L134 _public function_ `void Reset()`
- L139 _public function_ `bool IsEmpty() const`
- L140 _public function_ `int GetParent(int Index) const`
- L141 _public function_ `const TSet<int>& GetChildren(int Index) const`
- L142 _public function_ `const ISimulationModuleBase* GetSimModule(int Index) const`
- L143 _public function_ `ISimulationModuleBase* AccessSimModule(int Index) const`
- L144 _public function_ `bool IsValidNode(int Index) const`
- L145 _public function_ `int NumActiveNodes() const`
- L146 _public prototype_ `void GetRootNodes(TArray<int>& RootNodesOut);`
- L147 _public function_ `int GetNumNodes() const`
- L148 _public function_ `ESimTreeProcessingOrder GetSimTreeProcessingOrder() const`
- L150 _public prototype_ `int AddRoot(ISimulationModuleBase* SimModule);`
- L152 _public prototype_ `void Reparent(int Index, int ParentIndex);`
- L153 _public function_ `FSimModuleNode& GetNode(int Index)`
- L155 _public prototype_ `int AddNodeBelow(int AtIndex, ISimulationModuleBase* SimModule);`
- L157 _public prototype_ `int InsertNodeAbove(int AtIndex, ISimulationModuleBase* SimModule);`
- L159 _public prototype_ `void DeleteNode(int AtIndex);`
- L161 _public prototype_ `void AppendTreeUpdates(const FSimTreeUpdates& TreeUpdates);`
- L163 _public prototype_ `void Simulate(float DeltaTime, FAllInputs& Inputs, IPhysicsProxyBase* PhysicsProxy, Chaos::FPBDRigidParticleHandle* RootParticle);`
- L165 _public prototype_ `void OnContactModification(FCollisionContactModifier& Modifier, IPhysicsProxyBase* PhysicsProxy);`
- L167 _public function_ `void SetSimTreeProcessingOrder(ESimTreeProcessingOrder OrderIn)`
- L169 _public function_ `FDeferredForcesModular& AccessDeferredForces()`
- L170 _public function_ `const FDeferredForcesModular& GetDeferredForces() const`
- L171 _public function_ `const TArray<FSimModuleNode>& GetSimulationModuleTree()`
- L173 _public function_ `void SetAnimationEnabled(bool bInEnabled)`
- L174 _public function_ `bool IsAnimationEnabled()`
- L175 _public function_ `void SetSimulationEnabled(bool bInEnabled)`
- L176 _public function_ `bool IsSimulationEnabled()`
- L179 _public function_ `const FVehicleState& GetVehicleState() const`
- L185 _public function_ `template <typename T> FSimModuleNode* LocateNodeByType()`
- L198 _public function_ `int GetLargestComponentIndex()`
- L214 _public prototype_ `void GenerateReplicationStructure(Chaos::FModuleNetDataArray& NetData);`
- L215 _public prototype_ `void SetNetState(Chaos::FModuleNetDataArray& ModuleDatas);`
- L216 _public prototype_ `void SetSimState(const Chaos::FModuleNetDataArray& ModuleDatas);`
- L217 _public prototype_ `void InterpolateState(const float LerpFactor, Chaos::FModuleNetDataArray& LerpDatas, const Chaos::FModuleNetDataArray& MinDatas, const Chaos::FModuleNetDataArray& MaxDatas);`
- L219 _public function_ `FVehicleBlackboard* GetSimBlackboard()`
- L224 _public prototype_ `void SimulateNode(float DeltaTime, FAllInputs& Inputs, int NodeIdx, IPhysicsProxyBase* PhysicsProxy, Chaos::FPBDRigidParticleHandle* ParticleHandle);`
- L227 _protected prototype_ `void OnContactModificationInternal(int NodeIndex, FCollisionContactModifier& Modifier, IPhysicsProxyBase* PhysicsProxy);`
- L229 _protected prototype_ `void SimulateNodeBFS(float DeltaTime, FAllInputs& Inputs, const TArray<int>& RootNodes, IPhysicsProxyBase* PhysicsProxy, Chaos::FPBDRigidParticleHandle* ParticleHandle);`
- L231 _protected prototype_ `void DeleteNodesBelow(int NodeIdx);`
- L233 _protected prototype_ `int GetNextIndex();`
- L235 _protected prototype_ `void UpdateClusterUnionTransformsIfRequired(IPhysicsProxyBase* PhysicsProxy, ISimulationModuleBase* Module);`
- L238 _protected prototype_ `void UpdateModuleVelocites(IPhysicsProxyBase* PhysicsProxy, Chaos::FPBDRigidParticleHandle* RootParticle, bool bWake);`
- L239 _protected prototype_ `void UpdateVehicleState(Chaos::FPBDRigidParticleHandle* RootParticle);`
- L241 _protected member_ `TArray<FSimModuleNode> SimulationModuleTree;`
- L242 _protected member_ `TArray<int> FreeList;`
- L244 _protected member_ `FDeferredForcesModular DeferredForces;`
- L246 _protected member_ `Chaos::FAllInputs AllInputs;`
- L248 _protected member_ `bool bAnimationEnabled;`
- L249 _protected member_ `bool bSimulationEnabled;`
- L251 _protected member_ `FVehicleState VehicleState;`
- L252 _protected member_ `ESimTreeProcessingOrder SimTreeProcessingOrder;`
- L254 _protected member_ `TUniquePtr<FVehicleBlackboard> SimBlackboard;`

#### struct `Chaos::FSimModuleTree::FSimModuleNode`  
`struct FSimModuleNode`  
_L102-118_
- L104 _public function_ `FSimModuleNode() : SimModule(nullptr) , Parent(INVALID_IDX)`
- L110 _public function_ `bool IsValid() const`
- L112 _public member_ `ISimulationModuleBase* SimModule;`
- L113 _public member_ `int Parent;`
- L114 _public member_ `TSet<int> Children;`
- L116 _public member_ `const static int INVALID_IDX = -1;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API CHAOSVEHICLESCORE_API`
- L14 _delegate_ `DECLARE_STATS_GROUP(TEXT("ModularVehicle.SimTree"), STATGROUP_ModularVehicleSimTree`
- L26 _namespace_ `namespace Chaos`

### `Source/Runtime/Experimental/ChaosVehicles/ChaosVehiclesCore/Public/SimModule/SimModulesInclude.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/Experimental/ChaosVehicles/ChaosVehiclesCore/Public/SimModule/SimulationModuleBase.h` (Public)


#### struct `FCoreModularVehicleDebugParams`  
`struct FCoreModularVehicleDebugParams`  
_L19-26_
- L21 _public member_ `bool ShowMass = false;`
- L22 _public member_ `bool ShowForces = false;`
- L23 _public member_ `float DrawForceScaling = 0.0004f;`
- L24 _public member_ `float LevelSlopeThreshold = 0.86f;`
- L25 _public member_ `bool DisableForces = false;`

#### struct `Chaos::FModuleHitResults`  
`struct FModuleHitResults`  
_L56-62_
- L58 _public member_ `int SimIndex;`
- L59 _public member_ `FVector ImpactPoint;`
- L60 _public member_ `float Distance;`
- L61 _public member_ `bool bBlockingHit;`

#### struct `Chaos::FAllInputs`  
`struct FAllInputs`  
_L64-75_
- L66 _public function_ `FInputInterface& GetControls() const`
- L67 _public function_ `FInputInterface& GetState() const`
- L69 _public member_ `FTransform VehicleWorldTransform;`
- L70 _public member_ `TMap<int32, FModuleHitResults> HitResults;`
- L71 _public member_ `FInputInterface* ControlInputs = nullptr;`
- L72 _public member_ `FInputInterface* StateInputs = nullptr;`
- L73 _public member_ `bool bKeepVehicleAwake = false;`
- L74 _public member_ `float CurrentTimeDilation = 1.0f;`

#### struct `Chaos::FCreatedModule`  
`struct FCreatedModule`  
_L77-103_
- L79 _public function_ `FCreatedModule() : SimType("Empty"), Guid(INDEX_NONE), TreeIndex(INDEX_NONE)`
- L83 _public function_ `FCreatedModule(const FName& InSimType, int InGuid, int InTreeIndex) : SimType(InSimType), Guid(InGuid), TreeIndex(InTreeIndex)`
- L88 _public function_ `FCreatedModule(const FCreatedModule& Other) : SimType(Other.SimType), Guid(Other.Guid), TreeIndex(Other.TreeIndex)`
- L92 _public function_ `FCreatedModule& operator=(const FCreatedModule& Other)`
- L100 _public member_ `FName SimType;`
- L101 _public member_ `int Guid = INDEX_NONE;`
- L102 _public member_ `int32 TreeIndex = INDEX_NONE;`

#### struct `Chaos::FCreatedModules`  
`struct FCreatedModules`  
_L105-112_
- L107 _public function_ `FCreatedModules()`
- L111 _public member_ `TArray<Chaos::FCreatedModule> ModuleEvents;`

#### struct `Chaos::FSimModuleAnimationData`  
`struct FSimModuleAnimationData`  
_L114-131_
- L116 _public function_ `FSimModuleAnimationData() : BoneName(NAME_None) , AnimFlags(EAnimationFlags::AnimateNone) , AnimationLocOffset(FVector::ZeroVector) , AnimationRotOffset(FRotator::ZeroRotator) , CombinedRotation(FQuat::Identity) , AnimationSetupIndex(-1)`
- L125 _public member_ `FName BoneName;`
- L126 _public member_ `uint16 AnimFlags = EAnimationFlags::AnimateNone;`
- L127 _public member_ `FVector AnimationLocOffset;`
- L128 _public member_ `FRotator AnimationRotOffset;`
- L129 _public member_ `FQuat CombinedRotation;`
- L130 _public member_ `int AnimationSetupIndex;`

#### class `Chaos::TSimModuleSettings`  
`template <typename T> class TSimModuleSettings`  
_L138-159_
- desc: Code common between all simulation building blocks settings
- L142 _public function_ `explicit TSimModuleSettings(const T& SetupIn) : SetupData(SetupIn)`
- L147 _public function_ `FORCEINLINE T& AccessSetup()`
- L152 _public function_ `FORCEINLINE const T& Setup() const`
- L158 _private member_ `T SetupData;`

#### enum `Chaos::eSimModuleState`  
`enum eSimModuleState`  
_L162-166_
- L164 _public enumerator_ `Disabled`
- L165 _public enumerator_ `Enabled`

#### enum `Chaos::eSimModuleTypeFlags`  
`enum eSimModuleTypeFlags`  
_L168-174_
- L170 _public enumerator_ `NonFunctional = (1 << 0)` — bitmask 1,2,4,8
- L171 _public enumerator_ `Raycast = (1 << 1)` — requires raycast data
- L172 _public enumerator_ `TorqueBased = (1 << 2)` — performs torque calculations
- L173 _public enumerator_ `Velocity = (1 << 3)` — requires velocity data

#### enum `Chaos::EWheelAxis`  
`enum EWheelAxis`  
_L176-180_
- L178 _public enumerator_ `X` — X forward
- L179 _public enumerator_ `Y` — Y forward

#### class `Chaos::TSimulationModuleTypeableBase`  
`template<typename _To> class TSimulationModuleTypeableBase`  
_L190-201_
- L193 _public function_ `TSimulationModuleTypeableBase()`
- L197 _public function_ `static FName StaticSimTypeBase()`

#### class `Chaos::TSimulationModuleTypeable`  
`template<typename _To> class TSimulationModuleTypeable<_To>`  
_L207-218_
- L210 _public function_ `TSimulationModuleTypeable()`
- L214 _public function_ `static FName StaticSimType()`
- L232 _public function_ `static FName RecurseSimType()`

#### class `Chaos::TSimulationModuleTypeable`  
`template<typename _To, typename _From> class TSimulationModuleTypeable<_To,_From>`  
_L221-236_
- L210 _public function_ `TSimulationModuleTypeable()`
- L214 _public function_ `static FName StaticSimType()`
- L232 _public function_ `static FName RecurseSimType()`

#### struct `Chaos::TSimModuleTypeIsRecursive`  
`template<class T, class = void> struct TSimModuleTypeIsRecursive : std::false_type`  
_L240-242_
- inherits: `std::false_type`

#### struct `Chaos::TSimModuleTypeIsRecursive`  
`template<class T> struct TSimModuleTypeIsRecursive<T, std::enable_if_t<std::is_invocable_r<FName, decltype(T::RecurseSimType)>::value>> : std::integral_constant<bool, true>`  
_L245-247_
- inherits: `std::integral_constant<bool,true>`

#### class `Chaos::FSimulationModuleTypeContainer`  
`class FSimulationModuleTypeContainer`  
_L252-312_
- L255 _public member_ `TSet<FName> MyTypes;`
- L256 _public member_ `FName MostRecentAdd = NAME_None;`
- L257 _public function_ `void AddType(FName InType)`
- L262 _public function_ `bool IsSimType(FName InType) const`
- L266 _public function_ `FName GetSimType() const`
- L271 _public function_ `template <typename U> static FName GetStaticSimType()`
- L283 _public function_ `template<typename U> bool IsSimType() const`
- L295 _public function_ `template<typename U> U* Cast()`
- L304 _public function_ `template<typename U> const U* Cast() const`

#### class `Chaos::ISimulationModuleBase`  
`class ISimulationModuleBase : public FSimulationModuleTypeContainer, public TSimulationModuleTypeableBase<ISimulationModuleBase>`  
_L324-549_
- inherits: `FSimulationModuleTypeContainer,TSimulationModuleTypeableBase<ISimulationModuleBase>`
- desc: Interface base class for all simulation module building blocks
- L330 _public prototype_ `DEFINE_CHAOSSIMTYPENAME(ISimulationModuleBase);`
- L331 _public member_ `const static int INVALID_IDX = -1;`
- L333 _public function_ `ISimulationModuleBase() : SimModuleTree(nullptr) , SimTreeIndex(INVALID_IDX) , StateFlags(Enabled) , TransformIndex(INVALID_IDX) , ParticleIdx(INVALID_IDX) , LocalLinearVelocity(FVector::ZeroVector) , LocalAngularVelocity(FVector::ZeroVector) , bClustered(true) , bAnimationEnabled(true) , AnimationOffset(FVector::ZeroVector) , AppliedForce(FVector::ZeroVector) , Guid(INDEX_NONE) , CachedParticle(nullptr)`
- L348 _public prototype_ `virtual ~ISimulationModuleBase() = default;`
- L350 _public function_ `int GetGuid() const`
- L351 _public function_ `void SetGuid(int GuidIn)`
- L355 _public prototype_ `virtual const FString GetDebugName() const = 0;` — Get the friendly name for this module, primarily for logging & debugging module tree
- L360 _public prototype_ `virtual bool IsBehaviourType(eSimModuleTypeFlags InType) const = 0;` — Is Module of a specific behavioral data type
- L365 _public function_ `virtual bool IsEnabled() const` — Is Module active and simulating
- L370 _public function_ `void SetStateFlags(eSimModuleState StateFlagsIn)` — Set Module state, if simulating or not
- L375 _public function_ `virtual void OnConstruction_External(const Chaos::FPhysicsObjectHandle& PhysicsObject)` — Any post construction initialisation - called from Game Thread
- L380 _public function_ `virtual void OnTermination_External()` — Any cleaning up required - called from game thread
- L385 _public function_ `virtual void Simulate(IPhysicsProxyBase* Proxy, Chaos::FPBDRigidParticleHandle* ParticleHandle, float DeltaTime, const FAllInputs& Inputs, FSimModuleTree& VehicleModuleSystem)` — The main Simulation function that is called from the physics async callback thread
- L390 _public function_ `virtual void OnContactModification(Chaos::FCollisionContactModifier& Modifier, IPhysicsProxyBase* Proxy)`
- L395 _public function_ `virtual void Simulate(float DeltaTime, const FAllInputs& Inputs, FSimModuleTree& VehicleModuleSystem)` — The main Simulation function that is called from the physics async callback thread
- L400 _public function_ `virtual void Animate()` — Animate/modify the childToParent transforms, to say rotate a wheel, or rudder, etc
- L402 _public function_ `void SetAnimationEnabled(bool bInEnabled)`
- L403 _public function_ `bool IsAnimationEnabled()`
- L405 _public prototype_ `void SetAnimationData(const FName& BoneNameIn, const FVector& AnimationOffsetIn, int AnimationSetupIndexIn);`
- L406 _public function_ `const FSimModuleAnimationData& GetAnimationData() const`
- L407 _public function_ `const FVector& GetAnimationOffset() const`
- L408 _public function_ `const FName& GetBoneName() const`
- L409 _public function_ `int GetAnimationSetupIndex()`
- L414 _public function_ `virtual void DrawDebugInfo()` — Option to draw debug for this module requires CVar p.Chaos.DebugDraw.Enabled 1
- L419 _public prototype_ `virtual bool GetDebugString(FString& StringOut) const;` — Option to return debug text for drawing on the HUD in the Game Thread
- L424 _public function_ `void SetTransformIndex(int TransformIndexIn)` — The transform index references the transform collection, mapping the simulation module to the geometry collection data
- L425 _public function_ `const int GetTransformIndex() const`
- L430 _public function_ `void SetParticleIndex(FUniqueIdx ParticleIndexIn)` — The Particle unique index, should be valid on game and physics threads
- L431 _public function_ `const FUniqueIdx GetParticleIndex() const`
- L436 _public function_ `void SetTreeIndex(int TreeIndexIn)` — The modules own index in the simulation tree array
- L437 _public function_ `int GetTreeIndex() const`
- L442 _public function_ `void SetSimModuleTree(FSimModuleTree* SimModuleTreeIn)` — Very useful to store the simulation tree pointer in which we are stored, then we can access other modules that we reference through an index
- L448 _public prototype_ `void AddLocalForceAtPosition(const FVector& Force, const FVector& Position, bool bAllowSubstepping = true, bool bIsLocalForce = false, bool bLevelSlope = false, const FColor& DebugColorIn = FColor::Blue);` — Force application function, handles deferred force application and applying the force at the collect location based on whether the GC cluster is intact or fractured Note: forces are applied in local coordinates of the module
- L451 _public prototype_ `void AddForceAtCOMPosition(const FVector& Force, const FVector& OffsetFromCOM = FVector::ZeroVector, bool bAllowSubstepping = true, bool bLevelSlope = false, const FColor& DebugColorIn = FColor::Blue);`
- L457 _public prototype_ `void AddLocalForce(const FVector& Force, bool bAllowSubstepping = true, bool bIsLocalForce = false, bool bLevelSlope = false, const FColor& DebugColorIn = FColor::Blue);` — Force application function, handles deferred force application and applying the force at the collect location based on whether the GC cluster is intact or fractured Note: forces are applied in local coordinates of the module
- L463 _public prototype_ `void AddLocalTorque(const FVector& Torque, bool bAllowSubstepping = true, bool bAccelChangeIn = true, const FColor& DebugColorIn = FColor::Magenta);` — Torque application function Note: forces are applied in local coordinates of the module
- L470 _public function_ `void SetClustered(bool IsClusteredIn)` — Let the module know if it is still clustered or not
- L471 _public function_ `bool IsClustered() const`
- L476 _public function_ `void SetClusteredTransform(const FTransform& TransformIn)` — Set the COM relative transform of module when it is clustered, so relative to parent COM
- L477 _public function_ `const FTransform& GetClusteredTransform() const`
- L479 _public function_ `void SetInitialParticleTransform(const FTransform& TransformIn)`
- L480 _public function_ `const FTransform& GetInitialParticleTransform() const`
- L482 _public function_ `void SetComponentTransform(const FTransform& TransformIn)`
- L483 _public function_ `const FTransform& GetComponentTransform() const`
- L488 _public function_ `void SetIntactTransform(const FTransform& TransformIn)` — Set the COM relative transform of module when it is broken off, so relative to itself
- L489 _public function_ `const FTransform& GetIntactTransform() const`
- L490 _public member_ `bool IsInitialized = false;`
- L495 _public prototype_ `const FTransform& GetParentRelativeTransform() const;` — The modules transform relative to the simulating body will depend on whether the GC is intact (get the transform relative to intact cluster) or fractured (transform relative to fractured part)
- L500 _public function_ `void SetLocalLinearVelocity(const FVector& VelocityIn)` — Update the module with its current velocity
- L501 _public function_ `const FVector& GetLocalLinearVelocity() const`
- L502 _public function_ `void SetLocalAngularVelocity(const FVector& VelocityIn)`
- L503 _public function_ `const FVector& GetLocalAngularVelocity() const`
- L505 _public prototype_ `ISimulationModuleBase* GetParent();`
- L506 _public prototype_ `ISimulationModuleBase* GetFirstChild();`
- L508 _public prototype_ `FVehicleBlackboard* GetSimBlackboard();`
- L511 _public function_ `const FVector& GetAppliedForce()` — for headless chaos testing
- L514 _public prototype_ `virtual TSharedPtr<FModuleNetData> GenerateNetData(const int32 NodeArrayIndex) const = 0;` — this is the replication datas
- L516 _public function_ `virtual FSimOutputData* GenerateOutputData() const`
- L519 _public prototype_ `Chaos::FPBDRigidClusteredParticleHandle* GetClusterParticle(Chaos::FClusterUnionPhysicsProxy* Proxy);` — void SetClusterParticle(FPBDRigidClusteredParticleHandle* ParticleIn) { ClusterParticle = ParticleIn; }
- L521 _public prototype_ `Chaos::FPBDRigidParticleHandle* GetParticleFromUniqueIndex(int32 ParticleUniqueIdx, TArray<Chaos::FPBDRigidParticleHandle*>& Particles);`
- L525 _protected member_ `FSimModuleTree* SimModuleTree;` — A pointer back to the simulation tree where we are stored
- L526 _protected member_ `int SimTreeIndex;` — Index of this SimModule in the FSimModuleTree
- L527 _protected member_ `eSimModuleState StateFlags;` — TODO: make this more like flags
- L528 _protected member_ `int TransformIndex;` — Index of this Sim Module's node in Geometry Collection Transform array
- L529 _protected member_ `FUniqueIdx ParticleIdx;` — Physics particle unique index
- L531 _protected member_ `FTransform InitialParticleTransform;`
- L532 _protected member_ `FTransform RelativeOffsetTransform;`
- L533 _protected member_ `FTransform ComponentTransform;`
- L535 _protected member_ `FTransform ClusteredCOMRelativeTransform;`
- L536 _protected member_ `FTransform IntactCOMRelativeTransform;`
- L537 _protected member_ `FVector LocalLinearVelocity;`
- L538 _protected member_ `FVector LocalAngularVelocity;`
- L539 _protected member_ `bool bClustered;`
- L540 _protected member_ `bool bAnimationEnabled;`
- L541 _protected member_ `FVector AnimationOffset;`
- L542 _protected member_ `FSimModuleAnimationData AnimationData;`
- L545 _protected member_ `FVector AppliedForce;` — for headless chaos testing
- L546 _protected member_ `int Guid;` — needed a way of associating internal module with game thread.
- L548 _protected member_ `FPBDRigidClusteredParticleHandle* CachedParticle;`

#### struct `Chaos::FModuleNetData`  
`struct FModuleNetData : public FSimulationModuleTypeContainer, public TSimulationModuleTypeableBase<FModuleNetData>`  
_L554-588_
- inherits: `FSimulationModuleTypeContainer,TSimulationModuleTypeableBase<FModuleNetData>`
- desc: Interface base class for all module network serialization
- L556 _public prototype_ `DEFINE_CHAOSSIMTYPENAME(FModuleNetData);`
- L557 _public function_ `FModuleNetData(int InSimArrayIndex, const FString& InDebugString = FString()) : SimArrayIndex(InSimArrayIndex) #if !(UE_BUILD_SHIPPING || UE_BUILD_TEST) , DebugString(InDebugString) #endif`
- L564 _public prototype_ `virtual ~FModuleNetData() = default;`
- L566 _public prototype_ `virtual void Serialize(FArchive& Ar) = 0;`
- L567 _public function_ `virtual void DeltaSerialize(FArchive& Ar,const FModuleNetData* Previous)`
- L568 _public function_ `virtual void DeltaSerializeWithStash(FArchive& Ar,const FModuleNetData* Previous, TMap<FName,uint32>& InOutSerializationStash)`
- L569 _public prototype_ `virtual void FillNetState(const ISimulationModuleBase* SimModule) = 0;`
- L570 _public prototype_ `virtual void FillSimState(ISimulationModuleBase* SimModule) = 0;`
- L571 _public prototype_ `virtual void Lerp(const float LerpFactor, const FModuleNetData& Max, const FModuleNetData& MaxValue) = 0;`
- L577 _public function_ `virtual bool IsDefaultState()` — Return true if the current state of this module is the default state, If the state is default it will not be sent over the network, instead ApplyDefaultState() will be called on the receiving end to apply the default state for this module. Important: Be sure to also implement ApplyDefaultState() function to ensure that the data gets set to their desired values when not serialized. Example: bools that are false or true by default and floats that are 0.0f doesn't need to be networked
- L580 _public function_ `virtual void ApplyDefaultState()` — Set the states data to default values, called during deserialization if IsDefaultState() was true during serialization
- L582 _public member_ `int SimArrayIndex = -1;`
- L585 _public prototype_ `virtual FString ToString() const = 0;`
- L586 _public member_ `FString DebugString;`

#### struct `Chaos::FSimOutputData`  
`struct FSimOutputData : public FSimulationModuleTypeContainer, public TSimulationModuleTypeableBase<FSimOutputData>`  
_L592-612_
- inherits: `FSimulationModuleTypeContainer,TSimulationModuleTypeableBase<FSimOutputData>`
- L594 _public prototype_ `DEFINE_CHAOSSIMTYPENAME(FSimOutputData);`
- L595 _public prototype_ `FSimOutputData() = default;`
- L596 _public prototype_ `virtual ~FSimOutputData() = default;`
- L598 _public function_ `virtual bool IsEnabled()`
- L599 _public prototype_ `virtual FSimOutputData* MakeNewData() = 0;`
- L600 _public prototype_ `virtual void FillOutputState(const ISimulationModuleBase* SimModule);`
- L601 _public prototype_ `virtual void Lerp(const FSimOutputData& InCurrent, const FSimOutputData& InNext, float Alpha);`
- L602 _public function_ `virtual void GetFinalAnimDataGameThread(const FTransform& NewTransform, Chaos::FSimModuleAnimationData& AnimDataOut)`
- L604 _public member_ `bool bEnabled = true;`
- L605 _public member_ `FSimModuleAnimationData AnimationData;`
- L606 _public member_ `int ModuleGuid = -1;`
- L609 _public function_ `virtual FString ToString()`
- L610 _public member_ `FString DebugString;`

#### class `Chaos::IFactoryModule`  
`class IFactoryModule : public FSimulationModuleTypeContainer, public TSimulationModuleTypeableBase<IFactoryModule>`  
_L614-621_
- inherits: `FSimulationModuleTypeContainer,TSimulationModuleTypeableBase<IFactoryModule>`
- L617 _public prototype_ `DEFINE_CHAOSSIMTYPENAME(IFactoryModule);`
- L618 _public prototype_ `virtual ~IFactoryModule() = default;`
- L619 _public prototype_ `virtual TSharedPtr<Chaos::FModuleNetData> GenerateNetData(const int32 SimArrayIndex) const = 0;`

#### class `Chaos::TSimFactoryAutoRegister`  
`template<typename _To> class TSimFactoryAutoRegister`  
_L624-628_
- L627 _private member_ `inline static bool bSimFactoryRegistered = RegisterFactoryHelper<_To>();`

#### class `Chaos::FSimFactoryModule`  
`template <typename T> class FSimFactoryModule : public IFactoryModule`  
_L631-655_
- inherits: `IFactoryModule`
- L634 _public function_ `FSimFactoryModule(const FString& DebugNameIn)`
- L641 _public function_ `TSharedPtr<Chaos::FModuleNetData> GenerateNetData(const int32 SimArrayIndex) const override`
- L652 _public member_ `FString DebugString;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API CHAOSVEHICLESCORE_API`
- L15 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogSimulationModule, Warning, All);`
- L15 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSimulationModule, Warning, All);`
- L17 _macro_ `#define TSIMMODULETYPEABLE(clazz) Chaos::TSimulationModuleTypeableExt<clazz,&FName(#clazz)>`
- L28 _namespace_ `namespace Chaos`
- L36 _variable_ `const FName HandbrakeControlName("Han` (scope `Chaos`)
- L37 _variable_ `const FName ThrottleControlName("Thr` (scope `Chaos`)
- L38 _variable_ `const FName SteeringControlName("Ste` (scope `Chaos`)
- L39 _variable_ `const FName BrakeControlName("Bra` (scope `Chaos`)
- L40 _variable_ `const FName ClutchControlName("Clu` (scope `Chaos`)
- L41 _variable_ `const FName BoostControlName("Boo` (scope `Chaos`)
- L42 _variable_ `const FName ReverseControlName("Rev` (scope `Chaos`)
- L43 _variable_ `const FName ChangeUpControlName("Cha` (scope `Chaos`)
- L44 _variable_ `const FName ChangeDownControlName("Cha` (scope `Chaos`)
- L45 _variable_ `const FName PitchControlName("Pit` (scope `Chaos`)
- L46 _variable_ `const FName RollControlName("Rol` (scope `Chaos`)
- L47 _variable_ `const FName YawControlName("Yaw` (scope `Chaos`)
- L49 _namespace_ `namespace EAnimationFlags` (scope `Chaos`)
- L51 _variable_ `static uint16 AnimateNone = 0x00000000;` (scope `Chaos::EAnimationFlags`)
- L52 _variable_ `static uint16 AnimatePosition = 0x00000001;` (scope `Chaos::EAnimationFlags`)
- L53 _variable_ `static uint16 AnimateRotation = 0x00000002;` (scope `Chaos::EAnimationFlags`)
- L250 _variable_ `template<class T> constexpr bool TSimModuleTypeIsRecursive_v = TSimModuleTypeIsRecursive<T>::value;` (scope `Chaos`)
- L315 _macro_ `#define DEFINE_CHAOSSIMTYPENAME(cls) \`
- L590 _typedef_ `using FModuleNetDataArray = TArray<TSharedPtr<FModuleNetData>>;` (scope `Chaos`)

### `Source/Runtime/Experimental/ChaosVehicles/ChaosVehiclesCore/Public/SimModule/SuspensionBaseInterface.h` (Public)


#### struct `Chaos::FSpringTrace`  
`struct FSpringTrace`  
_L14-30_
- desc: Suspension world ray/shape trace start and end positions
- L16 _public member_ `FVector Start;`
- L17 _public member_ `FVector End;`
- L19 _public function_ `FVector TraceDir()`
- L25 _public function_ `float Length()`

#### struct `Chaos::FSuspensionTargetPoint`  
`struct FSuspensionTargetPoint`  
_L33-53_
- desc: Suspension target point data.
- L35 _public function_ `FSuspensionTargetPoint()`
- L37 _public function_ `FSuspensionTargetPoint(const FVector& InTargetPosition, const FVector& InImpactNormal, const float InHitDistance, const bool bInWheelInContact, const TEnumAsByte<EPhysicalSurface> InSurfaceType, IPhysicsProxyBase* InHitProxy) : TargetPosition(InTargetPosition) , ImpactNormal(InImpactNormal) , HitDistance(InHitDistance) , bWheelInContact(bInWheelInContact) , SurfaceType(InSurfaceType) , HitProxy(InHitProxy)`
- L47 _public member_ `FVector TargetPosition = FVector::ZeroVector;`
- L48 _public member_ `FVector ImpactNormal = FVector::ZeroVector;`
- L49 _public member_ `float HitDistance = 0.0f;`
- L50 _public member_ `bool bWheelInContact = false;`
- L51 _public member_ `TEnumAsByte<EPhysicalSurface> SurfaceType = EPhysicalSurface::SurfaceType_Default;`
- L52 _public member_ `IPhysicsProxyBase* HitProxy = nullptr;`

#### class `Chaos::FSuspensionBaseInterface`  
`class FSuspensionBaseInterface : public ISimulationModuleBase , public TSimulationModuleTypeable<FSuspensionBaseInterface>`  
_L55-102_
- inherits: `ISimulationModuleBase,TSimulationModuleTypeable<FSuspensionBaseInterface>`
- L61 _public prototype_ `DEFINE_CHAOSSIMTYPENAME(FSuspensionBaseInterface);`
- L62 _public function_ `FSuspensionBaseInterface()`
- L64 _public prototype_ `virtual ~FSuspensionBaseInterface() = default;`
- L66 _public prototype_ `virtual bool IsBehaviourType(eSimModuleTypeFlags InType) const override;`
- L68 _public prototype_ `virtual float GetMaxSpringLength() const = 0;`
- L70 _public prototype_ `virtual float GetSpringLength() const = 0;`
- L71 _public prototype_ `virtual void SetSpringLength(float InLength, float WheelRadius) = 0;`
- L72 _public prototype_ `virtual void GetWorldTraceEndpoints(float DeltaSeconds, const FTransform& BodyTransform, const FVector& Velocity, float WheelRadius, FSpringTrace& OutTrace) const = 0;`
- L73 _public prototype_ `void SetTargetPoint(const FSuspensionTargetPoint& InTargetPoint);`
- L74 _public function_ `const FSuspensionTargetPoint& GetTargetPoint() const`
- L75 _public function_ `bool IsWheelInContact() const`
- L77 _public function_ `void SetWheelSimTreeIndex(int WheelTreeIndexIn)`
- L78 _public function_ `int GetWheelSimTreeIndex() const`
- L80 _public function_ `TEnumAsByte<EPhysicalSurface> GetSurfaceType() const`
- L82 _public function_ `void SetImpactNormal(const FVector& NewValue)`
- L83 _public function_ `const FVector& GetImpactNormal() const`
- L85 _public function_ `void SetHitDistance(const float NewValue)`
- L86 _public function_ `float GetHitDistance() const`
- L88 _public function_ `void SetTargetPosition(const FVector& NewValue)`
- L89 _public function_ `const FVector& GetTargetPosition() const`
- L91 _public function_ `void SetHitProxy(IPhysicsProxyBase* NewValue)`
- L92 _public function_ `const IPhysicsProxyBase* GetHitProxy() const`
- L93 _public function_ `IPhysicsProxyBase* GetHitProxy()`
- L97 _protected member_ `int WheelSimTreeIndex = INVALID_IDX;`
- L101 _private member_ `FSuspensionTargetPoint TargetPoint;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API CHAOSVEHICLESCORE_API`
- L10 _namespace_ `namespace Chaos`

### `Source/Runtime/Experimental/ChaosVehicles/ChaosVehiclesCore/Public/SimModule/ThrusterModule.h` (Public)


#### struct `Chaos::FThrusterSettings`  
`struct FThrusterSettings`  
_L18-43_
- desc: <summary> Thruster settings </summary>
- L20 _public function_ `FThrusterSettings() : MaxThrustForce(0) , ForceAxis(FVector(1.0f, 0.0f, 0.0f)) , SteeringAxis(FVector(0.0f, 0.0f, 1.0f)) , ForceOffset(FVector::ZeroVector) , MaxSteeringAngle(0) , SteeringForceEffect(1.0f) , BoostMultiplier(2.0f) , MaxSpeed(125.0f) , SteeringEnabled(false)`
- L34 _public member_ `float MaxThrustForce;`
- L35 _public member_ `FVector ForceAxis;`
- L36 _public member_ `FVector SteeringAxis;`
- L37 _public member_ `FVector ForceOffset;`
- L38 _public member_ `float MaxSteeringAngle;`
- L39 _public member_ `float SteeringForceEffect;`
- L40 _public member_ `float BoostMultiplier;`
- L41 _public member_ `float MaxSpeed;`
- L42 _public member_ `bool SteeringEnabled;`

#### class `Chaos::FThrusterSimModule`  
`class FThrusterSimModule : public ISimulationModuleBase, public TSimModuleSettings<FThrusterSettings>, public TSimulationModuleTypeable<FThrusterSimModule>`  
_L49-69_
- inherits: `ISimulationModuleBase,TSimModuleSettings<FThrusterSettings>,TSimulationModuleTypeable<FThrusterSimModule>`
- desc: </summary>
- L52 _public prototype_ `DEFINE_CHAOSSIMTYPENAME(FThrusterSimModule);`
- L53 _public prototype_ `FThrusterSimModule(const FThrusterSettings& Settings);`
- L55 _public function_ `virtual TSharedPtr<FModuleNetData> GenerateNetData(const int32 NodeArrayIndex) const override`
- L57 _public function_ `virtual const FString GetDebugName() const`
- L59 _public function_ `virtual bool IsBehaviourType(eSimModuleTypeFlags InType) const override`
- L61 _public prototype_ `virtual void Simulate(float DeltaTime, const FAllInputs& Inputs, FSimModuleTree& VehicleModuleSystem) override;`
- L63 _public prototype_ `virtual void Animate() override;`
- L65 _public function_ `float GetSteerAngleDegrees() const`
- L68 _private member_ `float SteerAngleDegrees;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API CHAOSVEHICLESCORE_API`
- L10 _namespace_ `namespace Chaos`

### `Source/Runtime/Experimental/ChaosVehicles/ChaosVehiclesCore/Public/SimModule/TorqueSimModule.h` (Public)


#### struct `Chaos::FTorqueSimModuleData`  
`struct FTorqueSimModuleData : public FModuleNetData , public Chaos::TSimulationModuleTypeable<FTorqueSimModule,FTorqueSimModuleData>`  
_L14-48_
- inherits: `FModuleNetData,Chaos::TSimulationModuleTypeable<FTorqueSimModule,FTorqueSimModuleData>`
- L19 _public function_ `FTorqueSimModuleData(int NodeArrayIndex, const FString& InDebugString) : FModuleNetData(NodeArrayIndex, InDebugString)`
- L24 _public prototype_ `virtual void FillSimState(ISimulationModuleBase* SimModule) override;`
- L26 _public prototype_ `virtual void FillNetState(const ISimulationModuleBase* SimModule) override;`
- L28 _public function_ `virtual void Serialize(FArchive& Ar) override`
- L37 _public prototype_ `virtual void Lerp(const float LerpFactor, const FModuleNetData& Min, const FModuleNetData& Max) override;`
- L40 _public prototype_ `virtual FString ToString() const override;`
- L43 _public member_ `float AngularVelocity = 0.0f;`
- L44 _public member_ `float AngularPosition = 0.0f;`
- L45 _public member_ `float DriveTorque = 0.0f;`
- L46 _public member_ `float LoadTorque = 0.0f;`
- L47 _public member_ `float BrakingTorque = 0.0f;`

#### class `Chaos::FTorqueSimModule`  
`class FTorqueSimModule : public ISimulationModuleBase, public TSimulationModuleTypeable<FTorqueSimModule>`  
_L51-121_
- inherits: `ISimulationModuleBase,TSimulationModuleTypeable<FTorqueSimModule>`
- L56 _public prototype_ `DEFINE_CHAOSSIMTYPENAME(FTorqueSimModule);`
- L57 _public function_ `FTorqueSimModule() : DriveTorque(0.f) , LoadTorque(0.f) , BrakingTorque(0.f) , AngularVelocity(0.f) , AngularPosition(0.0f)`
- L69 _public function_ `virtual bool IsBehaviourType(eSimModuleTypeFlags InType) const` — Is Module of a specific type - used for casting
- L71 _public function_ `void SetDriveTorque(float TorqueIn)`
- L72 _public function_ `float GetDriveTorque() const`
- L74 _public function_ `void SetLoadTorque(float TorqueIn)`
- L75 _public function_ `float GetLoadTorque() const`
- L77 _public function_ `void SetBrakingTorque(float TorqueIn)`
- L78 _public function_ `float GetBrakingTorque() const`
- L80 _public function_ `void SetAngularVelocity(float AngularVelocityIn)`
- L81 _public function_ `float GetAngularVelocity() const`
- L83 _public function_ `void AddAngularVelocity(float AngularVelocityIn)`
- L85 _public function_ `void SetAngularPosition(float AngularPositionIn)`
- L86 _public function_ `float GetAngularPosition() const`
- L88 _public function_ `void SetRPM(float InRPM)`
- L89 _public function_ `float GetRPM() const`
- L94 _public prototype_ `void TransmitTorque(const FSimModuleTree& BlockSystem, float PushedTorque, float BrakeTorque = 0.f, float GearingRatio = 1.0f, float ClutchSlip = 1.0f);` — Transmit torque between this module and its Parent and Children. DriveTorque passed down to children, LoadTorque passed from child to parent
- L99 _public prototype_ `void IntegrateAngularVelocity(float DeltaTime, float Inertia, float MaxRotationVel = MAX_FLT);` — Integrate angular velocity using specified DeltaTime & Inertia value, Note the inertia should be the combined inertia of all the connected pieces otherwise things will rotate at different rates
- L104 _public function_ `static FTorqueSimModule* CastToTorqueInterface(ISimulationModuleBase* SimModule)` — Cast an ISimulationModuleBase to a FTorqueSimModule if compatible class
- L116 _protected member_ `float DriveTorque;`
- L117 _protected member_ `float LoadTorque;`
- L118 _protected member_ `float BrakingTorque;`
- L119 _protected member_ `float AngularVelocity;`
- L120 _protected member_ `float AngularPosition;`

#### class `Chaos::FWheelBaseInterface`  
`class FWheelBaseInterface : public FTorqueSimModule, public TSimulationModuleTypeable<FWheelBaseInterface>`  
_L123-161_
- inherits: `FTorqueSimModule,TSimulationModuleTypeable<FWheelBaseInterface>`
- L126 _public prototype_ `DEFINE_CHAOSSIMTYPENAME(FWheelBaseInterface);`
- L128 _public function_ `FWheelBaseInterface() : SuspensionSimTreeIndex(ISimulationModuleBase::INVALID_IDX) , SurfaceFriction(1.0f) , ForceIntoSurface(0.0f)`
- L134 _public function_ `void SetSuspensionSimTreeIndex(int IndexIn)`
- L135 _public function_ `int GetSuspensionSimTreeIndex() const`
- L136 _public function_ `void SetSurfaceFriction(float FrictionIn)`
- L137 _public function_ `void SetForceIntoSurface(float ForceIntoSurfaceIn)`
- L138 _public function_ `float GetForceIntoSurface() const`
- L139 _public function_ `float GetSurfaceFriction() const`
- L140 _public function_ `void SetGroundInteraction(Chaos::FPBDRigidParticleHandle* GroundParticleIn, const FVector& ImpactPointIn, const FVector& ImpactNormalIn)`
- L147 _public function_ `Chaos::FPBDRigidParticleHandle* GetGroundBody() const`
- L148 _public function_ `void ClearGroundBody()`
- L149 _public function_ `FVector GetImpactPoint() const`
- L150 _public function_ `FVector GetImpactNormal() const`
- L151 _public prototype_ `virtual float GetWheelRadius() const = 0;`
- L154 _protected member_ `int SuspensionSimTreeIndex;`
- L155 _protected member_ `float SurfaceFriction;`
- L156 _protected member_ `float ForceIntoSurface;`
- L157 _protected member_ `Chaos::FPBDRigidParticleHandle* GroundBody = nullptr;`
- L158 _protected member_ `FVector ImpactPoint = FVector::ZeroVector;`
- L159 _protected member_ `FVector ImpactNormal = FVector(0,0,1);`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API CHAOSVEHICLESCORE_API`
- L10 _namespace_ `namespace Chaos`

### `Source/Runtime/Experimental/ChaosVehicles/ChaosVehiclesCore/Public/SimModule/TransmissionModule.h` (Public)


#### struct `Chaos::FTransmissionSimModuleData`  
`struct FTransmissionSimModuleData : public FModuleNetData , public Chaos::TSimulationModuleTypeable<FTransmissionSimModule,FTransmissionSimModuleData>`  
_L16-46_
- inherits: `FModuleNetData,Chaos::TSimulationModuleTypeable<FTransmissionSimModule,FTransmissionSimModuleData>`
- L21 _public function_ `FTransmissionSimModuleData(int NodeArrayIndex, const FString& InDebugString) : FModuleNetData(NodeArrayIndex, InDebugString)`
- L26 _public prototype_ `virtual void FillSimState(ISimulationModuleBase* SimModule) override;`
- L28 _public prototype_ `virtual void FillNetState(const ISimulationModuleBase* SimModule) override;`
- L30 _public function_ `virtual void Serialize(FArchive& Ar) override`
- L37 _public prototype_ `virtual void Lerp(const float LerpFactor, const FModuleNetData& Min, const FModuleNetData& Max) override;`
- L40 _public prototype_ `virtual FString ToString() const override;`
- L43 _public member_ `int32 CurrentGear = 0;`
- L44 _public member_ `int32 TargetGear = 0;`
- L45 _public member_ `float CurrentGearChangeTime = 0.0f;`

#### struct `Chaos::FGearChangeEvent`  
`struct FGearChangeEvent`  
_L48-53_
- L50 _public function_ `FGearChangeEvent(int32 InGear) : ChangedToGear(InGear)`
- L52 _public member_ `int32 ChangedToGear = 0;`

#### struct `Chaos::FTransmissionOutputData`  
`struct FTransmissionOutputData : public FSimOutputData , public Chaos::TSimulationModuleTypeable<FTransmissionSimModule,FTransmissionOutputData>`  
_L55-71_
- inherits: `FSimOutputData,Chaos::TSimulationModuleTypeable<FTransmissionSimModule,FTransmissionOutputData>`
- L59 _public function_ `virtual FSimOutputData* MakeNewData() override`
- L60 _public function_ `static FSimOutputData* MakeNew()`
- L62 _public prototype_ `virtual void FillOutputState(const ISimulationModuleBase* SimModule) override;`
- L63 _public prototype_ `virtual void Lerp(const FSimOutputData& InCurrent, const FSimOutputData& InNext, float Alpha) override;`
- L66 _public prototype_ `virtual FString ToString() override;`
- L69 _public member_ `int32 CurrentGear;`
- L70 _public member_ `TArray<FGearChangeEvent> GearChangeEvents;`

#### struct `Chaos::FTransmissionSettings`  
`struct FTransmissionSettings`  
_L73-113_
- L81 _public function_ `FTransmissionSettings() : FinalDriveRatio(3.f) , ChangeUpRPM(5000) , ChangeDownRPM(2500) , GearChangeTime(0.5f) , GearHysteresisTime(2.0f) , TransmissionEfficiency(1.f) , TransmissionType(ETransType::AutomaticType) , AutoReverse(true)`
- L99 _public member_ `TArray<float> ForwardRatios;` — Gear ratios for forward gears
- L100 _public member_ `TArray<float> ReverseRatios;` — Gear ratios for reverse Gear(s)
- L101 _public member_ `float FinalDriveRatio;` — Final drive ratio [~4.0]
- L103 _public member_ `uint32 ChangeUpRPM;` — [RPM]
- L104 _public member_ `uint32 ChangeDownRPM;` — [RPM]
- L105 _public member_ `float GearChangeTime;` — [sec]
- L106 _public member_ `float GearHysteresisTime;` — [sec]
- L108 _public member_ `float TransmissionEfficiency;` — Loss from friction in the system mean we might run at around 0.94 Efficiency
- L110 _public member_ `ETransType TransmissionType;` — Specify Automatic or Manual transmission
- L112 _public member_ `bool AutoReverse;` — Arcade handling - holding Brake switches into reverse after vehicle has stopped

#### enum `Chaos::FTransmissionSettings::ETransType`  
`enum ETransType : uint8`  
_L75-79_
- L77 _public enumerator_ `ManualType`
- L78 _public enumerator_ `AutomaticType`

#### class `Chaos::FTransmissionSimModule`  
`class FTransmissionSimModule : public FTorqueSimModule, public TSimModuleSettings<FTransmissionSettings>, public TSimulationModuleTypeable<FTransmissionSimModule>`  
_L115-191_
- inherits: `FTorqueSimModule,TSimModuleSettings<FTransmissionSettings>,TSimulationModuleTypeable<FTransmissionSimModule>`
- L121 _public prototype_ `DEFINE_CHAOSSIMTYPENAME(FTransmissionSimModule);`
- L122 _public prototype_ `FTransmissionSimModule(const FTransmissionSettings& Settings);`
- L124 _public function_ `virtual TSharedPtr<FModuleNetData> GenerateNetData(const int32 SimArrayIndex) const override`
- L134 _public function_ `virtual FSimOutputData* GenerateOutputData() const override`
- L139 _public function_ `virtual const FString GetDebugName() const`
- L141 _public prototype_ `virtual bool GetDebugString(FString& StringOut) const override;`
- L143 _public function_ `virtual bool IsBehaviourType(eSimModuleTypeFlags InType) const override`
- L145 _public prototype_ `virtual void Simulate(float DeltaTime, const FAllInputs& Inputs, FSimModuleTree& VehicleModuleSystem) override;`
- L152 _protected prototype_ `void SetGear(int32 InGear, bool Immediate = false);` — set the target gear number to change to, can change gear immediately if specified i.e. rather than waiting for the gear change time to elapse
- L155 _protected prototype_ `float GetGearRatio(int32 InGear) const;` — Get the final combined gear ratio for the specified gear (reverse gears < 0, neutral 0, forward gears > 0)
- L158 _protected function_ `void ChangeUp()` — set the target gear to one higher than current target, will clamp gear index within rage
- L164 _protected function_ `void ChangeDown()` — set the target gear to one lower than current target, will clamp gear index within rage
- L170 _protected function_ `bool IsCurrentlyChangingGear() const` — Are we currently in the middle of a gear change
- L175 _protected function_ `void CorrectGearInputRange(int32& GearIndexInOut) const`
- L180 _protected function_ `int32 GetCurrentGear()`
- L181 _protected function_ `int32 GetTargetGear()`
- L184 _private member_ `int32 CurrentGear;` — <0 reverse gear(s), 0 neutral, >0 forward gears
- L185 _private member_ `int32 TargetGear;` — <0 reverse gear(s), 0 neutral, >0 forward gears
- L186 _private member_ `float CurrentGearChangeTime;` — Time to change gear, no power transmitted to the wheels during change
- L187 _private member_ `mutable int32 PreviousGear;`
- L189 _private member_ `bool AllowedToChangeGear;` — conditions are ok for an automatic gear change
- L190 _private member_ `float GearHysteresisTimer;`

#### class `Chaos::FTransmissionSimFactory`  
`class FTransmissionSimFactory : public FSimFactoryModule<FTransmissionSimModuleData> , public TSimulationModuleTypeable<FTransmissionSimModule,FTransmissionSimFactory> , public TSimFactoryAutoRegister<FTransmissionSimFactory>`  
_L193-201_
- inherits: `FSimFactoryModule<FTransmissionSimModuleData>,TSimulationModuleTypeable<FTransmissionSimModule,FTransmissionSimFactory>,TSimFactoryAutoRegister<FTransmissionSimFactory>`
- L200 _public function_ `FTransmissionSimFactory() : FSimFactoryModule(TEXT("Tran`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API CHAOSVEHICLESCORE_API`
- L10 _namespace_ `namespace Chaos`

### `Source/Runtime/Experimental/ChaosVehicles/ChaosVehiclesCore/Public/SimModule/VehicleBlackboard.h` (Public)


#### class `FVehicleBlackboard`  
`class FVehicleBlackboard`  
_L18-109_
- desc: VehicleBlackboard: this is a simple generic map that can store any type, used as a way for decoupled modules to share calculations or transient state data (on the physics thread only). Values submitted are copy-in, copy-out. Unlike a traditional blackboard pattern, there is no support for subscribing to changes.
- L73 _public function_ `template<typename T> bool TryGet(FName ObjName, T& OutFoundValue) const` — Attempt to retrieve an object from the blackboard. If found, OutFoundValue will be set. Returns true/false to indicate whether it was found.
- L85 _public function_ `bool Contains(FName ObjName)` — Returns true/false to indicate if an object is stored with that name
- L92 _public function_ `template<typename T> void Set(FName ObjName, T Obj)` — Store object by a named key, overwriting any existing object
- L98 _public prototype_ `void Invalidate(FName ObjName);` — Invalidate an object by name
- L101 _public prototype_ `void Invalidate(EInvalidationReason Reason);` — Invalidate all objects that can be affected by a particular circumstance (such as a rollback)
- L104 _public function_ `void InvalidateAll()` — Invalidate all objects
- L108 _private member_ `TMap<FName, TSharedPtr<BlackboardObject>> ObjectsByName;`

#### class `FVehicleBlackboard::BlackboardObject`  
`class BlackboardObject`  
_L21-62_
- L44 _public function_ `template<typename T> BlackboardObject(const T& obj) : ContainerPtr(MakeShared<ObjectContainer<T>>(obj))`
- L47 _public function_ `template<typename T> const T& Get() const`
- L54 _public function_ `template<typename T> T& GetMutable() const`
- L61 _private member_ `TSharedPtr<ObjectContainerBase> ContainerPtr;`

#### struct `FVehicleBlackboard::BlackboardObject::ObjectContainerBase`  
`struct ObjectContainerBase`  
_L24-26_
- desc: untyped base

#### struct `FVehicleBlackboard::BlackboardObject::ObjectContainer`  
`template<typename T> struct ObjectContainer : ObjectContainerBase`  
_L30-39_
- inherits: `ObjectContainerBase`
- desc: typed container
- L32 _public function_ `ObjectContainer(const T& t) : Object(t)`
- L34 _public function_ `const T& Get()`
- L35 _public function_ `T& GetMutable()`
- L38 _private member_ `T Object;`

#### enum `FVehicleBlackboard::EInvalidationReason`  
`enum class EInvalidationReason : uint8`  
_L65-69_
- L67 _public enumerator_ `FullReset` — All blackboard objects should be invalidated
- L68 _public enumerator_ `Rollback` — Invalidate any rollback-sensitive objects

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CHAOSVEHICLESCORE_API`

### `Source/Runtime/Experimental/ChaosVehicles/ChaosVehiclesCore/Public/SimModule/WheelModule.h` (Public)


#### struct `Chaos::FWheelSimModuleData`  
`struct FWheelSimModuleData : public FTorqueSimModuleData , public Chaos::TSimulationModuleTypeable<class FWheelSimModule,FWheelSimModuleData>`  
_L16-38_
- inherits: `FTorqueSimModuleData,Chaos::TSimulationModuleTypeable<classFWheelSimModule,FWheelSimModuleData>`
- L21 _public function_ `FWheelSimModuleData(int NodeArrayIndex, const FString& InDebugString) : FTorqueSimModuleData(NodeArrayIndex, InDebugString)`
- L26 _public function_ `virtual void FillSimState(ISimulationModuleBase* SimModule) override`
- L32 _public function_ `virtual void FillNetState(const ISimulationModuleBase* SimModule) override`

#### struct `Chaos::FWheelTouchChangeEvent`  
`struct FWheelTouchChangeEvent`  
_L40-45_
- L42 _public function_ `FWheelTouchChangeEvent(bool IsInContact) : bIsInContact(IsInContact)`
- L44 _public member_ `bool bIsInContact = 0;`

#### struct `Chaos::FWheelOutputData`  
`struct FWheelOutputData : public FSimOutputData , public Chaos::TSimulationModuleTypeable<class FWheelSimModule,FWheelOutputData>`  
_L47-69_
- inherits: `FSimOutputData,Chaos::TSimulationModuleTypeable<classFWheelSimModule,FWheelOutputData>`
- L51 _public function_ `virtual FSimOutputData* MakeNewData() override`
- L52 _public function_ `static FSimOutputData* MakeNew()`
- L54 _public prototype_ `virtual void FillOutputState(const ISimulationModuleBase* SimModule) override;`
- L55 _public prototype_ `virtual void Lerp(const FSimOutputData& InCurrent, const FSimOutputData& InNext, float Alpha) override;`
- L58 _public prototype_ `virtual FString ToString() override;`
- L61 _public member_ `bool bTouchingGround;`
- L62 _public member_ `float ForceIntoSurface;`
- L63 _public member_ `float SlipAngle;`
- L64 _public member_ `float RPM;`
- L65 _public member_ `float AngularPositionDegrees;`
- L66 _public member_ `float SteeringAngleDegrees;`
- L68 _public member_ `TArray<FWheelTouchChangeEvent> WheelTouchEvents;`

#### struct `Chaos::FWheelSettings`  
`struct FWheelSettings`  
_L71-127_
- L73 _public function_ `FWheelSettings() : Radius(30.0f) , Width(20.0f) , WheelInertia(100.0f) , FrictionMultiplier(3.0f) , LateralSlipGraphMultiplier(1.0f) , CorneringStiffness(1000.0f) , SlipAngleLimit(8.0f) , SlipModifier(0.9f) , ABSEnabled(true) , TractionControlEnabled(true) , SteeringEnabled(false) , HandbrakeEnabled(false) , AutoHandbrakeEnabled(false) , AutoHandbrakeVelocityThreshold(10.0f) , MaxSteeringAngle(45) , MaxBrakeTorque(4000) , HandbrakeTorque(3000) , MaxRotationVel(100.0f) , Axis(EWheelAxis::X) , ReverseDirection(false) , ForceOffset(FVector::ZeroVector)`
- L100 _public member_ `float Radius;`
- L101 _public member_ `float Width;`
- L102 _public member_ `float WheelInertia;`
- L104 _public member_ `float FrictionMultiplier;`
- L105 _public member_ `float LateralSlipGraphMultiplier;`
- L106 _public member_ `float CorneringStiffness;`
- L107 _public member_ `FGraph LateralSlipGraph;`
- L108 _public member_ `float SlipAngleLimit;`
- L109 _public member_ `float SlipModifier;`
- L111 _public member_ `bool ABSEnabled;` — Advanced braking system operational
- L112 _public member_ `bool TractionControlEnabled;` — Straight Line Traction Control
- L113 _public member_ `bool SteeringEnabled;`
- L114 _public member_ `bool HandbrakeEnabled;`
- L115 _public member_ `bool AutoHandbrakeEnabled;`
- L116 _public member_ `float AutoHandbrakeVelocityThreshold;`
- L118 _public member_ `float MaxSteeringAngle;`
- L119 _public member_ `float MaxBrakeTorque;`
- L120 _public member_ `float HandbrakeTorque;`
- L122 _public member_ `float MaxRotationVel;`
- L123 _public member_ `EWheelAxis Axis;`
- L124 _public member_ `bool ReverseDirection;`
- L125 _public member_ `FVector ForceOffset;`

#### class `Chaos::FWheelSimModule`  
`class FWheelSimModule : public FWheelBaseInterface, public TSimModuleSettings<FWheelSettings>, public TSimulationModuleTypeable<FWheelSimModule>`  
_L129-198_
- inherits: `FWheelBaseInterface,TSimModuleSettings<FWheelSettings>,TSimulationModuleTypeable<FWheelSimModule>`
- L133 _public prototype_ `DEFINE_CHAOSSIMTYPENAME(FWheelSimModule);`
- L134 _public prototype_ `FWheelSimModule(const FWheelSettings& Settings);`
- L136 _public function_ `virtual TSharedPtr<FModuleNetData> GenerateNetData(const int32 SimArrayIndex) const override`
- L146 _public function_ `virtual FSimOutputData* GenerateOutputData() const override`
- L151 _public function_ `virtual const FString GetDebugName() const`
- L153 _public prototype_ `virtual bool GetDebugString(FString& StringOut) const override;`
- L155 _public prototype_ `virtual void Simulate(float DeltaTime, const FAllInputs& Inputs, FSimModuleTree& VehicleModuleSystem) override;`
- L157 _public prototype_ `virtual void Animate() override;`
- L159 _public function_ `virtual bool IsBehaviourType(eSimModuleTypeFlags InType) const override`
- L161 _public function_ `virtual float GetWheelRadius() const override`
- L163 _public function_ `float GetSteerAngleDegrees() const`
- L165 _public function_ `FVector GetForceFromFriction() const`
- L169 _public function_ `void SetLinearSpeed(float LinearMetersPerSecondIn)` — set wheel rotational speed to match the specified linear forwards speed
- L175 _public function_ `float GetLinearSpeed()` — get linear forwards speed from angluar velocity and wheel radius
- L181 _public function_ `float GetEffectiveRadius() const` — Get the radius of the wheel [cm]
- L188 _private member_ `float BrakeTorque;` — [N.m]
- L190 _private member_ `FVector ForceFromFriction;`
- L191 _private member_ `float MassPerWheel;`
- L192 _private member_ `float SteerAngleDegrees;`
- L195 _private member_ `bool bTouchingGround;` — for output
- L196 _private member_ `mutable bool bPrevTouchingGround;`
- L197 _private member_ `float SlipAngle;`

#### class `Chaos::FWheelSimFactory`  
`class FWheelSimFactory : public FSimFactoryModule<FWheelSimModuleData> , public TSimulationModuleTypeable<FWheelSimModule,FWheelSimFactory> , public TSimFactoryAutoRegister<FWheelSimFactory>`  
_L201-209_
- inherits: `FSimFactoryModule<FWheelSimModuleData>,TSimulationModuleTypeable<FWheelSimModule,FWheelSimFactory>,TSimFactoryAutoRegister<FWheelSimFactory>`
- L208 _public function_ `FWheelSimFactory() : FSimFactoryModule(TEXT("Whee`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API CHAOSVEHICLESCORE_API`
- L9 _namespace_ `namespace Chaos`

### `Source/Runtime/Experimental/ChaosVehicles/ChaosVehiclesCore/Public/SimpleVehicle.h` (Public)


#### class `Chaos::IVehicleInterface`  
`class IVehicleInterface`  
_L25-29_

#### class `Chaos::FSimpleWheeledVehicle`  
`class FSimpleWheeledVehicle : public IVehicleInterface`  
_L35-190_
- inherits: `IVehicleInterface`
- desc: This class is currently just a container for the simulation components used by a wheeled vehicle Keeping all the physics systems together and accessible through the one vehicle class
- L38 _public function_ `FSimpleWheeledVehicle() : bSuspensionEnabled(true) , bMechanicalSimEnabled(true) , bWheelFrictionEnabled(true) , NumDrivenWheels(0) , bLegacyWheelFrictionPosition(false)`
- L48 _public function_ `virtual ~FSimpleWheeledVehicle()`
- L57 _public function_ `bool IsValid()`
- L62 _public function_ `FSimpleEngineSim& GetEngine()`
- L68 _public function_ `bool HasEngine() const`
- L73 _public function_ `bool HasTransmission() const`
- L78 _public function_ `bool HasTorqueControlSetup()`
- L83 _public function_ `bool HasTargetRotationControlSetup()`
- L88 _public function_ `bool HasStabilizeControlSetup()`
- L94 _public function_ `FSimpleTransmissionSim& GetTransmission()`
- L100 _public function_ `FSimpleDifferentialSim& GetDifferential()`
- L106 _public function_ `FSimpleWheelSim& GetWheel(int WheelIdx)`
- L112 _public function_ `FSimpleSuspensionSim& GetSuspension(int WheelIdx)`
- L118 _public function_ `FSimpleSteeringSim& GetSteering()`
- L124 _public function_ `FSimpleAerodynamicsSim& GetAerodynamics()`
- L130 _public function_ `FAerofoil& GetAerofoil(int AerofoilIdx)`
- L136 _public function_ `FSimpleThrustSim& GetThruster(int ThrusterIdx)`
- L142 _public function_ `FTorqueControlSim& GetTorqueControl()`
- L148 _public function_ `FTargetRotationControlSim& GetTargetRotationControl()`
- L154 _public function_ `FStabilizeControlSim& GetStabilizeControl()`
- L160 _public function_ `const TArray<FAxleSim>& GetAxles() const`
- L166 _public member_ `TArray<FSimpleEngineSim> Engine;`
- L167 _public member_ `TArray<FSimpleTransmissionSim> Transmission;`
- L168 _public member_ `TArray<FSimpleDifferentialSim> Differential;`
- L169 _public member_ `TArray<FSimpleWheelSim> Wheels;`
- L170 _public member_ `TArray<FSimpleSuspensionSim> Suspension;`
- L171 _public member_ `TArray<FSimpleSteeringSim> Steering;`
- L172 _public member_ `TArray<FSimpleAerodynamicsSim> Aerodynamics;`
- L173 _public member_ `TArray<FAerofoil> Aerofoils;`
- L174 _public member_ `TArray<FSimpleThrustSim> Thrusters;`
- L175 _public member_ `TArray<FAxleSim> Axles;`
- L177 _public member_ `TArray<FTorqueControlSim> TorqueControlSim;`
- L178 _public member_ `TArray<FTargetRotationControlSim> TargetRotationControlSim;`
- L179 _public member_ `TArray<FStabilizeControlSim> StabilizeControlSim;`
- L185 _public member_ `bool bSuspensionEnabled;`
- L186 _public member_ `bool bMechanicalSimEnabled;`
- L187 _public member_ `bool bWheelFrictionEnabled;`
- L188 _public member_ `uint32 NumDrivenWheels;`
- L189 _public member_ `bool bLegacyWheelFrictionPosition;`

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace Chaos`

### `Source/Runtime/Experimental/ChaosVehicles/ChaosVehiclesCore/Public/SteeringSystem.h` (Public)


#### enum `Chaos::ESteerType`  
`enum class ESteerType : uint8`  
_L18-23_
- L20 _public enumerator_ `SingleAngle`
- L21 _public enumerator_ `AngleRatio`
- L22 _public enumerator_ `Ackermann`

#### struct `Chaos::FSimpleSteeringConfig`  
`struct FSimpleSteeringConfig`  
_L25-43_
- L27 _public function_ `FSimpleSteeringConfig() : SteeringType(ESteerType::AngleRatio) , AngleRatio(0.7f) , TrackWidth(1.8f) , WheelBase(3.8f)`
- L34 _public member_ `ESteerType SteeringType;`
- L35 _public member_ `float AngleRatio;`
- L37 _public member_ `float TrackWidth;`
- L38 _public member_ `float WheelBase;`
- L40 _public member_ `float MaxSteeringAngle;`
- L42 _public member_ `FGraph SpeedVsSteeringCurve;`

#### class `Chaos::FAckermannSim`  
`class FAckermannSim : public TVehicleSystem<FSimpleSteeringConfig>`  
_L45-76_
- inherits: `TVehicleSystem<FSimpleSteeringConfig>`
- L49 _public prototype_ `FAckermannSim(const FSimpleSteeringConfig* SetupIn);`
- L51 _public prototype_ `void GetLeftHingeLocations(FVector2D& OutC1, FVector2D& OutP, FVector2D& OutC2);`
- L53 _public prototype_ `void GetRightHingeLocations(FVector2D& OutC1, FVector2D& OutP, FVector2D& OutC2);`
- L55 _public prototype_ `void CalculateAkermannAngle(float Input, float& OutSteerLeft, float& OutSteerRight);`
- L57 _public function_ `float GetMaxAckermanAngle()`
- L63 _private member_ `FVector2D C1;`
- L64 _private member_ `FVector2D C2;`
- L65 _private member_ `float R1;`
- L66 _private member_ `float R2;`
- L67 _private member_ `float SteerInputScaling;`
- L68 _private member_ `float MaxAckermanAngle;`
- L70 _private member_ `FVector2D LeftRodPt, RightRodPt;`
- L70 _private member_ `FVector2D LeftRodPt, RightRodPt;`
- L71 _private member_ `FVector2D LeftPivot;`
- L72 _private member_ `FVector2D RightPivot;`
- L74 _private member_ `float RestAngle;`

#### class `Chaos::FSimpleSteeringSim`  
`class FSimpleSteeringSim : public TVehicleSystem<FSimpleSteeringConfig>`  
_L78-129_
- inherits: `TVehicleSystem<FSimpleSteeringConfig>`
- L81 _public function_ `FSimpleSteeringSim(const FSimpleSteeringConfig* SetupIn) : TVehicleSystem<FSimpleSteeringConfig>(SetupIn) , Ackermann(SetupIn)`
- L87 _public function_ `float GetSteeringFromVelocity(float VelocityMPH)`
- L92 _public function_ `float GetSteeringAngle(float InNormSteering, float MaxSteeringAngle, float WheelSide)`
- L128 _public member_ `FAckermannSim Ackermann;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace Chaos`

### `Source/Runtime/Experimental/ChaosVehicles/ChaosVehiclesCore/Public/SteeringUtility.h` (Public)


#### struct `Chaos::FSteeringUtility`  
`struct FSteeringUtility`  
_L15-155_
- L27 _public function_ `static bool IntersectTwoCircles(float R1, float R2, float D, FVector2D& OutIntersection)` — Intersection of two axis aligned circles Radius R1, R2 with a separation distance between centers of D
- L62 _public function_ `static void CalculateAkermannAngle(bool Flip, float Input, FVector2D& C2, float R1, float R2 , float& OutSteerAngle, FVector2D& OutC1, FVector2D& OutPt)`
- L89 _public function_ `static float CalculateBetaDegrees(float TrackWidth, float WheelBase)`
- L93 _public function_ `static void AkermannSetup(float T, float Beta, float R, float& OutH, float& OutS)`
- L99 _public function_ `static void CalcJointPositions(float T, float Beta, float R, FVector2D& C1, float& R1, FVector2D& C2, float& R2)`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace Chaos`

### `Source/Runtime/Experimental/ChaosVehicles/ChaosVehiclesCore/Public/SuspensionSystem.h` (Public)


#### struct `Chaos::FSimpleSuspensionConfig`  
`struct FSimpleSuspensionConfig`  
_L27-81_
- L29 _public function_ `FSimpleSuspensionConfig() : SuspensionAxis(FVector(0.f, 0.f, -1.f)) , SuspensionForceOffset(FVector::ZeroVector) , SuspensionMaxRaise(0.f) , SuspensionMaxDrop(0.f) , MaxLength(0.f) , SpringRate(1.f) , SpringPreload(0.5f) , CompressionDamping(0.9f) , ReboundDamping(0.9f) , RestingForce(0.f) , Swaybar(0.5f) , DampingRatio(0.3f) , WheelLoadRatio(1.f) , RaycastSafetyMargin(0.0f) , SuspensionSmoothing(6)`
- L50 _public function_ `void SetSuspensionMaxRaise(float InSuspensionMaxRaise)`
- L56 _public function_ `void SetSuspensionMaxDrop(float InSuspensionMaxDrop)`
- L62 _public member_ `FVector SuspensionAxis;` — local axis, direction of suspension force raycast traces
- L63 _public member_ `FVector SuspensionForceOffset;` — relative position from wheel where suspension forces are applied
- L64 _public member_ `float SuspensionMaxRaise;` — distance [cm]
- L65 _public member_ `float SuspensionMaxDrop;` — distance [cm]
- L66 _public member_ `float MaxLength;` — distance [cm]
- L68 _public member_ `float SpringRate;` — spring constant
- L69 _public member_ `float SpringPreload;` — Amount of Spring force (independent spring movement)
- L70 _public member_ `float CompressionDamping;` — limit compression speed
- L71 _public member_ `float ReboundDamping;` — limit rebound speed
- L72 _public member_ `float RestingForce;` — force on spring when vehicle on level with no body roll
- L74 _public member_ `float Swaybar;` — Anti-roll bar
- L76 _public member_ `float DampingRatio;` — value between (0-no damping) and (1-critical damping)
- L77 _public member_ `float WheelLoadRatio;` — Normalized value, 0 no weight transfer, 1 Normal Weight transfer. A lower value cures lift off oversteer.
- L78 _public member_ `float RaycastSafetyMargin;` — raise start of raycast [cm]
- L80 _public member_ `int SuspensionSmoothing;` — [0-off , 10-max] smoothing visual appearance of wheel movement

#### struct `Chaos::FSuspensionTrace`  
`struct FSuspensionTrace`  
_L84-100_
- desc: Suspension world ray/shape trace start and end positions
- L86 _public member_ `FVector Start;`
- L87 _public member_ `FVector End;`
- L89 _public function_ `FVector TraceDir()`
- L95 _public function_ `float Length()`

#### class `Chaos::FSimpleSuspensionSim`  
`class FSimpleSuspensionSim : public TVehicleSystem<FSimpleSuspensionConfig>`  
_L102-235_
- inherits: `TVehicleSystem<FSimpleSuspensionConfig>`
- L105 _public function_ `FSimpleSuspensionSim(const FSimpleSuspensionConfig* SetupIn) : TVehicleSystem<FSimpleSuspensionConfig>(SetupIn) , DisplacementInput(0.f) , LastDisplacement(0.f) , LocalVelocity(FVector::ZeroVector) , SuspensionForce(0.f) , LocalOffset(FVector::ZeroVector) , SpringDisplacement(0.f) , SpringIndex(0) , LastSpringLength(0.f) , AveragingLength() , AveragingCount(0) , AveragingNum(0)`
- L124 _public function_ `void SetSuspensionLength(float InLength, float WheelRadius)` — #todo: Change This ; Set suspension length after determined from raycast
- L131 _public function_ `float GetNormalizedLength()`
- L144 _public function_ `void SetLocalVelocity(const FVector& InVelocity)` — set local velocity at suspension position
- L149 _public function_ `void SetLocalVelocityFromWorld(const FTransform& InWorldTransform, const FVector& InWorldVelocity)`
- L154 _public function_ `void SetLocalRestingPosition(const FVector& InOffset)`
- L159 _public function_ `void SetSpringIndex(uint32 InIndex)`
- L164 _public function_ `void UpdateWorldRaycastLocation(const FTransform& BodyTransform, float WheelRadius, FSuspensionTrace& OutTrace)`
- L174 _public function_ `float GetTraceLength(float WheelRadius)`
- L181 _public prototype_ `float GetSpringLength();`
- L183 _public function_ `float GetSuspensionForce() const`
- L188 _public function_ `FVector GetSuspensionForceVector(const FTransform& InTransform)`
- L194 _public function_ `float GetSuspensionOffset()`
- L199 _public function_ `const FVector& GetLocalRestingPosition() const`
- L206 _public prototype_ `void Simulate(float DeltaTime);`
- L208 _public function_ `int32 GetAveragingCount() const`
- L209 _public function_ `int32 GetAveragingNum() const`
- L210 _public function_ `float GetLastSpringLength() const`
- L211 _public function_ `float GetLastDisplacement() const`
- L212 _public function_ `float GetAveragingLength(const int32 LengthIndex) const`
- L214 _public function_ `void SetAveragingCount(const int32 InAveragingCount)`
- L215 _public function_ `void SetAveragingNum(const int32 InAveragingNum)`
- L216 _public function_ `void SetLastSpringLength(const float InLastSpringLength)`
- L217 _public function_ `void SetLastDisplacement(const float InLastDisplacement)`
- L218 _public function_ `void SetAveragingLength(const int32 LengthIndex, const float InAveragingLength)`
- L222 _protected member_ `float DisplacementInput;`
- L223 _protected member_ `float LastDisplacement;`
- L224 _protected member_ `FVector LocalVelocity;`
- L225 _protected member_ `float SuspensionForce;`
- L227 _protected member_ `FVector LocalOffset;`
- L228 _protected member_ `float SpringDisplacement;`
- L229 _protected member_ `uint32 SpringIndex;`
- L231 _protected member_ `float LastSpringLength;` — blend rather than jump to new location
- L232 _protected member_ `float AveragingLength[NUM_SUS_AVERAGING];`
- L233 _protected member_ `int AveragingCount;`
- L234 _protected member_ `int AveragingNum;`

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace Chaos`
- L25 _macro_ `#define NUM_SUS_AVERAGING 10`

### `Source/Runtime/Experimental/ChaosVehicles/ChaosVehiclesCore/Public/SuspensionUtility.h` (Public)


#### struct `FSuspensionUtility`  
`struct FSuspensionUtility`  
_L15-59_
- L31 _public prototype_ `static bool ComputeSprungMasses(const TArray<FVector>& MassSpringPositions, const float TotalMass, TArray<float>& OutSprungMasses);` — Compute the distribution of the mass of a body among springs. This method assumes that spring positions are given relative to the center of mass of the body, and that gravity occurs in the local -Z direction. Returns true if it was able to find a valid mass configuration. If only one or two springs are included, then a valid configuration may not result in a stable suspension system - a bicycle or pogostick, for example, which is not perfectly centered may have a valid sprung mass configuration without being stable.
- L36 _public prototype_ `static bool ComputeSprungMasses(const TArray<FVector>& LocalSpringPositions, const FVector& LocalCenterOfMass, const float TotalMass, TArray<float>& OutSprungMasses);` — Same as above, but allows the caller to specify spring locations in a local space which is not necessarily originated at the center of mass.
- L39 _public function_ `static float ComputeNaturalFrequency(float SpringRate, float SprungMass)` — Natural frequency of spring in radians/sec - divide by 2Pi to get result in Hz
- L45 _public function_ `static float ComputeCriticalDamping(float SpringRate, float SprungMass)` — Compute spring damping value that will achieve critical damping
- L53 _public function_ `static float ComputeDamping(float SpringRate, float SprungMass, float DampingRatio)` — Compute spring damping value that will achieve the desired damping ratio. A damping ratio between 0.2-0.5 is typical of vehicle suspension

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogVehicleUtility, Log, All);`
- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogVehicleUtility, Log, All);`

### `Source/Runtime/Experimental/ChaosVehicles/ChaosVehiclesCore/Public/ThrustSystem.h` (Public)


#### enum `Chaos::EThrustType`  
`enum class EThrustType : uint8`  
_L17-24_
- L19 _public enumerator_ `Fixed = 0`
- L20 _public enumerator_ `Wing`
- L21 _public enumerator_ `Rudder`
- L22 _public enumerator_ `Elevator`
- L23 _public enumerator_ `HelicopterRotor`

#### struct `Chaos::FSimpleThrustConfig`  
`struct FSimpleThrustConfig`  
_L26-36_
- L28 _public member_ `EThrustType Type;`
- L29 _public member_ `FVector Offset;`
- L30 _public member_ `FVector Axis;`
- L31 _public member_ `TArray<float> Curve;`
- L32 _public member_ `float MaxSpeed;`
- L33 _public member_ `float MaxThrustForce;`
- L34 _public member_ `float MaxControlAngle;`

#### class `Chaos::FSimpleThrustSim`  
`class FSimpleThrustSim : public TVehicleSystem<FSimpleThrustConfig>`  
_L38-101_
- inherits: `TVehicleSystem<FSimpleThrustConfig>`
- L42 _public prototype_ `FSimpleThrustSim(const FSimpleThrustConfig* SetupIn);`
- L44 _public function_ `void SetThrottle(float InThrottle)`
- L49 _public function_ `void SetPitch(float InPitch)`
- L54 _public function_ `void SetRoll(float InRoll)`
- L59 _public function_ `void SetYaw(float InYaw)`
- L65 _public function_ `void SetWorldVelocity(const FVector& InVelocity)`
- L71 _public function_ `const FVector& GetThrustForce() const` — Get functions
- L76 _public function_ `const FVector& GetThrustDirection() const`
- L81 _public prototype_ `const FVector GetThrustLocation() const;`
- L84 _public prototype_ `void Simulate(float DeltaTime);` — simulate
- L88 _protected member_ `float ThrottlePosition;` — [0..1 Normalized position]
- L90 _protected member_ `FVector ThrustForce;`
- L91 _protected member_ `FVector ThrustDirection;`
- L93 _protected member_ `bool ThrusterStarted;` — is the 'engine' turned off or has it been started
- L95 _protected member_ `FVector WorldVelocity;`
- L97 _protected member_ `float Pitch;`
- L98 _protected member_ `float Roll;`
- L99 _protected member_ `float Yaw;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace Chaos`

### `Source/Runtime/Experimental/ChaosVehicles/ChaosVehiclesCore/Public/TireSystem.h` (Public)


#### struct `Chaos::FSimpleTireConfig`  
`struct FSimpleTireConfig`  
_L20-44_
- L23 _public function_ `FSimpleTireConfig() : Radius(594.f / 2.f / 1000.0f) , Width(195.f / 1000.0f) , Depth(107.f / 1000.0f) , StaticFrictionCoefficient(0.5f) , KineticFrictionCoefficient(StaticFrictionCoefficient * 0.7f) , InitialTirePressure(0.f) , InitialTireWear(0.f)` — Tires are normally specified as 192/55R15
- L35 _public member_ `float Radius;`
- L36 _public member_ `float Width;`
- L37 _public member_ `float Depth;`
- L39 _public member_ `float StaticFrictionCoefficient;`
- L40 _public member_ `float KineticFrictionCoefficient;`
- L41 _public member_ `float InitialTirePressure;`
- L42 _public member_ `float InitialTireWear;`

#### class `Chaos::FSimpleTireSim`  
`class FSimpleTireSim : public TVehicleSystem<FSimpleTireConfig>`  
_L46-63_
- inherits: `TVehicleSystem<FSimpleTireConfig>`
- L49 _public function_ `FSimpleTireSim(const FSimpleTireConfig* SetupIn) : TVehicleSystem<FSimpleTireConfig>(SetupIn) , TirePressure(0.f) , TireTemperature(0.f) , TireWear(0.f)`
- L59 _private member_ `float TirePressure;`
- L60 _private member_ `float TireTemperature;`
- L61 _private member_ `float TireWear;` — [0 no wear, 1 fully worn]

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace Chaos`

### `Source/Runtime/Experimental/ChaosVehicles/ChaosVehiclesCore/Public/TransmissionSystem.h` (Public)


#### enum `Chaos::ETransmissionType`  
`enum ETransmissionType : uint8`  
_L24-28_
- L26 _public enumerator_ `Manual`
- L27 _public enumerator_ `Automatic`

#### enum `Chaos::EDifferentialType`  
`enum EDifferentialType : uint8`  
_L30-36_
- L32 _public enumerator_ `UndefinedDrive`
- L33 _public enumerator_ `AllWheelDrive`
- L34 _public enumerator_ `FrontWheelDrive`
- L35 _public enumerator_ `RearWheelDrive`

#### struct `Chaos::FSimpleDifferentialConfig`  
`struct FSimpleDifferentialConfig`  
_L38-48_
- L40 _public function_ `FSimpleDifferentialConfig() : DifferentialType(EDifferentialType::RearWheelDrive) , FrontRearSplit(0.5f)`
- L46 _public member_ `EDifferentialType DifferentialType;`
- L47 _public member_ `float FrontRearSplit;`

#### class `Chaos::FSimpleDifferentialSim`  
`class FSimpleDifferentialSim : public TVehicleSystem<FSimpleDifferentialConfig>`  
_L50-58_
- inherits: `TVehicleSystem<FSimpleDifferentialConfig>`
- L53 _public function_ `FSimpleDifferentialSim(const FSimpleDifferentialConfig* SetupIn) : TVehicleSystem<FSimpleDifferentialConfig>(SetupIn) , FrontRearSplit(Setup().FrontRearSplit)`
- L57 _public member_ `float FrontRearSplit;`

#### struct `Chaos::FSimpleTransmissionConfig`  
`struct FSimpleTransmissionConfig`  
_L60-86_
- L62 _public function_ `FSimpleTransmissionConfig() : FinalDriveRatio(1.f) , ChangeUpRPM(5000) , ChangeDownRPM(2500) , GearChangeTime(0.2f) , TransmissionEfficiency(1.f) , TransmissionType(ETransmissionType::Automatic) , AutoReverse(true)`
- L73 _public member_ `TArray<float> ForwardRatios;` — Gear ratios for forward gears
- L74 _public member_ `TArray<float> ReverseRatios;` — Gear ratios for reverse Gear(s)
- L75 _public member_ `float FinalDriveRatio;` — Final drive ratio [~4.0]
- L77 _public member_ `uint32 ChangeUpRPM;` — [#todo: RPM or % max RPM?]
- L78 _public member_ `uint32 ChangeDownRPM;` — [#todo: RPM or % max RPM?]
- L79 _public member_ `float GearChangeTime;` — [sec]
- L81 _public member_ `float TransmissionEfficiency;` — Loss from friction in the system mean we might run at around 0.94 Efficiency
- L83 _public member_ `ETransmissionType TransmissionType;` — Specify Automatic or Manual transmission
- L85 _public member_ `bool AutoReverse;` — Arcade handling - holding Brake switches into reverse after vehicle has stopped

#### class `Chaos::FSimpleTransmissionSim`  
`class FSimpleTransmissionSim : public TVehicleSystem<FSimpleTransmissionConfig>`  
_L89-235_
- inherits: `TVehicleSystem<FSimpleTransmissionConfig>`
- L92 _public prototype_ `FSimpleTransmissionSim(const FSimpleTransmissionConfig* SetupIn);`
- L100 _public prototype_ `void SetGear(int32 InGear, bool Immediate = false);` — set the target gear number to change to, can change gear immediately if specified i.e. rather than waiting for the gear change time to elapse
- L103 _public function_ `void ChangeUp()` — set the target gear to one higher than current target, will clamp gear index within rage
- L109 _public function_ `void ChangeDown()` — set the target gear to one lower than current target, will clamp gear index within rage
- L115 _public function_ `void SetEngineRPM(float InRPM)` — Tell the transmission system what the current engine RPM is, so we can decide when to change up/down with automatic transmission type
- L120 _public function_ `void SetAllowedToChangeGear(bool OkToChangeIn)`
- L129 _public function_ `int32 GetCurrentGear() const` — Get the current gear index, (reverse gears < 0, neutral 0, forward gears > 0)
- L135 _public function_ `int32 GetTargetGear() const` — Get the target gear index, (reverse gears < 0, neutral 0, forward gears > 0)
- L141 _public function_ `float GetCurrentGearChangeTime() const` — Get the current gear change time
- L147 _public function_ `void SetCurrentGear(const int32 InCurrentGear)` — Set the current gear index, (reverse gears < 0, neutral 0, forward gears > 0)
- L153 _public function_ `void SetTargetGear(const int32 InTargetGear)` — Set the target gear index, (reverse gears < 0, neutral 0, forward gears > 0)
- L159 _public function_ `void SetCurrentGearChangeTime(const float InCurrentGearChangeTime)` — Set the current gear change time
- L165 _public function_ `bool IsCurrentlyChangingGear() const` — Are we currently in the middle of a gear change
- L170 _public function_ `bool IsOutOfGear() const`
- L176 _public prototype_ `float GetGearRatio(int32 InGear);` — Get the final combined gear ratio for the specified gear (reverse gears < 0, neutral 0, forward gears > 0)
- L179 _public function_ `float GetTransmissionRPM(float InEngineRPM, int InGear)` — Get the transmission RPM, from the specified engine RPM and gear selection
- L190 _public function_ `float GetTransmissionRPM()` — Get the transmission RPM for the current state of the engine RPM and gear selection
- L196 _public function_ `float GetTransmissionTorque(float InEngineTorque)` — Given the engine torque return the transmission torque taking into account the gear ratios and transmission losses
- L208 _public function_ `float GetEngineRPMFromWheelRPM(float InWheelRPM)` — Get the expected engine RPM from the wheel RPM taking into account the current gear ratio (assuming no clutch slip)
- L218 _public prototype_ `void Simulate(float DeltaTime);` — Simulate - update internal state - changes gear when using automatic transmission - implements gear change time, where gear goes through neutral
- L220 _public function_ `void CorrectGearInputRange(int32& GearIndexInOut)`
- L227 _private member_ `int32 CurrentGear;` — <0 reverse gear(s), 0 neutral, >0 forward gears
- L228 _private member_ `int32 TargetGear;` — <0 reverse gear(s), 0 neutral, >0 forward gears
- L229 _private member_ `float CurrentGearChangeTime;` — Time to change gear, no power transmitted to the wheels during change
- L231 _private member_ `float EngineRPM;` — Engine Revs Per Minute
- L233 _private member_ `bool AllowedToChangeGear;`

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace Chaos`

### `Source/Runtime/Experimental/ChaosVehicles/ChaosVehiclesCore/Public/TransmissionUtility.h` (Public)


#### class `Chaos::FTransmissionUtility`  
`class FTransmissionUtility`  
_L15-31_
- L19 _public function_ `static bool IsWheelPowered(const EDifferentialType DifferentialType, const FSimpleWheelSim& PWheel)`
- L24 _public prototype_ `static bool IsWheelPowered(const EDifferentialType DifferentialType, const FSimpleWheelConfig::EAxleType AxleType, const bool EngineEnabled = false);`
- L26 _public prototype_ `static int GetNumWheelsOnAxle(FSimpleWheelConfig::EAxleType AxleType, const TArray<FSimpleWheelSim>& Wheels);`
- L28 _public prototype_ `static int GetNumDrivenWheels(const TArray<FSimpleWheelSim>& Wheels);`
- L30 _public prototype_ `static float GetTorqueRatioForWheel(const FSimpleDifferentialSim& PDifferential, const int WheelIndex, const TArray<FSimpleWheelSim>& Wheels);`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CHAOSVEHICLESCORE_API`
- L12 _namespace_ `namespace Chaos`

### `Source/Runtime/Experimental/ChaosVehicles/ChaosVehiclesCore/Public/VehicleSystemTemplate.h` (Public)


#### class `TVehicleSystem`  
`template <typename T> class TVehicleSystem`  
_L12-41_
- desc: Code common between all vehicle systems
- L16 _public function_ `TVehicleSystem() : SetupPtr(nullptr)`
- L20 _public function_ `TVehicleSystem(const T* SetupIn) : SetupPtr(SetupIn)`
- L25 _public function_ `T& AccessSetup()`
- L31 _public function_ `const T& Setup() const`
- L40 _public member_ `const T* SetupPtr;` — Setup data pointer is public if you want to use it directly

### `Source/Runtime/Experimental/ChaosVehicles/ChaosVehiclesCore/Public/VehicleUtility.h` (Public)


#### struct `Chaos::RealWorldConsts`  
`struct RealWorldConsts`  
_L24-51_
- L26 _public function_ `FORCEINLINE static float WaterDensity()`
- L31 _public function_ `FORCEINLINE static float AirDensity()`
- L36 _public function_ `FORCEINLINE static float HalfAirDensity()`
- L41 _public function_ `FORCEINLINE static float DryRoadFriction()`
- L46 _public function_ `FORCEINLINE static float WetRoadFriction()`

#### class `Chaos::FNormalisedGraph`  
`class FNormalisedGraph`  
_L53-86_
- L56 _public function_ `void Empty()`
- L61 _public function_ `void AddNormalized(float Value)`
- L66 _public function_ `float GetValue(float InX, float MaxX = 1.0f, float MaxY = 1.0f) const`
- L85 _private member_ `TArray<float> Graph;`

#### class `Chaos::FGraph`  
`class FGraph`  
_L88-114_
- L91 _public function_ `FGraph()`
- L96 _public function_ `void Empty()`
- L105 _public prototype_ `void Add(const FVec2& Value);`
- L107 _public prototype_ `float EvaluateY(float InX) const;`
- L109 _public function_ `bool IsEmpty() const`
- L111 _private member_ `TArray<FVec2> Graph;`
- L112 _private member_ `FVector2D BoundsX;`
- L113 _private member_ `FVector2D BoundsY;`

#### class `Chaos::FVehicleUtility`  
`class FVehicleUtility`  
_L116-162_
- L120 _public function_ `FORCEINLINE static void ClampNormalRange(float& InOutValue)` — clamp value between 0 and 1
- L126 _public function_ `static float YawFromForwardVectorRadians(const FVector& NormalizedForwardsVector)` — Calculate Yaw angle in Radians from a Normalized Forward facing vector
- L132 _public function_ `static float PitchFromForwardVectorRadians(const FVector& NormalizedForwardsVector)` — Calculate Pitch angle in Radians from a Normalized Forward facing vector
- L138 _public function_ `static float RollFromRightVectorRadians(const FVector& NormalizedRightVector)` — Calculate Roll angle in Radians from a Normalized Right facing vector
- L144 _public prototype_ `static float TurnRadiusFromThreePoints(const FVector& PtA, const FVector& PtB, const FVector& PtC);` — Calculate turn radius from three points. Note: this function is quite inaccurate for large radii. Return 0 if there is no answer, i.e. points lie on a line
- L146 _public function_ `static float CalculateSlipAngle(float Y, float X)`

#### class `Chaos::FTimeAndDistanceMeasure`  
`class FTimeAndDistanceMeasure`  
_L302-331_
- L305 _public prototype_ `FTimeAndDistanceMeasure(const FString& DescriptionIn, float InitialVelocityIn, float TargetVelocityIn, float TargetDistanceIn);`
- L307 _public prototype_ `void Reset();`
- L309 _public function_ `bool IsComplete() const`
- L311 _public prototype_ `void Update(float DeltaTime, const FVector& CurrentLocation, float CurrentVelocity);`
- L313 _public prototype_ `FString ToString() const;`
- L316 _private member_ `FString Description;`
- L317 _private member_ `bool PreStartConditionsMet;`
- L318 _private member_ `bool StartConditionsMet;`
- L319 _private member_ `bool MeasurementComplete;`
- L321 _private member_ `FVector InitialLocation;`
- L322 _private member_ `double InitialTime;`
- L324 _private member_ `float InitialVelocityMPH;`
- L325 _private member_ `float FinalTargetVelocityMPH;`
- L326 _private member_ `float FinalTargetDistanceMiles;`
- L328 _private member_ `float VelocityResultMPH;`
- L329 _private member_ `float DistanceResultMiles;`
- L330 _private member_ `float TimeResultSeconds;`

#### class `Chaos::FPerformanceMeasure`  
`class FPerformanceMeasure`  
_L333-392_
- L345 _public prototype_ `FPerformanceMeasure();`
- L347 _public function_ `void AddMeasure(FTimeAndDistanceMeasure& MeasureIn)`
- L352 _public function_ `const FTimeAndDistanceMeasure& GetMeasure(int MeasurementIdx)`
- L357 _public function_ `void ResetAll()`
- L365 _public function_ `void Update(float DeltaTime, const FVector& CurrentLocation, float CurrentVelocity)`
- L373 _public function_ `int GetNumMeasures() const`
- L378 _public function_ `void Enable()`
- L383 _public function_ `bool IsEnabled() const`
- L390 _private member_ `bool IsEnabledThisFrame;`
- L391 _private member_ `TArray<FTimeAndDistanceMeasure> PerformanceMeasure;`

#### enum `Chaos::FPerformanceMeasure::EMeasure`  
`enum class EMeasure : uint8`  
_L336-343_
- L338 _public enumerator_ `ZeroToThirtyMPH = 0`
- L339 _public enumerator_ `ZeroToSixtyMPH`
- L340 _public enumerator_ `QuarterMile`
- L341 _public enumerator_ `ThirtyToZeroMPH`
- L342 _public enumerator_ `SixtyToZeroMPH`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API CHAOSVEHICLESCORE_API`
- L19 _macro_ `#define VEHICLE_DEBUGGING_ENABLED 0` — Disable Optimizations in non debug build configurations
- L21 _namespace_ `namespace Chaos`
- L164 _function_ `FORCEINLINE float MToCmScaling()` (scope `Chaos`)
- L169 _function_ `FORCEINLINE float CmToMScaling()` (scope `Chaos`)
- L175 _function_ `FORCEINLINE float RPMToOmega(float RPM)` (scope `Chaos`) — revolutions per minute to radians per second
- L181 _function_ `FORCEINLINE float OmegaToRPM(float Omega)` (scope `Chaos`) — radians per second to revolutions per minute
- L187 _function_ `FORCEINLINE float KmHToCmS(float KmH)` (scope `Chaos`) — km/h to cm/s
- L193 _function_ `FORCEINLINE float CmSToKmH(float CmS)` (scope `Chaos`) — cm/s to km/h
- L199 _function_ `FORCEINLINE float CmSToMPH(float CmS)` (scope `Chaos`) — cm/s to miles per hour
- L205 _function_ `FORCEINLINE float MPHToCmS(float MPH)` (scope `Chaos`) — miles per hour to cm/s
- L211 _function_ `FORCEINLINE float MPHToMS(float MPH)` (scope `Chaos`) — miles per hour to meters per second
- L217 _function_ `FORCEINLINE float MSToMPH(float MS)` (scope `Chaos`) — meters per second to miles per hour
- L223 _function_ `FORCEINLINE float CmToM(float Cm)` (scope `Chaos`) — cm to meters
- L229 _function_ `FORCEINLINE FVector CmToM(const FVector& Cm)` (scope `Chaos`) — cm to meters
- L235 _function_ `FORCEINLINE float MToCm(float M)` (scope `Chaos`) — meters to cm
- L241 _function_ `FORCEINLINE FVector MToCm(const FVector& M)` (scope `Chaos`) — cm to meters
- L247 _function_ `FORCEINLINE float CmToMiles(float Cm)` (scope `Chaos`) — cm to meters - warning loss of precision
- L254 _function_ `FORCEINLINE float KmToMile(float Km)` (scope `Chaos`) — Km to miles
- L260 _function_ `FORCEINLINE float MileToKm(float Miles)` (scope `Chaos`) — miles to Km
- L266 _function_ `FORCEINLINE float M2ToCm2(float M2)` (scope `Chaos`) — meters squared to cm squared
- L272 _function_ `FORCEINLINE float Cm2ToM2(float Cm2)` (scope `Chaos`) — cm squared to meters squared
- L277 _function_ `FORCEINLINE float DegToRad(float InDeg)` (scope `Chaos`)
- L282 _function_ `FORCEINLINE float RadToDeg(float InRad)` (scope `Chaos`)
- L287 _function_ `FORCEINLINE float Sqr(float Val)` (scope `Chaos`)
- L292 _function_ `FORCEINLINE float TorqueMToCm(float TorqueIn)` (scope `Chaos`)
- L297 _function_ `FORCEINLINE float TorqueCmToM(float TorqueIn)` (scope `Chaos`)

### `Source/Runtime/Experimental/ChaosVehicles/ChaosVehiclesCore/Public/WheelSystem.h` (Public)


#### struct `Chaos::FSimpleWheelConfig`  
`struct FSimpleWheelConfig`  
_L42-154_
- desc: Wheel setup data that doesn't change during simulation
- L82 _public function_ `FSimpleWheelConfig() : Offset(FVector(2.f, 1.f, 0.f)) , WheelMass(20.f)`
- L115 _public member_ `FVector Offset;` — wheel tire
- L116 _public member_ `float WheelMass;` — Mass of wheel [Kg]
- L117 _public member_ `float WheelRadius;` — [cm]
- L118 _public member_ `float WheelWidth;` — [cm]
- L120 _public member_ `int MaxSteeringAngle;` — Yaw angle of steering [Degrees]
- L123 _public member_ `float MaxBrakeTorque;` — brakes
- L124 _public member_ `float HandbrakeTorque;` — Handbrake Torque [Nm]
- L125 _public member_ `bool ABSEnabled;` — Advanced braking system operational
- L128 _public member_ `bool BrakeEnabled;` — setup
- L129 _public member_ `bool HandbrakeEnabled;` — Handbrake is operational on this wheel
- L130 _public member_ `bool SteeringEnabled;` — Steering is operational on this wheel
- L131 _public member_ `bool EngineEnabled;` — Wheel is driven by an engine
- L132 _public member_ `bool TractionControlEnabled;` — Straight Line Traction Control
- L133 _public member_ `float TorqueRatio;` — Portion of torque going to this wheel (0->1)
- L135 _public member_ `EAxleType AxleType;`
- L137 _public member_ `EFrictionCombineMethod FrictionCombineMethod;` — #todo: use this variable
- L138 _public member_ `EExternalTorqueCombineMethod ExternalTorqueCombineMethod;`
- L140 _public member_ `float FrictionMultiplier;`
- L141 _public member_ `float LateralSlipGraphMultiplier;`
- L142 _public member_ `float CorneringStiffness;`
- L143 _public member_ `float SideSlipModifier;`
- L145 _public member_ `float SlipThreshold;`
- L146 _public member_ `float SkidThreshold;`
- L148 _public member_ `FGraph LateralSlipGraph;`
- L149 _public member_ `float MaxSpinRotation;`

#### enum `Chaos::FSimpleWheelConfig::EWheelDamageStatus`  
`enum EWheelDamageStatus`  
_L45-51_
- desc: #todo: use this
- L47 _public enumerator_ `NONE`
- L48 _public enumerator_ `BUCKLED`
- L49 _public enumerator_ `FLAT`
- L50 _public enumerator_ `MISSING`

#### enum `Chaos::FSimpleWheelConfig::EWheelSimulationStatus`  
`enum EWheelSimulationStatus`  
_L54-59_
- desc: #todo: use this
- L56 _public enumerator_ `ROLLING` — wheel speed matches the vehicle ground speed
- L57 _public enumerator_ `SPINNING` — wheel speed faster than vehicle ground speed
- L58 _public enumerator_ `LOCKED` — wheel is locked and sliding over surface

#### enum `Chaos::FSimpleWheelConfig::EFrictionCombineMethod`  
`enum EFrictionCombineMethod`  
_L62-66_
- desc: #todo: use this
- L64 _public enumerator_ `Multiply` — default - most correct
- L65 _public enumerator_ `Average`

#### enum `Chaos::FSimpleWheelConfig::EAxleType`  
`enum EAxleType : uint8`  
_L68-73_
- L70 _public enumerator_ `UndefinedAxle = 0`
- L71 _public enumerator_ `Front`
- L72 _public enumerator_ `Rear`

#### enum `Chaos::FSimpleWheelConfig::EExternalTorqueCombineMethod`  
`enum EExternalTorqueCombineMethod : uint8`  
_L75-80_
- L77 _public enumerator_ `None = 0`
- L78 _public enumerator_ `Override`
- L79 _public enumerator_ `Additive`

#### class `Chaos::FSimpleWheelSim`  
`class FSimpleWheelSim : public TVehicleSystem<FSimpleWheelConfig>`  
_L160-476_
- inherits: `TVehicleSystem<FSimpleWheelConfig>`
- desc: Wheel instance data changes during the simulation
- L164 _public prototype_ `FSimpleWheelSim(const FSimpleWheelConfig* SetupIn);`
- L169 _public function_ `void SetWheelRadius(float NewRadius)` — Set the wheel radius - can change dynamically during simulation if desired
- L175 _public function_ `void SetAngularPosition(float PositionIn)` — Set the angular position in radians
- L181 _public function_ `void SetAngularVelocity(float AngularVelocityIn)` — Set the angular position in radians/sec
- L187 _public function_ `void SetMatchingSpeed(float LinearMetersPerSecondIn)` — set wheel rotational speed to match the specified linear forwards speed
- L193 _public function_ `void SetBrakeTorque(float BrakeTorqueIn, bool bEngineBrakingIn = false)` — Set the braking torque - decelerating rotational force
- L200 _public function_ `void SetDriveTorque(float EngineTorqueIn)` — Set the drive torque - accelerating rotational force
- L205 _public function_ `void SetTorqueCombineMethod(FSimpleWheelConfig::EExternalTorqueCombineMethod InCombineMethod)`
- L210 _public function_ `void SetBrakeTorqueOverride(float BrakeTorqueIn, bool bEngineBrakingIn = false)`
- L216 _public function_ `void SetDriveTorqueOverride(float EngineTorqueIn)`
- L222 _public function_ `void SetVehicleGroundSpeed(const FVector& VIn)` — Set the vehicle's speed at the wheels location in local wheel coords
- L228 _public function_ `void SetWheelLoadForce(float WheelLoadForceIn)` — Set the force pressing the wheel into the terrain - from suspension
- L243 _public function_ `void SetSurfaceFriction(float InFriction)` — Set the friction coefficient of the surface under the wheel
- L248 _public function_ `void SetOnGround(bool OnGround)`
- L253 _public function_ `void SetSteeringAngle(float InAngle)`
- L258 _public function_ `void SetMaxOmega(float InMaxOmega)`
- L263 _public function_ `void SetWheelIndex(uint32 InIndex)`
- L273 _public function_ `static float GetNormalisedFrictionFromSlipAngle(float SlipIn)` — Amount of friction we can expect after taking into account the amount the wheel slips
- L284 _public function_ `FVector GetForceFromFriction() const` — return the calculated available friction force
- L290 _public function_ `float GetEffectiveRadius() const` — Get the radius of the wheel [cm]
- L296 _public function_ `float GetAngularPosition() const` — Get the angular position of the wheel [radians]
- L302 _public function_ `float GetAngularVelocity() const` — Get the angular velocity of the wheel [radians/sec]
- L308 _public function_ `float GetWheelRPM()` — Get the wheel RPM [revolutions per minute]
- L314 _public function_ `bool InContact() const` — Is the wheel in contact with the terrain or another object
- L319 _public function_ `bool IsSlipping() const`
- L324 _public function_ `bool IsSkidding() const`
- L328 _public function_ `bool IsABSActivated() const`
- L333 _public function_ `float GetSteeringAngle() const`
- L339 _public function_ `float GetNormalizedLongitudinalSlip() const` — Get the current longitudinal slip value [0 no slip - using static friction, 1 full slip - using dynamic friction]
- L344 _public function_ `float GetNormalizedLateralSlip() const`
- L350 _public function_ `float GetWheelLoadForce() const` — Get the magnitude of the force pressing the wheel into the terrain
- L356 _public function_ `float GetSurfaceFriction() const` — Get the friction coefficient of the surface in contact with the wheel
- L362 _public function_ `float GetSlipAngle() const` — Get the slip angle for this wheel - angle between wheel forward axis and velocity vector [degrees]
- L368 _public function_ `float GetDriveTorque() const` — Get the drive torque being applied to the wheel [N.m]
- L374 _public function_ `float GetBrakeTorque() const` — Get the braking torque being applied to the wheel [N.m]
- L380 _public function_ `float GetRoadSpeed() const` — Get the road speed at the wheel
- L386 _public function_ `float GetWheelGroundSpeed() const` — Get the linear ground speed of the wheel based on its current rotational speed
- L393 _public function_ `float GetSlipMagnitude() const` — Get the difference between the wheel speed and the effective ground speed of the vehicle at the wheel positive if wheel is faster than effective ground speed, negative if wheel is slower
- L400 _public function_ `float GetSkidMagnitude() const` — Get the effective ground speed along the lateral wheel axis positive if wheel is faster than effective ground speed, negative if wheel is slower
- L412 _public prototype_ `void Simulate(float DeltaTime);` — Simulate - figure out wheel lateral and longitudinal forces based on available friction at the wheel Wheel load force from body weight and the surface friction together determine the grip available at the wheel DriveTorque accelerates the wheel BrakeTorque decelerates the wheel
- L415 _public function_ `void SetMassPerWheel(float VehicleMassPerWheel)`
- L421 _public member_ `bool BrakeEnabled;` — Regular brakes are enabled for this wheel
- L422 _public member_ `bool HandbrakeEnabled;` — Handbrake is operational on this wheel
- L423 _public member_ `bool SteeringEnabled;` — Steering is operational on this wheel
- L424 _public member_ `bool EngineEnabled;` — Wheel is driven by an engine
- L425 _public member_ `bool TractionControlEnabled;` — Straight Line Traction Control
- L426 _public member_ `bool ABSEnabled;` — Advanced braking system operational
- L427 _public member_ `float FrictionMultiplier;`
- L428 _public member_ `float LateralSlipGraphMultiplier;`
- L429 _public member_ `float CorneringStiffness;`
- L430 _public member_ `float MaxSteeringAngle;`
- L431 _public member_ `float MaxBrakeTorque;`
- L432 _public member_ `float HandbrakeTorque;`
- L433 _public member_ `FSimpleWheelConfig::EExternalTorqueCombineMethod ExternalTorqueCombineMethod;`
- L435 _public member_ `float Re;` — [cm] Effective Wheel Radius could change dynamically if get a flat?, tire shreds
- L436 _public member_ `float Omega;` — [radians/sec] Wheel Rotation Angular Velocity
- L437 _public member_ `float Sx;`
- L438 _public member_ `float Inertia;`
- L440 _public member_ `float DriveTorque;` — In
- L441 _public member_ `float BrakeTorque;` — [N.m]
- L442 _public member_ `float ForceIntoSurface;` — [N]
- L443 _public member_ `FVector GroundVelocityVector;` — [Unreal Units cm.s-1]
- L444 _public member_ `float AngularPosition;` — [radians]
- L445 _public member_ `float SteeringAngle;` — [degrees ATM]
- L446 _public member_ `float SurfaceFriction;`
- L447 _public member_ `float MaxOmega;`
- L449 _public member_ `float ExternalDriveTorque;` — [N.m]
- L450 _public member_ `float ExternalBrakeTorque;` — [N.m]
- L452 _public member_ `FVector ForceFromFriction;`
- L453 _public member_ `float MassPerWheel;`
- L457 _public member_ `float SlipVelocity;` — Relative velocity between tire patch and ground ?? vector ??
- L458 _public member_ `float SlipAngle;` — Angle between wheel forwards and velocity vector
- L459 _public member_ `bool bInContact;` — Is tire in contact with the ground or free in the air
- L460 _public member_ `uint32 WheelIndex;` — purely for debugging purposes
- L461 _public member_ `bool bEngineBraking;` — Is the braking force coming from the engine
- L465 _public member_ `float AppliedLinearDriveForce;` — debug for now
- L466 _public member_ `float AppliedLinearBrakeForce;`
- L467 _public member_ `float LongitudinalAdhesiveLimit;`
- L468 _public member_ `float LateralAdhesiveLimit;`
- L469 _public member_ `float SideSlipModifier;`
- L470 _public member_ `float Spin;`
- L471 _public member_ `float AvailableGrip;`
- L472 _public member_ `FVector InputForces;`
- L473 _public member_ `bool bClipping;`
- L474 _public member_ `bool bABSActivated;`

#### struct `Chaos::FAxleConfig`  
`struct FAxleConfig`  
_L479-483_
- L481 _public member_ `TArray<uint16> WheelIndex;` — reference to wheels on this axle
- L482 _public member_ `float RollbarScaling;`

#### class `Chaos::FAxleSim`  
`class FAxleSim : public TVehicleSystem<FAxleConfig>`  
_L485-495_
- inherits: `TVehicleSystem<FAxleConfig>`
- L489 _public prototype_ `FAxleSim();`
- L491 _public function_ `void Simulate(float DeltaTime)`
- L493 _public member_ `FAxleConfig Setup;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace Chaos`
