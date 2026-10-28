# Developer / FunctionalTesting

- module root: `Source/Developer/FunctionalTesting`
- headers: 21; symbols: 710
- symbol kinds: class=28, delegate=4, enum=8, enumerator=27, externvar=2, function=41, macro=8, member=244, namespace=3, prototype=326, struct=19
- PrivateDependencyModuleNames: AIModule, AssetRegistry, AutomationController, Core, CoreUObject, EditorFramework, Engine, ImageWrapper, LevelEditor, MessageLog, NavigationSystem, RHI, RenderCore, SessionFrontend, Slate, SlateCore, SourceControl, UMG, UnrealEd

### `Source/Developer/FunctionalTesting/Classes/FuncTestRenderingComponent.h` (Public)


#### class `UFuncTestRenderingComponent`  
`class UFuncTestRenderingComponent : public UPrimitiveComponent`  
_L13-25_
- reflection: `UCLASS(hidecategories=Object, editinlinenew)`
- inherits: `UPrimitiveComponent`
- L18 _private prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy() override;`
- L19 _private function_ `virtual bool ShouldRecreateProxyOnUpdateTransform() const override`
- L23 _private prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform &LocalToWorld) const override;`

### `Source/Developer/FunctionalTesting/Classes/FunctionalAITest.h` (Public)


#### struct `FAITestSpawnInfoBase`  
`struct FAITestSpawnInfoBase`  
_L28-62_
- reflection: `USTRUCT(BlueprintType)`
- desc: FAITestSpawnInfoBase Base struct defining where & when to spawn. Used within a FAITestSpawnSetBase class.
- L34 _public member_ `TObjectPtr<AActor> SpawnLocation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=AISpawn)` — Where should AI be spawned
- L37 _public member_ `int32 NumberToSpawn;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=AISpawn, meta=(UIMin=1, ClampMin=1))`
- L41 _public member_ `float SpawnDelay;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AISpawn, meta = (UIMin = 0, ClampMin = 0))` — delay between consecutive spawn attempts
- L45 _public member_ `float PreSpawnDelay;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AISpawn, meta = (UIMin = 0, ClampMin = 0))` — delay before attempting first spawn
- L48 _public member_ `FName SpawnSetName;` — Gets filled owning spawn set upon game start
- L50 _public function_ `FAITestSpawnInfoBase() : SpawnLocation(nullptr) , NumberToSpawn(1) , SpawnDelay(0.0f) , PreSpawnDelay(0.0f)`
- L57 _public prototype_ `virtual ~FAITestSpawnInfoBase() = default;`
- L59 _public function_ `virtual bool IsValid() const`
- L61 _public prototype_ `virtual bool Spawn(AFunctionalAITestBase* AITest) const PURE_VIRTUAL(, return false;);`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FAITestSpawnInfoBase> : public TStructOpsTypeTraitsBase2<FAITestSpawnInfoBase>`  
_L65-71_
- inherits: `TStructOpsTypeTraitsBase2<FAITestSpawnInfoBase>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L68-70_

#### struct `FAITestSpawnInfo`  
`struct FAITestSpawnInfo : public FAITestSpawnInfoBase`  
_L79-105_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FAITestSpawnInfoBase`
- desc: FAITestSpawnInfo Generic AI Test Spawn Info used in FAITestSpawnSet within a generic AFunctionalAITest test.
- L85 _public member_ `TSubclassOf<class APawn> PawnClass;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=AISpawn)` — Determines AI to be spawned
- L89 _public member_ `TSubclassOf<class AAIController> ControllerClass;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=AISpawn)` — class to override default pawn's controller class. If None the default will be used
- L92 _public member_ `FGenericTeamId TeamID;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=AISpawn)`
- L96 _public member_ `TObjectPtr<class UBehaviorTree> BehaviorTree;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=AISpawn)` — if set will be applied to spawned AI
- L98 _public function_ `FAITestSpawnInfo() : BehaviorTree(nullptr)`
- L102 _public function_ `FORCEINLINE virtual bool IsValid() const override`
- L104 _public prototype_ `virtual bool Spawn(AFunctionalAITestBase* AITest) const override;`

#### struct `FPendingDelayedSpawn`  
`struct FPendingDelayedSpawn`  
_L114-146_
- reflection: `USTRUCT(BlueprintType)`
- desc: FPendingDelayedSpawn Struct defining a pending spawn request within a AFunctionalAITestBase.
- L118 _public member_ `uint32 NumberToSpawnLeft;`
- L119 _public member_ `float TimeToNextSpawn;`
- L120 _public member_ `bool bFinished;`
- L123 _public member_ `uint32 SpawnSetIndex;` — Index to spawn in the SpawnSets
- L126 _public member_ `uint32 SpawnInfoIndex;` — Index to spawn in the SpawnInfoContainer's spawnset
- L128 _public function_ `FPendingDelayedSpawn() : NumberToSpawnLeft(uint32(-1)) , TimeToNextSpawn(FLT_MAX) , bFinished(true) , SpawnSetIndex(uint32(-1)) , SpawnInfoIndex(uint32(-1))`
- L136 _public function_ `FPendingDelayedSpawn(const uint32 InSpawnSetIndex, const uint32 InSpawnInfoIndex, const int32 InNumberToSpawnLeft, const float InTimeToNextSpawn) : NumberToSpawnLeft(InNumberToSpawnLeft) , TimeToNextSpawn(InTimeToNextSpawn) , bFinished(false) , SpawnSetIndex(InSpawnSetIndex) , SpawnInfoIndex(InSpawnInfoIndex)`
- L145 _public prototype_ `void Tick(float TimeDelta, AFunctionalAITestBase* AITest);`

#### struct `FAITestSpawnSetBase`  
`struct FAITestSpawnSetBase`  
_L154-190_
- reflection: `USTRUCT(BlueprintType)`
- desc: FAITestSpawnSetBase Base struct defining an AI Test Spawn Set that are used in AFunctionalAITestBase tests.
- L160 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=AISpawn)` — give the set a name to help identify it if need be
- L163 _public member_ `uint32 bEnabled:1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=AISpawn)`
- L167 _public member_ `TObjectPtr<AActor> FallbackSpawnLocation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AISpawn)` — location used for spawning if spawn info doesn't define one
- L169 _public function_ `FAITestSpawnSetBase() : bEnabled(true) , FallbackSpawnLocation(nullptr)`
- L174 _public prototype_ `virtual ~FAITestSpawnSetBase() = default;`
- L177 _public prototype_ `virtual const FAITestSpawnInfoBase* GetSpawnInfo(const int32 SpawnInfoIndex) const PURE_VIRTUAL(, return nullptr;);` — Return the FAITestSpawnInfoBase at this index of the SpawnInfoContainer array. Const-correct version.
- L180 _public prototype_ `virtual FAITestSpawnInfoBase* GetSpawnInfo(const int32 SpawnInfoIndex) PURE_VIRTUAL(, return nullptr;);` — Return the FAITestSpawnInfoBase at this index of the SpawnInfoContainer array.
- L183 _public prototype_ `virtual bool IsValidSpawnInfoIndex(const int32 Index) const PURE_VIRTUAL(, return false;);` — Return whether the index is valid in the SpawnInfoContainer array.
- L186 _public prototype_ `virtual void ForEachSpawnInfo(TFunctionRef<void(const FAITestSpawnInfoBase&)> Predicate) const PURE_VIRTUAL(, );` — Pure virtual method to iterate through the spawn info container and execute Predicate on each in a const-correct way.
- L189 _public prototype_ `virtual void ForEachSpawnInfo(TFunctionRef<void(FAITestSpawnInfoBase&)> Predicate) PURE_VIRTUAL(,);` — Pure virtual method to iterate through the spawn info container and execute Predicate on each.

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FAITestSpawnSetBase> : public TStructOpsTypeTraitsBase2<FAITestSpawnSetBase>`  
_L192-198_
- inherits: `TStructOpsTypeTraitsBase2<FAITestSpawnSetBase>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L195-197_

#### struct `FAITestSpawnSet`  
`struct FAITestSpawnSet : public FAITestSpawnSetBase`  
_L206-231_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FAITestSpawnSetBase`
- desc: FAITestSpawnSet Generic AI Test Spawn Set that is used in regular AFunctionalAITest tests.
- L210 _public function_ `FAITestSpawnSet()`
- L213 _public prototype_ `virtual void ForEachSpawnInfo(TFunctionRef<void(const FAITestSpawnInfoBase&)> Predicate) const override;` — To iterate through the spawn info container and execute Predicate on each in a const-correct way.
- L216 _public prototype_ `virtual void ForEachSpawnInfo(TFunctionRef<void(FAITestSpawnInfoBase&)> Predicate) override;` — To iterate through the spawn info container and execute Predicate on each.
- L219 _public prototype_ `virtual const FAITestSpawnInfoBase* GetSpawnInfo(const int32 SpawnInfoIndex) const override;` — Return the FAITestSpawnInfoBase at this index of the SpawnInfoContainer array. Const-correct version.
- L222 _public prototype_ `virtual FAITestSpawnInfoBase* GetSpawnInfo(const int32 SpawnInfoIndex) override;` — Return the FAITestSpawnInfoBase at this index of the SpawnInfoContainer array.
- L225 _public prototype_ `virtual bool IsValidSpawnInfoIndex(const int32 Index) const override;` — Return whether the index is valid in the SpawnInfoContainer array.
- L230 _protected member_ `TArray<FAITestSpawnInfo> SpawnInfoContainer;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AISpawn)` — what to spawn

#### class `AFunctionalAITestBase`  
`class AFunctionalAITestBase : public AFunctionalTest`  
_L240-357_
- reflection: `UCLASS(MinimalAPI, Abstract, BlueprintType)`
- inherits: `AFunctionalTest`
- desc: AFunctionalAITestBase Base abstract class defining a Functional AI Test. You can derive from this base class to create a test with a different type of SpawnSets.
- L245 _public prototype_ `AFunctionalAITestBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L248 _public prototype_ `virtual void ForEachSpawnSet(TFunctionRef<void(const FAITestSpawnSetBase&)> Predicate) const PURE_VIRTUAL(, );` — Iterate through the list of spawn sets and execute Predicate on each in a const-correct way.
- L251 _public prototype_ `virtual void ForEachSpawnSet(TFunctionRef<void(FAITestSpawnSetBase&)> Predicate) PURE_VIRTUAL(, );` — Iterate through the list of spawn sets and execute Predicate on each.
- L254 _public prototype_ `virtual void RemoveSpawnSetIfPredicate(TFunctionRef<bool(FAITestSpawnSetBase&)> Predicate) PURE_VIRTUAL(, );` — Iterate through the list of spawn sets and remove the spawn set if Predicate returns true.
- L257 _public prototype_ `virtual const FAITestSpawnSetBase* GetSpawnSet(const int32 SpawnSetIndex) const PURE_VIRTUAL(, return nullptr;);` — Return the SpawnSet at this index of the SpawnSets array. Const-correct version.
- L260 _public prototype_ `virtual FAITestSpawnSetBase* GetSpawnSet(const int32 SpawnSetIndex) PURE_VIRTUAL(,return nullptr;);` — Return the SpawnSet at this index of the SpawnSets array.
- L263 _public prototype_ `const FAITestSpawnInfoBase* GetSpawnInfo(const int32 SpawnSetIndex, const int32 SpawnInfoIndex) const;` — Return the SpawnInfo at SpawnInfoIndexof the SpawnSet at SpawnSetIndex. Const-correct version.
- L266 _public prototype_ `FAITestSpawnInfoBase* GetSpawnInfo(const int32 SpawnSetIndex, const int32 SpawnInfoIndex);` — Return the SpawnInfo at SpawnInfoIndexof the SpawnSet at SpawnSetIndex.
- L269 _public prototype_ `virtual bool IsValidSpawnSetIndex(const int32 Index) const PURE_VIRTUAL(, return false;);` — Return whether the index is valid in the SpawnSets array.
- L279 _public prototype_ `bool Spawn(const int32 SpawnSetIndex, const int32 SpawnInfoIndex);` — Spawn this AI at this SpawnInfoIndex of the SpawnSetIndex spawn set. @param SpawnSetIndex	The index of the spawn set in the SpawnSets array @param SpawnInfoIndex	The index of the spawn info in the spawn set @return True if spawn was successful.
- L282 _protected member_ `float SpawnLocationRandomizationRange;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AITest, meta = (UIMin = "0.0"))`
- L285 _protected member_ `TArray<TObjectPtr<APawn>> SpawnedPawns;` — `UPROPERTY(BlueprintReadOnly, Category=AITest)`
- L288 _protected member_ `TArray<FPendingDelayedSpawn> PendingDelayedSpawns;` — `UPROPERTY(BlueprintReadOnly, Category = AITest)`
- L291 _protected member_ `int32 CurrentSpawnSetIndex;` — `UPROPERTY(BlueprintReadOnly, Category = AITest)`
- L294 _protected member_ `FString CurrentSpawnSetName;` — `UPROPERTY(BlueprintReadOnly, Category = AITest)`
- L298 _protected member_ `FFunctionalTestAISpawned OnAISpawned;` — `UPROPERTY(BlueprintAssignable)` — Called when a single AI finished spawning
- L302 _protected member_ `FFunctionalTestEventSignature OnAllAISPawned;` — `UPROPERTY(BlueprintAssignable)` — Called when a all AI finished spawning
- L306 _protected member_ `FVector NavMeshDebugOrigin;` — `UPROPERTY(EditAnywhere, Category = NavMeshDebug, meta = (MakeEditWidget = ""))` — navmesh debug: log navoctree modifiers around this point
- L310 _protected member_ `FVector NavMeshDebugExtent;` — `UPROPERTY(EditAnywhere, Category = NavMeshDebug)` — navmesh debug: extent around NavMeshDebugOrigin
- L314 _protected member_ `uint32 bWaitForNavMesh : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AITest)` — if set, ftest will postpone start until navmesh is fully generated
- L318 _protected member_ `uint32 bDebugNavMeshOnTimeout : 1;` — `UPROPERTY(EditAnywhere, Category = NavMeshDebug)` — if set, ftest will postpone start until navmesh is fully generated
- L320 _protected member_ `uint32 bSingleSetRun:1;`
- L324 _public prototype_ `virtual bool IsOneOfSpawnedPawns(AActor* Actor);` — `UFUNCTION(BlueprintCallable, Category = "Development")`
- L328 _protected prototype_ `virtual void BeginPlay() override;`
- L331 _public prototype_ `virtual void Tick(float DeltaSeconds) override;`
- L334 _public prototype_ `virtual bool RunTest(const TArray<FString>& Params = TArray<FString>()) override;`
- L335 _public prototype_ `virtual void StartTest() override;`
- L336 _public prototype_ `virtual void OnTimeout() override;`
- L337 _public prototype_ `virtual bool IsReady_Implementation() override;`
- L338 _public prototype_ `virtual bool WantsToRunAgain() const override;`
- L339 _public prototype_ `virtual void GatherRelevantActors(TArray<AActor*>& OutActors) const override;`
- L340 _public prototype_ `virtual void CleanUp() override;`
- L341 _public prototype_ `virtual FString GetAdditionalTestFinishedMessage(EFunctionalTestResult TestResult) const override;`
- L342 _public prototype_ `virtual FString GetReproString() const override;`
- L344 _public prototype_ `void AddSpawnedPawn(APawn& SpawnedPawn);`
- L346 _public prototype_ `FVector GetRandomizedLocation(const FVector& Location) const;`
- L350 _protected prototype_ `void KillOffSpawnedPawns();`
- L351 _protected prototype_ `void ClearPendingDelayedSpawns();`
- L352 _protected prototype_ `void StartSpawning();`
- L353 _protected prototype_ `void OnSpawningFailure();`
- L354 _protected prototype_ `bool IsNavMeshReady() const;`
- L356 _protected member_ `FTimerHandle NavmeshDelayTimer;`

