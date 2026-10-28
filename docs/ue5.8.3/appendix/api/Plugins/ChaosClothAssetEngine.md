# Plugins / ChaosClothAssetEngine

- module root: `Plugins/ChaosClothAsset/Source/ChaosClothAssetEngine`
- headers: 22; symbols: 906
- symbol kinds: class=20, delegate=3, enum=6, enumerator=20, externvar=1, function=166, macro=9, member=184, namespace=46, prototype=434, struct=15, typedef=1, variable=1
- PrivateDependencyModuleNames: ChaosCaching, ChaosCloth, ChaosClothAsset, Cloth Sim, ClothingSystemRuntimeInterface, Core, CoreUObject, Engine, PropertyEditor, RHI, RenderCore, Slate, StructUtilsEditor
- PrivateIncludePathModuleNames: DerivedDataCache
- PublicDependencyModuleNames: ClothingSystemRuntimeCommon, DataflowCore, DataflowEngine, DataflowSimulation

### `Plugins/ChaosClothAsset/Source/ChaosClothAssetEngine/Private/ChaosClothAsset/ClothAssetBuilder.h` (Private)


#### struct `UChaosClothAsset::FBuilder`  
`struct UChaosClothAsset::FBuilder`  
_L12-16_
- desc: Builder utility struct, nested struct of UChaosClothAsset.
- L15 _public prototype_ `static void BuildLod(FSkeletalMeshLODModel& LODModel, const UChaosClothAsset& ClothAsset, int32 LodIndex, const ITargetPlatform* TargetPlatform);` — Build a FSkeletalMeshLODModel out of the cloth asset for the specified LOD index and specified platform.

### `Plugins/ChaosClothAsset/Source/ChaosClothAssetEngine/Private/ChaosClothAsset/ClothAssetInteractorDataAsset.h` (Private)


#### struct `FClothAssetInteractorPropertyBag`  
`struct FClothAssetInteractorPropertyBag : public FInstancedPropertyBag`  
_L13-16_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FInstancedPropertyBag`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FClothAssetInteractorPropertyBag> : public TStructOpsTypeTraits<FInstancedPropertyBag>`  
_L19-21_
- inherits: `TStructOpsTypeTraits<FInstancedPropertyBag>`

#### class `UClothAssetInteractorDataAsset`  
`class UClothAssetInteractorDataAsset : public UDataAsset`  
_L27-61_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UDataAsset`
- desc: Data asset for setting groups of properties on the Chaos Cloth Asset Interactor.
- L35 _public function_ `const FClothAssetInteractorPropertyBag& GetPropertySet(const FName SetName) const` — `UFUNCTION(BlueprintCallable, Category = ClothProperty)` — Get the Property Set for a given Set Name. If Set Name does not exist, the Default Properties will be returned.
- L46 _public prototype_ `void SynchronizePropertySets();` — `UFUNCTION(CallInEditor, Category = "Interactor Properties", meta = (DisplayPriority = 2))` — Synchronize the Property Sets with the Default Properties by adding/removing properties. Existing property values will not be modified.
- L49 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L56 _private member_ `FClothAssetInteractorPropertyBag DefaultProperties;` — `UPROPERTY(EditAnywhere, Category = "Interactor Properties")` — Default Property schema and default values. Property Names should match the Interactor Name to set using the Cloth Asset Interactor. Only property types known to the interactor (float, double, int, string, Vector, Vector2D) will be used to set values.
- L60 _private member_ `TMap<FName, FClothAssetInteractorPropertyBag> PropertySets;` — `UPROPERTY(EditAnywhere, Category = "Interactor Properties", Meta = (FixedLayout))` — Property sets with matching schema to Default Properties.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CHAOSCLOTHASSETENGINE_API`

### `Plugins/ChaosClothAsset/Source/ChaosClothAssetEngine/Private/ChaosClothAsset/ClothAssetPrivate.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogChaosClothAsset, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogChaosClothAsset, Log, All);`
- L9 _delegate_ `DECLARE_STATS_GROUP(TEXT("ChaosClothAsset"), STATGROUP_ChaosClothAsset, STA`

### `Plugins/ChaosClothAsset/Source/ChaosClothAssetEngine/Private/ChaosClothAsset/ClothAssetSKMClothingSimulationInteractor.h` (Private)


#### class `UChaosClothAssetSKMClothingInteractor`  
`class UChaosClothAssetSKMClothingInteractor final : public UClothingInteractor`  
_L16-27_
- reflection: `UCLASS(Transient, NotBlueprintType, Hidden, HideDropdown, MinimalAPI)`
- inherits: `UClothingInteractor`
- desc: Dummy interactor not exposed to Blueprint used during initializations, until the correct clothing interactor is known from the simualtion.
- L23 _private prototype_ `void Initialize(const UChaosClothAssetSKMClothingAsset* InClothingAsset, int32 InClothingId);`
- L26 _private member_ `TObjectPtr<const UChaosClothAssetSKMClothingAsset> ClothingAsset;` — `UPROPERTY()`

#### class `UChaosClothAssetSKMClothingSimulationInteractor`  
`class UChaosClothAssetSKMClothingSimulationInteractor final : public UClothingSimulationInteractor`  
_L31-54_
- reflection: `UCLASS(Transient, BlueprintType, MinimalAPI)`
- inherits: `UClothingSimulationInteractor`
- desc: Simulation interactor for Cloth Assets running through a Skeletal Mesh simulation.
- L36 _private prototype_ `DECLARE_DELEGATE_OneParam(FCommand, UE::Chaos::ClothAsset::FSKMClothingSimulation*)`
- L40 _private prototype_ `virtual void Sync(IClothingSimulationInterface* InSimulation, const IClothingSimulationContext* InContext) override;`
- L42 _private prototype_ `virtual void PhysicsAssetUpdated() override;`
- L43 _private prototype_ `virtual void ClothConfigUpdated() override;`
- L44 _private prototype_ `virtual void SetAnimDriveSpringStiffness(float InStiffness) override;`
- L45 _private prototype_ `virtual void EnableGravityOverride(const FVector& InVector) override;`
- L46 _private prototype_ `virtual void DisableGravityOverride() override;`
- L48 _private prototype_ `virtual void SetNumIterations(int32 NumIterations) override;`
- L49 _private prototype_ `virtual void SetMaxNumIterations(int32 MaxNumIterations) override;`
- L50 _private prototype_ `virtual void SetNumSubsteps(int32 NumSubsteps) override;`
- L53 _private member_ `TArray<FCommand> Commands;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Chaos` (scope `UE`)
- L8 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)
- L36 _delegate_ `DECLARE_DELEGATE_OneParam(FCommand, UE::Chaos::ClothAsset::FSKMClothingSimulation*)`

### `Plugins/ChaosClothAsset/Source/ChaosClothAssetEngine/Private/ChaosClothAsset/ClothComponentCacheAdapter.h` (Private)


#### class `UE::Chaos::ClothAsset::FClothComponentCacheAdapter`  
`class FClothComponentCacheAdapter : public ::Chaos::FComponentCacheAdapter`  
_L20-53_
- inherits: `::Chaos::FComponentCacheAdapter`
- desc: Skeletal mesh cache adapter to be able to cache cloth simulation datas through the chaos cache system
- L24 _public prototype_ `virtual ~FClothComponentCacheAdapter() = default;`
- L27 _public prototype_ `virtual SupportType SupportsComponentClass(UClass* InComponentClass) const override;`
- L28 _public prototype_ `virtual UClass* GetDesiredClass() const override;`
- L29 _public prototype_ `virtual uint8 GetPriority() const override;`
- L30 _public prototype_ `virtual FGuid GetGuid() const override;`
- L31 _public prototype_ `virtual bool ValidForPlayback(UPrimitiveComponent* InComponent, UChaosCache* InCache) const override;`
- L32 _public prototype_ `virtual ::Chaos::FPhysicsSolver* GetComponentSolver(UPrimitiveComponent* InComponent) const override;`
- L33 _public prototype_ `virtual ::Chaos::FPhysicsSolverEvents* BuildEventsSolver(UPrimitiveComponent* InComponent) const override;`
- L34 _public prototype_ `virtual void SetRestState(UPrimitiveComponent* InComponent, UChaosCache* InCache, const FTransform& InRootTransform, ::Chaos::FReal InTime) const override;`
- L35 _public prototype_ `virtual bool InitializeForRecord(UPrimitiveComponent* InComponent, UChaosCache* InCache) override;`
- L36 _public prototype_ `virtual bool InitializeForPlayback(UPrimitiveComponent* InComponent, UChaosCache* InCache, float InTime) override;`
- L37 _public prototype_ `virtual void Record_PostSolve(UPrimitiveComponent* InComp, const FTransform& InRootTransform, FPendingFrameWrite& OutFrame, ::Chaos::FReal InTime) const override;`
- L38 _public prototype_ `virtual void Playback_PreSolve(UPrimitiveComponent* InComponent, UChaosCache* InCache, ::Chaos::FReal InTime, FPlaybackTickRecord& TickRecord, TArray<::Chaos::TPBDRigidParticleHandle<::Chaos::FReal, 3>*>& OutUpdatedRigids) const override;`
- L43 _public prototype_ `virtual void WaitForSolverTasks(UPrimitiveComponent* InComponent) const override;`
- L49 _private prototype_ `UChaosClothComponent* GetClothComponent(UPrimitiveComponent* InComponent) const;` — Return the cloth component.
- L51 _private prototype_ `FClothSimulationProxy* GetProxy(UPrimitiveComponent* InComponent) const;`
- L52 _private prototype_ `::Chaos::FClothingSimulationSolver* GetClothSolver(UPrimitiveComponent* InComponent) const;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Chaos`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Chaos` (scope `UE`)
- L13 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)

### `Plugins/ChaosClothAsset/Source/ChaosClothAssetEngine/Private/ChaosClothAsset/ClothComponentInstanceData.h` (Private)


#### struct `FChaosClothComponentInstanceData`  
`struct FChaosClothComponentInstanceData : public FSceneComponentInstanceData`  
_L16-31_
- reflection: `USTRUCT()`
- inherits: `FSceneComponentInstanceData`
- desc: Saves internal cloth component (transient) state that would otherwise be lost. Useful for when Blueprint construction scripts rerun for Blueprint-created components.
- L20 _public prototype_ `FChaosClothComponentInstanceData() = default;`
- L21 _public prototype_ `explicit FChaosClothComponentInstanceData(const UChaosClothComponent* SourceComponent);`
- L23 _public prototype_ `virtual bool ContainsData() const override;`
- L24 _public prototype_ `virtual void ApplyToComponent(UActorComponent* Component, const ECacheApplyPhase CacheApplyPhase) override;`
- L28 _private member_ `TObjectPtr<UChaosClothAssetBase> Asset;` — `UPROPERTY()`
- L29 _private member_ `uint8 bSimulateInEditor : 1;`
- L30 _private member_ `uint8 bHasOverrides : 1;`

### `Plugins/ChaosClothAsset/Source/ChaosClothAssetEngine/Private/ChaosClothAsset/ClothSimulationAccessoryMesh.h` (Private)


#### class `UE::Chaos::ClothAsset::FClothSimulationAccessoryMesh`  
`class FClothSimulationAccessoryMesh : public ::Chaos::FClothingSimulationAccessoryMesh`  
_L12-52_
- inherits: `::Chaos::FClothingSimulationAccessoryMesh`
- desc: Accessory mesh used as an input to a simulation. They are expected to share topology (e.g., Indices, PatternIndices) with their associated FClothingSimulationMesh
- L15 _public prototype_ `FClothSimulationAccessoryMesh(const TSharedRef<FCollectionClothConstFacade>& InClothFacade, const ::Chaos::FClothingSimulationMesh& InMesh, const int32 InAccessoryMeshIndex);`
- L17 _public prototype_ `virtual ~FClothSimulationAccessoryMesh();`
- L20 _public prototype_ `virtual int32 GetNumPoints() const override;` — Return the number of points.
- L23 _public function_ `virtual int32 GetNumPatternPoints() const override` — Return the number of pattern points (2d, unwelded).
- L29 _public prototype_ `virtual TConstArrayView<FVector3f> GetPositions() const override;` — Return the source mesh positions (pre-skinning).
- L32 _public function_ `virtual TConstArrayView<FVector2f> GetPatternPositions() const override` — Return the source mesh 2d pattern positions.
- L38 _public prototype_ `virtual TConstArrayView<FVector3f> GetNormals() const override;` — Return the source mesh normals (pre-skinning).
- L41 _public function_ `virtual TConstArrayView<FClothVertBoneData> GetBoneData() const override` — Return the bone data containing bone weights and influences.
- L48 _private prototype_ `void SetBoneData();`
- L50 _private member_ `const FCollectionClothSimAccessoryMeshConstFacade AccessoryMeshFacade;`
- L51 _private member_ `TArray<FClothVertBoneData> BoneData;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Chaos` (scope `UE`)
- L7 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)

### `Plugins/ChaosClothAsset/Source/ChaosClothAssetEngine/Private/ChaosClothAsset/ClothSimulationContext.h` (Private)


#### struct `UE::Chaos::ClothAsset::FClothSimulationContext`  
`struct FClothSimulationContext`  
_L19-66_
- desc: Cloth simulation context. Class used to pass data between the cloth component and its simulation proxy. The context is set in the game thread before the simulation is started and should not be modified until the simulation is ended.
- L22 _public member_ `float DeltaTime;` — Time step in seconds.
- L25 _public member_ `int32 LodIndex;` — Current LOD index at the start of the simulation.
- L28 _public member_ `FTransform ComponentTransform;` — Component to world transform.
- L31 _public member_ `float SolverGeometryScale;` — Scale applied to solver.
- L34 _public member_ `TArray<FTransform> BoneTransforms;` — Component space bone transforms of the owning component.
- L37 _public member_ `TArray<FMatrix44f> RefToLocalMatrices;` — Bone matrices used for skinning.
- L40 _public member_ `bool bTeleport = false;` — Teleport.
- L43 _public member_ `bool bReset = false;` — Reset.
- L46 _public member_ `bool bResetRestLengthsWithMorphTarget = false;` — Reset RestLengths (with morph target)
- L47 _public member_ `FString ResetRestLengthsMorphTargetName;`
- L50 _public member_ `float VelocityScale;` — Velocity scale to compensate for time differences when the MaxPhysicsDeltaTime kicks in.
- L53 _public member_ `FVector WorldGravity;` — Gravity extracted from the world.
- L56 _public member_ `FVector WindVelocity;` — Wind velocity at the component location.
- L59 _public member_ `FClothingSimulationCacheData CacheData;` — Data used by Chaos Cache
- L62 _public prototype_ `void Fill(const IClothComponentAdapter& ClothComponentAdapter, float InDeltaTime, float MaxDeltaTime, bool bIsInitialization = false, FClothingSimulationCacheData* CacheData = nullptr);` — Fill the context from data collected from the specified component.
- L65 _private member_ `TArray<uint16> RequiredExtraBones;` — Avoids reallocations while calculating RefToLocalMatrices

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Chaos` (scope `UE`)
- L9 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)

### `Plugins/ChaosClothAsset/Source/ChaosClothAssetEngine/Private/ChaosClothAsset/ClothSimulationMesh.h` (Private)


#### class `UE::Chaos::ClothAsset::FClothSimulationMesh`  
`class FClothSimulationMesh : public ::Chaos::FClothingSimulationMesh`  
_L15-77_
- inherits: `::Chaos::FClothingSimulationMesh`
- L18 _public prototype_ `FClothSimulationMesh( const FChaosClothSimulationModel& InClothSimulationModel, const FClothSimulationContext& InClothSimulationContext, const TArray<TSharedRef<const FManagedArrayCollection>>& InManagedArrayCollections, const FString& DebugName);`
- L24 _public prototype_ `virtual ~FClothSimulationMesh() override = default;`
- L26 _public prototype_ `FClothSimulationMesh(const FClothSimulationMesh&) = delete;`
- L27 _public prototype_ `FClothSimulationMesh(FClothSimulationMesh&&) = delete;`
- L28 _public prototype_ `FClothSimulationMesh& operator=(const FClothSimulationMesh&) = delete;`
- L29 _public prototype_ `FClothSimulationMesh& operator=(FClothSimulationMesh&&) = delete;`
- L32 _public prototype_ `virtual int32 GetNumLODs() const override;`
- L33 _public prototype_ `virtual int32 GetLODIndex() const override;`
- L34 _public prototype_ `virtual int32 GetOwnerLODIndex(int32 LODIndex) const override;`
- L35 _public prototype_ `virtual bool IsValidLODIndex(int32 LODIndex) const override;`
- L36 _public prototype_ `virtual int32 GetNumPoints(int32 LODIndex) const override;`
- L37 _public prototype_ `virtual int32 GetNumPatternPoints(int32 LODIndex) const override;`
- L38 _public prototype_ `virtual TConstArrayView<FVector3f> GetPositions(int32 LODIndex) const override;`
- L39 _public prototype_ `virtual TConstArrayView<FVector2f> GetPatternPositions(int32 LODIndex) const override;`
- L40 _public prototype_ `virtual TConstArrayView<FVector3f> GetNormals(int32 LODIndex) const override;`
- L41 _public prototype_ `virtual TConstArrayView<uint32> GetIndices(int32 LODIndex) const override;`
- L42 _public prototype_ `virtual TConstArrayView<uint32> GetPatternIndices(int32 LODIndex) const override;`
- L43 _public prototype_ `virtual TConstArrayView<uint32> GetPatternToWeldedIndices(int32 LODIndex) const override;`
- L44 _public prototype_ `virtual TArray<FName> GetWeightMapNames(int32 LODIndex) const override;`
- L45 _public prototype_ `virtual TMap<FString, int32> GetWeightMapIndices(int32 LODIndex) const override;`
- L46 _public prototype_ `virtual TArray<TConstArrayView<::Chaos::FRealSingle>> GetWeightMaps(int32 LODIndex) const override;`
- L47 _public prototype_ `virtual TMap<FString, const TSet<int32>*> GetVertexSets(int32 LODIndex) const override;`
- L48 _public prototype_ `virtual TMap<FString, const TSet<int32>*> GetFaceSets(int32 LODIndex) const override;`
- L49 _public prototype_ `virtual TMap<FString, TConstArrayView<int32>> GetFaceIntMaps(int32 LODIndex) const override;`
- L51 _public prototype_ `virtual TArray<TConstArrayView<TTuple<int32, int32, float>>> GetTethers(int32 LODIndex, bool ) const override;` — Note: there is only one set of tethers stored on ClothSimulationMesh assets
- L52 _public prototype_ `virtual int32 GetReferenceBoneIndex() const override;`
- L53 _public prototype_ `virtual FTransform GetReferenceBoneTransform() const override;`
- L54 _public prototype_ `virtual const TArray<FTransform>& GetBoneTransforms() const override;`
- L55 _public prototype_ `virtual const FTransform& GetComponentToWorldTransform() const override;`
- L56 _public prototype_ `virtual const TArray<FMatrix44f>& GetRefToLocalMatrices() const override;`
- L57 _public prototype_ `virtual TConstArrayView<int32> GetBoneMap() const override;`
- L58 _public prototype_ `virtual TConstArrayView<FClothVertBoneData> GetBoneData(int32 LODIndex) const override;`
- L59 _public prototype_ `virtual TConstArrayView<FMeshToMeshVertData> GetTransitionUpSkinData(int32 LODIndex) const override;`
- L60 _public prototype_ `virtual TConstArrayView<FMeshToMeshVertData> GetTransitionDownSkinData(int32 LODIndex) const override;`
- L61 _public prototype_ `virtual TSharedPtr<const FManagedArrayCollection> GetManagedArrayCollection(int32 LODIndex) const override;`
- L62 _public prototype_ `virtual int32 FindMorphTargetByName(int32 LODIndex, const FString& Name) const override;`
- L63 _public prototype_ `virtual TConstArrayView<FString> GetAllMorphTargetNames(int32 LODIndex) const override;`
- L64 _public prototype_ `virtual TConstArrayView<FVector3f> GetMorphTargetPositionDeltas(int32 LODIndex, int32 MorphTargetIndex) const override;`
- L65 _public prototype_ `virtual TConstArrayView<FVector3f> GetMorphTargetTangentZDeltas(int32 LODIndex, int32 MorphTargetIndex) const override;`
- L66 _public prototype_ `virtual TConstArrayView<int32> GetMorphTargetIndices(int32 LODIndex, int32 MorphTargetIndex) const override;`
- L67 _public prototype_ `virtual TConstArrayView<FName> GetAllAccessoryMeshNames(int32 LODIndex) const override;`
- L68 _public prototype_ `virtual const ::Chaos::FClothingSimulationAccessoryMesh* GetAccessoryMesh(int32 LODIndex, const FName& AccessoryMeshName) const override;`
- L72 _private member_ `const FChaosClothSimulationModel& ClothSimulationModel;`
- L73 _private member_ `const FClothSimulationContext& ClothSimulationContext;`
- L74 _private member_ `const TArray<TSharedRef<const FManagedArrayCollection>>& ManagedArrayCollections;`
- L75 _private member_ `TArray<TSharedRef<FCollectionClothConstFacade>> ClothFacades;`
- L76 _private member_ `TArray<TMap<FName,TUniquePtr<FClothSimulationAccessoryMesh>>> AccessoryMeshes;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Chaos` (scope `UE`)
- L9 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)

