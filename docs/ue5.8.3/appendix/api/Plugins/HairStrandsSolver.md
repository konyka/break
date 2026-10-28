# Plugins / HairStrandsSolver

- module root: `Plugins/Runtime/HairStrands/Source/HairStrandsSolver`
- headers: 4; symbols: 118
- symbol kinds: class=3, delegate=1, enum=1, enumerator=1, function=22, macro=1, member=41, namespace=2, prototype=41, struct=5
- PublicDependencyModuleNames: ChaosCaching, ComputeFramework, Core, CoreUObject, DataflowCore, DataflowEngine, DataflowSimulation, Engine, HairStrandsCore, OptimusCore, RHI, RenderCore

### `Plugins/Runtime/HairStrands/Source/HairStrandsSolver/Public/AddSolverDeformerNode.h` (Public)


#### struct `FAddSolverDeformerDataflowNode`  
`struct FAddSolverDeformerDataflowNode : public FDataflowSimulationNode`  
_L15-94_
- reflection: `USTRUCT(meta = (DataflowSimulation))`
- inherits: `FDataflowSimulationNode`
- desc: Add a graph deformer to the groom simulation
- L32 _public member_ `TArray<FDataflowSimulationProperty> PhysicsSolvers;` — `UPROPERTY(Transient, SkipSerialization, Meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "PhysicsSolvers"))` — Physics solvers to advance in time
- L36 _public member_ `FDataflowSimulationTime SimulationTime = FDataflowSimulationTime(0.0f,0.0f);` — `UPROPERTY(Transient, SkipSerialization, Meta = (DataflowInput))` — Delta time to use to advance the solver
- L42 _public member_ `TObjectPtr<UMeshDeformer> MeshDeformer = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Groom")` — Graph deformer solver the component is using. Declared as base UMeshDeformer to be compatible with the MeshDeformer property type customization (which asserts the picker's AllowedClass is assignable to the property class). Cast to UOptimusDeformer at use sites.
- L46 _public member_ `TArray<FDataflowNumericTypes> DeformerNumericInputs;` — `UPROPERTY()` — List of deformer numeric inputs that will appear in the option pins
- L50 _public member_ `TArray<FDataflowVectorTypes> DeformerVectorInputs;` — `UPROPERTY()` — List of deformer vector inputs that will appear in the option pins
- L54 _public member_ `TArray<FDataflowStringTypes> DeformerStringInputs;` — `UPROPERTY()` — List of deformer string inputs that will appear in the option pins
- L58 _public member_ `TArray<FDataflowBoolTypes> DeformerBoolInputs;` — `UPROPERTY()` — List of deformer bool inputs that will appear in the option pins
- L62 _public member_ `TArray<FDataflowTransformTypes> DeformerTransformInputs;` — `UPROPERTY()` — List of deformer transform inputs that will appear in the option pins
- L66 _public member_ `TArray<FDataflowNumericArrayTypes> DeformerNumericArrays;` — `UPROPERTY()` — List of deformer numeric arrays that will appear in the option pins
- L70 _public member_ `TArray<FDataflowVectorArrayTypes> DeformerVectorArrays;` — `UPROPERTY()` — List of deformer vector arrays that will appear in the option pins
- L74 _public member_ `TArray<FDataflowStringArrayTypes> DeformerStringArrays;` — `UPROPERTY()` — List of deformer string arrays that will appear in the option pins
- L78 _public member_ `TArray<FDataflowBoolArrayTypes> DeformerBoolArrays;` — `UPROPERTY()` — List of deformer bool arrays that will appear in the option pins
- L82 _public member_ `TArray<FDataflowTransformArrayTypes> DeformerTransformArrays;` — `UPROPERTY()` — List of deformer transform arrays that will appear in the option pins
- L85 _public prototype_ `virtual void EvaluateSimulation(UE::Dataflow::FDataflowSimulationContext& SimulationContext, const FDataflowOutput* Output) const override;`
- L86 _public prototype_ `virtual TArray<UE::Dataflow::FPin> AddPins() override;`
- L87 _public function_ `virtual bool CanAddPin() const override`
- L88 _public prototype_ `virtual TArray<UE::Dataflow::FPin> GetPinsToRemove() const override;`
- L89 _public function_ `virtual bool CanRemovePin() const override`
- L90 _public prototype_ `virtual void OnPinRemoved(const UE::Dataflow::FPin& Pin) override;`
- L91 _public prototype_ `virtual void OnInvalidate() override;`
- L92 _public prototype_ `virtual void PostSerialize(const FArchive& Ar) override;`

### `Plugins/Runtime/HairStrands/Source/HairStrandsSolver/Public/GroomCacheAdapter.h` (Public)


#### class `UE::Groom::FGroomCacheAdapter`  
`class FGroomCacheAdapter : public Chaos::FComponentCacheAdapter`  
_L17-81_
- inherits: `Chaos::FComponentCacheAdapter`
- desc: Groom cache adapter to be able to cache groom simulation data through the chaos cache system
- L21 _public prototype_ `virtual ~FGroomCacheAdapter();`
- L24 _public prototype_ `virtual SupportType SupportsComponentClass(UClass* InComponentClass) const override;`
- L25 _public prototype_ `virtual UClass* GetDesiredClass() const override;`
- L26 _public prototype_ `virtual uint8 GetPriority() const override;`
- L27 _public prototype_ `virtual FGuid GetGuid() const override;`
- L28 _public prototype_ `virtual void SetRestState(UPrimitiveComponent* InComponent, UChaosCache* InCache, const FTransform& InRootTransform, Chaos::FReal InTime) const override;`
- L29 _public prototype_ `virtual bool InitializeForRecord(UPrimitiveComponent* InComponent, FObservedComponent& InObserved) override;`
- L30 _public prototype_ `virtual bool InitializeForPlayback(UPrimitiveComponent* InComponent, FObservedComponent& InObserved, float InTime) override;`
- L31 _public prototype_ `virtual void InitializeForLoad(UPrimitiveComponent* InComponent, FObservedComponent& InObserved) override;`
- L32 _public prototype_ `virtual bool ValidForPlayback(UPrimitiveComponent* InComponent, UChaosCache* InCache) const override;`
- L33 _public prototype_ `virtual void Finalize() override;`
- L34 _public prototype_ `virtual Chaos::FPhysicsSolver* GetComponentSolver(UPrimitiveComponent* InComponent) const override;`
- L35 _public prototype_ `virtual Chaos::FPhysicsSolverEvents* BuildEventsSolver(UPrimitiveComponent* InComponent) const override;`
- L36 _public prototype_ `virtual void Record_PostSolve(UPrimitiveComponent* InComp, const FTransform& InRootTransform, FPendingFrameWrite& OutFrame, Chaos::FReal InTime) const override;`
- L37 _public function_ `virtual void Playback_PreSolve(UPrimitiveComponent* InComponent, UChaosCache* InCache, Chaos::FReal InTime, FPlaybackTickRecord& TickRecord, TArray<Chaos::TPBDRigidParticleHandle<Chaos::FReal, 3>*>& OutUpdatedRigids) const override`
- L38 _public prototype_ `virtual void WaitForSolverTasks(UPrimitiveComponent* InComponent) const override;`
- L70 _private prototype_ `static void FillCacheProcessor(const UGroomComponent* GroomComponent, FGroomCacheData& GroomCache, const int32 NumFrames, float& MaxTime, int32& MaxFrame);` — Fill the cache processor from the position buffer
- L74 _private member_ `mutable TMap<UPrimitiveComponent*,FGroomCacheData> GroomCaches;` — List of groom caches that will be used to record/play caches
- L77 _private member_ `bool bIsLoading = false;` — Boolean to check if we are reading the cache or not
- L80 _private member_ `mutable FGraphEventArray ReadbackTasks;` — List of readback tasks to process

#### struct `UE::Groom::FGroomCacheAdapter::FGroomCacheData`  
`struct FGroomCacheData`  
_L44-66_
- desc: Groom cache aata  that will store the readback results
- L46 _public function_ `FGroomCacheData() : CacheProcessor(EGroomCacheType::Guides, EGroomCacheAttributes::Position)`
- L50 _public member_ `FGroomCacheProcessor CacheProcessor;` — Cache processor to be used to build the groom cache
- L53 _public member_ `FString CacheName;` — Cache name to create the groom cache
- L56 _public member_ `FGroomAnimationInfo AnimInfo;` — Animation info to build the cache
- L59 _public member_ `TArray<TSharedPtr<FStrandsPositionOutput>> PositionsBuffer;` — Guides positions to be used to build the cache
- L62 _public member_ `UGroomCache* CacheAsset = nullptr;` — Cache asset used to record the positions
- L65 _public member_ `TArray<float> CacheTimes;` — Cache time at which the task is enqueued

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogGroomCache, Verbose, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogGroomCache, Verbose, All);`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Groom` (scope `UE`)