#### class `AFunctionalAITest`  
`class AFunctionalAITest : public AFunctionalAITestBase`  
_L365-391_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `AFunctionalAITestBase`
- desc: FuntionalAITest Functional AI Test using a regular FAITestSpawnSet as a default SpawnSet class type.
- L371 _public prototype_ `virtual void ForEachSpawnSet(TFunctionRef<void(const FAITestSpawnSetBase&)> Predicate) const override;` — Iterate through the list of spawn sets and execute Predicate on each in a const-correct way.
- L374 _public prototype_ `virtual void ForEachSpawnSet(TFunctionRef<void(FAITestSpawnSetBase&)> Predicate) override;` — Iterate through the list of spawn sets and execute Predicate on each.
- L377 _public prototype_ `virtual void RemoveSpawnSetIfPredicate(TFunctionRef<bool(FAITestSpawnSetBase&)> Predicate) override;` — Iterate through the list of spawn sets and remove the spawn set if Predicate returns true.
- L380 _public prototype_ `virtual const FAITestSpawnSetBase* GetSpawnSet(const int32 SpawnSetIndex) const override;` — Return the SpawnSet at this index of the SpawnSets array. Const-correct version.
- L383 _public prototype_ `virtual FAITestSpawnSetBase* GetSpawnSet(const int32 SpawnSetIndex) override;` — Return the SpawnSet at this index of the SpawnSets array.
- L386 _public prototype_ `virtual bool IsValidSpawnSetIndex(const int32 Index) const override;` — Return whether the index is valid in the SpawnSets array.
- L390 _protected member_ `TArray<FAITestSpawnSet> SpawnSets;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=AITest)`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API FUNCTIONALTESTING_API`
- L20 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FFunctionalTestAISpawned, AAIController*, Controller, APawn*, Pawn);`
- L20 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FFunctionalTestAISpawned, AAIController*, Controller, APawn*, Pawn);`
- L69 _enumerator_ `WithPureVirtual = true` (scope `TStructOpsTypeTraits::__anonda5e05bb0103`)
- L196 _enumerator_ `WithPureVirtual = true` (scope `TStructOpsTypeTraits::__anonda5e05bb0203`)

### `Source/Developer/FunctionalTesting/Classes/FunctionalTest.h` (Public)


#### class `FFunctionalTestExternalProfiler`  
`class FFunctionalTestExternalProfiler : public FScopedExternalProfilerBase`  
_L28-33_
- inherits: `FScopedExternalProfilerBase`
- desc: Experimental effort at automated cpu captures from the functional testing.
- L31 _public function_ `void StartProfiler(const bool bWantPause)`
- L32 _public function_ `void StopProfiler()`

#### struct `FStatsData`  
`struct FStatsData`  
_L36-46_
- L38 _public function_ `FStatsData() :NumFrames(0), SumTimeSeconds(0.0f)`
- L40 _public member_ `uint32 NumFrames;`
- L41 _public member_ `float SumTimeSeconds;`
- L42 _public member_ `FStatisticalFloat FrameTimeTracker;`
- L43 _public member_ `FStatisticalFloat GameThreadTimeTracker;`
- L44 _public member_ `FStatisticalFloat RenderThreadTimeTracker;`
- L45 _public member_ `FStatisticalFloat GPUTimeTracker;`

#### struct `FPerfStatsRecord`  
`struct FPerfStatsRecord`  
_L49-79_
- desc: A set of simple perf stats recorded over a period of frames.
- L51 _public prototype_ `FPerfStatsRecord(FString InName);`
- L53 _public member_ `FString Name;`
- L56 _public member_ `FStatsData Record;` — Stats data for the period we're interested in timing.
- L58 _public member_ `FStatsData Baseline;` — Stats data for the baseline.
- L60 _public member_ `float GPUBudget;`
- L61 _public member_ `float RenderThreadBudget;`
- L62 _public member_ `float GameThreadBudget;`
- L64 _public prototype_ `void SetBudgets(float InGPUBudget, float InRenderThreadBudget, float InGameThreadBudget);`
- L65 _public prototype_ `void Sample(UWorld* Owner, float DeltaSeconds, bool bBaseline);`
- L67 _public prototype_ `FString GetReportString()const;`
- L68 _public prototype_ `FString GetBaselineString()const;`
- L69 _public prototype_ `FString GetRecordString()const;`
- L70 _public prototype_ `FString GetOverBudgetString()const;`
- L72 _public prototype_ `void GetGPUTimes(double& OutMin, double& OutMax, double& OutAvg)const;`
- L73 _public prototype_ `void GetGameThreadTimes(double& OutMin, double& OutMax, double& OutAvg)const;`
- L74 _public prototype_ `void GetRenderThreadTimes(double& OutMin, double& OutMax, double& OutAvg)const;`
- L76 _public prototype_ `bool IsWithinGPUBudget()const;`
- L77 _public prototype_ `bool IsWithinGameThreadBudget()const;`
- L78 _public prototype_ `bool IsWithinRenderThreadBudget()const;`

#### enum `EComparisonMethod`  
`enum class EComparisonMethod : uint8`  
_L82-90_
- reflection: `UENUM(BlueprintType)`
- L84 _public enumerator_ `Equal_To`
- L85 _public enumerator_ `Not_Equal_To`
- L86 _public enumerator_ `Greater_Than_Or_Equal_To`
- L87 _public enumerator_ `Less_Than_Or_Equal_To`
- L88 _public enumerator_ `Greater_Than`
- L89 _public enumerator_ `Less_Than`

#### class `UAutomationPerformaceHelper`  
`class UAutomationPerformaceHelper : public UObject`  
_L100-192_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UObject`
- desc: Class for use with functional tests which provides various performance measuring features. Recording of basic, unintrusive performance stats. Automatic captures using external CPU and GPU profilers. Triggering and ending of writing full stats to a file.
- L104 _private member_ `TArray<FPerfStatsRecord> Records;`
- L105 _private member_ `bool bRecordingBasicStats;`
- L106 _private member_ `bool bRecordingBaselineBasicStats;`
- L107 _private member_ `bool bRecordingCPUCapture;`
- L108 _private member_ `bool bRecordingStatsFile;`
- L111 _private member_ `bool bGPUTraceIfBelowBudget;` — If true we check the GPU times vs GPU budget each tick and trigger a GPU trace if we fall below budget.
- L115 _public prototype_ `UAutomationPerformaceHelper();`
- L118 _public prototype_ `virtual UWorld* GetWorld() const override;` — UObject interface
- L124 _public prototype_ `void Tick(float DeltaSeconds);` — `UFUNCTION(BlueprintCallable, Category = Perf)`
- L128 _public prototype_ `void Sample(float DeltaSeconds);` — `UFUNCTION(BlueprintCallable, Category = Perf)` — Adds a sample to the stats counters for the current performance stats record.
- L131 _public prototype_ `void BeginRecordingBaseline(FString RecordName);` — `UFUNCTION(BlueprintCallable, Category = Perf)` — Begins recording a new named performance stats record. We start by recording the baseline
- L134 _public prototype_ `void EndRecordingBaseline();` — `UFUNCTION(BlueprintCallable, Category = Perf)` — Stops recording the baseline and moves to the main record.
- L137 _public prototype_ `void BeginRecording(FString RecordName, float InGPUBudget, float InRenderThreadBudget, float InGameThreadBudget);` — `UFUNCTION(BlueprintCallable, Category = Perf)` — Begins recording a new named performance stats record. We start by recording the baseline.
- L140 _public prototype_ `void EndRecording();` — `UFUNCTION(BlueprintCallable, Category = Perf)` — Stops recording performance stats.
- L143 _public prototype_ `void WriteLogFile(const FString& CaptureDir, const FString& CaptureExtension);` — `UFUNCTION(BlueprintCallable, Category = Perf)` — Writes the current set of performance stats records to a csv file in the profiling directory. An additional directory and an extension override can also be used.
- L146 _public prototype_ `bool IsRecording() const;` — `UFUNCTION(BlueprintCallable, Category = Perf)` — Returns true if this stats tracker is currently recording performance stats.
- L150 _public prototype_ `void OnBeginTests();` — `UFUNCTION(BlueprintCallable, Category = Perf)` — Does any init work across all tests..
- L153 _public prototype_ `void OnAllTestsComplete();` — `UFUNCTION(BlueprintCallable, Category = Perf)` — Does any final work needed as all tests are complete.
- L155 _public prototype_ `const FPerfStatsRecord* GetCurrentRecord() const;`
- L156 _public prototype_ `FPerfStatsRecord* GetCurrentRecord();`
- L159 _public prototype_ `bool IsCurrentRecordWithinGPUBudget() const;` — `UFUNCTION(BlueprintCallable, Category = Perf)`
- L161 _public prototype_ `bool IsCurrentRecordWithinGameThreadBudget() const;` — `UFUNCTION(BlueprintCallable, Category = Perf)`
- L163 _public prototype_ `bool IsCurrentRecordWithinRenderThreadBudget() const;` — `UFUNCTION(BlueprintCallable, Category = Perf)`
- L170 _public prototype_ `void StartCPUProfiling();` — `UFUNCTION(BlueprintCallable, Category = Perf)` — Communicates with external profiler to being a CPU capture.
- L173 _public prototype_ `void StopCPUProfiling();` — `UFUNCTION(BlueprintCallable, Category = Perf)` — Communicates with external profiler to end a CPU capture.
- L176 _public prototype_ `void TriggerGPUTraceIfRecordFallsBelowBudget();` — `UFUNCTION(BlueprintCallable, Category = Perf)` — Will trigger a GPU trace next time the current test falls below GPU budget.
- L179 _public prototype_ `void BeginStatsFile(const FString& RecordName);` — `UFUNCTION(BlueprintCallable, Category = Perf)` — Begins recording stats to a file.
- L182 _public prototype_ `void EndStatsFile();` — `UFUNCTION(BlueprintCallable, Category = Perf)` — Ends recording stats to a file.
- L185 _public member_ `FFunctionalTestExternalProfiler ExternalProfiler;`
- L189 _public member_ `FString OutputFileBase;` — The path and base name for all output files.
- L191 _public member_ `FString StartOfTestingTime;`

#### enum `EFunctionalTestResult`  
`enum class EFunctionalTestResult : uint8`  
_L195-208_
- reflection: `UENUM(BlueprintType)`
- L202 _public enumerator_ `Default` — When finishing a test if you use Default, you're not explicitly stating if the test passed or failed. Instead you're instead allowing any tested assertions to have decided that for you.  Even if you do explicitly log success, it can be overturned by errors that occurred during the test.
- L203 _public enumerator_ `Invalid`
- L204 _public enumerator_ `Error`
- L205 _public enumerator_ `Running`
- L206 _public enumerator_ `Failed`
- L207 _public enumerator_ `Succeeded`

#### struct `FFunctionalTestInfo`  
`struct FFunctionalTestInfo`  
_L223-231_
- desc: Registration information for an individual test
- L225 _public function_ `FFunctionalTestInfo(FString BeautifiedName, FString TestCommand, FString TestTags) : BeautifiedName(BeautifiedName), TestCommand(TestCommand), TestTags(TestTags)`
- L228 _public member_ `FString BeautifiedName;`
- L229 _public member_ `FString TestCommand;`
- L230 _public member_ `FString TestTags;`

#### enum `EFunctionalTestLogHandling`  
`enum class EFunctionalTestLogHandling : uint8`  
_L234-243_
- reflection: `UENUM(BlueprintType)`
- L240 _public enumerator_ `ProjectDefault` — How do log categories affect rest results. ProjectDefault can be set in DefaultEngine.ini but individual tests can override that
- L241 _public enumerator_ `OutputIsError`
- L242 _public enumerator_ `OutputIgnored`