### `Plugins/ChaosClothAsset/Source/ChaosClothAssetEngine/Private/ChaosClothAsset/CollisionSources.h` (Private)


#### class `UE::Chaos::ClothAsset::FCollisionSources`  
`class FCollisionSources final`  
_L17-82_
- desc: Cloth collision source container.
- L20 _public prototype_ `explicit FCollisionSources(USkinnedMeshComponent* InOwnerComponent = nullptr, bool bInCollideWithEnvironment = false);`
- L21 _public prototype_ `~FCollisionSources();`
- L23 _public prototype_ `void Add(USkinnedMeshComponent* SourceComponent, const UPhysicsAsset* SourcePhysicsAsset, bool bUseSphylsOnly = false);`
- L25 _public prototype_ `void Remove(const USkinnedMeshComponent* SourceComponent);`
- L27 _public prototype_ `void Remove(const USkinnedMeshComponent* SourceComponent, const UPhysicsAsset* SourcePhysicsAsset);`
- L29 _public prototype_ `void AddExternalCollisions(const FClothCollisionData& InExternalCollisions);`
- L31 _public prototype_ `void ClearExternalCollisions();`
- L33 _public prototype_ `void Reset();`
- L35 _public prototype_ `void SetOwnerComponent(USkinnedMeshComponent* InOwnerComponent);`
- L37 _public function_ `USkinnedMeshComponent* GetOwnerComponent() const`
- L42 _public function_ `void SetCollideWithEnvironment(bool bCollide)`
- L70 _private prototype_ `void ExtractSkinnedMeshCollisionData(FClothCollisionData& CollisionData);`
- L71 _private prototype_ `void ExtractEnvironmentalCollisionData(FClothCollisionData& CollisionData);`
- L72 _private prototype_ `void ExtractExternalCollisionData(FClothCollisionData& CollisionData);`
- L73 _private prototype_ `bool IsCollisionDataUpToDate(int32 InVersion) const;`
- L74 _private prototype_ `void MarkCollisionDataUpToDate(int32 InVersion);`
- L75 _private prototype_ `void ResolveWeakComponentPtrs();`
- L77 _private member_ `TWeakObjectPtr<USkinnedMeshComponent> OwnerComponent;`
- L78 _private member_ `TArray<FCollisionSource> CollisionSources;`
- L79 _private member_ `FClothCollisionData ExternalCollisions;`
- L80 _private member_ `int32 Version = INDEX_NONE;`
- L81 _private member_ `bool bCollideWithEnvironment = false;`

#### struct `UE::Chaos::ClothAsset::FCollisionSources::FCollisionSource`  
`struct FCollisionSource`  
_L50-68_
- L52 _public member_ `const TWeakObjectPtr<USkinnedMeshComponent> SourceComponent;`
- L54 _public member_ `const USkinnedMeshComponent* ResolvedSourceComponent = nullptr;` — Resolved copy of SourceComponent, refreshed prior to each update to avoid multiple TWeakObjectPtr resolves
- L55 _public member_ `const TWeakObjectPtr<const UPhysicsAsset> SourcePhysicsAsset;`
- L56 _public member_ `TWeakObjectPtr<const USkinnedAsset> CachedSkinnedAsset;`
- L57 _public member_ `FClothCollisionData CachedCollisionData;`
- L58 _public member_ `TArray<int32> CachedUsedBoneIndices;`
- L59 _public member_ `uint32 BoneTransformRevisionNumber = 0;`
- L60 _public member_ `bool bUseSphylsOnly = false;`
- L62 _public prototype_ `FCollisionSource( USkinnedMeshComponent* InSourceComponent, const UPhysicsAsset* InSourcePhysicsAsset, bool bInUseSphylsOnly);`
- L67 _public prototype_ `void ExtractCollisionData(const USkinnedMeshComponent& InOwnerComponent, FClothCollisionData& CollisionData);`

#### class `UE::Chaos::ClothAsset::FCollisionSourcesProxy`  
`class FCollisionSourcesProxy final`  
_L89-106_
- desc: Use a proxy object to extract collision data from the collision sources. The proxy allows for a different ownership than of the CollisionSources' owning component, permitting the collision data to remains with the simulation proxy even after the simulation proxy has been replaced.
- L92 _public function_ `explicit FCollisionSourcesProxy(FCollisionSources& InCollisionSources) : CollisionSources(InCollisionSources)`
- L94 _public function_ `const FClothCollisionData& GetCollisionData() const`
- L96 _public prototype_ `void ExtractCollisionData();`
- L99 _protected member_ `FCollisionSources& CollisionSources;`
- L100 _protected member_ `FClothCollisionData SkinnedMeshCollisionData;`
- L101 _protected member_ `FClothCollisionData EnvironmentalCollisionData;`
- L102 _protected member_ `FClothCollisionData ExternalCollisionData;`
- L104 _protected member_ `FClothCollisionData CollisionData;`
- L105 _protected member_ `int32 Version = INDEX_NONE;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Chaos` (scope `UE`)
- L12 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)

### `Plugins/ChaosClothAsset/Source/ChaosClothAssetEngine/Public/ChaosClothAsset/ClothAsset.h` (Public)


#### enum `EClothAssetAsyncProperties`  
`enum class EClothAssetAsyncProperties : uint64`  
_L25-34_
- reflection: `UENUM()`
- L27 _public enumerator_ `None = 0`
- L28 _public enumerator_ `RenderData UE_DEPRECATED(5.6, "Use EChaosClothAssetBaseAsyncProperties::RenderData instead.") = 1 << 0`
- L29 _public enumerator_ `ThumbnailInfo = 1 << 1`
- L30 _public enumerator_ `ImportedModel = 1 << 2`
- L31 _public enumerator_ `ClothCollection = 1 << 3`
- L32 _public enumerator_ `RefSkeleton UE_DEPRECATED(5.6, "Use EChaosClothAssetBaseAsyncProperties::RefSkeleton instead.") = 1 << 4`
- L33 _public enumerator_ `All = MAX_uint32` — Max is uint32 as we need some space for the UChaosClothAssetBase ones

