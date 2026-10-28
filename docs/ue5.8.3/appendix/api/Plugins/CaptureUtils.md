# Plugins / CaptureUtils

- module root: `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureUtils`
- headers: 22; symbols: 383
- symbol kinds: class=34, delegate=4, enum=2, enumerator=9, function=46, macro=15, member=76, namespace=44, prototype=129, struct=7, typedef=17
- PrivateDependencyModuleNames: 
- PublicDependencyModuleNames: Core, Engine, Networking, Sockets

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureUtils/Internal/ProcessRunner/ProcessRunner.h` (Internal)


#### enum `UE::CaptureManager::EProcessRunnerError`  
`enum class EProcessRunnerError : int32`  
_L13-21_
- L15 _public enumerator_ `PipeCreationFailed`
- L16 _public enumerator_ `LaunchFailed`
- L17 _public enumerator_ `Timeout`
- L18 _public enumerator_ `Cancelled`
- L19 _public enumerator_ `FailedToGetReturnCode`
- L20 _public enumerator_ `ExitedWithError`

#### class `UE::CaptureManager::FProcessRunner`  
`class UE_INTERNAL FProcessRunner`  
_L25-37_
- L28 _public prototype_ `static FProcessRunnerResult Run( const FString& InProcessPath, const FString& InProcessArguments, const FStopToken* InStopToken = nullptr, const TOptional<int32> InTimeoutSeconds = TOptional<int32>());`
- L35 _private prototype_ `static TArray<uint8> ReadPipe(void* InPipe);`
- L36 _private prototype_ `static TArray<uint8> DrainPipe(void* InPipe);`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace CaptureManager` (scope `UE`)
- L23 _typedef_ `using FProcessRunnerResult = TValueOrError<TArray<uint8>, EProcessRunnerError>;` (scope `UE::CaptureManager`)

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureUtils/Public/Asset/CaptureAssetSanitization.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace CaptureManager` (scope `UE`)
- L10 _prototype_ `void SanitizePackagePath(FString& OutPath, FString::ElementType InReplaceWith = TEXT('_'));` (scope `UE::CaptureManager`) — Replaces any invalid package path characters
- L13 _prototype_ `void SanitizeAssetName(FString& OutPath, FString::ElementType InReplaceWith = TEXT('_'));` (scope `UE::CaptureManager`) — Replaces any invalid object name characters

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureUtils/Public/Async/CallbackSynchronizer.h` (Public)


#### struct `UE::CaptureManager::ArgsBundle`  
`template<typename ...> struct ArgsBundle`  
_L17-19_

#### struct `UE::CaptureManager::FFunctionTraits`  
`template<typename T> struct FFunctionTraits : public FFunctionTraits<decltype(&T::operator())>`  
_L22-24_
- inherits: `FFunctionTraits<decltype(&T::operator())>`
- L29 _public typedef_ `using ReturnType = Return;`
- L30 _public typedef_ `using FnArgs = ArgsBundle<Args ...>;`
- L31 _public typedef_ `using FnType = Return(Args ...);`

#### struct `UE::CaptureManager::FFunctionTraits`  
`template<typename Return, typename Object, typename ... Args> struct FFunctionTraits<Return(Object::*)(Args ...)>`  
_L27-32_
- L29 _public typedef_ `using ReturnType = Return;`
- L30 _public typedef_ `using FnArgs = ArgsBundle<Args ...>;`
- L31 _public typedef_ `using FnType = Return(Args ...);`

#### struct `UE::CaptureManager::FFunctionTraits`  
`template<typename Return, typename Object, typename ... Args> struct FFunctionTraits<Return(Object::*)(Args ...) const>`  
_L35-40_
- L29 _public typedef_ `using ReturnType = Return;`
- L30 _public typedef_ `using FnArgs = ArgsBundle<Args ...>;`
- L31 _public typedef_ `using FnType = Return(Args ...);`

#### struct `UE::CaptureManager::FFunctionTraits`  
`template<typename Return, typename ... Args> struct FFunctionTraits<Return(*)(Args ...)>`  
_L43-48_
- L29 _public typedef_ `using ReturnType = Return;`
- L30 _public typedef_ `using FnArgs = ArgsBundle<Args ...>;`
- L31 _public typedef_ `using FnType = Return(Args ...);`

#### class `UE::CaptureManager::FCallbackSynchronizer`  
`class FCallbackSynchronizer : public TSharedFromThis<FCallbackSynchronizer>`  
_L50-97_
- inherits: `TSharedFromThis<FCallbackSynchronizer>`
- L53 _public prototype_ `DECLARE_DELEGATE(FAfterAllDelegate);`
- L55 _public prototype_ `FCallbackSynchronizer();`
- L56 _public prototype_ `~FCallbackSynchronizer();`
- L59 _public function_ `template<typename FCallback> auto CreateCallback(FCallback&& InCallback)`
- L65 _public prototype_ `void AfterAll(FAfterAllDelegate InAfterAllDelegate, bool bExecuteIfCounterZero = true);`
- L67 _public prototype_ `static TSharedPtr<FCallbackSynchronizer> Create();`
- L92 _private prototype_ `void Decrease();`
- L94 _private member_ `FAfterAllDelegate AfterAllDelegate;`
- L96 _private member_ `std::atomic_int Counter;`

