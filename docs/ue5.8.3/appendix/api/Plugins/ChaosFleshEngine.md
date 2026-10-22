# Plugins / ChaosFleshEngine

- module root: `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshEngine`
- headers: 26; symbols: 723
- symbol kinds: class=29, delegate=3, enum=5, enumerator=15, function=98, member=270, namespace=9, prototype=241, struct=30, typedef=23
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: Chaos, ChaosCaching, ChaosCachingUSD, ChaosFlesh, ClothingSystemRuntimeCommon, ComputeFramework, CoreUObject, DataflowCore, DataflowEngine, DataflowSimulation, Engine, FieldSystemEngine, NetCore, OptimusCore, Projects, RHI, RenderCore, Renderer, USDClasses, USDUtilities, UnrealUSDWrapper
- PublicDependencyModuleNames: Core, DataflowCore, DataflowEngine, DataflowSimulation, ProceduralMeshComponent

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshEngine/Private/ChaosFlesh/ChaosFleshEnginePluginPrivate.h` (Private)


#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_STATS_GROUP(TEXT("ChaosFlesh"), STATGROUP_ChaosFlesh, STATCAT_`

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshEngine/Private/GEO/IFileStream.h` (Private)


#### class `IFileStreamBuf`  
`class IFileStreamBuf : public std::streambuf`  
_L15-30_
- inherits: `std::streambuf`
- desc: Stream buffer that uses \c IFileHandle for file access.
- L17 _private member_ `static const unsigned int buffer_size = 512;`
- L18 _private member_ `IFileHandle* istream;`
- L19 _private member_ `unsigned char in[buffer_size];`
- L20 _private member_ `unsigned char out[buffer_size];`
- L21 _private member_ `int total_read;`
- L22 _private member_ `bool valid;`
- L24 _public prototype_ `IFileStreamBuf(IFileHandle* istream);`
- L25 _public prototype_ `virtual ~IFileStreamBuf();`
- L27 _public prototype_ `int process();`
- L28 _public prototype_ `virtual int underflow();`
- L29 _public prototype_ `virtual int overflow(int c = EOF);`

#### class `IFileStream`  
`class IFileStream : public std::istream`  
_L35-41_
- inherits: `std::istream`
- desc: Input stream that uses \c IFileHandle for file access.
- L37 _private member_ `IFileStreamBuf buf;`
- L39 _public prototype_ `IFileStream(IFileHandle* istream);`
- L40 _public prototype_ `virtual ~IFileStream();`

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshEngine/Public/ChaosCache/FleshComponentCacheAdapter.h` (Public)


#### struct `Chaos::FFleshCacheAdapterCVarParams`  
`struct FFleshCacheAdapterCVarParams`  
_L32-38_
- L35 _public member_ `bool bWriteBinary = true;` — USD caching options
- L36 _public member_ `bool bNoClobber = true;`
- L37 _public member_ `int32 SaveFrequency = 10;`

#### class `Chaos::FFleshCacheAdapter`  
`class FFleshCacheAdapter : public FComponentCacheAdapter`  
_L43-132_
- inherits: `FComponentCacheAdapter`
- desc: Skeletal mesh cache adapter to be able to cache cloth simulation datas through the chaos cache system
- L46 _public typedef_ `typedef Chaos::Softs::FDeformableSolver FDeformableSolver;`
- L47 _public typedef_ `typedef Chaos::Softs::FPBDEvolution FEvolution;`
- L48 _public typedef_ `typedef Chaos::Softs::FSolverParticles FParticles;`
- L51 _public prototype_ `static FString GetUSDCacheDirectory(const FObservedComponent& InObserved);`
- L52 _public prototype_ `static FString GetUSDCacheFileName(const UDeformablePhysicsComponent* FleshComp);`
- L53 _public prototype_ `static FString GetUSDCacheFilePathRO(const FObservedComponent& InObserved, const UDeformablePhysicsComponent* FleshComp);`
- L54 _public prototype_ `static FString GetUSDCacheFilePathRW(const FObservedComponent& InObserved, const UDeformablePhysicsComponent* FleshComp);`
- L57 _public prototype_ `virtual ~FFleshCacheAdapter();`
- L60 _public prototype_ `virtual SupportType SupportsComponentClass(UClass* InComponentClass) const override;`
- L61 _public prototype_ `virtual UClass* GetDesiredClass() const override;`
- L62 _public prototype_ `virtual uint8 GetPriority() const override;`
- L63 _public prototype_ `virtual FGuid GetGuid() const override;`
- L64 _public prototype_ `virtual bool ValidForPlayback(UPrimitiveComponent* InComponent, UChaosCache* InCache) const override;`
- L65 _public function_ `virtual bool SupportsPlayWhileRecording() const override`
- L66 _public prototype_ `virtual Chaos::FPhysicsSolver* GetComponentSolver(UPrimitiveComponent* InComponent) const override;`
- L67 _public prototype_ `virtual Chaos::FPhysicsSolverEvents* BuildEventsSolver(UPrimitiveComponent* InComponent) const override;`
- L68 _public prototype_ `virtual void SetRestState(UPrimitiveComponent* InComponent, UChaosCache* InCache, const FTransform& InRootTransform, Chaos::FReal InTime) const override;`
- L69 _public prototype_ `virtual bool InitializeForRecord(UPrimitiveComponent* InComponent, FObservedComponent& InObserved) override;`
- L70 _public prototype_ `virtual bool InitializeForPlayback(UPrimitiveComponent* InComponent, FObservedComponent& InObserved, float InTime) override;`
- L71 _public prototype_ `virtual void InitializeForLoad(UPrimitiveComponent* InComponent, FObservedComponent& InObserved) override;`
- L72 _public prototype_ `virtual void Record_PostSolve(UPrimitiveComponent* InComp, const FTransform& InRootTransform, FPendingFrameWrite& OutFrame, Chaos::FReal InTime) const override;`
- L73 _public prototype_ `virtual void Playback_PreSolve(UPrimitiveComponent* InComponent, UChaosCache* InCache, Chaos::FReal InTime, FPlaybackTickRecord& TickRecord, TArray<TPBDRigidParticleHandle<Chaos::FReal, 3>*>& OutUpdatedRigids) const override;`
- L78 _public prototype_ `virtual void Finalize() override;`
- L82 _public prototype_ `static FDeformableSolver* GetDeformableSolver(UPrimitiveComponent* InComponent);` — Get the component deformable solver
- L85 _public prototype_ `static Chaos::FRange GetParticleRange(UPrimitiveComponent* InComponent, const int32 NumParticles);` — Get the particle indices range for the component in the evolution particles list on the physics thread
- L87 _public function_ `bool SupportsRestartSimulation() const override`
- L91 _private prototype_ `void LoadCacheAtTime(UPrimitiveComponent* PrimitiveComponent, Chaos::FReal TargetTime, const int32 NumParticles, const bool bNeedsRange, const TFunction<void(const int32, const int32, const FVector3f&, const FVector3f&, const float MuscleActivation)>& LoadFunction) const;` — Load the cache for a given component at a specific time
- L96 _private member_ `bool bReadOnly = false;`
- L97 _private member_ `bool bUseMonolith = true;` — move to cvarparams when value clips is an option
- L120 _private member_ `mutable TMap<UPrimitiveComponent*,FPrimitiveStage> PrimitiveStages;` — Per primitive stages datas
- L124 _private member_ `inline static const FName VelocityXName = TEXT("Vel`
- L125 _private member_ `inline static const FName VelocityYName = TEXT("Vel`
- L126 _private member_ `inline static const FName VelocityZName = TEXT("Vel`
- L127 _private member_ `inline static const FName PositionXName = TEXT("Pos`
- L128 _private member_ `inline static const FName PositionYName = TEXT("Pos`
- L129 _private member_ `inline static const FName PositionZName = TEXT("Pos`

#### struct `Chaos::FFleshCacheAdapter::FPrimitiveStage`  
`struct FPrimitiveStage`  
_L100-117_
- desc: Structure holding the per primitive stage datas
- L106 _public member_ `FString FilePath;` — Cache files are stored in a "SimCache" directory at the root of the project. File name is derived from flesh component name.
- L107 _public member_ `FString PrimPath;`
- L110 _public member_ `double MinTime = TNumericLimits<double>::Max();` — Min time in the usd stage
- L113 _public member_ `double MaxTime = TNumericLimits<double>::Lowest();` — Max time in the usd stage
- L116 _public member_ `UE::FUsdStage MonolithStage;` — USD Monolith stage used to load/record datas

#### Free symbols / members of external scopes

- L20 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogChaosFleshCache, Verbose, All);`
- L20 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogChaosFleshCache, Verbose, All);`
- L22 _namespace_ `namespace Chaos`
- L22 _namespace_ `namespace Softs` (scope `Chaos`)
- L30 _namespace_ `namespace Chaos`

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshEngine/Public/ChaosFlesh/ChaosDeformableCollisionsActor.h` (Public)


#### class `ADeformableCollisionsActor`  
`class ADeformableCollisionsActor : public AActor, public IDeformableInterface`  
_L19-47_
- reflection: `UCLASS()`
- inherits: `AActor,IDeformableInterface`
- L26 _public prototype_ `void EnableSimulation(ADeformableSolverActor* Actor);` — `UFUNCTION(BlueprintCallable, Category = "Physics")`
- L29 _public member_ `TObjectPtr<UDeformableCollisionsComponent> DeformableCollisionsComponent;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Physics")`
- L30 _public function_ `UDeformableCollisionsComponent* GetCollisionsComponent() const`
- L33 _public member_ `TObjectPtr<ADeformableSolverActor> PrimarySolver;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics", meta = (DisplayPriority = 1))`
- L36 _public member_ `TArray<TObjectPtr<AStaticMeshActor>> StaticCollisions;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics", meta = (DisplayPriority = 2))`
- L39 _public member_ `TArray < TObjectPtr<AStaticMeshActor> > AddedBodies;`
- L40 _public member_ `TArray < TObjectPtr<AStaticMeshActor> > RemovedBodies;`
- L41 _public member_ `TArray < TObjectPtr<AStaticMeshActor> > PreEditChangeCollisionBodies;`
- L42 _public member_ `ADeformableSolverActor* PreEditChangePrimarySolver = nullptr;`
- L43 _public prototype_ `virtual void PreEditChange(FProperty* PropertyThatWillChange) override;`
- L44 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L45 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshEngine/Public/ChaosFlesh/ChaosDeformableCollisionsComponent.h` (Public)


#### class `UDeformableCollisionsComponent`  
`class UDeformableCollisionsComponent : public UDeformablePhysicsComponent`  
_L19-49_
- reflection: `UCLASS(meta = (BlueprintSpawnableComponent))`
- inherits: `UDeformablePhysicsComponent`
- desc: UDeformableCollisionsComponent
- L24 _public typedef_ `typedef Chaos::Softs::FDataMapValue FDataMapValue;`
- L25 _public typedef_ `typedef Chaos::Softs::FThreadingProxy FThreadingProxy;`
- L26 _public typedef_ `typedef Chaos::Softs::FCollisionManagerProxy FCollisionThreadingProxy;`
- L28 _public function_ `~UDeformableCollisionsComponent()`
- L31 _public prototype_ `virtual FThreadingProxy* NewProxy() override;` — Simulation Interface
- L32 _public prototype_ `virtual FDataMapValue NewDeformableData() override;`
- L35 _public prototype_ `void AddStaticMeshComponent(UStaticMeshComponent* StaticMeshComponent);` — `UFUNCTION(BlueprintCallable, Category = "Physics")`
- L38 _public prototype_ `void RemoveStaticMeshComponent(UStaticMeshComponent* StaticMeshComponent);` — `UFUNCTION(BlueprintCallable, Category = "Physics")`
- L41 _public member_ `TArray<TObjectPtr<UStaticMeshComponent>> CollisionBodies;` — `UPROPERTY(BlueprintReadOnly, Category = "Physics")`
- L44 _protected member_ `TArray<UStaticMeshComponent*> RemovedBodies;`
- L45 _protected member_ `TArray<UStaticMeshComponent*> AddedBodies;`
- L47 _protected member_ `TMap<TObjectPtr<UObject>, FThreadingProxy*> CollisionsMap;`
- L48 _protected member_ `TMap<TObjectPtr<UStaticMeshComponent>, TArray<FTransform>> CollisionBodiesPrevXf;`

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshEngine/Public/ChaosFlesh/ChaosDeformableConstraintsActor.h` (Public)