#### class `AFunctionalTest`  
`class AFunctionalTest : public AActor`  
_L249-848_
- reflection: `UCLASS(MinimalAPI, hidecategories=( Actor, Input, Rendering, HLOD ), Blueprintable)`
- inherits: `AActor`
- L254 _public prototype_ `AFunctionalTest(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L257 _public member_ `FString TestLabel;` — `UPROPERTY(BlueprintReadOnly, Category = "Functional Testing")`
- L265 _public member_ `FString Author;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Functional Testing", meta = (MultiLine = "true", DisplayName = "Owner"))` — The owner is the group or person responsible for the test. Generally you should use a group name like 'Editor' or 'Rendering'. When a test fails it may not be obvious who should investigate so this provides a associate responsible groups with tests.
- L271 _public member_ `FString Description;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Functional Testing", meta = (MultiLine = "true"))` — A description of the test, like what is this test trying to determine.
- L279 _public member_ `FString TestTags;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Functional Testing")` — Tags describing this test separated by square brackets, such as '[dog]' or '[cat]' or '[Graphics][prio0][unstable]'. Tags can be used to run subsets of tests, or to categorize data in test reports. Deprecating, please use "Edit Test Tags" instead.
- L286 _public prototype_ `void EditTags();` — `UFUNCTION(CallInEditor, Category="Functional Testing", DisplayName = "Edit Test Tags", meta=(DisplayAfter="TestTags"))` — Edit tags button that will open the Automation tab in the Session Frontend window then show the tag editor for this test.
- L290 _public prototype_ `FString GetBeautifiedName();` — Return functional test beautified name
- L294 _private member_ `TObjectPtr<UBillboardComponent> SpriteComponent;` — `UPROPERTY()`
- L296 _private member_ `FString PreviousTestTags;`
- L304 _protected member_ `uint32 bIsEnabled:1;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Functional Testing", meta=(ScriptName="IsEnabledValue"))` — Allows a test to be disabled.  If a test is disabled, it will not appear in the set of runnable tests (after saving the map).
- L310 _protected member_ `uint32 bIsInSublevel:1;` — `UPROPERTY(EditInstanceOnly, Category="Functional Testing")` — Allows a test to be enabled only if loaded from the specified persistent level; avoiding other levels to run the test.
- L316 _protected member_ `FName PersistentLevelName;` — `UPROPERTY(EditInstanceOnly, Category="Functional Testing", meta=(EditCondition="bIsInSublevel"))` — Name of the persistent level to run the test from.
- L322 _protected member_ `EFunctionalTestLogHandling LogErrorHandling;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Functional Testing", meta = (ScriptName = "LogErrorHandling"))` — Determines how LogErrors are handled during this test.
- L328 _protected member_ `EFunctionalTestLogHandling LogWarningHandling;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Functional Testing", meta = (ScriptName = "LogWarningHandling"))` — Determines how LogWarnings are handled during this test.
- L336 _protected member_ `TObjectPtr<AActor> ObservationPoint;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Functional Testing")` — Allows you to specify another actor to view the test from.  Usually this is a camera you place in the map to observe the test.  Not useful when running on a build farm, but provides a handy way to observe the test from a different location than you place the functional test actor.
- L342 _protected member_ `uint32 bShouldDelayGarbageCollection:1;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Functional Testing", AdvancedDisplay)` — Allows for garbage collection to be delayed. If delayed, garbage collection will be triggered at the end of a test run
- L349 _protected member_ `FRandomStream RandomNumbersStream;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Functional Testing", AdvancedDisplay)` — A random number stream that you can use during testing.  This number stream will be consistent every time the test is run.
- L354 _public member_ `EFunctionalTestResult Result;` — `UPROPERTY(BlueprintReadWrite, Category="Functional Testing")`
- L358 _public member_ `float PreparationTimeLimit;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Timeout")` — The Test's time limit for preparation, this is the time it has to return true when checking IsReady(). '0' means no limit.
- L362 _public member_ `float TimeLimit;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Timeout")` — Test's time limit. '0' means no limit
- L365 _public member_ `FText TimesUpMessage;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Timeout", meta=( MultiLine="true" ))`
- L369 _public member_ `EFunctionalTestResult TimesUpResult;` — `UPROPERTY(EditAnywhere, Category="Timeout")` — If test is limited by time this is the result that will be returned when time runs out
- L380 _public member_ `FFunctionalTestEventSignature OnTestPrepare;` — `UPROPERTY(BlueprintAssignable)` — Called when the test is ready to prepare
- L384 _public member_ `FFunctionalTestEventSignature OnTestStart;` — `UPROPERTY(BlueprintAssignable)` — Called when the test is started
- L388 _public member_ `FFunctionalTestEventSignature OnTestFinished;` — `UPROPERTY(BlueprintAssignable)` — Called when the test is finished. Use it to clean up
- L391 _public member_ `TArray<TObjectPtr<AActor>> AutoDestroyActors;` — `UPROPERTY(Transient)`
- L393 _public member_ `FString FailureMessage;`
- L397 _public member_ `TObjectPtr<class UFuncTestRenderingComponent> RenderComp;` — `UPROPERTY()`
- L400 _public member_ `TObjectPtr<class UTextRenderComponent> TestName;` — `UPROPERTY()`
- L404 _public member_ `TArray<FName> RerunCauses;` — List of causes we need a re-run.
- L407 _public member_ `FName CurrentRerunCause;` — Cause of the current rerun if we're in a named rerun.
- L415 _public prototype_ `virtual bool AssertTrue(bool Condition, const FString& Message, const UObject* ContextObject = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Asserts", meta = ( HidePin = "ContextObject", DefaultToSelf = "ContextObject"))` — Assert that a boolean value is true. @param Message	The message to display if the assert fails ("Assertion Failed: 'Message' for context ''")
- L422 _public prototype_ `virtual bool AssertFalse(bool Condition, const FString& Message, const UObject* ContextObject = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Asserts", meta = ( HidePin = "ContextObject", DefaultToSelf = "ContextObject"))` — Assert that a boolean value is false. @param Message	The message to display if the assert fails ("Assertion Failed: 'Message' for context ''")
- L429 _public prototype_ `virtual bool AssertIsValid(UObject* Object, const FString& Message, const UObject* ContextObject = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Asserts", meta = ( HidePin = "ContextObject", DefaultToSelf = "ContextObject"))` — Assert that a UObject is valid @param Message	The message to display if the object is invalid ("Invalid object: 'Message' for context ''")
- L436 _public prototype_ `virtual bool AssertValue_Int(int32 Actual, EComparisonMethod ShouldBe, int32 Expected, const FString& What, const UObject* ContextObject = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Asserts", DisplayName = "Assert Value (Integer)", meta = ( HidePin = "ContextObject", DefaultToSelf = "ContextObject"))` — Assert on a relationship between two integers. @param What	A name to use in the message if the assert fails (What: expected {Actual} to be <ShouldBe> {Expected} for context '')
- L443 _public prototype_ `virtual bool AssertValue_Float(float Actual, EComparisonMethod ShouldBe, float Expected, const FString& What, const UObject* ContextObject = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Asserts", DisplayName = "Assert Value (Float)", meta = ( HidePin = "ContextObject", DefaultToSelf = "ContextObject"))` — Assert on a relationship between two floats. @param What	A name to use in the message if the assert fails (What: expected {Actual} to be <ShouldBe> {Expected} for context '')
- L450 _public prototype_ `bool AssertValue_Double(double Actual, EComparisonMethod ShouldBe, double Expected, const FString& What, const UObject* ContextObject = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Asserts", DisplayName = "Assert Value (Double)", meta = (HidePin = "ContextObject", DefaultToSelf = "ContextObject"))` — Assert on a relationship between two doubles. @param What	A name to use in the message if the assert fails (What: expected {Actual} to be <ShouldBe> {Expected} for context '')
- L457 _public prototype_ `virtual bool AssertValue_DateTime(FDateTime Actual, EComparisonMethod ShouldBe, FDateTime Expected, const FString& What, const UObject* ContextObject = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Asserts", DisplayName = "Assert Value (DateTime)", meta = ( HidePin = "ContextObject", DefaultToSelf = "ContextObject"))` — Assert on a relationship between two DateTimes. @param What	A name to use in the message if the assert fails (What: expected {Actual} to be <ShouldBe> {Expected} for context '')
- L464 _public prototype_ `virtual bool AssertEqual_Transform(const FTransform& Actual, const FTransform& Expected, const FString& What, float Tolerance = 1.e-4f, const UObject* ContextObject = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Asserts", DisplayName = "Assert Equal (Transform)", meta = ( HidePin = "ContextObject", DefaultToSelf = "ContextObject"))` — Assert that two transforms are (components memberwise - translation, rotation, scale) equal within a small tolerance. @param What	A name to use in the message if the assert fails ("Expected 'What' to be {Expected} but it was {Actual} for context ''")
- L471 _public prototype_ `virtual bool AssertEqual_Float(float Actual, float Expected, const FString& What, float Tolerance = 1.e-4f, const UObject* ContextObject = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Asserts", DisplayName = "Assert Equal (Float)", meta = ( HidePin = "ContextObject", DefaultToSelf = "ContextObject"))` — Assert that two floats are equal within tolerance between two floats. @param What	A name to use in the message if the assert fails (What: expected {Actual} to be Equal To {Expected} within Tolerance for context '')
- L478 _public prototype_ `bool AssertEqual_Double(double Actual, double Expected, const FString& What, double Tolerance = 1.e-4, const UObject* ContextObject = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Asserts", DisplayName = "Assert Equal (Double)", meta = (HidePin = "ContextObject", DefaultToSelf = "ContextObject"))` — Assert that two double are equal within tolerance between two doubles. @param What	A name to use in the message if the assert fails (What: expected {Actual} to be Equal To {Expected} within Tolerance for context '')
- L485 _public prototype_ `virtual bool AssertEqual_Bool(bool Actual, bool Expected, const FString& What, const UObject* ContextObject = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Asserts", DisplayName = "Assert Equal (Bool)", meta = (HidePin = "ContextObject", DefaultToSelf = "ContextObject"))` — Assert that two bools are equal @param What	A name to use in the message if the assert fails (What: expected {Actual} to be Equal To {Expected} for context '')
- L492 _public prototype_ `virtual bool AssertEqual_Int(int Actual, int Expected, const FString& What, const UObject* ContextObject = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Asserts", DisplayName = "Assert Equal (Integer)", meta = (HidePin = "ContextObject", DefaultToSelf = "ContextObject"))` — Assert that two ints are equal @param What	A name to use in the message if the assert fails (What: expected {Actual} to be Equal To {Expected} for context '')
- L499 _public prototype_ `virtual bool AssertEqual_Name(FName Actual, FName Expected, const FString& What, const UObject* ContextObject = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Asserts", DisplayName = "Assert Equal (FName)", meta = (HidePin = "ContextObject", DefaultToSelf = "ContextObject"))` — Assert that two FNames are equal @param What	A name to use in the message if the assert fails (What: expected {Actual} to be Equal To {Expected} for context '')
- L506 _public prototype_ `virtual bool AssertEqual_Object(UObject* Actual, UObject* Expected, const FString& What, const UObject* ContextObject = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Asserts", DisplayName = "Assert Equal (Object)", meta = (HidePin = "ContextObject", DefaultToSelf = "ContextObject"))` — Assert that two Objects are equal @param What	A name to use in the message if the assert fails (What: expected {Actual} to be Equal To {Expected} for context '')
- L513 _public prototype_ `virtual bool AssertNotEqual_Transform(const FTransform& Actual, const FTransform& NotExpected, const FString& What, const UObject* ContextObject = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Asserts", DisplayName = "Assert Not Equal (Transform)", meta = ( HidePin = "ContextObject", DefaultToSelf = "ContextObject"))` — Assert that two transforms are (components memberwise - translation, rotation, scale) not equal within a small tolerance. @param What	A name to use in the message if the assert fails ("Expected 'What' not to be {Expected} but it was {Actual} for context ''")
- L520 _public prototype_ `virtual bool AssertEqual_Rotator(FRotator Actual, FRotator Expected, const FString& What, float Tolerance = 1.e-4f, const UObject* ContextObject = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Asserts", DisplayName = "Assert Equal (Rotator)", meta = ( HidePin = "ContextObject", DefaultToSelf = "ContextObject"))` — Assert that the component angles of two rotators are all equal within a small tolerance. @param What	A name to use in the message if the assert fails ("Expected 'What' to be {Expected} but it was {Actual} for context ''")
- L527 _public prototype_ `virtual bool AssertEqual_RotatorOrientation(FRotator Actual, FRotator Expected, const FString& What, float Tolerance = 1.e-4f, const UObject* ContextObject = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Asserts", DisplayName = "Assert Equal (Rotator Orientation)", meta = ( HidePin = "ContextObject", DefaultToSelf = "ContextObject"))` — Assert that the orientation of two rotators is the same within a small tolerance. Robust to quaternion singularities where angles can differ despite having an identical orientation. @param What	A name to use in the message if the assert fails ("Expected 'What' to be {Expected} but it was {Actual} for context ''")
- L534 _public prototype_ `virtual bool AssertNotEqual_Rotator(FRotator Actual, FRotator NotExpected, const FString& What, const UObject* ContextObject = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Asserts", DisplayName = "Assert Not Equal (Rotator)", meta = ( HidePin = "ContextObject", DefaultToSelf = "ContextObject"))` — Assert that the component angles of two rotators are all not equal within a small tolerance. @param What	A name to use in the message if the assert fails ("Expected 'What' not to be {Expected} but it was {Actual} for context ''")
- L541 _public prototype_ `virtual bool AssertEqual_Vector(FVector Actual, FVector Expected, const FString& What, float Tolerance = 1.e-4f, const UObject* ContextObject = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Asserts", DisplayName = "Assert Equal (Vector)", meta = ( HidePin = "ContextObject", DefaultToSelf = "ContextObject"))` — Assert that two vectors are (memberwise) equal within a small tolerance. @param What	A name to use in the message if the assert fails ("Expected 'What' to be {Expected} but it was {Actual} for context ''")
- L548 _public prototype_ `virtual bool AssertNotEqual_Vector(FVector Actual, FVector NotExpected, const FString& What, const UObject* ContextObject = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Asserts", DisplayName = "Assert Not Equal (Vector)", meta = ( HidePin = "ContextObject", DefaultToSelf = "ContextObject"))` — Assert that two vectors are (memberwise) not equal within a small tolerance. @param What	A name to use in the message if the assert fails ("Expected 'What' not to be {Expected} but it was {Actual} for context ''")
- L555 _public prototype_ `virtual bool AssertEqual_Vector2D(FVector2D Actual, FVector2D Expected, const FString& What, float Tolerance = 1.e-4f, const UObject* ContextObject = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Asserts", DisplayName = "Assert Equal (Vector2D)", meta = ( HidePin = "ContextObject", DefaultToSelf = "ContextObject"))` — Assert that two two-component vectors are (memberwise) equal within a small tolerance. @param What	A name to use in the message if the assert fails ("Expected 'What' to be {Expected} but it was {Actual} for context ''")
- L562 _public prototype_ `virtual bool AssertNotEqual_Vector2D(FVector2D Actual, FVector2D NotExpected, const FString& What, const UObject* ContextObject = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Asserts", DisplayName = "Assert Not Equal (Vector2D)", meta = ( HidePin = "ContextObject", DefaultToSelf = "ContextObject"))` — Assert that two two-component vectors are (memberwise) not equal within a small tolerance. @param What	A name to use in the message if the assert fails ("Expected 'What' not to be {Expected} but it was {Actual} for context ''")
- L569 _public prototype_ `virtual bool AssertEqual_Box2D(FBox2D Actual, FBox2D Expected, const FString& What, float Tolerance = 1.e-4f, const UObject* ContextObject = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Asserts", DisplayName = "Assert Equal (Box2D)", meta = (HidePin = "ContextObject", DefaultToSelf = "ContextObject"))` — Assert that two two-component boxes are (memberwise) equal within a small tolerance. @param What	A name to use in the message if the assert fails ("Expected 'What' to be {Expected} but it was {Actual} for context ''")
- L576 _public prototype_ `virtual bool AssertNotEqual_Box2D(FBox2D Actual, FBox2D NotExpected, const FString& What, const UObject* ContextObject = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Asserts", DisplayName = "Assert Not Equal (Box2D)", meta = (HidePin = "ContextObject", DefaultToSelf = "ContextObject"))` — Assert that two two-component boxes are (memberwise) not equal within a small tolerance. @param What	A name to use in the message if the assert fails ("Expected 'What' not to be {Expected} but it was {Actual} for context ''")
- L583 _public prototype_ `virtual bool AssertEqual_Vector4(FVector4 Actual, FVector4 Expected, const FString& What, float Tolerance = 1.e-4f, const UObject* ContextObject = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Asserts", DisplayName = "Assert Equal (Vector4)", meta = ( HidePin = "ContextObject", DefaultToSelf = "ContextObject"))` — Assert that two four-component vectors are (memberwise) equal within a small tolerance. @param What	A name to use in the message if the assert fails ("Expected 'What' to be {Expected} but it was {Actual} for context ''")
- L590 _public prototype_ `virtual bool AssertNotEqual_Vector4(FVector4 Actual, FVector4 NotExpected, const FString& What, const UObject* ContextObject = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Asserts", DisplayName = "Assert Not Equal (Vector4)", meta = ( HidePin = "ContextObject", DefaultToSelf = "ContextObject"))` — Assert that two four-component vectors are (memberwise) not equal within a small tolerance. @param What	A name to use in the message if the assert fails ("Expected 'What' not to be {Expected} but it was {Actual} for context ''")
- L597 _public prototype_ `virtual bool AssertEqual_Plane(FPlane Actual, FPlane Expected, const FString& What, float Tolerance = 1.e-4f, const UObject* ContextObject = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Asserts", DisplayName = "Assert Equal (Plane)", meta = ( HidePin = "ContextObject", DefaultToSelf = "ContextObject"))` — Assert that two planes are (memberwise) equal within a small tolerance. @param What	A name to use in the message if the assert fails ("Expected 'What' to be {Expected} but it was {Actual} for context ''")
- L604 _public prototype_ `virtual bool AssertNotEqual_Plane(FPlane Actual, FPlane NotExpected, const FString& What, const UObject* ContextObject = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Asserts", DisplayName = "Assert Not Equal (Plane)", meta = ( HidePin = "ContextObject", DefaultToSelf = "ContextObject"))` — Assert that two planes are (memberwise) not equal within a small tolerance. @param What	A name to use in the message if the assert fails ("Expected 'What' not to be {Expected} but it was {Actual} for context ''")
- L611 _public prototype_ `virtual bool AssertEqual_Quat(FQuat Actual, FQuat Expected, const FString& What, float Tolerance = 1.e-4f, const UObject* ContextObject = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Asserts", DisplayName = "Assert Equal (Quat)", meta = ( HidePin = "ContextObject", DefaultToSelf = "ContextObject"))` — Assert that two quats are (memberwise) equal within a small tolerance. @param What	A name to use in the message if the assert fails ("Expected 'What' to be {Expected} but it was {Actual} for context ''")
- L618 _public prototype_ `virtual bool AssertNotEqual_Quat(FQuat Actual, FQuat NotExpected, const FString& What, const UObject* ContextObject = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Asserts", DisplayName = "Assert Not Equal (Quat)", meta = ( HidePin = "ContextObject", DefaultToSelf = "ContextObject"))` — Assert that two quats are (memberwise) not equal within a small tolerance. @param What	A name to use in the message if the assert fails ("Expected 'What' not to be {Expected} but it was {Actual} for context ''")
- L625 _public prototype_ `virtual bool AssertEqual_Matrix(FMatrix Actual, FMatrix Expected, const FString& What, float Tolerance = 1.e-4f, const UObject* ContextObject = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Asserts", DisplayName = "Assert Equal (Matrix)", meta = ( HidePin = "ContextObject", DefaultToSelf = "ContextObject"))` — Assert that two 4x4 matrices are (memberwise) equal within a small tolerance. @param What	A name to use in the message if the assert fails ("Expected 'What' to be {Expected} but it was {Actual} for context ''")
- L632 _public prototype_ `virtual bool AssertNotEqual_Matrix(FMatrix Actual, FMatrix NotExpected, const FString& What, const UObject* ContextObject = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Asserts", DisplayName = "Assert Not Equal (Matrix)", meta = ( HidePin = "ContextObject", DefaultToSelf = "ContextObject"))` — Assert that two 4x4 matrices are (memberwise) not equal within a small tolerance. @param What	A name to use in the message if the assert fails ("Expected 'What' not to be {Expected} but it was {Actual} for context ''")
- L639 _public prototype_ `virtual bool AssertEqual_String(FString Actual, FString Expected, const FString& What, const UObject* ContextObject = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Asserts", DisplayName = "Assert Equal (String)", meta = ( HidePin = "ContextObject", DefaultToSelf = "ContextObject"))` — Assert that two Strings are equal. @param What	A name to use in the message if the assert fails ("Expected 'What' to be {Expected} but it was {Actual} for context ''")
- L646 _public prototype_ `virtual bool AssertNotEqual_String(FString Actual, FString NotExpected, const FString& What, const UObject* ContextObject = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Asserts", DisplayName = "Assert Not Equal (String)", meta = ( HidePin = "ContextObject", DefaultToSelf = "ContextObject"))` — Assert that two Strings are not equal. @param What	A name to use in the message if the assert fails ("Expected 'What' not to be {Expected} but it was {Actual} for context ''")
- L653 _public prototype_ `virtual bool AssertEqual_TraceQueryResults(const UTraceQueryTestResults* Actual, const UTraceQueryTestResults* Expected, const FString& What, const UObject* ContextObject = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Asserts", DisplayName = "Assert Equal (TraceQuery)", meta = (HidePin = "ContextObject", DefaultToSelf = "ContextObject"))` — Assert that two TraceQueryResults are equal. @param What	A name to use in the message if the assert fails ("Expected 'What' not to be {Expected} but it was {Actual} for context ''")
- L656 _public prototype_ `void AddWarning(const FString& Message);` — `UFUNCTION(BlueprintCallable, Category = "Reporting")`
- L659 _public prototype_ `virtual void AddError(const FString& Message);` — `UFUNCTION(BlueprintCallable, Category = "Reporting")`
- L662 _public prototype_ `virtual void AddInfo(const FString& Message);` — `UFUNCTION(BlueprintCallable, Category = "Reporting")`
- L666 _public prototype_ `void LogStep(ELogVerbosity::Type Verbosity, const FString& Message);` — TODO: break this out into a library
- L669 _public prototype_ `virtual bool RunTest(const TArray<FString>& Params = TArray<FString>());`
- L672 _public prototype_ `FString GetCurrentStepName() const;`
- L673 _public prototype_ `void StartStep(const FString& StepName);`
- L674 _public prototype_ `void FinishStep();`
- L675 _public prototype_ `bool IsInStep() const;`
- L678 _public prototype_ `virtual void FinishTest(EFunctionalTestResult TestResult, const FString& Message);` — `UFUNCTION(BlueprintCallable, Category="Functional Testing")`
- L681 _public prototype_ `virtual void LogMessage(const FString& Message);` — `UFUNCTION(BlueprintCallable, Category="Functional Testing")`
- L684 _public prototype_ `virtual void SetTimeLimit(float NewTimeLimit, EFunctionalTestResult ResultWhenTimeRunsOut);` — `UFUNCTION(BlueprintCallable, Category="Functional Testing")`
- L690 _public prototype_ `TArray<AActor*> DebugGatherRelevantActors() const;` — `UFUNCTION(BlueprintImplementableEvent, CallInEditor, Category="Functional Testing")` — Used by debug drawing to gather actors this test is using and point at them on the level to better understand test's setup
- L692 _public prototype_ `virtual void GatherRelevantActors(TArray<AActor*>& OutActors) const;`
- L696 _public prototype_ `bool OnWantsReRunCheck() const;` — `UFUNCTION(BlueprintImplementableEvent, Category="Functional Testing")` — retrieves information whether test wants to have another run just after finishing
- L698 _public function_ `virtual bool WantsToRunAgain() const`
- L702 _public prototype_ `void AddRerun(FName Reason);` — `UFUNCTION(BlueprintCallable, Category = "Functional Testing")` — Causes the test to be rerun for a specific named reason.
- L706 _public prototype_ `FName GetCurrentRerunReason() const;` — `UFUNCTION(BlueprintCallable, Category = "Functional Testing")` — Returns the current re-run reason if we're in a named re-run.
- L710 _public prototype_ `void SetConsoleVariable(const FString& Name, const FString& InValue);` — `UFUNCTION(BlueprintCallable, Category = "Functional Testing")` — Sets the CVar from the given input. Variable gets reset after the test.
- L714 _public prototype_ `void SetConsoleVariableFromInteger(const FString& Name, const int32 InValue);` — `UFUNCTION(BlueprintCallable, Category = "Functional Testing")` — Sets the CVar from the given input. Variable gets reset after the test.
- L718 _public prototype_ `void SetConsoleVariableFromFloat(const FString& Name, const float InValue);` — `UFUNCTION(BlueprintCallable, Category = "Functional Testing")` — Sets the CVar from the given input. Variable gets reset after the test.
- L722 _public prototype_ `void SetConsoleVariableFromBoolean(const FString& Name, const bool InValue);` — `UFUNCTION(BlueprintCallable, Category = "Functional Testing")` — Sets the CVar from the given input. Variable gets reset after the test.
- L725 _public prototype_ `FString OnAdditionalTestFinishedMessageRequest(EFunctionalTestResult TestResult) const;` — `UFUNCTION(BlueprintImplementableEvent, Category = "Functional Testing")`
- L727 _public function_ `virtual FString GetAdditionalTestFinishedMessage(EFunctionalTestResult TestResult) const`
- L734 _public prototype_ `virtual void RegisterAutoDestroyActor(AActor* ActorToAutoDestroy);` — `UFUNCTION(BlueprintCallable, Category="Development", meta=(Keywords = "Delete"))` — Actors registered this way will be automatically destroyed (by limiting their lifespan) on test finish
- L739 _public prototype_ `virtual void CleanUp();` — Called to clean up when tests is removed from the list of active tests after finishing execution. Note that FinishTest gets called after every "cycle" of a test (where further cycles are enabled by WantsToRunAgain calls). CleanUp gets called when all cycles are done.
- L741 _public function_ `virtual FString GetReproString() const`
- L744 _public prototype_ `virtual void PostLoad() override;`
- L745 _public prototype_ `void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L746 _public prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;`
- L748 _public prototype_ `static void OnSelectObject(UObject* NewSelection);`
- L752 _public prototype_ `virtual void OnConstruction(const FTransform& Transform) override;` — AActor interface begin
- L753 _public prototype_ `virtual void Tick(float DeltaSeconds) override;`
- L754 _public prototype_ `virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;`
- L756 _public function_ `virtual bool CanChangeIsSpatiallyLoadedFlag() const override`
- L757 _public function_ `virtual bool ActorTypeSupportsDataLayer() const override`
- L758 _public function_ `virtual bool ActorTypeSupportsExternalDataLayer() const override`
- L763 _public prototype_ `bool IsRunning() const;` — `UFUNCTION(BlueprintCallable, Category = "Functional Testing")`
- L766 _public prototype_ `bool IsEnabled() const;` — `UFUNCTION(BlueprintCallable, Category = "Functional Testing")`
- L769 _public prototype_ `bool IsEnabledInWorld(const UWorld* World) const;` — `UFUNCTION(BlueprintCallable, Category = "Functional Testing")`
- L777 _protected prototype_ `virtual void PrepareTest();` — Prepare Test is fired once the test starts up, before the test IsReady() and thus before Start Test is called. So if there's some initial conditions or setup that you might need for your IsReady() check, you might want to do that here.
- L785 _protected prototype_ `void ReceivePrepareTest();` — `UFUNCTION(BlueprintImplementableEvent, meta=( DisplayName="Prepare Test" ))` — Prepare Test is fired once the test starts up, before the test IsReady() and thus before Start Test is called. So if there's some initial conditions or setup that you might need for your IsReady() check, you might want to do that here.
- L791 _protected prototype_ `virtual void StartTest();` — Called once the IsReady() check for the test returns true.  After that happens the test has Officially started, and it will begin receiving Ticks in the blueprint.
- L798 _protected prototype_ `void ReceiveStartTest();` — `UFUNCTION(BlueprintImplementableEvent, meta=( DisplayName="Start Test" ))` — Called once the IsReady() check for the test returns true.  After that happens the test has Officially started, and it will begin receiving Ticks in the blueprint.
- L805 _protected prototype_ `void ReceiveTestFinished();` — `UFUNCTION(BlueprintImplementableEvent, meta=( DisplayName="Test Finished" ))` — Called during FinishTest().  Allows for clean-up on the blueprint side, so that the user can bring the test back to its default state, making it ready for the next one.
- L812 _protected prototype_ `bool IsReady();` — `UFUNCTION(BlueprintNativeEvent, Category="Functional Testing")` — IsReady() is called once per frame after a test is run, until it returns true.  You should use this function to delay Start being called on the test until preconditions are met.
- L814 _protected prototype_ `virtual bool IsReady_Implementation();`
- L816 _protected prototype_ `virtual void OnTimeout();`
- L821 _protected prototype_ `void GoToObservationPoint();` — Goto an observation location.
- L824 _public member_ `FFunctionalTestDoneSignature TestFinishedObserver;`
- L828 _public member_ `bool bIsRunning;` — `UPROPERTY(Transient)` — AG TEMP - solving a compile issue in a temp way to unblock the build
- L830 _public member_ `TArray<FString> Steps;`
- L833 _public member_ `float TotalTime;` — `UPROPERTY(BlueprintReadOnly, Category = "Functional Testing")`
- L835 _public member_ `uint32 RunFrame;`
- L836 _public member_ `float RunTime;`
- L838 _public member_ `uint32 StartFrame;`
- L839 _public member_ `float StartTime;`
- L842 _private member_ `bool bIsReady;`
- L843 _private member_ `TSharedPtr<FScopedTestEnvironment> EnvSetup;`
- L847 _public prototype_ `UBillboardComponent* GetSpriteComponent();` — Returns SpriteComponent subobject

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API FUNCTIONALTESTING_API`
- L24 _delegate_ `DECLARE_STATS_GROUP(TEXT("FunctionalTest"), STATGROUP_FunctionalTest, STAT`
- L211 _prototype_ `FString LexToString(const EFunctionalTestResult TestResult);` — Return a readable string of the provided EFunctionalTestResult enum
- L214 _prototype_ `FString MapPackageToAutomationPath(const FString& MapPackageName);` — Return a dot-separated path prefix string representing the map that contains a test
- L220 _prototype_ `FString MapPackageToAutomationPath(const FAssetData& MapAsset);` — Return a dot-separated path prefix string representing the map that contains a test. If the map defines a "TestPathOverride" AR tag, it'll take its value instead of building the default prefix.
- L245 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFunctionalTestEventSignature);`
- L245 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFunctionalTestEventSignature);`
- L246 _delegate_ `DECLARE_DELEGATE_OneParam(FFunctionalTestDoneSignature, class AFunctionalTest*);`
- L246 _prototype_ `DECLARE_DELEGATE_OneParam(FFunctionalTestDoneSignature, class AFunctionalTest*);`

### `Source/Developer/FunctionalTesting/Classes/FunctionalTestBase.h` (Public)


#### class `FFunctionalTestBase`  
`class FFunctionalTestBase : public FAutomationTestBase`  
_L11-112_
- inherits: `FAutomationTestBase`
- desc: Base class for Functional test cases.
- L14 _public prototype_ `FFunctionalTestBase(const FString& InName, const bool bInComplexTask);`
- L21 _public prototype_ `virtual bool SuppressLogs();` — If true logs will not be included in test events @return true to suppress logs
- L28 _public prototype_ `virtual bool ShouldCaptureLogCategory(const class FName& Category) const;` — Should the log category be captured and surfaced as part of the test. @return true to allow a log category through.
- L35 _public function_ `void SetLogErrorAndWarningHandling(TOptional<bool> InSuppressErrors, TOptional<bool> InSuppressWarnings, TOptional<bool> InWarningsAreErrors)` — Specify how log errors & warnings should be handled during tests. If values are not set then the project defaults will be used.
- L58 _public function_ `virtual bool SuppressLogErrors() override` — Determines if Error logs should be suppressed from test results
- L66 _public function_ `virtual bool SuppressLogWarnings() override` — Determines if Warning logs should be suppressed from test results
- L74 _public function_ `virtual bool ElevateLogWarningsToErrors() override` — Determines if Warning logs should be treated as errors
- L82 _public prototype_ `void SetFunctionalTestRunning(const FString& InName);` — Marks us as actively running a functional test
- L87 _public prototype_ `void SetFunctionalTestComplete(const FString& InName);` — Marks us as no longer running a test
- L92 _public function_ `static FString GetRunningTestName()` — Returns the name of the running functional test. Empty if no test is running
- L97 _public function_ `static bool IsFunctionalTestRunning()` — Returns true if a functional test is running (does not include map setup)
- L101 _protected prototype_ `void SetLogErrorAndWarningHandlingToDefault();`
- L103 _protected member_ `bool bSuppressLogErrors;`
- L104 _protected member_ `bool bSuppressLogWarnings;`
- L105 _protected member_ `bool bElevateLogWarningsToErrors;`
- L106 _protected member_ `bool bSuppressLogs;`
- L110 _private member_ `static bool bIsFunctionalTestRunning;`
- L111 _private member_ `static FString ActiveTestName;`

### `Source/Developer/FunctionalTesting/Classes/FunctionalTestGameMode.h` (Public)


#### class `AFunctionalTestGameMode`  
`class AFunctionalTestGameMode : public AGameModeBase`  
_L11-15_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `AGameModeBase`

### `Source/Developer/FunctionalTesting/Classes/FunctionalTestLevelScript.h` (Public)


#### class `AFunctionalTestLevelScript`  
`class AFunctionalTestLevelScript : public ALevelScriptActor`  
_L10-14_
- reflection: `UCLASS(MinimalAPI, notplaceable, meta=(KismetHideOverrides = "ReceiveAnyDamage,ReceivePointDamage,ReceiveRadialDamage,ReceiveActorBeginOverlap,ReceiveActorEndOverlap,ReceiveHit,ReceiveDestroyed,ReceiveActorBeginCursorOver,ReceiveActorEndCursorOver,ReceiveActorOnClicked,ReceiveActorOnReleased,ReceiveActorOnInputTouchBegin,ReceiveActorOnInputTouchEnd,ReceiveActorOnInputTouchEnter,ReceiveActorOnInputTouchLeave"), HideCategories=(Collision,Rendering,Transformation))`
- inherits: `ALevelScriptActor`

### `Source/Developer/FunctionalTesting/Classes/FunctionalTestUtilityLibrary.h` (Public)


#### class `UFunctionalTestUtilityLibrary`  
`class UFunctionalTestUtilityLibrary : public UBlueprintFunctionLibrary`  
_L17-26_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Used to expose C++ functions to tests that we don't want to make BP accessible in the engine itself.
- L25 _public prototype_ `static UTraceQueryTestResults* TraceChannelTestUtil(UObject* WorldContextObject, const FTraceChannelTestBatchOptions& BatchOptions, const FVector Start, const FVector End, float SphereCapsuleRadius, float CapsuleHalfHeight, FVector BoxHalfSize, const FRotator Orientation, ETraceTypeQuery TraceChannel, TArray<TEnumAsByte<EObjectTypeQuery> > ObjectTypes, FName ProfileName, bool bTraceComplex, const TArray<AActor*>& ActorsToIgnore, bool bIgnoreSelf, EDrawDebugTrace::Type DrawDebugType, FLinearColor TraceColor = FLinearColor::Red, FLinearColor TraceHitColor = FLinearColor::Green, float DrawTime = 5.0f);` — `UFUNCTION(BlueprintCallable, Category = "Utilities|Collision", meta = (bIgnoreSelf = "true", WorldContext = "WorldContextObject", AutoCreateRefTerm = "ActorsToIgnore", AdvancedDisplay = "TraceColor,TraceHitColor,DrawTime", Keywords = "sweep"))` — Helper function to trace and permute many options at once

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API FUNCTIONALTESTING_API`

