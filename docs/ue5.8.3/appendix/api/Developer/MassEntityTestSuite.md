# Developer / MassEntityTestSuite

- module root: `Source/Developer/MassEntityTestSuite`
- headers: 2; symbols: 274
- symbol kinds: class=27, enum=8, enumerator=13, function=31, macro=2, member=86, namespace=6, prototype=49, struct=45, typedef=7
- PrivateDependencyModuleNames: UnrealEd
- PublicDependencyModuleNames: AITestSuite, Core, CoreUObject, Engine, MassCore, MassEntity

### `Source/Developer/MassEntityTestSuite/Public/MassEntityTestFarmPlot.h` (Public)


#### struct `FFarmVisualDataRow`  
`struct FFarmVisualDataRow : public FTableRowBase`  
_L25-34_
- reflection: `USTRUCT()`
- inherits: `FTableRowBase`
- L30 _public member_ `TObjectPtr<UStaticMesh> Mesh = nullptr;` — `UPROPERTY(EditAnywhere, Category=Farm)`
- L33 _public member_ `TObjectPtr<UMaterialInterface> MaterialOverride = nullptr;` — `UPROPERTY(EditAnywhere, Category=Farm)`

#### struct `FFarmJustBecameReadyToHarvestTag`  
`struct FFarmJustBecameReadyToHarvestTag : public FMassTag`  
_L37-40_
- reflection: `USTRUCT()`
- inherits: `FMassTag`

#### struct `FFarmReadyToHarvestTag`  
`struct FFarmReadyToHarvestTag : public FMassTag`  
_L43-46_
- reflection: `USTRUCT()`
- inherits: `FMassTag`

#### struct `FFarmGridCellData`  
`struct FFarmGridCellData : public FMassFragment`  
_L49-55_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- L53 _public member_ `uint16 CellX = 0;`
- L54 _public member_ `uint16 CellY = 0;`

#### struct `FFarmWaterFragment`  
`struct FFarmWaterFragment : public FMassFragment`  
_L58-64_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- L62 _public member_ `float CurrentWater = 1.0f;`
- L63 _public member_ `float DeltaWaterPerSecond = -0.01f;`

#### struct `FFarmFlowerFragment`  
`struct FFarmFlowerFragment : public FMassFragment`  
_L67-73_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- L71 _public member_ `uint32 NumBonusTicks = 0;`
- L72 _public member_ `uint16 FlowerType = 0;`

#### struct `FFarmCropFragment`  
`struct FFarmCropFragment : public FMassFragment`  
_L76-81_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- L80 _public member_ `uint16 CropType = 0;`

#### struct `FFarmVisualFragment`  
`struct FFarmVisualFragment : public FMassFragment`  
_L85-92_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- L89 _public member_ `int32 InstanceIndex = -1;`
- L90 _public member_ `int32 HarvestIconIndex = -1;`
- L91 _public member_ `uint16 VisualType = 0;`

#### struct `FHarvestTimerFragment`  
`struct FHarvestTimerFragment : public FMassFragment`  
_L95-100_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- L99 _public member_ `uint32 NumSecondsLeft = 15;`

#### class `UFarmProcessorBase`  
`class UFarmProcessorBase : public UMassProcessor`  
_L105-114_
- reflection: `UCLASS(abstract)`
- inherits: `UMassProcessor`
- L110 _public prototype_ `UFarmProcessorBase();`
- L113 _protected member_ `FMassEntityQuery EntityQuery;`

#### class `UFarmWaterProcessor`  
`class UFarmWaterProcessor : public UFarmProcessorBase`  
_L119-126_
- reflection: `UCLASS()`
- inherits: `UFarmProcessorBase`
- L124 _public prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L125 _public prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`

#### class `UFarmHarvestTimerSystem_Flowers`  
`class UFarmHarvestTimerSystem_Flowers : public UFarmProcessorBase`  
_L131-137_
- reflection: `UCLASS()`
- inherits: `UFarmProcessorBase`
- L135 _private prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L136 _private prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`

