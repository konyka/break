# Plugins / Qos

- module root: `Plugins/Online/OnlineFramework/Source/Qos`
- headers: 8; symbols: 311
- symbol kinds: class=8, delegate=7, enum=4, enumerator=15, function=38, macro=11, member=105, prototype=113, struct=10
- DynamicallyLoadedModuleNames: Analytics, AnalyticsET
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, Icmp, Json, OnlineSubsystem, OnlineSubsystemUtils
- PrivateIncludePathModuleNames: Analytics

### `Plugins/Online/OnlineFramework/Source/Qos/Private/QosEvaluator.h` (Private)


#### struct `FQosParams`  
`struct FQosParams`  
_L21-27_
- desc: Input parameters to start a qos ping check
- L24 _public member_ `int32 NumTestsPerRegion;` — Number of ping requests per region
- L26 _public member_ `float Timeout;` — Amount of time to wait for each request

#### class `UQosEvaluator`  
`class UQosEvaluator : public UObject`  
_L52-175_
- reflection: `UCLASS(MinimalAPI, config = Engine)`
- inherits: `UObject`
- desc: Evaluates QoS metrics to determine the best datacenter under current conditions Additionally capable of generically pinging an array of servers that have a QosBeaconHost active
- L71 _public prototype_ `void FindDatacenters(const FQosParams& InParams, const TArray<FQosRegionInfo>& InRegions, const TArray<FQosDatacenterInfo>& InDatacenters, const FOnQosSearchComplete& InCompletionDelegate);` — Find all the advertised datacenters and begin the process of evaluating ping results Will return the default datacenter in the event of failure or no advertised datacenters @param InParams parameters defining the @param InRegions array of regions to query @param InDatacenters array of datacenters to query @param InCompletionDelegate delegate to fire when a datacenter choice has been made
- L78 _public function_ `bool IsActive() const` — Is a QoS operation active @return true if QoS is active, false otherwise
- L83 _public prototype_ `void Cancel();` — Cancel the current QoS operation at the earliest opportunity
- L85 _public prototype_ `void SetWorld(UWorld* InWorld);`
- L87 _public function_ `bool IsCanceled() const`
- L97 _protected prototype_ `bool PingRegionServers(const FQosParams& InParams, const FOnQosSearchComplete& InQosSearchCompleteDelegate);` — Use the udp ping code to ping known servers @param InParams parameters defining the request @param InQosSearchCompleteDelegate delegate to fire when all regions have completed their tests
- L101 _private prototype_ `void ResetDatacenterPingResults();`
- L103 _private prototype_ `static TArray<FIcmpTarget>& PopulatePingRequestList(TArray<FIcmpTarget>& OutTargets, const TArray<FDatacenterQosInstance>& Datacenters, int32 NumTestsPerRegion);`
- L106 _private prototype_ `static TArray<FIcmpTarget>& PopulatePingRequestList(TArray<FIcmpTarget>& OutTargets, const FQosDatacenterInfo& DatacenterDefinition, int32 NumTestsPerRegion);`
- L109 _private prototype_ `static FDatacenterQosInstance *const FindDatacenterByAddress(TArray<FDatacenterQosInstance>& Datacenters, const FString& ServerAddress, int32 ServerPort);`
- L112 _private prototype_ `void OnEchoManyCompleted(FIcmpEchoManyCompleteResult FinalResult, int32 NumTestsPerRegion, const FOnQosSearchComplete& InQosSearchCompleteDelegate);`
- L117 _private member_ `TWeakObjectPtr<UWorld> ParentWorld;` — Reference to external UWorld
- L119 _private member_ `FOnQosPingEvalComplete OnQosPingEvalComplete;`
- L122 _private member_ `double StartTimestamp;` — Start time of total test
- L125 _private member_ `bool bInProgress;` — `UPROPERTY()` — A QoS operation is in progress
- L128 _private member_ `bool bCancelOperation;` — `UPROPERTY()` — Should cancel occur at the next available opportunity
- L132 _private member_ `TArray<FDatacenterQosInstance> Datacenters;` — `UPROPERTY(Transient)` — Array of datacenters currently being evaluated
- L137 _private prototype_ `bool AreAllRegionsComplete();` — @return true if all ping requests have completed (new method)
- L144 _private prototype_ `void CalculatePingAverages(int32 TimeToDiscount = 0);` — Take all found ping results and process them before consumption at higher levels @param TimeToDiscount amount of time to subtract from calculation to compensate for external factors (frame rate, etc)
- L152 _public prototype_ `void SetAnalyticsProvider(TSharedPtr<IAnalyticsProvider> InAnalyticsProvider);`
- L156 _private prototype_ `void StartAnalytics();`
- L157 _private prototype_ `void EndAnalytics(EQosCompletionResult CompletionResult);`
- L160 _private member_ `TSharedPtr<IAnalyticsProvider> AnalyticsProvider;` — Reference to the provider to submit data to
- L162 _private member_ `TSharedPtr<FQosDatacenterStats> QosStats;` — Stats related to these operations
- L171 _private prototype_ `UWorld* GetWorld() const;` — Quick access to the current world
- L174 _private prototype_ `FTimerManager& GetWorldTimerManager() const;` — Quick access to the world timer manager

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API QOS_API`
- L34 _delegate_ `DECLARE_DELEGATE_OneParam(FOnQosPingEvalComplete, EQosCompletionResult );` — Delegate triggered when an evaluation of ping for all servers in a search query have completed @param Result the ping operation result
- L34 _prototype_ `DECLARE_DELEGATE_OneParam(FOnQosPingEvalComplete, EQosCompletionResult );` — Delegate triggered when an evaluation of ping for all servers in a search query have completed @param Result the ping operation result
- L44 _delegate_ `DECLARE_DELEGATE_FourParams(FOnQosSearchComplete, EQosCompletionResult , const TArray<FDatacenterQosInstance>& , FString* , FString* );` — Delegate triggered when all QoS search results have been investigated @param Result the QoS operation result @param DatacenterInstances The per-datacenter ping information @param OutSelectedRegion If present target will be set to the ReionManagers recommended region (may differ from actual best) @param OutSelectedSubRegion If present target will be set to the ReionManagers recommended sub region (may differ from actual best)
- L44 _prototype_ `DECLARE_DELEGATE_FourParams(FOnQosSearchComplete, EQosCompletionResult , const TArray<FDatacenterQosInstance>& , FString* , FString* );` — Delegate triggered when all QoS search results have been investigated @param Result the QoS operation result @param DatacenterInstances The per-datacenter ping information @param OutSelectedRegion If present target will be set to the ReionManagers recommended region (may differ from actual best) @param OutSelectedSubRegion If present target will be set to the ReionManagers recommended sub region (may differ from actual best)
- L177 _function_ `inline const TCHAR* ToString(EQosDatacenterResult Result)`
- L198 _function_ `inline const TCHAR* ToString(EQosCompletionResult Result)`

### `Plugins/Online/OnlineFramework/Source/Qos/Private/QosStats.h` (Private)


#### enum `EDatacenterResultType`  
`enum class EDatacenterResultType :uint8`  
_L14-26_
- L17 _public enumerator_ `Normal` — Normal flow result
- L19 _public enumerator_ `Cached` — Using previously cached value
- L21 _public enumerator_ `Forced` — Using forced
- L23 _public enumerator_ `Default` — Using forced default
- L25 _public enumerator_ `Failure` — Failure to complete

#### class `FQosDatacenterStats`  
`class FQosDatacenterStats`  
_L61-273_
- desc: Datacenter determination stats
- L156 _private member_ `static const FString QosStats_DatacenterEvent;` — Events
- L159 _private member_ `static const FString QosStats_SessionId;` — Common attribution
- L160 _private member_ `static const FString QosStats_Version;`
- L163 _private member_ `static const FString QosStats_Timestamp;` — Header stats
- L164 _private member_ `static const FString QosStats_TotalTime;`
- L167 _private member_ `static const FString QosStats_DeterminationType;` — Qos stats
- L168 _private member_ `static const FString QosStats_NumRegions;`
- L169 _private member_ `static const FString QosStats_RegionDetails;`
- L170 _private member_ `static const FString QosStats_NumResults;`
- L171 _private member_ `static const FString QosStats_NumSuccessCount;`
- L172 _private member_ `static const FString QosStats_NetworkType;`
- L173 _private member_ `static const FString QosStats_BestRegionId;`
- L174 _private member_ `static const FString QosStats_BestRegionPing;`
- L175 _private member_ `static const FString QosStats_BestEndpointId;`
- L176 _private member_ `static const FString QosStats_BestEndpointPing;`
- L177 _private member_ `static const FString QosStats_ChosenRegionId;`
- L178 _private member_ `static const FString QosStats_ChosenSubRegionId;`
- L179 _private member_ `static const FString QosStats_ChosenSubRegionPing;`
- L182 _private member_ `int32 StatsVersion;` — Version of the stats for separation
- L185 _private member_ `FQosStats_CompletePass QosData;` — Container of an entire search process
- L188 _private member_ `bool bAnalyticsInProgress;` — Analytics in progress
- L195 _private prototype_ `void StartTimer(FQosStats_Timer& Timer);` — Start the timer for a given stats container @param Timer Timer to start
- L202 _private prototype_ `void StopTimer(FQosStats_Timer& Timer);` — Stops the timer for a given stats container @param Timer Timer to stop
- L207 _private prototype_ `void Finalize();` — Finalize all the data, stopping timers, etc
- L215 _private prototype_ `void ParseQosResults(TSharedPtr<IAnalyticsProvider>& AnalyticsProvider, FGuid& SessionId);` — Parse an entire search, adding its data to the recorded event @param AnalyticsProvider provider recording the event @param SessionId unique id for the qos event
- L219 _public prototype_ `FQosDatacenterStats();`
- L220 _public prototype_ `virtual ~FQosDatacenterStats() = default;`
- L225 _public prototype_ `void StartQosPass();` — Start a Qos search pass
- L233 _public prototype_ `void RecordRegionInfo(const FDatacenterQosInstance& RegionInfo, int32 NumResults);` — Record a new region @param RegionInfo info obtained about a region @param NumResults num results considered
- L243 _public prototype_ `void RecordQosAttempt(const FString& Region, const FString& OwnerId, int32 PingInMs, bool bSuccess);` — Record a single ping attempt @param Region region of the server @param OwnerId the owner of the server (ip address) @param PingInMs ping to the server @param bSuccess was the attempt successful
- L250 _public prototype_ `void EndQosPass(EDatacenterResultType Result);` — End recording of a Qos determination @param Result results of the qos pass
- L257 _public prototype_ `void SetChosenRegion(FString&& Region);` — Set the chosen region from Qos Evaluation (may differ from the fastest/best based on rules) @param Region string region code of chosen region
- L264 _public prototype_ `void SetChosenSubRegion(FString && SubRegion);` — Set the chosen SubRegion from Qos Evaluation (may differ from the fastest/best based on rules) @param Region string SubRegion code of chosen region
- L271 _public prototype_ `void Upload(TSharedPtr<IAnalyticsProvider>& AnalyticsProvider);` — Record previously saved stats to an analytics provider @param AnalyticsProvider provider to record stats to

#### struct `FQosDatacenterStats::FQosStats_Timer`  
`struct FQosStats_Timer`  
_L65-76_
- L68 _public member_ `double MSecs;` — Time in ms captured
- L70 _public member_ `bool bInProgress;` — Is this timer running
- L72 _public function_ `FQosStats_Timer() : MSecs(0.0), bInProgress(false)`

#### class `FQosDatacenterStats::FQosStats_RegionInfo`  
`class FQosStats_RegionInfo : public FJsonSerializable`  
_L78-106_
- inherits: `FJsonSerializable`
- L82 _public member_ `FString RegionId;` — Region designation
- L84 _public member_ `FString ParentRegionId;` — Parent region
- L86 _public member_ `int32 NumResults;` — Number of Qos servers pinged
- L88 _public member_ `int32 AvgPing;` — Average ping across all results
- L90 _public member_ `bool bUsable;` — Is the region usable by the player
- L91 _public function_ `FQosStats_RegionInfo() : RegionId(TEXT("Unknown")) , ParentRegionId(TEXT("Unknown")) , NumResults(0) , AvgPing(UNREACHABLE_PING) , bUsable(false)`

#### struct `FQosDatacenterStats::FQosStats_QosSearchResult`  
`struct FQosStats_QosSearchResult`  
_L109-124_
- desc: Stats representation of a single Qos search result
- L112 _public member_ `FString OwnerId;` — Owner of the session
- L114 _public member_ `FString DatacenterId;` — Datacenter Id
- L116 _public member_ `int32 PingInMs;` — Ping time
- L118 _public member_ `bool bIsValid;` — Is this result valid
- L120 _public function_ `FQosStats_QosSearchResult() : PingInMs(0), bIsValid(false)`

#### struct `FQosDatacenterStats::FQosStats_CompletePass`  
`struct FQosStats_CompletePass`  
_L126-153_
- L129 _public member_ `FString Timestamp;` — Time of the search
- L131 _public member_ `EDatacenterResultType DeterminationType;` — Way the datacenter was chosen
- L133 _public member_ `FQosStats_Timer SearchTime;` — Time in ms it took to find the search results (exclusive)
- L135 _public member_ `TArray<FQosStats_RegionInfo> Regions;` — Array of region information
- L137 _public member_ `FString RulesChosenRegion;` — name for the region chosen based on rules
- L139 _public member_ `FString RulesChosenSubRegion;` — name for the sub region chosen based on rules
- L141 _public member_ `int32 NumTotalSearches;` — Number of search results tested
- L143 _public member_ `int32 NumSuccessAttempts;` — Number of successful search results
- L145 _public member_ `TArray<FQosStats_QosSearchResult> SearchResults;` — Array of search result details found this pass
- L147 _public function_ `FQosStats_CompletePass() : DeterminationType(EDatacenterResultType::Failure), NumTotalSearches(0), NumSuccessAttempts(0)`
- L152 _public prototype_ `~FQosStats_CompletePass() = default;`

#### Free symbols / members of external scopes

- L29 _function_ `inline const TCHAR* ToString(EDatacenterResultType ResultType)` — @return the stringified version of the enum passed in

### `Plugins/Online/OnlineFramework/Source/Qos/Public/QosBeaconClient.h` (Public)


#### enum `EQosResponseType`  
`enum class EQosResponseType : uint8`  
_L16-24_
- reflection: `UENUM()`
- desc: Types of responses that can come back from the beacon
- L19 _public enumerator_ `NoResponse` — Failed to connect to Qos endpoint
- L21 _public enumerator_ `Success` — Response received from the Qos host
- L23 _public enumerator_ `Failure` — Some kind of failure

#### class `AQosBeaconClient`  
`class AQosBeaconClient : public AOnlineBeaconClient`  
_L38-87_
- reflection: `UCLASS(MinimalAPI, transient, config=Engine)`
- inherits: `AOnlineBeaconClient`
- desc: A beacon client used for quality timings to a specified session
- L43 _private prototype_ `virtual void OnConnected() override;`
- L49 _private prototype_ `virtual void SendQosRequest(const FOnlineSessionSearchResult& DesiredHost);` — Initiate a Qos request with a given server
- L56 _private function_ `FOnQosRequestComplete& OnQosRequestComplete()` — Delegate triggered when a response from the Qos beacon has been received @return QosResponse response from the server
- L61 _protected member_ `double ConnectionStartTime;` — Time connection was established
- L63 _protected member_ `double QosStartTime;` — Time the Qos started
- L65 _protected member_ `FString DestSessionId;` — Session Id of the destination host
- L67 _protected member_ `bool bPendingQosRequest;` — Is there a Qos request in flight
- L70 _protected member_ `FOnQosRequestComplete QosRequestComplete;` — Delegate for Qos request responses
- L78 _protected prototype_ `virtual void ServerQosRequest(const FString& InSessionId);` — `UFUNCTION(server, reliable, WithValidation)` — Contact the server with a Qos request and begin timing @param InSessionId reference session id to make sure the session is the correct one
- L84 _protected prototype_ `virtual void ClientQosResponse(EQosResponseType Response);` — `UFUNCTION(client, reliable)` — Response from the host session after making a Qos request

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API QOS_API`
- L32 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnQosRequestComplete, EQosResponseType , int32 );` — Delegate triggered when a response from the Qos beacon has been received @param QosResponse response from the server @param ResponseTime time to respond in ms
- L32 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnQosRequestComplete, EQosResponseType , int32 );` — Delegate triggered when a response from the Qos beacon has been received @param QosResponse response from the server @param ResponseTime time to respond in ms