#### class `UChaosClothAsset`  
`class UChaosClothAsset : public UChaosClothAssetBase`  
_L41-280_
- reflection: `UCLASS(MinimalAPI, hidecategories = Object, BlueprintType, PrioritizeCategories = ("Dataflow"))`
- inherits: `UChaosClothAssetBase`
- desc: Cloth asset for pattern based simulation.
- L45 _public prototype_ `UChaosClothAsset(const FObjectInitializer& ObjectInitializer);`
- L46 _public prototype_ `UChaosClothAsset(FVTableHelper& Helper);` — This is declared so we can use TUniquePtr<FClothSimulationModel> with just a forward declare of that class
- L50 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L51 _public prototype_ `virtual void PostLoad() override;`
- L53 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L58 _public function_ `virtual UPhysicsAsset* GetPhysicsAsset() const`
- L59 _public function_ `virtual USkeleton* GetSkeleton() override` — Note: The USkeleton isn't a reliable source of reference skeleton
- L60 _public function_ `virtual const USkeleton* GetSkeleton() const override`
- L61 _public function_ `virtual void SetSkeleton(USkeleton* InSkeleton) override`
- L65 _public prototype_ `virtual void BuildLODModel(FSkeletalMeshRenderData& RenderData, const ITargetPlatform* TargetPlatform, int32 LODIndex) override;` — Build a LOD model for the targeted platform.
- L66 _public prototype_ `virtual FString BuildDerivedDataKey(const ITargetPlatform* TargetPlatform) override;`
- L67 _public function_ `virtual const TCHAR* GetDerivedDataPrefix() const override`
- L71 _public prototype_ `virtual const TCHAR* GetDerivedDataVersion() const override;`
- L72 _public prototype_ `virtual void PrepareMeshModel() override;`
- L75 _public function_ `virtual FSkeletalMeshModel* GetImportedModel() const override`
- L84 _public function_ `TArray<TSharedRef<const FManagedArrayCollection>>& GetClothCollections()` — `UE_DEPRECATED(5.7, "Use SetClothCollections() or GetClothCollectionsInternal() instead.")`
- L90 _public function_ `const TArray<TSharedRef<const FManagedArrayCollection>>& GetClothCollections() const` — Return the enclosed Cloth Collections.
- L103 _public prototype_ `void SetClothCollections(TArray<TSharedRef<const FManagedArrayCollection>>&& InClothCollections, bool bReregisterComponents = false);` — Set new Cloth Collections for this Cloth Asset. @param InClothCollections The source managed array collections to set to the asset. @param bReregisterComponents Whether to reregister all components using this asset. This is the safe way to hard reset all simulations.
- L112 _public prototype_ `void Build( const TArray<TSharedRef<const FManagedArrayCollection>>& InClothCollections, TArray<FChaosClothAssetLodTransitionDataCache>* InOutTransitionCache = nullptr, FText* ErrorText = nullptr, FText* VerboseText = nullptr);` — Rebuild this asset from the specified managed array collection data. @param InClothCollections The source managed array collections to build/rebuild the asset with. @param InOutTransitionCache The LOD transition cache to speed up the build process, if available. @param ErrorText The headline error text if any error occurs, an empty text otherwise. @param VerboseText The verbose description of the error if any.
- L119 _public prototype_ `void Build(TArray<FChaosClothAssetLodTransitionDataCache>* InOutTransitionCache = nullptr);` — `UE_DEPRECATED(5.6, "Will be made private. Use Build with cloth collections instead.")`
- L127 _public prototype_ `void CopySimMeshToRenderMesh(UMaterialInterface* Material = nullptr);` — `UE_DEPRECATED(5.6, "Use FClothGeometryTools:CopySimMeshToRenderMesh on the cloth collections instead.")` — Copy the draped simulation mesh patterns into the render mesh data. This is useful to visualize the simulation mesh, or when the simulation mesh can be used for both simulation and rendering. @param Material The material used to render. If none is specified the default debug cloth material will be used.
- L130 _public prototype_ `void SetPhysicsAsset(UPhysicsAsset* InPhysicsAsset);` — Set the physics asset for this cloth.
- L133 _public prototype_ `void UpdateSkeletonFromCollection(bool bRebuildModels);` — `UE_DEPRECATED(5.6, "Will be made private. Use Build with cloth collections instead.")`
- L136 _public prototype_ `void SetReferenceSkeleton(const FReferenceSkeleton* ReferenceSkeleton, bool bRebuildModels, bool bRebindMeshes);` — `UE_DEPRECATED(5.6, "SetReferenceSkeleton is deprecated. Skeletons must only been set through the cloth collections.")`
- L139 _public function_ `static void OnLodStrippingQualityLevelChanged(IConsoleVariable* )` — `UE_DEPRECATED(5.6, "No longer used.")`
- L146 _public function_ `void SetDataflowTerminal(const FString& InDataflowTerminal)` — `UE_DEPRECATED(5.6, "Function will be removed as the DataflowTerminal shouldn't be set by name/string.")` — Set the name of the Dataflow terminal node for this cloth asset. @param InDataflowTerminal The new name of the Dataflow terminal node.
- L155 _public function_ `FString GetDataflowTerminal() const` — `UE_DEPRECATED(5.6, "Use GetDataflowInstance() instead")` — Return the Dataflow graph asset associated to this cloth asset if any.
- L164 _public function_ `virtual TSharedPtr<const FChaosClothSimulationModel> GetClothSimulationModel(int32 = 0) const override` — Return the cloth simulation ready LOD model data.
- L168 _public prototype_ `virtual bool HasValidClothSimulationModels() const override;`
- L169 _public function_ `virtual int32 GetNumClothSimulationModels() const override`
- L173 _public function_ `virtual FName GetClothSimulationModelName(int32 ) const override`
- L177 _public function_ `virtual const TArray<TSharedRef<const FManagedArrayCollection>>& GetCollections(int32 ) const override`
- L181 _public function_ `virtual const UPhysicsAsset* GetPhysicsAssetForModel(int32 ) const override`
- L187 _public prototype_ `virtual void CacheDerivedData(FSkinnedAssetCompilationContext* Context) override;` — Load render data from DDC if the data is cached, otherwise generate render data and save into DDC
- L188 _public prototype_ `virtual UChaosClothAssetBase* CreatePreviewAssetCopy(UObject* Outer, EObjectFlags Flags) const override;`
- L191 _public function_ `virtual void SetReferenceSkeleton(const FReferenceSkeleton* ReferenceSkeleton) override` — `UE_DEPRECATED(5.6, "SetReferenceSkeleton is deprecated. Skeletons must only been set through the cloth collections.")`
- L195 _public function_ `virtual FGuid GetAssetGuid(int32 ) const override`
- L205 _private prototype_ `virtual void BeginBuildInternal(FSkinnedAssetBuildContext& Context) override;` — Initial step for the building process - Can't be done in parallel. USkinnedAsset Interface.
- L207 _private prototype_ `virtual void ExecuteBuildInternal(FSkinnedAssetBuildContext& Context) override;` — Thread-safe part. USkinnedAsset Interface.
- L209 _private prototype_ `virtual void FinishBuildInternal(FSkinnedAssetBuildContext& Context) override;` — Complete the building process - Can't be done in parallel. USkinnedAsset Interface.
- L210 _private prototype_ `virtual void BeginPostLoadAssetImpl(FSkinnedAssetPostLoadContext& Context) override;`
- L211 _private prototype_ `virtual void ExecutePostLoadAssetImpl(FSkinnedAssetPostLoadContext& Context) override;`
- L214 _private prototype_ `virtual FString GetAsyncPropertyName(uint64 Property) const override;` — Convert async property from enum value to string.
- L218 _private prototype_ `void BuildClothSimulationModel(TArray<FChaosClothAssetLodTransitionDataCache>* InOutTransitionCache = nullptr);` — Build the clothing simulation meshes from the Cloth Collection.
- L221 _private function_ `TArray<TSharedRef<const FManagedArrayCollection>>& GetClothCollectionsInternal()` — Return the cloth collection array with async protection access.
- L232 _private member_ `TObjectPtr<UDataflow> DataflowAsset_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Dataflow Asset is now stored in DataflowInstance"))` — Dataflow asset.
- L236 _private member_ `FString DataflowTerminal_DEPRECATED = "Cl` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Dataflow terminal name is now stored in DataflowInstance"))` — Dataflow Asset terminal node.
- L245 _private member_ `TObjectPtr<USkeleton> Skeleton;` — `UPROPERTY(EditAnywhere, Setter = SetSkeleton, Category = Skeleton, Meta = (EditCondition = "!HasDataflow()"))` — Skeleton asset used at creation time. This is of limited use since this USkeleton's reference skeleton might not necessarily match the one created for this asset. Set by the Dataflow evaluation.
- L249 _private member_ `TObjectPtr<UPhysicsAsset> PhysicsAsset;` — `UPROPERTY(EditAnywhere, Category = Collision, Meta = (EditCondition = "!HasDataflow()"))` — Physics asset used for collision. Set by the Dataflow evaluation.
- L254 _private member_ `bool bSmoothTransition_DEPRECATED = true;` — `UE_DEPRECATED(5.4, "Superseded by the ProxyDeformer node.")` — `UPROPERTY()` — Whether to blend positions between the skinned/simulated transitions of the cloth render mesh. Only used when not overridden in Dataflow by the ProxyDeformer node.
- L259 _private member_ `bool bUseMultipleInfluences_DEPRECATED = false;` — `UE_DEPRECATED(5.4, "Superseded by the ProxyDeformer node.")` — `UPROPERTY()` — Whether to use multiple triangle influences on the proxy wrap deformer to help smoothe deformations. Only used when not overridden in Dataflow by the ProxyDeformer node.
- L264 _private member_ `float SkinningKernelRadius_DEPRECATED = 30.f;` — `UE_DEPRECATED(5.4, "Superseded by the ProxyDeformer node.")` — `UPROPERTY()` — The radius from which to get the multiple triangle influences from the simulated proxy mesh. Only used when not overridden in Dataflow with the ProxyDeformer node.
- L268 _private member_ `FGuid AssetGuid;` — `UPROPERTY()` — A unique identifier as used by the section rendering code.
- L272 _private member_ `TArray<TSharedRef<const FManagedArrayCollection>> ClothCollections;` — `UE_DEPRECATED(5.4, "This must be protected for async build, always use the accessors even internally.")` — Cloth Collection containing this asset data. One per LOD.
- L275 _private member_ `TSharedPtr<FChaosClothSimulationModel> ClothSimulationModel;` — Simulation mesh Lods as fed to the solver for constraints creation. Ownership gets transferred to the proxy when it is changed during a simulation.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API CHAOSCLOTHASSETENGINE_API`
- L13 _namespace_ `namespace Dataflow`
- L35 _prototype_ `ENUM_CLASS_FLAGS(EClothAssetAsyncProperties);`

### `Plugins/ChaosClothAsset/Source/ChaosClothAssetEngine/Public/ChaosClothAsset/ClothAssetBase.h` (Public)


#### enum `EChaosClothAssetBaseAsyncProperties`  
`enum class EChaosClothAssetBaseAsyncProperties : uint32`  
_L30-39_
- reflection: `UENUM()`
- desc: Async build property lock identifiers for UChaosClothAssetBase. Bits 0-31 are reserved for the base class. Derived classes (e.g. UChaosClothAsset, UChaosOutfitAsset) use bits 32-63 via the generic AcquireAsyncProperty/ReleaseAsyncProperty/WaitUntilAsyncPropertyReleased templates declared on the base, which left-shift derived enum values by 32. The base class uses these bits directly via the EChaosClothAssetBaseAsyncProperties specializations.
- L32 _public enumerator_ `None = 0`
- L33 _public enumerator_ `RenderData = 1 << 0`
- L34 _public enumerator_ `RefSkeleton = 1 << 1`
- L35 _public enumerator_ `HasVertexColors = 1 << 2`
- L36 _public enumerator_ `OverlayMaterial = 1 << 3`
- L37 _public enumerator_ `OverlayMaterialMaxDrawDistance = 1 << 4`
- L38 _public enumerator_ `All = MAX_uint32`

#### class `UChaosClothAssetBase`  
`class UChaosClothAssetBase : public USkinnedAsset , public IDataflowContentOwner , public IDataflowInstanceInterface`  
_L47-601_
- reflection: `UCLASS(MinimalAPI, Abstract, BlueprintType)`
- inherits: `USkinnedAsset,IDataflowContentOwner,IDataflowInstanceInterface`
- desc: Base cloth asset class. Any object slot based on this type can be either a Cloth Asset or an Outfit Asset.
- L55 _public prototype_ `UChaosClothAssetBase(const FObjectInitializer& ObjectInitializer);`
- L59 _public prototype_ `virtual bool HasValidClothSimulationModels() const PURE_VIRTUAL(UChaosClothAssetBase::HasValidClothSimulationModels, return false;);` — Return whether the asset has any valid cloth simulation models and is simulation enabled.
- L63 _public prototype_ `virtual int32 GetNumClothSimulationModels() const PURE_VIRTUAL(UChaosClothAssetBase::GetNumClothSimulationModels, return 0;);` — Return the number of cloth simulation models in this asset.
- L67 _public prototype_ `virtual TSharedPtr<const FChaosClothSimulationModel> GetClothSimulationModel(int32 ModelIndex) const PURE_VIRTUAL(UChaosClothAssetBase::GetClothSimulationModel, return nullptr;);` — Return the simulation model physical data.
- L71 _public prototype_ `virtual FName GetClothSimulationModelName(int32 ModelIndex) const PURE_VIRTUAL(UChaosClothAssetBase::GetClothSimulationModelName, return NAME_None;);` — Return the name of the specified cloth simulation models in this asset.
- L75 _public prototype_ `virtual const TArray<TSharedRef<const FManagedArrayCollection>>& GetCollections(int32 ModelIndex) const PURE_VIRTUAL(UChaosClothAssetBase::GetCollections, static const TArray<TSharedRef<const FManagedArrayCollection>> EmptyArray; return EmptyArray;);` — Return the collections for this asset model (one per LOD).
- L79 _public prototype_ `virtual const UPhysicsAsset* GetPhysicsAssetForModel(int32 ModelIndex) const PURE_VIRTUAL(UChaosClothAssetBase::GetPhysicsAssetForModel, return nullptr;);` — Return the physics asset used for the simulation by this asset model.
- L83 _public prototype_ `virtual FGuid GetAssetGuid(int32 ModelIndex) const PURE_VIRTUAL(UChaosClothAssetBase::GetAssetGuid, return FGuid(););` — Return the asset GUID used to match the render sections for this asset model.
- L88 _public prototype_ `virtual void CacheDerivedData(FSkinnedAssetCompilationContext* Context);` — Load the running-platform render data from the DDC if cached, otherwise leave the render data untouched for the caller to rebuild.
- L96 _public function_ `virtual UChaosClothAssetBase* CreatePreviewAssetCopy(UObject* Outer, EObjectFlags Flags) const` — Create a simplified copy of this asset suitable for preview rendering (thumbnails, etc.). @param Outer The outer object for the preview copy. @param Flags Object flags for the preview copy. @return A transient asset copy, or nullptr if this asset can be used directly for previewing.
- L108 _public prototype_ `static UChaosClothAssetBase* CreateSimModelPreviewAsset( const UChaosClothAssetBase& SourceAsset, UObject* Outer, EObjectFlags Flags, UMaterialInterface* Material);` — Create a transient asset with render data built from the source asset's simulation models. Used for preview rendering when an asset has no render data, or for rendering the sim model specifically (e.g. Cloth3DSimView). @param SourceAsset Asset to read simulation models from. @param Outer The outer object for the preview asset. @param Flags Object flags for the preview asset. @param Material Material to apply. Use FClothEngineTools::GetSimPreviewMaterial() for the default. @return A transient asset, or nullptr if the source has no valid simulation models.
- L116 _public prototype_ `virtual void SetReferenceSkeleton(const FReferenceSkeleton* ReferenceSkeleton);` — Set the specified reference skeleton or a default reference skeleton with a simple root if ReferenceSkeleton is nullptr.
- L120 _public prototype_ `virtual TObjectPtr<UDataflowBaseContent> CreateDataflowContent() override;`
- L121 _public prototype_ `virtual void WriteDataflowContent(const TObjectPtr<UDataflowBaseContent>& DataflowContent) const override;`
- L122 _public prototype_ `virtual void ReadDataflowContent(const TObjectPtr<UDataflowBaseContent>& DataflowContent) override;`
- L126 _public prototype_ `virtual const FDataflowInstance& GetDataflowInstance() const override;`
- L127 _public prototype_ `virtual FDataflowInstance& GetDataflowInstance() override;`
- L131 _public prototype_ `virtual void BeginDestroy() override;`
- L132 _public prototype_ `virtual bool IsReadyForFinishDestroy() override;`
- L133 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L134 _public prototype_ `virtual void PostLoad() override;`
- L135 _public prototype_ `virtual void PostInitProperties() override;`
- L136 _public prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;`
- L138 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L139 _public prototype_ `virtual void BeginCacheForCookedPlatformData(const ITargetPlatform* TargetPlatform) override;`
- L140 _public prototype_ `virtual bool IsCachedCookedPlatformDataLoaded(const ITargetPlatform* TargetPlatform) override;`
- L141 _public prototype_ `virtual void ClearAllCachedCookedPlatformData() override;`
- L143 _public prototype_ `virtual void GetResourceSizeEx(FResourceSizeEx& CumulativeResourceSize) override;`
- L147 _public prototype_ `virtual FReferenceSkeleton& GetRefSkeleton() override;`
- L148 _public prototype_ `virtual const FReferenceSkeleton& GetRefSkeleton() const override;`
- L149 _public prototype_ `virtual FSkeletalMeshLODInfo* GetLODInfo(int32 Index);`
- L150 _public prototype_ `virtual const FSkeletalMeshLODInfo* GetLODInfo(int32 Index) const;`
- L152 _public function_ `virtual class UPhysicsAsset* GetShadowPhysicsAsset() const override` — `UFUNCTION(BlueprintGetter)`
- L156 _public function_ `virtual FMatrix GetComposedRefPoseMatrix(FName BoneName) const override`
- L160 _public function_ `virtual FMatrix GetComposedRefPoseMatrix(int32 BoneIndex) const override`
- L164 _public prototype_ `virtual const FMeshUVChannelInfo* GetUVChannelData(int32 MaterialIndex) const override;`
- L165 _public function_ `virtual bool GetSupportRayTracing() const override`
- L169 _public function_ `virtual int32 GetRayTracingMinLOD() const override`
- L173 _public function_ `virtual TArray<FMatrix44f>& GetRefBasesInvMatrix() override`
- L177 _public function_ `virtual const TArray<FMatrix44f>& GetRefBasesInvMatrix() const override`
- L181 _public function_ `virtual TArray<FSkeletalMeshLODInfo>& GetLODInfoArray() override`
- L185 _public function_ `virtual const TArray<FSkeletalMeshLODInfo>& GetLODInfoArray() const override`
- L189 _public prototype_ `virtual FSkeletalMeshRenderData* GetResourceForRendering() const override;`
- L190 _public function_ `virtual int32 GetDefaultMinLod() const`
- L194 _public function_ `virtual const FPerPlatformInt& GetMinLod() const override`
- L198 _public function_ `virtual TArray<FSkeletalMaterial>& GetMaterials() override`
- L202 _public function_ `virtual const TArray<FSkeletalMaterial>& GetMaterials() const override`
- L206 _public function_ `virtual bool IsMaterialUsed(int32 MaterialIndex) const override`
- L210 _public function_ `virtual int32 GetLODNum() const override`
- L214 _public function_ `virtual FBoxSphereBounds GetBounds() const override`
- L218 _public function_ `virtual TArray<class USkeletalMeshSocket*> GetActiveSocketList() const override`
- L222 _public function_ `virtual USkeletalMeshSocket* FindSocket(FName InSocketName) const override`
- L226 _public function_ `virtual USkeletalMeshSocket* FindSocketInfo(FName InSocketName, FTransform& OutTransform, int32& OutBoneIndex, int32& OutIndex) const override`
- L230 _public function_ `virtual UMeshDeformer* GetDefaultMeshDeformer() const override`
- L234 _public function_ `virtual UMeshDeformerCollection* GetTargetMeshDeformers() const override`
- L238 _public function_ `virtual bool HasHalfEdgeBuffer(int32 LODIndex) const override`
- L245 _public prototype_ `virtual class UMaterialInterface* GetOverlayMaterial() const override;` — `UFUNCTION(BlueprintCallable, Category = "Rendering|Material")` — Get the default overlay material used by this mesh
- L248 _public prototype_ `virtual float GetOverlayMaterialMaxDrawDistance() const override;` — `UFUNCTION(BlueprintCallable, Category = "Rendering|Material")` — Get the default overlay material max draw distance used by this mesh
- L249 _public function_ `virtual bool IsValidLODIndex(int32 Index) const override`
- L253 _public prototype_ `virtual int32 GetMinLodIdx(bool bForceLowestLODIdx = false) const override;`
- L254 _public function_ `virtual bool NeedCPUData(int32 LODIndex) const override`
- L258 _public prototype_ `virtual bool GetHasVertexColors() const override;`
- L259 _public prototype_ `virtual int32 GetPlatformMinLODIdx(const ITargetPlatform* TargetPlatform) const override;`
- L260 _public function_ `virtual const FPerPlatformBool& GetDisableBelowMinLodStripping() const override`
- L264 _public prototype_ `virtual bool IsMinLodQualityLevelEnable() const override;`
- L267 _public function_ `virtual bool GetEnableLODStreaming(const class ITargetPlatform* TargetPlatform) const override`
- L271 _public function_ `virtual int32 GetMaxNumStreamedLODs(const class ITargetPlatform* TargetPlatform) const override`
- L275 _public function_ `virtual int32 GetMaxNumOptionalLODs(const ITargetPlatform* TargetPlatform) const override`
- L282 _public function_ `virtual FSkeletalMeshModel* GetImportedModel() const override` — Default GetImportedModel returns the inherited MeshModel; derived classes override to add async-property waits.
- L289 _public function_ `const FPerQualityLevelInt& GetQualityLevelMinLod() const`
- L293 _public function_ `void SetQualityLevelMinLod(FPerQualityLevelInt InMinLod)`
- L300 _public prototype_ `void SetOverlayMaterial(class UMaterialInterface* NewOverlayMaterial);` — `UFUNCTION(BlueprintCallable, Category = "Rendering|Material")` — Change the default overlay material used by this mesh
- L303 _public prototype_ `void SetOverlayMaterialMaxDrawDistance(float InMaxDrawDistance);` — `UFUNCTION(BlueprintCallable, Category = "Rendering|Material")` — Change the default overlay material max draw distance used by this mesh
- L309 _public prototype_ `void SetDataflow(UDataflow* InDataflow);` — Set the Dataflow graph asset for this asset. @param InDataflow The new dataflow asset.
- L312 _public prototype_ `UDataflow* GetDataflow();` — Return the Dataflow graph asset associated to this asset if any.
- L315 _public prototype_ `const UDataflow* GetDataflow() const;` — Return the Dataflow graph asset associated to this asset if any, const version.
- L322 _public function_ `bool HasDataflow() const` — `UFUNCTION()` — Return whether there is a Dataflow graph associated with this asset. This function can be used in EditCondition.
- L328 _public prototype_ `void SetPreviewSceneSkeletalMesh(class USkeletalMesh* Mesh);`
- L329 _public prototype_ `class USkeletalMesh* GetPreviewSceneSkeletalMesh() const;`
- L331 _public prototype_ `void SetPreviewSceneAnimation(class UAnimationAsset* Animation);`
- L332 _public prototype_ `class UAnimationAsset* GetPreviewSceneAnimation() const;`
- L334 _public function_ `class UAssetImportData* GetAssetImportData() const`
- L339 _public function_ `void SetAssetImportData(class UAssetImportData* InAssetImportData)`
- L344 _public function_ `static FName GetAssetImportDataMemberName()`
- L350 _public prototype_ `void SetHasVertexColors(bool InbHasVertexColors);`
- L359 _public prototype_ `bool ExportToSkeletalMesh(USkeletalMesh& SkeletalMesh) const;` — Export the graphical representation of this asset to a SkeletalMesh asset. Includes skinning, but excludes all clothing simulation data since it isn't compatible with the Cloth Asset. @param SkeletalMesh The empty skeletal mesh asset to be written to. @return Whether the initialization of the skeletal mesh has succeeded or not.
- L365 _protected prototype_ `virtual const TCHAR* GetDerivedDataPrefix() const PURE_VIRTUAL(UChaosClothAssetBase::GetDerivedDataPrefix, return TEXT(""););` — DDC key prefix that distinguishes this asset type's cache entries, e.g. "CHAOSOUTFIT", "CHAOSCLOTH".
- L369 _protected prototype_ `virtual const TCHAR* GetDerivedDataVersion() const PURE_VIRTUAL(UChaosClothAssetBase::GetDerivedDataVersion, return TEXT(""););` — DDC key version GUID; bump to invalidate cached entries when the on-disk layout changes.
- L373 _protected prototype_ `void AppendBuildSettingsToDDCKey(FString& InOutKeySuffix, const ITargetPlatform* TargetPlatform);` — Append build settings to a DDC key suffix: GPU bone limits, bone influences, LODInfo GUIDs.
- L376 _protected prototype_ `void StoreDerivedData();` — Store the current running-platform render data to DDC and set the head DerivedDataKey.
- L379 _protected prototype_ `virtual bool IsInitialBuildDone() const override;` — True once the head render data carries a DerivedDataKey: set by Build->Store, DDC hit, or cooked-load.
- L382 _protected prototype_ `virtual void PrepareMeshModel();` — Prepare an empty FSkeletalMeshModel sized to the current head render data, used by BuildLODModel on a Cache miss.
- L385 _protected prototype_ `void EstablishCookedHeadKey();` — Maintain the cooked-load head invariant: head holds running-platform render data with matching DerivedDataKey.
- L388 _protected prototype_ `FSkeletalMeshRenderData* GetSerializeRenderData(FArchive& Ar);` — Cooked-save render data switch on Ar.CookingTarget(); builds the per-platform variant on miss.
- L391 _protected function_ `virtual void BeginPostLoadAssetImpl(FSkinnedAssetPostLoadContext& Context)` — Asset-specific BeginPostLoadInternal work, called on the game thread.
- L394 _protected function_ `virtual void ExecutePostLoadAssetImpl(FSkinnedAssetPostLoadContext& Context)` — Asset-specific ExecutePostLoadInternal work, may run on a worker thread.
- L398 _protected prototype_ `virtual FString GetAsyncPropertyName(uint64 Property) const override;` — Resolve the names of base-class async property bits (bits 0-31) for diagnostic logging.
- L401 _protected prototype_ `void OnPropertyChanged(const bool bReregisterComponents = false) const;` — Update all properties for components currently using this asset.
- L404 _protected prototype_ `void OnAssetChanged(const bool bReregisterComponents = true) const;` — Update all components currently using this asset.
- L408 _protected prototype_ `void ReregisterComponents() const;` — `UE_DEPRECATED(5.7, "Use OnAssetChanged instead.")` — Reregister all components using this asset to reset the simulation in case anything has changed.
- L411 _protected prototype_ `TArray<UActorComponent*> GetDependentComponents() const;` — Return all components currently using this asset.
- L415 _protected function_ `template <typename EnumType UE_REQUIRES(TIsEnum<EnumType>::Value)> void AcquireAsyncProperty(const EnumType AsyncProperties, ESkinnedAssetAsyncPropertyLockType LockType = ESkinnedAssetAsyncPropertyLockType::ReadWrite)` — Lock properties that should not be modified/accessed during async build.
- L423 _protected function_ `template <typename EnumType UE_REQUIRES(TIsEnum<EnumType>::Value)> void ReleaseAsyncProperty(const EnumType AsyncProperties, ESkinnedAssetAsyncPropertyLockType LockType = ESkinnedAssetAsyncPropertyLockType::ReadWrite)` — Release properties that should not be modified/accessed during async build.
- L434 _protected function_ `template <typename EnumType UE_REQUIRES(TIsEnum<EnumType>::Value)> void WaitUntilAsyncPropertyReleased(const EnumType AsyncProperties, ESkinnedAssetAsyncPropertyLockType LockType = ESkinnedAssetAsyncPropertyLockType::ReadWrite) const` — Wait for the asset to finish compilation to protect internal skinned asset data from race conditions during async build. This should be called before accessing all async accessible properties.
- L441 _protected prototype_ `void SetResourceForRendering(TUniquePtr<FSkeletalMeshRenderData>&& InSkeletalMeshRenderData);` — Set render data.
- L444 _protected prototype_ `void InitResources();` — Initialize all render resources.
- L447 _protected prototype_ `void ReleaseResources();` — Safely release the render data.
- L450 _protected prototype_ `void CalculateInvRefMatrices();` — Pre-calculate refpose-to-local transforms.
- L453 _protected prototype_ `void CalculateBounds();` — Calculate bounds from the render data's position vertex buffer.
- L457 _protected member_ `FDataflowInstance DataflowInstance;` — `UE_DEPRECATED(5.6, "This property isn't deprecated, but the proper getter and setter should be used instead in order to preserve correct behavior.")` — `UPROPERTY(EditAnywhere, Category = "Dataflow")`
- L461 _protected member_ `TArray<FSkeletalMaterial> Materials;` — `UPROPERTY(EditAnywhere, Category = Materials, Meta = (EditCondition = "!HasDataflow()"))` — List of materials for this cloth asset. Set by the Dataflow evaluation.
- L465 _protected member_ `TArray<FSkeletalMeshLODInfo> LODInfo;` — `UPROPERTY(VisibleAnywhere, EditFixedSize, Category = LevelOfDetails)` — Struct containing information for each LOD level, such as materials to use, and when use the LOD. Not currently editable or customizable through the Dataflow.
- L469 _protected member_ `FPerQualityLevelInt MinQualityLevelLOD = 0;` — `UPROPERTY(EditAnywhere, Category = LODSettings, meta = (DisplayName = "Quality Level Minimum LOD"))` — Set the Minimum LOD by Quality Level. This property is used when "Use Cloth Asset Min LOD Per Quality Levels" is set at the Project level. Otherwise, the (per platform) Minimum LOD value is used.
- L472 _protected member_ `FPerPlatformBool DisableBelowMinLodStripping;` — `UPROPERTY(EditAnywhere, Category = LODSettings)`
- L476 _protected member_ `FPerPlatformInt MinLod = 0;` — `UPROPERTY(EditAnywhere, Category = LODSettings, Meta = (DisplayName = "Minimum LOD"))` — Set the Minimum LOD by platform. This property is overridden by "Quality Level Minimum LOD" when "Use Cloth Asset Min LOD Per Quality Levels" is set at the Project level.
- L480 _protected member_ `uint8 bSupportRayTracing : 1;` — `UPROPERTY(EditAnywhere, Category = RayTracing)` — Enable raytracing for this asset.
- L484 _protected member_ `int32 RayTracingMinLOD;` — `UPROPERTY(EditAnywhere, Category = RayTracing)` — Minimum raytracing LOD for this asset.
- L491 _protected member_ `TObjectPtr<class UPhysicsAsset> ShadowPhysicsAsset;` — `UPROPERTY(EditAnywhere, AssetRegistrySearchable, BlueprintGetter = GetShadowPhysicsAsset, Category = Lighting)` — Physics asset whose shapes will be used for shadowing when components have bCastCharacterCapsuleDirectShadow or bCastCharacterCapsuleIndirectShadow enabled. Only spheres and sphyl shapes in the physics asset can be supported.  The more shapes used, the higher the cost of the capsule shadows will be.
- L496 _protected member_ `TObjectPtr<class UMaterialInterface> OverlayMaterial;` — `UE_DEPRECATED(5.6, "This must be protected for async build, always use the accessors even internally.")` — `UPROPERTY(EditAnywhere, Category = Rendering)` — Default translucent material to blend on top of this mesh. Mesh will be rendered twice - once with a base material and once with overlay material
- L501 _protected member_ `float OverlayMaterialMaxDrawDistance;` — `UE_DEPRECATED(5.6, "This must be protected for async build, always use the accessors even internally.")` — `UPROPERTY(EditAnywhere, Category = Rendering)` — Default max draw distance for overlay material. A distance of 0 indicates that overlay will be culled using primitive max distance.
- L505 _protected member_ `uint8 bHasVertexColors : 1 = false;` — `UE_DEPRECATED(5.6, "This must be protected for async build, always use the accessors even internally.")` — `UPROPERTY()`
- L509 _protected member_ `FReferenceSkeleton RefSkeleton;` — `UE_DEPRECATED(5.4, "This must be protected for async build, always use the accessors even internally.")` — Reference skeleton created from the provided skeleton asset.
- L514 _protected member_ `bool bHasDataflowAsset = false;` — `UE_DEPRECATED(5.8, "Use HasDataflow instead.")` — `UPROPERTY()`
- L517 _protected member_ `TSharedPtr<FSkeletalMeshModel> MeshModel;` — Transient source mesh model used to feed BuildLODModel during Cache(); built in PrepareMeshModel() and reset once GetPlatformSkeletalMeshRenderData() finishes caching.
- L522 _protected member_ `FBoxSphereBounds Bounds;` — `UPROPERTY()` — Bounds for this asset.
- L525 _protected member_ `FRenderCommandFence ReleaseResourcesFence;` — A fence which is used to keep track of the rendering thread releasing the static mesh resources.
- L530 _private function_ `template <> void AcquireAsyncProperty<EChaosClothAssetBaseAsyncProperties>(const EChaosClothAssetBaseAsyncProperties AsyncProperties, ESkinnedAssetAsyncPropertyLockType LockType)` — Lock base-class async property bits (0-31) directly, without the derived-class left-shift by 32.
- L537 _private function_ `template <> void ReleaseAsyncProperty<EChaosClothAssetBaseAsyncProperties>(const EChaosClothAssetBaseAsyncProperties AsyncProperties, ESkinnedAssetAsyncPropertyLockType LockType)` — Release base-class async property bits (0-31) directly, without the derived-class left-shift by 32.
- L544 _private function_ `template <> void WaitUntilAsyncPropertyReleased<EChaosClothAssetBaseAsyncProperties>(const EChaosClothAssetBaseAsyncProperties AsyncProperties, ESkinnedAssetAsyncPropertyLockType LockType) const` — Wait for base-class async property bits (0-31) directly, without the derived-class left-shift by 32.
- L550 _private prototype_ `virtual void BeginPostLoadInternal(FSkinnedAssetPostLoadContext& Context) override;`
- L551 _private prototype_ `virtual void ExecutePostLoadInternal(FSkinnedAssetPostLoadContext& Context) override;`
- L553 _private prototype_ `virtual void FinishPostLoadInternal(FSkinnedAssetPostLoadContext& Context) override;` — Complete the postload process - shared by all cloth asset types.
- L557 _private prototype_ `void UpdateSimulationActor(TObjectPtr<AActor>& SimulationActor) const;` — Update simulation actor/components from the asset data
- L561 _private prototype_ `void RegisterOnPackageReloadedDelegate();` — Register the OnPackageReloaded delegate to call OnAssetChanged() when reloading this asset.
- L563 _private prototype_ `void UnregisterOnPackageReloadedDelegate();` — Unregister the OnPackageReloaded delegate.
- L566 _private prototype_ `FSkeletalMeshRenderData& GetPlatformSkeletalMeshRenderData(const ITargetPlatform* TargetPlatform, bool bIsSerializeSaving);` — Get or build platform-specific render data for cooking via the linked-list pattern.
- L572 _private prototype_ `template<typename T> void SyncBPPreviewAsset(TSoftObjectPtr<T>& PreviewAsset, const TCHAR* const VarName);` — Helper function to move deprecated Cloth Editor preview assets to the new BP variable system.
- L582 _private member_ `TSoftObjectPtr<class USkeletalMesh> PreviewSceneSkeletalMesh;` — `UPROPERTY(DuplicateTransient, AssetRegistrySearchable)` — Optional Skeletal Mesh that the cloth asset is attached to in the Preview Scene in the Cloth Editor
- L586 _private member_ `TSoftObjectPtr<class UAnimationAsset> PreviewSceneAnimation;` — `UPROPERTY(DuplicateTransient, AssetRegistrySearchable)` — Optional animation attached to PreviewSceneSkeletalMesh in the Preview Scene in the Cloth Editor
- L590 _private member_ `TObjectPtr<class UAssetImportData> AssetImportData;` — `UPROPERTY(VisibleAnywhere, Instanced, Category = ImportSettings)` — Asset data to be used when re-importing
- L594 _private member_ `TUniquePtr<FSkeletalMeshRenderData> SkeletalMeshRenderData;` — Rendering data.
- L597 _private member_ `TArray<FMatrix44f> RefBasesInvMatrix;` — Reference skeleton precomputed bases.
- L600 _private member_ `TArray<FMatrix> CachedComposedRefPoseMatrices;` — Mesh-space ref pose, where parent matrices are applied to ref pose matrices.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CHAOSCLOTHASSETENGINE_API`
- L40 _prototype_ `ENUM_CLASS_FLAGS(EChaosClothAssetBaseAsyncProperties);`

### `Plugins/ChaosClothAsset/Source/ChaosClothAssetEngine/Public/ChaosClothAsset/ClothAssetInteractor.h` (Public)


#### class `UChaosClothAssetInteractor`  
`class UChaosClothAssetInteractor : public UClothingInteractor`  
_L16-210_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UClothingInteractor`
- L22 _public prototype_ `void SetProperties(const TArray<TSharedPtr<::Chaos::Softs::FCollectionPropertyFacade>>& InCollectionPropertyFacades);` — Set properties this interactor references.
- L25 _public prototype_ `void ResetProperties();` — Empty references to all properties.
- L29 _public prototype_ `TArray<FName> GetAllPropertyNames(int32 LODIndex = -1) const;` — `UFUNCTION(BlueprintCallable, Category = ClothProperty)` — Generate a list of all properties held by this interactor. Properties for all LODs will be returned if LODIndex = -1.
- L33 _public prototype_ `float GetFloatPropertyValue(const FName PropertyName, int32 LODIndex = 0, float DefaultValue = 0.f) const;` — `UFUNCTION(BlueprintCallable, Category = ClothProperty)` — Get the value for a property cast to float. DefaultValue will be returned if the property is not found.
- L37 _public prototype_ `float GetLowFloatPropertyValue(const FName PropertyName, int32 LODIndex = 0, float DefaultValue = 0.f) const;` — `UFUNCTION(BlueprintCallable, Category = ClothProperty)` — Get the low value for a weighted property value (same as GetFloatValue). DefaultValue will be returned if the property is not found.
- L41 _public prototype_ `float GetHighFloatPropertyValue(const FName PropertyName, int32 LODIndex = 0, float DefaultValue = 0.f) const;` — `UFUNCTION(BlueprintCallable, Category = ClothProperty)` — Get the high value for a weighted property value. DefaultValue will be returned if the property is not found.
- L45 _public prototype_ `FVector2D GetWeightedFloatPropertyValue(const FName PropertyName, int32 LODIndex = 0, FVector2D DefaultValue = FVector2D(0., 0.)) const;` — `UFUNCTION(BlueprintCallable, Category = ClothProperty)` — Get the low and high values for a weighted property value. DefaultValue will be returned if the property is not found.
- L49 _public prototype_ `int32 GetIntPropertyValue(const FName PropertyName, int32 LODIndex = 0, int32 DefaultValue = 0) const;` — `UFUNCTION(BlueprintCallable, Category = ClothProperty)` — Get the value for a property cast to int. DefaultValue will be returned if the property is not found.
- L53 _public prototype_ `FVector GetVectorPropertyValue(const FName PropertyName, int32 LODIndex = 0, FVector DefaultValue = FVector(0.)) const;` — `UFUNCTION(BlueprintCallable, Category = ClothProperty)` — Get the value for a property cast to vector. DefaultValue will be returned if the property is not found.
- L57 _public prototype_ `FString GetStringPropertyValue(const FName PropertyName, int32 LODIndex = 0, const FString& DefaultValue = "") const;` — `UFUNCTION(BlueprintCallable, Category = ClothProperty)` — Get the string value for a property (typically the associated map name for weighted values). DefaultValue will be returned if the property is not found.
- L61 _public prototype_ `void SetPropertySet(const FClothAssetInteractorPropertyBag& PropertySet, int32 LODIndex = -1);` — `UFUNCTION(BlueprintCallable, Category = ClothProperty)` — Set properties from an interactor data set
- L65 _public prototype_ `void SetFloatPropertyValue(const FName PropertyName, int32 LODIndex = -1, float Value = 0.f);` — `UFUNCTION(BlueprintCallable, Category = ClothProperty)` — Set the value for a property (if it exists). This sets the Low and High values for weighted values. All LODs will be set when LODIndex = -1.
- L69 _public prototype_ `void SetLowFloatPropertyValue(const FName PropertyName, int32 LODIndex = -1, float Value = 0.f);` — `UFUNCTION(BlueprintCallable, Category = ClothProperty)` — Set the low value for a weighted property (if it exists). All LODs will be set when LODIndex = -1.
- L73 _public prototype_ `void SetHighFloatPropertyValue(const FName PropertyName, int32 LODIndex = -1, float Value = 0.f);` — `UFUNCTION(BlueprintCallable, Category = ClothProperty)` — Set the high value for a weighted property (if it exists). All LODs will be set when LODIndex = -1.
- L77 _public prototype_ `void SetWeightedFloatPropertyValue(const FName PropertyName, int32 LODIndex = -1, FVector2D Value = FVector2D(0., 0.));` — `UFUNCTION(BlueprintCallable, Category = ClothProperty)` — Set the low and high values for a weighted property (if it exists). All LODs will be set when LODIndex = -1.
- L81 _public prototype_ `void SetIntPropertyValue(const FName PropertyName, int32 LODIndex = -1, int32 Value = 0);` — `UFUNCTION(BlueprintCallable, Category = ClothProperty)` — Set the value for a property (if it exists). All LODs will be set when LODIndex = -1.
- L85 _public prototype_ `void SetVectorPropertyValue(const FName PropertyName, int32 LODIndex = -1, FVector Value = FVector(0.));` — `UFUNCTION(BlueprintCallable, Category = ClothProperty)` — Set the value for a property (if it exists). All LODs will be set when LODIndex = -1.
- L89 _public prototype_ `void SetStringPropertyValue(const FName PropertyName, int32 LODIndex = -1, const FString& Value = "");` — `UFUNCTION(BlueprintCallable, Category = ClothProperty)` — Set the string value for a property (if it exists). This is typically the map name associated with a property. All LODs will be set when LODIndex = -1.
- L94 _public prototype_ `TArray<FString> GetAllProperties(int32 LODIndex = -1) const;` — `UFUNCTION(BlueprintCallable, meta = (DeprecatedFunction = "Note", DeprecationMessage = "Use GetAllPropertyNames instead"))` — Generate a list of all properties held by this interactor. Properties for all LODs will be returned if LODIndex = -1.
- L99 _public function_ `float GetFloatValue(const FString& PropertyName, int32 LODIndex = 0, float DefaultValue = 0.f) const` — `UFUNCTION(BlueprintCallable, Category = "ClothProperty|Deprecated", meta = (DeprecatedFunction = "Note", DeprecationMessage = "Use GetFloatPropertyValue instead"))` — `UE_DEPRECATED(5.7, "Use GetFloatPropertyValue instead")` — Get the value for a property cast to float. DefaultValue will be returned if the property is not found.
- L107 _public function_ `float GetLowFloatValue(const FString& PropertyName, int32 LODIndex = 0, float DefaultValue = 0.f) const` — `UFUNCTION(BlueprintCallable, Category = "ClothProperty|Deprecated", meta = (DeprecatedFunction = "Note", DeprecationMessage = "Use GetLowFloatPropertyValue instead"))` — `UE_DEPRECATED(5.7, "Use GetLowFloatPropertyValue instead")` — Get the low value for a weighted property value (same as GetFloatValue). DefaultValue will be returned if the property is not found.
- L115 _public function_ `float GetHighFloatValue(const FString& PropertyName, int32 LODIndex = 0, float DefaultValue = 0.f) const` — `UFUNCTION(BlueprintCallable, Category = "ClothProperty|Deprecated", meta = (DeprecatedFunction = "Note", DeprecationMessage = "Use GetHighFloatPropertyValue instead"))` — `UE_DEPRECATED(5.7, "Use GetHighFloatPropertyValue instead")` — Get the high value for a weighted property value. DefaultValue will be returned if the property is not found.
- L123 _public function_ `FVector2D GetWeightedFloatValue(const FString& PropertyName, int32 LODIndex = 0, FVector2D DefaultValue = FVector2D(0., 0.)) const` — `UFUNCTION(BlueprintCallable, Category = "ClothProperty|Deprecated", meta = (DeprecatedFunction = "Note", DeprecationMessage = "Use GetWeightedFloatPropertyValue instead"))` — `UE_DEPRECATED(5.7, "Use GetWeightedFloatPropertyValue instead")` — Get the low and high values for a weighted property value. DefaultValue will be returned if the property is not found.
- L131 _public function_ `int32 GetIntValue(const FString& PropertyName, int32 LODIndex = 0, int32 DefaultValue = 0) const` — `UFUNCTION(BlueprintCallable, Category = "ClothProperty|Deprecated", meta = (DeprecatedFunction = "Note", DeprecationMessage = "Use GetIntPropertyValue instead"))` — `UE_DEPRECATED(5.7, "Use GetIntPropertyValue instead")` — Get the value for a property cast to int. DefaultValue will be returned if the property is not found.
- L139 _public function_ `FVector GetVectorValue(const FString& PropertyName, int32 LODIndex = 0, FVector DefaultValue = FVector(0.)) const` — `UFUNCTION(BlueprintCallable, Category = "ClothProperty|Deprecated", meta = (DeprecatedFunction = "Note", DeprecationMessage = "Use GetVectorPropertyValue instead"))` — `UE_DEPRECATED(5.7, "Use GetVectorPropertyValue instead")` — Get the value for a property cast to vector. DefaultValue will be returned if the property is not found.
- L147 _public function_ `FString GetStringValue(const FString& PropertyName, int32 LODIndex = 0, const FString& DefaultValue = "") const` — `UFUNCTION(BlueprintCallable, Category = "ClothProperty|Deprecated", meta = (DeprecatedFunction = "Note", DeprecationMessage = "Use GetStringPropertyValue instead"))` — `UE_DEPRECATED(5.7, "Use GetStringPropertyValue instead")` — Get the string value for a property (typically the associated map name for weighted values). DefaultValue will be returned if the property is not found.
- L155 _public function_ `void SetFloatValue(const FString& PropertyName, int32 LODIndex = -1, float Value = 0.f)` — `UFUNCTION(BlueprintCallable, Category = "ClothProperty|Deprecated", meta = (DeprecatedFunction = "Note", DeprecationMessage = "Use SetFloatPropertyValue instead"))` — `UE_DEPRECATED(5.7, "Use SetFloatPropertyValue instead")` — Set the value for a property (if it exists). This sets the Low and High values for weighted values. All LODs will be set when LODIndex = -1.
- L163 _public function_ `void SetLowFloatValue(const FString& PropertyName, int32 LODIndex = -1, float Value = 0.f)` — `UFUNCTION(BlueprintCallable, Category = "ClothProperty|Deprecated", meta = (DeprecatedFunction = "Note", DeprecationMessage = "Use SetLowFloatPropertyValue instead"))` — `UE_DEPRECATED(5.7, "Use SetLowFloatPropertyValue instead")` — Set the low value for a weighted property (if it exists). All LODs will be set when LODIndex = -1.
- L171 _public function_ `void SetHighFloatValue(const FString& PropertyName, int32 LODIndex = -1, float Value = 0.f)` — `UFUNCTION(BlueprintCallable, Category = "ClothProperty|Deprecated", meta = (DeprecatedFunction = "Note", DeprecationMessage = "Use SetHighFloatPropertyValue instead"))` — `UE_DEPRECATED(5.7, "Use SetHighFloatPropertyValue instead")` — Set the high value for a weighted property (if it exists). All LODs will be set when LODIndex = -1.
- L179 _public function_ `void SetWeightedFloatValue(const FString& PropertyName, int32 LODIndex = -1, FVector2D Value = FVector2D(0., 0.))` — `UFUNCTION(BlueprintCallable, Category = "ClothProperty|Deprecated", meta = (DeprecatedFunction = "Note", DeprecationMessage = "Use SetWeightedFloatPropertyValue instead"))` — `UE_DEPRECATED(5.7, "Use SetWeightedFloatPropertyValue instead")` — Set the low and high values for a weighted property (if it exists). All LODs will be set when LODIndex = -1.
- L187 _public function_ `void SetIntValue(const FString& PropertyName, int32 LODIndex = -1, int32 Value = 0)` — `UFUNCTION(BlueprintCallable, Category = "ClothProperty|Deprecated", meta = (DeprecatedFunction = "Note", DeprecationMessage = "Use SetIntPropertyValue instead"))` — `UE_DEPRECATED(5.7, "Use SetIntPropertyValue instead")` — Set the value for a property (if it exists). All LODs will be set when LODIndex = -1.
- L195 _public function_ `void SetVectorValue(const FString& PropertyName, int32 LODIndex = -1, FVector Value = FVector(0.))` — `UFUNCTION(BlueprintCallable, Category = "ClothProperty|Deprecated", meta = (DeprecatedFunction = "Note", DeprecationMessage = "Use SetVectorPropertyValue instead"))` — `UE_DEPRECATED(5.7, "Use SetVectorPropertyValue instead")` — Set the value for a property (if it exists). All LODs will be set when LODIndex = -1.
- L203 _public function_ `void SetStringValue(const FString& PropertyName, int32 LODIndex = -1, const FString& Value = "")` — `UFUNCTION(BlueprintCallable, Category = "ClothProperty|Deprecated", meta = (DeprecatedFunction = "Note", DeprecationMessage = "Use SetStringPropertyValue instead"))` — `UE_DEPRECATED(5.7, "Use SetStringPropertyValue instead")` — Set the string value for a property (if it exists). This is typically the map name associated with a property. All LODs will be set when LODIndex = -1.
- L209 _private member_ `TArray<TWeakPtr<::Chaos::Softs::FCollectionPropertyFacade>> CollectionPropertyFacades;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Chaos`
- L9 _namespace_ `namespace Softs` (scope `Chaos`)

