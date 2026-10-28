# Programs / MassTests

- module root: `Source/Programs/MassTests`
- headers: 3; symbols: 196
- symbol kinds: class=20, enum=8, enumerator=13, function=40, member=45, namespace=3, prototype=25, struct=36, typedef=6
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, MassCore, MassEntity

### `Source/Programs/MassTests/Private/MassEntityLLTFixture.h` (Private)


#### struct `UE::Mass::LLT::FMassLLTFixture`  
`struct FMassLLTFixture`  
_L21-45_
- L23 _public member_ `TSharedPtr<FMassEntityManager> EntityManager;`
- L25 _public function_ `FMassLLTFixture()`
- L40 _public function_ `~FMassLLTFixture()`

#### struct `UE::Mass::LLT::FMassLLTEntityFixture`  
`struct FMassLLTEntityFixture : FMassLLTFixture`  
_L50-80_
- inherits: `FMassLLTFixture`
- L52 _public member_ `FMassArchetypeHandle EmptyArchetype;`
- L53 _public member_ `FMassArchetypeHandle FloatsArchetype;`
- L54 _public member_ `FMassArchetypeHandle IntsArchetype;`
- L55 _public member_ `FMassArchetypeHandle FloatsIntsArchetype;`
- L56 _public member_ `FMassArchetypeHandle LargeArchetype;`
- L58 _public member_ `FInstancedStruct InstanceInt;`
- L60 _public function_ `FMassLLTEntityFixture()`

#### struct `UE::Mass::LLT::FMassLLTProcessingPhasesFixture`  
`struct FMassLLTProcessingPhasesFixture : FMassLLTEntityFixture`  
_L86-139_
- inherits: `FMassLLTEntityFixture`
- L88 _public member_ `TSharedPtr<FMassLLTProcessingPhaseManager> PhaseManager;`
- L89 _public member_ `FMassProcessingPhaseConfig PhasesConfig[static_cast<int32>(EMassProcessingPhase::MAX)];`
- L90 _public member_ `int32 TickIndex = -1;`
- L91 _public member_ `FGraphEventRef CompletionEvent;`
- L92 _public member_ `float DeltaTime = 1.f / 30.f;`
- L94 _public function_ `FMassLLTProcessingPhasesFixture()`
- L99 _public function_ `~FMassLLTProcessingPhasesFixture()`
- L109 _public function_ `void InitializePhaseManager()`
- L115 _public function_ `void Tick()`
- L132 _public function_ `void WaitForCompletion()`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Mass` (scope `UE`)
- L15 _namespace_ `namespace LLT` (scope `UE::Mass`)

### `Source/Programs/MassTests/Private/MassEntityLLTProcessors.h` (Private)


#### class `UMassLLTProcessorBase`  
`class UMassLLTProcessorBase : public UMassProcessor`  
_L22-44_
- reflection: `UCLASS()`
- inherits: `UMassProcessor`
- L26 _public prototype_ `UMassLLTProcessorBase();`
- L27 _public function_ `FMassProcessorExecutionOrder& GetMutableExecutionOrder()`
- L28 _public prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L29 _public function_ `virtual bool ShouldAllowQueryBasedPruning(const bool bRuntimeMode = true) const override`
- L30 _public function_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>&) override`
- L32 _public typedef_ `using FExecutionFunction = TFunction<void(FMassEntityManager& EntityManager, FMassExecutionContext& Context)>;`
- L33 _public member_ `FExecutionFunction ExecutionFunction;`
- L34 _public member_ `FMassExecuteFunction ForEachEntityChunkExecutionFunction;`
- L36 _public function_ `void SetShouldAllowMultipleInstances(const bool bInShouldAllowDuplicated)`
- L37 _public prototype_ `void SetUseParallelForEachEntityChunk(bool bEnable);`
- L38 _public prototype_ `void TestExecute(TSharedPtr<FMassEntityManager>& EntityManager);`
- L40 _public function_ `FMassEntityCreationRequirements& GetEntityCreationRequirements()`
- L43 _public member_ `FMassEntityQuery EntityQuery;` — public on purpose, this is a test processor

