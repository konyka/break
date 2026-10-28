# Developer / AITestSuite

- module root: `Source/Developer/AITestSuite`
- headers: 26; symbols: 386
- symbol kinds: class=24, delegate=2, enum=6, enumerator=23, externvar=1, function=67, macro=30, member=109, namespace=7, prototype=105, struct=11, variable=1
- PublicDependencyModuleNames: AIModule, Core, CoreUObject, Engine, GameplayTasks

### `Source/Developer/AITestSuite/Classes/BehaviorTree/TestBTDecorator_Blackboard.h` (Public)


#### class `UTestBTDecorator_Blackboard`  
`class UTestBTDecorator_Blackboard : public UBTDecorator_Blackboard`  
_L11-33_
- reflection: `UCLASS(meta = (HiddenNode))`
- inherits: `UBTDecorator_Blackboard`
- L18 _public member_ `int32 LogIndexBecomeRelevant;` — `UPROPERTY()`
- L21 _public member_ `int32 LogIndexCeaseRelevant;` — `UPROPERTY()`
- L24 _public member_ `int32 LogIndexCalculate;` — `UPROPERTY()`
- L27 _protected prototype_ `virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L28 _protected prototype_ `virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L29 _protected prototype_ `virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;`
- L32 _private prototype_ `void LogExecution(int32 LogNumber) const;`

### `Source/Developer/AITestSuite/Classes/BehaviorTree/TestBTDecorator_Blueprint.h` (Public)


#### enum `EBPConditionType`  
`enum class EBPConditionType`  
_L10-15_
- reflection: `UENUM()`
- L12 _public enumerator_ `NoCondition`
- L13 _public enumerator_ `TrueCondition`
- L14 _public enumerator_ `FalseCondition`

#### class `UTestBTDecorator_Blueprint`  
`class UTestBTDecorator_Blueprint : public UBTDecorator_BlueprintBase`  
_L18-48_
- reflection: `UCLASS(meta = (HiddenNode))`
- inherits: `UBTDecorator_BlueprintBase`
- L25 _public member_ `EBPConditionType BPConditionType = EBPConditionType::TrueCondition;` — `UPROPERTY()`
- L28 _public member_ `int32 LogIndexBecomeRelevant;` — `UPROPERTY()`
- L31 _public member_ `int32 LogIndexCeaseRelevant;` — `UPROPERTY()`
- L34 _public member_ `int32 LogIndexCalculate;` — `UPROPERTY()`
- L37 _public member_ `FName ObservingKeyName = NAME_None;` — `UPROPERTY()`
- L40 _protected prototype_ `virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L41 _protected prototype_ `virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L42 _protected prototype_ `virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;`
- L43 _protected prototype_ `virtual void PostLoad() override;`
- L44 _protected prototype_ `virtual void PostInitProperties() override;`
- L47 _private prototype_ `void LogExecution(int32 LogNumber) const;`

### `Source/Developer/AITestSuite/Classes/BehaviorTree/TestBTDecorator_CantExecute.h` (Public)


#### class `UTestBTDecorator_CantExecute`  
`class UTestBTDecorator_CantExecute : public UBTDecorator`  
_L11-16_
- reflection: `UCLASS(meta=(HiddenNode))`
- inherits: `UBTDecorator`
- L15 _private prototype_ `virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;`

### `Source/Developer/AITestSuite/Classes/BehaviorTree/TestBTDecorator_DelayedAbort.h` (Public)


#### struct `FBTDelayedAbortMemory`  
`struct FBTDelayedAbortMemory`  
_L10-13_
- L12 _public member_ `uint64 EndFrameIdx;`

