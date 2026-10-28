# Plugins / ControlFlows

- module root: `Plugins/Experimental/ControlFlows/Source/ControlFlows`
- headers: 10; symbols: 324
- symbol kinds: class=20, delegate=9, enum=3, enumerator=6, function=61, macro=2, member=72, namespace=4, prototype=142, struct=2, typedef=2, variable=1
- PrivateDependencyModuleNames: Core, CoreUObject

### `Plugins/Experimental/ControlFlows/Source/ControlFlows/Public/ControlFlow.h` (Public)


#### class `FControlFlow`  
`class FControlFlow : public TSharedFromThis<FControlFlow>`  
_L124-420_
- inherits: `TSharedFromThis<FControlFlow>`
- L127 _public prototype_ `FControlFlow(const FString& FlowDebugName = TEXT(""));`
- L131 _public prototype_ `void ExecuteFlow();` — This needs to be called, otherwise nothing will happen!! Call after you finish adding functions to the queue. Calling with an empty queue is safe.
- L132 _public prototype_ `void Reset();`
- L133 _public prototype_ `bool IsRunning() const;`
- L134 _public function_ `size_t NumInQueue() const`
- L136 _public function_ `FSimpleMulticastDelegate& OnNodeComplete() const`
- L137 _public function_ `FSimpleMulticastDelegate& OnFlowComplete() const`
- L138 _public function_ `FSimpleMulticastDelegate& OnFlowCancel() const`
- L141 _public prototype_ `void CancelFlow();` — Will cancel ALL flows, both child ControlFlows and ControlFlows who owns this Flow. You've been warned.
- L143 _public prototype_ `FControlFlow& SetCancelledNodeAsComplete(bool bCancelledNodeIsComplete);`
- L145 _public prototype_ `TOptional<FString> GetCurrentStepDebugName() const;`
- L147 _public prototype_ `TSharedPtr<FTrackedActivity> GetTrackedActivity() const;`
- L150 _public prototype_ `FControlFlow& QueueDelay(const float InSeconds, const FString& NodeName = FString());`
- L151 _public prototype_ `FControlFlow& QueueSetCancelledNodeAsComplete(const bool bCancelledNodeIsComplete, const FString& NodeName = FString());`
- L154 _public function_ `template<typename...ArgsT> FControlFlow& QueueStep(const FString& NodeName, ArgsT...Params)`
- L161 _public function_ `template<typename...ArgsT> FControlFlow& QueueStep(const TCHAR* NodeName, ArgsT...Params)`
- L168 _public function_ `template<typename...ArgsT> FControlFlow& QueueStep(const char* NodeName, ArgsT...Params)`
- L175 _public function_ `template<typename...ArgsT> FControlFlow& QueueStep(ArgsT...Params)`
- L183 _public function_ `template<typename FunctionT, typename...ArgsT> FControlFlow& Loop(FunctionT InLoopLambda, ArgsT...Params)`
- L190 _public function_ `template<typename...ArgsT> FControlFlow& SwitchFlow(ArgsT...Args)`
- L196 _public function_ `template<typename FunctionT, typename...ArgsT> FControlFlow& BranchFlow(FunctionT InBranchLambda, ArgsT...Params)`
- L203 _public function_ `template<typename...ArgsT> FControlFlow& SplitFlow(ArgsT...Args)`
- L209 _public function_ `template<typename FunctionT, typename...ArgsT> FControlFlow& ForkFlow(FunctionT InForkLambda, ArgsT...Params)`
- L215 _public prototype_ `FControlFlow& TrackActivities(TSharedPtr<FTrackedActivity> InActivity = nullptr);`
- L218 _public prototype_ `FSimpleDelegate& QueueFunction(const FString& FlowNodeDebugName = TEXT(""));`
- L219 _public prototype_ `FControlFlowWaitDelegate& QueueWait(const FString& FlowNodeDebugName = TEXT(""));`
- L220 _public prototype_ `FControlFlowPopulator& QueueControlFlow(const FString& TaskName = TEXT(""), const FString& FlowNodeDebugName = TEXT(""));`
- L221 _public prototype_ `FControlFlowBranchDefiner& QueueControlFlowBranch(const FString& TaskName = TEXT(""), const FString& FlowNodeDebugName = TEXT(""));`
- L222 _public prototype_ `FConcurrentFlowsDefiner& QueueConcurrentFlows(const FString& TaskName = TEXT(""), const FString& FlowNodeDebugName = TEXT(""));`
- L223 _public prototype_ `FControlFlowConditionalLoopDefiner& QueueConditionalLoop(const FString& TaskName = TEXT(""), const FString& FlowNodeDebugName = TEXT(""));`
- L227 _private function_ `template<typename BindingObjectT, typename...PayloadParamsT> void QueueStep_Internal(const FString& InDebugName, TSharedRef<BindingObjectT> InBindingObject, PayloadParamsT...Params)`
- L235 _private function_ `template<typename BindingObjectT, typename...ArgsT> void QueueStep_Internal(const FString& InDebugName, BindingObjectT* InBindingObject, ArgsT...Params)`
- L242 _private function_ `template<typename BindingObjectClassT, typename...ArgsT> void QueueStep_Internal_DeduceBindingObject(const FString& InDebugName, typename TEnableIf<IsDerivedFromSharedFromThis<BindingObjectClassT>(), BindingObjectClassT*>::Type InBindingObject, ArgsT...Params)`
- L251 _private function_ `template<typename BindingObjectClassT, typename...ArgsT> void QueueStep_Internal_DeduceBindingObject(const FString& InDebugName, typename TEnableIf<TIsDerivedFrom<BindingObjectClassT, UObject>::IsDerived, BindingObjectClassT*>::Type InBindingObject, ArgsT...Params)`
- L259 _private function_ `template<typename BindingObjectClassT, typename...PayloadParamsT> void QueueStep_Internal_TSharedFromThis(const FString& InDebugName, TSharedRef<BindingObjectClassT> InBindingObject, typename TMemFunPtrType<false, BindingObjectClassT, EConditionalLoopResult(TSharedRef<FConditionalLoop>, PayloadParamsT...)>::Type InFunction, PayloadParamsT...Params)`
- L297 _private function_ `template<typename BindingObjectClassT, typename...PayloadParamsT> void QueueStep_Internal_UObject(const FString& InDebugName, BindingObjectClassT* InBindingObject, typename TMemFunPtrType<false, BindingObjectClassT, EConditionalLoopResult(TSharedRef<FConditionalLoop>, PayloadParamsT...)>::Type InFunction, PayloadParamsT...Params)`
- L347 _public prototype_ `TSharedRef<FControlFlowTask_BranchLegacy> QueueBranch(FControlFlowBranchDecider_Legacy& BranchDecider, const FString& TaskName = TEXT(""), const FString& FlowNodeDebugName = TEXT(""));` — Both of these implementations are deprecated
- L348 _public prototype_ `FControlFlowPopulator& QueueLoop(FControlFlowLoopComplete& LoopCompleteDelgate, const FString& TaskName = TEXT(""), const FString& FlowNodeDebugName = TEXT(""));`
- L351 _private function_ `inline void SetProfilerEventStarted()`
- L353 _private prototype_ `void HandleControlFlowNodeCompleted(const TSharedRef<const FControlFlowNode>& NodeCompleted);`
- L355 _private member_ `mutable FSimpleMulticastDelegate OnStepCompletedDelegate;`
- L356 _private member_ `mutable FSimpleMulticastDelegate OnFlowCompleteDelegate;`
- L357 _private member_ `mutable FSimpleMulticastDelegate OnFlowCancelledDelegate;`
- L359 _private member_ `mutable FSimpleDelegate OnCompleteDelegate_Internal;`
- L360 _private member_ `mutable FSimpleDelegate OnExecutedWithoutAnyNodesDelegate_Internal;`
- L361 _private member_ `mutable FSimpleDelegate OnCancelledDelegate_Internal;`
- L362 _private member_ `mutable FSimpleDelegate OnNodeWasNotBoundedOnExecution_Internal;`
- L365 _private prototype_ `void ExecuteNextNodeInQueue();`
- L367 _private prototype_ `void ExecuteNode(TSharedRef<FControlFlowNode_SelfCompleting> SelfCompletingNode);`
- L369 _private prototype_ `void HandleTaskNodeExecuted(TSharedRef<FControlFlowNode_Task> TaskNode);`
- L370 _private prototype_ `void HandleTaskNodeCancelled(TSharedRef<FControlFlowNode_Task> TaskNode);`
- L372 _private prototype_ `void HandleOnTaskComplete();`
- L373 _private prototype_ `void HandleOnTaskCancelled();`
- L375 _private prototype_ `void BroadcastCancellation();`
- L378 _private prototype_ `void LogNodeExecution(const FControlFlowNode& NodeExecuted);`
- L380 _private prototype_ `FString GetFlowPath() const;`
- L382 _private prototype_ `int32 GetRepeatedFlowCount() const;`
- L385 _public function_ `const FString& GetDebugName() const`
- L388 _private prototype_ `FString FormatOrGetNewNodeDebugName(const FString& FlowNodeDebugName = TEXT(""));`
- L392 _private member_ `static int32 UnnamedControlFlowCounter;`
- L394 _private member_ `FString DebugName;`
- L396 _private member_ `bool bInterpretCancelledNodeAsComplete = false;`
- L398 _private member_ `bool bBroadcastingStepComplete = false;`
- L400 _private member_ `int32 UnnamedNodeCounter = 0;`
- L402 _private member_ `int32 UnnamedBranchCounter = 0;`
- L404 _private member_ `TSharedPtr<FControlFlowNode_Task> CurrentlyRunningTask = nullptr;`
- L406 _private member_ `TSharedPtr<FControlFlowNode> CurrentNode = nullptr;`
- L408 _private member_ `TWeakPtr<FControlFlow> ParentFlow;`
- L410 _private member_ `TPair<double , float > LastZeroSecondDelay;`
- L413 _private member_ `TArray<TSharedRef<FControlFlow>> SubFlowStack_ForDebugging;` — TODO: Put behind some args, because this is expensive.
- L415 _private member_ `TArray<TSharedRef<FControlFlowNode>> FlowQueue;`
- L417 _private member_ `TSharedPtr<FTrackedActivity> Activity;`
- L419 _private member_ `bool bProfilerEventStarted = false;`

