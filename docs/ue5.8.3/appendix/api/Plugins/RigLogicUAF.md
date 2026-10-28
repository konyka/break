# Plugins / RigLogicUAF

- module root: `Plugins/Experimental/RigLogicUAF/Source/RigLogicUAF`
- headers: 5; symbols: 66
- symbol kinds: class=2, delegate=2, macro=1, member=23, namespace=8, prototype=21, struct=7, typedef=2
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: CoreUObject, Engine, Slate, SlateCore
- PublicDependencyModuleNames: Core, Engine, RigLogicModule, UAF, UAFAnimGraph

### `Plugins/Experimental/RigLogicUAF/Source/RigLogicUAF/Public/RigLogicInstanceData.h` (Public)


#### struct `UE::UAF::FRigLogicBoneMapping`  
`struct FRigLogicBoneMapping`  
_L15-19_
- L17 _public member_ `uint16 RigLogicJointIndex;`
- L18 _public member_ `int32 PoseBoneIndex;` — uint16 RigLogicJointIndex;   RigLogic joint index based on the internal RigLogic skeleton. Bone indices differ from the skeleton or skeletal mesh bone indices and need translation.

#### struct `UE::UAF::FPoseBoneControlAttributeMapping`  
`struct FPoseBoneControlAttributeMapping`  
_L21-29_
- L23 _public member_ `int32 PoseBoneIndex;`
- L24 _public member_ `int32 DNAJointIndex;` — int32 PoseBoneIndex;   Pose bone index based on the given LOD level.
- L25 _public member_ `int32 RotationX;`
- L26 _public member_ `int32 RotationY;`
- L27 _public member_ `int32 RotationZ;`
- L28 _public member_ `int32 RotationW;`

#### struct `UE::UAF::FRigLogicInstanceData`  
`struct FRigLogicInstanceData`  
_L32-53_
- desc: Instance data unique per reference pose, cloned by the maximum number of parallel evaluations. TODO: Better call it PoolData?
- L35 _public member_ `TSharedPtr<FSharedRigRuntimeContext> CachedRigRuntimeContext;` — Cached pointer to the shared RigLogic runtime context originally owned by UDNAAsset.
- L38 _public member_ `TSharedPtr<FDNAIndexMapping> CachedDNAIndexMapping;` — Cached pointer to the DNA index mapping which is originally owned by UDNAAsset.
- L41 _public member_ `TArray<TArray<FRigLogicBoneMapping>> RigLogicToSkeletonBoneIndexMappingPerLOD;` — Bone index mapping from a RigLogic joint index to the reference skeleton bone index, one per LOD level.
- L43 _public member_ `TArray<TArray<FPoseBoneControlAttributeMapping>> SparseDriverJointsToControlAttributesMapPerLOD;`
- L44 _public member_ `TArray<TArray<FPoseBoneControlAttributeMapping>> DenseDriverJointsToControlAttributesMapPerLOD;`
- L46 _public member_ `uint32 NumLODs = 0;`
- L48 _public prototype_ `void Init(const UE::UAF::FReferencePose* ReferencePose);`
- L51 _private prototype_ `void InitBoneIndexMapping(const UE::UAF::FReferencePose* ReferencePose);`
- L52 _private prototype_ `void InitSparseAndDenseDriverJointMapping(const UE::UAF::FReferencePose* ReferencePose);`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/RigLogicUAF/Source/RigLogicUAF/Public/RigLogicInstanceDataPool.h` (Public)


#### class `UE::UAF::FRigLogicInstanceDataPool`  
`class FRigLogicInstanceDataPool`  
_L9-21_
- L12 _public member_ `TMap<TWeakObjectPtr<const USkeletalMesh>, TArray<TSharedPtr<FRigLogicInstanceData>>> Datas;`
- L14 _public member_ `mutable FCriticalSection PoolAccessCriticalSection;`
- L16 _public prototype_ `TSharedPtr<FRigLogicInstanceData> RequestData(const UE::UAF::FReferencePose* InReferencePose);`
- L17 _public prototype_ `void FreeData(TWeakObjectPtr<const USkeletalMesh> SkeletalMesh, TSharedPtr<FRigLogicInstanceData> InData);`
- L19 _public prototype_ `void GarbageCollect();`
- L20 _public prototype_ `void Log();`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/RigLogicUAF/Source/RigLogicUAF/Public/RigLogicTask.h` (Public)


