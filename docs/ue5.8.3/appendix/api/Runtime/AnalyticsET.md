# Runtime / AnalyticsET

- module root: `Source/Runtime/Analytics/AnalyticsET`
- headers: 8; symbols: 241
- symbol kinds: class=8, delegate=2, enum=1, enumerator=7, function=24, macro=5, member=98, prototype=85, struct=8, typedef=3
- PrivateDependencyModuleNames: Analytics, HTTP, Json
- PublicDependencyModuleNames: Core
- PublicIncludePathModuleNames: Analytics

### `Source/Runtime/Analytics/AnalyticsET/Private/AnalyticsPerfTracker.h` (Private)


#### struct `FAnalyticsPerfTracker`  
`struct FAnalyticsPerfTracker : FTSTickerObjectBase`  
_L19-56_
- inherits: `FTSTickerObjectBase`
- desc: Measures analytics bandwidth. Only active when -AnalyticsTrackPerf is specified on the command line.
- L21 _public prototype_ `FAnalyticsPerfTracker();`
- L24 _public prototype_ `void RecordFlush(uint64 Bytes, uint64 NumEvents, double TimeSec);` — Called once per flush
- L26 _public prototype_ `bool IsEnabled() const;`
- L28 _public prototype_ `void SetRunID(const FString& InRunID);`
- L32 _private prototype_ `virtual bool Tick(float DeltaTime) override;` — Check to see if we need to log another window of time.
- L35 _private prototype_ `bool WindowExpired(double Now);` — Helper to reset our window in Tick.
- L38 _private prototype_ `void ResetWindow(double Now);` — Helper to reset our window in Tick.
- L41 _private member_ `FOutputDeviceFile LogFile{ *FPaths::Combine(*FPaths::ProjectSavedDir(), TEXT("Analyt` — log file to use.
- L42 _private member_ `FString StartDate;`
- L43 _private member_ `FString CL;`
- L44 _private member_ `FString RunID = FGuid().ToString().ToLower();`
- L46 _private member_ `double LastSubmitTime = 0.0;` — Window tracking data
- L47 _private member_ `double TimeThisWindow = 0.0;`
- L48 _private member_ `uint64 BytesThisWindow = 0;`
- L49 _private member_ `uint64 NumEventsThisWindow = 0;`
- L50 _private member_ `int FlushesThisWindow = 0;`
- L51 _private member_ `int FramesThisWindow = 0;`
- L53 _private member_ `double StartTime = FPlatformTime::Seconds();` — time when the first measurement was made.
- L55 _private member_ `bool bEnabled = false;` — Controls whether metrics gathering is enabled.

#### Free symbols / members of external scopes

