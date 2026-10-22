# Runtime / ClothingSystemRuntimeInterface

- module root: `Source/Runtime/ClothingSystemRuntimeInterface`
- headers: 13; symbols: 288
- symbol kinds: class=12, enum=2, enumerator=5, function=95, macro=6, member=66, namespace=3, prototype=86, struct=13
- PrivateDependencyModuleNames: Slate
- PublicDependencyModuleNames: Core, CoreUObject

### `Source/Runtime/ClothingSystemRuntimeInterface/Public/ClothCollisionData.h` (Public)


#### struct `FClothCollisionData`  
`struct FClothCollisionData`  
_L13-53_
- reflection: `USTRUCT()`
- L17 _public prototype_ `void Reset();`
- L19 _public prototype_ `void Append(const FClothCollisionData& InOther);`
- L21 _public prototype_ `void AppendTransformed(const FClothCollisionData& InOther, const TArray<FTransform>& BoneTransforms);`
- L27 _public prototype_ `void AppendUnique(const FClothCollisionData& InOther);` — Append collision data, but only the individual collision elements that don't already exist as to avoid duplicates. @Note This is an expensive operation and therefore it is best to call Append() on the first batch of collision data to merge right after a Reset().
- L29 _public function_ `bool IsEmpty() const`
- L36 _public member_ `TArray<FClothCollisionPrim_Sphere> Spheres;` — `UPROPERTY(EditAnywhere, Category = Collision)` — Sphere data
- L40 _public member_ `TArray<FClothCollisionPrim_SphereConnection> SphereConnections;` — `UPROPERTY(EditAnywhere, Category = Collision)` — Capsule data
- L44 _public member_ `TArray<FClothCollisionPrim_Convex> Convexes;` — `UPROPERTY(EditAnywhere, Category = Collision)` — Convex Data
- L48 _public member_ `TArray<FClothCollisionPrim_Box> Boxes;` — `UPROPERTY(EditAnywhere, Category = Collision)` — Box data
- L52 _public member_ `TArray<FClothCollisionPrim_ExtrudedTaperedCapsule> ExtrudedTaperedCapsules;` — `UPROPERTY(EditAnywhere, Category = Collision)` — Extruded tapered capsule data

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CLOTHINGSYSTEMRUNTIMEINTERFACE_API`

### `Source/Runtime/ClothingSystemRuntimeInterface/Public/ClothCollisionPrim.h` (Public)


#### struct `FClothCollisionPrim_Sphere`  
`struct FClothCollisionPrim_Sphere`  
_L13-39_
- reflection: `USTRUCT()`
- desc: Data for a single sphere primitive in the clothing simulation. This can either be a sphere on its own, or part of a capsule referenced by the indices in FClothCollisionPrim_Capsule
- L17 _public function_ `FClothCollisionPrim_Sphere(float InRadius = 0.0f, const FVector& InLocalPosition = FVector::ZeroVector, int32 InBoneIndex = INDEX_NONE) : BoneIndex(InBoneIndex) , Radius(InRadius) , LocalPosition(InLocalPosition)`
- L23 _public function_ `bool operator==(const FClothCollisionPrim_Sphere& Other) const`
- L32 _public member_ `int32 BoneIndex;` — `UPROPERTY()`
- L35 _public member_ `float Radius;` — `UPROPERTY()`
- L38 _public member_ `FVector LocalPosition;` — `UPROPERTY()`

#### struct `FClothCollisionPrim_SphereConnection`  
`struct FClothCollisionPrim_SphereConnection`  
_L45-70_
- reflection: `USTRUCT()`
- desc: Data for a single connected sphere primitive. This should be configured after all spheres have been processed as they are really just indexing the existing spheres
- L49 _public function_ `FClothCollisionPrim_SphereConnection(int32 SphereIndex0 = INDEX_NONE, int32 SphereIndex1 = INDEX_NONE, const FVector& InOneSidedPlaneNormal = FVector::ZeroVector)`
- L56 _public function_ `bool operator==(const FClothCollisionPrim_SphereConnection& Other) const`
- L65 _public member_ `int32 SphereIndices[2];` — `UPROPERTY()`
- L69 _public member_ `FVector OneSidedPlaneNormal = FVector::ZeroVector;` — `UPROPERTY()` — Zero vector means this is not a one-sided capsule.

#### struct `FClothCollisionPrim_ConvexFace`  
`struct FClothCollisionPrim_ConvexFace`  
_L74-90_
- reflection: `USTRUCT()`
- desc: Data for a convex face.
- L78 _public function_ `FClothCollisionPrim_ConvexFace(): Plane(ForceInit)`
- L80 _public function_ `bool operator==(const FClothCollisionPrim_ConvexFace& Other) const`
- L86 _public member_ `FPlane Plane;` — `UPROPERTY()`
- L89 _public member_ `TArray<int32> Indices;` — `UPROPERTY()`

#### struct `FClothCollisionPrim_Convex`  
`struct FClothCollisionPrim_Convex`  
_L98-158_
- reflection: `USTRUCT()`
- desc: Data for a single convex element A convex is a collection of planes, in which the clothing will attempt to stay outside of the shape created by the planes combined.
- L102 _public function_ `FClothCollisionPrim_Convex() : BoneIndex(INDEX_NONE)`
- L106 _public function_ `FClothCollisionPrim_Convex( TArray<FClothCollisionPrim_ConvexFace>&& InFaces, TArray<FVector>&& InSurfacePoints, int32 InBoneIndex = INDEX_NONE, const FVector& InLocalPosition = FVector::ZeroVector, const FQuat& InLocalRotation = FQuat::Identity) : Faces(InFaces) , SurfacePoints(InSurfacePoints) , LocalPosition(InLocalPosition) , LocalRotation(InLocalRotation) , BoneIndex(InBoneIndex)`
- L119 _public function_ `bool operator==(const FClothCollisionPrim_Convex& Other) const`
- L141 _public member_ `TArray<FPlane> Planes_DEPRECATED;` — `UPROPERTY()`
- L145 _public member_ `TArray<FClothCollisionPrim_ConvexFace> Faces;` — `UPROPERTY()`
- L148 _public member_ `TArray<FVector> SurfacePoints;` — `UPROPERTY()` — Surface points, used by Chaos and also for visualization
- L151 _public member_ `FVector LocalPosition = FVector::ZeroVector;` — `UPROPERTY()`
- L154 _public member_ `FQuat LocalRotation = FQuat::Identity;` — `UPROPERTY()`
- L157 _public member_ `int32 BoneIndex;` — `UPROPERTY()`

#### struct `FClothCollisionPrim_Box`  
`struct FClothCollisionPrim_Box`  
_L162-197_
- reflection: `USTRUCT()`
- desc: Data for a single box primitive.
- L166 _public function_ `FClothCollisionPrim_Box( const FVector& InLocalPosition = FVector::ZeroVector, const FQuat& InLocalRotation = FQuat::Identity, const FVector& InHalfExtents = FVector::ZeroVector, int32 InBoneIndex = INDEX_NONE) : LocalPosition(InLocalPosition) , LocalRotation(InLocalRotation) , HalfExtents(InHalfExtents) , BoneIndex(InBoneIndex)`
- L177 _public function_ `bool operator==(const FClothCollisionPrim_Box& Other) const`
- L187 _public member_ `FVector LocalPosition;` — `UPROPERTY()`
- L190 _public member_ `FQuat LocalRotation;` — `UPROPERTY()`
- L193 _public member_ `FVector HalfExtents;` — `UPROPERTY()`
- L196 _public member_ `int32 BoneIndex;` — `UPROPERTY()`

#### struct `FClothCollisionPrim_ExtrudedTaperedCapsule`  
`struct FClothCollisionPrim_ExtrudedTaperedCapsule`  
_L201-255_
- reflection: `USTRUCT()`
- desc: Data for an extruded tapered capsule primitive.
- L205 _public function_ `explicit FClothCollisionPrim_ExtrudedTaperedCapsule( const FVector& InLocalPosition = FVector::ZeroVector, const FQuat& InLocalRotation = FQuat::Identity, float InLength = 0.f, float InWidth = 0.f, float InRadius1 = 0.f, float InRadius2 = 0.f, int32 InBoneIndex = INDEX_NONE) : LocalPosition(InLocalPosition) , LocalRotation(InLocalRotation) , Length(InLength) , Width(InWidth) , Radius1(InRadius1) , Radius2(InRadius2) , BoneIndex(InBoneIndex)`
- L223 _public function_ `bool operator==(const FClothCollisionPrim_ExtrudedTaperedCapsule& Other) const`
- L236 _public member_ `FVector LocalPosition;` — `UPROPERTY()`
- L239 _public member_ `FQuat LocalRotation;` — `UPROPERTY()`
- L242 _public member_ `float Length;` — `UPROPERTY()`
- L245 _public member_ `float Width;` — `UPROPERTY()`
- L248 _public member_ `float Radius1;` — `UPROPERTY()`
- L251 _public member_ `float Radius2;` — `UPROPERTY()`
- L254 _public member_ `int32 BoneIndex;` — `UPROPERTY()`

### `Source/Runtime/ClothingSystemRuntimeInterface/Public/ClothConfigBase.h` (Public)


#### class `UClothConfigBase`  
`class UClothConfigBase : public UObject`  
_L18-48_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UObject`
- desc: Base class for simulator specific simulation controls. Each cloth instance on a skeletal mesh can have a unique cloth config
- L22 _public prototype_ `UClothConfigBase();`
- L23 _public prototype_ `virtual ~UClothConfigBase();`
- L26 _public prototype_ `virtual bool NeedsSelfCollisionData() const PURE_VIRTUAL(UClothConfigBase::NeedsSelfCollisionData, return false;);` — Return wherether to pre-compute self collision data.
- L30 _public prototype_ `virtual bool NeedsInverseMasses() const PURE_VIRTUAL(UClothConfigBase::NeedsInverseMasses, return false;);` — Return wherether to pre-compute inverse masses.
- L34 _public prototype_ `virtual bool NeedsNumInfluences() const PURE_VIRTUAL(UClothConfigBase::NeedsNumInfluences, return false;);` — Return wherether to pre-compute the influences.
- L38 _public prototype_ `virtual bool NeedsTethers() const PURE_VIRTUAL(UClothConfigBase::NeedsTethers, return false;);` — Return wherether to pre-compute the long range attachment tethers.
- L42 _public prototype_ `virtual float GetSelfCollisionRadius() const PURE_VIRTUAL(UClothConfigBase::GetSelfCollisionRadius, return 0.f;);` — Return the self collision radius to precomute self collision data.
- L46 _public prototype_ `virtual bool TethersUseGeodesicDistance() const PURE_VIRTUAL(UClothConfigBase::TethersUseGeodesicDistance, return false;);` — Return whether tethers need to be calculated using geodesic distances instead of eclidean.