#### class `UFarmHarvestTimerSystem_Crops`  
`class UFarmHarvestTimerSystem_Crops : public UFarmProcessorBase`  
_L142-148_
- reflection: `UCLASS()`
- inherits: `UFarmProcessorBase`
- L146 _private prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L147 _private prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`

#### class `UFarmHarvestTimerExpired`  
`class UFarmHarvestTimerExpired : public UFarmProcessorBase`  
_L153-159_
- reflection: `UCLASS()`
- inherits: `UFarmProcessorBase`
- L157 _private prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L158 _private prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`

#### class `UFarmHarvestTimerSetIcon`  
`class UFarmHarvestTimerSetIcon : public UFarmProcessorBase`  
_L164-180_
- reflection: `UCLASS()`
- inherits: `UFarmProcessorBase`
- L170 _public member_ `TObjectPtr<UHierarchicalInstancedStaticMeshComponent> HarvestIconISMC;` — `UPROPERTY()`
- L172 _public member_ `float GridCellWidth;`
- L173 _public member_ `float GridCellHeight;`
- L174 _public member_ `float HarvestIconHeight;`
- L175 _public member_ `float HarvestIconScale;`
- L178 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L179 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`

#### class `AMassEntityTestFarmPlot`  
`class AMassEntityTestFarmPlot : public AActor`  
_L185-255_
- reflection: `UCLASS(config=Game)`
- inherits: `AActor`
- L190 _public member_ `uint16 GridWidth = 40*7;`
- L191 _public member_ `uint16 GridHeight = 20*7;`
- L194 _public member_ `float GridCellWidth = 150.0f;` — `UPROPERTY(EditAnywhere, Category=Farm)`
- L197 _public member_ `float GridCellHeight = 150.0f;` — `UPROPERTY(EditAnywhere, Category=Farm)`
- L200 _public member_ `float HarvestIconScale = 0.3f;` — `UPROPERTY(EditAnywhere, Category=Farm)`
- L202 _public member_ `TArray<FMassEntityHandle> PlantedSquares;`
- L206 _public member_ `TArray<FFarmVisualDataRow> VisualDataTable;` — `UPROPERTY(EditAnywhere, Category=Farm)`
- L209 _public member_ `TArray<TObjectPtr<UHierarchicalInstancedStaticMeshComponent>> VisualDataISMCs;` — `UPROPERTY(Transient)`
- L211 _public member_ `float NextSecondTimer = 0.0f;`
- L214 _public member_ `TArray<TObjectPtr<UMassProcessor>> PerFrameSystems;` — `UPROPERTY(Transient)`
- L217 _public member_ `TArray<TObjectPtr<UMassProcessor>> PerSecondSystems;` — `UPROPERTY(Transient)`
- L221 _public member_ `TArray<uint16> TestDataFlowerIndicies;` — `UPROPERTY(EditAnywhere, Category=Farm)` — Indices into VisualDataTable for flowers
- L225 _public member_ `TArray<uint16> TestDataCropIndicies;` — `UPROPERTY(EditAnywhere, Category=Farm)` — Indices into VisualDataTable for crops
- L228 _public member_ `uint32 VisualNearCullDistance = 1000;` — `UPROPERTY(EditAnywhere, Category = Farm)`
- L231 _public member_ `uint32 VisualFarCullDistance = 1200;` — `UPROPERTY(EditAnywhere, Category = Farm)`
- L234 _public member_ `uint32 IconNearCullDistance = 400;` — `UPROPERTY(EditAnywhere, Category = Farm)`
- L237 _public member_ `uint32 IconFarCullDistance = 800;` — `UPROPERTY(EditAnywhere, Category = Farm)`
- L241 _private member_ `TObjectPtr<UHierarchicalInstancedStaticMeshComponent> HarvestIconISMC;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"), Category=Farm)`
- L243 _private member_ `TArray<int32> FreeHarvestIconIndicies;`
- L245 _private member_ `TSharedRef<FMassEntityManager> SharedEntityManager;`
- L248 _private prototype_ `void AddItemToGrid(FMassEntityManager& InEntityManager, uint16 X, uint16 Y, FMassArchetypeHandle Archetype, uint16 VisualIndex);`
- L251 _public prototype_ `AMassEntityTestFarmPlot();`
- L253 _public prototype_ `virtual void BeginPlay() override;`
- L254 _public prototype_ `virtual void TickActor(float DeltaTime, enum ELevelTick TickType, FActorTickFunction& ThisTickFunction) override;`

