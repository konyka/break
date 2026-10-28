# Runtime / ClothingSystemRuntimeCommon

- module root: `Source/Runtime/ClothingSystemRuntimeCommon`
- headers: 13; symbols: 361
- symbol kinds: class=10, delegate=6, enum=7, enumerator=28, function=62, macro=2, member=127, namespace=2, prototype=104, struct=13
- PrivateDependencyModuleNames: Engine, Slate
- PublicDependencyModuleNames: ClothingSystemRuntimeInterface, Core, CoreUObject
- PublicIncludePathModuleNames: ClothingSystemRuntimeInterface

### `Source/Runtime/ClothingSystemRuntimeCommon/Private/ClothingAssetCustomVersion.h` (Private)


#### struct `FClothingAssetCustomVersion`  
`struct FClothingAssetCustomVersion`  
_L9-30_
- desc: Custom serialization version for clothing assets
- L26 _public member_ `const static FGuid GUID;` — The GUID for this custom version number
- L29 _private function_ `FClothingAssetCustomVersion()`

#### enum `FClothingAssetCustomVersion::Type`  
`enum Type`  
_L11-23_
- L14 _public enumerator_ `BeforeCustomVersionWasAdded = 0` — Before any version changes were made
- L16 _public enumerator_ `AddVertexColorsToPhysicalMesh = 1` — Added storage of vertex colors with sim data, for editor usage
- L18 _public enumerator_ `MovePropertiesToCommonBaseClasses = 2` — Changed memory layouts by moving some properties to base classes
- L21 _public enumerator_ `VersionPlusOne` — -----<new versions can be added above this line>-------------------------------------------------
- L22 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

### `Source/Runtime/ClothingSystemRuntimeCommon/Public/ClothConfig.h` (Public)


#### enum `EClothMassMode`  
`enum class EClothMassMode : uint8`  
_L16-25_
- reflection: `UENUM()`
- desc: Different mass modes deciding the setup process.
- L19 _public enumerator_ `UniformMass` — The mass value is used to set the same mass for each particle.
- L21 _public enumerator_ `TotalMass` — The mass value is used to set the mass of the entire cloth, distributing it to each particle depending on the amount of connected surface area.
- L23 _public enumerator_ `Density` — The mass value is used to set the density of the cloth, calculating the mass for each particle depending on its connected surface area.
- L24 _public enumerator_ `MaxClothMassMode UMETA(Hidden)`

#### class `UClothConfigCommon`  
`class UClothConfigCommon : public UClothConfigBase`  
_L29-68_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UClothConfigBase`
- desc: Common configuration base class.
- L33 _public prototype_ `UClothConfigCommon();`
- L37 _public function_ `virtual void MigrateFrom(const FClothConfig_Legacy&)` — Migrate from the legacy FClothConfig structure.
- L40 _public function_ `virtual void MigrateFrom(const class UClothSharedConfigCommon*)` — Migrate from shared configs.
- L47 _public function_ `virtual bool MigrateTo(FClothConfig_Legacy&) const` — Migrate to the legacy FClothConfig structure. Useful for converting configs that are compatible with this legacy structure. @return true when the migration is possible, false otherwise.
- L51 _public function_ `virtual bool NeedsSelfCollisionData() const override` — Return whether to pre-compute self collision data.
- L54 _public function_ `virtual bool NeedsInverseMasses() const override` — Return whether to pre-compute inverse masses.
- L57 _public function_ `virtual bool NeedsNumInfluences() const override` — Return whether to pre-compute the influences.
- L60 _public function_ `virtual bool NeedsTethers() const override` — Return whether to pre-compute the long range attachment tethers.
- L63 _public function_ `virtual float GetSelfCollisionRadius() const override` — Return the self collision radius to precomute self collision data.
- L66 _public function_ `virtual bool TethersUseGeodesicDistance() const override` — Return whether tethers need to be calculated using geodesic distances instead of eclidean.

#### class `UClothSharedConfigCommon`  
`class UClothSharedConfigCommon : public UClothConfigCommon`  
_L72-78_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UClothConfigCommon`
- desc: Common shared configuration base class.
- L76 _public prototype_ `UClothSharedConfigCommon();`

### `Source/Runtime/ClothingSystemRuntimeCommon/Public/ClothConfig_Legacy.h` (Public)


#### enum `EClothingWindMethod_Legacy`  
`enum class EClothingWindMethod_Legacy : uint8`  
_L14-24_
- reflection: `UENUM()`
- desc: Deprecated, legacy definition kept for backward compatibility only. Use EClothingWindMethodNv instead. Redirected from the now defunct ClothingSystemRuntime module.
- L18 _public enumerator_ `Legacy` — Use legacy wind mode, where accelerations are modified directly by the simulation with no regard for drag or lift
- L23 _public enumerator_ `Accurate` — Use updated wind calculation for NvCloth based solved taking into account drag and lift, this will require those properties to be correctly set in the clothing configuration

#### struct `FClothConstraintSetup_Legacy`  
`struct FClothConstraintSetup_Legacy`  
_L32-58_
- reflection: `USTRUCT()`
- desc: Deprecated, legacy definition kept for backward compatibility only. Use FClothConstraintSetupNv instead. Redirected from the now defunct ClothingSystemRuntime module.
- L36 _public function_ `FClothConstraintSetup_Legacy() : Stiffness(1.0f) , StiffnessMultiplier(1.0f) , StretchLimit(1.0f) , CompressionLimit(1.0f)`
- L45 _public member_ `float Stiffness;` — `UPROPERTY()` — How stiff this constraint is, this affects how closely it will follow the desired position
- L49 _public member_ `float StiffnessMultiplier;` — `UPROPERTY()` — A multiplier affecting the above value
- L53 _public member_ `float StretchLimit;` — `UPROPERTY()` — The hard limit on how far this constraint can stretch
- L57 _public member_ `float CompressionLimit;` — `UPROPERTY()` — The hard limit on how far this constraint can compress