#### class `UDEPRECATED_ClothSharedSimConfigBase`  
`class UDEPRECATED_ClothSharedSimConfigBase : public UObject`  
_L55-66_
- reflection: `UCLASS(Abstract, Deprecated, MinimalAPI)`
- inherits: `UObject`
- desc: These settings are shared between all instances on a skeletal mesh Deprecated, use UClothConfigBase instead.
- L59 _public function_ `UDEPRECATED_ClothSharedSimConfigBase()`
- L60 _public prototype_ `virtual ~UDEPRECATED_ClothSharedSimConfigBase() = default;`
- L65 _public function_ `virtual UClothConfigBase* Migrate()` — Return a new updated cloth shared config migrated from this current object.

### `Source/Runtime/ClothingSystemRuntimeInterface/Public/ClothPhysicalMeshDataBase_Legacy.h` (Public)


#### class `UClothPhysicalMeshDataBase_Legacy`  
`class UClothPhysicalMeshDataBase_Legacy : public UObject`  
_L26-87_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: Deprecated, use FClothPhysicalMeshData instead. Simulation mesh points, topology, and spatial parameters defined on that topology. Created curing asset import or created from a skeletal mesh.
- L30 _public prototype_ `UClothPhysicalMeshDataBase_Legacy();`
- L31 _public prototype_ `virtual ~UClothPhysicalMeshDataBase_Legacy();`
- L34 _public prototype_ `TArray<float>* GetFloatArray(const uint32 Id) const;` — Retrieve a registered vertex weight array by unique @param Id.
- L37 _public prototype_ `TArray<uint32> GetFloatArrayIds() const;` — Get ids for all registered weight arrays.
- L40 _public prototype_ `TArray<TArray<float>*> GetFloatArrays() const;` — Get all registered weight arrays.
- L44 _protected prototype_ `void RegisterFloatArray(const uint32 Id, TArray<float> *Array);` — Register an @param Array keyed by a unique @param Id.
- L49 _public member_ `TArray<FVector3f> Vertices;` — `UPROPERTY()` — Positions of each simulation vertex
- L53 _public member_ `TArray<FVector3f> Normals;` — `UPROPERTY()` — Normal at each vertex
- L58 _public member_ `TArray<FColor> VertexColors;` — `UPROPERTY()` — Color at each vertex
- L63 _public member_ `TArray<uint32> Indices;` — `UPROPERTY()` — Indices of the simulation mesh triangles
- L67 _public member_ `TArray<float> InverseMasses;` — `UPROPERTY()` — Inverse mass for each vertex in the physical mesh
- L71 _public member_ `TArray<FClothVertBoneData> BoneData;` — `UPROPERTY()` — Indices and weights for each vertex, used to skin the mesh to create the reference pose
- L75 _public member_ `int32 NumFixedVerts;` — `UPROPERTY()` — Number of fixed verts in the simulation mesh (fixed verts are just skinned and do not simulate)
- L79 _public member_ `int32 MaxBoneWeights;` — `UPROPERTY()` — Maximum number of bone weights of any vetex
- L83 _public member_ `TArray<uint32> SelfCollisionIndices;` — `UPROPERTY()` — Valid indices to use for self collisions (reduced set of Indices)
- L86 _private member_ `TMap<uint32, TArray<float>*> IdToArray;`

