# Runtime / StudioTelemetry

- module root: `Source/Runtime/StudioTelemetry`
- headers: 3; symbols: 86
- symbol kinds: class=4, delegate=4, function=10, macro=4, member=21, prototype=39, struct=1, typedef=3
- PrivateDependencyModuleNames: Analytics, AnalyticsCSV, AnalyticsET, AnalyticsHorde, AnalyticsLog, BuildSettings, Core, HTTP, TelemetryUtils

### `Source/Runtime/StudioTelemetry/Private/AnalyticsProviderBroadcast.h` (Private)


#### class `FAnalyticsProviderBroadcast`  
`class FAnalyticsProviderBroadcast : public IAnalyticsProvider`  
_L24-69_
- inherits: `IAnalyticsProvider`
- desc: Implementation of the IAnalyticsProvider interface that forwards the API calls to an array of IAnalyticsProvider interfaces IAnalyticsProviders are specified in the Engine.ini interface and are constructed and configured automatically. AnalyticsLog for example in Engine/Config/BaseEngine.ini ; Studio Telemetry Settings [StudioTelemetry.Log] Name=LogAnalytics ProviderModule=AnalyticsLog UsageType=Editor This instructs the Broadcast provider to create a Provider from the AnalyticsLog module via the IANalyticsProviderModule interface. See FAnalayticsLog and FAnalyticsProviderLog for more details.
- L28 _public typedef_ `using TProviders = TMap<FString, TSharedPtr<IAnalyticsProvider>>;`
- L30 _public typedef_ `typedef TFunction<void(const FString& EventName, const TArray<FAnalyticsEventAttribute>& Attrs)> OnRecordEvent;`
- L33 _public prototype_ `FAnalyticsProviderBroadcast();`
- L35 _public prototype_ `static TSharedPtr<FAnalyticsProviderBroadcast> CreateAnalyticsProvider();`
- L37 _public prototype_ `virtual bool StartSession(const TArray<FAnalyticsEventAttribute>& Attributes = {}) override;`
- L38 _public prototype_ `virtual void EndSession() override;`
- L39 _public prototype_ `virtual void FlushEvents() override;`
- L41 _public prototype_ `virtual void SetDefaultEventAttributes(TArray<FAnalyticsEventAttribute>&& Attributes) override;`
- L42 _public prototype_ `virtual TArray<FAnalyticsEventAttribute> GetDefaultEventAttributesSafe() const override;`
- L43 _public prototype_ `virtual int32 GetDefaultEventAttributeCount() const override;`
- L44 _public prototype_ `virtual FAnalyticsEventAttribute GetDefaultEventAttribute(int AttributeIndex) const override;`
- L46 _public prototype_ `virtual bool SetSessionID(const FString& InSessionID) override;`
- L47 _public prototype_ `virtual void SetUserID(const FString& InUserID) override;`
- L49 _public prototype_ `virtual FString GetSessionID() const override;`
- L50 _public prototype_ `virtual FString GetUserID() const override;`
- L52 _public function_ `virtual void RecordEvent(const FString& EventName, const TArray<FAnalyticsEventAttribute>& Attributes) override`
- L57 _public prototype_ `virtual void RecordEvent(const FString& EventName, const TArray<FAnalyticsEventAttribute>& Attributes, EAnalyticsRecordEventMode Mode) override;`
- L58 _public prototype_ `void SetRecordEventCallback(OnRecordEvent Callback);`
- L59 _public function_ `bool HasValidProviders() const`
- L60 _public prototype_ `TWeakPtr<IAnalyticsProvider> GetAnalyticsProvider(const FString& Name);`
- L64 _private member_ `TProviders Providers;`
- L65 _private member_ `FString UserID;`
- L66 _private member_ `FString SessionID;`
- L67 _private member_ `TArray<FAnalyticsEventAttribute> DefaultEventAttributes;`
- L68 _private member_ `OnRecordEvent RecordEventCallback;`

### `Source/Runtime/StudioTelemetry/Private/StudioTelemetryLog.h` (Private)


