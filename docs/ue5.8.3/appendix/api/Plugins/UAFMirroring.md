# Plugins / UAFMirroring

- module root: `Plugins/Experimental/UAF/UAFMirroring/Source/UAFMirroring`
- headers: 4; symbols: 68
- symbol kinds: macro=1, member=23, namespace=8, prototype=20, struct=10, typedef=6
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: AnimationCore, Core, CoreUObject, Engine, RigVM, UAF, UAFAnimGraph
- PublicDependencyModuleNames: 

### `Plugins/Experimental/UAF/UAFMirroring/Source/UAFMirroring/Internal/MirroringTraitData.h` (Internal)


#### struct `FMirroringTraitSharedData`  
`struct FMirroringTraitSharedData : public FAnimNextTraitSharedData`  
_L13-37_
- reflection: `USTRUCT(meta = (DisplayName = "Mirroring", ShowTooltip = true))`
- inherits: `FAnimNextTraitSharedData`
- desc: A trait that can mirror an input's keyframe data.
- L19 _public member_ `FAnimNextTraitHandle Input;` — `UPROPERTY()` — Input node to query the keyframe to be mirrored.
- L23 _public member_ `FUAFMirroringTraitSetupParams Setup;` — `UPROPERTY(EditAnywhere, Category = "Setup", meta=(ShowOnlyInnerProperties))` — Defines whether to perform mirror pass (and what data table to use).
- L27 _public member_ `FUAFMirroringTraitApplyToParams ApplyTo;` — `UPROPERTY(EditAnywhere, Category = "Apply To", meta=(ShowOnlyInnerProperties))` — Defines what channels will be affected during the mirror pass.

#### struct `FMirroringAdditiveTraitSharedData`  
`struct FMirroringAdditiveTraitSharedData : public FAnimNextTraitSharedData`  
_L41-60_
- reflection: `USTRUCT(meta = (DisplayName = "Mirroring", ShowTooltip = true))`
- inherits: `FAnimNextTraitSharedData`
- desc: Same behaviour as FMirroringTrait, but as an additive (i.e. it only mirrors the super-trait’s output).
- L47 _public member_ `FUAFMirroringTraitSetupParams Setup;` — `UPROPERTY(EditAnywhere, Category = "Setup", meta=(ShowOnlyInnerProperties))` — Defines whether to perform mirror pass (and what data table to use).
- L51 _public member_ `FUAFMirroringTraitApplyToParams ApplyTo;` — `UPROPERTY(EditAnywhere, Category = "Apply To", meta=(ShowOnlyInnerProperties))` — Defines what channels will be affected during the mirror pass.

#### Free symbols / members of external scopes