### `Source/Developer/MassEntityTestSuite/Public/MassEntityTestTypes.h` (Public)


#### struct `FTestFragment_EntityHandle`  
`struct FTestFragment_EntityHandle : public FMassFragment`  
_L61-69_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- L66 _public member_ `FMassEntityHandle Value;` — `UPROPERTY()`
- L68 _public function_ `FTestFragment_EntityHandle(const FMassEntityHandle InValue = FMassEntityHandle()) : Value(InValue)`

#### struct `FTestFragment_Float`  
`struct FTestFragment_Float : public FMassFragment`  
_L72-78_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- L75 _public member_ `float Value = 0;`
- L77 _public function_ `FTestFragment_Float(const float InValue = 0.f) : Value(InValue)`

#### struct `FTestFragment_Int`  
`struct FTestFragment_Int : public FMassFragment`  
_L81-91_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- L86 _public member_ `int32 Value = 0;` — `UPROPERTY()`
- L88 _public function_ `FTestFragment_Int(const int32 InValue = 0) : Value(InValue)`
- L90 _public member_ `static constexpr int32 TestIntValue = 123456;`

#### struct `FTestFragment_Bool`  
`struct FTestFragment_Bool : public FMassFragment`  
_L94-100_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- L97 _public member_ `bool bValue = false;`
- L99 _public function_ `FTestFragment_Bool(const bool bInValue = false) : bValue(bInValue)`

#### struct `FTestFragment_Large`  
`struct FTestFragment_Large : public FMassFragment`  
_L103-114_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- L108 _public member_ `uint8 Value[64];` — `UPROPERTY()`
- L110 _public function_ `FTestFragment_Large(uint8 Fill = 0)`

#### struct `FTestFragment_Array`  
`struct FTestFragment_Array : public FMassFragment`  
_L117-128_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- L122 _public member_ `TArray<int32> Value;` — `UPROPERTY()`
- L124 _public function_ `FTestFragment_Array(uint8 Num = 0)`

#### struct `TMassFragmentTraits`  
`template<> struct TMassFragmentTraits<FTestFragment_Array> final`  
_L131-137_

#### enum `TMassFragmentTraits::(anonymous)`  
``  
_L134-136_

#### struct `FFragmentWithSharedPtr`  
`struct FFragmentWithSharedPtr : public FMassFragment`  
_L140-150_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- L144 _public member_ `TSharedPtr<int32> Data;`
- L146 _public prototype_ `FFragmentWithSharedPtr() = default;`
- L147 _public function_ `FFragmentWithSharedPtr(TSharedPtr<int32>& InData) : Data(InData)`

#### struct `TMassFragmentTraits`  
`template<> struct TMassFragmentTraits<FFragmentWithSharedPtr> final`  
_L153-159_

#### enum `TMassFragmentTraits::(anonymous)`  
``  
_L156-158_

#### struct `FTestChunkFragment_Int`  
`struct FTestChunkFragment_Int : public FMassChunkFragment`  
_L162-170_
- reflection: `USTRUCT()`
- inherits: `FMassChunkFragment`
- L167 _public member_ `int32 Value = 0;` — `UPROPERTY()`
- L169 _public function_ `FTestChunkFragment_Int(const int32 InValue = 0) : Value(InValue)`

#### struct `FTestChunkFragment_Float`  
`struct FTestChunkFragment_Float : public FMassChunkFragment`  
_L173-181_
- reflection: `USTRUCT()`
- inherits: `FMassChunkFragment`
- L178 _public member_ `float Value = 0.f;` — `UPROPERTY()`
- L180 _public function_ `FTestChunkFragment_Float(const float InValue = 0.f) : Value(InValue)`

#### struct `FTestSharedFragment_Int`  
`struct FTestSharedFragment_Int : public FMassSharedFragment`  
_L184-194_
- reflection: `USTRUCT()`
- inherits: `FMassSharedFragment`
- L186 _public typedef_ `using FValueType = int32;`
- L191 _public member_ `int32 Value = 0;` — `UPROPERTY()`
- L193 _public function_ `FTestSharedFragment_Int(const int32 InValue = 0) : Value(InValue)`