#### struct `FClothConfig_Legacy`  
`struct FClothConfig_Legacy`  
_L66-202_
- reflection: `USTRUCT()`
- desc: Deprecated, legacy definition kept for backward compatibility only. Inherit new config class from UClothConfigCommon instead. Redirected from the now defunct ClothingSystemRuntime module.
- L70 _public function_ `FClothConfig_Legacy() : WindMethod(EClothingWindMethod_Legacy::Legacy) , SelfCollisionRadius(0.0f) , SelfCollisionStiffness(0.0f) , SelfCollisionCullScale(1.0f) , Damping(0.4f) , Friction(0.1f) , WindDragCoefficient(0.02f/100.0f) , WindLiftCoefficient(0.02f/100.0f) , LinearDrag(0.2f) , AngularDrag(0.2f) , LinearInertiaScale(1.0f) , AngularInertiaScale(1.0f) , CentrifugalInertiaScale(1.0f) , SolverFrequency(120.0f) , StiffnessFrequency(100.0f) , GravityScale(1.0f) , GravityOverride(FVector::ZeroVector) , bUseGravityOverride(false) , TetherStiffness(1.0f) , TetherLimit(1.0f) , CollisionThickness(1.0f) , AnimDriveSpringStiffness(1.0f) , AnimDriveDamperStiffness(1.0f)`
- L98 _public member_ `EClothingWindMethod_Legacy WindMethod;` — `UPROPERTY()` — How wind should be processed, Accurate uses drag and lift to make the cloth react differently, legacy applies similar forces to all clothing without drag and lift (similar to APEX)
- L102 _public member_ `FClothConstraintSetup_Legacy VerticalConstraintConfig;` — `UPROPERTY()` — Constraint data for vertical constraints
- L106 _public member_ `FClothConstraintSetup_Legacy HorizontalConstraintConfig;` — `UPROPERTY()` — Constraint data for horizontal constraints
- L110 _public member_ `FClothConstraintSetup_Legacy BendConstraintConfig;` — `UPROPERTY()` — Constraint data for bend constraints
- L114 _public member_ `FClothConstraintSetup_Legacy ShearConstraintConfig;` — `UPROPERTY()` — Constraint data for shear constraints
- L118 _public member_ `float SelfCollisionRadius;` — `UPROPERTY()` — Size of self collision spheres centered on each vert
- L122 _public member_ `float SelfCollisionStiffness;` — `UPROPERTY()` — Stiffness of the spring force that will resolve self collisions
- L125 _public member_ `float SelfCollisionCullScale;` — `UPROPERTY()`
- L129 _public member_ `FVector Damping;` — `UPROPERTY()` — Damping of particle motion per-axis
- L133 _public member_ `float Friction;` — `UPROPERTY()` — Friction of the surface when colliding
- L137 _public member_ `float WindDragCoefficient;` — `UPROPERTY()` — Drag coefficient for wind calculations, higher values mean wind has more lateral effect on cloth
- L141 _public member_ `float WindLiftCoefficient;` — `UPROPERTY()` — Lift coefficient for wind calculations, higher values make cloth rise easier in wind
- L145 _public member_ `FVector LinearDrag;` — `UPROPERTY()` — Drag applied to linear particle movement per-axis
- L149 _public member_ `FVector AngularDrag;` — `UPROPERTY()` — Drag applied to angular particle movement, higher values should limit material bending (per-axis)
- L153 _public member_ `FVector LinearInertiaScale;` — `UPROPERTY()` — Scale for linear particle inertia, how much movement should translate to linear motion (per-axis)
- L157 _public member_ `FVector AngularInertiaScale;` — `UPROPERTY()` — Scale for angular particle inertia, how much movement should translate to angular motion (per-axis)
- L161 _public member_ `FVector CentrifugalInertiaScale;` — `UPROPERTY()` — Scale for centrifugal particle inertia, how much movement should translate to angular motion (per-axis)
- L165 _public member_ `float SolverFrequency;` — `UPROPERTY()` — Frequency of the position solver, lower values will lead to stretchier, bouncier cloth
- L169 _public member_ `float StiffnessFrequency;` — `UPROPERTY()` — Frequency for stiffness calculations, lower values will degrade stiffness of constraints
- L173 _public member_ `float GravityScale;` — `UPROPERTY()` — Scale of gravity effect on particles
- L177 _public member_ `FVector GravityOverride;` — `UPROPERTY()` — Direct gravity override value
- L181 _public member_ `bool bUseGravityOverride;` — `UPROPERTY()` — Use gravity override value vs gravity scale
- L185 _public member_ `float TetherStiffness;` — `UPROPERTY()` — Scale for stiffness of particle tethers between each other
- L189 _public member_ `float TetherLimit;` — `UPROPERTY()` — Scale for the limit of particle tethers (how far they can separate)
- L193 _public member_ `float CollisionThickness;` — `UPROPERTY()` — 'Thickness' of the simulated cloth, used to adjust collisions
- L197 _public member_ `float AnimDriveSpringStiffness;` — `UPROPERTY()` — Default spring stiffness for anim drive if an anim drive is in use
- L201 _public member_ `float AnimDriveDamperStiffness;` — `UPROPERTY()` — Default damper stiffness for anim drive if an anim drive is in use

### `Source/Runtime/ClothingSystemRuntimeCommon/Public/ClothLODData.h` (Public)


#### struct `FClothLODDataCommon`  
`struct FClothLODDataCommon`  
_L10-68_
- reflection: `USTRUCT()`
- desc: Common Cloth LOD representation for all clothing assets.
- L15 _public prototype_ `FClothLODDataCommon() = default;`
- L16 _public prototype_ `FClothLODDataCommon(const FClothLODDataCommon&) = default;`
- L17 _public prototype_ `FClothLODDataCommon(FClothLODDataCommon&&) = default;`
- L18 _public prototype_ `~FClothLODDataCommon() = default;`
- L19 _public prototype_ `FClothLODDataCommon& operator=(const FClothLODDataCommon&) = default;`
- L20 _public prototype_ `FClothLODDataCommon& operator=(FClothLODDataCommon&&) = default;`
- L25 _public member_ `FClothPhysicalMeshData PhysicalMeshData;` — `UPROPERTY(EditAnywhere, Category = SimMesh)` — Raw phys mesh data
- L29 _public member_ `bool bUseMultipleInfluences = false;` — `UPROPERTY()` — Whether to use multiple triangles to interpolate from simulated cloth mesh to render mesh
- L33 _public member_ `float SkinningKernelRadius = 100.0f;` — `UPROPERTY()` — Radius of the weighting kernel used to interpolate from simulated cloth mesh to render mesh
- L37 _public member_ `bool bSmoothTransition = false;` — `UPROPERTY()` — Whether to enable smooth transition from skinned mesh to clothed mesh.
- L42 _public member_ `FClothCollisionData CollisionData_DEPRECATED;` — `UE_DEPRECATED(all, "This property is no longer supported. Use a Physics Asset instead.")` — `UPROPERTY(Meta = (DeprecatedProperty, DeprecationMessage = "This property is no longer supported. Use a Physics Asset instead."))`
- L46 _public member_ `TArray<FClothParameterMask_Legacy> ParameterMasks_DEPRECATED;` — `UE_DEPRECATED(5.5, "This property is no longer supported. Use PointWeightMaps instead.")` — `UPROPERTY(Meta = (DeprecatedProperty, DeprecationMessage = "This property is no longer supported. Use PointWeightMaps instead."))`
- L50 _public member_ `TArray<FPointWeightMap> PointWeightMaps;` — `UPROPERTY(EditAnywhere, Category = Masks)` — Parameter masks defining the physics mesh masked data
- L53 _public prototype_ `void GetParameterMasksForTarget(const uint8 InTarget, TArray<FPointWeightMap*>& OutMasks);` — Get all available parameter masks for the specified target
- L57 _public prototype_ `void PushWeightsToMesh();` — Copy \c ParameterMasks to corresponding targets in \c ClothPhysicalMeshData.
- L61 _public member_ `TArray<FMeshToMeshVertData> TransitionUpSkinData;` — Skinning data for transitioning from a higher detail LOD to this one
- L64 _public member_ `TArray<FMeshToMeshVertData> TransitionDownSkinData;` — Skinning data for transitioning from a lower detail LOD to this one
- L67 _public prototype_ `bool Serialize(FArchive& Ar);` — Custom serialize for transition

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FClothLODDataCommon> : public TStructOpsTypeTraitsBase2<FClothLODDataCommon>`  
_L71-77_
- inherits: `TStructOpsTypeTraitsBase2<FClothLODDataCommon>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L74-76_

#### Free symbols / members of external scopes