#### class `ADeformableConstraintsActor`  
`class ADeformableConstraintsActor : public AActor, public IDeformableInterface`  
_L18-56_
- reflection: `UCLASS()`
- inherits: `AActor,IDeformableInterface`
- L25 _public prototype_ `void EnableSimulation(ADeformableSolverActor* Actor);` — `UFUNCTION(BlueprintCallable, Category = "Physics")`
- L28 _public member_ `TObjectPtr<UDeformableConstraintsComponent> DeformableConstraintsComponent;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Physics")`
- L29 _public function_ `UDeformableConstraintsComponent* GetConstraintsComponent() const`
- L32 _public member_ `TObjectPtr<ADeformableSolverActor> PrimarySolver;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics", meta = (DisplayPriority = 1))`
- L35 _public member_ `TArray<TObjectPtr<AFleshActor>> SourceBodies;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics", meta = (DisplayPriority = 2))`
- L38 _public member_ `TArray<TObjectPtr<AFleshActor>> TargetBodies;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics", meta = (DisplayPriority = 2))`
- L42 _public member_ `TArray < TObjectPtr<AFleshActor> > AddedSourceBodies;`
- L43 _public member_ `TArray < TObjectPtr<AFleshActor> > RemovedSourceBodies;`
- L45 _public member_ `TArray < TObjectPtr<AFleshActor> > AddedTargetBodies;`
- L46 _public member_ `TArray < TObjectPtr<AFleshActor> > RemovedTargetBodies;`
- L48 _public member_ `TArray < TObjectPtr<AFleshActor> > PreEditChangeSourceBodies;`
- L49 _public member_ `TArray < TObjectPtr<AFleshActor> > PreEditChangeTargetBodies;`
- L51 _public member_ `ADeformableSolverActor* PreEditChangePrimarySolver = nullptr;`
- L52 _public prototype_ `virtual void PreEditChange(FProperty* PropertyThatWillChange) override;`
- L53 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L54 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshEngine/Public/ChaosFlesh/ChaosDeformableConstraintsComponent.h` (Public)


#### enum `EDeformableConstraintType`  
`enum EDeformableConstraintType : uint8`  
_L16-21_
- desc: ENUM()
- L18 _public enumerator_ `Kinematic`
- L19 _public enumerator_ `LinearSpring`
- L20 _public enumerator_ `MAX`

#### struct `FDeformableConstraintParameters`  
`struct FDeformableConstraintParameters`  
_L25-51_
- reflection: `USTRUCT(BlueprintType)`
- L29 _public function_ `FDeformableConstraintParameters(float InStiffness = 100000.f, float InDamping = 1.f, EDeformableConstraintType InType = EDeformableConstraintType::Kinematic) : Type(InType) , Stiffness(InStiffness) , Damping(InDamping)`
- L37 _public member_ `EDeformableConstraintType Type;` — `UPROPERTY(EditAnywhere)`
- L40 _public member_ `float Stiffness = 100000.f;` — `UPROPERTY(EditAnywhere, Category = "Constraint")`
- L43 _public member_ `float Damping = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Constraint")`
- L45 _public function_ `Chaos::Softs::FDeformableConstraintParameters ToChaos()`

#### struct `FConstraintObject`  
`struct FConstraintObject`  
_L54-88_
- reflection: `USTRUCT(BlueprintType)`
- L58 _public function_ `FConstraintObject( TObjectPtr<UFleshComponent> InSource = nullptr, TObjectPtr<UFleshComponent> InTarget = nullptr, FDeformableConstraintParameters InParameters = FDeformableConstraintParameters()) : Source(InSource) , Target(InTarget) , Parameters(InParameters)`
- L68 _public member_ `TObjectPtr<UFleshComponent> Source;` — `UPROPERTY(EditAnywhere, Category = "Constraint")`
- L71 _public member_ `TObjectPtr<UFleshComponent> Target;` — `UPROPERTY(EditAnywhere, Category = "Constraint")`
- L74 _public member_ `FDeformableConstraintParameters Parameters;` — `UPROPERTY(EditAnywhere, Category = "Constraint")`
- L76 _public function_ `Chaos::Softs::FConstraintObjectKey ToChaos()`
- L84 _public function_ `bool operator==(const FConstraintObject& Other) const`

#### class `UDeformableConstraintsComponent`  
`class UDeformableConstraintsComponent : public UDeformablePhysicsComponent`  
_L94-132_
- reflection: `UCLASS(meta = (BlueprintSpawnableComponent))`
- inherits: `UDeformablePhysicsComponent`
- desc: UDeformableConstraintsComponent
- L99 _public typedef_ `typedef Chaos::Softs::FDataMapValue FDataMapValue;`
- L100 _public typedef_ `typedef Chaos::Softs::FThreadingProxy FThreadingProxy;`
- L101 _public typedef_ `typedef Chaos::Softs::FConstraintManagerProxy FConstraintThreadingProxy;`
- L102 _public typedef_ `typedef Chaos::Softs::FConstraintObjectKey FConstraintObjectKey;`
- L104 _public function_ `~UDeformableConstraintsComponent()`
- L107 _public prototype_ `virtual FThreadingProxy* NewProxy() override;` — Simulation Interface
- L108 _public prototype_ `virtual FDataMapValue NewDeformableData() override;`
- L111 _public prototype_ `void AddConstrainedBodies( UFleshComponent* SourceComponent, UFleshComponent* TargetComponent, FDeformableConstraintParameters InParameters);` — `UFUNCTION(BlueprintCallable, Category = "Physics")`
- L117 _public prototype_ `void RemoveConstrainedBodies( UFleshComponent* SourceComponent, UFleshComponent* TargetComponent, FDeformableConstraintParameters InParameters);` — `UFUNCTION(BlueprintCallable, Category = "Physics")`
- L123 _public member_ `TArray<FConstraintObject> Constraints;` — `UPROPERTY(BlueprintReadOnly, Category = "Physics")`
- L126 _protected prototype_ `bool IsValid(const FConstraintObject&) const;`
- L128 _protected member_ `TArray<FConstraintObject> RemovedConstraints;`
- L129 _protected member_ `TArray<FConstraintObject> AddedConstraints;`
- L131 _protected member_ `TMap<FConstraintObjectKey, FThreadingProxy*> ConstraintsMap;`

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshEngine/Public/ChaosFlesh/ChaosDeformableGPUBuffers.h` (Public)


#### class `UE::ChaosDeformable::FFloatArrayBufferWithSRV`  
`class FFloatArrayBufferWithSRV : public FVertexBufferWithSRV`  
_L12-36_
- inherits: `FVertexBufferWithSRV`
- desc: Floating point GPU buffer.
- L15 _public function_ `void SetBufferName(const FString& InBufferName)`
- L17 _public prototype_ `void Init(const float* InArray, const int32 Num);`
- L18 _public function_ `void Init(const TArray<float>& InArray)`
- L19 _public function_ `void Init(TArray<float>&& InArray)`
- L21 _public function_ `int32 GetNumValues() const`
- L22 _public prototype_ `uint32 GetBufferSize() const;`
- L25 _public function_ `void RetainLocalMemory()` — Retain local memory buffer for reuse, rather than reallocating.
- L28 _public prototype_ `void InitRHI(FRHICommandListBase& RHICmdList) override;` — FRenderResource overrides
- L29 _public function_ `FString GetFriendlyName() const override`
- L32 _private member_ `bool bEmptyArray = true;`
- L33 _private member_ `int32 NumValues = INDEX_NONE;`
- L34 _private member_ `FString BufferName;`
- L35 _private member_ `TArray<float> Array;`

#### class `UE::ChaosDeformable::FHalfArrayBufferWithSRV`  
`class FHalfArrayBufferWithSRV : public FVertexBufferWithSRV`  
_L41-64_
- inherits: `FVertexBufferWithSRV`
- desc: Floating point GPU buffer converting float to Half/FFloat16.
- L44 _public function_ `void SetBufferName(const FString& InBufferName)`
- L46 _public prototype_ `void Init(const FFloat16* InArray, const int32 Num);`
- L47 _public function_ `void Init(const TArray<FFloat16>& InArray)`
- L48 _public prototype_ `void Init(const float* InArray, const int32 Num);`
- L49 _public prototype_ `void Init(const TArray<float>& InArray);`
- L50 _public function_ `void Init(const FVector3f* InArray, const int32 Num)`
- L51 _public function_ `void Init(const FVector4f* InArray, const int32 Num)`
- L53 _public function_ `int32 GetNumValues() const`
- L54 _public prototype_ `uint32 GetBufferSize() const;`
- L57 _public prototype_ `void InitRHI(FRHICommandListBase& RHICmdList) override;` — FRenderResource overrides
- L58 _public function_ `FString GetFriendlyName() const override`
- L61 _private member_ `int32 NumValues = INDEX_NONE;`
- L62 _private member_ `FString BufferName;`
- L63 _private member_ `TArray<FFloat16> Array;`

#### class `UE::ChaosDeformable::FIndexArrayBufferWithSRV`  
`class FIndexArrayBufferWithSRV : public FVertexBufferWithSRV`  
_L69-102_
- inherits: `FVertexBufferWithSRV`
- desc: Integral GPU buffer compacting int32 to the smallest possible of uint8, uint16, or uint32.
- L72 _public function_ `void SetBufferName(const FString& InBufferName)`
- L75 _public prototype_ `void Init(const int32* InArray, const int32 Num);` — Convert float to uint8 with clamping, and optionaly shifting via \p MultOffset.
- L76 _public prototype_ `void Init(const uint32* InArray, const int32 Num);`
- L77 _public function_ `void Init(const TArray<int32>& InArray)`
- L78 _public function_ `void Init(const FIntVector2* InArray, const int32 Num)`
- L79 _public function_ `void Init(const FIntVector3* InArray, const int32 Num)`
- L80 _public function_ `void Init(const FIntVector4* InArray, const int32 Num)`
- L81 _public function_ `void Init(const TArray<FIntVector4>& InArray)`
- L83 _public function_ `void Force32BitPacking()`
- L85 _public function_ `int32 GetNumValues() const`
- L86 _public function_ `int32 GetDataStride() const`
- L87 _public function_ `int32 GetOffset() const`
- L88 _public prototype_ `uint32 GetBufferSize() const;`
- L91 _public prototype_ `void InitRHI(FRHICommandListBase& RHICmdList) override;` — FRenderResource overrides
- L92 _public function_ `FString GetFriendlyName() const override`
- L95 _private member_ `bool bUint8 = false;`
- L96 _private member_ `bool bUint16 = false;`
- L97 _private member_ `bool bForce32 = false;`
- L98 _private member_ `int32 Offset = 0;`
- L99 _private member_ `int32 NumValues = INDEX_NONE;`
- L100 _private member_ `FString BufferName;`
- L101 _private member_ `TArray<uint32> Array;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ChaosDeformable` (scope `UE`)

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshEngine/Public/ChaosFlesh/ChaosDeformableGameplayComponent.h` (Public)