#### struct `FUAFRigLogicTask`  
`struct FUAFRigLogicTask : public FAnimNextEvaluationTask`  
_L24-57_
- reflection: `USTRUCT()`
- inherits: `FAnimNextEvaluationTask`
- L28 _public prototype_ `DECLARE_ANIM_EVALUATION_TASK(FUAFRigLogicTask) static FUAFRigLogicTask Make(UE::UAF::FRigLogicTrait::FInstanceData* InstanceData);`
- L33 _public prototype_ `virtual void Execute(UE::UAF::FEvaluationVM& VM) const override;` — Task entry point
- L35 _public typedef_ `using FCachedIndexedCurve = TBaseBlendedCurve<FDefaultAllocator, UE::Anim::FCurveElementIndexed>;`
- L36 _public member_ `static constexpr uint16 ATTR_COUNT_PER_JOINT = 10;`
- L38 _public prototype_ `void UpdateControlCurves(FRigInstance* InRigInstance, const FBlendedCurve& Curves, const FCachedIndexedCurve& ControlAttributeCurves, const FCachedIndexedCurve& MLMaskCurves, const TArrayView<const float> NeutralJointValues, const TArrayView<const UE::UAF::FPoseBoneControlAttributeMapping> SparseDriverJointsToControlAttributesMap, const TArrayView<const UE::UAF::FPoseBoneControlAttributeMapping> DenseDriverJointsToControlAttributesMap, const UE::UAF::FLODPoseStack& InputPose) const;`
- L47 _public prototype_ `static void UpdateJoints(const TArrayView<const UE::UAF::FRigLogicBoneMapping> RigLogicIndexToMeshIndexMapping, const TArrayView<const uint16> VariableJointIndices, const TArrayView<const float> NeutralJointValues, const TArrayView<const float> DeltaJointValues, UE::UAF::FLODPoseStack& OutputPose);`
- L53 _public prototype_ `static void UpdateBlendShapeCurves(const FCachedIndexedCurve& MorphTargetCurves, const TArrayView<const float> BlendShapeValues, FBlendedCurve& OutputCurves);`
- L54 _public prototype_ `static void UpdateAnimMapCurves(const FCachedIndexedCurve& MaskMultiplierCurves, const TArrayView<const float> AnimMapOutputs, FBlendedCurve& OutputCurves);`
- L56 _public member_ `UE::UAF::FRigLogicTrait::FInstanceData* TraitInstanceData = nullptr;`

#### Free symbols / members of external scopes

- L21 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("UAF Task: RigLogic"), STAT_UAF_Task_RigLogic, STATGROUP_AnimNext,`

### `Plugins/Experimental/RigLogicUAF/Source/RigLogicUAF/Public/RigLogicTrait.h` (Public)


#### struct `FUAFRigLogicTraitSharedData`  
`struct FUAFRigLogicTraitSharedData : public FAnimNextTraitSharedData`  
_L17-38_
- reflection: `USTRUCT(meta = (DisplayName = "RigLogic"))`
- inherits: `FAnimNextTraitSharedData`
- L22 _public member_ `FAnimNextTraitHandle Input;` — `UPROPERTY()`
- L30 _public member_ `int32 LODThreshold = INDEX_NONE;` — `UPROPERTY(EditAnywhere, Category = RigLogic)` — Max LOD level that post-process AnimBPs are evaluated. For example if you have the threshold set to 2, it will evaluate until including LOD 2 (based on 0 index). In case the LOD level gets set to 3, it will stop evaluating the post-process AnimBP. Setting it to -1 will always evaluate it and disable LODing.

#### struct `UE::UAF::FRigLogicTrait`  
`struct FRigLogicTrait : FBaseTrait, IEvaluate, IUpdate, IUpdateTraversal, IHierarchy`  
_L47-76_
- inherits: `FBaseTrait,IEvaluate,IUpdate,IUpdateTraversal,IHierarchy`
- desc: FRigLogicTrait A trait that can run RigLogic.
- L51 _public typedef_ `using FSharedData = FUAFRigLogicTraitSharedData;`
- L64 _public prototype_ `virtual void PostEvaluate(FEvaluateTraversalContext& Context, const TTraitBinding<IEvaluate>& Binding) const override;` — IEvaluate impl
- L68 _public prototype_ `virtual void OnBecomeRelevant(FUpdateTraversalContext& Context, const TTraitBinding<IUpdate>& Binding, const FTraitUpdateState& TraitState) const override;` — IUpdate impl Called before the first update when a trait stack becomes relevant
- L71 _public prototype_ `virtual void QueueChildrenForTraversal(FUpdateTraversalContext& Context, const TTraitBinding<IUpdateTraversal>& Binding, const FTraitUpdateState& TraitState, FUpdateTraversalQueue& TraversalQueue) const override;` — IUpdateTraversal impl
- L74 _public prototype_ `virtual uint32 GetNumChildren(const FExecutionContext& Context, const TTraitBinding<IHierarchy>& Binding) const override;` — IHierarchy impl
- L75 _public prototype_ `virtual void GetChildren(const FExecutionContext& Context, const TTraitBinding<IHierarchy>& Binding, FChildrenArray& Children) const override;`

#### struct `UE::UAF::FRigLogicTrait::FInstanceData`  
`struct FInstanceData : FTrait::FInstanceData`  
_L54-61_
- inherits: `FTrait::FInstanceData`
- desc: Do we need this? Or is the input in the shared data sufficient?
- L57 _public member_ `FTraitPtr Input;` — Input node from which we receive the input pose as well as the facial expression curves.
- L60 _public member_ `TUniquePtr<FRigInstance> RigInstance;` — Actually cloned RigLogic instance owned by this class.

#### Free symbols / members of external scopes

- L33 _macro_ `#define TRAIT_LATENT_PROPERTIES_ENUMERATOR(GeneratorMacro) \` — Latent pin support boilerplate
- L40 _namespace_ `namespace UE`
- L40 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/RigLogicUAF/Source/RigLogicUAF/Public/RigLogicUAF.h` (Public)


#### class `UE::UAF::FRigLogicModule`  
`class FRigLogicModule : public IModuleInterface`  
_L12-20_
- inherits: `IModuleInterface`
- L16 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L17 _public prototype_ `virtual void ShutdownModule() override;`
- L19 _public member_ `UE::UAF::FRigLogicInstanceDataPool DataPool;`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogRigLogicUAF, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogRigLogicUAF, Log, All);`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace UAF` (scope `UE`)