#### struct `UE::CaptureManager::FCallbackSynchronizer::FMakeCallbackInternal`  
`template<typename ... Args> struct FMakeCallbackInternal<ArgsBundle<Args ...> >`  
_L75-90_
- L78 _public function_ `template<typename LT> static auto Get(TSharedPtr<FCallbackSynchronizer> InCallbackSynchronizer, LT&& InUserFn)`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API CAPTUREUTILS_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace CaptureManager` (scope `UE`)
- L53 _delegate_ `DECLARE_DELEGATE(FAfterAllDelegate);`
- L61 _typedef_ `using FIdentityFnArgs = typename FFunctionTraits<FCallback>::FnArgs;` (scope `UE::CaptureManager::FCallbackSynchronizer::CreateCallback`)
- L84 _function_ `` (scope `UE::CaptureManager::FCallbackSynchronizer::FMakeCallbackInternal::Get`)

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureUtils/Public/Async/CaptureTimerManager.h` (Public)


#### class `UE::CaptureManager::FCaptureTimerManager`  
`class FCaptureTimerManager`  
_L16-52_
- L20 _public typedef_ `using FTimerHandle = FTSTicker::FDelegateHandle;`
- L22 _public prototype_ `FCaptureTimerManager();`
- L23 _public prototype_ `FCaptureTimerManager(const float Resolution);`
- L25 _public prototype_ `~FCaptureTimerManager();`
- L27 _public prototype_ `FTimerHandle AddTimer(FTimerDelegate InDelegate, float InRate, bool InbLoop = false, float InFirstDelay = 0.f);`
- L28 _public prototype_ `void RemoveTimer(FTimerHandle Handle);`
- L31 _private member_ `static constexpr float IdealTimeResolution = 0.1f;`
- L49 _private member_ `FTSTicker Ticker;`
- L50 _private member_ `TUniquePtr<FRunnableThread> Thread;`
- L51 _private member_ `TUniquePtr<FTimerManagerRunnable> Runnable;`

#### class `UE::CaptureManager::FCaptureTimerManager::FTimerManagerRunnable`  
`class FTimerManagerRunnable final : public FRunnable`  
_L33-47_
- inherits: `FRunnable`
- L37 _public prototype_ `FTimerManagerRunnable(FCaptureTimerManager* InOwner, const float InResolution);`
- L39 _public prototype_ `virtual uint32 Run() override;`
- L40 _public prototype_ `virtual void Stop() override;`
- L44 _private member_ `FCaptureTimerManager* Owner;`
- L45 _private member_ `std::atomic_bool bShouldRun = true;`
- L46 _private member_ `const float IdealTimeResolution;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API CAPTUREUTILS_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace CaptureManager` (scope `UE`)

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureUtils/Public/Async/Event.h` (Public)


#### class `UE::CaptureManager::FCaptureEvent`  
`class FCaptureEvent`  
_L25-37_
- desc: Base class for all event sublasses
- L28 _public prototype_ `const FString& GetName() const;`
- L29 _public prototype_ `virtual ~FCaptureEvent();`
- L32 _protected prototype_ `FCaptureEvent(FString InName);`
- L36 _private member_ `FString Name;`

#### class `UE::CaptureManager::ICaptureEventSource`  
`class ICaptureEventSource`  
_L54-60_
- desc: Interface for classes that wish to provide capture event subscription to their clients
- L57 _public prototype_ `virtual TArray<FString> GetAvailableEvents() const = 0;`
- L58 _public prototype_ `virtual void SubscribeToEvent(const FString& InEventName, FCaptureEventHandler InHandler) = 0;`
- L59 _public prototype_ `virtual void UnsubscribeAll() = 0;`

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API CAPTUREUTILS_API`
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace CaptureManager` (scope `UE`)
- L40 _macro_ `#define CAPTURE_DEFINE_EMPTY_EVENT(ClassName, EventName) \` — Macro for easy definition of events that don't carry any data
- L51 _typedef_ `using FCaptureEventHandler = TManagedDelegate<TSharedPtr<const FCaptureEvent>>;` (scope `UE::CaptureManager`) — The SharedPtr points to a `const` event object because the shared event might end up on multiple threads in which case we'd have a thread safety issue without the event being `const`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureUtils/Public/Async/EventSourceUtils.h` (Public)


#### class `UE::CaptureManager::Private::FCaptureEventSourceBase`  
`class FCaptureEventSourceBase : public ICaptureEventSource`  
_L13-34_
- inherits: `ICaptureEventSource`
- L16 _public prototype_ `virtual ~FCaptureEventSourceBase();`
- L19 _public prototype_ `virtual TArray<FString> GetAvailableEvents() const override;`
- L21 _public prototype_ `virtual void SubscribeToEvent(const FString& InEventName, FCaptureEventHandler InHandler) override;` — NOTE: SubscribeToEvent() must not be called from an event handler that is being executed on the same thread
- L22 _public prototype_ `virtual void UnsubscribeAll() override;`
- L25 _protected prototype_ `void RegisterEvent(const FString& InEventName);`
- L26 _protected prototype_ `void PublishEventInternal(TSharedPtr<const FCaptureEvent> InEvent) const;`
- L29 _private typedef_ `using FHandlers = TTSMulticastDelegate<void(TSharedPtr<const FCaptureEvent>)>;`
- L31 _private member_ `mutable FRWLock HandlersLock;`
- L32 _private member_ `TMap<FString, FHandlers> EventToHandlersMap;`

