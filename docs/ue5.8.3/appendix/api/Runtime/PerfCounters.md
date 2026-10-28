# Runtime / PerfCounters

- module root: `Source/Runtime/PerfCounters`
- headers: 3; symbols: 115
- symbol kinds: class=4, delegate=3, enum=2, enumerator=5, function=20, member=27, prototype=50, struct=2, typedef=2
- PrivateDependencyModuleNames: Core, HTTPServer, Json

### `Source/Runtime/PerfCounters/Private/PerfCounters.h` (Private)


#### class `FPerfCounters`  
`class FPerfCounters : public FTSTickerObjectBase , public FSelfRegisteringExec , public IPerfCounters , public TSharedFromThis<FPerfCounters>`  
_L22-118_
- inherits: `FTSTickerObjectBase,FSelfRegisteringExec,IPerfCounters,TSharedFromThis<FPerfCounters>`
- L30 _public prototype_ `FPerfCounters(const FString& InUniqueInstanceId);`
- L31 _public prototype_ `virtual ~FPerfCounters();`
- L34 _public prototype_ `bool Initialize();` — Initializes this instance from JSON config.
- L37 _public prototype_ `virtual bool Tick(float DeltaTime) override;` — FTSTickerObjectBase
- L40 _public function_ `const FString& GetInstanceName() const override`
- L41 _public prototype_ `virtual double GetNumber(const FString& Name, double DefaultValue = 0.0) override;`
- L42 _public prototype_ `virtual void SetNumber(const FString& Name, double Value, uint32 Flags) override;`
- L43 _public prototype_ `virtual void SetString(const FString& Name, const FString& Value, uint32 Flags) override;`
- L44 _public prototype_ `virtual void SetJson(const FString& Name, const FProduceJsonCounterValue& InCallback, uint32 Flags) override;`
- L45 _public function_ `virtual FPerfCounterExecCommandCallback& OnPerfCounterExecCommand() override`
- L46 _public function_ `virtual const TMap<FString, FJsonVariant>& GetAllCounters() override`
- L47 _public prototype_ `virtual FString GetAllCountersAsJson() override;`
- L48 _public prototype_ `virtual void ResetStatsForNextPeriod() override;`
- L49 _public function_ `virtual TPerformanceHistogramMap& PerformanceHistograms() override`
- L51 _public prototype_ `virtual bool StartMachineLoadTracking() override;` — Legacy load tracking, which is raw frame time, not overshoot.
- L53 _public prototype_ `virtual bool StartMachineLoadTracking(double TickRate, const TArray<double>& FrameTimeHistogramBucketsMs) override;` — If OvershootBuckets is empty, will use legacy load tracking values, which is raw frame time, not overshoot.
- L54 _public prototype_ `virtual bool StopMachineLoadTracking();`
- L55 _public prototype_ `virtual bool ReportUnplayableCondition(const FString& ConditionDescription);`
- L60 _protected prototype_ `virtual bool Exec_Runtime(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar);`
- L65 _private prototype_ `void TickZeroLoad(float DeltaTime);`
- L66 _private prototype_ `void TickSystemCounters(float DeltaTime);`
- L75 _private prototype_ `bool ProcessStatsRequest(const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete);` — Processes a /stats request @param Request The incoming request @param OnComplete The invokable response result callback @return true if this request was handled herein, false otherwise
- L84 _private prototype_ `bool ProcessExecRequest(const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete);` — Process an /exec request @param Request The incoming request @param OnComplete The invokable response result callback @return true if this request was handled herein, false otherwise
- L87 _private member_ `FString UniqueInstanceId;` — Unique name of this instance
- L90 _private member_ `float InternalCountersUpdateInterval;` — Interval (in seconds) to update internal counters, added by the module itself, a config value
- L93 _private member_ `float LastTimeInternalCountersUpdated;` — Last time internal counters were updated
- L96 _private member_ `TMap<FString, FJsonVariant> PerfCounterMap;` — Map of all known performance counters
- L99 _private member_ `FPerfCounterExecCommandCallback ExecCmdCallback;` — Bound callback for script command execution
- L102 _private member_ `TPerformanceHistogramMap PerformanceHistogramMap;` — Map of performance histograms.
- L105 _private member_ `FZeroLoad* ZeroLoadThread;` — Data of zero-load thread (used for measuring machine load).
- L108 _private member_ `FRunnableThread* ZeroLoadRunnable;` — Zero-load thread runnable
- L111 _private member_ `TSharedPtr<IHttpRouter> HttpRouter = nullptr;` — Http request/response interface
- L114 _private member_ `FHttpRouteHandle StatsRouteHandle = nullptr;` — Route handle for /stats binding
- L117 _private member_ `FHttpRouteHandle ExecRouteHandle = nullptr;` — Route handle for /exec binding