### `Plugins/Online/OnlineFramework/Source/Qos/Public/QosBeaconHost.h` (Public)


#### class `AQosBeaconHost`  
`class AQosBeaconHost : public AOnlineBeaconHostObject`  
_L16-46_
- reflection: `UCLASS(MinimalAPI, transient, config=Engine)`
- inherits: `AOnlineBeaconHostObject`
- desc: A beacon host listening for Qos requests from a potential client
- L23 _private prototype_ `bool Init(FName InSessionName);`
- L31 _private prototype_ `void ProcessQosRequest(AQosBeaconClient* Client, const FString& SessionId);` — Handle a single Qos request received from an incoming client @param Client client beacon making the request @param SessionId id of the session that is being checked
- L32 _private prototype_ `bool DoesSessionMatch(const FString& SessionId) const;`
- L37 _private prototype_ `void DumpState() const;` — Output current state of beacon to log
- L42 _protected member_ `FName SessionName;` — Name of session this beacon is associated with
- L45 _protected member_ `int32 NumQosRequests;` — Running total of Qos requests received since the beacon was created

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API QOS_API`

### `Plugins/Online/OnlineFramework/Source/Qos/Public/QosInterface.h` (Public)


#### class `FQosInterface`  
`class FQosInterface : public TSharedFromThis<FQosInterface>, public FGCObject`  
_L19-157_
- inherits: `TSharedFromThis<FQosInterface>,FGCObject`
- desc: Main Qos interface for actions related to server quality of service
- L26 _public prototype_ `static TSharedRef<FQosInterface> Get();` — Get the interface singleton
- L31 _public prototype_ `bool Init();` — Re-initialize our FQosRegionManager instance
- L36 _public prototype_ `void BeginQosEvaluation(UWorld* World, const TSharedPtr<IAnalyticsProvider>& AnalyticsProvider, const FSimpleDelegate& OnComplete);` — Start running the async QoS evaluation
- L38 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnQosEvalCompleteDelegate);`
- L43 _public prototype_ `FOnQosEvalCompleteDelegate& OnQosEvalComplete();` — Get the delegate that is invoked when the current/next QoS evaluation completes.
- L48 _public prototype_ `bool IsQosEvaluationInProgress() const;` — Returns true if Qos is in the process of being evaluated
- L59 _public prototype_ `FString GetRegionId() const;` — Get the region ID for this instance, checking ini and commandline overrides. Dedicated servers will have this value specified on the commandline Clients pull this value from the settings (or command line) and do a ping test to determine if the setting is viable. @return the current region identifier
- L66 _public prototype_ `FString GetBestRegion() const;` — Get the region ID with the current best ping time, checking ini and commandline overrides. @return the default region identifier
- L69 _public prototype_ `bool AllRegionsFound() const;` — @return true if a reasonable enough number of results were returned from all known regions, false otherwise
- L76 _public prototype_ `const TArray<FRegionQosInstance>& GetRegionOptions() const;` — Get the list of regions that the client can choose from (returned from search and must meet min ping requirements) If this list is empty, the client cannot play.
- L84 _public prototype_ `void GetSubregionPreferences(const FString& RegionId, TArray<FString>& OutSubregions) const;` — Get a sorted list of subregions within a region @param RegionId region of interest @param OutSubregions list of subregions in sorted order
- L89 _public prototype_ `TMap<FString, int64> GetAllSubregionPingsMap() const;` — @return a map of subregion to the computed AvgPing for that subregion
- L94 _public prototype_ `bool IsUsableRegion(const FString& InRegionId) const;` — @return true if this is a usable region, false otherwise
- L99 _public prototype_ `bool SetSelectedRegion(const FString& RegionId);` — Try to set the selected region ID (must be present in GetRegionOptions)
- L102 _public prototype_ `void ClearSelectedRegion();` — Clear the region to nothing, used for logging out
- L107 _public prototype_ `void ForceSelectRegion(const FString& RegionId);` — Force the selected region creating a fake RegionOption if necessary
- L116 _public prototype_ `static FString GetDatacenterId();` — Get the datacenter id for this instance, checking ini and commandline overrides This is only relevant for dedicated servers (so they can advertise). Client does not search on this in any way @return the default datacenter identifier
- L123 _public prototype_ `static FString GetAdvertisedSubregionId();` — Get the subregion id for this instance, checking ini and commandline overrides This is only relevant for dedicated servers (so they can advertise). Client does not search on this (but may choose to prioritize results later)
- L128 _public prototype_ `void DumpRegionStats();` — Debug output for current region / datacenter information
- L133 _public prototype_ `void RegisterQoSSettingsChangedDelegate(const FSimpleDelegate& OnQoSSettingsChanged);` — Register a delegate to be called when QoS settings have changed.
- L138 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnQosRegionIdChanged, const FString& , const FString& );` — Delegate that fires whenever the current QoS region ID changes.
- L139 _public prototype_ `FOnQosRegionIdChanged& OnQosRegionIdChanged();`
- L144 _protected prototype_ `FQosInterface();`
- L147 _protected prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L148 _protected function_ `virtual FString GetReferencerName() const override`
- L156 _private member_ `TObjectPtr<UQosRegionManager> RegionManager;` — Reference to the evaluator for making datacenter determinations

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API QOS_API`
- L14 _macro_ `#define NO_REGION TEXT("NONE")`
- L38 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnQosEvalCompleteDelegate);`
- L138 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnQosRegionIdChanged, const FString& , const FString& );` — Delegate that fires whenever the current QoS region ID changes.

