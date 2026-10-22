# Plugins / StageMonitor

- module root: `Plugins/VirtualProduction/StageMonitoring/Source/StageMonitor`
- headers: 9; symbols: 204
- symbol kinds: class=9, delegate=7, enum=1, enumerator=4, function=16, member=49, prototype=113, struct=5
- PrivateDependencyModuleNames: CoreUObject, Engine, GameplayTags, Json, JsonUtilities, Serialization, StageMonitorCommon, VPRoles, VPUtilities
- PublicDependencyModuleNames: Core, StageDataCore

### `Plugins/VirtualProduction/StageMonitoring/Source/StageMonitor/Private/StageCriticalEventHandler.h` (Private)


#### struct `FCriticalStateEntry`  
`struct FCriticalStateEntry`  
_L17-21_
- desc: Holds information about what caused a critical state and for what timerange The range starts at first critical state entry and ends when last critical states exits
- L19 _public member_ `TArray<FName> Sources;`
- L20 _public member_ `TRange<double> Range;`

#### class `FStageCriticalEventHandler`  
`class FStageCriticalEventHandler`  
_L29-70_
- desc: Stage monitoring becomes critical when it's in a state where accuracy, timing, performance is essential This class manages the state of the stage. Multiple sources can set the stage in critical state. All of them needs to close for the stage state to come back as normal.
- L34 _public function_ `bool IsCriticalStateActive() const` — Whether or not a critical state is currently active
- L37 _public prototype_ `bool IsTimingPartOfCriticalRange(double TimeInSeconds) const;` — Verify if a time is part of any critical state range we've encountered, including the active one
- L40 _public prototype_ `void HandleCriticalEventMessage(const FCriticalStateProviderMessage* Message);` — Process new critical event message and update current state accordingly
- L43 _public prototype_ `void RemoveProviderEntries(double CurrentTime, const FGuid& Identifier);` — Used to clean up the event handler in case a provider is closed, while critical events associated to it are opened
- L46 _public prototype_ `FName GetCurrentCriticalStateSource() const;` — Returns the source name of the current critical state
- L49 _public prototype_ `TArray<FName> GetCriticalStateHistorySources() const;` — Returns the sources that triggered a critical state at some point
- L52 _public prototype_ `TArray<FName> GetCriticalStateSources(double TimeInSeconds) const;` — Returns the sources of the critical state that provided time is in. Empty is not critical state found
- L56 _private prototype_ `void CloseCriticalState(double CurrentSeconds);` — Close critical state at specified timestamp if only one layer is active
- L63 _private member_ `TMap<FGuid, TArray<FName>> ActiveEvents;` — Current active events per provider. A provider can trigger more than one type of events When no more providers have active events, the critical event range is closed
- L66 _private member_ `TOptional<FCriticalStateEntry> CurrentState;` — Timing range of the current critical state. Unbounded until it's completed
- L69 _private member_ `TArray<FCriticalStateEntry> CriticalStateHistory;` — History of timing ranges when stage was in critical state

### `Plugins/VirtualProduction/StageMonitoring/Source/StageMonitor/Private/StageMonitor.h` (Private)