- L75 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anondc0ab6990103`)

### `Source/Runtime/ClothingSystemRuntimeCommon/Public/ClothLODData_Legacy.h` (Public)


#### struct `FClothParameterMask_Legacy`  
`struct FClothParameterMask_Legacy`  
_L20-51_
- reflection: `USTRUCT()`
- desc: Deprecated, legacy definition kept for backward compatibility only. Use FPointWeightMap instead. Redirected from the now defunct ClothingSystemRuntime module.
- L24 _public prototype_ `FClothParameterMask_Legacy();`
- L26 _public prototype_ `void MigrateTo(FPointWeightMap& Weights);`
- L30 _public member_ `FName MaskName;` — `UPROPERTY()` — Name of the mask, mainly for users to differentiate
- L34 _public member_ `EWeightMapTargetCommon CurrentTarget;` — `UPROPERTY()` — The currently targeted parameter for the mask
- L38 _public member_ `float MaxValue_DEPRECATED;` — `UPROPERTY()` — The maximum value currently in the mask value array
- L42 _public member_ `float MinValue_DEPRECATED;` — `UPROPERTY()` — The maximum value currently in the mask value array
- L46 _public member_ `TArray<float> Values;` — `UPROPERTY()` — The actual values stored in the mask
- L50 _public member_ `bool bEnabled;` — `UPROPERTY()` — Whether this mask is enabled and able to effect final mesh values

#### class `UClothLODDataCommon_Legacy`  
`class UClothLODDataCommon_Legacy : public UObject`  
_L58-97_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: Deprecated, legacy definition kept for backward compatibility only. Use FClothLODDataCommon instead.
- L62 _public prototype_ `UClothLODDataCommon_Legacy(const FObjectInitializer& Init);`
- L63 _public prototype_ `virtual ~UClothLODDataCommon_Legacy();`
- L67 _public member_ `TObjectPtr<UClothPhysicalMeshDataBase_Legacy> PhysicalMeshData_DEPRECATED;` — `UPROPERTY()` — Deprecated, use ClothPhysicalMeshData instead
- L71 _public member_ `FClothPhysicalMeshData ClothPhysicalMeshData;` — `UPROPERTY()` — Raw phys mesh data
- L75 _public member_ `FClothCollisionData CollisionData;` — `UPROPERTY()` — Collision primitive and convex data for clothing collisions
- L80 _public member_ `TArray<FPointWeightMap> ParameterMasks;` — `UPROPERTY()` — Parameter masks defining the physics mesh masked data
- L84 _public member_ `TArray<FMeshToMeshVertData> TransitionUpSkinData;` — Skinning data for transitioning from a higher detail LOD to this one
- L87 _public member_ `TArray<FMeshToMeshVertData> TransitionDownSkinData;` — Skinning data for transitioning from a lower detail LOD to this one
- L90 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — Custom serialize for transition
- L93 _public prototype_ `virtual void PostLoad() override;` — Migrate deprecated properties
- L96 _public prototype_ `void MigrateTo(struct FClothLODDataCommon& LodData);` — Migrate this deprecated UObject class to the structure format (called by UClothingAssetCommon::PostLoad())

### `Source/Runtime/ClothingSystemRuntimeCommon/Public/ClothPhysicalMeshData.h` (Public)


#### struct `FClothPhysicalMeshData`  
`struct FClothPhysicalMeshData`  
_L25-154_
- reflection: `USTRUCT()`
- desc: Spatial simulation data for a mesh.
- L30 _public prototype_ `FClothPhysicalMeshData();` — Construct an empty cloth physical mesh with default common targets.
- L32 _public prototype_ `~FClothPhysicalMeshData() = default;`
- L33 _public prototype_ `FClothPhysicalMeshData(const FClothPhysicalMeshData&) = default;`
- L34 _public prototype_ `FClothPhysicalMeshData& operator=(const FClothPhysicalMeshData&) = default;`
- L38 _public prototype_ `void MigrateFrom(FClothPhysicalMeshData& ClothPhysicalMeshData);` — Migrate from same, used to migrate LOD data from the UClothLODDataCommon_Legacy.
- L41 _public prototype_ `void MigrateFrom(UClothPhysicalMeshDataBase_Legacy* ClothPhysicalMeshDataBase);` — Migrate from the legacy physical mesh data class, used to migrate LOD data from the UClothLODDataCommon_Legacy.
- L44 _public prototype_ `void Reset(const int32 InNumVerts, const int32 InNumIndices);` — Reset the default common targets for this cloth physical mesh.
- L47 _public prototype_ `void ClearWeightMaps();` — Clear out any default weight maps and delete any other ones.
- L50 _public prototype_ `void BuildSelfCollisionData(float SelfCollisionRadius);` — Build the self collision indices with the specified radius.
- L53 _public prototype_ `void CalculateInverseMasses();` — Recalculate the node inverse masses.
- L56 _public prototype_ `void CalculateNumInfluences();` — Recalculate the number of influences for the bone data.
- L59 _public prototype_ `void CalculateTethers(bool bUseEuclideanDistance, bool bUseGeodesicDistance);` — Recalculate the long range attachment tethers.
- L63 _public function_ `template<typename T> bool HasWeightMap(const T Target) const` — Retrieve whether a vertex weight array has already been registered.
- L67 _public function_ `template<typename T> const FPointWeightMap* FindWeightMap(const T Target) const` — Retrieve a pointer to a registered vertex weight array by unique @param Id, or nullptr if none is found.
- L71 _public function_ `template<typename T> FPointWeightMap* FindWeightMap(const T Target)` — Retrieve a pointer to a registered vertex weight array by unique @param Id, or nullptr if none is found.
- L75 _public function_ `template<typename T> FPointWeightMap& AddWeightMap(const T Target)` — Retrieve a pointer to a registered vertex weight array by unique @param Id, or add one if it doesn't exist already.
- L79 _public function_ `template<typename T> FPointWeightMap& FindOrAddWeightMap(const T Target)` — Retrieve a pointer to a registered vertex weight array by unique @param Id, or add one if it doesn't exist already.
- L83 _public function_ `template<typename T> const FPointWeightMap& GetWeightMap(const T Target) const` — Retrieve a registered vertex weight array by unique @param Id. The array must exists or this function will assert.
- L87 _public function_ `template<typename T> FPointWeightMap& GetWeightMap(const T Target)` — Retrieve a registered vertex weight array by unique @param Id. The array must exists or this function will assert.
- L91 _public member_ `TArray<FVector3f> Vertices;` — `UPROPERTY(EditAnywhere, Category = SimMesh)` — Positions of each simulation vertex
- L95 _public member_ `TArray<FVector3f> Normals;` — `UPROPERTY(EditAnywhere, Category = SimMesh)` — Normal at each vertex
- L100 _public member_ `TArray<FColor> VertexColors;` — `UPROPERTY(EditAnywhere, Category = SimMesh)` — Color at each vertex
- L105 _public member_ `TArray<uint32> Indices;` — `UPROPERTY(EditAnywhere, Category = SimMesh)` — Indices of the simulation mesh triangles
- L109 _public member_ `TMap<uint32, FPointWeightMap> WeightMaps;` — `UPROPERTY(EditAnywhere, Category = SimMesh)` — The weight maps, or masks, used by this mesh, sorted by their target id
- L113 _public member_ `TArray<float> InverseMasses;` — `UPROPERTY(EditAnywhere, Category = SimMesh)` — Inverse mass for each vertex in the physical mesh
- L117 _public member_ `TArray<FClothVertBoneData> BoneData;` — `UPROPERTY(EditAnywhere, Category = SimMesh)` — Indices and weights for each vertex, used to skin the mesh to create the reference pose
- L121 _public member_ `TSet<int32> SelfCollisionVertexSet;` — `UPROPERTY(EditAnywhere, Category = SimMesh)` — Valid indices to use for self collisions (reduced set of Indices)
- L125 _public member_ `FClothTetherData EuclideanTethers;` — `UPROPERTY(EditAnywhere, Category = SimMesh)` — Long range attachment tethers, using euclidean (beeline) distance to find the closest attachment
- L129 _public member_ `FClothTetherData GeodesicTethers;` — `UPROPERTY(EditAnywhere, Category = SimMesh)` — Long range attachment tethers, using geodesic (surface) distance to find the closest attachment
- L133 _public member_ `int32 MaxBoneWeights;` — `UPROPERTY(EditAnywhere, Category = SimMesh)` — Maximum number of bone weights of any vetex
- L137 _public member_ `int32 NumFixedVerts;` — `UPROPERTY(EditAnywhere, Category = SimMesh)` — Number of fixed verts in the simulation mesh (fixed verts are just skinned and do not simulate)
- L141 _public member_ `TArray<uint32> SelfCollisionIndices;` — `UE_DEPRECATED(5.4, "Use SelfCollisionVertexSet instead.")` — `UPROPERTY()`
- L145 _public member_ `TArray<float> MaxDistances_DEPRECATED;` — `UPROPERTY()` — Deprecated. Use WeightMaps instead.
- L147 _public member_ `TArray<float> BackstopDistances_DEPRECATED;` — `UPROPERTY()`
- L149 _public member_ `TArray<float> BackstopRadiuses_DEPRECATED;` — `UPROPERTY()`
- L151 _public member_ `TArray<float> AnimDriveMultipliers_DEPRECATED;` — `UPROPERTY()`

### `Source/Runtime/ClothingSystemRuntimeCommon/Public/ClothTetherData.h` (Public)


#### struct `FClothTetherData`  
`struct FClothTetherData`  
_L21-89_
- reflection: `USTRUCT()`
- desc: Long range attachment tether pathfinding based on Dijkstra's algorithm. For more information about the long range attachment, see: https://matthias-research.github.io/pages/publications/sca2012cloth.pdf
- L32 _public member_ `static constexpr float KinematicDistanceThreshold = 0.1f;` — Particles whose MaxDistance / TetherEnds mask is strictly less than this are treated as kinematic for tether sorting. Authoritative source for the legacy "barely allowed to move" cutoff — referenced by the converter and consumed throughout the cloth simulation pipeline so the same threshold is applied to legacy assets at convert time and to runtime tether generation.
- L35 _public member_ `TArray<TArray<TTuple<int32, int32, float>>> Tethers;` — Long range attachment tether start/end/length, sorted in sequential batches of independant tethers.
- L41 _public prototype_ `void GenerateTethers( const TConstArrayView<FVector3f>& Points,` — Generate the tethers by following the triangle mesh network from the closest kinematic to each dynamic point. Inside array items can be processed concurrently, but the outside array must be iterated on sequentially.
- L84 _public prototype_ `void GenerateTethers( TArray<TArray<TPair<float, int32>>>&& PerDynamicNodeTethers);` — Generate the tether batches from existing tether data. PerDynamicNodeTethers is an array where Index = DynamicIndex, and Value is an array of TPair<float, int32>  = {Distance, KinematicIndex}
- L88 _public prototype_ `bool Serialize(FArchive& Ar);` — Custom serializer, since neiher an array of array nor a tuple can be set as a UPROPERTY.

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FClothTetherData> : public TStructOpsTypeTraitsBase2<FClothTetherData>`  
_L92-99_
- inherits: `TStructOpsTypeTraitsBase2<FClothTetherData>`
- L98 _public member_ `static constexpr EPropertyObjectReferenceType WithSerializerObjectReferences = EPropertyObjectReferenceType::None;`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L95-97_

#### Free symbols / members of external scopes

- L96 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anon3408cde60103`)

### `Source/Runtime/ClothingSystemRuntimeCommon/Public/ClothingAsset.h` (Public)


#### struct `ClothingAssetUtils::FClothingAssetMeshBinding`  
`struct FClothingAssetMeshBinding`  
_L25-31_
- desc: Helper struct to hold binding information on a clothing asset, used to enumerate all of the bindings on a skeletal mesh with \c GetAllMeshClothingAssetBindings() below.
- L27 _public member_ `UClothingAssetBase* Asset;`
- L28 _public member_ `int32 LODIndex;`
- L29 _public member_ `int32 SectionIndex;`
- L30 _public member_ `int32 AssetInternalLodIndex;`

#### class `UClothingAssetCustomData`  
`class UClothingAssetCustomData : public UObject`  
_L115-118_
- reflection: `UE_DEPRECATED(5.0, "Redundant class.")`
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UObject`
- desc: Custom data wrapper for clothing assets.

#### enum `EClothingCachedDataFlagsCommon`  
`enum class EClothingCachedDataFlagsCommon : uint8`  
_L123-131_
- desc: Common flags used by InvalidateCachedData.
- L125 _public enumerator_ `None = 0`
- L126 _public enumerator_ `InverseMasses = 1 << 0`
- L127 _public enumerator_ `NumInfluences = 1 << 1`
- L128 _public enumerator_ `SelfCollisionData = 1 << 2`
- L129 _public enumerator_ `Tethers = 1 << 3`
- L130 _public enumerator_ `All = 0xFF`

#### class `UClothingAssetCommon`  
`class UClothingAssetCommon : public UClothingAssetBase`  
_L143-392_
- reflection: `UCLASS(hidecategories = Object, BlueprintType, MinimalAPI)`
- inherits: `UClothingAssetBase`
- desc: Implementation of non-solver specific, but common Engine related functionality. Solver specific implementations may wish to override this class to construct their own default instances of child classes, such as \c ClothSimConfig and \c CustomData, as well as override the \c AddNewLod() factory to build their own implementation of \c UClothLODDataBase.
- L148 _public prototype_ `UClothingAssetCommon(const FObjectInitializer& ObjectInitializer);`
- L156 _public prototype_ `virtual bool BindToSkeletalMesh(USkeletalMesh* InSkelMesh, const int32 InMeshLodIndex, const int32 InSectionIndex, const int32 InAssetLodIndex) override;` — Create weights for skinning the render mesh to our simulation mesh, and weights to drive our sim mesh from the skeleton.
- L166 _public prototype_ `virtual void UnbindFromSkeletalMesh(USkeletalMesh* InSkelMesh, const int32 InMeshLodIndex, const int32 InSectionIndex) override;` — Unbind Clothing Data from the specified Skeletal Mesh LOD sections. If MeshLodIndex is INDEX_NONE, the Clothing Data will get unbound from all LODs and all sections (ignoring SectionIndex in this case). If SectionIndex is INDEX_NONE, the Clothing Data will get unbound from all sections of the specified LOD. @param InSkelMesh The Skeletal Mesh to unbind the Clothing Data from. @param InMeshLodIndex Mesh LOD to remove this asset from (could still be bound to other LODs), or INDEX_NONE to unbind all LODs. @param InSectionIndex The Skeletal Mesh section to unbind, or INDEX_NONE to unbind all sections.
- L169 _public function_ `virtual void UnbindFromSkeletalMesh(USkeletalMesh* InSkelMesh) override` — `UE_DEPRECATED(5.8, "Use UnbindFromSkeletalMesh(USkeletalMesh* InSkelMesh, const int32 InMeshLodIndex, const int32 InSectionIndex) instead.")`
- L175 _public function_ `virtual void UnbindFromSkeletalMesh(USkeletalMesh* InSkelMesh, const int32 InMeshLodIndex) override` — `UE_DEPRECATED(5.8, "Use UnbindFromSkeletalMesh(USkeletalMesh* InSkelMesh, const int32 InMeshLodIndex, const int32 InSectionIndex) instead.")`
- L184 _public prototype_ `virtual void UpdateAllLODBiasMappings(USkeletalMesh* SkeletalMesh) override;` — Update all extra LOD deformer mappings. This should be called whenever the raytracing LOD bias has changed.
- L193 _public prototype_ `virtual void GetSimulationMesh(const int32 InMeshLodIndex, TArray<FVector3f>& OutPositions, TArray<uint32>& OutIndices, TArray<float>& OutMaxDistances) const override;` — Return the simulation mesh. Used to calculate the LOD bias deformer mappings. @param OutPositions The simulation mesh positions. @param OutIndices The simulation mesh triangle indices. @param OutMaxDistances The simulation mesh max distance attributes (0 for kinematic, >0 for dynamic). must match the number of positions.
- L200 _public prototype_ `void ApplyParameterMasks(bool bUpdateFixedVertData = false, bool bInvalidateDerivedDataCache = true);` — Callback envoked after weights have been edited. Calls \c PushWeightsToMesh() on each \c ClothLodData, and invalidates cached data. Optionaly recalculate the owner's sections fixed vertex data based on this asset masks, and invalidate the DDC for this asset.
- L207 _public prototype_ `void BuildLodTransitionData();` — Builds the LOD transition data. When we transition between LODs we skin the incoming mesh to the outgoing mesh in exactly the same way the render mesh is skinned to create a smooth swap
- L213 _public prototype_ `virtual void PreEditUndo() override;` — Stop any simulation from using this asset.
- L218 _public prototype_ `virtual void PostEditUndo() override;` — Restart simulation using this asset after undo change.
- L226 _public prototype_ `virtual void RefreshBoneMapping(USkeletalMesh* InSkelMesh) override;` — Rebuilds the \c UsedBoneIndices array from looking up the entries in the \c UsedBoneNames array, in the \p InSkelMesh's reference skeleton.
- L229 _public prototype_ `void CalculateReferenceBoneIndex();` — Calculates the preferred root bone for the simulation.
- L232 _public prototype_ `virtual bool IsValidLod(int32 InLodIndex) const override;` — Returns \c true if \p InLodIndex is a valid LOD id (index into \c ClothLodData).
- L235 _public prototype_ `virtual int32 GetNumLods() const override;` — Returns the number of valid LOD's (length of the \c ClothLodData array).
- L242 _public function_ `virtual void InvalidateAllCachedData() override` — Called on the clothing asset when the base data (physical mesh, config etc.) has changed, so any intermediate generated data can be regenerated.
- L248 _public prototype_ `void InvalidateFlaggedCachedData(EClothingCachedDataFlagsCommon Flags);` — Called on the clothing asset when the base data (physical mesh, config etc.) has changed, so any intermediate generated data can be regenerated.
- L253 _public prototype_ `virtual int32 AddNewLod() override;` — Add a new LOD class instance.
- L256 _public prototype_ `void RemoveLastLod();` — Remove the last clothing LOD (and unbind it).
- L259 _public prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& ChainEvent) override;` — Called after changes in any of the asset properties.
- L264 _public function_ `template<typename ClothConfigType, typename = typename TEnableIf<TIsDerivedFrom<ClothConfigType, UClothConfigBase>::IsDerived>::Type> const ClothConfigType* GetClothConfig() const` — Return a const cloth config pointer of the desired cloth config type, or nullptr if there isn't any suitable.
- L272 _public function_ `template<typename ClothConfigType, typename = typename TEnableIf<TIsDerivedFrom<ClothConfigType, UClothConfigBase>::IsDerived>::Type> ClothConfigType* GetClothConfig()` — Return a cloth config pointer of the desired cloth config type, or nullptr if there isn't any suitable.
- L279 _public prototype_ `virtual void PostLoad() override;` — Migrate deprecated objects.
- L281 _public prototype_ `static void DeclareConstructClasses(TArray<FTopLevelAssetPath>& OutConstructClasses, const UClass* SpecificSubclass);`
- L285 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — Serialize deprecated objects.
- L288 _public prototype_ `virtual void PostUpdateAllAssets() override;` — Propagate the shared simulation configs between assets. Called after all cloth assets sharing the same simulation are loaded.
- L292 _public member_ `TObjectPtr<UPhysicsAsset> PhysicsAsset;` — `UPROPERTY(EditAnywhere, Category = "Skeletal Mesh Clothing")` — The physics asset to extract collisions from when building a simulation.
- L297 _public member_ `TMap<FName, TObjectPtr<UClothConfigBase>> ClothConfigs;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, EditFixedSize, Instanced, Category = "Skeletal Mesh Clothing")` — Simulation specific cloth parameters. Use GetClothConfig() to retrieve the correct parameters/config type for the desired cloth simulation system.
- L304 _public member_ `TObjectPtr<UClothConfigBase> ClothSharedSimConfig_DEPRECATED;` — `UPROPERTY()` — Shared by all cloth instances in a skeletal mesh Only supported with Chaos Cloth for now This may not be editable on unused cloth assets
- L309 _public member_ `TObjectPtr<UClothConfigBase> ClothSimConfig_DEPRECATED;` — `UPROPERTY()` — Parameters for how the NVcloth behaves. These will have no effect on Chaos cloth
- L316 _public member_ `TObjectPtr<UClothConfigBase> ChaosClothSimConfig_DEPRECATED;` — `UPROPERTY()` — Parameters for how Chaos cloth behaves These will not affect NVcloth For now, we have two configuration parameters so that we can switch between chaos and non chaos at will without losing the original NVcloth data
- L320 _public member_ `TArray<TObjectPtr<UClothLODDataCommon_Legacy>> ClothLodData_DEPRECATED;` — `UPROPERTY()` — Deprecated. Use LodData instead
- L325 _public member_ `TArray<FClothLODDataCommon> LodData;` — `UPROPERTY()` — The actual asset data, listed by LOD.
- L329 _public member_ `TArray<int32> LodMap;` — `UPROPERTY()` — Tracks which clothing LOD each skel mesh LOD corresponds to (LodMap[SkelLod]=ClothingLod).
- L333 _public member_ `TArray<FName> UsedBoneNames;` — `UPROPERTY()` — List of bones this asset uses inside its parent mesh.
- L337 _public member_ `TArray<int32> UsedBoneIndices;` — `UPROPERTY()` — List of the indices for the bones in UsedBoneNames, used for remapping.
- L341 _public member_ `int32 ReferenceBoneIndex;` — `UPROPERTY()` — Bone to treat as the root of the simulation space.
- L349 _public member_ `FClothConfig_Legacy ClothConfig_DEPRECATED;` — `UPROPERTY()` — Deprecated property for transitioning the \c FClothConfig struct to the \c UClothConfigBase array, in a new property called \c ClothConfigs.
- L356 _private function_ `template<typename ClothConfigType, typename = typename TEnableIf<TIsDerivedFrom<ClothConfigType, UClothConfigBase>::IsDerived>::Type> void SetClothConfig(ClothConfigType* ClothConfig)` — Add or replace a new cloth config of the specified type.
- L366 _private prototype_ `bool AddClothConfigs();` — Create and add any missing cloth configs. If a config from a different factory exists already, the newly created config will attempt to initialize its parameters from it. Return true when at least one config has been added, false otherwise.
- L371 _private prototype_ `void PropagateSharedConfigs(bool bMigrateSharedConfigToConfig=false);` — Propagate the shared simulation configs between assets. Also migrate all deprecated shared parameters which have been moved to the per cloth configs if required. Called after a cloth asset is created or loaded.
- L376 _private function_ `template<typename PredicateType> bool AnyOfClothConfigs(PredicateType Predicate) const` — Return true when any one of the cloth configs fullfill the predicate. Used to select which type of data to cache.
- L386 _private prototype_ `virtual TArray<TPair<FText, FText>> GetStats() const override;` — Return all LODs' stats.
- L389 _private prototype_ `void ReregisterComponentsUsingClothing();` — Helper functions used in PostPropertyChangeCb
- L390 _private prototype_ `void ForEachInteractorUsingClothing(TFunction<void (UClothingSimulationInteractor*)> Func);`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API CLOTHINGSYSTEMRUNTIMECOMMON_API`
- L18 _namespace_ `namespace ClothingAssetUtils`
- L43 _prototype_ `void UnbindFromSkeletalMesh(const UClothingAssetBase& Asset, USkeletalMesh& SkeletalMesh, const int32 MeshLodIndex = INDEX_NONE, const int32 SectionIndex = INDEX_NONE);` (scope `ClothingAssetUtils`) — Unbind Clothing Data from the specified Skeletal Mesh LOD sections. If MeshLodIndex is INDEX_NONE, the Clothing Data will get unbound from all LODs and all sections (ignoring SectionIndex in this case). If SectionIndex is INDEX_NONE, the Clothing Data will get unbound from all sections of the specified LOD. @param Asset The clothing data to unbind. @param SkeletalMesh The Skeletal Mesh to unbind the Clothing Data from. @param MeshLodIndex Mesh LOD to remove this asset from (could still be bound to other LODs), or INDEX_NONE to unbind all LODs. @param SectionIndex The Skeletal Mesh section to unbind, or INDEX_NONE to unbind all sections.
- L50 _prototype_ `bool HasAnyMeshClothingAssetBindings(const USkeletalMesh* SkeletalMesh);` (scope `ClothingAssetUtils`) — Return whether there are any cloth bindings whithin the skeletal mesh model. Uses the cloth mapping data as the source predicate to match the behavior of GetAllMeshClothingAssetBindings(). @param SkeletalMesh The skeletal mesh to check the cloth binding from.
- L58 _prototype_ `bool HasAnyLodMeshClothingAssetBindings(const USkeletalMesh* SkeletalMesh, const int32 LodIndex);` (scope `ClothingAssetUtils`) — Return whether there are any cloth bindings whithin the skeletal mesh model LOD. Uses the cloth mapping data as the source predicate to match the behavior of GetAllLodMeshClothingAssetBindings(). @param SkeletalMesh The skeletal mesh to check the cloth binding from. @param LodIndex The specified LOD.
- L65 _prototype_ `void GetAllMeshClothingAssetBindings(const USkeletalMesh* SkeletalMesh, TArray<FClothingAssetMeshBinding>& OutBindings);` (scope `ClothingAssetUtils`) — Given a skeletal mesh model, find all of the currently bound clothing assets and their binding information. @param SkeletalMesh The skeletal mesh to extract binding from. @param OutBindings The list of bindings to write to.
- L73 _prototype_ `void GetAllLodMeshClothingAssetBindings( const USkeletalMesh* SkeletalMesh, TArray<FClothingAssetMeshBinding>& OutBindings, int32 LodIndex);` (scope `ClothingAssetUtils`) — Given a skeletal mesh model, find all of the currently bound clothing assets and their binding information. @param SkeletalMesh The skeletal mesh to extract binding from. @param OutBindings The list of bindings to write to. @param LodIndex The specified LOD.
- L84 _prototype_ `void ClearLODBiasMappings(USkeletalMesh& SkeletalMesh, const int32 UpdatedLodIndex, const int32 SectionIndex);` (scope `ClothingAssetUtils`) — Clear all deformer section that relies on the specified cloth sim data bound to a LOD section. @param SkeletalMesh The skeletal mesh to clear. @param UpdatedLodIndex The recently updated Skeletal Mesh LOD index from which the bias mapping needs to be cleared. @param SectionIndex The section to clear.
- L96 _prototype_ `void UpdateLODBiasMappings( const UClothingAssetBase& Asset, const USkeletalMesh* SkeletalMesh, const int32 UpdatedLODIndex, const int32 SectionIndex, const bool bSmoothTransition = true, const bool bUseMultipleInfluences = false, const float SkinningKernelRadius = 20.f);` (scope `ClothingAssetUtils`) — Add extra cloth deformer mappings to cope with a different raytracing LOD than the one currently rendered. @param Asset The Clothing Asset to use to generate the mapping of the section for all LODs above the updated LOD up to the max LOD. @param SkeletalMesh The Skeletal Mesh for which to calculate the render deformer mapping @param UpdatedLODIndex The Skeletal Mesh LOD that has just been updated. Only LOD from above this one will receive new bias mapping if they exist. @param SectionIndex The Skeletal Mesh section index to update. @param bSmoothTransition Whether to create a smooth transition area between skinned render vertices and deformed render vertices using the vertex mapping blend weight. @param bUseMultipleInfluences Whether to use multiple simulation mesh triangles to set the deformer influences of the render vertices. @param SkinningKernelRadius The radius from which to search for the closest simulation mesh triangles.
- L106 _prototype_ `void ClearSectionClothingData(FSkelMeshSection& Section);` (scope `ClothingAssetUtils`) — `UE_DEPRECATED(5.7, "Unused low level function, will be removed or re-added as a member to FSkelMeshSection.")`
- L132 _prototype_ `ENUM_CLASS_FLAGS(EClothingCachedDataFlagsCommon);`
- L379 _function_ `` (scope `UClothingAssetCommon::AnyOfClothConfigs`)