### `Plugins/Online/OnlineFramework/Source/Qos/Public/QosModule.h` (Public)


#### class `FQosModule`  
`class FQosModule : public IModuleInterface, public FSelfRegisteringExec`  
_L17-71_
- inherits: `IModuleInterface,FSelfRegisteringExec`
- desc: Module for QoS service utilities
- L29 _public function_ `static inline FQosModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L39 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L47 _public prototype_ `TSharedRef<FQosInterface> GetQosInterface();` — Get the interface singleton
- L51 _protected prototype_ `virtual bool Exec_Runtime(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;` — FSelfRegisteringExec
- L54 _private member_ `TSharedPtr<FQosInterface> QosInterface;`
- L64 _private prototype_ `virtual void StartupModule() override;` — Called when voice module is loaded Initialize platform specific parts of template handling
- L70 _private prototype_ `virtual void ShutdownModule() override;` — Called when voice module is unloaded Shutdown platform specific parts of template handling

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API QOS_API`
- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogQos, Display, All);` — Logging related to parties

### `Plugins/Online/OnlineFramework/Source/Qos/Public/QosPackage.h` (Public)


#### Free symbols / members of external scopes

- L10 _macro_ `#define PACKAGE_SCOPE public`
- L12 _macro_ `#define PACKAGE_SCOPE protected`