### `Source/Developer/FunctionalTesting/Classes/FunctionalTestingManager.h` (Public)


#### class `UFunctionalTestingManager`  
`class UFunctionalTestingManager : public UBlueprintFunctionLibrary`  
_L29-98_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- L34 _private member_ `TArray<TObjectPtr<class AFunctionalTest>> TestsLeft;` — `UPROPERTY(Transient)`
- L37 _private member_ `TArray<TObjectPtr<class AFunctionalTest>> AllTests;` — `UPROPERTY(Transient)`
- L40 _private member_ `FFunctionalTestEventSignature OnSetupTests;` — `UPROPERTY(BlueprintAssignable)`
- L43 _private member_ `FFunctionalTestEventSignature OnTestsComplete;` — `UPROPERTY(BlueprintAssignable)`
- L46 _private member_ `FFunctionalTestEventSignature OnTestsBegin;` — `UPROPERTY(BlueprintAssignable)`
- L53 _private prototype_ `static bool RunAllFunctionalTests(UObject* WorldContextObject, bool bNewLog = true, bool bRunLooped = false, FString FailedTestsReproString = TEXT(""));` — `UFUNCTION(BlueprintCallable, Category="FunctionalTesting", meta=(WorldContext="WorldContextObject", CallableWithoutWorldContext ))` — Triggers in sequence all functional tests found on the level. @return true if any tests have been triggered
- L55 _private function_ `bool IsRunning() const`
- L56 _private function_ `bool IsFinished() const`
- L57 _private function_ `bool IsLooped() const`
- L58 _private function_ `void SetLooped(const bool bNewLooped)`
- L61 _protected prototype_ `static UFunctionalTestingManager* GetManager(UObject* WorldContext);`
- L63 _protected prototype_ `void TriggerFirstValidTest();`
- L64 _protected prototype_ `void SetUpTests();`
- L66 _protected prototype_ `void OnTestDone(class AFunctionalTest* FTest);`
- L68 _protected prototype_ `bool RunFirstValidTest();`
- L70 _protected prototype_ `void NotifyTestDone(class AFunctionalTest* FTest);`
- L72 _protected prototype_ `void SetReproString(FString ReproString);`
- L73 _protected prototype_ `void AllTestsDone();`
- L75 _protected prototype_ `void OnWorldCleanedUp(UWorld* World, bool bSessionEnded, bool bCleanupResources);`
- L76 _protected prototype_ `virtual UWorld* GetWorld() const override;`
- L78 _protected member_ `bool bIsRunning;`
- L79 _protected member_ `bool bFinished;`
- L80 _protected member_ `bool bLooped;`
- L81 _protected member_ `bool bInitialDelayApplied;`
- L82 _protected member_ `bool bIsTearingDown;`
- L83 _protected member_ `uint32 CurrentIteration;`
- L85 _protected member_ `FFunctionalTestDoneSignature TestFinishedObserver;`
- L88 _protected member_ `FString StartingReproString;` — FString GatheredFailedTestsReproString;
- L89 _protected member_ `TArray<FString> TestReproStrings;`
- L94 _private member_ `TUniquePtr<UE::Private::FTickEditorTest> EditorTick;`
- L97 _private member_ `FTimerHandle TriggerFirstValidTestTimerHandle;`

