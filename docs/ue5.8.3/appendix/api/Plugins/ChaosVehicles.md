# Plugins / ChaosVehicles

- module root: `Plugins/Experimental/ChaosVehiclesPlugin/Source/ChaosVehicles`
- headers: 12; symbols: 967
- symbol kinds: class=11, delegate=2, enum=14, enumerator=45, function=113, member=463, namespace=1, prototype=268, struct=48, typedef=2
- PublicDependencyModuleNames: AnimGraphRuntime, ChaosVehiclesCore, ChaosVehiclesEngine, Core, CoreUObject, Engine, EngineSettings, RHI, RenderCore

### `Plugins/Experimental/ChaosVehiclesPlugin/Source/ChaosVehicles/Public/AnimNode_StageCoachWheelController.h` (Public)


#### struct `FAnimNode_StageCoachWheelController`  
`struct FAnimNode_StageCoachWheelController : public FAnimNode_SkeletalControlBase`  
_L17-63_
- reflection: `USTRUCT()`
- inherits: `FAnimNode_SkeletalControlBase`
- desc: Simple controller that replaces or adds to the translation/rotation of a single bone.
- L23 _public member_ `int WheelSpokeCount;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Alpha, meta = (PinShownByDefault))` — Number of spokes visible on wheel
- L27 _public member_ `float MaxAngularVelocity;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Alpha, meta = (PinShownByDefault))` — Wheel max rotation speed in degrees/second
- L31 _public member_ `float ShutterSpeed;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Alpha, meta = (PinShownByDefault))` — Camera shutter speed in frames/second
- L35 _public member_ `float StageCoachBlend;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Alpha, meta = (PinShownByDefault))` — Blend effect degrees/second
- L38 _public prototype_ `FAnimNode_StageCoachWheelController();`
- L41 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;` — FAnimNode_Base interface
- L45 _public prototype_ `virtual void EvaluateSkeletalControl_AnyThread(FComponentSpacePoseContext& Output, TArray<FBoneTransform>& OutBoneTransforms) override;` — FAnimNode_SkeletalControlBase interface
- L46 _public prototype_ `virtual bool IsValidToEvaluate(const USkeleton* Skeleton, const FBoneContainer& RequiredBones) override;`
- L47 _public prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;`
- L52 _private prototype_ `virtual void InitializeBoneReferences(const FBoneContainer& RequiredBones) override;` — FAnimNode_SkeletalControlBase interface
- L61 _private member_ `TArray<FWheelLookupData> Wheels;`
- L62 _private member_ `FVehicleAnimationInstanceProxy* AnimInstanceProxy;`

#### struct `FAnimNode_StageCoachWheelController::FWheelLookupData`  
`struct FWheelLookupData`  
_L55-59_
- L57 _public member_ `int32 WheelIndex;`
- L58 _public member_ `FBoneReference BoneReference;`

### `Plugins/Experimental/ChaosVehiclesPlugin/Source/ChaosVehicles/Public/AnimNode_WheelController.h` (Public)


#### struct `FAnimNode_WheelController`  
`struct FAnimNode_WheelController : public FAnimNode_SkeletalControlBase`  
_L17-46_
- reflection: `USTRUCT()`
- inherits: `FAnimNode_SkeletalControlBase`
- desc: Simple controller that replaces or adds to the translation/rotation of a single bone.
- L21 _public prototype_ `FAnimNode_WheelController();`
- L24 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;` — FAnimNode_Base interface
- L28 _public prototype_ `virtual void EvaluateSkeletalControl_AnyThread(FComponentSpacePoseContext& Output, TArray<FBoneTransform>& OutBoneTransforms) override;` — FAnimNode_SkeletalControlBase interface
- L29 _public prototype_ `virtual bool IsValidToEvaluate(const USkeleton* Skeleton, const FBoneContainer& RequiredBones) override;`
- L30 _public prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;`
- L35 _private prototype_ `virtual void InitializeBoneReferences(const FBoneContainer& RequiredBones) override;` — FAnimNode_SkeletalControlBase interface
- L44 _private member_ `TArray<FWheelLookupData> Wheels;`
- L45 _private member_ `const FVehicleAnimationInstanceProxy* AnimInstanceProxy;` — TODO: we only cache this to use in eval where it's safe. Should change API to pass proxy into eval

#### struct `FAnimNode_WheelController::FWheelLookupData`  
`struct FWheelLookupData`  
_L38-42_
- L40 _public member_ `int32 WheelIndex;`
- L41 _public member_ `FBoneReference BoneReference;`

### `Plugins/Experimental/ChaosVehiclesPlugin/Source/ChaosVehicles/Public/ChaosVehicleManager.h` (Public)


#### class `FChaosVehicleManager`  
`class FChaosVehicleManager`  
_L17-84_
- L22 _public member_ `static uint32 VehicleSetupTag;` — Updated when vehicles need to recreate their physics state. Used when values tweaked while the game is running.
- L24 _public prototype_ `FChaosVehicleManager(FPhysScene* PhysScene);`
- L25 _public prototype_ `~FChaosVehicleManager();`
- L28 _public function_ `FPhysScene_Chaos& GetScene() const` — Get Physics Scene
- L33 _public prototype_ `void AddVehicle( TWeakObjectPtr<UChaosVehicleMovementComponent> Vehicle );` — Register a Physics vehicle for processing
- L38 _public prototype_ `void RemoveVehicle( TWeakObjectPtr<UChaosVehicleMovementComponent> Vehicle );` — Unregister a Physics vehicle from processing
- L43 _public prototype_ `void ScenePreTick(FPhysScene* PhysScene, float DeltaTime);` — Update vehicle tuning and other state such as input
- L46 _public prototype_ `void DetachFromPhysScene(FPhysScene* PhysScene);` — Detach this vehicle manager from a FPhysScene (remove delegates, remove from map etc)
- L48 _public prototype_ `void Update(FPhysScene* PhysScene, float DeltaTime);`
- L49 _public prototype_ `void PostUpdate(FChaosScene* PhysScene);`
- L51 _public prototype_ `void ParallelUpdateVehicles(float DeltaSeconds);`
- L54 _public prototype_ `static FChaosVehicleManager* GetVehicleManagerFromScene(FPhysScene* PhysScene);` — Find a vehicle manager from an FPhysScene
- L56 _public prototype_ `void RegisterCallbacks();`
- L57 _public prototype_ `void UnregisterCallbacks();`
- L61 _private member_ `static TMap<FPhysScene*, FChaosVehicleManager*> SceneToVehicleManagerMap;` — Map of physics scenes to corresponding vehicle manager
- L64 _private member_ `FPhysScene_Chaos& Scene;` — The physics scene we belong to
- L66 _private member_ `static bool GInitialized;`
- L69 _private member_ `TArray<TWeakObjectPtr<UChaosVehicleMovementComponent>> Vehicles;` — All instanced vehicles
- L71 _private member_ `FDelegateHandle OnPhysScenePreTickHandle;`
- L72 _private member_ `FDelegateHandle OnPhysScenePostTickHandle;`
- L74 _private member_ `static FDelegateHandle OnPostWorldInitializationHandle;`
- L75 _private member_ `static FDelegateHandle OnWorldCleanupHandle;`
- L78 _private member_ `FChaosVehicleManagerAsyncCallback* AsyncCallback;` — Async callback from the physics engine - we can run our simulation here
- L79 _private member_ `int32 Timestamp;`
- L80 _private member_ `int32 SubStepCount;`
- L82 _private member_ `TArray<Chaos::TSimCallbackOutputHandle<FChaosVehicleManagerAsyncOutput>> PendingOutputs;`
- L83 _private member_ `Chaos::TSimCallbackOutputHandle<FChaosVehicleManagerAsyncOutput> LatestOutput;`

### `Plugins/Experimental/ChaosVehiclesPlugin/Source/ChaosVehicles/Public/ChaosVehicleManagerAsyncCallback.h` (Public)


#### enum `EChaosAsyncVehicleDataType`  
`enum EChaosAsyncVehicleDataType : int8`  
_L21-25_
- L23 _public enumerator_ `AsyncInvalid`
- L24 _public enumerator_ `AsyncDefault`

#### struct `FVehicleInputs`  
`struct FVehicleInputs`  
_L29-70_
- reflection: `USTRUCT()`
- desc: Vehicle inputs from the player controller
- L33 _public function_ `FVehicleInputs() : SteeringInput(0.f) , ThrottleInput(0.f) , BrakeInput(0.f) , PitchInput(0.f) , RollInput(0.f) , YawInput(0.f) , HandbrakeInput(0.f)`
- L45 _public member_ `float SteeringInput;` — `UPROPERTY()` — Steering output to physics system. Range -1...1
- L49 _public member_ `float ThrottleInput;` — `UPROPERTY()` — Accelerator output to physics system. Range 0...1
- L53 _public member_ `float BrakeInput;` — `UPROPERTY()` — Brake output to physics system. Range 0...1
- L57 _public member_ `float PitchInput;` — `UPROPERTY()` — Body Pitch output to physics system. Range -1...1
- L61 _public member_ `float RollInput;` — `UPROPERTY()` — Body Roll output to physics system. Range -1...1
- L65 _public member_ `float YawInput;` — `UPROPERTY()` — Body Yaw output to physics system. Range -1...1
- L69 _public member_ `float HandbrakeInput;` — `UPROPERTY()` — Handbrake output to physics system. Range 0...1

#### struct `FControlInputs`  
`struct FControlInputs : public FVehicleInputs`  
_L74-101_
- reflection: `USTRUCT()`
- inherits: `FVehicleInputs`
- desc: Control inputs holding the vehicle ones + persisten ones
- L78 _public function_ `FControlInputs() : FVehicleInputs() , ParkingEnabled(false) , TransmissionType(Chaos::ETransmissionType::Automatic) , GearUpInput(false) , GearDownInput(false)`
- L88 _public member_ `bool ParkingEnabled;` — `UPROPERTY()` — Check if the parking is enabled
- L92 _public member_ `uint8 TransmissionType;` — `UPROPERTY()` — Type of transmission (manual/auto)
- L96 _public member_ `bool GearUpInput;` — `UPROPERTY()` — Check if the user has risen the gear
- L100 _public member_ `bool GearDownInput;` — `UPROPERTY()` — Check if the user has descreased the gear

#### struct `FNetworkVehicleInputs`  
`struct FNetworkVehicleInputs : public FNetworkPhysicsData`  
_L105-145_
- reflection: `USTRUCT()`
- inherits: `FNetworkPhysicsData`
- desc: Vehicle Inputs data that will be used in the inputs history to be applied while simulating
- L111 _public member_ `FControlInputs VehicleInputs;` — `UPROPERTY()` — List of incoming control inputs coming from the local client
- L115 _public member_ `float TransmissionChangeTime = 0.0;` — `UPROPERTY()` — Transmission change time that could be set/changed from GT
- L119 _public member_ `int32 TransmissionCurrentGear = 0;` — `UPROPERTY()` — Transmission current gear that could be set/changed from GT
- L123 _public member_ `int32 TransmissionTargetGear = 0;` — `UPROPERTY()` — Transmission target gear that could be set/changed from GT
- L126 _public prototype_ `virtual void ApplyData(UActorComponent* NetworkComponent) const override;` — Apply the data onto the network physics component
- L129 _public prototype_ `virtual void BuildData(const UActorComponent* NetworkComponent) override;` — Build the data from the network physics component
- L132 _public prototype_ `virtual void DecayData(float DecayAmount) override;` — Decay input during resimulation
- L135 _public prototype_ `bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);` — Serialize data function that will be used to transfer the struct across the network
- L138 _public prototype_ `virtual void InterpolateData(const FNetworkPhysicsData& MinData, const FNetworkPhysicsData& MaxData) override;` — Interpolate the data in between two inputs data
- L141 _public prototype_ `virtual void MergeData(const FNetworkPhysicsData& FromData) override;` — Merge data into this input
- L144 _public prototype_ `virtual const FString DebugData() override;` — Return string with input debug data

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FNetworkVehicleInputs> : public TStructOpsTypeTraitsBase2<FNetworkVehicleInputs>`  
_L148-154_
- inherits: `TStructOpsTypeTraitsBase2<FNetworkVehicleInputs>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L151-153_

#### struct `FNetworkVehicleStates`  
`struct FNetworkVehicleStates : public FNetworkPhysicsData`  
_L158-212_
- reflection: `USTRUCT()`
- inherits: `FNetworkPhysicsData`
- desc: Vehicle states data that will be used in the states history to rewind the simulation at some point inn time
- L164 _public member_ `FVector StateLastVelocity = FVector(0,0,0);` — `UPROPERTY()` — Vehicle state last velocity
- L168 _public member_ `TArray<float> WheelsOmega;` — `UPROPERTY()` — Angular velocity for each wheels
- L172 _public member_ `TArray<float> WheelsAngularPosition;` — `UPROPERTY()` — Angular position for each wheels
- L176 _public member_ `TArray<float> SuspensionLastDisplacement;` — `UPROPERTY()` — Suspension latest displacement to be used while simulating
- L180 _public member_ `TArray<float> SuspensionLastSpringLength;` — `UPROPERTY()` — Suspension latest spring length to be used while simulating
- L184 _public member_ `TArray<float> SuspensionAveragedLength;` — `UPROPERTY()` — Suspension averaged length for smoothing
- L188 _public member_ `TArray<int32> SuspensionAveragedCount;` — `UPROPERTY()` — Suspension averaged count for smoothing
- L192 _public member_ `TArray<int32> SuspensionAveragedNum;` — `UPROPERTY()` — Suspension averaged number for smoothing
- L196 _public member_ `float EngineOmega = 0.0;` — `UPROPERTY()` — Engine angular velocity
- L199 _public prototype_ `virtual void ApplyData(UActorComponent* NetworkComponent) const override;` — Apply the data onto the network physics component
- L202 _public prototype_ `virtual void BuildData(const UActorComponent* NetworkComponent) override;` — Build the data from the network physics component
- L205 _public prototype_ `bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);` — Serialize data function that will be used to transfer the struct across the network
- L208 _public prototype_ `virtual void InterpolateData(const FNetworkPhysicsData& MinData, const FNetworkPhysicsData& MaxData) override;` — Interpolate the data in between two inputs data
- L211 _public prototype_ `virtual const FString DebugData() override;` — Return string with state debug data

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FNetworkVehicleStates> : public TStructOpsTypeTraitsBase2<FNetworkVehicleStates>`  
_L215-221_
- inherits: `TStructOpsTypeTraitsBase2<FNetworkVehicleStates>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L218-220_

#### struct `FWheelsOutput`  
`struct FWheelsOutput`  
_L225-326_
- reflection: `USTRUCT()`
- desc: Local physics wheels outputs not replicated across the network
- L229 _public function_ `FWheelsOutput() : InContact(false) , SteeringAngle(0.f) , AngularPosition(0.f) , AngularVelocity(0.f) , WheelRadius(0.f) , LateralAdhesiveLimit(0.f) , LongitudinalAdhesiveLimit(0.f) , SlipAngle(0.f) , bIsSlipping(false) , SlipMagnitude(0.f) , bIsSkidding(false) , SkidMagnitude(0.f) , SkidNormal(FVector(1,0,0)) , SuspensionOffset(0.f) , SpringForce(0.f) , NormalizedSuspensionLength(0.f) , DriveTorque(0.f) , BrakeTorque(0.f) , bABSActivated(false) , bBlockingHit(false) , ImpactPoint(FVector::ZeroVector) , HitLocation(FVector::ZeroVector) , PhysMaterial(nullptr)`
- L258 _public member_ `bool InContact;` — `UPROPERTY()` — wheels
- L261 _public member_ `float SteeringAngle;` — `UPROPERTY()`
- L264 _public member_ `float AngularPosition;` — `UPROPERTY()`
- L267 _public member_ `float AngularVelocity;` — `UPROPERTY()`
- L270 _public member_ `float WheelRadius;` — `UPROPERTY()`
- L273 _public member_ `float LateralAdhesiveLimit;` — `UPROPERTY()`
- L276 _public member_ `float LongitudinalAdhesiveLimit;` — `UPROPERTY()`
- L279 _public member_ `float SlipAngle;` — `UPROPERTY()`
- L282 _public member_ `bool bIsSlipping;` — `UPROPERTY()`
- L285 _public member_ `float SlipMagnitude;` — `UPROPERTY()`
- L288 _public member_ `bool bIsSkidding;` — `UPROPERTY()`
- L291 _public member_ `float SkidMagnitude;` — `UPROPERTY()`
- L294 _public member_ `FVector SkidNormal;` — `UPROPERTY()`
- L298 _public member_ `float SuspensionOffset;` — `UPROPERTY()` — suspension related
- L301 _public member_ `float SpringForce;` — `UPROPERTY()`
- L304 _public member_ `float NormalizedSuspensionLength;` — `UPROPERTY()`
- L307 _public member_ `float DriveTorque;` — `UPROPERTY()`
- L310 _public member_ `float BrakeTorque;` — `UPROPERTY()`
- L313 _public member_ `bool bABSActivated;` — `UPROPERTY()`
- L316 _public member_ `bool bBlockingHit;` — `UPROPERTY()`
- L319 _public member_ `FVector ImpactPoint;` — `UPROPERTY()`
- L322 _public member_ `FVector HitLocation;` — `UPROPERTY()`
- L325 _public member_ `TWeakObjectPtr<UPhysicalMaterial> PhysMaterial;` — `UPROPERTY()`