#### Free symbols / members of external scopes

- L424 _macro_ `#define CONTROL_FLOW_PERF_TRACE_STEP(FlowHandle, EventName) \`
- L433 _macro_ `#define CONTROL_FLOW_PERF_TRACE_STEP(FlowHandle, EventName)`

### `Plugins/Experimental/ControlFlows/Source/ControlFlows/Public/ControlFlowBranch.h` (Public)


#### class `FControlFlowBranch`  
`class FControlFlowBranch : public TSharedFromThis<FControlFlowBranch>`  
_L9-46_
- inherits: `TSharedFromThis<FControlFlowBranch>`
- L12 _public function_ `FControlFlow& AddOrGetBranch(const int32& InKey, const FString& DebugBranchName = TEXT(""))`
- L28 _public function_ `bool Contains(const int32& Key) const`
- L29 _public function_ `TSharedRef<FControlFlow>& FindChecked(const int32& Key)`
- L31 _public function_ `bool IsAnyBranchRunning() const`
- L45 _private member_ `TMap<int32, TSharedRef<FControlFlow>> Branches;`

#### Free symbols / members of external scopes

- L7 _variable_ `static int32 UnnamedControlFlowBranchCounter = 0;`

### `Plugins/Experimental/ControlFlows/Source/ControlFlows/Public/ControlFlowConcurrency.h` (Public)


