# Plugins / RigMapperOp

- module root: `Plugins/Experimental/Animation/RigMapperOp/Source/RigMapperOp`
- headers: 2; symbols: 80
- symbol kinds: class=3, function=19, macro=2, member=17, prototype=29, struct=8, typedef=2
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: AnimationCore, Core, CoreUObject, Engine, IKRig, RigMapper
- PublicDependencyModuleNames: 

### `Plugins/Experimental/Animation/RigMapperOp/Source/RigMapperOp/Public/RigMapperOp.h` (Public)


#### struct `FIKRetargetRigMapperOpSettingsBase`  
`struct FIKRetargetRigMapperOpSettingsBase : public FIKRetargetOpSettingsBase`  
_L22-34_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FIKRetargetOpSettingsBase`
- L33 _public member_ `bool bCopyAllSourceCurves = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Copy Curves")` — Whether to copy all curves over to the target animation instance NOTE: This setting also applies when exporting retargeted animations. True: all source curves are copied to the target animation instance/asset False: only remapped curves are copied on the target animation instance/asset In general, we should set this to true if the source and target rig are the same, and the RigMapper covers only a subset of the controls, but false otherwise.

#### struct `FIKRetargetRigMapperOpSettings`  
`struct FIKRetargetRigMapperOpSettings : public FIKRetargetRigMapperOpSettingsBase`  
_L37-56_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Single Definition RigMapper Settings"))`
- inherits: `FIKRetargetRigMapperOpSettingsBase`
- L43 _public member_ `TObjectPtr<URigMapperDefinition> Definition;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RigMapper)` — User defined RigMapper definition
- L48 _public member_ `bool bOverrideFromUserDataDefinitions = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RigMapper)` — Whether should RigMapper definition be overridden with the array of definitions from target skeletal mesh UserData NOTE: Should not be used if there are multiple single RigMapper ops in the sequence
- L52 _public member_ `TArray<TObjectPtr<URigMapperDefinition>> Definitions;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use Definition instead"))` — TODO: Remove in UE 5.8
- L54 _public prototype_ `virtual const UClass* GetControllerType() const override;`
- L55 _public prototype_ `virtual void CopySettingsAtRuntime(const FIKRetargetOpSettingsBase* InSettingsToCopyFrom) override;`