#### class `UE::CaptureManager::FCaptureEventSource`  
`class FCaptureEventSource : public Private::FCaptureEventSourceBase`  
_L38-54_
- inherits: `Private::FCaptureEventSourceBase`
- desc: Class to be publicly inherited to get basic event source functionality. All functions are thread-safe.
- L42 _protected function_ `template<typename EventType, typename ... Args> void PublishEvent(Args&&... InArgs) const`
- L47 _protected function_ `void PublishEventPtr(TSharedPtr<const FCaptureEvent> InEvent) const`

#### class `UE::CaptureManager::FCaptureEventSourceWithLimiter`  
`class FCaptureEventSourceWithLimiter : public Private::FCaptureEventSourceBase`  
_L57-113_
- inherits: `Private::FCaptureEventSourceBase`
- desc: Class to be publicly inherited to get event source functionality where rate of events published is limited. All functions are thread-safe.
- L60 _public function_ `FCaptureEventSourceWithLimiter(int32 InThresholdMillis) : ThresholdMillis(InThresholdMillis), LastPublish(0)`
- L73 _protected function_ `template<typename EventType, typename ... EventArgs> bool PublishIfThresholdReached(bool bInForcePublish, EventArgs&& ... InEventArgs)` — When PublishIfThresholdReached() is called the publishing will mostly only occur if the time since last publish is greater than the threshold (although this isn't guaranteed and multiple events can still be published in rare cases). The unpublished events are simply dropped (i.e. not buffered so the client has to make sure that won't cause problems to the subscribers. The client can also force publish an event which will do the publishing no matter what the current time is and reset the time measurement. This is handy for publishing events whose dropping will break continuity for the client or for publishing the last event in a line of optional events to trigger the final update.
- L91 _protected function_ `void PublishEventIgnoreThresholdPtr(TSharedPtr<const FCaptureEvent> InEvent)` — Always publishes the event while completely ignoring the threshold mechanism. If you want to force publishing of an event AND update the "last publish" timestamp, please use PublishIfThresholdReached(true, ...)
- L97 _protected function_ `template<typename EventType, typename ... EventArgs> void PublishEventIgnoreThreshold(EventArgs&&... InEventArgs)`
- L105 _private function_ `bool IsThresholdPassed(const FDateTime& InLastPublish, const FDateTime& InNow) const`
- L111 _private member_ `const int32 ThresholdMillis;`
- L112 _private member_ `std::atomic<int64> LastPublish;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API CAPTUREUTILS_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace CaptureManager` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::CaptureManager`)

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureUtils/Public/Async/HelperFunctions.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace CaptureManager` (scope `UE`)
- L11 _prototype_ `void CallOnGameThread(TFunction<void()> InFunction);` (scope `UE::CaptureManager`) — Sends InFunction to be called on the GameThread and waits for the result

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureUtils/Public/Async/ManagedDelegate.h` (Public)


#### enum `UE::CaptureManager::EDelegateExecutionThread`  
`enum class EDelegateExecutionThread`  
_L11-16_
- L13 _public enumerator_ `GameThread = 0`
- L14 _public enumerator_ `InternalThread` — Thread on which the function invoking the delegate is being run on
- L15 _public enumerator_ `AnyThread`

#### class `UE::CaptureManager::TManagedDelegate`  
`template<typename ... Args> class TManagedDelegate`  
_L61-100_
- L64 _public typedef_ `using Type = TDelegate<void(Args...)>;`
- L66 _public prototype_ `TManagedDelegate() = default;`
- L69 _public function_ `template<typename Func> TManagedDelegate(Func InFunc, EDelegateExecutionThread InThread = EDelegateExecutionThread::GameThread) : TManagedDelegate(Type::CreateLambda(MoveTemp(InFunc)), InThread)`
- L74 _public function_ `TManagedDelegate(Type InDelegate, EDelegateExecutionThread InThread = EDelegateExecutionThread::GameThread) : Delegate(MoveTemp(InDelegate)) , ExecutionThread(InThread)`
- L80 _public function_ `void operator()(Args... InArgs)`
- L88 _public function_ `void operator()(Args... InArgs) const`
- L98 _private member_ `Type Delegate;`
- L99 _private member_ `EDelegateExecutionThread ExecutionThread;`

#### class `UE::CaptureManager::TManagedMulticastDelegate`  
`template<typename ... Args> class TManagedMulticastDelegate`  
_L103-139_
- L106 _public typedef_ `using DelegateType = TDelegate<void(Args...)>;`
- L108 _public prototype_ `TManagedMulticastDelegate() = default;`
- L111 _public function_ `template<typename Func> void Add(Func InFunc, EDelegateExecutionThread InThread = EDelegateExecutionThread::GameThread)`
- L116 _public function_ `void Add(DelegateType InDelegate, EDelegateExecutionThread InThread = EDelegateExecutionThread::GameThread)`
- L124 _public function_ `void operator()(Args... InArgs)`
- L129 _public function_ `void operator()(Args... InArgs) const`
- L136 _private typedef_ `using Type = TMulticastDelegate<void(Args...)>;`
- L138 _private member_ `Type Delegate;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace CaptureManager` (scope `UE`)
- L18 _namespace_ `namespace Private` (scope `UE::CaptureManager`)
- L21 _function_ `static ENamedThreads::Type GetThreadType(EDelegateExecutionThread InThread)` (scope `UE::CaptureManager::Private`)
- L36 _function_ `template<typename ... Args> static void ExecuteDelegate(TDelegate<void(Args...)> InDelegate, EDelegateExecutionThread InThread, Args&&... InArgs)` (scope `UE::CaptureManager::Private`)
- L48 _function_ `` (scope `UE::CaptureManager::Private::ExecuteDelegate`)
- L119 _function_ `` (scope `UE::CaptureManager::TManagedMulticastDelegate::Add`)

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureUtils/Public/Async/Monitor.h` (Public)


#### class `UE::CaptureManager::TMonitor`  
`template<typename T> class TMonitor`  
_L11-77_
- L18 _public function_ `template <typename... Args> TMonitor(Args&&... InArgs) : Object(Forward<Args>(InArgs)...)`
- L23 _public function_ `TMonitor(T InObject) : Object(MoveTemp(InObject))`
- L53 _public function_ `FHelper operator->()`
- L58 _public function_ `FHelper Lock()`
- L63 _public function_ `T& GetUnsafe()`
- L68 _public function_ `T Claim()`
- L75 _private member_ `FCriticalSection Mutex;`
- L76 _private member_ `T Object;`

#### class `UE::CaptureManager::TMonitor::FHelper`  
`class FHelper`  
_L28-51_
- L31 _public function_ `FHelper(TMonitor* InOwner) : Owner(InOwner) , ScopeLock(&InOwner->Mutex)`
- L37 _public function_ `T* operator->()`
- L42 _public function_ `T& operator*()`
- L49 _private member_ `TMonitor* Owner;`
- L50 _private member_ `FScopeLock ScopeLock;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace CaptureManager` (scope `UE`)

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureUtils/Public/Async/QueueRunner.h` (Public)


#### class `UE::CaptureManager::TQueueRunner`  
`template<class T> class TQueueRunner : public FRunnable`  
_L17-104_
- inherits: `FRunnable`
- L21 _public function_ `DECLARE_DELEGATE_OneParam(FOnProcess, T InElem) TQueueRunner(FOnProcess InOnProcess = nullptr) : bRunning(false) , OnProcess(MoveTemp(InOnProcess))`
- L30 _public function_ `virtual ~TQueueRunner() override`
- L38 _public function_ `void Add(T InElement)`
- L48 _public function_ `void Empty()`
- L54 _public function_ `bool IsRunning() const`
- L61 _protected function_ `virtual uint32 Run() override`
- L88 _protected function_ `virtual void Stop() override`
- L97 _private member_ `std::atomic<bool> bRunning;`
- L98 _private member_ `FOnProcess OnProcess;`
- L100 _private member_ `FCriticalSection Mutex;`
- L101 _private member_ `FEventRef Event;`
- L102 _private member_ `TQueue<T> Queue;`
- L103 _private member_ `TUniquePtr<FRunnableThread> Thread;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace CaptureManager` (scope `UE`)
- L21 _delegate_ `DECLARE_DELEGATE_OneParam(FOnProcess, T InElem) TQueueRunner(FOnProcess InOnProcess = nullptr) : bRunning(false) , OnProcess(MoveTemp(InOnProcess)) { Thread.Reset(FRunnableThread::Create(this, TEXT("Queue Runner"), 128 * 1024, TPri_Normal, FPlatformAffinity::GetPoolThreadMask())); } virtual ~TQueueRunner() override { if (Thread) { Thread->Kill(true); } } void Add(T InElement) { { FScopeLock lock(&Mutex); Queue.Enqueue(MoveTemp(InElement)); } Event->Trigger(); } void Empty() { FScopeLock lock(&Mutex); Queue.Empty(); } bool IsRunning() const { return bRunning.load(); } protected:`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureUtils/Public/Async/StopToken.h` (Public)


#### class `UE::CaptureManager::FStopToken`  
`class FStopToken`  
_L14-33_
- L18 _public prototype_ `FStopToken() = default;`
- L19 _public prototype_ `FStopToken(const FStopToken& InOther) = default;`
- L20 _public prototype_ `FStopToken(FStopToken&& InOther) = default;`
- L21 _public prototype_ `FStopToken& operator=(const FStopToken& InOther) = default;`
- L22 _public prototype_ `FStopToken& operator=(FStopToken&& InOther) = default;`
- L24 _public prototype_ `bool IsStopRequested() const;`
- L30 _private prototype_ `FStopToken(TWeakPtr<const FSharedState> InSharedState);`
- L32 _private member_ `TWeakPtr<const FSharedState> SharedStateWeak;`

#### class `UE::CaptureManager::FStopRequester`  
`class FStopRequester`  
_L35-53_
- L38 _public prototype_ `FStopRequester();`
- L40 _public prototype_ `FStopRequester(const FStopRequester& InOther) = default;`
- L41 _public prototype_ `FStopRequester(FStopRequester&& InOther) = default;`
- L42 _public prototype_ `FStopRequester& operator=(const FStopRequester& InOther) = default;`
- L43 _public prototype_ `FStopRequester& operator=(FStopRequester&& InOther) = default;`
- L45 _public prototype_ `void RequestStop();`
- L46 _public prototype_ `bool IsStopRequested() const;`
- L48 _public prototype_ `FStopToken CreateToken() const;`
- L52 _private member_ `TSharedPtr<FSharedState> SharedState;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API CAPTUREUTILS_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace CaptureManager` (scope `UE`)

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureUtils/Public/Async/Task.h` (Public)


#### class `UE::CaptureManager::FCancelableAsyncTask`  
`class FCancelableAsyncTask`  
_L16-37_
- L19 _public typedef_ `using FTaskFunction = TFunction<void(const FStopToken&)>;`
- L21 _public prototype_ `explicit FCancelableAsyncTask(FTaskFunction InTaskFunction);`
- L23 _public prototype_ `~FCancelableAsyncTask();`
- L25 _public prototype_ `bool IsDone();`
- L27 _public prototype_ `void StartSync();`
- L28 _public prototype_ `void StartAsync();`
- L30 _public prototype_ `void Cancel();`
- L35 _private member_ `FStopRequester StopRequester;`
- L36 _private member_ `TUniquePtr<FAsyncTask<FAsyncTaskInternal>> AsyncTask;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API CAPTUREUTILS_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace CaptureManager` (scope `UE`)

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureUtils/Public/Async/TaskProgress.h` (Public)


#### class `UE::CaptureManager::FTaskProgress`  
`class FTaskProgress : public TSharedFromThis<FTaskProgress>`  
_L16-66_
- inherits: `TSharedFromThis<FTaskProgress>`
- L20 _public prototype_ `DECLARE_DELEGATE_OneParam(FProgressReporter, double InProgress);`
- L46 _public prototype_ `FTaskProgress(uint32 InAmountOfWork, FProgressReporter InReport);`
- L47 _public prototype_ `void SetReportThreshold(double InReportThresholdPercent);`
- L49 _public prototype_ `FTask StartTask();`
- L51 _public prototype_ `double GetTotalProgress() const;`
- L55 _private prototype_ `void Update(int32 InTaskToUpdate, double InProgress);`
- L56 _private prototype_ `void Report();`
- L58 _private member_ `FProgressReporter Reporter;`
- L60 _private member_ `std::atomic<int32> CurrentTask;`
- L61 _private member_ `double ReportThreshold = 0.0;`
- L63 _private member_ `std::atomic<double> LastReportedValue = 0.0;`
- L65 _private member_ `mutable TMonitor<TArray<double>> CurrentProgressValues;`

#### class `UE::CaptureManager::FTaskProgress::FTask`  
`class FTask`  
_L22-44_
- L26 _public prototype_ `FTask();`
- L28 _public prototype_ `FTask(const FTask& InTask);`
- L29 _public prototype_ `FTask& operator=(const FTask& InTask);`
- L31 _public prototype_ `FTask(FTask&& InTask);`
- L32 _public prototype_ `FTask& operator=(FTask&& InTask);`
- L34 _public prototype_ `void Update(double InProgress);`
- L38 _private prototype_ `FTask(TWeakPtr<FTaskProgress> InTaskProgress, int32 InId);`
- L40 _private member_ `TWeakPtr<FTaskProgress> TaskProgress;`
- L41 _private member_ `int32 Id;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API CAPTUREUTILS_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace CaptureManager` (scope `UE`)
- L20 _delegate_ `DECLARE_DELEGATE_OneParam(FProgressReporter, double InProgress);`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureUtils/Public/Async/TaskWaiter.h` (Public)


#### class `UE::CaptureManager::FTaskWaiter`  
`class FTaskWaiter`  
_L11-26_
- L15 _public prototype_ `FTaskWaiter();`
- L16 _public prototype_ `~FTaskWaiter();`
- L18 _public prototype_ `bool CreateTask();`
- L19 _public prototype_ `void FinishTask();`
- L20 _public prototype_ `void WaitForAll();`
- L24 _private member_ `std::atomic<uint32> TaskCounter;`
- L25 _private member_ `const uint32 CanCreateTaskFlag = 0x80000000;`

#### Free symbols / members of external scopes

- L6 _macro_ `#define UE_API CAPTUREUTILS_API`
- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace CaptureManager` (scope `UE`)

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureUtils/Public/CaptureManagerTakeId.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace CaptureManager` (scope `UE`)
- L9 _typedef_ `using FTakeId = int32;` (scope `UE::CaptureManager`)

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureUtils/Public/CaptureUtilsModule.h` (Public)


#### class `FCaptureUtilsModule`  
`class FCaptureUtilsModule : public IModuleInterface`  
_L11-23_
- inherits: `IModuleInterface`
- L15 _public prototype_ `virtual void StartupModule() override;`
- L16 _public prototype_ `virtual void ShutdownModule() override;`
- L18 _public prototype_ `TSharedRef<UE::CaptureManager::FCaptureTimerManager> GetTimerManager();`
- L22 _private member_ `TSharedPtr<UE::CaptureManager::FCaptureTimerManager> TimerManager;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CAPTUREUTILS_API`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureUtils/Public/Network/Error.h` (Public)


#### class `UE::CaptureManager::FCaptureProtocolError`  
`class FCaptureProtocolError`  
_L14-34_
- L18 _public prototype_ `FCaptureProtocolError();`
- L19 _public prototype_ `FCaptureProtocolError(FString InMessage, int32 InCode = 0);`
- L21 _public prototype_ `FCaptureProtocolError(const FCaptureProtocolError& InOther) = default;`
- L22 _public prototype_ `FCaptureProtocolError(FCaptureProtocolError&& InOther) = default;`
- L24 _public prototype_ `FCaptureProtocolError& operator=(const FCaptureProtocolError& InOther) = default;`
- L25 _public prototype_ `FCaptureProtocolError& operator=(FCaptureProtocolError&& InOther) = default;`
- L27 _public prototype_ `const FString& GetMessage() const;`
- L28 _public prototype_ `int32 GetCode() const;`
- L32 _private member_ `FString Message;`
- L33 _private member_ `int32 Code = 0;`

#### class `UE::CaptureManager::TProtocolResult`  
`template <typename ValueType> class TProtocolResult : public TValueOrError<ValueType, FCaptureProtocolError>`  
_L37-76_
- inherits: `TValueOrError<ValueType,FCaptureProtocolError>`
- L41 _private typedef_ `using Base = TValueOrError<ValueType, FCaptureProtocolError>;`
- L45 _public function_ `TProtocolResult(ValueType&& InValueType) : Base(MakeValue(MoveTemp(InValueType)))`
- L50 _public function_ `TProtocolResult(const ValueType& InValueType) : Base(MakeValue(InValueType))`
- L55 _public function_ `TProtocolResult(FCaptureProtocolError&& InErrorType) : Base(MakeError(MoveTemp(InErrorType)))`
- L60 _public function_ `TProtocolResult(const FCaptureProtocolError& InErrorType) : Base(MakeError(InErrorType))`
- L66 _public function_ `template <typename... ArgTypes> TProtocolResult(TInPlaceType<ValueType>&&, ArgTypes&&... Args) : Base(MakeValue(Forward<ArgTypes>(Args)...))`
- L72 _public function_ `template <typename... ArgTypes> TProtocolResult(TInPlaceType<FCaptureProtocolError>&&, ArgTypes&&... Args) : Base(MakeError(Forward<ArgTypes>(Args)...))`
- L83 _private typedef_ `using Base = TValueOrError<void, FCaptureProtocolError>;`
- L87 _public function_ `TProtocolResult(TInPlaceType<void>) : Base(MakeValue())`
- L103 _public function_ `template <typename... ArgTypes> TProtocolResult(ArgTypes&&... Args) : Base(MakeError(Forward<ArgTypes>(Args)...))`

#### class `UE::CaptureManager::TProtocolResult`  
`template <> class TProtocolResult<void> : public TValueOrError<void, FCaptureProtocolError>`  
_L79-107_
- inherits: `TValueOrError<void,FCaptureProtocolError>`
- L41 _private typedef_ `using Base = TValueOrError<ValueType, FCaptureProtocolError>;`
- L45 _public function_ `TProtocolResult(ValueType&& InValueType) : Base(MakeValue(MoveTemp(InValueType)))`
- L50 _public function_ `TProtocolResult(const ValueType& InValueType) : Base(MakeValue(InValueType))`
- L55 _public function_ `TProtocolResult(FCaptureProtocolError&& InErrorType) : Base(MakeError(MoveTemp(InErrorType)))`
- L60 _public function_ `TProtocolResult(const FCaptureProtocolError& InErrorType) : Base(MakeError(InErrorType))`
- L66 _public function_ `template <typename... ArgTypes> TProtocolResult(TInPlaceType<ValueType>&&, ArgTypes&&... Args) : Base(MakeValue(Forward<ArgTypes>(Args)...))`
- L72 _public function_ `template <typename... ArgTypes> TProtocolResult(TInPlaceType<FCaptureProtocolError>&&, ArgTypes&&... Args) : Base(MakeError(Forward<ArgTypes>(Args)...))`
- L83 _private typedef_ `using Base = TValueOrError<void, FCaptureProtocolError>;`
- L87 _public function_ `TProtocolResult(TInPlaceType<void>) : Base(MakeValue())`
- L103 _public function_ `template <typename... ArgTypes> TProtocolResult(ArgTypes&&... Args) : Base(MakeError(Forward<ArgTypes>(Args)...))`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CAPTUREUTILS_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace CaptureManager` (scope `UE`)

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureUtils/Public/Network/NetworkMisc.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace CaptureManager` (scope `UE`)
- L11 _prototype_ `TOptional<FString> GetLocalIpAddress();` (scope `UE::CaptureManager`)
- L12 _prototype_ `TOptional<FString> GetLocalHostName();` (scope `UE::CaptureManager`)
- L13 _prototype_ `FString GetLocalHostNameChecked();` (scope `UE::CaptureManager`)

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureUtils/Public/Network/TcpClient.h` (Public)


#### class `UE::CaptureManager::FTcpClient`  
`class FTcpClient final`  
_L30-58_
- L34 _public member_ `static constexpr uint32 BufferSize = 2 * 1024 * 1024;`
- L35 _public member_ `static constexpr int32 DisconnectedError = -10;`
- L36 _public member_ `static constexpr int32 ReadError = -3;`
- L37 _public member_ `static constexpr int32 NoPendingDataError = -2;`
- L38 _public member_ `static constexpr int32 TimeoutError = -1;`
- L40 _public prototype_ `FTcpClient();`
- L41 _public prototype_ `~FTcpClient();`
- L43 _public prototype_ `TProtocolResult<void> Init();`
- L45 _public prototype_ `TProtocolResult<void> Start(const FString& InServerAddress);` — Blocking function until connection is established
- L46 _public prototype_ `TProtocolResult<void> Stop();`
- L48 _public prototype_ `bool IsRunning() const;`
- L50 _public prototype_ `TProtocolResult<void> SendMessage(const TArray<uint8>& InPayload);`
- L51 _public prototype_ `TProtocolResult<TArray<uint8>> ReceiveMessage(const uint64 InSize, const uint32 InWaitTimeoutMs = ITcpSocketReader::DefaultWaitTimeoutMs);`
- L55 _private member_ `FSocketPtr TcpSocket;`
- L57 _private member_ `bool bRunning;`

#### class `UE::CaptureManager::FTcpClientReader`  
`class FTcpClientReader final : public ITcpSocketReader`  
_L60-69_
- inherits: `ITcpSocketReader`
- L63 _public prototype_ `FTcpClientReader(FTcpClient& InClient);`
- L65 _public prototype_ `virtual TProtocolResult<TArray<uint8>> ReceiveMessage(const uint64 InSize, const uint32 InWaitTimeoutMs = DefaultWaitTimeoutMs) override;`
- L68 _private member_ `FTcpClient& Client;`

#### class `UE::CaptureManager::FTcpClientWriter`  
`class FTcpClientWriter final : public ITcpSocketWriter`  
_L71-81_
- inherits: `ITcpSocketWriter`
- L74 _public prototype_ `FTcpClientWriter(FTcpClient& InClient);`
- L76 _public prototype_ `virtual TProtocolResult<void> SendMessage(const TArray<uint8>& InPayload) override;`
- L80 _private member_ `FTcpClient& Client;`

#### Free symbols / members of external scopes

- L23 _macro_ `#define UE_API CAPTUREUTILS_API`
- L25 _namespace_ `namespace UE`
- L25 _namespace_ `namespace CaptureManager` (scope `UE`)
- L28 _typedef_ `using FSocketPtr = TUniquePtr<FSocket, FSocketDeleter>;` (scope `UE::CaptureManager`)

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureUtils/Public/Network/TcpReaderWriter.h` (Public)


#### class `UE::CaptureManager::ITcpSocketReader`  
`class ITcpSocketReader`  
_L12-20_
- L15 _public member_ `static constexpr uint32 DefaultWaitTimeoutMs = 1000;`
- L17 _public prototype_ `virtual ~ITcpSocketReader() = default;`
- L19 _public prototype_ `virtual TProtocolResult<TArray<uint8>> ReceiveMessage(const uint64 InSize, const uint32 InWaitTimeoutMs = DefaultWaitTimeoutMs) = 0;`

#### class `UE::CaptureManager::ITcpSocketWriter`  
`class ITcpSocketWriter`  
_L22-28_
- L25 _public prototype_ `virtual ~ITcpSocketWriter() = default;`
- L27 _public prototype_ `virtual TProtocolResult<void> SendMessage(const TArray<uint8>& InPayload) = 0;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace CaptureManager` (scope `UE`)

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureUtils/Public/Network/TcpServer.h` (Public)


#### class `UE::CaptureManager::FTcpClientHandler`  
`class FTcpClientHandler final`  
_L31-55_
- L35 _public member_ `static constexpr uint32 MaxBufferSize = 500 * 1024;`
- L36 _public member_ `static constexpr int32 DisconnectedError = -10;`
- L37 _public member_ `static constexpr int32 TimeoutError = -1;`
- L39 _public prototype_ `FTcpClientHandler(FSocketPtr InSocket, FString InEndpoint);`
- L40 _public prototype_ `~FTcpClientHandler();`
- L42 _public prototype_ `TProtocolResult<void> SendMessage(const TArray<uint8>& InData);`
- L43 _public prototype_ `TProtocolResult<TArray<uint8>> ReceiveMessage(const uint64 InSize, const uint32 InWaitTimeoutMs = ITcpSocketReader::DefaultWaitTimeoutMs);`
- L45 _public prototype_ `TProtocolResult<uint32> HasPendingData() const;`
- L47 _public prototype_ `const FString& GetEndpoint() const;`
- L49 _public prototype_ `bool operator==(const FTcpClientHandler& InOther);`
- L53 _private member_ `FSocketPtr Socket;`
- L54 _private member_ `FString Endpoint;`

#### class `UE::CaptureManager::FTcpServer`  
`class FTcpServer`  
_L57-92_
- L61 _public member_ `static constexpr uint32 ThreadWaitTime = 500;` — Milliseconds
- L62 _public member_ `static constexpr uint16 AnyPort = 0;` — OS assigned port
- L64 _public prototype_ `DECLARE_DELEGATE_TwoParams(FConnectionHandler, TWeakPtr<FTcpClientHandler> InClient, bool bConnected) FTcpServer(const uint32 InMaxNumberOfClients);`
- L68 _public prototype_ `TProtocolResult<uint16> Start(const uint16 InListenPort = AnyPort);`
- L69 _public prototype_ `TProtocolResult<void> Stop();`
- L71 _public prototype_ `bool IsRunning() const;`
- L73 _public prototype_ `TProtocolResult<void> SendMessage(const TArray<uint8>& InMessage, const FString& InEndpoint);`
- L75 _public prototype_ `void DisconnectClient(const FString& InEndpoint);`
- L76 _public prototype_ `void SetConnectionHandler(FConnectionHandler InOnConnectionHandler);`
- L78 _public prototype_ `int32 GetPort() const;`
- L82 _private member_ `TUniquePtr<FTcpListener> Listener;`
- L83 _private member_ `FSocketPtr Socket;`
- L85 _private member_ `uint32 MaxNumberOfClients;`
- L86 _private member_ `TMap<FString, TSharedPtr<FTcpClientHandler>> Clients;`
- L88 _private member_ `FConnectionHandler OnConnectionHandler;`
- L89 _private member_ `FRWLock Mutex;`
- L91 _private member_ `std::atomic_bool bRunning;`

#### class `UE::CaptureManager::FTcpConnectionReader`  
`class FTcpConnectionReader final : public ITcpSocketReader`  
_L94-103_
- inherits: `ITcpSocketReader`
- L97 _public prototype_ `FTcpConnectionReader(FTcpClientHandler& InClient);`
- L99 _public prototype_ `virtual TProtocolResult<TArray<uint8>> ReceiveMessage(const uint64 InSize, const uint32 InWaitTimeoutMs = DefaultWaitTimeoutMs) override;`
- L102 _private member_ `FTcpClientHandler& Client;`

#### class `UE::CaptureManager::FTcpConnectionWriter`  
`class FTcpConnectionWriter final : public ITcpSocketWriter`  
_L105-115_
- inherits: `ITcpSocketWriter`
- L108 _public prototype_ `FTcpConnectionWriter(FTcpClientHandler& InClient);`
- L110 _public prototype_ `virtual TProtocolResult<void> SendMessage(const TArray<uint8>& InPayload) override;`
- L114 _private member_ `FTcpClientHandler& Client;`

#### Free symbols / members of external scopes

- L24 _macro_ `#define UE_API CAPTUREUTILS_API`
- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace CaptureManager` (scope `UE`)
- L29 _typedef_ `using FSocketPtr = TUniquePtr<FSocket, FSocketDeleter>;` (scope `UE::CaptureManager`)
- L64 _delegate_ `DECLARE_DELEGATE_TwoParams(FConnectionHandler, TWeakPtr<FTcpClientHandler> InClient, bool bConnected) FTcpServer(const uint32 InMaxNumberOfClients);`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureUtils/Public/Network/UdpClient.h` (Public)


#### struct `UE::CaptureManager::FUdpClientConfigure`  
`struct FUdpClientConfigure`  
_L26-30_
- L28 _public member_ `uint16 ListenPort = 0;`
- L29 _public member_ `FString MulticastIpAddress = "";`

#### class `UE::CaptureManager::FUdpClient`  
`class FUdpClient final`  
_L34-57_
- L38 _public prototype_ `FUdpClient();`
- L39 _public prototype_ `~FUdpClient();`
- L41 _public prototype_ `TProtocolResult<void> Init(FUdpClientConfigure InConfig, FOnSocketDataReceived InReceiveHandler);`
- L42 _public prototype_ `TProtocolResult<void> Start();`
- L43 _public prototype_ `TProtocolResult<void> Stop();`
- L45 _public prototype_ `TProtocolResult<int32> SendMessage(const TArray<uint8>& InPayload, const FString& InEndpoint);`
- L49 _private member_ `static constexpr uint32 ThreadWaitTime = 500;` — Milliseconds
- L50 _private member_ `static constexpr uint32 BufferSize = 2 * 1024 * 1024;`
- L52 _private member_ `TUniquePtr<FSocket> UdpSocket;`
- L54 _private member_ `TUniquePtr<FUdpSocketReceiver> UdpReceiver;`
- L56 _private member_ `bool bRunning;`

#### Free symbols / members of external scopes

- L21 _macro_ `#define UE_API CAPTUREUTILS_API`
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace CaptureManager` (scope `UE`)
- L32 _macro_ `#define CHECK_BOOL(Function) if (bool Result = Function; !Result) { return FCaptureProtocolError("Failed to execute function"); }`
