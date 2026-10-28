# Plugins / MetaHumanCaptureUtils

- module root: `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureUtils`
- headers: 9; symbols: 163
- symbol kinds: class=15, delegate=1, enum=2, enumerator=2, function=59, macro=10, member=21, namespace=3, prototype=32, struct=8, typedef=10
- PrivateDependencyModuleNames: 
- PublicDependencyModuleNames: Core, CoreUObject, Engine

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureUtils/Private/MetaHumanCaptureUtilsModule.h` (Private)


#### class `MetaHumanCaptureUtilsModule`  
`class MetaHumanCaptureUtilsModule : public IModuleInterface`  
_L7-9_
- inherits: `IModuleInterface`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureUtils/Public/Async/CallbackSynchronizer.h` (Public)


#### struct `ArgsBundle`  
`template<typename ...> struct ArgsBundle`  
_L14-16_

#### struct `FFunctionTraits`  
`template<typename T> struct FFunctionTraits : public FFunctionTraits<decltype(&T::operator())>`  
_L19-21_
- inherits: `FFunctionTraits<decltype(&T::operator())>`
- L26 _public typedef_ `using ReturnType = Return;`
- L27 _public typedef_ `using FnArgs = ArgsBundle<Args ...>;`
- L28 _public typedef_ `using FnType = Return(Args ...);`

#### struct `FFunctionTraits`  
`template<typename Return, typename Object, typename ... Args> struct FFunctionTraits<Return(Object::*)(Args ...)>`  
_L24-29_
- L26 _public typedef_ `using ReturnType = Return;`
- L27 _public typedef_ `using FnArgs = ArgsBundle<Args ...>;`
- L28 _public typedef_ `using FnType = Return(Args ...);`

#### struct `FFunctionTraits`  
`template<typename Return, typename Object, typename ... Args> struct FFunctionTraits<Return(Object::*)(Args ...) const>`  
_L32-37_
- L26 _public typedef_ `using ReturnType = Return;`
- L27 _public typedef_ `using FnArgs = ArgsBundle<Args ...>;`
- L28 _public typedef_ `using FnType = Return(Args ...);`

#### struct `FFunctionTraits`  
`template<typename Return, typename ... Args> struct FFunctionTraits<Return(*)(Args ...)>`  
_L40-45_
- L26 _public typedef_ `using ReturnType = Return;`
- L27 _public typedef_ `using FnArgs = ArgsBundle<Args ...>;`
- L28 _public typedef_ `using FnType = Return(Args ...);`

#### class `FCallbackSynchronizer`  
`FCallbackSynchronizer : public TSharedFromThis<FCallbackSynchronizer>`  
_L48-95_
- reflection: `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureUtils is deprecated. This functionality is now available in the CaptureManagerCore/CaptureUtils module")`
- inherits: `TSharedFromThis<FCallbackSynchronizer>`
- L51 _public prototype_ `DECLARE_DELEGATE(FAfterAllDelegate);`
- L53 _public prototype_ `FCallbackSynchronizer();`
- L54 _public prototype_ `~FCallbackSynchronizer();`
- L57 _public function_ `template<typename FCallback> auto CreateCallback(FCallback&& InCallback)`
- L63 _public prototype_ `void AfterAll(FAfterAllDelegate InAfterAllDelegate, bool bExecuteIfCounterZero = true);`
- L65 _public prototype_ `static TSharedPtr<FCallbackSynchronizer> Create();`
- L90 _private prototype_ `void Decrease();`
- L92 _private member_ `FAfterAllDelegate AfterAllDelegate;`
- L94 _private member_ `std::atomic_int Counter;`

#### struct `FCallbackSynchronizer::FMakeCallbackInternal`  
`template<typename ... Args> struct FMakeCallbackInternal<ArgsBundle<Args ...> >`  
_L73-88_
- L76 _public function_ `template<typename LT> static auto Get(TSharedPtr<FCallbackSynchronizer> InCallbackSynchronizer, LT&& InUserFn)`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API METAHUMANCAPTUREUTILS_API`
- L51 _delegate_ `DECLARE_DELEGATE(FAfterAllDelegate);`
- L59 _typedef_ `using FIdentityFnArgs = typename FFunctionTraits<FCallback>::FnArgs;` (scope `FCallbackSynchronizer::CreateCallback`)
- L82 _function_ `` (scope `FCallbackSynchronizer::FMakeCallbackInternal::Get`)

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureUtils/Public/Async/Event.h` (Public)