#### class `UTestBTDecorator_DelayedAbort`  
`class UTestBTDecorator_DelayedAbort : public UBTDecorator`  
_L16-31_
- reflection: `UCLASS(meta = (HiddenNode))`
- inherits: `UBTDecorator`
- L21 _private member_ `int32 DelayTicks;` — `UPROPERTY()`
- L24 _private member_ `bool bOnlyOnce;` — `UPROPERTY()`
- L26 _private prototype_ `virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L27 _private prototype_ `virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;`
- L28 _private prototype_ `virtual uint16 GetInstanceMemorySize() const override;`
- L29 _private prototype_ `virtual void InitializeMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryInit::Type InitType) const override;`
- L30 _private prototype_ `virtual void CleanupMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryClear::Type CleanupType) const override;`

### `Source/Developer/AITestSuite/Classes/BehaviorTree/TestBTDecorator_LoopUntil.h` (Public)


#### class `UTestBTDecorator_LoopUntil`  
`class UTestBTDecorator_LoopUntil : public UBTDecorator_LoopUntil`  
_L12-19_
- reflection: `UCLASS(meta=(HiddenNode), MinimalAPI)`
- inherits: `UBTDecorator_LoopUntil`
- desc: Loop until test version used for unit tests
- L17 _public prototype_ `UTestBTDecorator_LoopUntil(const FObjectInitializer& ObjectInitializer);`
- L18 _public prototype_ `void SetRequiredResult(const EBTNodeResult::Type InRequiredResult);`

### `Source/Developer/AITestSuite/Classes/BehaviorTree/TestBTDecorator_NodeMemoryValidator.h` (Public)


#### struct `FBTNodeMemoryValidatorDecoratorMemory`  
`struct FBTNodeMemoryValidatorDecoratorMemory`  
_L8-12_
- L10 _public member_ `static constexpr uint32 TestValue = 0xABBAABBA;`
- L11 _public member_ `uint32 Dummy;`

#### class `UTestBTDecorator_NodeMemoryValidator`  
`class UTestBTDecorator_NodeMemoryValidator : public UBTDecorator`  
_L15-47_
- reflection: `UCLASS(meta=(HiddenNode))`
- inherits: `UBTDecorator`
- L20 _protected prototype_ `virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L21 _protected prototype_ `virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L22 _protected prototype_ `virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;`
- L23 _protected prototype_ `virtual void OnNodeActivation(FBehaviorTreeSearchData& SearchData) override;`
- L24 _protected prototype_ `virtual void OnNodeDeactivation(FBehaviorTreeSearchData& SearchData, EBTNodeResult::Type NodeResult) override;`
- L25 _protected prototype_ `virtual void OnNodeProcessed(FBehaviorTreeSearchData& SearchData, EBTNodeResult::Type& NodeResult) override;`
- L26 _protected prototype_ `virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;`
- L28 _protected prototype_ `virtual void InitializeMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryInit::Type InitType) const override;`
- L29 _protected prototype_ `virtual void CleanupMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryClear::Type CleanupType) const override;`
- L30 _protected prototype_ `virtual uint16 GetInstanceMemorySize() const override;`
- L35 _private function_ `template<typename T> T* GetCheckedNodeMemory(FBehaviorTreeSearchData& SearchData) const`
- L42 _private function_ `template<typename T> const T* GetCheckedNodeMemory(const FBehaviorTreeSearchData& SearchData) const`

### `Source/Developer/AITestSuite/Classes/BehaviorTree/TestBTService_BTStopAction.h` (Public)


#### enum `EBTTestServiceStopTiming`  
`enum class EBTTestServiceStopTiming : uint8`  
_L9-14_
- reflection: `UENUM()`
- L11 _public enumerator_ `DuringBecomeRelevant`
- L12 _public enumerator_ `DuringTick`
- L13 _public enumerator_ `DuringCeaseRelevant`

#### class `UTestBTService_BTStopAction`  
`class UTestBTService_BTStopAction : public UBTService`  
_L17-33_
- reflection: `UCLASS(meta = (HiddenNode))`
- inherits: `UBTService`
- L22 _private member_ `int32 LogIndex;` — `UPROPERTY()`
- L25 _private member_ `EBTTestServiceStopTiming StopTiming;` — `UPROPERTY()`
- L28 _private member_ `EBTTestStopAction StopAction;` — `UPROPERTY()`
- L30 _private prototype_ `virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L31 _private prototype_ `virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L32 _private prototype_ `virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;`

### `Source/Developer/AITestSuite/Classes/BehaviorTree/TestBTService_Log.h` (Public)


#### class `UTestBTService_Log`  
`class UTestBTService_Log : public UBTService`  
_L10-46_
- reflection: `UCLASS(meta = (HiddenNode))`
- inherits: `UBTService`
- L15 _private member_ `int32 LogActivation;` — `UPROPERTY()`
- L18 _private member_ `int32 LogDeactivation;` — `UPROPERTY()`
- L21 _private member_ `FName KeyNameTick;` — `UPROPERTY()`
- L24 _private member_ `FName KeyNameBecomeRelevant;` — `UPROPERTY()`
- L27 _private member_ `FName KeyNameCeaseRelevant;` — `UPROPERTY()`
- L30 _private member_ `int32 LogTick;` — `UPROPERTY()`
- L33 _private member_ `int32 TicksDelaySetKeyNameTick;` — `UPROPERTY()`
- L36 _private member_ `int32 NumTicks;` — `UPROPERTY()`
- L39 _private member_ `bool bToggleValue;` — `UPROPERTY()`
- L41 _private prototype_ `virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L42 _private prototype_ `virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L43 _private prototype_ `virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;`
- L45 _private prototype_ `void SetFlagOnTick(FName InKeyNameTick, bool bInCallTickOnSearchStart = false);`

### `Source/Developer/AITestSuite/Classes/BehaviorTree/TestBTStopAction.h` (Public)


#### enum `EBTTestStopAction`  
`enum class EBTTestStopAction : uint8`  
_L9-17_
- reflection: `UENUM()`
- L11 _public enumerator_ `StopTree`
- L12 _public enumerator_ `UnInitialize`
- L13 _public enumerator_ `Cleanup`
- L14 _public enumerator_ `Restart_ForceReevaluateRootNode`
- L15 _public enumerator_ `Restart_Complete`
- L16 _public enumerator_ `StartTree`

#### Free symbols / members of external scopes

- L19 _prototype_ `void DoBTStopAction(UBehaviorTreeComponent& OwnerComp, const EBTTestStopAction StopAction);`

### `Source/Developer/AITestSuite/Classes/BehaviorTree/TestBTTask_BTStopAction.h` (Public)


#### enum `EBTTestTaskStopTiming`  
`enum class EBTTestTaskStopTiming : uint8`  
_L9-15_
- reflection: `UENUM()`
- L11 _public enumerator_ `DuringExecute`
- L12 _public enumerator_ `DuringTick`
- L13 _public enumerator_ `DuringAbort`
- L14 _public enumerator_ `DuringFinish`

#### class `UTestBTTask_BTStopAction`  
`class UTestBTTask_BTStopAction : public UBTTaskNode`  
_L18-42_
- reflection: `UCLASS(meta=(HiddenNode))`
- inherits: `UBTTaskNode`
- L23 _public prototype_ `UTestBTTask_BTStopAction(const FObjectInitializer& ObjectInitializer);`
- L25 _public prototype_ `virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L26 _public prototype_ `virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L28 _public prototype_ `virtual void TickTask(class UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;`
- L29 _public prototype_ `virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;`
- L32 _public member_ `EBTTestTaskStopTiming StopTiming;` — `UPROPERTY()`
- L35 _public member_ `EBTTestStopAction StopAction;` — `UPROPERTY()`
- L38 _public member_ `int32 LogIndex;` — `UPROPERTY()`
- L41 _public member_ `TEnumAsByte<EBTNodeResult::Type> LogResult;` — `UPROPERTY()`

### `Source/Developer/AITestSuite/Classes/BehaviorTree/TestBTTask_LatentWithFlags.h` (Public)


#### struct `FBTLatentTaskMemory`  
`struct FBTLatentTaskMemory`  
_L9-15_
- L11 _public member_ `uint64 FlagFrameIdx;`
- L12 _public member_ `uint64 EndFrameIdx;`
- L13 _public member_ `uint8 bFlagSet : 1;`
- L14 _public member_ `uint8 bIsAborting : 1;`

#### enum `EBTTestChangeFlagBehavior`  
`enum class EBTTestChangeFlagBehavior : uint8`  
_L18-22_
- reflection: `UENUM()`
- L20 _public enumerator_ `Set`
- L21 _public enumerator_ `Toggle`

#### class `UTestBTTask_LatentWithFlags`  
`class UTestBTTask_LatentWithFlags : public UBTTaskNode`  
_L25-82_
- reflection: `UCLASS(meta = (HiddenNode))`
- inherits: `UBTTaskNode`
- L31 _public prototype_ `UTestBTTask_LatentWithFlags();`
- L34 _public member_ `int32 LogIndexExecuteStart = 0;` — `UPROPERTY()`
- L37 _public member_ `int32 LogIndexExecuting = -1;` — `UPROPERTY()`
- L40 _public member_ `int32 LogIndexExecuteFinish = 0;` — `UPROPERTY()`
- L43 _public member_ `int32 LogIndexAbortStart = 0;` — `UPROPERTY()`
- L46 _public member_ `int32 LogIndexAborting = -1;` — `UPROPERTY()`
- L49 _public member_ `int32 LogIndexAbortFinish = 0;` — `UPROPERTY()`
- L53 _public member_ `int32 ExecuteHalfTicks = 2;` — `UPROPERTY()` — Num of ticks before 'execute start' and `set execute flag` and then the same num of ticks before `execute finish`
- L57 _public member_ `int32 AbortHalfTicks = 2;` — `UPROPERTY()` — Num of ticks before 'abort start' and `set abort flag` and then the same num of ticks before `abort finish`
- L60 _public member_ `FName KeyNameExecute = TEXT("Boo` — `UPROPERTY()`
- L63 _public member_ `FName KeyNameAbort = TEXT("Boo` — `UPROPERTY()`
- L66 _public member_ `EBTTestChangeFlagBehavior ChangeFlagBehavior = EBTTestChangeFlagBehavior::Set;` — `UPROPERTY()`
- L69 _public member_ `TEnumAsByte<EBTNodeResult::Type> LogResult = EBTNodeResult::Succeeded;` — `UPROPERTY()`
- L72 _protected prototype_ `virtual EBTNodeResult::Type ExecuteTask(class UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L73 _protected prototype_ `virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L74 _protected prototype_ `virtual uint16 GetInstanceMemorySize() const override;`
- L75 _protected prototype_ `virtual void InitializeMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryInit::Type InitType) const override;`
- L76 _protected prototype_ `virtual void CleanupMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryClear::Type CleanupType) const override;`
- L77 _protected prototype_ `void LogExecution(class UBehaviorTreeComponent& OwnerComp, int32 LogNumber);`
- L79 _protected prototype_ `virtual void TickTask(class UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;`
- L81 _protected prototype_ `void ChangeFlag(UBehaviorTreeComponent& OwnerComp, FName FlagToChange) const;`

### `Source/Developer/AITestSuite/Classes/BehaviorTree/TestBTTask_Log.h` (Public)


#### struct `FBTLogTaskMemory`  
`struct FBTLogTaskMemory`  
_L9-12_
- L11 _public member_ `uint64 EndFrameIdx;`

#### class `UTestBTTask_Log`  
`class UTestBTTask_Log : public UBTTaskNode`  
_L15-43_
- reflection: `UCLASS(meta=(HiddenNode))`
- inherits: `UBTTaskNode`
- L20 _private member_ `int32 LogIndex;` — `UPROPERTY()`
- L23 _private member_ `int32 LogFinished;` — `UPROPERTY()`
- L26 _private member_ `int32 ExecutionTicks;` — `UPROPERTY()`
- L29 _private member_ `int32 LogTickIndex;` — `UPROPERTY()`
- L32 _private member_ `TEnumAsByte<EBTNodeResult::Type> LogResult;` — `UPROPERTY()`
- L34 _private prototype_ `virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L35 _private prototype_ `virtual uint16 GetInstanceMemorySize() const override;`
- L36 _private prototype_ `virtual void InitializeMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryInit::Type InitType) const override;`
- L37 _private prototype_ `virtual void CleanupMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryClear::Type CleanupType) const override;`
- L39 _private prototype_ `void LogExecution(UBehaviorTreeComponent& OwnerComp, int32 LogNumber);`
- L42 _protected prototype_ `virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;`

### `Source/Developer/AITestSuite/Classes/BehaviorTree/TestBTTask_RunBehavior.h` (Public)


#### class `UTestBTTask_RunBehavior`  
`class UTestBTTask_RunBehavior : public UBTTask_RunBehavior`  
_L9-22_
- reflection: `UCLASS(MinimalAPI, meta = (HiddenNode))`
- inherits: `UBTTask_RunBehavior`
- L18 _private function_ `void SetSubtreeAsset(UBehaviorTree* Asset)` — Sets the subtree asset to run. @note This method has been added for test purpose only and should be called only before the task gets activated.

### `Source/Developer/AITestSuite/Classes/BehaviorTree/TestBTTask_SetFlag.h` (Public)


#### class `UTestBTTask_SetFlag`  
`class UTestBTTask_SetFlag : public UBTTaskNode`  
_L10-31_
- reflection: `UCLASS(meta=(HiddenNode))`
- inherits: `UBTTaskNode`
- L15 _private member_ `FName KeyName;` — `UPROPERTY()`
- L18 _private member_ `bool bValue;` — `UPROPERTY()`
- L21 _private member_ `FName OnAbortKeyName;` — `UPROPERTY()`
- L24 _private member_ `bool bOnAbortValue;` — `UPROPERTY()`
- L27 _private member_ `TEnumAsByte<EBTNodeResult::Type> TaskResult;` — `UPROPERTY()`
- L29 _private prototype_ `virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L30 _private prototype_ `virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`