#### class `APhasedAutomationActorBase`  
`class APhasedAutomationActorBase : public AActor`  
_L101-112_
- reflection: `UCLASS(abstract, Blueprintable, MinimalAPI)`
- inherits: `AActor`
- L108 _public prototype_ `void OnFunctionalTestingComplete();` — `UFUNCTION(BlueprintImplementableEvent, Category = "Automation")`
- L111 _public prototype_ `void OnFunctionalTestingBegin();` — `UFUNCTION(BlueprintImplementableEvent, Category = "Automation")`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace FFunctionalTesting`
- L17 _externvar_ `extern const TCHAR* ReproStringTestSeparator;` (scope `FFunctionalTesting`)
- L18 _externvar_ `extern const TCHAR* ReproStringParamsSeparator;` (scope `FFunctionalTesting`)
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace Private` (scope `UE`)

### `Source/Developer/FunctionalTesting/Classes/FunctionalUIScreenshotTest.h` (Public)


#### enum `EWidgetTestAppearLocation`  
`enum class EWidgetTestAppearLocation`  
_L17-21_
- reflection: `UENUM()`
- L19 _public enumerator_ `Viewport`
- L20 _public enumerator_ `PlayerScreen`

#### class `AFunctionalUIScreenshotTest`  
`class AFunctionalUIScreenshotTest : public AScreenshotFunctionalTestBase`  
_L27-81_
- reflection: `UCLASS(Blueprintable, MinimalAPI)`
- inherits: `AScreenshotFunctionalTestBase`
- L32 _public prototype_ `AFunctionalUIScreenshotTest(const FObjectInitializer& ObjectInitializer);`
- L35 _public prototype_ `virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;`
- L38 _protected prototype_ `virtual void PrepareTest() override;`
- L40 _protected prototype_ `virtual void OnScreenshotTakenAndCompared() override;`
- L42 _protected prototype_ `virtual void RequestScreenshot() override;`
- L44 _protected prototype_ `virtual bool IsReady_Implementation() override;`
- L46 _protected prototype_ `virtual void Tick(float DeltaSeconds) override;`
- L50 _protected member_ `TSubclassOf<UUserWidget> WidgetClass;` — `UPROPERTY(EditAnywhere, Category = "UI")`
- L53 _protected member_ `TObjectPtr<UUserWidget> SpawnedWidget;` — `UPROPERTY()`
- L56 _protected member_ `EWidgetTestAppearLocation WidgetLocation;` — `UPROPERTY(EditAnywhere, Category = "UI")`
- L59 _protected member_ `TObjectPtr<UTextureRenderTarget2D> ScreenshotRT;` — `UPROPERTY(Transient, DuplicateTransient)`
- L62 _protected member_ `bool bHideDebugCanvas;` — `UPROPERTY(EditAnywhere, Category = "UI")`
- L65 _private member_ `TOptional<bool> PreviousDebugCanvasVisible;`
- L66 _private member_ `int32 NumTickPassed;`
- L67 _private member_ `bool bWasPreviouslyUsingFixedDeltaTime;`
- L68 _private member_ `double PreviousFixedDeltaTime;`
- L69 _private member_ `const double TestFixedDeltaTime = 1 / 60.0;`
- L77 _private member_ `TFuture<FScreenshotData> Future;`
- L78 _private member_ `FDelegateHandle Handle;`
- L80 _private prototype_ `static void ReadBackBufferData(TPromise<FScreenshotData>& Promise, FRHITexture* Texture);`