#### class `UMassLLTProcessor_A`  
`class UMassLLTProcessor_A : public UMassLLTProcessorBase`  
_L50-53_
- reflection: `UCLASS()`
- inherits: `UMassLLTProcessorBase`

#### class `UMassLLTProcessor_B`  
`class UMassLLTProcessor_B : public UMassLLTProcessorBase`  
_L56-59_
- reflection: `UCLASS()`
- inherits: `UMassLLTProcessorBase`

#### class `UMassLLTProcessor_C`  
`class UMassLLTProcessor_C : public UMassLLTProcessorBase`  
_L62-65_
- reflection: `UCLASS()`
- inherits: `UMassLLTProcessorBase`

#### class `UMassLLTProcessor_D`  
`class UMassLLTProcessor_D : public UMassLLTProcessorBase`  
_L68-71_
- reflection: `UCLASS()`
- inherits: `UMassLLTProcessorBase`

#### class `UMassLLTProcessor_E`  
`class UMassLLTProcessor_E : public UMassLLTProcessorBase`  
_L74-77_
- reflection: `UCLASS()`
- inherits: `UMassLLTProcessorBase`

#### class `UMassLLTProcessor_F`  
`class UMassLLTProcessor_F : public UMassLLTProcessorBase`  
_L80-83_
- reflection: `UCLASS()`
- inherits: `UMassLLTProcessorBase`

#### class `UMassLLTProcessor_Floats`  
`class UMassLLTProcessor_Floats : public UMassLLTProcessorBase`  
_L89-95_
- reflection: `UCLASS()`
- inherits: `UMassLLTProcessorBase`
- L93 _public member_ `TArrayView<FTestFragment_Float> Floats;`
- L94 _public prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`

#### class `UMassLLTProcessor_Ints`  
`class UMassLLTProcessor_Ints : public UMassLLTProcessorBase`  
_L98-104_
- reflection: `UCLASS()`
- inherits: `UMassLLTProcessorBase`
- L102 _public member_ `TArrayView<FTestFragment_Int> Ints;`
- L103 _public prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`

#### class `UMassLLTProcessor_FloatsInts`  
`class UMassLLTProcessor_FloatsInts : public UMassLLTProcessorBase`  
_L107-114_
- reflection: `UCLASS()`
- inherits: `UMassLLTProcessorBase`
- L111 _public member_ `TArrayView<FTestFragment_Float> Floats;`
- L112 _public member_ `TArrayView<FTestFragment_Int> Ints;`
- L113 _public prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`

#### class `UMassLLTStaticCounterProcessor`  
`class UMassLLTStaticCounterProcessor : public UMassProcessor`  
_L120-133_
- reflection: `UCLASS()`
- inherits: `UMassProcessor`
- L124 _public prototype_ `UMassLLTStaticCounterProcessor();`
- L125 _public function_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override`
- L129 _public function_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>&) override`
- L130 _public function_ `virtual bool ShouldAllowQueryBasedPruning(const bool bRuntimeMode = true) const override`
- L132 _public member_ `static int32 StaticCounter;`

#### class `UMassLLTProcessorAutoExecuteQuery`  
`class UMassLLTProcessorAutoExecuteQuery : public UMassProcessor`  
_L139-149_
- reflection: `UCLASS()`
- inherits: `UMassProcessor`
- L143 _public prototype_ `UMassLLTProcessorAutoExecuteQuery();`
- L144 _public function_ `void SetAutoExecuteQuery(TSharedPtr<UE::Mass::FQueryExecutor> InAutoExecuteQuery)`
- L148 _public member_ `FMassEntityQuery EntityQuery{ *this };`

#### class `UMassLLTProcessorAutoExecuteQueryComparison`  
`class UMassLLTProcessorAutoExecuteQueryComparison : public UMassLLTProcessorBase`  
_L152-159_
- reflection: `UCLASS()`
- inherits: `UMassLLTProcessorBase`
- L156 _public prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>&) override;`
- L157 _public prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L158 _public member_ `FMassEntityQuery EntityQuery{ *this };`