#### struct `FPhysicsVehicleOutput`  
`struct FPhysicsVehicleOutput`  
_L332-366_
- reflection: `USTRUCT()`
- desc: Per Vehicle Output State from Physics Thread to Game Thread
- L336 _public function_ `FPhysicsVehicleOutput() : CurrentGear(0) , TargetGear(0) , EngineRPM(0.f) , EngineTorque(0.f) , TransmissionRPM(0.f) , TransmissionTorque(0.f)`
- L347 _public member_ `TArray<FWheelsOutput> Wheels;` — `UPROPERTY()`
- L350 _public member_ `int32 CurrentGear;` — `UPROPERTY()`
- L353 _public member_ `int32 TargetGear;` — `UPROPERTY()`
- L356 _public member_ `float EngineRPM;` — `UPROPERTY()`
- L359 _public member_ `float EngineTorque;` — `UPROPERTY()`
- L362 _public member_ `float TransmissionRPM;` — `UPROPERTY()`
- L365 _public member_ `float TransmissionTorque;` — `UPROPERTY()`

#### struct `FWheelTraceParams`  
`struct FWheelTraceParams`  
_L368-372_
- L370 _public member_ `ESweepType SweepType;`
- L371 _public member_ `ESweepShape SweepShape;`

#### struct `FPhysicsVehicleInputs`  
`struct FPhysicsVehicleInputs`  
_L377-391_
- desc: Per Vehicle input State from Game Thread to Physics Thread
- L379 _public function_ `FPhysicsVehicleInputs() : GravityZ(0.0f) , TraceParams() , TraceCollisionResponse() , WheelTraceParams()`
- L386 _public member_ `float GravityZ;`
- L387 _public member_ `mutable FNetworkVehicleInputs NetworkInputs;`
- L388 _public member_ `mutable FCollisionQueryParams TraceParams;`
- L389 _public member_ `mutable FCollisionResponseContainer TraceCollisionResponse;`
- L390 _public member_ `mutable TArray<FWheelTraceParams> WheelTraceParams;`

#### struct `FPhysicsVehicleTraits`  
`struct FPhysicsVehicleTraits`  
_L393-397_
- L395 _public typedef_ `using InputsType = FNetworkVehicleInputs;`
- L396 _public typedef_ `using StatesType = FNetworkVehicleStates;`

#### struct `FChaosVehicleAsyncInput`  
`struct FChaosVehicleAsyncInput`  
_L402-425_
- desc: Per Vehicle Input State from Game Thread to Physics Thread
- L404 _public member_ `const EChaosAsyncVehicleDataType Type;`
- L405 _public member_ `UChaosVehicleMovementComponent* Vehicle;`
- L406 _public member_ `Chaos::FSingleParticlePhysicsProxy* Proxy;`
- L408 _public member_ `FPhysicsVehicleInputs PhysicsInputs;`
- L413 _public prototype_ `virtual TUniquePtr<struct FChaosVehicleAsyncOutput> Simulate(UWorld* World, const float DeltaSeconds, const float TotalSeconds, bool& bWakeOut) const;` — Vehicle simulation running on the Physics Thread
- L415 _public prototype_ `virtual void ApplyDeferredForces(Chaos::FRigidBodyHandle_Internal* RigidHandle) const;`
- L417 _public function_ `FChaosVehicleAsyncInput(EChaosAsyncVehicleDataType InType = EChaosAsyncVehicleDataType::AsyncInvalid) : Type(InType) , Vehicle(nullptr)`
- L424 _public prototype_ `virtual ~FChaosVehicleAsyncInput() = default;`

#### struct `FChaosVehicleManagerAsyncInput`  
`struct FChaosVehicleManagerAsyncInput : public Chaos::FSimCallbackInput`  
_L427-439_
- inherits: `Chaos::FSimCallbackInput`
- L429 _public member_ `TArray<TUniquePtr<FChaosVehicleAsyncInput>> VehicleInputs;`
- L431 _public member_ `TWeakObjectPtr<UWorld> World;`
- L432 _public member_ `int32 Timestamp = INDEX_NONE;`
- L434 _public function_ `void Reset()`

#### struct `FChaosVehicleAsyncOutput`  
`struct FChaosVehicleAsyncOutput`  
_L444-456_
- desc: Async Output Data
- L446 _public member_ `const EChaosAsyncVehicleDataType Type;`
- L447 _public member_ `bool bValid;` — indicates no work was done
- L448 _public member_ `FPhysicsVehicleOutput VehicleSimOutput;`
- L450 _public function_ `FChaosVehicleAsyncOutput(EChaosAsyncVehicleDataType InType = EChaosAsyncVehicleDataType::AsyncInvalid) : Type(InType) , bValid(false)`
- L455 _public prototype_ `virtual ~FChaosVehicleAsyncOutput() = default;`

#### struct `FChaosVehicleManagerAsyncOutput`  
`struct FChaosVehicleManagerAsyncOutput : public Chaos::FSimCallbackOutput`  
_L461-470_
- inherits: `Chaos::FSimCallbackOutput`
- desc: Async Output for all of the vehicles handled by this Vehicle Manager
- L463 _public member_ `TArray<TUniquePtr<FChaosVehicleAsyncOutput>> VehicleOutputs;`
- L464 _public member_ `int32 Timestamp = INDEX_NONE;`
- L466 _public function_ `void Reset()`

#### class `FChaosVehicleManagerAsyncCallback`  
`class FChaosVehicleManagerAsyncCallback : public Chaos::TSimCallbackObject<FChaosVehicleManagerAsyncInput, FChaosVehicleManagerAsyncOutput, Chaos::ESimCallbackOptions::Presimulate | Chaos::ESimCallbackOptions::Rewind>`  
_L475-482_
- inherits: `Chaos::TSimCallbackObject<FChaosVehicleManagerAsyncInput,FChaosVehicleManagerAsyncOutput,Chaos::ESimCallbackOptions::Presimulate|Chaos::ESimCallbackOptions::Rewind>`
- desc: Async callback from the Physics Engine where we can perform our vehicle simulation
- L478 _public prototype_ `virtual FName GetFNameForStatId() const override;`
- L480 _private prototype_ `virtual void ProcessInputs_Internal(int32 PhysicsStep) override;`
- L481 _private prototype_ `virtual void OnPreSimulate_Internal() override;`

#### Free symbols / members of external scopes

- L19 _delegate_ `DECLARE_STATS_GROUP(TEXT("ChaosVehicleManager"), STATGROUP_ChaosVehicleManager, S`
- L152 _enumerator_ `WithNetSerializer = true` (scope `TStructOpsTypeTraits::__anon3c817beb0103`)
- L219 _enumerator_ `WithNetSerializer = true` (scope `TStructOpsTypeTraits::__anon3c817beb0203`)

### `Plugins/Experimental/ChaosVehiclesPlugin/Source/ChaosVehicles/Public/ChaosVehicleMovementComponent.h` (Public)


#### struct `FVehicleDebugParams`  
`struct FVehicleDebugParams`  
_L34-54_
- L36 _public member_ `bool ShowCOM = false;`
- L37 _public member_ `bool ShowModelOrigin = false;`
- L38 _public member_ `bool ShowAllForces = false;`
- L39 _public member_ `bool ShowAerofoilForces = false;`
- L40 _public member_ `bool ShowAerofoilSurface = false;`
- L41 _public member_ `bool DisableTorqueControl = false;`
- L42 _public member_ `bool DisableStabilizeControl = false;`
- L43 _public member_ `bool DisableAerodynamics = false;`
- L44 _public member_ `bool DisableAerofoils = false;`
- L45 _public member_ `bool DisableThrusters = false;`
- L46 _public member_ `bool BatchQueries = false;`
- L47 _public member_ `bool CacheTraceOverlap = false;`
- L48 _public member_ `float ForceDebugScaling = 0.0006f;`
- L49 _public member_ `float SleepCounterThreshold = 15;`
- L50 _public member_ `bool DisableVehicleSleep = false;`
- L51 _public member_ `bool EnableMultithreading = true;`
- L52 _public member_ `float SetMaxMPH = 0.0f;`
- L53 _public member_ `float ControlInputWakeTolerance = 0.02f;`

#### struct `FVehicleReplicatedState`  
`struct FVehicleReplicatedState : public FVehicleInputs`  
_L59-81_
- reflection: `USTRUCT()`
- inherits: `FVehicleInputs`
- L63 _public function_ `FVehicleReplicatedState() : FVehicleInputs()`
- L72 _public member_ `int32 TargetGear;` — `UPROPERTY()` — state replication: gear
- L76 _public member_ `float ThrottleUp;` — `UPROPERTY()` — input replication: increase throttle
- L80 _public member_ `float ThrottleDown;` — `UPROPERTY()` — input replication: decrease throttle

#### struct `FVehicleTorqueControlConfig`  
`struct FVehicleTorqueControlConfig`  
_L84-156_
- reflection: `USTRUCT()`
- L89 _public function_ `FVehicleTorqueControlConfig()`
- L96 _public member_ `bool Enabled;` — `UPROPERTY(EditAnywhere, Category = Setup)` — Torque Control Enabled
- L100 _public member_ `float YawTorqueScaling;` — `UPROPERTY(EditAnywhere, Category = Setup)` — Yaw Torque Scaling
- L103 _public member_ `float YawFromSteering;` — `UPROPERTY(EditAnywhere, Category = Setup)`
- L106 _public member_ `float YawFromRollTorqueScaling;` — `UPROPERTY(EditAnywhere, Category = Setup)`
- L110 _public member_ `float PitchTorqueScaling;` — `UPROPERTY(EditAnywhere, Category = Setup)` — Pitch Torque Scaling
- L114 _public member_ `float RollTorqueScaling;` — `UPROPERTY(EditAnywhere, Category = Setup)` — Roll Torque Scaling
- L117 _public member_ `float RollFromSteering;` — `UPROPERTY(EditAnywhere, Category = Setup)`
- L121 _public member_ `float RotationDamping;` — `UPROPERTY(EditAnywhere, Category = Setup)` — Rotation damping
- L123 _public function_ `const Chaos::FTorqueControlConfig& GetTorqueControlConfig()`
- L129 _public function_ `void InitDefaults()`
- L142 _private function_ `void FillTorqueControlSetup()`
- L155 _private member_ `Chaos::FTorqueControlConfig PTorqueControlConfig;`

#### struct `FVehicleTargetRotationControlConfig`  
`struct FVehicleTargetRotationControlConfig`  
_L159-253_
- reflection: `USTRUCT()`
- L164 _public function_ `FVehicleTargetRotationControlConfig()`
- L171 _public member_ `bool Enabled;` — `UPROPERTY(EditAnywhere, Category = Setup)` — Rotation Control Enabled
- L174 _public member_ `bool bRollVsSpeedEnabled;` — `UPROPERTY(EditAnywhere, Category = Setup)`
- L177 _public member_ `float RollControlScaling;` — `UPROPERTY(EditAnywhere, Category = Setup)`
- L180 _public member_ `float RollMaxAngle;` — `UPROPERTY(EditAnywhere, Category = Setup)`
- L183 _public member_ `float PitchControlScaling;` — `UPROPERTY(EditAnywhere, Category = Setup)`
- L186 _public member_ `float PitchMaxAngle;` — `UPROPERTY(EditAnywhere, Category = Setup)`
- L190 _public member_ `float RotationStiffness;` — `UPROPERTY(EditAnywhere, Category = Setup)` — Rotation stiffness
- L194 _public member_ `float RotationDamping;` — `UPROPERTY(EditAnywhere, Category = Setup)` — Rotation damping
- L198 _public member_ `float MaxAccel;` — `UPROPERTY(EditAnywhere, Category = Setup)` — Rotation mac accel
- L201 _public member_ `float AutoCentreRollStrength;` — `UPROPERTY(EditAnywhere, Category = Setup)`
- L204 _public member_ `float AutoCentrePitchStrength;` — `UPROPERTY(EditAnywhere, Category = Setup)`
- L207 _public member_ `float AutoCentreYawStrength;` — `UPROPERTY(EditAnywhere, Category = Setup)`
- L209 _public function_ `const Chaos::FTargetRotationControlConfig& GetTargetRotationControlConfig()`
- L215 _public function_ `void InitDefaults()`
- L236 _private function_ `void FillTargetRotationControlSetup()`
- L252 _private member_ `Chaos::FTargetRotationControlConfig PTargetRotationControlConfig;`

#### struct `FVehicleStabilizeControlConfig`  
`struct FVehicleStabilizeControlConfig`  
_L256-300_
- reflection: `USTRUCT()`
- L261 _public function_ `FVehicleStabilizeControlConfig()`
- L268 _public member_ `bool Enabled;` — `UPROPERTY(EditAnywhere, Category = Setup)` — Torque Control Enabled
- L272 _public member_ `float AltitudeHoldZ;` — `UPROPERTY(EditAnywhere, Category = Setup)` — Yaw Torque Scaling
- L275 _public member_ `float PositionHoldXY;` — `UPROPERTY(EditAnywhere, Category = Setup)`
- L277 _public function_ `const Chaos::FStabilizeControlConfig& GetStabilizeControlConfig()`
- L283 _public function_ `void InitDefaults()`
- L291 _private function_ `void FillStabilizeControlSetup()`
- L298 _private member_ `Chaos::FStabilizeControlConfig PStabilizeControlConfig;`

#### struct `FVehicleState`  
`struct FVehicleState`  
_L303-357_
- desc: Commonly used state - evaluated once used wherever required
- L305 _public function_ `FVehicleState() : VehicleWorldTransform(FTransform::Identity) , VehicleWorldVelocity(FVector::ZeroVector) , VehicleLocalVelocity(FVector::ZeroVector) , VehicleWorldAngularVelocity(FVector::ZeroVector) , VehicleWorldCOM(FVector::ZeroVector) , WorldVelocityNormal(FVector::ZeroVector) , VehicleUpAxis(FVector(0.f, 0.f, 1.f)) , VehicleForwardAxis(FVector(1.f, 0.f, 0.f)) , VehicleRightAxis(FVector(0.f, 1.f, 0.f)) , LocalAcceleration(FVector::ZeroVector) , LocalGForce(FVector::ZeroVector) , LastFrameVehicleLocalVelocity(FVector::ZeroVector) , ForwardSpeed(0.f) , ForwardsAcceleration(0.f) , NumWheelsOnGround(0) , bAllWheelsOnGround(false) , bVehicleInAir(true) , bSleeping(false) , SleepCounter(0)`
- L330 _public prototype_ `void CaptureState(const FBodyInstance* TargetInstance, float GravityZ, float DeltaTime);` — Cache some useful data at the start of the frame from GT BodyInstance
- L333 _public prototype_ `void CaptureState(const Chaos::FRigidBodyHandle_Internal* Handle, float GravityZ, float DeltaTime);` — Cache some useful data at the start of the frame from Physics thread Particle Handle
- L335 _public member_ `FTransform VehicleWorldTransform;`
- L336 _public member_ `FVector VehicleWorldVelocity;`
- L337 _public member_ `FVector VehicleLocalVelocity;`
- L338 _public member_ `FVector VehicleWorldAngularVelocity;`
- L339 _public member_ `FVector VehicleWorldCOM;`
- L340 _public member_ `FVector WorldVelocityNormal;`
- L342 _public member_ `FVector VehicleUpAxis;`
- L343 _public member_ `FVector VehicleForwardAxis;`
- L344 _public member_ `FVector VehicleRightAxis;`
- L345 _public member_ `FVector LocalAcceleration;`
- L346 _public member_ `FVector LocalGForce;`
- L347 _public member_ `FVector LastFrameVehicleLocalVelocity;`
- L349 _public member_ `float ForwardSpeed;`
- L350 _public member_ `float ForwardsAcceleration;`
- L352 _public member_ `int NumWheelsOnGround;`
- L353 _public member_ `bool bAllWheelsOnGround;`
- L354 _public member_ `bool bVehicleInAir;`
- L355 _public member_ `bool bSleeping;`
- L356 _public member_ `int SleepCounter;`