### `Plugins/Runtime/HairStrands/Source/HairStrandsSolver/Public/GroomSolverComponent.h` (Public)


#### struct `FGroomSolverSettings`  
`struct FGroomSolverSettings`  
_L18-48_
- reflection: `USTRUCT()`
- desc: Solver settings that will be used in dataflow/deformergraph
- L24 _public member_ `float MaxLODDistance = 1000;` — `UPROPERTY(EditAnywhere, Category = "LODs", meta = (ClampMin = "0", UIMin = "0"))` — Maximum LOD distance (if distance between the component and the views is higher that this threshold, no simulation)
- L28 _public member_ `float MinLODDistance = 100;` — `UPROPERTY(EditAnywhere, Category = "LODs", meta = (ClampMin = "0", UIMin = "0"))` — Minimum LOD distance (if distance between the component and the views is lower that this threshold, no simulation)
- L32 _public member_ `float MaxPointsCount = 100000;` — `UPROPERTY(EditAnywhere, Category = "LODs")` — Maximum number of points the solver is going to simulate
- L35 _public member_ `TArray<int32> CurveDynamicIndices;` — List of dynamic curves
- L38 _public member_ `TArray<int32> CurveKinematicIndices;` — List of kinematic curves
- L41 _public member_ `TArray<int32> PointDynamicIndices;` — List of dynamic points
- L44 _public member_ `TArray<int32> PointKinematicIndices;` — List of kinematic points
- L47 _public member_ `TArray<int32> ObjectDistanceLods;` — List of object curve lods

