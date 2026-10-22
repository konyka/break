# Plugins / ApexDestruction

- module root: `Plugins/Runtime/ApexDestruction/Source/ApexDestruction`
- headers: 7; symbols: 184
- symbol kinds: class=4, delegate=2, enum=2, enumerator=6, externvar=1, function=14, macro=1, member=74, namespace=3, prototype=67, struct=10
- PrivateDependencyModuleNames: APEX, ApexDestructionLib, Core, CoreUObject, EditorFramework, Engine, NavigationSystem, PhysX, RHI, RenderCore, UnrealEd

### `Plugins/Runtime/ApexDestruction/Source/ApexDestruction/Public/ApexDestructibleAssetImport.h` (Public)
_(no declarations extracted)_

### `Plugins/Runtime/ApexDestruction/Source/ApexDestruction/Public/ApexDestructionCustomPayload.h` (Public)


#### struct `FUpdateChunksInfo`  
`struct UE_DEPRECATED(4.26, "APEX is deprecated. Destruction in future will be supported using Chaos Destruction.") FUpdateChunksInfo`  
_L8-15_
- L10 _public member_ `int32 ChunkIndex;`
- L11 _public member_ `FTransform WorldTM;`
- L13 _public function_ `FUpdateChunksInfo(int32 InChunkIndex, const FTransform & InWorldTM) : ChunkIndex(InChunkIndex), WorldTM(InWorldTM)`

### `Plugins/Runtime/ApexDestruction/Source/ApexDestruction/Public/ApexDestructionModule.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace nvidia`
- L10 _namespace_ `namespace apex` (scope `nvidia`)
- L17 _externvar_ `extern nvidia::apex::ModuleDestructible* GApexModuleDestructible;`

### `Plugins/Runtime/ApexDestruction/Source/ApexDestruction/Public/DestructibleActor.h` (Public)


#### class `ADestructibleActor`  
`class ADestructibleActor : public AActor`  
_L19-54_
- reflection: `UE_DEPRECATED(4.26, "APEX is deprecated. Destruction in future will be supported using Chaos Destruction.")`
- reflection: `UCLASS(hideCategories=(Input), showCategories=("Input|MouseInput", "Input|TouchInput"), ComponentWrapperClass)`
- inherits: `AActor`
- L29 _private member_ `TObjectPtr<UDestructibleComponent> DestructibleComponent;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Destruction, meta = (ExposeFunctionCategories = "Destruction,Components|Destructible", AllowPrivateAccess = "true"))`
- L34 _public member_ `FActorFractureSignature OnActorFracture;` — `UPROPERTY(BlueprintAssignable, Category = "Components|Destructible")`
- L39 _public member_ `uint32 bAffectNavigation : 1;` — `UE_DEPRECATED(4.24, "This property will be removed in future versions. Please use bCanEverAffectNavigation in DestructionComponent.")` — `UPROPERTY(config, BlueprintReadWrite, Category = Navigation, meta = (DeprecationMessage = "Setting the value from Blueprint script does nothing. Please use bCanEverAffectNavigation in DestructionComponent."))`
- L44 _public prototype_ `virtual bool GetReferencedContentObjects( TArray<UObject*>& Objects ) const override;`
- L45 _public prototype_ `virtual void PostLoad() override;`
- L52 _public function_ `UDestructibleComponent* GetDestructibleComponent() const` — Returns DestructibleComponent subobject