#### class `FCaptureEvent`  
`FCaptureEvent`  
_L23-35_
- reflection: `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureUtils is deprecated. This functionality is now available in the CaptureManagerCore/CaptureUtils module")`
- desc: Base class for all event sublasses
- L26 _public prototype_ `const FString& GetName() const;`
- L27 _public prototype_ `virtual ~FCaptureEvent();`
- L30 _protected prototype_ `FCaptureEvent(FString InName);`
- L34 _private member_ `FString Name;`

#### class `ICaptureEventSource`  
`class ICaptureEventSource`  
_L54-60_
- desc: Interface for classes that wish to provide capture event subscription to their clients
- L57 _public prototype_ `virtual TArray<FString> GetAvailableEvents() const = 0;`
- L58 _public prototype_ `virtual void SubscribeToEvent(const FString& InEventName, FCaptureEventHandler InHandler) = 0;`
- L59 _public prototype_ `virtual void UnsubscribeAll() = 0;`

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API METAHUMANCAPTUREUTILS_API`
- L38 _macro_ `#define METAHUMAN_CAPTURE_DEFINE_EMPTY_EVENT(ClassName, EventName) \` — Macro for easy definition of events that don't carry any data
- L50 _typedef_ `using FCaptureEventHandler = TManagedDelegate<TSharedPtr<const FCaptureEvent>>;` — The SharedPtr points to a `const` event object because the shared event might end up on multiple threads in which case we'd have a thread safety issue without the event being `const`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureUtils/Public/Async/EventSourceUtils.h` (Public)


#### class `detail::FCaptureEventSourceBase`  
`FCaptureEventSourceBase : public ICaptureEventSource`  
_L14-35_
- reflection: `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureUtils is deprecated. This functionality is now available in the CaptureManagerCore/CaptureUtils module")`
- inherits: `ICaptureEventSource`
- L17 _public prototype_ `virtual ~FCaptureEventSourceBase();`
- L20 _public prototype_ `virtual TArray<FString> GetAvailableEvents() const override;`
- L22 _public prototype_ `virtual void SubscribeToEvent(const FString& InEventName, FCaptureEventHandler InHandler) override;` — NOTE: SubscribeToEvent() must not be called from an event handler that is being executed on the same thread
- L23 _public prototype_ `virtual void UnsubscribeAll() override;`
- L26 _protected prototype_ `void RegisterEvent(const FString& InEventName);`
- L27 _protected prototype_ `void PublishEventInternal(TSharedPtr<const FCaptureEvent> InEvent) const;`
- L30 _private typedef_ `using FHandlers = TMulticastDelegate<void(TSharedPtr<const FCaptureEvent>)>;`
- L32 _private member_ `mutable FRWLock HandlersLock;`
- L33 _private member_ `TMap<FString, FHandlers> EventToHandlersMap;`

#### class `FCaptureEventSource`  
`class FCaptureEventSource : public detail::FCaptureEventSourceBase`  
_L39-55_
- inherits: `detail::FCaptureEventSourceBase`
- desc: Class to be publicly inherited to get basic event source functionality. All functions are thread-safe.
- L43 _protected function_ `template<typename EventType, typename ... Args> void PublishEvent(Args&&... InArgs) const`
- L48 _protected function_ `void PublishEventPtr(TSharedPtr<const FCaptureEvent> InEvent) const`