### `Source/Developer/AITestSuite/Classes/BehaviorTree/TestBTTask_SetValue.h` (Public)


#### class `UTestBTTask_SetValue`  
`class UTestBTTask_SetValue : public UBTTaskNode`  
_L10-31_
- reflection: `UCLASS(meta=(HiddenNode))`
- inherits: `UBTTaskNode`
- L15 _private member_ `FName KeyName;` — `UPROPERTY()`
- L18 _private member_ `int32 Value;` — `UPROPERTY()`
- L21 _private member_ `FName OnAbortKeyName;` — `UPROPERTY()`
- L24 _private member_ `int32 OnAbortValue;` — `UPROPERTY()`
- L27 _private member_ `TEnumAsByte<EBTNodeResult::Type> TaskResult;` — `UPROPERTY()`
- L29 _private prototype_ `virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L30 _private prototype_ `virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`

### `Source/Developer/AITestSuite/Classes/BehaviorTree/TestBTTask_SetValuesWithLogs.h` (Public)


#### struct `FBTSetValueTaskMemory`  
`struct FBTSetValueTaskMemory`  
_L8-12_
- L10 _public member_ `uint64 EndFrameIdx;`
- L11 _public member_ `uint64 EndFrameIdx2;`

#### class `UTestBTTask_SetValuesWithLogs`  
`class UTestBTTask_SetValuesWithLogs : public UBTTaskNode`  
_L15-78_
- reflection: `UCLASS(meta=(HiddenNode))`
- inherits: `UBTTaskNode`
- L20 _public prototype_ `UTestBTTask_SetValuesWithLogs(const FObjectInitializer& ObjectInitializer);`
- L24 _public member_ `int32 LogIndex;` — `UPROPERTY()` — Index logged when we execute the task
- L28 _public member_ `int32 LogFinished;` — `UPROPERTY()` — Index logged when we finish the task
- L32 _public member_ `int32 ExecutionTicks1;` — `UPROPERTY()` — Number of execution ticks until we set Blackboard KeyName2 Value2
- L36 _public member_ `int32 ExecutionTicks2;` — `UPROPERTY()` — Number of execution ticks after ExecutionTicks1 that we end the task
- L40 _public member_ `int32 LogTickIndex;` — `UPROPERTY()` — Index logged when we tick the task
- L44 _public member_ `FName KeyName1;` — `UPROPERTY()` — Blackboard keyname used when we start the task
- L48 _public member_ `int32 Value1;` — `UPROPERTY()` — Blackboard value set when we start the task
- L52 _public member_ `FName KeyName2;` — `UPROPERTY()` — Blackboard keyname used after ExecutionTicks1 execution ticks
- L56 _public member_ `int32 Value2;` — `UPROPERTY()` — Blackboard value set after ExecutionTicks1 execution ticks
- L60 _public member_ `FName OnAbortKeyName;` — `UPROPERTY()` — Blackboard keyname used when we abort the task
- L64 _public member_ `int32 OnAbortValue;` — `UPROPERTY()` — Blackboard value set when we abort the task
- L68 _public member_ `TEnumAsByte<EBTNodeResult::Type> TaskResult;` — `UPROPERTY()` — Result when we finish the task
- L71 _protected prototype_ `virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;`
- L72 _protected prototype_ `void LogExecution(UBehaviorTreeComponent& OwnerComp, int32 LogNumber);`
- L73 _protected prototype_ `virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L74 _protected prototype_ `virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L75 _protected prototype_ `virtual uint16 GetInstanceMemorySize() const override;`
- L76 _protected prototype_ `virtual void InitializeMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryInit::Type InitType) const override;`
- L77 _protected prototype_ `virtual void CleanupMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryClear::Type CleanupType) const override;`

### `Source/Developer/AITestSuite/Classes/BehaviorTree/TestBTTask_TimerBasedLatent.h` (Public)


#### struct `FBTTimerBasedLatentTaskMemory`  
`struct FBTTimerBasedLatentTaskMemory`  
_L7-11_
- L9 _public member_ `FTimerHandle TimerHandle;`
- L10 _public member_ `uint8 bIsAborting : 1;`

#### class `UTestBTTask_TimerBasedLatent`  
`class UTestBTTask_TimerBasedLatent : public UBTTaskNode`  
_L14-52_
- reflection: `UCLASS(meta = (HiddenNode))`
- inherits: `UBTTaskNode`
- L20 _public prototype_ `UTestBTTask_TimerBasedLatent();`
- L23 _public member_ `int32 LogIndexExecuteStart = INDEX_NONE;` — `UPROPERTY()`
- L26 _public member_ `int32 LogIndexExecuteFinish = INDEX_NONE;` — `UPROPERTY()`
- L29 _public member_ `int32 LogIndexAbortStart = INDEX_NONE;` — `UPROPERTY()`
- L32 _public member_ `int32 LogIndexAbortFinish = INDEX_NONE;` — `UPROPERTY()`
- L36 _public member_ `int32 NumTicksExecuting = 0;` — `UPROPERTY()` — Num of ticks from 'execute start' to 'execute finish'
- L40 _public member_ `int32 NumTicksAborting = 0;` — `UPROPERTY()` — Num of ticks from 'abort start' to 'abort finish'
- L43 _public member_ `TEnumAsByte<EBTNodeResult::Type> LogResult = EBTNodeResult::Succeeded;` — `UPROPERTY()`
- L46 _protected prototype_ `virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L47 _protected prototype_ `virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L48 _protected prototype_ `virtual uint16 GetInstanceMemorySize() const override;`
- L49 _protected prototype_ `virtual void InitializeMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryInit::Type InitType) const override;`
- L50 _protected prototype_ `virtual void CleanupMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryClear::Type CleanupType) const override;`
- L51 _protected prototype_ `void LogExecution(UBehaviorTreeComponent& OwnerComp, int32 LogNumber) const;`

### `Source/Developer/AITestSuite/Classes/BehaviorTree/TestBTTask_ToggleFlag.h` (Public)


#### class `UTestBTTask_ToggleFlag`  
`class UTestBTTask_ToggleFlag : public UBTTaskNode`  
_L8-28_
- reflection: `UCLASS(meta=(HiddenNode))`
- inherits: `UBTTaskNode`
- L13 _public prototype_ `UTestBTTask_ToggleFlag(const FObjectInitializer& ObjectInitializer);`
- L15 _public prototype_ `virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L18 _public member_ `int32 LogIndex;` — `UPROPERTY()`
- L21 _public member_ `FName KeyName;` — `UPROPERTY()`
- L24 _public member_ `int32 NumToggles;` — `UPROPERTY()`
- L27 _public member_ `TEnumAsByte<EBTNodeResult::Type> TaskResult;` — `UPROPERTY()`