#### enum `EInputFunctionType`  
`enum class EInputFunctionType : uint8`  
_L361-366_
- reflection: `UENUM()`
- desc: Input Options
- L363 _public enumerator_ `LinearFunction = 0`
- L364 _public enumerator_ `SquaredFunction`
- L365 _public enumerator_ `CustomCurve`

#### struct `FVehicleInputRateConfig`  
`struct FVehicleInputRateConfig`  
_L369-451_
- reflection: `USTRUCT()`
- L377 _public member_ `float RiseRate;` — `UPROPERTY(EditAnywhere, Category=VehicleInputRate)` — Rate at which the input value rises
- L383 _public member_ `float FallRate;` — `UPROPERTY(EditAnywhere, Category=VehicleInputRate)` — Rate at which the input value falls
- L389 _public member_ `EInputFunctionType InputCurveFunction;` — `UPROPERTY(EditAnywhere, Category=VehicleInputRate)` — Controller input curve, various predefined options, linear, squared, or user can specify a custom curve function
- L396 _public member_ `FRuntimeFloatCurve UserCurve;` — `UPROPERTY(EditAnywhere, Category = VehicleInputRate)` — Controller input curve - should be a normalized float curve, i.e. time from 0 to 1 and values between 0 and 1 This curve is only sued if the InputCurveFunction above is set to CustomCurve
- L398 _public function_ `FVehicleInputRateConfig() : RiseRate(5.0f), FallRate(5.0f), InputCurveFunction(EInputFunctionType::LinearFunction)`
- L401 _public function_ `float InterpInputValue(float DeltaTime, float CurrentValue, float NewValue) const` — Change an output value using max rise and fall rates
- L415 _public function_ `float CalcControlFunction(float InputValue)`

#### enum `EVehicleAerofoilType`  
`enum class EVehicleAerofoilType : uint8`  
_L455-461_
- reflection: `UENUM()`
- L457 _public enumerator_ `Fixed = 0`
- L458 _public enumerator_ `Wing` — affected by Roll input
- L459 _public enumerator_ `Rudder` — affected by steering/yaw input
- L460 _public enumerator_ `Elevator` — affected by Pitch input

#### enum `EVehicleThrustType`  
`enum class EVehicleThrustType : uint8`  
_L465-472_
- reflection: `UENUM()`
- L467 _public enumerator_ `Fixed = 0`
- L468 _public enumerator_ `Wing` — affected by Roll input
- L469 _public enumerator_ `Rudder` — affected by steering/yaw input
- L470 _public enumerator_ `Elevator` — affected by Pitch input

#### struct `FVehicleAerofoilConfig`  
`struct FVehicleAerofoilConfig`  
_L476-549_
- reflection: `USTRUCT()`
- L480 _public function_ `FVehicleAerofoilConfig()`
- L487 _public member_ `EVehicleAerofoilType AerofoilType;` — `UPROPERTY(EditAnywhere, Category = AerofoilSetup)` — Does this aerofoil represent a fixed spoiler, an aircraft wing, etc how is controlled.
- L491 _public member_ `FName BoneName;` — `UPROPERTY(EditAnywhere, Category = AerofoilSetup)` — Bone name on mesh where aerofoil is centered
- L495 _public member_ `FVector Offset;` — `UPROPERTY(EditAnywhere, Category = AerofoilSetup)` — Additional offset to give the aerofoil.
- L499 _public member_ `FVector UpAxis;` — `UPROPERTY(EditAnywhere, Category = AerofoilSetup)` — Up Axis of aerofoil.
- L503 _public member_ `float Area;` — `UPROPERTY(EditAnywhere, Category = AerofoilSetup)` — Area of aerofoil surface [Meters Squared] - larger value creates more lift but also more drag
- L507 _public member_ `float Camber;` — `UPROPERTY(EditAnywhere, Category = AerofoilSetup)` — camber of wing - leave as zero for a rudder - can be used to trim/level elevator for level flight
- L511 _public member_ `float MaxControlAngle;` — `UPROPERTY(EditAnywhere, Category = AerofoilSetup)` — The angle in degrees through which the control surface moves - leave at 0 if it is a fixed surface
- L514 _public member_ `float StallAngle;` — `UPROPERTY(EditAnywhere, Category = AerofoilSetup)`
- L518 _public member_ `float LiftMultiplier;` — `UPROPERTY(EditAnywhere, Category = AerofoilSetup)` — cheat to control amount of lift independently from lift
- L522 _public member_ `float DragMultiplier;` — `UPROPERTY(EditAnywhere, Category = AerofoilSetup)` — cheat to control amount of drag independently from lift, a value of zero will offer no drag
- L524 _public function_ `const Chaos::FAerofoilConfig& GetPhysicsAerofoilConfig(const UChaosVehicleMovementComponent& MovementComponent)`
- L530 _public function_ `void InitDefaults()`
- L546 _private prototype_ `void FillAerofoilSetup(const UChaosVehicleMovementComponent& MovementComponent);`
- L548 _private member_ `Chaos::FAerofoilConfig PAerofoilConfig;`

#### struct `FVehicleThrustConfig`  
`struct FVehicleThrustConfig`  
_L552-617_
- reflection: `USTRUCT()`
- L556 _public function_ `FVehicleThrustConfig()`
- L563 _public member_ `EVehicleThrustType ThrustType;` — `UPROPERTY(EditAnywhere, Category = ThrustSetup)` — Does this aerofoil represent a fixed spoiler, an aircraft wing, etc how is controlled.
- L567 _public member_ `FName BoneName;` — `UPROPERTY(EditAnywhere, Category = ThrustSetup)` — Bone name on mesh where thrust is located
- L571 _public member_ `FVector Offset;` — `UPROPERTY(EditAnywhere, Category = ThrustSetup)` — Additional offset to give the location, or use in preference to the bone
- L575 _public member_ `FVector ThrustAxis;` — `UPROPERTY(EditAnywhere, Category = ThrustSetup)` — Up Axis of thrust.
- L587 _public member_ `float MaxThrustForce;` — `UPROPERTY(EditAnywhere, Category = ThrustSetup)` — Maximum thrust force
- L591 _public member_ `float MaxControlAngle;` — `UPROPERTY(EditAnywhere, Category = ThrustSetup)` — The angle in degrees through which the control surface moves - leave at 0 if it is a fixed surface
- L594 _public function_ `const Chaos::FSimpleThrustConfig& GetPhysicsThrusterConfig(const UChaosVehicleMovementComponent& MovementComponent)` — #todo:ControlAxes - X, Y, Z, or X & Y, etc
- L600 _public function_ `void InitDefaults()`
- L613 _private prototype_ `void FillThrusterSetup(const UChaosVehicleMovementComponent& MovementComponent);`
- L615 _private member_ `Chaos::FSimpleThrustConfig PThrusterConfig;`

#### class `UChaosVehicleSimulation`  
`class UChaosVehicleSimulation`  
_L619-714_
- L622 _public function_ `virtual ~UChaosVehicleSimulation()`
- L627 _public function_ `virtual void Init(TUniquePtr<Chaos::FSimpleWheeledVehicle>& PVehicleIn)`
- L632 _public function_ `virtual void UpdateConstraintHandles(TArray<FPhysicsConstraintHandle>& ConstraintHandlesIn)`
- L634 _public prototype_ `virtual void TickVehicle(UWorld* WorldIn, float DeltaTime, const FChaosVehicleAsyncInput& InputData, FChaosVehicleAsyncOutput& OutputData, Chaos::FRigidBodyHandle_Internal* Handle);`
- L637 _public prototype_ `void SyncHistoryInputs(const FChaosVehicleAsyncInput& InputData, Chaos::FRigidBodyHandle_Internal* Handle);` — Update the async inputs and the history ones
- L640 _public prototype_ `virtual void ApplyDeferredForces(Chaos::FRigidBodyHandle_Internal* Handle);` — Apply the defered forces onto the vehicles
- L643 _public prototype_ `virtual void UpdateState(float DeltaTime, const FChaosVehicleAsyncInput& InputData, Chaos::FRigidBodyHandle_Internal* Handle);` — Update the vehicle state
- L646 _public prototype_ `virtual void UpdateSimulation(float DeltaTime, const FChaosVehicleAsyncInput& InputData, Chaos::FRigidBodyHandle_Internal* Handle);` — Advance the vehicle simulation
- L649 _public prototype_ `virtual void FillOutputState(FChaosVehicleAsyncOutput& Output);` — Fill the vehicle output state
- L652 _public function_ `virtual bool CanSimulate() const` — Are enough vehicle systems specified such that physics vehicle simulation is possible
- L655 _public prototype_ `virtual void ApplyInput(const FControlInputs& ControlInputs, float DeltaTime);` — Pass control Input to the vehicle systems
- L658 _public prototype_ `virtual void ApplyAerodynamics(float DeltaTime);` — Apply aerodynamic forces to vehicle body
- L661 _public prototype_ `virtual void ApplyAerofoilForces(float DeltaTime);` — Apply Aerofoil forces to vehicle body
- L664 _public prototype_ `virtual void ApplyThrustForces(float DeltaTime);` — Apply Thruster forces to vehicle body
- L667 _public prototype_ `virtual void ApplyTorqueControl(float DeltaTime, const FChaosVehicleAsyncInput& InputData);` — Apply direct control over vehicle body rotation
- L670 _public prototype_ `void AddForce(const FVector& Force, bool bAllowSubstepping = true, bool bAccelChange = false);` — Add a force to this vehicle
- L673 _public prototype_ `void AddForceAtPosition(const FVector& Force, const FVector& Position, bool bAllowSubstepping = true, bool bIsLocalForce = false);` — Add a force at a particular position (world space when bIsLocalForce = false, body space otherwise)
- L676 _public prototype_ `void AddImpulse(const FVector& Impulse, bool bVelChange);` — Add an impulse to this vehicle
- L679 _public prototype_ `void AddImpulseAtPosition(const FVector& Impulse, const FVector& Position);` — Add an impulse to this vehicle and a particular world position
- L682 _public prototype_ `void AddTorqueInRadians(const FVector& Torque, bool bAllowSubstepping = true, bool bAccelChange = false);` — Add a torque to this vehicle
- L685 _public prototype_ `void InitializeWheel(int WheelIndex, const Chaos::FSimpleWheelConfig* InWheelSetup);` — Reinitialize a wheel at runtime
- L688 _public prototype_ `void InitializeSuspension(int WheelIndex, const Chaos::FSimpleSuspensionConfig* InSuspensionSetup);` — Reinitialize the physics suspension at runtime
- L691 _public prototype_ `virtual void DrawDebug3D();` — Draw debug text for the wheels and suspension
- L692 _public member_ `UWorld* World;`
- L695 _public member_ `Chaos::FRigidBodyHandle_Internal* RigidHandle;` — Physics Thread Representation of chassis rigid body
- L697 _public member_ `FVehicleState VehicleState;`
- L700 _public member_ `TUniquePtr<Chaos::FSimpleWheeledVehicle> PVehicle;` — #todo: this isn't very configurable
- L702 _public member_ `FDeferredForces DeferredForces;`
- L705 _public member_ `FControlInputs VehicleInputs;` — Current control inputs that is being used on the PT
- L707 _public member_ `FVehicleInputRateConfig ThrottleInputRate;`
- L708 _public member_ `FVehicleInputRateConfig SteeringInputRate;`
- L709 _public member_ `FVehicleInputRateConfig BrakeInputRate;`
- L710 _public member_ `FVehicleInputRateConfig HandbrakeInputRate;`
- L711 _public member_ `FVehicleInputRateConfig RollInputRate;`
- L712 _public member_ `FVehicleInputRateConfig PitchInputRate;`
- L713 _public member_ `FVehicleInputRateConfig YawInputRate;`