#### class `UMassLLTProcessorAutoExecuteQueryComparison_Parallel`  
`class UMassLLTProcessorAutoExecuteQueryComparison_Parallel : public UMassLLTProcessorBase`  
_L162-169_
- reflection: `UCLASS()`
- inherits: `UMassLLTProcessorBase`
- L166 _public prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>&) override;`
- L167 _public prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L168 _public member_ `FMassEntityQuery EntityQuery{ *this };`

#### class `UMassLLTCompositeObserverProcessor`  
`class UMassLLTCompositeObserverProcessor : public UMassObserverProcessor`  
_L175-205_
- reflection: `UCLASS()`
- inherits: `UMassObserverProcessor`
- L179 _public function_ `UMassLLTCompositeObserverProcessor()`
- L185 _public member_ `int32 ExecuteCallCount = 0;`
- L187 _public function_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override`
- L192 _public function_ `void SetObservedTypesForTest(std::initializer_list<const UScriptStruct*> Types)`
- L201 _public function_ `void SetObservedOperationsForTest(const EMassObservedOperationFlags InFlags)`

#### class `UMassLLTWorldSubsystem`  
`class UMassLLTWorldSubsystem : public UWorldSubsystem`  
_L211-221_
- reflection: `UCLASS()`
- inherits: `UWorldSubsystem`
- L215 _public prototype_ `void Write(int32 InNumber);`
- L216 _public prototype_ `int32 Read() const;`
- L219 _private prototype_ `UE_MT_DECLARE_RW_ACCESS_DETECTOR(AccessDetector);`
- L220 _private member_ `int32 Number = 0;`

#### struct `TMassExternalSubsystemTraits`  
`template<> struct TMassExternalSubsystemTraits<UMassLLTWorldSubsystem>`  
_L224-231_

#### enum `TMassExternalSubsystemTraits::(anonymous)`  
``  
_L227-230_

#### class `UMassLLTParallelSubsystem`  
`class UMassLLTParallelSubsystem : public UMassSubsystemBase`  
_L234-237_
- reflection: `UCLASS()`
- inherits: `UMassSubsystemBase`

#### struct `TMassExternalSubsystemTraits`  
`template<> struct TMassExternalSubsystemTraits<UMassLLTParallelSubsystem>`  
_L240-247_

#### enum `TMassExternalSubsystemTraits::(anonymous)`  
``  
_L243-246_

#### class `UMassLLTEngineSubsystem`  
`class UMassLLTEngineSubsystem : public UEngineSubsystem`  
_L250-253_
- reflection: `UCLASS()`
- inherits: `UEngineSubsystem`

#### struct `TMassExternalSubsystemTraits`  
`template<> struct TMassExternalSubsystemTraits<UMassLLTEngineSubsystem>`  
_L256-263_

#### enum `TMassExternalSubsystemTraits::(anonymous)`  
``  
_L259-262_

#### class `UMassLLTLocalPlayerSubsystem`  
`class UMassLLTLocalPlayerSubsystem : public ULocalPlayerSubsystem`  
_L266-269_
- reflection: `UCLASS()`
- inherits: `ULocalPlayerSubsystem`

#### struct `TMassExternalSubsystemTraits`  
`template<> struct TMassExternalSubsystemTraits<UMassLLTLocalPlayerSubsystem>`  
_L272-279_

#### enum `TMassExternalSubsystemTraits::(anonymous)`  
``  
_L275-278_

#### class `UMassLLTGameInstanceSubsystem`  
`class UMassLLTGameInstanceSubsystem : public UGameInstanceSubsystem`  
_L282-285_
- reflection: `UCLASS()`
- inherits: `UGameInstanceSubsystem`

#### struct `TMassExternalSubsystemTraits`  
`template<> struct TMassExternalSubsystemTraits<UMassLLTGameInstanceSubsystem>`  
_L288-295_

#### enum `TMassExternalSubsystemTraits::(anonymous)`  
``  
_L291-294_