#### class `FCaptureEventSourceWithLimiter`  
`class FCaptureEventSourceWithLimiter : public detail::FCaptureEventSourceBase`  
_L58-114_
- inherits: `detail::FCaptureEventSourceBase`
- desc: Class to be publicly inherited to get event source functionality where rate of events published is limited. All functions are thread-safe.
- L61 _public function_ `FCaptureEventSourceWithLimiter(int32 InThresholdMillis) : ThresholdMillis(InThresholdMillis), LastPublish(0)`
- L74 _protected function_ `template<typename EventType, typename ... EventArgs> bool PublishIfThresholdReached(bool bInForcePublish, EventArgs&& ... InEventArgs)` — When PublishIfThresholdReached() is called the publishing will mostly only occur if the time since last publish is greater than the threshold (although this isn't guaranteed and multiple events can still be published in rare cases). The unpublished events are simply dropped (i.e. not buffered so the client has to make sure that won't cause problems to the subscribers. The client can also force publish an event which will do the publishing no matter what the current time is and reset the time measurement. This is handy for publishing events whose dropping will break continuity for the client or for publishing the last event in a line of optional events to trigger the final update.
- L92 _protected function_ `void PublishEventIgnoreThresholdPtr(TSharedPtr<const FCaptureEvent> InEvent)` — Always publishes the event while completely ignoring the threshold mechanism. If you want to force publishing of an event AND update the "last publish" timestamp, please use PublishIfThresholdReached(true, ...)
- L98 _protected function_ `template<typename EventType, typename ... EventArgs> void PublishEventIgnoreThreshold(EventArgs&&... InEventArgs)`
- L106 _private function_ `bool IsThresholdPassed(const FDateTime& InLastPublish, const FDateTime& InNow) const`
- L112 _private member_ `const int32 ThresholdMillis;`
- L113 _private member_ `std::atomic<int64> LastPublish;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API METAHUMANCAPTUREUTILS_API`
- L11 _namespace_ `namespace detail`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureUtils/Public/Async/ManagedDelegate.h` (Public)


#### enum `EDelegateExecutionThread`  
`enum class EDelegateExecutionThread`  
_L8-12_
- L10 _public enumerator_ `GameThread = 0`
- L11 _public enumerator_ `InternalThread` — Thread on which the function invoking the delegate is being run on

#### class `TManagedDelegate`  
`template<typename ... Args> class TManagedDelegate`  
_L39-78_
- L42 _public typedef_ `using Type = TDelegate<void(Args...)>;`
- L44 _public prototype_ `TManagedDelegate() = default;`
- L47 _public function_ `template<typename Func> TManagedDelegate(Func InFunc, EDelegateExecutionThread InThread = EDelegateExecutionThread::GameThread) : TManagedDelegate(Type::CreateLambda(InFunc), InThread)`
- L52 _public function_ `TManagedDelegate(Type InDelegate, EDelegateExecutionThread InThread = EDelegateExecutionThread::GameThread) : Delegate(MoveTemp(InDelegate)) , ExecutionThread(InThread)`
- L58 _public function_ `void operator()(Args... InArgs)`
- L66 _public function_ `void operator()(Args... InArgs) const`
- L76 _private member_ `Type Delegate;`
- L77 _private member_ `EDelegateExecutionThread ExecutionThread;`

#### class `TManagedMulticastDelegate`  
`template<typename ... Args> class TManagedMulticastDelegate`  
_L81-117_
- L84 _public typedef_ `using DelegateType = TDelegate<void(Args...)>;`
- L86 _public prototype_ `TManagedMulticastDelegate() = default;`
- L89 _public function_ `template<typename Func> void Add(Func InFunc, EDelegateExecutionThread InThread = EDelegateExecutionThread::GameThread)`
- L94 _public function_ `void Add(DelegateType InDelegate, EDelegateExecutionThread InThread = EDelegateExecutionThread::GameThread)`
- L102 _public function_ `void operator()(Args... InArgs)`
- L107 _public function_ `void operator()(Args... InArgs) const`
- L114 _private typedef_ `using Type = TMulticastDelegate<void(Args...)>;`
- L116 _private member_ `Type Delegate;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace details`
- L17 _function_ `template<typename ... Args> static void ExecuteDelegate(TDelegate<void(Args...)> InDelegate, EDelegateExecutionThread InThread, Args&&... InArgs)` (scope `details`)
- L22 _function_ `` (scope `details::ExecuteDelegate`)
- L97 _function_ `` (scope `TManagedMulticastDelegate::Add`)

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureUtils/Public/Async/StopToken.h` (Public)


#### class `FStopToken`  
`class FStopToken`  
_L9-29_
- L16 _public prototype_ `FStopToken();` — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureUtils is deprecated. This functionality is now available in the CaptureManagerCore/CaptureUtils module")` — We can't deprecate the type itself without encountering seemingly impossible to suppress warnings inside TTuple (due to its usage in various maps, which can't be easily removed or replaced), so we deprecate the constructor to at least provide some degree of warning
- L18 _public prototype_ `void RequestStop();`
- L19 _public prototype_ `bool IsStopRequested() const;`
- L28 _private member_ `TSharedPtr<FSharedState> SharedState;`

#### struct `FStopToken::FSharedState`  
`struct FSharedState`  
_L23-26_
- L25 _public member_ `std::atomic_bool State = false;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API METAHUMANCAPTUREUTILS_API`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureUtils/Public/Async/Task.h` (Public)


#### class `FAbortableAsyncTask`  
`class FAbortableAsyncTask`  
_L11-81_
- L14 _public typedef_ `using FTaskFunction = TFunction<void(const FStopToken&)>;`
- L17 _public function_ `FAbortableAsyncTask(FTaskFunction InTaskFunction) : AsyncTask(MakeUnique<FAsyncTask<FAsyncTaskInternal>>(StopToken, MoveTemp(InTaskFunction)))`
- L23 _public function_ `~FAbortableAsyncTask()`
- L29 _public prototype_ `FAbortableAsyncTask(const FAbortableAsyncTask&) = delete;`
- L30 _public prototype_ `FAbortableAsyncTask& operator=(const FAbortableAsyncTask&) = delete;`
- L31 _public prototype_ `FAbortableAsyncTask(FAbortableAsyncTask&&) = delete;`
- L32 _public prototype_ `FAbortableAsyncTask& operator=(FAbortableAsyncTask&&) = delete;`
- L34 _public function_ `bool IsDone()`
- L39 _public function_ `void StartSync()`
- L44 _public function_ `void StartAsync()`
- L49 _public function_ `void Abort()`
- L79 _private member_ `FStopToken StopToken;`
- L80 _private member_ `TUniquePtr<FAsyncTask<FAsyncTaskInternal>> AsyncTask;`

#### class `FAbortableAsyncTask::FAsyncTaskInternal`  
`class FAsyncTaskInternal : public FNonAbandonableTask`  
_L55-77_
- inherits: `FNonAbandonableTask`
- L58 _public function_ `FAsyncTaskInternal(const FStopToken& InStopToken, FTaskFunction&& InTaskFunction) : StopToken(InStopToken), TaskFunction(MoveTemp(InTaskFunction))`
- L64 _public function_ `void DoWork()`
- L69 _public function_ `inline TStatId GetStatId() const`
- L75 _private member_ `const FStopToken& StopToken;`
- L76 _private member_ `FTaskFunction TaskFunction;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureUtils/Public/Error/Result.h` (Public)


#### class `TResult`  
`template<class ResultType, class ErrorType> class TResult`  
_L8-118_
- L12 _public function_ `TResult(const ResultType& InReturnValue) : Result(TInPlaceType<ResultType>(), InReturnValue)`
- L17 _public function_ `TResult(ResultType&& InReturnValue) : Result(TInPlaceType<ResultType>(), MoveTemp(InReturnValue))`
- L22 _public function_ `TResult(const ErrorType& InError) : Result(TInPlaceType<ErrorType>(), InError)`
- L27 _public function_ `TResult(ErrorType&& InError) : Result(TInPlaceType<ErrorType>(), MoveTemp(InError))`
- L32 _public function_ `TResult(const TResult& InOther) : Result(InOther.Result)`
- L37 _public function_ `TResult(TResult&& InOther) : Result(MoveTemp(InOther.Result))`
- L42 _public function_ `TResult& operator=(const TResult& InOther)`
- L52 _public function_ `TResult& operator=(TResult&& InOther)`
- L62 _public prototype_ `~TResult() = default;`
- L64 _public function_ `bool IsValid() const`
- L69 _public function_ `bool IsError() const`
- L74 _public function_ `const ResultType& GetResult() const`
- L80 _public function_ `ResultType& GetResult()`
- L86 _public function_ `ResultType ClaimResult()`
- L92 _public function_ `const ErrorType& GetError() const`
- L98 _public function_ `ErrorType& GetError()`
- L104 _public function_ `ErrorType ClaimError()`
- L110 _public function_ `explicit operator bool()`
- L117 _private member_ `TVariant<ResultType, ErrorType> Result;`
- L131 _public function_ `TResult(FVoidResultTag) : bIsResultValid(true)`
- L136 _public function_ `TResult(const ErrorType& InError) : Error(InError) , bIsResultValid(false)`
- L142 _public function_ `TResult(ErrorType&& InError) : Error(MoveTemp(InError)) , bIsResultValid(false)`
- L148 _public function_ `TResult(const TResult& InOther) : Error(InOther.Error), bIsResultValid(InOther.bIsResultValid)`
- L154 _public function_ `TResult(TResult&& InOther) : Error(MoveTemp(InOther.Error)), bIsResultValid(InOther.bIsResultValid)`
- L184 _public function_ `~TResult()` — We can not use =default here without triggering deprecation warnings on user supplied types. Ideally we would want those warnings to fire but there appears to be no way to suppress them for internal usage with our deprecated types.
- L223 _private member_ `ErrorType Error;`
- L224 _private member_ `bool bIsResultValid;`

#### struct `FVoidResultTag`  
`struct FVoidResultTag`  
_L120-122_

#### class `TResult`  
`template<class ErrorType> class TResult<void, ErrorType>`  
_L127-225_
- L12 _public function_ `TResult(const ResultType& InReturnValue) : Result(TInPlaceType<ResultType>(), InReturnValue)`
- L17 _public function_ `TResult(ResultType&& InReturnValue) : Result(TInPlaceType<ResultType>(), MoveTemp(InReturnValue))`
- L22 _public function_ `TResult(const ErrorType& InError) : Result(TInPlaceType<ErrorType>(), InError)`
- L27 _public function_ `TResult(ErrorType&& InError) : Result(TInPlaceType<ErrorType>(), MoveTemp(InError))`
- L32 _public function_ `TResult(const TResult& InOther) : Result(InOther.Result)`
- L37 _public function_ `TResult(TResult&& InOther) : Result(MoveTemp(InOther.Result))`
- L42 _public function_ `TResult& operator=(const TResult& InOther)`
- L52 _public function_ `TResult& operator=(TResult&& InOther)`
- L62 _public prototype_ `~TResult() = default;`
- L64 _public function_ `bool IsValid() const`
- L69 _public function_ `bool IsError() const`
- L74 _public function_ `const ResultType& GetResult() const`
- L80 _public function_ `ResultType& GetResult()`
- L86 _public function_ `ResultType ClaimResult()`
- L92 _public function_ `const ErrorType& GetError() const`
- L98 _public function_ `ErrorType& GetError()`
- L104 _public function_ `ErrorType ClaimError()`
- L110 _public function_ `explicit operator bool()`
- L117 _private member_ `TVariant<ResultType, ErrorType> Result;`
- L131 _public function_ `TResult(FVoidResultTag) : bIsResultValid(true)`
- L136 _public function_ `TResult(const ErrorType& InError) : Error(InError) , bIsResultValid(false)`
- L142 _public function_ `TResult(ErrorType&& InError) : Error(MoveTemp(InError)) , bIsResultValid(false)`
- L148 _public function_ `TResult(const TResult& InOther) : Error(InOther.Error), bIsResultValid(InOther.bIsResultValid)`
- L154 _public function_ `TResult(TResult&& InOther) : Error(MoveTemp(InOther.Error)), bIsResultValid(InOther.bIsResultValid)`
- L184 _public function_ `~TResult()` — We can not use =default here without triggering deprecation warnings on user supplied types. Ideally we would want those warnings to fire but there appears to be no way to suppress them for internal usage with our deprecated types.
- L223 _private member_ `ErrorType Error;`
- L224 _private member_ `bool bIsResultValid;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureUtils/Public/Error/ScopeGuard.h` (Public)


#### class `TScopeGuard`  
`template<typename FuncType> class TScopeGuard final`  
_L6-33_
- L8 _private member_ `FuncType Func;`
- L9 _private member_ `bool bIsActive;`
- L12 _public function_ `TScopeGuard(FuncType InFunc) : Func(MoveTemp(InFunc)), bIsActive(true)`
- L15 _public function_ `~TScopeGuard()`
- L21 _public prototype_ `TScopeGuard() = delete;`
- L22 _public prototype_ `TScopeGuard(const TScopeGuard&) = delete;`
- L23 _public function_ `TScopeGuard(TScopeGuard&& other) : Func(MoveTemp(other.Func)), bIsActive(other.bIsActive)`
- L27 _public prototype_ `TScopeGuard& operator=(const TScopeGuard&) = delete;`
- L28 _public prototype_ `TScopeGuard& operator=(TScopeGuard&&) = delete;`
- L30 _public function_ `void Dismiss() noexcept`

#### enum `detail::FScopeGuardOnExit`  
`enum class FScopeGuardOnExit`  
_L42-42_

#### Free symbols / members of external scopes

- L37 _function_ `template<typename FuncType> TScopeGuard<FuncType> MakeScopeGuard(FuncType InFunc)`
- L41 _namespace_ `namespace detail`
- L44 _function_ `template<typename Fun> TScopeGuard<Fun> operator+(FScopeGuardOnExit, Fun&& InFn)` (scope `detail`)
- L51 _macro_ `#define SCOPE_EXIT \` — Helper macro
- L54 _macro_ `#define SCOPE_GUARD_CONCATENATE_IMPL(s1, s2) s1 ## s2`
- L55 _macro_ `#define SCOPE_GUARD_CONCATENATE(s1, s2) SCOPE_GUARD_CONCATENATE_IMPL(s1, s2)`
- L58 _macro_ `#define SCOPE_GUARD_ANONYMOUS_VARIABLE(str) SCOPE_GUARD_CONCATENATE(str, __COUNTER__)`
- L60 _macro_ `#define SCOPE_GUARD_ANONYMOUS_VARIABLE(str) SCOPE_GUARD_CONCATENATE(str, __LINE__)`