#### class `UChaosVehicleMovementComponent`  
`class UChaosVehicleMovementComponent : public UPawnMovementComponent`  
_L721-1326_
- reflection: `UCLASS(Abstract, hidecategories = (PlanarMovement, "Components|Movement|Planar", Activation, "Components|Activation"))`
- inherits: `UPawnMovementComponent`
- desc: Base component to handle the vehicle simulation for an actor.
- L738 _private member_ `uint8 bReverseAsBrake : 1;` — `UPROPERTY(EditAnywhere, Category = VehicleSetup)` — If true, the brake and reverse controls will behave in a more arcade fashion where holding reverse also functions as brake. For a more realistic approach turn this off
- L742 _private member_ `uint8 bThrottleAsBrake : 1;` — `UPROPERTY(EditAnywhere, Category = VehicleSetup, meta = (EditCondition = "bReverseAsBrake"))` — If true, when reversing the throttle will behave like a brake while the vehicle moving in a backwards direction - requires bReverseAsBrake to be enabled for operation
- L748 _public member_ `float Mass;` — `UPROPERTY(EditAnywhere, Category = VehicleSetup, meta = (ClampMin = "0.01", UIMin = "0.01"))` — Mass to set the vehicle chassis to. It's much easier to tweak vehicle settings when the mass doesn't change due to tweaks with the physics asset. [kg]
- L754 _public member_ `bool bEnableCenterOfMassOverride;` — `UPROPERTY(EditAnywhere, Category = VehicleSetup)` — Enable to override the calculated COM position with your own fixed value - this prevents the vehicle handling changing when the asset changes
- L760 _public member_ `FVector CenterOfMassOverride;` — `UPROPERTY(EditAnywhere, Category = VehicleSetup, meta = (EditCondition = "bEnableCenterOfMassOverride"))` — The center of mass override value, this value overrides the calculated COM and the COM offset value in the mesh is also ignored.
- L764 _public member_ `float ChassisWidth;` — `UPROPERTY(EditAnywhere, Category = VehicleSetup, meta = (ClampMin = "0.01", UIMin = "0.01"))` — Chassis width used for drag force computation (cm)
- L768 _public member_ `float ChassisHeight;` — `UPROPERTY(EditAnywhere, Category = VehicleSetup, meta = (ClampMin = "0.01", UIMin = "0.01"))` — Chassis height used for drag force computation (cm)
- L772 _public member_ `float DragCoefficient;` — `UPROPERTY(EditAnywhere, Category = VehicleSetup)` — DragCoefficient of the vehicle chassis - force resisting forward motion at speed
- L776 _public member_ `float DownforceCoefficient;` — `UPROPERTY(EditAnywhere, Category = VehicleSetup)` — DownforceCoefficient of the vehicle chassis - force pressing vehicle into ground at speed
- L780 _public member_ `float DragArea;` — `UPROPERTY(transient)` — Drag area in Meters^2
- L784 _public member_ `float DebugDragMagnitude;` — `UPROPERTY(transient)` — Debug drag magnitude last applied
- L788 _public member_ `FVector InertiaTensorScale;` — `UPROPERTY(EditAnywhere, Category = VehicleSetup, AdvancedDisplay)` — Scales the vehicle's inertia in each direction (forward, right, up)
- L792 _public member_ `float SleepThreshold;` — `UPROPERTY(EditAnywhere, Category = VehicleSetup)` — Option to apply some aggressive sleep logic, larger number is more agressive, 0 disables
- L796 _public member_ `float SleepSlopeLimit;` — `UPROPERTY(EditAnywhere, Category = VehicleSetup, meta = (ClampMin = "0.01", UIMin = "0.01", ClampMax = "1.0", UIMax = "1.0"))` — Option to apply some aggressive sleep logic if slopes up Z is less than this value, i.e value = Cos(SlopeAngle) so 0.866 will sleep up to 30 degree slopes
- L800 _public member_ `TArray<FVehicleAerofoilConfig> Aerofoils;` — `UPROPERTY(EditAnywhere, Category = AerofoilSetup)` — Optional aerofoil setup - can be used for car spoilers or aircraft wings/elevator/rudder
- L804 _public member_ `TArray<FVehicleThrustConfig> Thrusters;` — `UPROPERTY(EditAnywhere, Category = ThrusterSetup)` — Optional thruster setup, use one or more as your main engine or as supplementary booster
- L808 _public member_ `FVehicleTorqueControlConfig TorqueControl;` — `UPROPERTY(EditAnywhere, Category = ArcadeControl)` — Arcade style direct control of vehicle rotation via torque force
- L812 _public member_ `FVehicleTargetRotationControlConfig TargetRotationControl;` — `UPROPERTY(EditAnywhere, Category = ArcadeControl)` — Arcade style direct control of vehicle rotation via torque force
- L816 _public member_ `FVehicleStabilizeControlConfig StabilizeControl;` — `UPROPERTY(EditAnywhere, Category = ArcadeControl)` — Arcade style control of vehicle
- L819 _public member_ `uint32 VehicleSetupTag;` — Used to recreate the physics if the blueprint changes.
- L824 _protected member_ `uint8 bRawHandbrakeInput : 1;` — `UPROPERTY(Transient)` — True if the player is holding the handbrake
- L828 _protected member_ `uint8 bRawGearUpInput : 1;` — `UPROPERTY(Transient)` — True if the player is holding gear up
- L832 _protected member_ `uint8 bRawGearDownInput : 1;` — `UPROPERTY(Transient)` — True if the player is holding gear down
- L836 _protected member_ `uint32 bWasAvoidanceUpdated : 1;` — `UPROPERTY(Transient)` — Was avoidance updated in this frame?
- L839 _protected member_ `uint8 bParkEnabled : 1;` — `UPROPERTY(Transient)`
- L841 _protected member_ `Chaos::ETransmissionType TransmissionType;`
- L844 _protected member_ `TObjectPtr<UNetworkPhysicsComponent> NetworkPhysicsComponent = nullptr;` — `UPROPERTY()`
- L849 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject interface
- L854 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;` — Respond to a property change in editor
- L858 _public prototype_ `virtual void SetUpdatedComponent(USceneComponent* NewUpdatedComponent) override;` — Overridden to allow registration with components NOT owned by a Pawn.
- L861 _public prototype_ `virtual void SetOverrideController(AController* OverrideController);` — Allow the player controller of a different pawn to control this vehicle
- L865 _public prototype_ `virtual bool ShouldCreatePhysicsState() const override;` — Return true if it's suitable to create a physics representation of the vehicle at this time
- L868 _public prototype_ `virtual bool HasValidPhysicsState() const override;` — Returns true if the physics state exists
- L871 _public prototype_ `virtual bool CanCreateVehicle() const;` — Return true if we are ready to create a vehicle, false if the setup has missing references
- L874 _public prototype_ `virtual void OnCreatePhysicsState() override;` — Used to create any physics engine information for this component
- L877 _public prototype_ `virtual void OnDestroyPhysicsState() override;` — Used to shut down and physics engine structure for this component
- L880 _public prototype_ `virtual void PreTickGT(float DeltaTime);` — Updates the vehicle tuning and other state such as user input.
- L883 _public prototype_ `virtual void StopMovementImmediately() override;` — Stops movement immediately (zeroes velocity, usually zeros acceleration for components with acceleration).
- L887 _public prototype_ `void SetThrottleInput(float Throttle);` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ChaosVehicleMovement")` — Set the user input for the vehicle throttle [range 0 to 1]
- L891 _public prototype_ `void IncreaseThrottleInput(float ThrottleDelta);` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ChaosVehicleMovement")` — Increase the vehicle throttle position [throttle range normalized 0 to 1]
- L895 _public prototype_ `void DecreaseThrottleInput(float ThrottleDelta);` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ChaosVehicleMovement")` — Decrease the vehicle throttle position  [throttle range normalized 0 to 1]
- L899 _public prototype_ `void SetBrakeInput(float Brake);` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ChaosVehicleMovement")` — Set the user input for the vehicle Brake [range 0 to 1]
- L903 _public prototype_ `void SetSteeringInput(float Steering);` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ChaosVehicleMovement")` — Set the user input for the vehicle steering [range -1 to 1]
- L907 _public prototype_ `void SetPitchInput(float Pitch);` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ChaosVehicleMovement")` — Set the user input for the vehicle pitch [range -1 to 1]
- L911 _public prototype_ `void SetRollInput(float Roll);` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ChaosVehicleMovement")` — Set the user input for the vehicle roll [range -1 to 1]
- L915 _public prototype_ `void SetYawInput(float Yaw);` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ChaosVehicleMovement")` — Set the user input for the vehicle yaw [range -1 to 1]
- L919 _public prototype_ `void SetHandbrakeInput(bool bNewHandbrake);` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ChaosVehicleMovement")` — Set the user input for handbrake
- L923 _public prototype_ `void SetParked(bool bParked);` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ChaosVehicleMovement")` — Set the vehicle in park mode
- L927 _public prototype_ `void SetSleeping(bool bEnableSleep);` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ChaosVehicleMovement")` — Set the vehicle sleeping (bEnableSleep=true) or wake it up (bEnableSleep=false)
- L931 _public prototype_ `void SetChangeUpInput(bool bNewGearUp);` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ChaosVehicleMovement")` — Set the user input for gear up
- L935 _public prototype_ `void SetChangeDownInput(bool bNewGearDown);` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ChaosVehicleMovement")` — Set the user input for gear down
- L939 _public prototype_ `void SetTargetGear(int32 GearNum, bool bImmediate);` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ChaosVehicleMovement")` — Set the user input for gear (-1 reverse, 0 neutral, 1+ forward)
- L943 _public prototype_ `void SetUseAutomaticGears(bool bUseAuto);` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ChaosVehicleMovement")` — Set the flag that will be used to select auto-gears
- L947 _public prototype_ `void SetRequiresControllerForInputs(bool bRequiresController);` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ChaosVehicleMovement")` — Set the flag that determines whether a controller is required to set control inputs
- L951 _public prototype_ `int32 GetCurrentGear() const;` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ChaosVehicleMovement")` — Get current gear
- L955 _public prototype_ `int32 GetTargetGear() const;` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ChaosVehicleMovement")` — Get target gear
- L959 _public prototype_ `bool GetUseAutoGears() const;` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ChaosVehicleMovement")` — Are gears being changed automatically?
- L963 _public prototype_ `float GetForwardSpeed() const;` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ChaosVehicleMovement")` — How fast the vehicle is moving forward
- L967 _public prototype_ `float GetForwardSpeedMPH() const;` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ChaosVehicleMovement")` — How fast the vehicle is moving forward
- L971 _public function_ `float GetThrottleInput()` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ChaosVehicleMovement")` — Get the user input for the vehicle throttle - can use this to feed control to a connected trailer
- L975 _public function_ `float GetBrakeInput()` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ChaosVehicleMovement")` — Get the user input for the vehicle brake - can use this to feed control to a connected trailer
- L979 _public function_ `bool GetHandbrakeInput() const` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ChaosVehicleMovement")` — Get the user input for the vehicle handbrake - can use this to feed control to a connected trailer
- L983 _public function_ `float GetSteeringInput()` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ChaosVehicleMovement")` — Get the user input for the vehicle steering - can use this to feed control to a connected trailer
- L988 _public prototype_ `bool IsParked() const;` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ChaosVehicleMovement")` — Is the vehicle in park mode
- L992 _public function_ `void ResetVehicle()` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ChaosVehicleMovement")` — Reset some vehicle state - call this if you are say creating pool of vehicles that get reused and you don't want to carry over the previous state
- L995 _public prototype_ `void GetBaseSnapshot(FBaseSnapshotData& SnapshotOut) const;` — Grab a snapshot of the vehicle instance dynamic state
- L998 _public prototype_ `void SetBaseSnapshot(const FBaseSnapshotData& SnapshotIn);` — Set snapshot of vehicle instance dynamic state
- L1001 _public function_ `void EnableSelfRighting(bool InState)` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ChaosVehicleMovement")`
- L1009 _public prototype_ `FVector LocateBoneOffset(const FName InBoneName, const FVector& InExtraOffset) const;` — location local coordinates of named bone in skeleton, apply additional offset or just use offset if no bone located
- L1011 _public function_ `TUniquePtr<FPhysicsVehicleOutput>& PhysicsVehicleOutput()`
- L1016 _public function_ `virtual float GetSuspensionOffset(int WheelIndex)`
- L1019 _public prototype_ `TUniquePtr<FChaosVehicleAsyncInput> SetCurrentAsyncInputOutput(int32 InputIdx, FChaosVehicleManagerAsyncOutput* CurOutput, FChaosVehicleManagerAsyncOutput* NextOutput, float Alpha, int32 VehicleManagerTimestamp);` — ----ASYNC----
- L1021 _public prototype_ `void SetCurrentAsyncInputOutputInternal(FChaosVehicleAsyncInput* CurInput, int32 InputIdx, FChaosVehicleManagerAsyncOutput* CurOutput, int32 VehicleManagerTimestamp);`
- L1022 _public prototype_ `void SetCurrentAsyncInputOutputInternal(FChaosVehicleAsyncInput* CurInput, int32 InputIdx, FChaosVehicleManagerAsyncOutput* CurOutput, FChaosVehicleManagerAsyncOutput* NextOutput, float Alpha, int32 VehicleManagerTimestamp);`
- L1024 _public prototype_ `virtual void Update(float DeltaTime);`
- L1026 _public prototype_ `virtual void ResetVehicleState();`
- L1029 _public prototype_ `virtual void ParallelUpdate(float DeltaSeconds);` — Get output data from Physics Thread
- L1031 _public prototype_ `void FinalizeSimCallbackData(FChaosVehicleManagerAsyncInput& Input);`
- L1033 _public member_ `EChaosAsyncVehicleDataType CurAsyncType;`
- L1034 _public member_ `FChaosVehicleAsyncInput* CurAsyncInput;`
- L1035 _public member_ `struct FChaosVehicleAsyncOutput* CurAsyncOutput;`
- L1036 _public member_ `struct FChaosVehicleAsyncOutput* NextAsyncOutput;`
- L1037 _public member_ `float OutputInterpAlpha;`
- L1050 _public member_ `TArray<FAsyncOutputWrapper> OutputsWaitingOn;`
- L1056 _protected member_ `FVehicleReplicatedState ReplicatedState;` — `UPROPERTY(Transient, Replicated)` — replicated state of vehicle
- L1059 _protected member_ `float AngErrorAccumulator;` — accumulator for RB replication errors
- L1063 _protected member_ `float RawSteeringInput;` — `UPROPERTY(Transient)` — What the player has the steering set to. Range -1...1
- L1067 _protected member_ `float RawThrottleInput;` — `UPROPERTY(Transient)` — What the player has the accelerator set to. Range -1...1
- L1071 _protected member_ `float RawBrakeInput;` — `UPROPERTY(Transient)` — What the player has the brake set to. Range -1...1
- L1075 _protected member_ `float RawPitchInput;` — `UPROPERTY(Transient)` — What the player has the pitch set to. Range -1...1
- L1079 _protected member_ `float RawRollInput;` — `UPROPERTY(Transient)` — What the player has the roll set to. Range -1...1
- L1083 _protected member_ `float RawYawInput;` — `UPROPERTY(Transient)` — What the player has the yaw set to. Range -1...1
- L1087 _protected member_ `float SteeringInput;` — `UPROPERTY(Transient)` — Steering output to physics system. Range -1...1
- L1091 _protected member_ `float ThrottleInput;` — `UPROPERTY(Transient)` — Accelerator output to physics system. Range 0...1
- L1095 _protected member_ `float BrakeInput;` — `UPROPERTY(Transient)` — Brake output to physics system. Range 0...1
- L1099 _protected member_ `float PitchInput;` — `UPROPERTY(Transient)` — Body Pitch output to physics system. Range -1...1
- L1103 _protected member_ `float RollInput;` — `UPROPERTY(Transient)` — Body Roll output to physics system. Range -1...1
- L1107 _protected member_ `float YawInput;` — `UPROPERTY(Transient)` — Body Yaw output to physics system. Range -1...1
- L1111 _protected member_ `float HandbrakeInput;` — `UPROPERTY(Transient)` — Handbrake output to physics system. Range 0...1
- L1115 _protected member_ `bool bRequiresControllerForInputs;` — `UPROPERTY(EditAnywhere, Category = VehicleInput)` — Bypass the need for a controller in order for the controls to be processed.
- L1119 _protected member_ `float IdleBrakeInput;` — `UPROPERTY(EditAnywhere, Category = VehicleInput)` — How much to press the brake when the player has release throttle
- L1123 _protected member_ `float StopThreshold;` — `UPROPERTY(EditAnywhere, Category = VehicleInput)` — Auto-brake when absolute vehicle forward speed is less than this (cm/s)
- L1127 _protected member_ `float WrongDirectionThreshold;` — `UPROPERTY(EditAnywhere, Category = VehicleInput)` — Auto-brake when vehicle forward speed is opposite of player input by at least this much (cm/s)
- L1132 _public member_ `FVehicleInputRateConfig ThrottleInputRate;` — `UPROPERTY(EditAnywhere, Category = VehicleInput, AdvancedDisplay)` — Rate at which input throttle can rise and fall
- L1136 _public member_ `FVehicleInputRateConfig BrakeInputRate;` — `UPROPERTY(EditAnywhere, Category = VehicleInput, AdvancedDisplay)` — Rate at which input brake can rise and fall
- L1140 _public member_ `FVehicleInputRateConfig SteeringInputRate;` — `UPROPERTY(EditAnywhere, Category = VehicleInput, AdvancedDisplay)` — Rate at which input steering can rise and fall
- L1144 _public member_ `FVehicleInputRateConfig HandbrakeInputRate;` — `UPROPERTY(EditAnywhere, Category = VehicleInput, AdvancedDisplay)` — Rate at which input handbrake can rise and fall
- L1148 _public member_ `FVehicleInputRateConfig PitchInputRate;` — `UPROPERTY(EditAnywhere, Category = VehicleInput, AdvancedDisplay)` — Rate at which input pitch can rise and fall
- L1152 _public member_ `FVehicleInputRateConfig RollInputRate;` — `UPROPERTY(EditAnywhere, Category = VehicleInput, AdvancedDisplay)` — Rate at which input roll can rise and fall
- L1156 _public member_ `FVehicleInputRateConfig YawInputRate;` — `UPROPERTY(EditAnywhere, Category = VehicleInput, AdvancedDisplay)` — Rate at which input yaw can rise and fall
- L1159 _public prototype_ `void ApplyMigratedVehicleState();`
- L1166 _protected prototype_ `float CalcSteeringInput();` — Compute steering input
- L1169 _protected prototype_ `void CalcThrottleBrakeInput(float& ThrottleOut, float& BrakeOut);` — Compute throttle & brake input
- L1172 _protected prototype_ `float CalcHandbrakeInput();` — Compute handbrake input
- L1175 _protected prototype_ `float CalcPitchInput();` — Compute pitch input
- L1178 _protected prototype_ `float CalcRollInput();` — Compute roll input
- L1181 _protected prototype_ `float CalcYawInput();` — Compute yaw input
- L1184 _protected prototype_ `float CalcThrottleUpInput();` — Compute throttle inputs
- L1185 _protected prototype_ `float CalcThrottleDownInput();`
- L1191 _protected prototype_ `virtual void ClearInput();` — Clear all interpolated inputs to default values. Raw input won't be cleared, the vehicle may resume input based movement next frame.
- L1197 _protected prototype_ `virtual void ClearRawInput();` — Clear all raw inputs to default values. Interpolated input won't be cleared, the vehicle will begin interpolating to no input.
- L1199 _protected function_ `void ClearAllInput()`
- L1208 _protected prototype_ `virtual void UpdateState(float DeltaTime);` — Read current state for simulation
- L1211 _protected prototype_ `virtual void ProcessSleeping(const FControlInputs& ControlInputs);` — Option to aggressively sleep the vehicle
- L1215 _protected prototype_ `void ServerUpdateState(float InSteeringInput, float InThrottleInput, float InBrakeInput , float InHandbrakeInput, int32 InCurrentGear, float InRollInput, float InPitchInput, float InYawInput);` — `UFUNCTION(reliable, server, WithValidation)` — Pass current state to server
- L1221 _protected prototype_ `virtual AController* GetController() const override;` — Get our controller
- L1224 _protected prototype_ `APlayerController* GetPlayerController() const;` — Retrieve the player controller of the vehicle component
- L1227 _protected prototype_ `class UMeshComponent* GetMesh() const;` — Get the mesh this vehicle is tied to
- L1230 _protected prototype_ `USkeletalMeshComponent* GetSkeletalMesh();` — Get Mesh cast as USkeletalMeshComponent, may return null if cast fails
- L1233 _protected prototype_ `UStaticMeshComponent* GetStaticMesh();` — Get Mesh cast as UStaticMeshComponent, may return null if cast fails
- L1236 _protected prototype_ `virtual void CreateVehicle();` — Create and setup the Chaos vehicle
- L1238 _protected prototype_ `virtual TUniquePtr<Chaos::FSimpleWheeledVehicle> CreatePhysicsVehicle();`
- L1241 _protected function_ `virtual void FixupSkeletalMesh()` — Skeletal mesh needs some special handling in the vehicle case
- L1244 _protected prototype_ `virtual void SetupVehicle(TUniquePtr<Chaos::FSimpleWheeledVehicle>& PVehicle);` — Allocate and setup the Chaos vehicle
- L1247 _protected prototype_ `virtual void PostSetupVehicle();` — Do some final setup after the Chaos vehicle gets created
- L1250 _protected prototype_ `virtual void SetupVehicleMass();` — Adjust the Chaos Physics mass
- L1252 _protected prototype_ `void UpdateMassProperties(FBodyInstance* BI);`
- L1255 _protected prototype_ `virtual void ComputeConstants();` — When vehicle is created we want to compute some helper data like drag area, etc.... Derived classes should use this to properly compute things like engine RPM
- L1259 _protected prototype_ `void ShowDebugInfo(class AHUD* HUD, class UCanvas* Canvas, const class FDebugDisplayInfo& DisplayInfo, float& YL, float& YPos);`
- L1262 _protected prototype_ `virtual void DrawDebug(UCanvas* Canvas, float& YL, float& YPos);` — Draw debug text for the wheels and suspension
- L1265 _protected prototype_ `void DrawLine2D(UCanvas* Canvas, const FVector2D& StartPos, const FVector2D& EndPos, FColor Color, float Thickness = 1.f);` — draw 2D debug line to UI canvas
- L1268 _protected prototype_ `bool CanSendMigratedPhysicsState(const FUObjectMigrationContext* MigrationContext, EObjectMigrationSendType ObjMigrationSendType) const;`
- L1271 _protected prototype_ `virtual void MigratePhysicsState(FArchive& Ar);` — migrates physics related state (such as vehicle ouput)
- L1273 _protected prototype_ `virtual void PostMigrate(const struct FUObjectMigrationContext& MigrationContext) override;`
- L1276 _protected function_ `float GetForwardAcceleration()`
- L1281 _protected prototype_ `FBodyInstance* GetBodyInstance();`
- L1282 _protected prototype_ `const FBodyInstance* GetBodyInstance() const;`
- L1283 _protected member_ `FVehicleState VehicleState;`
- L1284 _protected member_ `TUniquePtr<FPhysicsVehicleOutput> PVehicleOutput;` — FVehicleState VehicleState;							  Useful vehicle state captured at start of frame
- L1287 _protected member_ `FDelegateHandle MeshOnPhysicsStateChangeHandle;` — Handle for delegate registered on mesh component
- L1291 _protected member_ `TUniquePtr<UChaosVehicleSimulation> VehicleSimulationPT;`
- L1294 _protected member_ `TObjectPtr<AController> OverrideController;` — `UPROPERTY(transient, Replicated)`
- L1296 _protected function_ `const Chaos::FSimpleAerodynamicsConfig& GetAerodynamicsConfig()`
- L1302 _protected function_ `void FillAerodynamicsSetup()`
- L1309 _protected prototype_ `void WakeAllEnabledRigidBodies();`
- L1310 _protected prototype_ `void PutAllEnabledRigidBodiesToSleep();`
- L1313 _protected member_ `Chaos::FSimpleAerodynamicsConfig PAerodynamicsSetup;`
- L1314 _protected member_ `int32 TargetGear;`
- L1316 _protected member_ `float PrevSteeringInput;`
- L1317 _protected member_ `float PrevReplicatedSteeringInput;`
- L1318 _protected member_ `bool bUsingNetworkPhysicsPrediction;`
- L1322 _private member_ `bool bIsMigrated = false;`
- L1323 _private member_ `FNetworkVehicleStates MigratedVehicleStates;`
- L1324 _private member_ `bool bIsVehicleStatesMigrated = false;`