#### struct `FMassLLTPhaseTickTask`  
`struct FMassLLTPhaseTickTask`  
_L300-314_
- L302 _public prototype_ `FMassLLTPhaseTickTask(const TSharedRef<FMassProcessingPhaseManager>& InPhaseManager, const EMassProcessingPhase InPhase, const float InDeltaTime);`
- L304 _public prototype_ `static TStatId GetStatId();`
- L305 _public prototype_ `static ENamedThreads::Type GetDesiredThread();`
- L306 _public prototype_ `static ESubsequentsMode::Type GetSubsequentsMode();`
- L308 _public prototype_ `void DoTask(ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent);`
- L311 _private member_ `const TSharedRef<FMassProcessingPhaseManager> PhaseManager;`
- L312 _private member_ `const EMassProcessingPhase Phase = EMassProcessingPhase::MAX;`
- L313 _private member_ `const float DeltaTime = 0.f;`

#### struct `FMassLLTProcessingPhaseManager`  
`struct FMassLLTProcessingPhaseManager : public FMassProcessingPhaseManager`  
_L320-324_
- inherits: `FMassProcessingPhaseManager`
- L322 _public prototype_ `void Start(const TSharedPtr<FMassEntityManager>& InEntityManager);`
- L323 _public prototype_ `void OnNewArchetype(const FMassArchetypeHandle& NewArchetype);`

#### Free symbols / members of external scopes

- L228 _enumerator_ `GameThreadOnly = false` (scope `TMassExternalSubsystemTraits::__anon9abee0160103`)
- L229 _enumerator_ `ThreadSafeWrite = false` (scope `TMassExternalSubsystemTraits::__anon9abee0160103`)
- L244 _enumerator_ `GameThreadOnly = false` (scope `TMassExternalSubsystemTraits::__anon9abee0160203`)
- L245 _enumerator_ `ThreadSafeWrite = true` (scope `TMassExternalSubsystemTraits::__anon9abee0160203`)
- L260 _enumerator_ `GameThreadOnly = false` (scope `TMassExternalSubsystemTraits::__anon9abee0160303`)
- L261 _enumerator_ `ThreadSafeWrite = false` (scope `TMassExternalSubsystemTraits::__anon9abee0160303`)
- L276 _enumerator_ `GameThreadOnly = false` (scope `TMassExternalSubsystemTraits::__anon9abee0160403`)
- L277 _enumerator_ `ThreadSafeWrite = false` (scope `TMassExternalSubsystemTraits::__anon9abee0160403`)
- L292 _enumerator_ `GameThreadOnly = false` (scope `TMassExternalSubsystemTraits::__anon9abee0160503`)
- L293 _enumerator_ `ThreadSafeWrite = false` (scope `TMassExternalSubsystemTraits::__anon9abee0160503`)
- L330 _function_ `template<typename T> T* NewTestProcessor(TSharedPtr<FMassEntityManager> EntityManager)`
- L340 _function_ `template<typename TProcessor> int32 SimpleProcessorRun(FMassEntityManager& EntityManager)`
- L346 _function_ `` (scope `SimpleProcessorRun`)

### `Source/Programs/MassTests/Private/MassEntityLLTTypes.h` (Private)


#### struct `FTestFragment_Float`  
`struct FTestFragment_Float : public FMassFragment`  
_L14-20_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- L17 _public member_ `float Value = 0;`
- L19 _public function_ `FTestFragment_Float(const float InValue = 0.f) : Value(InValue)`

#### struct `FTestFragment_Int`  
`struct FTestFragment_Int : public FMassFragment`  
_L23-33_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- L28 _public member_ `int32 Value = 0;` — `UPROPERTY()`
- L30 _public function_ `FTestFragment_Int(const int32 InValue = 0) : Value(InValue)`
- L32 _public member_ `static constexpr int32 TestIntValue = 123456;`

#### struct `FTestFragment_Bool`  
`struct FTestFragment_Bool : public FMassFragment`  
_L36-42_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- L39 _public member_ `bool bValue = false;`
- L41 _public function_ `FTestFragment_Bool(const bool bInValue = false) : bValue(bInValue)`