#### struct `FRigBoundRayCasts`  
`struct FRigBoundRayCasts`  
_L16-38_
- reflection: `USTRUCT(BlueprintType)`
- L21 _public member_ `bool bEnableRigBoundRaycasts = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics")`
- L24 _public member_ `int32 MaxNumTests = 5;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics")`
- L27 _public member_ `bool bTestDownOnly = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics")`
- L30 _public member_ `float TestRange = 0.5f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics")`
- L34 _public member_ `TArray<TWeakObjectPtr<UPrimitiveComponent>> EnvironmentCollisionsSkipList;` — `UPROPERTY(EditAnywhere, Category = "Physics")` — Objects to skip if hit during \c DetectEnvironmentCollisions().
- L37 _public member_ `TEnumAsByte<ECollisionChannel> CollisionChannel = ECC_WorldStatic;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics")`

#### struct `FGameplayColllisions`  
`struct FGameplayColllisions`  
_L42-49_
- reflection: `USTRUCT(BlueprintType)`
- L47 _public member_ `FRigBoundRayCasts RigBoundRayCasts;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics")`

#### class `UDeformableGameplayComponent`  
`class UDeformableGameplayComponent : public UDeformableTetrahedralComponent`  
_L55-92_
- reflection: `UCLASS(meta = (BlueprintSpawnableComponent))`
- inherits: `UDeformableTetrahedralComponent`
- desc: UDeformableGameplayComponent
- L60 _public prototype_ `~UDeformableGameplayComponent();`
- L63 _public prototype_ `virtual void PreSolverUpdate() override;`
- L82 _public prototype_ `void DetectEnvironmentCollisions(const int32 MaxNumTests = 100, const bool bTestDownOnly = true, const float TestRange = 0.0, const ECollisionChannel CollisionChannel = ECollisionChannel::ECC_PhysicsBody);` — DetectEnvironmentCollisions Do raycasts against the scene and feed the results into transient constraints in the solver. Setup data for this method is initialized in the FAuthorSceneCollisionCandidates dataflow node, stored in the rest collection. The TargetDeformationSkeleton on the rest collection is used for the origin of the raycasts. \p MaxNumTests is the upper limit on the number of scene line tests. \p bTestDownOnly culls line tests that are not in the "down" direction. \p TestRange indicates how close to "down" tests need to be; 1 means only vectors pointing straight down are tested, 0.5 would include any vector about 45 degrees from straight down, 0.0 means any vector pointing down at all, and negative values up to -1 would include vectors pointing up. \p CollisionChannel denotes which scene objects to collide against.
- L86 _public member_ `FGameplayColllisions GameplayColllisions;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics", DisplayName = "Collisions", meta = (DisplayPriority = 10))`
- L91 _private member_ `TSet<int32> EnvCollisionsPreviousHits;`

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshEngine/Public/ChaosFlesh/ChaosDeformablePhysicsComponent.h` (Public)


#### class `UDeformablePhysicsComponent`  
`class UDeformablePhysicsComponent : public UPrimitiveComponent, public IDeformableInterface`  
_L21-75_
- reflection: `UCLASS(meta = (BlueprintSpawnableComponent))`
- inherits: `UPrimitiveComponent,IDeformableInterface`
- desc: UDeformablePhysicsComponent
- L26 _public typedef_ `typedef Chaos::Softs::FDeformableSolver FDeformableSolver;`
- L27 _public typedef_ `typedef Chaos::Softs::FThreadingProxy FThreadingProxy;`
- L28 _public typedef_ `typedef Chaos::Softs::FDataMapValue FDataMapValue;`
- L30 _public function_ `~UDeformablePhysicsComponent()`
- L33 _public prototype_ `void EnableSimulation(UDeformableSolverComponent* DeformableSolverComponent);` — `UFUNCTION(BlueprintCallable, Category = "Physics")`
- L36 _public prototype_ `void DisableSimulation();` — `UFUNCTION(BlueprintCallable, Category = "Physics")`
- L39 _public prototype_ `void EnableSimulationFromActor(ADeformableSolverActor* DeformableSolverActor);` — `UFUNCTION(BlueprintCallable, Category = "Physics")`
- L41 _public function_ `virtual FThreadingProxy* NewProxy()`
- L42 _public prototype_ `virtual void AddProxy(Chaos::Softs::FDeformableSolver::FGameThreadAccess& GameThreadSolver);`
- L43 _public prototype_ `virtual void RemoveProxy(Chaos::Softs::FDeformableSolver::FGameThreadAccess& GameThreadSolver);`
- L44 _public function_ `virtual void PreSolverUpdate()`
- L45 _public function_ `virtual FDataMapValue NewDeformableData()`
- L46 _public function_ `virtual void UpdateFromSimulation(const FDataMapValue* SimulationBuffer)`
- L47 _public function_ `virtual FDataMapValue WriteRestartDataToSimulation()`
- L49 _public prototype_ `virtual void OnCreatePhysicsState() override;`
- L50 _public prototype_ `virtual void OnDestroyPhysicsState() override;`
- L51 _public prototype_ `virtual bool ShouldCreatePhysicsState() const override;`
- L52 _public prototype_ `virtual bool HasValidPhysicsState() const override;`
- L55 _public prototype_ `UDeformableSolverComponent* GetDeformableSolver();` — PrimarySolver
- L56 _public prototype_ `const UDeformableSolverComponent* GetDeformableSolver() const;`
- L63 _public member_ `TSoftObjectPtr<UDeformableSolverComponent> PrimarySolverComponent;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics", meta = (DisplayPriority = 2))` — Primary solver component in which this flesh component has been registered. Soft object ptr since the UDeformablePhysicsComponent is stored in the chaos cache which requires soft ref in order to record itself from another thread
- L65 _public function_ `const FThreadingProxy* GetPhysicsProxy() const`
- L66 _public function_ `FThreadingProxy* GetPhysicsProxy()`
- L69 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L73 _protected member_ `FThreadingProxy* PhysicsProxy = nullptr;`

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshEngine/Public/ChaosFlesh/ChaosDeformableSolverActor.h` (Public)


#### class `ADeformableSolverActor`  
`class ADeformableSolverActor : public AActor, public IDeformableInterface`  
_L17-42_
- reflection: `UCLASS()`
- inherits: `AActor,IDeformableInterface`
- L23 _public function_ `UDeformableSolverComponent* GetDeformableSolverComponent()`
- L24 _public function_ `const UDeformableSolverComponent* GetDeformableSolverComponent() const`
- L27 _public member_ `TObjectPtr<UDeformableSolverComponent> SolverComponent = nullptr;` — `UPROPERTY(Category = "Physics", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))`
- L33 _public member_ `TObjectPtr<UBillboardComponent> SpriteComponent;` — `UPROPERTY()` — Display icon in the editor
- L36 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L40 _private prototype_ `void CreateBillboardIcon(const FObjectInitializer& ObjectInitializer);`

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshEngine/Public/ChaosFlesh/ChaosDeformableSolverComponent.h` (Public)


#### struct `FConnectedObjectsGroup`  
`struct FConnectedObjectsGroup`  
_L21-27_
- reflection: `USTRUCT(BlueprintType)`
- L26 _public member_ `TArray< TObjectPtr<UDeformablePhysicsComponent> > DeformableComponents;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ConnectedObjects", meta = (EditCondition = "false"))`

#### struct `FDataflowFleshSolverProxy`  
`struct FDataflowFleshSolverProxy : public FDataflowPhysicsSolverProxy`  
_L30-61_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FDataflowPhysicsSolverProxy`
- L34 _public function_ `FDataflowFleshSolverProxy(Chaos::Softs::FDeformableSolverProperties InProp = Chaos::Softs::FDeformableSolverProperties()) : FDataflowPhysicsSolverProxy()`
- L38 _public prototype_ `virtual ~FDataflowFleshSolverProxy() override = default;`
- L41 _public function_ `virtual void AdvanceSolverDatas(const float DeltaTime) override`
- L46 _public function_ `virtual float GetTimeStep() override`
- L51 _public function_ `virtual bool IsValid() const override`
- L53 _public function_ `virtual const UScriptStruct* GetScriptStruct() const override`
- L60 _public member_ `TUniquePtr<Chaos::Softs::FDeformableSolver> Solver;` — Chaos deformable solver that will be used in the component

#### struct `TStructOpsTypeTraits`  
`template <> struct TStructOpsTypeTraits<FDataflowFleshSolverProxy> : public TStructOpsTypeTraitsBase2<FDataflowFleshSolverProxy>`  
_L64-67_
- inherits: `TStructOpsTypeTraitsBase2<FDataflowFleshSolverProxy>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
`enum`  
_L66-66_

#### class `UDeformableSolverComponent`  
`class UDeformableSolverComponent : public USceneComponent, public IDeformableInterface, public IDataflowPhysicsSolverInterface`  
_L73-179_
- reflection: `UCLASS(meta = (BlueprintSpawnableComponent))`
- inherits: `USceneComponent,IDeformableInterface,IDataflowPhysicsSolverInterface`
- desc: UDeformableSolverComponent
- L78 _public typedef_ `typedef Chaos::Softs::FThreadingProxy FThreadingProxy;`
- L79 _public typedef_ `typedef Chaos::Softs::FFleshThreadingProxy FFleshThreadingProxy;`
- L80 _public typedef_ `typedef Chaos::Softs::FDeformablePackage FDeformablePackage;`
- L81 _public typedef_ `typedef Chaos::Softs::FDataMapValue FDataMapValue;`
- L82 _public typedef_ `typedef Chaos::Softs::FDeformableSolver FDeformableSolver;`
- L84 _public prototype_ `~UDeformableSolverComponent();`
- L85 _public prototype_ `void UpdateTickGroup();`
- L88 _public function_ `virtual FString GetSimulationName() const override`
- L89 _public function_ `virtual FDataflowSimulationAsset& GetSimulationAsset() override`
- L90 _public function_ `virtual const FDataflowSimulationAsset& GetSimulationAsset() const override`
- L91 _public function_ `virtual FDataflowSimulationProxy* GetSimulationProxy() override`
- L92 _public function_ `virtual const FDataflowSimulationProxy* GetSimulationProxy() const override`
- L93 _public prototype_ `virtual void BuildSimulationProxy() override;`
- L94 _public prototype_ `virtual void ResetSimulationProxy() override;`
- L95 _public prototype_ `virtual void WriteToSimulation(const float DeltaTime, const bool bAsyncTask) override;`
- L96 _public prototype_ `virtual void ReadFromSimulation(const float DeltaTime, const bool bAsyncTask) override;`
- L97 _public prototype_ `virtual void ReadRestartData() override;`
- L102 _public prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;`
- L107 _public function_ `virtual bool ShouldCreatePhysicsState() const override`
- L108 _public prototype_ `virtual void BeginPlay() override;`
- L109 _public prototype_ `virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;`
- L110 _public prototype_ `virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;`
- L114 _public prototype_ `FDeformableSolver::FGameThreadAccess GameThreadAccess();` — Game thread access to the solver proxy
- L117 _public prototype_ `FDeformableSolver::FPhysicsThreadAccess PhysicsThreadAccess();` — Physics thread access to the solver proxy
- L119 _public prototype_ `bool IsSimulating(UDeformablePhysicsComponent*) const;`
- L120 _public prototype_ `bool IsSimulatable() const;`
- L121 _public prototype_ `void AddDeformableProxy(UDeformablePhysicsComponent* InComponent);`
- L122 _public prototype_ `void RemoveDeformableProxy(UDeformablePhysicsComponent* InComponent);`
- L123 _public prototype_ `void Simulate(float DeltaTime);`
- L124 _public function_ `void SetSimulationTicking(const bool InSimulationTicking)`
- L127 _public prototype_ `void UpdateDeformableEndTickState(bool bRegister);` — Callback to trigger the deformable update after the simulation
- L131 _public prototype_ `void ResetSimulationProperties(const FSolverTimingGroup& TimingGroup, const FSolverEvolutionGroup& EvolutionGroup, FSolverCollisionsGroup CollisionsGroup, FSolverConstraintsGroup ConstraintsGroup, FSolverForcesGroup ForcesGroup, FSolverDebuggingGroup DebuggingGroup, FSolverMuscleActivationGroup MuscleActivationGroup);` — `UFUNCTION(CallInEditor, BlueprintCallable, Category = "Physics")` — Stop the simulation, and keep the cloth in its last pose.
- L137 _public member_ `FDataflowSimulationAsset SimulationAsset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics", meta=(EditConditionHides), AdvancedDisplay)` — Solver dataflow asset used to advance in time
- L141 _public member_ `FConnectedObjectsGroup ConnectedObjects;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Physics", meta = (EditCondition = "false"))` — Properties : Do NOT place ungrouped properties in this class
- L144 _public member_ `FSolverTimingGroup SolverTiming;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Physics")`
- L147 _public member_ `FSolverEvolutionGroup SolverEvolution;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Physics")`
- L150 _public member_ `FSolverCollisionsGroup SolverCollisions;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Physics")`
- L153 _public member_ `FSolverConstraintsGroup SolverConstraints;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Physics")`
- L156 _public member_ `FSolverForcesGroup SolverForces;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Physics")`
- L159 _public member_ `FSolverDebuggingGroup SolverDebugging;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Physics")`
- L162 _public member_ `FSolverMuscleActivationGroup SolverMuscleActivation;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Physics")`
- L165 _public member_ `FDataflowFleshSolverProxy FleshSolverProxy;` — Simulation Variables
- L168 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L174 _protected member_ `FGraphEventRef ParallelDeformableTask;` — Ref for the deformable solvers parallel task, so we can detect whether or not a sim is running
- L175 _protected member_ `FDeformableEndTickFunction DeformableEndTickFunction;`
- L178 _protected member_ `bool bSimulationTicking = true;` — Boolean to check if we can tick the simulation

