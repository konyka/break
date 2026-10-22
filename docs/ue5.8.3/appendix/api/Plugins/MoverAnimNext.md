# Plugins / MoverAnimNext

- module root: `Plugins/Experimental/MoverAnimNext/Source/MoverAnimNext`
- headers: 5; symbols: 45
- symbol kinds: class=1, member=28, prototype=10, struct=6
- PrivateDependencyModuleNames: CoreUObject, DeveloperSettings, Engine, PhysicsCore, RigVM, RigVMDeveloper
- PublicDependencyModuleNames: Core, Mover, PoseSearch, UAF

### `Plugins/Experimental/MoverAnimNext/Source/MoverAnimNext/Private/Graph/RigUnit_GenerateMoverTrajectory.h` (Private)


#### struct `FRigUnit_GenerateMoverTrajectory`  
`struct FRigUnit_GenerateMoverTrajectory : public FRigUnit_AnimNextBase`  
_L18-60_
- reflection: `USTRUCT(meta = (DisplayName = "Generate Trajectory from Mover", Category = "Mover", NodeColor = "0, 1, 1", Keywords = "Mover, Trajectory"))`
- inherits: `FRigUnit_AnimNextBase`
- desc: A utility node to generate a trajectory from a mover component
- L22 _public prototype_ `RIGVM_METHOD() void Execute();`
- L27 _public member_ `TObjectPtr<UMoverComponent> MoverComponent;` — `UPROPERTY(EditAnywhere, Category = "Trajectory", meta = (Input))` — The mover component to generate the trajectory for
- L31 _public member_ `float DeltaTime = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Trajectory", meta = (Input))` — This should be the most recent simulation time that was used to get us to our current state
- L35 _public member_ `float HistorySamplingInterval = -1.f;` — `UPROPERTY(EditAnywhere, Category = "Trajectory", meta = (Input))` — The sampling interval to use for the history
- L39 _public member_ `int32 NumHistorySamples = 30;` — `UPROPERTY(EditAnywhere, Category = "Trajectory", meta = (Input))` — The upper limit of samples to use for the history
- L43 _public member_ `float PredictionSamplingInterval = 0.1f;` — `UPROPERTY(EditAnywhere, Category = "Trajectory", meta = (Input))` — The interval to use for prediction (in seconds)
- L47 _public member_ `int32 NumPredictionSamples = 15;` — `UPROPERTY(EditAnywhere, Category = "Trajectory", meta = (Input))` — The upper limit of samples to use for prediction
- L51 _public member_ `FFrameRate MoverSamplingFrameRate = FFrameRate(60, 1);` — `UPROPERTY(EditAnywhere, Category = "Trajectory", meta = (Input))` — Sampling frame rate to query the mover, doesn't necessarily match the PredictionSamplingInterval which is used to write to the trajectory
- L55 _public member_ `FTransformTrajectory InOutTrajectory;` — `UPROPERTY(EditAnywhere, Category = "Trajectory", meta = (Input, Output))` — The resulting trajectory
- L59 _public member_ `FAnimNextExecuteContext ExecuteContext;` — `UPROPERTY(EditAnywhere, DisplayName = "Execute", Category = "BeginExecution", meta = (Input, Output))` — The execution result

### `Plugins/Experimental/MoverAnimNext/Source/MoverAnimNext/Private/Graph/RigUnit_MoverToggleRootMotion.h` (Private)


#### struct `FRigUnit_MoverToggleRootMotion`  
`struct FRigUnit_MoverToggleRootMotion : public FRigUnit_AnimNextBase`  
_L23-45_
- reflection: `USTRUCT(meta = (DisplayName = "Mover Toggle Root Motion", Category = "Mover", NodeColor = "0, 1, 1", Keywords = "Mover, Root Motion, Enable, Disable"))`
- inherits: `FRigUnit_AnimNextBase`
- desc: RigVM Node that can be used to toggle mover root motion. The toggle will occur next frame. You should also update your animation tick dependencies to so that animation runs before mover when this is toggled. For example. Within UAF during PrePhysics: If (bRootMotionEnabled) -> AddDependency : MoverComponent, Before, SimulateMovment -> RemoveDependency : MoverComponent, After, SimulateMovment If (!bRootMotionEnabled) -> RemoveDependency : MoverComponent, Before, SimulateMovment -> AddDependency : MoverComponent, After, SimulateMovment Where: If / AddDependency / RemoveDependency are nodes in your RigVM UAF PrePhysics graph.
- L27 _public prototype_ `RIGVM_METHOD() void Execute();`
- L32 _public member_ `TObjectPtr<UMoverComponent> MoverComponent = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Mover", meta = (Input))` — Mover to toggle root motion on
- L36 _public member_ `bool bRootMotionEnabled = false;` — `UPROPERTY(EditAnywhere, Category = "Mover", meta = (Input))` — True if we want to enable root motion on the mover
- L40 _public member_ `bool bToggleOnGameThread = true;` — `UPROPERTY(EditAnywhere, Category = "Mover", AdvancedDisplay, meta = (Input))` — True if we want to delay the toggle to next frame on game thread. This allows for tick dependencies to change for next frame
- L44 _public member_ `FAnimNextExecuteContext ExecuteContext;` — `UPROPERTY(EditAnywhere, DisplayName = "Execute", Category = "Mover", meta = (Input, Output))` — Execution input / output

### `Plugins/Experimental/MoverAnimNext/Source/MoverAnimNext/Private/Graph/RigUnit_TrajectoryAnalysis.h` (Private)