#### struct `UChaosVehicleMovementComponent::FAsyncOutputWrapper`  
`struct FAsyncOutputWrapper`  
_L1039-1049_
- L1041 _public member_ `int32 Idx;`
- L1042 _public member_ `int32 Timestamp;`
- L1044 _public function_ `FAsyncOutputWrapper() : Idx(INDEX_NONE) , Timestamp(INDEX_NONE)`

#### Free symbols / members of external scopes

- L27 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogVehicle, Log, All);`
- L27 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogVehicle, Log, All);`

### `Plugins/Experimental/ChaosVehiclesPlugin/Source/ChaosVehicles/Public/ChaosVehicleWheel.h` (Public)


#### enum `ESweepShape`  
`enum class ESweepShape : uint8`  
_L25-35_
- reflection: `UENUM()`
- L28 _public enumerator_ `Raycast UMETA(DisplayName = "Raycast")` — Use ray to determine suspension length to ground - fastest
- L31 _public enumerator_ `Spherecast UMETA(DisplayName = "Spherecast")` — Use sphere to determine suspension length to ground
- L34 _public enumerator_ `Shapecast UMETA(DisplayName = "Shapecast")` — Use wheel collision shape to determine suspension length to ground - Slowest

#### enum `ESweepType`  
`enum class ESweepType : uint8`  
_L38-44_
- reflection: `UENUM()`
- L41 _public enumerator_ `SimpleSweep UMETA(DisplayName = "SimpleSweep")` — Sweeps against simple geometry only
- L43 _public enumerator_ `ComplexSweep UMETA(DisplayName = "ComplexSweep")` — Sweeps against complex geometry only

#### enum `EAxleType`  
`enum class EAxleType : uint8`  
_L47-52_
- reflection: `UENUM()`
- L49 _public enumerator_ `Undefined = 0`
- L50 _public enumerator_ `Front`
- L51 _public enumerator_ `Rear`

#### enum `ETorqueCombineMethod`  
`enum class ETorqueCombineMethod : uint8`  
_L55-63_
- reflection: `UENUM()`
- L58 _public enumerator_ `None = 0` — External torque value has no effect - default
- L60 _public enumerator_ `Override` — completely replace existing torques, can set and forget will apply same torque every frame until zeroed
- L62 _public enumerator_ `Additive` — Combine external torque with existing torques, must set external torque every frame

#### class `UChaosVehicleWheel`  
`class UChaosVehicleWheel : public UObject`  
_L66-422_
- reflection: `UCLASS(BlueprintType, Blueprintable)`
- inherits: `UObject`
- L75 _private member_ `TObjectPtr<class UStaticMesh> CollisionMesh;` — `UPROPERTY(EditDefaultsOnly, Category = Shape)` — Static mesh with collision setup for wheel, will be used to create wheel shape (if empty, sphere will be added as wheel shape, check bDontCreateShape flag)
- L79 _private member_ `EAxleType AxleType;` — `UPROPERTY(EditAnywhere, Category = Wheel)` — If left undefined then the bAffectedByEngine value is used, if defined then bAffectedByEngine is ignored and the differential setup on the vehicle defines which wheels get power from the engine
- L86 _private member_ `FVector Offset;` — `UPROPERTY(EditAnywhere, Category = Wheel)` — If BoneName is specified, offset the wheel from the bone's location. Otherwise this offsets the wheel from the vehicle's origin.
- L90 _private member_ `float WheelRadius;` — `UPROPERTY(EditAnywhere, Category = Wheel, meta = (ClampMin = "0.01", UIMin = "0.01"))` — Radius of the wheel
- L94 _private member_ `float WheelWidth;` — `UPROPERTY(EditAnywhere, Category = Wheel, meta = (ClampMin = "0.01", UIMin = "0.01"))` — Width of the wheel
- L98 _private member_ `float WheelMass;` — `UPROPERTY(EditAnywhere, Category = Wheel, meta = (ClampMin = "0.01", UIMin = "0.01"))` — Mass of the wheel Kg
- L102 _private member_ `float CorneringStiffness;` — `UPROPERTY(EditAnywhere, Category = Wheel)` — Tyre Cornering Ability
- L106 _private member_ `float FrictionForceMultiplier;` — `UPROPERTY(EditAnywhere, Category = Wheel)` — Friction Force Multiplier
- L110 _private member_ `float SideSlipModifier;` — `UPROPERTY(EditAnywhere, Category = Wheel, meta = (ClampMin = "0.0", UIMin = "0.0", ClampMax = "1.0", UIMax = "1.0"))` — Wheel Lateral Skid Grip Loss, lower number less grip on skid
- L114 _private member_ `float SlipThreshold;` — `UPROPERTY(EditAnywhere, Category = Wheel, meta = (ClampMin = "0.0", UIMin = "0.0"))` — Wheel Longitudinal Slip Threshold
- L118 _private member_ `float SkidThreshold;` — `UPROPERTY(EditAnywhere, Category = Wheel, meta = (ClampMin = "0.0", UIMin = "0.0"))` — Wheel Lateral Skid Threshold
- L122 _private member_ `float MaxSteerAngle;` — `UPROPERTY(EditAnywhere, Category = WheelsSetup)` — steer angle in degrees for this wheel
- L126 _private member_ `bool bAffectedBySteering;` — `UPROPERTY(EditAnywhere, Category = WheelsSetup)` — Whether steering should affect this wheel
- L130 _private member_ `bool bAffectedByBrake;` — `UPROPERTY(EditAnywhere, Category = Wheel)` — Whether brake should affect this wheel
- L134 _private member_ `bool bAffectedByHandbrake;` — `UPROPERTY(EditAnywhere, Category = Wheel)` — Whether handbrake should affect this wheel
- L138 _private member_ `bool bAffectedByEngine;` — `UPROPERTY(EditAnywhere, Category = Wheel)` — Whether engine should power this wheel
- L142 _private member_ `bool bABSEnabled;` — `UPROPERTY(EditAnywhere, Category = Wheel)` — Advanced Braking System Enabled
- L146 _private member_ `bool bTractionControlEnabled;` — `UPROPERTY(EditAnywhere, Category = Wheel)` — Straight Line Traction Control Enabled
- L150 _private member_ `float MaxWheelspinRotation;` — `UPROPERTY(EditAnywhere, Category = Wheel)` — Max Wheelspin rotation rad/sec
- L154 _private member_ `ETorqueCombineMethod ExternalTorqueCombineMethod;` — `UPROPERTY(EditAnywhere, Category = Wheel)` — Determines how the SetDriveTorque/SetBrakeTorque inputs are combined with the internal torques
- L157 _private member_ `FRuntimeFloatCurve LateralSlipGraph;` — `UPROPERTY(EditAnywhere, Category = Setup)`
- L161 _private member_ `FVector SuspensionAxis;` — `UPROPERTY(EditAnywhere, Category = Suspension)` — Local body direction in which where suspension forces are applied (typically along -Z-axis)
- L165 _private member_ `FVector SuspensionForceOffset;` — `UPROPERTY(EditAnywhere, Category = Suspension)` — Vertical offset from where suspension forces are applied (along Z-axis)
- L169 _private member_ `float SuspensionMaxRaise;` — `UPROPERTY(EditAnywhere, Category = Suspension)` — How far the wheel can go above the resting position
- L173 _private member_ `float SuspensionMaxDrop;` — `UPROPERTY(EditAnywhere, Category = Suspension)` — How far the wheel can drop below the resting position
- L177 _private member_ `float SuspensionDampingRatio;` — `UPROPERTY(EditAnywhere, Category = Suspension)` — Suspension damping, larger value causes the suspension to come to rest faster [range 0 to 1]
- L186 _private member_ `float WheelLoadRatio;` — `UPROPERTY(EditAnywhere, Category = Suspension, meta = (ClampMin = "0.0", UIMin = "0.0", ClampMax = "1.0", UIMax = "1.0"))` — Amount wheel load effects wheel friction. At 0 wheel friction is completely independent of the loading on the wheel (This is artificial as it always assumes even balance between all wheels) At 1 wheel friction is based on the force pressing wheel into the ground. This is more realistic. Lower value cures lift off over-steer, generally makes vehicle easier to handle under extreme motions.
- L190 _private member_ `float SpringRate;` — `UPROPERTY(EditAnywhere, Category = Suspension)` — Spring Force (N/m)
- L194 _private member_ `float SpringPreload;` — `UPROPERTY(EditAnywhere, Category = Suspension)` — Spring Preload (N/m)
- L198 _private member_ `int SuspensionSmoothing;` — `UPROPERTY(EditAnywhere, Category = Suspension, meta = (ClampMin = "0.0", UIMin = "0", ClampMax = "10.0", UIMax = "10"))` — Smooth suspension [0-off, 10-max] - Warning might cause momentary visual inter-penetration of the wheel against objects/terrain
- L202 _private member_ `float RollbarScaling;` — `UPROPERTY(EditAnywhere, Category = Suspension, meta = (ClampMin = "0.0", UIMin = "0", ClampMax = "1.0", UIMax = "1"))` — Anti-roll effect
- L206 _private member_ `ESweepShape SweepShape;` — `UPROPERTY(EditAnywhere, Category = Suspension)` — Wheel suspension trace type, defaults to ray trace
- L210 _private member_ `ESweepType SweepType;` — `UPROPERTY(EditAnywhere, Category = Suspension)` — Whether wheel suspension considers simple, complex
- L214 _private member_ `float MaxBrakeTorque;` — `UPROPERTY(EditAnywhere, Category = Brakes)` — max brake torque for this wheel (Nm)
- L221 _private member_ `float MaxHandBrakeTorque;` — `UPROPERTY(EditAnywhere, Category = Brakes)` — Max handbrake brake torque for this wheel (Nm). A handbrake should have a stronger brake torque than the brake. This will be ignored for wheels that are not affected by the handbrake.
- L225 _private member_ `TObjectPtr<class UChaosWheeledVehicleMovementComponent> VehicleComponent;` — `UPROPERTY(transient)` — The vehicle that owns us
- L229 _private member_ `int32 WheelIndex;` — `UPROPERTY(transient)` — Our index in the vehicle's (and setup's) wheels array
- L233 _private member_ `float DebugLongSlip;` — `UPROPERTY(transient)` — Longitudinal slip experienced by the wheel
- L237 _private member_ `float DebugLatSlip;` — `UPROPERTY(transient)` — Lateral slip experienced by the wheel
- L241 _private member_ `float DebugNormalizedTireLoad;` — `UPROPERTY(transient)` — How much force the tire experiences at rest divided by how much force it is experiencing now
- L244 _private member_ `float DebugTireLoad;` — How much force the tire is experiencing now
- L248 _private member_ `float DebugWheelTorque;` — `UPROPERTY(transient)` — Wheel torque
- L252 _private member_ `float DebugLongForce;` — `UPROPERTY(transient)` — Longitudinal force the wheel is applying to the chassis
- L256 _private member_ `float DebugLatForce;` — `UPROPERTY(transient)` — Lateral force the wheel is applying to the chassis
- L260 _private member_ `FVector Location;` — `UPROPERTY(transient)` — Worldspace location of this wheel
- L264 _private member_ `FVector OldLocation;` — `UPROPERTY(transient)` — Worldspace location of this wheel last frame
- L268 _private member_ `FVector Velocity;` — `UPROPERTY(transient)` — Current velocity of the wheel center (change in location over time)
- L271 _private prototype_ `float GetSteerAngle() const;` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|WheeledVehicleMovement")`
- L274 _private prototype_ `float GetRotationAngle() const;` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|WheeledVehicleMovement")`
- L277 _private prototype_ `float GetRotationAngularVelocity() const;` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|WheeledVehicleMovement")`
- L280 _private prototype_ `float GetSuspensionOffset() const;` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|WheeledVehicleMovement")`
- L283 _private prototype_ `float GetWheelRadius() const;` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|WheeledVehicleMovement")`
- L286 _private prototype_ `float GetWheelAngularVelocity() const;` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|WheeledVehicleMovement")`
- L289 _private prototype_ `FVector GetSuspensionAxis() const;` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|WheeledVehicleMovement")`
- L292 _private prototype_ `bool IsInAir() const;` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|WheeledVehicleMovement")`
- L295 _private function_ `EAxleType GetAxleType()` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|WheeledVehicleMovement")`
- L301 _private prototype_ `virtual void Init(class UChaosWheeledVehicleMovementComponent* InVehicleSim, int32 InWheelIndex);` — Initialize this wheel instance
- L306 _private prototype_ `virtual void Shutdown();` — Notify this wheel it will be removed from the scene
- L311 _private prototype_ `struct FChaosWheelSetup& GetWheelSetup();` — Get the Axle setup we were created from
- L316 _private prototype_ `virtual void Tick(float DeltaTime);` — Tick this class when the vehicle ticks
- L323 _private prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;` — Respond to a property change in editor
- L332 _protected prototype_ `FVector GetPhysicsLocation();` — Get the wheel's location in physics land
- L336 _private prototype_ `FChaosVehicleManager* GetVehicleManager() const;`
- L338 _private function_ `void FillWheelSetup()`
- L382 _private function_ `void FillSuspensionSetup()`
- L402 _private member_ `Chaos::FSimpleWheelConfig PWheelConfig;`
- L403 _private member_ `Chaos::FSimpleSuspensionConfig PSuspensionConfig;`
- L407 _public function_ `const Chaos::FSimpleWheelConfig& GetPhysicsWheelConfig()`
- L413 _public function_ `const Chaos::FSimpleSuspensionConfig& GetPhysicsSuspensionConfig()`
- L420 _public prototype_ `UPhysicalMaterial* GetContactSurfaceMaterial();` — Get contact surface material

### `Plugins/Experimental/ChaosVehiclesPlugin/Source/ChaosVehicles/Public/ChaosVehiclesPlugin.h` (Public)


#### class `IChaosVehiclesPlugin`  
`class IChaosVehiclesPlugin : public IModuleInterface`  
_L13-49_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L17 _public prototype_ `virtual void StartupModule();`
- L18 _public prototype_ `virtual void ShutdownModule();`
- L27 _public function_ `static inline IChaosVehiclesPlugin& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L37 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L44 _private prototype_ `void PhysSceneInit(FPhysScene* PhysScene);`
- L45 _private prototype_ `void PhysSceneTerm(FPhysScene* PhysScene);`
- L47 _private member_ `FDelegateHandle OnPhysSceneInitHandle;`
- L48 _private member_ `FDelegateHandle OnPhysSceneTermHandle;`