### `Source/Developer/AITestSuite/Classes/MockAI.h` (Public)


#### struct `FTestTickHelper`  
`struct FTestTickHelper : FTickableGameObject`  
_L18-27_
- inherits: `FTickableGameObject`
- L20 _public member_ `TWeakObjectPtr<class UMockAI> Owner;`
- L22 _public function_ `FTestTickHelper() : Owner(nullptr)`
- L23 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L24 _public function_ `virtual bool IsTickable() const override`
- L25 _public function_ `virtual bool IsTickableInEditor() const override`
- L26 _public prototype_ `virtual TStatId GetStatId() const override;`

#### class `UMockAI`  
`class UMockAI : public UObject`  
_L30-62_
- reflection: `UCLASS()`
- inherits: `UObject`
- L36 _private member_ `FTestTickHelper TickHelper;`
- L39 _private member_ `TObjectPtr<AActor> Actor = nullptr;` — `UPROPERTY()`
- L42 _private member_ `TObjectPtr<UBlackboardComponent> BBComp = nullptr;` — `UPROPERTY()`
- L45 _private member_ `TObjectPtr<UBrainComponent> BrainComp = nullptr;` — `UPROPERTY()`
- L48 _private member_ `TObjectPtr<UAIPerceptionComponent> PerceptionComp = nullptr;` — `UPROPERTY()`
- L51 _private function_ `template<typename TBrainClass> void UseBrainComponent()`
- L56 _private prototype_ `void UseBlackboardComponent();`
- L57 _private prototype_ `void UsePerceptionComponent();`
- L59 _private prototype_ `void SetEnableTicking(bool bShouldTick);`
- L61 _private prototype_ `virtual void TickMe(float DeltaTime);`