#### struct `AFunctionalUIScreenshotTest::FScreenshotData`  
`struct FScreenshotData`  
_L71-75_
- L73 _public member_ `TArray<FColor> ColorData;`
- L74 _public member_ `FIntPoint Size;`

### `Source/Developer/FunctionalTesting/Classes/ScreenshotFunctionalTest.h` (Public)


#### class `AScreenshotFunctionalTest`  
`class AScreenshotFunctionalTest : public AScreenshotFunctionalTestBase`  
_L20-74_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `AScreenshotFunctionalTestBase`
- desc: No UI
- L25 _public prototype_ `AScreenshotFunctionalTest(const FObjectInitializer& ObjectInitializer);`
- L27 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L31 _public member_ `bool bCameraCutOnScreenshotPrep;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", SimpleDisplay)` — Tests not relying on temporal effects can force a camera cut to flush stale data
- L35 _protected prototype_ `virtual bool RunTest(const TArray<FString>& Params = TArray<FString>()) override;`
- L36 _protected prototype_ `virtual void PrepareTest() override;`
- L37 _protected prototype_ `virtual bool IsReady_Implementation() override;`
- L38 _protected prototype_ `virtual void Tick(float DeltaSeconds) override;`
- L40 _protected prototype_ `virtual void RequestScreenshot() override;`
- L41 _protected prototype_ `virtual void OnScreenShotCaptured(int32 InSizeX, int32 InSizeY, const TArray<FColor>& InImageData) override;`
- L42 _protected prototype_ `virtual void OnScreenshotTakenAndCompared() override;`
- L61 _private prototype_ `bool SetupNextVariant();`
- L62 _private prototype_ `void SetupVariant(EVariantType VariantType);`
- L64 _private member_ `TBitArray<> RequestedVariants;`
- L65 _private member_ `const TCHAR* CurrentVariantName;`
- L66 _private member_ `const TCHAR* VariantRestoreCommand;`
- L69 _private prototype_ `void ReprepareTest();` — Used for subsequent variants after the first is done
- L71 _private member_ `uint32 VariantFrame;`
- L72 _private member_ `float VariantTime;`
- L73 _private member_ `bool bVariantQueued;`

#### enum `AScreenshotFunctionalTest::EVariantType`  
`enum EVariantType`  
_L47-52_
- L49 _public enumerator_ `Baseline = 0`
- L50 _public enumerator_ `ViewRectOffset`
- L51 _public enumerator_ `Num`

#### struct `AScreenshotFunctionalTest::FVariantInfo`  
`struct FVariantInfo`  
_L54-59_
- L56 _public member_ `const TCHAR* Name;`
- L57 _public member_ `const TCHAR* SetupCommand;`
- L58 _public member_ `const TCHAR* RestoreCommand;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API FUNCTIONALTESTING_API`

### `Source/Developer/FunctionalTesting/Classes/ScreenshotFunctionalTestBase.h` (Public)


#### class `AScreenshotFunctionalTestBase`  
`class AScreenshotFunctionalTestBase : public AFunctionalTest`  
_L23-92_
- reflection: `UCLASS(MinimalAPI, Blueprintable, abstract)`
- inherits: `AFunctionalTest`
- desc: Base class for screenshot functional test
- L28 _public prototype_ `AScreenshotFunctionalTestBase(const FObjectInitializer& ObjectInitializer);`
- L31 _public prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;`
- L32 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L35 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L37 _public prototype_ `virtual void FinishTest(EFunctionalTestResult TestResult, const FString& Message) override;`
- L41 _protected prototype_ `virtual void PrepareTest() override;` — Set player view target to screenshot camera and call PrepareForScreenshot
- L44 _protected prototype_ `virtual bool IsReady_Implementation() override;` — Handle screenshot delay
- L47 _protected prototype_ `virtual void StartTest() override;` — Register OnScreenshotTakenAndCompared and call RequestScreenshot
- L50 _protected prototype_ `virtual void OnScreenshotTakenAndCompared();` — Call RestoreViewport and finish this test
- L53 _protected prototype_ `void PrepareForScreenshot();` — Resize viewport to screenshot size (if possible) and set up screenshot environment (disable AA, etc.)
- L56 _protected prototype_ `virtual void RequestScreenshot();` — Doesn't actually request in base class. It simply register OnScreenshotCaptured
- L61 _protected prototype_ `virtual void OnScreenShotCaptured(int32 InSizeX, int32 InSizeY, const TArray<FColor>& InImageData);` — Pass screenshot pixels and meta data to FAutomationTestFramework. Register OnComparisonComplete which will be called the automation test system when screenshot comparison is complete
- L64 _protected prototype_ `void OnComparisonComplete(const FAutomationScreenshotCompareResults& CompareResults);` — Do some logging and trigger OnScreenshotTakenAndCompared
- L67 _protected prototype_ `void RestoreViewSettings();` — Restore viewport size and original environment settings
- L69 _protected prototype_ `virtual void OnTimeout() override;`
- L74 _protected member_ `FString Notes;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Screenshot", meta = (MultiLine = "true"))`
- L77 _protected member_ `TObjectPtr<class UCameraComponent> ScreenshotCamera;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Screenshot")`
- L80 _protected member_ `FAutomationScreenshotOptions ScreenshotOptions;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Screenshot", SimpleDisplay)`
- L82 _protected member_ `FIntPoint ViewportRestoreSize;`
- L85 _protected member_ `TSharedPtr<FAutomationTestScreenshotEnvSetup> ScreenshotEnvSetup;`
- L89 _private member_ `bool bNeedsViewSettingsRestore;`
- L90 _private member_ `bool bNeedsViewportRestore;`
- L91 _private member_ `bool bScreenshotCompleted;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API FUNCTIONALTESTING_API`

### `Source/Developer/FunctionalTesting/Classes/TestPhaseComponent.h` (Public)


#### class `UTestPhaseComponent`  
`class UTestPhaseComponent : public USceneComponent`  
_L12-20_
- reflection: `UCLASS(hidecategories=Object, editinlinenew)`
- inherits: `USceneComponent`
- L17 _public prototype_ `UTestPhaseComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`

### `Source/Developer/FunctionalTesting/Classes/TraceQueryTestResults.h` (Public)


#### struct `FTraceChannelTestBatchOptions`  
`struct FTraceChannelTestBatchOptions`  
_L16-72_
- reflection: `USTRUCT(BlueprintType)`
- L20 _public function_ `FTraceChannelTestBatchOptions()`
- L32 _public function_ `bool operator==(const FTraceChannelTestBatchOptions& Other) const`
- L38 _public function_ `bool operator!=(const FTraceChannelTestBatchOptions& Other) const`
- L45 _public member_ `bool bLineTrace;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility|Collision")` — Whether to do line traces
- L49 _public member_ `bool bSphereTrace;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility|Collision")` — Whether to do sphere traces
- L53 _public member_ `bool bCapsuleTrace;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility|Collision")` — Whether to do capsule traces
- L57 _public member_ `bool bBoxTrace;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility|Collision")` — Whether to do box traces
- L61 _public member_ `bool bChannelTrace;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility|Collision")` — Whether to do channel traces
- L65 _public member_ `bool bObjectsTrace;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility|Collision")` — Whether to do object traces
- L69 _public member_ `bool bProfileTrace;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility|Collision")` — Whether to do profile traces
- L71 _public prototype_ `FString ToString() const;`

#### struct `FTraceQueryTestNames`  
`struct FTraceQueryTestNames`  
_L75-89_
- reflection: `USTRUCT(BlueprintType)`
- L80 _public member_ `FName ComponentName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility|Collision")`
- L83 _public member_ `FName PhysicalMaterialName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility|Collision")`
- L86 _public member_ `FName ActorName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility|Collision")`
- L88 _public prototype_ `FString ToString() const;`

#### struct `FTraceQueryTestResultsInnerMost`  
`struct FTraceQueryTestResultsInnerMost`  
_L92-125_
- reflection: `USTRUCT(BlueprintType)`
- L98 _public member_ `FHitResult SingleHit;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility|Collision")` — Result from doing a single sweep
- L102 _public member_ `FTraceQueryTestNames SingleNames;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility|Collision")` — Names found from doing a single sweep
- L106 _public member_ `bool bSingleResult = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility|Collision")` — The true/false value returned from the single sweep
- L110 _public member_ `TArray<FHitResult> MultiHits;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility|Collision")` — Result from doing a multi sweep
- L114 _public member_ `TArray<FTraceQueryTestNames> MultiNames;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility|Collision")` — Names found from doing a multi sweep
- L118 _public member_ `bool bMultiResult = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility|Collision")` — The true/false value returned from the multi sweep
- L120 _public prototype_ `FString ToString() const;`
- L122 _public prototype_ `void CaptureNames();`
- L124 _public prototype_ `bool AssertEqual(const FTraceQueryTestResultsInnerMost& Expected, const FString& What, const UObject* ContextObject, AFunctionalTest& FunctionalTest) const;`

#### struct `FTraceQueryTestResultsInner`  
`struct FTraceQueryTestResultsInner`  
_L128-153_
- reflection: `USTRUCT(BlueprintType)`
- L134 _public member_ `FTraceQueryTestResultsInnerMost LineResults;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility|Collision")` — The results associated with the line trace
- L138 _public member_ `FTraceQueryTestResultsInnerMost SphereResults;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility|Collision")` — The results associated with the sphere
- L142 _public member_ `FTraceQueryTestResultsInnerMost CapsuleResults;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility|Collision")` — The results associated with the capsule
- L146 _public member_ `FTraceQueryTestResultsInnerMost BoxResults;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility|Collision")` — The results associated with the box
- L148 _public prototype_ `FString ToString(const FTraceChannelTestBatchOptions& BatchOptions) const;`
- L150 _public prototype_ `void CaptureNames();`
- L152 _public prototype_ `bool AssertEqual(const FTraceQueryTestResultsInner& Expected, const FString& What, const UObject* ContextObject, AFunctionalTest& FunctionalTest) const;`

#### class `UTraceQueryTestResults`  
`class UTraceQueryTestResults : public UObject`  
_L156-184_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- L162 _public member_ `FTraceQueryTestResultsInner ChannelResults;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility|Collision")` — Results for channel trace
- L166 _public member_ `FTraceQueryTestResultsInner ObjectResults;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility|Collision")` — Results for object trace
- L170 _public member_ `FTraceQueryTestResultsInner ProfileResults;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility|Collision")` — Results for profile trace
- L173 _public member_ `FTraceChannelTestBatchOptions BatchOptions;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility|Collision")`
- L177 _public prototype_ `FString ToString();` — `UFUNCTION(BlueprintCallable, Category = "Utility|Collision")` — Output string value
- L179 _public prototype_ `bool AssertEqual(const UTraceQueryTestResults* Expected, const FString& What, const UObject* ContextObject, AFunctionalTest& FunctionalTest) const;`
- L181 _public prototype_ `void CaptureNames();`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API FUNCTIONALTESTING_API`

### `Source/Developer/FunctionalTesting/Public/AutomationBlueprintFunctionLibrary.h` (Public)


#### class `FAutomationTaskStatusBase`  
`class FAutomationTaskStatusBase`  
_L22-32_
- desc: FAutomationTaskStatusBase - abstract class for task status
- L25 _public prototype_ `virtual ~FAutomationTaskStatusBase() = default;`
- L27 _public function_ `bool IsDone() const`
- L28 _public function_ `virtual void SetDone()`
- L31 _protected member_ `bool Done = false;`

#### class `UAutomationEditorTask`  
`class UAutomationEditorTask : public UObject`  
_L38-57_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Transient)`
- inherits: `UObject`
- desc: UAutomationEditorTask
- L43 _public prototype_ `virtual ~UAutomationEditorTask() = default;`
- L47 _public prototype_ `bool IsTaskDone() const;` — `UFUNCTION(BlueprintCallable, Category = "Automation")` — Query if the Editor task is done
- L51 _public prototype_ `bool IsValidTask() const;` — `UFUNCTION(BlueprintCallable, Category = "Automation")` — Query if a task was setup
- L53 _public prototype_ `void BindTask(TUniquePtr<FAutomationTaskStatusBase> inTask);`
- L56 _private member_ `TUniquePtr<FAutomationTaskStatusBase> Task;`

#### struct `FAutomationWaitForLoadingOptions`  
`struct FAutomationWaitForLoadingOptions`  
_L60-68_
- reflection: `USTRUCT(BlueprintType)`
- L67 _public member_ `bool WaitForReplicationToSettle = false;` — `UPROPERTY(BlueprintReadWrite, Category = "Automation")`