### `Source/Runtime/ClothingSystemRuntimeCommon/Public/ClothingSimulation.h` (Public)


#### class `FClothingSimulationContextCommon`  
`class FClothingSimulationContextCommon : public IClothingSimulationContext`  
_L22-86_
- inherits: `IClothingSimulationContext`
- desc: Base simulation data that just about every simulation would need.
- L25 _public prototype_ `FClothingSimulationContextCommon();`
- L26 _public prototype_ `FClothingSimulationContextCommon(const FClothingSimulationContextCommon&) = default;`
- L27 _public prototype_ `FClothingSimulationContextCommon& operator=(const FClothingSimulationContextCommon&) = default;`
- L32 _public prototype_ `virtual void Fill(const USkeletalMeshComponent* InComponent, float InDeltaSeconds, float InMaxPhysicsDelta, bool bIsInitialization);` — Fill this context using the given skeletal mesh component
- L36 _protected prototype_ `virtual void FillBoneTransforms(const USkeletalMeshComponent* InComponent);` — Default fill behavior as expected to be used by every simulation
- L37 _protected prototype_ `virtual void FillRefToLocals(const USkeletalMeshComponent* InComponent, bool bIsInitialization);`
- L38 _protected prototype_ `virtual void FillComponentToWorld(const USkeletalMeshComponent* InComponent);`
- L39 _protected prototype_ `virtual void FillWorldGravity(const USkeletalMeshComponent* InComponent);`
- L40 _protected prototype_ `virtual void FillWindVelocity(const USkeletalMeshComponent* InComponent);`
- L41 _protected prototype_ `virtual void FillDeltaSeconds(float InDeltaSeconds, float InMaxPhysicsDelta);`
- L42 _protected prototype_ `virtual void FillTeleportMode(const USkeletalMeshComponent* InComponent, float InDeltaSeconds, float InMaxPhysicsDelta);`
- L43 _protected prototype_ `virtual void FillMaxDistanceScale(const USkeletalMeshComponent* InComponent);`
- L44 _protected prototype_ `virtual void FillSolverGeometryScale(const USkeletalMeshComponent* InComponent);`
- L48 _public member_ `TArray<FTransform> BoneTransforms;` — Component space bone transforms of the owning component
- L51 _public member_ `TArray<FMatrix44f> RefToLocals;` — Ref to local matrices from the owning component (for skinning fixed verts)
- L54 _public member_ `FTransform ComponentToWorld;` — Component to world transform of the owning component
- L57 _public member_ `FVector WorldGravity;` — Gravity extracted from the world
- L60 _public member_ `FVector WindVelocity;` — Wind velocity at the component location
- L64 _public member_ `float WindAdaption;` — Wind adaption, a measure of how quickly to adapt to the wind speed when using the legacy wind calculation mode
- L67 _public member_ `float DeltaSeconds;` — Delta for this tick
- L70 _public member_ `float VelocityScale;` — Velocity scale to compensate input velocities in case the MaxPhysicsDelta kicks in
- L73 _public member_ `EClothingTeleportMode TeleportMode;` — Whether and how we should teleport the simulation this tick
- L76 _public member_ `float MaxDistanceScale;` — Scale for the max distance constraints of the simulation mesh
- L79 _public member_ `float SolverGeometryScale = 1.f;` — Scale applied to all incoming geometry
- L82 _public member_ `int32 PredictedLod;` — The predicted LOD of the skeletal mesh component running the simulation
- L85 _public member_ `FClothingSimulationCacheData CacheData;` — Data read from the cache.

