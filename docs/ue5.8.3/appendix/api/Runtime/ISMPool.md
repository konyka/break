# Runtime / ISMPool

- module root: `Source/Runtime/Experimental/ISMPool`
- headers: 4; symbols: 145
- symbol kinds: class=4, enum=1, enumerator=12, function=12, macro=1, member=52, prototype=50, struct=8, typedef=5
- PublicDependencyModuleNames: Core, CoreUObject, Engine, UnrealEd

### `Source/Runtime/Experimental/ISMPool/Public/ISMPool/ISMPoolActor.h` (Public)


#### class `AISMPoolActor`  
`class AISMPoolActor : public AActor`  
_L11-26_
- reflection: `UCLASS(ConversionRoot, ComponentWrapperClass, MinimalAPI)`
- inherits: `AActor`
- L17 _private member_ `TObjectPtr<class UISMPoolComponent> ISMPoolComp;` — `UPROPERTY(Category = ISMPoolActor, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))`
- L20 _private member_ `TObjectPtr<class UISMPoolDebugDrawComponent> ISMPoolDebugDrawComp;`
- L25 _public function_ `UISMPoolComponent* GetISMPoolComp() const` — Returns ISMPoolComp subobject

### `Source/Runtime/Experimental/ISMPool/Public/ISMPool/ISMPoolComponent.h` (Public)


#### struct `FISMPoolInstanceGroups`  
`struct FISMPoolInstanceGroups`  
_L22-96_
- desc: Structure containing a set of allocated instance ranges in an FISMPoolMeshISM which is the manager for a single ISM component. The instance ranges don't change once allocated, and aren't the same as the actual render indices in the ISM. The reason that we don't store the the actual ISM render indices is that ISM component is free to reorder its instances whenever it likes.
- L24 _public typedef_ `using FInstanceGroupId = int32;`
- L40 _public function_ `void Reset()` — Reset all contents.
- L49 _public function_ `bool IsEmpty() const` — Returns true if no groups ranges are in use.
- L55 _public function_ `int32 GetMaxInstanceIndex() const` — Returns the maximum instance index that we have allocated in a group.
- L61 _public function_ `FInstanceGroupId AddGroup(int32 Count)` — Add a new group range.
- L84 _public function_ `void RemoveGroup(FInstanceGroupId GroupId)` — Remove a group range.
- L92 _public member_ `int32 TotalInstanceCount = 0;`
- L93 _public member_ `int32 TotalFreeInstanceCount = 0;`
- L94 _public member_ `TArray<FInstanceGroupRange> GroupRanges;`
- L95 _public member_ `TArray<FInstanceGroupId> FreeList;`

#### struct `FISMPoolInstanceGroups::FInstanceGroupRange`  
`struct FInstanceGroupRange`  
_L27-37_
- desc: A single continuous range associated with an FInstanceGroupId.
- L29 _public function_ `FInstanceGroupRange(int32 InStart, int32 InCount) : Start(InStart) , Count(InCount)`
- L35 _public member_ `int32 Start = 0;`
- L36 _public member_ `int32 Count = 0;`

#### struct `FISMPoolComponentDescription`  
`struct FISMPoolComponentDescription`  
_L101-145_
- desc: A description for an ISM component.
- L119 _public member_ `uint32 Flags = WorldPositionOffsetWritesVelocity|EvaluateWorldPositionOffset|AffectShadow;`
- L120 _public member_ `int32 NumCustomDataFloats = 0;`
- L121 _public member_ `FVector Position = FVector::ZeroVector;`
- L122 _public member_ `int32 StartCullDistance = 0;`
- L123 _public member_ `int32 EndCullDistance = 0;`
- L124 _public member_ `int32 MinLod = 0;`
- L125 _public member_ `int32 CustomDepthStencilValue = 0;`
- L126 _public member_ `uint32 GroupHash = 0;` — Optional, allows identical SMs to be separated into different groups for finer grained culling
- L127 _public member_ `float LodScale = 1.f;`
- L128 _public member_ `TArray<FName> Tags;`
- L129 _public member_ `FName StatsCategory;`
- L131 _public function_ `bool operator==(const FISMPoolComponentDescription& Other) const`