### `Plugins/ChaosClothAsset/Source/ChaosClothAssetEngine/Public/ChaosClothAsset/ClothAssetSKMClothingAsset.h` (Public)


#### class `UChaosClothAssetSKMClothingAsset`  
`class UChaosClothAssetSKMClothingAsset final : public UClothingAssetBase`  
_L18-105_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UClothingAssetBase`
- desc: Clothing Data implementation for the Cloth/Outfit Asset.
- L22 _public prototype_ `UChaosClothAssetSKMClothingAsset(const FObjectInitializer& ObjectInitializer);`
- L30 _public prototype_ `void SetAsset(const UChaosClothAssetBase* InAsset);` — Assign a Cloth or an Outfit Asset to this clothing data. @note This is only possible WITH_EDITOR since the Skeletal Mesh might need to be rebuild when the asset is changed. @param InAsset The new asset to set.
- L36 _public prototype_ `void OnAssetChanged(const bool bReregisterComponents = true);` — Call this function whenever the Cloth or Outfit Asset has changed (e.g. once rebuilt in Dataflow). @param bReregisterComponents Whether to reregister the dependent components. When set to false, the registration must be carried outside of this function call.
- L40 _public function_ `const UChaosClothAssetBase* GetAsset() const` — Return the underlaying Cloth or Outfit Asset used in this clothing data.
- L46 _public function_ `int32 GetClothSimulationModelIndex() const` — Return the index of the simulation model used from the Cloth or Outfit Asset.
- L51 _public prototype_ `const TSharedPtr<const FChaosClothSimulationModel>& GetTransientSimulationModel() const;`
- L53 _public prototype_ `bool HasAnySimulationMeshData(const int32 LODIndex) const;`
- L58 _private prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L62 _private prototype_ `virtual bool BindToSkeletalMesh(USkeletalMesh* SkeletalMesh, const int32 MeshLodIndex, const int32 SectionIndex, const int32 AssetLodIndex) override;`
- L63 _private prototype_ `virtual void UnbindFromSkeletalMesh(USkeletalMesh* SkeletalMesh, const int32 MeshLodIndexx, const int32 SectionIndex) override;`
- L64 _private prototype_ `virtual void UpdateAllLODBiasMappings(USkeletalMesh* SkeletalMesh) override;`
- L65 _private prototype_ `virtual void GetSimulationMesh(const int32 InMeshLodIndex, TArray<FVector3f>& OutPositions, TArray<uint32>& OutIndices, TArray<float>& OutMaxDistances) const override;`
- L66 _private prototype_ `virtual TArray<TPair<FText, FText>> GetStats() const override;`
- L67 _private prototype_ `virtual USkinnedAsset* GetSkinnedAssetDependency() const override;`
- L69 _private prototype_ `virtual void RefreshBoneMapping(USkeletalMesh* SkeletalMesh) override;`
- L70 _private function_ `virtual bool IsValid() const override`
- L74 _private function_ `virtual void PostUpdateAllAssets() override`
- L78 _private prototype_ `void OnModelChanged();`
- L80 _private prototype_ `FName GetClothSimulationModelName() const;`
- L81 _private prototype_ `FGuid GetClothSimulationModelGuid() const;`
- L85 _private prototype_ `TArray<FString> GetClothSimulationModelIds() const;` — `UFUNCTION(CallInEditor)`
- L89 _private member_ `TObjectPtr<const UChaosClothAssetBase> Asset;` — `UPROPERTY(EditAnywhere, Category = "Chaos Cloth Asset")` — Cloth or Outfit Asset to use with this Skeletal Mesh.
- L97 _private member_ `FString ClothSimulationModelId;` — `UPROPERTY(EditAnywhere, Category = "Chaos Cloth Asset", Meta = (DisplayName = "Cloth Simulation Model", GetOptions = "GetClothSimulationModelIds"))` — The Simulation Model to use for this Clothing Data. Useful for Outfit Assets that may contain multiple models. The name is followed by the model GUID, since it is technically possible to have two pieces of clothing with the same name in an Outfit Asset.
- L101 _private member_ `int32 ClothSimulationModelIndex = INDEX_NONE;` — `UPROPERTY()`
- L103 _private member_ `TSharedPtr<const FChaosClothSimulationModel> TransientSimulationModel;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API CHAOSCLOTHASSETENGINE_API`

### `Plugins/ChaosClothAsset/Source/ChaosClothAssetEngine/Public/ChaosClothAsset/ClothAssetSKMClothingSimulation.h` (Public)


#### class `UE::Chaos::ClothAsset::FSKMClothingSimulationContext`  
`class FSKMClothingSimulationContext final: public IClothingSimulationContext`  
_L31-41_
- inherits: `IClothingSimulationContext`
- desc: Context for the SKM simulation, only used to temporarily store the simulation timestep, the actual simulation context is managed by the simulation proxy.
- L36 _private function_ `FSKMClothingSimulationContext() : IClothingSimulationContext()`
- L37 _private prototype_ `virtual ~FSKMClothingSimulationContext() override = default;`
- L40 _private member_ `float DeltaTime = 0.f;` — Simulation timestep.

#### class `UE::Chaos::ClothAsset::FSKMClothingSimulation`  
`class FSKMClothingSimulation final : public IClothingSimulationInterface , public IClothComponentAdapter , public FGCObject`  
_L44-163_
- inherits: `IClothingSimulationInterface,IClothComponentAdapter,FGCObject`
- desc: Skeletal Mesh simulation class that interfaces between the Skeletal Mesh Component and the Cloth Simulation Proxy.
- L50 _public prototype_ `FSKMClothingSimulation();`
- L54 _public prototype_ `void ResetConfigProperties();` — Reset all cloth simulation config properties to the values stored in the original cloth asset. Game thread only.
- L57 _public prototype_ `void RecreateClothSimulationProxy();` — Hard reset the cloth simulation by recreating the proxy.
- L60 _public prototype_ `UChaosClothAssetInteractor* GetPropertyInteractor(const UChaosClothAssetBase* Asset, int32 ModelIndex) const;` — Return a property interactor for the specified asset and model.
- L63 _public function_ `const ::Chaos::FClothVisualizationNoGC* GetClothVisualization() const` — Return the visualization object for this simulation.
- L71 _private prototype_ `void SetNumIterations(int32 NumIterations);`
- L72 _private prototype_ `void SetMaxNumIterations(int32 MaxNumIterations);`
- L73 _private prototype_ `void SetNumSubsteps(int32 NumSubsteps);`
- L76 _private prototype_ `virtual void Initialize() override;`
- L77 _private prototype_ `virtual void Shutdown() override;`
- L79 _private function_ `virtual IClothingSimulationContext* CreateContext() override`
- L83 _private prototype_ `virtual void FillContextAndPrepareTick(const USkeletalMeshComponent* InComponent, float InDeltaTime, IClothingSimulationContext* InOutContext, bool bIsInitialization, bool bForceTeleportResetOnly) override;`
- L84 _private function_ `virtual void DestroyContext(IClothingSimulationContext* Context) override`
- L89 _private prototype_ `virtual void CreateActor(USkeletalMeshComponent* InOwnerComponent, const UClothingAssetBase* ClothingAsset, int32 SimDataIndex) override;`
- L90 _private prototype_ `virtual void EndCreateActor() override;`
- L91 _private prototype_ `virtual void DestroyActors() override;`
- L93 _private prototype_ `virtual bool ShouldSimulateLOD(int32 OwnerLODIndex) const override;`
- L94 _private prototype_ `virtual void Simulate_AnyThread(const IClothingSimulationContext* Context) override;`
- L95 _private prototype_ `virtual void ForceClothNextUpdateTeleportAndReset_AnyThread() override;`
- L96 _private prototype_ `virtual void HardResetSimulation(const IClothingSimulationContext* InContext) override;`
- L97 _private prototype_ `virtual void AppendSimulationData(TMap<int32, FClothSimulData>& OutData, const USkeletalMeshComponent* OwnerComponent, const USkinnedMeshComponent* OverrideComponent) const override;`
- L99 _private prototype_ `virtual FBoxSphereBounds GetBounds(const USkeletalMeshComponent* OwnerComponent) const override;`
- L101 _private prototype_ `virtual void AddExternalCollisions(const FClothCollisionData& Data) override;`
- L102 _private prototype_ `virtual void ClearExternalCollisions() override;`
- L103 _private function_ `virtual int32 GetNumCloths() const override`
- L104 _private function_ `virtual int32 GetNumKinematicParticles() const override`
- L105 _private function_ `virtual int32 GetNumDynamicParticles() const override`
- L106 _private function_ `virtual int32 GetNumIterations() const override`
- L107 _private function_ `virtual int32 GetNumSubsteps() const override`
- L108 _private function_ `virtual float GetSimulationTime() const override`
- L109 _private function_ `virtual bool IsTeleported() const override`
- L113 _private prototype_ `virtual const USkinnedMeshComponent& GetOwnerComponent() const override;`
- L114 _private function_ `virtual FCollisionSources& GetCollisionSources() const override`
- L118 _private prototype_ `virtual TArray<const UChaosClothAssetBase*> GetAssets() const override;`
- L119 _private prototype_ `virtual TSharedPtr<const FChaosClothSimulationModel> GetActiveClothSimulationModel(const UChaosClothAssetBase* Asset, int32 ModelIndex) const override;`
- L120 _private prototype_ `virtual int32 GetSimulationGroupId(const UChaosClothAssetBase* Asset, int32 ModelIndex) const override;`
- L121 _private prototype_ `virtual int32 GetNextLinkedSimulationGroupId(int32 PrevSimulationGroupId) const override;`
- L122 _private prototype_ `virtual const FReferenceSkeleton* GetReferenceSkeleton() const override;`
- L123 _private prototype_ `virtual EClothingTeleportMode GetClothTeleportMode() const override;`
- L124 _private prototype_ `virtual bool IsSimulationEnabled() const override;`
- L125 _private prototype_ `virtual bool IsSimulationSuspended() const override;`
- L127 _private function_ `virtual bool NeedsResetRestLengths() const override` — TODO: Make this a property interactor function
- L131 _private function_ `virtual const FString& GetRestLengthsMorphTargetName() const override` — TODO: Make this a property interactor function
- L135 _private prototype_ `virtual float GetClothGeometryScale() const override;`
- L136 _private prototype_ `virtual const TArray<TSharedPtr<const FManagedArrayCollection>>& GetPropertyCollections(const UChaosClothAssetBase* Asset, int32 ModelIndex) const override;`
- L137 _private prototype_ `virtual const TArray<TSharedPtr<const FManagedArrayCollection>>& GetSolverPropertyCollections() const override;`
- L138 _private prototype_ `virtual void ClearPropertyCollectionsDirtyFlags(int32 LodIndex) const override;`
- L139 _private prototype_ `virtual bool HasAnySimulationMeshData(int32 LodIndex) const override;`
- L143 _private prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L144 _private prototype_ `virtual FString GetReferencerName() const override;`
- L147 _private prototype_ `const FChaosClothSimulationProperties* GetSolverProperties() const;`
- L148 _private prototype_ `const TArray<TSharedPtr<::Chaos::Softs::FCollectionPropertyFacade>>& GetSolverPropertyFacades() const;`
- L150 _private prototype_ `void CalculateLODHasAnyRenderClothMappingData();`
- L152 _private member_ `USkeletalMeshComponent* OwnerComponent = nullptr;`
- L153 _private member_ `TUniquePtr<FCollisionSources> CollisionSources;`
- L154 _private member_ `TSharedPtr<FClothSimulationProxy> ClothSimulationProxy;`
- L156 _private typedef_ `using FAssetClothSimulationProperties = TPair<const UChaosClothAssetSKMClothingAsset*, FChaosClothSimulationProperties>;`
- L157 _private member_ `TArray<FAssetClothSimulationProperties> AssetClothSimulationProperties;` — Asset properties, matches CreateActor's SimDataIndex, some assets may appear multiple times, some entries might have a null asset
- L159 _private member_ `TBitArray<> LODHasAnyRenderClothMappingData;`
- L161 _private member_ `bool bNeedsResetRestLengths = false;`
- L162 _private member_ `FString RestLengthsMorphTargetName;`

#### class `UChaosClothAssetSKMClothingSimulationFactory`  
`class UChaosClothAssetSKMClothingSimulationFactory final : public UClothingSimulationFactory`  
_L167-206_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UClothingSimulationFactory`
- L172 _public prototype_ `UChaosClothAssetSKMClothingSimulationFactory();`
- L177 _private function_ `virtual IClothingSimulationInterface* CreateSimulation() const override`
- L182 _private function_ `virtual void DestroySimulation(IClothingSimulationInterface* Simulation) const override`
- L187 _private prototype_ `virtual bool SupportsAsset(const UClothingAssetBase* Asset) const override;`
- L189 _private function_ `virtual bool SupportsRuntimeInteraction() const override`
- L194 _private prototype_ `virtual UClothingSimulationInteractor* CreateInteractor() override;`
- L196 _private function_ `virtual TArrayView<const TSubclassOf<UClothConfigBase>> GetClothConfigClasses() const override`
- L201 _private function_ `const UEnum* GetWeightMapTargetEnum() const override`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace Chaos`
- L21 _namespace_ `namespace Softs` (scope `Chaos`)
- L27 _namespace_ `namespace UE`
- L27 _namespace_ `namespace Chaos` (scope `UE`)
- L27 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)

### `Plugins/ChaosClothAsset/Source/ChaosClothAssetEngine/Public/ChaosClothAsset/ClothComponent.h` (Public)


#### struct `FChaosClothSimulationProperties`  
`struct FChaosClothSimulationProperties final`  
_L39-54_
- reflection: `USTRUCT()`
- desc: Private structure that contains all simulation properties runtime elements. These get created per cloth asset/outfit piece when the component is registered.
- L44 _public member_ `TObjectPtr<UChaosClothAssetInteractor> ClothOutfitInteractor;` — `UPROPERTY(Transient)`
- L45 _public member_ `TArray<TSharedPtr<const FManagedArrayCollection>> PropertyCollections;`
- L46 _public member_ `TArray<TSharedPtr<::Chaos::Softs::FCollectionPropertyFacade>> CollectionPropertyFacades;`
- L48 _public prototype_ `FChaosClothSimulationProperties() = default;`
- L49 _public function_ `explicit FChaosClothSimulationProperties(const TArray<TSharedRef<const FManagedArrayCollection>>& AssetPropertyCollections)`
- L53 _public prototype_ `void Initialize(const TArray<TSharedRef<const FManagedArrayCollection>>& AssetPropertyCollections);`

#### struct `FChaosClothComponentEndTickFunction`  
`struct FChaosClothComponentEndTickFunction : public FTickFunction`  
_L58-67_
- reflection: `USTRUCT()`
- inherits: `FTickFunction`
- desc: TG_LastDemotable wait on the parallel cloth task. Mirror of FSkeletalMeshComponentClothEndTickFunction.
- L62 _public member_ `UChaosClothComponent* Target = nullptr;`
- L64 _public prototype_ `virtual void ExecuteTick(float DeltaTime, enum ELevelTick TickType, ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent) override;`
- L65 _public prototype_ `virtual FString DiagnosticMessage() override;`
- L66 _public prototype_ `virtual FName DiagnosticContext(bool bDetailed) override;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FChaosClothComponentEndTickFunction> : public TStructOpsTypeTraitsBase2<FChaosClothComponentEndTickFunction>`  
_L70-76_
- inherits: `TStructOpsTypeTraitsBase2<FChaosClothComponentEndTickFunction>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L73-75_