#### class `FStageMonitor`  
`class FStageMonitor : public IStageMonitor`  
_L21-118_
- inherits: `IStageMonitor`
- desc: Implementation of the stage monitor
- L25 _public prototype_ `FStageMonitor() = default;`
- L26 _public prototype_ `FStageMonitor(const FStageMonitor&) = delete;`
- L27 _public prototype_ `FStageMonitor& operator=(const FStageMonitor&) = delete;`
- L28 _public prototype_ `FStageMonitor(FStageMonitor&&) = default;`
- L29 _public prototype_ `FStageMonitor& operator=(FStageMonitor&&) = default;`
- L30 _public prototype_ `virtual ~FStageMonitor();`
- L33 _public function_ `virtual bool IsActive() const override`
- L37 _public prototype_ `void Initialize();`
- L38 _public prototype_ `void Start();`
- L39 _public prototype_ `void Stop();`
- L44 _private prototype_ `bool SendMessageInternal(FStageDataBaseMessage* Payload, UScriptStruct* Type, EStageMessageFlags InFlags);` — Sends a message using messagebus to connected providers
- L47 _private prototype_ `void PublishMessageInternal(FStageDataBaseMessage* Payload, UScriptStruct* Type);` — Broadcast a message on messagebus
- L50 _private prototype_ `void HandleStageData(const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);` — Catchall messages of messagebus to handle DataProvider messages
- L53 _private prototype_ `void HandleProviderDiscoveryResponse(const FStageProviderDiscoveryResponseMessage& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);` — Handles discovery response coming from a data provider
- L56 _private prototype_ `void HandleProviderCloseMessage(const FStageProviderCloseMessage& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);` — Handles Close message from a provider shutting down
- L59 _private prototype_ `bool Tick(float DeltaTime);`
- L62 _private prototype_ `void UpdateProviderState();` — Updates each provider's state based on last communication timestamp
- L65 _private prototype_ `void SendDiscoveryMessage();` — Broadcasts a discovery message to find new providers and also keep communication active with all providers
- L68 _private prototype_ `void OnPreExit();` — Shutdowns monitor before everything has exited. Let know providers that we're out
- L72 _private function_ `template<typename MessageType, typename... Args> bool SendMessage(EStageMessageFlags Flags, Args&&... args)` — Generic send message to support constructor parameters directly and temp object created
- L84 _private function_ `template<typename MessageType, typename... Args> void PublishMessage(Args&&... args)` — Generic publish message to support constructor parameters directly and temp object created
- L96 _private member_ `TSharedPtr<FMessageEndpoint, ESPMode::ThreadSafe> MonitorEndpoint;` — Endpoint used to communicate with providers
- L99 _private member_ `TArray<FGuid> InvalidDataProviders;` — List of providers we received discovery response from that we not usable (wrong version, session id...)
- L102 _private member_ `TSharedPtr<IStageMonitorSession> Session;` — Current active session where we dispatch new data
- L105 _private member_ `double LastSentDiscoveryMessage = 0.0;` — Timestamp when we last sent a discovery message
- L108 _private member_ `bool bIsActive = false;` — Whether monitor is active (sending out discovery, listening to providers) or not
- L111 _private member_ `FTSTicker::FDelegateHandle TickerHandle;` — Handle to our ticking delegate (Ticks only when bIsActive is true)
- L114 _private member_ `FGuid Identifier;` — This monitor identifier
- L117 _private member_ `FStageProviderDiscoveryMessage CachedDiscoveryMessage;` — DiscoveryMessage built once and broadcasted periodically

### `Plugins/VirtualProduction/StageMonitoring/Source/StageMonitor/Private/StageMonitorModule.h` (Private)


#### class `FStageMonitorModule`  
`class FStageMonitorModule : public IStageMonitorModule`  
_L15-48_
- inherits: `IStageMonitorModule`
- L18 _public prototype_ `virtual ~FStageMonitorModule() = default;`
- L21 _public prototype_ `virtual void StartupModule() override;`
- L22 _public prototype_ `virtual void ShutdownModule() override;`
- L26 _public prototype_ `virtual IStageMonitor& GetStageMonitor() override;`
- L27 _public prototype_ `virtual IStageMonitorSessionManager& GetStageMonitorSessionManager() override;`
- L28 _public prototype_ `virtual void EnableMonitor(bool bEnable) override;`
- L34 _private prototype_ `void OnEngineLoopInitComplete();` — Create StageMonitor when engine is fully initialized
- L39 _protected member_ `TUniquePtr<FStageMonitor> StageMonitor;` — Single instance of the StageMonitor
- L42 _protected member_ `TUniquePtr<FStageMonitorSessionManager> SessionManager;` — Stage monitor session manager responsible to create/load/save sessions
- L45 _protected member_ `TUniquePtr<FAutoConsoleCommand> CommandStart;`
- L46 _protected member_ `TUniquePtr<FAutoConsoleCommand> CommandStop;`

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogStageMonitor, Log, All);`
- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogStageMonitor, Log, All);`