### `Source/Developer/AITestSuite/Classes/MockAI_BT.h` (Public)


#### class `UMockAI_BT`  
`class UMockAI_BT : public UMockAI`  
_L14-26_
- reflection: `UCLASS()`
- inherits: `UMockAI`
- L19 _private member_ `TObjectPtr<UBehaviorTreeComponent> BTComp;` — `UPROPERTY()`
- L21 _private member_ `static TArray<int32> ExecutionLog;`
- L22 _private member_ `TArray<int32> ExpectedResult;`
- L24 _private prototype_ `bool IsRunning() const;`
- L25 _private prototype_ `void RunBT(UBehaviorTree& BTAsset, EBTExecutionMode::Type RunType = EBTExecutionMode::SingleRun);`

### `Source/Developer/AITestSuite/Classes/MockGameplayTasks.h` (Public)


#### enum `ETestTaskMessage::Type`  
`enum Type`  
_L18-25_
- L20 _public enumerator_ `Activate`
- L21 _public enumerator_ `Tick`
- L22 _public enumerator_ `ExternalConfirm`
- L23 _public enumerator_ `ExternalCancel`
- L24 _public enumerator_ `Ended`

#### class `UMockTask_Log`  
`class UMockTask_Log : public UGameplayTask`  
_L29-55_
- reflection: `UCLASS()`
- inherits: `UGameplayTask`
- L34 _protected member_ `FTestLogger<int32>* Logger;`
- L35 _protected member_ `bool bShoudEndAsPartOfActivation;`
- L38 _public prototype_ `UMockTask_Log(const FObjectInitializer& ObjectInitializer);`
- L40 _public prototype_ `static UMockTask_Log* CreateTask(IGameplayTaskOwnerInterface& TaskOwner, FTestLogger<int32>& InLogger, const FGameplayResourceSet& Resources = FGameplayResourceSet(), uint8 Priority = FGameplayTasks::DefaultPriority);`
- L43 _protected prototype_ `virtual void Activate() override;`
- L44 _protected prototype_ `virtual void OnDestroy(bool bOwnerFinished) override;`
- L47 _public prototype_ `virtual void TickTask(float DeltaTime) override;`
- L48 _public prototype_ `virtual void ExternalConfirm(bool bEndTask) override;`
- L49 _public prototype_ `virtual void ExternalCancel() override;`
- L52 _public function_ `void EnableTick()` — testing only hack-functions
- L54 _public function_ `void SetInstaEnd(bool bNewValue)`

#### class `UMockGameplayTasksComponent`  
`class UMockGameplayTasksComponent : public UGameplayTasksComponent`  
_L61-67_
- reflection: `UCLASS()`
- inherits: `UGameplayTasksComponent`
- desc: a Testing-time component that is a way to access UGameplayTasksComponent's protected properties
- L66 _public function_ `int32 GetTaskPriorityQueueSize() const`