### `Source/Runtime/ClothingSystemRuntimeInterface/Public/ClothVertBoneData.h` (Public)


#### struct `FClothVertBoneData`  
`struct FClothVertBoneData`  
_L9-37_
- reflection: `USTRUCT()`
- desc: Bone data for a vertex
- L13 _public function_ `FClothVertBoneData() : NumInfluences(0)`
- L24 _public member_ `static const int8 MaxTotalInfluences = 12;` — MAX_TOTAL_INFLUENCES = 12 is defined in GPUSkinPublicDefs.h, but that would require a dependency on Engine, which we can't have here.  Until that can be migrated elsewhere (not to mention if), we make a redundant variable with an 8 in it, that needs to stay in sync with MAX_TOTAL_INFLUENCES.
- L28 _public member_ `int32 NumInfluences;` — `UPROPERTY()` — Number of influences for this vertex.
- L32 _public member_ `uint16 BoneIndices[MaxTotalInfluences];` — `UPROPERTY()` — Up to MAX_TOTAL_INFLUENCES bone indices that this vert is weighted to
- L36 _public member_ `float BoneWeights[MaxTotalInfluences];` — `UPROPERTY()` — The weights for each entry in BoneIndices

### `Source/Runtime/ClothingSystemRuntimeInterface/Public/ClothingAssetBase.h` (Public)