#### class `PRAGMA_DISABLE_DEPRECATION_WARNINGS`  
`PRAGMA_DISABLE_DEPRECATION_WARNINGS : public IClothingSimulation`  
_L90-105_
- reflection: `UE_DEPRECATED(5.7, "Use IClothingSimulationInterface instead.")`
- inherits: `IClothingSimulationPRAGMA_ENABLE_DEPRECATION_WARNINGS`
- desc: Base simulation to fill in common data for the base context
- L95 _public prototype_ `FClothingSimulationCommon();`
- L96 _public prototype_ `virtual ~FClothingSimulationCommon();`
- L100 _protected prototype_ `virtual void FillContextAndPrepareTick(const USkeletalMeshComponent* InComponent, float InDeltaTime, IClothingSimulationContext* InOutContext, bool bIsInitialization, bool bForceTeleportResetOnly) override;` — Fills in the base data for a clothing simulation
- L104 _protected member_ `float MaxPhysicsDelta;` — Maximum physics time, incoming deltas will be clamped down to this value on long frames

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API CLOTHINGSYSTEMRUNTIMECOMMON_API`
- L15 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Compute Clothing Normals"), STAT_ClothComputeNormals, STA` — Common simulation stats
- L16 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Internal Solve"), STAT_ClothInternalSolve, STATGROUP_Phy`
- L17 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Update Collisions"), STAT_ClothUpdateCollisions, STATGROUP_`
- L18 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Skin Physics Mesh"), STAT_ClothSkinPhysMesh, STATGROUP_`
- L19 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Fill Context"), STAT_ClothFillContext, STATGROUP_Physi`