#### class `UAutomationBlueprintFunctionLibrary`  
`class UAutomationBlueprintFunctionLibrary : public UBlueprintFunctionLibrary`  
_L74-257_
- reflection: `UCLASS(MinimalAPI, meta=(ScriptName="AutomationLibrary"))`
- inherits: `UBlueprintFunctionLibrary`
- L80 _public prototype_ `static void FinishLoadingBeforeScreenshot();` — `UFUNCTION(BlueprintCallable, Category = "Automation")`
- L82 _public prototype_ `static bool TakeAutomationScreenshotInternal(UObject* WorldContextObject, const FString& ScreenShotName, const FString& Notes, FAutomationScreenshotOptions Options);`
- L84 _public prototype_ `static FAutomationScreenshotData BuildScreenshotData(const FString& MapOrContext, const FString& ScreenShotName, int32 Width, int32 Height);`
- L85 _public prototype_ `static FAutomationScreenshotData BuildScreenshotData(UWorld* InWorld, const FString& ScreenShotName, int32 Width, int32 Height);`
- L87 _public prototype_ `static FIntPoint GetAutomationScreenshotSize(const FAutomationScreenshotOptions& Options);`
- L93 _public prototype_ `static void TakeAutomationScreenshot(UObject* WorldContextObject, FLatentActionInfo LatentInfo, const FString& Name, const FString& Notes, const FAutomationScreenshotOptions& Options);` — `UFUNCTION(BlueprintCallable, Category = "Automation", meta = (Latent, HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject", LatentInfo = "LatentInfo", Name = "" ))` — Takes a screenshot of the game's viewport.  Does not capture any UI.
- L99 _public prototype_ `static void TakeAutomationScreenshotAtCamera(UObject* WorldContextObject, FLatentActionInfo LatentInfo, ACameraActor* Camera, const FString& NameOverride, const FString& Notes, const FAutomationScreenshotOptions& Options);` — `UFUNCTION(BlueprintCallable, Category = "Automation", meta = (Latent, HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject", LatentInfo = "LatentInfo", NameOverride = "" ))` — Takes a screenshot of the game's viewport, from a particular camera actors POV.  Does not capture any UI.
- L104 _public prototype_ `static bool TakeAutomationScreenshotOfUI_Immediate(UObject* WorldContextObject, const FString& Name, const FAutomationScreenshotOptions& Options);`
- L107 _public prototype_ `static void TakeAutomationScreenshotOfUI(UObject* WorldContextObject, FLatentActionInfo LatentInfo, const FString& Name, const FAutomationScreenshotOptions& Options);` — `UFUNCTION(BlueprintCallable, Category = "Automation", meta = ( Latent, HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject", LatentInfo = "LatentInfo", NameOverride = "" ))`
- L110 _public prototype_ `static void EnableStatGroup(UObject* WorldContextObject, FName GroupName);` — `UFUNCTION(BlueprintCallable, Category = "Automation", meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"))`
- L113 _public prototype_ `static void DisableStatGroup(UObject* WorldContextObject, FName GroupName);` — `UFUNCTION(BlueprintCallable, Category = "Automation", meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"))`
- L116 _public prototype_ `static float GetStatIncAverage(FName StatName);` — `UFUNCTION(BlueprintCallable, Category = "Automation")`
- L119 _public prototype_ `static float GetStatIncMax(FName StatName);` — `UFUNCTION(BlueprintCallable, Category = "Automation")`
- L122 _public prototype_ `static float GetStatExcAverage(FName StatName);` — `UFUNCTION(BlueprintCallable, Category = "Automation")`
- L125 _public prototype_ `static float GetStatExcMax(FName StatName);` — `UFUNCTION(BlueprintCallable, Category = "Automation")`
- L128 _public prototype_ `static float GetStatCallCount(FName StatName);` — `UFUNCTION(BlueprintCallable, Category = "Automation")`
- L134 _public prototype_ `static bool AreAutomatedTestsRunning();` — `UFUNCTION(BlueprintPure, Category="Automation")` — Lets you know if any automated tests are running, or are about to run and the automation system is spinning up tests.
- L137 _public prototype_ `static void AutomationWaitForLoading(UObject* WorldContextObject, FLatentActionInfo LatentInfo, FAutomationWaitForLoadingOptions Options);` — `UFUNCTION(BlueprintCallable, Category = "Automation", meta = (Latent, HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject", LatentInfo = "LatentInfo"))`
- L143 _public prototype_ `static UAutomationEditorTask* TakeHighResScreenshot(int32 ResX, int32 ResY, FString Filename, ACameraActor* Camera = nullptr, bool bMaskEnabled = false, bool bCaptureHDR = false, EComparisonTolerance ComparisonTolerance = EComparisonTolerance::Low, FString ComparisonNotes = TEXT(""), float Delay = 0.0, bool bForceGameView = true);` — `UFUNCTION(BlueprintCallable, Category = "Automation", meta = (AdvancedDisplay="Camera, bMaskEnabled, bCaptureHDR, ComparisonTolerance, ComparisonNotes, bForceGameView"))` — take high res screenshot in editor.
- L152 _public prototype_ `static bool CompareImageAgainstReference(FString ImageFilePath, FString ComparisonName = TEXT(""), EComparisonTolerance ComparisonTolerance = EComparisonTolerance::Low, FString ComparisonNotes = TEXT(""), UObject* WorldContextObject = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Automation", meta = (AdvancedDisplay = "ComparisonName, ComparisonTolerance, ComparisonNotes", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"))` — request image comparison. @param ImageFilePath	Absolute path to the image location. All 8bit RGBA channels supported formats by the engine are accepted. @param ComparisonName	Optional name for the comparison, by default the basename of ImageFilePath is used @return				True if comparison was successfully enqueued
- L158 _public prototype_ `static void AddTestTelemetryData(FString DataPoint, float Measurement, FString Context = TEXT(""));` — `UFUNCTION(BlueprintCallable, Category = "Automation", meta = (AdvancedDisplay = "Context"))` — Add Telemetry data to currently running automated test.
- L164 _public prototype_ `static void SetTestTelemetryStorage(FString StorageName);` — `UFUNCTION(BlueprintCallable, Category = "Automation")` — Set Telemetry data storage name of currently running automated test.
- L170 _public prototype_ `static FAutomationScreenshotOptions GetDefaultScreenshotOptionsForGameplay(EComparisonTolerance Tolerance = EComparisonTolerance::Low, float Delay = 0.2);` — `UFUNCTION(BlueprintPure, Category="Automation")`
- L176 _public prototype_ `static FAutomationScreenshotOptions GetDefaultScreenshotOptionsForRendering(EComparisonTolerance Tolerance = EComparisonTolerance::Low, float Delay = 0.2);` — `UFUNCTION(BlueprintPure, Category="Automation")`
- L183 _public prototype_ `static void AddExpectedLogError(FString ExpectedPatternString, int32 Occurrences = 1, bool ExactMatch = false, bool IsRegex = true);` — `UFUNCTION(BlueprintCallable, Category = "Automation", meta = (AdvancedDisplay = "Occurrences, ExactMatch, IsRegex"))` — Mute the report of log error and warning matching a pattern during an automated test. Treat the pattern as regex by default. @param ExpectedPatternString	Expects a Regex pattern.
- L189 _public prototype_ `static void AddExpectedPlainLogError(FString ExpectedString, int32 Occurrences = 1, bool ExactMatch = false);` — `UFUNCTION(BlueprintCallable, Category = "Automation", meta = (AdvancedDisplay = "Occurrences, ExactMatch"))` — Mute the report of log error and warning matching a plain string during an automated test
- L195 _public prototype_ `static void AddExpectedLogMessage(FString ExpectedPatternString, int32 Occurrences = 1, bool ExactMatch = false, bool IsRegex = true);` — `UFUNCTION(BlueprintCallable, Category = "Automation", meta = (AdvancedDisplay = "Occurrences, ExactMatch, IsRegex"))` — Expect a specific log message to match a pattern during an automated test regardless of its verbosity. Treat the pattern as regex by default.
- L201 _public prototype_ `static void AddExpectedPlainLogMessage(FString ExpectedString, int32 Occurrences = 1, bool ExactMatch = false);` — `UFUNCTION(BlueprintCallable, Category = "Automation", meta = (AdvancedDisplay = "Occurrences, ExactMatch"))` — Expect a specific log message to match a plain string during an automated test regardless of its verbosity
- L208 _public prototype_ `static void SetScalabilityQualityLevelRelativeToMax(UObject* WorldContextObject, int32 Value = 1);` — `UFUNCTION(BlueprintCallable, Category = "Automation", meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"))` — Sets all other settings based on an overall value @param Value 0:Cinematic, 1:Epic...etc.
- L211 _public prototype_ `static void SetScalabilityQualityToEpic(UObject* WorldContextObject);` — `UFUNCTION(BlueprintCallable, Category = "Automation", meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"))`
- L214 _public prototype_ `static void SetScalabilityQualityToLow(UObject* WorldContextObject);` — `UFUNCTION(BlueprintCallable, Category = "Automation", meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"))`
- L218 _public prototype_ `static void SetEditorViewportViewMode(EViewModeIndex Index);` — `UFUNCTION(BlueprintCallable, Category = "Automation")` — Sets all viewports of the first found level editor to have the given ViewMode (Lit/Unlit/etc.)
- L222 _public prototype_ `static void SetEditorActiveViewportViewMode(EViewModeIndex Index);` — `UFUNCTION(BlueprintCallable, Category = "Automation")` — Sets ViewMode (Lit/Unlit/etc.) of the first active viewport found
- L226 _public prototype_ `static EViewModeIndex GetEditorActiveViewportViewMode();` — `UFUNCTION(BlueprintCallable, Category = "Automation")` — Get the ViewMode (Lit/Unlit/etc.) of the active viewport. Returns VMI_Unknown if fails to get the active viewport view mode index.
- L230 _public prototype_ `static void SetEditorActiveViewportWireframeOpacity(float Opacity);` — `UFUNCTION(BlueprintCallable, Category = "Automation")` — Sets the opacity for wireframe viewport view modes of the active viewport.
- L234 _public prototype_ `static float GetEditorActiveViewportWireframeOpacity();` — `UFUNCTION(BlueprintCallable, Category = "Automation")` — Retrieves the opacity for wireframe viewport view modes of the active viewport.
- L238 _public prototype_ `static void SetEditorViewportVisualizeBuffer(FName BufferName);` — `UFUNCTION(BlueprintCallable, Category = "Automation")` — Sets all viewports of the first found level editor to have the VisualizeBuffer ViewMode and also display a given buffer (BaseColor/Metallic/Roughness/etc.)
- L244 _public prototype_ `static void AddTestInfo(const FString& InLogItem);` — `UFUNCTION(BlueprintCallable, Category = "Automation")` — Add info to currently running automated test.
- L250 _public prototype_ `static void AddTestWarning(const FString& InLogItem);` — `UFUNCTION(BlueprintCallable, Category = "Automation")` — Add warning to currently running automated test.
- L256 _public prototype_ `static void AddTestError(const FString& InLogItem);` — `UFUNCTION(BlueprintCallable, Category = "Automation")` — Add error to currently running automated test.

#### class `FConsoleVariableSwapperTempl`  
`template<typename T> class FConsoleVariableSwapperTempl`  
_L262-276_
- L265 _public prototype_ `FConsoleVariableSwapperTempl(FString InConsoleVariableName);`
- L267 _public prototype_ `void Set(T Value);`
- L269 _public prototype_ `void Restore();`
- L272 _private member_ `bool bModified;`
- L273 _private member_ `FString ConsoleVariableName;`
- L275 _private member_ `T OriginalValue;`

#### class `FAutomationTestScreenshotEnvSetup`  
`class FAutomationTestScreenshotEnvSetup`  
_L278-309_
- L281 _public prototype_ `FAutomationTestScreenshotEnvSetup();`
- L282 _public prototype_ `~FAutomationTestScreenshotEnvSetup();`
- L287 _public prototype_ `void Setup(UWorld* InWorld, FAutomationScreenshotOptions& InOutOptions);` — Disable AA, auto-exposure, motion blur, contact shadow if InOutOptions.bDisableNoisyRenderingFeatures. Update screenshot comparison tolerance stored in InOutOptions. Set visualization buffer name if required.
- L290 _public prototype_ `void Restore();` — Restore the old settings.
- L293 _private member_ `FConsoleVariableSwapperTempl<int32> DefaultFeature_AntiAliasing;`
- L294 _private member_ `FConsoleVariableSwapperTempl<int32> DefaultFeature_AutoExposure;`
- L295 _private member_ `FConsoleVariableSwapperTempl<int32> DefaultFeature_MotionBlur;`
- L296 _private member_ `FConsoleVariableSwapperTempl<int32> MotionBlurQuality;`
- L297 _private member_ `FConsoleVariableSwapperTempl<int32> ScreenSpaceReflectionQuality;`
- L298 _private member_ `FConsoleVariableSwapperTempl<int32> EyeAdaptationQuality;`
- L299 _private member_ `FConsoleVariableSwapperTempl<int32> ContactShadows;`
- L300 _private member_ `FConsoleVariableSwapperTempl<float> TonemapperGamma;`
- L301 _private member_ `FConsoleVariableSwapperTempl<float> TonemapperSharpen;`
- L302 _private member_ `FConsoleVariableSwapperTempl<float> ScreenPercentage;`
- L303 _private member_ `FConsoleVariableSwapperTempl<int32> DynamicResTestScreenPercentage;`
- L304 _private member_ `FConsoleVariableSwapperTempl<int32> DynamicResOperationMode;`
- L305 _private member_ `FConsoleVariableSwapperTempl<float> SecondaryScreenPercentage;`
- L307 _private member_ `TWeakObjectPtr<UWorld> WorldPtr;`
- L308 _private member_ `TSharedPtr< class FAutomationViewExtension, ESPMode::ThreadSafe > AutomationViewExtension;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API FUNCTIONALTESTING_API`

### `Source/Developer/FunctionalTesting/Public/AutomationScreenshotOptions.h` (Public)


#### enum `EComparisonTolerance`  
`enum class EComparisonTolerance : uint8`  
_L11-18_
- reflection: `UENUM(BlueprintType)`
- L13 _public enumerator_ `Zero`
- L14 _public enumerator_ `Low`
- L15 _public enumerator_ `Medium`
- L16 _public enumerator_ `High`
- L17 _public enumerator_ `Custom`

#### struct `FComparisonToleranceAmount`  
`struct FComparisonToleranceAmount`  
_L21-65_
- reflection: `USTRUCT(BlueprintType)`
- L27 _public function_ `FComparisonToleranceAmount() : Red(0) , Green(0) , Blue(0) , Alpha(0) , MinBrightness(0) , MaxBrightness(255)`
- L37 _public function_ `FComparisonToleranceAmount(uint8 R, uint8 G, uint8 B, uint8 A, uint8 InMinBrightness, uint8 InMaxBrightness) : Red(R) , Green(G) , Blue(B) , Alpha(A) , MinBrightness(InMinBrightness) , MaxBrightness(InMaxBrightness)`
- L49 _public member_ `uint8 Red;` — `UPROPERTY(EditAnywhere, Category="Tolerance")`
- L52 _public member_ `uint8 Green;` — `UPROPERTY(EditAnywhere, Category="Tolerance")`
- L55 _public member_ `uint8 Blue;` — `UPROPERTY(EditAnywhere, Category="Tolerance")`
- L58 _public member_ `uint8 Alpha;` — `UPROPERTY(EditAnywhere, Category="Tolerance")`
- L61 _public member_ `uint8 MinBrightness;` — `UPROPERTY(EditAnywhere, Category="Tolerance")`
- L64 _public member_ `uint8 MaxBrightness;` — `UPROPERTY(EditAnywhere, Category="Tolerance")`