#### struct `FTestFragment_Large`  
`struct FTestFragment_Large : public FMassFragment`  
_L45-56_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- L50 _public member_ `uint8 Value[64];` — `UPROPERTY()`
- L52 _public function_ `FTestFragment_Large(uint8 Fill = 0)`

#### struct `FTestFragment_Array`  
`struct FTestFragment_Array : public FMassFragment`  
_L59-70_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- L64 _public member_ `TArray<int32> Value;` — `UPROPERTY()`
- L66 _public function_ `FTestFragment_Array(uint8 Num = 0)`

#### struct `TMassFragmentTraits`  
`template<> struct TMassFragmentTraits<FTestFragment_Array> final`  
_L73-79_

#### enum `TMassFragmentTraits::(anonymous)`  
``  
_L76-78_

#### struct `FFragmentWithSharedPtr`  
`struct FFragmentWithSharedPtr : public FMassFragment`  
_L82-92_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- L86 _public member_ `TSharedPtr<int32> Data;`
- L88 _public prototype_ `FFragmentWithSharedPtr() = default;`
- L89 _public function_ `FFragmentWithSharedPtr(TSharedPtr<int32>& InData) : Data(InData)`

#### struct `TMassFragmentTraits`  
`template<> struct TMassFragmentTraits<FFragmentWithSharedPtr> final`  
_L95-101_

#### enum `TMassFragmentTraits::(anonymous)`  
``  
_L98-100_

#### struct `FTestChunkFragment_Int`  
`struct FTestChunkFragment_Int : public FMassChunkFragment`  
_L107-115_
- reflection: `USTRUCT()`
- inherits: `FMassChunkFragment`
- L112 _public member_ `int32 Value = 0;` — `UPROPERTY()`
- L114 _public function_ `FTestChunkFragment_Int(const int32 InValue = 0) : Value(InValue)`

#### struct `FTestChunkFragment_Float`  
`struct FTestChunkFragment_Float : public FMassChunkFragment`  
_L118-126_
- reflection: `USTRUCT()`
- inherits: `FMassChunkFragment`
- L123 _public member_ `float Value = 0.f;` — `UPROPERTY()`
- L125 _public function_ `FTestChunkFragment_Float(const float InValue = 0.f) : Value(InValue)`

#### struct `FTestSharedFragment_Int`  
`struct FTestSharedFragment_Int : public FMassSharedFragment`  
_L132-142_
- reflection: `USTRUCT()`
- inherits: `FMassSharedFragment`
- L134 _public typedef_ `using FValueType = int32;`
- L139 _public member_ `int32 Value = 0;` — `UPROPERTY()`
- L141 _public function_ `FTestSharedFragment_Int(const int32 InValue = 0) : Value(InValue)`

#### struct `FTestSharedFragment_Array`  
`struct FTestSharedFragment_Array : public FMassSharedFragment`  
_L145-156_
- reflection: `USTRUCT()`
- inherits: `FMassSharedFragment`
- L147 _public typedef_ `using FValueType = TArray<int32>;`
- L152 _public member_ `TArray<int32> Value;` — `UPROPERTY()`
- L154 _public prototype_ `FTestSharedFragment_Array() = default;`
- L155 _public function_ `FTestSharedFragment_Array(TArray<int32>&& InValue) : Value(MoveTemp(InValue))`

#### struct `TMassSharedFragmentTraits`  
`template<> struct TMassSharedFragmentTraits<FTestSharedFragment_Int> final`  
_L159-165_

#### enum `TMassSharedFragmentTraits::(anonymous)`  
``  
_L162-164_

#### struct `FTestConstSharedFragment_Int`  
`struct FTestConstSharedFragment_Int : public FMassConstSharedFragment`  
_L168-178_
- reflection: `USTRUCT()`
- inherits: `FMassConstSharedFragment`
- L170 _public typedef_ `using FValueType = int32;`
- L175 _public member_ `int32 Value = 0;` — `UPROPERTY()`
- L177 _public function_ `FTestConstSharedFragment_Int(const int32 InValue = 0) : Value(InValue)`