- L30 _macro_ `#define TRAIT_LATENT_PROPERTIES_ENUMERATOR(GeneratorMacro) \` — Latent pin support boilerplate
- L62 _namespace_ `namespace UE`
- L62 _namespace_ `namespace UAF` (scope `UE`)
- L65 _typedef_ `using FMirroringTraitData = FMirroringTraitSharedData;` (scope `UE::UAF`) — Namespaced alias
- L66 _typedef_ `using FMirroringAdditiveTraitData = FMirroringAdditiveTraitSharedData;` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFMirroring/Source/UAFMirroring/Private/Mirroring.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace UAF` (scope `UE`)
- L11 _prototype_ `int32 GetNumOfBonesForMirrorData(const FReferencePose & InReferencePose);` (scope `UE::UAF`) — Number of mesh bones (use this when pre-sizing the arrays for bind pose mirror data and mirror map).
- L24 _prototype_ `void BuildReferencePoseMirrorData( const FReferencePose& InReferencePose, EAxis::Type InMirrorAxis, TConstArrayView<FBoneIndexType> InMeshBoneIndexToMirroredMeshBoneIndexMap, TArrayView<FQuat> OutRefPoseMeshSpaceRotations, TArrayView<FQuat> OutRefPoseMeshSpaceRotationCorrections);` (scope `UE::UAF`) — Build the bind-pose data needed to mirror a pose. * @param InReferencePose Reference/bind pose context. Used to access bind pose local transforms and parent maps. @param InMirrorAxis Mirror axis (X/Y/Z) @param InMeshBoneIndexToMirroredMeshBoneIndexMap Array view of mirrored mesh bone indices @param OutRefPoseMeshSpaceRotations A pre-sized array view to fill reference pose rotations in mesh space @param OutRefPoseMeshSpaceRotationCorrections A pre-sized array view to fill reference pose rotation corrections in mesh space @note Output arrays are expected to be pre-sized to the number of bones in the reference pose's skeleton (i.e. LOD0).
- L40 _prototype_ `void BuildMeshBoneIndexMirrorMap( const FReferencePose& InReferencePose, const UMirrorDataTable& InMirrorDataTable, TArrayView<FBoneIndexType> OutMeshBoneIndexToMirroredMeshBoneIndexMap);` (scope `UE::UAF`) — Build a mesh-bone mirror map from a mirror data table. @param InReferencePose Reference/bind pose context. Used to query a mesh bone index by name. @param InMirrorDataTable Data table with mirror bone name pairs (and mirror axis) @param OutMeshBoneIndexToMirroredMeshBoneIndexMap A pre-sized array view to fill with mirrored mesh bone indices. @note Output map is expected to be pre-sized to the number of bones in the reference pose's skeleton (i.e. LOD0)
- L51 _prototype_ `void MirrorPose( FLODPose& InOutLODPose, const UMirrorDataTable& InMirrorDataTable);` (scope `UE::UAF`) — Mirror a pose in place using a mirror data table. @param InOutLODPose Pose to mirror (local-space) @param InMirrorDataTable Data table with mirror bone name pairs (and mirror axis)
- L66 _prototype_ `void MirrorPose( FLODPose& InOutLODPose, EAxis::Type InMirrorAxis, TConstArrayView<FBoneIndexType> InMeshBoneIndexToMirroredMeshBoneIndexMap, TConstArrayView<FQuat> InRefPoseMeshSpaceRotations, TConstArrayView<FQuat> InRefPoseMeshSpaceRotationCorrections);` (scope `UE::UAF`) — Mirror a pose in place using explicit mirror axis + precomputed bind-pose data. @param InOutLODPose Pose to mirror (local-space) @param InMirrorAxis Mirror axis (X/Y/Z) @param InMeshBoneIndexToMirroredMeshBoneIndexMap Mapping from mesh bone index to its mirrored counterpart (if any) @param InRefPoseMeshSpaceRotations Reference pose rotations in mesh space @param InRefPoseMeshSpaceRotationCorrections Reference pose rotation corrections in mesh space @note Input map and arrays are expected to be the size of to the number of bones in the reference pose's skeleton (i.e. LOD0)

### `Plugins/Experimental/UAF/UAFMirroring/Source/UAFMirroring/Private/MirroringTrait.h` (Private)


#### struct `UE::UAF::FMirroringTrait`  
`struct FMirroringTrait : FBaseTrait, IEvaluate, IHierarchy, IGarbageCollection`  
_L27-56_
- inherits: `FBaseTrait,IEvaluate,IHierarchy,IGarbageCollection`
- desc: Mirroring Base Trait A trait that can mirror an input's keyframe data.
- L31 _public typedef_ `using FSharedData = FMirroringTraitSharedData;`
- L48 _public prototype_ `virtual void PostEvaluate(FEvaluateTraversalContext& Context, const TTraitBinding<IEvaluate>& Binding) const override;` — IEvaluate impl
- L51 _public prototype_ `virtual uint32 GetNumChildren(const FExecutionContext& Context, const TTraitBinding<IHierarchy>& Binding) const override;` — IHierarchy impl
- L52 _public prototype_ `virtual void GetChildren(const FExecutionContext& Context, const TTraitBinding<IHierarchy>& Binding, FChildrenArray& Children) const override;`
- L55 _public prototype_ `virtual void AddReferencedObjects(const FExecutionContext& Context, const TTraitBinding<IGarbageCollection>& Binding, FReferenceCollector& Collector) const override;` — IGarbageCollection impl