#### enum `FISMPoolComponentDescription::EFlags`  
`enum EFlags`  
_L103-117_
- L105 _public enumerator_ `UseHISM = 1 << 1` — HISM is no longer supported. This flag is ignored.
- L106 _public enumerator_ `GpuLodSelection = 1 << 2`
- L107 _public enumerator_ `ReverseCulling = 1 << 3`
- L108 _public enumerator_ `StaticMobility = 1 << 4`
- L109 _public enumerator_ `WorldPositionOffsetWritesVelocity = 1 << 5`
- L110 _public enumerator_ `EvaluateWorldPositionOffset = 1 << 6`
- L111 _public enumerator_ `AffectShadow = 1 << 7`
- L112 _public enumerator_ `AffectDistanceFieldLighting = 1 << 8`
- L113 _public enumerator_ `AffectDynamicIndirectLighting = 1 << 9`
- L114 _public enumerator_ `AffectFarShadow = 1 << 10`
- L115 _public enumerator_ `DistanceCullPrimitive = 1 << 11`
- L116 _public enumerator_ `UsesCustomDepthStencil = 1 << 12`

#### struct `FISMPoolStaticMeshInstance`  
`struct FISMPoolStaticMeshInstance`  
_L165-207_
- desc: A mesh with potentially overriden materials and ISM property description. We batch instances into ISMs that have equivalent values for this structure.
- L167 _public member_ `TWeakObjectPtr<UStaticMesh> StaticMesh;`
- L168 _public member_ `TArray<TWeakObjectPtr<UMaterialInterface>> MaterialsOverrides;`
- L169 _public member_ `TArray<float> CustomPrimitiveData;`
- L170 _public member_ `FISMPoolComponentDescription Desc;`
- L172 _public function_ `bool operator==(const FISMPoolStaticMeshInstance& Other) const`

#### struct `FISMPoolMeshInfo`  
`struct FISMPoolMeshInfo`  
_L226-234_
- desc: Describes a group of instances within an ISM.
- L228 _public member_ `int32 ISMIndex;`
- L229 _public member_ `FISMPoolInstanceGroups::FInstanceGroupId InstanceGroupIndex;`
- L231 _public member_ `TArray<float> CustomData;`
- L232 _public prototype_ `TArrayView<const float> CustomDataSlice(int32 InstanceIndex, int32 NumCustomDataFloatsPerInstance);`
- L233 _public prototype_ `void ShadowCopyCustomData(int32 InstanceCount, int32 NumCustomDataFloatsPerInstance, TArrayView<const float> CustomDataFloats);`

#### struct `FISMPoolMeshGroup`  
`struct FISMPoolMeshGroup`  
_L242-260_
- desc: A mesh group which is a collection of meshes and their related FISMPoolMeshInfo. We group these with a single handle with the expectation that a client will want to own multiple meshs and release them together.
- L244 _public typedef_ `using FMeshId = int32;`
- L247 _public prototype_ `FMeshId AddMesh(const FISMPoolStaticMeshInstance& MeshInstance, int32 InstanceCount, const FISMPoolMeshInfo& ISMInstanceInfo, TArrayView<const float> CustomDataFloats);` — Adds a new mesh with instance count. We expect to only add a unique mesh instance once to each group. Returns a ID that can be used to update the instances.
- L249 _public prototype_ `bool BatchUpdateInstancesTransforms(FISMPool& ISMPool, FMeshId MeshId, int32 StartInstanceIndex, TArrayView<const FTransform> NewInstancesTransforms, bool bWorldSpace, bool bMarkRenderStateDirty, bool bTeleport);` — Update instance transforms for a group of instances.
- L250 _public prototype_ `void BatchUpdateInstanceCustomData(FISMPool& ISMPool, int32 CustomFloatIndex, float CustomFloatValue);`
- L253 _public prototype_ `void RemoveAllMeshes(FISMPool& ISMPool);` — Remove all of our managed meshes and associated instances.
- L256 _public member_ `TArray<FISMPoolMeshInfo> MeshInfos;` — Array of allocated mesh infos.
- L259 _public member_ `bool bAllowPerInstanceRemoval = false;` — Flag for whether we allow removal of instances when transform scale is set to zero.