#### Free symbols / members of external scopes

- L20 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogPerfCounters, Log, All);`
- L20 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPerfCounters, Log, All);`

### `Source/Runtime/PerfCounters/Private/ZeroLoad.h` (Private)


#### class `FZeroLoad`  
`class FZeroLoad : public FRunnable`  
_L10-48_
- inherits: `FRunnable`
- L13 _private member_ `FThreadSafeCounter ExitRequest;` — signal request to stop and exit thread
- L16 _private member_ `double TickRate;` — Tick frequency, HZ
- L19 _private member_ `FHistogram TickTimeHistogram;` — Histogram of thread loop times, not accessed outside of the thread
- L22 _private member_ `FCriticalSection HitchMessagesLock;` — Guards access to hitch messages
- L25 _private member_ `TArray<FString> HitchMessagesToBeLogged;` — Hitches that have not yet been logged
- L28 _private prototype_ `void AddHitchMessage(double HitchDurationInMs);` — Adds a message to log. We avoid calling UE_LOG directly since this can add locks at unpredictable times.
- L33 _public prototype_ `virtual bool Init() override;` — FRunnable interface
- L34 _public prototype_ `virtual uint32 Run() override;`
- L35 _public prototype_ `virtual void Stop() override;`
- L36 _public prototype_ `virtual void Exit() override;`
- L40 _public prototype_ `bool GetHitchMessages(TArray<FString>& OutArray);` — Gets messages to log - can block.
- L43 _public prototype_ `bool GetFrameTimeHistogram(FHistogram& OutHistogram);` — Gets frame time histogram - not guarded, should only be accessed after thread has stopped!
- L45 _public prototype_ `FZeroLoad(double InTickRate);`
- L46 _public prototype_ `FZeroLoad(double InTickRate, const TArray<double>& FrameTimeHistogramBucketsMs);`
- L47 _public prototype_ `virtual ~FZeroLoad() = default;`

### `Source/Runtime/PerfCounters/Public/PerfCountersModule.h` (Public)