#### enum `EConcurrentExecution`  
`enum class EConcurrentExecution`  
_L12-17_
- L14 _public enumerator_ `Default` — Flows will execute in a single thread; always in the same order
- L15 _public enumerator_ `Random` — Flows will execute in a single thread; random order
- L16 _public enumerator_ `Parallel` — Flows will execute in actual separate threads

#### class `FConcurrentControlFlows`  
`class FConcurrentControlFlows : public TSharedFromThis<FConcurrentControlFlows>`  
_L20-61_
- inherits: `TSharedFromThis<FConcurrentControlFlows>`
- desc: All Flows will be executed concurrently (or in-parallel, See: EConcurrentExecution). WARNING: Having a non-terminating loop within a fork can cause a forever hang for the forked step
- L25 _public prototype_ `FControlFlow& AddOrGetProng(int32 InIdentifier, const FString& DebugSubFlowName = TEXT(""));`
- L26 _public prototype_ `FControlFlow& AddOrGetFlow(int32 InIdentifier, const FString& DebugSubFlowName = TEXT(""));`
- L28 _public prototype_ `FConcurrentControlFlows& SetExecution(const EConcurrentExecution InBehavior);`
- L36 _private prototype_ `bool AreAllSubFlowsCompletedOrCancelled() const;`
- L37 _private prototype_ `bool HasAnySubFlowBeenExecuted() const;`
- L39 _private prototype_ `void HandleConcurrentFlowDone(int32 FlowIndex, const bool bCompleted);`
- L41 _private prototype_ `void CheckToBroadcastComplete();`
- L43 _private prototype_ `void Execute();`
- L44 _private prototype_ `void CancelAll();` — Do not make public
- L46 _private prototype_ `void OnAllCompleted();`
- L47 _private prototype_ `void OnAllCancelled();`
- L49 _private member_ `FSimpleDelegate OnConcurrencyCompleted;`
- L50 _private member_ `FSimpleDelegate OnConcurrencyCancelled;`
- L52 _private member_ `EConcurrentExecution ExecutionBehavior = EConcurrentExecution::Default;`
- L53 _private member_ `bool bCancelAllHasBegun = false;`
- L54 _private member_ `TSharedPtr<FConcurrentControlFlows::FParallelFlowLock, ESPMode::ThreadSafe> ParallelFlowLock;`
- L55 _private member_ `TMap<int32, TSharedRef<FConcurrencySubFlowContainer>> ConcurrentFlows;`
- L57 _private member_ `TWeakPtr<FControlFlowSubTaskBase> OwningTask;`
- L60 _private prototype_ `FConcurrentControlFlowBehavior GetConcurrencyBehavior() const;`

#### struct `FConcurrentControlFlows::FParallelFlowLock`  
`struct FParallelFlowLock`  
_L23-23_