#### class `UClothingAssetBase`  
`class UClothingAssetBase : public UObject`  
_L27-180_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UObject`
- desc: An interface object for any clothing asset the engine can use. Any clothing asset concrete object should derive from this.
- L41 _public prototype_ `virtual bool BindToSkeletalMesh(USkeletalMesh* InSkelMesh, const int32 InMeshLodIndex, const int32 InSectionIndex, const int32 InAssetLodIndex) PURE_VIRTUAL(UClothingAssetBase::BindToSkeletalMesh, return false;);` — Binds a clothing asset submesh to a skeletal mesh section. @param InSkelMesh Skel mesh to bind to. @param InMeshLodIndex Mesh LOD to bind this asset to. @param InSectionIndex Section in the skel mesh to replace. @param InAssetLodIndex Internal clothing LOD to use.
- L52 _public prototype_ `virtual void UnbindFromSkeletalMesh(USkeletalMesh* InSkelMesh, const int32 InMeshLodIndex, const int32 InSectionIndex) PRAGMA_DISABLE_DEPRECATION_WARNINGS PURE_VIRTUAL(UClothingAssetBase::UnbindFromSkeletalMesh, UnbindFromSkeletalMesh(InSkelMesh, InMeshLodIndex); return;);` — Unbind Clothing Data from the specified Skeletal Mesh LOD sections. If MeshLodIndex is INDEX_NONE, the Clothing Data will get unbound from all LODs and all sections (ignoring SectionIndex in this case). If SectionIndex is INDEX_NONE, the Clothing Data will get unbound from all sections of the specified LOD. @param InSkelMesh The Skeletal Mesh to unbind the Clothing Data from. @param InMeshLodIndex Mesh LOD to remove this asset from (could still be bound to other LODs), or INDEX_NONE to unbind all LODs. @param InSectionIndex The Skeletal Mesh section to unbind, or INDEX_NONE to unbind all sections.
- L58 _public function_ `virtual void UnbindFromSkeletalMesh(USkeletalMesh* InSkelMesh)` — `UE_DEPRECATED(5.8, "Implement and use UnbindFromSkeletalMesh(USkeletalMesh* InSkelMesh, const int32 InMeshLodIndex, const int32 InSectionIndex) instead.")`
- L61 _public function_ `virtual void UnbindFromSkeletalMesh(USkeletalMesh* InSkelMesh, const int32 InMeshLodIndex)` — `UE_DEPRECATED(5.8, "Implement and use UnbindFromSkeletalMesh(USkeletalMesh* InSkelMesh, const int32 InMeshLodIndex, const int32 InSectionIndex) instead.")`
- L67 _public prototype_ `virtual void UpdateAllLODBiasMappings(USkeletalMesh* SkeletalMesh) PURE_VIRTUAL(UClothingAssetBase::UpdateAllLODBiasMappings, return;);` — Update all extra LOD deformer mappings. This should be called whenever the raytracing LOD bias is changed.
- L78 _public prototype_ `virtual void GetSimulationMesh(const int32 InMeshLodIndex, TArray<FVector3f>& OutPositions, TArray<uint32>& OutIndices, TArray<float>& OutMaxDistances) const PURE_VIRTUAL(UClothingAssetBase::GetSimulationMesh, return;);` — Return the simulation mesh. Used to calculate the LOD bias deformer mappings. @param InMeshLodIndex The bound skeletal mesh LOD (in case this clothing data hold multiple LODs). @param OutPositions The simulation mesh positions. @param OutIndices The simulation mesh triangle indices. @param OutMaxDistances The simulation mesh max distance attributes (0 for kinematic, >0 for dynamic). must match the number of positions.
- L83 _public function_ `virtual int32 AddNewLod()` — `UE_DEPRECATED(5.7, "Use UClothingAssetCommon::AddNewLod() instead.")` — Add a new LOD class instance.
- L94 _public function_ `virtual void BuildLodTransitionData()` — `UE_DEPRECATED(5.7, "Use UClothingAssetCommon::BuildLodTransitionData() instead.")` — Builds the LOD transition data When we transition between LODs we skin the incoming mesh to the outgoing mesh in exactly the same way the render mesh is skinned to create a smooth swap
- L101 _public function_ `virtual TArray<TPair<FText, FText>> GetStats() const` — Gather stats for the Skeletal Mesh editor details view. @return An array of pairs stat name, stat value that will be displayed in a row. @note Stats without values are displayed as the line header and act as a newline for the following entries.
- L111 _public function_ `virtual USkinnedAsset* GetSkinnedAssetDependency() const` — Get a Skinned Asset dependency that participates in async compilation, if any. Used by the Skeletal Mesh to declare any compilation dependencies from the clothing assets. @return The underlying Skinned Asset or nullptr if this clothing asset has no such dependency.
- L115 _public prototype_ `virtual void PostInitProperties() override;` — Make sure the object is transactional.
- L125 _public function_ `virtual void InvalidateAllCachedData()` — `UE_DEPRECATED(5.7, "Use UClothingAssetCommon::InvalidateAllCachedData() instead.")` — Called on the clothing asset when the base data (physical mesh, config etc.) has changed, so any intermediate generated data can be regenerated.
- L134 _public prototype_ `virtual void RefreshBoneMapping(USkeletalMesh* InSkelMesh) PURE_VIRTUAL(UClothingAssetBase::RefreshBoneMapping, return;);` — Messages to the clothing asset that the bones in the parent mesh have possibly changed, which could invalidate the bone indices stored in the LOD data. @param InSkelMesh - The mesh to use to remap the bones
- L138 _public function_ `virtual bool IsValid() const` — Check the validity of this clothing data, for example for when it is dependent from an asset that isn't ready or accessible.
- L145 _public function_ `virtual bool IsValidLod(int32 InLodIndex) const` — `UE_DEPRECATED(5.7, "Use UClothingAssetCommon::IsValidLod() instead.")` — Check the validity of a LOD index
- L152 _public function_ `virtual int32 GetNumLods() const` — `UE_DEPRECATED(5.7, "Use UClothingAssetCommon::GetNumLods() instead.")` — Get the number of LODs defined in the clothing asset
- L158 _public prototype_ `virtual void PostUpdateAllAssets() PURE_VIRTUAL(UClothingAssetBase::PostUpdateAllAssets(), return;);` — Called after all cloth assets sharing the same simulation are added or loaded
- L162 _public function_ `const FGuid& GetAssetGuid() const` — Get the guid identifying this asset
- L174 _protected prototype_ `static void WarningNotification(const FText& Text);` — Warn using slate's notification manager. Use this method to notify binding issues back to the user.
- L179 _protected member_ `FGuid AssetGuid;` — `UPROPERTY()` — Guid to identify this asset. Will be embedded into chunks that are created using this asset

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API CLOTHINGSYSTEMRUNTIMEINTERFACE_API`
- L20 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogClothingAsset, Log, All);`

### `Source/Runtime/ClothingSystemRuntimeInterface/Public/ClothingSimulationFactory.h` (Public)


#### class `IClothingSimulationFactoryClassProvider`  
`class IClothingSimulationFactoryClassProvider : public IModularFeature`  
_L28-39_
- inherits: `IModularFeature`
- desc: An interface for a class that will provide default simulation factory classes Used by modules wanting to override clothing simulation to provide their own implementation
- L33 _public member_ `static const FName FeatureName;` — The feature name to register against for providers
- L38 _public prototype_ `virtual TSubclassOf<class UClothingSimulationFactory> GetClothingSimulationFactoryClass() const = 0;` — Called by the engine to get the clothing simulation factory associated with this provider for skeletal mesh components (see USkeletalMeshComponent constructor). Returns Factory class for simulations or nullptr to disable clothing simulation

#### class `UClothingSimulationFactory`  
`class UClothingSimulationFactory : public UObject`  
_L43-128_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UObject`
- desc: Any clothing simulation factory should derive from this interface object to interact with the engine
- L49 _public prototype_ `static TSubclassOf<class UClothingSimulationFactory> GetDefaultClothingSimulationFactoryClass();` — `UE_DEPRECATED(5.7, "Use GetClothingSimulationFactory() instead.")`
- L54 _public prototype_ `static UClothingSimulationFactory* GetClothingSimulationFactory(const UClothingAssetBase* InAsset);` — Return the clothing simulation factory for the specified asset. Calls SupportsAsset() internally. If multiple simulation support the specified asset type then this returns the first one registered through IClothingSimulationFactoryClassProvider.
- L57 _public function_ `virtual IClothingSimulationInterface* CreateSimulation() const` — Create a simulation object for a skeletal mesh to use (see IClothingSimulationInterface)
- L66 _public function_ `virtual IClothingSimulation* CreateSimulation()` — `UE_DEPRECATED(5.7, "Use IClothingSimulationInterface instead.")`
- L73 _public function_ `virtual void DestroySimulation(IClothingSimulationInterface* InSimulation) const` — Destroy a simulation object, guaranteed to be a pointer returned from CreateSimulation for this factory
- L85 _public function_ `virtual void DestroySimulation(IClothingSimulation* InSimulation)` — `UE_DEPRECATED(5.7, "Use IClothingSimulationInterface instead.")`
- L90 _public function_ `virtual bool SupportsAsset(const UClothingAssetBase* InAsset) const` — Given an asset, decide whether this factory can create a simulation to use the data inside (return false if data is invalid or missing in the case of custom data)
- L96 _public function_ `virtual bool SupportsAsset(UClothingAssetBase* InAsset)` — `UE_DEPRECATED(5.7, "Use const version instead.")`
- L103 _public function_ `virtual bool SupportsRuntimeInteraction() const` — Whether or not we provide an interactor object to manipulate the simulation at runtime. If true is returned then CreateInteractor *must* create a valid object to handle this
- L111 _public function_ `virtual bool SupportsRuntimeInteraction()` — `UE_DEPRECATED(5.7, "Use const version instead.")`
- L118 _public prototype_ `virtual UClothingSimulationInteractor* CreateInteractor() PURE_VIRTUAL(UClothingSimulationFactory::CreateInteractor, return nullptr;);` — Creates the runtime interactor object for a clothing simulation. This object will receive events allowing it to write data to the simulation context in a safe manner
- L122 _public prototype_ `virtual TArrayView<const TSubclassOf<UClothConfigBase>> GetClothConfigClasses() const PURE_VIRTUAL(UClothingSimulationFactory::GetClothConfigClasses, return TArrayView<const TSubclassOf<UClothConfigBase>>(););` — Return the cloth config type for this cloth factory
- L126 _public prototype_ `virtual const UEnum* GetWeightMapTargetEnum() const PURE_VIRTUAL(UClothingSimulationFactory::GetWeightMapTargetEnum, return nullptr;);` — Return an enum of the weight map targets that can be used with this simulation.

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API CLOTHINGSYSTEMRUNTIMEINTERFACE_API`

### `Source/Runtime/ClothingSystemRuntimeInterface/Public/ClothingSimulationInstance.h` (Public)


#### struct `FClothingSimulationInstance`  
`struct FClothingSimulationInstance`  
_L24-197_
- reflection: `USTRUCT()`
- desc: Clothing simulation objects. Facade to the simulation interfaces to allow for a simplified implementation and multiple simulations to coexist with each other.
- L63 _public prototype_ `FClothingSimulationInstance(USkeletalMeshComponent* SkeletalMeshComponent, const FFactoryAssetGroup& FactoryAssetGroup);` — Construct a new clothing simulation instance for the specified asset group and component.
- L65 _public prototype_ `FClothingSimulationInstance();`
- L66 _public prototype_ `~FClothingSimulationInstance();`
- L68 _public prototype_ `FClothingSimulationInstance(const FClothingSimulationInstance&) = delete;`
- L69 _public prototype_ `FClothingSimulationInstance(FClothingSimulationInstance&&) = default;`
- L70 _public prototype_ `FClothingSimulationInstance& operator=(const FClothingSimulationInstance&) = delete;`
- L71 _public prototype_ `FClothingSimulationInstance& operator=(FClothingSimulationInstance&&) = default;`
- L74 _public function_ `UClothingSimulationFactory* GetClothingSimulationFactory() const` — Return the clothing simulation factory used to initialize this clothing simulation instance.
- L80 _public function_ `const IClothingSimulationInterface* GetClothingSimulation() const` — Return the clothing simulation pointer.
- L86 _public function_ `IClothingSimulationInterface* GetClothingSimulation()` — Return the clothing simulation pointer.
- L92 _public function_ `const IClothingSimulationContext* GetClothingSimulationContext() const` — Return the clothing simulation context.
- L98 _public function_ `IClothingSimulationContext* GetClothingSimulationContext()` — Return the clothing simulation context.
- L104 _public function_ `UClothingSimulationInteractor* GetClothingSimulationInteractor() const` — Return a non const version of the clothing interactor (non const methods are used to update simulation parameters).
- L110 _public prototype_ `void RemoveAllClothingActors();` — Remove all actors.
- L113 _public prototype_ `void SyncClothingInteractor();` — Synchronize the simulation with the changes requested by the interactor.
- L116 _public function_ `void HardResetSimulation()` — Hard reset the cloth simulation
- L123 _public function_ `void GetCollisions(FClothCollisionData& Collisions, bool bIncludeExternal) const` — `UE_DEPRECATED(5.8, "GetCollisions has been deprecated. Use CollisionSources to add external collisions instead.")` — Return the collision data from this simulation instance.
- L127 _public function_ `void AppendUniqueCollisions(FClothCollisionData& OutCollisions, bool bIncludeExternal) const` — `UE_DEPRECATED(5.8, "AppendUniqueCollisions has been deprecated. Use CollisionSources to add external collisions instead.")` — Append unique collision data from this simulation instance to the specified collision data.
- L130 _public function_ `void AddExternalCollisions(const FClothCollisionData& Collisions)` — Add external dynamic collisions.
- L136 _public function_ `void ClearExternalCollisions()` — Remove all dynamically added external collisions.
- L142 _public prototype_ `void FillContextAndPrepareTick(const USkeletalMeshComponent* OwnerComponent, float DeltaTime, bool bIsInitialization);` — Fill the simulation context and do any other related game-thread initialization.
- L145 _public function_ `void Simulate()` — Advance the simulation. This method may be called asynchronously.
- L158 _public function_ `void AppendSimulationData(TMap<int32, FClothSimulData>& CurrentSimulationData, const USkeletalMeshComponent* OwnerComponent, const USkinnedMeshComponent* LeaderPoseComponent) const` — Append the simulation data.
- L168 _public function_ `FBoxSphereBounds GetBounds(const USkeletalMeshComponent* OwnerComponent) const` — Return this simulation bounds.
- L179 _private member_ `IClothingSimulationInterface* ClothingSimulation = nullptr;` — ClothingSimulations are responsible for maintaining and simulating clothing actors.
- L182 _private member_ `IClothingSimulationContext* ClothingSimulationContext = nullptr;` — ClothingSimulationContexts are a datastore for simulation data sent to the clothing thread.
- L190 _private member_ `TObjectPtr<UClothingSimulationInteractor> ClothingSimulationInteractor;` — `UPROPERTY(Transient)` — Objects responsible for interacting with the clothing simulation. Blueprints and code can call/set data on this from the game thread and the next time it is safe to do so the interactor will sync to the simulation context.
- L194 _private member_ `TObjectPtr<UClothingSimulationFactory> ClothingSimulationFactory;` — `UPROPERTY(Transient)` — Simulation factory.
- L196 _private member_ `int32 CurrentOwnerLODIndex = INDEX_NONE;` — This is populated by FillContextAndPrepareTick

#### struct `FClothingSimulationInstance::FFactoryAssetGroup`  
`struct FFactoryAssetGroup`  
_L36-60_
- desc: Factory asset group. Group of clothing data that run under the same simulation type, and the clothing simulation factory associated with them. The group storage array always matches the order of the SkeletalMesh clothing data so that the indices are the same, with a nullptr entry into the array to signify that the asset is part of a different group. This is to avoid an additional array of indices, knowing that most Skeletal Meshes have rarely more than half a dozen clothing data.
- L39 _public function_ `FFactoryAssetGroup(UClothingSimulationFactory* InClothingSimulationFactory, const int32 NumTotalClothAssets) : ClothingSimulationFactory(InClothingSimulationFactory)`
- L46 _public function_ `void AddClothingAsset(const UClothingAssetBase* ClothingAsset, const int32 Index)`
- L51 _public function_ `const UClothingSimulationFactory* GetClothingSimulationFactory() const`
- L58 _private member_ `UClothingSimulationFactory* ClothingSimulationFactory;`
- L59 _private member_ `TArray<const UClothingAssetBase*> ClothingAssets;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FClothingSimulationInstance> : public TStructOpsTypeTraitsBase2<FClothingSimulationInstance>`  
_L200-206_
- inherits: `TStructOpsTypeTraitsBase2<FClothingSimulationInstance>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L203-205_

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CLOTHINGSYSTEMRUNTIMEINTERFACE_API`
- L204 _enumerator_ `WithCopy = false` (scope `TStructOpsTypeTraits::__anon78d400600103`)

### `Source/Runtime/ClothingSystemRuntimeInterface/Public/ClothingSimulationInteractor.h` (Public)


#### class `UClothingInteractor`  
`class UClothingInteractor : public UObject`  
_L30-54_
- reflection: `UCLASS(Abstract, BlueprintType, MinimalAPI)`
- inherits: `UObject`
- desc: Abstract class to control clothing specific interaction. Must be cast to the end used clothing simulation object before use.
- L37 _protected function_ `virtual void Sync(IClothingSimulationInterface* Simulation)`
- L49 _protected function_ `virtual void Sync(IClothingSimulation* Simulation)` — `UE_DEPRECATED(5.7, "Use IClothingSimulationInterface instead.")`
- L53 _protected member_ `int32 ClothingId = -1;` — Clothing Asset slot as passed to the CreateActor function

#### class `UClothingSimulationInteractor`  
`class UClothingSimulationInteractor : public UObject`  
_L64-191_
- reflection: `UCLASS(Abstract, BlueprintType, MinimalAPI)`
- inherits: `UObject`
- desc: If a clothing simulation is able to be interacted with at runtime then a derived interactor should be created, and at least the basic API implemented for that simulation. Only write to the simulation and context during the call to Sync, as that is guaranteed to be a safe place to access this data.
- L70 _public prototype_ `virtual void CreateClothingInteractor(const UClothingAssetBase* ClothingAsset, int32 ClothingId);` — Create a cloth specific interactor. Override either this method or the simpler CreateClothingInteractor method.
- L73 _public prototype_ `void DestroyClothingInteractors();` — Destroy all interactors.
- L83 _public prototype_ `virtual void Sync(IClothingSimulationInterface* Simulation, const IClothingSimulationContext* Context);` — Sync the interactor with the clothing simulation to use any changes made on the next simulate. This will be called at a time that is guaranteed to never overlap with the running simulation. The simulation will have to be written in a way to pick up these changes on the next update. Any inherited class must call this function to also Sync the ClothingInteractors.
- L87 _public prototype_ `virtual void Sync(IClothingSimulation* Simulation, IClothingSimulationContext* Context);` — `UE_DEPRECATED(5.7, "Use IClothingSimulationInterface instead.")`
- L92 _public prototype_ `virtual void PhysicsAssetUpdated() PURE_VIRTUAL(UClothingSimulationInteractor::PhysicsAssetUpdated, );` — `UFUNCTION(BlueprintCallable, Category=ClothingSimulation)` — Called to update collision status without restarting the simulation.
- L97 _public prototype_ `virtual void ClothConfigUpdated() PURE_VIRTUAL(UClothingSimulationInteractor::ClothConfigUpdated, );` — `UFUNCTION(BlueprintCallable, Category=ClothingSimulation)` — Called to update the cloth config without restarting the simulation.
- L102 _public prototype_ `virtual void SetAnimDriveSpringStiffness(float InStiffness) PURE_VIRTUAL(UClothingSimulationInteractor::SetAnimDriveSpringStiffness, );` — `UFUNCTION(BlueprintCallable, Category = ClothingSimulation)` — Set the stiffness of the spring force for the animation drive.
- L107 _public prototype_ `virtual void EnableGravityOverride(const FVector& InVector) PURE_VIRTUAL(UClothingSimulationInteractor::EnableGravityOverride, );` — `UFUNCTION(BlueprintCallable, Category = ClothingSimulation)` — Set a new gravity override and enable the override.
- L112 _public prototype_ `virtual void DisableGravityOverride() PURE_VIRTUAL(UClothingSimulationInteractor::DisableGravityOverride, );` — `UFUNCTION(BlueprintCallable, Category = ClothingSimulation)` — Disable any currently set gravity override.
- L117 _public prototype_ `virtual void SetNumIterations(int32 NumIterations = 1) PURE_VIRTUAL(UClothingSimulationInteractor::SetNumIterations, );` — `UFUNCTION(BlueprintCallable, Category = ClothingSimulation)` — Set the number of time dependent solver iterations.
- L122 _public prototype_ `virtual void SetMaxNumIterations(int32 MaxNumIterations = 10) PURE_VIRTUAL(UClothingSimulationInteractor::SetMaxNumIterations, );` — `UFUNCTION(BlueprintCallable, Category = ClothingSimulation)` — Set the maximum number of solver iterations.
- L127 _public prototype_ `virtual void SetNumSubsteps(int32 NumSubsteps = 1) PURE_VIRTUAL(UClothingSimulationInteractor::SetNumSubsteps, );` — `UFUNCTION(BlueprintCallable, Category = ClothingSimulation, Meta = (Keywords = "Subdivisions"))` — Set the number of substeps or subdivisions.
- L134 _public function_ `int32 GetNumCloths() const` — `UFUNCTION(BlueprintCallable, Category = ClothingSimulation)` — Return the number of cloths run by the simulation.
- L138 _public function_ `int32 GetNumKinematicParticles() const` — `UFUNCTION(BlueprintCallable, Category = ClothingSimulation)` — Return the number of kinematic (animated) particles.
- L142 _public function_ `int32 GetNumDynamicParticles() const` — `UFUNCTION(BlueprintCallable, Category = ClothingSimulation)` — Return the number of dynamic (simulated) particles.
- L149 _public function_ `int32 GetNumIterations() const` — `UFUNCTION(BlueprintCallable, Category = ClothingSimulation)` — Return the solver number of iterations. This could be different from the number set if the simulation hasn't updated yet.
- L156 _public function_ `int32 GetNumSubsteps() const` — `UFUNCTION(BlueprintCallable, Category = ClothingSimulation)` — Return the solver number of subdivisions./ This could be different from the number set if the simulation hasn't updated yet.
- L160 _public function_ `float GetSimulationTime() const` — `UFUNCTION(BlueprintCallable, Category = ClothingSimulation)` — Return the instant average simulation time in ms.
- L164 _public prototype_ `UClothingInteractor* GetClothingInteractor(const FName ClothingAssetName) const;` — `UFUNCTION(BlueprintCallable, Category = ClothingSimulation)` — Return a cloth interactor for this simulation.
- L167 _public function_ `UClothingInteractor* GetClothingInteractor(const FString& ClothingAssetName) const` — `UE_DEPRECATED(5.7, "Use FName version instead.")`
- L174 _public member_ `TMap<FName, TObjectPtr<UClothingInteractor>> ClothingInteractors;` — `UPROPERTY()` — Cloth interactors currently created.
- L178 _protected function_ `virtual UClothingInteractor* CreateClothingInteractor()` — Create a clothing interactor. This method is called by the public CreateClothingInteractor() default implementation.
- L185 _private member_ `int32 LastNumCloths = 0;` — Simulation infos updated during the sync
- L186 _private member_ `int32 LastNumKinematicParticles = 0;`
- L187 _private member_ `int32 LastNumDynamicParticles = 0;`
- L188 _private member_ `int32 LastNumIterations = 0;`
- L189 _private member_ `int32 LastNumSubsteps = 0;`
- L190 _private member_ `float LastSimulationTime = 0.f;`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API CLOTHINGSYSTEMRUNTIMEINTERFACE_API`