#### class `UMockGameplayTaskOwner`  
`class UMockGameplayTaskOwner : public UObject, public IGameplayTaskOwnerInterface`  
_L70-80_
- reflection: `UCLASS()`
- inherits: `UObject,IGameplayTaskOwnerInterface`
- L76 _public member_ `TObjectPtr<UGameplayTasksComponent> GTComponent;` — `UPROPERTY()`
- L78 _public function_ `virtual UGameplayTasksComponent* GetGameplayTasksComponent(const UGameplayTask& Task) const override`
- L79 _public function_ `virtual AActor* GetGameplayTaskOwner(const UGameplayTask* Task) const`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace ETestTaskMessage`

### `Source/Developer/AITestSuite/Public/AITestSuite.h` (Public)


#### class `IAITestSuite`  
`class IAITestSuite : public IModuleInterface`  
_L13-38_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L24 _public function_ `static inline IAITestSuite& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L34 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Source/Developer/AITestSuite/Public/AITestsCommon.h` (Public)


#### class `FAITestCommand_WaitOneTick`  
`class FAITestCommand_WaitOneTick : public IAutomationLatentCommand`  
_L26-35_
- inherits: `IAutomationLatentCommand`
- L29 _public function_ `FAITestCommand_WaitOneTick() : bAlreadyRun(false)`
- L32 _public prototype_ `virtual bool Update() override;`
- L34 _private member_ `bool bAlreadyRun;`

#### struct `FAITestBase`  
`struct FAITestBase`  
_L46-88_
- L50 _private member_ `TArray<UObject*> SpawnedObjects;` — internals
- L51 _private member_ `uint32 bTearedDown : 1;`
- L53 _protected member_ `FAutomationTestBase* TestRunner;`
- L55 _protected function_ `FAITestBase() : bTearedDown(false), TestRunner(nullptr)`
- L59 _protected function_ `template<typename ClassToSpawn> ClassToSpawn* NewAutoDestroyObject(UObject* Outer = GetTransientPackage())`
- L67 _protected prototype_ `void AddAutoDestroyObject(UObject& ObjectRef);`
- L68 _protected prototype_ `virtual UWorld& GetWorld() const;`
- L70 _protected function_ `FAutomationTestBase& GetTestRunner() const`
- L74 _public function_ `virtual void SetTestRunner(FAutomationTestBase& AutomationTestInstance)`
- L77 _public prototype_ `virtual ~FAITestBase();` — interface
- L79 _public function_ `virtual bool SetUp()` — @return true if setup was completed successfully, false otherwise (which will result in failing the test instance).
- L81 _public function_ `virtual bool Update()` — @return true to indicate that the test is done.
- L83 _public function_ `virtual void VerifyLatentResults()` — lets the Test instance test the results. Use AITEST_*_LATENT macros
- L85 _public function_ `virtual bool InstantTest()` — @return false to indicate an issue with test execution. Will signal to automation framework this test instance failed.
- L87 _public prototype_ `virtual void TearDown();` — it's essential that overriding functions call the super-implementation. Otherwise, the check in ~FAITestBase will fail.

#### struct `FAITest_SimpleComponentBasedTest`  
`template<class FReal> struct FAITest_SimpleComponentBasedTest : public FAITestBase`  
_L173-205_
- inherits: `FAITestBase`
- L175 _public member_ `FTestLogger<int32> Logger;`
- L176 _public member_ `FReal* Component;`
- L178 _public function_ `FAITest_SimpleComponentBasedTest()`
- L183 _public function_ `virtual void SetTestRunner(FAutomationTestBase& AutomationTestInstance) override`
- L189 _public function_ `virtual ~FAITest_SimpleComponentBasedTest() override`
- L194 _public function_ `virtual bool SetUp() override`
- L201 _public function_ `void TickComponent()`

#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAITestSuite, Log, All);`
- L15 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAITestSuite, Log, All);`
- L16 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogBehaviorTreeTest, Log, All);`
- L16 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogBehaviorTreeTest, Log, All);`
- L18 _prototype_ `DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FAITestCommand_WaitSeconds, float, Duration);`
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace AITestSuite` (scope `UE`)
- L23 _prototype_ `void ConditionallyBreakOnTestFail();` (scope `UE::AITestSuite`) — Will cause UE_DEBUG_BREAK if `test.BreakOnTestFail` console variable is true
- L37 _namespace_ `namespace FAITestHelpers`
- L39 _prototype_ `UWorld* GetWorld();` (scope `FAITestHelpers`)
- L40 _variable_ `static constexpr float TickInterval = 1.f / 30;` (scope `FAITestHelpers`)
- L42 _prototype_ `void UpdateFrameCounter();` (scope `FAITestHelpers`)
- L43 _prototype_ `uint64 FramesCounter();` (scope `FAITestHelpers`)
- L96 _macro_ `#define IMPLEMENT_AI_LATENT_TEST(TestClass, PrettyName) \` — @note that TestClass needs to derive from FAITestBase
- L114 _macro_ `#define IMPLEMENT_AI_INSTANT_TEST_WITH_FLAGS(TestClass, PrettyName, TestFlags) \`
- L134 _macro_ `#define IMPLEMENT_AI_INSTANT_TEST(TestClass, PrettyName) \`
- L162 _macro_ `#define IMPLEMENT_INSTANT_TEST_WITH_FIXTURE(Fixture, PrettyGroupNameString, TestExperiment) \` — This macro allows one to implement a whole set of simple tests that share common setups. To use it first implement a struct that builds the said common setup. Like so: struct FMyCommonSetup : public FAITestBase { virtual bool SetUp() override { // your test common setup build code here // return false if setup fails and the test needs to be aborted return true; } }; Once that's done you can implement a specific test using this setup class like so: IMPLEMENT_INSTANT_TEST_WITH_FIXTURE(FMyCommonSetup, "System.Engine.AI.MyTestGroup", ThisSpecificTestName) { // your test code here // return false to indicate the whole test instance failed for some reason return true; }
- L213 _macro_ `#define __AITEST_IMPL(_TestRunner, What, Value, Test, RetVal)\`
- L220 _macro_ `#define AITEST_TRUE_EX(_TestRunner, What, Value) __AITEST_IMPL(_TestRunner, What, Value, TestTrue, false)`
- L221 _macro_ `#define AITEST_FALSE_EX(_TestRunner, What, Value) __AITEST_IMPL(_TestRunner, What, Value, TestFalse, false)`
- L222 _macro_ `#define AITEST_NULL_EX(_TestRunner, What, Pointer) __AITEST_IMPL(_TestRunner, What, Pointer, TestNull, false)`
- L223 _macro_ `#define AITEST_NOT_NULL_EX(_TestRunner, What, Pointer) \`
- L227 _macro_ `#define AITEST_TRUE(What, Value) AITEST_TRUE_EX(GetTestRunner(), What, Value)`
- L228 _macro_ `#define AITEST_FALSE(What, Value) AITEST_FALSE_EX(GetTestRunner(), What, Value)`
- L229 _macro_ `#define AITEST_NULL(What, Pointer) AITEST_NULL_EX(GetTestRunner(), What, Pointer)`
- L230 _macro_ `#define AITEST_NOT_NULL(What, Pointer) AITEST_NOT_NULL_EX(GetTestRunner(), What, Pointer)`
- L232 _namespace_ `namespace FTestHelpers`
- L235 _function_ `template<typename T1, typename T2> inline bool TestEqual(const FString& Description, T1 Expression, T2 Expected, FAutomationTestBase& This)` (scope `FTestHelpers`)
- L241 _function_ `template<typename T1, typename T2> inline bool TestEqual(const FString& Description, T1* Expression, T2* Expected, FAutomationTestBase& This)` (scope `FTestHelpers`)
- L247 _function_ `template<typename T1, typename T2> inline bool TestNotEqual(const FString& Description, T1 Expression, T2 Expected, FAutomationTestBase& This)` (scope `FTestHelpers`)
- L253 _function_ `template<typename T1, typename T2> inline bool TestNotEqual(const FString& Description, T1* Expression, T2* Expected, FAutomationTestBase& This)` (scope `FTestHelpers`)
- L258 _function_ `inline void AddInfo(const FString& Info, FAutomationTestBase& This)` (scope `FTestHelpers`)
- L264 _macro_ `#define __AITEST_HELPER_IMPL(_TestRunner, What, Actual, Expected, Test, RetVal)\`
- L271 _macro_ `#define AITEST_EQUAL_EX(_TestRunner, What, Actual, Expected) __AITEST_HELPER_IMPL(_TestRunner, What, Actual, Expected, TestEqual, false)`
- L272 _macro_ `#define AITEST_NOT_EQUAL_EX(_TestRunner, What, Actual, Expected) __AITEST_HELPER_IMPL(_TestRunner, What, Actual, Expected, TestNotEqual, false)`
- L273 _macro_ `#define AITEST_INFO_EX(_TestRunner, InfoString) FTestHelpers::AddInfo(InfoString, _TestRunner)`
- L275 _macro_ `#define AITEST_EQUAL(What, Actual, Expected) AITEST_EQUAL_EX(GetTestRunner(), What, Actual, Expected)`
- L276 _macro_ `#define AITEST_NOT_EQUAL(What, Actual, Expected) AITEST_NOT_EQUAL_EX(GetTestRunner(), What, Actual, Expected)`
- L277 _macro_ `#define AITEST_INFO(InfoString) AITEST_INFO_EX(GetTestRunner(), InfoString)`
- L289 _macro_ `#define AITEST_TRUE_LATENT(What, Value) __AITEST_IMPL(GetTestRunner(), What, Value, TestTrue, )`
- L290 _macro_ `#define AITEST_FALSE_LATENT(What, Value) __AITEST_IMPL(GetTestRunner(), What, Value, TestFalse, )`
- L291 _macro_ `#define AITEST_NULL_LATENT(What, Pointer) __AITEST_IMPL(GetTestRunner(), What, Pointer, TestNull, )`
- L292 _macro_ `#define AITEST_NOT_NULL_LATENT(What, Pointer) __AITEST_IMPL(GetTestRunner(), What, Pointer, TestNotNull, )`
- L293 _macro_ `#define AITEST_EQUAL_LATENT(What, Actual, Expected) __AITEST_HELPER_IMPL(GetTestRunner(), What, Actual, Expected, TestEqual, )`
- L294 _macro_ `#define AITEST_NOT_EQUAL_LATENT(What, Actual, Expected) __AITEST_HELPER_IMPL(GetTestRunner(), What, Actual, Expected, TestNotEqual, )`

