# Plugins / MessageBusTester

- module root: `Plugins/Experimental/MessageBusTester/Source/MessageBusTester`
- headers: 9; symbols: 235
- symbol kinds: class=8, delegate=5, enum=3, enumerator=6, function=20, macro=3, member=89, namespace=1, prototype=84, struct=15, typedef=1
- PrivateDependencyModuleNames: Core, CoreUObject, MessageLog, Messaging
- PublicDependencyModuleNames: DeveloperSettings, MessagingCommon, UdpMessaging

### `Plugins/Experimental/MessageBusTester/Source/MessageBusTester/Private/MessageBusTester.h` (Private)


#### class `FMessageBusTester`  
`class FMessageBusTester : public IMessageBusTester`  
_L28-224_
- inherits: `IMessageBusTester`
- desc: Implementation of the MessageBus Tester
- L44 _public prototype_ `FMessageBusTester();`
- L45 _public prototype_ `FMessageBusTester(const FMessageBusTester&) = delete;`
- L46 _public prototype_ `FMessageBusTester& operator=(const FMessageBusTester&) = delete;`
- L47 _public prototype_ `virtual ~FMessageBusTester();`
- L50 _public prototype_ `virtual bool IsActive() const override;`
- L51 _public function_ `virtual FOnDiscoveredTesterListChanged& OnDiscoveredTesterListChanged() override`
- L52 _public function_ `virtual FOnTestPlanChanged& OnTestPlanChanged() override`
- L53 _public function_ `virtual TConstArrayView<TSharedPtr<FDiscoveredTester, ESPMode::ThreadSafe>> GetDiscoveredTesters() const override`
- L58 _public function_ `virtual bool IsRunning() const override`
- L62 _public function_ `virtual bool StartSystem() override`
- L67 _public function_ `virtual bool StopSystem() override`
- L73 _public prototype_ `virtual bool ClearLostTesters() override;`
- L74 _public function_ `virtual const FMessageBusTestPlan& GetTestPlan() const override`
- L75 _public prototype_ `virtual void AddTestPlanItem(FTestPlanItem NewItem) override;`
- L76 _public prototype_ `virtual void RemoveTestPlanItem(int32 Index) override;`
- L78 _public prototype_ `virtual bool StartTest() override;`
- L79 _public prototype_ `virtual bool StopTest(bool bShouldExitOnStop = false) override;`
- L80 _public prototype_ `virtual EMessageBusTesterState GetState() const override;`
- L84 _public prototype_ `void Initialize();`
- L85 _public prototype_ `void Start();`
- L86 _public prototype_ `void Stop();`
- L91 _private prototype_ `void SendKeepAlive_AnyThread();`
- L94 _private prototype_ `bool SendMessageInternal(FTesterBaseMessage* Payload, UScriptStruct* Type, const TArray<FMessageAddress>& Addresses, EMessageBusTesterMessageFlags InFlags) const;` — Sends a message using messagebus to connected providers
- L97 _private prototype_ `void HandleDiscoveredTester(const FGuid& Identifier, const FTesterInstanceDescriptor& Descriptor, const FMessageAddress& Address);`
- L98 _private prototype_ `bool AddTester(const FGuid& Identifier, const FTesterInstanceDescriptor& Descriptor, const FMessageAddress& Address);`
- L99 _private prototype_ `void FillTesterDescription(const FGuid& Identifier, const FTesterInstanceDescriptor& NewDescriptor, const FMessageAddress& NewAddress, TSharedPtr<FDiscoveredTester, ESPMode::ThreadSafe>& OutEntry) const;`
- L101 _private prototype_ `void ProcessOnGameThread(const FTesterDiscoveryMessage& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);`
- L102 _private prototype_ `void ProcessOnGameThread(const FTesterStartTestMessage& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);`
- L103 _private prototype_ `void ProcessOnGameThread(const FTesterStopTestMessage& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);`
- L104 _private prototype_ `void ProcessOnGameThread(const FTestPayloadReceptionMessage& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);`
- L107 _private prototype_ `bool Tick(float DeltaTime);`
- L110 _private prototype_ `void UpdateDiscoveredTester();` — Updates each provider's state based on last communication timestamp
- L113 _private prototype_ `void SendDiscoveryMessage();` — Broadcasts a discovery message to find new providers and also keep communication active with all providers
- L116 _private prototype_ `void OnPreExit();` — Shutdowns monitor before everything has exited. Let know providers that we're out
- L118 _private prototype_ `void UpdateTestSequence();`
- L122 _private function_ `template<typename MessageType> bool SendMessage(MessageType* Payload, EMessageBusTesterMessageFlags Flags)` — Generic send message to support constructor parameters directly and temp object created
- L142 _private function_ `template<typename MessageType> bool SendMessage(MessageType* Payload, const TArray<FMessageAddress>& Addresses, EMessageBusTesterMessageFlags Flags)` — Generic send message to support constructor parameters directly and temp object created
- L148 _private prototype_ `void SetupTestPlan();`
- L151 _private prototype_ `template<typename TInboundType> void HandleMessage(const TInboundType& Inbound, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);`
- L153 _private prototype_ `void SetState(EMessageBusTesterState InState);`
- L157 _private prototype_ `void ExportResultsToCSV();` — Dump test results to a CSV file.
- L160 _private prototype_ `void TriggerAppExit();` — Set the shutdown timer to trigger this app to exit.
- L163 _private member_ `TMpscQueue<FInboundMessage> InboundMessages;` — Messages received from message bus.
- L166 _private member_ `TUniquePtr<FMessageBusTesterHeartBeat> MessageBusHeartBeat;` — Unique pointer to the heart beat thread runnable.
- L169 _private member_ `TSharedPtr<FMessageEndpoint, ESPMode::ThreadSafe> TesterEndpoint;` — Endpoint used to communicate with other testers
- L172 _private member_ `TArray<TSharedPtr<FDiscoveredTester, ESPMode::ThreadSafe>> DiscoveredTesters;` — List of discovered endpoints that we are tracking for testing.
- L175 _private member_ `TArray<FGuid> InvalidTesters;` — List of providers we received discovery response from that were not usable (wrong version, session id...)
- L178 _private member_ `std::atomic<EMessageBusTesterState> State = EMessageBusTesterState::Idle;` — Current state of the tester.
- L181 _private member_ `std::atomic<uint64> KeepAliveNumber = 0;` — Tracks the current keep alive counter.
- L184 _private member_ `double LastSentDiscoveryMessage = 0.0;` — Timestamp when we last sent a discovery message
- L187 _private member_ `FTSTicker::FDelegateHandle TickerHandle;` — Handle to our ticking delegate.
- L190 _private member_ `FGuid Identifier;` — This tester identifier
- L193 _private member_ `FTesterDiscoveryMessage CachedDiscoveryMessage;` — DiscoveryMessage built once and broadcasted periodically
- L195 _private member_ `FCriticalSection DiscoveredTesterCriticalSection;`
- L197 _private member_ `FOnDiscoveredTesterListChanged DiscoveredTesterListChangedDelegate;`
- L198 _private member_ `FOnTestPlanChanged TestPlanChangedDelegate;`
- L200 _private member_ `FMessageBusTestPlan TestPlan;`
- L203 _private member_ `double StartTime = -1;` — Test start time. If bStartOnLaunch is specified then this value will get set on first payload reception.
- L206 _private member_ `double ShutdownTime = -1;` — Time to execute shutdown. If a test duration has been specified then a shutdown time will be set at the end of the duration.
- L209 _private member_ `double TestDuration = -1;` — Run time duration in seconds. A number less than or equal to 0 indicates that we run forever.  If this is set we will also force the app to terminate.
- L212 _private member_ `FString ResultsToCSV;` — Optional path to a CSV file that is written on exit.
- L215 _private member_ `bool bStartOnLaunch = false;` — Indicates if we should execute our test plans as soon as we detect other clients.
- L223 _private member_ `TArray<FTestPlanItemTracker> TestPlanItemTrackers;`