#### struct `FISMPoolISM`  
`struct FISMPoolISM`  
_L263-280_
- desc: Structure containting all info for a single ISM.
- L266 _public prototype_ `void CreateISM(USceneComponent* InOwningComponent);` — Create the ISMComponent according to settings on the mesh instance.
- L268 _public prototype_ `void InitISM(const FISMPoolStaticMeshInstance& InMeshInstance, bool bKeepAlive, bool bOverrideTransformUpdates = false);` — Initialize the ISMComponent according to settings on the mesh instance.
- L270 _public prototype_ `FISMPoolInstanceGroups::FInstanceGroupId AddInstanceGroup(int32 InstanceCount, TArrayView<const float> CustomDataFloats);` — Add a group to the ISM. Returns the group index.
- L273 _public member_ `FISMPoolStaticMeshInstance MeshInstance;` — Unique description of ISM component settings.
- L275 _public member_ `TObjectPtr<UInstancedStaticMeshComponent> ISMComponent;` — Created ISM component. Will be nullptr when this slot has been recycled to FISMPool FreeList.
- L277 _public member_ `FISMPoolInstanceGroups InstanceGroups;` — Groups of instances allocated in the ISM.
- L279 _public member_ `TArray<FPrimitiveInstanceId> InstanceIds;` — Id of Instance in ISMC

#### struct `FISMPool`  
`struct FISMPool`  
_L284-336_
- desc: A pool of ISMs.
- L286 _public typedef_ `using FISMIndex = int32;`
- L288 _public prototype_ `FISMPool();`
- L291 _public prototype_ `FISMIndex GetOrAddISM(UISMPoolComponent* OwningComponent, const FISMPoolStaticMeshInstance& MeshInstance, bool& bOutISMCreated);` — Find or add an ISM and return an ISM index handle.
- L293 _public prototype_ `void RemoveISM(FISMIndex ISMIndex, bool bKeepAlive, bool bRecycle);` — Remove an ISM.
- L295 _public prototype_ `FISMPoolMeshInfo AddInstancesToISM(UISMPoolComponent* OwningComponent, const FISMPoolStaticMeshInstance& MeshInstance, int32 InstanceCount, TArrayView<const float> CustomDataFloats);` — Add instances to ISM and return a mesh info handle.
- L297 _public prototype_ `void RemoveInstancesFromISM(const FISMPoolMeshInfo& MeshInfo);` — Remove instances from an ISM.
- L299 _public prototype_ `bool BatchUpdateInstancesTransforms(FISMPoolMeshInfo& MeshInfo, int32 StartInstanceIndex, TArrayView<const FTransform> NewInstancesTransforms, bool bWorldSpace, bool bMarkRenderStateDirty, bool bTeleport, bool bAllowPerInstanceRemoval);` — Update ISM contents.
- L300 _public prototype_ `void BatchUpdateInstanceCustomData(FISMPoolMeshInfo const& MeshInfo, int32 CustomFloatIndex, float CustomFloatValue);`
- L303 _public prototype_ `void Clear();` — Clear all ISM components and associated data.
- L306 _public prototype_ `void Tick(UISMPoolComponent* OwningComponent);` — Tick maintenance of free list and preallocation.
- L309 _public prototype_ `void RequestPreallocateMeshInstance(const FISMPoolStaticMeshInstance& MeshInstances);` — Add an ISM description to the preallocation queue.
- L311 _public prototype_ `void ProcessPreallocationRequests(UISMPoolComponent* OwningComponent, int32 MaxPreallocations);` — Process the preallocation queue. Processing is timesliced so that only some of the queue will be processed in every call.
- L313 _public prototype_ `void UpdateAbsoluteTransforms(const FTransform& BaseTransform, EUpdateTransformFlags UpdateTransformFlags, ETeleportType Teleport);`
- L315 _public prototype_ `bool RequiresTick() const;`
- L318 _public member_ `TArray<FISMPoolISM> ISMs;` — Array of ISM objects.
- L320 _public member_ `TMap<FISMPoolStaticMeshInstance, FISMIndex> MeshToISMIndex;` — Mapping from mesh description to ISMs array slot.
- L323 _public member_ `TSet<FISMPoolStaticMeshInstance> PrellocationQueue;` — Set of ISM descriptions that we would like to preallocate.
- L326 _public member_ `TArray<int32> FreeList;` — Free list of indices in ISMs that are empty.
- L328 _public member_ `TArray<int32> FreeListISM;` — Free list of indices in ISMs that have registered ISM components.
- L331 _public member_ `bool bCachedKeepAlive = false;` — Cached state of lifecycle cvars from the last Tick()
- L332 _public member_ `bool bCachedRecycle = false;`
- L335 _public member_ `bool bDisableBoundsAndTransformUpdate = false;` — Whether we force ISMs to use parent bounds and disable transform updates