#### struct `UE::UAF::FMirroringTrait::FInstanceData`  
`struct FInstanceData : FTrait::FInstanceData`  
_L33-45_
- inherits: `FTrait::FInstanceData`
- L36 _public member_ `FTraitPtr Input;` — Input node to query the keyframe to be mirrored.
- L39 _public member_ `TSharedPtr<FAnimNextEvaluationMirroringTask> Task;` — Task containing the setup data on how to do the mirroring
- L42 _public member_ `bool bHasMirrorStateChanged = false;` — Used to trigger inertial blends.
- L44 _public prototype_ `void Construct(const FExecutionContext& Context, const FTraitBinding& Binding);`

#### struct `UE::UAF::FMirroringAdditiveTrait`  
`struct FMirroringAdditiveTrait : FAdditiveTrait, IUpdate, IEvaluate, IGarbageCollection`  
_L63-85_
- inherits: `FAdditiveTrait,IUpdate,IEvaluate,IGarbageCollection`
- desc: Mirroring Additive Trait Same behaviour as FMirroringTrait, but as an additive (i.e. it only mirrors the super-trait’s output).
- L67 _public typedef_ `using FSharedData = FMirroringAdditiveTraitSharedData;`
- L81 _public prototype_ `virtual void PostEvaluate(FEvaluateTraversalContext& Context, const TTraitBinding<IEvaluate>& Binding) const override;` — IEvaluate impl
- L84 _public prototype_ `virtual void AddReferencedObjects(const FExecutionContext& Context, const TTraitBinding<IGarbageCollection>& Binding, FReferenceCollector& Collector) const override;` — IGarbageCollection impl

#### struct `UE::UAF::FMirroringAdditiveTrait::FInstanceData`  
`struct FInstanceData : FTrait::FInstanceData`  
_L69-78_
- inherits: `FTrait::FInstanceData`
- L71 _public member_ `TSharedPtr<FAnimNextEvaluationMirroringTask> Task;`
- L74 _public member_ `bool bHasMirrorStateChanged = false;` — Used to trigger inertial blends.
- L76 _public prototype_ `void Construct(const FExecutionContext& Context, const FTraitBinding& Binding);`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFMirroring/Source/UAFMirroring/Public/MirroringTask.h` (Public)


#### struct `FUAFMirroringTraitSetupParams`  
`struct FUAFMirroringTraitSetupParams`  
_L21-32_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Mirroring Trait Setup Parameters"))`
- desc: Mirroring Setup Parameters This struct holds the minimal configuration needed to enable a mirror pass. @see UMirrorDataTable, FMirroringTrait, FMirroringAdditiveTrait
- L27 _public member_ `bool bShouldMirror = true;` — `UPROPERTY(EditAnywhere, Category = Settings, meta=(DisplayName = "Mirror"))` — Whether to perform mirror pass
- L31 _public member_ `TObjectPtr<const UMirrorDataTable> MirrorDataTable = nullptr;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (ExportAsReference="true"))` — Data table to map bones to their mirrored counterpart

#### struct `FUAFMirroringTraitApplyToParams`  
`struct FUAFMirroringTraitApplyToParams`  
_L42-57_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Mirroring Trait Apply To Parameters"))`
- desc: Mirroring Apply/Filter Parameters This struct holds flags for the channels that can be affected during the mirror pass (i.e. Bones, Curves, Attributes). @see FMirroringTrait, FMirroringAdditiveTrait, FAnimNextEvaluationMirroringTask
- L48 _public member_ `bool bShouldMirrorBones = true;` — `UPROPERTY(EditAnywhere, Category = Channels, meta=(DisplayName = "Bones"))` — Whether to mirror bone transforms
- L52 _public member_ `bool bShouldMirrorCurves = true;` — `UPROPERTY(EditAnywhere, Category = Channels, meta=(DisplayName = "Curves"))` — Whether to mirror animation curves
- L56 _public member_ `bool bShouldMirrorAttributes = true;` — `UPROPERTY(EditAnywhere, Category = Channels, meta=(DisplayName = "Attributes"))` — Whether to mirror attributes