#### struct `FMessageBusTester::FInboundMessage`  
`struct FInboundMessage`  
_L31-42_
- L34 _public function_ `template<typename T> FInboundMessage(const T& InType, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext) : Context(InContext)`
- L40 _public member_ `FMessageBusTesterTypes Type;`
- L41 _public member_ `TSharedRef<IMessageContext, ESPMode::ThreadSafe> Context;`

#### struct `FMessageBusTester::FTestPlanItemTracker`  
`struct FTestPlanItemTracker`  
_L217-222_
- L219 _public member_ `FTestPlanItem ItemDescription;`
- L220 _public member_ `TMap<FGuid, int32> SentPayloadIds;`
- L221 _public member_ `double LastPayloadSentTimestamp = 0.0;`

#### Free symbols / members of external scopes

- L23 _typedef_ `using FMessageBusTesterTypes = TVariant<FTesterDiscoveryMessage, FTesterStartTestMessage, FTesterStopTestMessage, FTestPayloadReceptionMessage>;`

### `Plugins/Experimental/MessageBusTester/Source/MessageBusTester/Private/MessageBusTesterLogger.h` (Private)


#### class `FMessageBusTesterLogger`  
`class FMessageBusTesterLogger : public IMessageBusTesterLogger`  
_L12-31_
- inherits: `IMessageBusTesterLogger`
- L18 _public prototype_ `virtual void Log(const FName& TesterName, FString&& InLogMessage, EMessageSeverity::Type Verbosity ) override;`
- L19 _public prototype_ `virtual void ClearLog() override;`
- L20 _public function_ `virtual FOnMessageBusTesterNewLogReceived& OnMessageBusTesterNewLogReceived() override`
- L21 _public function_ `virtual FOnMessageBusTesterLogCleared& OnMessageBusTesterLogCleared() override`
- L27 _private member_ `TArray<TSharedPtr<FMessageBusTesterLogEntry>> Entries;`
- L29 _private member_ `FOnMessageBusTesterNewLogReceived NewLogReceivedDelegate;`
- L30 _private member_ `FOnMessageBusTesterLogCleared LogClearedDelegate;`