#### struct `FTestSharedFragment_Array`  
`struct FTestSharedFragment_Array : public FMassSharedFragment`  
_L197-208_
- reflection: `USTRUCT()`
- inherits: `FMassSharedFragment`
- L199 _public typedef_ `using FValueType = TArray<int32>;`
- L204 _public member_ `TArray<int32> Value;` — `UPROPERTY()`
- L206 _public prototype_ `FTestSharedFragment_Array() = default;`
- L207 _public function_ `FTestSharedFragment_Array(const TArray<int32>&& InValue) : Value(InValue)`

#### struct `TMassSharedFragmentTraits`  
`template<> struct TMassSharedFragmentTraits<FTestSharedFragment_Int> final`  
_L211-217_

#### enum `TMassSharedFragmentTraits::(anonymous)`  
``  
_L214-216_

#### struct `FTestConstSharedFragment_Int`  
`struct FTestConstSharedFragment_Int : public FMassConstSharedFragment`  
_L220-230_
- reflection: `USTRUCT()`
- inherits: `FMassConstSharedFragment`
- L222 _public typedef_ `using FValueType = int32;`
- L227 _public member_ `int32 Value = 0;` — `UPROPERTY()`
- L229 _public function_ `FTestConstSharedFragment_Int(const int32 InValue = 0) : Value(InValue)`

#### struct `FTestSharedFragment_Float`  
`struct FTestSharedFragment_Float : public FMassSharedFragment`  
_L233-243_
- reflection: `USTRUCT()`
- inherits: `FMassSharedFragment`
- L235 _public typedef_ `using FValueType = float;`
- L240 _public member_ `float Value = 0.f;` — `UPROPERTY()`
- L242 _public function_ `FTestSharedFragment_Float(const float InValue = 0) : Value(InValue)`

#### struct `FTestConstSharedFragment_Float`  
`struct FTestConstSharedFragment_Float : public FMassConstSharedFragment`  
_L246-256_
- reflection: `USTRUCT()`
- inherits: `FMassConstSharedFragment`
- L248 _public typedef_ `using FValueType = float;`
- L253 _public member_ `float Value = 0.f;` — `UPROPERTY()`
- L255 _public function_ `FTestConstSharedFragment_Float(const float InValue = 0) : Value(InValue)`

#### struct `FTestFragment_Tag`  
`struct FTestFragment_Tag : public FMassTag`  
_L260-263_
- reflection: `USTRUCT()`
- inherits: `FMassTag`
- desc: @todo rename to FTestTag

#### struct `FTestTag_A`  
`struct FTestTag_A : public FMassTag`  
_L266-269_
- reflection: `USTRUCT()`
- inherits: `FMassTag`

#### struct `FTestTag_B`  
`struct FTestTag_B : public FMassTag`  
_L272-275_
- reflection: `USTRUCT()`
- inherits: `FMassTag`

#### struct `FTestTag_C`  
`struct FTestTag_C : public FMassTag`  
_L278-281_
- reflection: `USTRUCT()`
- inherits: `FMassTag`

#### struct `FTestTag_D`  
`struct FTestTag_D : public FMassTag`  
_L284-287_
- reflection: `USTRUCT()`
- inherits: `FMassTag`

#### struct `FTestFragment_SparseInt`  
`struct FTestFragment_SparseInt : public FMassSparseFragment`  
_L290-300_
- reflection: `USTRUCT()`
- inherits: `FMassSparseFragment`
- L294 _public function_ `FTestFragment_SparseInt(const int32 InValue = 0) : Value(InValue)`
- L299 _public member_ `int32 Value = 0;`

#### struct `FTestFragment_SparseFloat`  
`struct FTestFragment_SparseFloat : public FMassSparseFragment`  
_L303-313_
- reflection: `USTRUCT()`
- inherits: `FMassSparseFragment`
- L307 _public function_ `FTestFragment_SparseFloat(const float InValue = 0.f) : Value(InValue)`
- L312 _public member_ `float Value = 0.f;`