### `Plugins/Online/OnlineFramework/Source/Qos/Public/QosRegionManager.h` (Public)


#### enum `EQosDatacenterResult`  
`enum class EQosDatacenterResult : uint8`  
_L20-28_
- reflection: `UENUM()`
- desc: Enum for single region QoS return codes
- L23 _public enumerator_ `Invalid` — Incomplete, invalid result
- L25 _public enumerator_ `Success` — QoS operation was successful
- L27 _public enumerator_ `Incomplete` — QoS operation with one or more ping failures

#### enum `EQosCompletionResult`  
`enum class EQosCompletionResult : uint8`  
_L43-53_
- reflection: `UENUM()`
- desc: Enum for possible QoS return codes
- L46 _public enumerator_ `Invalid` — Incomplete, invalid result
- L48 _public enumerator_ `Success` — QoS operation was successful
- L50 _public enumerator_ `Failure` — QoS operation ended in failure
- L52 _public enumerator_ `Canceled` — QoS operation was canceled

#### struct `FQosSubspaceComparisonParams`  
`struct FQosSubspaceComparisonParams`  
_L73-131_
- reflection: `USTRUCT()`
- desc: Parameters to control the rules-based comparison of subspace vs non-subspace datacenter QoS results. @see FDatacenterQosInstance::IsNonSubspaceRecommended(const FDatacenterQosInstance&, const FDatacenterQosInstance&, const FQosSubspaceComparisonParams&)
- L83 _public member_ `int32 MaxNonSubspacePingMs;` — `UPROPERTY()` — Maximum allowed ping of the non-subspace. If greater than this value, it is too slow, so fails to qualify. Set to zero or less to disable checks against this field.
- L91 _public member_ `int32 MinSubspacePingMs;` — `UPROPERTY()` — Minimum allowed ping of the subspace. If below this value, it should not be overridden by the non-subspace. Set to zero or less to disable checks against this field.
- L99 _public member_ `int32 ConstantMaxToleranceMs;` — `UPROPERTY()` — Maximum allowed difference between the subspace and non-subspace's ping values in milliseconds. If greater than this value, the non-subspace is too slow, so fails to qualify. Set to zero or less to disable checks against this field.
- L109 _public member_ `float ScaledMaxTolerancePct;` — `UPROPERTY()` — Maximum allowed difference between the subspace and non-subspace's ping values, which scales as a proportion of the non-subspace's ping, so will differ between comparisons when sorting a single list of datacenters. If greater than the scaled difference, the non-subspace is too slow, so fails to qualify. Set to zero or less to disable checks against this field.
- L111 _public function_ `FQosSubspaceComparisonParams() : MaxNonSubspacePingMs(0) , MinSubspacePingMs(0) , ConstantMaxToleranceMs(0) , ScaledMaxTolerancePct(0.0f)`
- L119 _public function_ `FQosSubspaceComparisonParams(int32 InMaxNonSubspacePingMs, int32 InMinSubspacePingMs, int32 InConstantMaxToleranceMs, float InScaledMaxTolerancePct) : MaxNonSubspacePingMs(InMaxNonSubspacePingMs) , MinSubspacePingMs(InMinSubspacePingMs) , ConstantMaxToleranceMs(InConstantMaxToleranceMs) , ScaledMaxTolerancePct(InScaledMaxTolerancePct)`
- L127 _public function_ `float CalcScaledMaxToleranceMs(int32 PingMs) const`

