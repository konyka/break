# Plugins / IKRigUAF

- module root: `Plugins/Animation/IKRig/Source/IKRigUAF`
- headers: 2; symbols: 19
- symbol kinds: class=1, delegate=1, member=12, prototype=3, struct=2
- PublicDependencyModuleNames: Core, CoreUObject, Engine, IKRig, RigVM, UAF, UAFAnimGraph

### `Plugins/Animation/IKRig/Source/IKRigUAF/Public/IKRigUAFModule.h` (Public)


#### class `FIKRigUAFModule`  
`class FIKRigUAFModule : public IModuleInterface`  
_L7-12_
- inherits: `IModuleInterface`
- L10 _public prototype_ `virtual void StartupModule() override;`
- L11 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Animation/IKRig/Source/IKRigUAF/Public/RigUnit_UAFIKRetargeter.h` (Public)


#### struct `FIKRetargetWorkData`  
`struct FIKRetargetWorkData`  
_L18-31_
- reflection: `USTRUCT(BlueprintType)`
- L23 _public member_ `FIKRetargetProcessor Processor;` — the runtime processor used to run the retarget and generate new poses
- L26 _public member_ `TArray<FTransform> SourceMeshPoseLocal;` — scratch space for adapting the LOD'd pose to the full input pose
- L27 _public member_ `TArray<FTransform> SourceMeshPoseGlobal;`
- L30 _public member_ `FRetargetProfile Profile;` — reusable profile to pass to the retargeter (merged with input profile)

#### struct `FRigUnit_UAFIKRetargeter`  
`struct FRigUnit_UAFIKRetargeter : public FRigUnit_AnimNextBase`  
_L35-72_
- reflection: `USTRUCT(MinimalAPI, meta=(DisplayName="IK Retargeter", Category="Animation Graph", NodeColor="1, 0, 1", Keywords="Retarget, IK"))`
- inherits: `FRigUnit_AnimNextBase`
- desc: IK Retargeting UAF Graph node.
- L39 _public prototype_ `RIGVM_METHOD() void Execute();`
- L44 _public member_ `FAnimNextGraphLODPose SourcePose;` — `UPROPERTY(EditAnywhere, DisplayName = "Source Pose", Category = "Graph", meta = (Input))` — The source input pose to retarget.
- L48 _public member_ `FAnimNextGraphReferencePose TargetAnimGraphRefPose;` — `UPROPERTY(EditAnywhere, DisplayName = "Target Ref Pose", Category = "Graph", meta = (Input))` — The ref pose of the target skeletal mesh.
- L52 _public member_ `TObjectPtr<UIKRetargeter> IKRetargetAsset;` — `UPROPERTY(EditAnywhere, DisplayName = "IK Retarget Asset", Category = "Graph", meta = (Input))` — An IK Retarget asset defining the retargeting operations to run.
- L56 _public member_ `FRetargetProfile CustomRetargetProfile;` — `UPROPERTY(EditAnywhere, DisplayName = "Custom Profile", Category = "Graph", meta = (Input))` — Connect a custom retarget profile to modify the retargeter's settings at runtime.
- L61 _public member_ `TArray<FName> OverrideSetNames;` — `UPROPERTY(EditAnywhere, DisplayName = "Custom Override Sets", Category = "Graph", meta = (Input))` — An optional list of property override sets to apply to op settings NOTE: these names must match the names of override sets stored in the retarget asset
- L65 _public member_ `FAnimNextGraphLODPose TargetPose;` — `UPROPERTY(EditAnywhere, DisplayName = "Retargeted Pose", Category = "Graph", meta = (Output))` — The output pose for the target skeletal mesh.
- L68 _public member_ `FAnimNextExecuteContext ExecuteContext;` — `UPROPERTY(EditAnywhere, DisplayName = "Execute", Category = "BeginExecution", meta = (Input, Output))`
- L71 _public member_ `FIKRetargetWorkData WorkData;` — `UPROPERTY(meta = (Hidden))`

#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("UAF RigUnit: IK Retargeter Total"), STAT_AnimNext_RigUnit_IKRetargeter, ST`