#### struct `FIKRetargetRigMapperUserDataOpSettings`  
`struct FIKRetargetRigMapperUserDataOpSettings : public FIKRetargetRigMapperOpSettingsBase`  
_L59-65_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "UserData RigMapper Settings"))`
- inherits: `FIKRetargetRigMapperOpSettingsBase`
- L63 _public prototype_ `virtual const UClass* GetControllerType() const override;`
- L64 _public prototype_ `virtual void CopySettingsAtRuntime(const FIKRetargetOpSettingsBase* InSettingsToCopyFrom) override;`

#### struct `FRigMapperOpHelper`  
`struct FRigMapperOpHelper`  
_L68-136_
- desc: A helper struct containing business logic common for all RigMapper ops
- L71 _public prototype_ `FRigMapperOpHelper() = default;`
- L73 _public prototype_ `bool InitializeRigMapping(const TArray<URigMapperDefinition*>& InDefinitions);`
- L75 _public prototype_ `void ProcessAnimSequenceCurves(FIKRetargetCurvesOpBase::FCurveData InCurveMetaData, FIKRetargetCurvesOpBase::FFrameValues InCurveFrameValues, FIKRetargetCurvesOpBase::FCurveData& OutCurveMetaData, FIKRetargetCurvesOpBase::FFrameValues& OutCurveFrameValues, bool bCopyAllSourceCurves) const;`
- L78 _public prototype_ `void EvaluateRigMapping(const FBlendedCurve& InCurve, FBlendedCurve& OutCurve);`
- L80 _public prototype_ `bool CheckReInit(const TArray<URigMapperDefinition*>& InCurrentDefinitions);`
- L82 _public function_ `bool IsValid() const`
- L84 _public prototype_ `static URigMapperDefinitionUserData* GetUserDataFromMesh(const USkeletalMesh* InMesh);`
- L89 _private member_ `TArray<TObjectPtr<URigMapperDefinition>> LoadedDefinitions;` — The definitions that we have loaded. Cached to check against changes and reinit if need be
- L92 _private member_ `FRigMapperProcessor RigMapperProcessor;` — The processor to evaluate the rig mapping
- L95 _private member_ `FRigMapperProcessor::FPoseValues CachedInputValues;` — The cached input values passed to the rig mapper processor to avoid reallocations
- L98 _private member_ `FRigMapperProcessor::FPoseValues CachedOutputValues;` — The cached output values passed to the rig mapper processor to avoid reallocations
- L130 _private typedef_ `using FInputCurveMappings = UE::Anim::TNamedValueArray<FDefaultAllocator, FRigMapperCurveMapping>;` — Input curve mapping for bulk get of the curve values
- L131 _private member_ `FInputCurveMappings InputCurveMappings;`
- L134 _private typedef_ `using FOutputCurveMappings = UE::Anim::TNamedValueArray<FDefaultAllocator, FRigMapperOutputCurveMapping>;` — Output curve mapping for the bulk get of the curve values
- L135 _private member_ `FOutputCurveMappings OutputCurveMappings;`

#### struct `FRigMapperOpHelper::FRigMapperCurveMapping`  
`struct FRigMapperCurveMapping`  
_L101-113_
- desc: Base curve mapping for bulk get/set of the linked pose curves
- L103 _public prototype_ `FRigMapperCurveMapping() = default;`
- L105 _public function_ `FRigMapperCurveMapping(FName InName, int32 InCurveIndex) : Name(InName) , CurveIndex(InCurveIndex)`
- L111 _public member_ `FName Name = NAME_None;`
- L112 _public member_ `int32 CurveIndex = INDEX_NONE;`

#### struct `FRigMapperOpHelper::FRigMapperOutputCurveMapping`  
`struct FRigMapperOutputCurveMapping : FRigMapperCurveMapping`  
_L116-127_
- inherits: `FRigMapperCurveMapping`
- desc: Curve mapping for bulk set of the curves with a mapping to the matching input
- L118 _public prototype_ `FRigMapperOutputCurveMapping() = default;`
- L120 _public function_ `FRigMapperOutputCurveMapping(FName InName, int32 InOutputCurveIndex, int32 InInputCurveIndex) : FRigMapperCurveMapping(InName, InOutputCurveIndex) , InputCurveIndex(InInputCurveIndex)`
- L126 _public member_ `int32 InputCurveIndex = INDEX_NONE;`

#### struct `FIKRetargetRigMapperOp`  
`struct FIKRetargetRigMapperOp : public FIKRetargetCurvesOpBase`  
_L140-205_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Single RigMapper"))`
- inherits: `FIKRetargetCurvesOpBase`
- desc: Single definition RigMapper op with an option to use UserData definitions array
- L145 _public prototype_ `virtual bool Initialize( const FIKRetargetProcessor& InProcessor, const FRetargetSkeleton& InSourceSkeleton, const FTargetSkeleton& InTargetSkeleton, const FIKRetargetOpBase* InParentOp, FIKRigLogger& Log) override;`
- L153 _public function_ `virtual void Run( FIKRetargetProcessor& InProcessor, const double InDeltaTime, const TArray<FTransform>& InSourceGlobalPose, TArray<FTransform>& OutTargetGlobalPose) override` — NOTE: RigMapper ops do not do anything in Run().
- L159 _public function_ `virtual FIKRetargetOpSettingsBase* GetSettings() override`
- L164 _public function_ `virtual void SetSettings(const FIKRetargetOpSettingsBase* InSettings) override`
- L169 _public function_ `virtual const UScriptStruct* GetSettingsType() const override`
- L174 _public function_ `virtual const UScriptStruct* GetParentOpType() const override`
- L179 _public function_ `virtual const UScriptStruct* GetType() const override`
- L184 _public function_ `virtual bool IsAbstract() const override`
- L186 _public function_ `virtual bool IsSingleton() const override`
- L188 _public prototype_ `virtual void ProcessAnimSequenceCurves(FIKRetargetCurvesOpBase::FCurveData InCurveMetaData, FIKRetargetCurvesOpBase::FFrameValues InCurveFrameValues, FIKRetargetCurvesOpBase::FCurveData& OutCurveMetaData, FIKRetargetCurvesOpBase::FFrameValues& OutCurveFrameValues) const override;`
- L191 _public prototype_ `virtual void AnimGraphPreUpdateMainThread(USkeletalMeshComponent& SourceMeshComponent, USkeletalMeshComponent& TargetMeshComponent) override;`
- L193 _public prototype_ `virtual void AnimGraphEvaluateAnyThread(FPoseContext& Output) override;`
- L195 _public prototype_ `bool PostLoadSplitOp(TArray<FInstancedStruct>& OutNewOps);`
- L198 _public member_ `FIKRetargetRigMapperOpSettings Settings;` — `UPROPERTY()`
- L201 _protected prototype_ `TArray<URigMapperDefinition*> GetDefinitionsToLoad(const USkeletalMesh* InTargetMesh);`
- L204 _protected member_ `FRigMapperOpHelper Helper;` — A helper struct containing business logic common for all RigMapper ops