### `Plugins/VirtualProduction/StageMonitoring/Source/StageMonitor/Private/StageMonitorSession.h` (Private)


#### class `FStageMonitorSession`  
`class FStageMonitorSession : public IStageMonitorSession`  
_L19-118_
- inherits: `IStageMonitorSession`
- desc: Implementation of the stage monitor session. Handles new data being received and organizes it for outside access
- L22 _public prototype_ `FStageMonitorSession(const FString& InSessionName);`
- L23 _public prototype_ `~FStageMonitorSession() = default;`
- L28 _public prototype_ `virtual void HandleDiscoveredProvider(const FGuid& Identifier, const FStageInstanceDescriptor& Descriptor, const FMessageAddress& Address) override;`
- L29 _public prototype_ `virtual bool AddProvider(const FGuid& Identifier, const FStageInstanceDescriptor& Descriptor, const FMessageAddress& Address) override;`
- L30 _public prototype_ `virtual void AddProviderMessage(UScriptStruct* Type, const FStageProviderMessage* MessageData) override;`
- L31 _public prototype_ `virtual TArray<FMessageAddress> GetProvidersAddress() const override;`
- L32 _public prototype_ `virtual void SetProviderState(const FGuid& Identifier, EStageDataProviderState State) override;`
- L33 _public function_ `virtual TConstArrayView<FStageSessionProviderEntry> GetProviders() const override`
- L34 _public function_ `virtual TConstArrayView<FStageSessionProviderEntry> GetClearedProviders() const override`
- L35 _public prototype_ `virtual bool GetProvider(const FGuid& Identifier, FStageSessionProviderEntry& OutProviderEntry, EGetProviderFlags Flags = EGetProviderFlags::Default) const override;`
- L36 _public prototype_ `virtual void ClearAll() override;`
- L37 _public prototype_ `virtual void ClearUnresponsiveProviders() override;`
- L38 _public prototype_ `virtual void GetAllEntries(TArray<TSharedPtr<FStageDataEntry>>& OutEntries) override;`
- L39 _public prototype_ `virtual TSharedPtr<FStageDataEntry> GetLatest(const FGuid& Identifier, UScriptStruct* Type) override;`
- L40 _public prototype_ `virtual EStageDataProviderState GetProviderState(const FGuid& Identifier) override;`
- L41 _public prototype_ `virtual bool IsStageInCriticalState() const override;`
- L42 _public prototype_ `virtual bool IsTimePartOfCriticalState(double TimeInSeconds) const override;`
- L43 _public prototype_ `virtual FName GetCurrentCriticalStateSource() const override;`
- L44 _public prototype_ `virtual TArray<FName> GetCriticalStateHistorySources() const override;`
- L45 _public prototype_ `virtual TArray<FName> GetCriticalStateSources(double TimeInSeconds) const override;`
- L46 _public prototype_ `virtual FString GetSessionName() const override;`
- L48 _public function_ `virtual FOnStageSessionNewDataReceived& OnStageSessionNewDataReceived() override`
- L49 _public function_ `virtual FOnStageSessionDataCleared& OnStageSessionDataCleared() override`
- L50 _public function_ `virtual FOnStageDataProviderListChanged& OnStageDataProviderListChanged() override`
- L51 _public function_ `virtual FOnStageDataProviderStateChanged& OnStageDataProviderStateChanged() override`
- L55 _public prototype_ `void GetIdentifierMapping(TMap<FGuid, FGuid>& OutMapping);` — Retrieve the current mapping for identifier
- L58 _public prototype_ `void SetIdentifierMapping(const TMap<FGuid, FGuid>& NewMapping);` — Sets a new identifier mapping for the session
- L63 _private prototype_ `void UpdateProviderLatestEntry(const FGuid& Identifier, UScriptStruct* Type, TSharedPtr<FStageDataEntry> NewEntry);` — Update snapshot for this message type per provider.
- L66 _private prototype_ `void InsertNewEntry(TSharedPtr<FStageDataEntry> NewEntry);` — Inserts a new message entry in our list, sorted by timecode in seconds
- L71 _private prototype_ `void FillProviderDescription(const FGuid& Identifier, const FStageInstanceDescriptor& NewDescriptor, const FMessageAddress& NewAddress, FStageSessionProviderEntry& OutEntry);` — Fills in the information on a data provider entry Could be for a new entry, an existing entry that we are updating since it was rediscovered
- L78 _private prototype_ `void UpdateIdentifierMapping(const FGuid& OldIdentifier, const FGuid& NewIdentifier);` — Updates mapping for identifier that existed in the past to the latest identifier associated with the "same" provider. When showing old activities, this must be kept to associate old activity identifier to active provider's identifier
- L83 _private member_ `TArray<FStageSessionProviderEntry> Providers;` — List of providers currently monitored
- L86 _private member_ `TArray<TSharedPtr<FStageDataEntry>> Entries;` — List of all messages received.
- L89 _private member_ `TMap<FGuid, TArray<TSharedPtr<FStageDataEntry>>> ProviderLatestData;` — Latest entry per message type for each provider
- L92 _private member_ `TUniquePtr<FStageCriticalEventHandler> CriticalEventHandler;` — Manages critical state messages to manage this session's state
- L95 _private member_ `FString SessionName;` — This session name. Used for display
- L98 _private member_ `FOnStageSessionNewDataReceived OnNewDataReceivedDelegate;` — Delegate triggered when new data was received
- L101 _private member_ `FOnStageSessionDataCleared OnStageSessionDataClearedDelegate;` — Delegate triggered when session data is cleared
- L104 _private member_ `FOnStageDataProviderListChanged OnStageDataProviderListChangedDelegate;` — Delegate triggered when the list of monitored providers changed
- L107 _private member_ `FOnStageDataProviderStateChanged OnStageDataProviderStateChangedDelegate;` — Delegate triggered when the state of a monitored providers changed
- L110 _private member_ `TArray<FStageSessionProviderEntry> ClearedProviders;` — Unresponsive providers cleared from the list
- L117 _private member_ `TMap<FGuid, FGuid> IdentifierMapping;` — When a provider is rematched to an old one, its identifier might have changed Old activities will still have the previous identifier, so this is used to keep track of identifier history