#### class `UISMPoolComponent`  
`class UISMPoolComponent: public USceneComponent`  
_L344-401_
- reflection: `UCLASS(meta = (BlueprintSpawnableComponent), MinimalAPI)`
- inherits: `USceneComponent`
- desc: UISMPoolComponent. Component that manages a pool of ISM components in order to allow multiple client components that use the same meshes to the share ISMs.
- L349 _public typedef_ `using FMeshGroupId = int32;`
- L350 _public typedef_ `using FMeshId = int32;`
- L353 _public prototype_ `virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;`
- L354 _public prototype_ `virtual void GetResourceSizeEx(FResourceSizeEx& CumulativeResourceSize) override;`
- L362 _public prototype_ `FMeshGroupId CreateMeshGroup(bool bAllowPerInstanceRemoval = false);` — Create an Mesh group which represent an arbitrary set of mesh with their instance no resources are created until the meshes are added for this group return a mesh group Id used to add and update instances
- L365 _public prototype_ `void DestroyMeshGroup(FMeshGroupId MeshGroupId);` — Destroy  a mesh group and its associated resources
- L368 _public prototype_ `FMeshId AddMeshToGroup(FMeshGroupId MeshGroupId, const FISMPoolStaticMeshInstance& MeshInstance, int32 InstanceCount, TArrayView<const float> CustomDataFloats);` — Add a static mesh for a mesh group
- L371 _public prototype_ `bool BatchUpdateInstancesTransforms(FMeshGroupId MeshGroupId, FMeshId MeshId, int32 StartInstanceIndex, TArrayView<const FTransform> NewInstancesTransforms, bool bWorldSpace = false, bool bMarkRenderStateDirty = false, bool bTeleport = false);` — Update transforms for a mesh group
- L374 _public prototype_ `bool BatchUpdateInstancesTransforms(FMeshGroupId MeshGroupId, FMeshId MeshId, int32 StartInstanceIndex, const TArray<FTransform>& NewInstancesTransforms, bool bWorldSpace = false, bool bMarkRenderStateDirty = false, bool bTeleport = false);` — `UE_DEPRECATED(5.3, "BatchUpdateInstancesTransforms Array parameter version is deprecated, use the TArrayView version instead")`
- L377 _public prototype_ `bool BatchUpdateInstanceCustomData(FMeshGroupId MeshGroupId, int32 CustomFloatIndex, float CustomFloatValue);` — Update a single slot of custom instance data for all instances in a mesh group
- L383 _public prototype_ `void PreallocateMeshInstance(const FISMPoolStaticMeshInstance& MeshInstance);` — Preallocate an ISM in the pool. Doing this early for known mesh instance descriptions can reduce the component registration cost of AddMeshToGroup() for newly discovered mesh descriptions.
- L385 _public prototype_ `void SetTickablePoolManagement(bool bEnablePoolManagement);`
- L387 _public prototype_ `void SetOverrideTransformUpdates(bool bOverrideUpdates);`
- L389 _public prototype_ `void UpdateAbsoluteTransforms(const FTransform& BaseTransform, EUpdateTransformFlags UpdateTransformFlags, ETeleportType Teleport);`
- L391 _public prototype_ `void EnableComponentTickIfPoolManagementEnabled();`
- L394 _private member_ `uint32 NextMeshGroupId = 0;`
- L395 _private member_ `TMap<FMeshGroupId, FISMPoolMeshGroup> MeshGroups;`
- L396 _private member_ `FISMPool Pool;`
- L397 _private member_ `bool bIsPoolManagementEnabled = true;`