#### struct `FTestTag_SparseA`  
`struct FTestTag_SparseA : public FMassSparseTag`  
_L316-319_
- reflection: `USTRUCT()`
- inherits: `FMassSparseTag`

#### struct `FTestTag_SparseB`  
`struct FTestTag_SparseB : public FMassSparseTag`  
_L322-325_
- reflection: `USTRUCT()`
- inherits: `FMassSparseTag`

#### class `UMassTestProcessorBase`  
`class UMassTestProcessorBase : public UMassProcessor`  
_L329-364_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassProcessor`
- L333 _public prototype_ `UMassTestProcessorBase();`
- L334 _public function_ `FMassProcessorExecutionOrder& GetMutableExecutionOrder()`
- L335 _public prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L336 _public function_ `virtual bool ShouldAllowQueryBasedPruning(const bool bRuntimeMode = true) const`
- L341 _public function_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>&) override` — Leaving the implementation empty since it's up to the child classes and specific use-cases to determine the actual requirements for EntityQuery.
- L343 _public typedef_ `using FExecutionFunction = TFunction<void(FMassEntityManager& EntityManager, FMassExecutionContext& Context)>;`
- L344 _public member_ `FExecutionFunction ExecutionFunction;`
- L350 _public member_ `FMassExecuteFunction ForEachEntityChunkExecutionFunction;` — By default ExecutionFunction is configured to pass this function over to EntityQuery.ForEachEntityChunk call. Note that this function won't be used if you override ExecutionFunction's default value.
- L352 _public function_ `void SetShouldAllowMultipleInstances(const bool bInShouldAllowDuplicated)`
- L354 _public prototype_ `void SetUseParallelForEachEntityChunk(bool bEnable);`
- L355 _public prototype_ `void TestExecute(TSharedPtr<FMassEntityManager>& EntityManager);`
- L357 _public function_ `FMassEntityCreationRequirements& GetEntityCreationRequirements()`
- L363 _public member_ `FMassEntityQuery EntityQuery;` — public on purpose, this is a test processor, no worries about access

#### class `UMassTestProcessor_A`  
`class UMassTestProcessor_A : public UMassTestProcessorBase`  
_L367-370_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassTestProcessorBase`

#### class `UMassTestProcessor_B`  
`class UMassTestProcessor_B : public UMassTestProcessorBase`  
_L373-376_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassTestProcessorBase`

#### class `UMassTestProcessor_C`  
`class UMassTestProcessor_C : public UMassTestProcessorBase`  
_L379-382_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassTestProcessorBase`

#### class `UMassTestProcessor_D`  
`class UMassTestProcessor_D : public UMassTestProcessorBase`  
_L385-388_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassTestProcessorBase`

#### class `UMassTestProcessor_E`  
`class UMassTestProcessor_E : public UMassTestProcessorBase`  
_L391-394_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassTestProcessorBase`

#### class `UMassTestProcessor_F`  
`class UMassTestProcessor_F : public UMassTestProcessorBase`  
_L397-400_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassTestProcessorBase`

#### class `UMassTestProcessor_Floats`  
`class UMassTestProcessor_Floats : public UMassTestProcessorBase`  
_L403-409_
- reflection: `UCLASS()`
- inherits: `UMassTestProcessorBase`
- L407 _public member_ `TArrayView<FTestFragment_Float> Floats;`
- L408 _public prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`

#### class `UMassTestProcessor_Ints`  
`class UMassTestProcessor_Ints : public UMassTestProcessorBase`  
_L412-418_
- reflection: `UCLASS()`
- inherits: `UMassTestProcessorBase`
- L416 _public member_ `TArrayView<FTestFragment_Int> Ints;`
- L417 _public prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`