#### class `UIKRetargetRigMapperOpController`  
`class UIKRetargetRigMapperOpController : public UIKRetargetOpControllerBase`  
_L209-223_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UIKRetargetOpControllerBase`
- desc: The blueprint/python API for editing a RigMapper Op
- L217 _public prototype_ `FIKRetargetRigMapperOpSettings GetSettings();` — `UFUNCTION(BlueprintCallable, Category = Settings)` — Get the current op settings as a struct. @return FIKRetargetRigMapperOpSettings struct with the current settings used by the op.
- L222 _public prototype_ `void SetSettings(FIKRetargetRigMapperOpSettings InSettings);` — `UFUNCTION(BlueprintCallable, Category = Settings)` — Set the op settings. Input is a custom struct type for this op. @param InSettings a FIKRetargetRigMapperOpSettings struct containing all the settings to apply to this op

#### struct `FIKRetargetRigMapperUserDataOp`  
`struct FIKRetargetRigMapperUserDataOp : public FIKRetargetCurvesOpBase`  
_L227-291_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "UserData RigMapper"))`
- inherits: `FIKRetargetCurvesOpBase`
- desc: UserData definitions ONLY RigMapper op
- L232 _public prototype_ `virtual bool Initialize( const FIKRetargetProcessor& InProcessor, const FRetargetSkeleton& InSourceSkeleton, const FTargetSkeleton& InTargetSkeleton, const FIKRetargetOpBase* InParentOp, FIKRigLogger& Log) override;`
- L240 _public function_ `virtual void Run( FIKRetargetProcessor& InProcessor, const double InDeltaTime, const TArray<FTransform>& InSourceGlobalPose, TArray<FTransform>& OutTargetGlobalPose) override` — NOTE: RigMapper ops do not do anything in Run().
- L247 _public function_ `virtual FIKRetargetOpSettingsBase* GetSettings() override`
- L252 _public function_ `virtual void SetSettings(const FIKRetargetOpSettingsBase* InSettings) override`
- L257 _public function_ `virtual const UScriptStruct* GetSettingsType() const override`
- L262 _public function_ `virtual const UScriptStruct* GetParentOpType() const override`
- L267 _public function_ `virtual const UScriptStruct* GetType() const override`
- L272 _public function_ `virtual bool IsAbstract() const override`
- L274 _public function_ `virtual bool IsSingleton() const override`
- L276 _public prototype_ `virtual void ProcessAnimSequenceCurves(FIKRetargetCurvesOpBase::FCurveData InCurveMetaData, FIKRetargetCurvesOpBase::FFrameValues InCurveFrameValues, FIKRetargetCurvesOpBase::FCurveData& OutCurveMetaData, FIKRetargetCurvesOpBase::FFrameValues& OutCurveFrameValues) const;`
- L279 _public prototype_ `virtual void AnimGraphPreUpdateMainThread(USkeletalMeshComponent& SourceMeshComponent, USkeletalMeshComponent& TargetMeshComponent) override;`
- L281 _public prototype_ `virtual void AnimGraphEvaluateAnyThread(FPoseContext& Output) override;`
- L284 _public member_ `FIKRetargetRigMapperUserDataOpSettings Settings;` — `UPROPERTY()`
- L287 _protected prototype_ `TArray<URigMapperDefinition*> GetDefinitionsToLoad(const USkeletalMesh* InTargetMesh);`
- L290 _protected member_ `FRigMapperOpHelper Helper;` — A helper struct containing business logic common for all RigMapper ops

#### class `UIKRetargetRigMapperUserDataOpController`  
`class UIKRetargetRigMapperUserDataOpController : public UIKRetargetOpControllerBase`  
_L295-310_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UIKRetargetOpControllerBase`
- desc: The blueprint/python API for editing a RigMapper UserData Op
- L303 _public prototype_ `FIKRetargetRigMapperUserDataOpSettings GetSettings();` — `UFUNCTION(BlueprintCallable, Category = Settings)` — Get the current op settings as a struct. @return FIKRetargetRigMapperUserDataOpSettings struct with the current settings used by the op.
- L308 _public prototype_ `void SetSettings(FIKRetargetRigMapperUserDataOpSettings InSettings);` — `UFUNCTION(BlueprintCallable, Category = Settings)` — Set the op settings. Input is a custom struct type for this op. @param InSettings a FIKRetargetRigMapperUserDataOpSettings struct containing all the settings to apply to this op

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API RIGMAPPEROP_API`
- L14 _macro_ `#define LOCTEXT_NAMESPACE "RigMapperOp"`

### `Plugins/Experimental/Animation/RigMapperOp/Source/RigMapperOp/Public/RigMapperOpModule.h` (Public)


#### class `FRigMapperOpModule`  
`class FRigMapperOpModule : public IModuleInterface`  
_L7-14_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L13 _public prototype_ `virtual void ShutdownModule() override;`