### `Source/Runtime/ClothingSystemRuntimeCommon/Public/ClothingSimulationCacheData.h` (Public)


#### struct `FClothingSimulationCacheData`  
`struct FClothingSimulationCacheData`  
_L9-55_
- L12 _public member_ `TArray<FVector> CachedPositions;` — Solver space cached positions for the kinematics targets. (Sparse--use CacheIndices to map to full)
- L15 _public member_ `TArray<FVector> CachedVelocities;` — Solver space cached velocities for the kinematics targets. (Sparse--use CacheIndices to map to full)
- L18 _public member_ `TArray<int32> CacheIndices;` — Indices used to map from CachedPositions/Velocities to solver indices
- L21 _public member_ `TMap<int32, FTransform> CachedReferenceSpaceTransforms;` — Cached ReferenceSpaceTransform per cloth. Key is Cloth GroupId
- L23 _public prototype_ `FClothingSimulationCacheData() = default;`
- L24 _public prototype_ `FClothingSimulationCacheData(const FClothingSimulationCacheData& Other) = default;`
- L25 _public function_ `FClothingSimulationCacheData(FClothingSimulationCacheData&& Other) : CachedPositions(MoveTemp(Other.CachedPositions)) , CachedVelocities(MoveTemp(Other.CachedVelocities)) , CacheIndices(MoveTemp(Other.CacheIndices)) , CachedReferenceSpaceTransforms(MoveTemp(Other.CachedReferenceSpaceTransforms))`
- L32 _public prototype_ `FClothingSimulationCacheData& operator=(const FClothingSimulationCacheData& Other) = default;`
- L33 _public function_ `FClothingSimulationCacheData& operator=(FClothingSimulationCacheData&& Other)`
- L42 _public function_ `void Reset()`
- L50 _public function_ `bool HasData() const`