### `Plugins/Experimental/ChaosVehiclesPlugin/Source/ChaosVehicles/Public/ChaosWheeledVehicleMovementComponent.h` (Public)


#### struct `FWheeledVehicleDebugParams`  
`struct FWheeledVehicleDebugParams`  
_L19-44_
- L21 _public member_ `bool ShowWheelCollisionNormal = false;`
- L22 _public member_ `bool ShowSuspensionRaycasts = false;`
- L23 _public member_ `bool ShowSuspensionLimits = false;`
- L24 _public member_ `bool ShowWheelForces = false;`
- L25 _public member_ `bool ShowSuspensionForces = false;`
- L26 _public member_ `bool ShowBatchQueryExtents = false;`
- L27 _public member_ `bool ShowRaycastComponent = false;`
- L28 _public member_ `bool ShowRaycastMaterial = false;`
- L29 _public member_ `bool CacheSuspensionOffset = true;`
- L30 _public member_ `int TraceTypeOverride = 0;`
- L32 _public member_ `bool DisableSuspensionForces = false;`
- L33 _public member_ `bool DisableFrictionForces = false;`
- L34 _public member_ `bool DisableRollbarForces = false;`
- L35 _public member_ `bool DisableConstraintSuspension = false;`
- L37 _public member_ `float ThrottleOverride = 0.f;`
- L38 _public member_ `float SteeringOverride = 0.f;`
- L40 _public member_ `bool ResetPerformanceMeasurements = false;`
- L42 _public member_ `float OverlapTestExpansionXY = 100.f;`
- L43 _public member_ `float OverlapTestExpansionZ = 50.f;`

#### enum `EDebugPages`  
`enum EDebugPages : uint8`  
_L51-61_
- desc: There is too much information for one screen full of debug data, so sub-pages of information are available Advance through pages using p.Vehicles.NextDebugPage | p.Vehicles.PrevDebugPage which can be hooked up to the keyboard or a controller in blueprint using execCommand
- L53 _public enumerator_ `BasicPage = 0`
- L54 _public enumerator_ `PerformancePage`
- L55 _public enumerator_ `SteeringPage`
- L56 _public enumerator_ `FrictionPage`
- L57 _public enumerator_ `SuspensionPage`
- L58 _public enumerator_ `TransmissionPage`
- L60 _public enumerator_ `MaxDebugPages` — keep as last value

#### enum `EVehicleDifferential`  
`enum class EVehicleDifferential : uint8`  
_L64-70_
- reflection: `UENUM()`
- L66 _public enumerator_ `Undefined`
- L67 _public enumerator_ `AllWheelDrive`
- L68 _public enumerator_ `FrontWheelDrive`
- L69 _public enumerator_ `RearWheelDrive`

#### struct `FWheelStatus`  
`struct FWheelStatus`  
_L78-180_
- reflection: `USTRUCT(BlueprintType)`
- desc: Structure containing information about the status of a single wheel of the vehicle.
- L84 _public member_ `bool bInContact;` — `UPROPERTY()` — This wheel is in contact with the ground
- L88 _public member_ `FVector ContactPoint;` — `UPROPERTY()` — Wheel contact point
- L92 _public member_ `FVector HitLocation;` — `UPROPERTY()` — Wheel contact location
- L96 _public member_ `TWeakObjectPtr<class UPhysicalMaterial> PhysMaterial;` — `UPROPERTY()` — Material that wheel is in contact with
- L100 _public member_ `float NormalizedSuspensionLength;` — `UPROPERTY()` — Normalized suspension length at this wheel
- L104 _public member_ `float SpringForce;` — `UPROPERTY()` — Spring Force that is occurring at wheel suspension
- L108 _public member_ `float SlipAngle;` — `UPROPERTY()` — Slip angle at the wheel - difference between wheel local direction and velocity at wheel
- L112 _public member_ `bool bIsSlipping;` — `UPROPERTY()` — Is the wheel slipping
- L116 _public member_ `float SlipMagnitude;` — `UPROPERTY()` — Magnitude of slippage of wheel, difference between wheel speed and ground speed
- L121 _public member_ `bool bIsSkidding;` — `UPROPERTY()` — Is the wheel skidding
- L125 _public member_ `float SkidMagnitude;` — `UPROPERTY()` — Magnitude of skid
- L129 _public member_ `FVector SkidNormal;` — `UPROPERTY()` — Direction of skid, i.e. normalized direction
- L133 _public member_ `float DriveTorque;` — `UPROPERTY()` — Drive torque currently applied at wheel
- L137 _public member_ `float BrakeTorque;` — `UPROPERTY()` — Brake torque currently applied at wheel
- L141 _public member_ `bool bABSActivated;` — `UPROPERTY()` — Is the ABS currently engaged - useful for audio Q's
- L143 _public function_ `FWheelStatus()`
- L148 _public function_ `explicit FWheelStatus(EForceInit InInit)`
- L153 _public function_ `explicit FWheelStatus(ENoInit NoInit)`
- L158 _public function_ `void Init()`
- L177 _public prototype_ `FString ToString() const;`
- L179 _public member_ `bool bIsValid;`

#### struct `FVehicleDifferentialConfig`  
`struct FVehicleDifferentialConfig`  
_L183-220_
- reflection: `USTRUCT()`
- L187 _public function_ `FVehicleDifferentialConfig()`
- L194 _public member_ `EVehicleDifferential DifferentialType;` — `UPROPERTY(EditAnywhere, Category=Setup)` — Type of differential
- L198 _public member_ `float FrontRearSplit;` — `UPROPERTY(EditAnywhere, Category = Setup, meta = (ClampMin = "0.0", UIMin = "0.0", ClampMax = "1.0", UIMax = "1.0"))` — Ratio of torque split between front and rear (<0.5 means more to front, >0.5 means more to rear, works only with 4W type)
- L200 _public function_ `const Chaos::FSimpleDifferentialConfig& GetPhysicsDifferentialConfig()`
- L206 _public function_ `void InitDefaults()`
- L212 _public function_ `void FillDifferentialSetup()`
- L218 _public member_ `Chaos::FSimpleDifferentialConfig PDifferentialConfig;`

#### struct `FVehicleEngineConfig`  
`struct FVehicleEngineConfig`  
_L223-309_
- reflection: `USTRUCT()`
- L227 _public function_ `FVehicleEngineConfig()`
- L234 _public member_ `FRuntimeFloatCurve TorqueCurve;` — `UPROPERTY(EditAnywhere, Category = Setup)` — Torque [Normalized 0..1] for a given RPM
- L238 _public member_ `float MaxTorque;` — `UPROPERTY(EditAnywhere, Category = Setup)` — Max Engine Torque (Nm) is multiplied by TorqueCurve
- L242 _public member_ `float MaxRPM;` — `UPROPERTY(EditAnywhere, Category = Setup, meta = (ClampMin = "0.01", UIMin = "0.01"))` — Maximum revolutions per minute of the engine
- L246 _public member_ `float EngineIdleRPM;` — `UPROPERTY(EditAnywhere, Category = Setup, meta = (ClampMin = "0.01", UIMin = "0.01"))` — Idle RMP of engine then in neutral/stationary
- L250 _public member_ `float EngineBrakeEffect;` — `UPROPERTY(EditAnywhere, Category = Setup)` — Braking effect from engine, when throttle released
- L254 _public member_ `float EngineRevUpMOI;` — `UPROPERTY(EditAnywhere, Category = Setup, meta = (ClampMin = "0.01", UIMin = "0.01"))` — Affects how fast the engine RPM speed up
- L258 _public member_ `float EngineRevDownRate;` — `UPROPERTY(EditAnywhere, Category = Setup, meta = (ClampMin = "0.01", UIMin = "0.01"))` — Affects how fast the engine RPM slows down
- L260 _public function_ `const Chaos::FSimpleEngineConfig& GetPhysicsEngineConfig()`
- L266 _public function_ `void InitDefaults()`
- L276 _public function_ `float GetTorqueFromRPM(float EngineRPM)`
- L286 _private function_ `void FillEngineSetup()`
- L307 _private member_ `Chaos::FSimpleEngineConfig PEngineConfig;`

#### struct `FVehicleTransmissionConfig`  
`struct FVehicleTransmissionConfig`  
_L312-427_
- reflection: `USTRUCT()`
- L316 _public function_ `FVehicleTransmissionConfig()`
- L325 _public member_ `bool bUseAutomaticGears;` — `UPROPERTY(EditAnywhere, Category = VehicleSetup, meta=(DisplayName = "Automatic Transmission"))` — Whether to use automatic transmission
- L328 _public member_ `bool bUseAutoReverse;` — `UPROPERTY(EditAnywhere, Category = VehicleSetup, meta = (DisplayName = "Automatic Reverse"))`
- L332 _public member_ `float FinalRatio;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = Setup)` — The final gear ratio multiplies the transmission gear ratios.
- L336 _public member_ `TArray<float> ForwardGearRatios;` — `UPROPERTY(EditAnywhere, Category = Setup, AdvancedDisplay)` — Forward gear ratios
- L340 _public member_ `TArray<float> ReverseGearRatios;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = Setup)` — Reverse gear ratio(s)
- L344 _public member_ `float ChangeUpRPM;` — `UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0", UIMin = "0.0", ClampMax = "50000.0", UIMax = "50000.0"), Category = Setup)` — Engine Revs at which gear up change ocurrs
- L348 _public member_ `float ChangeDownRPM;` — `UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0", UIMin = "0.0", ClampMax = "50000.0", UIMax = "50000.0"), Category = Setup)` — Engine Revs at which gear down change ocurrs
- L352 _public member_ `float GearChangeTime;` — `UPROPERTY(EditAnywhere, Category = Setup, meta = (ClampMin = "0.0", UIMin = "0.0"))` — Time it takes to switch gears (seconds)
- L356 _public member_ `float TransmissionEfficiency;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = Setup)` — Mechanical frictional losses mean transmission might operate at 0.94 (94% efficiency)
- L358 _public function_ `const Chaos::FSimpleTransmissionConfig& GetPhysicsTransmissionConfig()`
- L364 _public function_ `void InitDefaults()`
- L384 _public function_ `float GetGearRatio(int32 InGear)`
- L403 _private function_ `void FillTransmissionSetup()`
- L425 _private member_ `Chaos::FSimpleTransmissionConfig PTransmissionConfig;`

#### enum `ESteeringType`  
`enum class ESteeringType : uint8`  
_L433-438_
- reflection: `UENUM()`
- desc: Single angle : both wheels steer by the same amount AngleRatio   : outer wheels on corner steer less than the inner ones by set ratio Ackermann	 : Ackermann steering principle is applied
- L435 _public enumerator_ `SingleAngle`
- L436 _public enumerator_ `AngleRatio`
- L437 _public enumerator_ `Ackermann`

#### struct `FVehicleSteeringConfig`  
`struct FVehicleSteeringConfig`  
_L442-510_
- reflection: `USTRUCT()`
- L446 _public function_ `FVehicleSteeringConfig()`
- L455 _public member_ `ESteeringType SteeringType;` — `UPROPERTY(EditAnywhere, Category = SteeringSetup)` — Single angle : both wheels steer by the same amount AngleRatio   : outer wheels on corner steer less than the inner ones by set ratio Ackermann	 : Ackermann steering principle is applied
- L459 _public member_ `float AngleRatio;` — `UPROPERTY(EditAnywhere, Category = SteeringSetup)` — Only applies when AngleRatio is selected
- L463 _public member_ `FRuntimeFloatCurve SteeringCurve;` — `UPROPERTY(EditAnywhere, Category = SteeringSetup)` — Maximum steering versus forward speed (MPH)
- L466 _public function_ `const Chaos::FSimpleSteeringConfig& GetPhysicsSteeringConfig(FVector2D WheelTrackDimensions)`
- L472 _public function_ `void InitDefaults()`
- L487 _private function_ `void FillSteeringSetup(FVector2D WheelTrackDimensions)`
- L508 _private member_ `Chaos::FSimpleSteeringConfig PSteeringConfig;`

#### struct `FChaosWheelSetup`  
`struct FChaosWheelSetup`  
_L514-535_
- reflection: `USTRUCT()`
- L520 _public member_ `TSubclassOf<UChaosVehicleWheel> WheelClass;` — `UPROPERTY(EditAnywhere, Category = WheelSetup)` — The wheel class to use
- L528 _public member_ `FName BoneName;` — `UPROPERTY(EditAnywhere, Category = WheelSetup)` — Bone name on mesh to create wheel at
- L532 _public member_ `FVector AdditionalOffset;` — `UPROPERTY(EditAnywhere, Category = WheelSetup)` — Additional offset to give the wheels for this axle.
- L534 _public prototype_ `FChaosWheelSetup();`