#### struct `FAutomationScreenshotOptions`  
`struct FAutomationScreenshotOptions`  
_L68-246_
- reflection: `USTRUCT(BlueprintType)`
- L73 _public function_ `FAutomationScreenshotOptions() : Resolution(ForceInit) , Delay(0.2f) , FrameDelay(5) , bOverride_OverrideTimeTo(false) , OverrideTimeTo(0.0f) , bDisableNoisyRenderingFeatures(true) , bDisableTonemapping(true) , ViewSettings(nullptr) , VisualizeBuffer(NAME_None) , Tolerance(EComparisonTolerance::Zero) , ToleranceAmount() , MaximumLocalError(0.10f) , MaximumGlobalError(0.02f) , bIgnoreAntiAliasing(true) , bIgnoreColors(false) , bAllowEmulatingSplitscreen(true)`
- L93 _public function_ `FAutomationScreenshotOptions(EComparisonTolerance InTolerance) : Resolution(ForceInit) , Delay(0.2f) , FrameDelay(5) , bOverride_OverrideTimeTo(false) , OverrideTimeTo(0.0f) , bDisableNoisyRenderingFeatures(true) , bDisableTonemapping(true) , ViewSettings(nullptr) , VisualizeBuffer(NAME_None) , Tolerance(InTolerance) , ToleranceAmount() , MaximumLocalError(0.10f) , MaximumGlobalError(0.02f) , bIgnoreAntiAliasing(true) , bIgnoreColors(false) , bAllowEmulatingSplitscreen(true)`
- L119 _public member_ `FVector2D Resolution;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Screenshot")` — The desired resolution of the screenshot, if none is provided, it will use the default for the platform setup in the automation settings.
- L125 _public member_ `float Delay;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Screenshot")` — The delay before we take the screenshot (measured in seconds). Both this delay and the frame delay must be met before the screenshot is taken.
- L131 _public member_ `int32 FrameDelay;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Screenshot")` — The delay before we take the screenshot (measured in number of frames). Both this frame delay and the time delay must be met before the screenshot is taken.
- L134 _public member_ `bool bOverride_OverrideTimeTo;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Overrides, meta = (PinHiddenByDefault, InlineEditConditionToggle))`
- L142 _public member_ `double OverrideTimeTo;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Screenshot", meta=(editcondition = "bOverride_OverrideTimeTo"))` — Overrides World Time, Real Time to the value provided.  Sets Delta Time to 0.  Only affects the time being sent to the render thread and materials.  The time accumulating on the game thread is unaffected.
- L151 _public member_ `bool bDisableNoisyRenderingFeatures;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Screenshot")` — Disables Anti-Aliasing, Motion Blur, Screen Space Reflections, Eye Adaptation, Tonemapper and Contact Shadows, because those features contribute a lot to the noise in the final rendered image.  If you're explicitly looking for changes. Unchecking the option will make accessible the Disable Eye Adaptation checkbox.
- L158 _public member_ `bool bDisableTonemapping;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Screenshot", meta = (EditCondition = "!bDisableNoisyRenderingFeatures", DisplayName = "Disable Eye Adaptation"))` — Disables Eye Adaptation and sets Tonemapper to fixed gamma curve. Should generally be on unless testing tone mapping or other post-processing results.
- L165 _public member_ `TObjectPtr<UAutomationViewSettings> ViewSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Screenshot")` — Assign custom view settings to control which rendering options we allow on while taking the screenshot.
- L173 _public member_ `FName VisualizeBuffer;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Screenshot")` — Allows you to screenshot a buffer other than the default final lit scene image.  Useful if you're trying to build a test for a specific GBuffer, that may be harder to tell if errors are introduced in it.
- L180 _public member_ `EComparisonTolerance Tolerance;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Comparison")` — These are quick defaults for tolerance levels, we default to low, because generally there's some constant variability in every pixel's color introduced by TxAA.
- L188 _public member_ `FComparisonToleranceAmount ToleranceAmount;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Comparison")` — For each channel and brightness levels you can control a region where the colors are found to be essentially the same.  Generally this is necessary as modern rendering techniques tend to introduce noise constantly to hide aliasing.
- L198 _public member_ `float MaximumLocalError;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Comparison", meta=( ClampMin = 0, ClampMax = 1, UIMin = 0, UIMax = 1 ))` — After you've accounted for color tolerance changes, you now need to control for local acceptable error. Which depending on how pixels were colored on triangle edges may be a few percent of the image being outside the tolerance levels.  Unlike the MaximumGlobalError, the MaximumLocalError works by focusing on a smaller subset of the image.  These chunks will have be compared to the local error, in an attempt to locate hot spots of change that are important, that would be ignored by the global error.
- L206 _public member_ `float MaximumGlobalError;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Comparison", meta=( ClampMin = 0, ClampMax = 1, UIMin = 0, UIMax = 1 ))` — After you've accounted for color tolerance changes, you now need to control for total acceptable error. Which depending on how pixels were colored on triangle edges may be a few percent of the image being outside the tolerance levels.
- L213 _public member_ `bool bIgnoreAntiAliasing;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Comparison")` — If this is true, we search neighboring pixels looking for the expected pixel as what may have happened, is that the pixel shifted a little.
- L219 _public member_ `bool bIgnoreColors;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Comparison", AdvancedDisplay)` — If this is true, all we compare is luminance of the scene.
- L225 _public member_ `bool bAllowEmulatingSplitscreen;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Comparison")` — If this is true, this test can use emulated splitscreen rendering when r.ScreenshotTest.EmulateSplitscreenMode = 1, 2, or 3.
- L228 _public function_ `void SetToleranceAmounts(EComparisonTolerance InTolerance)`

### `Source/Developer/FunctionalTesting/Public/AutomationViewSettings.h` (Public)


#### class `UAutomationViewSettings`  
`class UAutomationViewSettings : public UDataAsset`  
_L12-56_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UDataAsset`
- L17 _public function_ `UAutomationViewSettings() : AntiAliasing(true) , MotionBlur(true) , TemporalAA(true) , ScreenSpaceReflections(true) , ScreenSpaceAO(true) , DistanceFieldAO(true) , ContactShadows(true) , EyeAdaptation(true) , Bloom(true)`
- L31 _public member_ `bool AntiAliasing;` — `UPROPERTY(EditAnywhere, Category="Rendering")`
- L34 _public member_ `bool MotionBlur;` — `UPROPERTY(EditAnywhere, Category="Rendering")`
- L37 _public member_ `bool TemporalAA;` — `UPROPERTY(EditAnywhere, Category="Rendering")`
- L40 _public member_ `bool ScreenSpaceReflections;` — `UPROPERTY(EditAnywhere, Category="Rendering")`
- L43 _public member_ `bool ScreenSpaceAO;` — `UPROPERTY(EditAnywhere, Category="Rendering")`
- L46 _public member_ `bool DistanceFieldAO;` — `UPROPERTY(EditAnywhere, Category="Rendering")`
- L49 _public member_ `bool ContactShadows;` — `UPROPERTY(EditAnywhere, Category="Rendering")`
- L52 _public member_ `bool EyeAdaptation;` — `UPROPERTY(EditAnywhere, Category="Rendering")`
- L55 _public member_ `bool Bloom;` — `UPROPERTY(EditAnywhere, Category = "Rendering")`

### `Source/Developer/FunctionalTesting/Public/DelayForFramesLatentAction.h` (Public)


#### class `FDelayForFramesLatentAction`  
`class FDelayForFramesLatentAction : public FPendingLatentAction`  
_L13-31_
- inherits: `FPendingLatentAction`
- L16 _public prototype_ `FDelayForFramesLatentAction(const FLatentActionInfo& LatentInfo, int32 NumFrames);`
- L17 _public prototype_ `virtual ~FDelayForFramesLatentAction();`
- L19 _public prototype_ `virtual void UpdateOperation(FLatentResponse& Response) override;`
- L23 _public prototype_ `virtual FString GetDescription() const override;` — Returns a human readable description of the latent operation's current state
- L27 _private member_ `FName ExecutionFunction;`
- L28 _private member_ `int32 OutputLink;`
- L29 _private member_ `FWeakObjectPtr CallbackTarget;`
- L30 _private member_ `int32 FramesRemaining;`

### `Source/Developer/FunctionalTesting/Public/FunctionalTestingHelper.h` (Public)
_(no declarations extracted)_

### `Source/Developer/FunctionalTesting/Public/FunctionalTestingModule.h` (Public)


#### class `IFunctionalTestingModule`  
`class IFunctionalTestingModule : public IModuleInterface`  
_L12-60_
- inherits: `IModuleInterface`
- L16 _public prototype_ `virtual void RunAllTestsOnMap(bool bClearLog, bool bRunLooped) = 0;` — Triggers in sequence all functional tests found on the level
- L19 _public prototype_ `virtual void RunTestOnMap(const FString& TestName, bool bClearLog, bool bRunLooped) = 0;` — Runs a single test
- L22 _public prototype_ `virtual void MarkPendingActivation() = 0;` — Sets that a test is being started
- L25 _public prototype_ `virtual bool IsActivationPending() const = 0;` — True if a test is about to start
- L28 _public prototype_ `virtual bool IsRunning() const = 0;` — True if there is an active UFunctionalTestingManager
- L31 _public prototype_ `virtual bool IsFinished() const = 0;` — True if a UFunctionalTestingManager was spawned and is now done
- L34 _public prototype_ `virtual void SetManager(class UFunctionalTestingManager* NewManager) = 0;` — Sets the active testing manager
- L37 _public prototype_ `virtual class UFunctionalTestingManager* GetCurrentManager() = 0;` — Gets the active testing manager
- L40 _public prototype_ `virtual void SetLooping(const bool bLoop) = 0;` — If true, will run tests forever
- L44 _public prototype_ `virtual void GetMapTests(bool bEditorOnlyTests, TArray<FString>& OutBeautifiedNames, TArray<FString>& OutTestCommands, TArray<FString>& OutTestMapAssets) const = 0;` — `UE_DEPRECATED(5.5, "GetMapTests() with four parameters has been deprecated.")` — Gets a list of maps/tests in the current project
- L52 _public prototype_ `virtual void GetMapTests(bool bEditorOnlyTests, TArray<FFunctionalTestInfo>& OutTestInfo, TArray<FString>& OutTestMapAssets) const = 0;` — Gets a list of tests and maps in the current project @param bEditorOnlyTests	Only collect tests which run in the Editor @param OutTestInfo		Updated to contain execution information for each test @param OutTestMapAssets	Updated with the unique *.umap assets which contain tests
- L55 _public function_ `static IFunctionalTestingModule& Get()` — Gets the debugger singleton or returns NULL

#### Free symbols / members of external scopes

- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogFunctionalTest, Log, All);`

### `Source/Developer/FunctionalTesting/Public/GroundTruthData.h` (Public)


#### class `UGroundTruthData`  
`class UGroundTruthData : public UObject`  
_L22-54_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- L27 _public prototype_ `UGroundTruthData();`
- L30 _public prototype_ `void SaveObject(UObject* GroundTruth);` — `UFUNCTION(BlueprintCallable, Category = "Automation")`
- L33 _public prototype_ `UObject* LoadObject();` — `UFUNCTION(BlueprintCallable, Category = "Automation")`
- L36 _public prototype_ `bool CanModify() const;` — `UFUNCTION(BlueprintCallable, Category = "Automation")`
- L39 _public prototype_ `void ResetObject();` — `UFUNCTION(BlueprintCallable, Category = "Automation")`
- L42 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L48 _public member_ `bool bResetGroundTruth;` — `UPROPERTY(EditAnywhere, Category = Data)`
- L53 _protected member_ `TObjectPtr<UObject> ObjectData;` — `UPROPERTY(VisibleAnywhere, Export, Category=Data)`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API FUNCTIONALTESTING_API`

### `Source/Developer/FunctionalTesting/Public/TakeScreenshotAfterTimeLatentAction.h` (Public)


#### class `FTakeScreenshotAfterTimeLatentAction`  
`class FTakeScreenshotAfterTimeLatentAction : public FPendingLatentAction`  
_L11-38_
- inherits: `FPendingLatentAction`
- L14 _public prototype_ `FTakeScreenshotAfterTimeLatentAction(const FLatentActionInfo& LatentInfo, const FString& InScreenshotName, const FString& InNotes, FAutomationScreenshotOptions InOptions);`
- L15 _public prototype_ `virtual ~FTakeScreenshotAfterTimeLatentAction();`
- L17 _public prototype_ `virtual void UpdateOperation(FLatentResponse& Response) override;`
- L21 _public prototype_ `virtual FString GetDescription() const override;` — Returns a human readable description of the latent operation's current state
- L25 _private prototype_ `void OnScreenshotTakenAndCompared();`
- L28 _private member_ `FName ExecutionFunction;`
- L29 _private member_ `int32 OutputLink;`
- L30 _private member_ `FWeakObjectPtr CallbackTarget;`
- L31 _private member_ `FString ScreenshotName;`
- L32 _private member_ `FString Notes;`
- L33 _private member_ `float SecondsRemaining;`
- L34 _private member_ `bool FinishedLoading;`
- L35 _private member_ `bool IssuedScreenshotCapture;`
- L36 _private member_ `bool TakenScreenshot;`
- L37 _private member_ `FAutomationScreenshotOptions Options;`

#### class `FWaitForScreenshotComparisonLatentAction`  
`class FWaitForScreenshotComparisonLatentAction : public FPendingLatentAction`  
_L40-61_
- inherits: `FPendingLatentAction`
- L43 _public prototype_ `FWaitForScreenshotComparisonLatentAction(const FLatentActionInfo& LatentInfo);`
- L44 _public prototype_ `virtual ~FWaitForScreenshotComparisonLatentAction();`
- L46 _public prototype_ `virtual void UpdateOperation(FLatentResponse& Response) override;`
- L50 _public prototype_ `virtual FString GetDescription() const override;` — Returns a human readable description of the latent operation's current state
- L54 _private prototype_ `void OnScreenshotTakenAndCompared();`
- L57 _private member_ `FName ExecutionFunction;`
- L58 _private member_ `int32 OutputLink;`
- L59 _private member_ `FWeakObjectPtr CallbackTarget;`
- L60 _private member_ `bool TakenScreenshot;`