#### Free symbols / members of external scopes

- L66 _enumerator_ `enum { WithCopy = false };` (scope `TStructOpsTypeTraits::__anon2f777b380103`)

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshEngine/Public/ChaosFlesh/ChaosDeformableSolverGroups.h` (Public)


#### struct `FSolverTimingGroup`  
`struct FSolverTimingGroup`  
_L9-31_
- reflection: `USTRUCT(BlueprintType)`
- L14 _public member_ `int32 NumSubSteps = 2;` — `UPROPERTY(EditAnywhere, Category = "SolverTiming")`
- L17 _public member_ `int32 NumSolverIterations = 5;` — `UPROPERTY(EditAnywhere, Category = "SolverTiming")`
- L20 _public member_ `bool FixTimeStep = false;` — `UPROPERTY(EditAnywhere, Category = "SolverTiming")`
- L23 _public member_ `float TimeStepSize = 0.05f;` — `UPROPERTY(EditAnywhere, Category = "SolverTiming")`
- L26 _public member_ `bool bDoThreadedAdvance = true;` — `UPROPERTY(EditAnywhere, Category = "SolverTiming")`
- L30 _public member_ `EDeformableExecutionModel ExecutionModel = EDeformableExecutionModel::Chaos_Deformable_PostPhysics;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SolverTiming")` — ObjectType defines how to initialize the rigid objects state, Kinematic, Sleeping, Dynamic.

#### struct `FSolverDebuggingGroup`  
`struct FSolverDebuggingGroup`  
_L34-40_
- reflection: `USTRUCT(BlueprintType)`
- L39 _public member_ `bool CacheToFile = false;` — `UPROPERTY(EditAnywhere, Category = "Physics")`

#### struct `FSolverQuasistaticsGroup`  
`struct FSolverQuasistaticsGroup`  
_L43-49_
- reflection: `USTRUCT(BlueprintType)`
- L48 _public member_ `bool bDoQuasistatics = false;` — `UPROPERTY(EditAnywhere, Category = "Quasistatics")`

#### struct `FSolverEvolutionGroup`  
`struct FSolverEvolutionGroup`  
_L52-59_
- reflection: `USTRUCT(BlueprintType)`
- L57 _public member_ `FSolverQuasistaticsGroup SolverQuasistatics;` — `UPROPERTY(EditAnywhere, Category = "Evolution")`

#### struct `FSolverGridBasedCollisionsGroup`  
`struct FSolverGridBasedCollisionsGroup`  
_L62-71_
- reflection: `USTRUCT(BlueprintType)`
- L67 _public member_ `bool bUseGridBasedConstraints = false;` — `UPROPERTY(EditAnywhere, Category = "GridBasedCollisions")`
- L70 _public member_ `float GridDx = 25.;` — `UPROPERTY(EditAnywhere, Category = "GridBasedCollisions")`

#### struct `FInComponentSpringCollisionGroup`  
`struct FInComponentSpringCollisionGroup`  
_L74-85_
- reflection: `USTRUCT(BlueprintType)`
- L80 _public member_ `bool bDoInComponentSpringCollision = false;` — `UPROPERTY(EditAnywhere, Category = "InComponentSpringCollision")` — If uses in-component spring self-collision
- L84 _public member_ `int32 NRingExcluded = 1;` — `UPROPERTY(EditAnywhere, Category = "InComponentSpringCollision")` — N ring to exclude for in-component spring self-collision

#### struct `FSpringCollisionGroup`  
`struct FSpringCollisionGroup`  
_L88-115_
- reflection: `USTRUCT(BlueprintType)`
- L94 _public member_ `bool bDoSpringCollision = false;` — `UPROPERTY(EditAnywhere, Category = "SpringCollision")` — If uses component-component spring collision
- L98 _public member_ `FInComponentSpringCollisionGroup InComponentSpringCollision;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SpringCollision")` — In-component spring self collision detection parameters
- L102 _public member_ `float CollisionSearchRadius = 0.f;` — `UPROPERTY(EditAnywhere, Category = "SpringCollision")` — Search radius for point triangle collision pairs
- L106 _public member_ `float SpringCollisionStiffness = 500.f;` — `UPROPERTY(EditAnywhere, Category = "SpringCollision")` — Collision spring stiffness; larger value will stop penetration better
- L110 _public member_ `bool bAllowSliding = true;` — `UPROPERTY(EditAnywhere, Category = "SpringCollision")` — Anisotropic springs will allow sliding on the triangle
- L114 _public member_ `bool bCollideWithFullmesh = true;` — `UPROPERTY(EditAnywhere, Category = "SpringCollision")` — Do self collision with kinematic triangles as well

#### struct `FSphereRepulsionGroup`  
`struct FSphereRepulsionGroup`  
_L118-133_
- reflection: `USTRUCT(BlueprintType)`
- L124 _public member_ `bool bDoSphereRepulsion = false;` — `UPROPERTY(EditAnywhere, Category = "SphereRepulsion")` — If uses sphere repulsion for collision
- L128 _public member_ `float SphereRepulsionRadius = 0.f;` — `UPROPERTY(EditAnywhere, Category = "SphereRepulsion")` — Search radius for repulsion pairs
- L132 _public member_ `float SphereRepulsionStiffness = 500.f;` — `UPROPERTY(EditAnywhere, Category = "SphereRepulsion")` — Stiffness for sphere repulsion

#### struct `FSolverGaussSeidelConstraintsGroup`  
`struct FSolverGaussSeidelConstraintsGroup`  
_L136-167_
- reflection: `USTRUCT(BlueprintType)`
- L142 _public member_ `bool bUseGaussSeidelConstraints = false;` — `UPROPERTY(EditAnywhere, Category = "GaussSeidelConstraints")` — Enable the Gauss Seidel solver instead of the existing XPBD.
- L146 _public member_ `bool bUseGSNeohookean = false;` — `UPROPERTY(EditAnywhere, Category = "GaussSeidelConstraints")` — Enable another model that runs simulation faster.
- L150 _public member_ `bool bUseSOR = true;` — `UPROPERTY(EditAnywhere, Category = "GaussSeidelConstraints")` — Enable acceleration technique for Gauss Seidel solver to make simulation look better within a limited budget.
- L154 _public member_ `float OmegaSOR = 1.6f;` — `UPROPERTY(EditAnywhere, Category = "GaussSeidelConstraints")` — Acceleration related parameter. Tune it down if simulation becomes unstable.
- L158 _public member_ `bool bEnableDynamicSprings = true;` — `UPROPERTY(EditAnywhere, Category = "GaussSeidelConstraints")` — Enable dynamic springs controlled by constraint manager.
- L162 _public member_ `FSpringCollisionGroup SpringCollision;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GaussSeidelConstraints")` — Component-component collision detection radius and stiffness
- L166 _public member_ `FSphereRepulsionGroup SphereRepulsion;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GaussSeidelConstraints")` — Sphere repulsion parameters

#### struct `FSolverCollisionsGroup`  
`struct FSolverCollisionsGroup`  
_L170-179_
- reflection: `USTRUCT(BlueprintType)`
- L175 _public member_ `bool bUseFloor = true;` — `UPROPERTY(EditAnywhere, Category = "Physics")`

#### struct `FSolverCorotatedConstraintsGroup`  
`struct FSolverCorotatedConstraintsGroup`  
_L182-194_
- reflection: `USTRUCT(BlueprintType)`
- L187 _public member_ `bool bEnableCorotatedConstraint = true;` — `UPROPERTY(EditAnywhere, Category = "Corotated")`
- L190 _public member_ `bool bDoBlended = false;` — `UPROPERTY(EditAnywhere, Category = "Corotated")`
- L193 _public member_ `float BlendedZeta = 0;` — `UPROPERTY(EditAnywhere, Category = "Corotated")`

#### struct `FSolverConstraintsGroup`  
`struct FSolverConstraintsGroup`  
_L197-213_
- reflection: `USTRUCT(BlueprintType)`
- L202 _public member_ `bool bEnablePositionTargets = true;` — `UPROPERTY(EditAnywhere, Category = "Constraints")`
- L205 _public member_ `bool bEnableKinematics = true;` — `UPROPERTY(EditAnywhere, Category = "Constraints")`
- L208 _public member_ `FSolverCorotatedConstraintsGroup CorotatedConstraints;` — `UPROPERTY(EditAnywhere, Category = "Constraints")`
- L212 _public member_ `FSolverGaussSeidelConstraintsGroup GaussSeidelConstraints;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Constraints")` — These are options for another solver.

#### struct `FSolverForcesGroup`  
`struct FSolverForcesGroup`  
_L216-238_
- reflection: `USTRUCT(BlueprintType)`
- L222 _public member_ `float YoungModulus = 100000;` — `UE_DEPRECATED(5.6, "YoungModulus has been deprecated.")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Please use SetFleshDefaultProperties dataflow node to set up vertex stiffness."))`
- L226 _public member_ `float Damping = 0;` — `UE_DEPRECATED(5.6, "Damping has been deprecated.")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Please use SetFleshDefaultProperties dataflow node to set up vertex damping."))`
- L229 _public member_ `bool bEnableGravity = true;` — `UPROPERTY(EditAnywhere, Category = "Forces")`
- L232 _public prototype_ `FSolverForcesGroup() = default;`
- L233 _public prototype_ `FSolverForcesGroup(const FSolverForcesGroup&) = default;`
- L234 _public prototype_ `FSolverForcesGroup(FSolverForcesGroup&&) = default;`
- L235 _public prototype_ `FSolverForcesGroup& operator=(const FSolverForcesGroup&) = default;`
- L236 _public prototype_ `FSolverForcesGroup& operator=(FSolverForcesGroup&&) = default;`