### `Plugins/Experimental/MessageBusTester/Source/MessageBusTester/Private/MessageBusTesterModule.h` (Private)


#### class `FMessageBusTesterModule`  
`class FMessageBusTesterModule : public IMessageBusTesterModule`  
_L18-41_
- inherits: `IMessageBusTesterModule`
- L21 _public prototype_ `virtual ~FMessageBusTesterModule() = default;`
- L24 _public prototype_ `virtual void StartupModule() override;`
- L25 _public prototype_ `virtual void ShutdownModule() override;`
- L29 _public prototype_ `virtual IMessageBusTester& GetMessageBusTester() override;`
- L30 _public prototype_ `virtual IMessageBusTesterLogger& GetLogger() override;`
- L39 _protected member_ `TUniquePtr<FMessageBusTester> MessageBusTester;` — Single instance of the MessageBusTester
- L40 _protected member_ `TUniquePtr<FMessageBusTesterLogger> Logger;`

#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMessageBusTester, Log, All);`
- L15 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMessageBusTester, Log, All);`

### `Plugins/Experimental/MessageBusTester/Source/MessageBusTester/Public/DiscoveredTester.h` (Public)


#### struct `FPayloadInfo`  
`struct FPayloadInfo`  
_L16-35_
- L18 _public function_ `FPayloadInfo(const FTestPayloadMessage& PayloadMessage) : PayloadId(PayloadMessage.PayloadId) , SentTime(FPlatformTime::Seconds()) , PayloadSize(PayloadMessage.Payload.Num())`
- L26 _public function_ `bool operator==(const FPayloadInfo& Other) const`
- L31 _public member_ `int32 PayloadId = INDEX_NONE;`
- L32 _public member_ `double SentTime = 0.0;`
- L33 _public member_ `int64 PayloadSize = 0;`
- L34 _public member_ `double AcknowledgedTime = -1.0;`

#### struct `FKeepAliveStatistics`  
`struct FKeepAliveStatistics`  
_L37-47_
- L39 _public member_ `double LastUnreliableKeepAliveReceptionInterval = 0.0;`
- L40 _public member_ `double MinUnreliableKeepAliveInterval = DBL_MAX;`
- L41 _public member_ `double MaxUnreliableKeepAliveInterval = 0.0;`
- L42 _public member_ `double AverageUnreliableKeepAliveInterval = 0.0;`
- L43 _public member_ `double LastReliableKeepAliveReceptionInterval = 0.0;`
- L44 _public member_ `double MinReliableKeepAliveInterval = DBL_MAX;`
- L45 _public member_ `double MaxReliableKeepAliveInterval = 0.0;`
- L46 _public member_ `double AverageReliableKeepAliveInterval = 0.0;`

#### class `FDiscoveredTester`  
`class FDiscoveredTester`  
_L51-102_
- L53 _private function_ `bool operator==(const FDiscoveredTester& Other) const`
- L54 _private function_ `bool operator!=(const FDiscoveredTester& Other) const`
- L57 _public prototype_ `void UpdateConnectionState();`
- L58 _public prototype_ `void NotifyPayloadSent(const FTestPayloadMessage& PayloadMessage);`
- L59 _public prototype_ `void NotifyAckReceived(const FTestPayloadReceptionMessage& AckMessage);`
- L60 _public prototype_ `void NotifyKeepAliveReceived(bool bIsReliable);`
- L61 _public prototype_ `bool IsPendingPayloadAck(int32 PayloadId) const;`
- L66 _public member_ `FGuid Identifier;` — Identifier of this tester
- L69 _public member_ `FTesterInstanceDescriptor Descriptor;` — Detailed descriptor
- L72 _public member_ `FMessageAddress Address;` — Address of this Tester
- L75 _public member_ `EMessageBusTesterState State = EMessageBusTesterState::Idle;` — State of this Tester based on message reception
- L78 _public member_ `EDiscoveredTesterConnectionState ConnectionState = EDiscoveredTesterConnectionState::Connected;` — State of this Tester based on message reception
- L80 _public member_ `FMessageTransportStatistics Statistics;`
- L83 _public member_ `double LastReceivedMessageTime = 0.0;` — Timestamp when last message was received based on FPlatformTime::Seconds
- L86 _public member_ `double LastUnreliableKeepAliveMessageTime = 0.0;` — Timestamp when last KeepAlive was received based on FPlatformTime::Seconds
- L89 _public member_ `double LastReliableKeepAliveMessageTime = 0.0;` — Timestamp when last KeepAlive was received based on FPlatformTime::Seconds
- L92 _public member_ `FMovingWindowAverageFast<double, 128> AverageUnreliableKeepAliveIntervalWindow;` — Last interval between keep alive reception
- L93 _public member_ `FMovingWindowAverageFast<double, 128> AverageReliableKeepAliveIntervalWindow;`
- L96 _public member_ `FMovingWindowAverageFast<double, 128> AverageMbPerSecond;` — Running average of transfer performance.
- L98 _public member_ `FKeepAliveStatistics KeepAliveStatistics;`
- L100 _public member_ `TArray<FPayloadInfo> SentPayloads;`
- L101 _public member_ `TArray<FPayloadInfo> AcknowledgedPayloads;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API MESSAGEBUSTESTER_API`

### `Plugins/Experimental/MessageBusTester/Source/MessageBusTester/Public/IMessageBusTester.h` (Public)


#### class `IMessageBusTester`  
`class IMessageBusTester`  
_L13-46_
- desc: Interface for the MessageBusTester
- L17 _public function_ `virtual ~IMessageBusTester()`
- L22 _public prototype_ `virtual bool IsActive() const = 0;` — Returns true if tester is active
- L24 _public prototype_ `virtual TConstArrayView<TSharedPtr<FDiscoveredTester, ESPMode::ThreadSafe>> GetDiscoveredTesters() const = 0;`
- L27 _public prototype_ `virtual bool ClearLostTesters() = 0;` — Clear any lost testers and return true if any were removed.
- L29 _public prototype_ `virtual const FMessageBusTestPlan& GetTestPlan() const = 0;`
- L31 _public prototype_ `virtual bool IsRunning() const = 0;`
- L32 _public prototype_ `virtual bool StartSystem() = 0;`
- L33 _public prototype_ `virtual bool StopSystem() = 0;`
- L35 _public prototype_ `virtual bool StartTest() = 0;`
- L36 _public prototype_ `virtual bool StopTest(bool bShouldExitOnStop = false) = 0;`
- L37 _public prototype_ `virtual void AddTestPlanItem(FTestPlanItem NewItem) = 0;`
- L38 _public prototype_ `virtual void RemoveTestPlanItem(int32 Index) = 0;`
- L39 _public prototype_ `virtual EMessageBusTesterState GetState() const = 0;`
- L41 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnDiscoveredTesterListChanged);`
- L42 _public prototype_ `virtual FOnDiscoveredTesterListChanged& OnDiscoveredTesterListChanged() = 0;`
- L44 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnTestPlanChanged);`
- L45 _public prototype_ `virtual FOnTestPlanChanged& OnTestPlanChanged() = 0;`

#### Free symbols / members of external scopes

- L41 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnDiscoveredTesterListChanged);`
- L44 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnTestPlanChanged);`

### `Plugins/Experimental/MessageBusTester/Source/MessageBusTester/Public/IMessageBusTesterLogger.h` (Public)


#### struct `FMessageBusTesterLogEntry`  
`struct FMessageBusTesterLogEntry`  
_L10-22_
- L12 _public prototype_ `FMessageBusTesterLogEntry() = default;`
- L13 _public function_ `FMessageBusTesterLogEntry(FName InLogSource, FString&& InLogMessage, EMessageSeverity::Type InMessageSeverity) : Source(InLogSource) , LogMessage(MoveTemp(InLogMessage)) , MessageSeverity(InMessageSeverity)`
- L19 _public member_ `FName Source = NAME_None;`
- L20 _public member_ `FString LogMessage;`
- L21 _public member_ `EMessageSeverity::Type MessageSeverity = EMessageSeverity::Info;`

#### class `IMessageBusTesterLogger`  
`class IMessageBusTesterLogger`  
_L25-39_
- L29 _public prototype_ `virtual ~IMessageBusTesterLogger() = default;`
- L31 _public prototype_ `virtual void Log(const FName& TesterName, FString&& InLogMessage, EMessageSeverity::Type Verbosity = EMessageSeverity::Info) = 0;`
- L32 _public prototype_ `virtual void ClearLog() = 0;`
- L34 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnMessageBusTesterNewLogReceived, TSharedRef<FMessageBusTesterLogEntry> );`
- L35 _public prototype_ `virtual FOnMessageBusTesterNewLogReceived& OnMessageBusTesterNewLogReceived() = 0;`
- L37 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnMessageBusTesterLogCleared);`
- L38 _public prototype_ `virtual FOnMessageBusTesterLogCleared& OnMessageBusTesterLogCleared() = 0;`

#### Free symbols / members of external scopes

- L34 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnMessageBusTesterNewLogReceived, TSharedRef<FMessageBusTesterLogEntry> );`
- L37 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnMessageBusTesterLogCleared);`

### `Plugins/Experimental/MessageBusTester/Source/MessageBusTester/Public/IMessageBusTesterModule.h` (Public)


#### class `IMessageBusTesterModule`  
`class IMessageBusTesterModule : public IModuleInterface`  
_L11-17_
- inherits: `IModuleInterface`
- L14 _public prototype_ `virtual IMessageBusTester& GetMessageBusTester() = 0;`
- L16 _public prototype_ `virtual IMessageBusTesterLogger& GetLogger() = 0;`

### `Plugins/Experimental/MessageBusTester/Source/MessageBusTester/Public/MessageBusTesterCommon.h` (Public)


#### enum `EMessageBusTesterMessageFlags`  
`enum class EMessageBusTesterMessageFlags : uint8`  
_L17-23_
- reflection: `UENUM()`
- desc: Message flags configuring how a message is sent
- L19 _public enumerator_ `None = 0`
- L22 _public enumerator_ `Reliable = 1 << 0` — Sends this message as reliable, to make sure it's received by the receivers

#### enum `EMessageBusTesterState`  
`enum class EMessageBusTesterState : uint8`  
_L28-34_
- reflection: `UENUM()`
- desc: States that a tester can be in
- L31 _public enumerator_ `Active` — Testing is active (messages are sent between each testers)
- L33 _public enumerator_ `Idle` — Tester is idle

#### enum `EDiscoveredTesterConnectionState`  
`enum class EDiscoveredTesterConnectionState : uint8`  
_L38-44_
- reflection: `UENUM()`
- desc: Connection state for a MessageBus tester.
- L41 _public enumerator_ `Connected` — Tester is considered connected
- L43 _public enumerator_ `Lost` — Tester was considered lost

#### struct `FTesterInstanceDescriptor`  
`struct FTesterInstanceDescriptor`  
_L52-77_
- reflection: `USTRUCT(MinimalAPI)`
- desc: Holds descriptive information about another tester. Information that won't change for a session Used when testers connects
- L60 _public member_ `FString MachineName;` — `UPROPERTY()` — Machine name read from FPlatformProcess::ComputerName()
- L64 _public member_ `uint32 ProcessId = 0;` — `UPROPERTY()` — ProcessId read from FPlatformProcess::GetCurrentProcessId
- L68 _public member_ `FName FriendlyName;` — `UPROPERTY()` — Friendly name for this Unreal instance. If empty, this will be MachineName - ProcessId
- L72 _public member_ `int32 SessionId = INDEX_NONE;` — `UPROPERTY()` — Session Id that may be used to differentiate different sessions on the network
- L76 _public member_ `int32 MessageVersion = 1;` — `UPROPERTY()` — Provision for versioning a tester if we need to differentiate version.

#### struct `FTesterBaseMessage`  
`struct FTesterBaseMessage`  
_L83-96_
- reflection: `USTRUCT(MinimalAPI)`
- desc: Base structure for all message bus tester messages
- L91 _public member_ `FGuid Identifier;` — `UPROPERTY()` — Identifier of this instance
- L95 _public member_ `FQualifiedFrameTime FrameTime;` — `UPROPERTY()` — FrameTime of the sender.

#### struct `FTesterDiscoveryMessage`  
`struct FTesterDiscoveryMessage : public FTesterBaseMessage`  
_L102-117_
- reflection: `USTRUCT(MinimalAPI)`
- inherits: `FTesterBaseMessage`
- desc: Message broadcasted periodically by the monitor to discover new providers
- L107 _public prototype_ `FTesterDiscoveryMessage() = default;`
- L108 _public function_ `FTesterDiscoveryMessage(FTesterInstanceDescriptor&& InDescriptor) : Descriptor(MoveTemp(InDescriptor))`
- L116 _public member_ `FTesterInstanceDescriptor Descriptor;` — `UPROPERTY()` — Detailed description of a tester

#### struct `FTesterKeepAliveMessage`  
`struct FTesterKeepAliveMessage : public FTesterBaseMessage`  
_L123-144_
- reflection: `USTRUCT(MinimalAPI)`
- inherits: `FTesterBaseMessage`
- L128 _public prototype_ `FTesterKeepAliveMessage() = default;`
- L129 _public function_ `FTesterKeepAliveMessage(uint64 InNumber) : KeepAliveNumber(InNumber)`
- L137 _public member_ `uint64 KeepAliveNumber = 0;` — `UPROPERTY()`
- L140 _public member_ `bool bReliablySent = true;` — `UPROPERTY()`
- L143 _public member_ `EMessageBusTesterState State = EMessageBusTesterState::Idle;` — `UPROPERTY()`

#### struct `FTestPlanItem`  
`struct FTestPlanItem`  
_L147-156_
- reflection: `USTRUCT(MinimalAPI)`
- L152 _public member_ `int32 NumBytes = 1024;` — `UPROPERTY()`
- L155 _public member_ `float IntervalSeconds = 0;` — `UPROPERTY()`

#### struct `FMessageBusTestPlan`  
`struct FMessageBusTestPlan`  
_L159-165_
- reflection: `USTRUCT(MinimalAPI)`
- L164 _public member_ `TArray<FTestPlanItem> TestPlanItems;` — `UPROPERTY()`

#### struct `FTesterStartTestMessage`  
`struct FTesterStartTestMessage : public FTesterBaseMessage`  
_L171-182_
- reflection: `USTRUCT(MinimalAPI)`
- inherits: `FTesterBaseMessage`
- L176 _public prototype_ `FTesterStartTestMessage() = default;`
- L181 _public member_ `FMessageBusTestPlan TestPlan;` — `UPROPERTY()`

#### struct `FTesterStopTestMessage`  
`struct FTesterStopTestMessage : public FTesterBaseMessage`  
_L188-197_
- reflection: `USTRUCT(MinimalAPI)`
- inherits: `FTesterBaseMessage`
- L193 _public prototype_ `FTesterStopTestMessage() = default;`
- L196 _public member_ `bool bEngineShouldExit = false;` — `UPROPERTY()`

#### struct `FTestPayloadMessage`  
`struct FTestPayloadMessage : public FTesterBaseMessage`  
_L205-222_
- reflection: `USTRUCT(MinimalAPI)`
- inherits: `FTesterBaseMessage`
- L210 _public prototype_ `FTestPayloadMessage() = default;`
- L215 _public member_ `int32 TestPlanIndex = INDEX_NONE;` — `UPROPERTY()`
- L218 _public member_ `int32 PayloadId = 0;` — `UPROPERTY()`
- L221 _public member_ `TArray<uint8> Payload;` — `UPROPERTY()`

#### struct `FTestPayloadReceptionMessage`  
`struct FTestPayloadReceptionMessage : public FTesterBaseMessage`  
_L228-245_
- reflection: `USTRUCT(MinimalAPI)`
- inherits: `FTesterBaseMessage`
- L233 _public prototype_ `FTestPayloadReceptionMessage() = default;`
- L238 _public member_ `int32 TestPlanIndex = INDEX_NONE;` — `UPROPERTY()`
- L241 _public member_ `int32 PayloadId = 0;` — `UPROPERTY()`
- L244 _public member_ `int32 ReceivedPayloadSize = 0;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MESSAGEBUSTESTER_API`
- L24 _prototype_ `ENUM_CLASS_FLAGS(EMessageBusTesterMessageFlags);`
- L247 _namespace_ `namespace MessageBusTesterUtils`
- L249 _prototype_ `FTesterInstanceDescriptor GetInstanceDescriptor();` (scope `MessageBusTesterUtils`)

### `Plugins/Experimental/MessageBusTester/Source/MessageBusTester/Public/MessageBusTesterSettings.h` (Public)


#### class `UMessageBusTesterSettings`  
`class UMessageBusTesterSettings : public UDeveloperSettings`  
_L16-67_
- reflection: `UCLASS(config=Engine, MinimalAPI)`
- inherits: `UDeveloperSettings`
- desc: Settings for the MessageBusTester plugin modules.
- L21 _public prototype_ `UMessageBusTesterSettings();`
- L23 _public prototype_ `virtual FName GetCategoryName() const;`
- L25 _public prototype_ `virtual FText GetSectionText() const override;`
- L30 _public prototype_ `int32 GetSessionId() const;` — Returns current SessionId either based on settings or overriden by commandline
- L36 _public member_ `bool bUseSessionId = true;` — `UPROPERTY(config, EditAnywhere, Category = "Settings")` — If true, message bus will only listen to Testers with same sessionId
- L44 _protected member_ `int32 SessionId = INDEX_NONE;` — `UPROPERTY(config, EditAnywhere, Category = "Settings")` — The projects SessionId to differentiate data sent over network. @note It may be overriden via the command line, "-MessageBusTesterSessionId=1"
- L50 _public member_ `float TimeoutInterval = 10.0f;` — `UPROPERTY(config, EditAnywhere, Category = "Settings", meta=(Units="s", ClampMin=0.5f))` — Interval threshold between KeepAlive reception before considering another tester as dropped
- L54 _public member_ `float DiscoveryMessageInterval = 2.0f;` — `UPROPERTY(config, EditAnywhere, Category = "Settings", meta=(Units="s", ClampMin=0.5f))` — Interval between each discovery signal
- L60 _public member_ `TOptional<int32> CommandLineSessionId;` — The current SessionId in a MessageBusTesting context read from the command line. ie. "-MessageBusTesterSessionId=1"
- L66 _public member_ `FName CommandLineFriendlyName;` — A friendly name for that instance given through command line (-MessageBusTesterFriendlyName=) to identify it when monitoring. If none, by default it will be filled with MachineName:ProcessId

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MESSAGEBUSTESTER_API`