#### class `IPerfCounters`  
`class IPerfCounters`  
_L47-214_
- desc: A programming interface for setting/updating performance counters
- L87 _public typedef_ `typedef TMap<FName, FHistogram> TPerformanceHistogramMap;` — Array used to store performance histograms.
- L90 _public prototype_ `virtual ~IPerfCounters() = default;`
- L93 _public prototype_ `virtual const FString& GetInstanceName() const = 0;` — Get the unique identifier for this perf counter instance
- L96 _public prototype_ `virtual double GetNumber(const FString& Name, double DefaultValue = 0.0) = 0;` — Returns currently held value, or DefaultValue if none
- L99 _public prototype_ `virtual void SetNumber(const FString& Name, double Value, uint32 Flags = 0) = 0;` — Maps value to a numeric holder
- L102 _public prototype_ `virtual void SetString(const FString& Name, const FString& Value, uint32 Flags = 0) = 0;` — Maps value to a string holder
- L105 _public prototype_ `virtual void SetJson(const FString& Name, const FProduceJsonCounterValue& Callback, uint32 Flags = 0) = 0;` — Make a callback so we can request more extensive types on demand (presumably backed by some struct locally)
- L108 _public prototype_ `virtual FPerfCounterExecCommandCallback& OnPerfCounterExecCommand() = 0;` — @return delegate called when an exec command is to be executed
- L111 _public prototype_ `virtual const TMap<FString, FJsonVariant>& GetAllCounters() = 0;` — @return all perf counters as they are stored, with minimum conversion
- L114 _public prototype_ `virtual FString GetAllCountersAsJson() = 0;` — @return all perf counters as JSON
- L117 _public prototype_ `virtual void ResetStatsForNextPeriod() = 0;` — Clears transient perf counters, essentially marking beginning of a new stats period
- L120 _public prototype_ `virtual TPerformanceHistogramMap& PerformanceHistograms() = 0;` — Returns performance histograms for direct manipulation by the client code.
- L123 _public prototype_ `virtual bool StartMachineLoadTracking() = 0;` — Starts tracking overall machine load.
- L126 _public prototype_ `virtual bool StartMachineLoadTracking(double TickRate, const TArray<double>& FrameTimeHistogramBucketsMs) = 0;` — Starts tracking overall machine load (empty array will use default hitch buckets).
- L129 _public prototype_ `virtual bool StopMachineLoadTracking() = 0;` — Stops tracking overall machine load.
- L132 _public prototype_ `virtual bool ReportUnplayableCondition(const FString& ConditionDescription) = 0;` — Reports an unplayable condition.
- L137 _public function_ `int32 Get(const FString& Name, int32 Val = 0)` — Get overloads
- L142 _public function_ `uint32 Get(const FString& Name, uint32 Val = 0)`
- L147 _public function_ `float Get(const FString& Name, float Val = 0.0f)`
- L152 _public function_ `double Get(const FString& Name, double Val = 0.0)`
- L166 _public function_ `int32 Increment(const FString & Name, int32 Add = 1, int32 DefaultValue = 0, uint32 Flags = IPerfCounters::Flags::Transient)` — @brief Convenience method for incrementing a transient counter @param Name the name of the counter @param Add value of the increment (will be added to the counter, can be negative) @param DefaultValue if the counter did not exist or was cleared, this is what it will be initialized to before performing the addition @param Flags flags for the counter @return current value (i.e. after the increment)
- L175 _public function_ `void Set(const FString& Name, int32 Val, uint32 Flags = 0)`
- L180 _public function_ `void Set(const FString& Name, uint32 Val, uint32 Flags = 0)`
- L185 _public function_ `void Set(const FString& Name, float Val, uint32 Flags = 0)`
- L190 _public function_ `void Set(const FString& Name, double Val, uint32 Flags = 0)`
- L195 _public function_ `void Set(const FString& Name, int64 Val, uint32 Flags = 0)`
- L200 _public function_ `void Set(const FString& Name, uint64 Val, uint32 Flags = 0)`
- L205 _public function_ `void Set(const FString& Name, const FString& Val, uint32 Flags = 0)`
- L210 _public function_ `void Set(const FString& Name, const FProduceJsonCounterValue& Callback, uint32 Flags = 0)`

#### enum `IPerfCounters::Flags`  
`enum Flags : uint32`  
_L51-55_
- L54 _public enumerator_ `Transient = (1 << 0)` — Perf counter with this flag will be removed by "perfcounters clear" command

#### struct `IPerfCounters::FJsonVariant`  
`struct FJsonVariant`  
_L57-66_
- L59 _public member_ `enum { Null, String, Number, Callback } Format;`
- L60 _public member_ `FString StringValue;`
- L61 _public member_ `double NumberValue;`
- L62 _public member_ `FProduceJsonCounterValue CallbackValue;`
- L63 _public member_ `uint32 Flags;`
- L65 _public function_ `FJsonVariant() : Format(Null), NumberValue(0)`

#### enum `IPerfCounters::FJsonVariant::(anonymous)`  
`enum`  
_L59-59_