### `Plugins/VirtualProduction/StageMonitoring/Source/StageMonitor/Private/StageMonitorSessionManager.h` (Private)


#### struct `FMonitorSessionInfo`  
`struct FMonitorSessionInfo`  
_L20-28_
- reflection: `USTRUCT()`
- desc: Header written at beginning of json file to have an idea of what's in the file
- L25 _public member_ `static constexpr int32 CurrentVersion = 1;`
- L27 _public member_ `int32 Version = CurrentVersion;` — `UPROPERTY()`

#### class `FStageMonitorSessionManager`  
`class FStageMonitorSessionManager : public IStageMonitorSessionManager`  
_L31-92_
- inherits: `IStageMonitorSessionManager`
- L35 _public prototype_ `virtual TSharedPtr<IStageMonitorSession> CreateSession() override;`
- L36 _public prototype_ `virtual bool LoadSession(const FString& FileName) override;`
- L37 _public prototype_ `virtual bool SaveSession(const FString& FileName) override;`
- L38 _public prototype_ `virtual TSharedPtr<IStageMonitorSession> GetActiveSession() override;`
- L39 _public prototype_ `virtual TSharedPtr<IStageMonitorSession> GetLoadedSession() override;`
- L40 _public prototype_ `virtual FOnStageMonitorSessionLoaded& OnStageMonitorSessionLoaded() override;`
- L41 _public prototype_ `virtual FOnStageMonitorSessionSaved& OnStageMonitorSessionSaved() override;`
- L56 _private prototype_ `void OnLoadSessionCompletedTask(const TSharedPtr<FStageMonitorSession>& InLoadedSession, const FString& FileName, const FString& InError);` — Scheduled on gamethread by the anythread async task when loading was completed
- L59 _private prototype_ `void OnSaveSessionCompletedTask(const FString& FileName, const FString& InError);` — Scheduled on gamethread by the anythread async task when saving was completed
- L62 _private prototype_ `void LoadSessionTask_AnyThread(const FString& FileName);` — Task used to load session from file and populate it from the json data
- L65 _private prototype_ `void SaveSessionTask_AnyThread(const FString& FileName, const FSavingTaskData& TaskData);` — Task used to save current session to a file
- L68 _private prototype_ `UScriptStruct* FindStructFromName_AnyThread(FName TypeName);` — Finds a static struct from the specified FName.
- L73 _private member_ `TSharedPtr<FStageMonitorSession> ActiveSession;` — Live session. Used by the monitor to dump new activities
- L76 _private member_ `TSharedPtr<FStageMonitorSession> LoadedSession;` — Imported session used to be displayed in UI
- L79 _private member_ `TMap<FName, UScriptStruct*> TypeCache;` — Cached static structs per FName to accelerate looking for message type
- L82 _private member_ `bool bIsSaving = false;` — Whether we are saving. Flagged before launching the async task and cleared on completion. Always on gamethread
- L85 _private member_ `bool bIsLoading = false;` — Whether we are loading. Flagged before launching the async task and cleared on completion. Always on gamethread
- L88 _private member_ `FOnStageMonitorSessionLoaded OnStageMonitorSessionLoadedDelegate;` — Delegate triggered when the requested session was loaded
- L91 _private member_ `FOnStageMonitorSessionSaved OnStageMonitorSessionSavedDelegate;` — Delegate triggered when the requested session was loaded