#### struct `FDataflowGroomSolverProxy`  
`struct FDataflowGroomSolverProxy : public FDataflowPhysicsSolverProxy #if CPP , public Chaos::FPhysicsSolverEvents #endif`  
_L52-89_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FDataflowPhysicsSolverProxy,Chaos::FPhysicsSolverEvents`
- desc: Dataflow groom solver proxy used in dataflow simulation
- L59 _public function_ `FDataflowGroomSolverProxy(FGroomSolverSettings InProp = FGroomSolverSettings()) : FDataflowPhysicsSolverProxy()`
- L63 _public function_ `virtual ~FDataflowGroomSolverProxy() override`
- L69 _public function_ `virtual void AdvanceSolverDatas(const float DeltaTime) override`
- L76 _public function_ `virtual bool IsValid() const override`
- L78 _public function_ `virtual const UScriptStruct* GetScriptStruct() const override`
- L85 _public member_ `UMeshDeformerInstance* DeformerInstance = nullptr;` — Deformer instance coming from the component
- L88 _public member_ `TMap<FGuid, FGuid> DeformerInstanceGuids;` — Deformer Instance GUIDs

#### struct `TStructOpsTypeTraits`  
`template <> struct TStructOpsTypeTraits<FDataflowGroomSolverProxy> : public TStructOpsTypeTraitsBase2<FDataflowGroomSolverProxy>`  
_L92-95_
- inherits: `TStructOpsTypeTraitsBase2<FDataflowGroomSolverProxy>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
`enum`  
_L94-94_