#### class `UChaosClothComponent`  
`class UChaosClothComponent : public USkinnedMeshComponent , public IDataflowPhysicsSolverInterface , public UE::Chaos::ClothAsset::IClothComponentAdapter`  
_L86-566_
- reflection: `UCLASS(MinimalAPI, ClassGroup = Physics, Meta = (BlueprintSpawnableComponent, ToolTip = "Chaos Cloth Component"), DisplayName = "Chaos Cloth Component", HideCategories = (Object, "Mesh|SkeletalAsset", Constraints, Advanced, Cooking, Collision, Navigation))`
- inherits: `USkinnedMeshComponent,IDataflowPhysicsSolverInterface,UE::Chaos::ClothAsset::IClothComponentAdapter`
- desc: Cloth simulation component.
- L93 _public prototype_ `UChaosClothComponent(const FObjectInitializer& ObjectInitializer);`
- L94 _public prototype_ `UChaosClothComponent(FVTableHelper& Helper);`
- L95 _public prototype_ `~UChaosClothComponent();`
- L99 _public prototype_ `void SetAsset(UChaosClothAssetBase* InAsset);` — `UFUNCTION(BlueprintCallable, Category = "ClothComponent", Meta = (Keywords = "Chaos Cloth Outfit Asset"))` — Set the cloth object used by this component, could be a cloth asset, an outfit asset, or any other type of asset inheriting from UChaosClothAssetBase.
- L103 _public prototype_ `UChaosClothAssetBase* GetAsset() const;` — `UFUNCTION(BlueprintPure, Category = "ClothComponent", Meta = (Keywords = "Chaos Cloth Outfit Asset"))` — Get the cloth object used by this component, could be a cloth asset, an outfit asset, or any other type of asset inheriting from UChaosClothAssetBase.
- L108 _public prototype_ `void SetClothAsset(UChaosClothAsset* InClothAsset);` — `UFUNCTION(BlueprintCallable, Category = "ClothComponent", Meta = (DeprecatedFunction, Keywords = "Chaos Cloth Asset"))` — `UE_DEPRECATED(5.6, "Use SetAsset instead.")` — Set the cloth asset used by this component.
- L113 _public prototype_ `UChaosClothAsset* GetClothAsset() const;` — `UFUNCTION(BlueprintPure, Category = "ClothComponent", Meta = (DeprecatedFunction, Keywords = "Chaos Cloth Asset"))` — `UE_DEPRECATED(5.6, "Use GetAsset instead.")` — Get the cloth asset used by this component.
- L117 _public function_ `void ResetTeleportMode()` — `UFUNCTION(BlueprintCallable, Category = "ClothComponent", Meta = (Keywords = "Chaos Cloth Teleport"))` — Reset the teleport mode.
- L121 _public function_ `void ForceNextUpdateTeleport()` — `UFUNCTION(BlueprintCallable, Category = "ClothComponent", Meta = (Keywords = "Chaos Cloth Teleport"))` — Teleport the cloth particles to the new reference bone location keeping pose and velocities prior to advancing the simulation.
- L125 _public function_ `void ForceNextUpdateTeleportAndReset()` — `UFUNCTION(BlueprintCallable, Category = "ClothComponent", Meta = (Keywords = "Chaos Cloth Teleport Reset"))` — Teleport the cloth particles to the new reference bone location while reseting the pose and velocities prior to advancing the simulation.
- L129 _public function_ `void ResetRestLengthsWithMorphTarget(const FString& MorphTargetName)` — `UFUNCTION(BlueprintCallable, Category = "ClothComponent", Meta = (Keywords = "Chaos Cloth Reset Rest Length Morph Target"))` — Reset the cloth rest lengths with a given morph target (applied to base pose). If MorphTargetName is empty or does not exist, the rest lengths will be reset to default.
- L132 _public function_ `bool NeedsTeleport() const` — Return whether teleport is currently requested. Use GetClothTeleportMode to get teleport mode including any auto-teleport based on teleport thresholds.
- L135 _public function_ `bool NeedsReset() const` — Return whether reseting the pose is currently requested. Use GetClothTeleportMode to get teleport mode including any auto-teleport based on teleport thresholds
- L138 _public function_ `virtual bool NeedsResetRestLengths() const override` — Part of the IClothComponentAdapter implementation.
- L139 _public function_ `virtual const FString& GetRestLengthsMorphTargetName() const override`
- L145 _public function_ `virtual EClothingTeleportMode GetClothTeleportMode() const override` — Get currently calculated teleport mode. Part of the IClothComponentAdapter implementation.
- L149 _public function_ `void SuspendSimulation()` — `UFUNCTION(CallInEditor, BlueprintCallable, Category = "ClothComponent", Meta = (UnsafeDuringActorConstruction, Keywords = "Chaos Cloth Simulation Suspend"))` — Stop the simulation, and keep the cloth in its last pose.
- L153 _public function_ `void ResumeSimulation()` — `UFUNCTION(CallInEditor, BlueprintCallable, Category = "ClothComponent", Meta = (UnsafeDuringActorConstruction, Keywords = "Chaos Cloth Simulation Resume"))` — Resume a previously suspended simulation.
- L160 _public prototype_ `virtual bool IsSimulationSuspended() const override;` — `UFUNCTION(BlueprintCallable, Category = "ClothComponent", Meta = (Keywords = "Chaos Cloth Simulation Suspend"))` — Return whether or not the simulation is currently suspended. Part of the IClothComponentAdapter implementation.
- L164 _public function_ `void SetEnableSimulation(bool bEnable)` — `UFUNCTION(BlueprintCallable, Category = "ClothComponent", Meta = (UnsafeDuringActorConstruction, Keywords = "Chaos Cloth Simulation Enable"))` — Set whether or not to enable simulation.
- L171 _public prototype_ `virtual bool IsSimulationEnabled() const override;` — `UFUNCTION(BlueprintCallable, Category = "ClothComponent", Meta = (Keywords = "Chaos Cloth Simulation Enable"))` — Return whether or not the simulation is currently enabled. Part of the IClothComponentAdapter implementation.
- L175 _public prototype_ `void ResetConfigProperties();` — `UFUNCTION(BlueprintCallable, Category = "ClothComponent", Meta = (Keywords = "Chaos Cloth Config Property"))` — Reset all cloth simulation config properties to the values stored in the original cloth asset.
- L179 _public prototype_ `void RecreateClothSimulationProxy();` — `UFUNCTION(CallInEditor, BlueprintCallable, Category = "ClothComponent", Meta = (DisplayName = "Hard Reset Simulation", Keywords = "Chaos Cloth Recreate Simulation Proxy"))` — Hard reset the cloth simulation by recreating the proxy.
- L190 _public prototype_ `UChaosClothAssetInteractor* GetClothOutfitInteractor(int32 ModelIndex = 0, const FName ClothSimulationModelName = NAME_None);` — `UFUNCTION(BlueprintCallable, Category = "ClothComponent")` — Find the current interactor for the cloth outfit associated with this cloth component. The default parameter values will always find the interactor when the cloth component is using a cloth asset. When using an outfit asset, an interactor from each cloth simulation models can be chosen by specifying either the model index or the model name. The solver properties interactor can also be obtained on model index 0 as it is shared across all models, but only set on the first one. @param ModelIndex The index of the outfit simulation model to retrieve the interactor for. Can be ignored or used as a fallback when seraching by name. Must be 0 for the solver interactor. @param ClothSimulationModelName The name of the outfit model to retrieve the interactor for. Leave it empty to use the ModelIndex instead of when retieving the solver interactor.
- L200 _public prototype_ `void AddCollisionSource(USkinnedMeshComponent* SourceComponent, const UPhysicsAsset* SourcePhysicsAsset, bool bUseSphylsOnly = false);` — `UFUNCTION(BlueprintCallable, Category = "ClothComponent", Meta = (Keywords = "Chaos Cloth Collision Source"))` — Add a collision source for the cloth on this component. Each cloth tick, the collision defined by the physics asset, transformed by the bones in the source component, will be applied to the simulation. @param SourceComponent The component to extract collision transforms from. @param SourcePhysicsAsset The physics asset that defines the collision primitives (that will be transformed by the SourceComponent's bones). @param bUseSphylsOnly Whether to only use spheres and capsules from the collision sources (which is faster and matches the legacy behavior).
- L204 _public prototype_ `void RemoveCollisionSource(const USkinnedMeshComponent* SourceComponent, const UPhysicsAsset* SourcePhysicsAsset);` — `UFUNCTION(BlueprintCallable, Category = "ClothComponent", Meta = (Keywords = "Chaos Cloth Collision Source"))` — Remove a cloth collision source matching the specified component and physics asset,
- L208 _public prototype_ `void RemoveCollisionSources(const USkinnedMeshComponent* SourceComponent);` — `UFUNCTION(BlueprintCallable, Category = "ClothComponent", Meta = (Keywords = "Chaos Cloth Collision Source"))` — Remove all cloth collision sources matching the specified component.
- L212 _public prototype_ `void ResetCollisionSources();` — `UFUNCTION(BlueprintCallable, Category = "ClothComponent", Meta = (Keywords = "Chaos Cloth Collision Source"))` — Remove all cloth collision sources.
- L218 _public function_ `virtual UE::Chaos::ClothAsset::FCollisionSources& GetCollisionSources() const override` — Return all collision sources currently assigned to this component. Part of the IClothComponentAdapter implementation.
- L222 _public prototype_ `void SetCollideWithEnvironment(bool bCollide);` — `UFUNCTION(BlueprintCallable, Category = "ClothComponent", Meta = (Keywords = "Chaos Cloth Collide Environment"))` — Set whether or not to collide with the environment.
- L226 _public function_ `bool GetCollideWithEnvironment() const` — `UFUNCTION(BlueprintCallable, Category = "ClothComponent", Meta = (Keywords = "Chaos Cloth Collide Environment"))` — Set whether or not to collision with the environment is enabled.
- L233 _public prototype_ `void SetSimulateInEditor(const bool bInSimulateInEditor);` — `UFUNCTION(BlueprintCallable, Category = "ClothComponent", meta = (DevelopmentOnly, UnsafeDuringActorConstruction = "true"))` — Sets whether or not to simulate cloth in the editor. This is supported only in the editor
- L237 _public function_ `bool GetSimulateInEditor() const` — Return whether the cloth is set to simulate in the editor.
- L245 _public function_ `const TArray<TSharedPtr<const FManagedArrayCollection>>& GetPropertyCollections(int32 ModelIndex) const` — Return the property collections holding the runtime properties for this cloth component model (one per LOD). This might be different from the cloth asset's since the component's properties can be modified in code or in blueprints. This could also be different from the cloth simulation object until the cloth simulation thread synchronise the properties.
- L253 _public function_ `virtual const TArray<TSharedPtr<const FManagedArrayCollection>>& GetSolverPropertyCollections() const override` — Return the solver property collections. Part of the IClothComponentAdapter implementation.
- L258 _public function_ `const TArray<TSharedPtr<const FManagedArrayCollection>>& GetPropertyCollections() const` — `UE_DEPRECATED(5.6, "Use GetPropertyCollections(int32 ModelIndex) instead.")`
- L263 _public function_ `const UE::Chaos::ClothAsset::FClothSimulationProxy* GetClothSimulationProxy() const`
- L271 _public function_ `virtual float GetClothGeometryScale() const override` — This scale is applied to all cloth geometry (e.g., cloth meshes and collisions) in order to simulate in a different scale space than world. This scale is not applied to distance-based simulation parameters such as MaxDistance. This property is currently only read by the cloth solver when creating cloth actors, but may become animatable in the future. Part of the IClothComponentAdapter implementation.
- L272 _public function_ `void SetClothGeometryScale(float Scale)`
- L280 _public prototype_ `float GetTeleportDistanceThreshold() const;` — `UFUNCTION(BlueprintGetter, Category = ClothComponent)` — Gets the teleportation distance threshold. @return Threshold value.
- L288 _public prototype_ `void SetTeleportDistanceThreshold(float Threshold);` — `UFUNCTION(BlueprintSetter, Category = ClothComponent)` — Sets the teleportation distance threshold. @param threshold Threshold value.
- L296 _public prototype_ `float GetTeleportRotationThreshold() const;` — `UFUNCTION(BlueprintGetter, Category = ClothComponent)` — Gets the teleportation rotation threshold. @return Threshold in degrees.
- L298 _public function_ `void SetBindToLeaderComponent(bool bValue)`
- L303 _public function_ `bool GetBindToLeaderComponent() const`
- L314 _public prototype_ `void SetTeleportRotationThreshold(float Threshold);` — `UFUNCTION(BlueprintSetter, Category = ClothComponent)` — Sets the teleportation rotation threshold. @param threshold Threshold in degrees.
- L317 _public prototype_ `void UpdateConfigProperties();` — Update config properties from the asset. Will only update existing values.
- L320 _public prototype_ `void WaitForExistingParallelClothSimulation_GameThread();` — Stalls on any currently running clothing simulations.
- L324 _public function_ `void SetTickOnceInEditor()` — This will cause the component to tick once in editor. Both flags will be consumed on that tick. Used for the cache adapter.
- L328 _public function_ `UThumbnailInfo* GetThumbnailInfo()`
- L337 _protected prototype_ `virtual void PostLoad() override;`
- L338 _protected prototype_ `virtual void PostDuplicate(bool bDuplicateForPIE) override;`
- L340 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L341 _protected prototype_ `virtual void PostEditImport() override;`
- L342 _protected prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;`
- L347 _protected prototype_ `virtual void OnRegister() override;`
- L348 _protected prototype_ `virtual void OnUnregister() override;`
- L349 _protected prototype_ `virtual void SetComponentTickEnabled(bool bEnabled) override;`
- L350 _protected prototype_ `virtual bool IsComponentTickEnabled() const override;`
- L351 _protected prototype_ `virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;`
- L352 _protected prototype_ `virtual bool RequiresPreEndOfFrameSync() const override;`
- L353 _protected prototype_ `virtual void OnPreEndOfFrameSync() override;`
- L355 _protected prototype_ `virtual TStructOnScope<FActorComponentInstanceData> GetComponentInstanceData() const override;`
- L360 _protected prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;`
- L361 _protected prototype_ `virtual void OnAttachmentChanged() override;`
- L362 _protected prototype_ `virtual bool IsVisible() const override;`
- L366 _protected prototype_ `virtual void RefreshBoneTransforms(FActorComponentTickFunction* TickFunction = nullptr) override;`
- L367 _protected prototype_ `virtual void GetUpdateClothSimulationData_AnyThread(TMap<int32, FClothSimulData>& OutClothSimulData, FMatrix& OutLocalToWorld, float& OutBlendWeight) const override;`
- L368 _protected prototype_ `virtual void SetSkinnedAssetAndUpdate(USkinnedAsset* InSkinnedAsset, bool bReinitPose = true) override;`
- L369 _protected prototype_ `virtual void GetAdditionalRequiredBonesForLeader(int32 LODIndex, TArray<FBoneIndexType>& InOutRequiredBones) const override;`
- L370 _protected prototype_ `virtual void FinalizeBoneTransform() override;`
- L371 _protected prototype_ `virtual FDelegateHandle RegisterOnBoneTransformsFinalizedDelegate(const FOnBoneTransformsFinalizedMultiCast::FDelegate& Delegate) override;`
- L372 _protected prototype_ `virtual void UnregisterOnBoneTransformsFinalizedDelegate(const FDelegateHandle& DelegateHandle) override;`
- L376 _protected function_ `virtual FString GetSimulationName() const override`
- L377 _protected function_ `virtual FDataflowSimulationAsset& GetSimulationAsset() override`
- L378 _protected function_ `virtual const FDataflowSimulationAsset& GetSimulationAsset() const override`
- L379 _protected prototype_ `virtual FDataflowSimulationProxy* GetSimulationProxy() override;`
- L380 _protected prototype_ `virtual const FDataflowSimulationProxy* GetSimulationProxy() const override;`
- L381 _protected prototype_ `virtual void BuildSimulationProxy() override;`
- L382 _protected prototype_ `virtual void ResetSimulationProxy() override;`
- L383 _protected prototype_ `virtual void WriteToSimulation(const float DeltaTime, const bool bAsyncTask) override;`
- L384 _protected prototype_ `virtual void ReadFromSimulation(const float DeltaTime, const bool bAsyncTask) override;`
- L385 _protected prototype_ `virtual void PreProcessSimulation(const float DeltaTime) override;`
- L386 _protected prototype_ `virtual void PostProcessSimulation(const float DeltaTime) override;`
- L390 _protected function_ `virtual const USkinnedMeshComponent& GetOwnerComponent() const override`
- L394 _protected prototype_ `virtual const FReferenceSkeleton* GetReferenceSkeleton() const override;`
- L395 _protected function_ `virtual TArray<const UChaosClothAssetBase*> GetAssets() const override`
- L399 _protected prototype_ `virtual int32 GetSimulationGroupId(const UChaosClothAssetBase* InAsset, int32 ModelIndex) const override;`
- L400 _protected function_ `virtual const TArray<TSharedPtr<const FManagedArrayCollection>>& GetPropertyCollections(const UChaosClothAssetBase* InAsset, int32 ModelIndex) const override`
- L405 _protected prototype_ `virtual void ClearPropertyCollectionsDirtyFlags(int32 LODIndex) const override;`
- L406 _protected prototype_ `virtual bool HasAnySimulationMeshData(int32 LODIndex) const override;`
- L410 _protected prototype_ `virtual TSharedPtr<UE::Chaos::ClothAsset::FClothSimulationProxy> CreateClothSimulationProxy();` — Override this function for setting up custom simulation proxies when the component is registered.
- L413 _private prototype_ `void CreateClothSimulationProxyImpl();`
- L414 _private prototype_ `void StartNewParallelSimulation(float DeltaTime);`
- L415 _private prototype_ `void HandleExistingParallelSimulation();`
- L416 _private prototype_ `bool ShouldWaitForParallelSimulationInTickComponent() const;`
- L417 _private prototype_ `bool ShouldUseEndTickWait() const;`
- L418 _private prototype_ `void UpdateComponentSpaceTransforms();`
- L419 _private prototype_ `void UpdateVisibility();`
- L420 _private prototype_ `void UpdateClothTeleport();`
- L423 _private prototype_ `void RefreshAsset();` — Sync the editor-only Asset alias from the underlying SkinnedAsset.
- L426 _private prototype_ `void RegisterEndTick(bool bRegister);` — Register/unregister the TG_LastDemotable wait tick. Drives registration from the in-tick wait CVar gate.
- L429 _private member_ `FChaosClothComponentEndTickFunction EndTickFunction;` — Tick function that waits on the parallel cloth simulation task in TG_LastDemotable.
- L437 _private member_ `FDataflowSimulationAsset SimulationAsset;` — `UPROPERTY(EditAnywhere, Category = ClothComponent, meta=(EditConditionHides), AdvancedDisplay)` — Solver dataflow asset used to advance in time
- L441 _private member_ `float BlendWeight = 1.f;` — `UPROPERTY(Interp, Category = ClothComponent)` — Blend amount between the skinned (=0) and the simulated pose (=1).
- L447 _private member_ `float ClothGeometryScale = 1.f;` — `UPROPERTY(EditAnywhere, Category = ClothComponent, meta = (UIMin = 0.0, UIMax = 10.0, ClampMin = 0.0, ClampMax = 10000.0))` — This scale is applied to all cloth geometry (e.g., cloth meshes and collisions) in order to simulate in a different scale space than world.This scale is not applied to distance-based simulation parameters such as MaxDistance. This property is currently only read by the cloth solver when creating cloth actors, but may become animatable in the future.
- L451 _private member_ `uint8 bUseAttachedParentAsPoseComponent : 1;` — `UPROPERTY(EditAnywhere, Category = ClothComponent)` — If enabled, and the parent is another Skinned Mesh Component (e.g. another Cloth Component, Poseable Mesh Component, Skeletal Mesh Component, ...etc.), use its pose.
- L455 _private member_ `uint8 bWaitForParallelTask : 1;` — `UPROPERTY(EditAnywhere, Category = ClothComponent)` — Whether to wait for the cloth simulation to end in the TickComponent instead of in the EndOfFrameUpdates.
- L459 _private member_ `uint8 bEnableSimulation : 1;` — `UPROPERTY(Interp, Category = ClothComponent)` — Whether to enable the simulation or use the skinned pose instead.
- L463 _private member_ `uint8 bSuspendSimulation : 1;` — `UPROPERTY(Interp, Category = ClothComponent)` — Whether to suspend the simulation and use the last simulated pose.
- L473 _private member_ `uint8 bBindToLeaderComponent : 1;` — `UPROPERTY(EditAnywhere, Category = ClothComponent)` — Whether to use the leader component simulation result. Currently only supported when using UseAttachedParentAsPoseComponent If this component has a valid LeaderPoseComponent then this makes cloth items on the follower component take the transforms of the cloth items on the leader component instead of simulating separately. @Note The meshes used in the components must be identical for the cloth to bind correctly
- L477 _private member_ `uint8 bTeleport : 1;` — `UPROPERTY(Interp, Category = ClothComponent)` — Whether to teleport the cloth prior to advancing the simulation.
- L481 _private member_ `uint8 bReset : 1;` — `UPROPERTY(Interp, Category = ClothComponent)` — Whether to reset the pose, bTeleport must be true.
- L485 _private member_ `uint8 bCollideWithEnvironment : 1;` — `UPROPERTY(EditAnywhere, Category = ClothComponent)` — Collide with the environment.
- L490 _private member_ `uint8 bSimulateInEditor : 1;` — `UPROPERTY(EditInstanceOnly, Transient, Setter = SetSimulateInEditor, Getter = GetSimulateInEditor, Category = ClothComponent)` — Whether to run the simulation in editor.
- L495 _private member_ `TObjectPtr<UChaosClothAssetBase> Asset;` — `UE_DEPRECATED(5.6, "This property isn't deprecated, but getter and setter must be used at all times to preserve correct operations.")` — `UPROPERTY(EditAnywhere, Transient, Setter = SetAsset, BlueprintSetter = SetAsset, Getter = GetAsset, BlueprintGetter = GetAsset, Category = ClothComponent)` — Asset used by this component. Can be either a cloth asset or an outfit asset.
- L500 _private member_ `TWeakObjectPtr<UChaosClothComponent> LeaderClothComponent;` — `UPROPERTY()` — Cloth leader component used to drive simulation. This may have its own leader component
- L508 _private member_ `float TeleportDistanceThreshold;` — `UPROPERTY(EditAnywhere, BlueprintGetter = GetTeleportDistanceThreshold, BlueprintSetter = SetTeleportDistanceThreshold, Category = ClothComponent)` — Conduct teleportation if the character's movement is greater than this threshold in 1 frame. Zero or negative values will skip the check. You can also do force teleport manually using ForceNextUpdateTeleport() / ForceNextUpdateTeleportAndReset().
- L516 _private member_ `float TeleportRotationThreshold;` — `UPROPERTY(EditAnywhere, BlueprintGetter = GetTeleportRotationThreshold, BlueprintSetter = SetTeleportRotationThreshold, Category = ClothComponent)` — Rotation threshold in degrees, ranging from 0 to 180. Conduct teleportation if the character's rotation is greater than this threshold in 1 frame. Zero or negative values will skip the check.
- L519 _private member_ `float ClothTeleportDistThresholdSquared;` — Used for pre-computation using tTeleportDistanceThreshold property
- L522 _private member_ `float ClothTeleportCosineThresholdInRad;` — Used for pre-computation using TeleportRotationThreshold property
- L525 _private member_ `FMatrix PrevRootBoneMatrix;` — previous root bone matrix to compare the difference and decide to do clothing teleport
- L528 _private member_ `EClothingTeleportMode ClothTeleportMode;` — Currently calculated ClothTeleport based on bTeleport, bReset as well as any teleport calculated based on TeleportDistanceThreshold and TeleportRotationThreshold
- L531 _private member_ `bool bTeleportOnce = false;` — Like bTeleport, but cleared every frame
- L534 _private member_ `bool bResetOnce = false;` — Like bReset, but cleared every frame
- L536 _private member_ `bool bHasValidRenderDataForVisibility = false;`
- L539 _private member_ `bool bResetRestLengthsFromMorphTarget = false;` — Reset restlengths from morph target.
- L540 _private member_ `FString ResetRestLengthsMorphTargetName;`
- L547 _private member_ `TArray<FChaosClothSimulationProperties> ClothSimulationProperties;` — `UPROPERTY(Transient, NonTransactional)` — Simulation properties per cloth model. Transient because it doesn't need to be serialized but contains pointers to UObject that needs not be garbage collected.
- L549 _private member_ `TSharedPtr<UE::Chaos::ClothAsset::FClothSimulationProxy> ClothSimulationProxy;`
- L552 _private member_ `FOnBoneTransformsFinalizedMultiCast OnBoneTransformsFinalizedMC;` — Multicaster fired when this component bone transforms are finalized
- L555 _private member_ `TUniquePtr<UE::Chaos::ClothAsset::FCollisionSources> CollisionSources;` — External sources for collision
- L558 _private member_ `bool bTickOnceInEditor = false;`
- L564 _private member_ `TObjectPtr<UThumbnailInfo> ThumbnailInfo;` — `UPROPERTY(VisibleAnywhere, Instanced, AdvancedDisplay, Category=StaticMesh)` — Information for thumbnail rendering

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API CHAOSCLOTHASSETENGINE_API`
- L13 _namespace_ `namespace Dataflow`
- L22 _namespace_ `namespace Chaos`
- L22 _namespace_ `namespace Softs` (scope `Chaos`)
- L27 _namespace_ `namespace UE`
- L27 _namespace_ `namespace Chaos` (scope `UE`)
- L27 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)
- L74 _enumerator_ `WithCopy = false` (scope `TStructOpsTypeTraits::__anonaf5acb130103`)

### `Plugins/ChaosClothAsset/Source/ChaosClothAssetEngine/Public/ChaosClothAsset/ClothComponentAdapter.h` (Public)


#### class `UE::Chaos::ClothAsset::IClothComponentAdapter`  
`class IClothComponentAdapter`  
_L20-88_
- L27 _public prototype_ `virtual const USkinnedMeshComponent& GetOwnerComponent() const = 0;` — Return the SkinnedMeshComponent owning this adapter. It can be this object pointer or a different owner component if this interface isn't directly implemented on a component.
- L30 _public prototype_ `virtual FCollisionSources& GetCollisionSources() const = 0;` — Return the collision sources to use in cloth simulation proxy.
- L33 _public prototype_ `virtual TArray<const UChaosClothAssetBase*> GetAssets() const = 0;` — Return the list of cloth/outfit assets in use by this adapter.
- L36 _public function_ `virtual TSharedPtr<const FChaosClothSimulationModel> GetActiveClothSimulationModel(const UChaosClothAssetBase* Asset, int32 ModelIndex) const` — Return the cloth simulation model at ModelIndex for Asset.
- L42 _public prototype_ `virtual int32 GetSimulationGroupId(const UChaosClothAssetBase* Asset, int32 ModelId) const = 0;` — Return the index of the model assigned to the render section, or INDEX_NONE when the model shouldn't be simulated.
- L51 _public function_ `virtual int32 GetNextLinkedSimulationGroupId(int32 PrevSimulationGroupId) const` — Return the next SimulationGroupId when multiple group IDs are sharing the same simulated cloth, or INDEX_NONE when SimulationGroupId is the last linked element. Use GetSimulationGroupId() to get the initial ID, and call GetNextLinkedSimulationGroupId() with the previous ID to retrieve the subsequent linked IDs. This function allows for a single simulated cloth to update multiple simulation data slots.
- L54 _public prototype_ `virtual const FReferenceSkeleton* GetReferenceSkeleton() const = 0;` — Return the reference skeleton as passed to the component renderer.
- L57 _public prototype_ `virtual EClothingTeleportMode GetClothTeleportMode() const = 0;` — Return the current teleport mode.
- L60 _public prototype_ `virtual bool IsSimulationEnabled() const = 0;` — Return whether the simulation is currently running.
- L63 _public prototype_ `virtual bool IsSimulationSuspended() const = 0;` — Return whether the simulation is currently suspended.
- L66 _public prototype_ `virtual bool NeedsResetRestLengths() const = 0;` — Return whether the cloth mesh rest lengths needs to be reset.
- L69 _public prototype_ `virtual const FString& GetRestLengthsMorphTargetName() const = 0;` — Return the name of the current morph target.
- L72 _public prototype_ `virtual float GetClothGeometryScale() const = 0;` — Return the scale applied to all cloth geometries (cloth meshes and collisions) in order to simulate in a different scale space.
- L75 _public prototype_ `virtual const TArray<TSharedPtr<const FManagedArrayCollection>>& GetPropertyCollections(const UChaosClothAssetBase* Asset, int32 ModelIndex) const = 0;` — Return the runtime property collections used for modifications of the specified cloth/outfit asset simulation model.
- L78 _public prototype_ `virtual const TArray<TSharedPtr<const FManagedArrayCollection>>& GetSolverPropertyCollections() const = 0;` — Return the runtime solver property collections.
- L81 _public function_ `virtual void ClearPropertyCollectionsDirtyFlags(int32 LodIndex) const` — Clear all property collections dirty flags. This is handled by the simulation proxy once the collections have been copied.
- L84 _public prototype_ `virtual bool HasAnySimulationMeshData(int32 LodIndex) const = 0;` — Return true when any of the simulated assets LOD models have valid simulation data, or false otherwise.
- L87 _protected prototype_ `virtual ~IClothComponentAdapter() = default;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Chaos` (scope `UE`)
- L16 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)

### `Plugins/ChaosClothAsset/Source/ChaosClothAssetEngine/Public/ChaosClothAsset/ClothEngineTools.h` (Public)


#### struct `UE::Chaos::ClothAsset::FClothEngineTools`  
`struct FClothEngineTools`  
_L37-119_
- desc: Tools operating on cloth collections with Engine dependency
- L40 _public prototype_ `static void GenerateTethers(const TSharedRef<FManagedArrayCollection>& ClothCollection, const FName& WeightMap, const bool bGeodesicTethers, const FVector2f& MaxDistanceValue = FVector2f(0.f, 1.f));` — Generate tether data.
- L41 _public prototype_ `static void GenerateTethersFromSelectionSet(const TSharedRef<FManagedArrayCollection>& ClothCollection, const FName& FixedEndSet, const bool bGeodesicTethers);`
- L43 _public prototype_ `static void GenerateTethersFromCustomSelectionSets(const TSharedRef<FManagedArrayCollection>& ClothCollection, const FName& FixedEndSet, const TArray<TPair<FName, FName>>& CustomTetherEndSets, const bool bGeodesicTethers);` — @param CustomTetherEndSets: First element of each pair is DynamicSet, second is FixedSet
- L46 _public prototype_ `static FPointWeightMap GetMaxDistanceWeightMap(const FCollectionClothConstFacade& ClothFacade, const ::Chaos::Softs::FCollectionPropertyConstFacade& PropertyFacade, const int32 NumLodSimVertices);` — Retrieve the MaxDistance weight map from the cloth facades. Return an empty map if the collection doesn't match the requested NumLodSimVertices.
- L48 _public prototype_ `static FPointWeightMap GetMaxDistanceWeightMap(const TSharedRef<const FManagedArrayCollection>& ClothCollection, const int32 NumLodSimVertices);` — Retrieve the MaxDistance weight map from the cloth collection. Return an empty map if the collection doesn't match the requested NumLodSimVertices.
- L51 _public prototype_ `static int32 CalculateReferenceBoneIndex(const TArray<int32>& UsedBones, const FReferenceSkeleton& ReferenceSkeleton);` — Calculate ReferenceBone from bone closest to the root of all used bones
- L53 _public prototype_ `static int32 CalculateReferenceBoneIndex(const TSharedRef<const FManagedArrayCollection>& ClothCollection, const FReferenceSkeleton& ReferenceSkeleton);` — Calculate ReferenceBone from bone closest to the root of all used weighted sim bones in a collection
- L66 _public prototype_ `static bool CalculateRemappedBoneIndicesIfCompatible( const FCollectionClothConstFacade& Cloth1, const FCollectionClothConstFacade& Cloth2, FSoftObjectPath& OutMergedSkeletalMeshPath, TArray<int32>& OutBoneIndicesRemapCloth1, TArray<int32>& OutBoneIndicesRemapCloth2, FText* OutIncompatibleErrorDetails = nullptr);` — Determine if skeletal meshes on two different cloth collections are compatible (one's reference skeleton is a subset of the other). If they are, determine which skeletal mesh is the superset, and calculate remap indices that can be used to remap bone indices from the subset collection to the superset skeletal mesh. @param Cloth1 The cloth facade for the first cloth collection. @param Cloth2 The cloth facade for the second cloth collection. @param OutMergedSkeletalMeshPath The superset skeletal mesh used as reference skeleton, either Cloth1 or Cloth2's skeletal mesh path. @param OutBoneIndicesRemapCloth1 Remap indices to convert Cloth1 BoneIndices to OutMergedSkeletalMeshPath's ref skeleton. Empty if no remapping is required. @param OutBoneIndicesRemapCloth2 Remap indices to convert Cloth2 BoneIndices to OutMergedSkeletalMeshPath's ref skeleton. Empty if no remapping is required. @param OutIncompatibleErrorDetails optional text describing why the skeletal meshes aren't compatible (empty if no error). @return Whether or not the collections are compatible.
- L77 _public prototype_ `static void RemapBoneIndices(FCollectionClothFacade& Cloth, const TArray<int32>& BoneIndicesRemap, const int32 SimVertex3DOffset = 0, const int32 RenderVertexOffset = 0);` — Remap Bone indices for a cloth collection using remap array calculated by CalculateRemappedBoneIndicesIfCompatible. Only vertices beginning with the provided Offsets will be remapped (can be set to non-zero to remap after merging collections)
- L86 _public prototype_ `static TUniquePtr<FSkeletalMeshRenderData> BuildSimPreviewRenderData(const UChaosClothAssetBase& Asset);` — Build a FSkeletalMeshRenderData from the asset's simulation model vertex data. Used for preview rendering (thumbnails) when the asset has no render data. @param Asset The cloth asset base to build preview render data from. @return The built render data, or nullptr if the asset has no valid simulation models.
- L89 _public prototype_ `static UMaterialInterface* GetSimPreviewMaterial();` — Load the default material for sim-model preview rendering (CameraLitDoubleSided).
- L96 _public prototype_ `static int32 CopySimMeshToSimAccessoryMesh(const FName& AccessoryMeshName, FCollectionClothFacade& ToCloth, const FCollectionClothConstFacade& FromCloth, bool bUseSimImportVertexID, FText* OutIncompatibleErrorDetails = nullptr);` — Create a new SimAccessoryMesh by copying the SimMesh data from one collection into another. Optionally use SimImportVertexID to match data rather than a straight copy of SimVertices3D. Any unmatched vertices will copy the data from the existing Sim Mesh. Returns the newly created accessory mesh's index
- L107 _public prototype_ `static TSharedRef<const FManagedArrayCollection> TrimClothCollectionOnCook( const FString& AssetName, const TSharedRef<const FManagedArrayCollection>& ClothCollection, bool bLog);` — Return a cook-trimmed copy of a cloth collection, or the cloth collection itself when trimming is disabled. Falls back to the input collection when p.ClothCollectionOnlyCookRequiredFacades is disabled. @param AssetName Label used when logging the trim result. @param ClothCollection Source collection to trim. @param bLog Pass false to avoid log entries (the cooker calls Serialize twice per package). @return The trimmed collection, or the input collection when trimming is disabled.
- L117 _public prototype_ `static FString GetCookedAssetPath(const FArchive& Ar);` — Return the underlying asset path for a save archive, stripping the PackageHarvester wrapper where necessary. @param Ar Cook save archive to inspect. @return The unwrapped asset path, or Ar.GetArchiveName() unchanged when no wrapper is present.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CHAOSCLOTHASSETENGINE_API`
- L20 _namespace_ `namespace Chaos`
- L22 _namespace_ `namespace Softs` (scope `Chaos`)
- L28 _namespace_ `namespace UE`
- L28 _namespace_ `namespace Chaos` (scope `UE`)
- L28 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)