### `Source/Runtime/ClothingSystemRuntimeInterface/Public/ClothingSimulationInterface.h` (Public)


#### class `IClothingSimulationContext`  
`class IClothingSimulationContext`  
_L19-24_
- desc: Empty interface, derived simulation modules define the contents of the context.
- L22 _public prototype_ `IClothingSimulationContext();`
- L23 _public prototype_ `virtual ~IClothingSimulationContext();`

#### class `IClothingSimulationInterface`  
`class IClothingSimulationInterface`  
_L34-178_
- desc: Base class for clothing simulators. The majority of the API for this class is protected. For the most part the simulation is not designed to be used outside of the FClothingSimulationInstance implementation which is used in the Skeletal Mesh Component, as its parallel simulation is tied to the Skeletal Mesh Component tick and dependents. Any method that is available in the public section below should consider that it may be called while the simulation is running.
- L37 _public prototype_ `IClothingSimulationInterface();`
- L38 _public prototype_ `virtual ~IClothingSimulationInterface();`
- L51 _protected prototype_ `virtual void CreateActor(USkeletalMeshComponent* InOwnerComponent, const UClothingAssetBase* InAsset, int32 SimDataIndex) = 0;` — Create an actor for this simulation from the data in InAsset Simulation data for this actor should be written back to SimDataIndex in AppendSimulationData @param InOwnerComponent - The component requesting this actor @param InAsset - The asset to create an actor from @param SimDataIndex - the sim data index to use when doing the writeback in AppendSimulationData
- L54 _protected prototype_ `virtual void EndCreateActor() = 0;` — Called once all CreateActor have been called.
- L57 _protected prototype_ `virtual IClothingSimulationContext* CreateContext() = 0;` — Create a new context, will not be filled, call FillContextAndPrepareTick before simulating with this context
- L66 _protected prototype_ `virtual void FillContextAndPrepareTick(const USkeletalMeshComponent* InComponent, float InDeltaTime, IClothingSimulationContext* InOutContext, bool bIsInitialization, bool bForceTeleportResetOnly) = 0;` — Fills an existing context for a single simulation step and do any other work that needs to be called by the engine on the game thread prior to simulation. @param InComponent - The component to fill the context for @param InOutContext - The context to fill @param bIsInitialization - Whether this fill is occurring as part of the actor creation stage @param bForceTeleportResetOnly - Whether ForceClothNextUpdateTeleportAndReset instead of Simulate and AppendSimulationData will be called.
- L69 _protected prototype_ `virtual void Initialize() = 0;` — Initialize the simulation, will be called before any Simulate calls
- L75 _protected prototype_ `virtual void Shutdown() = 0;` — Shutdown the simulation, this should clear ALL resources as we no longer expect to call any other function on this simulation without first calling Initialize again.
- L81 _protected prototype_ `virtual bool ShouldSimulateLOD(int32 OwnerLODIndex) const = 0;` — Called by the engine to determine if this simulation can run this tick at this LOD. ForceClothNextUpdateTeleportAndReset rather than Simulate and AppendSimulationData will be called this tick.
- L91 _protected prototype_ `virtual void Simulate_AnyThread(const IClothingSimulationContext* InContext) = 0;` — Run a single tick of the simulation. The pointer InContext is guaranteed (when called by the engine) to be the context allocated in CreateContext and can be assumed to be safely castable to any derived type allocated there. New callers should take care to make sure only the correct context is ever passed through. @note Can be called asynchronously outside of the game thread. @param InContext - The context to use during simulation, will have been filled in FillContextAndPrepareTick
- L97 _protected prototype_ `virtual void ForceClothNextUpdateTeleportAndReset_AnyThread() = 0;` — Called instead of Simulate when not ticking. @note Can be called asynchronously outside of the game thread.
- L100 _protected prototype_ `virtual void HardResetSimulation(const IClothingSimulationContext* InContext) = 0;` — Hard reset the simulation without necessarily recreating cloth actors.
- L103 _protected prototype_ `virtual void DestroyActors() = 0;` — Simulation should remove all of it's actors when next possible and free them
- L109 _protected prototype_ `virtual void DestroyContext(IClothingSimulationContext* InContext) = 0;` — Destroy a context object, engine will always pass a context created using CreateContext @param InContext - The context to destroy
- L118 _protected prototype_ `virtual void AppendSimulationData(TMap<int32, FClothSimulData>& InOutData, const USkeletalMeshComponent* OwnerComponent, const USkinnedMeshComponent* OverrideComponent) const = 0;` — Fill FClothSimulData map for the clothing simulation. Should fill a map pair per-actor. Do not remove InOutData elements which you are not responsible for: they may have been written by a different instance. @param InOutData - The simulation data to write to @param OwnerComponent - the component that owns the simulation @param OverrideComponent - An override component if bound to a leader pose component
- L121 _protected prototype_ `virtual FBoxSphereBounds GetBounds(const USkeletalMeshComponent* InOwnerComponent) const = 0;` — Get the bounds of the simulation mesh in local simulation space
- L129 _protected prototype_ `virtual void AddExternalCollisions(const FClothCollisionData& InData) = 0;` — Called by the engine when an external object wants to inject collision data into this simulation above and beyond what is specified in the asset for the internal actors Examples: Scene collision, collision for parents we are attached to @param InData - Collisions to add to this simulation
- L136 _protected prototype_ `virtual void ClearExternalCollisions() = 0;` — Called by the engine when external collisions are no longer necessary or when they need to be updated with some of the previous collisions removed. It is recommended in derived simulations to avoid freeing any allocations regarding external collisions as it is likely more will be added soon after this call
- L139 _protected function_ `virtual void GetCollisions(FClothCollisionData& OutCollisions, bool bIncludeExternal = true) const` — `UE_DEPRECATED(5.8, "GetCollisions has been deprecated. Use CollisionSources to add external collisions instead.")`
- L144 _public prototype_ `inline const IClothingSimulation* DynamicCastToIClothingSimulation() const;` — `UE_DEPRECATED(5.7, "This method is used to ease transition between the new and old interface and will be removed.")`
- L147 _public prototype_ `inline IClothingSimulation* DynamicCastToIClothingSimulation();` — `UE_DEPRECATED(5.7, "This method is used to ease transition between the new and old interface and will be removed.")`
- L151 _public function_ `virtual int32 GetNumCloths() const` — Return the number of simulated cloths. Implementation must be thread safe.
- L153 _public function_ `virtual int32 GetNumKinematicParticles() const` — Return the number of kinematic (fixed) particles. Implementation must be thread safe.
- L155 _public function_ `virtual int32 GetNumDynamicParticles() const` — Return the number of dynamic (simulated) particles. Implementation must be thread safe.
- L161 _public function_ `virtual int32 GetNumIterations() const` — Return the number of iterations used by the solver. This is the maximum used as an indicative value only, as this could vary between cloths. Implementation must be thread safe.
- L167 _public function_ `virtual int32 GetNumSubsteps() const` — Return the number of substeps used by the solver. This is the maximum used as an indicative value only, as this could vary between cloths. Implementation must be thread safe.
- L169 _public function_ `virtual float GetSimulationTime() const` — Return the simulation time in ms. Implementation must be thread safe.
- L171 _public function_ `virtual bool IsTeleported() const` — Return whether the simulation is teleported. Implementation must be thread safe.
- L177 _private member_ `bool bIsLegacyInterface = false;` — UE_DEPRECATED(5.7, "Use IClothingSimulationInterface instead.")
- L319 _function_ `inline const class IClothingSimulation* IClothingSimulationInterface::DynamicCastToIClothingSimulation() const`
- L324 _function_ `inline IClothingSimulation* IClothingSimulationInterface::DynamicCastToIClothingSimulation()`

