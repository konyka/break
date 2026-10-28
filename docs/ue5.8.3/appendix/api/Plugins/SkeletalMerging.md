# Plugins / SkeletalMerging

- module root: `Plugins/Runtime/SkeletalMerging/Source/SkeletalMerging`
- headers: 1; symbols: 28
- symbol kinds: class=1, delegate=1, function=1, macro=1, member=14, prototype=8, struct=2
- PrivateDependencyModuleNames: Core, CoreUObject, Engine

### `Plugins/Runtime/SkeletalMerging/Source/SkeletalMerging/Public/SkeletalMergingLibrary.h` (Public)


#### struct `FSkeletalMeshMergeParams`  
`struct FSkeletalMeshMergeParams`  
_L17-61_
- reflection: `USTRUCT(BlueprintType)`
- desc: Struct containing all parameters used to perform a Skeletal Mesh merge.
- L21 _public function_ `FSkeletalMeshMergeParams()`
- L34 _public member_ `TArray<FSkelMeshMergeSectionMapping> MeshSectionMappings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=SkeletalMeshMerge)` — An optional array to map sections from the source meshes to merged section entries
- L38 _public member_ `TArray<FSkelMeshMergeMeshUVTransforms> UVTransformsPerMesh;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=SkeletalMeshMerge)` — An optional array to transform the UVs in each mesh
- L42 _public member_ `TArray<TObjectPtr<USkeletalMesh>> MeshesToMerge;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=SkeletalMeshMerge)` — The list of skeletal meshes to merge.
- L46 _public member_ `int32 StripTopLODS;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=SkeletalMeshMerge)` — The number of high LODs to remove from input meshes
- L50 _public member_ `uint32 bNeedsCpuAccess:1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=SkeletalMeshMerge)` — Whether or not the resulting mesh needs to be accessed by the CPU for any reason (e.g. for spawning particle effects).
- L55 _public member_ `uint32 bSkeletonBefore:1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=SkeletalMeshMerge)` — Update skeleton before merge. Otherwise, update after. Skeleton must also be provided.
- L60 _public member_ `TObjectPtr<USkeleton> Skeleton;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=SkeletalMeshMerge)` — Skeleton that will be used for the merged mesh. Leave empty if the generated skeleton is OK.

#### struct `FSkeletonMergeParams`  
`struct FSkeletonMergeParams`  
_L67-98_
- reflection: `USTRUCT(BlueprintType)`
- desc: Struct containing all parameters used to perform a Skeleton merge.
- L73 _public member_ `TArray<TObjectPtr<USkeleton>> SkeletonsToMerge;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=SkeletonMerge)` — The list of skeletons to merge.
- L77 _public member_ `bool bMergeSockets = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=SkeletonMerge)` — Whether or not to include Sockets when merging the Skeletons
- L81 _public member_ `bool bMergeVirtualBones = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=SkeletonMerge)` — Whether or not to include Virtual Bones when merging the Skeletons
- L85 _public member_ `bool bMergeCurveNames = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=SkeletonMerge)` — Whether or not to include (Animation) Curve names when merging the Skeletons
- L89 _public member_ `bool bMergeBlendProfiles = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=SkeletonMerge)` — Whether or not to include Blend Profiles when merging the Skeletons
- L93 _public member_ `bool bMergeAnimSlotGroups = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=SkeletonMerge)` — Whether or not to include Animation Slot Group (names) when merging the Skeletons
- L97 _public member_ `bool bCheckSkeletonsCompatibility = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=SkeletonMerge)` — Whether or not to check if there are invalid parent chains or shared bones with different reference transforms

#### class `USkeletalMergingLibrary`  
`class USkeletalMergingLibrary : public UBlueprintFunctionLibrary`  
_L104-128_
- reflection: `UCLASS(MinimalAPI, ClassGroup=(Custom))`
- inherits: `UBlueprintFunctionLibrary`
- desc: Component that can be used to perform Skeletal Mesh merges from Blueprints.
- L113 _public prototype_ `static class USkeletalMesh* MergeMeshes(const FSkeletalMeshMergeParams& Params);` — `UFUNCTION(BlueprintCallable, Category="Mesh Merge", meta=(UnsafeDuringActorConstruction="true"))` — Merges the given meshes into a single mesh. @return The merged mesh (will be invalid if the merge failed).
- L120 _public prototype_ `static class USkeleton* MergeSkeletons(const FSkeletonMergeParams& Params);` — `UFUNCTION(BlueprintCallable, Category="Skeleton Merge", meta=(UnsafeDuringActorConstruction="true"))` — Merges the skeletons for the provided meshes into a single skeleton. @return The merged Skeleton
- L123 _protected prototype_ `static void AddSockets(USkeleton* InSkeleton, const TArray<TObjectPtr<class USkeletalMeshSocket>>& InSockets);`
- L124 _protected prototype_ `static void AddVirtualBones(USkeleton* InSkeleton, const TArray<const struct FVirtualBone*>& InVirtualBones);`
- L125 _protected prototype_ `static void AddCurveNames(USkeleton* InSkeleton, const TMap<FName, const struct FCurveMetaData*>& InCurves);`
- L126 _protected prototype_ `static void AddBlendProfiles(USkeleton* InSkeleton, const TMap<FName, TArray<const class UBlendProfile*>>& InBlendProfiles);`
- L127 _protected prototype_ `static void AddAnimationSlotGroups(USkeleton* InSkeleton, const TMap<FName, TSet<FName>>& InSlotGroupsNames);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SKELETALMERGING_API`
- L11 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogSkeletalMeshMerge, Log, All);`
- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSkeletalMeshMerge, Log, All);`