- L8 _macro_ `#define ANALYTICS_PERF_TRACKING_ENABLED !UE_BUILD_SHIPPING` — When enabled (and -AnalyticsTrackPerf is specified on the command line, will log out analytics flush timings on a regular basis to Saved/AnalyticsTiming.csv.
- L59 _prototype_ `void SetAnayticsETPerfTrackingRunID(const FString& RunID);` — Used to set the RunID between matches in game code. Must be carefully called only in situations where ANALYTICS_PERF_TRACKING_ENABLED = 1
- L62 _prototype_ `FAnalyticsPerfTracker& GetAnalyticsPerfTracker();` — Used to get the analytics perf tracker singleton
- L65 _prototype_ `void TearDownAnalyticsPerfTracker();` — Used to tear down the analytics perf tracker singleton
- L67 _macro_ `#define ANALYTICS_FLUSH_TRACKING_BEGIN() double FlushStartTime = FPlatformTime::Seconds()`
- L68 _macro_ `#define ANALYTICS_FLUSH_TRACKING_END(NumBytes, NumEvents) GetAnalyticsPerfTracker().RecordFlush(NumBytes, NumEvents, FPlatformTime::Seconds() - FlushStartTime)`
- L72 _macro_ `#define ANALYTICS_FLUSH_TRACKING_BEGIN(...)`
- L73 _macro_ `#define ANALYTICS_FLUSH_TRACKING_END(...)`

### `Source/Runtime/Analytics/AnalyticsET/Public/AnalyticsET.h` (Public)


#### class `FAnalyticsET`  
`class FAnalyticsET : public IAnalyticsProviderModule`  
_L22-149_
- inherits: `IAnalyticsProviderModule`
- desc: Public implementation of EpicGames.MCP.AnalyticsProvider
- L34 _public function_ `static inline FAnalyticsET& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L132 _public prototype_ `virtual TSharedPtr<IAnalyticsProvider> CreateAnalyticsProvider(const FAnalyticsProviderConfigurationDelegate& GetConfigValue) const override;` — IAnalyticsProviderModule interface. Creates the analytics provider given a configuration delegate. The keys required exactly match the field names in the Config object.
- L138 _public prototype_ `virtual TSharedPtr<IAnalyticsProviderET> CreateAnalyticsProviderET(const FAnalyticsProviderConfigurationDelegate& GetConfigValue) const;` — Construct an ET analytics provider given a configuration delegate. The keys required exactly match the field names in the Config object.
- L144 _public prototype_ `virtual TSharedPtr<IAnalyticsProviderET> CreateAnalyticsProvider(const Config& ConfigValues) const;` — Construct an ET analytics provider directly from a config object.
- L147 _private prototype_ `virtual void StartupModule() override;`
- L148 _private prototype_ `virtual void ShutdownModule() override;`

#### struct `FAnalyticsET::Config`  
`struct Config`  
_L48-121_
- desc: Defines required configuration values for ET analytics provider. APIKeyET MUST be set. Set APIServerET to an empty string to create a "NULL" analytics provider that will be a valid instance but will suppress sending any events.
- L51 _public member_ `FString APIKeyET;` — ET APIKey - Get from your account manager
- L53 _public member_ `FString APIServerET;` — ET API Server - Base URL to send events. Set this to an empty string to essentially create a NULL analytics provider that will be non-null, but won't actually send events.
- L55 _public member_ `FString APIEndpointET;` — ET API Endpoint - This is the API endpoint for the provider.
- L57 _public member_ `FString APIUnixSocketPathET;` — ET API UnixSocketPath - This is the UnixSocketPath to use as the target for the API endpoint for the provider.
- L59 _public member_ `TArray<FString> AltAPIServersET;` — ET Alt API Servers - Base URLs to send events on retry.
- L65 _public member_ `FString AppVersionET;` — AppVersion - defines the app version passed to the provider. By default this will be FEngineVersion::Current(), but you can supply your own. As a convenience, you can use -AnalyticsAppVersion=XXX to force the AppVersion to a specific value. Useful for playtest etc where you want to define a specific version string dynamically. If you supply your own Version string, occurrences of "%VERSION%" are replaced with FEngineVersion::Current(). ie, -AnalyticsAppVersion=MyCustomID-%VERSION%.
- L67 _public member_ `bool UseLegacyProtocol = false;` — When true, sends events using the legacy ET protocol that passes all attributes as URL parameters. Defaults to false.
- L69 _public member_ `bool bDropEventsOnFlushFailure = true;` — When true (default), events are dropped if flush fails
- L71 _public member_ `FString AppEnvironment;` — The AppEnvironment that the data router should use. Defaults to GetDefaultAppEnvironment.
- L73 _public member_ `FString UploadType;` — The UploadType that the data router should use. Defaults to GetDefaultUploadType.
- L75 _public member_ `uint32 RetryLimitCount = 0;` — Maximum number of retries to attempt.
- L77 _public member_ `float FlushIntervalSec = -1.f;` — Maximum time to elapse before forcing events to be flushed. Use a negative value to use the defaults (60 sec).
- L79 _public member_ `int32 MaximumPayloadSize = -1;` — Maximum size a payload can reach before we force a flush of the payload. Use a negative value to use the defaults. See FAnalyticsProviderETEventCache.
- L81 _public member_ `int32 PreallocatedPayloadSize = -1;` — We preallocate a payload. It defaults to the Maximum configured payload size (see FAnalyticsProviderETEventCache). Use a negative value use the default. See FAnalyticsProviderETEventCache.
- L84 _public prototype_ `Config() = default;` — Default ctor to ensure all values have their proper default.
- L86 _public function_ `Config(FString InAPIKeyET, FString InAPIServerET, FString InAppVersionET = FString(), bool InUseLegacyProtocol = false, FString InAppEnvironment = FString(), FString InUploadType = FString(), TArray<FString> InAltApiServers = TArray<FString>(), float InFlushIntervalSec = -1.f, int32 InMaximumPayloadSize = -1, int32 InPreallocatedPayloadSize = -1) : APIKeyET(MoveTemp(InAPIKeyET)) , APIServerET(MoveTemp(InAPIServerET)) , AltAPIServersET(MoveTemp(InAltApiServers)) , AppVersionET(MoveTemp(InAppVersionET)) , UseLegacyProtocol(InUseLegacyProtocol) , AppEnvironment(MoveTemp(InAppEnvironment)) , UploadType(MoveTemp(InUploadType)) , FlushIntervalSec(InFlushIntervalSec) , MaximumPayloadSize(InMaximumPayloadSize) , PreallocatedPayloadSize(InPreallocatedPayloadSize)` — Ctor exposing common configurables .
- L100 _public function_ `static FString GetKeyNameForAPIKey()` — KeyName required for APIKey configuration.
- L102 _public function_ `static FString GetKeyNameForAPIServer()` — KeyName required for APIServer configuration.
- L104 _public function_ `static FString GetKeyNameForAPIEndpoint()` — KeyName required for APIEndpoint configuration.
- L106 _public function_ `static FString GetKeyNameForAPIUnixSocketPath()` — KeyName required for APIEndpoint configuration.
- L108 _public function_ `static FString GetKeyNameForAppVersion()` — KeyName required for AppVersion configuration.
- L110 _public function_ `static FString GetKeyNameForUseLegacyProtocol()` — Optional parameter to use the legacy backend protocol.
- L112 _public function_ `static FString GetKeyNameForAppEnvironment()` — For the the data router backend protocol.
- L114 _public function_ `static FString GetKeyNameForUploadType()` — For the the data router backend protocol.
- L116 _public function_ `static FString GetDefaultAppEnvironment()` — Default value if no APIServer configuration is provided.
- L118 _public function_ `static FString GetDefaultUploadType()` — Default value if no UploadType is given, and UseDataRouter protocol is specified.
- L120 _public function_ `static FString GetDefaultAPIEndpoint()` — Default value if no APIEndpoint is given.

### `Source/Runtime/Analytics/AnalyticsET/Public/AnalyticsFlowTracker.h` (Public)


#### class `FAnalyticsFlowTracker`  
`class UE_DEPRECATED(5.4, "Use FAnalyticsTracer instead.") FAnalyticsFlowTracker : FNoncopyable`  
_L11-98_
- inherits: `FNoncopyable`
- L14 _public function_ `FAnalyticsFlowTracker()`
- L15 _public function_ `~FAnalyticsFlowTracker()`
- L18 _public prototype_ `void SetProvider(TSharedPtr<IAnalyticsProvider> AnalyticsProvider);` — Sets the analytics provider for the flow tracker.
- L21 _public prototype_ `void StartSession();` — Begins a new flow tracking session. Will emit Flow and SubFlow events to the specified analytics provider
- L24 _public prototype_ `void EndSession();` — Ends all open Flows and SubFlows
- L27 _public prototype_ `FGuid StartFlow(const FName& FlowName);` — Start a new Flow, the existing flow context will be pushed onto a stack and the new flow will become the current context
- L30 _public prototype_ `bool EndFlow(bool bSuccess = true, const TArray<FAnalyticsEventAttribute>& AdditionalAttributes = {});` — End the flow for the current context and pop the stack
- L33 _public prototype_ `bool EndFlow(const FName& FlowName, bool bSuccess = true, const TArray<FAnalyticsEventAttribute>& AdditionalAttributes = {});` — End an existing flow by name
- L36 _public prototype_ `bool EndFlow(const FGuid& FlowGuid, bool bSuccess = true, const TArray<FAnalyticsEventAttribute>& AdditionalAttributes = {});` — End an bool flow by GUID
- L39 _public prototype_ `FGuid StartSubFlow(const FName& SubFlowName);` — Start a new flow and add it to the current flow context
- L42 _public prototype_ `FGuid StartSubFlow(const FName& SubFlowName, const FGuid& FlowGuid);` — Start a new flow step and add it to a specific flow context by GUID
- L45 _public prototype_ `bool EndSubFlow(const FName& SubFlowName, bool bSuccess = true, const TArray<FAnalyticsEventAttribute>& AdditionalAttributes = {});` — End an existing flow step by name
- L48 _public prototype_ `bool EndSubFlow(const FGuid& SubFlowGuid, bool bSuccess = true, const TArray<FAnalyticsEventAttribute>& AdditionalAttributes = {});` — End an existing flow step by GUID
- L80 _private prototype_ `bool EndFlowInternal(const FGuid& FlowGuid, bool bSuccess = true, const TArray<FAnalyticsEventAttribute>& AdditionalAttributes = {});`
- L82 _private prototype_ `FGuid StartSubFlowInternal(const FName& NewSubFlowName, const FGuid& FlowGuid);`
- L83 _private prototype_ `bool EndSubFlowInternal(const FGuid& SubFlowGuid, bool bSuccess = true, const TArray<FAnalyticsEventAttribute>& AdditionalAttributes = {});`
- L85 _private member_ `TMap<FName, FGuid> FlowGuidRegistry;`
- L86 _private member_ `TMap<FGuid, FFlowData> FlowDataRegistry;`
- L87 _private member_ `TMap<FName, FGuid> SubFlowGuidRegistry;`
- L88 _private member_ `TMap<FGuid, FSubFlowData> SubFlowDataRegistry;`
- L89 _private member_ `TArray<FGuid> FlowDataStack;`
- L90 _private member_ `FCriticalSection CriticalSection;`
- L91 _private member_ `TSharedPtr<IAnalyticsProvider> AnalyticsProvider;`
- L93 _private member_ `const uint32 FlowSchemaVersion = 4;`
- L94 _private member_ `const FString FlowEventName = "It`
- L96 _private member_ `const uint32 SubFlowSchemaVersion = 4;`
- L97 _private member_ `const FString SubFlowEventName = "It`

#### struct `FAnalyticsFlowTracker::FSubFlowData`  
`struct FSubFlowData`  
_L52-65_
- L54 _public member_ `FName FlowName;`
- L55 _public member_ `FGuid FlowGuid = FGuid();`
- L56 _public member_ `FName SubFlowName;`
- L57 _public member_ `FGuid SubFlowGuid;`
- L58 _public member_ `FDateTime StartTime = 0;`
- L59 _public member_ `FDateTime EndTime = 0;`
- L60 _public member_ `FThreadId ThreadId = 0;`
- L61 _public member_ `double TimeInSeconds = 0;`
- L62 _public member_ `bool bSuccess = false;`
- L63 _public member_ `int32 ScopeDepth;`
- L64 _public member_ `TArray<FAnalyticsEventAttribute> AdditionalEventAttributes;`

#### struct `FAnalyticsFlowTracker::FFlowData`  
`struct FFlowData`  
_L68-78_
- L70 _public member_ `FName FlowName = "No`
- L71 _public member_ `FGuid FlowGuid = FGuid();`
- L72 _public member_ `FDateTime StartTime = 0;`
- L73 _public member_ `FDateTime EndTime = 0;`
- L74 _public member_ `FThreadId ThreadId = 0 ;`
- L75 _public member_ `double TimeInSeconds = 0;`
- L76 _public member_ `TArray<FGuid> SubFlowDataArray;`
- L77 _public member_ `TArray<FGuid> SubFlowDataStack;`

#### Free symbols / members of external scopes

- L9 _typedef_ `using FThreadId = uint32;`

### `Source/Runtime/Analytics/AnalyticsET/Public/AnalyticsProviderETEventCache.h` (Public)


#### class `FAnalyticsProviderETEventCache`  
`class FAnalyticsProviderETEventCache`  
_L25-164_
- desc: Mixin class for Epic Telemetry implementors. The purpose of this class is to support the concept of caching events that are added via the standard RecordEvent API and serializing them into a payload in a Json format compatible with Epic's backend data collectors. The job of transporting these payloads to an external collector (generally expected to be via HTTP) is left to higher level classes to implement. All public APIs in this class are threadsafe. Implemented via crappy critical sections for now, but they are safe.
- L35 _public prototype_ `FAnalyticsProviderETEventCache(int32 MaximumPayloadSize = -1, int32 InPreallocatedPayloadSize = -1);` — Default ctor. @param InPreallocatedPayloadSize - size to preallocate the payload buffer to during init and after flushing. If negative, will match the INI-configured MaximumPayloadSize. @param MaximumPayloadSize - size before a payload will be queued for flush. This ensures that no payload ever gets too large. See AddToCache() and HasFlushesQueued() for details. If negative, will use INI-configured value: Engine:[AnalyticsProviderETEventCache]MaximumPayloadSize, or 100KB if not configured.
- L41 _public prototype_ `void AddToCache(FString EventName, const TArray<FAnalyticsEventAttribute>& Attributes);` — Adds a new event to the cache. If the estimated payload size will increase beyond MaximumPayloadSize then a flush will be queued here. This will make HasFlushesQueued() == true.
- L42 _public prototype_ `void AddToCache(FString EventName);`
- L49 _public prototype_ `void SetDefaultAttributes(TArray<FAnalyticsEventAttribute>&& DefaultAttributes);` — Sets an array of attributes that will automatically be appended to any event that is sent. Logical effect is like adding them to all events before calling RecordEvent. Practically, it is implemented much more efficiently from a storage and allocation perspective.
- L54 _public prototype_ `TArray<FAnalyticsEventAttribute> GetDefaultAttributes() const;` — @return the current array of default attributes.
- L59 _public prototype_ `int32 GetDefaultAttributeCount() const;` — @return the number of default attributes are currently being applied.
- L65 _public prototype_ `FAnalyticsEventAttribute GetDefaultAttribute(int32 AttributeIndex) const;` — Range checking is not done, similar to TArray. Use GetDefaultAttributeCount() first! @return one attribute of the default attributes so we don't have to copy the entire attribute array.
- L69 _public prototype_ `FString FlushCache(SIZE_T* OutEventCount = nullptr);` — `UE_DEPRECATED(4.25, "This method has been deprecated, use FlushCacheUTF8() instead.")` — Flushes the cache as a string. This method is inefficient because we build up the array directly as UTF8. If nothing is cached, returns an empty string.
- L72 _public prototype_ `TArray<uint8> FlushCacheUTF8();` — Flushes the cache as a UTF8 char array. Returns a uint8 because that's what IHttpRequest prefers. If nothing is cached, returns an empty array.
- L77 _public prototype_ `TArray<uint8> CreateImmediatePayload(const FString& EventName, const TArray<FAnalyticsEventAttribute>& Attributes) const;` — Creates a immediate payload with the existing default attributes
- L82 _public prototype_ `bool CanFlush() const;` — Determines whether we have anything we need to flush, either a queued flush or existing events in the payload.
- L89 _public prototype_ `bool HasFlushesQueued() const;` — Lets external code know that there are payloads queued for flush. This happens when AddCache() calls cause the payload size to exceed MaxPayloadSize. Calling code needs to notice this and flush the queue.
- L94 _public prototype_ `int GetNumCachedEvents() const;` — Gets the number of cached events (doesn't include any flushes that are already queued for flush).
- L100 _public prototype_ `void SetPreallocatedPayloadSize(int32 InSetPreallocatedPayloadSize);` — Sets the preallocated payload size @param InPreallocatedCacheSize size to preallocate the payload buffer to during init and after flushing. If negative, will match the INI-configured MaximumPayloadSize.
- L103 _public prototype_ `int32 GetSetPreallocatedPayloadSize() const;` — Gets the preallocated size of the payload buffer.
- L118 _public prototype_ `static void OnStartupModule();`
- L121 _private prototype_ `void QueueFlush();`
- L123 _private prototype_ `TSharedRef<FAnalyticsProviderETEventCache> CloneForImmediateMode() const;`
- L149 _private member_ `int32 MaximumPayloadSize;`
- L150 _private member_ `int32 PreallocatedPayloadSize;`
- L156 _private member_ `TArray<FAnalyticsEventEntry> CachedEventEntries;` — List of analytic events pending a server update . NOTE: The following members MUST be accessed inside a lock on CachedEventsCS!!
- L157 _private member_ `TArray<uint8> CachedEventUTF8Stream;`
- L158 _private member_ `TArray<FAnalyticsEventAttribute> CachedDefaultAttributes;`
- L159 _private member_ `TArray<uint8> CachedDefaultAttributeUTF8Stream;`
- L160 _private member_ `TArray<TArray<uint8>> FlushQueue;`
- L163 _private member_ `mutable FTransactionallySafeCriticalSection CachedEventsCS;` — Critical section for updating the CachedEvents. Mutable to allow const methods to access the list.

#### class `FAnalyticsProviderETEventCache::Lock`  
`class Lock`  
_L108-116_
- desc: For when you need to take a lock across multiple API calls
- L111 _public function_ `UE_NODISCARD_CTOR explicit Lock(FAnalyticsProviderETEventCache& EventCache) : ScopedLock(EventCache.CachedEventsCS)`
- L115 _private member_ `UE::TScopeLock<FTransactionallySafeCriticalSection> ScopedLock;`

#### struct `FAnalyticsProviderETEventCache::FAnalyticsEventEntry`  
`struct FAnalyticsEventEntry`  
_L128-147_
- desc: Analytics event entry to be cached
- L131 _public member_ `FString EventName;` — name of event
- L133 _public member_ `FDateTime TimeStamp;` — local time when event was triggered
- L135 _public member_ `int32 DateOffsetByteOffset;` — byte offset into the payload stream that this DateOffset will be stored. Used when flushing the payload to set the proper DateOffset.
- L137 _public member_ `int32 EventSizeChars;` — Total charts used by the event. Mostly used for debugging large payloads.
- L141 _public function_ `FAnalyticsEventEntry(FString&& InEventName, int32 InDateOffsetByteOffset, int32 InEventSizeChars) : EventName(MoveTemp(InEventName)) , TimeStamp(FDateTime::UtcNow()) , DateOffsetByteOffset(InDateOffsetByteOffset) , EventSizeChars(InEventSizeChars)` — Constructor. Requires rvalue-refs to ensure we move values efficiently into this struct.

### `Source/Runtime/Analytics/AnalyticsET/Public/AnalyticsSessionSummaryManager.h` (Public)


#### enum `EAnalyticsSessionShutdownType`  
`enum class EAnalyticsSessionShutdownType : int32`  
_L23-32_
- desc: Defines how the principal process (the application for which analytics is gathered) exited. When the analytics session summary manager aggregates the summaries for a session, it looks for 'ShutdownTypeCode' key and if the key is found, it converts it to its string representation and add the 'ShutdownType' property known by the analytics backend.
- L25 _public enumerator_ `Shutdown`
- L26 _public enumerator_ `Terminated`
- L27 _public enumerator_ `Debugged`
- L28 _public enumerator_ `Crashed`
- L29 _public enumerator_ `Abnormal`
- L30 _public enumerator_ `Unknown`
- L31 _public enumerator_ `Hang`

#### class `FAnalyticsSessionSummaryManager`  
`class FAnalyticsSessionSummaryManager`  
_L51-205_
- desc: Manages the lifecycle of analytics summaries created by an application and its subsidiary processes. It manages the summary files created by the processes, tracks which processes are working together, aggregates the summaries from collaborating processes, discards outdated sessions and sends the final summary reports. Several processes can collaborate to collect analytics for one principal process. The common case being the Editor acting as the principal process and CrashReportClient (CRC) acting as a subsidiary process. The principal process and its subsidiaries form a group of processes tied together. The last process of the group to exit is responsible to aggregates and sends the final report for the principal process. For any reasons, if the final report cannot be sent by a group, the responsibility to deal with the left over is put on the principal process. The principal process is responsible to clean up the left over from its previous execution(s) and possibly salvage and send reports delayed.
- L55 _public member_ `static const TAnalyticsProperty<int32> ShutdownTypeCodeProperty;` — Special key handled by the manager for the analytics backend. Its value must be one of EAnalyticsSessionShutdownType enum value.
- L58 _public member_ `static const TAnalyticsProperty<bool> IsUserLoggingOutProperty;` — Special key handled in CRC to decide if an abnormal shutdown crash report should be generated.
- L71 _public prototype_ `FAnalyticsSessionSummaryManager(const FString& ProcessName, const FString& ProcessGroupId, const FString& UserId, const FString& AppId, const FString& AppVersion, const FString& SessionId, const FString& SavedDir = TEXT(""));` — Constructs a manager for the principal process, usually the main application. @param ProcessName The process tag name of the principal process. Ex. "Editor". @param ProcessGroupId A unique ID shared by the principal and subsidiary processes. This is how information created by various processes is associated. @param UserId The current analytics user ID. @see IAnalyticsProviderET @param AppId The current application ID used by analytics to identify the application. @see IAnalyticsProviderET @param AppVersion the current application version used by the analytics for this application. @see IAnalyticsProviderET @param SessionId the current session ID assigned by the analytics. @see IAnalyticsProviderET @param SavedDir The directory where files will be persisted. Should be the same for the principal and the subsidiary processes. If unspecified, the manager uses its internal default.
- L80 _public prototype_ `FAnalyticsSessionSummaryManager(const FString& ProcessName, const FString& ProcessGroupId, uint32 PrincipalProcessId, const FString& SavedDir = TEXT(""));` — Constructs a manager for a subsidiary process, usually a companion process that collects extra information on the behalf of the principal process. @param ProcessName The process tag name of the subsidiary process. Ex. "CrashReportClient". @param ProcessGroupId A unique ID shared by the principal and subsidiary processes. This is how information created by various processes is associated. @param PrincipalProcessId The principal process ID to which this subsidiary process is associated. @param SavedDir The directory where files will be persisted. Should be the same for the principal and the subsidiary processes. If unspecified, the manager uses its internal default.
- L85 _public prototype_ `~FAnalyticsSessionSummaryManager();` — Destructor.
- L90 _public prototype_ `void Tick();` — Discovers and salvages/sends/cleans up left over from previous execution(s), if any. Only the principal process can send left over sessions.
- L98 _public prototype_ `TSharedPtr<IAnalyticsPropertyStore> MakeStore(uint32 InitialCapacity);` — Creates a new property store associated to this manager process group. The manager only sends an analytics session summary when all collecting processes have closed their property store. Ensure to flush and release the store before calling the manager Shutdown() to ensure the session is sent as soon a possible. Subsequent calls to MakeStore will increment an internal counter in the store's filename. @param InitialCapacity The amount of space to reserve in the file.
- L107 _public prototype_ `void SetSender(TSharedPtr<IAnalyticsSessionSummarySender> Sender);` — Sets a summary sender to enable the manager to send sessions. If the sender is null, the sessions are not sent. If the sender is set, the manager will periodically search and send pending sessions, usually the one left over from processes that died unexpectedly. As a rule, the principal process is responsible to send the left over summary sessions and a subsidiary process only sends the current sessions summary if it is the last process of the group to exit. The manager deletes the session data while sending.
- L113 _public prototype_ `void SetUserId(const FString& UserId);` — Sets a the user id used for reporting analytics. Allows for changing the application user after startup. Will set the user id on all existing stores created from this session summary manager.
- L122 _public prototype_ `void Shutdown(bool bDiscard = false);` — Shuts down and sends the session summaries that can be sent, if a sender is set. Remember to flush and discard the property store returned by MakeStore() before shutting down to prevent delaying the report. @param bDiscard Whether the current session is discarded or not. Discarded sessions are not sent. @see SetSender() @see MakeStore()
- L129 _public prototype_ `static void CleanupExpiredFiles(const FString& SavedDir = TEXT(""));` — Cleans up all expired files that match the analytics session filename pattern. The manager automaticallly clean up if it runs, but if the analytics is off and the manager is not instantiated anymore, some dead files can be left over. @param SavedDir The directory used to save the analytic files. If unspecified, use the internal default.
- L135 _public function_ `static FTimespan GetSessionExpirationAge()` — Returns the age at which a session is considered expired and shouldn't be sent anymore. @return The expiration delay.
- L166 _private prototype_ `FAnalyticsSessionSummaryManager(const FString& ProcessName, const FString& ProcessGroupId, uint32 InCurrentProcessId, uint32 PrincipalProcessId, const FString& UserId, const FString& AppId, const FString& AppVersion, const FString& SessionId, const FString& SessionRootDir);` — Delegate constructor.
- L169 _private prototype_ `TMap<FString, FProcessGroup> GetSessionFiles() const;` — Returns all processes group (key is process group id) for which files exists.
- L172 _private prototype_ `void ProcessSummary(const FString& ProcessGroupId, const FProcessGroup& ProcessGroup);` — Processes the information collected by the principal and its subsidiary processes and decides if a summmary can be aggregated and sent.
- L175 _private prototype_ `bool AggregateSummaries(const FString& ProcessGroupId, const FProcessGroup& ProcessGroup, TArray<FAnalyticsEventAttribute>& OutSummaryProperties, TArray<FAnalyticsEventAttribute>& OutInternalProperties);` — Loads the summaries created for the application and its subsidiary processes (like Editor/CRC combo) and aggregates summary properties.
- L178 _private prototype_ `bool CleanupFiles(const TArray<FPropertyFileInfo>& PropertyFiles, bool bOnSuccess);` — Deletes the files used to record and perist the properties.
- L181 _private function_ `bool IsOrphanGroupsOwner() const` — Checks if this process is allowed to process and send orphan files.
- L184 _private prototype_ `bool IsPrincipalProcess() const;` — Returns whether this manager instance represents the principal process of a group.
- L187 _private prototype_ `void PruneTrackedPropertyStores();` — Prune the list of property stores for invalid entries.
- L190 _private member_ `TArray<TWeakPtr<IAnalyticsPropertyStore>> WeakPropertyStores;`
- L191 _private member_ `TSharedPtr<IAnalyticsSessionSummarySender> SummarySender;`
- L192 _private member_ `FString ProcessName;`
- L193 _private member_ `FString ProcessGroupId;`
- L194 _private member_ `FString UserId;`
- L195 _private member_ `FString AppId;`
- L196 _private member_ `FString AppVersion;`
- L197 _private member_ `FString SessionId;`
- L198 _private member_ `FString SessionRootPath;`
- L199 _private member_ `uint32 CurrentProcessId;`
- L200 _private member_ `uint32 PrincipalProcessId;`
- L201 _private member_ `uint32 StoreCounter;`
- L202 _private member_ `double NextOrphanSessionCheckTimeSecs;`
- L203 _private member_ `bool bOrphanGroupOwner = false;`
- L204 _private member_ `bool bIsPrincipal = false;`

#### struct `FAnalyticsSessionSummaryManager::FPropertyFileInfo`  
`struct FPropertyFileInfo`  
_L139-149_
- desc: Information about a property store used by a process.
- L142 _public member_ `uint32 ProcessId = 0;` — The ID of the process that wrote the property file. Ex. CRC can write a summary for an Editor session.
- L145 _public member_ `FString ProcessName;` — The tag name of the process that wrote the property file.
- L148 _public member_ `FString Pathname;` — Pathname to the property file.

#### struct `FAnalyticsSessionSummaryManager::FProcessGroup`  
`struct FProcessGroup`  
_L152-162_
- desc: Lists the files created by a process group.
- L155 _public member_ `uint32 PrincipalProcessId = 0;` — Identify the process for which the summary was written.
- L158 _public member_ `FString PrincipalProcessName;` — The principal process name.
- L161 _public member_ `TArray<FPropertyFileInfo> PropertyFiles;` — The list of files generated by the processes in the group.

#### Free symbols / members of external scopes

- L37 _prototype_ `const TCHAR* LexToString(EAnalyticsSessionShutdownType ShutdownTypeCode);` — Converts the specified shutdown code to its string representation.

### `Source/Runtime/Analytics/AnalyticsET/Public/AnalyticsSessionSummarySender.h` (Public)


#### class `FAnalyticsSessionSummarySender`  
`class FAnalyticsSessionSummarySender : public IAnalyticsSessionSummarySender`  
_L17-40_
- inherits: `IAnalyticsSessionSummarySender`
- desc: Sends the analytics session summary to Epic Games analytics service.
- L25 _public prototype_ `FAnalyticsSessionSummarySender(IAnalyticsProviderET& Provider, TFunction<bool(const FAnalyticsEventAttribute&)> ShouldEmitFilterFunc = TFunction<bool(const FAnalyticsEventAttribute&)>());` — Construction a summary sender. @param Provider The analytics provider that will be used to emits the summary event. @param ShouldEmitFilterFunc A filter function invoked for each properties before sending. If the function is bound and returns false, the property will be filtered out. If unbound, all properties passed to SendSesionSummary() are emitted.
- L35 _public prototype_ `virtual bool SendSessionSummary(const FString& UserId, const FString& AppId, const FString& AppVersion, const FString& SessionId, const TArray<FAnalyticsEventAttribute>& Properties) override;` — Emits the summary events for the specified session id on behalf of the specified user/app/appversion. The function filters the properties by invoking the functor specified at construction. @param UserId The user emitting the report. @param AppId The application for which the reports is emitted. @param AppVersion The application version for which the report is emitted. @param SessionId The session is for which the report is emitted. @param Properties The list of properties that makes up the summary event.
- L38 _private member_ `IAnalyticsProviderET& AnalyticsProvider;`
- L39 _private member_ `TFunction<bool(const FAnalyticsEventAttribute&)> ShouldEmitPropFunc;`

### `Source/Runtime/Analytics/AnalyticsET/Public/IAnalyticsProviderET.h` (Public)


#### struct `FAnalyticEventQueuedInfo`  
`struct FAnalyticEventQueuedInfo`  
_L22-27_
- L24 _public member_ `const EAnalyticsRecordEventMode Mode;`
- L25 _public member_ `const FString& EventName;`
- L26 _public member_ `const TArray<FAnalyticsEventAttribute>& Attributes;`

#### class `IAnalyticsProviderET`  
`class IAnalyticsProviderET : public IAnalyticsProvider`  
_L38-174_
- inherits: `IAnalyticsProvider`
- desc: ET specific analytics provider instance. Exposes additional APIs to support Json-based events, default attributes, and allowing events to be disabled (generally via hotfixing).
- L50 _public function_ `virtual void RecordEvent(const FString& EventName, const TArray<FAnalyticsEventAttribute>& Attributes) override` — This class augments RecordEvent with a version that takes the EventName by rvalue reference to save a string copy. Implement the base version in terms of this one.
- L58 _public function_ `virtual void RecordEvent(const FString& EventName, const TArray<FAnalyticsEventAttribute>& Attributes, EAnalyticsRecordEventMode Mode) override` — This class augments RecordEvent with a version that takes the EventName by rvalue reference to save a string copy. Implement the base version in terms of this one.
- L66 _public function_ `virtual bool StartSession(const TArray<FAnalyticsEventAttribute>& Attributes) override` — This class augments StartSession with a version that takes the SessionID instead of always generating it. Implement the base version in terms of this one.
- L82 _public prototype_ `virtual void SetAppID(FString&& AppID) = 0;` — Special setter to set the AppID, something that is not normally allowed for third party analytics providers. @param AppID The new AppID to set
- L89 _public function_ `const FString& GetAppID() const` — Method to get the AppID (APIKey) @return the AppID (APIKey)
- L96 _public prototype_ `virtual void SetAppVersion(FString&& AppVersion) = 0;` — Sets the AppVersion. @param AppVersion The new AppVersion.
- L103 _public function_ `const FString& GetAppVersion() const` — Method to get the AppVersion @return the AppVersion
- L108 _public prototype_ `virtual bool StartSession(FString InSessionID, const TArray<FAnalyticsEventAttribute>& Attributes) = 0;` — Primary StartSession API. Allow move semantics to capture the attributes.
- L116 _public prototype_ `virtual bool ShouldRecordEvent(const FString& EventName) const = 0;` — Allows higher level code to abort logic to set up for a RecordEvent call by checking the filter that will be used to send the event first. @param EventName The name of the event. @return true if the event will be recorded using the currently installed ShouldRecordEvent function
- L121 _public prototype_ `virtual void RecordEvent(FString&& EventName, const TArray<FAnalyticsEventAttribute>& Attributes) = 0;` — Primary RecordEvent API. Allow move semantics to capture the attributes.
- L126 _public prototype_ `virtual void RecordEvent(FString&& EventName, const TArray<FAnalyticsEventAttribute>& Attributes, EAnalyticsRecordEventMode Mode) = 0;` — Overload to allow platforms to implement events that are immediately sent when supported. @see EAnalyticsRecordEventMode.
- L131 _public prototype_ `virtual void SetUrlDomain(const FString& Domain, const TArray<FString>& AltDomains) = 0;` — Updates the default Domain and AltDomains.
- L136 _public prototype_ `virtual void SetUrlPath(const FString& Path) = 0;` — Updates the Path
- L141 _public prototype_ `virtual void SetHeader(const FString& HeaderName, const FString& HeaderValue) = 0;` — Sets a header to be included with analytics http requests
- L143 _public typedef_ `typedef TFunction<void(const FString& EventName, const TArray<FAnalyticsEventAttribute>& Attrs, bool bJson)> OnEventRecorded;`
- L150 _public prototype_ `virtual void SetEventCallback(const OnEventRecorded& Callback) = 0;` — Set a callback to be invoked any time an event is queued. @param the callback
- L155 _public prototype_ `virtual void BlockUntilFlushed(float InTimeoutSec) = 0;` — Blocks execution in the thread until all events have been flushed to the network.
- L160 _public prototype_ `virtual const FAnalyticsET::Config& GetConfig() const = 0;` — Return the current provider configuration.
- L163 _public typedef_ `typedef TFunction<bool(const IAnalyticsProviderET& ThisProvider, const FString& EventName)> ShouldRecordEventFunction;` — Callback used before any event is actually sent. Allows higher level code to disable events.
- L166 _public prototype_ `virtual void SetShouldRecordEventFunc(const ShouldRecordEventFunction& ShouldRecordEventFunc) = 0;` — Set an event filter to dynamically control whether an event should be sent.
- L168 _public prototype_ `virtual FOnPreAnalyticsEventProcessed& OnPreAnalyticsEventProcessed() = 0;`
- L169 _public prototype_ `virtual FOnAnalyticsEventQueued& OnAnalyticsEventQueued() = 0;`
- L173 _private member_ `mutable TArray<FAnalyticsEventAttribute> UnsafeDefaultAttributes;` — Needed to support the old, unsafe GetDefaultAttributes() API.

#### Free symbols / members of external scopes

- L20 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPreAnalyticsEventProcessed, TSharedRef<IHttpRequest, ESPMode::ThreadSafe>& );` — Fired immediately prior to the HTTP request for an analytics event being processed by HTTP
- L20 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPreAnalyticsEventProcessed, TSharedRef<IHttpRequest, ESPMode::ThreadSafe>& );` — Fired immediately prior to the HTTP request for an analytics event being processed by HTTP
- L34 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAnalyticsEventQueued, bool& , const FAnalyticEventQueuedInfo& ) class IAnalyticsProviderET : public IAnalyticsProvider { public: using IAnalyticsProvider::StartSession; using IAnalyticsProvider::RecordEvent;` — Fired on every analytic event being queued boolean value should only be left alone or set to false, which will cause the event to not be queued. FAnalyticEventQueuedInfo is only valid during the broadcast, you must copy any data from it that you need to keep

### `Source/Runtime/Analytics/AnalyticsET/Public/IAnalyticsSessionSummarySender.h` (Public)


#### class `IAnalyticsSessionSummarySender`  
`class IAnalyticsSessionSummarySender`  
_L11-25_
- desc: Sends the analytics session summary to a backend service.
- L14 _public prototype_ `virtual ~IAnalyticsSessionSummarySender() = default;`
- L24 _public prototype_ `virtual bool SendSessionSummary(const FString& UserId, const FString& AppId, const FString& AppVersion, const FString& SessionId, const TArray<FAnalyticsEventAttribute>& Properties) = 0;` — Emits the summary events for the specified session id on behalf of the specified user/app/appversion. The function filters the properties by invoking the functor specified at construction. @param UserId The user emitting the report. @param AppId The application for which the reports is emitted. @param AppVersion The application version for which the report is emitted. @param SessionId The session is for which the report is emitted. @param Properties The list of properties that makes up the summary event.