### `Source/Runtime/ClothingSystemRuntimeCommon/Public/ClothingSystemRuntimeCommonModule.h` (Public)


#### class `FClothingSystemRuntimeCommonModule`  
`class FClothingSystemRuntimeCommonModule : public IModuleInterface`  
_L7-18_
- inherits: `IModuleInterface`
- L12 _public prototype_ `FClothingSystemRuntimeCommonModule();`
- L14 _public prototype_ `virtual void StartupModule() override;`
- L15 _public prototype_ `virtual void ShutdownModule() override;`

### `Source/Runtime/ClothingSystemRuntimeCommon/Public/PointWeightMap.h` (Public)


#### enum `EWeightMapTargetCommon`  
`enum class EWeightMapTargetCommon : uint8`  
_L11-24_
- reflection: `UENUM()`
- desc: The possible targets for a physical mesh point weight map.
- L13 _public enumerator_ `None = 0` — None, should always be zero
- L14 _public enumerator_ `MaxDistance` — The distance that each vertex can move away from its reference (skinned) position
- L15 _public enumerator_ `BackstopDistance` — Distance along the plane of the surface that the particles can travel (separation constraint)
- L16 _public enumerator_ `BackstopRadius` — Radius of movement to allow for backstop movement
- L17 _public enumerator_ `AnimDriveStiffness` — Strength of anim drive per-particle (spring driving particle back to skinned location
- L18 _public enumerator_ `AnimDriveDamping_DEPRECATED UMETA(Hidden)` — Chaos onlyweightmap, deprecated from the common declaration
- L19 _public enumerator_ `FirstUserTarget`
- L21 _public enumerator_ `LastUserTarget = 200` — Users can add additional targets between this range.
- L23 _public enumerator_ `TetherEndsMask` — Add additional common targets after here.

#### struct `FPointWeightMap`  
`struct FPointWeightMap`  
_L32-188_
- reflection: `USTRUCT()`
- desc: A mask is simply some storage for a physical mesh parameter painted onto clothing. Used in the editor for users to paint onto and then target to a parameter, which is then later applied to a phys mesh
- L36 _public function_ `FPointWeightMap() #if WITH_EDITORONLY_DATA : Name(NAME_None) , CurrentTarget((uint8)EWeightMapTargetCommon::None) , bEnabled(false) #endif`
- L44 _public function_ `explicit FPointWeightMap(int32 NumPoints, float Value = 0.f) #if WITH_EDITORONLY_DATA : Name(NAME_None) , CurrentTarget((uint8)EWeightMapTargetCommon::None) , bEnabled(false) #endif`
- L54 _public function_ `explicit FPointWeightMap(const TConstArrayView<float>& InValues) : Values(InValues) #if WITH_EDITORONLY_DATA , Name(NAME_None) , CurrentTarget((uint8)EWeightMapTargetCommon::None) , bEnabled(false) #endif`
- L63 _public function_ `FPointWeightMap(const TConstArrayView<float>& InValues, float Offset, float Scale) #if WITH_EDITORONLY_DATA : Name(NAME_None) , CurrentTarget((uint8)EWeightMapTargetCommon::None) , bEnabled(false) #endif`
- L78 _public prototype_ `~FPointWeightMap() = default;`
- L84 _public function_ `void Initialize(const int32 NumPoints)` — Reset this map to the specified number of points, and set all the values to zero. @param NumPoints the number of points to initialize the map with.
- L101 _public function_ `void Initialize(const FPointWeightMap& Source, T Target)`
- L111 _public function_ `void Empty()` — Empty this map of any values.
- L115 _public function_ `int32 Num() const` — Return the number of values in this map.
- L122 _public function_ `const float& operator[](int32 Index) const` — Return the current float value for the requested point. @param Index the value/point index to retrieve, must be within range or it will assert.
- L129 _public function_ `float& operator[](int32 Index)` — Return the current float value for the requested point. @param Index the value/point index to retrieve, must be within range or it will assert.
- L136 _public function_ `float GetValue(int32 Index) const` — Get a value from the map, or return 0 if the index is out of bounds. @param Index the value/point index to retrieve
- L144 _public function_ `void SetValue(int32 Index, float Value)` — Set a value in the map checking first whether the index is within bounds. @param Index the value/point index to set @param Value the value to set
- L152 _public function_ `bool IsBelowThreshold(const int32 Index, const float Threshold=0.1f) const` — Return whether the specified point weight is below (or equal) to the specified threshold. @param Index the value/point index to retrieve @param Threshold, the value threshold to test against for.
- L156 _public function_ `bool AreAnyBelowThreshold(const int32 Index0, const int32 Index1, const int32 Index2, const float Threshold=0.1f) const` — Return whether at least one of the specified triangle points has weight below (or equal) to the specified @param Threshold.
- L160 _public function_ `bool AreAllBelowThreshold(const int32 Index0, const int32 Index1, const int32 Index2, const float Threshold=0.1f) const` — Return whether all of the specified triangle points have weight below (or equal) to the specified @param Threshold.
- L164 _public function_ `bool IsZeroed() const` — Return whether all points' values are zero.
- L168 _public function_ `void CalcRanges(float& MinValue, float& MaxValue)` — Calculates Min/Max values based on values.
- L173 _public member_ `TArray<float> Values;` — `UPROPERTY()` — The actual values stored in the mask
- L178 _public member_ `FName Name;` — `UPROPERTY()` — Name of the mask, mainly for users to differentiate
- L182 _public member_ `uint8 CurrentTarget;` — `UPROPERTY()` — The currently targeted parameter for the mask, @seealso EWeightMapTargetCommon
- L186 _public member_ `bool bEnabled;` — `UPROPERTY()` — Whether this mask is enabled and able to effect final mesh values

#### Free symbols / members of external scopes

- L165 _function_ `` (scope `FPointWeightMap::IsZeroed`)

### `Source/Runtime/ClothingSystemRuntimeCommon/Public/Utils/ClothingMeshUtils.h` (Public)


#### struct `ClothingMeshUtils::FMeshToMeshFilterSet`  
`struct FMeshToMeshFilterSet`  
_L15-19_
- L17 _public member_ `TSet<int32> SourceTriangles;` — Set of triangle index in the source ClothMeshDesc
- L18 _public member_ `TSet<int32> TargetVertices;` — Set of vertex index in the target ClothMeshDesc

#### class `ClothingMeshUtils::ClothMeshDesc`  
`class ClothMeshDesc`  
_L21-100_
- L24 _public function_ `ClothMeshDesc(TConstArrayView<FVector3f> InPositions, TConstArrayView<FVector3f> InNormals, TConstArrayView<uint32> InIndices) : Positions(InPositions) , Normals(InNormals) , Indices(InIndices) , bHasValidBVH(false)`
- L32 _public function_ `ClothMeshDesc(TConstArrayView<FVector3f> InPositions, TConstArrayView<FVector3f> InNormals, TConstArrayView<FVector3f> InTangents, TConstArrayView<uint32> InIndices) : Positions(InPositions) , Normals(InNormals) , Tangents(InTangents) , Indices(InIndices) , bHasValidBVH(false)`
- L42 _public function_ `ClothMeshDesc(TConstArrayView<FVector3f> InPositions, TConstArrayView<uint32> InIndices) : Positions(InPositions) , Indices(InIndices) , bHasValidBVH(false)` — Construct a mesh descriptor with re-calculated (averaged) normals to match the simulation output.
- L51 _public function_ `const TConstArrayView<FVector3f>& GetPositions() const`
- L52 _public function_ `const TConstArrayView<FVector3f>& GetNormals() const`
- L53 _public function_ `const TConstArrayView<FVector3f>& GetTangents() const`
- L54 _public function_ `const TConstArrayView<uint32>& GetIndices() const`
- L57 _public function_ `bool HasValidMesh() const` — Return whether the mesh descriptor has a valid number of normals and triangle indices.
- L60 _public function_ `bool HasTangents() const` — Return whether this descriptor has been initialized with tangent information.
- L63 _public function_ `bool HasAveragedNormals() const` — Return whether this descriptor has been initialized with the normals generated from the averaged triangle normals.
- L66 _public prototype_ `float DistanceToTriangle(const FVector& Position, int32 TriangleBaseIndex) const;` — Find the distance to the specified triangle from a point.
- L69 _public function_ `TArray<int32>& GetFilteredTriangles() const` — Return the current list of filtered triangles.
- L72 _public prototype_ `void GatherAllSourceTrianglesForTargetVertex(const TArray<FMeshToMeshFilterSet>& FilterSets, int32 TargetVertex) const;` — Create an array with all source triangles whose filter set from the given array containts the specified target vertex.
- L75 _public prototype_ `TArray<int32> FindCandidateTriangles(const FVector& InPoint, float InTolerance = KINDA_SMALL_NUMBER) const;` — Find the closest triangles from the specified point.
- L81 _public prototype_ `TConstArrayView<float> GetMaxEdgeLengths() const;` — Return the max edge length for each edge coming out of a mesh vertex. Useful for guiding the search radius when searching for nearest triangles.
- L84 _private prototype_ `void ComputeAveragedNormals();`
- L88 _private member_ `TConstArrayView<FVector3f> Positions;`
- L89 _private member_ `TConstArrayView<FVector3f> Normals;`
- L90 _private member_ `TConstArrayView<FVector3f> Tangents;`
- L91 _private member_ `TConstArrayView<uint32> Indices;`
- L93 _private member_ `TArray<FVector3f> AveragedNormals;`
- L95 _private member_ `mutable bool bHasValidBVH;`
- L96 _private member_ `mutable Chaos::TAABBTree<int32, Chaos::TAABBTreeLeafArray<int32, false>, false> BVH;`
- L98 _private member_ `mutable TArray<float> MaxEdgeLengths;`
- L99 _private member_ `mutable TArray<int32> FilteredTriangles;`

#### class `ClothingMeshUtils::FVertexParameterMapper`  
`class FVertexParameterMapper`  
_L189-293_
- desc: Object used to map vertex parameters between two meshes using the same barycentric mesh to mesh mapping data we use for clothing
- L194 _public function_ `FVertexParameterMapper(TConstArrayView<FVector3f> InMesh0Positions, TConstArrayView<FVector3f> InMesh0Normals, TConstArrayView<FVector3f> InMesh1Positions, TConstArrayView<FVector3f> InMesh1Normals, TConstArrayView<uint32> InMesh1Indices) : Mesh0Positions(InMesh0Positions) , Mesh0Normals(InMesh0Normals) , Mesh1Positions(InMesh1Positions) , Mesh1Normals(InMesh1Normals) , Mesh1Indices(InMesh1Indices)`
- L209 _public function_ `template<typename T, typename Lambda> void Map(TConstArrayView<T>& SourceData, TArray<T>& DestData, const Lambda& Func)` — Generic mapping function, can be used to map any type with a provided callable
- L277 _public prototype_ `void Map(TConstArrayView<float> Source, TArray<float>& Dest);` — Remap float scalar values. This transfers the values from source to dest by matching the mesh topologies using barycentric coordinates of the dest mesh (Mesh0) positions over the source mesh (Mesh1).
- L286 _private prototype_ `void GenerateEmbeddedPositions(TArray<FVector4>& OutEmbeddedPositions, TArray<int32>& OutSourceIndices);` — Embeds a list of positions into a source mesh @param OutEmbeddedPositions Embedded version of the original positions, a barycentric coordinate and distance along the normal of the triangle @param OutSourceIndices Source index list for the embedded positions, 3 per position to denote the source triangle
- L288 _private member_ `TConstArrayView<FVector3f> Mesh0Positions;`
- L289 _private member_ `TConstArrayView<FVector3f> Mesh0Normals;`
- L290 _private member_ `TConstArrayView<FVector3f> Mesh1Positions;`
- L291 _private member_ `TConstArrayView<FVector3f> Mesh1Normals;`
- L292 _private member_ `TConstArrayView<uint32> Mesh1Indices;`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogClothingMeshUtils, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogClothingMeshUtils, Log, All);`
- L13 _namespace_ `namespace ClothingMeshUtils`
- L105 _prototype_ `void SkinPhysicsMesh( const TArray<int32>& BoneMap,` (scope `ClothingMeshUtils`) — Static method for calculating a skinned mesh result from source data
- L126 _prototype_ `void GenerateMeshToMeshVertData( TArray<FMeshToMeshVertData>& OutMeshToMeshVertData, const ClothMeshDesc& TargetMesh, const ClothMeshDesc& SourceMesh, const FPointWeightMap* MaxDistances, bool bUseSmoothTransitions, bool bUseMultipleInfluences, float KernelMaxDistance, const TArray<FMeshToMeshFilterSet>& FilterSets = TArray<FMeshToMeshFilterSet>());` (scope `ClothingMeshUtils`) — Given mesh information for two meshes, generate a list of skinning data to embed TargetMesh in SourceMesh @param OutMeshToMeshVertData      - Final skinning data @param TargetMesh                 - Mesh data for the mesh we are embedding @param SourceMesh                 - Mesh data for the mesh we are embedding into @param MaxDistances               - Fixed positions mask used to update the vertex contributions, or null if the update is not required @param bUseSmoothTransitions      - Set blend weight to smoothen transitions between the fixed and deformed vertices when updating the vertex contributions @param bUseMultipleInfluences     - Whether to take a weighted average of influences from multiple source triangles @param KernelMaxDistance          - Max distance parameter for weighting kernel for when using multiple influences @param FilterSets                 - A set of source triangle indices to filter the search from, will use all source triangles if empty
- L140 _prototype_ `void ComputeVertexContributions( TArray<FMeshToMeshVertData> &InOutSkinningData, const FPointWeightMap* const InMaxDistances, const bool bInSmoothTransition, const bool bInUseMultipleInfluences = false);` (scope `ClothingMeshUtils`) — Computes how much each vertex contributes to the final mesh. The final mesh is a blend between the cloth and the skinned mesh.
- L158 _prototype_ `FVector4f GetPointBaryAndDist( const FVector3f& A, const FVector3f& B, const FVector3f& C, const FVector3f& Point);` (scope `ClothingMeshUtils`) — Given a triangle ABC with normals at each vertex NA, NB and NC, get a barycentric coordinate and corresponding distance from the triangle encoded in an FVector4 where the components are (BaryX, BaryY, BaryZ, Dist) @param A		- Position of triangle vertex A @param B		- Position of triangle vertex B @param C		- Position of triangle vertex C @param NA	- Normal at vertex A @param NB	- Normal at vertex B @param NC	- Normal at vertex C @param Point	- Point to calculate Bary+Dist for
- L176 _prototype_ `FVector4f GetPointBaryAndDistWithNormals( const FVector3f& A, const FVector3f& B, const FVector3f& C, const FVector3f& NA, const FVector3f& NB, const FVector3f& NC, const FVector3f& Point);` (scope `ClothingMeshUtils`) — Given a triangle ABC with normals at each vertex NA, NB and NC, get a barycentric coordinate and corresponding distance from the triangle encoded in an FVector4 where the components are (BaryX, BaryY, BaryZ, Dist) @param A		- Position of triangle vertex A @param B		- Position of triangle vertex B @param C		- Position of triangle vertex C @param NA	- Normal at vertex A @param NB	- Normal at vertex B @param NC	- Normal at vertex C @param Point	- Point to calculate Bary+Dist for