#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogStudioTelemetry, Log, All);` — StudioTelemetry plugin logging
- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogStudioTelemetry, Log, All);` — StudioTelemetry plugin logging

### `Source/Runtime/StudioTelemetry/Public/StudioTelemetry.h` (Public)


#### class `FStudioTelemetry`  
`class FStudioTelemetry : public IModuleInterface`  
_L24-160_
- inherits: `IModuleInterface`
- desc: Studio Telemetry API Notes: Interface for adding Studio level Telemetry to products. Studio Telemetry will never function in shipping builds. Developers are encouraged to add post their own development telemetry events via this API. Developers can implement their own IAnalyticsProviderModule where custom recording of Studio Telemetry events to their own Analytics Backend is desired. Custom AnalyticsProviders can be added to the plugin via the .ini. See FAnalyticsProviderLog or FAnalyticsProviderET for example. Telemetry events are recored to all registered IAnalyticsProviders supplied in the .ini file using the FAnalyticsProviderBroadcast provider, except where specifically recorded with the RecordEvent(ProviderName,.. ) API below
- L28 _public typedef_ `typedef TFunction<void(const FString& EventName, const TArray<FAnalyticsEventAttribute>& Attrs)> OnRecordEventCallback;`
- L31 _public function_ `static bool IsAvailable()` — Check whether the module is available
- L34 _public prototype_ `static FStudioTelemetry& Get();` — Access to the module singleton
- L37 _public prototype_ `TWeakPtr<IAnalyticsProvider> GetProvider(const FString& ProviderName);` — Access to the a specific named analytics provider within the system
- L40 _public prototype_ `TWeakPtr<IAnalyticsProvider> GetProvider();` — Access to the broadcast analytics provider for the system
- L43 _public prototype_ `TWeakPtr<IAnalyticsTracer> GetTracer();` — Access to the tracer for the system
- L46 _public prototype_ `bool StartSession();` — Starts a new analytics session. Returns true if the session was already running or started successfully
- L49 _public prototype_ `void EndSession();` — Ends an existing analytics session
- L52 _public prototype_ `bool IsSessionRunning() const;` — Is Session Running
- L55 _public prototype_ `void RecordEvent(const FString& EventName, const TArray<FAnalyticsEventAttribute>& Attributes = {});` — Thread safe method to record an event to all registered analytics providers
- L58 _public prototype_ `void RecordEvent(const FName CategoryName, const FString& EventName, const TArray<FAnalyticsEventAttribute>& Attributes = {});` — Thread safe method to record an event to all registered analytics providers
- L61 _public prototype_ `void RecordEventToProvider(const FString& ProviderName, const FString& EventName, const TArray<FAnalyticsEventAttribute>& Attributes = {});` — Thread safe method to record an event to the specifically named analytics provider
- L64 _public prototype_ `void FlushEvents();` — Thread safe method to flush all events on all registered analytics providers
- L67 _public prototype_ `TSharedPtr<IAnalyticsSpan> StartSpan(const FName Name, const TArray<FAnalyticsEventAttribute>& AdditionalAttributes = {});` — Start a new span specifying the parent
- L70 _public prototype_ `TSharedPtr<IAnalyticsSpan> StartSpan(const FName Name, TSharedPtr<IAnalyticsSpan> ParentSpan, const TArray<FAnalyticsEventAttribute>& AdditionalAttributes = {});` — Start a new span specifying the parent
- L73 _public prototype_ `bool EndSpan(TSharedPtr<IAnalyticsSpan> Span, const TArray<FAnalyticsEventAttribute>& AdditionalAttributes = {});` — End an existing span
- L76 _public prototype_ `bool EndSpan(const FName Name, const TArray<FAnalyticsEventAttribute>& AdditionalAttributes = {});` — End an existing span by name
- L79 _public prototype_ `TSharedPtr<IAnalyticsSpan> GetSpan(const FName Name);` — Get an active span by name, non active spans will not be available
- L82 _public prototype_ `TSharedPtr<IAnalyticsSpan> GetSessionSpan() const;` — Get the root session span
- L85 _public prototype_ `void SetRecordEventCallback(OnRecordEventCallback);` — Callback for interception of telemetry events recording that can be used by Developers to send telemetry events to their own back end, though it is recommended that Developers implement their own IAnalyticsProvider via their own IAnalyticsProviderModule
- L88 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnStartSession);` — Delegates for event callbacks
- L89 _public function_ `FOnStartSession& GetOnStartSession()`
- L91 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnEndSession);`
- L92 _public function_ `FOnEndSession& GetOnEndSession()`
- L94 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnRecordEvent, const FString&, const TArray<FAnalyticsEventAttribute>&);`
- L95 _public function_ `FOnRecordEvent& GetOnRecordEvent()`
- L139 _private prototype_ `void LoadConfiguration();` — Configure the plugin
- L150 _private member_ `FCriticalSection CriticalSection;`
- L151 _private member_ `TSharedPtr<FAnalyticsProviderBroadcast> AnalyticsProvider;`
- L152 _private member_ `TSharedPtr<IAnalyticsTracer> AnalyticsTracer;`
- L153 _private member_ `OnRecordEventCallback RecordEventCallback;`
- L154 _private member_ `FGuid SessionGUID;`
- L155 _private member_ `FConfig Config;`
- L156 _private member_ `FDateTime SessionStartTime;`
- L157 _private member_ `FOnStartSession OnStartSession;`
- L158 _private member_ `FOnEndSession OnEndSession;`
- L159 _private member_ `FOnRecordEvent OnRecordEvent;`