### `Plugins/ChaosClothAsset/Source/ChaosClothAssetEngine/Public/ChaosClothAsset/ClothLodTransitionDataCache.h` (Public)


#### struct `FChaosClothAssetLodTransitionDataCache`  
`struct FChaosClothAssetLodTransitionDataCache`  
_L9-22_
- reflection: `USTRUCT()`
- L14 _public member_ `FMD5Hash ModelHash;` — Hash of this model. Require valid hash of Up and Down models to be able to re-use the transition data.
- L17 _public member_ `TArray<FMeshToMeshVertData> LODTransitionUpData;` — LOD Transition mesh to mesh skinning weights.
- L18 _public member_ `TArray<FMeshToMeshVertData> LODTransitionDownData;`
- L21 _public prototype_ `bool Serialize(FArchive& Ar);` — Custom serialize for MD5Hash

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FChaosClothAssetLodTransitionDataCache> : public TStructOpsTypeTraitsBase2<FChaosClothAssetLodTransitionDataCache>`  
_L25-31_
- inherits: `TStructOpsTypeTraitsBase2<FChaosClothAssetLodTransitionDataCache>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L28-30_

#### Free symbols / members of external scopes

- L29 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anonca6c6cb80103`)

### `Plugins/ChaosClothAsset/Source/ChaosClothAssetEngine/Public/ChaosClothAsset/ClothSimulationModel.h` (Public)


#### struct `FChaosClothSimulationLodModel`  
`struct FChaosClothSimulationLodModel`  
_L22-85_
- reflection: `USTRUCT()`
- desc: Cloth simulation LOD model. Contains the LOD data as fed to the solver for constraints creation.
- L28 _public member_ `TArray<FVector3f> Positions;` — `UPROPERTY()` — Vertex positions.
- L32 _public member_ `TArray<FVector3f> Normals;` — `UPROPERTY()` — Vertex Normals.
- L36 _public member_ `TArray<uint32> Indices;` — `UPROPERTY()` — Triangles indices.
- L40 _public member_ `TArray<FClothVertBoneData> BoneData;` — `UPROPERTY()` — Skinning weights.
- L44 _public member_ `TArray<uint16> RequiredExtraBoneIndices;` — `UPROPERTY()` — Already remapped using UsedBoneIndices. These are bones that are needed by this LOD for skinning that aren't needed for render.
- L47 _public member_ `TArray<FMeshToMeshVertData> LODTransitionUpData;` — LOD Transition mesh to mesh skinning weights.
- L48 _public member_ `TArray<FMeshToMeshVertData> LODTransitionDownData;`
- L52 _public member_ `TArray<FVector2f> PatternPositions;` — `UPROPERTY()` — 2d pattern positions.
- L56 _public member_ `TArray<uint32> PatternIndices;` — `UPROPERTY()` — Pattern triangle indices. Indexing into PatternPositions.
- L60 _public member_ `TArray<uint32> PatternToWeldedIndices;` — `UPROPERTY()` — Map from PatternsPositions indices to Positions indices.
- L63 _public member_ `TMap<FName, TArray<float>> WeightMaps;` — Weight maps for storing painted attributes modifiers on constraint properties.
- L67 _public member_ `FClothTetherData TetherData;` — `UPROPERTY()` — Tether data
- L70 _public member_ `TMap<FName, TSet<int32>> VertexSets;` — Vertex sets
- L73 _public member_ `TMap<FName, TArray<int32>> FaceIntMaps;` — Face int maps (currently used by cloth collision layers)
- L76 _public member_ `TMap<FName, TSet<int32>> FaceSets;` — Face sets
- L79 _public prototype_ `bool Serialize(FArchive& Ar);` — Custom serialize for weight maps
- L81 _public prototype_ `void GetResourceSizeEx(FResourceSizeEx& CumulativeResourceSize);`
- L84 _public prototype_ `int32 CalcMaxBoneInfluences() const;` — Calculate the maximum number of bone influences used by the skinning weights.

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FChaosClothSimulationLodModel> : public TStructOpsTypeTraitsBase2<FChaosClothSimulationLodModel>`  
_L88-94_
- inherits: `TStructOpsTypeTraitsBase2<FChaosClothSimulationLodModel>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L91-93_

#### struct `FChaosClothSimulationModel`  
`struct FChaosClothSimulationModel`  
_L101-146_
- reflection: `USTRUCT()`
- desc: Cloth simulation model. Contains the LOD models.
- L107 _public member_ `TArray<FChaosClothSimulationLodModel> ClothSimulationLodModels;` — `UPROPERTY()` — LOD data.
- L111 _public member_ `TArray<FName> UsedBoneNames;` — `UPROPERTY()` — List of bones this asset uses from the reference skeleton.
- L115 _public member_ `TArray<int32> UsedBoneIndices;` — `UPROPERTY()` — List of the indices for the bones in UsedBoneNames, used for remapping.
- L119 _public member_ `int32 ReferenceBoneIndex = INDEX_NONE;` — `UPROPERTY()` — Bone to treat as the root of the simulation space.
- L121 _public prototype_ `FChaosClothSimulationModel() = default;`
- L122 _public prototype_ `FChaosClothSimulationModel(const TArray<TSharedRef<const FManagedArrayCollection>>& ClothCollections, const FReferenceSkeleton& ReferenceSkeleton, TArray<FChaosClothAssetLodTransitionDataCache>* InOutTransitionCache = nullptr);`
- L124 _public function_ `int32 GetNumLods() const`
- L126 _public function_ `bool IsValidLodIndex(int32 LodIndex) const`
- L128 _public function_ `int32 GetNumVertices(int32 LodIndex) const`
- L129 _public function_ `int32 GetNumTriangles(int32 LodIndex) const`
- L131 _public function_ `TConstArrayView<FVector3f> GetPositions(int32 LodIndex) const`
- L132 _public function_ `TConstArrayView<FVector2f> GetPatternPositions(int32 LodIndex) const`
- L133 _public function_ `TConstArrayView<FVector3f> GetNormals(int32 LodIndex) const`
- L134 _public function_ `TConstArrayView<uint32> GetIndices(int32 LodIndex) const`
- L135 _public function_ `TConstArrayView<uint32> GetPatternIndices(int32 LodIndex) const`
- L136 _public function_ `TConstArrayView<uint32> GetPatternToWeldedIndices(int32 LodIndex) const`
- L137 _public function_ `TConstArrayView<FClothVertBoneData> GetBoneData(int32 LodIndex) const`
- L138 _public prototype_ `TArray<TConstArrayView<TTuple<int32, int32, float>>> GetTethers(int32 LodIndex) const;`
- L140 _public prototype_ `void CalculateLODTransitionUpDownData(TArray<FChaosClothAssetLodTransitionDataCache>* InOutTransitionCache = nullptr);`
- L142 _public prototype_ `void GetResourceSizeEx(FResourceSizeEx& CumulativeResourceSize);`
- L145 _public prototype_ `void RemapBoneIndices(const TArray<int32>& BoneMap);` — Remap used bones to a new skeleton.

#### Free symbols / members of external scopes

- L92 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anon83d4d8160103`)