#### struct `FTestSharedFragment_Float`  
`struct FTestSharedFragment_Float : public FMassSharedFragment`  
_L181-191_
- reflection: `USTRUCT()`
- inherits: `FMassSharedFragment`
- L183 _public typedef_ `using FValueType = float;`
- L188 _public member_ `float Value = 0.f;` — `UPROPERTY()`
- L190 _public function_ `FTestSharedFragment_Float(const float InValue = 0) : Value(InValue)`

#### struct `FTestConstSharedFragment_Float`  
`struct FTestConstSharedFragment_Float : public FMassConstSharedFragment`  
_L194-204_
- reflection: `USTRUCT()`
- inherits: `FMassConstSharedFragment`
- L196 _public typedef_ `using FValueType = float;`
- L201 _public member_ `float Value = 0.f;` — `UPROPERTY()`
- L203 _public function_ `FTestConstSharedFragment_Float(const float InValue = 0) : Value(InValue)`

#### struct `FTestFragment_Tag`  
`struct FTestFragment_Tag : public FMassTag`  
_L210-213_
- reflection: `USTRUCT()`
- inherits: `FMassTag`

#### struct `FTestTag_A`  
`struct FTestTag_A : public FMassTag`  
_L216-219_
- reflection: `USTRUCT()`
- inherits: `FMassTag`

#### struct `FTestTag_B`  
`struct FTestTag_B : public FMassTag`  
_L222-225_
- reflection: `USTRUCT()`
- inherits: `FMassTag`

#### struct `FTestTag_C`  
`struct FTestTag_C : public FMassTag`  
_L228-231_
- reflection: `USTRUCT()`
- inherits: `FMassTag`

#### struct `FTestTag_D`  
`struct FTestTag_D : public FMassTag`  
_L234-237_
- reflection: `USTRUCT()`
- inherits: `FMassTag`

#### struct `FTestFragment_SparseInt`  
`struct FTestFragment_SparseInt : public FMassSparseFragment`  
_L243-253_
- reflection: `USTRUCT()`
- inherits: `FMassSparseFragment`
- L247 _public function_ `FTestFragment_SparseInt(const int32 InValue = 0) : Value(InValue)`
- L252 _public member_ `int32 Value = 0;`

#### struct `FTestFragment_SparseFloat`  
`struct FTestFragment_SparseFloat : public FMassSparseFragment`  
_L256-266_
- reflection: `USTRUCT()`
- inherits: `FMassSparseFragment`
- L260 _public function_ `FTestFragment_SparseFloat(const float InValue = 0.f) : Value(InValue)`
- L265 _public member_ `float Value = 0.f;`

#### struct `FTestTag_SparseA`  
`struct FTestTag_SparseA : public FMassSparseTag`  
_L269-272_
- reflection: `USTRUCT()`
- inherits: `FMassSparseTag`

#### struct `FTestTag_SparseB`  
`struct FTestTag_SparseB : public FMassSparseTag`  
_L275-278_
- reflection: `USTRUCT()`
- inherits: `FMassSparseTag`

#### struct `FTestFragment_EntityHandle`  
`struct FTestFragment_EntityHandle : public FMassFragment`  
_L284-295_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- L288 _public member_ `FMassEntityHandle Value;`
- L290 _public function_ `FTestFragment_EntityHandle(const FMassEntityHandle InValue = FMassEntityHandle()) : Value(InValue)`

#### Free symbols / members of external scopes

- L77 _enumerator_ `AuthorAcceptsItsNotTriviallyCopyable = true` (scope `TMassFragmentTraits::__anone9192d380103`)
- L99 _enumerator_ `AuthorAcceptsItsNotTriviallyCopyable = true` (scope `TMassFragmentTraits::__anone9192d380203`)
- L163 _enumerator_ `GameThreadOnly = true` (scope `TMassSharedFragmentTraits::__anone9192d380303`)