#### struct `FWheelState`  
`struct FWheelState`  
_L538-560_
- desc: Commonly used Wheel state - evaluated once used wherever required for that frame
- L540 _public prototype_ `FWheelState();`
- L541 _public prototype_ `~FWheelState();`
- L543 _public prototype_ `FWheelState(const FWheelState& Other);`
- L544 _public prototype_ `FWheelState& operator=(const FWheelState& Other);`
- L546 _public prototype_ `void Init(int NumWheels);`
- L549 _public prototype_ `void CaptureState(int WheelIdx, const FVector& WheelOffset, const FBodyInstance* TargetInstance);` — Commonly used Wheel state - evaluated once used wherever required for that frame
- L550 _public prototype_ `void CaptureState(int WheelIdx, const FVector& WheelOffset, const Chaos::FRigidBodyHandle_Internal* Handle);`
- L551 _public prototype_ `void CaptureState(int WheelIdx, const FVector& WheelOffset, const Chaos::FRigidBodyHandle_Internal* VehicleHandle, const FVector& ContactPoint, const Chaos::FRigidBodyHandle_Internal* SurfaceHandle);`
- L552 _public prototype_ `static FVector GetVelocityAtPoint(const Chaos::FRigidBodyHandle_Internal* Rigid, const FVector& InPoint);`
- L554 _public member_ `TArray<FVector> WheelLocalLocation;`
- L555 _public member_ `TArray<FVector> WheelWorldLocation;` — TArray<FVector> WheelLocalLocation;	  Current Location Of Wheels In Local Coordinates
- L556 _public member_ `TArray<FVector> WorldWheelVelocity;` — TArray<FVector> WheelWorldLocation;	  Current Location Of Wheels In World Coordinates
- L557 _public member_ `TArray<FVector> LocalWheelVelocity;` — TArray<FVector> WorldWheelVelocity;   Current velocity at wheel location In World Coordinates - combined linear and angular
- L558 _public member_ `TArray<Chaos::FSuspensionTrace> Trace;` — TArray<FVector> LocalWheelVelocity;   Local velocity of Wheel
- L559 _public member_ `TArray<FHitResult> TraceResult;`

#### class `UChaosWheeledVehicleSimulation`  
`class UChaosWheeledVehicleSimulation : public UChaosVehicleSimulation`  
_L564-628_
- inherits: `UChaosVehicleSimulation`
- L568 _public prototype_ `UChaosWheeledVehicleSimulation();`
- L570 _public prototype_ `virtual ~UChaosWheeledVehicleSimulation();`
- L572 _public function_ `virtual void Init(TUniquePtr<Chaos::FSimpleWheeledVehicle>& PVehicleIn) override`
- L579 _public prototype_ `virtual void UpdateConstraintHandles(TArray<FPhysicsConstraintHandle>& ConstraintHandlesIn) override;`
- L581 _public prototype_ `virtual void TickVehicle(UWorld* WorldIn, float DeltaTime, const FChaosVehicleAsyncInput& InputData, FChaosVehicleAsyncOutput& OutputData, Chaos::FRigidBodyHandle_Internal* Handle) override;`
- L584 _public prototype_ `virtual void UpdateSimulation(float DeltaTime, const FChaosVehicleAsyncInput& InputData, Chaos::FRigidBodyHandle_Internal* Handle) override;` — Advance the vehicle simulation
- L587 _public prototype_ `virtual void UpdateState(float DeltaTime, const FChaosVehicleAsyncInput& InputData, Chaos::FRigidBodyHandle_Internal* Handle) override;` — Update the vehicle state
- L589 _public prototype_ `virtual void FillOutputState(FChaosVehicleAsyncOutput& Output) override;`
- L592 _public prototype_ `virtual bool CanSimulate() const override;` — Are enough vehicle systems specified such that physics vehicle simulation is possible
- L595 _public prototype_ `virtual void ApplyInput(const FControlInputs& ControlInputs, float DeltaTime) override;` — Pass control Input to the vehicle systems
- L598 _public prototype_ `virtual void PerformSuspensionTraces(const TArray<Chaos::FSuspensionTrace>& SuspensionTrace, FCollisionQueryParams& TraceParams, FCollisionResponseContainer& CollisionResponse, TArray<FWheelTraceParams>& WheelTraceParams);` — Perform suspension ray/shape traces
- L602 _public prototype_ `virtual void ProcessMechanicalSimulation(float DeltaTime);` — Update the engine/transmission simulation
- L605 _public prototype_ `virtual void ProcessSteering(const FControlInputs& ControlInputs);` — Process steering mechanism
- L608 _public prototype_ `virtual void ApplyWheelFrictionForces(float DeltaTime);` — calculate and apply lateral and longitudinal friction forces from wheels
- L611 _public prototype_ `virtual void ApplySuspensionForces(float DeltaTime, TArray<FWheelTraceParams>& WheelTraceParams);` — calculate and apply chassis suspension forces
- L613 _public prototype_ `bool IsWheelSpinning() const;`
- L614 _public prototype_ `bool ContainsTraces(const FBox& Box, const TArray<struct Chaos::FSuspensionTrace>& SuspensionTrace);`
- L618 _public prototype_ `virtual void DrawDebug3D() override;` — Draw 3D debug lines and things along side the 3D model
- L620 _public member_ `FWheelState WheelState;`
- L622 _public member_ `TArray<FPhysicsConstraintHandle> ConstraintHandles;`
- L625 _public member_ `TArray<FOverlapResult> OverlapResults;` — cache trace overlap query
- L626 _public member_ `bool bOverlapHit;`
- L627 _public member_ `FBox QueryBox;`

#### class `UChaosWheeledVehicleMovementComponent`  
`class UChaosWheeledVehicleMovementComponent : public UChaosVehicleMovementComponent`  
_L633-963_
- reflection: `UCLASS(ClassGroup = (Physics), meta = (BlueprintSpawnableComponent), hidecategories = (PlanarMovement, "Components|Movement|Planar", Activation, "Components|Activation"))`
- inherits: `UChaosVehicleMovementComponent`
- L638 _private member_ `bool bSuspensionEnabled;` — `UPROPERTY(EditAnywhere, Category = WheelSetup)`
- L641 _private member_ `bool bWheelFrictionEnabled;` — `UPROPERTY(EditAnywhere, Category = WheelSetup)`
- L644 _private member_ `bool bLegacyWheelFrictionPosition;` — `UPROPERTY(EditAnywhere, Category = WheelSetup)`
- L648 _private member_ `TArray<FChaosWheelSetup> WheelSetups;` — `UPROPERTY(EditAnywhere, Category = WheelSetup)` — Wheels to create
- L651 _private member_ `struct FCollisionResponseContainer WheelTraceCollisionResponses;` — `UPROPERTY(EditAnywhere, Category = Custom)`
- L654 _private member_ `bool bMechanicalSimEnabled;` — `UPROPERTY(EditAnywhere, Category = MechanicalSetup)`
- L658 _private member_ `FVehicleEngineConfig EngineSetup;` — `UPROPERTY(EditAnywhere, Category = MechanicalSetup, meta = (EditCondition = "bMechanicalSimEnabled"))` — Engine
- L662 _private member_ `FVehicleDifferentialConfig DifferentialSetup;` — `UPROPERTY(EditAnywhere, Category = MechanicalSetup, meta = (EditCondition = "bMechanicalSimEnabled"))` — Differential
- L666 _private member_ `FVehicleTransmissionConfig TransmissionSetup;` — `UPROPERTY(EditAnywhere, Category = MechanicalSetup, meta = (EditCondition = "bMechanicalSimEnabled"))` — Transmission data
- L670 _private member_ `FVehicleSteeringConfig SteeringSetup;` — `UPROPERTY(EditAnywhere, Category = SteeringSetup)` — Transmission data
- L674 _private member_ `TArray<TObjectPtr<class UChaosVehicleWheel>> Wheels;` — `UPROPERTY(transient, duplicatetransient, BlueprintReadOnly, Category = Vehicle)` — Our instanced wheels
- L678 _private prototype_ `float GetEngineRotationSpeed() const;` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ChaosWheeledVehicleMovement")` — Get current engine's rotation speed
- L682 _private prototype_ `float GetEngineMaxRotationSpeed() const;` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ChaosWheeledVehicleMovement")` — Get current engine's max rotation speed
- L685 _private function_ `int GetNumWheels() const` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ChaosWheeledVehicleMovement")`
- L691 _private prototype_ `static void BreakWheelStatus(const struct FWheelStatus& Status, bool& bInContact, FVector& ContactPoint, UPhysicalMaterial*& PhysMaterial , float& NormalizedSuspensionLength, float& SpringForce, float& SlipAngle, bool& bIsSlipping, float& SlipMagnitude, bool& bIsSkidding, float& SkidMagnitude, FVector& SkidNormal, float& DriveTorque, float& BrakeTorque, bool& bABSActivated);` — `UFUNCTION(BlueprintPure, Category = "Vehicles")`
- L695 _private prototype_ `static FWheelStatus MakeWheelStatus(bool bInContact, FVector& ContactPoint, UPhysicalMaterial* PhysMaterial , float NormalizedSuspensionLength, float SpringForce, float SlipAngle, bool bIsSlipping, float SlipMagnitude, bool bIsSkidding, float SkidMagnitude, FVector& SkidNormal, float DriveTorque, float BrakeTorque, bool bABSActivated);` — `UFUNCTION(BlueprintPure, Category = "Vehicles")`
- L699 _private prototype_ `static void BreakWheeledSnapshot(const struct FWheeledSnaphotData& Snapshot, FTransform& Transform, FVector& LinearVelocity , FVector& AngularVelocity, int& SelectedGear, float& EngineRPM, TArray<FWheelSnapshot>& WheelSnapshots);` — `UFUNCTION(BlueprintPure, Category = "Vehicles")`
- L703 _private prototype_ `static FWheeledSnaphotData MakeWheeledSnapshot(FTransform Transform, FVector LinearVelocity, FVector AngularVelocity , int SelectedGear, float EngineRPM, const TArray<FWheelSnapshot>& WheelSnapshots);` — `UFUNCTION(BlueprintPure, Category = "Vehicles")`
- L707 _private prototype_ `static void BreakWheelSnapshot(const struct FWheelSnapshot& Snapshot, float& SuspensionOffset , float& WheelRotationAngle, float& SteeringAngle, float& WheelRadius, float& WheelAngularVelocity);` — `UFUNCTION(BlueprintPure, Category = "Vehicles")`
- L711 _private prototype_ `static FWheelSnapshot MakeWheelSnapshot(float SuspensionOffset, float WheelRotationAngle , float SteeringAngle, float WheelRadius, float WheelAngularVelocity);` — `UFUNCTION(BlueprintPure, Category = "Vehicles")`
- L716 _private function_ `const FWheelStatus& GetWheelState(int WheelIndex) const` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ChaosWheeledVehicleMovement")` — Get a wheels current simulation state
- L721 _private prototype_ `virtual float GetSuspensionOffset(int WheelIndex) override;`
- L722 _private prototype_ `UPhysicalMaterial* GetPhysMaterial(int WheelIndex);`
- L725 _private function_ `void SetWheelTraceAllChannels(ECollisionResponse NewResponse)` — Set all channels to the specified response - for wheel raycasts
- L731 _private function_ `void SetWheelTraceResponseToChannel(ECollisionChannel Channel, ECollisionResponse NewResponse)` — Set the response of this body to the supplied settings - for wheel raycasts
- L742 _private prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L743 _private prototype_ `virtual void PostLoad() override;`
- L746 _private prototype_ `virtual void ParallelUpdate(float DeltaSeconds);` — Get output data from Physics Thread
- L749 _private prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L752 _private prototype_ `virtual bool CanCreateVehicle() const override;` — Are the configuration references configured sufficiently that the vehicle can be created
- L755 _private prototype_ `virtual void OnCreatePhysicsState() override;` — Used to create any physics engine information for this component
- L758 _private prototype_ `virtual void OnDestroyPhysicsState() override;` — Used to shut down and pysics engine structure for this component
- L761 _private prototype_ `static void NextDebugPage();` — display next debug page
- L764 _private prototype_ `static void PrevDebugPage();` — display previous debug page
- L768 _private function_ `void EnableMechanicalSim(bool InState)` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ChaosWheeledVehicleMovement")` — Enable or completely bypass the ProcessMechanicalSimulation call
- L775 _private function_ `void EnableSuspension(bool InState)` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ChaosWheeledVehicleMovement")` — Enable or completely bypass the ApplySuspensionForces call
- L782 _private function_ `void EnableWheelFriction(bool InState)` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ChaosWheeledVehicleMovement")` — Enable or completely bypass the ApplyWheelFrictionForces call
- L788 _private prototype_ `void SetWheelClass(int WheelIndex, TSubclassOf<UChaosVehicleWheel> InWheelClass);` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ChaosWheeledVehicleMovement")`
- L792 _private prototype_ `virtual FWheeledSnaphotData GetSnapshot() const;` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ChaosWheeledVehicleMovement")` — Grab a snapshot of the vehicle instance dynamic state
- L796 _private prototype_ `virtual void SetSnapshot(const FWheeledSnaphotData& SnapshotIn);` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ChaosWheeledVehicleMovement")` — Set snapshot of vehicle instance dynamic state
- L802 _private prototype_ `void SetMaxEngineTorque(float Torque);` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ChaosWheeledVehicleMovement")` — change handling via blueprint at runtime
- L805 _private prototype_ `void SetDragCoefficient(float DragCoeff);` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ChaosWheeledVehicleMovement")`
- L808 _private prototype_ `void SetDownforceCoefficient(float DownforceCoeff);` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ChaosWheeledVehicleMovement")`
- L811 _private prototype_ `void SetDifferentialFrontRearSplit(float FrontRearSlpit);` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ChaosWheeledVehicleMovement")`
- L814 _private prototype_ `void SetTractionControlEnabled(int WheelIndex, bool Enabled);` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ChaosWheeledVehicleMovement")`
- L817 _private prototype_ `void SetABSEnabled(int WheelIndex, bool Enabled);` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ChaosWheeledVehicleMovement")`
- L820 _private prototype_ `void SetAffectedByBrake(int WheelIndex, bool Enabled);` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ChaosWheeledVehicleMovement")`
- L823 _private prototype_ `void SetAffectedByHandbrake(int WheelIndex, bool Enabled);` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ChaosWheeledVehicleMovement")`
- L826 _private prototype_ `void SetAffectedBySteering(int WheelIndex, bool Enabled);` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ChaosWheeledVehicleMovement")`
- L829 _private prototype_ `void SetAffectedByEngine(int WheelIndex, bool Enabled);` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ChaosWheeledVehicleMovement")`
- L832 _private prototype_ `void SetWheelRadius(int WheelIndex, float Radius);` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ChaosWheeledVehicleMovement")`
- L835 _private prototype_ `void SetWheelFrictionMultiplier(int WheelIndex, float Friction);` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ChaosWheeledVehicleMovement")`
- L838 _private prototype_ `void SetWheelSlipGraphMultiplier(int WheelIndex, float Multiplier);` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ChaosWheeledVehicleMovement")`
- L841 _private prototype_ `void SetWheelMaxBrakeTorque(int WheelIndex, float Torque);` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ChaosWheeledVehicleMovement")`
- L844 _private prototype_ `void SetWheelHandbrakeTorque(int WheelIndex, float Torque);` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ChaosWheeledVehicleMovement")`
- L847 _private prototype_ `void SetWheelMaxSteerAngle(int WheelIndex, float AngleDegrees);` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ChaosWheeledVehicleMovement")`
- L850 _private prototype_ `void SetTorqueCombineMethod(ETorqueCombineMethod InCombineMethod, int32 WheelIndex);` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ChaosWheeledVehicleMovement")`
- L853 _private prototype_ `void SetDriveTorque(float DriveTorque, int32 WheelIndex);` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ChaosWheeledVehicleMovement")`
- L856 _private prototype_ `void SetBrakeTorque(float BrakeTorque, int32 WheelIndex);` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ChaosWheeledVehicleMovement")`
- L859 _private prototype_ `void SetSuspensionParams(float Rate, float Damping, float Preload, float MaxRaise, float MaxDrop, int32 WheelIndex);` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ChaosWheeledVehicleMovement")`
- L862 _private function_ `virtual TUniquePtr<Chaos::FSimpleWheeledVehicle> CreatePhysicsVehicle() override`
- L871 _private prototype_ `virtual void SetupVehicle(TUniquePtr<Chaos::FSimpleWheeledVehicle>& PVehicle) override;` — Allocate and setup the Chaos vehicle
- L873 _private prototype_ `virtual void ResetVehicleState() override;`
- L881 _protected prototype_ `virtual void ComputeConstants() override;` — Re-Compute any runtime constants values that rely on setup data
- L884 _protected prototype_ `virtual void FixupSkeletalMesh();` — Skeletal mesh needs some special handling in the vehicle case
- L887 _protected prototype_ `virtual void CreateVehicle();` — Create and setup the Chaos vehicle
- L890 _protected prototype_ `virtual void CreateWheels();` — Instantiate and setup our wheel objects
- L893 _protected prototype_ `virtual void DestroyWheels();` — Release our wheel objects
- L896 _protected prototype_ `virtual void SetupVehicleShapes();` — Set up the chassis and wheel shapes
- L899 _protected prototype_ `void SetupSuspension(TUniquePtr<Chaos::FSimpleWheeledVehicle>& PVehicle);` — Setup calculated suspension parameters
- L902 _protected prototype_ `void RecalculateAxles();` — Maps UChaosVehicleWheel Axle to a wheel index
- L905 _protected prototype_ `virtual FVector GetWheelRestingPosition(const FChaosWheelSetup& WheelSetup);` — Get the local position of the wheel at rest
- L909 _protected prototype_ `void FillWheelOutputState();` — Update
- L912 _protected prototype_ `virtual void Update(float DeltaTime) override;` — Fill Async input state
- L918 _protected prototype_ `virtual void DrawDebug(UCanvas* Canvas, float& YL, float& YPos);` — Draw 2D debug text graphs on UI for the wheels, suspension and other systems
- L921 _protected function_ `const FVector2D& GetWheelLayoutDimensions() const` — Get distances between wheels - primarily a debug display helper
- L927 _protected prototype_ `virtual void PostMigrate(const struct FUObjectMigrationContext& MigrationContext) override;`
- L934 _private prototype_ `FVector2D CalculateWheelLayoutDimensions();` — Get distances between wheels - primarily a debug display helper
- L937 _private prototype_ `float CalcDialAngle(float CurrentValue, float MaxValue);`
- L938 _private prototype_ `void DrawDial(UCanvas* Canvas, FVector2D Pos, float Radius, float CurrentValue, float MaxValue);`
- L950 _private member_ `static EDebugPages DebugPage;`
- L951 _private member_ `uint32 NumDrivenWheels;`
- L952 _private member_ `FVector2D WheelTrackDimensions;` — uint32 NumDrivenWheels;   The number of wheels that have engine enabled checked
- L953 _private member_ `TMap<UChaosVehicleWheel*, TArray<int>> AxleToWheelMap;`
- L954 _private member_ `TArray<FPhysicsConstraintHandle> ConstraintHandles;`
- L955 _private member_ `TArray<FWheelStatus> WheelStatus;`
- L956 _private member_ `TArray<FCachedState> CachedState;` — TArray<FWheelStatus> WheelStatus;   Wheel output status
- L957 _private member_ `Chaos::FPerformanceMeasure PerformanceMeasure;`
- L960 _private member_ `bool bAreWheelsMigrated = false;`