#### class `UMassTestProcessor_FloatsInts`  
`class UMassTestProcessor_FloatsInts : public UMassTestProcessorBase`  
_L421-428_
- reflection: `UCLASS()`
- inherits: `UMassTestProcessorBase`
- L425 _public member_ `TArrayView<FTestFragment_Float> Floats;`
- L426 _public member_ `TArrayView<FTestFragment_Int> Ints;`
- L427 _public prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`

#### class `UMassTestStaticCounterProcessor`  
`class UMassTestStaticCounterProcessor : public UMassProcessor`  
_L441-455_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassProcessor`
- L446 _public prototype_ `UMassTestStaticCounterProcessor();`
- L447 _public function_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override`
- L451 _public function_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>&) override`
- L452 _public function_ `virtual bool ShouldAllowQueryBasedPruning(const bool bRuntimeMode = true) const override`
- L454 _public member_ `static int StaticCounter;`

#### class `UMassTestProcessorAutoExecuteQuery`  
`class UMassTestProcessorAutoExecuteQuery : public UMassProcessor`  
_L458-468_
- reflection: `UCLASS()`
- inherits: `UMassProcessor`
- L462 _public prototype_ `UMassTestProcessorAutoExecuteQuery();`
- L463 _public function_ `void SetAutoExecuteQuery(TSharedPtr<UE::Mass::FQueryExecutor> InAutoExecuteQuery)`
- L467 _public member_ `FMassEntityQuery EntityQuery{ *this };`

#### class `UMassTestProcessorAutoExecuteQueryComparison`  
`class UMassTestProcessorAutoExecuteQueryComparison : public UMassTestProcessorBase`  
_L471-478_
- reflection: `UCLASS()`
- inherits: `UMassTestProcessorBase`
- L475 _public prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>&) override;`
- L476 _public prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L477 _public member_ `FMassEntityQuery EntityQuery{ *this };`

#### class `UMassTestProcessorAutoExecuteQueryComparison_Parallel`  
`class UMassTestProcessorAutoExecuteQueryComparison_Parallel : public UMassTestProcessorBase`  
_L481-488_
- reflection: `UCLASS()`
- inherits: `UMassTestProcessorBase`
- L485 _public prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>&) override;`
- L486 _public prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L487 _public member_ `FMassEntityQuery EntityQuery{ *this };`

#### struct `FExecutionTestBase`  
`struct FExecutionTestBase : FAITestBase`  
_L490-497_
- inherits: `FAITestBase`
- L492 _public member_ `TSharedPtr<FMassEntityManager> EntityManager;`
- L493 _public member_ `bool bMakeWorldEntityManagersOwner = true;`
- L495 _public prototype_ `virtual bool SetUp() override;`
- L496 _public prototype_ `virtual void TearDown() override;`

#### struct `FEntityTestBase`  
`struct FEntityTestBase : FExecutionTestBase`  
_L499-510_
- inherits: `FExecutionTestBase`
- L501 _public member_ `FMassArchetypeHandle EmptyArchetype;`
- L502 _public member_ `FMassArchetypeHandle FloatsArchetype;`
- L503 _public member_ `FMassArchetypeHandle IntsArchetype;`
- L504 _public member_ `FMassArchetypeHandle FloatsIntsArchetype;`
- L505 _public member_ `FMassArchetypeHandle LargeArchetype;`
- L507 _public member_ `FInstancedStruct InstanceInt;`
- L509 _public prototype_ `virtual bool SetUp() override;`

#### struct `FProcessingPhasesTestBase`  
`struct FProcessingPhasesTestBase : FEntityTestBase`  
_L513-530_
- inherits: `FEntityTestBase`
- L515 _public typedef_ `using Super = FEntityTestBase;`
- L517 _public member_ `TSharedPtr<UE::Mass::Testing::FMassTestProcessingPhaseManager> PhaseManager;`
- L518 _public member_ `FMassProcessingPhaseConfig PhasesConfig[int(EMassProcessingPhase::MAX)];`
- L519 _public member_ `int32 TickIndex = -1;`
- L520 _public member_ `FGraphEventRef CompletionEvent;`
- L521 _public member_ `float DeltaTime = 1.f / 30;`
- L522 _public member_ `UWorld* World = nullptr;`
- L524 _public prototype_ `FProcessingPhasesTestBase();`
- L525 _public prototype_ `virtual bool SetUp() override;`
- L526 _public prototype_ `virtual bool Update() override;`
- L527 _public prototype_ `virtual void TearDown() override;`
- L528 _public prototype_ `virtual void VerifyLatentResults() override;`
- L529 _public prototype_ `virtual bool PopulatePhasesConfig() = 0;`