#### struct `FQosPingServerInfo`  
`struct FQosPingServerInfo`  
_L137-147_
- reflection: `USTRUCT()`
- desc: Individual ping server details
- L143 _public member_ `FString Address;` — `UPROPERTY()` — Address of server
- L146 _public member_ `int32 Port = 0;` — `UPROPERTY()` — Port of server

#### struct `FQosDatacenterInfo`  
`struct FQosDatacenterInfo`  
_L153-194_
- reflection: `USTRUCT()`
- desc: Metadata about datacenters that can be queried
- L159 _public member_ `FString Id;` — `UPROPERTY()` — Id for this datacenter
- L162 _public member_ `FString RegionId;` — `UPROPERTY()` — Parent Region
- L165 _public member_ `bool bEnabled;` — `UPROPERTY()` — Is this region tested (only valid if region is enabled)
- L168 _public member_ `TArray<FQosPingServerInfo> Servers;` — `UPROPERTY()` — Addresses of ping servers
- L170 _public function_ `FQosDatacenterInfo() : bEnabled(true)`
- L175 _public function_ `bool IsValid() const`
- L180 _public function_ `bool IsPingable() const`
- L185 _public function_ `bool IsSubspace(const TCHAR* const SubspaceDelimiter) const`
- L190 _public function_ `FString ToDebugString() const`