#### struct `FConcurrencySubFlowContainer`  
`struct FConcurrencySubFlowContainer : public TSharedFromThis<FConcurrencySubFlowContainer>`  
_L63-88_
- inherits: `TSharedFromThis<FConcurrencySubFlowContainer>`
- L65 _public prototype_ `FConcurrencySubFlowContainer(const FString& InDebugName);`
- L70 _private prototype_ `bool HasBeenExecuted() const;`
- L71 _private prototype_ `bool HasBeenCancelled() const;`
- L72 _private prototype_ `bool IsCompleteOrCancelled() const;`
- L74 _private prototype_ `void Execute(TWeakPtr<FConcurrentControlFlows::FParallelFlowLock> InFlowLock);`
- L75 _private prototype_ `void Cancel();`
- L76 _private prototype_ `FSimpleDelegate& OnComplete();`
- L77 _private prototype_ `FSimpleDelegate& OnExecutedWithoutAnyNodes();`
- L78 _private prototype_ `FSimpleDelegate& OnCancelled();`
- L79 _private prototype_ `const FString& GetDebugName();`
- L81 _private prototype_ `TSharedRef<FControlFlow> GetControlFlow() const;`
- L83 _private member_ `bool bHasBeenExecuted = false;`
- L84 _private member_ `bool bHasBeenCancelled = false;`
- L86 _private member_ `TSharedRef<FControlFlow> SubFlow;`
- L87 _private member_ `TSharedPtr<FConcurrentControlFlows::FParallelFlowLock, ESPMode::ThreadSafe> ParallelFlowLock;`

#### class `FConcurrentControlFlowBehavior`  
`class FConcurrentControlFlowBehavior`  
_L91-116_
- desc: Placeholder class to extend Concurrency behavior
- L115 _private function_ `EContinueConditions GetContinueCondition() const`

#### enum `FConcurrentControlFlowBehavior::EContinueConditions`  
`enum class EContinueConditions`  
_L95-113_
- L97 _public enumerator_ `Default`

### `Plugins/Experimental/ControlFlows/Source/ControlFlows/Public/ControlFlowConditionalLoop.h` (Public)


#### class `FConditionalLoop`  
`class FConditionalLoop : public TSharedFromThis<FConditionalLoop>`  
_L11-26_
- inherits: `TSharedFromThis<FConditionalLoop>`
- desc: In contrast to, for example, iterator loops
- L14 _public prototype_ `FConditionalLoop();`
- L16 _public prototype_ `FControlFlow& CheckConditionFirst();`
- L17 _public prototype_ `FControlFlow& RunLoopFirst();`
- L18 _public prototype_ `FControlFlow& ExecuteAtLeastOnce();`
- L19 _public prototype_ `FControlFlow& SetCheckConditionFirst(bool bInValue);`
- L24 _private member_ `TOptional<bool> CheckConditionalFirst;`
- L25 _private member_ `TSharedRef<FControlFlow> FlowLoop;`

### `Plugins/Experimental/ControlFlows/Source/ControlFlows/Public/ControlFlowContainer.h` (Public)


#### class `FControlFlowContainerBase`  
`class FControlFlowContainerBase : public TSharedFromThis<FControlFlowContainerBase>`  
_L22-49_
- inherits: `TSharedFromThis<FControlFlowContainerBase>`
- L25 _public prototype_ `FControlFlowContainerBase() = delete;`
- L26 _public prototype_ `virtual ~FControlFlowContainerBase() = default;`
- L28 _public function_ `FControlFlowContainerBase(TSharedRef<FControlFlow> InFlow, const FString& FlowId) : ControlFlow(InFlow), FlowName(FlowId)`
- L35 _public prototype_ `virtual bool OwningObjectEqualTo(const void* InObject) const = 0;`
- L37 _public function_ `const FString& GetFlowName() const`
- L39 _public function_ `TSharedRef<FControlFlow> GetControlFlow() const`
- L42 _private prototype_ `virtual bool OwningObjectIsValid() const = 0;`
- L46 _private member_ `TSharedRef<FControlFlow> ControlFlow;`
- L48 _private member_ `FString FlowName;`

#### class `TControlFlowContainer`  
`template<typename T> class TControlFlowContainer : public FControlFlowContainerBase`  
_L52-74_
- inherits: `FControlFlowContainerBase`
- L55 _public prototype_ `TControlFlowContainer() = delete;`
- L56 _public function_ `TControlFlowContainer(T* InOwner, TSharedRef<FControlFlow> InFlow, const FString& FlowId) : FControlFlowContainerBase(InFlow, FlowId) , OwningObject(InOwner)`
- L62 _private function_ `virtual bool OwningObjectEqualTo(const void* InObject) const override final`
- L67 _private function_ `virtual bool OwningObjectIsValid() const override final`
- L73 _private member_ `TWeakPtrVariant<T> OwningObject;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Private` (scope `UE`)
- L15 _prototype_ `static bool OwningObjectIsValid(TSharedRef<const FControlFlowContainerBase> InFlowContainer);` (scope `UE::Private`)
- L76 _namespace_ `namespace UE`
- L76 _namespace_ `namespace Private` (scope `UE`)
- L78 _function_ `static inline bool OwningObjectIsValid(TSharedRef<const FControlFlowContainerBase> InFlowContainer)` (scope `UE::Private`)

### `Plugins/Experimental/ControlFlows/Source/ControlFlows/Public/ControlFlowManager.h` (Public)