#### struct `UE::UAF::FMirroringTraitCache`  
`struct FMirroringTraitCache`  
_L72-112_
- desc: Mirroring Cache Holds all precomputed data needed to mirror keyframe output efficiently, so it doesn’t have to be rebuilt every evaluation. @see FAnimNextEvaluationMirroringTask
- L75 _public member_ `TArray<FBoneIndexType> MeshBoneIndexToMirroredMeshBoneIndexMap;` — Cached mirror indices map (invalidated on skeletal mesh or mirror data table change)
- L78 _public member_ `TArray<FQuat> MeshSpaceReferencePoseRotations;` — Cached bind pose rotations (invalidated on skeletal mesh change)
- L81 _public member_ `TArray<FQuat> MeshSpaceReferenceRotationCorrections;` — Cached bind pose rotation corrections (invalidated on skeletal mesh change)
- L84 _public member_ `TCustomBoneIndexArray<FCompactPoseBoneIndex, FCompactPoseBoneIndex> CompactPoseBoneIndexToMirroredCompactPoseBoneIndexMap;` — Cached mirror indices map but using FCompactPoseIndex (invalidated on skeletal mesh or mirror data table change)
- L87 _public member_ `TWeakObjectPtr<const USkeletalMesh> SkeletalMesh = nullptr;` — Skeletal mesh used to build this cache
- L90 _public member_ `TWeakObjectPtr<const UMirrorDataTable> MirrorTable = nullptr;` — Mirror data table used to build this cache
- L96 _public prototype_ `bool AreMirrorMapsValid(const UE::UAF::FReferencePose& InReferencePose, const TWeakObjectPtr<const UMirrorDataTable>& InMirrorTable, bool bInShouldMirrorBones, bool bInShouldMirrorAttributes) const;` — True if the cached mirror maps were generated using exactly these assets. Any mismatch (different mesh/mirror table, size mismatch) means you must rebuild the mirror maps.
- L102 _public prototype_ `bool IsReferencePoseDataValid(const UE::UAF::FReferencePose& InReferencePose, bool bInShouldMirrorBones) const;` — True if the cached bind/reference-pose data matches this mesh. Any mismatch (different mesh table, size mismatch)  means you must rebuild the reference-pose arrays.
- L108 _public prototype_ `bool IsValid(const UE::UAF::FReferencePose& InReferencePose, const TWeakObjectPtr<const UMirrorDataTable>& InMirrorTable, bool bInShouldMirrorBones, bool bInShouldMirrorAttributes) const;` — True if the cache was generated using exactly these assets. Any mismatch (different mesh/mirror table, size mismatch) means you must rebuild the cache.
- L111 _public prototype_ `void Clear();` — Empty arrays and reset ptrs to assets

#### struct `FAnimNextEvaluationMirroringTask`  
`struct FAnimNextEvaluationMirroringTask : public FAnimNextEvaluationTask`  
_L122-145_
- reflection: `USTRUCT()`
- inherits: `FAnimNextEvaluationTask`
- desc: Mirroring Task This pop the top keyframe from the VM keyframe stack, mirrors it, and pushes back the result onto the stack.
- L126 _public prototype_ `DECLARE_ANIM_EVALUATION_TASK(FAnimNextEvaluationMirroringTask)`
- L133 _public member_ `FUAFMirroringTraitApplyToParams ApplyTo;` — `UPROPERTY(VisibleAnywhere, Category = "Apply To")`
- L136 _public member_ `mutable UE::UAF::FMirroringTraitCache Cache;` — Cache for bind pose rotation, corrections, and mirror map
- L139 _public prototype_ `virtual void Execute(UE::UAF::FEvaluationVM& VM) const override;` — Task entry point
- L144 _private prototype_ `void EnsureCache(const UE::UAF::FEvaluationVM& VM, const UE::UAF::FReferencePose& InReferencePose) const;` — Ensures the mirror cache matches the given inputs, rebuilds if stale.

#### Free symbols / members of external scopes

- L59 _namespace_ `namespace UE`
- L59 _namespace_ `namespace UAF` (scope `UE`)
- L62 _typedef_ `using FMirroringTraitSetupParams = FUAFMirroringTraitSetupParams;` (scope `UE::UAF`) — Namespaced alias
- L63 _typedef_ `using FMirroringTraitApplyToParams = FUAFMirroringTraitApplyToParams;` (scope `UE::UAF`)