#### struct `UChaosWheeledVehicleMovementComponent::FCachedState`  
`struct FCachedState`  
_L941-948_
- L943 _public function_ `FCachedState() : WheelOffset(0.f), bIsValid(false)`
- L946 _public member_ `float WheelOffset;`
- L947 _public member_ `bool bIsValid;`

### `Plugins/Experimental/ChaosVehiclesPlugin/Source/ChaosVehicles/Public/DeferredForces.h` (Public)


#### enum `EForceFlags`  
`enum class EForceFlags : uint32`  
_L8-16_
- L10 _public enumerator_ `None = 0` — No flags.
- L12 _public enumerator_ `AllowSubstepping = 1 << 0`
- L13 _public enumerator_ `AccelChange = 1 << 1`
- L14 _public enumerator_ `VelChange = 1 << 2`
- L15 _public enumerator_ `IsLocalForce = 1 << 3`

#### class `FDeferredForces`  
`class FDeferredForces`  
_L27-178_
- L105 _public function_ `void Add(const FApplyForceData& ApplyForceDataIn)`
- L110 _public function_ `void Add(const FApplyForceAtPositionData& ApplyForceAtPositionDataIn)`
- L115 _public function_ `void Add(const FAddTorqueInRadiansData& ApplyTorqueDataIn)`
- L120 _public function_ `void Add(const FAddImpulseData& ApplyImpulseDataIn)`
- L125 _public function_ `void Add(const FAddImpulseAtPositionData& ApplyImpulseAtPositionDataIn)`
- L131 _public function_ `void Apply(Chaos::FRigidBodyHandle_Internal* RigidHandle)`
- L167 _private prototype_ `void AddForce(Chaos::FRigidBodyHandle_Internal* RigidHandle, const FApplyForceData& DataIn);`
- L168 _private prototype_ `void AddForceAtPosition(Chaos::FRigidBodyHandle_Internal* RigidHandle, const FApplyForceAtPositionData& DataIn);`
- L169 _private prototype_ `void AddTorque(Chaos::FRigidBodyHandle_Internal* RigidHandle, const FAddTorqueInRadiansData& DataIn);`
- L170 _private prototype_ `void AddImpulse(Chaos::FRigidBodyHandle_Internal* RigidHandle, const FAddImpulseData& DataIn);`
- L171 _private prototype_ `void AddImpulseAtPosition(Chaos::FRigidBodyHandle_Internal* RigidHandle, const FAddImpulseAtPositionData& DataIn);`
- L173 _private member_ `TArray<FApplyForceData> ApplyForceDatas;`
- L174 _private member_ `TArray<FApplyForceAtPositionData> ApplyForceAtPositionDatas;`
- L175 _private member_ `TArray<FAddTorqueInRadiansData> ApplyTorqueDatas;`
- L176 _private member_ `TArray<FAddImpulseData> ApplyImpulseDatas;`
- L177 _private member_ `TArray<FAddImpulseAtPositionData> ApplyImpulseAtPositionDatas;`

#### struct `FDeferredForces::FApplyForceData`  
`struct FApplyForceData`  
_L33-47_
- L37 _public function_ `FApplyForceData(const FVector& ForceIn, bool bAllowSubsteppingIn, bool bAccelChangeIn) : Force(ForceIn) , Flags(EForceFlags::None)`
- L45 _public member_ `FVector Force;`
- L46 _public member_ `EForceFlags Flags;`

#### struct `FDeferredForces::FApplyForceAtPositionData`  
`struct FApplyForceAtPositionData`  
_L49-63_
- L51 _public function_ `FApplyForceAtPositionData(const FVector& ForceIn, const FVector& PositionIn, bool bAllowSubsteppingIn, bool bIsLocalForceIn) : Force(ForceIn) , Position(PositionIn) , Flags(EForceFlags::None)`
- L60 _public member_ `FVector Force;`
- L61 _public member_ `FVector Position;`
- L62 _public member_ `EForceFlags Flags;`

#### struct `FDeferredForces::FAddTorqueInRadiansData`  
`struct FAddTorqueInRadiansData`  
_L65-77_
- L67 _public function_ `FAddTorqueInRadiansData(const FVector& TorqueIn, bool bAllowSubsteppingIn, bool bAccelChangeIn) : Torque(TorqueIn) , Flags(EForceFlags::None)`
- L75 _public member_ `FVector Torque;`
- L76 _public member_ `EForceFlags Flags;`

#### struct `FDeferredForces::FAddImpulseData`  
`struct FAddImpulseData`  
_L79-90_
- L81 _public function_ `FAddImpulseData(const FVector& ImpulseIn, const bool bVelChangeIn) : Impulse(ImpulseIn) , Flags(EForceFlags::None)`
- L88 _public member_ `FVector Impulse;`
- L89 _public member_ `EForceFlags Flags;`

#### struct `FDeferredForces::FAddImpulseAtPositionData`  
`struct FAddImpulseAtPositionData`  
_L92-103_
- L94 _public function_ `FAddImpulseAtPositionData(const FVector& ImpulseIn, const FVector& PositionIn) : Impulse(ImpulseIn) , Position(PositionIn)`
- L101 _public member_ `FVector Impulse;`
- L102 _public member_ `FVector Position;`

#### Free symbols / members of external scopes

- L17 _prototype_ `ENUM_CLASS_FLAGS(EForceFlags);`
- L21 _namespace_ `namespace Chaos`

### `Plugins/Experimental/ChaosVehiclesPlugin/Source/ChaosVehicles/Public/SnapshotData.h` (Public)


#### struct `FBaseSnapshotData`  
`struct FBaseSnapshotData`  
_L10-31_
- reflection: `USTRUCT(BlueprintType)`
- desc: : public UObject
- L15 _public function_ `FBaseSnapshotData()`
- L23 _public member_ `FTransform Transform;` — `UPROPERTY()` — world coords
- L26 _public member_ `FVector LinearVelocity;` — `UPROPERTY()` — world coords
- L29 _public member_ `FVector AngularVelocity;` — `UPROPERTY()` — world coords

#### struct `FWheelSnapshot`  
`struct FWheelSnapshot`  
_L34-61_
- reflection: `USTRUCT(BlueprintType)`
- L38 _public function_ `FWheelSnapshot()`
- L48 _public member_ `float SuspensionOffset;` — `UPROPERTY()` — suspension location
- L51 _public member_ `float WheelRotationAngle;` — `UPROPERTY()` — wheel rotation angle, rotated position
- L54 _public member_ `float SteeringAngle;` — `UPROPERTY()` — steering position
- L57 _public member_ `float WheelRadius;` — `UPROPERTY()` — radius of the wheel can be changed dynamically, to sim damaged ot flat
- L60 _public member_ `float WheelAngularVelocity;` — `UPROPERTY()` — speed of rotation of wheel

#### struct `FWheeledSnaphotData`  
`struct FWheeledSnaphotData : public FBaseSnapshotData`  
_L64-84_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FBaseSnapshotData`
- L69 _public function_ `FWheeledSnaphotData()`
- L76 _public member_ `int SelectedGear;` — `UPROPERTY()` — -ve reverse gear(s), 0 neutral, +ve forward gears
- L79 _public member_ `float EngineRPM;` — `UPROPERTY()` — Engine Revolutions Per Minute
- L82 _public member_ `TArray<FWheelSnapshot> WheelSnapshots;` — `UPROPERTY()`

### `Plugins/Experimental/ChaosVehiclesPlugin/Source/ChaosVehicles/Public/VehicleAnimationInstance.h` (Public)


#### struct `FWheelAnimationData`  
`struct FWheelAnimationData`  
_L13-18_
- L15 _public member_ `FName BoneName;`
- L16 _public member_ `FRotator RotOffset;`
- L17 _public member_ `FVector LocOffset;`

#### struct `FVehicleAnimationInstanceProxy`  
`struct FVehicleAnimationInstanceProxy : public FAnimInstanceProxy`  
_L22-73_
- reflection: `USTRUCT()`
- inherits: `FAnimInstanceProxy`
- desc: Proxy override for this UAnimInstance-derived class
- L26 _public function_ `FVehicleAnimationInstanceProxy() : FAnimInstanceProxy() , WheelSpokeCount(0) , MaxAngularVelocity(256.f) , ShutterSpeed(30.f) , StageCoachBlend(730.f)`
- L35 _public function_ `FVehicleAnimationInstanceProxy(UAnimInstance* Instance) : FAnimInstanceProxy(Instance) , WheelSpokeCount(0) , MaxAngularVelocity(256.f) , ShutterSpeed(30.f) , StageCoachBlend(730.f)`
- L46 _public prototype_ `void SetWheeledVehicleComponent(const UChaosWheeledVehicleMovementComponent* InWheeledVehicleComponent);`
- L49 _public prototype_ `virtual void PreUpdate(UAnimInstance* InAnimInstance, float DeltaSeconds) override;` — FAnimInstanceProxy interface begin
- L52 _public function_ `const TArray<FWheelAnimationData>& GetWheelAnimData() const`
- L57 _public function_ `void SetStageCoachEffectParams(int InWheelSpokeCount, float InMaxAngularVelocity, float InShutterSpeed, float InStageCoachBlend)`
- L66 _private member_ `TArray<FWheelAnimationData> WheelInstances;`
- L68 _private member_ `int WheelSpokeCount;` — Number of spokes visible on wheel
- L69 _private member_ `float MaxAngularVelocity;` — Wheel max rotation speed in degrees/second
- L70 _private member_ `float ShutterSpeed;` — Camera shutter speed in frames/second
- L71 _private member_ `float StageCoachBlend;` — Blend effect degrees/second

#### class `UVehicleAnimationInstance`  
`class UVehicleAnimationInstance : public UAnimInstance`  
_L76-110_
- reflection: `UCLASS(transient)`
- inherits: `UAnimInstance`
- L82 _private prototype_ `class AWheeledVehiclePawn* GetVehicle();` — `UFUNCTION(BlueprintCallable, Category = "Animation")` — Makes a montage jump to the end of a named section.
- L85 _public member_ `TArray<TArray<FWheelAnimationData>> WheelData;`
- L88 _public function_ `void SetWheeledVehicleComponent(const UChaosWheeledVehicleMovementComponent* InWheeledVehicleComponent)`
- L94 _public function_ `const UChaosWheeledVehicleMovementComponent* GetWheeledVehicleComponent() const`
- L101 _private prototype_ `virtual void NativeInitializeAnimation() override;` — UAnimInstance interface begin
- L102 _private prototype_ `virtual FAnimInstanceProxy* CreateAnimInstanceProxy() override;`
- L103 _private prototype_ `virtual void DestroyAnimInstanceProxy(FAnimInstanceProxy* InProxy) override;`
- L106 _private member_ `FVehicleAnimationInstanceProxy AnimInstanceProxy;`
- L109 _private member_ `TObjectPtr<const UChaosWheeledVehicleMovementComponent> WheeledVehicleComponent;` — `UPROPERTY(transient)`

### `Plugins/Experimental/ChaosVehiclesPlugin/Source/ChaosVehicles/Public/WheeledVehiclePawn.h` (Public)


#### class `AWheeledVehiclePawn`  
`class AWheeledVehiclePawn : public APawn`  
_L20-52_
- reflection: `UCLASS(abstract, config=Game, BlueprintType)`
- inherits: `APawn`
- L27 _private member_ `TObjectPtr<class USkeletalMeshComponent> Mesh;` — `UPROPERTY(Category = Vehicle, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))` — The main skeletal mesh associated with this Vehicle
- L31 _private member_ `TObjectPtr<class UChaosVehicleMovementComponent> VehicleMovementComponent;` — `UPROPERTY(Category = Vehicle, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))` — vehicle simulation component
- L35 _public member_ `static FName VehicleMeshComponentName;` — Name of the MeshComponent. Use this name if you want to prevent creation of the component (with ObjectInitializer.DoNotCreateDefaultSubobject).
- L38 _public member_ `static FName VehicleMovementComponentName;` — Name of the VehicleMovement. Use this name if you want to use a different class (with ObjectInitializer.SetDefaultSubobjectClass).
- L41 _public prototype_ `class UChaosVehicleMovementComponent* GetVehicleMovementComponent() const;` — Util to get the wheeled vehicle movement component
- L44 _public prototype_ `virtual void DisplayDebug(class UCanvas* Canvas, const FDebugDisplayInfo& DebugDisplay, float& YL, float& YPos) override;`
- L48 _public function_ `class USkeletalMeshComponent* GetMesh() const` — Returns Mesh subobject
- L51 _public function_ `class UChaosVehicleMovementComponent* GetVehicleMovement() const` — Returns VehicleMovement subobject