#### struct `FSolverMuscleActivationGroup`  
`struct FSolverMuscleActivationGroup`  
_L241-263_
- reflection: `USTRUCT(BlueprintType)`
- L247 _public member_ `bool bDoMuscleActivation = false;` — `UPROPERTY(EditAnywhere, Category = "MuscleActivation", DisplayName = "Do Length Based Muscle Activation")` — Muscle activation is driven by origin-insertion length. Check SetMuscleActivationParameter for more info.
- L251 _public member_ `bool bOverrideMuscleActivationWithAnimatedCurves = false;` — `UPROPERTY(EditAnywhere, Category = "MuscleActivation")` — Override muscle activation with animation curves. Check ReadSkeletalMeshCurves node for more info.
- L254 _public function_ `void SetDoLengthBasedMuscleActivation(bool bInDoMuscleActivation)`
- L255 _public function_ `bool GetDoLengthBasedMuscleActivation() const`
- L256 _public prototype_ `FSolverMuscleActivationGroup() = default;`
- L257 _public prototype_ `~FSolverMuscleActivationGroup() = default;`
- L258 _public prototype_ `FSolverMuscleActivationGroup(const FSolverMuscleActivationGroup&) = default;`
- L259 _public prototype_ `FSolverMuscleActivationGroup(FSolverMuscleActivationGroup&&) = default;`
- L260 _public prototype_ `FSolverMuscleActivationGroup& operator=(const FSolverMuscleActivationGroup&) = default;`
- L261 _public prototype_ `FSolverMuscleActivationGroup& operator=(FSolverMuscleActivationGroup&&) = default;`

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshEngine/Public/ChaosFlesh/ChaosDeformableSolverThreading.h` (Public)


#### class `FParallelDeformableTask`  
`class FParallelDeformableTask`  
_L14-36_
- L16 _private member_ `UDeformableSolverComponent* DeformableSolverComponent;`
- L17 _private member_ `float DeltaTime;`
- L20 _public function_ `FParallelDeformableTask(UDeformableSolverComponent* InDeformableSolverComponent, float InDeltaTime) : DeformableSolverComponent(InDeformableSolverComponent) , DeltaTime(InDeltaTime)`
- L26 _public function_ `TStatId GetStatId() const`
- L31 _public prototype_ `static ENamedThreads::Type GetDesiredThread();`
- L33 _public prototype_ `static ESubsequentsMode::Type GetSubsequentsMode();`
- L35 _public prototype_ `void DoTask(ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent);`

#### struct `FDeformableEndTickFunction`  
`struct FDeformableEndTickFunction : public FTickFunction`  
_L43-61_
- reflection: `USTRUCT()`
- inherits: `FTickFunction`
- desc: Tick function that does post physics work on deformable components. This executes in EndPhysics (after physics is done)
- L47 _public member_ `UDeformableSolverComponent* DeformableSolverComponent = nullptr;`
- L56 _public prototype_ `virtual void ExecuteTick(float DeltaTime, enum ELevelTick TickType, ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent) override;` — Abstract function to execute the tick. @param DeltaTime - frame time to advance, in seconds. @param TickType - kind of tick for this frame. @param CurrentThread - thread we are executing on, useful to pass along as new tasks are created. @param MyCompletionGraphEvent - completion event for this task. Useful for holding the completetion of this task until certain child tasks are complete.
- L58 _public prototype_ `virtual FString DiagnosticMessage() override;` — Abstract function to describe this tick. Used to print messages about illegal cycles in the dependency graph.
- L60 _public prototype_ `virtual FName DiagnosticContext(bool bDetailed) override;` — Function used to describe this tick for active tick reporting.

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FDeformableEndTickFunction> : public TStructOpsTypeTraitsBase2<FDeformableEndTickFunction>`  
_L64-70_
- inherits: `TStructOpsTypeTraitsBase2<FDeformableEndTickFunction>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L67-69_

#### Free symbols / members of external scopes

- L68 _enumerator_ `WithCopy = false` (scope `TStructOpsTypeTraits::__anonc134dddb0103`)

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshEngine/Public/ChaosFlesh/ChaosDeformableTetrahedralComponent.h` (Public)


#### enum `ChaosDeformableBindingOption`  
`enum ChaosDeformableBindingOption : uint8`  
_L29-37_
- reflection: `UENUM()`
- desc: Options for binding positions query.
- L31 _public enumerator_ `WorldPos UMETA(DisplayName = "World Positions")`
- L32 _public enumerator_ `WorldDelta UMETA(DisplayName = "World Deltas")`
- L33 _public enumerator_ `ComponentPos UMETA(DisplayName = "Component Positions")`
- L34 _public enumerator_ `ComponentDelta UMETA(DisplayName = "Component Deltas")`
- L35 _public enumerator_ `BonePos UMETA(DisplayName = "Bone Positions")`
- L36 _public enumerator_ `BoneDelta UMETA(DisplayName = "Bone Deltas")`

#### struct `FFleshSimulationSpaceGroup`  
`struct FFleshSimulationSpaceGroup`  
_L41-62_
- reflection: `USTRUCT(BlueprintType)`
- L50 _public member_ `FName SimSpaceBoneName;` — `UPROPERTY(EditAnywhere, Category = "Physics", meta = (GetOptions = "GetSimSpaceBoneNameOptions", EditCondition = "SimSpace == ChaosDeformableSimSpace::Bone"))` — Bone from the associated skeletal mesh (indicated by RestCollection.TargetSkeletalMesh) to use as the space the sim runs in.
- L54 _public member_ `TEnumAsByte<ChaosDeformableSimSpace> SimSpace = ChaosDeformableSimSpace::World;` — `UPROPERTY(EditAnywhere, Category = "Physics")` — Space the simulation will run in.
- L58 _public member_ `TObjectPtr<USkeletalMesh> SimSpaceSkeletalMesh;` — `UPROPERTY()` — The skeletal mesh to use pull the \c SimSpaceBoneName from.
- L60 _public member_ `int32 SimSpaceTransformIndex = INDEX_NONE;`
- L61 _public member_ `int32 SimSpaceTransformGlobalIndex = INDEX_NONE;`

#### struct `FBodyForcesGroup`  
`struct FBodyForcesGroup`  
_L66-84_
- reflection: `USTRUCT(BlueprintType)`
- L71 _public member_ `bool bApplyGravity = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics")`
- L74 _public member_ `float DampingMultiplier = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))`
- L77 _public member_ `float StiffnessMultiplier = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))`
- L80 _public member_ `float IncompressibilityMultiplier = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))`
- L83 _public member_ `float InflationMultiplier = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))`

#### class `UDeformableTetrahedralComponent`  
`class UDeformableTetrahedralComponent : public UDeformablePhysicsComponent, public IDataflowGeometryCachable`  
_L90-236_
- reflection: `UCLASS(meta = (BlueprintSpawnableComponent))`
- inherits: `UDeformablePhysicsComponent,IDataflowGeometryCachable`
- desc: UDeformableTetrahedralComponent
- L95 _public typedef_ `typedef Chaos::Softs::FFleshThreadingProxy FFleshThreadingProxy;`
- L97 _public prototype_ `~UDeformableTetrahedralComponent();`
- L100 _public prototype_ `virtual void BeginPlay() override;` — USceneComponent Interface
- L101 _public prototype_ `virtual void OnRegister() override;`
- L102 _public prototype_ `virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;`
- L103 _public prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;`
- L104 _public prototype_ `void UpdateLocalBounds();`
- L105 _public prototype_ `virtual void EndPlay(const EEndPlayReason::Type ReasonEnd) override;`
- L106 _public prototype_ `void Invalidate();`
- L112 _public function_ `Chaos::Softs::FChaosFleshDeformableGPUManager& GetGPUBufferManager()` — GPU Interface
- L115 _public prototype_ `virtual FThreadingProxy* NewProxy() override;` — Simulation Interface
- L116 _public prototype_ `virtual FDataMapValue NewDeformableData() override;`
- L117 _public prototype_ `virtual void UpdateFromSimulation(const FDataMapValue* SimulationBuffer) override;`
- L118 _public prototype_ `virtual FDataMapValue WriteRestartDataToSimulation() override;`
- L122 _public prototype_ `void SetRestCollection(const UFleshAsset * InRestCollection);` — `UFUNCTION(BlueprintCallable, Category = "Physics")` — RestCollection
- L125 _public function_ `const UFleshAsset* GetRestCollection() const` — `UFUNCTION(BlueprintCallable, Category = "Physics")`
- L128 _public prototype_ `void ResetDynamicCollection();` — DynamicCollection
- L129 _public function_ `UFleshDynamicAsset* GetDynamicCollection()`
- L130 _public function_ `const UFleshDynamicAsset* GetDynamicCollection() const`
- L133 _public prototype_ `void ResetSimulationCollection();` — SimulationCollection
- L134 _public function_ `USimulationAsset* GetSimulationCollection()`
- L135 _public function_ `const USimulationAsset* GetSimulationCollection() const`
- L139 _public prototype_ `TArray<FVector> GetSkeletalMeshBindingPositions(const USkeletalMesh* InSkeletalMesh) const;` — `UFUNCTION(BlueprintCallable, Category = "Physics", meta = (DeprecatedFunction, DeprecationMessage = "Use GetSkeletalMeshEmbeddedPositions() instead."))` — @deprecated Use GetSkeletalMeshEmbeddedPositions() instead.
- L142 _public prototype_ `virtual TArray<FVector3f> GetGeometryCachePositions(const USkeletalMesh* SkeletalMesh) const override;`
- L143 _public prototype_ `virtual TArray<FVector3f> GetGeometryCachePositions(const UStaticMesh* StaticMesh) const override;`
- L145 _public prototype_ `virtual TOptional<TArray<int32>> GetMeshImportVertexMap(const USkinnedAsset& SkinnedMeshAsset) const override;`
- L147 _public prototype_ `virtual bool IsSkeletalMeshAnimationCompatible(const USkeletalMeshComponent* SkeletalMeshComponent) const override;`
- L150 _public function_ `virtual void SetMaterial(int32 Index, UMaterialInterface* InMaterial) override`
- L162 _public prototype_ `TArray<FVector> GetSkeletalMeshEmbeddedPositions(const ChaosDeformableBindingOption Format, const FTransform TargetDeformationSkeletonOffset, const FName TargetBone = "", const float SimulationBlendWeight = 1.f) const;` — `UFUNCTION(BlueprintCallable, Category = "Physics")` — Get the current positions of the transformation hierarchy from \c TargetDeformationSkeleton, deformed by the tetrahedral mesh.  Results can be in world space postions/deltas, component space positions/deltas, or bone space positions/deltas.  If a bone space is desired \p TargetBone must indicate which bone to use. TargetDeformationSkeletonOffset is an offset transform that moves the \c TargetDeformationSkeleton to be co-located with the flesh mesh.
- L165 _public member_ `FFleshSimulationSpaceGroup SimulationSpace;` — `UPROPERTY(EditAnywhere, Category = "Physics", meta = (DisplayPriority = 10))`
- L168 _public member_ `FBodyForcesGroup BodyForces;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics", meta = (DisplayPriority = 10))`
- L171 _public member_ `float MassMultiplier = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0", DisplayPriority = 100))`
- L174 _public member_ `TObjectPtr<UProceduralMeshComponent> Mesh;` — `UPROPERTY(EditAnywhere, Category = "Rendering")`
- L177 _public member_ `TObjectPtr<UMaterialInterface> Material = nullptr;` — `UPROPERTY(BlueprintReadWrite, Category = "Rendering")`
- L180 _public member_ `TArray<int32> HideTetrahedra;` — `UPROPERTY(EditAnywhere, Category = "Rendering")`
- L185 _private member_ `TObjectPtr<const UFleshAsset> RestCollection;` — `UPROPERTY(EditAnywhere, Category = "Physics", meta = (DisplayPriority = 1))` — FleshAsset that describes the simulation rest state.
- L189 _private member_ `TObjectPtr<UFleshDynamicAsset> DynamicCollection;` — `UPROPERTY()` — Current simulation state.
- L193 _private member_ `TObjectPtr<USimulationAsset> SimulationCollection;` — `UPROPERTY()` — Simulator input
- L197 _private prototype_ `TArray<FString> GetSimSpaceBoneNameOptions() const;` — `UFUNCTION(CallInEditor)` — Returns a list of bone names from the currently selected skeletal mesh.
- L202 _private prototype_ `bool UpdateSimSpaceTransformIndex();` — Update \c SimSpaceSkeletalMesh and \c SimSpaceTransformIndex according to \c RestCollection->TargetSkeletalMesh and SimSpaceBoneName. \ret \c true if a valid sim space transform is found.
- L206 _private prototype_ `FTransform GetSimSpaceRestTransform() const;` — Return the rest transform to be used as the simulation space. \c UpdateSimSpaceTransformIndex() must be called prior to calling this function.
- L220 _private member_ `FFleshRenderMesh* RenderMesh = nullptr;`
- L221 _private prototype_ `void RenderProceduralMesh();`
- L222 _private prototype_ `void ResetProceduralMesh();`
- L224 _private member_ `bool bBoundsNeedsUpdate = true;`
- L225 _private member_ `FBoxSphereBounds BoundingBox = FBoxSphereBounds(ForceInitToZero);`
- L227 _private member_ `FTransform PrevTransform = FTransform::Identity;`
- L229 _private prototype_ `TArray<FVector> GetSkeletalMeshEmbeddedPositionsInternal(const ChaosDeformableBindingOption Format, const FTransform TargetDeformationSkeletonOffset, const FName TargetBone = "", const float SimulationBlendWeight = 1.f, TArray<bool>* OutInfluence = nullptr) const;`
- L230 _private prototype_ `TArray<FVector> GetEmbeddedPositionsInternal(const TArray<FVector>& InPositions, const FName SkeletalMeshName, const float SimulationBlendWeight = 1.f, TArray<bool>* OutInfluence = nullptr) const;`
- L231 _private prototype_ `TArray<FVector> GetSkeletalMeshBindingPositionsInternal(const USkeletalMesh* InSkeletalMesh, TArray<bool>* OutInfluence = nullptr) const;`
- L232 _private prototype_ `void DebugDrawSkeletalMeshBindingPositions() const;`
- L235 _private member_ `Chaos::Softs::FChaosFleshDeformableGPUManager GPUBufferManager;` — FChaosDeformableTetrahedralSceneProxy* RenderProxy = nullptr;