#### class `FControlFlowStatics`  
`class FControlFlowStatics`  
_L12-162_
- L16 _public function_ `template<typename OwningObjectT> static FControlFlow& Create(OwningObjectT* OwningObject, const FString& FlowId)`
- L31 _public function_ `template<typename OwningObjectT> static void StopFlow(OwningObjectT* OwningObject, const FString& FlowId)`
- L44 _public function_ `template<typename OwningObjectT> static FControlFlow* Find(OwningObjectT* OwningObject, const FString& FlowId)`
- L56 _public function_ `template<typename OwningObjectT> static FControlFlow& FindOrCreate(OwningObjectT* OwningObject, const FString& FlowId, bool bResetIfFound = false)`
- L69 _public function_ `template<typename OwningObjectT> static bool IsRunning(OwningObjectT* OwningObject, const FString& FlowId)`
- L77 _private prototype_ `static TArray<TSharedRef<FControlFlowContainerBase>>& GetNewlyCreatedFlows();` — These flows will be checked the next frame to make sure they are executed. If they are not, it will execute the flow and remove from this array.
- L80 _private prototype_ `static TArray<TSharedRef<FControlFlowContainerBase>>& GetPersistentFlows();` — These flows will not be checked the next frame, and will be moved to executing when we find ourselves executing.
- L83 _private prototype_ `static TArray<TSharedRef<FControlFlowContainerBase>>& GetExecutingFlows();` — Flows that are actively running.
- L86 _private prototype_ `static TArray<TSharedRef<FControlFlowContainerBase>>& GetFinishedFlows();` — Final Array that flows are moved to before being deleted.
- L90 _private function_ `template<typename OwningObjectT> static FControlFlow& Create_Internal(OwningObjectT* OwningObject, const FString& FlowId, bool bIsPersistent)`
- L114 _private function_ `template<typename OwningObjectT> static TSharedPtr<FControlFlow> Find_Internal(OwningObjectT* OwningObject, const FString& FlowId, TArray<TSharedRef<FControlFlowContainerBase>>& InArray)`
- L140 _private prototype_ `static void HandleControlFlowStartedNotification(TSharedRef<const FControlFlow> InFlow);`
- L141 _private function_ `static void HandleControlFlowFinishedNotification()`
- L144 _private prototype_ `static void CheckNewlyCreatedFlows();`
- L145 _private prototype_ `static void CheckForInvalidFlows();`
- L148 _private prototype_ `static bool IterateThroughNewlyCreatedFlows(float DeltaTime);`
- L149 _private prototype_ `static bool IterateForInvalidFlows(float DeltaTime);`
- L152 _private prototype_ `static FControlFlowStatics& Get();`
- L155 _private member_ `TArray<TSharedRef<FControlFlowContainerBase>> NewlyCreatedFlows;`
- L156 _private member_ `TArray<TSharedRef<FControlFlowContainerBase>> PersistentFlows;`
- L157 _private member_ `TArray<TSharedRef<FControlFlowContainerBase>> ExecutingFlows;`
- L158 _private member_ `TArray<TSharedRef<FControlFlowContainerBase>> FinishedFlows;`
- L160 _private member_ `FTSTicker::FDelegateHandle NextFrameCheckForExecution;`
- L161 _private member_ `FTSTicker::FDelegateHandle NextFrameCheckForFlowCleanup;`

### `Plugins/Experimental/ControlFlows/Source/ControlFlows/Public/ControlFlowNode.h` (Public)


#### enum `EConditionalLoopResult`  
`enum class EConditionalLoopResult`  
_L29-33_
- L31 _public enumerator_ `RunLoop`
- L32 _public enumerator_ `LoopFinished`

#### class `FControlFlowNode`  
`class FControlFlowNode : public TSharedFromThis<FControlFlowNode>`  
_L38-71_
- inherits: `TSharedFromThis<FControlFlowNode>`
- L41 _public prototype_ `FControlFlowNode();`
- L42 _public prototype_ `FControlFlowNode(TSharedRef<FControlFlow> ControlFlowParent, const FString& FlowNodeDebugName);`
- L44 _public prototype_ `virtual ~FControlFlowNode();`
- L46 _public prototype_ `void ContinueFlow();`
- L47 _public prototype_ `virtual void CancelFlow();`
- L49 _public prototype_ `TSharedPtr<FTrackedActivity> GetTrackedActivity() const;`
- L51 _public function_ `[[nodiscard]] bool HasCancelBeenRequested() const`
- L53 _public prototype_ `virtual FString GetNodeName() const;`
- L55 _public prototype_ `void SetProfilerEventStarted();`
- L57 _public function_ `[[nodiscard]] const TWeakPtr<FControlFlow>& GetParent() const`
- L63 _protected function_ `virtual void Execute()`
- L65 _protected prototype_ `void LogExecution();`
- L67 _protected member_ `TWeakPtr<FControlFlow> Parent = nullptr;`
- L68 _protected member_ `FString NodeName;`
- L69 _protected member_ `bool bCancelled = false;`
- L70 _protected member_ `bool bWasBoundOnExecution = true;`

#### class `FControlFlowNode_RequiresCallback`  
`class FControlFlowNode_RequiresCallback : public FControlFlowNode`  
_L73-86_
- inherits: `FControlFlowNode`
- L76 _public prototype_ `FControlFlowNode_RequiresCallback(TSharedRef<FControlFlow> ControlFlowParent, const FString& FlowNodeDebugName);`
- L77 _public prototype_ `FControlFlowNode_RequiresCallback(TSharedRef<FControlFlow> ControlFlowParent, const FString& FlowNodeDebugName, const FControlFlowWaitDelegate& InCallback);`
- L80 _protected prototype_ `virtual void Execute() override;`
- L85 _private member_ `FControlFlowWaitDelegate Process;`

#### class `FControlFlowNode_SelfCompleting`  
`class FControlFlowNode_SelfCompleting : public FControlFlowNode`  
_L88-101_
- inherits: `FControlFlowNode`
- L91 _public prototype_ `FControlFlowNode_SelfCompleting(TSharedRef<FControlFlow> ControlFlowParent, const FString& FlowNodeDebugName);`
- L92 _public prototype_ `FControlFlowNode_SelfCompleting(TSharedRef<FControlFlow> ControlFlowParent, const FString& FlowNodeDebugName, const FSimpleDelegate& InCallback);`
- L95 _protected prototype_ `virtual void Execute() override;`
- L100 _private member_ `FSimpleDelegate Process;`

#### class `FControlFlowNode_Task`  
`class FControlFlowNode_Task : public FControlFlowNode`  
_L105-130_
- inherits: `FControlFlowNode`
- L108 _public prototype_ `FControlFlowNode_Task(TSharedRef<FControlFlow> ControlFlowParent, TSharedRef<FControlFlowSubTaskBase> ControlFlowTask, const FString& FlowNodeDebugName);`
- L111 _public prototype_ `virtual void CancelFlow() override;`
- L116 _protected function_ `FContolFlowTaskEvent& OnExecute() const`
- L117 _protected function_ `FContolFlowTaskEvent& OnCancelRequested() const`
- L119 _protected prototype_ `virtual void Execute() override;`
- L120 _protected prototype_ `virtual FString GetNodeName() const override;`
- L121 _protected prototype_ `void CompleteCancelFlow();`
- L123 _protected function_ `TSharedRef<FControlFlowSubTaskBase> GetFlowTask() const`
- L126 _private member_ `mutable FContolFlowTaskEvent OnExecuteDelegate;`
- L127 _private member_ `mutable FContolFlowTaskEvent OnCancelRequestedDelegate;`
- L129 _private member_ `TSharedRef<FControlFlowSubTaskBase> FlowTask;`

#### Free symbols / members of external scopes

- L17 _typedef_ `using FControlFlowNodePtr = TSharedPtr<FControlFlowNode>;`
- L18 _typedef_ `using FControlFlowNodeRef = TSharedRef<FControlFlowNode>;`
- L20 _delegate_ `DECLARE_DELEGATE_OneParam(FControlFlowWaitDelegate, FControlFlowNodeRef) DECLARE_DELEGATE_OneParam(FControlFlowPopulator, TSharedRef<FControlFlow>) DECLARE_DELEGATE_RetVal(bool, FControlFlowLoopComplete) DECLARE_DELEGATE_RetVal(int32, FControlFlowBranchDecider_Legacy)`
- L20 _prototype_ `DECLARE_DELEGATE_OneParam(FControlFlowWaitDelegate, FControlFlowNodeRef) DECLARE_DELEGATE_OneParam(FControlFlowPopulator, TSharedRef<FControlFlow>) DECLARE_DELEGATE_RetVal(bool, FControlFlowLoopComplete) DECLARE_DELEGATE_RetVal(int32, FControlFlowBranchDecider_Legacy)`
- L21 _delegate_ `DECLARE_DELEGATE_OneParam(FControlFlowPopulator, TSharedRef<FControlFlow>) DECLARE_DELEGATE_RetVal(bool, FControlFlowLoopComplete) DECLARE_DELEGATE_RetVal(int32, FControlFlowBranchDecider_Legacy)`
- L23 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FControlFlowLoopComplete) DECLARE_DELEGATE_RetVal(int32, FControlFlowBranchDecider_Legacy)`
- L24 _delegate_ `DECLARE_DELEGATE_RetVal(int32, FControlFlowBranchDecider_Legacy)`
- L27 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(int32, FControlFlowBranchDefiner, TSharedRef<FControlFlowBranch>);` — Would be nice to not force people to use int32 for the branch key, but finding the syntax to get it to work properly proved to be more difficult than it was worth. End result is callers have to cast to an int32.
- L34 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(EConditionalLoopResult, FControlFlowConditionalLoopDefiner, TSharedRef<FConditionalLoop>);`
- L34 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(EConditionalLoopResult, FControlFlowConditionalLoopDefiner, TSharedRef<FConditionalLoop>);`
- L36 _delegate_ `DECLARE_DELEGATE_OneParam(FConcurrentFlowsDefiner, TSharedRef<FConcurrentControlFlows>);`
- L36 _prototype_ `DECLARE_DELEGATE_OneParam(FConcurrentFlowsDefiner, TSharedRef<FConcurrentControlFlows>);`
- L103 _delegate_ `DECLARE_DELEGATE_OneParam(FContolFlowTaskEvent, TSharedRef<FControlFlowNode_Task>);`
- L103 _prototype_ `DECLARE_DELEGATE_OneParam(FContolFlowTaskEvent, TSharedRef<FControlFlowNode_Task>);`

### `Plugins/Experimental/ControlFlows/Source/ControlFlows/Public/ControlFlowTask.h` (Public)


#### class `FControlFlowSubTaskBase`  
`class FControlFlowSubTaskBase : public TSharedFromThis<FControlFlowSubTaskBase>`  
_L8-37_
- inherits: `TSharedFromThis<FControlFlowSubTaskBase>`
- desc: Empty Task
- L11 _public function_ `FControlFlowSubTaskBase()`
- L12 _public prototype_ `FControlFlowSubTaskBase(const FString& TaskName);`
- L14 _public prototype_ `virtual ~FControlFlowSubTaskBase() = default;`
- L16 _public function_ `const FString& GetTaskName() const`
- L17 _public function_ `void SetOwningNode(TSharedRef<FControlFlowNode_Task> InNode)`
- L18 _public prototype_ `TWeakPtr<FControlFlow> GetOwningFlowForTaskNode() const;`
- L23 _protected function_ `FSimpleDelegate& OnComplete() const`
- L24 _protected function_ `FSimpleDelegate& OnCancelled() const`
- L26 _protected prototype_ `virtual void Execute();`
- L27 _protected prototype_ `virtual void Cancel();`
- L30 _protected member_ `TWeakPtr<FControlFlowNode_Task> OwningNode;`
- L33 _private member_ `mutable FSimpleDelegate TaskCompleteCallback;`
- L34 _private member_ `mutable FSimpleDelegate TaskCancelledCallback;`
- L36 _private member_ `FString DebugName;`

#### class `FControlFlowSimpleSubTask`  
`class FControlFlowSimpleSubTask : public FControlFlowSubTaskBase`  
_L41-63_
- inherits: `FControlFlowSubTaskBase`
- L44 _public prototype_ `FControlFlowSimpleSubTask(const FString& TaskName);`
- L49 _protected function_ `FControlFlowPopulator& GetTaskPopulator() const`
- L51 _protected function_ `TSharedPtr<FControlFlow> GetTaskFlow() const`
- L53 _protected prototype_ `virtual void Execute() override;`
- L54 _protected prototype_ `virtual void Cancel() override;`
- L57 _private prototype_ `void CompletedSubTask();`
- L58 _private prototype_ `void CancelledSubTask();`
- L60 _private member_ `mutable FControlFlowPopulator TaskPopulator;`
- L62 _private member_ `TSharedPtr<FControlFlow> TaskFlow = nullptr;`

#### class `FControlFlowTask_LoopDeprecated`  
`class FControlFlowTask_LoopDeprecated : public FControlFlowSimpleSubTask`  
_L67-83_
- inherits: `FControlFlowSimpleSubTask`
- L71 _public prototype_ `FControlFlowTask_LoopDeprecated(FControlFlowLoopComplete& TaskCompleteDelegate, const FString& TaskName);`
- L75 _protected prototype_ `virtual void Execute() override;`
- L76 _protected prototype_ `virtual void Cancel() override;`
- L79 _private prototype_ `void CompletedLoop();`
- L80 _private prototype_ `void CancelledLoop();`
- L82 _private member_ `FControlFlowLoopComplete TaskCompleteDecider;`

#### class `FControlFlowTask_BranchLegacy`  
`class FControlFlowTask_BranchLegacy : public FControlFlowSubTaskBase`  
_L87-130_
- inherits: `FControlFlowSubTaskBase`
- L90 _public prototype_ `FControlFlowTask_BranchLegacy(FControlFlowBranchDecider_Legacy& BranchDecider, const FString& TaskName);`
- L93 _public prototype_ `FSimpleDelegate& QueueFunction(int32 BranchIndex, const FString& FlowNodeDebugName = TEXT(""));` — Returns a delegate for easier syntax to bind a function for the flow to execute and then move on
- L96 _public prototype_ `FControlFlowWaitDelegate& QueueWait(int32 BranchIndex, const FString& FlowNodeDebugName = TEXT(""));` — The flow will execute this function where the bound function takes in a ControlFlowNode. The Flow will pause until ControlFlowNode->CompleteExecution() is called.
- L99 _public prototype_ `FControlFlowPopulator& QueueControlFlow(int32 BranchIndex, const FString& TaskName = TEXT(""), const FString& FlowNodeDebugName = TEXT(""));` — Allows you to break up your flow into Smaller Tasks to help organize your flow. The flow will execute the FControlFlowPopulator only once
- L102 _public prototype_ `TSharedRef<FControlFlowTask_BranchLegacy> QueueBranch(int32 BranchIndex, FControlFlowBranchDecider_Legacy& BranchDecider, const FString& TaskName = TEXT(""), const FString& FlowNodeDebugName = TEXT(""));` — Adds a branch to your flow. The flow will use FControlFlowBranchDecider to determine which flow branch to execute
- L105 _public prototype_ `FControlFlowPopulator& QueueLoop(int32 BranchIndex, FControlFlowLoopComplete& LoopCompleteDelgate, const FString& TaskName = TEXT(""), const FString& FlowNodeDebugName = TEXT(""));` — Adds a Loop to your flow. The flow will use FControlFlowLoopComplete - if this returns false, the flow will execute FControlFlowPopulator until true is returned
- L108 _public function_ `template <typename... VarTypes> void QueueStep(int32 BranchIndex, VarTypes... Vars)`
- L116 _protected prototype_ `virtual void Execute() override;`
- L117 _protected prototype_ `virtual void Cancel() override;`
- L120 _private prototype_ `void HandleBranchCompleted();`
- L121 _private prototype_ `void HandleBranchCancelled();`
- L123 _private prototype_ `TSharedRef<FControlFlow> GetOrAddBranch(int32 BranchIndex);`
- L125 _private member_ `mutable FControlFlowBranchDecider_Legacy BranchDelegate;`
- L127 _private member_ `TMap<int32, TSharedRef<FControlFlow>> Branches;`
- L129 _private member_ `TOptional<int32> SelectedBranch;`

#### class `FControlFlowTask_Branch`  
`class FControlFlowTask_Branch : public FControlFlowSubTaskBase`  
_L134-159_
- inherits: `FControlFlowSubTaskBase`
- L140 _public function_ `FControlFlowTask_Branch(const FString& TaskName) : FControlFlowSubTaskBase(TaskName)`
- L144 _public function_ `FControlFlowBranchDefiner& GetDelegate()`
- L146 _public member_ `TSharedPtr<FTrackedActivity> Activity;`
- L149 _protected prototype_ `virtual void Execute() override;`
- L150 _protected prototype_ `virtual void Cancel() override;`
- L154 _private prototype_ `void HandleBranchCompleted();`
- L155 _private prototype_ `void HandleBranchCancelled();`
- L157 _private member_ `FControlFlowBranchDefiner BranchDelegate;`
- L158 _private member_ `TSharedPtr<FControlFlow> SelectedBranchFlow;`

#### class `FControlFlowTask_ConcurrentFlows`  
`class FControlFlowTask_ConcurrentFlows : public FControlFlowSubTaskBase`  
_L163-186_
- inherits: `FControlFlowSubTaskBase`
- L169 _public function_ `FControlFlowTask_ConcurrentFlows(const FString& TaskName) : FControlFlowSubTaskBase(TaskName)`
- L173 _public function_ `FConcurrentFlowsDefiner& GetDelegate()`
- L176 _protected prototype_ `virtual void Execute() override;`
- L177 _protected prototype_ `virtual void Cancel() override;`
- L181 _private prototype_ `void HandleConcurrentFlowsCompleted();`
- L182 _private prototype_ `void HandleConcurrentFlowsCancelled();`
- L184 _private member_ `FConcurrentFlowsDefiner ConcurrentFlowDelegate;`
- L185 _private member_ `TSharedPtr<FConcurrentControlFlows> ConcurrentFlows;`

### `Plugins/Experimental/ControlFlows/Source/ControlFlows/Public/ControlFlowTask_Loop.h` (Public)


#### class `FControlFlowTask_ConditionalLoop`  
`class FControlFlowTask_ConditionalLoop : public FControlFlowSubTaskBase`  
_L10-41_
- inherits: `FControlFlowSubTaskBase`
- desc: In contrast to, for example, iterator loops
- L13 _public function_ `FControlFlowTask_ConditionalLoop(const FString& TaskName) : FControlFlowSubTaskBase(TaskName)`
- L17 _public function_ `FControlFlowConditionalLoopDefiner& GetDelegate()`
- L21 _protected prototype_ `virtual void Execute() override;`
- L22 _protected prototype_ `virtual void Cancel() override;`
- L25 _private prototype_ `void Helper_ConditionalCheck(const EConditionalLoopResult InCondition) const;`
- L27 _private prototype_ `void HandleLoopCompleted();`
- L28 _private prototype_ `void HandleLoopCancelled();`
- L29 _private prototype_ `void HandleOnNodeWasNotBoundedOnExecution();`
- L31 _private member_ `FControlFlowConditionalLoopDefiner ConditionalLoopDelegate;`
- L32 _private member_ `TSharedPtr<FConditionalLoop> ConditionalLoop;`
- L34 _private member_ `bool bHandleUsed = false;`
- L40 _private member_ `bool bStopLoopingOnUnboundedDelegate = false;` — While using the '.Loop' syntax, the object doing the bounding can suddenly be destroyed and cause a stack overflow with an infinite loop 'bStopLoopingOnUnboundedDelegate' is used to prevent this

### `Plugins/Experimental/ControlFlows/Source/ControlFlows/Public/ControlFlows.h` (Public)


#### class `FControlFlowsModule`  
`class FControlFlowsModule : public IModuleInterface`  
_L10-17_
- inherits: `IModuleInterface`
- L15 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L16 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogControlFlows, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogControlFlows, Log, All);`