#### struct `FStageMonitorSessionManager::FSavingTaskData`  
`struct FSavingTaskData`  
_L47-53_
- desc: Internal struct meant to pass data from save request to async task
- L49 _public member_ `FStageDataExportSettings Settings;`
- L50 _public member_ `TArray<FStageSessionProviderEntry> Providers;`
- L51 _public member_ `TMap<FGuid, FGuid> IdentifierMapping;`
- L52 _public member_ `TArray<TSharedPtr<FStageDataEntry>> Entries;`

### `Plugins/VirtualProduction/StageMonitoring/Source/StageMonitor/Public/IStageMonitor.h` (Public)


#### class `IStageMonitor`  
`class IStageMonitor`  
_L16-26_
- desc: Interface for the stage monitor. Users can get the instance from the stage monitor module
- L20 _public function_ `virtual ~IStageMonitor()`
- L25 _public prototype_ `virtual bool IsActive() const = 0;` — Returns true if monitor is actively listening for activities

### `Plugins/VirtualProduction/StageMonitoring/Source/StageMonitor/Public/IStageMonitorModule.h` (Public)


#### class `IStageMonitorModule`  
`class IStageMonitorModule : public IModuleInterface`  
_L14-56_
- inherits: `IModuleInterface`
- L23 _public function_ `static inline IStageMonitorModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L33 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() during shutdown if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L41 _public prototype_ `virtual IStageMonitor& GetStageMonitor() = 0;` — Returns the stage monitor instance
- L46 _public prototype_ `virtual IStageMonitorSessionManager& GetStageMonitorSessionManager() = 0;` — Returns the stage monitor session manager
- L51 _public prototype_ `virtual void EnableMonitor(bool bEnable) = 0;` — Enable or disables StageMonitor
- L55 _private member_ `static const FName ModuleName;`

### `Plugins/VirtualProduction/StageMonitoring/Source/StageMonitor/Public/IStageMonitorSession.h` (Public)


#### enum `EGetProviderFlags`  
`enum class EGetProviderFlags`  
_L17-39_
- desc: Flags controlling the behavior of struct serializer backends.
- L22 _public enumerator_ `None = 0` — Nothing special
- L28 _public enumerator_ `UseClearedProviders = 1 << 0` — Include cleared provider in the search @note This is required to correctly support localization
- L33 _public enumerator_ `UseIdentifierMapping = 1 << 1` — Use Identifier mapping if Identifier isn't found in list.
- L38 _public enumerator_ `Default = UseClearedProviders | UseIdentifierMapping` — Default.

#### struct `FStageSessionProviderEntry`  
`struct FStageSessionProviderEntry`  
_L48-74_
- reflection: `USTRUCT()`
- desc: Entry corresponding to a provider we are monitoring Contains information related to the provider so we can communicate with it and more dynamic information like last communication received
- L53 _public prototype_ `FStageSessionProviderEntry() = default;`
- L55 _public function_ `bool operator==(const FStageSessionProviderEntry& Other) const`
- L56 _public function_ `bool operator!=(const FStageSessionProviderEntry& Other) const`
- L60 _public member_ `FGuid Identifier;` — `UPROPERTY()` — Identifier of this provider
- L64 _public member_ `FStageInstanceDescriptor Descriptor;` — `UPROPERTY()` — Detailed descriptor
- L67 _public member_ `FMessageAddress Address;` — Address of this provider
- L70 _public member_ `EStageDataProviderState State = EStageDataProviderState::Closed;` — State of this provider based on message reception
- L73 _public member_ `double LastReceivedMessageTime = 0.0;` — Timestamp when last message was received based on FApp::GetCurrentTime

#### struct `FStageDataEntry`  
`struct FStageDataEntry`  
_L79-83_
- desc: Data entry containing data received from a provider
- L81 _public member_ `TSharedPtr<FStructOnScope> Data;`
- L82 _public member_ `double MessageTime = 0.0;`

#### class `IStageMonitorSession`  
`class IStageMonitorSession`  
_L89-214_
- desc: Interface describing a session of data received by the monitor Can be exported and reimported for future analysis
- L93 _public function_ `virtual ~IStageMonitorSession()`
- L98 _public prototype_ `virtual void HandleDiscoveredProvider(const FGuid& Identifier, const FStageInstanceDescriptor& Descriptor, const FMessageAddress& Address) = 0;` — Handles discovery response of a provider. Might already be found, unresponsive or a new one
- L104 _public prototype_ `virtual bool AddProvider(const FGuid& Identifier, const FStageInstanceDescriptor& Descriptor, const FMessageAddress& Address) = 0;` — Adds a new provider to the ones we're handling data for. Returns true if a provider was added
- L107 _public prototype_ `virtual TArray<FMessageAddress> GetProvidersAddress() const = 0;` — Returns the addresses of the providers currently monitored
- L112 _public prototype_ `virtual void SetProviderState(const FGuid& Identifier, EStageDataProviderState State) = 0;` — Changes a provider's monitoring state
- L117 _public prototype_ `virtual void AddProviderMessage(UScriptStruct* Type, const FStageProviderMessage* MessageData) = 0;` — Adds a message to the session
- L122 _public prototype_ `virtual TConstArrayView<FStageSessionProviderEntry> GetProviders() const = 0;` — Get all providers that have been connected to the monitor
- L127 _public prototype_ `virtual TConstArrayView<FStageSessionProviderEntry> GetClearedProviders() const = 0;` — Get providers that were connected at some point but got cleared
- L132 _public prototype_ `virtual bool GetProvider(const FGuid& Identifier, FStageSessionProviderEntry& OutProviderEntry, EGetProviderFlags Flags = EGetProviderFlags::Default) const = 0;` — Get ProviderEntry associated to an identifier
- L137 _public prototype_ `virtual void ClearAll() = 0;` — Clear every activities of the session
- L142 _public prototype_ `virtual void ClearUnresponsiveProviders() = 0;` — Clear unresponsive providers from active list
- L147 _public prototype_ `virtual void GetAllEntries(TArray<TSharedPtr<FStageDataEntry>>& OutEntries) = 0;` — Returns all entries that have been received
- L152 _public prototype_ `virtual TSharedPtr<FStageDataEntry> GetLatest(const FGuid& Identifier, UScriptStruct* Type) = 0;` — Returns the state of the desired provider
- L157 _public prototype_ `virtual EStageDataProviderState GetProviderState(const FGuid& Identifier) = 0;` — Returns the state of the desired provider
- L162 _public prototype_ `virtual bool IsStageInCriticalState() const = 0;` — Returns true if stage monitor currently in critical state (i.e. recording)
- L167 _public prototype_ `virtual bool IsTimePartOfCriticalState(double TimeInSeconds) const = 0;` — Returns true if the given time is part of a critical state time range.
- L172 _public prototype_ `virtual FName GetCurrentCriticalStateSource() const = 0;` — Returns Source name of the current critical state. Returns None if not active
- L177 _public prototype_ `virtual TArray<FName> GetCriticalStateHistorySources() const = 0;` — Returns a list of all sources that triggered a critical state
- L183 _public prototype_ `virtual TArray<FName> GetCriticalStateSources(double TimeInSeconds) const = 0;` — Returns a list of all sources that triggered a critical state during TimeInSeconds. If provided time is not part of a critical state, returned array will be empty
- L188 _public prototype_ `virtual FString GetSessionName() const = 0;` — Returns the name of that session.
- L194 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnStageSessionNewDataReceived, TSharedPtr<FStageDataEntry> );` — Callback triggered when new data has been added to the session
- L195 _public prototype_ `virtual FOnStageSessionNewDataReceived& OnStageSessionNewDataReceived() = 0;`
- L200 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnStageSessionDataCleared);` — Callback triggered when data from the session has been cleared
- L201 _public prototype_ `virtual FOnStageSessionDataCleared& OnStageSessionDataCleared() = 0;`
- L206 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnStageDataProviderListChanged);` — Callback triggered when provider list changed
- L207 _public prototype_ `virtual FOnStageDataProviderListChanged& OnStageDataProviderListChanged() = 0;`
- L212 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnStageDataProviderStateChanged, const FGuid& , EStageDataProviderState );` — Callback triggered when provider state has changed
- L213 _public prototype_ `virtual FOnStageDataProviderStateChanged& OnStageDataProviderStateChanged() = 0;`

#### Free symbols / members of external scopes

- L40 _prototype_ `ENUM_CLASS_FLAGS(EGetProviderFlags);`
- L194 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnStageSessionNewDataReceived, TSharedPtr<FStageDataEntry> );` — Callback triggered when new data has been added to the session
- L200 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnStageSessionDataCleared);` — Callback triggered when data from the session has been cleared
- L206 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnStageDataProviderListChanged);` — Callback triggered when provider list changed
- L212 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnStageDataProviderStateChanged, const FGuid& , EStageDataProviderState );` — Callback triggered when provider state has changed

### `Plugins/VirtualProduction/StageMonitoring/Source/StageMonitor/Public/IStageMonitorSessionManager.h` (Public)


#### class `IStageMonitorSessionManager`  
`class IStageMonitorSessionManager`  
_L9-48_
- L13 _public prototype_ `virtual ~IStageMonitorSessionManager() = default;`
- L17 _public prototype_ `virtual TSharedPtr<IStageMonitorSession> CreateSession() = 0;` — Creates a new active session. If one is already present, it will return an invalid session
- L23 _public prototype_ `virtual bool LoadSession(const FString& FileName) = 0;` — Request to load a session. Returns true if loading was effectively requested Loading will be done async and a callback. Listen for OnStageMonitorSessionLoaded to know when it's done
- L29 _public prototype_ `virtual bool SaveSession(const FString& FileName) = 0;` — Request to save a session. Returns true if saving was effectively requested Loading will be done async and a callback. Listen for OnStageMonitorSessionSaved to know when it's done
- L32 _public prototype_ `virtual TSharedPtr<IStageMonitorSession> GetActiveSession() = 0;` — Returns the current active (live) session
- L35 _public prototype_ `virtual TSharedPtr<IStageMonitorSession> GetLoadedSession() = 0;` — Returns the loaded session
- L40 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnStageMonitorSessionLoaded);` — Callback triggered when a requested session was loaded
- L41 _public prototype_ `virtual FOnStageMonitorSessionLoaded& OnStageMonitorSessionLoaded() = 0;`
- L46 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnStageMonitorSessionSaved);` — Callback triggered when a requested session was saved
- L47 _public prototype_ `virtual FOnStageMonitorSessionSaved& OnStageMonitorSessionSaved() = 0;`

#### Free symbols / members of external scopes

- L40 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnStageMonitorSessionLoaded);` — Callback triggered when a requested session was loaded
- L46 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnStageMonitorSessionSaved);` — Callback triggered when a requested session was saved