#### struct `UDeformableTetrahedralComponent::FFleshRenderMesh`  
`struct FFleshRenderMesh`  
_L211-219_
- desc: Render the Procedural Mesh
- L213 _public member_ `TArray<FVector> Vertices;`
- L214 _public member_ `TArray<int32> Triangles;`
- L215 _public member_ `TArray<FVector> Normals;`
- L216 _public member_ `TArray<FVector2D> UVs;`
- L217 _public member_ `TArray<FLinearColor> Colors;`
- L218 _public member_ `TArray<FProcMeshTangent> Tangents;`

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshEngine/Public/ChaosFlesh/ChaosDeformableTypes.h` (Public)


#### enum `EDeformableExecutionModel`  
`enum class EDeformableExecutionModel : uint8`  
_L12-19_
- reflection: `UENUM(BlueprintType)`
- L14 _public enumerator_ `Chaos_Deformable_PrePhysics UMETA(DisplayName = "Before Physics")`
- L15 _public enumerator_ `Chaos_Deformable_DuringPhysics UMETA(DisplayName = "During Physics")`
- L16 _public enumerator_ `Chaos_Deformable_PostPhysics UMETA(DisplayName = "After Physics")`
- L18 _public enumerator_ `Chaos_Max UMETA(Hidden)`

#### struct `FChaosEngineDeformableCVarParams`  
`struct FChaosEngineDeformableCVarParams`  
_L21-50_
- L23 _public member_ `bool bEnableDeformableSolver = true;`
- L25 _public member_ `bool bDoDrawSimulationMesh = true;`
- L27 _public member_ `bool bDoDrawSimulationMesh = false;`
- L29 _public member_ `bool bDoDrawSkeletalMeshBindingPositions = false;`
- L30 _public member_ `float DrawSkeletalMeshBindingPositionsSimulationBlendWeight = 1.f;`
- L31 _public member_ `bool bDoDrawSceneRaycasts = false;`
- L32 _public member_ `bool bDoDrawCandidateRaycasts = false;`
- L34 _public member_ `int32 EnvCollisionsLineTraceBatchSize = 10;`
- L36 _public member_ `bool bTestUnpacking = false;`
- L37 _public member_ `bool bTestSparseMappings = false;`
- L38 _public member_ `bool bTestCompressedIndexing = false;`
- L39 _public member_ `bool bUpdateGPUBuffersOnTick = true;`
- L41 _public function_ `bool IsDebugDrawingEnabled()`

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshEngine/Public/ChaosFlesh/ChaosFleshDeformerBufferManager.h` (Public)


#### class `Chaos::Softs::FChaosFleshDeformableGPUManager`  
`class FChaosFleshDeformableGPUManager`  
_L13-142_
- L99 _public prototype_ `FChaosFleshDeformableGPUManager();`
- L100 _public prototype_ `FChaosFleshDeformableGPUManager(UDeformableTetrahedralComponent* InComponent);`
- L101 _public prototype_ `virtual ~FChaosFleshDeformableGPUManager();`
- L103 _public prototype_ `void SetOwner(UDeformableTetrahedralComponent* InComponent);`
- L106 _public function_ `void RegisterGPUBufferConsumer(const void* ID) const` — Register a consumer of a buffer this class will manage.
- L108 _public prototype_ `void UnRegisterGPUBufferConsumer(const void* ID) const;` — Remove a registered consumer.
- L110 _public function_ `bool HasRegisteredGPUBufferConsumer() const` — Returns \c true if there's at least 1 registered consumer.
- L113 _public prototype_ `bool InitGPUBindingsBuffer(const void* ID, const FName MeshName, const int32 LodIndex, const bool ForceInit=false);` — Initialize the binding data for a render mesh. Will register \p ID as consumer. Returns success.
- L115 _public prototype_ `bool HasGPUBindingsBuffer(const void* ID, const FName MeshName, const int32 LodIndex) const;` — Returns true if we have a matching bindings buffer.
- L121 _public prototype_ `bool UpdateGPUBuffers();` — If a consumer has been registered, updates time varying data from the component's dynamic collection. Returns success.
- L124 _public prototype_ `const FBindingsBuffer* GetBindingsBuffer(const void* ID, const FName MeshName, const int32 LodIndex) const;` — Look up bindings data buffers associated with \p ID, \p MeshName, and \p LodIndex.
- L125 _public prototype_ `FBindingsBuffer* GetBindingsBuffer(const void* ID, const FName MeshName, const int32 LodIndex);`
- L128 _private member_ `UDeformableTetrahedralComponent* Component = nullptr;`
- L131 _private prototype_ `const FFleshCollection* GetRestCollection() const;` — Convenience functions
- L132 _private prototype_ `const TManagedArray<FVector3f>* GetRestVertexArray() const;`
- L133 _private prototype_ `const TManagedArray<FVector3f>* GetVertexArray() const;`
- L136 _private member_ `mutable TArray<const void*> GPUBufferConsumers;` — Consumers
- L139 _private typedef_ `typedef TTuple<void*, FName, int32> BufferId;` — Data tables
- L140 _private typedef_ `typedef TMap<BufferId, TSharedPtr<FBindingsBuffer>> IdToBuffers;`
- L141 _private member_ `IdToBuffers BufferTable;`

#### class `Chaos::Softs::FChaosFleshDeformableGPUManager::FBindingsBuffer`  
`class FBindingsBuffer`  
_L16-96_
- L19 _public prototype_ `FBindingsBuffer();`
- L20 _public prototype_ `~FBindingsBuffer();`
- L22 _public prototype_ `void SetOwnerName(const FName& OwnerName);`
- L25 _public prototype_ `bool InitData(const TManagedArrayAccessor<FIntVector4>* ParentsArray, const TManagedArrayAccessor<FVector4f>* WeightsArray, const TManagedArrayAccessor<FVector3f>* OffsetArray, const TManagedArrayAccessor<float>* MaskArray, const TManagedArray<FVector3f>* RestVerticesArray, const TManagedArray<FVector3f>* VerticesArray);` — Initialize GPU buffers.
- L31 _public prototype_ `bool UpdateVertices(const TArray<FVector3f>& DenseVertex);` — Update local sparse vertices buffer from dense vertices, and uploads to GPU. Returns \c true if \p DenseVertex differs from prior values.
- L33 _public function_ `UE::ChaosDeformable::FFloatArrayBufferWithSRV& GetRestVerticesBuffer()`
- L34 _public function_ `const UE::ChaosDeformable::FFloatArrayBufferWithSRV& GetRestVerticesBuffer() const`
- L36 _public function_ `UE::ChaosDeformable::FFloatArrayBufferWithSRV& GetVerticesBuffer()`
- L37 _public function_ `const UE::ChaosDeformable::FFloatArrayBufferWithSRV& GetVerticesBuffer() const`
- L39 _public function_ `UE::ChaosDeformable::FIndexArrayBufferWithSRV& GetParentsBuffer()`
- L40 _public function_ `const UE::ChaosDeformable::FIndexArrayBufferWithSRV& GetParentsBuffer() const`
- L42 _public function_ `UE::ChaosDeformable::FIndexArrayBufferWithSRV& GetVertsToParentsBuffer()`
- L43 _public function_ `const UE::ChaosDeformable::FIndexArrayBufferWithSRV& GetVertsToParentsBuffer() const`
- L45 _public function_ `UE::ChaosDeformable::FHalfArrayBufferWithSRV& GetWeightsBuffer()`
- L46 _public function_ `const UE::ChaosDeformable::FHalfArrayBufferWithSRV& GetWeightsBuffer() const`
- L48 _public function_ `UE::ChaosDeformable::FHalfArrayBufferWithSRV& GetOffsetsBuffer()`
- L49 _public function_ `const UE::ChaosDeformable::FHalfArrayBufferWithSRV& GetOffsetsBuffer() const`
- L51 _public function_ `UE::ChaosDeformable::FHalfArrayBufferWithSRV& GetMaskBuffer()`
- L52 _public function_ `const UE::ChaosDeformable::FHalfArrayBufferWithSRV& GetMaskBuffer() const`
- L60 _private prototype_ `bool UpdateSparseVertices(const TArray<FVector3f>& DenseVertexIn, TArray<FVector3f>& SparseVerticesIn) const;`
- L66 _private prototype_ `void InitCondensationMapping(const TManagedArrayAccessor<FIntVector4>& ParentsArray);` — Create a mapping that reduces the number of vertices referenced by the parents array, and the vertices required by culling unreferenced vertices.
- L69 _private prototype_ `void DestroyGPUBuffers();` — Release GPU resources.
- L72 _private member_ `FRenderCommandFence RenderResourceDestroyFence;` — Fence used in render thread cleanup on destruction.
- L75 _private member_ `UE::ChaosDeformable::FFloatArrayBufferWithSRV VerticesBuffer;` — Non-const
- L78 _private member_ `UE::ChaosDeformable::FFloatArrayBufferWithSRV RestVerticesBuffer;` — Const
- L79 _private member_ `UE::ChaosDeformable::FIndexArrayBufferWithSRV ParentsBuffer;`
- L80 _private member_ `UE::ChaosDeformable::FIndexArrayBufferWithSRV VertsToParentsBuffer;`
- L81 _private member_ `UE::ChaosDeformable::FHalfArrayBufferWithSRV WeightsBuffer;`
- L82 _private member_ `UE::ChaosDeformable::FHalfArrayBufferWithSRV OffsetsBuffer;`
- L83 _private member_ `UE::ChaosDeformable::FHalfArrayBufferWithSRV MaskBuffer;`
- L86 _private member_ `TArray<int32> SparseToDenseIndices;` — Sparse vertex index to dense (excludes -1) - maps dense vertices to SparseVertices.
- L88 _private member_ `TArray<uint32> VertsToSparseParents;` — For each render vertex, the corresponding sparse parent index.
- L90 _private member_ `TArray<FIntVector4> SparseParents;` — Sparse (unique) parents.
- L93 _private member_ `TArray<FVector3f> SparseRestVertices;` — Local buffer for sparse rest vertices.
- L95 _private member_ `TArray<FVector3f> SparseVertices;` — Local buffer for sparse time varying vertices.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Chaos`
- L11 _namespace_ `namespace Softs` (scope `Chaos`)

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshEngine/Public/ChaosFlesh/ChaosFleshEnginePlugin.h` (Public)