#### struct `FRigUnit_GetTrajectorySampleAtTime`  
`struct FRigUnit_GetTrajectorySampleAtTime : public FRigUnit_AnimNextBase`  
_L15-37_
- reflection: `USTRUCT(meta = (DisplayName = "Get Trajectory Sample At Time", Category = "Trajectory", NodeColor = "0, 1, 1", Keywords = "Trajectory"))`
- inherits: `FRigUnit_AnimNextBase`
- desc: Returns a sample of a trajectory at a given time
- L19 _public prototype_ `RIGVM_METHOD() void Execute();`
- L24 _public member_ `FTransformTrajectorySample OutTrajectorySample;` — `UPROPERTY(EditAnywhere, Category = "Trajectory", meta = (Output))` — The resulting trajectory sample
- L28 _public member_ `FTransformTrajectory InTrajectory;` — `UPROPERTY(EditAnywhere, Category = "Trajectory", meta = (Input))` — The input trajectory to analyze
- L32 _public member_ `float Time = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Trajectory", meta = (Input))` — The time at which to analyze the trajectory
- L36 _public member_ `bool bExtrapolate = false;` — `UPROPERTY(EditAnywhere, Category = "Trajectory", meta = (Input))` — If True the trajectory will be extrapolated beyond its bounds

#### struct `FRigUnit_GetTrajectoryVelocity`  
`struct FRigUnit_GetTrajectoryVelocity : public FRigUnit_AnimNextBase`  
_L43-69_
- reflection: `USTRUCT(meta = (DisplayName = "Get Trajectory Velocity", Category = "Trajectory", NodeColor = "0, 1, 1", Keywords = "Trajectory"))`
- inherits: `FRigUnit_AnimNextBase`
- desc: Computes the velocity between two times on a trajectory
- L47 _public prototype_ `RIGVM_METHOD() void Execute();`
- L52 _public member_ `FTransformTrajectory InTrajectory;` — `UPROPERTY(EditAnywhere, Category = "Trajectory", meta = (Input))` — The input trajectory to analyze
- L56 _public member_ `FVector OutVelocity = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = "Trajectory", meta = (Output))` — The resulting velocity between the two provided times
- L60 _public member_ `float Time1 = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Trajectory", meta = (Input))` — The first time to analyze
- L64 _public member_ `float Time2 = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Trajectory", meta = (Input))` — The second time to analyze
- L68 _public member_ `bool bExtrapolate = false;` — `UPROPERTY(EditAnywhere, Category = "Trajectory", meta = (Input))` — If True the trajectory will be extrapolated beyond its bounds

#### struct `FRigUnit_GetTrajectoryAngularVelocity`  
`struct FRigUnit_GetTrajectoryAngularVelocity : public FRigUnit_AnimNextBase`  
_L75-101_
- reflection: `USTRUCT(meta = (DisplayName = "Get Trajectory Angular Velocity", Category = "Trajectory", NodeColor = "0, 1, 1", Keywords = "Trajectory"))`
- inherits: `FRigUnit_AnimNextBase`
- desc: Computes the angular velocity between two times on a trajectory
- L79 _public prototype_ `RIGVM_METHOD() void Execute();`
- L84 _public member_ `FTransformTrajectory InTrajectory;` — `UPROPERTY(EditAnywhere, Category = "Trajectory", meta = (Input))` — The input trajectory to analyze
- L88 _public member_ `FVector OutAngularVelocity = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = "Trajectory", meta = (Output))` — The resulting angular velocity between the two provided times
- L92 _public member_ `float Time1 = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Trajectory", meta = (Input))` — The first time to analyze
- L96 _public member_ `float Time2 = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Trajectory", meta = (Input))` — The second time to analyze
- L100 _public member_ `bool bExtrapolate = false;` — `UPROPERTY(EditAnywhere, Category = "Trajectory", meta = (Input))` — If True the trajectory will be extrapolated beyond its bounds

### `Plugins/Experimental/MoverAnimNext/Source/MoverAnimNext/Private/Module/RigVMTrait_ModuleEventDependency_MoverComponentTickFunctions.h` (Private)


#### struct `FRigVMTrait_ModuleEventDependency_MoverComponentTickFunctions`  
`struct FRigVMTrait_ModuleEventDependency_MoverComponentTickFunctions : public FRigVMTrait_ModuleEventDependency`  
_L15-32_
- reflection: `USTRUCT(DisplayName = "Mover Component Tick Functions", meta = (ShowTooltip = true))`
- inherits: `FRigVMTrait_ModuleEventDependency`
- desc: A dependency on one of the tick functions that make up a MoverComponent's update flow. This uses the first-found MoverComponent on the current actor. TODO: add support beyond standalone (non-networked) Mover backends
- L21 _public prototype_ `virtual FString GetDisplayName() const override;`
- L25 _public prototype_ `virtual void OnAddDependency(const UE::UAF::FModuleDependencyContext& InContext) const override;` — FAnimNextModuleEventDependency interface
- L26 _public prototype_ `virtual void OnRemoveDependency(const UE::UAF::FModuleDependencyContext& InContext) const override;`
- L31 _public member_ `EMoverTickPhase DependentMoverTickPhase = EMoverTickPhase::ApplyState;` — `UPROPERTY(EditAnywhere, Category = "Dependency")` — The Mover tick phase that this dependency relates to

### `Plugins/Experimental/MoverAnimNext/Source/MoverAnimNext/Public/MoverAnimNextModule.h` (Public)


#### class `FMoverAnimNextModule`  
`class FMoverAnimNextModule : public IModuleInterface`  
_L8-15_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L14 _public prototype_ `virtual void ShutdownModule() override;`