#### class `UMassTestWorldSubsystem`  
`class UMassTestWorldSubsystem : public UWorldSubsystem`  
_L543-553_
- reflection: `UCLASS()`
- inherits: `UWorldSubsystem`
- L547 _public prototype_ `void Write(int32 InNumber);`
- L548 _public prototype_ `int32 Read() const;`
- L551 _private prototype_ `UE_MT_DECLARE_RW_ACCESS_DETECTOR(AccessDetector);`
- L552 _private member_ `int Number = 0;`

#### struct `TMassExternalSubsystemTraits`  
`template<> struct TMassExternalSubsystemTraits<UMassTestWorldSubsystem>`  
_L556-563_

#### enum `TMassExternalSubsystemTraits::(anonymous)`  
``  
_L559-562_

#### class `UMassTestParallelSubsystem`  
`class UMassTestParallelSubsystem : public UMassSubsystemBase`  
_L566-569_
- reflection: `UCLASS()`
- inherits: `UMassSubsystemBase`

#### struct `TMassExternalSubsystemTraits`  
`template<> struct TMassExternalSubsystemTraits<UMassTestParallelSubsystem>`  
_L572-579_

#### enum `TMassExternalSubsystemTraits::(anonymous)`  
``  
_L575-578_

#### class `UMassTestEngineSubsystem`  
`class UMassTestEngineSubsystem : public UEngineSubsystem`  
_L582-585_
- reflection: `UCLASS()`
- inherits: `UEngineSubsystem`

#### struct `TMassExternalSubsystemTraits`  
`template<> struct TMassExternalSubsystemTraits<UMassTestEngineSubsystem>`  
_L588-595_

#### enum `TMassExternalSubsystemTraits::(anonymous)`  
``  
_L591-594_

#### class `UMassTestLocalPlayerSubsystem`  
`class UMassTestLocalPlayerSubsystem : public ULocalPlayerSubsystem`  
_L598-601_
- reflection: `UCLASS()`
- inherits: `ULocalPlayerSubsystem`

#### struct `TMassExternalSubsystemTraits`  
`template<> struct TMassExternalSubsystemTraits<UMassTestLocalPlayerSubsystem>`  
_L604-611_

#### enum `TMassExternalSubsystemTraits::(anonymous)`  
``  
_L607-610_

#### class `UMassTestGameInstanceSubsystem`  
`class UMassTestGameInstanceSubsystem : public UGameInstanceSubsystem`  
_L614-617_
- reflection: `UCLASS()`
- inherits: `UGameInstanceSubsystem`

#### struct `TMassExternalSubsystemTraits`  
`template<> struct TMassExternalSubsystemTraits<UMassTestGameInstanceSubsystem>`  
_L620-627_

#### enum `TMassExternalSubsystemTraits::(anonymous)`  
``  
_L623-626_

#### struct `UE::Mass::Testing::FMassTestPhaseTickTask`  
`struct FMassTestPhaseTickTask`  
_L632-646_
- desc: Test-time TaskGraph task for triggering processing phases.
- L634 _public prototype_ `FMassTestPhaseTickTask(const TSharedRef<FMassProcessingPhaseManager>& InPhaseManager, const EMassProcessingPhase InPhase, const float InDeltaTime);`
- L636 _public prototype_ `static TStatId GetStatId();`
- L637 _public prototype_ `static ENamedThreads::Type GetDesiredThread();`
- L638 _public prototype_ `static ESubsequentsMode::Type GetSubsequentsMode();`
- L640 _public prototype_ `void DoTask(ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent);`
- L643 _private member_ `const TSharedRef<FMassProcessingPhaseManager> PhaseManager;`
- L644 _private member_ `const EMassProcessingPhase Phase = EMassProcessingPhase::MAX;`
- L645 _private member_ `const float DeltaTime = 0.f;`