#### class `IClothingSimulation`  
`class UE_DEPRECATED(5.7, "Use IClothingSimulationInterface instead.") IClothingSimulation : public IClothingSimulationInterface`  
_L180-316_
- inherits: `IClothingSimulationInterface`
- L183 _public prototype_ `IClothingSimulation();`
- L184 _public prototype_ `virtual ~IClothingSimulation();`
- L209 _protected function_ `virtual void CreateActor(USkeletalMeshComponent* InOwnerComponent, const UClothingAssetBase* InAsset, int32 SimDataIndex) override` — Create an actor for this simulation from the data in InAsset Simulation data for this actor should be written back to SimDataIndex in AppendSimulationData @param InOwnerComponent - The component requesting this actor @param InAsset - The asset to create an actor from @param SimDataIndex - the sim data index to use when doing the writeback in AppendSimulationData
- L217 _protected function_ `virtual void CreateActor(USkeletalMeshComponent* InOwnerComponent, UClothingAssetBase* InAsset, int32 SimDataIndex)` — `UE_DEPRECATED(5.7, "Use const arguments version instead,")`
- L226 _protected function_ `virtual void FillContextAndPrepareTick(const USkeletalMeshComponent* InComponent, float InDeltaTime, IClothingSimulationContext* InOutContext, bool bIsInitialization, bool bForceTeleportResetOnly) override` — Fills an existing context for a single simulation step and do any other work that needs to be called by the engine on the game thread prior to simulation. @param InComponent - The component to fill the context for @param InOutContext - The context to fill @param bIsInitialization - Whether this fill is occurring as part of the actor creation stage @param bForceTeleportResetOnly - Whether ForceClothNextUpdateTeleportAndReset instead of Simulate and AppendSimulationData will be called.
- L234 _protected function_ `virtual void FillContext(USkeletalMeshComponent* InComponent, float InDeltaTime, IClothingSimulationContext* InOutContext, bool bIsInitialization)` — `UE_DEPRECATED(5.7, "Use FillContextAndPrepareTick instead.")`
- L241 _protected function_ `virtual void FillContext(USkeletalMeshComponent* InComponent, float InDeltaTime, IClothingSimulationContext* InOutContext)` — `UE_DEPRECATED(5.7, "Use FillContextAndPrepareTick instead.")`
- L248 _protected function_ `virtual bool ShouldSimulate() const` — `UE_DEPRECATED(5.7, "This method has not been used consistently and has been replaced with ShouldSimulateLOD")` — Called by the engine to detect whether or not the simulation should run, essentially are there any actors that need to simulate in this simulation
- L256 _protected function_ `virtual bool ShouldSimulateLOD(int32 OwnerLODIndex) const override` — Called by the engine to determine if this simulation can run this tick at this LOD. ForceClothNextUpdateTeleportAndReset rather than Simulate and AppendSimulationData will be called this tick.
- L270 _protected function_ `virtual void Simulate_AnyThread(const IClothingSimulationContext* InContext) override` — Run a single tick of the simulation. The pointer InContext is guaranteed (when called by the engine) to be the context allocated in CreateContext and can be assumed to be safely castable to any derived type allocated there. New callers should make care to make sure only the correct context is ever passed through @param InContext - The context to use during simulation, will have been filled in FillContextAndPrepareTick
- L278 _protected function_ `virtual void Simulate(IClothingSimulationContext* InContext)` — `UE_DEPRECATED(5.7, "Use Simulate_AnyThread instead,")`
- L281 _protected function_ `virtual void ForceClothNextUpdateTeleportAndReset_AnyThread() override` — Called instead of Simulate when not ticking.
- L284 _protected function_ `virtual void HardResetSimulation(const IClothingSimulationContext* InContext) override` — Hard reset the simulation without necessarily recreating cloth actors.
- L293 _protected function_ `virtual void AppendSimulationData(TMap<int32, FClothSimulData>& InOutData, const USkeletalMeshComponent* OwnerComponent, const USkinnedMeshComponent* OverrideComponent) const override` — Fill FClothSimulData map for the clothing simulation. Should fill a map pair per-actor. Do not remove InOutData elements which you are not responsible for: they may have been written by a different instance. @param InOutData - The simulation data to write to @param OwnerComponent - the component that owns the simulation @param OverrideComponent - An override component if bound to a leader pose component
- L301 _protected function_ `virtual void GetSimulationData(TMap<int32, FClothSimulData>& OutData, USkeletalMeshComponent* InOwnerComponent, USkinnedMeshComponent* InOverrideComponent) const` — `UE_DEPRECATED(5.7, "Use AppendSimulationData instead.")`
- L305 _public function_ `virtual void GatherStats() const` — `UE_DEPRECATED(5.7, "GatherStats is unused and will be removed from future interfaces. Do not override.")`
- L308 _public function_ `virtual void SetNumIterations(int32 NumIterations)` — `UE_DEPRECATED(5.7, "Use a clothing simulation interactor to set this simulation property instead.")`
- L310 _public function_ `virtual void SetMaxNumIterations(int32 MaxNumIterations)` — `UE_DEPRECATED(5.7, "Use a clothing simulation interactor to set this simulation property instead.")`
- L312 _public function_ `virtual void SetNumSubsteps(int32 NumSubsteps)` — `UE_DEPRECATED(5.7, "Use a clothing simulation interactor to set this simulation property instead.")`
- L315 _public function_ `virtual void UpdateWorldForces(const USkeletalMeshComponent* OwnerComponent)` — `UE_DEPRECATED(5.7, "Use FillContextAndPrepareTick instead.")`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CLOTHINGSYSTEMRUNTIMEINTERFACE_API`

### `Source/Runtime/ClothingSystemRuntimeInterface/Public/ClothingSimulationTeleportHelpers.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace ClothingSimulation` (scope `UE`)
- L8 _namespace_ `namespace TeleportHelpers` (scope `UE::ClothingSimulation`)
- L10 _function_ `inline float ComputeTeleportCosineRotationThreshold(float ThresholdInDegrees)` (scope `UE::ClothingSimulation::TeleportHelpers`)
- L18 _function_ `inline float ComputeTeleportDistanceThresholdSquared(float ThresholdDistance)` (scope `UE::ClothingSimulation::TeleportHelpers`)
- L24 _prototype_ `EClothingTeleportMode CalculateClothingTeleport(EClothingTeleportMode CurrentTeleportMode, const FMatrix& CurRootBoneMat, const FMatrix& PrevRootBoneMat, bool bResetAfterTeleport, float ClothTeleportDistThresholdSquared, float ClothTeleportCosineThresholdInRad);` (scope `UE::ClothingSimulation::TeleportHelpers`)

### `Source/Runtime/ClothingSystemRuntimeInterface/Public/ClothingSystemRuntimeInterfaceModule.h` (Public)


#### class `FClothingSystemRuntimeInterfaceModule`  
`class FClothingSystemRuntimeInterfaceModule : public IModuleInterface`  
_L7-18_
- inherits: `IModuleInterface`
- L12 _public prototype_ `FClothingSystemRuntimeInterfaceModule();`
- L14 _public prototype_ `virtual void StartupModule() override;`
- L15 _public prototype_ `virtual void ShutdownModule() override;`

### `Source/Runtime/ClothingSystemRuntimeInterface/Public/ClothingSystemRuntimeTypes.h` (Public)


#### struct `FClothSimulData`  
`struct FClothSimulData`  
_L14-42_
- desc: Data produced by a clothing simulation
- L16 _public function_ `void Reset()`
- L23 _public function_ `bool IsReset() const`
- L29 _public member_ `TArray<FVector3f, TAlignedHeapAllocator<16>> Positions;` — Positions of the simulation mesh particles (aligned for SIMD loads)
- L32 _public member_ `TArray<FVector3f, TAlignedHeapAllocator<16>> Normals;` — Normals at the simulation mesh particles (aligned for SIMD loads)
- L35 _public member_ `FTransform Transform;` — Transform applied per position/normal element when loaded
- L38 _public member_ `FTransform ComponentRelativeTransform;` — Transform relative to the component to update clothing root transform when not ticking clothing but rendering a component
- L41 _public member_ `int32 LODIndex;` — Current LOD index the data is valid for

#### enum `EClothingTeleportMode`  
`enum class EClothingTeleportMode : uint8`  
_L45-55_
- reflection: `UENUM()`
- L48 _public enumerator_ `None = 0` — No teleport, simulate as normal
- L50 _public enumerator_ `Teleport` — Teleport the simulation, causing no intertial effects but keep the sim mesh shape
- L52 _public enumerator_ `TeleportAndReset` — Teleport the simulation, causing no intertial effects and reset the sim mesh shape
- L54 _public enumerator_ `HardReset` — Hard reset the simulation by refreshing the cloth config

#### struct `IClothSimulationDataProvider`  
`struct IClothSimulationDataProvider`  
_L57-60_
- L59 _public prototype_ `virtual void GetUpdateClothSimulationData_AnyThread(TMap<int32, FClothSimulData>& OutClothSimulData, FMatrix& OutLocalToWorld, float& OutClothBlendWeight) const = 0;`