#### class `UGroomSolverComponent`  
`class UGroomSolverComponent : public UMeshComponent, public IDataflowPhysicsSolverInterface`  
_L99-209_
- reflection: `UCLASS(HideCategories = (Object, Physics, Collision, Activation, Mobility, "Components|Activation"), meta = (BlueprintSpawnableComponent), ClassGroup = Physics, MinimalAPI)`
- inherits: `UMeshComponent,IDataflowPhysicsSolverInterface`
- desc: Groom solver component in which groom component could be added to be solver together
- L105 _public prototype_ `UGroomSolverComponent(const FObjectInitializer& ObjectInitializer);`
- L108 _public function_ `virtual FString GetSimulationName() const override`
- L109 _public function_ `virtual FDataflowSimulationAsset& GetSimulationAsset() override`
- L110 _public function_ `virtual const FDataflowSimulationAsset& GetSimulationAsset() const override`
- L111 _public function_ `virtual FDataflowSimulationProxy* GetSimulationProxy() override`
- L112 _public function_ `virtual const FDataflowSimulationProxy* GetSimulationProxy() const override`
- L113 _public function_ `virtual void BuildSimulationProxy() override`
- L114 _public function_ `virtual void ResetSimulationProxy() override`
- L115 _public function_ `virtual void WriteToSimulation(const float DeltaTime, const bool bAsyncTask) override`
- L116 _public function_ `virtual void ReadFromSimulation(const float DeltaTime, const bool bAsyncTask) override`
- L121 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L126 _public prototype_ `virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;`
- L127 _public prototype_ `virtual void OnRegister() override;`
- L128 _public prototype_ `virtual void OnUnregister() override;`
- L129 _public prototype_ `virtual void CreateRenderState_Concurrent(FRegisterComponentContext* Context) override;`
- L130 _public prototype_ `virtual void SendRenderDynamicData_Concurrent() override;`
- L131 _public prototype_ `virtual void DestroyRenderState_Concurrent() override;`
- L136 _public prototype_ `void AddGroomComponent(UGroomComponent* GroomComponent);` — `UFUNCTION(BlueprintCallable, Category = "Groom")` — Add a groom component to the solver
- L140 _public prototype_ `void RemoveGroomComponent(UGroomComponent* GroomComponent);` — `UFUNCTION(BlueprintCallable, Category = "Groom")` — Remove a groom component to the solver
- L144 _public prototype_ `void ResetGroomComponents();` — `UFUNCTION(BlueprintCallable, Category = "Groom")` — Reset the solver groom components
- L148 _public prototype_ `void AddCollisionComponent(UMeshComponent* CollisionComponent, const int32 LODIndex);` — `UFUNCTION(BlueprintCallable, Category = "Groom")` — Add a collision component to the solver
- L152 _public prototype_ `void RemoveCollisionComponent(UMeshComponent* CollisionComponent);` — `UFUNCTION(BlueprintCallable, Category = "Groom")` — Remove a collision component to the solver
- L156 _public prototype_ `void ResetCollisionComponents();` — `UFUNCTION(BlueprintCallable, Category = "Groom")` — Reset the solver collision components
- L159 _public function_ `const TSet< TObjectPtr<UGroomComponent> >& GetGroomComponents() const` — Get the solver groom components
- L162 _public function_ `const TMap< TObjectPtr<UMeshComponent>, int32 >& GetCollisionComponents() const` — Get the solver collision components
- L166 _public prototype_ `void SetDeformerSolver(UMeshDeformer* DeformerSolver);` — `UFUNCTION(BlueprintCallable, Category = "Groom")` — Change the MeshDeformer solver that is used for this Component.
- L169 _public function_ `const FGroomSolverSettings& GetSolverSettings() const` — Get the groom solver settings
- L172 _public function_ `UMeshDeformerInstance* GetMeshDeformerInstance() const` — Return the mesh deformer instance
- L177 _private prototype_ `void SelectDynamicCurves();` — Select the number of dynamic curves based on the distance component-views
- L181 _private member_ `FGroomSolverSettings SolverSettings;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Solver settings used to control the simulation
- L185 _private member_ `FDataflowSimulationAsset SimulationAsset;` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta=(EditConditionHides), AdvancedDisplay)` — Solver dataflow asset used to advance in time
- L189 _private member_ `TSet< TObjectPtr<UGroomComponent> > GroomComponents;` — `UPROPERTY(VisibleAnywhere, Category = "Groom")` — List of physics objects registered to the solver
- L193 _private member_ `TObjectPtr<UMeshDeformer> MeshDeformer = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Groom", meta = (DisplayPriority = 2))` — Graph deformer solver the component is using
- L197 _private member_ `TObjectPtr<UMeshDeformerInstance> DeformerInstance = nullptr;` — `UPROPERTY(Transient)` — Object containing state for the MeshDeformer.
- L201 _private member_ `TObjectPtr<UMeshDeformerInstanceSettings> DeformerSettings = nullptr;` — `UPROPERTY(VisibleAnywhere, Instanced, Category = "Groom", meta = (DisplayName = "Deformer Settings", EditCondition = "DeformerSettings!=nullptr", ShowOnlyInnerProperties))` — Object containing instance settings for the MeshDeformer.
- L204 _private member_ `FDataflowGroomSolverProxy GroomSolverProxy;` — Groom solver proxy to be used in dataflow
- L208 _private member_ `TMap< TObjectPtr<UMeshComponent>, int32 > CollisionComponents;` — `UPROPERTY(VisibleAnywhere, Category = "Groom")` — List of collision components registered to the solver

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API HAIRSTRANDSSOLVER_API`
- L94 _enumerator_ `enum { WithCopy = false };` (scope `TStructOpsTypeTraits::__anon4772a1ef0103`)

### `Plugins/Runtime/HairStrands/Source/HairStrandsSolver/Public/HairStrandsSolverModule.h` (Public)


#### class `FHairStrandsSolverModule`  
`class FHairStrandsSolverModule : public IModuleInterface`  
_L10-22_
- inherits: `IModuleInterface`
- desc: Hair dataflow construction module public interface
- L15 _public prototype_ `virtual void StartupModule() override;`
- L16 _public prototype_ `virtual void ShutdownModule() override;`
- L21 _private member_ `TUniquePtr<UE::Groom::FGroomCacheAdapter> GroomCacheAdapter;` — Cache adapter to be used when caching grooms in dataflow