### `Source/Developer/AITestSuite/Public/BTBuilder.h` (Public)


#### struct `FBTBuilder`  
`struct FBTBuilder`  
_L33-435_
- L35 _public function_ `static UBehaviorTree& CreateBehaviorTree()`
- L72 _public function_ `static UBehaviorTree& CreateBehaviorTree(UBehaviorTree& ParentTree)`
- L80 _public function_ `static UBTComposite_Selector& AddSelector(UBehaviorTree& TreeOb)`
- L88 _public function_ `static UBTComposite_Selector& AddSelector(UBTCompositeNode& ParentNode)`
- L99 _public function_ `static UBTComposite_Sequence& AddSequence(UBehaviorTree& TreeOb)`
- L107 _public function_ `static UBTComposite_Sequence& AddSequence(UBTCompositeNode& ParentNode)`
- L118 _public function_ `static UBTComposite_SimpleParallel& AddParallel(UBehaviorTree& TreeOb, EBTParallelMode::Type Mode)`
- L127 _public function_ `static UBTComposite_SimpleParallel& AddParallel(UBTCompositeNode& ParentNode, EBTParallelMode::Type Mode)`
- L140 _public function_ `template<class T> static T& AddTask(UBTCompositeNode& ParentNode, UClass* TaskClass = T::StaticClass())`
- L148 _public function_ `static void AddTask(UBTCompositeNode& ParentNode, int32 LogIndex, EBTNodeResult::Type NodeResult, int32 ExecutionTicks = 0, int32 LogTickIndex = -1)`
- L160 _public function_ `static void AddTaskLogFinish(UBTCompositeNode& ParentNode, int32 LogIndex, int32 FinishIndex, EBTNodeResult::Type NodeResult, int32 ExecutionTicks = 0)`
- L172 _public function_ `static void AddTaskFlagChange(UBTCompositeNode& ParentNode, bool bValue, EBTNodeResult::Type NodeResult, FName BoolKeyName = TEXT("Bool1"), FName BoolOnAbortKeyName = FName(), bool bOnAbortValue = false)`
- L185 _public function_ `static void AddTaskToggleFlag(UBTCompositeNode& ParentNode, EBTNodeResult::Type NodeResult, FName BoolKeyName, int32 NumToggles)`
- L196 _public function_ `static void AddTaskValueChange(UBTCompositeNode& ParentNode, int32 Value, EBTNodeResult::Type NodeResult, FName IntKeyName = TEXT("Int"), FName IntOnAbortKeyName = FName(), int32 OnAbortValue = 0)`
- L209 _public function_ `static void AddTaskValuesChangedWithLogs(UBTCompositeNode& ParentNode, int32 LogIndex, EBTNodeResult::Type NodeResult, int32 Value1, int32 Value2, FName IntKeyName1 = TEXT("Int"), FName IntKeyName2 = TEXT("Int2"), int32 ExecutionTicks1 = 0, int32 ExecutionTicks2 = 0, int32 LogTickIndex = -1, int32 LogFinished = -1, FName IntOnAbortKeyName = FName(), int32 OnAbortValue = 0)`
- L229 _public function_ `static void AddTaskSubtree(UBTCompositeNode& ParentNode, UBehaviorTree* TreeAsset)`
- L241 _public function_ `static void AddTaskLatentFlags(UBTCompositeNode& ParentNode, EBTNodeResult::Type NodeResult, int32 ExecuteHalfTicks, FName ExecuteKeyName, int32 ExecuteLogStart, int32 ExecuteLogFinish, int32 AbortHalfTicks = 0, FName AbortKeyName = NAME_None, int32 AbortLogStart = 0, int32 AbortLogFinish = 0, EBTTestChangeFlagBehavior ChangeFlagBehavior = EBTTestChangeFlagBehavior::Set)`
- L263 _public function_ `static void AddTaskBTStopAction(UBTCompositeNode& ParentNode, int32 LogIndex, EBTNodeResult::Type NodeResult, EBTTestTaskStopTiming StopTiming, EBTTestStopAction StopAction)`
- L276 _public function_ `template<class T> static T& WithDecorator(UBTCompositeNode& ParentNode, UClass* DecoratorClass = T::StaticClass())`
- L287 _public function_ `static void WithDecoratorBlackboard(UBTCompositeNode& ParentNode, EBasicKeyOperation::Type Condition, EBTFlowAbortMode::Type Observer, FName BoolKeyName = TEXT("Bool1"), int32 LogIndexBecomeRelevant = -1, int32 LogIndexCeaseRelevant = -1, int32 LogIndexCalculate = -1)`
- L309 _public function_ `static void WithDecoratorBlackboard(UBTCompositeNode& ParentNode, EArithmeticKeyOperation::Type Condition, int32 Value, EBTFlowAbortMode::Type Observer, EBTBlackboardRestart::Type NotifyMode, FName IntKeyName = TEXT("Int"), int32 LogIndexBecomeRelevant = -1, int32 LogIndexCeaseRelevant = -1, int32 LogIndexCalculate = -1)`
- L339 _public function_ `static void WithDecoratorDelayedAbort(UBTCompositeNode& ParentNode, int32 NumTicks, bool bAbortOnlyOnce = true)`
- L346 _public function_ `static void WithDecoratorBlueprint(UBTCompositeNode& ParentNode, EBTFlowAbortMode::Type Observer, EBPConditionType BPConditionType = EBPConditionType::TrueCondition, int32 LogIndexBecomeRelevant = -1, int32 LogIndexCeaseRelevant = -1, int32 LogIndexCalculate = -1, FName ObservingKeyName = NAME_None )`
- L361 _public function_ `static void WithDecoratorLoop(UBTCompositeNode& ParentNode, int32 NumLoops = 2)`
- L367 _public function_ `static void WithDecoratorLoopUntil(UBTCompositeNode& ParentNode, EBTNodeResult::Type RequiredResult)`
- L374 _public function_ `template<class T> static T& WithService(UBTCompositeNode& ParentNode, UClass* ServiceClass = T::StaticClass())`
- L382 _public function_ `static void WithServiceLog(UBTCompositeNode& ParentNode, int32 ActivationIndex, int32 DeactivationIndex, int32 TickIndex = INDEX_NONE, FName TickBoolKeyName = NAME_None, bool bCallTickOnSearchStart = false, FName BecomeRelevantBoolKeyName = NAME_None, FName CeaseRelevantBoolKeyName = NAME_None, bool bToggleValue = false, int32 TicksDelaySetKeyNameTick = 0)`
- L395 _public function_ `static void WithServiceBTStopAction(UBTCompositeNode& ParentNode, int32 LogIndex, EBTTestServiceStopTiming StopTiming, EBTTestStopAction StopAction)`
- L404 _public function_ `template<class T> static T& WithTaskService(UBTCompositeNode& ParentNode, UClass* ServiceClass = T::StaticClass())`
- L415 _public function_ `static void WithTaskServiceLog(UBTCompositeNode& ParentNode, int32 ActivationIndex, int32 DeactivationIndex, int32 TickIndex = INDEX_NONE, FName TickBoolKeyName = NAME_None, bool bCallTickOnSearchStart = false, FName BecomeRelevantBoolKeyName = NAME_None, FName CeaseRelevantBoolKeyName = NAME_None, bool bToggleValue = false)`
- L427 _public function_ `static void WithTaskServiceBTStopAction(UBTCompositeNode& ParentNode, int32 LogIndex, EBTTestServiceStopTiming StopTiming, EBTTestStopAction StopAction)`