#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FActorFractureSignature, const FVector&, HitPoint, const FVector&, HitDirection);` — Delegate for notification when fracture occurs
- L15 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FActorFractureSignature, const FVector&, HitPoint, const FVector&, HitDirection);` — Delegate for notification when fracture occurs

### `Plugins/Runtime/ApexDestruction/Source/ApexDestruction/Public/DestructibleComponent.h` (Public)


#### class `UDestructibleComponent`  
`class UDestructibleComponent : public USkinnedMeshComponent, public IDestructibleInterface`  
_L31-198_
- reflection: `UE_DEPRECATED(4.26, "APEX is deprecated. Destruction in future will be supported using Chaos Destruction.")`
- reflection: `UCLASS(ClassGroup = Physics, hidecategories = (Object, Mesh, "Mesh|SkeletalAsset", "Components|SkinnedMesh", Mirroring, Activation, "Components|Activation"), config = Engine, editinlinenew, meta = (BlueprintSpawnableComponent))`
- inherits: `USkinnedMeshComponent,IDestructibleInterface`
- L37 _private member_ `uint32 bFractureEffectOverride:1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=DestructibleComponent)` — If set, use this actor's fracture effects instead of the asset's fracture effects.
- L41 _private member_ `TArray<struct FFractureEffect> FractureEffects;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, editfixedsize, Category=DestructibleComponent)` — Fracture effects for each fracture level. Used only if Fracture Effect Override is set.
- L48 _private member_ `bool bEnableHardSleeping;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=DestructibleComponent)` — Enable "hard sleeping" for destruction-generated PxActors.  This means that they turn kinematic when they sleep, but can be made dynamic again by application of enough damage.
- L54 _private member_ `float LargeChunkThreshold;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DestructibleComponent)` — The minimum size required to treat chunks as Large.
- L60 _private member_ `TObjectPtr<class UDestructibleMesh> DestructibleMesh_DEPRECATED;` — `UPROPERTY(Transient, BlueprintSetter=SetDestructibleMesh, BlueprintGetter=GetDestructibleMesh, Category = "Components|Destructible", meta = (DeprecatedProperty, DeprecatedMessage = "Destructible mesh is now deprected, use UGeometryCollection instead"))` — Provide a blueprint interface for setting the destructible mesh
- L66 _private prototype_ `virtual void PostEditChangeProperty( struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L69 _private prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L75 _private prototype_ `virtual void ApplyDamage(float DamageAmount, const FVector& HitLocation, const FVector& ImpulseDir, float ImpulseStrength) override;` — `UFUNCTION(BlueprintCallable, Category="Components|Destructible")` — Take damage
- L79 _private prototype_ `virtual void ApplyRadiusDamage(float BaseDamage, const FVector& HurtOrigin, float DamageRadius, float ImpulseStrength, bool bFullDamage) override;` — `UFUNCTION(BlueprintCallable, Category="Components|Destructible")` — Take radius damage
- L83 _private prototype_ `void SetDestructibleMesh(class UDestructibleMesh* NewMesh);` — `UE_DEPRECATED("5.1", "Destructible mesh is now deprected, use UGeometryCollection instead")` — `UFUNCTION(BlueprintCallable, BlueprintSetter, Category="Components|Destructible", meta=(DeprecatedFunction, DeprecationMessage="Destructible mesh is now deprected, use UGeometryCollection instead"))`
- L87 _private prototype_ `class UDestructibleMesh* GetDestructibleMesh();` — `UE_DEPRECATED("5.1", "Destructible mesh is now deprected, use UGeometryCollection instead")` — `UFUNCTION(BlueprintCallable, BlueprintGetter, Category="Components|Destructible", meta = (DeprecatedFunction, DeprecationMessage = "Destructible mesh is now deprected, use UGeometryCollection instead"))`
- L91 _private member_ `FComponentFractureSignature OnComponentFracture;` — `UPROPERTY(BlueprintAssignable, Category = "Components|Destructible")` — Called when a component is touched
- L96 _public prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;`
- L97 _public prototype_ `virtual void OnUpdateTransform(EUpdateTransformFlags UpdateTransformFlags, ETeleportType Teleport = ETeleportType::None) override;`
- L98 _public prototype_ `virtual void Activate(bool bReset=false) override;`
- L99 _public prototype_ `virtual void Deactivate() override;`
- L103 _public prototype_ `virtual void BeginPlay() override;`
- L105 _protected prototype_ `virtual void OnCreatePhysicsState() override;`
- L106 _protected prototype_ `virtual void OnDestroyPhysicsState() override;`
- L108 _public prototype_ `virtual class UBodySetup* GetBodySetup() override;`
- L112 _public prototype_ `virtual FBodyInstance* GetBodyInstance(FName BoneName = NAME_None, bool bGetWelded = true, int32 Index = INDEX_NONE) const override;`
- L113 _public prototype_ `virtual bool CanEditSimulatePhysics() override;`
- L114 _public prototype_ `virtual bool IsAnySimulatingPhysics() const override;`
- L116 _public prototype_ `virtual void AddImpulse(FVector Impulse, FName BoneName = NAME_None, bool bVelChange = false) override;`
- L117 _public prototype_ `virtual void AddImpulseAtLocation(FVector Impulse, FVector Position, FName BoneName = NAME_None) override;`
- L118 _public prototype_ `virtual void AddForce(FVector Force, FName BoneName = NAME_None, bool bAccelChange = false) override;`
- L119 _public prototype_ `virtual void AddForceAtLocation(FVector Force, FVector Location, FName BoneName = NAME_None) override;`
- L120 _public prototype_ `virtual void AddForceAtLocationLocal(FVector Force, FVector Location, FName BoneName = NAME_None) override;`
- L121 _public prototype_ `virtual void AddRadialImpulse(FVector Origin, float Radius, float Strength, ERadialImpulseFalloff Falloff, bool bVelChange=false) override;`
- L122 _public prototype_ `virtual void AddRadialForce(FVector Origin, float Radius, float Strength, ERadialImpulseFalloff Falloff, bool bAccelChange = false) override;`
- L123 _public prototype_ `virtual void ReceiveComponentDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;`
- L125 _public prototype_ `virtual bool LineTraceComponent( FHitResult& OutHit, const FVector Start, const FVector End, const FCollisionQueryParams& Params ) override;`
- L126 _public prototype_ `virtual bool SweepComponent( FHitResult& OutHit, const FVector Start, const FVector End, const FQuat& ShapeWorldRotation, const FCollisionShape& CollisionShape, bool bTraceComplex=false) override;`
- L127 _public prototype_ `virtual void SetEnableGravity(bool bGravityEnabled) override;`
- L129 _public prototype_ `virtual void WakeRigidBody(FName BoneName ) override;`
- L130 _public prototype_ `virtual void SetSimulatePhysics(bool bSimulate) override;`
- L132 _public prototype_ `virtual void SetMaterial(int32 ElementIndex, UMaterialInterface* Material) override;`
- L133 _public prototype_ `virtual void SetCollisionEnabled(ECollisionEnabled::Type NewType) override;`
- L134 _public prototype_ `virtual void SetCollisionProfileName(FName InCollisionProfileName, bool bUpdateOverlaps=true) override;`
- L135 _public prototype_ `virtual void OnActorEnableCollisionChanged() override;`
- L137 _public prototype_ `virtual void SetCollisionResponseToChannel(ECollisionChannel Channel, ECollisionResponse NewResponse) override;`
- L138 _public prototype_ `virtual void SetCollisionResponseToAllChannels(ECollisionResponse NewResponse) override;`
- L139 _public prototype_ `virtual void SetCollisionResponseToChannels(const FCollisionResponseContainer& NewReponses) override;`
- L143 _public prototype_ `virtual bool ShouldUpdateTransform(bool bLODHasChanged) const override;`
- L144 _public prototype_ `virtual void RefreshBoneTransforms(FActorComponentTickFunction* TickFunction = NULL) override;`
- L145 _public prototype_ `virtual void SetSkeletalMesh(USkeletalMesh* InSkelMesh, bool bReinitPose = true) override;`
- L146 _public prototype_ `virtual FTransform GetSocketTransform(FName InSocketName, ERelativeTransformSpace TransformSpace = RTS_World) const override;`
- L156 _public prototype_ `void SetChunkVisible( int32 ChunkIndex, bool bInVisible );` — This method makes a chunk (fractured piece) visible or invisible. @param ChunkIndex - Which chunk to affect.  ChunkIndex must lie in the range: 0 <= ChunkIndex < ((DestructibleMesh*)USkeletalMesh)->ApexDestructibleAsset->chunkCount(). @param bVisible - If true, the chunk will be made visible.  Otherwise, the chunk is made invisible.
- L165 _public prototype_ `void SetChunkWorldRT( int32 ChunkIndex, const FQuat& WorldRotation, const FVector& WorldTranslation );` — This method sets a chunk's (fractured piece's) world rotation and translation. @param ChunkIndex - Which chunk to affect.  ChunkIndex must lie in the range: 0 <= ChunkIndex < ((DestructibleMesh*)USkeletalMesh)->ApexDestructibleAsset->chunkCount(). @param WorldRotation - The orientation to give to the chunk in world space, represented as a quaternion. @param WorldRotation - The world space position to give to the chunk.
- L169 _public prototype_ `virtual bool DoCustomNavigableGeometryExport(FNavigableGeometryExport& GeomExport) const override;`
- L171 _public function_ `FORCEINLINE static int32 ChunkIdxToBoneIdx(int32 ChunkIdx)`
- L172 _public function_ `FORCEINLINE static int32 BoneIdxToChunkIdx(int32 BoneIdx)`
- L176 _private prototype_ `void SetChunksWorldTM(const TArray<FUpdateChunksInfo>& UpdateInfos);`
- L179 _private prototype_ `bool IsFracturedOrInitiallyStatic() const;`
- L182 _private prototype_ `bool ExecuteOnPhysicsReadOnly(TFunctionRef<void()> Func) const;` — Obtains the appropriate PhysX scene lock for READING and executes the passed in lambda.
- L185 _private prototype_ `bool ExecuteOnPhysicsReadWrite(TFunctionRef<void()> Func) const;` — Obtains the appropriate PhysX scene lock for WRITING and executes the passed in lambda.
- L188 _private member_ `FCollisionResponse LargeChunkCollisionResponse;` — Collision response used for chunks
- L189 _private member_ `FCollisionResponse SmallChunkCollisionResponse;`
- L193 _private member_ `float ContactOffsetFactor;` — Cached values for computing contact offsets
- L194 _private member_ `float MinContactOffset;`
- L195 _private member_ `float MaxContactOffset;`

#### Free symbols / members of external scopes

- L21 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FComponentFractureSignature, const FVector &, HitPoint, const FVector &, HitDirection);` — Delegate for notification when fracture occurs
- L21 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FComponentFractureSignature, const FVector &, HitPoint, const FVector &, HitDirection);` — Delegate for notification when fracture occurs

### `Plugins/Runtime/ApexDestruction/Source/ApexDestruction/Public/DestructibleFractureSettings.h` (Public)


#### enum `EDestructibleImportOptions::Type`  
`enum Type`  
_L18-24_
- L21 _public enumerator_ `None = 0` — Just imports the APEX asset
- L23 _public enumerator_ `PreserveSettings = 1<<0` — Preserves settings in DestructibleMesh

#### struct `FFractureMaterial`  
`struct FFractureMaterial`  
_L31-78_
- reflection: `UE_DEPRECATED(4.26, "APEX is deprecated. Destruction in future will be supported using Chaos Destruction.")`
- reflection: `USTRUCT()`
- desc: Parameters to describe the application of U,V coordinates on a particular slice within a destructible.
- L40 _public member_ `FVector2D UVScale;` — `UPROPERTY(EditAnywhere, Category=FractureMaterial)` — The UV scale (geometric distance/unit texture distance) for interior materials. Default = (100.0f,100.0f).
- L47 _public member_ `FVector2D UVOffset;` — `UPROPERTY(EditAnywhere, Category=FractureMaterial)` — A UV origin offset for interior materials. Default = (0.0f,0.0f).
- L54 _public member_ `FVector Tangent;` — `UPROPERTY(EditAnywhere, Category=FractureMaterial)` — Object-space vector specifying surface tangent direction.  If this vector is (0.0f,0.0f,0.0f), then an arbitrary direction will be chosen. Default = (0.0f,0.0f,0.0f).
- L61 _public member_ `float UAngle;` — `UPROPERTY(EditAnywhere, Category=FractureMaterial)` — Angle from tangent direction for the u coordinate axis. Default = 0.0f.
- L69 _public member_ `int32 InteriorElementIndex;` — `UPROPERTY(EditAnywhere, Category=FractureMaterial)` — The element index to use for the newly-created triangles. If a negative index is given, a new element will be created for interior triangles. Default = -1
- L71 _public function_ `FFractureMaterial() : UVScale(100.0f, 100.0f) , UVOffset(0.0f, 0.0f) , Tangent(0.0f, 0.0f, 0.0f) , UAngle(0.0f) , InteriorElementIndex(-1)`

#### struct `FDestructibleChunkParameters`  
`struct UE_DEPRECATED(4.26, "APEX is deprecated. Destruction in future will be supported using Chaos Destruction.") FDestructibleChunkParameters`  
_L83-128_
- reflection: `USTRUCT()`
- desc: Per-chunk authoring data.
- L93 _public member_ `bool bIsSupportChunk;` — `UPROPERTY(EditAnywhere, Category=DestructibleChunkParameters)` — Defines the chunk to be environmentally supported, if the appropriate NxDestructibleParametersFlag flags are set in NxDestructibleParameters. Default = false.
- L100 _public member_ `bool bDoNotFracture;` — `UPROPERTY(EditAnywhere, Category=DestructibleChunkParameters)` — Defines the chunk to be unfractureable.  If this is true, then none of its children will be fractureable. Default = false.
- L107 _public member_ `bool bDoNotDamage;` — `UPROPERTY(EditAnywhere, Category=DestructibleChunkParameters)` — Defines the chunk to be undamageable.  This means this chunk will not fracture, but its children might. Default = false.
- L120 _public member_ `bool bDoNotCrumble;` — `UPROPERTY(EditAnywhere, Category=DestructibleChunkParameters)` — Defines the chunk to be uncrumbleable.  This means this chunk will not be broken down into fluid mesh particles no matter how much damage it takes.  Note: this only applies to chunks with no children.  For a chunk with children, then: 1) The chunk may be broken down into its children, and then its children may be crumbled, if the doNotCrumble flag is not set on them. 2) If the Destructible module's chunk depth offset LOD may be set such that this chunk effectively has no children. In this case, the doNotCrumble flag will apply to it. Default = false.
- L122 _public function_ `FDestructibleChunkParameters() : bIsSupportChunk(false) , bDoNotFracture(false) , bDoNotDamage(false) , bDoNotCrumble(false)`

#### class `UDestructibleFractureSettings`  
`class UE_DEPRECATED(4.26, "APEX is deprecated. Destruction in future will be supported using Chaos Destruction.") UDestructibleFractureSettings : public UObject`  
_L133-183_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: Information to create an NxDestructibleAsset
- L141 _private prototype_ `virtual ~UDestructibleFractureSettings();` — Destructor. Defined to avoid compilation errors on clang where the UHT generated CPP file ends up instantiating destructors for member variables without full type information
- L144 _private prototype_ `UDestructibleFractureSettings(FVTableHelper& Helper);` — DO NOT USE. This constructor is for internal usage only for hot-reload purposes.
- L148 _private member_ `int32 CellSiteCount;` — `UPROPERTY(EditAnywhere, Category = Voronoi, meta = (ClampMin = "1", UIMin = "1"))` — The number of voronoi cell sites.
- L153 _private member_ `FFractureMaterial FractureMaterialDesc;` — `UPROPERTY(EditAnywhere, transient, Category=General)` — Stored interior material data.  Just need one as we only support Voronoi splitting.
- L158 _private member_ `int32 RandomSeed;` — `UPROPERTY(EditAnywhere, Category=General)` — Random seed for reproducibility
- L162 _private member_ `TArray<FVector> VoronoiSites;` — `UPROPERTY()` — Stored Voronoi sites
- L166 _private member_ `int32 OriginalSubmeshCount;` — `UPROPERTY()` — The mesh's original number of submeshes.  APEX needs to store this in the authoring.
- L170 _private member_ `TArray<TObjectPtr<UMaterialInterface>> Materials;` — `UPROPERTY()` — APEX references materials by name, but we'll bypass that mechanism and use of UE materials instead.
- L175 _private member_ `TArray<FDestructibleChunkParameters> ChunkParameters;` — `UPROPERTY()` — Per-chunk authoring parameters, which should be made writable when a chunk selection GUI is in place.
- L179 _private prototype_ `virtual void PostInitProperties() override;`
- L180 _private prototype_ `virtual void BeginDestroy() override;`
- L181 _private prototype_ `virtual void Serialize(FArchive& Ar) override;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace EDestructibleImportOptions`

### `Plugins/Runtime/ApexDestruction/Source/ApexDestruction/Public/DestructibleMesh.h` (Public)


#### enum `EImpactDamageOverride`  
`enum EImpactDamageOverride : int`  
_L23-29_
- reflection: `UENUM()`
- desc: Chunks up to the depth DefaultImpactDamageDepth will take impact damage, unless IDO_On or IDO_Off is chosen.
- L25 _public enumerator_ `IDO_None`
- L26 _public enumerator_ `IDO_On`
- L27 _public enumerator_ `IDO_Off`
- L28 _public enumerator_ `IDO_MAX`

#### struct `FDestructibleDepthParameters`  
`struct UE_DEPRECATED(4.26, "APEX is deprecated. Destruction in future will be supported using Chaos Destruction.") FDestructibleDepthParameters`  
_L34-46_
- reflection: `USTRUCT()`
- desc: Properties that may be set for all chunks at a particular depth in the fracture hierarchy.
- L43 _public function_ `FDestructibleDepthParameters() : ImpactDamageOverride(IDO_None)`

#### struct `FDestructibleParametersFlag`  
`struct UE_DEPRECATED(4.26, "APEX is deprecated. Destruction in future will be supported using Chaos Destruction.") FDestructibleParametersFlag`  
_L51-146_
- reflection: `USTRUCT()`
- desc: Flags that apply to a destructible actor.
- L61 _public member_ `uint32 bAccumulateDamage:1;` — `UPROPERTY(EditAnywhere, Category=DestructibleParametersFlag)` — If set, chunks will "remember" damage applied to them, so that many applications of a damage amount below damageThreshold will eventually fracture the chunk.  If not set, a single application of damage must exceed damageThreshold in order to fracture the chunk.
- L71 _public member_ `uint32 bAssetDefinedSupport:1;` — `UPROPERTY(EditAnywhere, Category=DestructibleParametersFlag)` — If set, then chunks which are tagged as "support" chunks (via NxDestructibleChunkDesc::isSupportChunk) will have environmental support in static destructibles. Note: if both bAssetDefinedSupport and bWorldSupport are set, then chunks must be tagged as "support" chunks AND overlap the Scene's static geometry in order to be environmentally supported.
- L81 _public member_ `uint32 bWorldSupport:1;` — `UPROPERTY(EditAnywhere, Category=DestructibleParametersFlag)` — If set, then chunks which overlap the Scene's static geometry will have environmental support in static destructibles. Note: if both bAssetDefinedSupport and bWorldSupport are set, then chunks must be tagged as "support" chunks AND overlap the Scene's static geometry in order to be environmentally supported.
- L89 _public member_ `uint32 bDebrisTimeout:1;` — `UPROPERTY(EditAnywhere, Category=DestructibleParametersFlag)` — Whether or not chunks at or deeper than the "debris" depth (see NxDestructibleParameters::debrisDepth) will time out.  The lifetime is a value between NxDestructibleParameters::debrisLifetimeMin and NxDestructibleParameters::debrisLifetimeMax, based upon the destructible module's LOD setting.
- L98 _public member_ `uint32 bDebrisMaxSeparation:1;` — `UPROPERTY(EditAnywhere, Category=DestructibleParametersFlag)` — Whether or not chunks at or deeper than the "debris" depth (see NxDestructibleParameters::debrisDepth) will be removed if they separate too far from their origins.  The maxSeparation is a value between NxDestructibleParameters::debrisMaxSeparationMin and NxDestructibleParameters::debrisMaxSeparationMax, based upon the destructible module's LOD setting.
- L108 _public member_ `uint32 bCrumbleSmallestChunks:1;` — `UPROPERTY(EditAnywhere, Category=DestructibleParametersFlag)` — If set, the smallest chunks may be further broken down, either by fluid crumbles (if a crumble particle system is specified in the NxDestructibleActorDesc), or by simply removing the chunk if no crumble particle system is specified.  Note: the "smallest chunks" are normally defined to be the deepest level of the fracture hierarchy.  However, they may be taken from higher levels of the hierarchy if NxModuleDestructible::setMaxChunkDepthOffset is called with a non-zero value.
- L117 _public member_ `uint32 bAccurateRaycasts:1;` — `UPROPERTY(EditAnywhere, Category=DestructibleParametersFlag)` — If set, the NxDestructibleActor::rayCast function will search within the nearest visible chunk hit for collisions with child chunks.  This is used to get a better raycast position and normal, in case the parent collision volume does not tightly fit the graphics mesh.  The returned chunk index will always be that of the visible parent that is intersected, however.
- L125 _public member_ `uint32 bUseValidBounds:1;` — `UPROPERTY(EditAnywhere, Category=DestructibleParametersFlag)` — If set, the ValidBounds field of NxDestructibleParameters will be used.  These bounds are translated (but not scaled or rotated) to the origin of the destructible actor.  If a chunk or chunk island moves outside of those bounds, it is destroyed.
- L132 _public member_ `uint32 bFormExtendedStructures:1;` — `UPROPERTY(EditAnywhere, Category=DestructibleParametersFlag)` — If initially static, the destructible will become part of an extended support structure if it is in contact with another static destructible that also has this flag set.
- L135 _public function_ `FDestructibleParametersFlag() : bAccumulateDamage(false) , bAssetDefinedSupport(false) , bWorldSupport(false) , bDebrisTimeout(false) , bDebrisMaxSeparation(false) , bCrumbleSmallestChunks(false) , bAccurateRaycasts(false) , bUseValidBounds(false) , bFormExtendedStructures(false)`

#### struct `FDestructibleDamageParameters`  
`struct UE_DEPRECATED(4.26, "APEX is deprecated. Destruction in future will be supported using Chaos Destruction.") FDestructibleDamageParameters`  
_L151-210_
- reflection: `USTRUCT()`
- desc: Parameters that pertain to chunk damage.
- L159 _public member_ `float DamageThreshold;` — `UPROPERTY(EditAnywhere, Category=DestructibleDamageParameters)` — The damage amount which will cause a chunk to fracture (break free).
- L163 _public member_ `float DamageSpread;` — `UPROPERTY(EditAnywhere, Category=DestructibleDamageParameters)` — Controls how easily damage spreads. DamageRadius = Damage*DamageSpread. All chunks within DamageRadius will take damage. Full damage is taken at zero distance, and zero damage at the DamageRadius.
- L170 _public member_ `bool bEnableImpactDamage;` — `UPROPERTY(EditAnywhere, Category = DestructibleDamageParameters)` — Whether to apply damage to destructible when colliding with an object. @see ImpactDamage
- L177 _public member_ `float ImpactDamage;` — `UPROPERTY(EditAnywhere, Category=DestructibleDamageParameters, meta = (editcondition = "bEnableImpactDamage"))` — Controls how much damage is applied upon collision. Damage = ImpactDamage * ImpactForce. @see DepthParameters for per level control of ImpactDamage
- L184 _public member_ `int32 DefaultImpactDamageDepth;` — `UPROPERTY(EditAnywhere, Category = DestructibleDamageParameters, meta = (ClampMin = "0", UIMin = "0", editcondition = "bEnableImpactDamage"))` — Max depth level where impact damage is enabled. @see DepthParameters for per level control of ImpactDamage If negative, impact damage is disabled
- L191 _public member_ `bool bCustomImpactResistance;` — `UPROPERTY(EditAnywhere, Category = DestructibleDamageParameters)` — By default, objects that collide with destructibles will bounce back. Custom resistance allows for finer control of how much a destructible "pushes back" against a colliding object. @see ImpactResistance
- L198 _public member_ `float ImpactResistance;` — `UPROPERTY(EditAnywhere, meta = (ClampMin = "0.001", UIMin = "0", editcondition = "bCustomImpactResistance"), Category = DestructibleDamageParameters)` — Controls how much resistance is applied to colliding objects. Weak materials like glass should set this to a low value so that objects will pass right through them during fracture. @see DepthParameters for per level control of ImpactResistance
- L201 _public function_ `FDestructibleDamageParameters() : DamageThreshold(1.0f) , DamageSpread(0.1f) , bEnableImpactDamage(false) , ImpactDamage(0.1f) , DefaultImpactDamageDepth(0.f) , bCustomImpactResistance(false) , ImpactResistance(1.f)`

#### struct `FDestructibleDebrisParameters`  
`struct UE_DEPRECATED(4.26, "APEX is deprecated. Destruction in future will be supported using Chaos Destruction.") FDestructibleDebrisParameters`  
_L215-264_
- reflection: `USTRUCT()`
- desc: Parameters that pertain to chunk debris-level settings.
- L228 _public member_ `float DebrisLifetimeMin;` — `UPROPERTY(EditAnywhere, Category=DestructibleDebrisParameters)` — "Debris chunks" (see debrisDepth, above) will be destroyed after a time (in seconds) separated from non-debris chunks.  The actual lifetime is interpolated between these two bDebrisTimeout, based upon the module's LOD setting.  To disable lifetime, clear the bDebrisTimeout flag in the flags field. If debrisLifetimeMax < debrisLifetimeMin, the mean of the two is used for both. Default debrisLifetimeMin = 1.0, debrisLifetimeMax = 10.0f.
- L231 _public member_ `float DebrisLifetimeMax;` — `UPROPERTY(EditAnywhere, Category=DestructibleDebrisParameters)`
- L242 _public member_ `float DebrisMaxSeparationMin;` — `UPROPERTY(EditAnywhere, Category=DestructibleDebrisParameters)` — "Debris chunks" (see debrisDepth, above) will be destroyed if they are separated from their origin by a distance greater than maxSeparation.  The actual maxSeparation is interpolated between these two values, based upon the module's LOD setting.  To disable maxSeparation, clear the bDebrisMaxSeparation flag in the flags field. If debrisMaxSeparationMax < debrisMaxSeparationMin, the mean of the two is used for both. Default debrisMaxSeparationMin = 1.0, debrisMaxSeparationMax = 10.0f.
- L245 _public member_ `float DebrisMaxSeparationMax;` — `UPROPERTY(EditAnywhere, Category=DestructibleDebrisParameters)`
- L253 _public member_ `FBox ValidBounds;` — `UPROPERTY(EditAnywhere, Category=DestructibleDebrisParameters)` — "Debris chunks" (see debrisDepth, above) will be destroyed if they leave this box. The box translates with the destructible actor's initial position, but does not rotate or scale.
- L257 _public function_ `FDestructibleDebrisParameters() : DebrisLifetimeMin(1.0f) , DebrisLifetimeMax(10.0f) , DebrisMaxSeparationMin(1.0f) , DebrisMaxSeparationMax(10.0f) , ValidBounds(FVector(-500000.0f), FVector(500000.0f))`

#### struct `FDestructibleAdvancedParameters`  
`struct UE_DEPRECATED(4.26, "APEX is deprecated. Destruction in future will be supported using Chaos Destruction.") FDestructibleAdvancedParameters`  
_L269-310_
- reflection: `USTRUCT()`
- desc: Parameters that are less-often used.
- L279 _public member_ `float DamageCap;` — `UPROPERTY(EditAnywhere, Category=DestructibleAdvancedParameters)` — Limits the amount of damage applied to a chunk.  This is useful for preventing the entire destructible from getting pulverized by a very large application of damage.  This can easily happen when impact damage is used, and the damage amount is proportional to the impact force (see forceToDamage).
- L287 _public member_ `float ImpactVelocityThreshold;` — `UPROPERTY(EditAnywhere, Category=DestructibleAdvancedParameters)` — Large impact force may be reported if rigid bodies are spawned inside one another.  In this case the realative velocity of the two objects will be low.  This variable allows the user to set a minimum velocity threshold for impacts to ensure that the objects are moving at a min velocity in order for the impact force to be considered.
- L294 _public member_ `float MaxChunkSpeed;` — `UPROPERTY(EditAnywhere, Category=DestructibleAdvancedParameters)` — If greater than 0, the chunks' speeds will not be allowed to exceed this value.  Use 0 to disable this feature (this is the default).
- L301 _public member_ `float FractureImpulseScale;` — `UPROPERTY(EditAnywhere, Category=DestructibleAdvancedParameters)` — Scale factor used to apply an impulse force along the normal of chunk when fractured.  This is used in order to "push" the pieces out as they fracture.
- L304 _public function_ `FDestructibleAdvancedParameters() : DamageCap(0) , ImpactVelocityThreshold(0) , MaxChunkSpeed(0) , FractureImpulseScale(0)`

#### struct `FDestructibleSpecialHierarchyDepths`  
`struct UE_DEPRECATED(4.26, "APEX is deprecated. Destruction in future will be supported using Chaos Destruction.") FDestructibleSpecialHierarchyDepths`  
_L315-366_
- reflection: `USTRUCT()`
- desc: Special hierarchy depths for various behaviors.
- L326 _public member_ `int32 SupportDepth;` — `UPROPERTY(EditAnywhere, Category=DestructibleSpecialHierarchyDepths)` — The chunk hierarchy depth at which to create a support graph.  Higher depth levels give more detailed support, but will give a higher computational load.  Chunks below the support depth will never be supported.
- L332 _public member_ `int32 MinimumFractureDepth;` — `UPROPERTY(EditAnywhere, Category=DestructibleSpecialHierarchyDepths)` — The chunks will not be broken free below this depth.
- L339 _public member_ `bool bEnableDebris;` — `UPROPERTY(EditAnywhere, Category = DestructibleSpecialHierarchyDepths)` — Enables debris at a specific depth level. @see DebrisDepth
- L345 _public member_ `int32 DebrisDepth;` — `UPROPERTY(EditAnywhere, Category = DestructibleSpecialHierarchyDepths, meta = (UIMin = "0", editcondition = "bEnableDebris"))` — The hierarchy depth at which chunks are considered to be "debris."
- L354 _public member_ `int32 EssentialDepth;` — `UPROPERTY(EditAnywhere, Category=DestructibleSpecialHierarchyDepths, meta=(DisplayName = "Essential LOD Depth"))` — The chunk hierarchy depth up to which chunks will always be processed.  These chunks are considered to be essential either for gameplay or visually. The minimum value is 0, meaning the level 0 chunk is always considered essential. Default value is 0.
- L359 _public function_ `FDestructibleSpecialHierarchyDepths() : SupportDepth(0) , MinimumFractureDepth(0) , bEnableDebris(false) , DebrisDepth(-1) , EssentialDepth(0)` — Default constructor.

#### struct `FDestructibleParameters`  
`struct UE_DEPRECATED(4.26, "APEX is deprecated. Destruction in future will be supported using Chaos Destruction.") FDestructibleParameters`  
_L371-404_
- reflection: `USTRUCT()`
- desc: Parameters that apply to a destructible actor.
- L377 _public member_ `struct FDestructibleDamageParameters DamageParameters;` — `UPROPERTY(EditAnywhere, Category=DestructibleParameters)` — Parameters that pertain to chunk damage.  See DestructibleDamageParameters.
- L381 _public member_ `struct FDestructibleDebrisParameters DebrisParameters;` — `UPROPERTY(EditAnywhere, Category=DestructibleParameters)` — Parameters that pertain to chunk debris-level settings.  See DestructibleDebrisParameters.
- L385 _public member_ `struct FDestructibleAdvancedParameters AdvancedParameters;` — `UPROPERTY(EditAnywhere, Category=DestructibleParameters)` — Parameters that are less-often used.  See DestructibleAdvancedParameters.
- L389 _public member_ `struct FDestructibleSpecialHierarchyDepths SpecialHierarchyDepths;` — `UPROPERTY(EditAnywhere, Category=DestructibleParameters)` — Special hierarchy depths for various behaviors.
- L398 _public member_ `TArray<struct FDestructibleDepthParameters> DepthParameters;` — `UPROPERTY(EditAnywhere, editfixedsize, Category=DestructibleParameters)` — Parameters that apply to every chunk at a given level. the element [0] of the array applies to the level 0 (unfractured) chunk, element [1] applies to the level 1 chunks, etc.
- L403 _public member_ `struct FDestructibleParametersFlag Flags;` — `UPROPERTY(EditAnywhere, Category=DestructibleParameters)` — A collection of flags defined in DestructibleParametersFlag.

#### class `UDestructibleMesh`  
`class UE_DEPRECATED(4.26, "APEX is deprecated. Destruction in future will be supported using Chaos Destruction.") UDestructibleMesh : public USkeletalMesh`  
_L411-498_
- reflection: `UCLASS(hidecategories = (Object, Mesh, LevelOfDetail, Mirroring, Physics, Reimport, Clothing), MinimalAPI)`
- inherits: `USkeletalMesh`
- desc: Holds an APEX destructible asset as well as an associated USkeletalMesh.
- L417 _private member_ `struct FDestructibleParameters DefaultDestructibleParameters;` — `UPROPERTY(EditAnywhere, Category=DestructibleMesh)` — Parameters controlling the destruction behavior.
- L421 _private member_ `TArray<struct FFractureEffect> FractureEffects;` — `UPROPERTY(EditAnywhere, editfixedsize, Category=Effects)` — Fracture effects for each fracture level, unless overridden in the component.
- L427 _private member_ `TObjectPtr<class UDestructibleFractureSettings> FractureSettings;` — `UPROPERTY(instanced)` — Information used to author an NxDestructibleAsset
- L432 _private member_ `TObjectPtr<UStaticMesh> SourceStaticMesh;` — `UPROPERTY()` — Static mesh this destructible mesh is created from. Is nullptr if not created from a static mesh
- L436 _private member_ `FDateTime SourceSMImportTimestamp;` — `UPROPERTY()` — Timestamp of the source static meshes last import at the time this destruction mesh has been generated.
- L440 _private member_ `TArray<TObjectPtr<UStaticMesh>> FractureChunkMeshes;` — `UPROPERTY(Transient)` — Array of static meshes to build the fracture chunks from
- L447 _public prototype_ `virtual void PostLoad() override;`
- L448 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L449 _public prototype_ `virtual void FinishDestroy() override;`
- L451 _public prototype_ `virtual void PreEditChange(FProperty* PropertyAboutToChange) override;`
- L453 _public function_ `virtual bool HasCustomActorFactory() const`
- L458 _public function_ `virtual bool HasCustomActorReimportFactory() const`
- L467 _public prototype_ `void LoadDefaultDestructibleParametersFromApexAsset();` — Fills DefaultDestructibleParameters with parameters from the NxDestructibleAsset.
- L472 _public prototype_ `void CreateFractureSettings();` — Create DestructibleFractureSettings for this DestructibleMesh if it doesn't have one.
- L480 _public prototype_ `bool BuildFractureSettingsFromStaticMesh(UStaticMesh* StaticMesh);` — Imports FractureSettings data from a StaticMesh @param StaticMesh The StaticMesh to import @return true on success, false otherwise.
- L488 _public prototype_ `bool BuildFromStaticMesh(UStaticMesh& StaticMesh);` — Initializes this DestructibleMesh from a StaticMesh. @param StaticMesh The StaticMesh to import @return true on success, false otherwise.
- L497 _public prototype_ `bool SetupChunksFromStaticMeshes(const TArray<UStaticMesh*>& ChunkMeshes);` — Initialized this DestructibleMesh from the StaticMesh it was created from and the passed in ChunkMeshes to build the level 1 chunks from. @param ChunkMeshes Meshes to build the level1 chunks from @return true on success, false otherwise.

#### Free symbols / members of external scopes

- L16 _macro_ `#define WITH_DESTRUCTIBLE_DEPRECATION 0`
- L500 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDestructible, Warning, All);`