#### Free symbols / members of external scopes

- L147 _function_ `inline uint32 GetTypeHash(const FISMPoolComponentDescription& Desc)`
- L209 _function_ `inline uint32 GetTypeHash(const FISMPoolStaticMeshInstance& MeshInstance)`

### `Source/Runtime/Experimental/ISMPool/Public/ISMPool/ISMPoolDebugDrawComponent.h` (Public)


#### class `UISMPoolDebugDrawComponent`  
`class UISMPoolDebugDrawComponent : public UDebugDrawComponent`  
_L15-57_
- reflection: `UCLASS(MinimalAPI, ClassGroup = Debug)`
- inherits: `UDebugDrawComponent`
- L20 _private member_ `bool bShowGlobalStats = false;` — `UPROPERTY(EditAnywhere, Category = Debug)`
- L23 _private member_ `bool bShowStats = false;` — `UPROPERTY(EditAnywhere, Category = Debug)`
- L26 _private member_ `bool bShowBounds = false;` — `UPROPERTY(EditAnywhere, Category = Debug)`
- L29 _private member_ `TObjectPtr<const UInstancedStaticMeshComponent> SelectedComponent;` — `UPROPERTY(Transient)`
- L31 _private member_ `float SelectTimer = 0.f;`
- L34 _protected prototype_ `virtual void BeginPlay() override;`
- L35 _protected prototype_ `virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;`
- L36 _protected prototype_ `virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;`
- L37 _protected prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;`
- L40 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L43 _protected prototype_ `void UpdateTickEnabled();`
- L46 _protected prototype_ `virtual FDebugRenderSceneProxy* CreateDebugSceneProxy() override;`
- L48 _protected member_ `FDebugDrawDelegateHelper DebugDrawDelegateHelper;`
- L49 _protected function_ `virtual FDebugDrawDelegateHelper& GetDebugDrawDelegateHelper() override`
- L51 _protected member_ `FDelegateHandle OnScreenMessagesHandle;`
- L52 _protected prototype_ `void GetOnScreenMessages(TMultiMap<FCoreDelegates::EOnScreenMessageSeverity, FText>& OutMessages);`
- L56 _public prototype_ `static void UpdateAllTickEnabled();`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API ISMPOOL_API`

### `Source/Runtime/Experimental/ISMPool/Public/ISMPool/ISMPoolSubSystem.h` (Public)


#### class `UISMPoolSubSystem`  
`class UISMPoolSubSystem : public UWorldSubsystem`  
_L14-38_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWorldSubsystem`
- desc: A subsystem managing ISMPool actors.
- L19 _public prototype_ `UISMPoolSubSystem();`
- L22 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;` — USubsystem BEGIN
- L23 _public prototype_ `virtual void Deinitialize() override;`
- L27 _public prototype_ `AISMPoolActor* FindISMPoolActor(ULevel* Level);` — Finds or creates an actor.
- L30 _public prototype_ `void GetISMPoolActors(TArray<AISMPoolActor*>& OutActors) const;` — Get all actors managed by the subsystem.
- L34 _protected prototype_ `void OnActorEndPlay(AActor* InSource, EEndPlayReason::Type Reason);` — `UFUNCTION()`
- L37 _protected member_ `TMap<TObjectPtr<ULevel>, TObjectPtr<AISMPoolActor> > PerLevelISMPoolActors;` — ISMPool are per level