### `Source/Developer/AITestSuite/Public/TestLogger.h` (Public)


#### struct `FTestLogger`  
`template<typename ValueType> struct FTestLogger`  
_L10-42_
- L12 _public member_ `TArray<ValueType> ExpectedValues;`
- L13 _public member_ `TArray<ValueType> LoggedValues;`
- L14 _public member_ `FAutomationTestBase* TestRunner;`
- L16 _public function_ `FTestLogger(FAutomationTestBase* InTestRunner = nullptr) : TestRunner(InTestRunner)`
- L21 _public function_ `~FTestLogger()`
- L26 _public function_ `void Log(const ValueType& Value)`

### `Source/Developer/AITestSuite/Public/TestableEnsures.h` (Public)


#### Free symbols / members of external scopes

- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogTestableEnsures, Log, All);`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace AITestSuite` (scope `UE`)
- L15 _externvar_ `extern int32 TestsInProgress;` (scope `UE::AITestSuite`)
- L18 _macro_ `#define AITEST_SCOPED_CHECK(PartialTextToExpect, NumOccurrences) \`
- L32 _macro_ `#define aiTestableEnsureMsgf(InExpression, InFormat, ... ) \`
- L46 _macro_ `#define aiTestableCheckf(InExpression, InFormat, ... ) \`
- L60 _macro_ `#define aiTestableCheckfReturn(InExpression, ReturnExpression, InFormat, ... ) \`