#### struct `UE::Mass::Testing::FMassTestProcessingPhaseManager`  
`struct FMassTestProcessingPhaseManager : public FMassProcessingPhaseManager`  
_L649-653_
- inherits: `FMassProcessingPhaseManager`
- desc: The main point of this FMassProcessingPhaseManager extension is to disable world-based ticking, even if a world is available.
- L651 _public prototype_ `void Start(const TSharedPtr<FMassEntityManager>& InEntityManager);`
- L652 _public prototype_ `void OnNewArchetype(const FMassArchetypeHandle& NewArchetype);`

#### class `UMassTestCompositeObserverProcessor`  
`class UMassTestCompositeObserverProcessor : public UMassObserverProcessor`  
_L664-696_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMassObserverProcessor`
- desc: Minimal concrete multi-type observer processor for unit tests. Counts invocations of Execute() to verify deduplication guarantees. bAutoRegisterWithObserverRegistry is set to false in the constructor so that the CDO produced during module init does not attempt to contact UMassObserverRegistry.
- L668 _public function_ `UMassTestCompositeObserverProcessor()`
- L674 _public member_ `int32 ExecuteCallCount = 0;`
- L676 _public function_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override`
- L682 _public function_ `void SetObservedTypesForTest(std::initializer_list<const UScriptStruct*> Types)` — Sets the observed types list directly for test configuration.
- L692 _public function_ `void SetObservedOperationsForTest(const EMassObservedOperationFlags InFlags)` — Sets the observed operation flags directly for test configuration.

#### Free symbols / members of external scopes

- L22 _macro_ `#define UE_API MASSENTITYTESTSUITE_API`
- L26 _macro_ `#define MASS_SCOPED_ENSURE_TEST(PartialTextToExpect, NumOccurrences) \` — Works with checks too, but didn't want to make the name too lon
- L55 _namespace_ `namespace UE`
- L55 _namespace_ `namespace Mass` (scope `UE`)
- L55 _namespace_ `namespace Testing` (scope `UE::Mass`)
- L135 _enumerator_ `AuthorAcceptsItsNotTriviallyCopyable = true` (scope `TMassFragmentTraits::__anon83bed8ff0103`)
- L157 _enumerator_ `AuthorAcceptsItsNotTriviallyCopyable = true` (scope `TMassFragmentTraits::__anon83bed8ff0203`)
- L215 _enumerator_ `GameThreadOnly = true` (scope `TMassSharedFragmentTraits::__anon83bed8ff0303`)
- L431 _function_ `template<typename T> T* NewTestProcessor(TSharedPtr<FMassEntityManager> EntityManager)`
- L533 _function_ `template<typename T> void ShuffleDataWithRandomStream(FRandomStream& Rand, TArray<T>& Data)`
- L560 _enumerator_ `GameThreadOnly = false` (scope `TMassExternalSubsystemTraits::__anon83bed8ff0403`)
- L561 _enumerator_ `ThreadSafeWrite = false` (scope `TMassExternalSubsystemTraits::__anon83bed8ff0403`)
- L576 _enumerator_ `GameThreadOnly = false` (scope `TMassExternalSubsystemTraits::__anon83bed8ff0503`)
- L577 _enumerator_ `ThreadSafeWrite = true` (scope `TMassExternalSubsystemTraits::__anon83bed8ff0503`)
- L592 _enumerator_ `GameThreadOnly = false` (scope `TMassExternalSubsystemTraits::__anon83bed8ff0603`)
- L593 _enumerator_ `ThreadSafeWrite = false` (scope `TMassExternalSubsystemTraits::__anon83bed8ff0603`)
- L608 _enumerator_ `GameThreadOnly = false` (scope `TMassExternalSubsystemTraits::__anon83bed8ff0703`)
- L609 _enumerator_ `ThreadSafeWrite = false` (scope `TMassExternalSubsystemTraits::__anon83bed8ff0703`)
- L624 _enumerator_ `GameThreadOnly = false` (scope `TMassExternalSubsystemTraits::__anon83bed8ff0803`)
- L625 _enumerator_ `ThreadSafeWrite = false` (scope `TMassExternalSubsystemTraits::__anon83bed8ff0803`)
- L629 _namespace_ `namespace UE`
- L629 _namespace_ `namespace Mass` (scope `UE`)
- L629 _namespace_ `namespace Testing` (scope `UE::Mass`)