#### struct `IPerfCounters::Histograms`  
`struct Histograms`  
_L69-84_
- desc: Named engine-wide histograms
- L72 _public member_ `static const FName FrameTime;` — Frame time histogram for the duration of the match.
- L74 _public member_ `static const FName FrameTimePeriodic;` — Frame time histogram for shorter intervals.
- L76 _public member_ `static const FName FrameTimeWithoutSleep;` — Frame time histogram (without sleep) for the duration of the match.
- L78 _public member_ `static const FName ServerReplicateActorsTime;` — ServerReplicateActors time histogram for the duration of the match.
- L80 _public member_ `static const FName SleepTime;` — Sleep time histogram for the duration of the match.
- L83 _public member_ `static const FName ZeroLoadFrameTime;` — Zero load thread frame time histogram.

#### class `IPerfCountersModule`  
`class IPerfCountersModule : public IModuleInterface`  
_L220-261_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L230 _public function_ `static inline IPerfCountersModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L240 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L246 _public prototype_ `static int32 GetHTTPStatsPort();` — Returns the HTTP port to bind for the stats request. Returns -1 if none were specified
- L251 _public prototype_ `virtual IPerfCounters* GetPerformanceCounters() const = 0;` — @return the currently initialized / in use perf counters
- L260 _public prototype_ `virtual IPerfCounters* CreatePerformanceCounters(const FString& UniqueInstanceId = TEXT("")) = 0;` — Creates and initializes the performance counters object @param UniqueInstanceId		optional parameter that allows to assign a known name for this set of counters (a default one that will include process id will be provided if not given) @return IPerfCounters object (should be explicitly deleted later), or nullptr if failed

#### Free symbols / members of external scopes

- L24 _typedef_ `typedef TSharedRef< TJsonWriter<TCHAR,TPrettyJsonPrintPolicy<TCHAR> > > FPrettyJsonWriter;`
- L32 _delegate_ `DECLARE_DELEGATE_OneParam(FProduceJsonCounterValue, const FPrettyJsonWriter& );` — Delegate called for a given counter to generate custom json at the time the query is made @param JsonWriter json output writer
- L32 _prototype_ `DECLARE_DELEGATE_OneParam(FProduceJsonCounterValue, const FPrettyJsonWriter& );` — Delegate called for a given counter to generate custom json at the time the query is made @param JsonWriter json output writer
- L42 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FPerfCounterExecCommandCallback, const FString& , FOutputDevice& );` — Delegate called when an exec command has been passed in on via the query port @param ExecCmd string command to execute @param Output output device to write the response back to the querying service @return true if the call was handled, false otherwise
- L42 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FPerfCounterExecCommandCallback, const FString& , FOutputDevice& );` — Delegate called when an exec command has been passed in on via the query port @param ExecCmd string command to execute @param Output output device to write the response back to the querying service @return true if the call was handled, false otherwise
- L59 _enumerator_ `enum { Null, String, Number, Callback } Format; FString StringValue; double NumberValue; FProduceJsonCounterValue CallbackValue; uint32 Flags; FJsonVariant() : Format(Null)` (scope `IPerfCounters::FJsonVariant::__anonc73d03e20103`)
- L59 _enumerator_ `enum { Null, String, Number, Callback } Format; FString StringValue; double NumberValue; FProduceJsonCounterValue CallbackValue; uint32 Flags; FJsonVariant() : Format(Null)` (scope `IPerfCounters::FJsonVariant::__anonc73d03e20103`)
- L59 _enumerator_ `enum { Null, String, Number, Callback } Format; FString StringValue; double NumberValue; FProduceJsonCounterValue CallbackValue; uint32 Flags; FJsonVariant() : Format(Null)` (scope `IPerfCounters::FJsonVariant::__anonc73d03e20103`)
- L59 _enumerator_ `enum { Null, String, Number, Callback } Format; FString StringValue; double NumberValue; FProduceJsonCounterValue CallbackValue; uint32 Flags; FJsonVariant() : Format(Null)` (scope `IPerfCounters::FJsonVariant::__anonc73d03e20103`)