#### class `FStudioTelemetry::FSessionScope`  
`class FSessionScope`  
_L98-110_
- desc: Scoped Session helper class
- L101 _public function_ `FSessionScope()`
- L106 _public function_ `~FSessionScope()`

#### class `FStudioTelemetry::FSpanScope`  
`class FSpanScope`  
_L113-134_
- desc: Scoped Span helper class
- L116 _public function_ `FSpanScope(const FName Name, const TArray<FAnalyticsEventAttribute>& AdditionalAttributes = {} )`
- L124 _public function_ `~FSpanScope()`
- L133 _private member_ `TSharedPtr<IAnalyticsSpan> Span;`

#### struct `FStudioTelemetry::FConfig`  
`struct FConfig`  
_L141-148_
- L143 _public member_ `bool bSendTelemetry = true;` — Only send telemetry data if we have been requested to
- L144 _public member_ `bool bSendUserData = false;` — Never send user data unless specifically asked to
- L145 _public member_ `bool bSendHardwareData = false;` — Never send hardware data unless specifically asked to4
- L146 _public member_ `bool bSendOSData = false;` — Never send operating system data unless specifically asked to
- L147 _public member_ `bool bSendSessionContext = true;` — Send the session context data with every event

#### Free symbols / members of external scopes

- L88 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnStartSession);` — Delegates for event callbacks
- L91 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnEndSession);`
- L94 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnRecordEvent, const FString&, const TArray<FAnalyticsEventAttribute>&);`
- L163 _macro_ `#define STUDIO_TELEMETRY_SESSION_SCOPE FStudioTelemetry::FSessionScope UE_JOIN(FSessionScope, __LINE__);` — Useful macros for scoped sessions and spans
- L164 _macro_ `#define STUDIO_TELEMETRY_SPAN_SCOPE(Name) FStudioTelemetry::FSpanScope UE_JOIN(FSpanScope, __LINE__)(TEXT(#Name));`
- L165 _macro_ `#define STUDIO_TELEMETRY_START_SPAN(Name) if (FStudioTelemetry::Get().IsAvailable()) { FStudioTelemetry::Get().StartSpan(TEXT(#Name));}`
- L166 _macro_ `#define STUDIO_TELEMETRY_END_SPAN(Name) if (FStudioTelemetry::Get().IsAvailable()) { FStudioTelemetry::Get().EndSpan(TEXT(#Name));}`