### `Plugins/ChaosClothAsset/Source/ChaosClothAssetEngine/Public/ChaosClothAsset/ClothSimulationProxy.h` (Public)


#### class `UE::Chaos::ClothAsset::FClothSimulationProxy`  
`class FClothSimulationProxy : public FDataflowPhysicsSolverProxy`  
_L48-220_
- inherits: `FDataflowPhysicsSolverProxy`
- desc: Cloth simulation proxy. Class used to share data between the cloth simulation and the component.
- L51 _public prototype_ `explicit FClothSimulationProxy(const IClothComponentAdapter& ClothComponentAdapter);`
- L52 _public prototype_ `~FClothSimulationProxy();`
- L54 _public prototype_ `FClothSimulationProxy() = delete;` — This object cannot be created without a valid reference to an owner component
- L55 _public prototype_ `FClothSimulationProxy(const FClothSimulationProxy&) = delete;` — Disable the copy as there must be a single unique proxy per component
- L56 _public prototype_ `FClothSimulationProxy(FClothSimulationProxy&&) = delete;` — Disable the move to force it to be associated with a valid component reference
- L57 _public prototype_ `FClothSimulationProxy& operator=(const FClothSimulationProxy&) = delete;`
- L58 _public prototype_ `FClothSimulationProxy& operator=(FClothSimulationProxy&&) = delete;`
- L60 _public prototype_ `virtual void PostConstructor();`
- L63 _public prototype_ `bool Tick_GameThread(float DeltaTime);` — Start the simulation if it isn't paused or suspended and return true, or simply update the existing simulation data and return false otherwise.
- L66 _public prototype_ `void CompleteParallelSimulation_GameThread();` — Wait for the parallel task to complete if one was running, and update the simulation data.
- L69 _public function_ `bool IsParallelSimulationTaskValid() const` — Returns true if a parallel simulation task has been launched and the simulation data has not been updated, i.e., CompleteParallelSimulation_GameThread will do something.
- L76 _public prototype_ `void PreProcess_GameThread(float DeltaTime, bool bForceWaitForInitialization = false);` — Prepare the proxy before the simulation is setup. For specialized usage when not calling Tick_GameThread. @param bForceWaitForInitialization will ignore the value of p.ChaosClothAsset.WaitForAsyncClothInitialization and force waiting for any in flight initialization, guaranteeing successful preprocessing..
- L78 _public prototype_ `bool PreSimulate_GameThread(float DeltaTime);` — Prepare the simulation data. For specialized usage when not calling Tick_GameThread.
- L84 _public prototype_ `void PostSimulate_GameThread(TMap<int32, FClothSimulData>* OutClothSimulDataOverride = nullptr);` — Write data back onto the game thread once the simulation is done. For specialized usage when not calling Tick_GameThread. @param OutClothSimulDataOverride An optional override to store the resulting simulation data, or nullptr to use the internally owned map insted.
- L90 _public prototype_ `void PostProcess_GameThread(TMap<int32, FClothSimulData>* OutClothSimulDataOverride = nullptr);` — Post setup, required for when the simulation didn't run. For specialized usage when not calling Tick_GameThread. @param OutClothSimulDataOverride An optional override to store the resulting simulation data, or nullptr to use the internally owned map insted.
- L93 _public prototype_ `void ForcePendingReset_GameThread();` — Force a pending cloth reset. For specialized usage when not calling Tick_GameThread.
- L96 _public prototype_ `void HardResetSimulation_GameThread();` — Hard reset the simulation after config changes.
- L103 _public prototype_ `const TMap<int32, FClothSimulData>& GetCurrentSimulationData_AnyThread() const;` — Return a map of all simulation data as used by the skeletal rendering code. The map key is the rendering section's cloth index as set in FSkelMeshRenderSection::CorrespondClothAssetIndex, which is 0 for the entire cloth component since all of its sections share the same simulation data.
- L105 _public prototype_ `FBoxSphereBounds CalculateBounds_AnyThread() const;`
- L107 _public prototype_ `const ::Chaos::FClothVisualizationNoGC* GetClothVisualization() const;`
- L109 _public function_ `int32 GetNumCloths() const`
- L110 _public function_ `int32 GetNumKinematicParticles() const`
- L111 _public function_ `int32 GetNumDynamicParticles() const`
- L112 _public function_ `int32 GetNumIterations() const`
- L113 _public function_ `int32 GetNumSubsteps() const`
- L114 _public function_ `int32 GetNumLinearSolveIterations() const`
- L115 _public function_ `float GetLinearSolveError() const`
- L116 _public function_ `float GetSimulationTime() const`
- L117 _public function_ `bool IsTeleported() const`
- L119 _public function_ `bool HasCacheData() const` — `UE_DEPRECATED(5.6, "CacheData is reset after the context is updated, making this method unreliable.")`
- L122 _protected prototype_ `void PostConstructorInternal(bool bAsyncInitialization);`
- L123 _protected prototype_ `void Tick();`
- L124 _protected prototype_ `void WriteSimulationData(TMap<int32, FClothSimulData>* OutClothSimulDataOverride = nullptr);`
- L125 _protected prototype_ `void InitializeConfigs();`
- L127 _protected prototype_ `void PreProcess_Internal(float DeltaTime);`
- L130 _private prototype_ `void FillSimulationContext(float DeltaTime, bool bIsInitialization = false);`
- L133 _private prototype_ `void BeginInitialization_GameThread();`
- L135 _private prototype_ `void ExecuteInitialization();` — Thread-safe part of Initialization.
- L137 _private prototype_ `void WaitForParallelInitialization_GameThread();` — Wait for any in-flight initialization.
- L139 _private prototype_ `void CompleteInitialization_GameThread();` — Wait for any in-flight initialization and complete the initialization process. Can't be done in parallel.
- L141 _private prototype_ `bool ShouldEnableSolver(bool bSolverCurrentlyEnabled) const;`
- L142 _private prototype_ `void UpdateClothLODs();`
- L145 _private function_ `virtual void AdvanceSolverDatas(const float DeltaTime) override`
- L158 _private member_ `FGraphEventRef ParallelTask;` — Reference for the cloth parallel task, to detect whether or not a simulation is running
- L161 _private member_ `FGraphEventRef ParallelInitializationTask;` — Reference for the cloth async initialization parallel task, to detect whether or not initialization is not complete.
- L164 _private member_ `TMap<int32, FClothSimulData> CurrentSimulationData;` — Simulation data written back to the component after the simulation has taken place
- L167 _private member_ `const IClothComponentAdapter& ClothComponentAdapter;` — Owner component
- L170 _private member_ `TUniquePtr<FClothSimulationContext> ClothSimulationContext;` — Simulation context used to store the required component data for the duration of the simulation
- L173 _private member_ `TUniquePtr<FCollisionSourcesProxy> CollisionSourcesProxy;` — The collision data for the external collision sources
- L176 _private member_ `TArray<TSharedPtr<const FChaosClothSimulationModel>> ClothSimulationModels;` — The cloth simulation model used to create this simulation, ownership might get transferred to this proxy if it changes during the simulation
- L179 _private member_ `TUniquePtr<::Chaos::FClothingSimulationSolver> Solver;` — Simulation objects
- L180 _private member_ `TArray<TUniquePtr<::Chaos::FClothingSimulationMesh>> Meshes;`
- L181 _private member_ `TArray<TUniquePtr<::Chaos::FClothingSimulationCloth>> Cloths;`
- L182 _private member_ `TArray<TUniquePtr<::Chaos::FClothingSimulationConfig>> Configs;`
- L183 _private member_ `TArray<TUniquePtr<::Chaos::FClothingSimulationCollider>> Colliders;`
- L185 _private member_ `TUniquePtr<::Chaos::FClothVisualizationNoGC> Visualization;`
- L197 _private member_ `TUniquePtr<FClothingSimulationCacheData> CacheData;`
- L198 _private member_ `ESolverMode SolverMode = ESolverMode::Default;`
- L201 _private member_ `std::atomic<int32> NumCloths;` — Properties that must be readable from all threads
- L202 _private member_ `std::atomic<int32> NumKinematicParticles;`
- L203 _private member_ `std::atomic<int32> NumDynamicParticles;`
- L204 _private member_ `std::atomic<int32> NumIterations;`
- L205 _private member_ `std::atomic<int32> NumSubsteps;`
- L206 _private member_ `std::atomic<float> SimulationTime;`
- L207 _private member_ `std::atomic<bool> bIsTeleported;`
- L208 _private member_ `std::atomic<int32> LastLinearSolveIterations;` — For single cloth only.
- L209 _private member_ `std::atomic<float> LastLinearSolveError;` — For single cloth only.
- L212 _private member_ `const float MaxDeltaTime;` — Cached value of the MaxPhysicsDeltaTime setting for the life of this proxy
- L214 _private member_ `mutable bool bHasInvalidReferenceBoneTransforms : 1 = false;`
- L215 _private member_ `mutable bool bHasNonMatchingReferenceBones : 1 = false;`
- L216 _private member_ `bool bNeedResetClothFromNanCheck : 1 = false;`
- L217 _private member_ `bool bIsSimulating : 1 = false;` — Whether the proxy has been running the simulation, for internal use only
- L218 _private member_ `bool bIsInitialized : 1 = false;` — Whether the proxy has finished initialization, for internal use only
- L219 _private member_ `bool bIsPreProcessed : 1 = false;` — Whether the proxy was initialized when Tick_GameThread/PreProcess_GameThread was called, for internal use only

#### enum `UE::Chaos::ClothAsset::FClothSimulationProxy::ESolverMode`  
`enum struct ESolverMode : uint8`  
_L191-196_
- desc: Additional data used by the cache adapter
- L193 _public enumerator_ `Default = 0` — Default behavior. Enable solver if no cache data available.
- L194 _public enumerator_ `EnableSolverForSimulateRecord = 1` — Normal simulation. Also used when Recording.
- L195 _public enumerator_ `DisableSolverForPlayback = 2` — Solver is disabled. Used when live playing back cache.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API CHAOSCLOTHASSETENGINE_API`
- L17 _namespace_ `namespace Chaos`
- L23 _namespace_ `namespace Chaos`
- L38 _namespace_ `namespace UE`
- L38 _namespace_ `namespace Chaos` (scope `UE`)
- L38 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)
- L223 _macro_ `#define CHAOS_TRANSFORM_CLOTH_SIMUL_DATA_ISPC_ENABLED_DEFAULT 1`
- L228 _variable_ `static constexpr bool bTransformClothSimulData_ISPC_Enabled = INTEL_ISPC && CHAOS_TRANSFORM_CLOTH_SIMUL_DATA_ISPC_ENABLED_DEFAULT;` (scope `UE::Chaos::ClothAsset`)
- L230 _externvar_ `extern bool bTransformClothSimulData_ISPC_Enabled;` (scope `UE::Chaos::ClothAsset`)

### `Plugins/ChaosClothAsset/Source/ChaosClothAssetEngine/Public/ChaosClothAsset/SkeletalMeshConverterClassProvider.h` (Public)


#### class `UClothAssetSkeletalMeshConverter`  
`class UClothAssetSkeletalMeshConverter : public UObject`  
_L12-20_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UObject`
- desc: Modular base class for skeletal mesh conversion.
- L18 _public prototype_ `virtual bool ExportToSkeletalMesh(const class UChaosClothAssetBase& ClothAssetBase, class USkeletalMesh& SkeletalMesh) const PURE_VIRTUAL(UClothAssetSkeletalMeshConverter::ExportToSkeletalMesh, return false;);` — Build a skeletal mesh from the specified Cloth Asset.

#### class `IClothAssetSkeletalMeshConverterClassProvider`  
`class IClothAssetSkeletalMeshConverterClassProvider : public IModularFeature`  
_L27-33_
- inherits: `IModularFeature`
- desc: A modular interface to provide ways to build a SkeletalMesh from a DynamicMesh, which can be used to build a SkeletalMesh from a ClothCollection. This cannot be done in a non Editor module due to the required dependency being in a Developper folder, and instead is exposed as a modular feature in order to be called from the UChaosClothAssetBase engine class.
- L30 _public member_ `inline static const FName FeatureName = TEXT("ICl`
- L32 _public prototype_ `virtual TSubclassOf<UClothAssetSkeletalMeshConverter> GetClothAssetSkeletalMeshConverter() const = 0;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API CHAOSCLOTHASSETENGINE_API`