#### class `IChaosFleshEnginePlugin`  
`class IChaosFleshEnginePlugin : public IModuleInterface`  
_L13-38_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L24 _public function_ `static inline IChaosFleshEnginePlugin& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L34 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshEngine/Public/ChaosFlesh/FleshActor.h` (Public)


#### class `AFleshActor`  
`class AFleshActor : public AActor, public IDeformableInterface`  
_L18-41_
- reflection: `UCLASS()`
- inherits: `AActor,IDeformableInterface`
- L25 _public prototype_ `void EnableSimulation(ADeformableSolverActor* Actor);` — `UFUNCTION(BlueprintCallable, Category = "Physics")`
- L28 _public member_ `TObjectPtr<UFleshComponent> FleshComponent;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Physics")`
- L29 _public function_ `UFleshComponent* GetFleshComponent() const`
- L32 _public member_ `TObjectPtr<ADeformableSolverActor> PrimarySolver;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics", meta = (DisplayPriority = 1))`
- L35 _public member_ `ADeformableSolverActor* PreEditChangePrimarySolver = nullptr;`
- L36 _public prototype_ `virtual void PreEditChange(FProperty* PropertyThatWillChange) override;`
- L37 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L38 _public prototype_ `virtual bool GetReferencedContentObjects(TArray<UObject*>& Objects) const override;`
- L39 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshEngine/Public/ChaosFlesh/FleshAsset.h` (Public)


#### class `FFleshAssetEdit`  
`class FFleshAssetEdit`  
_L34-51_
- desc: FFleshAssetEdit Structured RestCollection access where the scope of the object controls serialization back into the dynamic collection
- L37 _public typedef_ `typedef TFunctionRef<void()> FPostEditFunctionCallback;`
- L43 _public prototype_ `FFleshAssetEdit(UFleshAsset* InAsset, FPostEditFunctionCallback InCallable);` — @param UFleshAsset				The FAsset to edit
- L44 _public prototype_ `~FFleshAssetEdit();`
- L46 _public prototype_ `FFleshCollection* GetFleshCollection();`
- L49 _private member_ `FPostEditFunctionCallback PostEditCallback;`
- L50 _private member_ `UFleshAsset* Asset;`

#### class `UFleshAsset`  
`class UFleshAsset : public UObject, public IDataflowContentOwner, public IDataflowInstanceInterface`  
_L60-241_
- reflection: `UCLASS(BlueprintType, customconstructor)`
- inherits: `UObject,IDataflowContentOwner,IDataflowInstanceInterface`
- desc: UFleshAsset (UObject) UObject wrapper for the FFleshAsset
- L81 _private member_ `TSharedPtr<FFleshCollection, ESPMode::ThreadSafe> FleshCollection;` — FleshCollection The FleshCollection stores all the user per-particle properties for the asset. This is used for simulation and artists configuration. Only edit the FleshCollection using its Edit object. For example; { FFleshAssetEdit EditObject = UFleshAsset->EditCollection(); if( TSharedPtr<FFleshCollection> FleshCollection = EditObject.GetFleshCollection() ) { } // the destructor of the edit object will perform invalidation. }
- L83 _private prototype_ `void PostEditCallback();`
- L87 _public prototype_ `UFleshAsset(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L91 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — Post edit change property
- L92 _public prototype_ `virtual void PostEditUndo() override;`
- L94 _public prototype_ `void PropagateTransformUpdateToComponents() const;` — Propogate the fact that transform have been updated to all components
- L95 _public prototype_ `void BuildResourceForRendering(FSkeletalMeshRenderData& OutSkeletalMeshRenderData) const;`
- L100 _public prototype_ `void SetCollection(FFleshCollection* InCollection);` — `UE_DEPRECATED(5.7, "Use SetFleshCollection instead")` — Editing the collection should only be through the edit object.
- L102 _public function_ `const FFleshCollection* GetCollection() const` — `UE_DEPRECATED(5.7, "Use GetFleshCollection instead")`
- L104 _public function_ `FFleshCollection* GetCollection()` — `UE_DEPRECATED(5.7, "Access to non-const FleshCollection is now deprecated, use SetFleshCollection to modify FleshCollection.")`
- L106 _public prototype_ `void SetFleshCollection(TUniquePtr<FFleshCollection>&& InCollection);`
- L107 _public function_ `TSharedPtr<const FFleshCollection> GetFleshCollection() const`
- L109 _public prototype_ `TArray<FSkeletalMaterial> GetMaterials() const;`
- L110 _public prototype_ `const FReferenceSkeleton& GetRefSkeleton() const;`
- L111 _public prototype_ `FGuid GetAssetGuid() const;`
- L113 _public prototype_ `TManagedArray<FVector3f>& GetPositions();`
- L114 _public prototype_ `const TManagedArray<FVector3f>* FindPositions() const;`
- L116 _public function_ `FFleshAssetEdit EditCollection() const`
- L121 _public prototype_ `void Serialize(FArchive& Ar);`
- L122 _public prototype_ `virtual void PostLoad() override;`
- L124 _public prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;`
- L127 _public prototype_ `virtual TObjectPtr<UDataflowBaseContent> CreateDataflowContent() override;`
- L128 _public prototype_ `virtual void WriteDataflowContent(const TObjectPtr<UDataflowBaseContent>& DataflowContent) const override;`
- L129 _public prototype_ `virtual void ReadDataflowContent(const TObjectPtr<UDataflowBaseContent>& DataflowContent) override;`
- L133 _public prototype_ `virtual const FDataflowInstance& GetDataflowInstance() const;`
- L134 _public prototype_ `virtual FDataflowInstance& GetDataflowInstance();`
- L145 _public member_ `TObjectPtr<UDataflow> DataflowAsset;` — `UE_DEPRECATED(5.8, "Direct set/get is no longer authorized, use SetDataflowAsset instead")` — `UPROPERTY(BlueprintReadWrite, BlueprintSetter = SetDataflowAsset, BlueprintGetter = GetDataflowAsset, Category = "Dataflow")` — this is deprecated data replaced with Setter and Getter but it is exposed to blueprint so we use the Setter/Getter to make sure the blueprint will use them
- L149 _public member_ `FString DataflowTerminal = "Fl` — `UE_DEPRECATED(5.8, "Direct set/get is no longer authorized, use SetDataflowTerminal instead")` — `UPROPERTY(BlueprintReadWrite, BlueprintSetter = SetDataflowTerminal, BlueprintGetter = GetDataflowTerminal, Category = "Dataflow")`
- L153 _public prototype_ `void SetDataflowAsset(UDataflow* InDataflowAsset);` — `UFUNCTION(BlueprintCallable, Category = "Dataflow")`
- L156 _public prototype_ `UDataflow* GetDataflowAsset() const;` — `UFUNCTION(BlueprintCallable, Category = "Dataflow")`
- L159 _public prototype_ `void SetDataflowTerminal(const FString& InDataflowTerminal);` — `UFUNCTION(BlueprintCallable, Category = "Dataflow")`
- L162 _public prototype_ `FString GetDataflowTerminal() const;` — `UFUNCTION(BlueprintCallable, Category = "Dataflow")`
- L165 _private prototype_ `void MigrateDeprecatedDataflowData();`
- L168 _private member_ `FDataflowInstance DataflowInstance;` — `UPROPERTY(EditAnywhere, Category = "Dataflow")`
- L172 _public member_ `TArray<FStringValuePair> Overrides;` — `UPROPERTY(EditAnywhere, Category = "Dataflow")`
- L178 _public member_ `TObjectPtr<USkeletalMesh> SkeletalMesh;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")` — SkeletalMesh
- L181 _public member_ `TObjectPtr<USkeleton> Skeleton;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")`
- L188 _public member_ `TObjectPtr<USkeletalMesh> TargetDeformationSkeleton;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering")` — Skeleton to use with the flesh deformer or \c GetSkeletalMeshEmbeddedPositions() on the flesh component. Bindings for this skeletal mesh must be stored in the rest collection.
- L192 _public member_ `TObjectPtr<UStaticMesh> StaticMesh;` — `UE_DEPRECATED(5.8, "FleshAsset StaticMesh property is deprecated, as it is not no longer used")` — `UPROPERTY()`
- L196 _public member_ `bool bRenderInEditor = true;` — `UPROPERTY(EditAnywhere, Category = "Render")`
- L200 _public member_ `TObjectPtr<class UThumbnailInfo> ThumbnailInfo;` — `UPROPERTY()` — Information for thumbnail rendering
- L212 _public member_ `TSoftObjectPtr<UAnimationAsset> PreviewAnimationAsset = nullptr;` — `UPROPERTY(DuplicateTransient, AssetRegistrySearchable)` — Animation asset used in this asset
- L215 _public member_ `FSolverTimingGroup PreviewSolverTiming;` — `UPROPERTY(DuplicateTransient, AssetRegistrySearchable)`
- L218 _public member_ `FSolverEvolutionGroup PreviewSolverEvolution;` — `UPROPERTY(DuplicateTransient, AssetRegistrySearchable)`
- L221 _public member_ `FSolverCollisionsGroup PreviewSolverCollisions;` — `UPROPERTY(DuplicateTransient, AssetRegistrySearchable)`
- L224 _public member_ `FSolverConstraintsGroup PreviewSolverConstraints;` — `UPROPERTY(DuplicateTransient, AssetRegistrySearchable)`
- L227 _public member_ `FSolverForcesGroup PreviewSolverForces;` — `UPROPERTY(DuplicateTransient, AssetRegistrySearchable)`
- L230 _public member_ `FSolverDebuggingGroup PreviewSolverDebugging;` — `UPROPERTY(DuplicateTransient, AssetRegistrySearchable)`
- L233 _public member_ `FSolverMuscleActivationGroup PreviewSolverMuscleActivation;` — `UPROPERTY(DuplicateTransient, AssetRegistrySearchable)`
- L240 _private member_ `FGuid AssetGuid = FGuid::NewGuid();` — `UPROPERTY()` — A unique identifier as used by the section rendering code.

#### class `UDataflowFleshContent`  
`class UDataflowFleshContent : public UDataflowSkeletalContent`  
_L248-286_
- reflection: `UCLASS()`
- inherits: `UDataflowSkeletalContent`
- desc: Dataflow content owning dataflow and solver properties that will be used to evaluate the graph
- L253 _public prototype_ `UDataflowFleshContent();`
- L254 _public function_ `virtual ~UDataflowFleshContent() override`
- L257 _public prototype_ `static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);`
- L260 _public prototype_ `virtual void SetActorProperties(TObjectPtr<AActor>& PreviewActor) const override;` — Set all the preview actor exposed properties
- L263 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L267 _public member_ `FSolverTimingGroup SolverTiming;` — `UPROPERTY(EditAnywhere, Category = "Preview", Transient, SkipSerialization)`
- L270 _public member_ `FSolverEvolutionGroup SolverEvolution;` — `UPROPERTY(EditAnywhere, Category = "Preview", Transient, SkipSerialization)`
- L273 _public member_ `FSolverCollisionsGroup SolverCollisions;` — `UPROPERTY(EditAnywhere, Category = "Preview", Transient, SkipSerialization)`
- L276 _public member_ `FSolverConstraintsGroup SolverConstraints;` — `UPROPERTY(EditAnywhere, Category = "Preview", Transient, SkipSerialization)`
- L279 _public member_ `FSolverForcesGroup SolverForces;` — `UPROPERTY(EditAnywhere, Category = "Preview", Transient, SkipSerialization)`
- L282 _public member_ `FSolverDebuggingGroup SolverDebugging;` — `UPROPERTY(EditAnywhere, Category = "Preview", Transient, SkipSerialization)`
- L285 _public member_ `FSolverMuscleActivationGroup SolverMuscleActivation;` — `UPROPERTY(EditAnywhere, Category = "Preview", Transient, SkipSerialization)`

#### Free symbols / members of external scopes

- L118 _function_ `return FFleshAssetEdit(ThisNC, [ThisNC]() {ThisNC->PostEditCallback(); });` (scope `UFleshAsset::EditCollection`)

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshEngine/Public/ChaosFlesh/FleshCollectionEngineUtility.h` (Public)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace ChaosFlesh`
- L14 _prototype_ `FString GetMeshId(const USkeletalMesh* SkeletalMesh, const bool bUseImportModel);` (scope `ChaosFlesh`)
- L16 _prototype_ `FString GetMeshId(const UStaticMesh* StaticMesh);` (scope `ChaosFlesh`)
- L18 _prototype_ `void BoundSurfacePositions( const FString& MeshId, const FFleshCollection* FleshCollection, const TManagedArray<FVector3f>* RestVertices, const TManagedArray<FVector3f>* SimulatedVertices, TArray<FVector3f>& OutPositions);` (scope `ChaosFlesh`)
- L25 _prototype_ `void BoundSurfacePositions( const USkeletalMesh* SkeletalMesh, const FFleshCollection* FleshCollection, const TManagedArray<FVector3f>* RestVertices, const TManagedArray<FVector3f>* SimulatedVertices, TArray<FVector3f>& OutPositions);` (scope `ChaosFlesh`)
- L32 _prototype_ `void BoundSurfacePositions( const UStaticMesh* StaticMesh, const FFleshCollection* FleshCollection, const TManagedArray<FVector3f>* RestVertices, const TManagedArray<FVector3f>* SimulatedVertices, TArray<FVector3f>& OutPositions);` (scope `ChaosFlesh`)

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshEngine/Public/ChaosFlesh/FleshComponent.h` (Public)


#### class `UFleshComponent`  
`class UFleshComponent : public UDeformableGameplayComponent`  
_L29-34_
- reflection: `UCLASS(meta = (BlueprintSpawnableComponent))`
- inherits: `UDeformableGameplayComponent`
- desc: FleshComponent

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshEngine/Public/ChaosFlesh/FleshDynamicAsset.h` (Public)


#### class `UFleshDynamicAsset`  
`class UFleshDynamicAsset : public UObject`  
_L23-51_
- reflection: `UCLASS(customconstructor)`
- inherits: `UObject`
- desc: UFleshDynamicAsset (UObject) UObject wrapper for the dynamic attributes from the tetrahedral simulation. FVectorArray Vertex = GetAttribute<FVector3f>("Vertex", VerticesGroup)
- L28 _public prototype_ `UFleshDynamicAsset(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L29 _public prototype_ `void Init();`
- L30 _public prototype_ `void Reset(const FManagedArrayCollection* InCopyFrom = nullptr);`
- L31 _public prototype_ `void ResetAttributesFrom(const FManagedArrayCollection* InCopyFrom);`
- L33 _public prototype_ `TManagedArray<FVector3f>& GetPositions();`
- L34 _public prototype_ `const TManagedArray<FVector3f>* FindPositions() const;`
- L35 _public prototype_ `TManagedArray<int32>& GetObjectState();`
- L36 _public prototype_ `TManagedArray<float>& GetActivations();`
- L37 _public prototype_ `const TManagedArray<float>* FindActivations() const;`
- L39 _public function_ `const FManagedArrayCollection* GetCollection() const`
- L40 _public function_ `FManagedArrayCollection* GetCollection()`
- L50 _private member_ `TSharedPtr<FManagedArrayCollection, ESPMode::ThreadSafe> DynamicCollection;` — FManagedArrayCollection The ManagedArrayCollection stores all the dynamic properties of the simulation. This is non-const data stored on the component.

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshEngine/Public/ChaosFlesh/SimulationAsset.h` (Public)


#### class `USimulationAsset`  
`class USimulationAsset : public UObject`  
_L18-42_
- reflection: `UCLASS(customconstructor)`
- inherits: `UObject`
- desc: USimulationAsset (UObject) UObject wrapper for the dynamic attributes that are inputs to the tetrahedral simulation.
- L23 _public prototype_ `USimulationAsset(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L24 _public prototype_ `void Init();`
- L25 _public prototype_ `void Reset(const FManagedArrayCollection* InCopyFrom = nullptr);`
- L26 _public prototype_ `void ResetAttributesFrom(const FManagedArrayCollection* InCopyFrom);`
- L28 _public prototype_ `TManagedArray<int32>& GetObjectState();`
- L30 _public function_ `const FManagedArrayCollection* GetCollection() const`
- L31 _public function_ `FManagedArrayCollection* GetCollection()`
- L41 _private member_ `TSharedPtr<FManagedArrayCollection, ESPMode::ThreadSafe> SimulationCollection;` — FManagedArrayCollection The ManagedArrayCollection stores all the dynamic properties for input to the simulation. This is non-const data stored on the component.

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshEngine/Public/DataInterfaces/DIFleshDeformer.h` (Public)


#### struct `FFleshDeformerParameters`  
`struct FFleshDeformerParameters`  
_L21-24_
- reflection: `USTRUCT()`

#### class `UDIFleshDeformer`  
`class UDIFleshDeformer : public UOptimusComputeDataInterface`  
_L31-59_
- reflection: `UCLASS(Category = ComputeFramework)`
- inherits: `UOptimusComputeDataInterface`
- desc: Compute Framework Data Interface for reading skeletal mesh and tetrahedral mesh bindings.
- L36 _public prototype_ `virtual ~UDIFleshDeformer();`
- L39 _public prototype_ `FString GetDisplayName() const override;`
- L40 _public prototype_ `TArray<FOptimusCDIPinDefinition> GetPinDefinitions() const override;`
- L41 _public prototype_ `TSubclassOf<UActorComponent> GetRequiredComponentClass() const override;`
- L45 _public function_ `TCHAR const* GetClassName() const override`
- L46 _public prototype_ `void GetSupportedInputs(TArray<FShaderFunctionDefinition>& OutFunctions) const override;`
- L47 _public prototype_ `void GetShaderParameters(TCHAR const* UID, FShaderParametersMetadataBuilder& InOutBuilder, FShaderParametersMetadataAllocations& InOutAllocations) const override;`
- L48 _public prototype_ `void GetPermutations(FComputeKernelPermutationVector& OutPermutationVector) const override;`
- L49 _public prototype_ `void GetShaderHash(FString& InOutKey) const override;`
- L50 _public prototype_ `void GetHLSL(FString& OutHLSL, FString const& InDataInterfaceName) const override;`
- L51 _public prototype_ `UComputeDataProvider* CreateDataProvider(TObjectPtr<UObject> InBinding, uint64 InInputMask, uint64 InOutputMask) const override;`
- L55 _public member_ `FFleshDeformerParameters FleshDeformerParameters;` — `UPROPERTY(EditAnywhere, Category = Deformer, meta = (ShowOnlyInnerProperties))`
- L58 _private member_ `mutable TWeakObjectPtr<UDeformableTetrahedralComponent> ProducerComponent;`

#### class `UDIFleshDeformerDataProvider`  
`class UDIFleshDeformerDataProvider : public UComputeDataProvider`  
_L63-83_
- reflection: `UCLASS(BlueprintType, editinlinenew, Category = ComputeFramework)`
- inherits: `UComputeDataProvider`
- desc: Compute Framework Data Provider for reading skeletal mesh.
- L69 _public member_ `TObjectPtr<USkinnedMeshComponent> SkinnedMesh = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Binding)`
- L72 _public member_ `TObjectPtr<UStaticMeshComponent> StaticMesh = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Binding)`
- L75 _public member_ `TObjectPtr<UDeformableTetrahedralComponent> FleshMesh = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Binding)`
- L78 _public member_ `FFleshDeformerParameters FleshDeformerParameters;` — `UPROPERTY()`
- L81 _public prototype_ `FComputeDataProviderRenderProxy* GetRenderProxy() override;`

#### class `FDIFleshDeformerProviderProxy`  
`class FDIFleshDeformerProviderProxy : public FComputeDataProviderRenderProxy`  
_L85-136_
- inherits: `FComputeDataProviderRenderProxy`
- L88 _public prototype_ `FDIFleshDeformerProviderProxy(USkinnedMeshComponent* SkinnedMeshComponentIn, UDeformableTetrahedralComponent* FleshComponentIn, const FFleshDeformerParameters& FleshDeformerParametersIn);`
- L91 _public prototype_ `bool IsValid(FValidationData const& InValidationData) const override;`
- L92 _public prototype_ `void GatherPermutations(FPermutationData& InOutPermutationData) const override;`
- L93 _public prototype_ `void AllocateResources(FRDGBuilder& GraphBuilder, FAllocationData const& InAllocationData) override;`
- L94 _public prototype_ `void GatherDispatchData(FDispatchData const& InDispatchData);`
- L98 _private typedef_ `using FParameters = FFleshDeformerDataInterfaceParameters;`
- L100 _private member_ `USkinnedMeshComponent* SkinnedMeshComponent = nullptr;`
- L101 _private member_ `FSceneInterface* SceneInterface = nullptr;`
- L102 _private member_ `FPrimitiveComponentId ComponentId;`
- L103 _private member_ `UDeformableTetrahedralComponent* FleshComponent = nullptr;`
- L105 _private member_ `FFleshDeformerParameters FleshDeformerParameters;`
- L107 _private member_ `int32 TetIndex = INDEX_NONE;`
- L108 _private member_ `FString MeshId;`
- L110 _private member_ `uint32 NumVertices = 0;`
- L112 _private member_ `uint32 NumTetRestVertices = 0;`
- L113 _private member_ `uint32 NumTetVertices = 0;`
- L115 _private member_ `uint32 NumParents = 0;`
- L116 _private member_ `uint32 NumWeights = 0;`
- L117 _private member_ `uint32 NumOffset = 0;`
- L118 _private member_ `uint32 NumMask = 0;`
- L120 _private member_ `FRDGBuffer* TetRestVertexBuffer = nullptr;`
- L121 _private member_ `FRDGBufferSRV* TetRestVertexBufferSRV = nullptr;`
- L122 _private member_ `FRDGBuffer* TetVertexBuffer = nullptr;`
- L123 _private member_ `FRDGBufferSRV* TetVertexBufferSRV = nullptr;`
- L125 _private member_ `FRDGBuffer* ParentsBuffer = nullptr;`
- L126 _private member_ `FRDGBufferSRV* ParentsBufferSRV = nullptr;`
- L127 _private member_ `FRDGBuffer* WeightsBuffer = nullptr;`
- L128 _private member_ `FRDGBufferSRV* WeightsBufferSRV = nullptr;`
- L129 _private member_ `FRDGBuffer* OffsetBuffer = nullptr;`
- L130 _private member_ `FRDGBufferSRV* OffsetBufferSRV = nullptr;`
- L131 _private member_ `FRDGBuffer* MaskBuffer = nullptr;`
- L132 _private member_ `FRDGBufferSRV* MaskBufferSRV = nullptr;`
- L134 _private member_ `float NullFloatBuffer = 0.0f;`
- L135 _private member_ `int32 NullIntBuffer = 0;`

#### Free symbols / members of external scopes

- L18 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogFleshDeformer, Verbose, All);`
- L18 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogFleshDeformer, Verbose, All);`

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshEngine/Public/GEO/GEO.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace ChaosFlesh`
- L11 _prototype_ `bool ReadGEO(const std::string& filename, TMap<FString, int32>& IntVars, TMap<FString, TArray<int32>>& IntVectorVars, TMap<FString, TArray<float>>& FloatVectorVars, TMap<FString, TPair<TArray<std::string>, TArray<int32>>>& IndexedStringVars, std::ostream* errorStream=nullptr);` (scope `ChaosFlesh`)