#### struct `FQosRegionInfo`  
`struct FQosRegionInfo`  
_L200-256_
- reflection: `USTRUCT()`
- desc: Metadata about regions made up of datacenters
- L206 _public member_ `FText DisplayName;` — `UPROPERTY()` — Localized name of the region
- L209 _public member_ `FString RegionId;` — `UPROPERTY()` — Id for the region, all datacenters must reference one of these
- L212 _public member_ `bool bEnabled;` — `UPROPERTY()` — Is this region tested at all (if false, overrides individual datacenters)
- L215 _public member_ `bool bVisible;` — `UPROPERTY()` — Is this region visible in the UI (can be saved by user, replaced with auto if region disappears
- L218 _public member_ `bool bAutoAssignable;` — `UPROPERTY()` — Can this region be considered for auto detection
- L221 _public member_ `bool bAllowSubspaceBias;` — `UPROPERTY()` — Enable biased sorting algorithm on results for this region, which prefers non-subspaces over subspaces
- L224 _public member_ `FQosSubspaceComparisonParams SubspaceBiasParams;` — `UPROPERTY()` — Granular settings for biased subspace-based sorting algorithm, if enabled for this region
- L226 _public function_ `FQosRegionInfo() : bEnabled(true) , bVisible(true) , bAutoAssignable(true) , bAllowSubspaceBias(false)`
- L234 _public function_ `bool IsValid() const`
- L240 _public function_ `bool IsPingable() const` — @return true if this region is supposed to be tested
- L246 _public function_ `bool IsUsable() const` — @return true if a user can select this region in game
- L252 _public function_ `bool IsAutoAssignable() const` — @return true if this region can be auto assigned

#### struct `FDatacenterQosInstance`  
`struct FDatacenterQosInstance`  
_L260-376_
- reflection: `USTRUCT()`
- desc: Runtime information about a given region
- L266 _public member_ `FQosDatacenterInfo Definition;` — `UPROPERTY(Transient)` — Information about the datacenter
- L269 _public member_ `EQosDatacenterResult Result;` — `UPROPERTY(Transient)` — Success of the qos evaluation
- L272 _public member_ `int32 AvgPingMs;` — `UPROPERTY(Transient)` — Avg ping times across all search results
- L275 _public member_ `TArray<int32> PingResults;` — `UPROPERTY(Transient)` — Transient list of ping times obtained for this datacenter
- L277 _public member_ `int32 NumResponses;` — Number of good results
- L280 _public member_ `FDateTime LastCheckTimestamp;` — `UPROPERTY(Transient)` — Last time this datacenter was checked
- L283 _public member_ `bool bUsable;` — `UPROPERTY(Transient)` — Is the parent region usable
- L285 _public function_ `FDatacenterQosInstance() : Result(EQosDatacenterResult::Invalid) , AvgPingMs(UNREACHABLE_PING) , NumResponses(0) , LastCheckTimestamp(0) , bUsable(true)`
- L294 _public function_ `FDatacenterQosInstance(const FQosDatacenterInfo& InMeta, bool bInUsable) : Definition(InMeta) , Result(EQosDatacenterResult::Invalid) , AvgPingMs(UNREACHABLE_PING) , NumResponses(0) , LastCheckTimestamp(0) , bUsable(bInUsable)`
- L305 _public function_ `void Reset()` — reset the data to its default state
- L332 _public prototype_ `static bool IsLessWhenBiasedTowardsNonSubspace(const FDatacenterQosInstance& A, const FDatacenterQosInstance& B, const FQosSubspaceComparisonParams& ComparisonParams, const TCHAR* const SubspaceDelimiter);` — Compares the avg ping of two datacenters, handling cases where one is a subspace and the other is not, and like-for-like. When comparing subspace vs non-subspace, this will bias towards the non-subspace, as long as it satisfies the series of qualifying rules. When comparing like-for-like, average ping is compared, as usual. @param A - Left-hand datacenter QoS data to compare @param B - Right-hand datacenter QoS data to compare @param ComparisonParams - Rules settings for subspace vs non-subspace comparison @param SubspaceDelimiter - Search term to look for in datacenter ID; if found, implies that it is a subspace @return True if left-hand datacenter is "better", otherwise false (right-hand datacenter is "better") @see FDatacenterQosInstance::IsNonSubspaceRecommended(const FDatacenterQosInstance&, const FDatacenterQosInstance&, const FQosSubspaceComparisonParams&)
- L344 _public prototype_ `static bool IsNonSubspaceRecommended(const FDatacenterQosInstance& NonSubspace, const FDatacenterQosInstance& Subspace, const FQosSubspaceComparisonParams& ComparisonParams);` — Compares a subspace datacenter and a non-subspace datacenter, applying the qualifying rules to bias non-subspaces, configured via the supplied comparison parameters. @param NonSubspace - The non-subspace datacenter QoS data (must be already known to not be a subspace) @param Subspace - The subspace datacenter QoS data (must be already known to be a subspace) @param ComparisonParams - Granulator adjustments to the comparison rules @return True if the NonSubspace is "better" (i.e. passes the qualifying rules), otherwise false.
- L358 _public prototype_ `static const FDatacenterQosInstance& CompareBiasedTowardsNonSubspace( const FDatacenterQosInstance& NonSubspace, const FDatacenterQosInstance& Subspace, const FQosSubspaceComparisonParams& ComparisonParams);` — Compares a subspace datacenter and a non-subspace datacenter, applying the qualifying rules to bias non-subspaces, configured via the supplied comparison parameters. @param NonSubspace - The non-subspace datacenter QoS data (must be already known to not be a subspace) @param Subspace - The subspace datacenter QoS data (must be already known to be a subspace) @param ComparisonParams - Granulator adjustments to the comparison rules @return A reference to the input datacenter that is considered "better" after rules-based comparison. @see FDatacenterQosInstance::IsNonSubspaceRecommended(const FDatacenterQosInstance&, const FDatacenterQosInstance&, const FQosSubspaceComparisonParams&)
- L373 _public prototype_ `static const FDatacenterQosInstance* const CompareBiasedTowardsNonSubspace( const FDatacenterQosInstance* const NonSubspace, const FDatacenterQosInstance* const Subspace, const FQosSubspaceComparisonParams& ComparisonParams);` — Compares a subspace datacenter and a non-subspace datacenter, applying the qualifying rules to bias non-subspaces, configured via the supplied comparison parameters. @param NonSubspace - The non-subspace datacenter QoS data (must be already known to not be a subspace) @param Subspace - The subspace datacenter QoS data (must be already known to be a subspace) @param ComparisonParams - Granulator adjustments to the comparison rules @return A pointer to the input datacenter that is considered "better" after rules-based comparison. @see FDatacenterQosInstance::IsNonSubspaceRecommended(const FDatacenterQosInstance&, const FDatacenterQosInstance&, const FQosSubspaceComparisonParams&)

#### struct `FRegionQosInstance`  
`struct FRegionQosInstance`  
_L379-449_
- reflection: `USTRUCT()`
- L385 _public member_ `FQosRegionInfo Definition;` — `UPROPERTY(Transient)` — Information about the region
- L389 _public member_ `TArray<FDatacenterQosInstance> DatacenterOptions;` — `UPROPERTY()` — Array of all known datacenters and their status
- L391 _public function_ `FRegionQosInstance()`
- L395 _public function_ `FRegionQosInstance(const FQosRegionInfo& InMeta) : Definition(InMeta)`
- L401 _public function_ `const FString& GetRegionId() const` — @return the region id for this region instance
- L407 _public function_ `bool IsUsable() const` — @return if this region data is usable externally
- L413 _public function_ `bool IsAutoAssignable() const` — @return true if this region can be consider for auto detection
- L420 _public prototype_ `EQosDatacenterResult GetRegionResult() const;` — @return the result of this region ping request
- L423 _public prototype_ `int32 GetBestAvgPing() const;` — @return the ping recorded in the best sub region
- L426 _public prototype_ `FString GetBestSubregion() const;` — @return the subregion with the best ping
- L429 _public prototype_ `void GetSubregionPreferences(TArray<FString>& OutSubregions) const;` — @return sorted list of subregions by best ping
- L432 _public prototype_ `void SortDatacenterOptionsByAvgPingAsc();` — Sort the list of datacenter options into ascending order of average ping
- L445 _public prototype_ `void SortDatacenterSubspacesByRecommended(const FQosSubspaceComparisonParams& ComparisonParams, const TCHAR* const SubspaceDelimiter);` — Sort the list of datacenter options into ascending order, using rules-based comparison for cases where a subspace is being compared to a non-subspace; non-subspace will be favoured if it passes the rules check. Like-for-like comparisons are favour lower average ping. @param ComparisonParams - Granulator adjustments to the comparison rules @param SubspaceDelimiter - Search term to look for in datacenter ID; if found, implies that it is a subspace @see FDatacenterQosInstance::IsLessWhenBiasedTowardsNonSubspace(const FDatacenterQosInstance&, const FDatacenterQosInstance&, const FQosSubspaceComparisonParams&, const TCHAR*);
- L448 _public prototype_ `void LogDatacenterResults() const;` — Print list of datacenters results for this region to QoS log.

#### class `UQosRegionManager`  
`class UQosRegionManager : public UObject`  
_L455-715_
- reflection: `UCLASS(MinimalAPI, config = Engine)`
- inherits: `UObject`
- desc: Main Qos interface for actions related to server quality of service
- L465 _public prototype_ `void BeginQosEvaluation(UWorld* World, const TSharedPtr<IAnalyticsProvider>& AnalyticsProvider, const FSimpleDelegate& OnComplete);` — Start running the async QoS evaluation
- L470 _public prototype_ `bool IsQosEvaluationInProgress() const;` — Returns true if Qos is in the process of being evaluated
- L481 _public prototype_ `FString GetRegionId() const;` — Get the region ID for this instance, checking ini and commandline overrides. Dedicated servers will have this value specified on the commandline Clients pull this value from the settings (or command line) and do a ping test to determine if the setting is viable. @return the current region identifier
- L488 _public prototype_ `FString GetBestRegion() const;` — Get the region ID with the current best ping time, checking ini and commandline overrides. @return the default region identifier
- L495 _public prototype_ `const TArray<FRegionQosInstance>& GetRegionOptions() const;` — Get the list of regions that the client can choose from (returned from search and must meet min ping requirements) If this list is empty, the client cannot play.
- L503 _public prototype_ `void GetSubregionPreferences(const FString& RegionId, TArray<FString>& OutSubregions) const;` — Get a sorted list of subregions within a region @param RegionId region of interest @param OutSubregions list of subregions in sorted order
- L506 _public prototype_ `TMap<FString, int64> GetAllSubregionPingsMap() const;` — @return map of all subregions to avg ping times
- L511 _public prototype_ `bool IsUsableRegion(const FString& InRegionId) const;` — @return true if this is a usable region, false otherwise
- L518 _public prototype_ `bool SetSelectedRegion(const FString& RegionId, bool bForce=false);` — Try to set the selected region ID (must be present in GetRegionOptions) @param bForce if true then use selected region even if QoS eval has not completed successfully
- L521 _public prototype_ `void ClearSelectedRegion();` — Clear the region to nothing, used for logging out
- L526 _public prototype_ `void ForceSelectRegion(const FString& RegionId);` — Force the selected region creating a fake RegionOption if necessary
- L531 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnQosRegionIdChanged, const FString& , const FString& );` — Delegate that fires whenever the current QoS region ID changes.
- L532 _public function_ `FOnQosRegionIdChanged& OnQosRegionIdChanged()`
- L541 _public prototype_ `static FString GetDatacenterId();` — Get the datacenter id for this instance, checking ini and commandline overrides This is only relevant for dedicated servers (so they can advertise). Client does not search on this in any way @return the default datacenter identifier
- L548 _public prototype_ `static FString GetAdvertisedSubregionId();` — Get the subregion id for this instance, checking ini and commandline overrides This is only relevant for dedicated servers (so they can advertise). Client does not search on this (but may choose to prioritize results later)
- L551 _public prototype_ `bool AllRegionsFound() const;` — @return true if a reasonable enough number of results were returned from all known regions, false otherwise
- L556 _public prototype_ `void DumpRegionStats() const;` — Debug output for current region / datacenter information
- L558 _public prototype_ `void RegisterQoSSettingsChangedDelegate(const FSimpleDelegate& OnQoSSettingsChanged);`
- L560 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnQosEvalCompleteDelegate);`
- L565 _public function_ `FOnQosEvalCompleteDelegate& OnQosEvalComplete()` — Get the delegate that is invoked when the current/next QoS evaluation completes.
- L570 _public prototype_ `virtual void PostReloadConfig(class FProperty* PropertyThatWasLoaded) override;` — Begin UObject interface
- L578 _private prototype_ `const TCHAR* GetSubspaceDelimiter() const;` — Get the delimiter string used to split primary subspace ID from a subregion ID.
- L585 _private prototype_ `static const FRegionQosInstance* FindQosRegionById(const TArray<FRegionQosInstance>& Regions, const FString& RegionId);` — Finds the QOS region result that matches the given region ID from an array of region results. @return pointer the the region result if found, otherwise nullptr
- L594 _private prototype_ `static const FRegionQosInstance* FindBestQosRegion(const TArray<FRegionQosInstance>& Regions);` — Finds the QOS region result that has the "best" ping result. Assumes that the datacenter results within each region result are pre-sorted, e.g. by average ping, or via a recommendation bias algorithm. @return pointer to the "best" region result, determined by a previous sort of region datacenters, otherwise nullptr if no results exist.
- L598 _private prototype_ `static bool TestCompareDatacentersBySubspace();` — Test methods for debugging datacenter comparisons that use special rules when dealing with subspaces.
- L599 _private prototype_ `static bool TestSortDatacenterSubspacesByRecommended();`
- L600 _private prototype_ `static FRegionQosInstance TestCreateExampleRegionResult();`
- L608 _private prototype_ `void SanityCheckDefinitions() const;` — Double check assumptions based on current region/datacenter definitions
- L610 _private prototype_ `void OnQosEvaluationComplete(EQosCompletionResult Result, const TArray<FDatacenterQosInstance>& DatacenterInstances, FString* OutSelectedRegion, FString* OutSelectedSubRegion);`
- L615 _private prototype_ `void TrySetDefaultRegion();` — Use the existing set value, or if it is currently invalid, set the next best region available
- L620 _private prototype_ `int32 GetMaxPingMs() const;` — @return max allowable ping to any region and still be allowed to play
- L630 _private prototype_ `bool IsSubspaceBiasOrderEnabled() const;` — Should datacenter QoS results be sorted using rules-based comparison where subspaces are encountered? Determined via bEnableSubspaceBiasOrder engine configuration param for QosRegionManager. Global enable/disable may be overridden by `qossubspacebias=true|false` command-line arg. @return True if rules-based sorting (when dealing with subspaces) is enabled, otherwise false.
- L642 _private prototype_ `bool IsSubspaceBiasOrderEnabled(const FQosRegionInfo& RegionDefinition) const;` — Should datacenter QoS results be sorted using rules-based comparison where subspaces are encountered for the given region's QoS data? Determined via bEnableSubspaceBiasOrder engine configuration param for QosRegionManager, and the specific region's RegionDefinition entry. Global enable/disable may be overridden by `qossubspacebias=true|false` command-line arg. @return True if rules-based sorting (when dealing with subspaces) is enabled, otherwise false.
- L647 _private prototype_ `void RefreshUsableSubregions();` — Rebuild the list of usable subregions sorted by ping ascending.
- L651 _private member_ `int32 NumTestsPerRegion;` — `UPROPERTY(Config)` — Number of times to ping a given region using random sampling of available servers
- L655 _private member_ `float PingTimeout;` — `UPROPERTY(Config)` — Timeout value for each ping request
- L662 _private member_ `bool bEnableSubspaceBiasOrder;` — `UPROPERTY(Config)` — Global switch to enable/disable sorting of QoS datacenter results using rules-based comparison, where subspaces are encountered.
- L669 _private member_ `FString SubspaceDelimiter;` — `UPROPERTY(Config)` — Delimiter string that identifies a subspace datacenter ID. e.g. "DE_S" would be a subspace of the "DE" subregion, using "_" as the delimiter.
- L673 _private member_ `FQosSubspaceComparisonParams SubspaceBiasParams;` — `UPROPERTY(Config)` — Granular settings for biased subspace-based sorting algorithm which applies when returning all subregions for queries
- L677 _private member_ `TArray<FQosRegionInfo> RegionDefinitions;` — `UPROPERTY(Config)` — Metadata about existing regions
- L681 _private member_ `TArray<FQosDatacenterInfo> DatacenterDefinitions;` — `UPROPERTY(Config)` — Metadata about datacenters within existing regions
- L684 _private member_ `FDateTime LastCheckTimestamp;` — `UPROPERTY()`
- L688 _private member_ `TObjectPtr<UQosEvaluator> Evaluator;` — `UPROPERTY()` — Reference to the evaluator for making datacenter determinations (null when not active)
- L691 _private member_ `EQosCompletionResult QosEvalResult;` — `UPROPERTY()` — Result of the last datacenter test
- L694 _private member_ `TArray<FRegionQosInstance> RegionOptions;` — `UPROPERTY()` — Array of all known regions and the datacenters in them
- L698 _private member_ `FString ForceRegionId;` — `UPROPERTY()` — Value forced to be the region (development)
- L701 _private member_ `bool bRegionForcedViaCommandline;` — `UPROPERTY()` — Was the region forced via commandline
- L704 _private member_ `FString SelectedRegionId;` — `UPROPERTY()` — Value set by the game to be the current region
- L706 _private member_ `TArray<FString> UsableSubregions;` — List of all useable subregions sorted by ping. Does not include accelerated regions.
- L708 _private member_ `FOnQosEvalCompleteDelegate OnQosEvalCompleteDelegate;`
- L710 _private member_ `FSimpleDelegate OnQoSSettingsChangedDelegate;`
- L712 _private member_ `FOnQosRegionIdChanged OnQosRegionIdChangedDelegate;`
- L714 _private member_ `static const TCHAR* SubspaceDelimiterDefault;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API QOS_API`
- L14 _macro_ `#define UNREACHABLE_PING 9999`
- L16 _macro_ `#define DEBUG_SUBCOMPARE_BY_SUBSPACE 0`
- L30 _function_ `inline const TCHAR* LexToString(EQosDatacenterResult Result)`
- L55 _function_ `inline const TCHAR* LexToString(EQosCompletionResult Result)`
- L531 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnQosRegionIdChanged, const FString& , const FString& );` — Delegate that fires whenever the current QoS region ID changes.
- L560 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnQosEvalCompleteDelegate);`
