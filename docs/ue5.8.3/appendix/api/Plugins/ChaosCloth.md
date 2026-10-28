# Plugins / ChaosCloth

- module root: `Plugins/ChaosCloth/Source/ChaosCloth`
- headers: 24; symbols: 1372
- symbol kinds: class=19, delegate=5, enum=7, enumerator=47, externvar=5, function=361, macro=12, member=334, namespace=23, prototype=529, struct=19, typedef=6, variable=5
- PublicDependencyModuleNames: Buoyancy, Chaos, ChaosCaching, ClothingSystemRuntimeCommon, ClothingSystemRuntimeInterface, Core, CoreUObject, Engine, Water

### `Plugins/ChaosCloth/Source/ChaosCloth/Private/ChaosCloth/ChaosClothConfigCustomVersion.h` (Private)


#### struct `FChaosClothConfigCustomVersion`  
`struct FChaosClothConfigCustomVersion`  
_L9-36_
- desc: Custom serialization version for cloth config
- L32 _public member_ `const static FGuid GUID;` — The GUID for this custom version number
- L35 _private function_ `FChaosClothConfigCustomVersion()`

#### enum `FChaosClothConfigCustomVersion::Type`  
`enum Type`  
_L11-29_
- L14 _public enumerator_ `BeforeCustomVersionWasAdded = 0` — Before any version changes were made
- L16 _public enumerator_ `UpdateDragDefault = 1` — Update drag default to better preserve legacy behavior
- L18 _public enumerator_ `AddDampingThicknessMigration = 2` — Added damping and collision thickness per cloth
- L20 _public enumerator_ `AddGravitySelfCollisionMigration = 3` — Added gravity and self collision thickness per cloth
- L22 _public enumerator_ `RemoveInternalConfigParameters = 4` — Remove internal config parameters from UI
- L24 _public enumerator_ `AddLegacyBackstopParameter = 5` — Add a parameter to fix the backstop behavior without breaking PhysX assets backward compatibility
- L27 _public enumerator_ `VersionPlusOne` — -----<new versions can be added above this line>-------------------------------------------------
- L28 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

### `Plugins/ChaosCloth/Source/ChaosCloth/Private/ChaosCloth/ChaosClothPrivate.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogChaosCloth, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogChaosCloth, Log, All);`
- L9 _delegate_ `DECLARE_STATS_GROUP(TEXT("ChaosCloth"), STATGROUP_ChaosCloth, STATCAT_`

### `Plugins/ChaosCloth/Source/ChaosCloth/Private/ChaosCloth/ChaosClothSharedConfigCustomVersion.h` (Private)


#### struct `FChaosClothSharedConfigCustomVersion`  
`struct FChaosClothSharedConfigCustomVersion`  
_L9-28_
- desc: Custom serialization version for clothing assets
- L24 _public member_ `const static FGuid GUID;` — The GUID for this custom version number
- L27 _private function_ `FChaosClothSharedConfigCustomVersion()`

#### enum `FChaosClothSharedConfigCustomVersion::Type`  
`enum Type`  
_L11-21_
- L14 _public enumerator_ `BeforeCustomVersionWasAdded = 0` — Before any version changes were made
- L16 _public enumerator_ `AddGravityOverride = 1` — Added gravity override/gravity scale properties
- L19 _public enumerator_ `VersionPlusOne` — -----<new versions can be added above this line>-------------------------------------------------
- L20 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

### `Plugins/ChaosCloth/Source/ChaosCloth/Private/ChaosCloth/ChaosClothingAccessoryMeshData.h` (Private)


#### struct `Chaos::FClothingAccessoryMeshData`  
`struct FClothingAccessoryMeshData`  
_L12-64_
- L14 _public member_ `const int32 NumParticles;`
- L15 _public member_ `const FClothingSimulationAccessoryMesh& AccessoryMesh;`
- L17 _public prototype_ `FClothingAccessoryMeshData( int32 InNumParticles, const FClothingSimulationAccessoryMesh& InAccessoryMesh);`
- L21 _public prototype_ `void AllocateParticles();`
- L22 _public prototype_ `void DeallocateParticles();`
- L23 _public prototype_ `void ResetStartPose();`
- L24 _public prototype_ `void Update(const FClothingSimulationSolver* Solver);`
- L25 _public prototype_ `void ApplyPreSimulationTransforms(const Softs::FSolverVec3& DeltaLocalSpaceLocation, const Softs::FSolverRigidTransform3& GroupSpaceTransform, const Softs::FSolverReal DeltaTime);`
- L26 _public prototype_ `void PreSubstep(const Softs::FSolverReal InterpolationAlpha);`
- L28 _public function_ `const TArray<Softs::FSolverVec3>& GetOldAnimationPositions() const`
- L32 _public function_ `const TArray<Softs::FSolverVec3>& GetAnimationPositions() const`
- L36 _public function_ `const TArray<Softs::FSolverVec3>& GetInterpolatedAnimationPositions() const`
- L40 _public function_ `const TArray<Softs::FSolverVec3>& GetOldAnimationNormals() const`
- L44 _public function_ `const TArray<Softs::FSolverVec3>& GetAnimationNormals() const`
- L48 _public function_ `const TArray<Softs::FSolverVec3>& GetInterpolatedAnimationNormals() const`
- L52 _public function_ `const TArray<Softs::FSolverVec3>& GetAnimationVelocities() const`
- L57 _private member_ `TArray<Softs::FSolverVec3> OldAnimationPositions;`
- L58 _private member_ `TArray<Softs::FSolverVec3> AnimationPositions;`
- L59 _private member_ `TArray<Softs::FSolverVec3> InterpolatedAnimationPositions;`
- L60 _private member_ `TArray<Softs::FSolverVec3> OldAnimationNormals;`
- L61 _private member_ `TArray<Softs::FSolverVec3> AnimationNormals;`
- L62 _private member_ `TArray<Softs::FSolverVec3> InterpolatedAnimationNormals;`
- L63 _private member_ `TArray<Softs::FSolverVec3> AnimationVelocities;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Chaos`

### `Plugins/ChaosCloth/Source/ChaosCloth/Private/ChaosCloth/ChaosWeightMapTarget.h` (Private)


#### enum `EChaosWeightMapTarget`  
`enum class EChaosWeightMapTarget : uint8`  
_L10-36_
- reflection: `UENUM()`
- desc: Targets for painted weight maps (aka masks).
- L12 _public enumerator_ `None = (uint8)EWeightMapTargetCommon::None`
- L13 _public enumerator_ `MaxDistance = (uint8)EWeightMapTargetCommon::MaxDistance`
- L14 _public enumerator_ `BackstopDistance = (uint8)EWeightMapTargetCommon::BackstopDistance`
- L15 _public enumerator_ `BackstopRadius = (uint8)EWeightMapTargetCommon::BackstopRadius`
- L16 _public enumerator_ `AnimDriveStiffness = (uint8)EWeightMapTargetCommon::AnimDriveStiffness`
- L17 _public enumerator_ `TetherEndsMask = (uint8)EWeightMapTargetCommon::TetherEndsMask`
- L20 _public enumerator_ `AnimDriveDamping = (uint8)EWeightMapTargetCommon::AnimDriveDamping_DEPRECATED` — Add Chaos specific maps below this line
- L21 _public enumerator_ `TetherStiffness = (uint8)EWeightMapTargetCommon::FirstUserTarget`
- L22 _public enumerator_ `TetherScale`
- L23 _public enumerator_ `Drag`
- L24 _public enumerator_ `Lift`
- L25 _public enumerator_ `EdgeStiffness`
- L26 _public enumerator_ `BendingStiffness`
- L27 _public enumerator_ `AreaStiffness`
- L28 _public enumerator_ `BucklingStiffness`
- L29 _public enumerator_ `Pressure`
- L30 _public enumerator_ `FlatnessRatio`
- L31 _public enumerator_ `OuterDrag`
- L32 _public enumerator_ `OuterLift`
- L35 _public enumerator_ `MAX UMETA(Hidden)` — Add Chaos specific maps above this line

### `Plugins/ChaosCloth/Source/ChaosCloth/Private/ChaosCloth/SkeletalMeshComponentCacheAdapter.h` (Private)


#### class `Chaos::FSkeletalMeshCacheAdapter`  
`class FSkeletalMeshCacheAdapter : public FComponentCacheAdapter`  
_L14-53_
- inherits: `FComponentCacheAdapter`
- desc: Skeletal mesh cache adapter to be able to cache cloth simulation datas through the chaos cache system
- L18 _public prototype_ `virtual ~FSkeletalMeshCacheAdapter() = default;`
- L21 _public prototype_ `virtual SupportType SupportsComponentClass(UClass* InComponentClass) const override;`
- L22 _public prototype_ `virtual UClass* GetDesiredClass() const override;`
- L23 _public prototype_ `virtual uint8 GetPriority() const override;`
- L24 _public prototype_ `virtual FGuid GetGuid() const override;`
- L25 _public prototype_ `virtual bool ValidForPlayback(UPrimitiveComponent* InComponent, UChaosCache* InCache) const override;`
- L26 _public prototype_ `virtual Chaos::FPhysicsSolver* GetComponentSolver(UPrimitiveComponent* InComponent) const override;`
- L27 _public prototype_ `virtual Chaos::FPhysicsSolverEvents* BuildEventsSolver(UPrimitiveComponent* InComponent) const override;`
- L28 _public prototype_ `virtual void SetRestState(UPrimitiveComponent* InComponent, UChaosCache* InCache, const FTransform& InRootTransform, Chaos::FReal InTime) const override;`
- L29 _public prototype_ `virtual bool InitializeForRecord(UPrimitiveComponent* InComponent, UChaosCache* InCache) override;`
- L30 _public prototype_ `virtual bool InitializeForPlayback(UPrimitiveComponent* InComponent, UChaosCache* InCache, float InTime) override;`
- L31 _public prototype_ `virtual void Record_PostSolve(UPrimitiveComponent* InComp, const FTransform& InRootTransform, FPendingFrameWrite& OutFrame, Chaos::FReal InTime) const override;`
- L32 _public prototype_ `virtual void Playback_PreSolve(UPrimitiveComponent* InComponent, UChaosCache* InCache, Chaos::FReal InTime, FPlaybackTickRecord& TickRecord, TArray<TPBDRigidParticleHandle<Chaos::FReal, 3>*>& OutUpdatedRigids) const override;`
- L37 _public prototype_ `virtual void WaitForSolverTasks(UPrimitiveComponent* InComponent) const override;`
- L46 _private prototype_ `Chaos::FClothingSimulationSolver* GetClothSolver(UPrimitiveComponent* InComponent) const;` — Return the adapter component cloth solver @param InComponent skelmesh component from which the cloth solver will be extracted @return Cloth solver used by the skelmesh component
- L51 _private prototype_ `void InitializeForRestState(UPrimitiveComponent* InComponent) const;` — Initialize the skelmesh adapter when changing the rest state @param InComponent skelmesh component from which the cloth solver will be extracted

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Chaos`

### `Plugins/ChaosCloth/Source/ChaosCloth/Public/ChaosCloth/ChaosClothComplexColliders.h` (Public)


#### class `Chaos::FClothComplexColliders`  
`class FClothComplexColliders final`  
_L18-162_
- L21 _public prototype_ `FClothComplexColliders( Softs::FEvolution* InEvolution, int32 InCollisionRangeId);`
- L25 _public prototype_ `~FClothComplexColliders() = default;`
- L27 _public function_ `int32 GetCollisionRangeId() const`
- L30 _public prototype_ `void SwapBuffersForFrameFlip();` — --- Solver interface ----
- L31 _public prototype_ `void KinematicUpdate(const Softs::FSolverCollisionParticlesRange& Particles, const Softs::FSolverReal Dt, const Softs::FSolverReal Alpha);`
- L32 _public prototype_ `void ApplyPreSimulationTransforms(const Softs::FSolverRigidTransform3& PreSimulationTransform, const Softs::FSolverVec3& DeltaLocalSpaceLocation, const TConstArrayView<Softs::FSolverRigidTransform3>& OldParticleTransforms, const TConstArrayView<Softs::FSolverRigidTransform3>& ParticleTransforms, const Softs::FSolverReal Dt);`
- L34 _public function_ `void SetSkipSkinnedTriangleMeshKinematicUpdate(bool bSkip)`
- L42 _public prototype_ `void Reset();` — ---- Collider interface ---- Warning: changing subbone indices can cause any extracted FPBDComplexColliderBoneData to go stale. You must re-extract after calling these methods.
- L43 _public prototype_ `void AddSubBoneIndices(const TArray<int32>& SubBoneIndices);`
- L45 _public prototype_ `void AddSkinnedLevelSet(int32 Index, const TArray<int32>& MappedSubBones, const FImplicitObjectPtr& SkinnedLevelSet);`
- L46 _public prototype_ `void AddMLLevelSet(int32 Index, const TArray<int32>& MappedSubBones, const FImplicitObjectPtr& MLLevelSet);`
- L47 _public prototype_ `void AddSkinnedTriangleMesh(int32 Index, const TArray<int32>& MappedSubBones, const FImplicitObjectPtr& SkinnedTriangleMesh);`
- L48 _public prototype_ `void Update(const Softs::FSolverTransform3& ComponentToLocalSpace, const TArray<FTransform>& BoneTransforms, const TConstArrayView<Softs::FSolverRigidTransform3>& CollisionRangeTransforms);`
- L49 _public prototype_ `void ResetStartPose();`
- L51 _public function_ `void SetMinLODSize(const Softs::FSolverReal InMinLODSize)`
- L58 _public prototype_ `void ExtractComplexColliderBoneData(TMap<Softs::FParticleRangeIndex, Softs::FPBDComplexColliderBoneData>& Data) const;` — -- Constraints interface ----
- L59 _public function_ `int32 GetNumSkinnedTriangleMeshes() const`
- L63 _public function_ `const FImplicitObjectPtr& GetSkinnedTriangleMesh(int32 Index) const`
- L67 _public function_ `int32 GetSkinnedTriangleMeshIndex(int32 Index) const`
- L71 _public function_ `const TArray<Softs::FSolverVec3>& GetSkinnedTriangleMeshVelocities(int32 Index) const`
- L78 _private member_ `Softs::FEvolution* Evolution;`
- L79 _private member_ `int32 CollisionRangeId;`
- L115 _private member_ `FCollisionSubBones CollisionSubBones;`
- L123 _private member_ `TArray<FSkinnedLevelSetData> SkinnedLevelSets;`
- L131 _private member_ `TArray<FMLLevelSetData> MLLevelSets;`
- L158 _private member_ `TArray<FSkinnedTriangleMeshData> SkinnedTriangleMeshes;`
- L159 _private member_ `bool bSkipSkinnedTriangleMeshKinematicUpdate = false;`
- L160 _private member_ `Softs::FSolverReal MinLODSize = 0.f;`

#### struct `Chaos::FClothComplexColliders::FCollisionSubBones`  
`struct FCollisionSubBones : public TArrayCollection`  
_L81-114_
- inherits: `TArrayCollection`
- L83 _public function_ `FCollisionSubBones()`
- L95 _public function_ `void Reset()`
- L100 _public function_ `void AddSubBones(int32 Num)`
- L106 _public member_ `TArrayCollectionArray<int32> BoneIndices;`
- L107 _public member_ `TArrayCollectionArray<Softs::FSolverRigidTransform3> BaseTransforms;`
- L108 _public member_ `TArrayCollectionArray<Softs::FSolverRigidTransform3> OldTransforms;`
- L109 _public member_ `TArrayCollectionArray<Softs::FSolverRigidTransform3> Transforms;`
- L110 _public member_ `TArrayCollectionArray<Softs::FSolverVec3> X;`
- L111 _public member_ `TArrayCollectionArray<Softs::FSolverVec3> V;`
- L112 _public member_ `TArrayCollectionArray<Softs::FSolverRotation3> R;`
- L113 _public member_ `TArrayCollectionArray<Softs::FSolverVec3> W;`

#### struct `Chaos::FClothComplexColliders::FSkinnedLevelSetData`  
`struct FSkinnedLevelSetData`  
_L117-122_
- L119 _public member_ `int32 Index;`
- L120 _public member_ `TArray<int32> MappedSubBones;`
- L121 _public member_ `FImplicitObjectPtr SkinnedLevelSet;`

#### struct `Chaos::FClothComplexColliders::FMLLevelSetData`  
`struct FMLLevelSetData`  
_L125-130_
- L127 _public member_ `int32 Index;`
- L128 _public member_ `TArray<int32> MappedSubBones;`
- L129 _public member_ `FImplicitObjectPtr MLLevelSet;`

#### struct `Chaos::FClothComplexColliders::FSkinnedTriangleMeshData`  
`struct FSkinnedTriangleMeshData`  
_L133-157_
- L135 _public member_ `int32 Index;`
- L136 _public member_ `TArray<int32> MappedSubBones;`
- L137 _public member_ `FImplicitObjectPtr SkinnedTriangleMesh;` — Note: SkinnedTriangleMesh LocalPositions will be in solver/particle space, not collision space.
- L156 _public member_ `} SkinnedPositions;` — Interpolated positions are on the SkinnedTriangleMesh

#### struct `Chaos::FClothComplexColliders::FSkinnedTriangleMeshData::FSkinnedPositions`  
`struct FSkinnedPositions : public TArrayCollection`  
_L138-156_
- inherits: `TArrayCollection`
- L140 _public function_ `FSkinnedPositions()`
- L147 _public function_ `void SetNum(int32 Num)`
- L152 _public member_ `TArrayCollectionArray<Softs::FSolverVec3> OldPositions;`
- L153 _public member_ `TArrayCollectionArray<Softs::FSolverVec3> Positions;`
- L154 _public member_ `TArrayCollectionArray<Softs::FSolverVec3> SolverSpaceVelocities;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Chaos`
- L12 _namespace_ `namespace Softs` (scope `Chaos`)

### `Plugins/ChaosCloth/Source/ChaosCloth/Public/ChaosCloth/ChaosClothConfig.h` (Public)


#### struct `FChaosClothWeightedValue`  
`struct FChaosClothWeightedValue`  
_L12-35_
- reflection: `USTRUCT()`
- L24 _public member_ `float Low = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Weighted Value", Meta = (DisplayName = "Low Weight", ChaosClothShortName = "Lo"))` — Parameter value corresponding to the lower bound of the Weight Map. A Weight Map stores a series of Weight values assigned to each point, all between 0 and 1. The weights are used to interpolate the individual values from Low to High assigned to each different point. A Weight of 0 always corresponds to the Low parameter value, and a Weight of 1 to the High parameter value. The value for Low can be set to be bigger than for High in order to reverse the effect of the Weight Map.
- L34 _public member_ `float High = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Weighted Value", Meta = (DisplayName = "High Weight", ChaosClothShortName = "Hi"))` — Parameter value corresponding to the upper bound of the Weight Map. A Weight Map stores a series of Weight values assigned to each point, all between 0 and 1. The weights are used to interpolate the individual values from Low to High assigned to each different point. A Weight of 0 always corresponds to the Low parameter value, and a Weight of 1 to the High parameter value. The value for Low can be set to be bigger than for High in order to reverse the effect of the Weight Map.

#### enum `EChaosClothTetherMode`  
`enum class EChaosClothTetherMode : uint8`  
_L42-51_
- reflection: `UENUM()`
- desc: Long range attachment options. Deprecated.
- L45 _public enumerator_ `FastTetherFastLength` — Fast Tether Fast Length: Use fast euclidean methods to both setup the tethers and calculate their lengths. Fast initialization and simulation times, but is very prone to artifacts.
- L47 _public enumerator_ `AccurateTetherFastLength` — Accurate Tether Fast Length: Use the accurate geodesic method to setup the tethers and a fast euclidean method to calculate their lengths. Slow initialization times and fast simulation times, but can still be prone to artifacts.
- L49 _public enumerator_ `AccurateTetherAccurateLength UMETA(Hidden)` — Accurate Tether Accurate Length: Use accurate geodesic method to both setup the tethers and calculate their lengths. Slow initialization and simulation times, but this is the most accurate setting showing the less artifacts.
- L50 _public enumerator_ `MaxChaosClothTetherMode UMETA(Hidden)`

#### class `UChaosClothConfig`  
`class UChaosClothConfig : public UClothConfigCommon`  
_L56-537_
- reflection: `UCLASS(HideCategories = (Collision), MinimalAPI)`
- inherits: `UClothConfigCommon`
- desc: Hiding categories that will be used in the future
- L60 _public prototype_ `UChaosClothConfig();`
- L64 _public prototype_ `virtual void MigrateFrom(const FClothConfig_Legacy&) override;` — Migrate from the legacy FClothConfig structure.
- L67 _public prototype_ `virtual void MigrateFrom(const UClothSharedConfigCommon* ClothSharedConfig) override;` — Migrate from shared config.
- L70 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — Serialize override used to set the current custom version.
- L73 _public prototype_ `virtual void PostLoad() override;` — PostLoad override used to deal with updates/changes in properties.
- L75 _public function_ `virtual bool NeedsSelfCollisionData() const override`
- L78 _public function_ `virtual bool NeedsInverseMasses() const override` — Return wherether to pre-compute Inverse Masses.
- L81 _public function_ `virtual bool NeedsTethers() const override` — Return wherether to pre-compute the Long Range Attachment tethers.
- L84 _public function_ `virtual float GetSelfCollisionRadius() const override` — Return the self collision radius to precomute self collision data.
- L87 _public function_ `virtual bool TethersUseGeodesicDistance() const override` — Return whether tethers need to be calculated using geodesic distances instead of eclidean.
- L90 _public prototype_ `float GetMassValue() const;` — Return the mass value, from whichever mass mode (Density, UniformMass, or TotalMass) is selected.
- L99 _public member_ `EClothMassMode MassMode = EClothMassMode::Density;` — `UPROPERTY(EditAnywhere, Category = "Mass Properties")` — How cloth particle mass is determined -	Uniform Mass: Every particle's mass will be set to the value specified in the UniformMass setting. Mostly to avoid as it can cause some serious issues with irregular tessellations. -	Total Mass: The total mass is distributed equally over all the particles. Useful when referencing a specific garment size and feel. -	Density: A constant mass density is used. Density is usually the preferred way of setting mass since it allows matching real life materials' density values.
- L103 _public member_ `float UniformMass = 0.00015f;` — `UPROPERTY(EditAnywhere, Category = "Mass Properties", meta = (UIMin = "0.000001", UIMax = "0.001", ClampMin = "0", EditCondition = "MassMode == EClothMassMode::UniformMass"))` — The value used when the Mass Mode is set to Uniform Mass.
- L107 _public member_ `float TotalMass = 0.5f;` — `UPROPERTY(EditAnywhere, Category = "Mass Properties", meta = (UIMin = "0.001", UIMax = "10", ClampMin = "0", EditCondition = "MassMode == EClothMassMode::TotalMass"))` — The value used when Mass Mode is set to TotalMass.
- L120 _public member_ `float Density = 0.35f;` — `UPROPERTY(EditAnywhere, Category = "Mass Properties", meta = (UIMin = "0.001", UIMax = "1", ClampMin = "0", EditCondition = "MassMode == EClothMassMode::Density"))` — The value used when Mass Mode is set to Density. Melton Wool: 0.7 Heavy leather: 0.6 Polyurethane: 0.5 Denim: 0.4 Light leather: 0.3 Cotton: 0.2 Silk: 0.1
- L124 _public member_ `float MinPerParticleMass = 0.0001f;` — `UPROPERTY()` — This is a lower bound to cloth particle masses.
- L133 _public member_ `FChaosClothWeightedValue EdgeStiffnessWeighted = { 1.f, 1.f };` — `UPROPERTY(EditAnywhere, Category = "Material Properties", DisplayName = "Edge Stiffness", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))` — The Stiffness of segments constraints. Increase the iteration count for stiffer materials. If an enabled Weight Map (Mask with values in the range [0;1]) targeting the "Edge Stiffness" is added to the cloth, then both the Low and High values will be used in conjunction with the per particle Weight stored in the Weight Map to interpolate the final value from them. Otherwise only the Low value is meaningful and sufficient to enable this constraint.
- L142 _public member_ `FChaosClothWeightedValue BendingStiffnessWeighted = { 1.f, 1.f };` — `UPROPERTY(EditAnywhere, Category = "Material Properties", DisplayName = "Bending Stiffness", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))` — The Stiffness of cross segments and bending elements constraints. Increase the iteration count for stiffer materials. If an enabled Weight Map (Mask with values in the range [0;1]) targeting the "Bend Stiffness" is added to the cloth, then both the Low and High values will be used in conjunction with the per particle Weight stored in the Weight Map to interpolate the final value from them. Otherwise only the Low value is meaningful and sufficient to enable this constraint.
- L146 _public member_ `bool bUseBendingElements = false;` — `UPROPERTY(EditAnywhere, Category = "Material Properties")` — Enable the more accurate bending element constraints instead of the faster cross-edge spring constraints used for controlling bending stiffness.
- L153 _public member_ `float BucklingRatio = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Material Properties", DisplayName = "Buckling Ratio", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1", EditCondition = "bUseBendingElements"))` — Once the element has bent such that it's folded more than this ratio from its rest angle ("buckled"), switch to using Buckling Stiffness instead of Bending Stiffness. When Buckling Ratio = 0, the Buckling Stiffness will never be used. When BucklingRatio = 1, the Buckling Stiffness will be used as soon as its bent past its rest configuration.
- L163 _public member_ `FChaosClothWeightedValue BucklingStiffnessWeighted = { 1.f, 1.f };` — `UPROPERTY(EditAnywhere, Category = "Material Properties", DisplayName = "Buckling Stiffness", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1", EditCondition = "bUseBendingElements"))` — Bending will use this stiffness instead of Bending Stiffness once the cloth has buckled, i.e., bent beyond a certain angle. Typically, Buckling Stiffness is set to be less than Bending Stiffness. Buckling Ratio determines the switch point between using Bending Stiffness and Buckling Stiffness. If an enabled Weight Map (Mask with values in the range [0;1]) targeting the "Buckling Stiffness" is added to the cloth, then both the Low and High values will be used in conjunction with the per particle Weight stored in the Weight Map to interpolate the final value from them. Otherwise only the Low value is meaningful and sufficient to enable this constraint.
- L174 _public member_ `FChaosClothWeightedValue FlatnessRatio = { 0.f, 1.f };` — `UPROPERTY(EditAnywhere, Category = "Material Properties", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1", EditCondition = "bUseBendingElements"))` — Calculate rest angles as a ratio between completely flat and whatever is the 3D rest angle. When FlatnessRatio = 0, the rest angle will match the input mesh.. When FlatnessRatio = 1, the rest angle will be 0 (completely flat). If an enabled Weight Map (Mask with values in the range [0;1]) targeting the "Flatness Ratio" is added to the cloth, then both the Low and High values will be used in conjunction with the per particle Weight stored in the Weight Map to interpolate the final value from them. Otherwise only the Low value is meaningful and sufficient to enable this constraint.
- L183 _public member_ `FChaosClothWeightedValue AreaStiffnessWeighted = { 1.f, 1.f };` — `UPROPERTY(EditAnywhere, Category = "Material Properties", DisplayName = "Area Stiffness", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))` — The stiffness of the surface area preservation constraints. Increase the iteration count for stiffer materials. If an enabled Weight Map (Mask with values in the range [0;1]) targeting the "Bend Stiffness" is added to the cloth, then both the Low and High values will be used in conjunction with the per particle Weight stored in the Weight Map to interpolate the final value from them. Otherwise only the Low value is meaningful and sufficient to enable this constraint.
- L187 _public member_ `float VolumeStiffness = 0.f;` — `UPROPERTY()` — The stiffness of the volume preservation constraints.
- L201 _public member_ `FChaosClothWeightedValue TetherStiffness = { 1.f, 1.f };` — `UPROPERTY(EditAnywhere, Category = "Long Range Attachment", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))` — The tethers' stiffness of the long range attachment constraints. The long range attachment connects each of the cloth particles to its closest fixed point with a spring constraint. This can be used to compensate for a lack of stretch resistance when the iterations count is kept low for performance reasons. Can lead to an unnatural pull string puppet like behavior. If an enabled Weight Map (Mask with values in the range [0;1]) targeting the "Tether Stiffness" is added to the cloth, then both the Low and High values will be used in conjunction with the per particle Weight stored in the Weight Map to interpolate the final value from them. Otherwise only the Low value is meaningful and sufficient to enable this constraint. Use 0, 0 to disable.
- L211 _public member_ `FChaosClothWeightedValue TetherScale = { 1.f, 1.f };` — `UPROPERTY(EditAnywhere, Category = "Long Range Attachment", meta = (UIMin = "1.", UIMax = "1.1", ClampMin = "0.01", ClampMax = "10"))` — The limit scale of the long range attachment constraints (aka tether limit). If an enabled Weight Map (Mask with values in the range [0;1]) targeting the "Tether Scale" is added to the cloth, then both the Low and High values will be used in conjunction with the per particle Weight stored in the Weight Map to interpolate the final value from them. Otherwise only the Low value is meaningful and sufficient to set the tethers' scale.
- L219 _public member_ `bool bUseGeodesicDistance = true;` — `UPROPERTY(EditAnywhere, Category = "Long Range Attachment")` — Use geodesic instead of euclidean distance calculations for the Long Range Attachment constraint, which is slower at setup but more accurate at establishing the correct position and length of the tethers, and therefore is less prone to artifacts during the simulation.
- L223 _public member_ `float ShapeTargetStiffness = 0.f;` — `UPROPERTY()` — The stiffness of the shape target constraints.
- L227 _public member_ `float CollisionThickness = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Collision Properties", meta = (UIMin = "0", UIMax = "100", ClampMin = "0", ClampMax = "1000"))` — The added thickness of collision shapes.
- L231 _public member_ `float FrictionCoefficient = 0.8f;` — `UPROPERTY(EditAnywhere, Category = "Collision Properties", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "10"))` — Friction coefficient for cloth - collider interaction.
- L238 _public member_ `bool bUseCCD = false;` — `UPROPERTY(EditAnywhere, Category = "Collision Properties")` — Use continuous collision detection (CCD) to prevent any missed collisions between fast moving particles and colliders. This has a negative effect on performance compared to when resolving collision without using CCD.
- L242 _public member_ `bool bUseSelfCollisions = false;` — `UPROPERTY(EditAnywhere, Category = "Collision Properties")` — Enable self collision repulsion forces (point-face).
- L246 _public member_ `float SelfCollisionThickness = 2.0f;` — `UPROPERTY(EditAnywhere, Category = "Collision Properties", meta = (UIMin = "0", UIMax = "100", ClampMin = "0", ClampMax = "1000", EditCondition = "bUseSelfCollisions"))` — The radius of the spheres used in self collision. (i.e., offset per side. total thickness of cloth is 2x this value)
- L250 _public member_ `float SelfCollisionFriction = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Collision Properties", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "10", EditCondition = "bUseSelfCollisions"))` — Friction coefficient for cloth - cloth interaction.
- L254 _public member_ `bool bUseSelfIntersections = false;` — `UPROPERTY(EditAnywhere, Category = "Collision Properties", meta = (EditCondition = "bUseSelfCollisions"))` — Enable self intersection resolution. This will try to fix any cloth intersections that are not handled by collision repulsions.
- L258 _public member_ `bool bUseSelfCollisionSpheres = false;` — `UPROPERTY(EditAnywhere, Category = "Collision Properties",meta = (EditCondition = "!bUseSelfCollisions"))` — Enable sphere-based self collision repulsion forces.
- L262 _public member_ `float SelfCollisionSphereRadius = 0.5f;` — `UPROPERTY(EditAnywhere, Category = "Collision Properties", meta = (EditCondition = "!bUseSelfCollisions && bUseSelfCollisionSpheres", UIMin = "0", UIMax = "100", ClampMin = "0", ClampMax = "1000"))` — The radius of the spheres used in self collision centered at each vertex.
- L266 _public member_ `float SelfCollisionSphereStiffness = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Collision Properties", meta = (EditCondition = "!bUseSelfCollisions && bUseSelfCollisionSpheres", UIMin = "0", UIMax = "100", ClampMin = "0", ClampMax = "1000"))` — The stiffness of the springs used to control self collision.
- L273 _public member_ `float SelfCollisionSphereRadiusCullMultiplier = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Collision Properties", meta = (EditCondition = "!bUseSelfCollisions && bUseSelfCollisionSpheres", ClampMin = "1"))` — Multiplier for culling the self collision spheres. Spheres are seeded on every vertex, and culled based on SelfCollisionSphereRadius * SelfCollisionSphereRadiusCullMultiplier.
- L282 _public member_ `bool bUseLegacyBackstop = false;` — `UPROPERTY(EditAnywhere, Category = "Collision Properties")` — This parameter is automatically set by the migration code. It can be overridden here to use the old way of authoring the backstop distances. The legacy backstop requires the sphere radius to be included within the painted distance mask, making it difficult to author correctly. In this case the backstop distance is the distance from the animated mesh to the center of the corresponding backstop collision sphere. The non legacy backstop automatically adds the matching sphere's radius to the distance calculations at runtime to make for a simpler authoring of the backstop distances. In this case the backstop distance is the distance from the animated mesh to the surface of the backstop collision sphere. In both cases, a positive backstop distance goes against the corresponding animated mesh's normal, and a negative backstop distance goes along the corresponding animated mesh's normal.
- L289 _public member_ `float DampingCoefficient = 0.01f;` — `UPROPERTY(EditAnywhere, Category = "Environmental Properties", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))` — The amount of global damping applied to the cloth velocities, also known as point damping. Point damping improves simulation stability, but can also cause an overall slow-down effect and therefore is best left to very small percentage amounts.
- L298 _public member_ `float LocalDampingCoefficient = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Environmental Properties", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))` — The amount of local damping applied to the cloth velocities. This type of damping only damps individual deviations of the particles velocities from the global motion. It makes the cloth deformations more cohesive and reduces jitter without affecting the overall movement. It can also produce synchronization artifacts where part of the cloth mesh are disconnected (which might well be desirable, or not), and is more expensive than global damping.
- L306 _public member_ `bool bUsePointBasedWindModel = false;` — `UPROPERTY(EditAnywhere, Category = "Environmental Properties")` — This parameter is automatically set by the migration code. It can be overridden here to use the old deprecated "Legacy" wind model in order to preserve behavior with previous versions of the engine. The old wind model is not an accurate aerodynamic model and as such should be avoided. Being point based, it doesn't take into account the surface area that gets hit by the wind. Using this model makes the simulation slightly slower, disables the aerodynamically accurate wind model, and prevents the cloth to interact with the surrounding environment (air, water, ...etc.) even when there is no wind.
- L318 _public member_ `FChaosClothWeightedValue Drag = { 0.035f, 1.f };` — `UPROPERTY(EditAnywhere, Category = "Environmental Properties", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "10", EditCondition = "!bUsePointBasedWindModel"))` — The aerodynamic coefficient of drag applying on each particle. When "Outer Drag" is enabled, this acts as the "Inner Drag", i.e., drag applied when the air velocity is moving in the mesh normal direction. If an enabled Weight Map (Mask with values in the range [0;1]) targeting the "Drag" is added to the cloth, then both the Low and High values will be used in conjunction with the per particle Weight stored in the Weight Map to interpolate the final value from them. Otherwise only the Low value is meaningful and sufficient to set the aerodynamic drag.
- L321 _public member_ `bool bEnableOuterDrag = false;` — `UPROPERTY(EditAnywhere, Category = "Environmental Properties", meta = (InlineEditConditionToggle))`
- L332 _public member_ `FChaosClothWeightedValue OuterDrag = { 0.035f, 1.f };` — `UPROPERTY(EditAnywhere, Category = "Environmental Properties", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "10", EditCondition = "bEnableOuterDrag"))` — The aerodynamic coefficient of drag applying on each particle when the air velocity is moving against the mesh normal direction. If an enabled Weight Map (Mask with values in the range [0;1]) targeting the "Outer Drag" is added to the cloth, then both the Low and High values will be used in conjunction with the per particle Weight stored in the Weight Map to interpolate the final value from them. Otherwise only the Low value is meaningful and sufficient to set the aerodynamic drag.
- L344 _public member_ `FChaosClothWeightedValue Lift = { 0.035f, 1.f };` — `UPROPERTY(EditAnywhere, Category = "Environmental Properties", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "10", EditCondition = "!bUsePointBasedWindModel"))` — The aerodynamic coefficient of lift applying on each particle. When "Outer Lift" is enabled, this acts as the "Inner lift", i.e., lift applied when the air velocity is moving in the mesh normal direction. If an enabled Weight Map (Mask with values in the range [0;1]) targeting the "Lift" is added to the cloth, then both the Low and High values will be used in conjunction with the per particle Weight stored in the Weight Map to interpolate the final value from them. Otherwise only the Low value is meaningful and sufficient to set the aerodynamic lift.
- L347 _public member_ `bool bEnableOuterLift = false;` — `UPROPERTY(EditAnywhere, Category = "Environmental Properties", meta = (InlineEditConditionToggle))`
- L358 _public member_ `FChaosClothWeightedValue OuterLift = { 0.035f, 1.f };` — `UPROPERTY(EditAnywhere, Category = "Environmental Properties", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "10", EditCondition = "bEnableOuterLift"))` — The aerodynamic coefficient of lift applying on each particle when the air velocity is moving against the mesh normal direction. If an enabled Weight Map (Mask with values in the range [0;1]) targeting the "Outer Lift" is added to the cloth, then both the Low and High values will be used in conjunction with the per particle Weight stored in the Weight Map to interpolate the final value from them. Otherwise only the Low value is meaningful and sufficient to set the aerodynamic lift.
- L362 _public member_ `bool bUseGravityOverride = false;` — `UPROPERTY(EditAnywhere, Category = "Environmental Properties", meta = (InlineEditConditionToggle))` — Use the config gravity value instead of world gravity.
- L366 _public member_ `float GravityScale = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Environmental Properties")` — Scale factor applied to the world gravity and also to the clothing simulation interactor gravity. Does not affect the gravity if set using the override below.
- L370 _public member_ `FVector Gravity = { 0.f, 0.f, -980.665f };` — `UPROPERTY(EditAnywhere, Category = "Environmental Properties", meta = (EditCondition = "bUseGravityOverride"))` — The gravitational acceleration vector [cm/s^2]
- L380 _public member_ `FChaosClothWeightedValue Pressure = { 0.0f, 1.f };` — `UPROPERTY(EditAnywhere, Category = "Environmental Properties", meta = (UIMin = "-10", UIMax = "10", ClampMin = "-100", ClampMax = "100"))` — Pressure force strength applied in the normal direction(use negative value to push toward backface) If an enabled Weight Map (Mask with values in the range [0;1]) targeting the "Pressure" is added to the cloth, then both the Low and High values will be used in conjunction with the per particle Weight stored in the Weight Map to interpolate the final value from them. Otherwise only the Low value is meaningful and sufficient to set the pressure.
- L390 _public member_ `FChaosClothWeightedValue AnimDriveStiffness = { 0.f, 1.f };` — `UPROPERTY(EditAnywhere, Category = "Animation Properties", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))` — The strength of the constraint driving the cloth towards the animated goal mesh. If an enabled Weight Map (Mask with values in the range [0;1]) targeting the "Anim Drive Stiffness" is added to the cloth, then both the Low and High values will be used in conjunction with the per particle Weight stored in the Weight Map to interpolate the final value from them. Otherwise only the Low value is meaningful and sufficient to enable this constraint.
- L400 _public member_ `FChaosClothWeightedValue AnimDriveDamping = { 0.f, 1.f };` — `UPROPERTY(EditAnywhere, Category = "Animation Properties", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))` — The damping amount of the anim drive. If an enabled Weight Map (Mask with values in the range [0;1]) targeting the "Anim Drive Damping" is added to the cloth, then both the Low and High values will be used in conjunction with the per particle Weight stored in the Weight Map to interpolate the final value from them. Otherwise only the Low value is sufficient to work on this constraint.
- L407 _public member_ `EChaosSoftsSimulationSpace VelocityScaleSpace = EChaosSoftsSimulationSpace::ReferenceBoneSpace;` — `UPROPERTY(EditAnywhere, Category = "Animation Properties")` — All vector properties in this section (e.g., Linear Velocity Scale, Max Linear Acceleration) will be evaluated in this space.
- L413 _public member_ `FVector LinearVelocityScale = { 0.75f, 0.75f, 0.75f };` — `UPROPERTY(EditAnywhere, Category = "Animation Properties", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))` — The amount of linear velocities sent to the local cloth space from the reference bone (the closest bone to the root on which the cloth section has been skinned, or the root itself if the cloth isn't skinned).
- L419 _public member_ `bool bEnableLinearVelocityClamping = false;` — `UPROPERTY(EditAnywhere, Category = "Animation Properties", meta = (InlineEditConditionToggle))` — Enable linear velocity clamping.
- L426 _public member_ `FVector3f MaxLinearVelocity = { 1000.f, 1000.f, 1000.f };` — `UPROPERTY(EditAnywhere, Category = "Animation Properties", meta = (ClampMin = "0", EditCondition = "bEnableLinearVelocityClamping"))` — The maximum amount of linear velocity sent to the local cloth space from the reference bone (the closest bone to the root on which the cloth section has been skinned, or the root itself if the cloth isn't skinned).
- L432 _public member_ `bool bEnableLinearAccelerationClamping = false;` — `UPROPERTY(EditAnywhere, Category = "Animation Properties", meta = (InlineEditConditionToggle))` — Enable linear acceleration clamping.
- L439 _public member_ `FVector3f MaxLinearAcceleration = { 60000.f, 60000.f, 60000.f };` — `UPROPERTY(EditAnywhere, Category = "Animation Properties", meta = (ClampMin = "0", EditCondition = "bEnableLinearAccelerationClamping"))` — The maximum amount of linear acceleration sent to the local cloth space from the reference bone (the closest bone to the root on which the cloth section has been skinned, or the root itself if the cloth isn't skinned).
- L446 _public member_ `float AngularVelocityScale = 0.75f;` — `UPROPERTY(EditAnywhere, Category = "Animation Properties", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))` — The amount of angular velocities sent to the local cloth space from the reference bone (the closest bone to the root on which the cloth section has been skinned, or the root itself if the cloth isn't skinned).
- L452 _public member_ `bool bEnableAngularVelocityClamping = false;` — `UPROPERTY(EditAnywhere, Category = "Animation Properties", meta = (InlineEditConditionToggle))` — Enable angular velocity clamping.
- L459 _public member_ `float MaxAngularVelocity = 200.f;` — `UPROPERTY(EditAnywhere, Category = "Animation Properties", meta = (ClampMin = "0", EditCondition = "bEnableAngularVelocityClamping"))` — The maximum amount of angular velocity sent to the local cloth space from the reference bone (the closest bone to the root on which the cloth section has been skinned, or the root itself if the cloth isn't skinned).
- L465 _public member_ `bool bEnableAngularAccelerationClamping = false;` — `UPROPERTY(EditAnywhere, Category = "Animation Properties", meta = (InlineEditConditionToggle))` — Enable angular acceleration clamping.
- L472 _public member_ `float MaxAngularAcceleration = 12000.f;` — `UPROPERTY(EditAnywhere, Category = "Animation Properties", meta = (ClampMin = "0", EditCondition = "bEnableAngularAccelerationClamping"))` — The maximum amount of angular acceleration sent to the local cloth space from the reference bone (the closest bone to the root on which the cloth section has been skinned, or the root itself if the cloth isn't skinned).
- L479 _public member_ `EChaosClothingSimulationSolverFictitiousForcesModel FictitiousForcesModel = EChaosClothingSimulationSolverFictitiousForcesModel::FullScale;` — `UPROPERTY(EditAnywhere, Category = "Animation Properties")` — Fictitious forces model. Decide how fictitious forces (e.g. centrifugal force) are applied to the simulation.
- L492 _public member_ `float FictitiousAngularScale = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Animation Properties", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "2", EditCondition = "FictitiousForcesModel != EChaosClothingSimulationSolverFictitiousForcesModel::None"))` — The portion of the angular velocity that is used to calculate the strength of all fictitious forces (e.g. centrifugal force). In Legacy model, this parameter is only having an effect on the portion of the reference bone's angular velocity that has been removed from the simulation via the Angular Velocity Scale parameter. This means it has no effect when AngularVelocityScale is set to 1 and Angular Velocity and Acceleration clamps are disabled, in which case the cloth is simulated with full world space angular velocities and subjected to the true physical world inertial forces. In FullScale model, this parameter has also an effect when the cloth is simulated with full world space angular velocities, and isn't affected by the Angular Velocity Scale parameter. Values range from 0 to 2, with 0 showing no centrifugal effect, 1 full centrifugal effect, and 2 an overdriven centrifugal effect.
- L496 _public member_ `bool bUseTetrahedralConstraints = false;` — `UPROPERTY()` — Enable tetrahedral constraints.
- L500 _public member_ `bool bUseThinShellVolumeConstraints = false;` — `UPROPERTY()` — Enable thin shell volume constraints.
- L504 _public member_ `bool bUseContinuousCollisionDetection = false;` — `UPROPERTY()` — Enable continuous collision detection.
- L509 _public member_ `float EdgeStiffness_DEPRECATED = 1.f;` — `UPROPERTY()`
- L513 _public member_ `float BendingStiffness_DEPRECATED = 1.f;` — `UPROPERTY()` — The Stiffness of the bending constraints. Increase the iteration count for stiffer materials. Increase the iteration count for stiffer materials.
- L517 _public member_ `float AreaStiffness_DEPRECATED = 1.f;` — `UPROPERTY()` — The stiffness of the area preservation constraints. Increase the iteration count for stiffer materials.
- L520 _public member_ `EChaosClothTetherMode TetherMode_DEPRECATED = EChaosClothTetherMode::MaxChaosClothTetherMode;` — `UPROPERTY()`
- L523 _public member_ `float LimitScale_DEPRECATED = 1.f;` — `UPROPERTY()`
- L526 _public member_ `float DragCoefficient_DEPRECATED = 0.07f;` — `UPROPERTY()`
- L529 _public member_ `float LiftCoefficient_DEPRECATED = 0.035f;` — `UPROPERTY()`
- L532 _public member_ `float AnimDriveSpringStiffness_DEPRECATED = 0.f;` — `UPROPERTY()`
- L535 _public member_ `float StrainLimitingStiffness_DEPRECATED = 0.5f;` — `UPROPERTY()`

#### class `UChaosClothSharedSimConfig`  
`class UChaosClothSharedSimConfig : public UClothSharedConfigCommon`  
_L546-628_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UClothSharedConfigCommon`
- desc: Chaos config settings shared between all instances of a skeletal mesh. Unlike UChaosClothConfig, these settings contain common cloth simulation parameters that cannot change between the various clothing assets assigned to a specific skeletal mesh. @seealso UChaosClothConfig.
- L550 _public prototype_ `UChaosClothSharedSimConfig();`
- L554 _public prototype_ `virtual void MigrateFrom(const FClothConfig_Legacy& ClothConfig) override;` — Migrate from the legacy FClothConfig structure.
- L557 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — Serialize override used to set the current custom version.
- L560 _public prototype_ `virtual void PostLoad() override;` — PostLoad override used to deal with updates/changes in properties.
- L564 _public prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& ChainEvent) override;` — Called after changes in any of the asset properties.
- L573 _public member_ `int32 IterationCount = 1;` — `UPROPERTY(EditAnywhere, Category = Simulation, meta = (UIMin = "1", UIMax = "10", ClampMin = "1", ClampMax = "100"))` — The number of time step dependent solver iterations. This sets iterations at 60fps. This will increase the stiffness of all constraints but will increase the CPU cost. If the frame rate is higher, the actual number of iterations used by the solver might be less, if the frame rate is lower it might be more.
- L580 _public member_ `int32 MaxIterationCount = 10;` — `UPROPERTY(EditAnywhere, Category = Simulation, meta = (UIMin = "1", UIMax = "10", ClampMin = "1", ClampMax = "100"))` — The maximum number of solver iterations. This is the upper limit of the number of iterations set in solver, when the frame rate is lower than 60fps.
- L587 _public member_ `int32 SubdivisionCount = 1;` — `UPROPERTY(EditAnywhere, Category = Simulation, meta = (UIMin = "1", UIMax = "10", ClampMin = "1", ClampMax = "100"))` — The number of solver substeps. This will increase the precision of the collision inputs and help with constraint resolutions but will increase the CPU cost.
- L592 _public member_ `float SelfCollisionThickness_DEPRECATED = 2.0f;` — `UPROPERTY()` — The radius of the spheres used in self collision
- L596 _public member_ `float CollisionThickness_DEPRECATED = 1.0f;` — `UPROPERTY()` — The radius of cloth points when considering collisions against collider shapes.
- L600 _public member_ `bool bUseDampingOverride_DEPRECATED = true;` — `UPROPERTY()` — Use shared config damping rather than per cloth damping.
- L604 _public member_ `float Damping_DEPRECATED = 0.01f;` — `UPROPERTY()` — The amount of cloth damping. Override the per cloth damping coefficients.
- L608 _public member_ `bool bUseGravityOverride_DEPRECATED = false;` — `UPROPERTY()` — Use the config gravity value instead of world gravity.
- L612 _public member_ `float GravityScale_DEPRECATED = 1.f;` — `UPROPERTY()` — Scale factor applied to the world gravity and also to the clothing simulation interactor gravity. Does not affect the gravity if set using the override below.
- L616 _public member_ `FVector Gravity_DEPRECATED = { 0.f, 0.f, -980.665f };` — `UPROPERTY()` — The gravitational acceleration vector [cm/s^2]
- L622 _public member_ `bool bUseLocalSpaceSimulation = true;` — `UPROPERTY()` — Enable local space simulation to help with jitter due to floating point precision errors if the character is far away from the world origin
- L627 _public member_ `bool bUseXPBDConstraints = false;` — `UPROPERTY()` — Enable the XPBD constraints that resolve stiffness independently from the number of iterations Experimental, this feature might be removed without warning, not for production use

### `Plugins/ChaosCloth/Source/ChaosCloth/Public/ChaosCloth/ChaosClothConstraints.h` (Public)


#### class `Chaos::FClothConstraints`  
`class FClothConstraints final`  
_L27-319_
- L30 _public prototype_ `FClothConstraints();`
- L31 _public prototype_ `~FClothConstraints();`
- L35 _public prototype_ `void Initialize( Softs::FEvolution* InEvolution, FPerSolverFieldSystem* InPerSolverField, const TArray<Softs::FSolverVec3>& InInterpolatedAnimationPositions, const TArray<Softs::FSolverVec3>& InInterpolatedAnimationNormals, const TArray<Softs::FSolverVec3>& InAnimationVelocities, const TArray<Softs::FSolverVec3>& InNormals, const TArray<Softs::FSolverRigidTransform3>& InLastSubframeCollisionTransformsCCD, TArray<bool>& InCollisionParticleCollided, TArray<Softs::FSolverVec3>& InCollisionContacts, TArray<Softs::FSolverVec3>& InCollisionNormals, TArray<Softs::FSolverReal>& InCollisionPhis, int32 InParticleRangeId);` — ---- Solver interface ---- Force-based solver
- L50 _public prototype_ `void UpdateFromSolver(const Softs::FSolverVec3& SolverGravity, bool bPerClothGravityOverrideEnabled, const Softs::FSolverVec3& FictitiousAngularVelocity, const Softs::FSolverVec3& ReferenceSpaceLocation, const Softs::FSolverVec3& SolverWindVelocity, const Softs::FSolverReal LegacyWindAdaptation);` — Force-based solver
- L55 _public prototype_ `void Initialize( Softs::FPBDEvolution* InEvolution, const TArray<Softs::FSolverVec3>& InInterpolatedAnimationPositions, const TArray<Softs::FSolverVec3>& ,` — PBD solver
- L64 _public function_ `void SetSkipSelfCollisionInit(bool bValue)`
- L66 _public prototype_ `void OnCollisionRangeRemoved(int32 CollisionRangeId);`
- L70 _public prototype_ `void AddRules( const Softs::FCollectionPropertyConstFacade& ConfigProperties, const FTriangleMesh& TriangleMesh, const FClothingPatternData* PatternData, const TMap<FString, TConstArrayView<FRealSingle>>& WeightMaps, const TMap<FString, const TSet<int32>*>& VertexSets, const TMap<FString, const TSet<int32>*>& FaceSets, const TMap<FString, TConstArrayView<int32>>& FaceIntMaps, const TArray<TConstArrayView<TTuple<int32, int32, FRealSingle>>>& Tethers, Softs::FSolverReal MeshScale, bool bEnabled, const TArray<const FClothComplexColliders*>& ComplexColliders = TArray<const FClothComplexColliders*>(), const TSharedPtr<const FManagedArrayCollection>& ManagedArrayCollection = TSharedPtr<const FManagedArrayCollection>(), const TMap<FName, FClothingAccessoryMeshData>* AccessoryMeshes = nullptr);` — ---- Cloth interface ----
- L86 _public function_ `void AddRules( const Softs::FCollectionPropertyConstFacade& ConfigProperties, const FTriangleMesh& TriangleMesh, const FClothingPatternData* PatternData, const TMap<FString, TConstArrayView<FRealSingle>>& WeightMaps, const TMap<FString, const TSet<int32>*>& VertexSets, const TMap<FString, const TSet<int32>*>& FaceSets, const TMap<FString, TConstArrayView<int32>>& FaceIntMaps, const TArray<TConstArrayView<TTuple<int32, int32, FRealSingle>>>& Tethers, Softs::FSolverReal MeshScale, bool bEnabled, const FTriangleMesh* MultiResCoarseLODMesh = nullptr, const int32 MultiResCoarseLODParticleRangeId = INDEX_NONE, const TSharedPtr<Softs::FMultiResConstraints>& FineLODMultiResConstraint = TSharedPtr<Softs::FMultiResConstraints>(nullptr), const TArray<const FClothComplexColliders*>& ComplexColliders = TArray<const FClothComplexColliders*>(), const TSharedPtr<const FManagedArrayCollection>& ManagedArrayCollection = TSharedPtr<const FManagedArrayCollection>(), const TMap<FName, FClothingAccessoryMeshData>* AccessoryMeshes = nullptr)` — `UE_DEPRECATED(5.8, "MultiRes constraint is no longer supported. Use other version of AddRules instead.")`
- L107 _public prototype_ `void Update( const Softs::FCollectionPropertyConstFacade& ConfigProperties, const TMap<FString, TConstArrayView<FRealSingle>>& WeightMaps, const TMap<FString, const TSet<int32>*>& VertexSets, const TMap<FString, const TSet<int32>*>& FaceSets, const TMap<FString, TConstArrayView<int32>>& FaceIntMaps, Softs::FSolverReal MeshScale, Softs::FSolverReal MaxDistancesScale = (Softs::FSolverReal)1., const FRotation3& LocalSpaceRotation = FRotation3::Identity, const FRotation3& ReferenceSpaceRotation = FRotation3::Identity, const FReal LocalSpaceScale = (Softs::FSolverReal)1., const FSolverVec3 LocalSpaceLocation = FSolverVec3::ZeroVector);`
- L122 _public prototype_ `void Enable(bool bEnable);` — NOTE: this only does something if using the PBDSolver. Force-based solver constraints are activated automatically when activating a particle range.
- L124 _public prototype_ `void ResetRestLengths( const TConstArrayView<Softs::FSolverVec3>& NewRestLengthPositions, const Softs::FCollectionPropertyConstFacade& ConfigProperties, const TMap<FString, TConstArrayView<FRealSingle>>& WeightMaps);`
- L131 _public function_ `const TSharedPtr<Softs::FPBDEdgeSpringConstraints>& GetEdgeSpringConstraints() const` — ---- Debug functions ----
- L132 _public function_ `const TSharedPtr<Softs::FXPBDEdgeSpringConstraints>& GetXEdgeSpringConstraints() const`
- L133 _public function_ `const TSharedPtr<Softs::FXPBDStretchBiasElementConstraints>& GetXStretchBiasConstraints() const`
- L134 _public function_ `const TSharedPtr<Softs::FXPBDAnisotropicSpringConstraints>& GetXAnisoSpringConstraints() const`
- L135 _public function_ `const TSharedPtr<Softs::FPBDBendingSpringConstraints>& GetBendingSpringConstraints() const`
- L136 _public function_ `const TSharedPtr<Softs::FXPBDBendingSpringConstraints>& GetXBendingSpringConstraints() const`
- L137 _public function_ `const TSharedPtr<Softs::FPBDBendingConstraints>& GetBendingElementConstraints() const`
- L138 _public function_ `const TSharedPtr<Softs::FXPBDBendingConstraints>& GetXBendingElementConstraints() const`
- L139 _public function_ `const TSharedPtr<Softs::FXPBDAnisotropicBendingConstraints>& GetXAnisoBendingElementConstraints() const`
- L140 _public function_ `const TSharedPtr<Softs::FPBDExtremeDeformationConstraints>& GetExtremeDeformationConstraints() const`
- L141 _public function_ `const TSharedPtr<Softs::FPBDAreaSpringConstraints>& GetAreaSpringConstraints() const`
- L142 _public function_ `const TSharedPtr<Softs::FXPBDAreaSpringConstraints>& GetXAreaSpringConstraints() const`
- L143 _public function_ `const TSharedPtr<Softs::FPBDLongRangeConstraints>& GetLongRangeConstraints() const`
- L144 _public function_ `const TSharedPtr<Softs::FPBDSphericalConstraint>& GetMaximumDistanceConstraints() const`
- L145 _public function_ `const TSharedPtr<Softs::FPBDSphericalBackstopConstraint>& GetBackstopConstraints() const`
- L146 _public function_ `const TSharedPtr<Softs::FPBDAnimDriveConstraint>& GetAnimDriveConstraints() const`
- L147 _public function_ `const TSharedPtr<Softs::FPBDCollisionSpringConstraints>& GetSelfCollisionConstraints() const`
- L148 _public function_ `const TSharedPtr<Softs::FPBDTriangleMeshIntersections>& GetSelfIntersectionConstraints() const`
- L149 _public function_ `const TSharedPtr<Softs::FPBDTriangleMeshCollisions>& GetSelfCollisionInit() const`
- L150 _public function_ `const TSharedPtr<Softs::FPBDSelfCollisionSphereConstraints>& GetSelfCollisionSphereConstraints() const`
- L152 _public function_ `const TSharedPtr<Softs::FVelocityAndPressureField>& GetVelocityAndPressureField() const`
- L154 _public function_ `const TSharedPtr<Buoyancy::FBuoyancyField>& GetBuoyancyField() const`
- L156 _public function_ `const TSharedPtr<Softs::FExternalForces>& GetExternalForces() const`
- L157 _public function_ `const TSharedPtr<Softs::FPBDSoftBodyCollisionConstraint>& GetCollisionConstraint() const`
- L158 _public function_ `const TSharedPtr<Softs::FPBDSkinnedTriangleMeshCollisionConstraints>& GetSkinnedTriangleCollisionsConstraint() const`
- L160 _public function_ `const TSharedPtr<Softs::FMultiResConstraints>& GetMultiResConstraints() const` — `UE_DEPRECATED(5.8, "MultiResConstraints have been deprecated")`
- L161 _public function_ `const TSharedPtr<Softs::FXPBDVertexConstraints>& GetClothVertexSpringConstraints() const`
- L162 _public function_ `const TSharedPtr<Softs::FXPBDVertexFaceConstraints>& GetClothVertexFaceSpringConstraints() const`
- L163 _public function_ `const TSharedPtr<Softs::FXPBDFaceConstraints>& GetClothFaceSpringConstraints() const`
- L164 _public function_ `const TSharedPtr<Softs::FPBDVertexFaceRepulsionConstraints>& GetRepulsionConstraints() const`
- L168 _private prototype_ `void CreateSelfCollisionConstraints( const Softs::FCollectionPropertyConstFacade& ConfigProperties, const TMap<FString, TConstArrayView<FRealSingle>>& WeightMaps, const TMap<FString, const TSet<int32>*>& VertexSets, const TMap<FString, const TSet<int32>*>& FaceSets, const TMap<FString, TConstArrayView<int32>>& FaceIntMaps, const FTriangleMesh& TriangleMesh);`
- L175 _private prototype_ `void CreateStretchConstraints( const Softs::FCollectionPropertyConstFacade& ConfigProperties, const TMap<FString, TConstArrayView<FRealSingle>>& WeightMaps, const FTriangleMesh& TriangleMesh, const FClothingPatternData* PatternData, const TSharedPtr<const FManagedArrayCollection>& ManagedArrayCollection, Softs::FSolverReal MeshScale);`
- L182 _private prototype_ `void CreateBendingConstraints( const Softs::FCollectionPropertyConstFacade& ConfigProperties, const TMap<FString, TConstArrayView<FRealSingle>>& WeightMaps, const FTriangleMesh& TriangleMesh, const FClothingPatternData* PatternData);`
- L187 _private prototype_ `void CreateExtremeDeformationConstraints( const Softs::FCollectionPropertyConstFacade& ConfigProperties, const TMap<FString, TConstArrayView<FRealSingle>>& WeightMaps, const TMap<FString, const TSet<int32>*>& VertexSets, const FTriangleMesh& TriangleMesh, const FClothingPatternData* PatternData);`
- L193 _private prototype_ `void CreateAreaConstraints( const Softs::FCollectionPropertyConstFacade& ConfigProperties, const TMap<FString, TConstArrayView<FRealSingle>>& WeightMaps, const FTriangleMesh& TriangleMesh, const FClothingPatternData* PatternData);`
- L198 _private prototype_ `void CreateLongRangeConstraints( const Softs::FCollectionPropertyConstFacade& ConfigProperties, const TMap<FString, TConstArrayView<FRealSingle>>& WeightMaps, const TArray<TConstArrayView<TTuple<int32, int32, FRealSingle>>>& Tethers, Softs::FSolverReal MeshScale);`
- L203 _private prototype_ `void CreateMaxDistanceConstraints( const Softs::FCollectionPropertyConstFacade& ConfigProperties, const TMap<FString, TConstArrayView<FRealSingle>>& WeightMaps, Softs::FSolverReal MeshScale);`
- L207 _private prototype_ `void CreateBackstopConstraints( const Softs::FCollectionPropertyConstFacade& ConfigProperties, const TMap<FString, TConstArrayView<FRealSingle>>& WeightMaps, Softs::FSolverReal MeshScale, const TMap<FName, FClothingAccessoryMeshData>* AccessoryMeshes);`
- L212 _private prototype_ `void CreateAnimDriveConstraints( const Softs::FCollectionPropertyConstFacade& ConfigProperties, const TMap<FString, TConstArrayView<FRealSingle>>& WeightMaps);`
- L215 _private prototype_ `void CreateVelocityAndPressureField( const Softs::FCollectionPropertyConstFacade& ConfigProperties, const TMap<FString, TConstArrayView<FRealSingle>>& WeightMaps, const FTriangleMesh& TriangleMesh );`
- L220 _private prototype_ `void CreateVelocityPressureAndBuoyancyField( const Softs::FCollectionPropertyConstFacade& ConfigProperties, const TMap<FString, TConstArrayView<FRealSingle>>& WeightMaps, const FTriangleMesh& TriangleMesh );`
- L226 _private prototype_ `void CreateExternalForces( const Softs::FCollectionPropertyConstFacade& ConfigProperties, const TMap<FString, TConstArrayView<FRealSingle>>& WeightMaps );`
- L230 _private prototype_ `void CreateCollisionConstraint( const Softs::FCollectionPropertyConstFacade& ConfigProperties, Softs::FSolverReal MeshScale, const TMap<FString, TConstArrayView<FRealSingle>>& WeightMaps, const TArray<const FClothComplexColliders*>& ComplexColliders);`
- L235 _private prototype_ `void CreateClothClothConstraints( const Softs::FCollectionPropertyConstFacade& ConfigProperties, const TSharedPtr<const FManagedArrayCollection>& ManagedArrayCollection);`
- L239 _private prototype_ `void CreateForceBasedRules();`
- L240 _private prototype_ `void CreatePBDRules();`
- L242 _private member_ `TSharedPtr<Softs::FPBDEdgeSpringConstraints> EdgeConstraints;`
- L243 _private member_ `TSharedPtr<Softs::FXPBDEdgeSpringConstraints> XEdgeConstraints;`
- L244 _private member_ `TSharedPtr<Softs::FXPBDStretchBiasElementConstraints> XStretchBiasConstraints;`
- L245 _private member_ `TSharedPtr<Softs::FXPBDAnisotropicSpringConstraints> XAnisoSpringConstraints;`
- L246 _private member_ `TSharedPtr<Softs::FPBDBendingSpringConstraints> BendingConstraints;`
- L247 _private member_ `TSharedPtr<Softs::FXPBDBendingSpringConstraints> XBendingConstraints;`
- L248 _private member_ `TSharedPtr<Softs::FPBDBendingConstraints> BendingElementConstraints;`
- L249 _private member_ `TSharedPtr<Softs::FXPBDBendingConstraints> XBendingElementConstraints;`
- L250 _private member_ `TSharedPtr<Softs::FXPBDAnisotropicBendingConstraints> XAnisoBendingElementConstraints;`
- L251 _private member_ `TSharedPtr<Softs::FPBDAreaSpringConstraints> AreaConstraints;`
- L252 _private member_ `TSharedPtr<Softs::FXPBDAreaSpringConstraints> XAreaConstraints;`
- L253 _private member_ `TSharedPtr<Softs::FPBDLongRangeConstraints> LongRangeConstraints;`
- L254 _private member_ `TSharedPtr<Softs::FPBDSphericalConstraint> MaximumDistanceConstraints;`
- L255 _private member_ `TSharedPtr<Softs::FPBDSphericalBackstopConstraint> BackstopConstraints;`
- L256 _private member_ `TSharedPtr<Softs::FPBDAnimDriveConstraint> AnimDriveConstraints;`
- L257 _private member_ `TSharedPtr<Softs::FPBDTriangleMeshCollisions> SelfCollisionInit;`
- L258 _private member_ `TSharedPtr<Softs::FPBDCollisionSpringConstraints> SelfCollisionConstraints;`
- L259 _private member_ `TSharedPtr<Softs::FPBDTriangleMeshIntersections> SelfIntersectionConstraints;`
- L260 _private member_ `TSharedPtr<Softs::FPBDSelfCollisionSphereConstraints> SelfCollisionSphereConstraints;`
- L261 _private member_ `TSharedPtr<Softs::FPBDExtremeDeformationConstraints> ExtremeDeformationConstraints;`
- L263 _private member_ `Softs::FSolverVec3 SolverWindVelocity;` — Set from solver and added to wind from the config
- L264 _private member_ `TSharedPtr<Softs::FVelocityAndPressureField> VelocityAndPressureField;`
- L265 _private member_ `TSharedPtr<Buoyancy::FBuoyancyField> VelocityPressureAndBuoyancyField;`
- L266 _private member_ `TSharedPtr<Softs::FExternalForces> ExternalForces;`
- L267 _private member_ `TSharedPtr<Softs::FPBDSoftBodyCollisionConstraint> CollisionConstraint;`
- L268 _private member_ `TSharedPtr<Softs::FPBDSkinnedTriangleMeshCollisionConstraints> SkinnedTriangleCollisionsConstraint;`
- L269 _private member_ `TSharedPtr<Softs::FXPBDVertexConstraints> ClothVertexSpringConstraints;`
- L270 _private member_ `TSharedPtr<Softs::FXPBDVertexFaceConstraints> ClothVertexFaceSpringConstraints;`
- L271 _private member_ `TSharedPtr<Softs::FXPBDFaceConstraints> ClothFaceSpringConstraints;`
- L272 _private member_ `TSharedPtr<Softs::FPBDVertexFaceRepulsionConstraints> RepulsionConstraints;`
- L276 _private member_ `Softs::FEvolution* Evolution;` — Exactly one of these should be non-null
- L277 _private member_ `Softs::FPBDEvolution* PBDEvolution;`
- L279 _private member_ `const TArray<Softs::FSolverVec3>* AnimationPositions;`
- L280 _private member_ `const TArray<Softs::FSolverVec3>* AnimationNormals;`
- L281 _private member_ `const TArray<Softs::FSolverVec3>* AnimationVelocities;`
- L283 _private member_ `int32 ParticleOffset;`
- L284 _private member_ `int32 ParticleRangeId;`
- L285 _private member_ `int32 NumParticles;`
- L287 _private member_ `int32 NumConstraintInits;`
- L288 _private member_ `int32 NumConstraintRules;`
- L289 _private member_ `int32 NumPostCollisionConstraintRules;`
- L290 _private member_ `int32 NumPostprocessingConstraintRules;`
- L292 _private member_ `bool bSkipSelfCollisionInit = false;`
- L295 _private member_ `FPerSolverFieldSystem* PerSolverField;`
- L296 _private member_ `const TArray<Softs::FSolverVec3>* Normals;`
- L297 _private member_ `const TArray<Softs::FSolverRigidTransform3>* LastSubframeCollisionTransformsCCD;`
- L298 _private member_ `TArray<bool>* CollisionParticleCollided;`
- L299 _private member_ `TArray<Softs::FSolverVec3>* CollisionContacts;`
- L300 _private member_ `TArray<Softs::FSolverVec3>* CollisionNormals;`
- L301 _private member_ `TArray<Softs::FSolverReal>* CollisionPhis;`
- L303 _private member_ `int32 NumPreSubstepInits;`
- L304 _private member_ `int32 NumExternalForceRules;`
- L305 _private member_ `int32 NumPreSubstepConstraintRules;`
- L306 _private member_ `int32 NumCollisionConstraintRules;`
- L307 _private member_ `int32 NumUpdateLinearSystemRules;`
- L308 _private member_ `int32 NumUpdateLinearSystemCollisionsRules;`
- L312 _private member_ `int32 ConstraintInitOffset;`
- L313 _private member_ `int32 ConstraintRuleOffset;`
- L314 _private member_ `int32 PostCollisionConstraintRuleOffset;`
- L315 _private member_ `int32 PostprocessingConstraintRuleOffset;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace Buoyancy`
- L20 _namespace_ `namespace Chaos`

### `Plugins/ChaosCloth/Source/ChaosCloth/Public/ChaosCloth/ChaosClothModule.h` (Public)


#### class `IChaosClothModuleInterface`  
`class IChaosClothModuleInterface : public IModuleInterface`  
_L13-15_
- inherits: `IModuleInterface`

#### Free symbols / members of external scopes

- L8 _macro_ `#define CHAOS_CLOTH_MODULE_NAME "ChaosCloth"`

### `Plugins/ChaosCloth/Source/ChaosCloth/Public/ChaosCloth/ChaosClothVisualization.h` (Public)


#### class `Chaos::FClothVisualizationNoGC`  
`class FClothVisualizationNoGC`  
_L23-501_
- L26 _public prototype_ `explicit FClothVisualizationNoGC(const ::Chaos::FClothingSimulationSolver* InSolver = nullptr);`
- L27 _public prototype_ `virtual ~FClothVisualizationNoGC();`
- L58 _public prototype_ `void SetSolver(const ::Chaos::FClothingSimulationSolver* InSolver);` — Editor & runtime functions
- L60 _public prototype_ `void DrawParticleIndices(const FDrawTextsContext& Context = FDrawTextsContext()) const;`
- L61 _public prototype_ `void DrawElementIndices(const FDrawTextsContext& Context = FDrawTextsContext()) const;`
- L62 _public prototype_ `void DrawMaxDistanceValues(const FDrawTextsContext& Context = FDrawTextsContext()) const;`
- L63 _public prototype_ `void DrawLocalSpaceBoneNames(const FDrawTextsContext& Context = FDrawTextsContext()) const;`
- L65 _public prototype_ `void DrawPhysMeshWired(const FDrawContext& Context = FDrawContext()) const;`
- L66 _public prototype_ `void DrawAnimMeshWired(const FDrawContext& Context = FDrawContext()) const;`
- L67 _public prototype_ `void DrawAnimNormals(const FDrawContext& Context = FDrawContext(), const FReal Length = 20.) const;`
- L68 _public prototype_ `void DrawAnimVelocities(const FDrawContext& Context = FDrawContext()) const;`
- L69 _public prototype_ `void DrawOpenEdges(const FDrawContext& Context = FDrawContext()) const;`
- L70 _public prototype_ `void DrawPointNormals(const FDrawContext& Context = FDrawContext(), const FReal Length = 20.) const;`
- L71 _public prototype_ `void DrawPointVelocities(const FDrawContext& Context = FDrawContext()) const;`
- L72 _public prototype_ `void DrawCollision(const FDrawContext& Context = FDrawContext(), const bool bWireframe = false) const;`
- L73 _public prototype_ `void DrawBackstops(const FDrawContext& Context = FDrawContext()) const;`
- L74 _public prototype_ `void DrawBackstopDistances(const FDrawContext& Context = FDrawContext()) const;`
- L75 _public prototype_ `void DrawMaxDistances(const FDrawContext& Context = FDrawContext()) const;`
- L76 _public prototype_ `void DrawAnimDrive(const FDrawContext& Context = FDrawContext()) const;`
- L77 _public prototype_ `void DrawEdgeConstraint(const FDrawContext& Context = FDrawContext()) const;`
- L78 _public prototype_ `void DrawBendingConstraint(const FDrawContext& Context = FDrawContext()) const;`
- L79 _public prototype_ `void DrawLongRangeConstraint(const FDrawContext& Context = FDrawContext()) const;`
- L80 _public prototype_ `void DrawWindAndPressureForces(const FDrawContext& Context = FDrawContext(), const FReal LengthScale = 10.) const;`
- L81 _public prototype_ `void DrawWindVelocity(const FDrawContext& Context = FDrawContext(), const FReal LengthScale = 0.1) const;`
- L82 _public prototype_ `void DrawLocalSpace(const FDrawContext& Context = FDrawContext(), const FReal LengthScale = 1.) const;`
- L83 _public prototype_ `void DrawVelocityScale(const FDrawContext& Context = FDrawContext(), const FReal LengthScale = 0.1) const;`
- L84 _public prototype_ `void DrawSelfCollision(const FDrawContext& Context = FDrawContext()) const;`
- L85 _public prototype_ `void DrawSelfIntersection(const FDrawContext& Context = FDrawContext()) const;`
- L86 _public prototype_ `void DrawSelfCollisionThickness(const FDrawContext& Context = FDrawContext()) const;`
- L87 _public prototype_ `void DrawClothCollisionThickness(const FDrawContext& Context = FDrawContext()) const;`
- L88 _public prototype_ `void DrawInnerCollisionThickness(const FDrawContext& Context = FDrawContext()) const;`
- L89 _public prototype_ `void DrawKinematicColliderWired(const FDrawContext& Context = FDrawContext()) const;`
- L90 _public prototype_ `void DrawBounds(const FDrawContext& Context = FDrawContext()) const;`
- L91 _public prototype_ `void DrawGravity(const FDrawContext& Context = FDrawContext()) const;`
- L92 _public prototype_ `void DrawFictitiousAngularForces(const FDrawContext& Context = FDrawContext()) const;`
- L93 _public prototype_ `void DrawClothClothConstraints(const FDrawContext& Context = FDrawContext()) const;`
- L94 _public prototype_ `void DrawTeleportReset(const FDrawContext& Context = FDrawContext()) const;`
- L95 _public prototype_ `void DrawExtremlyDeformedEdges(const FDrawContext& Context = FDrawContext()) const;`
- L96 _public prototype_ `void DrawAccessoryMesh(const FDrawContext& Context = FDrawContext(), const FName& AccessoryMeshName = NAME_None) const;`
- L97 _public prototype_ `void DrawAccessoryMeshNormals(const FDrawContext& Context = FDrawContext(), const FName& AccessoryMeshName = NAME_None, const FReal Length = 20.) const;`
- L100 _public function_ `void DrawParticleIndices(FCanvas* Canvas, const FSceneView* SceneView = nullptr) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L105 _public function_ `void DrawElementIndices(FCanvas* Canvas, const FSceneView* SceneView = nullptr) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L110 _public function_ `void DrawMaxDistanceValues(FCanvas* Canvas, const FSceneView* SceneView = nullptr) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L115 _public function_ `void DrawLocalSpaceBoneNames(FCanvas* Canvas, const FSceneView* SceneView = nullptr) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L121 _public function_ `void DrawPhysMeshWired(FPrimitiveDrawInterface* PDI) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L126 _public function_ `void DrawAnimMeshWired(FPrimitiveDrawInterface* PDI) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L131 _public function_ `void DrawAnimNormals(FPrimitiveDrawInterface* PDI, const FReal Length) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L136 _public function_ `void DrawAnimVelocities(FPrimitiveDrawInterface* PDI) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L141 _public function_ `void DrawOpenEdges(FPrimitiveDrawInterface* PDI) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L146 _public function_ `void DrawPointNormals(FPrimitiveDrawInterface* PDI, const FReal Length) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L151 _public function_ `void DrawPointVelocities(FPrimitiveDrawInterface* PDI) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L156 _public function_ `void DrawCollision(FPrimitiveDrawInterface* PDI, bool bWireframe) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L161 _public function_ `void DrawBackstops(FPrimitiveDrawInterface* PDI) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L166 _public function_ `void DrawBackstopDistances(FPrimitiveDrawInterface* PDI) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L171 _public function_ `void DrawMaxDistances(FPrimitiveDrawInterface* PDI) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L176 _public function_ `void DrawAnimDrive(FPrimitiveDrawInterface* PDI) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L181 _public function_ `void DrawEdgeConstraint(FPrimitiveDrawInterface* PDI) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L186 _public function_ `void DrawBendingConstraint(FPrimitiveDrawInterface* PDI) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L191 _public function_ `void DrawLongRangeConstraint(FPrimitiveDrawInterface* PDI) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L196 _public function_ `void DrawWindAndPressureForces(FPrimitiveDrawInterface* PDI, const FReal LengthScale) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L201 _public function_ `void DrawWindVelocity(FPrimitiveDrawInterface* PDI, const FReal LengthScale) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L206 _public function_ `void DrawLocalSpace(FPrimitiveDrawInterface* PDI, const FReal LengthScale) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L211 _public function_ `void DrawVelocityScale(FPrimitiveDrawInterface* PDI, const FReal LengthScale) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L216 _public function_ `void DrawSelfCollision(FPrimitiveDrawInterface* PDI) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L221 _public function_ `void DrawSelfIntersection(FPrimitiveDrawInterface* PDI) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L226 _public function_ `void DrawSelfCollisionThickness(FPrimitiveDrawInterface* PDI) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L231 _public function_ `void DrawKinematicColliderWired(FPrimitiveDrawInterface* PDI) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L236 _public function_ `void DrawBounds(FPrimitiveDrawInterface* PDI) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L241 _public function_ `void DrawGravity(FPrimitiveDrawInterface* PDI) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L246 _public function_ `void DrawFictitiousAngularForces(FPrimitiveDrawInterface* PDI) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L251 _public function_ `void DrawMultiResConstraint(FPrimitiveDrawInterface* PDI = nullptr) const` — `UE_DEPRECATED(5.8, "MultiResConstraints have been deprecated.")`
- L255 _public function_ `void DrawClothClothConstraints(FPrimitiveDrawInterface* PDI) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L260 _public function_ `void DrawTeleportReset(FPrimitiveDrawInterface* PDI) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L265 _public function_ `void DrawExtremlyDeformedEdges(FPrimitiveDrawInterface* PDI) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L270 _public function_ `void DrawAccessoryMesh(FPrimitiveDrawInterface* PDI, const FName& AccessoryMeshName = NAME_None) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L275 _public function_ `void DrawAccessoryMeshNormals(FPrimitiveDrawInterface* PDI, const FName& AccessoryMeshName = NAME_None, const FReal Length = 20.) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L281 _public function_ `void SetSolver(const ::Chaos::FClothingSimulationSolver* )`
- L282 _public function_ `void DrawParticleIndices(const FDrawTextsContext& = FDrawTextsContext()) const`
- L283 _public function_ `void DrawElementIndices(const FDrawTextsContext& = FDrawTextsContext()) const`
- L284 _public function_ `void DrawMaxDistanceValues(const FDrawTextsContext& = FDrawTextsContext()) const`
- L285 _public function_ `void DrawLocalSpaceBoneNames(const FDrawTextsContext& = FDrawTextsContext()) const`
- L286 _public function_ `void DrawPhysMeshWired(const FDrawContext& = FDrawContext()) const`
- L287 _public function_ `void DrawAnimMeshWired(const FDrawContext& = FDrawContext()) const`
- L288 _public function_ `void DrawAnimNormals(const FDrawContext& = FDrawContext(), const FReal = 20.) const`
- L289 _public function_ `void DrawOpenEdges(const FDrawContext& = FDrawContext()) const`
- L290 _public function_ `void DrawPointNormals(const FDrawContext& = FDrawContext(), const FReal = 20.) const`
- L291 _public function_ `void DrawPointVelocities(const FDrawContext& = FDrawContext()) const`
- L292 _public function_ `void DrawCollision(const FDrawContext& = FDrawContext(), bool = false) const`
- L293 _public function_ `void DrawBackstops(const FDrawContext& = FDrawContext()) const`
- L294 _public function_ `void DrawBackstopDistances(const FDrawContext& = FDrawContext()) const`
- L295 _public function_ `void DrawMaxDistances(const FDrawContext& = FDrawContext()) const`
- L296 _public function_ `void DrawAnimDrive(const FDrawContext& = FDrawContext()) const`
- L297 _public function_ `void DrawEdgeConstraint(const FDrawContext& = FDrawContext()) const`
- L298 _public function_ `void DrawBendingConstraint(const FDrawContext& = FDrawContext()) const`
- L299 _public function_ `void DrawLongRangeConstraint(const FDrawContext& = FDrawContext()) const`
- L300 _public function_ `void DrawWindAndPressureForces(const FDrawContext& = FDrawContext(), const FReal = 10.) const`
- L301 _public function_ `void DrawWindVelocity(const FDrawContext& = FDrawContext(), const FReal = 0.1) const`
- L302 _public function_ `void DrawLocalSpace(const FDrawContext& = FDrawContext(), FReal = 1.) const`
- L303 _public function_ `void DrawVelocityScale(const FDrawContext& = FDrawContext(), const FReal = 0.1) const`
- L304 _public function_ `void DrawSelfCollision(const FDrawContext& = FDrawContext()) const`
- L305 _public function_ `void DrawSelfIntersection(const FDrawContext& = FDrawContext()) const`
- L306 _public function_ `void DrawSelfCollisionThickness(const FDrawContext& = FDrawContext()) const`
- L307 _public function_ `void DrawClothCollisionThickness(const FDrawContext & = FDrawContext()) const`
- L308 _public function_ `void DrawInnerCollisionThickness(const FDrawContext & = FDrawContext()) const`
- L309 _public function_ `void DrawKinematicColliderWired(const FDrawContext& = FDrawContext()) const`
- L310 _public function_ `void DrawBounds(const FDrawContext& = FDrawContext()) const`
- L311 _public function_ `void DrawGravity(const FDrawContext& = FDrawContext()) const`
- L312 _public function_ `void DrawFictitiousAngularForces(const FDrawContext& = FDrawContext()) const`
- L313 _public function_ `void DrawClothClothConstraints(const FDrawContext& = FDrawContext()) const`
- L314 _public function_ `void DrawExtremlyDeformedEdges(const FDrawContext& = FDrawContext()) const`
- L315 _public function_ `void DrawAccessoryMesh(const FDrawContext& = FDrawContext(), const FName& = NAME_None) const`
- L316 _public prototype_ `void DrawAccessoryMeshNormals(const FDrawContext& = FDrawContext(), const FName& = NAME_None, const FReal = 20.) const;`
- L319 _public function_ `void DrawParticleIndices(FCanvas* , const FSceneView* ) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L321 _public function_ `void DrawElementIndices(FCanvas* , const FSceneView* ) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L323 _public function_ `void DrawMaxDistanceValues(FCanvas* , const FSceneView* ) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L325 _public function_ `void DrawLocalSpaceBoneNames(FCanvas* , const FSceneView* ) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L327 _public function_ `void DrawPhysMeshWired(FPrimitiveDrawInterface* ) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L329 _public function_ `void DrawAnimMeshWired(FPrimitiveDrawInterface* ) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L331 _public function_ `void DrawAnimNormals(FPrimitiveDrawInterface* , const FReal ) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L333 _public function_ `void DrawOpenEdges(FPrimitiveDrawInterface* ) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L335 _public function_ `void DrawPointNormals(FPrimitiveDrawInterface* , const FReal ) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L337 _public function_ `void DrawPointVelocities(FPrimitiveDrawInterface* ) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L339 _public function_ `void DrawCollision(FPrimitiveDrawInterface* , bool ) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L341 _public function_ `void DrawBackstops(FPrimitiveDrawInterface* ) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L343 _public function_ `void DrawBackstopDistances(FPrimitiveDrawInterface* ) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L345 _public function_ `void DrawMaxDistances(FPrimitiveDrawInterface* ) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L347 _public function_ `void DrawAnimDrive(FPrimitiveDrawInterface* ) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L349 _public function_ `void DrawEdgeConstraint(FPrimitiveDrawInterface* ) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L351 _public function_ `void DrawBendingConstraint(FPrimitiveDrawInterface* ) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L353 _public function_ `void DrawLongRangeConstraint(FPrimitiveDrawInterface* ) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L355 _public function_ `void DrawWindAndPressureForces(FPrimitiveDrawInterface* , const FReal ) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L357 _public function_ `void DrawWindVelocity(FPrimitiveDrawInterface* , const FReal ) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L359 _public function_ `void DrawLocalSpace(FPrimitiveDrawInterface* , FReal ) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L361 _public function_ `void DrawVelocityScale(FPrimitiveDrawInterface* , const FReal ) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L363 _public function_ `void DrawSelfCollision(FPrimitiveDrawInterface* ) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L365 _public function_ `void DrawSelfIntersection(FPrimitiveDrawInterface* ) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L367 _public function_ `void DrawSelfCollisionThickness(FPrimitiveDrawInterface* ) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L369 _public function_ `void DrawKinematicColliderWired(FPrimitiveDrawInterface* ) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L371 _public function_ `void DrawBounds(FPrimitiveDrawInterface* ) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L373 _public function_ `void DrawGravity(FPrimitiveDrawInterface* ) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L375 _public function_ `void DrawFictitiousAngularForces(FPrimitiveDrawInterface* ) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L377 _public function_ `void DrawMultiResConstraint(FPrimitiveDrawInterface* = nullptr) const` — `UE_DEPRECATED(5.8, "MultiRes Constraints have been deprecated.")`
- L379 _public function_ `void DrawClothClothConstraints(FPrimitiveDrawInterface* ) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L381 _public function_ `void DrawExtremlyDeformedEdges(FPrimitiveDrawInterface* ) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L383 _public function_ `void DrawAccessoryMesh(FPrimitiveDrawInterface* , const FName& = NAME_None) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L385 _public prototype_ `void DrawAccessoryMeshNormals(FPrimitiveDrawInterface* , const FName& = NAME_None, const FReal = 20.) const;` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L389 _public function_ `void DrawAnimNormals(FPrimitiveDrawInterface* PDI) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L395 _public function_ `void DrawPointNormals(FPrimitiveDrawInterface* PDI) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L401 _public function_ `void DrawCollision(FPrimitiveDrawInterface* PDI) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L407 _public function_ `void DrawWindAndPressureForces(FPrimitiveDrawInterface* PDI) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L413 _public function_ `void DrawWindVelocity(FPrimitiveDrawInterface* PDI) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L419 _public function_ `void DrawVelocityScale(FPrimitiveDrawInterface* PDI) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L425 _public function_ `void DrawLocalSpace(FPrimitiveDrawInterface* PDI) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L433 _public prototype_ `void DrawPhysMeshShaded(const FDrawContext& Context = FDrawContext()) const;` — Editor only functions
- L434 _public prototype_ `void DrawSelfCollisionLayers(const FDrawContext& Context = FDrawContext()) const;`
- L435 _public prototype_ `void DrawInpaintWeightsMatched(const FDrawContext& Context = FDrawContext()) const;`
- L436 _public prototype_ `void DrawKinematicColliderShaded(const FDrawContext& Context = FDrawContext()) const;`
- L438 _public prototype_ `void DrawWeightMapWithName(const FDrawContext& Context = FDrawContext(), const FString& Name = "") const;` — When Name is empty, the string stored by the cvar p.ChaosClothVisualization.WeightMapName is used instead
- L440 _public prototype_ `void DrawSimMorphTarget(const FDrawContext& Context = FDrawContext(), const FString& Name = "") const;` — Will draw current morph target (if any) if no name or an invalid name is specified
- L441 _public prototype_ `TArray<FString> GetAllWeightMapNames() const;`
- L442 _public prototype_ `TArray<FString> GetAllMorphTargetNames() const;`
- L443 _public prototype_ `TArray<FString> GetAllVertexSetNames() const;`
- L444 _public prototype_ `TArray<FName> GetAllAccessoryMeshNames() const;`
- L448 _public function_ `void DrawPhysMeshShaded(FPrimitiveDrawInterface* PDI) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")` — Editor only functions
- L454 _public function_ `void DrawWeightMap(FPrimitiveDrawInterface* PDI) const` — `UE_DEPRECATED(5.8, "Use DrawWeightMapWithName instead.")`
- L459 _public function_ `void DrawSelfCollisionLayers(FPrimitiveDrawInterface* PDI) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L464 _public function_ `void DrawInpaintWeightsMatched(FPrimitiveDrawInterface* PDI) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L469 _public function_ `void DrawKinematicColliderShaded(FPrimitiveDrawInterface* PDI) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L474 _public function_ `void DrawWeightMapWithName(FPrimitiveDrawInterface* PDI, const FString& Name) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L480 _public function_ `void DrawSimMorphTarget(FPrimitiveDrawInterface* PDI, const FString& Name = "") const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")` — Will draw current morph target (if any) if no name or an invalid name is specified
- L485 _public function_ `void DrawPhysMeshShaded(const FDrawContext& Context = FDrawContext()) const`
- L486 _public function_ `void DrawKinematicColliderShaded(const FDrawContext& Context = FDrawContext()) const`
- L489 _public function_ `void DrawPhysMeshShaded(FPrimitiveDrawInterface* ) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L491 _public function_ `void DrawKinematicColliderShaded(FPrimitiveDrawInterface* ) const` — `UE_DEPRECATED(5.8, "Use Context version of this method instead.")`
- L497 _private member_ `const ::Chaos::FClothingSimulationSolver* Solver;` — Simulation objects

#### struct `Chaos::FClothVisualizationNoGC::FDrawFilter`  
`struct FDrawFilter`  
_L29-33_
- L31 _public member_ `FString VertexSet;`
- L32 _public member_ `int32 SingleVertex = INDEX_NONE;`

#### struct `Chaos::FClothVisualizationNoGC::FDrawContext`  
`struct FDrawContext`  
_L35-43_
- L37 _public function_ `explicit FDrawContext(FPrimitiveDrawInterface* InPDI = nullptr) : PDI(InPDI)`
- L41 _public member_ `FPrimitiveDrawInterface* PDI = nullptr;`
- L42 _public member_ `FDrawFilter Filter;`

#### struct `Chaos::FClothVisualizationNoGC::FDrawTextsContext`  
`struct FDrawTextsContext`  
_L45-54_
- L47 _public function_ `explicit FDrawTextsContext(FCanvas* InCanvas = nullptr, const FSceneView* InSceneView = nullptr) : Canvas(InCanvas), SceneView(InSceneView)`
- L51 _public member_ `FCanvas* Canvas = nullptr;`
- L52 _public member_ `const FSceneView* SceneView = nullptr;`
- L53 _public member_ `FDrawFilter Filter;`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace Chaos`

### `Plugins/ChaosCloth/Source/ChaosCloth/Public/ChaosCloth/ChaosClothingCacheSchema.h` (Public)


#### struct `Chaos::FClothingCacheSchema`  
`struct FClothingCacheSchema`  
_L18-37_
- L21 _public prototype_ `static void RecordPostSolve(const FClothingSimulationSolver& ClothSolver, FPendingFrameWrite& OutFrame, FReal InTime);` — This should only be called from the ClothSolver as a PostSolve callback (when it is safe to read directly from ClothSolver data)
- L23 _public prototype_ `static void PlaybackPreSolve(UChaosCache& InCache, FReal InTime, FPlaybackTickRecord& TickRecord, FClothingSimulationSolver& ClothSolver);` — This should only be called from the ClothSolver as a PreSolve callback (when it is safe to write directly to ClothSolver data)
- L24 _public prototype_ `static void LoadCacheData(UChaosCache* InCache, FReal InTime, FClothingSimulationCacheData& CacheData);`
- L26 _public prototype_ `static bool CacheIsValidForPlayback(UChaosCache* InCache);`
- L29 _private member_ `inline static const FName VelocityXName = TEXT("Vel`
- L30 _private member_ `inline static const FName VelocityYName = TEXT("Vel`
- L31 _private member_ `inline static const FName VelocityZName = TEXT("Vel`
- L32 _private member_ `inline static const FName PositionXName = TEXT("Pos`
- L33 _private member_ `inline static const FName PositionYName = TEXT("Pos`
- L34 _private member_ `inline static const FName PositionZName = TEXT("Pos`
- L36 _private member_ `inline static const FName ReferenceTransformsName = TEXT("Ref`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace Chaos`

### `Plugins/ChaosCloth/Source/ChaosCloth/Public/ChaosCloth/ChaosClothingPatternData.h` (Public)


#### struct `Chaos::FClothingPatternData`  
`struct FClothingPatternData`  
_L10-32_
- L12 _public member_ `FTriangleMesh PatternTriangleMesh;`
- L14 _public member_ `TConstArrayView<FVector2f> PatternPositions;`
- L15 _public member_ `TConstArrayView<uint32> PatternToWeldedIndices;`
- L16 _public member_ `TArray<TVec3<FVec2f>> WeldedFaceVertexPatternPositions;` — This will be empty if there are no PatternPositions
- L18 _public prototype_ `FClothingPatternData( int32 InNumParticles, const TConstArrayView<uint32>& InIndices, const TConstArrayView<FVector2f>& InPatternPositions, const TConstArrayView<uint32>& InPatternIndices, const TConstArrayView<uint32>& InPatternToWeldedIndices);`
- L26 _private prototype_ `void Reset();`
- L28 _private prototype_ `void GenerateDerivedPatternData( int32 InNumParticles, const TConstArrayView<uint32>& InIndices, const TConstArrayView<uint32>& InPatternIndices);`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Chaos`

### `Plugins/ChaosCloth/Source/ChaosCloth/Public/ChaosCloth/ChaosClothingSimulation.h` (Public)


#### class `Chaos::PRAGMA_DISABLE_DEPRECATION_WARNINGS`  
`PRAGMA_DISABLE_DEPRECATION_WARNINGS : public FClothingSimulationCommon PRAGMA_ENABLE_DEPRECATION_WARNINGS`  
_L28-211_
- reflection: `UE_DEPRECATED(5.7, "Use IClothingSimulationInterface instead.")`
- inherits: `FClothingSimulationCommonPRAGMA_ENABLE_DEPRECATION_WARNINGS`
- L33 _public prototype_ `FClothingSimulation();`
- L40 _protected prototype_ `virtual void Initialize() override;`
- L41 _protected prototype_ `virtual void Shutdown() override;`
- L43 _protected prototype_ `virtual IClothingSimulationContext* CreateContext() override;`
- L44 _protected function_ `virtual void DestroyContext(IClothingSimulationContext* InContext) override`
- L46 _protected prototype_ `virtual void CreateActor(USkeletalMeshComponent* InOwnerComponent, const UClothingAssetBase* InAsset, int32 SimDataIndex) override;`
- L47 _protected prototype_ `virtual void EndCreateActor() override;`
- L48 _protected prototype_ `virtual void DestroyActors() override;`
- L50 _protected prototype_ `virtual void FillContextAndPrepareTick(const USkeletalMeshComponent* InComponent, float InDeltaTime, IClothingSimulationContext* InOutContext, bool bIsInitialization, bool bForceTeleportResetOnly) override;`
- L51 _protected prototype_ `virtual bool ShouldSimulateLOD(int32 OwnerLODIndex) const override;`
- L52 _protected prototype_ `virtual void Simulate_AnyThread(const IClothingSimulationContext* InContext) override;`
- L53 _protected prototype_ `virtual void ForceClothNextUpdateTeleportAndReset_AnyThread() override;`
- L54 _protected function_ `virtual void HardResetSimulation(const IClothingSimulationContext* InContext) override`
- L58 _protected prototype_ `virtual void AppendSimulationData(TMap<int32, FClothSimulData>& OutData, const USkeletalMeshComponent* InOwnerComponent, const USkinnedMeshComponent* InOverrideComponent) const override;`
- L61 _protected prototype_ `virtual FBoxSphereBounds GetBounds(const USkeletalMeshComponent* InOwnerComponent) const override;` — Return bounds in local space (or in world space if InOwnerComponent is null).
- L63 _protected prototype_ `virtual void AddExternalCollisions(const FClothCollisionData& InData) override;`
- L64 _protected prototype_ `virtual void ClearExternalCollisions() override;`
- L68 _public prototype_ `void SetGravityOverride(const FVector& InGravityOverride);`
- L69 _public prototype_ `void DisableGravityOverride();`
- L72 _public prototype_ `void RefreshClothConfig(const IClothingSimulationContext* InContext);` — Function to be called if any of the assets' configuration parameters have changed
- L76 _public prototype_ `void RefreshPhysicsAsset();` — Function to be called if any of the assets' physics assets changes (colliders) This seems to only happen when UPhysicsAsset::RefreshPhysicsAssetChange is called with bFullClothRefresh set to false during changes created using the viewport manipulators.
- L79 _public function_ `virtual int32 GetNumCloths() const override`
- L80 _public function_ `virtual int32 GetNumKinematicParticles() const override`
- L81 _public function_ `virtual int32 GetNumDynamicParticles() const override`
- L82 _public function_ `virtual int32 GetNumIterations() const override`
- L83 _public function_ `virtual int32 GetNumSubsteps() const override`
- L84 _public function_ `virtual float GetSimulationTime() const override`
- L85 _public function_ `virtual bool IsTeleported() const override`
- L88 _public prototype_ `FClothingSimulationCloth* GetCloth(int32 ClothId);`
- L90 _public function_ `FClothingSimulationSolver* GetSolver()`
- L95 _public function_ `void DebugDrawPhysMeshShaded(FPrimitiveDrawInterface* PDI) const` — `UE_DEPRECATED(5.8, "Call debug draw methods directly from the GetClothVisualization() instead.")` — Editor only debug draw function
- L101 _public function_ `void DebugDrawParticleIndices(FCanvas* Canvas = nullptr, const FSceneView* SceneView = nullptr) const` — `UE_DEPRECATED(5.8, "Call debug draw methods directly from the GetClothVisualization() instead.")` — Editor & runtime debug draw functions
- L103 _public function_ `void DebugDrawElementIndices(FCanvas* Canvas = nullptr, const FSceneView* SceneView = nullptr) const` — `UE_DEPRECATED(5.8, "Call debug draw methods directly from the GetClothVisualization() instead.")`
- L105 _public function_ `void DebugDrawMaxDistanceValues(FCanvas* Canvas = nullptr, const FSceneView* SceneView = nullptr) const` — `UE_DEPRECATED(5.8, "Call debug draw methods directly from the GetClothVisualization() instead.")`
- L107 _public function_ `void DebugDrawLocalSpaceBoneNames(FCanvas* Canvas = nullptr, const FSceneView* SceneView = nullptr) const` — `UE_DEPRECATED(5.8, "Call debug draw methods directly from the GetClothVisualization() instead.")`
- L109 _public function_ `void DebugDrawPhysMeshWired(FPrimitiveDrawInterface* PDI = nullptr) const` — `UE_DEPRECATED(5.8, "Call debug draw methods directly from the GetClothVisualization() instead.")`
- L111 _public function_ `void DebugDrawAnimMeshWired(FPrimitiveDrawInterface* PDI = nullptr) const` — `UE_DEPRECATED(5.8, "Call debug draw methods directly from the GetClothVisualization() instead.")`
- L113 _public function_ `void DebugDrawAnimNormals(FPrimitiveDrawInterface* PDI = nullptr) const` — `UE_DEPRECATED(5.8, "Call debug draw methods directly from the GetClothVisualization() instead.")`
- L115 _public function_ `void DebugDrawAnimVelocities(FPrimitiveDrawInterface* PDI = nullptr) const` — `UE_DEPRECATED(5.8, "Call debug draw methods directly from the GetClothVisualization() instead.")`
- L117 _public function_ `void DebugDrawPointNormals(FPrimitiveDrawInterface* PDI = nullptr) const` — `UE_DEPRECATED(5.8, "Call debug draw methods directly from the GetClothVisualization() instead.")`
- L119 _public function_ `void DebugDrawPointVelocities(FPrimitiveDrawInterface* PDI = nullptr) const` — `UE_DEPRECATED(5.8, "Call debug draw methods directly from the GetClothVisualization() instead.")`
- L121 _public function_ `void DebugDrawCollision(FPrimitiveDrawInterface* PDI = nullptr) const` — `UE_DEPRECATED(5.8, "Call debug draw methods directly from the GetClothVisualization() instead.")`
- L123 _public function_ `void DebugDrawBackstops(FPrimitiveDrawInterface* PDI = nullptr) const` — `UE_DEPRECATED(5.8, "Call debug draw methods directly from the GetClothVisualization() instead.")`
- L125 _public function_ `void DebugDrawBackstopDistances(FPrimitiveDrawInterface* PDI = nullptr) const` — `UE_DEPRECATED(5.8, "Call debug draw methods directly from the GetClothVisualization() instead.")`
- L127 _public function_ `void DebugDrawMaxDistances(FPrimitiveDrawInterface* PDI = nullptr) const` — `UE_DEPRECATED(5.8, "Call debug draw methods directly from the GetClothVisualization() instead.")`
- L129 _public function_ `void DebugDrawAnimDrive(FPrimitiveDrawInterface* PDI = nullptr) const` — `UE_DEPRECATED(5.8, "Call debug draw methods directly from the GetClothVisualization() instead.")`
- L131 _public function_ `void DebugDrawEdgeConstraint(FPrimitiveDrawInterface* PDI = nullptr) const` — `UE_DEPRECATED(5.8, "Call debug draw methods directly from the GetClothVisualization() instead.")`
- L133 _public function_ `void DebugDrawBendingConstraint(FPrimitiveDrawInterface* PDI = nullptr) const` — `UE_DEPRECATED(5.8, "Call debug draw methods directly from the GetClothVisualization() instead.")`
- L135 _public function_ `void DebugDrawLongRangeConstraint(FPrimitiveDrawInterface* PDI = nullptr) const` — `UE_DEPRECATED(5.8, "Call debug draw methods directly from the GetClothVisualization() instead.")`
- L137 _public function_ `void DebugDrawWindAndPressureForces(FPrimitiveDrawInterface* PDI = nullptr) const` — `UE_DEPRECATED(5.8, "Call debug draw methods directly from the GetClothVisualization() instead.")`
- L139 _public function_ `void DebugDrawWindVelocity(FPrimitiveDrawInterface* PDI = nullptr) const` — `UE_DEPRECATED(5.8, "Call debug draw methods directly from the GetClothVisualization() instead.")`
- L141 _public function_ `void DebugDrawLocalSpace(FPrimitiveDrawInterface* PDI = nullptr) const` — `UE_DEPRECATED(5.8, "Call debug draw methods directly from the GetClothVisualization() instead.")`
- L143 _public function_ `void DebugDrawSelfCollision(FPrimitiveDrawInterface* PDI = nullptr) const` — `UE_DEPRECATED(5.8, "Call debug draw methods directly from the GetClothVisualization() instead.")`
- L145 _public function_ `void DebugDrawSelfIntersection(FPrimitiveDrawInterface* PDI = nullptr) const` — `UE_DEPRECATED(5.8, "Call debug draw methods directly from the GetClothVisualization() instead.")`
- L147 _public function_ `void DebugDrawBounds(FPrimitiveDrawInterface* PDI = nullptr) const` — `UE_DEPRECATED(5.8, "Call debug draw methods directly from the GetClothVisualization() instead.")`
- L149 _public function_ `void DebugDrawGravity(FPrimitiveDrawInterface* PDI = nullptr) const` — `UE_DEPRECATED(5.8, "Call debug draw methods directly from the GetClothVisualization() instead.")`
- L151 _public function_ `void DebugDrawTeleportReset(FPrimitiveDrawInterface* PDI = nullptr) const` — `UE_DEPRECATED(5.8, "Call debug draw methods directly from the GetClothVisualization() instead.")`
- L153 _public function_ `void DebugDrawExtremlyDeformedEdges(FPrimitiveDrawInterface* PDI = nullptr) const` — `UE_DEPRECATED(5.8, "Call debug draw methods directly from the GetClothVisualization() instead.")`
- L155 _public function_ `void DebugDrawVelocityScale(FPrimitiveDrawInterface* PDI = nullptr) const` — `UE_DEPRECATED(5.8, "Call debug draw methods directly from the GetClothVisualization() instead.")`
- L159 _public function_ `const FClothVisualizationNoGC* GetClothVisualization() const` — Return the visualization object for this simulation.
- L165 _private prototype_ `void ResetStats();`
- L166 _private prototype_ `void UpdateStats(const FClothingSimulationCloth* Cloth);`
- L168 _private prototype_ `void UpdateSimulationFromSharedSimConfig();`
- L170 _private prototype_ `const FClothingSimulationContext* GetClothingSimulationContext(const USkeletalMeshComponent* SkeletalMeshComponent) const;`
- L174 _private member_ `FClothVisualizationNoGC Visualization;` — Visualization object
- L177 _private member_ `TUniquePtr<FClothingSimulationSolver> Solver;` — Simulation objects
- L178 _private member_ `TArray<TUniquePtr<FClothingSimulationMesh>> Meshes;`
- L179 _private member_ `TArray<TUniquePtr<FClothingSimulationCloth>> Cloths;`
- L180 _private member_ `TArray<TUniquePtr<FClothingSimulationCollider>> Colliders;`
- L181 _private member_ `TArray<TUniquePtr<FClothingSimulationConfig>> Configs;`
- L184 _private member_ `FClothCollisionData ExternalCollisionData;` — External collision Data
- L187 _private member_ `const UChaosClothSharedSimConfig* ClothSharedSimConfig;` — Shared cloth config
- L189 _private member_ `TBitArray<> LODHasAnyRenderClothMappingData;` — Used by ShouldSimulateLOD
- L192 _private member_ `TAtomic<int32> NumCloths;` — Properties that must be readable from all threads
- L193 _private member_ `TAtomic<int32> NumKinematicParticles;`
- L194 _private member_ `TAtomic<int32> NumDynamicParticles;`
- L195 _private member_ `TAtomic<int32> NumIterations;`
- L196 _private member_ `TAtomic<int32> NumSubsteps;`
- L197 _private member_ `TAtomic<float> SimulationTime;`
- L198 _private member_ `TAtomic<bool> bIsTeleported;`
- L201 _private member_ `bool bUseLocalSpaceSimulation;` — Overrides
- L202 _private member_ `bool bUseGravityOverride;`
- L203 _private member_ `FVector GravityOverride;`
- L204 _private member_ `FReal MaxDistancesMultipliers;`
- L207 _private member_ `int32 StepCount;`
- L208 _private member_ `int32 ResetCount;`
- L210 _private member_ `mutable bool bHasInvalidReferenceBoneTransforms;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace Chaos`
- L25 _typedef_ `typedef FClothingSimulationContextCommon FClothingSimulationContext;` (scope `Chaos`)
- L215 _macro_ `#define CHAOS_GET_SIM_DATA_ISPC_ENABLED_DEFAULT 1`
- L219 _macro_ `#define USE_ISPC_KERNEL_CONSOLE_VARIABLES_IN_SHIPPING 0`
- L224 _variable_ `static constexpr bool bChaos_GetSimData_ISPC_Enabled = INTEL_ISPC && CHAOS_GET_SIM_DATA_ISPC_ENABLED_DEFAULT;`
- L226 _externvar_ `extern bool bChaos_GetSimData_ISPC_Enabled;`

### `Plugins/ChaosCloth/Source/ChaosCloth/Public/ChaosCloth/ChaosClothingSimulationAccessoryMesh.h` (Public)


#### class `Chaos::FClothingSimulationAccessoryMesh`  
`class FClothingSimulationAccessoryMesh`  
_L19-108_
- desc: Accessory mesh used as an input to a simulation. They are expected to share topology (e.g., Indices, PatternIndices) with their associated FClothingSimulationMesh
- L22 _public prototype_ `FClothingSimulationAccessoryMesh(const FClothingSimulationMesh& InMesh, const FName& InAccessoryMeshName);`
- L24 _public prototype_ `virtual ~FClothingSimulationAccessoryMesh();`
- L26 _public prototype_ `FClothingSimulationAccessoryMesh(const FClothingSimulationAccessoryMesh&) = delete;`
- L27 _public prototype_ `FClothingSimulationAccessoryMesh(FClothingSimulationAccessoryMesh&&) = delete;`
- L28 _public prototype_ `FClothingSimulationAccessoryMesh& operator=(const FClothingSimulationAccessoryMesh&) = delete;`
- L29 _public prototype_ `FClothingSimulationAccessoryMesh& operator=(FClothingSimulationAccessoryMesh&&) = delete;`
- L31 _public function_ `const FName& GetAccessoryMeshName() const`
- L34 _public prototype_ `virtual int32 GetNumPoints() const = 0;` — Return the number of points.
- L37 _public prototype_ `virtual int32 GetNumPatternPoints() const = 0;` — Return the number of pattern points (2d, unwelded).
- L40 _public prototype_ `virtual TConstArrayView<FVector3f> GetPositions() const = 0;` — Return the source mesh positions (pre-skinning).
- L43 _public prototype_ `virtual TConstArrayView<FVector2f> GetPatternPositions() const = 0;` — Return the source mesh 2d pattern positions.
- L46 _public prototype_ `virtual TConstArrayView<FVector3f> GetNormals() const = 0;` — Return the source mesh normals (pre-skinning).
- L49 _public prototype_ `virtual TConstArrayView<FClothVertBoneData> GetBoneData() const = 0;` — Return the bone data containing bone weights and influences.
- L52 _public function_ `virtual int32 FindMorphTargetByName(const FString& Name) const` — Return the MorphTargetIndex for a given Morph Target Name, if it exists. NOTE: currently only the DefaultAccessoryMesh supports Morph Targets.
- L58 _public function_ `virtual TConstArrayView<FString> GetAllMorphTargetNames() const` — Get a list of all MorphTargets. (Index matches FindMorphTargetByName)
- L64 _public function_ `virtual TConstArrayView<FVector3f> GetMorphTargetPositionDeltas(int32 MorphTargetIndex) const` — Get all Morph Target position deltas for a given MorphTargetIndex (e.g., index returned by FindMorphTargetByName). Deltas index back to Positions via MorphTargetIndices
- L70 _public function_ `virtual TConstArrayView<FVector3f> GetMorphTargetTangentZDeltas(int32 MorphTargetIndex) const` — Get all Morph Target tangent z (normal) deltas for a given MorphTargetIndex (e.g., index returned by FindMorphTargetByName). Deltas index back to Normals via MorphTargetIndices
- L76 _public function_ `virtual TConstArrayView<int32> GetMorphTargetIndices(int32 MorphTargetIndex) const` — Get all Morph Target indices for a given MorphTargetIndex (e.g., index returned by FindMorphTargetByName). These indices can map MorphTargetDeltas back to Positions.
- L82 _public prototype_ `void Update( const FClothingSimulationSolver* Solver, const TArrayView<Softs::FSolverVec3>& OutPositions, const TArrayView<Softs::FSolverVec3>& OutNormals, int32 ActiveMorphTargetIndex = INDEX_NONE, float ActiveMorphTargetWeight = 0.f) const;` — Update the mesh for the next solver step, doing skinning and matching the shapes during LOD changes.
- L89 _public prototype_ `void ApplyMorphTarget( int32 ActiveMorphTargetIndex, float ActiveMorphTargetWeight, const TArrayView<Softs::FSolverVec3>& InOutPositions, const TArrayView<Softs::FSolverVec3>& InOutNormals) const;`
- L97 _private prototype_ `void SkinPhysicsMesh( int32 ActiveMorphTargetIndex, float ActiveMorphTargetWeight, const FReal LocalSpaceScale, const FVec3& LocalSpaceLocation, const TArrayView<Softs::FSolverVec3>& OutPositions, const TArrayView<Softs::FSolverVec3>& OutNormals) const;`
- L106 _protected member_ `const FClothingSimulationMesh& Mesh;`
- L107 _protected member_ `const FName AccessoryMeshName;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API CHAOSCLOTH_API`
- L13 _namespace_ `namespace Chaos`
- L112 _macro_ `#define CHAOS_SKIN_PHYSICS_MESH_ISPC_ENABLED_DEFAULT 1`
- L116 _macro_ `#define USE_ISPC_KERNEL_CONSOLE_VARIABLES_IN_SHIPPING 0`
- L121 _variable_ `static constexpr bool bChaos_SkinPhysicsMesh_ISPC_Enabled = INTEL_ISPC && CHAOS_SKIN_PHYSICS_MESH_ISPC_ENABLED_DEFAULT;`
- L123 _externvar_ `extern bool bChaos_SkinPhysicsMesh_ISPC_Enabled;`

### `Plugins/ChaosCloth/Source/ChaosCloth/Public/ChaosCloth/ChaosClothingSimulationCloth.h` (Public)


#### class `Chaos::FClothingSimulationCloth`  
`class FClothingSimulationCloth final`  
_L22-249_
- desc: Cloth simulation node
- L32 _public prototype_ `FClothingSimulationCloth( FClothingSimulationConfig* InConfig, FClothingSimulationMesh* InMesh, TArray<FClothingSimulationCollider*>&& InColliders, uint32 InGroupId);`
- L38 _public prototype_ `~FClothingSimulationCloth();`
- L40 _public prototype_ `FClothingSimulationCloth(const FClothingSimulationCloth&) = delete;`
- L41 _public prototype_ `FClothingSimulationCloth(FClothingSimulationCloth&&) = delete;`
- L42 _public prototype_ `FClothingSimulationCloth& operator=(const FClothingSimulationCloth&) = delete;`
- L43 _public prototype_ `FClothingSimulationCloth& operator=(FClothingSimulationCloth&&) = delete;`
- L45 _public function_ `uint32 GetGroupId() const`
- L46 _public function_ `uint32 GetLODIndex(const FClothingSimulationSolver* Solver) const`
- L48 _public function_ `int32 GetNumActiveKinematicParticles() const`
- L49 _public function_ `int32 GetNumActiveDynamicParticles() const`
- L52 _public function_ `void SetMaxDistancesMultiplier(FRealSingle InMaxDistancesMultiplier)` — ---- Animatable property setters ----
- L54 _public function_ `void Reset()`
- L55 _public function_ `void Teleport()`
- L56 _public function_ `void ResetRestLengthsWithMorphTarget(const FString& MorphTargetName)`
- L64 _public function_ `FClothingSimulationMesh* GetMesh() const` — ---- Node property getters/setters
- L65 _public prototype_ `void SetMesh(FClothingSimulationMesh* InMesh);`
- L67 _public function_ `FClothingSimulationConfig* GetConfig() const`
- L68 _public prototype_ `void SetConfig(FClothingSimulationConfig* InConfig);`
- L70 _public function_ `const TArray<FClothingSimulationCollider*>& GetColliders() const`
- L71 _public prototype_ `void SetColliders(TArray<FClothingSimulationCollider*>&& InColliders);`
- L72 _public prototype_ `void AddCollider(FClothingSimulationCollider* InCollider);`
- L73 _public prototype_ `void RemoveCollider(FClothingSimulationCollider* InCollider);`
- L74 _public prototype_ `void RemoveColliders();`
- L79 _public prototype_ `TConstArrayView<Softs::FSolverVec3> GetAnimationPositions(const FClothingSimulationSolver* Solver) const;` — ---- Debugging/visualization functions Return the solver's input positions for this cloth source current LOD, not thread safe, call must be done right after the solver update.
- L81 _public prototype_ `TConstArrayView<Softs::FSolverVec3> GetOldAnimationPositions(const FClothingSimulationSolver* Solver) const;` — Return the solver's input positions for this cloth source current LOD, not thread safe, call must be done right after the solver update.
- L83 _public prototype_ `TConstArrayView<Softs::FSolverVec3> GetAnimationNormals(const FClothingSimulationSolver* Solver) const;` — Return the solver's input normals for this cloth source current LOD, not thread safe, call must be done right after the solver update.
- L85 _public prototype_ `TConstArrayView<Softs::FSolverVec3> GetAnimationVelocities(const FClothingSimulationSolver* Solver) const;` — Return the solver's input velocities for this cloth source current LOD, not thread safe, call must be done right after the solver update.
- L86 _public prototype_ `bool AccessoryMeshExists(const FClothingSimulationSolver* Solver, const FName& AccessoryMeshName) const;`
- L88 _public prototype_ `TConstArrayView<Softs::FSolverVec3> GetAccessoryMeshPositions(const FClothingSimulationSolver* Solver, const FName& AccessoryMeshName) const;` — Return the solver's input positions for this cloth source current LOD, not thread safe, call must be done right after the solver update.
- L90 _public prototype_ `TConstArrayView<Softs::FSolverVec3> GetOldAccessoryMeshPositions(const FClothingSimulationSolver* Solver, const FName& AccessoryMeshName) const;` — Return the solver's input positions for this cloth source current LOD, not thread safe, call must be done right after the solver update.
- L92 _public prototype_ `TConstArrayView<Softs::FSolverVec3> GetAccessoryMeshNormals(const FClothingSimulationSolver* Solver, const FName& AccessoryMeshName) const;` — Return the solver's input normals for this cloth source current LOD, not thread safe, call must be done right after the solver update.
- L94 _public prototype_ `TConstArrayView<Softs::FSolverVec3> GetAccessoryMeshVelocities(const FClothingSimulationSolver* Solver, const FName& AccessoryMeshName) const;` — Return the solver's input velocities for this cloth source current LOD, not thread safe, call must be done right after the solver update.
- L96 _public prototype_ `TConstArrayView<Softs::FSolverVec3> GetParticlePositions(const FClothingSimulationSolver* Solver) const;` — Return the solver's positions for this cloth current LOD, not thread safe, call must be done right after the solver update.
- L98 _public prototype_ `TConstArrayView<Softs::FSolverVec3> GetParticleVelocities(const FClothingSimulationSolver* Solver) const;` — Return the solver's velocities for this cloth current LOD, not thread safe, call must be done right after the solver update.
- L100 _public prototype_ `TConstArrayView<Softs::FSolverVec3> GetParticleNormals(const FClothingSimulationSolver* Solver) const;` — Return the solver's normals for this cloth current LOD, not thread safe, call must be done right after the solver update.
- L102 _public prototype_ `TConstArrayView<Softs::FSolverReal> GetParticleInvMasses(const FClothingSimulationSolver* Solver) const;` — Return the solver's inverse masses for this cloth current LOD, not thread safe, call must be done right after the solver update.
- L105 _public prototype_ `TVec3<FRealSingle> GetGravity(const FClothingSimulationSolver* Solver) const;` — Return the current gravity as applied by the solver using the various overrides, not thread safe, call must be done right after the solver update. Does not have GravityScale applied when using Force-based solver (Get the per-particle value directly from cloth constraints' external forces).
- L107 _public prototype_ `FAABB3 CalculateBoundingBox(const FClothingSimulationSolver* Solver) const;` — Return the current bounding box based on a given solver, not thread safe, call must be done right after the solver update.
- L109 _public prototype_ `int32 GetParticleRangeId(const FClothingSimulationSolver* Solver) const;` — Return the current LOD ParticleRangeId, or INDEX_NONE if no LOD is currently selected.
- L111 _public function_ `int32 GetOffset(const FClothingSimulationSolver* Solver) const` — `UE_DEPRECATED(5.4, "Offset has been renamed ParticleRangeId to reflect that it is no longer an offset.")`
- L113 _public prototype_ `int32 GetNumParticles(const FClothingSimulationSolver* Solver) const;` — Return the current LOD num particles, or 0 if no LOD is currently selected.
- L115 _public prototype_ `const FTriangleMesh& GetTriangleMesh(const FClothingSimulationSolver* Solver) const;` — Return the current LOD mesh.
- L117 _public prototype_ `TConstArrayView<FRealSingle> GetWeightMapByName(const FClothingSimulationSolver* Solver, const FString& Name) const;` — Return the weight map of the specified name if available on the current LOD, or an empty array view otherwise.
- L119 _public prototype_ `TConstArrayView<FRealSingle> GetWeightMapByProperty(const FClothingSimulationSolver* Solver, const FName& Property) const;` — Return the weight map of the specified property name if it exists and is available on the current LOD, or an empty array view otherwise.
- L122 _public function_ `TConstArrayView<FRealSingle> GetWeightMapByProperty(const FClothingSimulationSolver* Solver, const StringType Property) const` — `UE_DEPRECATED(5.7, "Use FName property version of this method instead")`
- L127 _public prototype_ `TSet<FString> GetAllWeightMapNames() const;` — Return list of weight map names available across all LODs
- L129 _public prototype_ `TConstArrayView<int32> GetFaceIntMapByName(const FClothingSimulationSolver* Solver, const FString& Name) const;` — Return the face int map of the specified name if available on the current LOD, or an empty array view otherwise.
- L131 _public prototype_ `TConstArrayView<int32> GetFaceIntMapByProperty(const FClothingSimulationSolver* Solver, const FName& Property) const;` — Return the face int map of the specified property name if it exists and is available on the current LOD, or an empty array view otherwise.
- L134 _public function_ `TConstArrayView<int32> GetFaceIntMapByProperty(const FClothingSimulationSolver* Solver, const StringType Property) const` — `UE_DEPRECATED(5.7, "Use FName property version of this method instead")`
- L138 _public prototype_ `TSet<FString> GetAllVertexSetNames() const;`
- L140 _public prototype_ `const TSet<int32>* GetVertexSetByName(const FClothingSimulationSolver* Solver, const FString& Name) const;` — Return the vertex set of the specified name if available on the current LOD.
- L142 _public prototype_ `const TSet<int32>* GetVertexSetByProperty(const FClothingSimulationSolver* Solver, const FName& Property) const;` — Return the vertex set  of the specified property name if it exists and is available on the current LOD.
- L143 _public prototype_ `FString GetPropertyString(const FClothingSimulationSolver* Solver, const FName& Name) const;`
- L145 _public prototype_ `const TArray<TConstArrayView<TTuple<int32, int32, float>>>& GetTethers(const FClothingSimulationSolver* Solver) const;` — Return the current LOD tethers.
- L147 _public prototype_ `int32 GetReferenceBoneIndex() const;` — Return the reference bone index for this cloth.
- L149 _public function_ `const FRigidTransform3& GetReferenceSpaceTransform() const` — Return the local reference space transform for this cloth.
- L150 _public prototype_ `int32 GetCurrentMorphTargetIndex(const FClothingSimulationSolver* Solver) const;`
- L151 _public prototype_ `FRealSingle GetCurrentMorphTargetWeight(const FClothingSimulationSolver* Solver) const;`
- L152 _public prototype_ `TSet<FString> GetAllMorphTargetNames() const;`
- L153 _public prototype_ `TSet<FName> GetAllAccessoryMeshNames() const;`
- L155 _public function_ `FRealSingle GetTimeSinceLastTeleport() const`
- L156 _public function_ `FRealSingle GetTimeSinceLastReset() const`
- L161 _public prototype_ `void Add(FClothingSimulationSolver* Solver);` — ---- Solver interface ----
- L162 _public prototype_ `void Remove(FClothingSimulationSolver* Solver);`
- L164 _public prototype_ `void PreUpdate(FClothingSimulationSolver* Solver);`
- L165 _public prototype_ `void Update(FClothingSimulationSolver* Solver);`
- L166 _public prototype_ `void PostUpdate(FClothingSimulationSolver* Solver);`
- L168 _public prototype_ `void UpdateFromCache(const FClothingSimulationCacheData& CacheData);`
- L170 _public prototype_ `void ApplyPreSimulationTransforms(FClothingSimulationSolver* Solver, const Softs::FSolverVec3& DeltaLocalSpaceLocation, const Softs::FSolverRigidTransform3& GroupSpaceTransform, const Softs::FSolverReal DeltaTime);`
- L171 _public prototype_ `void PreSubstep(FClothingSimulationSolver* Solver, const Softs::FSolverReal InterpolationAlpha);`
- L175 _public prototype_ `UE_CHAOS_DECLARE_INDEXLESS_PROPERTYCOLLECTION_NAME(UseGeodesicTethers, bool);`
- L176 _public prototype_ `UE_CHAOS_DECLARE_INDEXLESS_PROPERTYCOLLECTION_NAME(MassMode, int32);`
- L177 _public prototype_ `UE_CHAOS_DECLARE_INDEXLESS_PROPERTYCOLLECTION_NAME(MinPerParticleMass, float);`
- L178 _public prototype_ `UE_CHAOS_DECLARE_INDEXLESS_PROPERTYCOLLECTION_NAME(MassValue, float);`
- L180 _public prototype_ `UE_CHAOS_DECLARE_INDEXLESS_PROPERTYCOLLECTION_NAME(UseGravityOverride, bool);`
- L181 _public prototype_ `UE_CHAOS_DECLARE_INDEXLESS_PROPERTYCOLLECTION_NAME(GravityOverride, FVector3f);`
- L182 _public prototype_ `UE_CHAOS_DECLARE_INDEXLESS_PROPERTYCOLLECTION_NAME(GravityScale, float);`
- L184 _public prototype_ `UE_CHAOS_DECLARE_INDEXLESS_PROPERTYCOLLECTION_NAME(VelocityScaleSpace, int32);`
- L185 _public prototype_ `UE_CHAOS_DECLARE_INDEXLESS_PROPERTYCOLLECTION_NAME(LinearVelocityScale, FVector3f);`
- L186 _public prototype_ `UE_CHAOS_DECLARE_INDEXLESS_PROPERTYCOLLECTION_NAME(AngularVelocityScale, float);`
- L187 _public prototype_ `UE_CHAOS_DECLARE_INDEXLESS_PROPERTYCOLLECTION_NAME(MaxVelocityScale, float);`
- L188 _public prototype_ `UE_CHAOS_DECLARE_INDEXLESS_PROPERTYCOLLECTION_NAME(MaxLinearVelocity, FVector3f);`
- L189 _public prototype_ `UE_CHAOS_DECLARE_INDEXLESS_PROPERTYCOLLECTION_NAME(MaxLinearAcceleration, FVector3f);`
- L190 _public prototype_ `UE_CHAOS_DECLARE_INDEXLESS_PROPERTYCOLLECTION_NAME(MaxAngularVelocity, float);`
- L191 _public prototype_ `UE_CHAOS_DECLARE_INDEXLESS_PROPERTYCOLLECTION_NAME(MaxAngularAcceleration, float);`
- L192 _public prototype_ `UE_CHAOS_DECLARE_INDEXLESS_PROPERTYCOLLECTION_NAME(FictitiousAngularScale, float);`
- L193 _public prototype_ `UE_CHAOS_DECLARE_INDEXLESS_PROPERTYCOLLECTION_NAME(FictitiousForcesModel, int32);`
- L195 _public prototype_ `UE_CHAOS_DECLARE_INDEXLESS_PROPERTYCOLLECTION_NAME(UsePointBasedWindModel, bool);`
- L197 _public prototype_ `UE_CHAOS_DECLARE_INDEXLESS_PROPERTYCOLLECTION_NAME(DampingCoefficient, float);`
- L198 _public prototype_ `UE_CHAOS_DECLARE_INDEXLESS_PROPERTYCOLLECTION_NAME(LocalDampingCoefficient, float);`
- L200 _public prototype_ `UE_CHAOS_DECLARE_INDEXLESS_PROPERTYCOLLECTION_NAME(CollisionThickness, float);`
- L201 _public prototype_ `UE_CHAOS_DECLARE_INDEXLESS_PROPERTYCOLLECTION_NAME(FrictionCoefficient, float);`
- L202 _public prototype_ `UE_CHAOS_DECLARE_INDEXLESS_PROPERTYCOLLECTION_NAME(UseCCD, bool);`
- L204 _public prototype_ `UE_CHAOS_DECLARE_INDEXLESS_PROPERTYCOLLECTION_NAME(KinematicVertices3D, bool);` — Selection set name string property; bool value is not actually used.
- L207 _private prototype_ `int32 GetNumParticles(int32 InLODIndex) const;`
- L208 _private prototype_ `int32 GetParticleRangeId(const FClothingSimulationSolver* Solver, int32 InLODIndex) const;`
- L214 _private member_ `FClothingSimulationMesh* Mesh = nullptr;` — Cloth parameters
- L215 _private member_ `FClothingSimulationConfig* Config = nullptr;`
- L216 _private member_ `TArray<FClothingSimulationCollider*> Colliders;`
- L217 _private member_ `uint32 GroupId = 0;`
- L219 _private member_ `TSharedPtr<FManagedArrayCollection> PropertyCollection;` — Used for backward compatibility only, otherwise the properties are owned by the Config
- L221 _private member_ `FRealSingle MaxDistancesMultiplier = 1.f;` — Legacy multiplier
- L223 _private member_ `bool bUseLODIndexOverride = false;`
- L224 _private member_ `int32 LODIndexOverride = 0;`
- L225 _private member_ `bool bNeedsReset = false;`
- L226 _private member_ `bool bNeedsTeleport = false;`
- L229 _private member_ `bool bResetRestLengthsFromMorphTarget = false;` — Reset restlengths from morph target.
- L230 _private member_ `FString ResetRestLengthsMorphTargetName;`
- L233 _private member_ `FRealSingle TimeSinceLastTeleport = 0.f;`
- L234 _private member_ `FRealSingle TimeSinceLastReset = 0.f;`
- L238 _private member_ `FRigidTransform3 ReferenceSpaceTransform;` — Reference space transform
- L239 _private member_ `FVec3 AppliedReferenceSpaceVelocity;` — After scaling/clamping
- L240 _private member_ `FVec3 AppliedReferenceSpaceAngularVelocity;` — After scaling/clamping
- L243 _private member_ `TArray<TUniquePtr<FLODData>> LODData;` — LOD data
- L244 _private member_ `TMap<FClothingSimulationSolver*, int32> LODIndices;`
- L247 _private member_ `int32 NumActiveKinematicParticles = 0;` — Stats
- L248 _private member_ `int32 NumActiveDynamicParticles = 0;`

#### enum `Chaos::FClothingSimulationCloth::EMassMode`  
`enum EMassMode`  
_L25-30_
- L27 _public enumerator_ `UniformMass`
- L28 _public enumerator_ `TotalMass`
- L29 _public enumerator_ `Density`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace Chaos`

### `Plugins/ChaosCloth/Source/ChaosCloth/Public/ChaosCloth/ChaosClothingSimulationCollider.h` (Public)


#### struct `Chaos::FLevelSetCollisionData`  
`struct FLevelSetCollisionData`  
_L25-36_
- L27 _public member_ `const TSharedPtr<Chaos::FLevelSet, ESPMode::ThreadSafe> LevelSet;`
- L28 _public member_ `FTransform Transform;`
- L29 _public member_ `int32 BoneIndex;`
- L31 _public function_ `FLevelSetCollisionData(const TSharedPtr<Chaos::FLevelSet, ESPMode::ThreadSafe>& InLevelSet, const FTransform& InTransform, int32 InBoneIndex) : LevelSet(InLevelSet) , Transform(InTransform) , BoneIndex(InBoneIndex)`

#### struct `Chaos::FSkinnedLevelSetCollisionData`  
`struct FSkinnedLevelSetCollisionData`  
_L38-49_
- L40 _public member_ `const TRefCountPtr<Chaos::TWeightedLatticeImplicitObject<Chaos::FLevelSet>> WeightedLevelSet;`
- L41 _public member_ `int32 BoneIndex;`
- L42 _public member_ `TArray<int32> MappedSkinnedBones;`
- L44 _public function_ `FSkinnedLevelSetCollisionData(const TRefCountPtr<Chaos::TWeightedLatticeImplicitObject<Chaos::FLevelSet>>& InWeightedLevelSet, int32 InBoneIndex, TArray<int32>&& InMappedSkinnedBones) : WeightedLevelSet(InWeightedLevelSet) , BoneIndex(InBoneIndex) , MappedSkinnedBones(MoveTemp(InMappedSkinnedBones))`

#### struct `Chaos::FMLLevelSetCollisionData`  
`struct FMLLevelSetCollisionData`  
_L51-62_
- L53 _public member_ `const TSharedPtr<Chaos::FMLLevelSet> MLLevelSet;`
- L54 _public member_ `int32 BoneIndex;`
- L55 _public member_ `TArray<int32> MappedActiveBoneIndices;`
- L57 _public function_ `FMLLevelSetCollisionData(const TSharedPtr<Chaos::FMLLevelSet>& InMLLevelSet, int32 InBoneIndex, TArray<int32>&& InMappedActiveBoneIndices) : MLLevelSet(InMLLevelSet) , BoneIndex(InBoneIndex) , MappedActiveBoneIndices(MoveTemp(InMappedActiveBoneIndices))`

#### struct `Chaos::FSkinnedTriangleMeshCollisionData`  
`struct FSkinnedTriangleMeshCollisionData`  
_L64-75_
- L66 _public member_ `const TRefCountPtr<Chaos::FSkinnedTriangleMesh> SkinnedTriangleMesh;`
- L67 _public member_ `int32 BoneIndex;`
- L68 _public member_ `TArray<int32> MappedSkinnedBones;`
- L70 _public function_ `FSkinnedTriangleMeshCollisionData(const TRefCountPtr<Chaos::FSkinnedTriangleMesh>& InSkinnedTriangleMesh, int32 InBoneIndex, TArray<int32>&& InMappedSkinnedBones) : SkinnedTriangleMesh(InSkinnedTriangleMesh) , BoneIndex(InBoneIndex) , MappedSkinnedBones(MoveTemp(InMappedSkinnedBones))`

#### struct `Chaos::FClothCollisionDataExtended`  
`struct FClothCollisionDataExtended`  
_L77-91_
- L79 _public member_ `TArray<FLevelSetCollisionData> LevelSets;`
- L80 _public member_ `TArray<FSkinnedLevelSetCollisionData> SkinnedLevelSets;`
- L81 _public member_ `TArray<FMLLevelSetCollisionData> MLLevelSets;`
- L82 _public member_ `TArray<FSkinnedTriangleMeshCollisionData> SkinnedTriangleMeshes;`
- L84 _public function_ `void Reset()`

#### class `Chaos::FClothingSimulationCollider`  
`class FClothingSimulationCollider final`  
_L94-189_
- desc: Collider simulation node
- L105 _public prototype_ `FClothingSimulationCollider(const UPhysicsAsset* InPhysicsAsset, const FReferenceSkeleton* InReferenceSkeleton);`
- L106 _public prototype_ `~FClothingSimulationCollider();`
- L108 _public prototype_ `FClothingSimulationCollider(const FClothingSimulationCollider&) = delete;`
- L109 _public prototype_ `FClothingSimulationCollider(FClothingSimulationCollider&&) = delete;`
- L110 _public prototype_ `FClothingSimulationCollider& operator=(const FClothingSimulationCollider&) = delete;`
- L111 _public prototype_ `FClothingSimulationCollider& operator=(FClothingSimulationCollider&&) = delete;`
- L113 _public prototype_ `int32 GetNumGeometries() const;`
- L116 _public prototype_ `FClothCollisionData GetCollisionData(const FClothingSimulationSolver* Solver, const FClothingSimulationCloth* Cloth) const;` — Return source (untransformed) collision data for LODless, external and active LODs.
- L120 _public function_ `void SetCollisionData(const FClothCollisionData* InCollisionData)` — ---- Animatable property setters ---- Set external collision data, will only get updated when used as a Solver Collider TODO: Subclass collider?
- L124 _public prototype_ `void Add(FClothingSimulationSolver* Solver, FClothingSimulationCloth* Cloth);` — ---- Cloth interface ----
- L125 _public prototype_ `void Remove(FClothingSimulationSolver* Solver, FClothingSimulationCloth* Cloth);`
- L127 _public prototype_ `void PreUpdate(FClothingSimulationSolver* Solver, FClothingSimulationCloth* Cloth);`
- L128 _public prototype_ `void Update(FClothingSimulationSolver* Solver, FClothingSimulationCloth* Cloth);`
- L129 _public prototype_ `void ResetStartPose(FClothingSimulationSolver* Solver, FClothingSimulationCloth* Cloth);`
- L134 _public prototype_ `TConstArrayView<Softs::FSolverVec3> GetCollisionTranslations(const FClothingSimulationSolver* Solver, const FClothingSimulationCloth* Cloth, ECollisionDataType CollisionDataType) const;` — ---- Debugging and visualization functions ---- Return current active LOD collision particles translations, not thread safe, to use after solver update.
- L137 _public prototype_ `TConstArrayView<Softs::FSolverRotation3> GetCollisionRotations(const FClothingSimulationSolver* Solver, const FClothingSimulationCloth* Cloth, ECollisionDataType CollisionDataType) const;` — Return current active LOD collision particles rotations, not thread safe, to use after solver update.
- L140 _public prototype_ `TConstArrayView<Softs::FSolverRigidTransform3> GetOldCollisionTransforms(const FClothingSimulationSolver* Solver, const FClothingSimulationCloth* Cloth, ECollisionDataType CollisionDataType) const;` — Return current active LOD previous frame collision particles transforms, not thread safe, to use after solver update.
- L143 _public prototype_ `TConstArrayView<FImplicitObjectPtr> GetCollisionGeometry(const FClothingSimulationSolver* Solver, const FClothingSimulationCloth* Cloth, ECollisionDataType CollisionDataType) const;` — Return current active LOD collision geometries, not thread safe, to use after solver update.
- L146 _public prototype_ `TConstArrayView<bool> GetCollisionStatus(const FClothingSimulationSolver* Solver, const FClothingSimulationCloth* Cloth, ECollisionDataType CollisionDataType) const;` — Return whether the collision has been hit by a particle during CCD.
- L150 _public prototype_ `static void ExtractPhysicsAssetCollision( const UPhysicsAsset* PhysicsAsset, const FReferenceSkeleton* ReferenceSkeleton, FClothCollisionData& ClothCollisionData, FClothCollisionDataExtended& ClothCollisionDataExtended, TArray<int32>& UsedBoneIndices,` — Extract all collisions from the physics asset into a more cloth friendly format
- L161 _public prototype_ `int32 GetCollisionRangeId(const FClothingSimulationSolver* Solver, const FClothingSimulationCloth* Cloth, ECollisionDataType CollisionDataType) const;` — Return the collision particle range ID for the specified type if valid. If ECollisionDataType::LODs is asked, then the offset returned is for the current LOD.
- L164 _private prototype_ `int32 GetNumGeometries(int32 InSlotIndex) const;`
- L167 _private prototype_ `int32 GetCollisionRangeId(const FClothingSimulationSolver* Solver, const FClothingSimulationCloth* Cloth, int32 InSlotIndex) const;` — Return the collision particle range ID for the specified slot being LODLess, external, or any of the LODs collision.
- L170 _private prototype_ `bool GetCollisionRangeIdAndNumGeometries(const FClothingSimulationSolver* Solver, const FClothingSimulationCloth* Cloth, ECollisionDataType CollisionDataType, int32& OutCollisionRangeId, int32& OutNumGeometries) const;` — Return the collision particle  range ID and number of geometries for the specified type if valid. If ECollisionDataType::LODs is asked, then the offset returned is for the current LOD.
- L173 _private typedef_ `typedef TPair<const FClothingSimulationSolver*, const FClothingSimulationCloth*> FSolverClothPair;`
- L177 _private member_ `const UPhysicsAsset* PhysicsAsset = nullptr;`
- L178 _private member_ `const FReferenceSkeleton* ReferenceSkeleton = nullptr;`
- L179 _private member_ `const FClothCollisionData* CollisionData = nullptr;` — External collision data
- L181 _private member_ `bool bHasExternalCollisionChanged = false;`
- L184 _private member_ `TArray<TUniquePtr<FLODData>> LODData;` — Collision primitives
- L185 _private member_ `TMap<FSolverClothPair, int32> LODIndices;`
- L188 _private member_ `FReal Scale = 1.f;` — Initial scale

#### enum `Chaos::FClothingSimulationCollider::ECollisionDataType`  
`enum class ECollisionDataType : int32`  
_L97-103_
- L99 _public enumerator_ `LODless = 0` — Global LODless collision slot filled with physics collisions
- L100 _public enumerator_ `External` — External collision slot added/removed at every frame
- L101 _public enumerator_ `LODs` — LODIndex based start slot for LODs collisions
- L102 _public enumerator_ `Count`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace Chaos`
- L192 _prototype_ `ENUM_RANGE_BY_COUNT(Chaos::FClothingSimulationCollider::ECollisionDataType, Chaos::FClothingSimulationCollider::ECollisionDataType::Count);`

### `Plugins/ChaosCloth/Source/ChaosCloth/Public/ChaosCloth/ChaosClothingSimulationConfig.h` (Public)


#### class `Chaos::FClothingSimulationConfig`  
`class FClothingSimulationConfig final`  
_L21-109_
- desc: Cloth simulation properties
- L24 _public prototype_ `FClothingSimulationConfig();`
- L25 _public prototype_ `FClothingSimulationConfig(const TArray<TSharedPtr<const FManagedArrayCollection>>& InPropertyCollections);`
- L27 _public prototype_ `~FClothingSimulationConfig();`
- L29 _public prototype_ `FClothingSimulationConfig(const FClothingSimulationConfig&) = delete;`
- L30 _public prototype_ `FClothingSimulationConfig(FClothingSimulationConfig&&) = delete;`
- L31 _public prototype_ `FClothingSimulationConfig& operator=(const FClothingSimulationConfig&) = delete;`
- L32 _public prototype_ `FClothingSimulationConfig& operator=(FClothingSimulationConfig&&) = delete;`
- L40 _public prototype_ `void Initialize(const UChaosClothConfig* ClothConfig, const UChaosClothSharedSimConfig* ClothSharedConfig, bool bUseLegacyConfig = false);` — Initialize configuration from cloth config UObjects. @param ClothConfig The cloth config UObject. @param ClothSharedConfig The cloth solver shared config UObject. @param bUseLegacyConfig Whether to make the config a legacy cloth config, so that the constraints disable themselves with missing masks, ...etc.
- L48 _public prototype_ `void Initialize(const TArray<TSharedPtr<const FManagedArrayCollection>>& InPropertyCollections, bool bForceDirty = false, int32 LODIndex = INDEX_NONE);` — Initialize config from an array of property collections (one per LOD). @param InPropertyCollections The cloth source property collections to initialize from. @param bForceDirty Whether to force the initialization even if the source property collections haven't changed. @param LODIndex The index of the LOD to replace, or INDEX_NONE to replace all LODs.
- L51 _public prototype_ `const Softs::FCollectionPropertyConstFacade& GetProperties(int32 LODIndex) const;` — Return a property collection facade for reading properties from this configuration.
- L52 _public function_ `const Softs::FCollectionPropertyConstFacade& GetProperties() const`
- L59 _public prototype_ `Softs::FCollectionPropertyFacade& GetProperties(int32 LODIndex);` — Return a property collection facade for setting properties for this configuration.
- L60 _public function_ `Softs::FCollectionPropertyFacade& GetProperties()`
- L67 _public function_ `TSharedPtr<const FManagedArrayCollection> GetPropertyCollection(int32 LODIndex) const` — Return this configuration's internal property collection.
- L72 _public function_ `TSharedPtr<const FManagedArrayCollection> GetPropertyCollection() const`
- L78 _public function_ `bool IsLegacySingleLOD() const`
- L79 _public function_ `int32 GetNumLODs() const`
- L80 _public function_ `bool IsValidLOD(int32 LODIndex) const`
- L86 _public function_ `template<typename FunctionType> void ForAllProperties(FunctionType Func)`
- L95 _public function_ `template<typename FunctionType> void ForAllProperties(FunctionType Func) const`
- L103 _public member_ `inline static const FName UseLegacyConfigName = TEXT("Use`
- L106 _private member_ `bool bIsLegacySingleLOD = false;`
- L107 _private member_ `TArray<TSharedPtr<FManagedArrayCollection>> PropertyCollections;`
- L108 _private member_ `TArray<TUniquePtr<Softs::FCollectionPropertyMutableFacade>> Properties;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Chaos`
- L13 _namespace_ `namespace Softs` (scope `Chaos`)

### `Plugins/ChaosCloth/Source/ChaosCloth/Public/ChaosCloth/ChaosClothingSimulationDefaultAccessoryMesh.h` (Public)


#### class `Chaos::FClothingSimulationDefaultAccessoryMesh`  
`class FClothingSimulationDefaultAccessoryMesh final : public FClothingSimulationAccessoryMesh`  
_L13-66_
- inherits: `FClothingSimulationAccessoryMesh`
- desc: Wrapper around a FClothingSimulationMesh's LOD Data so it can share methods with accessory meshes.
- L16 _public prototype_ `FClothingSimulationDefaultAccessoryMesh(const FClothingSimulationMesh& InMesh, const int32 InLODIndex);`
- L18 _public prototype_ `virtual ~FClothingSimulationDefaultAccessoryMesh();`
- L20 _public function_ `const FClothingSimulationMesh& GetMesh() const`
- L25 _public function_ `int32 GetLODIndex() const`
- L31 _public prototype_ `virtual int32 GetNumPoints() const override;` — Return the number of points.
- L34 _public prototype_ `virtual int32 GetNumPatternPoints() const override;` — Return the number of pattern points (2d, unwelded).
- L37 _public prototype_ `virtual TConstArrayView<FVector3f> GetPositions() const override;` — Return the source mesh positions (pre-skinning).
- L40 _public prototype_ `virtual TConstArrayView<FVector2f> GetPatternPositions() const override;` — Return the source mesh 2d pattern positions.
- L43 _public prototype_ `virtual TConstArrayView<FVector3f> GetNormals() const override;` — Return the source mesh normals (pre-skinning).
- L46 _public prototype_ `virtual TConstArrayView<FClothVertBoneData> GetBoneData() const override;` — Return the bone data containing bone weights and influences.
- L49 _public prototype_ `virtual int32 FindMorphTargetByName(const FString& Name) const override;` — Return the MorphTargetIndex for a given Morph Target Name, if it exists.
- L52 _public prototype_ `virtual TConstArrayView<FString> GetAllMorphTargetNames() const override;` — Get a list of all MorphTargets. (Index matches FindMorphTargetByName)
- L55 _public prototype_ `virtual TConstArrayView<FVector3f> GetMorphTargetPositionDeltas(int32 MorphTargetIndex) const override;` — Get all Morph Target position deltas for a given MorphTargetIndex (e.g., index returned by FindMorphTargetByName). Deltas index back to Positions via MorphTargetIndices
- L58 _public prototype_ `virtual TConstArrayView<FVector3f> GetMorphTargetTangentZDeltas(int32 MorphTargetIndex) const override;` — Get all Morph Target tangent z (normal) deltas for a given MorphTargetIndex (e.g., index returned by FindMorphTargetByName). Deltas index back to Normals via MorphTargetIndices
- L61 _public prototype_ `virtual TConstArrayView<int32> GetMorphTargetIndices(int32 MorphTargetIndex) const override;` — Get all Morph Target indices for a given MorphTargetIndex (e.g., index returned by FindMorphTargetByName). These indices can map MorphTargetDeltas back to Positions.
- L64 _private member_ `static const FName DefaultAccessoryMeshName;`
- L65 _private member_ `const int32 LODIndex;`

#### Free symbols / members of external scopes

- L6 _macro_ `#define UE_API CHAOSCLOTH_API`
- L8 _namespace_ `namespace Chaos`

### `Plugins/ChaosCloth/Source/ChaosCloth/Public/ChaosCloth/ChaosClothingSimulationFactory.h` (Public)


#### class `UChaosClothingSimulationFactory`  
`class UChaosClothingSimulationFactory final : public UClothingSimulationFactory`  
_L10-23_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UClothingSimulationFactory`
- L14 _public prototype_ `virtual IClothingSimulationInterface* CreateSimulation() const override;`
- L15 _public prototype_ `virtual void DestroySimulation(IClothingSimulationInterface* InSimulation) const override;`
- L16 _public prototype_ `virtual bool SupportsAsset(const UClothingAssetBase* InAsset) const override;`
- L18 _public prototype_ `virtual bool SupportsRuntimeInteraction() const override;`
- L19 _public prototype_ `virtual UClothingSimulationInteractor* CreateInteractor() override;`
- L21 _public prototype_ `virtual TArrayView<const TSubclassOf<UClothConfigBase>> GetClothConfigClasses() const override;`
- L22 _public prototype_ `const UEnum* GetWeightMapTargetEnum() const override;`

### `Plugins/ChaosCloth/Source/ChaosCloth/Public/ChaosCloth/ChaosClothingSimulationInteractor.h` (Public)


#### class `UChaosClothingInteractor`  
`class UChaosClothingInteractor : public UClothingInteractor`  
_L33-99_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UClothingInteractor`
- L38 _public prototype_ `virtual void Sync(IClothingSimulationInterface* Simulation);`
- L41 _public prototype_ `void SetMaterialLinear(float EdgeStiffness = 1.f, float BendingStiffness = 1.f, float AreaStiffness = 1.f);` — `UFUNCTION(BlueprintCallable, Category = ClothingSimulation, Meta = (Keywords = "Chaos Edge Bending Area Stiffness"))`
- L44 _public prototype_ `void SetMaterial(FVector2D EdgeStiffness = FVector2D(1.f, 1.f), FVector2D BendingStiffness = FVector2D(1.f, 1.f), FVector2D AreaStiffness = FVector2D(1.f, 1.f));` — `UFUNCTION(BlueprintCallable, Category = ClothingSimulation, Meta = (Keywords = "Chaos Edge Bending Area Stiffness"))`
- L47 _public prototype_ `void SetMaterialBuckling(FVector2D BucklingRatio = FVector2D(0.f, 0.f), FVector2D BucklingStiffness = FVector2D(1.f, 1.f));` — `UFUNCTION(BlueprintCallable, Category = ClothingSimulation, Meta = (Keywords = "Chaos Bending Element Buckling Stiffness Ratio"))`
- L50 _public prototype_ `void SetLongRangeAttachmentLinear(float TetherStiffness = 1.f, float TetherScale = 1.f);` — `UFUNCTION(BlueprintCallable, Category = ClothingSimulation, Meta = (Keywords = "Chaos Tether Stiffness Scale"))`
- L53 _public prototype_ `void SetLongRangeAttachment(FVector2D TetherStiffness = FVector2D(1.f, 1.f), FVector2D TetherScale = FVector2D(1.f, 1.f));` — `UFUNCTION(BlueprintCallable, Category = ClothingSimulation, Meta = (Keywords = "Chaos Tether Stiffness Scale"))`
- L56 _public prototype_ `void SetCollision(float CollisionThickness = 1.f, float FrictionCoefficient = 0.8f, bool bUseCCD = false, float SelfCollisionThickness = 2.f);` — `UFUNCTION(BlueprintCallable, Category = ClothingSimulation, Meta = (Keywords = "Chaos Self Thickness Friction Coefficient"))`
- L59 _public prototype_ `void SetBackstop(bool bEnabled = true);` — `UFUNCTION(BlueprintCallable, Category = ClothingSimulation, Meta = (Keywords = "Chaos Backstop Enable Disable Use"))`
- L62 _public prototype_ `void SetDamping(float DampingCoefficient = 0.01f, float LocalDampingCoefficient = 0.f);` — `UFUNCTION(BlueprintCallable, Category = ClothingSimulation, Meta = (Keywords = "Chaos Coefficient"))`
- L66 _public prototype_ `void SetAerodynamics(float DragCoefficient = 0.07f, float LiftCoefficient = 0.035f, FVector WindVelocity = FVector(0.f, 0.f, 0.f));` — `UFUNCTION(BlueprintCallable, Category = ClothingSimulation, Meta = (Keywords = "Chaos Wind Drag Lift Coefficient"))` — Deprecated. This function cannot set different Low and High values for the Drag and Lift weight maps. Use SetWind instead.
- L69 _public prototype_ `void SetWind(FVector2D Drag = FVector2D(0.07f, 0.5f), FVector2D Lift = FVector2D(0.07f, 0.5f), float AirDensity = 1.225e-6f, FVector WindVelocity = FVector(0.f, 0.f, 0.f), FVector2D OuterDrag = FVector2D(0.07f, 0.5f), FVector2D OuterLift = FVector2D(0.07, 0.5f));` — `UFUNCTION(BlueprintCallable, Category = ClothingSimulation, Meta = (Keywords = "Chaos Wind Drag Lift Coefficient Air Density Velocity"))`
- L72 _public prototype_ `void SetPressure(FVector2D Pressure = FVector2D(0.f, 1.f));` — `UFUNCTION(BlueprintCallable, Category = ClothingSimulation, Meta = (Keywords = "Chaos Pressure"))`
- L75 _public prototype_ `void SetGravity(float GravityScale = 1.f, bool bIsGravityOverridden = false, FVector GravityOverride = FVector(0.f, 0.f, -981.f));` — `UFUNCTION(BlueprintCallable, Category = ClothingSimulation, Meta = (Keywords = "Chaos Scale Override"))`
- L78 _public prototype_ `void SetAnimDriveLinear(float AnimDriveStiffness = 0.f);` — `UFUNCTION(BlueprintCallable, Category = ClothingSimulation, Meta = (Keywords = "Chaos Stiffness"))`
- L81 _public prototype_ `void SetAnimDrive(FVector2D AnimDriveStiffness = FVector2D(0.f, 1.f), FVector2D AnimDriveDamping = FVector2D(0.f, 1.f));` — `UFUNCTION(BlueprintCallable, Category = ClothingSimulation, Meta = (Keywords = "Chaos Stiffness Damping"))`
- L84 _public prototype_ `void SetVelocityScale(FVector LinearVelocityScale = FVector(0.75f, 0.75f, 0.75f), float AngularVelocityScale = 0.75f, float FictitiousAngularScale = 1.f);` — `UFUNCTION(BlueprintCallable, Category = ClothingSimulation, Meta = (Keywords = "Chaos Linear Angular Velocity Scale"))`
- L87 _public prototype_ `void SetVelocityClamps(bool bEnableLinearVelocityClamping = false, FVector MaxLinearVelocity = FVector(1000., 1000., 1000.), bool bEnableLinearAccelerationClamping = false, FVector MaxLinearAcceleration = FVector(60000., 60000., 60000.), bool bEnableAngularVelocityClamping = false, float MaxAngularVelocity = 200.f, bool bEnableAngularAccelerationClamping = false, float MaxAngularAcceleration = 12000.f);` — `UFUNCTION(BlueprintCallable, Category = ClothingSimulation, Meta = (Keywords = "Chaos Max Linear Angular Velocity Acceleration Clamp"))`
- L93 _public prototype_ `void ResetAndTeleport(bool bReset = false, bool bTeleport = false);` — `UFUNCTION(BlueprintCallable, Category = ClothingSimulation, Meta = (Keywords = "Chaos"))`
- L97 _private member_ `TArray<Chaos::Internal::FClothingInteractorCommand> Commands;` — Cloth command queue processed when we hit a sync
- L98 _private member_ `TArray<Chaos::Internal::FClothingInteractorConfigCommand> ConfigCommands;`

#### class `UChaosClothingSimulationInteractor`  
`class UChaosClothingSimulationInteractor : public UClothingSimulationInteractor`  
_L102-125_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UClothingSimulationInteractor`
- L107 _public prototype_ `virtual void Sync(IClothingSimulationInterface* InSimulation, const IClothingSimulationContext* InContext) override;` — UClothingSimulationInteractor interface
- L109 _public prototype_ `virtual void PhysicsAssetUpdated() override;`
- L110 _public prototype_ `virtual void ClothConfigUpdated() override;`
- L111 _public prototype_ `virtual void SetAnimDriveSpringStiffness(float Stiffness) override;`
- L112 _public prototype_ `virtual void EnableGravityOverride(const FVector& Gravity) override;`
- L113 _public prototype_ `virtual void DisableGravityOverride() override;`
- L114 _public prototype_ `virtual void SetNumIterations(int32 NumIterations = 1) override;`
- L115 _public prototype_ `virtual void SetMaxNumIterations(int32 MaxNumIterations = 10) override;`
- L116 _public prototype_ `virtual void SetNumSubsteps(int32 NumSubsteps = 1) override;`
- L119 _protected prototype_ `virtual UClothingInteractor* CreateClothingInteractor() override;`
- L123 _private member_ `TArray<Chaos::Internal::FClothingSimulationInteractorCommand> Commands;` — Simulation command queue processed when we hit a sync
- L124 _private member_ `TArray<Chaos::Internal::FClothingInteractorConfigCommand> ConfigCommands;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Chaos`
- L16 _namespace_ `namespace Chaos`
- L16 _namespace_ `namespace Internal` (scope `Chaos`)
- L19 _delegate_ `DECLARE_DELEGATE_TwoParams(FClothingInteractorConfigCommand, Chaos::FClothingSimulationConfig*, int32) DECLARE_DELEGATE_OneParam(FClothingInteractorCommand, Chaos::FClothingSimulationCloth*) PRAGMA_DISABLE_DEPRECATION_WARNINGS` — Command signature for handling synced command buffer
- L20 _delegate_ `DECLARE_DELEGATE_OneParam(FClothingInteractorCommand, Chaos::FClothingSimulationCloth*) PRAGMA_DISABLE_DEPRECATION_WARNINGS`
- L22 _delegate_ `DECLARE_DELEGATE_TwoParams(FClothingSimulationInteractorCommand, Chaos::FClothingSimulation*, const FClothingSimulationContextCommon*) PRAGMA_ENABLE_DEPRECATION_WARNINGS } using FChaosClothingInteractorConfigCommand UE_DEPRECATED(5.7, "For internal use only. Use Chaos::Internal version instead.") =`
- L26 _typedef_ `using FChaosClothingInteractorConfigCommand UE_DEPRECATED(5.7, "For internal use only. Use Chaos::Internal version instead.") =`
- L27 _typedef_ `using FChaosClothingInteractorCommand UE_DEPRECATED(5.7, "For internal use only. Use Chaos::Internal version inst` — `UE_DEPRECATED(5.7, "For internal use only. Use Chaos::Internal version instead.")`
- L29 _typedef_ `using FChaosClothingSimulationInteractorCommand UE_DEPRECATED(5.7, "For internal use only. Use Chaos::Internal version instead.") = TDelegate<void(Chaos:` — `UE_DEPRECATED(5.7, "For internal use only. Use Chaos::Internal version instead.")` — `UE_DEPRECATED(5.7, "For internal use only. Use Chaos::Internal version instead.")` — `UE_DEPRECATED(5.7, "Use IClothingSimulationInterface instead.")`

### `Plugins/ChaosCloth/Source/ChaosCloth/Public/ChaosCloth/ChaosClothingSimulationMesh.h` (Public)


#### class `Chaos::FClothingSimulationMesh`  
`class FClothingSimulationMesh`  
_L24-254_
- desc: Mesh simulation node
- L27 _public prototype_ `explicit FClothingSimulationMesh(const FString& InDebugName);`
- L29 _public prototype_ `virtual ~FClothingSimulationMesh();`
- L31 _public prototype_ `FClothingSimulationMesh(const FClothingSimulationMesh&) = delete;`
- L32 _public prototype_ `FClothingSimulationMesh(FClothingSimulationMesh&&) = delete;`
- L33 _public prototype_ `FClothingSimulationMesh& operator=(const FClothingSimulationMesh&) = delete;`
- L34 _public prototype_ `FClothingSimulationMesh& operator=(FClothingSimulationMesh&&) = delete;`
- L37 _public function_ `const FString& GetDebugName() const`
- L41 _public function_ `FName GetReferenceBoneName() const`
- L51 _public prototype_ `virtual int32 GetNumLODs() const = 0;` — Return the number of LODs on this mesh.
- L54 _public prototype_ `virtual int32 GetLODIndex() const = 0;` — Return the cloth mesh LOD Index. The returned value can then be used to switch LODs on the simulation object.
- L57 _public function_ `virtual int32 GetLODIndexFromOwnerLODIndex(int32 OwnerLODIndex) const` — Return the cloth mesh LOD Index for a given owner LOD index.
- L65 _public prototype_ `virtual int32 GetOwnerLODIndex(int32 LODIndex) const = 0;` — Return the owner component LOD Index from the specified cloth mesh LOD index, or 0 if the owner LOD cannot be determined. The mapping between the cloth mesh LOD and the owner component LOD is not necessarily one to one.
- L68 _public prototype_ `virtual bool IsValidLODIndex(int32 LODIndex) const = 0;` — Return whether the specified LOD index is valid.
- L71 _public prototype_ `virtual int32 GetNumPoints(int32 LODIndex) const = 0;` — Return the number of points for the specified LOD, or 0 if the LOD is empty or invalid.
- L74 _public prototype_ `virtual int32 GetNumPatternPoints(int32 LODIndex) const = 0;` — Return the number of pattern points (2d, unwelded) for the specified LOD, or 0 if patterns are not supported or the LOD is empty or invalid.
- L77 _public prototype_ `virtual TConstArrayView<FVector3f> GetPositions(int32 LODIndex) const = 0;` — Return the source mesh positions (pre-skinning).
- L80 _public prototype_ `virtual TConstArrayView<FVector2f> GetPatternPositions(int32 LODIndex) const = 0;` — Return the source mesh 2d pattern positions.
- L83 _public prototype_ `virtual TConstArrayView<FVector3f> GetNormals(int32 LODIndex) const = 0;` — Return the source mesh normals (pre-skinning).
- L86 _public prototype_ `virtual TConstArrayView<uint32> GetIndices(int32 LODIndex) const = 0;` — Return the specified LOD's triangle indices for this mesh.
- L89 _public prototype_ `virtual TConstArrayView<uint32> GetPatternIndices(int32 LODIndex) const = 0;` — Return the specified LOD's pattern (unwelded) triangle indices for this mesh, or empty array if patterns are not supported.
- L92 _public prototype_ `virtual TConstArrayView<uint32> GetPatternToWeldedIndices(int32 LODIndex) const = 0;` — Return the specified LOD's map from pattern (unwelded) vertices to (welded) vertices, or empty array if patterns are not supported.
- L95 _public prototype_ `virtual TArray<FName> GetWeightMapNames(int32 LODIndex) const = 0;` — Return all weight maps associated with this mesh returned in the same order as GetWeightMaps.
- L98 _public prototype_ `virtual TMap<FString, int32> GetWeightMapIndices(int32 LODIndex) const = 0;` — Return a map of all weight map names associated with this mesh to the index in the array returned by GetWeightMaps.
- L101 _public prototype_ `virtual TArray<TConstArrayView<FRealSingle>> GetWeightMaps(int32 LODIndex) const = 0;` — Return the specified LOD's weight map.
- L104 _public prototype_ `virtual TMap<FString, const TSet<int32>*> GetVertexSets(int32 LODIndex) const = 0;` — Return the specified LOD's vertex sets.
- L107 _public prototype_ `virtual TMap<FString, const TSet<int32>*> GetFaceSets(int32 LODIndex) const = 0;` — Return the specified LOD's face sets.
- L110 _public prototype_ `virtual TMap<FString, TConstArrayView<int32>> GetFaceIntMaps(int32 LODIndex) const = 0;` — Return the specified LOD's face int maps.
- L113 _public prototype_ `virtual TArray<TConstArrayView<TTuple<int32, int32, float>>> GetTethers(int32 LODIndex, bool bUseGeodesicTethers) const = 0;` — Return the tethers connections for the long range attachment into convenient parallel friendly batches.
- L116 _public prototype_ `virtual int32 GetReferenceBoneIndex() const = 0;` — Return the bone to treat as the root of the simulation space.
- L119 _public prototype_ `virtual FTransform GetReferenceBoneTransform() const = 0;` — Return the transform of the bone treated as the root of the simulation space.
- L122 _public prototype_ `virtual const TArray<FTransform>& GetBoneTransforms() const = 0;` — Return the bone transforms as required when updating the collider pose.
- L125 _public prototype_ `virtual const FTransform& GetComponentToWorldTransform() const = 0;` — Return the transform of the bone treated as the root of the simulation space.
- L128 _public prototype_ `virtual const TArray<FMatrix44f>& GetRefToLocalMatrices() const = 0;` — Return the skinning matrices.
- L131 _public prototype_ `virtual TConstArrayView<int32> GetBoneMap() const = 0;` — Return the bone map used to remap the used bones index into the correct skinning matrix index.
- L134 _public prototype_ `virtual TConstArrayView<FClothVertBoneData> GetBoneData(int32 LODIndex) const = 0;` — Return the bone data containing bone weights and influences.
- L137 _public prototype_ `virtual TConstArrayView<FMeshToMeshVertData> GetTransitionUpSkinData(int32 LODIndex) const = 0;` — Return the transition up data (PrevLODIndex < LODIndex), for matching shapes during LOD changes.
- L140 _public prototype_ `virtual TConstArrayView<FMeshToMeshVertData> GetTransitionDownSkinData(int32 LODIndex) const = 0;` — Return the transition down data (PrevLODIndex > LODIndex), for matching shapes during LOD changes.
- L143 _public prototype_ `virtual Softs::FSolverReal GetScale() const;` — Return this mesh uniform scale as the maximum of the three axis scale value.
- L146 _public function_ `virtual TSharedPtr<const FManagedArrayCollection> GetManagedArrayCollection(int32 LODIndex) const` — Return the associated ManagedArrayCollection for this LOD, if it exists.
- L152 _public function_ `virtual int32 FindMorphTargetByName(int32 LODIndex, const FString& Name) const` — Return the MorphTargetIndex for a given Morph Target Name, if it exists.
- L158 _public function_ `virtual TConstArrayView<FString> GetAllMorphTargetNames(int32 LODIndex) const` — Get a list of all MorphTargets for a given LODIndex. (Index matches FindMorphTargetByName)
- L164 _public function_ `virtual TConstArrayView<FVector3f> GetMorphTargetPositionDeltas(int32 LODIndex, int32 MorphTargetIndex) const` — Get all Morph Target position deltas for a given MorphTargetIndex (e.g., index returned by FindMorphTargetByName). Deltas index back to Positions via MorphTargetIndices
- L170 _public function_ `virtual TConstArrayView<FVector3f> GetMorphTargetTangentZDeltas(int32 LODIndex, int32 MorphTargetIndex) const` — Get all Morph Target tangent z (normal) deltas for a given MorphTargetIndex (e.g., index returned by FindMorphTargetByName). Deltas index back to Normals via MorphTargetIndices
- L176 _public function_ `virtual TConstArrayView<int32> GetMorphTargetIndices(int32 LODIndex, int32 MorphTargetIndex) const` — Get all Morph Target indices for a given MorphTargetIndex (e.g., index returned by FindMorphTargetByName). These indices can map MorphTargetDeltas back to Positions.
- L181 _public function_ `virtual TConstArrayView<FName> GetAllAccessoryMeshNames(int32 LODIndex) const`
- L187 _public function_ `virtual const FClothingSimulationAccessoryMesh* GetAccessoryMesh(int32 LODIndex, const FName& AccessoryMeshName) const` — Return the Accessory Mesh if it exists.
- L192 _public function_ `FClothingSimulationDefaultAccessoryMesh GetDefaultAccessoryMesh(int32 LODIndex) const`
- L198 _public prototype_ `bool WrapDeformLOD( int32 PrevLODIndex, int32 LODIndex, const Softs::FSolverVec3* Normals, const Softs::FSolverVec3* Positions, Softs::FSolverVec3* OutPositions) const;` — Deform the specified positions to match the shape of the previous LOD.
- L206 _public prototype_ `bool WrapDeformLOD( int32 PrevLODIndex, int32 LODIndex, const Softs::FSolverVec3* Normals, const Softs::FPAndInvM* PositionAndInvMs, const Softs::FSolverVec3* Velocities, Softs::FPAndInvM* OutPositionAndInvMs0, Softs::FSolverVec3* OutPositions1, Softs::FSolverVec3* OutVelocities) const;` — Deform the specified positions and transfer velocities to match the dynamics of the previous LOD.
- L217 _public prototype_ `void Update( FClothingSimulationSolver* Solver, int32 PrevLODIndex, int32 LODIndex, int32 PrevOffset, int32 Offset, int32 ActiveMorphTargetIndex = INDEX_NONE, float ActiveMorphTargetWeight = 0.f);` — Update the mesh for the next solver step, doing skinning and matching the shapes during LOD changes.
- L227 _public prototype_ `void ApplyMorphTarget( int32 LODIndex, int32 ActiveMorphTargetIndex, float ActiveMorphTargetWeight, const TArrayView<Softs::FSolverVec3>& InOutPositions, const TArrayView<Softs::FSolverVec3>& InOutNormals) const;` — Apply a Morph Target to a given set of positions
- L237 _private prototype_ `bool WrapDeformLOD( int32 PrevLODIndex, int32 LODIndex, const TConstArrayView<Softs::FSolverVec3>& Positions, const TConstArrayView<Softs::FSolverVec3>& Normals, TArrayView<Softs::FSolverVec3>& OutPositions, TArrayView<Softs::FSolverVec3>& OutNormals) const;`
- L247 _private member_ `FString DebugName;` — Debug name of the source component.
- L252 _protected member_ `FName ReferenceBoneName = NAME_None;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API CHAOSCLOTH_API`
- L18 _namespace_ `namespace Chaos`

### `Plugins/ChaosCloth/Source/ChaosCloth/Public/ChaosCloth/ChaosClothingSimulationSkeletalMesh.h` (Public)


#### class `Chaos::FClothingSimulationSkeletalMesh`  
`class FClothingSimulationSkeletalMesh final : public FClothingSimulationMesh`  
_L11-62_
- inherits: `FClothingSimulationMesh`
- L14 _public prototype_ `FClothingSimulationSkeletalMesh(const UClothingAssetCommon* InAsset, const USkeletalMeshComponent* InSkeletalMeshComponent);`
- L15 _public prototype_ `virtual ~FClothingSimulationSkeletalMesh() override = default;`
- L17 _public prototype_ `FClothingSimulationSkeletalMesh(const FClothingSimulationSkeletalMesh&) = delete;`
- L18 _public prototype_ `FClothingSimulationSkeletalMesh(FClothingSimulationSkeletalMesh&&) = delete;`
- L19 _public prototype_ `FClothingSimulationSkeletalMesh& operator=(const FClothingSimulationSkeletalMesh&) = delete;`
- L20 _public prototype_ `FClothingSimulationSkeletalMesh& operator=(FClothingSimulationSkeletalMesh&&) = delete;`
- L22 _public function_ `const UClothingAssetCommon* GetAsset() const`
- L23 _public function_ `const USkeletalMeshComponent* GetSkeletalMeshComponent() const`
- L26 _public prototype_ `virtual int32 GetNumLODs() const override;`
- L27 _public prototype_ `virtual int32 GetLODIndex() const override;`
- L28 _public prototype_ `virtual int32 GetLODIndexFromOwnerLODIndex(int32 OwnerLODIndex) const override;`
- L29 _public prototype_ `virtual int32 GetOwnerLODIndex(int32 LODIndex) const override;`
- L30 _public prototype_ `virtual bool IsValidLODIndex(int32 LODIndex) const override;`
- L31 _public prototype_ `virtual int32 GetNumPoints(int32 LODIndex) const override;`
- L32 _public prototype_ `virtual int32 GetNumPatternPoints(int32 LODIndex) const override;`
- L33 _public prototype_ `virtual TConstArrayView<FVector3f> GetPositions(int32 LODIndex) const override;`
- L34 _public prototype_ `virtual TConstArrayView<FVector2f> GetPatternPositions(int32 LODIndex) const override;`
- L35 _public prototype_ `virtual TConstArrayView<FVector3f> GetNormals(int32 LODIndex) const override;`
- L36 _public prototype_ `virtual TConstArrayView<uint32> GetIndices(int32 LODIndex) const override;`
- L37 _public prototype_ `virtual TConstArrayView<uint32> GetPatternIndices(int32 LODIndex) const override;`
- L38 _public prototype_ `virtual TConstArrayView<uint32> GetPatternToWeldedIndices(int32 LODIndex) const override;`
- L39 _public prototype_ `virtual TArray<FName> GetWeightMapNames(int32 LODIndex) const override;`
- L40 _public prototype_ `virtual TMap<FString, int32> GetWeightMapIndices(int32 LODIndex) const override;`
- L41 _public prototype_ `virtual TArray<TConstArrayView<FRealSingle>> GetWeightMaps(int32 LODIndex) const override;`
- L42 _public prototype_ `virtual TMap<FString, const TSet<int32>*> GetVertexSets(int32 LODIndex) const override;`
- L43 _public prototype_ `virtual TMap<FString, const TSet<int32>*> GetFaceSets(int32 LODIndex) const override;`
- L44 _public prototype_ `virtual TMap<FString, TConstArrayView<int32>> GetFaceIntMaps(int32 LODIndex) const override;`
- L45 _public prototype_ `virtual TArray<TConstArrayView<TTuple<int32, int32, float>>> GetTethers(int32 LODIndex, bool bUseGeodesicTethers) const override;`
- L46 _public prototype_ `virtual int32 GetReferenceBoneIndex() const override;`
- L47 _public prototype_ `virtual FTransform GetReferenceBoneTransform() const override;`
- L48 _public prototype_ `virtual const TArray<FTransform>& GetBoneTransforms() const override;`
- L49 _public prototype_ `virtual const FTransform& GetComponentToWorldTransform() const override;`
- L50 _public prototype_ `virtual const TArray<FMatrix44f>& GetRefToLocalMatrices() const override;`
- L51 _public prototype_ `virtual TConstArrayView<int32> GetBoneMap() const override;`
- L52 _public prototype_ `virtual TConstArrayView<FClothVertBoneData> GetBoneData(int32 LODIndex) const override;`
- L53 _public prototype_ `virtual TConstArrayView<FMeshToMeshVertData> GetTransitionUpSkinData(int32 LODIndex) const override;`
- L54 _public prototype_ `virtual TConstArrayView<FMeshToMeshVertData> GetTransitionDownSkinData(int32 LODIndex) const override;`
- L58 _private prototype_ `const FClothingSimulationContextCommon* GetContext() const;`
- L60 _private member_ `const UClothingAssetCommon* Asset;`
- L61 _private member_ `const USkeletalMeshComponent* SkeletalMeshComponent;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Chaos`

### `Plugins/ChaosCloth/Source/ChaosCloth/Public/ChaosCloth/ChaosClothingSimulationSolver.h` (Public)


#### enum `EChaosClothingSimulationSolverFictitiousForcesModel`  
`enum class EChaosClothingSimulationSolverFictitiousForcesModel : uint8`  
_L24-34_
- reflection: `UENUM()`
- desc: Fictitious forces model. Decide how fictitious forces (e.g. centrifugal force) are applied to the simulation.
- L27 _public enumerator_ `None` — Don't apply fictitious forces.
- L29 _public enumerator_ `Legacy` — Use partial scaled angular velocity, fictitious forces are calculated from the portion of the scaled character velocities. Legacy behavior, use the FullScale model instead.
- L31 _public enumerator_ `AppliedScale` — Use applied angular velocity (velocities after clamping), fictitious forces are calculated from the applied scale character velocities.
- L33 _public enumerator_ `FullScale` — Use full angular velocity, fictitious forces are calculated from the full scale character velocities.

#### class `Chaos::FClothingSimulationSolver`  
`class FClothingSimulationSolver final : public FPhysicsSolverEvents`  
_L52-633_
- inherits: `FPhysicsSolverEvents`
- desc: Solver simulation node
- L55 _public typedef_ `using EFictitiousForcesModel = EChaosClothingSimulationSolverFictitiousForcesModel;`
- L57 _public prototype_ `FClothingSimulationSolver(FClothingSimulationConfig* InConfig = nullptr, bool bUseLegacySolver = true);`
- L58 _public prototype_ `~FClothingSimulationSolver();`
- L60 _public prototype_ `FClothingSimulationSolver(const FClothingSimulationSolver&) = delete;`
- L61 _public prototype_ `FClothingSimulationSolver(FClothingSimulationSolver&&) = delete;`
- L62 _public prototype_ `FClothingSimulationSolver& operator=(const FClothingSimulationSolver&) = delete;`
- L63 _public prototype_ `FClothingSimulationSolver& operator=(FClothingSimulationSolver&&) = delete;`
- L65 _public function_ `bool IsLegacySolver() const`
- L68 _public prototype_ `void SetLocalSpaceLocation(const FVec3& InLocalSpaceLocation, bool bReset = false);` — ---- Animatable property setters ----
- L69 _public function_ `const FVec3& GetLocalSpaceLocation() const`
- L70 _public function_ `void SetLocalSpaceRotation(const FQuat& InLocalSpaceRotation)`
- L71 _public function_ `const FRotation3& GetLocalSpaceRotation() const`
- L72 _public prototype_ `void SetLocalSpaceScale(FReal InLocalSpaceScale, bool bReset = false);`
- L73 _public function_ `FReal GetLocalSpaceScale() const`
- L74 _public function_ `void SetVelocityScale(FReal InVelocityScale)`
- L75 _public function_ `FReal GetVelocityScale() const`
- L78 _public function_ `void EnableClothGravityOverride(bool bInIsClothGravityOverrideEnabled)` — Disables all Cloths gravity override mechanism
- L79 _public function_ `bool IsClothGravityOverrideEnabled() const`
- L80 _public function_ `void SetGravity(const TVec3<FRealSingle>& InGravity)`
- L81 _public function_ `const TVec3<FRealSingle>& GetGravity() const`
- L83 _public prototype_ `void SetWindVelocity(const TVec3<FRealSingle>& InWindVelocity, FRealSingle InLegacyWindAdaption = (FRealSingle)0.);`
- L84 _public function_ `const TVec3<FRealSingle>& GetWindVelocity() const`
- L86 _public prototype_ `int32 GetNumIterations() const;`
- L87 _public prototype_ `int32 GetMaxNumIterations() const;`
- L88 _public prototype_ `int32 GetNumSubsteps() const;`
- L90 _public function_ `void SetEnableSolver(bool InbEnableSolver)`
- L91 _public function_ `bool GetEnableSolver() const`
- L95 _public prototype_ `void SetCloths(TArray<FClothingSimulationCloth*>&& InCloths);` — ---- Object management functions ----
- L96 _public prototype_ `void AddCloth(FClothingSimulationCloth* InCloth);`
- L97 _public prototype_ `void RemoveCloth(FClothingSimulationCloth* InCloth);`
- L98 _public prototype_ `void RemoveCloths();`
- L100 _public prototype_ `void RefreshCloth(FClothingSimulationCloth* InCloth);`
- L101 _public prototype_ `void RefreshCloths();`
- L103 _public function_ `TConstArrayView<const FClothingSimulationCloth*> GetCloths() const`
- L106 _public function_ `FClothingSimulationConfig* GetConfig() const` — Get the solver configuration.
- L112 _public prototype_ `void SetConfig(FClothingSimulationConfig* InConfig);` — Set the solver configuration. Can use a cloth config if a single cloth is being simulated.
- L114 _public prototype_ `void SetSolverLOD(int32 LODIndex);`
- L115 _public function_ `int32 GetSolverLOD() const`
- L118 _public prototype_ `void Update(FSolverReal InDeltaTime);` — Advance the simulation.
- L120 _public prototype_ `void ExtremeDeformationReset();`
- L123 _public function_ `FSolverReal GetDeltaTime() const` — Return the last delta time used for advancing the simulation.
- L126 _public prototype_ `void UpdateFromCache(const FClothingSimulationCacheData& CacheData);` — Set the cached positions onto the particles
- L129 _public prototype_ `int32 GetNumUsedIterations() const;` — Return the actual of number of iterations used by the Evolution solver after the update (different from the number of iterations, depends on frame rate)
- L130 _public function_ `int32 GetNumUsedSubsteps() const`
- L132 _public prototype_ `int32 GetNumLinearSolverIterations(int32 ParticleRangeId) const;` — Return the actual number of linear solver iterations used by the Evolution solver after the update (force-based solver only)
- L134 _public prototype_ `FRealSingle GetLinearSolverError(int32 ParticleRangeId) const;` — Return the final error of the linear solver after the update (force-based solver only)
- L136 _public prototype_ `FBoxSphereBounds CalculateBounds() const;`
- L140 _public prototype_ `int32 AddParticles(int32 NumParticles, uint32 GroupId);` — ---- Cloth interface ----
- L141 _public prototype_ `void EnableParticles(int32 ParticleRangeId, bool bEnable);`
- L143 _public prototype_ `void ResetStartPose(int32 ParticleRangeId, int32 NumParticles);`
- L146 _public function_ `FSolverReal GetTime() const` — Get the current solver time
- L147 _public prototype_ `void SetParticleMassUniform(int32 ParticleRangeId, const FVector2f& UniformMass, const TConstArrayView<FRealSingle>& UniformMassMultipliers, FRealSingle MinPerParticleMass, const FTriangleMesh& Mesh, const TFunctionRef<bool(int32)>& KinematicPredicate);`
- L148 _public prototype_ `void SetParticleMassFromTotalMass(int32 ParticleRangeId, FRealSingle TotalMass, FRealSingle MinPerParticleMass, const FTriangleMesh& Mesh, const TFunctionRef<bool(int32)>& KinematicPredicate);`
- L149 _public prototype_ `void SetParticleMassFromDensity(int32 ParticleRangeId, const FVector2f& Density, const TConstArrayView<FRealSingle>& DensityMultipliers, FRealSingle MinPerParticleMass, const FTriangleMesh& Mesh, const TFunctionRef<bool(int32)>& KinematicPredicate);`
- L150 _public function_ `void SetParticleMassUniform(int32 ParticleRangeId, FRealSingle UniformMass, FRealSingle MinPerParticleMass, const FTriangleMesh& Mesh, const TFunctionRef<bool(int32)>& KinematicPredicate)`
- L154 _public function_ `void SetParticleMassFromDensity(int32 ParticleRangeId, FRealSingle Density, FRealSingle MinPerParticleMass, const FTriangleMesh& Mesh, const TFunctionRef<bool(int32)>& KinematicPredicate)`
- L161 _public prototype_ `void SetReferenceVelocityScale( uint32 GroupId, const FRigidTransform3& OldReferenceSpaceTransform, const FRigidTransform3& ReferenceSpaceTransform, TVec3<FReal>& InOutAppliedReferenceVelocity,` — Set the amount of velocity allowed to filter from the given change in reference space transform, including local simulation space. NOTE: Force-based solver does not apply FictitiousAngularScale here. It's applied directly via the PropertyCollection.
- L179 _public function_ `void SetReferenceVelocityScale( uint32 GroupId, const FRigidTransform3& OldReferenceSpaceTransform, const FRigidTransform3& ReferenceSpaceTransform, TVec3<FReal>& InOutAppliedReferenceVelocity,` — `UE_DEPRECATED(5.8, "Use the version that takes a EFictitiousForcesModel argument instead.")`
- L215 _public function_ `void SetReferenceVelocityScale( uint32 GroupId, const FRigidTransform3& OldReferenceSpaceTransform, const FRigidTransform3& ReferenceSpaceTransform, const TVec3<FRealSingle>& LinearVelocityScale, FRealSingle AngularVelocityScale, FRealSingle FictitiousAngularScale, FRealSingle MaxVelocityScale = 1.f, bool bDisableFictitiousForces = false)` — `UE_DEPRECATED(5.8, "Use the version that takes a EFictitiousForcesModel argument instead.")`
- L247 _public prototype_ `void SetProperties( uint32 GroupId, FRealSingle DampingCoefficient, FRealSingle MotionDampingCoefficient, FRealSingle CollisionThickness, FRealSingle FrictionCoefficient);` — PBDSolver version
- L255 _public prototype_ `void SetProperties(int32 ParticleRangeId, const Softs::FCollectionPropertyConstFacade& PropertyCollection, const TMap<FString, TConstArrayView<FRealSingle>>& WeightMaps) ;` — Force based solver version
- L260 _public prototype_ `void SetUseCCD(uint32 GroupId, bool bUseCCD);` — Set whether to use continuous collision detection.
- L263 _public prototype_ `void SetGravity(uint32 GroupId, const TVec3<FRealSingle>& Gravity);` — Set per group gravity, used to override solver's gravity. Must be called during cloth update.
- L266 _public prototype_ `void SetWindVelocity(uint32 GroupId, const TVec3<FRealSingle>& InWindVelocity);` — Set per group wind velocity, used to override solver's wind velocity. Must be called during cloth update.
- L269 _public prototype_ `void SetWindAndPressureGeometry( uint32 GroupId, const FTriangleMesh& TriangleMesh, const Softs::FCollectionPropertyConstFacade& PropertyCollection, const TMap<FString, TConstArrayView<FRealSingle>>& WeightMaps);` — Set the geometry affected by the wind and pressure
- L275 _public prototype_ `void SetWindAndPressureGeometry( uint32 GroupId, const FTriangleMesh& TriangleMesh, const TConstArrayView<FRealSingle>& DragMultipliers, const TConstArrayView<FRealSingle>& OuterDragMultipliers, const TConstArrayView<FRealSingle>& LiftMultipliers, const TConstArrayView<FRealSingle>& OuterLiftMultipliers, const TConstArrayView<FRealSingle>& PressureMultipliers);`
- L285 _public function_ `void SetWindAndPressureGeometry( uint32 GroupId, const FTriangleMesh& TriangleMesh, const TConstArrayView<FRealSingle>& DragMultipliers, const TConstArrayView<FRealSingle>& LiftMultipliers, const TConstArrayView<FRealSingle>& PressureMultipliers)` — `UE_DEPRECATED(5.5, "Use version with PropertyCollection (preferred) or OuterDrag and OuterLift")`
- L296 _public prototype_ `void SetWindAndPressureProperties( uint32 GroupId, const Softs::FCollectionPropertyConstFacade& PropertyCollection, const TMap<FString, TConstArrayView<FRealSingle>>& WeightMaps, bool bEnableAerodynamics);` — Set the wind and pressure properties.
- L302 _public prototype_ `void SetWindAndPressureProperties( uint32 GroupId, const TVec2<FRealSingle>& Drag, const TVec2<FRealSingle>& OuterDrag, const TVec2<FRealSingle>& Lift, const TVec2<FRealSingle>& OuterLift, FRealSingle FluidDensity, const TVec2<FRealSingle>& Pressure);`
- L312 _public function_ `void SetWindAndPressureProperties( uint32 GroupId, const TVec2<FRealSingle>& Drag, const TVec2<FRealSingle>& Lift, FRealSingle FluidDensity = 1.225f, const TVec2<FRealSingle>& Pressure = TVec2<FRealSingle>::ZeroVector)` — `UE_DEPRECATED(5.5, "Use version with PropertyCollection (preferred) or OuterDrag and OuterLift")`
- L323 _public prototype_ `const Softs::FVelocityAndPressureField& GetWindVelocityAndPressureField(uint32 GroupId) const;` — Return the wind velocity and pressure field associated with a given group id.
- L326 _public prototype_ `void AddExternalForces(uint32 GroupId, bool bUseLegacyWind);` — Add external forces to the particles
- L329 _public function_ `const TArray<Softs::FSolverVec3>& GetOldAnimationPositions() const`
- L330 _public function_ `const TArray<Softs::FSolverVec3>& GetAnimationPositions() const`
- L331 _public function_ `const TArray<Softs::FSolverVec3>& GetInterpolatedAnimationPositions() const`
- L332 _public function_ `const TArray<Softs::FSolverVec3>& GetOldAnimationNormals() const`
- L333 _public function_ `const TArray<Softs::FSolverVec3>& GetAnimationNormals() const`
- L334 _public function_ `const TArray<Softs::FSolverVec3>& GetInterpolatedAnimationNormals() const`
- L335 _public function_ `const TArray<Softs::FSolverVec3>& GetNormals() const`
- L336 _public function_ `const TArray<Softs::FSolverVec3>& GetAnimationVelocities() const`
- L338 _public prototype_ `TConstArrayView<Softs::FSolverVec3> GetOldAnimationPositionsView(int32 ParticleRangeId) const;`
- L339 _public prototype_ `TArrayView<Softs::FSolverVec3> GetOldAnimationPositionsView(int32 ParticleRangeId);`
- L340 _public prototype_ `TConstArrayView<Softs::FSolverVec3> GetAnimationPositionsView(int32 ParticleRangeId) const;`
- L341 _public prototype_ `TArrayView<Softs::FSolverVec3> GetAnimationPositionsView(int32 ParticleRangeId);`
- L342 _public prototype_ `TConstArrayView<Softs::FSolverVec3> GetInterpolatedAnimationPositionsView(int32 ParticleRangeId) const;`
- L343 _public prototype_ `TArrayView<Softs::FSolverVec3> GetInterpolatedAnimationPositionsView(int32 ParticleRangeId);`
- L344 _public prototype_ `TConstArrayView<Softs::FSolverVec3> GetOldAnimationNormalsView(int32 ParticleRangeId) const;`
- L345 _public prototype_ `TArrayView<Softs::FSolverVec3> GetOldAnimationNormalsView(int32 ParticleRangeId);`
- L346 _public prototype_ `TConstArrayView<Softs::FSolverVec3> GetAnimationNormalsView(int32 ParticleRangeId) const;`
- L347 _public prototype_ `TArrayView<Softs::FSolverVec3> GetAnimationNormalsView(int32 ParticleRangeId);`
- L348 _public prototype_ `TConstArrayView<Softs::FSolverVec3> GetInterpolatedAnimationNormalsView(int32 ParticleRangeId) const;`
- L349 _public prototype_ `TArrayView<Softs::FSolverVec3> GetInterpolatedAnimationNormalsView(int32 ParticleRangeId);`
- L350 _public prototype_ `TConstArrayView<Softs::FSolverVec3> GetNormalsView(int32 ParticleRangeId) const;`
- L351 _public prototype_ `TArrayView<Softs::FSolverVec3> GetNormalsView(int32 ParticleRangeId);`
- L352 _public prototype_ `TConstArrayView<Softs::FSolverVec3> GetAnimationVelocitiesView(int32 ParticleRangeId) const;`
- L353 _public prototype_ `TArrayView<Softs::FSolverVec3> GetAnimationVelocitiesView(int32 ParticleRangeId);`
- L355 _public function_ `const Softs::FSolverVec3* GetOldAnimationPositions(int32 ParticleRangeId) const`
- L356 _public function_ `Softs::FSolverVec3* GetOldAnimationPositions(int32 ParticleRangeId)`
- L357 _public function_ `const Softs::FSolverVec3* GetAnimationPositions(int32 ParticleRangeId) const`
- L358 _public function_ `Softs::FSolverVec3* GetAnimationPositions(int32 ParticleRangeId)`
- L359 _public function_ `const Softs::FSolverVec3* GetInterpolatedAnimationPositions(int32 ParticleRangeId) const`
- L360 _public function_ `Softs::FSolverVec3* GetInterpolatedAnimationPositions(int32 ParticleRangeId)`
- L361 _public function_ `const Softs::FSolverVec3* GetOldAnimationNormals(int32 ParticleRangeId) const`
- L362 _public function_ `Softs::FSolverVec3* GetOldAnimationNormals(int32 ParticleRangeId)`
- L363 _public function_ `const Softs::FSolverVec3* GetAnimationNormals(int32 ParticleRangeId) const`
- L364 _public function_ `Softs::FSolverVec3* GetAnimationNormals(int32 ParticleRangeId)`
- L366 _public function_ `const Softs::FSolverVec3* GetInterpolatedAnimationNormals(int32 ParticleRangeId) const`
- L367 _public function_ `Softs::FSolverVec3* GetInterpolatedAnimationNormals(int32 ParticleRangeId)`
- L368 _public function_ `const Softs::FSolverVec3* GetNormals(int32 ParticleRangeId) const`
- L369 _public function_ `Softs::FSolverVec3* GetNormals(int32 ParticleRangeId)`
- L370 _public function_ `const Softs::FSolverVec3* GetAnimationVelocities(int32 ParticleRangeId) const`
- L371 _public function_ `Softs::FSolverVec3* GetAnimationVelocities(int32 ParticleRangeId)`
- L373 _public prototype_ `const TArray<Softs::FPAndInvM>& GetParticlePandInvMs() const;`
- L374 _public prototype_ `const TArray<Softs::FSolverVec3>& GetParticleXs() const;`
- L375 _public prototype_ `const TArray<Softs::FSolverVec3>& GetParticleVs() const;`
- L376 _public prototype_ `const TArray<Softs::FSolverReal>& GetParticleInvMasses() const;`
- L378 _public prototype_ `TConstArrayView<Softs::FPAndInvM> GetParticlePandInvMsView(int32 ParticleRangeId) const;`
- L379 _public prototype_ `TArrayView<Softs::FPAndInvM> GetParticlePandInvMsView(int32 ParticleRangeId);`
- L380 _public prototype_ `TConstArrayView<Softs::FSolverVec3> GetParticleXsView(int32 ParticleRangeId) const;`
- L381 _public prototype_ `TArrayView<Softs::FSolverVec3> GetParticleXsView(int32 ParticleRangeId);`
- L382 _public prototype_ `TConstArrayView<Softs::FSolverVec3> GetParticleVsView(int32 ParticleRangeId) const;`
- L383 _public prototype_ `TArrayView<Softs::FSolverVec3> GetParticleVsView(int32 ParticleRangeId);`
- L384 _public prototype_ `TConstArrayView<Softs::FSolverReal> GetParticleInvMassesView(int32 ParticleRangeId) const;`
- L385 _public prototype_ `TArrayView<Softs::FSolverReal> GetParticleInvMassesView(int32 ParticleRangeId);`
- L387 _public function_ `const Softs::FPAndInvM* GetParticlePandInvMs(int32 ParticleRangeId) const`
- L391 _public function_ `Softs::FPAndInvM* GetParticlePandInvMs(int32 ParticleRangeId)`
- L395 _public function_ `const Softs::FSolverVec3* GetParticleXs(int32 ParticleRangeId) const`
- L399 _public function_ `Softs::FSolverVec3* GetParticleXs(int32 ParticleRangeId)`
- L403 _public function_ `const Softs::FSolverVec3* GetParticleVs(int32 ParticleRangeId) const`
- L407 _public function_ `Softs::FSolverVec3* GetParticleVs(int32 ParticleRangeId)`
- L411 _public function_ `const Softs::FSolverReal* GetParticleInvMasses(int32 ParticleRangeId) const`
- L416 _public function_ `const FClothConstraints& GetClothConstraints(int32 ParticleRangeId) const`
- L417 _public function_ `FClothConstraints& GetClothConstraints(int32 ParticleRangeId)`
- L419 _public prototype_ `bool UsesBuoyancy();`
- L420 _public prototype_ `void PreSimulateBuoyancyField_GameThread(float dt, const UWorld* World, const FBox BoundingBox);`
- L422 _public prototype_ `uint32 GetNumParticles() const;`
- L423 _public prototype_ `int32 GetNumActiveParticles() const;`
- L424 _public prototype_ `int32 GetGlobalParticleOffset(int32 ParticleRangeId) const;`
- L426 _public function_ `const Softs::FSolverVec3& GetAppliedReferenceSpaceVelocity(uint32 GroupId) const`
- L427 _public function_ `const Softs::FSolverVec3& GetAppliedReferenceSpaceAngularVelocity(uint32 GroupId) const`
- L429 _public function_ `const Softs::FSolverVec3& GetOriginalReferenceSpaceVelocity(uint32 GroupId) const`
- L430 _public function_ `const Softs::FSolverVec3& GetOriginalReferenceSpaceAngularVelocity(uint32 GroupId) const`
- L435 _public prototype_ `int32 AddCollisionParticles(int32 NumCollisionParticles, uint32 GroupId, int32 RecycledCollisionRangeId = 0);` — ---- Collider interface ----
- L436 _public prototype_ `void EnableCollisionParticles(int32 CollisionRangeId, bool bEnable);`
- L438 _public function_ `const FClothComplexColliders* GetComplexColliders(int32 CollisionRangeId) const` — This method is not supported by LegacySolver and will return nullptr.
- L446 _public function_ `FClothComplexColliders* GetComplexColliders(int32 CollisionRangeId)`
- L455 _public prototype_ `void ResetCollisionStartPose(int32 CollisionRangeId, int32 NumCollisionParticles);`
- L457 _public prototype_ `TConstArrayView<int32> GetCollisionBoneIndicesView(int32 CollisionRangeId) const;`
- L458 _public prototype_ `TArrayView<int32> GetCollisionBoneIndicesView(int32 CollisionRangeId);`
- L459 _public prototype_ `TConstArrayView<Softs::FSolverRigidTransform3> GetCollisionBaseTransformsView(int32 CollisionRangeId) const;`
- L460 _public prototype_ `TArrayView<Softs::FSolverRigidTransform3> GetCollisionBaseTransformsView(int32 CollisionRangeId);`
- L461 _public prototype_ `TConstArrayView<Softs::FSolverRigidTransform3> GetOldCollisionTransformsView(int32 CollisionRangeId) const;`
- L462 _public prototype_ `TArrayView<Softs::FSolverRigidTransform3> GetOldCollisionTransformsView(int32 CollisionRangeId);`
- L463 _public prototype_ `TConstArrayView<Softs::FSolverRigidTransform3> GetCollisionTransformsView(int32 CollisionRangeId) const;`
- L464 _public prototype_ `TArrayView<Softs::FSolverRigidTransform3> GetCollisionTransformsView(int32 CollisionRangeId);`
- L465 _public prototype_ `TConstArrayView<Softs::FSolverVec3> GetCollisionParticleXsView(int32 CollisionRangeId) const;`
- L466 _public prototype_ `TArrayView<Softs::FSolverVec3> GetCollisionParticleXsView(int32 CollisionRangeId);`
- L467 _public prototype_ `TConstArrayView<Softs::FSolverRotation3> GetCollisionParticleRsView(int32 CollisionRangeId) const;`
- L468 _public prototype_ `TArrayView<Softs::FSolverRotation3> GetCollisionParticleRsView(int32 CollisionRangeId);`
- L469 _public prototype_ `TConstArrayView<FImplicitObjectPtr> GetCollisionGeometryView(int32 CollisionRangeId) const;`
- L470 _public prototype_ `TConstArrayView<bool> GetCollisionStatusView(int32 CollisionRangeId) const;`
- L471 _public prototype_ `TConstArrayView<Softs::FSolverRigidTransform3> GetLastSubframeCollisionTransformsCCDView(int32 CollisionRangeId) const;`
- L472 _public prototype_ `TArrayView<Softs::FSolverRigidTransform3> GetLastSubframeCollisionTransformsCCDView(int32 CollisionRangeId);`
- L474 _public prototype_ `void SetCollisionGeometry(int32 CollisionRangeId, int32 Index, FImplicitObjectPtr&& Geometry);`
- L476 _public prototype_ `const TArray<Softs::FSolverVec3>& GetCollisionContacts() const;`
- L477 _public prototype_ `const TArray<Softs::FSolverVec3>& GetCollisionNormals() const;`
- L478 _public prototype_ `const TArray<Softs::FSolverReal>& GetCollisionPhis() const;`
- L480 _public function_ `const int32* GetCollisionBoneIndices(int32 CollisionRangeId) const`
- L481 _public function_ `int32* GetCollisionBoneIndices(int32 CollisionRangeId)`
- L482 _public function_ `const Softs::FSolverRigidTransform3* GetCollisionBaseTransforms(int32 CollisionRangeId) const`
- L483 _public function_ `Softs::FSolverRigidTransform3* GetCollisionBaseTransforms(int32 CollisionRangeId)`
- L484 _public function_ `const Softs::FSolverRigidTransform3* GetOldCollisionTransforms(int32 CollisionRangeId) const`
- L485 _public function_ `Softs::FSolverRigidTransform3* GetOldCollisionTransforms(int32 CollisionRangeId)`
- L486 _public function_ `const Softs::FSolverRigidTransform3* GetCollisionTransforms(int32 CollisionRangeId) const`
- L487 _public function_ `Softs::FSolverRigidTransform3* GetCollisionTransforms(int32 CollisionRangeId)`
- L488 _public function_ `const Softs::FSolverVec3* GetCollisionParticleXs(int32 CollisionRangeId) const`
- L489 _public function_ `Softs::FSolverVec3* GetCollisionParticleXs(int32 CollisionRangeId)`
- L490 _public function_ `const Softs::FSolverRotation3* GetCollisionParticleRs(int32 CollisionRangeId) const`
- L491 _public function_ `Softs::FSolverRotation3* GetCollisionParticleRs(int32 CollisionRangeId)`
- L492 _public function_ `const FImplicitObjectPtr* GetCollisionGeometry(int32 CollisionRangeId) const`
- L493 _public function_ `const bool* GetCollisionStatus(int32 CollisionRangeId) const`
- L494 _public function_ `const Softs::FSolverRigidTransform3* GetLastSubframeCollisionTransformsCCD(int32 CollisionRangeId) const`
- L498 _public function_ `Softs::FSolverRigidTransform3* GetLastSubframeCollisionTransformsCCD(int32 CollisionRangeId)`
- L506 _public function_ `void SetCollisionGeometry(int32 Offset, int32 Index, TUniquePtr<Chaos::FImplicitObject>&& Geometry)` — `UE_DEPRECATED(5.4, "Use SetCollisionGeometry instead.")`
- L509 _public function_ `const TUniquePtr<Chaos::FImplicitObject>* GetCollisionGeometries(int32 Offset) const` — `UE_DEPRECATED(5.4, "Use GetCollisionGeometry instead.")`
- L512 _public function_ `FPerSolverFieldSystem& GetPerSolverField()` — ---- Field interface ----
- L513 _public function_ `const FPerSolverFieldSystem& GetPerSolverField() const`
- L517 _public prototype_ `UE_CHAOS_DECLARE_INDEXLESS_PROPERTYCOLLECTION_NAME(NumIterations, int32);` — Solver Properties
- L518 _public prototype_ `UE_CHAOS_DECLARE_INDEXLESS_PROPERTYCOLLECTION_NAME(MaxNumIterations, int32);`
- L519 _public prototype_ `UE_CHAOS_DECLARE_INDEXLESS_PROPERTYCOLLECTION_NAME(NumSubsteps, int32);`
- L520 _public prototype_ `UE_CHAOS_DECLARE_INDEXLESS_PROPERTYCOLLECTION_NAME(DynamicSubstepDeltaTime, float);`
- L521 _public prototype_ `UE_CHAOS_DECLARE_INDEXLESS_PROPERTYCOLLECTION_NAME(EnableNumSelfCollisionSubsteps, bool);`
- L522 _public prototype_ `UE_CHAOS_DECLARE_INDEXLESS_PROPERTYCOLLECTION_NAME(NumSelfCollisionSubsteps, int32);`
- L525 _private prototype_ `void Reset();`
- L528 _private prototype_ `void ParticleMassClampAndKinematicStateUpdate(Softs::FSolverParticlesRange& Particles, Softs::FSolverReal MinPerParticleMass, const TFunctionRef<bool(int32)>& KinematicPredicate);` — Begin Force-only methods
- L529 _private prototype_ `Softs::FSolverReal SetParticleMassPerArea(Softs::FSolverParticlesRange& Particles, const FTriangleMesh& Mesh);`
- L530 _private prototype_ `void ParticleMassUpdateDensity(Softs::FSolverParticlesRange& Particles, const FTriangleMesh& Mesh, const Softs::FSolverVec2& Density, const TConstArrayView<FRealSingle>& DensityMultipliers);`
- L534 _private prototype_ `void ResetParticles();` — Begin PBD-only methods
- L535 _private prototype_ `void ResetCollisionParticles(int32 InCollisionParticlesOffset = 0);`
- L536 _private prototype_ `void ParticleMassClampAndKinematicStateUpdate(int32 Offset, int32 Size, Softs::FSolverReal MinPerParticleMass, const TFunctionRef<bool(int32)>& KinematicPredicate);`
- L537 _private prototype_ `Softs::FSolverReal SetParticleMassPerArea(int32 Offset, int32 Size, const FTriangleMesh& Mesh);`
- L538 _private prototype_ `void ParticleMassUpdateDensity(const FTriangleMesh& Mesh, int32 Offset, int32 Size, const Softs::FSolverVec2& Density, const TConstArrayView<FRealSingle>& DensityMultipliers);`
- L541 _private prototype_ `void ApplyPreSimulationTransforms();`
- L542 _private prototype_ `void PreSubstep(const Softs::FSolverReal InterpolationAlpha, bool bDetectSelfCollisions);`
- L545 _private prototype_ `void UpdateSolverField();` — Update the solver field forces/velocities at the particles location
- L550 _private member_ `TUniquePtr<Softs::FEvolution> Evolution;` — Exactly one of these should be non-null
- L551 _private member_ `TUniquePtr<Softs::FPBDEvolution> PBDEvolution;`
- L555 _private member_ `TArray<FClothingSimulationCloth*> Cloths;` — Object arrays
- L558 _private member_ `int32 SolverLOD = 0;` — Solver config
- L559 _private member_ `FClothingSimulationConfig* Config = nullptr;`
- L560 _private member_ `TSharedPtr<FManagedArrayCollection> PropertyCollection;` — Used for backward compatibility only, otherwise the properties are owned by the Config
- L563 _private member_ `TArrayCollectionArray<Softs::FSolverRigidTransform3> PreSimulationTransforms;` — Simulation group attributes
- L564 _private member_ `TArrayCollectionArray<Softs::FSolverVec3> FictitiousAngularVelocities;` — Relative angular velocity of the reference bone. Depends on the fictitious angular scale factor when using PBDEvolution (is applied later for Evolution)
- L565 _private member_ `TArrayCollectionArray<Softs::FSolverVec3> ReferenceSpaceLocations;` — Center of rotations for fictitious forces and local velocity damping in local coordinate to the simulation space location
- L566 _private member_ `TArrayCollectionArray<Softs::FSolverVec3> AppliedReferenceSpaceVelocities;` — Used for local velocity damping.
- L567 _private member_ `TArrayCollectionArray<Softs::FSolverVec3> AppliedReferenceSpaceAngularVelocities;` — Used for local velocity damping.
- L569 _private member_ `TArrayCollectionArray<Softs::FSolverVec3> OriginalReferenceSpaceVelocities;` — Reference space velocity before any scaling or clamping. Used for debug draw.
- L570 _private member_ `TArrayCollectionArray<Softs::FSolverVec3> OriginalReferenceSpaceAngularVelocities;` — Reference space velocity before any scaling or clamping. Used for debug draw.
- L575 _private member_ `TArrayCollectionArray<Softs::FSolverVec3> Normals;` — Particle attributes
- L576 _private member_ `TArrayCollectionArray<Softs::FSolverVec3> OldAnimationPositions;`
- L577 _private member_ `TArrayCollectionArray<Softs::FSolverVec3> AnimationPositions;`
- L578 _private member_ `TArrayCollectionArray<Softs::FSolverVec3> InterpolatedAnimationPositions;`
- L579 _private member_ `TArrayCollectionArray<Softs::FSolverVec3> OldAnimationNormals;`
- L580 _private member_ `TArrayCollectionArray<Softs::FSolverVec3> AnimationNormals;`
- L581 _private member_ `TArrayCollectionArray<Softs::FSolverVec3> InterpolatedAnimationNormals;`
- L582 _private member_ `TArrayCollectionArray<Softs::FSolverVec3> AnimationVelocities;`
- L585 _private member_ `TArrayCollectionArray<int32> CollisionBoneIndices;` — Collision particle attributes
- L586 _private member_ `TArrayCollectionArray<Softs::FSolverRigidTransform3> CollisionBaseTransforms;`
- L587 _private member_ `TArrayCollectionArray<Softs::FSolverRigidTransform3> OldCollisionTransforms;`
- L588 _private member_ `TArrayCollectionArray<Softs::FSolverRigidTransform3> CollisionTransforms;`
- L589 _private member_ `TArrayCollectionArray<Softs::FSolverRigidTransform3> LastSubframeCollisionTransformsCCD;`
- L590 _private member_ `TArrayCollectionArray<bool> Collided;`
- L593 _private member_ `TMap<int32, TUniquePtr<FClothComplexColliders>> ComplexColliders;` — Extended collision data to support complex colliders (FEvolution only)
- L597 _private member_ `TMap<int32, TUniquePtr<FClothConstraints>> ClothsConstraints;` — Cloth constraints
- L600 _private member_ `FReal OldLocalSpaceScale = 1.;` — Local space simulation
- L601 _private member_ `FReal LocalSpaceScale = 1.;`
- L602 _private member_ `FVec3 OldLocalSpaceLocation;` — This is used to translate between world space and simulation space,
- L603 _private member_ `FVec3 OldLocalSpaceLocation;` — add this to simulation space coordinates to get world space coordinates, must keep FReal as underlying type for LWC
- L604 _private member_ `FRotation3 LocalSpaceRotation;` — NOTE: Currently the simulation does not apply LocalSpaceRotation.
- L605 _private member_ `FReal VelocityScale;`
- L609 _private member_ `FSolverReal Time;` — Time stepping
- L610 _private member_ `FSolverReal DeltaTime;`
- L611 _private member_ `int32 NumUsedSubsteps;` — may change depending on dynamic substepping.
- L614 _private member_ `TArray<FSolverVec3> CollisionContacts;` — FEvolution-only
- L615 _private member_ `TArray<FSolverVec3> CollisionNormals;`
- L616 _private member_ `TArray<FSolverReal> CollisionPhis;`
- L619 _private member_ `int32 CollisionParticlesOffset;` — Solver colliders offset (PBD Evolution-only)
- L620 _private member_ `int32 CollisionParticlesSize;` — Number of solver only colliders
- L623 _private member_ `TVec3<FRealSingle> Gravity;` — Solver parameters
- L624 _private member_ `TVec3<FRealSingle> WindVelocity;`
- L625 _private member_ `FRealSingle LegacyWindAdaption;`
- L626 _private member_ `bool bIsClothGravityOverrideEnabled;`
- L629 _private member_ `FPerSolverFieldSystem PerSolverField;` — Field system unique to the cloth solver
- L632 _private member_ `bool bEnableSolver;` — Boolean to enable/disable solver in case caching is used

#### Free symbols / members of external scopes

- L36 _namespace_ `namespace Chaos`
- L46 _namespace_ `namespace Softs` (scope `Chaos`)
- L638 _macro_ `#define CHAOS_CALCULATE_BOUNDS_ISPC_ENABLED_DEFAULT 1`
- L642 _macro_ `#define CHAOS_PRE_SIMULATION_TRANSFORMS_ISPC_ENABLED_DEFAULT 1`
- L646 _macro_ `#define CHAOS_PRE_SUBSTEP_INTERPOLATION_ISPC_ENABLED_DEFAULT 1`
- L650 _macro_ `#define USE_ISPC_KERNEL_CONSOLE_VARIABLES_IN_SHIPPING 0`
- L655 _variable_ `static constexpr bool bChaos_CalculateBounds_ISPC_Enabled = INTEL_ISPC && CHAOS_CALCULATE_BOUNDS_ISPC_ENABLED_DEFAULT;`
- L656 _variable_ `static constexpr bool bChaos_PreSimulationTransforms_ISPC_Enabled = INTEL_ISPC && CHAOS_PRE_SIMULATION_TRANSFORMS_ISPC_ENABLED_DEFAULT;`
- L657 _variable_ `static constexpr bool bChaos_PreSubstepInterpolation_ISPC_Enabled = INTEL_ISPC && CHAOS_PRE_SUBSTEP_INTERPOLATION_ISPC_ENABLED_DEFAULT;`
- L659 _externvar_ `extern bool bChaos_PreSimulationTransforms_ISPC_Enabled;`
- L660 _externvar_ `extern bool bChaos_CalculateBounds_ISPC_Enabled;`
- L661 _externvar_ `extern bool bChaos_PreSubstepInterpolation_ISPC_Enabled;`
