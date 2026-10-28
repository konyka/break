# Plugins / CaptureProtocolStack

- module root: `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureProtocolStack`
- headers: 27; symbols: 1010
- symbol kinds: class=81, delegate=11, enum=7, enumerator=30, externvar=179, function=7, macro=14, member=200, namespace=74, prototype=353, struct=21, typedef=32, variable=1
- PrivateDependencyModuleNames: CoreUObject, Engine, Json, JsonUtilities, Networking, Sockets
- PublicDependencyModuleNames: CaptureUtils, Core

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureProtocolStack/Private/Control/Capabilities/Utils.h` (Private)


#### struct `UE::CaptureManager::FCapabilityUtilities`  
`struct FCapabilityUtilities`  
_L15-27_
- L17 _public prototype_ `static TProtocolResult<void> TypeStringToEnum(const FString& InTypeString, ECapabilityValue::Type& OutType);`
- L18 _public prototype_ `static TProtocolResult<void> ValueFromJsonObject(const TSharedPtr<FJsonObject>& InJsonObject, const FString& InKey, const ECapabilityValue::Type InType, FCapabilityValue& OutValue);`
- L22 _public prototype_ `static void SetProperJsonFieldType(const FString& InKey, const FCapabilityValue& InValue, TSharedPtr<FJsonObject>& OutJsonObjectPtr);`
- L26 _public prototype_ `static ECapabilityValue::Type TypeFromVariant(const FCapabilityValue& InValue);`

#### Free symbols / members of external scopes

- L11 _macro_ `#define CPS_API CAPTUREPROTOCOLSTACK_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace CaptureManager` (scope `UE`)

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureProtocolStack/Private/Control/Messages/ProtocolConstants.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace CaptureManager` (scope `UE`)
- L7 _namespace_ `namespace CPS` (scope `UE::CaptureManager`)
- L7 _namespace_ `namespace AddressPaths` (scope `UE::CaptureManager::CPS`)
- L10 _externvar_ `extern const TCHAR* GCapabilitiesRoot;` (scope `UE::CaptureManager::CPS::AddressPaths`) — Capabilities
- L11 _externvar_ `extern const TCHAR* GCapabilitiesListAll;` (scope `UE::CaptureManager::CPS::AddressPaths`)
- L12 _externvar_ `extern const TCHAR* GCapabilityProperties;` (scope `UE::CaptureManager::CPS::AddressPaths`)
- L13 _externvar_ `extern const TCHAR* GCapabilityPropertySet;` (scope `UE::CaptureManager::CPS::AddressPaths`)
- L14 _externvar_ `extern const TCHAR* GCapabilityPropertyGet;` (scope `UE::CaptureManager::CPS::AddressPaths`)
- L15 _externvar_ `extern const TCHAR* GCapabilityCommands;` (scope `UE::CaptureManager::CPS::AddressPaths`)
- L16 _externvar_ `extern const TCHAR* GCapabilityCommandExecute;` (scope `UE::CaptureManager::CPS::AddressPaths`)
- L17 _externvar_ `extern const TCHAR* GCapabilityEvents;` (scope `UE::CaptureManager::CPS::AddressPaths`)
- L18 _externvar_ `extern const TCHAR* GCapabilityEventSubscribe;` (scope `UE::CaptureManager::CPS::AddressPaths`)
- L19 _externvar_ `extern const TCHAR* GCapabilityEventUnsubscribe;` (scope `UE::CaptureManager::CPS::AddressPaths`)
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace CaptureManager` (scope `UE`)
- L22 _namespace_ `namespace CPS` (scope `UE::CaptureManager`)
- L22 _namespace_ `namespace Capabilities` (scope `UE::CaptureManager::CPS`)
- L24 _externvar_ `extern const TCHAR* GId;` (scope `UE::CaptureManager::CPS::Capabilities`)
- L25 _externvar_ `extern const TCHAR* GName;` (scope `UE::CaptureManager::CPS::Capabilities`)
- L26 _externvar_ `extern const TCHAR* GValue;` (scope `UE::CaptureManager::CPS::Capabilities`)
- L27 _externvar_ `extern const TCHAR* GArguments;` (scope `UE::CaptureManager::CPS::Capabilities`)
- L28 _externvar_ `extern const TCHAR* GParameters;` (scope `UE::CaptureManager::CPS::Capabilities`)
- L29 _externvar_ `extern const TCHAR* GProperties;` (scope `UE::CaptureManager::CPS::Capabilities`)
- L30 _externvar_ `extern const TCHAR* GType;` (scope `UE::CaptureManager::CPS::Capabilities`)
- L31 _externvar_ `extern const TCHAR* GAccess;` (scope `UE::CaptureManager::CPS::Capabilities`)
- L32 _externvar_ `extern const TCHAR* GReadOnly;` (scope `UE::CaptureManager::CPS::Capabilities`)
- L33 _externvar_ `extern const TCHAR* GReadWrite;` (scope `UE::CaptureManager::CPS::Capabilities`)
- L34 _externvar_ `extern const TCHAR* GMin;` (scope `UE::CaptureManager::CPS::Capabilities`)
- L35 _externvar_ `extern const TCHAR* GMax;` (scope `UE::CaptureManager::CPS::Capabilities`)
- L36 _externvar_ `extern const TCHAR* GEnumOptions;` (scope `UE::CaptureManager::CPS::Capabilities`)
- L37 _externvar_ `extern const TCHAR* GCurrentValue;` (scope `UE::CaptureManager::CPS::Capabilities`)
- L38 _externvar_ `extern const TCHAR* GGet;` (scope `UE::CaptureManager::CPS::Capabilities`)
- L39 _externvar_ `extern const TCHAR* GSet;` (scope `UE::CaptureManager::CPS::Capabilities`)
- L40 _externvar_ `extern const TCHAR* GCommands;` (scope `UE::CaptureManager::CPS::Capabilities`)
- L41 _externvar_ `extern const TCHAR* GExecute;` (scope `UE::CaptureManager::CPS::Capabilities`)
- L42 _externvar_ `extern const TCHAR* GOptional;` (scope `UE::CaptureManager::CPS::Capabilities`)
- L43 _externvar_ `extern const TCHAR* GReturnType;` (scope `UE::CaptureManager::CPS::Capabilities`)
- L44 _externvar_ `extern const TCHAR* GDefaultValue;` (scope `UE::CaptureManager::CPS::Capabilities`)
- L45 _externvar_ `extern const TCHAR* GEvents;` (scope `UE::CaptureManager::CPS::Capabilities`)
- L46 _externvar_ `extern const TCHAR* GSubscribe;` (scope `UE::CaptureManager::CPS::Capabilities`)
- L47 _externvar_ `extern const TCHAR* GUnsubscribe;` (scope `UE::CaptureManager::CPS::Capabilities`)
- L48 _externvar_ `extern const TCHAR* GBoolean;` (scope `UE::CaptureManager::CPS::Capabilities`)
- L49 _externvar_ `extern const TCHAR* GInteger;` (scope `UE::CaptureManager::CPS::Capabilities`)
- L50 _externvar_ `extern const TCHAR* GFloat;` (scope `UE::CaptureManager::CPS::Capabilities`)
- L51 _externvar_ `extern const TCHAR* GString;` (scope `UE::CaptureManager::CPS::Capabilities`)
- L52 _externvar_ `extern const TCHAR* GEnumeration;` (scope `UE::CaptureManager::CPS::Capabilities`)

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureProtocolStack/Private/ExportClient/Definitions.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace CaptureManager` (scope `UE`)
- L10 _variable_ `static constexpr uint32 InactivityTimeoutMs = 15000;` (scope `UE::CaptureManager`) — 15 seconds as recommended by the CPS Specification

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureProtocolStack/Public/Control/Capabilities/Capability.h` (Public)


#### enum `UE::CaptureManager::ECapabilityValue::Type`  
`enum Type`  
_L15-22_
- L17 _public enumerator_ `Boolean`
- L18 _public enumerator_ `Integer`
- L19 _public enumerator_ `Float`
- L20 _public enumerator_ `String`
- L21 _public enumerator_ `Enum`

#### enum `UE::CaptureManager::ECapabilityAccess::Type`  
`enum Type`  
_L27-31_
- L29 _public enumerator_ `ReadOnly = 0`
- L30 _public enumerator_ `ReadWrite = 1`

#### struct `UE::CaptureManager::FCapabilityProperty`  
`struct FCapabilityProperty`  
_L38-48_
- L40 _public member_ `FString Id;`
- L41 _public member_ `FString Name;`
- L42 _public member_ `ECapabilityValue::Type Type;`
- L43 _public member_ `ECapabilityAccess::Type Access;`
- L44 _public member_ `TOptional<TVariant<int32, float>> Min;`
- L45 _public member_ `TOptional<TVariant<int32, float>> Max;`
- L46 _public member_ `TOptional<TArray<FString>> EnumOptions;`
- L47 _public member_ `FCapabilityValue CurrentValue;`

#### struct `UE::CaptureManager::FCommandParameterDescriptor`  
`struct FCommandParameterDescriptor`  
_L50-56_
- L52 _public member_ `FString Name;`
- L53 _public member_ `ECapabilityValue::Type Type;`
- L54 _public member_ `bool Optional;`
- L55 _public member_ `FCapabilityValue DefaultValue;`

#### struct `UE::CaptureManager::FCapabilityCommand`  
`struct FCapabilityCommand`  
_L58-65_
- L60 _public member_ `FString Id;`
- L61 _public member_ `FString Name;`
- L63 _public member_ `TArray<FCommandParameterDescriptor> Parameters;`
- L64 _public member_ `TOptional<ECapabilityValue::Type> ReturnType;`

#### struct `UE::CaptureManager::FEventArgumentDescriptor`  
`struct FEventArgumentDescriptor`  
_L67-71_
- L69 _public member_ `FString Name;`
- L70 _public member_ `ECapabilityValue::Type Type;`

#### struct `UE::CaptureManager::FCapabilityEvent`  
`struct FCapabilityEvent`  
_L73-79_
- L75 _public member_ `FString Id;`
- L76 _public member_ `FString Name;`
- L78 _public member_ `TArray<FEventArgumentDescriptor> Arguments;`

#### struct `UE::CaptureManager::FCapability`  
`struct FCapability`  
_L81-88_
- L83 _public member_ `FString Id;`
- L84 _public member_ `FString Name;`
- L85 _public member_ `TMap<FString, FCapabilityProperty> Properties;`
- L86 _public member_ `TMap<FString, FCapabilityCommand> Commands;`
- L87 _public member_ `TMap<FString, FCapabilityEvent> Events;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace CaptureManager` (scope `UE`)
- L13 _namespace_ `namespace ECapabilityValue` (scope `UE::CaptureManager`)
- L25 _namespace_ `namespace ECapabilityAccess` (scope `UE::CaptureManager`)
- L34 _typedef_ `using FCapabilityValue = TVariant<bool, int32, float, FString>;` (scope `UE::CaptureManager`)
- L36 _typedef_ `using FCapabilityValues = TMap<FString, FCapabilityValue>;` (scope `UE::CaptureManager`)

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureProtocolStack/Public/Control/Communication/ControlCommunication.h` (Public)


#### class `UE::CaptureManager::FControlCommunication`  
`class FControlCommunication final`  
_L19-82_
- L23 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnPacketReceived, FControlPacket InPacket) DECLARE_DELEGATE(FCommunicationStoppedHandler) FControlCommunication();`
- L28 _public prototype_ `TProtocolResult<void> Init();`
- L29 _public prototype_ `TProtocolResult<void> Start(const FString& InServerIp, const uint16 InServerPort);`
- L30 _public prototype_ `void Stop();`
- L32 _public prototype_ `bool IsRunning() const;`
- L34 _public prototype_ `void SendMessage(FControlPacket InMessage);`
- L36 _public prototype_ `void SetReceiveHandler(FOnPacketReceived InReceiveHandler);`
- L37 _public prototype_ `void SetCommunicationStoppedHandler(FCommunicationStoppedHandler InConnectionStateHandler);`
- L63 _private prototype_ `void RunnableHandler(TSharedPtr<FRunnable> InRunnable);`
- L64 _private prototype_ `void CommunicationRunnableStopped();`
- L66 _private prototype_ `void SendNextPacket();`
- L67 _private prototype_ `void SendPacket(FControlPacket InPacket);`
- L68 _private prototype_ `void ReceiveNextPacket();`
- L70 _private prototype_ `TProtocolResult<FControlPacketHeader> ReceiveControlHeader();`
- L71 _private prototype_ `TProtocolResult<void> ReceiveControlPacket(const FControlPacketHeader& InHeader);`
- L73 _private member_ `FTcpClient Client;`
- L74 _private member_ `FOnPacketReceived ReceiveHandler;`
- L75 _private member_ `FCommunicationStoppedHandler CommunicationStoppedHandler;`
- L77 _private member_ `TQueue<FControlPacket> SenderQueue;`
- L78 _private member_ `std::atomic_int SenderQueueCurrentSize = 0;`
- L79 _private member_ `TQueue<FControlPacket> ReceiverQueue;`
- L80 _private member_ `TQueueRunner<TSharedPtr<FRunnable>> SynchronizedRunnable;`
- L81 _private member_ `TWeakPtr<FCommunicationRunnable> Runnable;`

#### class `UE::CaptureManager::FControlCommunication::FCommunicationRunnable`  
`class FCommunicationRunnable : public FRunnable`  
_L41-60_
- inherits: `FRunnable`
- L45 _public prototype_ `FCommunicationRunnable(FControlCommunication& InCommunication);`
- L46 _public prototype_ `virtual ~FCommunicationRunnable();`
- L48 _public prototype_ `uint32 Run() override;`
- L49 _public prototype_ `void Stop() override;`
- L51 _public prototype_ `void Join();`
- L55 _private prototype_ `void HandleError(const FCaptureProtocolError& Error);`
- L57 _private member_ `FControlCommunication& Communication;`
- L58 _private member_ `bool bIsRunning;`
- L59 _private member_ `FEventRef DoneEvent;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace CaptureManager` (scope `UE`)
- L23 _delegate_ `DECLARE_DELEGATE_OneParam(FOnPacketReceived, FControlPacket InPacket) DECLARE_DELEGATE(FCommunicationStoppedHandler) FControlCommunication();`
- L24 _delegate_ `DECLARE_DELEGATE(FCommunicationStoppedHandler) FControlCommunication();`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureProtocolStack/Public/Control/Communication/ControlPacket.h` (Public)


#### class `UE::CaptureManager::FControlPacketHeader`  
`class FControlPacketHeader final`  
_L16-36_
- L20 _public member_ `static const TArray<uint8> Header;`
- L22 _public prototype_ `static TProtocolResult<FControlPacketHeader> Deserialize(ITcpSocketReader& InReader, uint32 InTimeoutForControlHeader = ITcpSocketReader::DefaultWaitTimeoutMs);`
- L24 _public prototype_ `static uint32 GetHeaderSize();`
- L26 _public prototype_ `FControlPacketHeader();`
- L27 _public prototype_ `FControlPacketHeader(uint16 InVersion, uint32 InPayloadSize);`
- L29 _public prototype_ `uint16 GetVersion() const;`
- L30 _public prototype_ `uint32 GetPayloadSize() const;`
- L34 _private member_ `uint16 Version = 0;`
- L35 _private member_ `uint32 PayloadSize = 0;`

#### class `UE::CaptureManager::FControlPacket`  
`class FControlPacket final`  
_L38-62_
- L42 _public prototype_ `static TProtocolResult<FControlPacket> Deserialize(const FControlPacketHeader& InPacketHeader, ITcpSocketReader& InReader);`
- L43 _public prototype_ `static TProtocolResult<void> Serialize(const FControlPacket& InMessage, ITcpSocketWriter& InWriter);`
- L45 _public prototype_ `FControlPacket();`
- L46 _public prototype_ `FControlPacket(uint16 InVersion, TArray<uint8> InPayload);`
- L48 _public prototype_ `FControlPacket(const FControlPacket& InOther) = default;`
- L49 _public prototype_ `FControlPacket(FControlPacket&& InOther) = default;`
- L51 _public prototype_ `FControlPacket& operator=(const FControlPacket& InOther) = default;`
- L52 _public prototype_ `FControlPacket& operator=(FControlPacket&& InOther) = default;`
- L54 _public prototype_ `uint16 GetVersion() const;`
- L55 _public prototype_ `const TArray<uint8>& GetPayload() const;`
- L56 _public prototype_ `uint32 GetPayloadSize() const;`
- L60 _private member_ `FControlPacketHeader Header;`
- L61 _private member_ `TArray<uint8> Payload;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace CaptureManager` (scope `UE`)

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureProtocolStack/Public/Control/ControlMessenger.h` (Public)


#### class `UE::CaptureManager::FKeepAliveCounter`  
`class FKeepAliveCounter`  
_L29-41_
- L32 _public prototype_ `FKeepAliveCounter();`
- L34 _public prototype_ `void Increment();`
- L35 _public prototype_ `void Reset();`
- L36 _public prototype_ `bool HasReached(uint16 InBound);`
- L40 _private member_ `std::atomic<uint16> Counter;`

#### class `UE::CaptureManager::FControlMessenger`  
`class FControlMessenger final`  
_L43-210_
- L48 _public typedef_ `template<class RequestType> using FOnControlResponse = TDelegate<void(TProtocolResult<typename RequestType::ResponseType> InResult)>;`
- L50 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnDisconnect, const FString& InCause);`
- L52 _public member_ `static constexpr int32 ResponseWaitTime = 3;` — Seconds
- L53 _public member_ `static constexpr int32 KeepAliveInterval = 5;` — Seconds
- L54 _public member_ `static const TCHAR* HandshakeSessionId;`
- L56 _public prototype_ `FControlMessenger();`
- L57 _public prototype_ `~FControlMessenger();`
- L59 _public prototype_ `void RegisterUpdateHandler(FString InAddressPath, FControlUpdate::FOnUpdateMessage InUpdateHandler);`
- L60 _public prototype_ `void RegisterDisconnectHandler(FOnDisconnect InOnDisconnectHandler);`
- L62 _public prototype_ `TProtocolResult<void> Start(const FString& InServerIp, const uint16 InServerPort);`
- L63 _public prototype_ `void Stop();`
- L65 _public prototype_ `TProtocolResult<void> StartSession();`
- L66 _public prototype_ `TProtocolResult<FGetServerInformationResponse> GetServerInformation();`
- L67 _public prototype_ `TProtocolResult<FGetTakeListResponse> GetTakeList();`
- L70 _public function_ `template<class RequestType> TProtocolResult<typename RequestType::ResponseType> SendRequest(RequestType InRequest)`
- L153 _public function_ `template<class RequestType> void SendAsyncRequest(RequestType InRequest, FOnControlResponse<RequestType> InOnResponse)`
- L179 _private prototype_ `void SendPacket(FControlPacket InPacket);`
- L180 _private prototype_ `void KeepAlive();`
- L181 _private prototype_ `void MessageHandler(FControlPacket InPacket);`
- L182 _private prototype_ `void CommunicationStoppedHandler();`
- L184 _private prototype_ `uint32 GenerateTransactionId() const;`
- L185 _private prototype_ `uint64 GetTimestamp() const;`
- L187 _private prototype_ `void StartKeepAliveTimer();`
- L188 _private prototype_ `void StopKeepAliveTimer();`
- L190 _private prototype_ `void OnAsyncRequestProcess(FAsyncRequestDelegate InAsyncDelegate);`
- L192 _private member_ `FControlCommunication Communication;`
- L194 _private member_ `FCriticalSection SessionIdMutex;`
- L195 _private member_ `FString SessionId;`
- L197 _private member_ `FCriticalSection RequestsMutex;`
- L198 _private member_ `TMap<uint32, TUniquePtr<FRequestContext>> RequestContexts;`
- L200 _private member_ `FCriticalSection UpdatesMutex;`
- L201 _private member_ `TMap<FString, FControlUpdate::FOnUpdateMessage> UpdateHandlers;`
- L203 _private member_ `FCaptureTimerManager::FTimerHandle KeepAliveTimer;`
- L204 _private member_ `FKeepAliveCounter KeepAliveFailures;`
- L206 _private member_ `TQueueRunner<FAsyncRequestDelegate> AsyncRequestRunner;`
- L207 _private member_ `FOnDisconnect OnDisconnectHandler;`
- L209 _private member_ `mutable std::atomic<uint32> NextTransactionId{0};`

#### struct `UE::CaptureManager::FControlMessenger::FRequestContext`  
`struct FRequestContext`  
_L166-177_
- L168 _public function_ `FRequestContext(FControlMessage InRequest, TPromise<TProtocolResult<FControlMessage>> InPromise) : Request(MoveTemp(InRequest)) , Promise(MoveTemp(InPromise))`
- L174 _public member_ `FControlMessage Request;`
- L176 _public member_ `TPromise<TProtocolResult<FControlMessage>> Promise;`

#### Free symbols / members of external scopes

- L24 _macro_ `#define UE_API CAPTUREPROTOCOLSTACK_API`
- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace CaptureManager` (scope `UE`)
- L50 _delegate_ `DECLARE_DELEGATE_OneParam(FOnDisconnect, const FString& InCause);`
- L156 _function_ `` (scope `UE::CaptureManager::FControlMessenger::SendAsyncRequest`)
- L164 _delegate_ `DECLARE_DELEGATE(FAsyncRequestDelegate) struct FRequestContext { FRequestContext(FControlMessage InRequest, TPromise<TProtocolResult<FControlMessage>> InPromise) : Request(MoveTemp(InRequest)) , Promise(MoveTemp(InPromise)) { } FControlMessage Request; TPromise<TProtocolResult<FControlMessage>> Promise; };`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureProtocolStack/Public/Control/Messages/Constants.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace CaptureManager` (scope `UE`)
- L7 _namespace_ `namespace CPS` (scope `UE::CaptureManager`)
- L7 _namespace_ `namespace AddressPaths` (scope `UE::CaptureManager::CPS`)
- L10 _externvar_ `extern const TCHAR* GKeepAlive;` (scope `UE::CaptureManager::CPS::AddressPaths`) — Requests/Responses
- L11 _externvar_ `extern const TCHAR* GStartSession;` (scope `UE::CaptureManager::CPS::AddressPaths`)
- L12 _externvar_ `extern const TCHAR* GStopSession;` (scope `UE::CaptureManager::CPS::AddressPaths`)
- L13 _externvar_ `extern const TCHAR* GSubscribe;` (scope `UE::CaptureManager::CPS::AddressPaths`)
- L14 _externvar_ `extern const TCHAR* GUnsubscribe;` (scope `UE::CaptureManager::CPS::AddressPaths`)
- L15 _externvar_ `extern const TCHAR* GGetServerInformation;` (scope `UE::CaptureManager::CPS::AddressPaths`)
- L16 _externvar_ `extern const TCHAR* GGetState;` (scope `UE::CaptureManager::CPS::AddressPaths`)
- L17 _externvar_ `extern const TCHAR* GStartRecordingTake;` (scope `UE::CaptureManager::CPS::AddressPaths`)
- L18 _externvar_ `extern const TCHAR* GStopRecordingTake;` (scope `UE::CaptureManager::CPS::AddressPaths`)
- L19 _externvar_ `extern const TCHAR* GAbortRecordingTake;` (scope `UE::CaptureManager::CPS::AddressPaths`)
- L20 _externvar_ `extern const TCHAR* GGetTakeList;` (scope `UE::CaptureManager::CPS::AddressPaths`)
- L21 _externvar_ `extern const TCHAR* GGetTakeMetadata;` (scope `UE::CaptureManager::CPS::AddressPaths`)
- L22 _externvar_ `extern const TCHAR* GExportTakeData;` (scope `UE::CaptureManager::CPS::AddressPaths`)
- L23 _externvar_ `extern const TCHAR* GExportTakeVideoFrame;` (scope `UE::CaptureManager::CPS::AddressPaths`)
- L24 _externvar_ `extern const TCHAR* GExportCameraFeedFrame;` (scope `UE::CaptureManager::CPS::AddressPaths`)
- L25 _externvar_ `extern const TCHAR* GPauseExport;` (scope `UE::CaptureManager::CPS::AddressPaths`)
- L26 _externvar_ `extern const TCHAR* GCancelExport;` (scope `UE::CaptureManager::CPS::AddressPaths`)
- L27 _externvar_ `extern const TCHAR* GGetStreamingSubjects;` (scope `UE::CaptureManager::CPS::AddressPaths`)
- L28 _externvar_ `extern const TCHAR* GStartStreaming;` (scope `UE::CaptureManager::CPS::AddressPaths`)
- L29 _externvar_ `extern const TCHAR* GStopStreaming;` (scope `UE::CaptureManager::CPS::AddressPaths`)
- L32 _externvar_ `extern const TCHAR* GSessionStopped;` (scope `UE::CaptureManager::CPS::AddressPaths`) — Updates
- L33 _externvar_ `extern const TCHAR* GRecordingStatus;` (scope `UE::CaptureManager::CPS::AddressPaths`)
- L34 _externvar_ `extern const TCHAR* GTakeAdded;` (scope `UE::CaptureManager::CPS::AddressPaths`)
- L35 _externvar_ `extern const TCHAR* GTakeRemoved;` (scope `UE::CaptureManager::CPS::AddressPaths`)
- L36 _externvar_ `extern const TCHAR* GTakeUpdated;` (scope `UE::CaptureManager::CPS::AddressPaths`)
- L39 _externvar_ `extern const TCHAR* GCapabilitiesRoot;` (scope `UE::CaptureManager::CPS::AddressPaths`) — Capabilities
- L40 _externvar_ `extern const TCHAR* GCapabilitiesListAll;` (scope `UE::CaptureManager::CPS::AddressPaths`)
- L41 _externvar_ `extern const TCHAR* GCapabilityProperties;` (scope `UE::CaptureManager::CPS::AddressPaths`)
- L42 _externvar_ `extern const TCHAR* GCapabilityPropertySet;` (scope `UE::CaptureManager::CPS::AddressPaths`)
- L43 _externvar_ `extern const TCHAR* GCapabilityPropertyGet;` (scope `UE::CaptureManager::CPS::AddressPaths`)
- L44 _externvar_ `extern const TCHAR* GCapabilityCommands;` (scope `UE::CaptureManager::CPS::AddressPaths`)
- L45 _externvar_ `extern const TCHAR* GCapabilityCommandExecute;` (scope `UE::CaptureManager::CPS::AddressPaths`)
- L46 _externvar_ `extern const TCHAR* GCapabilityEvents;` (scope `UE::CaptureManager::CPS::AddressPaths`)
- L47 _externvar_ `extern const TCHAR* GCapabilityEventSubscribe;` (scope `UE::CaptureManager::CPS::AddressPaths`)
- L48 _externvar_ `extern const TCHAR* GCapabilityEventUnsubscribe;` (scope `UE::CaptureManager::CPS::AddressPaths`)
- L51 _externvar_ `extern const TCHAR* GDiskCapacity;` (scope `UE::CaptureManager::CPS::AddressPaths`) — Platform Specific: IOS
- L52 _externvar_ `extern const TCHAR* GBattery;` (scope `UE::CaptureManager::CPS::AddressPaths`)
- L53 _externvar_ `extern const TCHAR* GThermalState;` (scope `UE::CaptureManager::CPS::AddressPaths`)
- L56 _namespace_ `namespace UE`
- L56 _namespace_ `namespace CaptureManager` (scope `UE`)
- L56 _namespace_ `namespace CPS` (scope `UE::CaptureManager`)
- L56 _namespace_ `namespace Properties` (scope `UE::CaptureManager::CPS`)
- L60 _externvar_ `extern const TCHAR* GSessionId;` (scope `UE::CaptureManager::CPS::Properties`) — Keys Messages
- L61 _externvar_ `extern const TCHAR* GAddressPath;` (scope `UE::CaptureManager::CPS::Properties`)
- L62 _externvar_ `extern const TCHAR* GTransactionId;` (scope `UE::CaptureManager::CPS::Properties`)
- L63 _externvar_ `extern const TCHAR* GTimestamp;` (scope `UE::CaptureManager::CPS::Properties`)
- L64 _externvar_ `extern const TCHAR* GType;` (scope `UE::CaptureManager::CPS::Properties`)
- L65 _externvar_ `extern const TCHAR* GBody;` (scope `UE::CaptureManager::CPS::Properties`)
- L66 _externvar_ `extern const TCHAR* GError;` (scope `UE::CaptureManager::CPS::Properties`)
- L67 _externvar_ `extern const TCHAR* GDescription;` (scope `UE::CaptureManager::CPS::Properties`)
- L70 _externvar_ `extern const TCHAR* GSlateName;` (scope `UE::CaptureManager::CPS::Properties`) — Requests
- L71 _externvar_ `extern const TCHAR* GTakeNumber;` (scope `UE::CaptureManager::CPS::Properties`)
- L72 _externvar_ `extern const TCHAR* GSubject;` (scope `UE::CaptureManager::CPS::Properties`)
- L73 _externvar_ `extern const TCHAR* GScenario;` (scope `UE::CaptureManager::CPS::Properties`)
- L74 _externvar_ `extern const TCHAR* GTags;` (scope `UE::CaptureManager::CPS::Properties`)
- L75 _externvar_ `extern const TCHAR* GNames;` (scope `UE::CaptureManager::CPS::Properties`)
- L76 _externvar_ `extern const TCHAR* GTakeName;` (scope `UE::CaptureManager::CPS::Properties`)
- L77 _externvar_ `extern const TCHAR* GFiles;` (scope `UE::CaptureManager::CPS::Properties`)
- L78 _externvar_ `extern const TCHAR* GName;` (scope `UE::CaptureManager::CPS::Properties`)
- L79 _externvar_ `extern const TCHAR* GOffset;` (scope `UE::CaptureManager::CPS::Properties`)
- L80 _externvar_ `extern const TCHAR* GStreamPort;` (scope `UE::CaptureManager::CPS::Properties`)
- L81 _externvar_ `extern const TCHAR* GSubjectIds;` (scope `UE::CaptureManager::CPS::Properties`)
- L85 _externvar_ `extern const TCHAR* GId;` (scope `UE::CaptureManager::CPS::Properties`) — Responses
- L86 _externvar_ `extern const TCHAR* GModel;` (scope `UE::CaptureManager::CPS::Properties`)
- L87 _externvar_ `extern const TCHAR* GPlatformName;` (scope `UE::CaptureManager::CPS::Properties`)
- L88 _externvar_ `extern const TCHAR* GPlatformVersion;` (scope `UE::CaptureManager::CPS::Properties`)
- L89 _externvar_ `extern const TCHAR* GSoftwareName;` (scope `UE::CaptureManager::CPS::Properties`)
- L90 _externvar_ `extern const TCHAR* GSoftwareVersion;` (scope `UE::CaptureManager::CPS::Properties`)
- L91 _externvar_ `extern const TCHAR* GExportPort;` (scope `UE::CaptureManager::CPS::Properties`)
- L92 _externvar_ `extern const TCHAR* GIsRecording;` (scope `UE::CaptureManager::CPS::Properties`)
- L93 _externvar_ `extern const TCHAR* GPlatformState;` (scope `UE::CaptureManager::CPS::Properties`)
- L94 _externvar_ `extern const TCHAR* GTakes;` (scope `UE::CaptureManager::CPS::Properties`)
- L95 _externvar_ `extern const TCHAR* GDateTime;` (scope `UE::CaptureManager::CPS::Properties`)
- L96 _externvar_ `extern const TCHAR* GFrames;` (scope `UE::CaptureManager::CPS::Properties`)
- L97 _externvar_ `extern const TCHAR* GAppVersion;` (scope `UE::CaptureManager::CPS::Properties`)
- L98 _externvar_ `extern const TCHAR* GLength;` (scope `UE::CaptureManager::CPS::Properties`)
- L99 _externvar_ `extern const TCHAR* GVideo;` (scope `UE::CaptureManager::CPS::Properties`)
- L100 _externvar_ `extern const TCHAR* GFrameRate;` (scope `UE::CaptureManager::CPS::Properties`)
- L101 _externvar_ `extern const TCHAR* GHeight;` (scope `UE::CaptureManager::CPS::Properties`)
- L102 _externvar_ `extern const TCHAR* GWidth;` (scope `UE::CaptureManager::CPS::Properties`)
- L103 _externvar_ `extern const TCHAR* GAudio;` (scope `UE::CaptureManager::CPS::Properties`)
- L104 _externvar_ `extern const TCHAR* GChannels;` (scope `UE::CaptureManager::CPS::Properties`)
- L105 _externvar_ `extern const TCHAR* GSampleRate;` (scope `UE::CaptureManager::CPS::Properties`)
- L106 _externvar_ `extern const TCHAR* GBitsPerChannel;` (scope `UE::CaptureManager::CPS::Properties`)
- L107 _externvar_ `extern const TCHAR* GSubjects;` (scope `UE::CaptureManager::CPS::Properties`)
- L108 _externvar_ `extern const TCHAR* GControls;` (scope `UE::CaptureManager::CPS::Properties`)
- L109 _externvar_ `extern const TCHAR* GVersion;` (scope `UE::CaptureManager::CPS::Properties`)
- L110 _externvar_ `extern const TCHAR* GAnimationMetadata;` (scope `UE::CaptureManager::CPS::Properties`)
- L113 _externvar_ `extern const TCHAR* GTotalCapacity;` (scope `UE::CaptureManager::CPS::Properties`) — Platform Specific: iOS
- L114 _externvar_ `extern const TCHAR* GRemainingCapacity;` (scope `UE::CaptureManager::CPS::Properties`)
- L115 _externvar_ `extern const TCHAR* GBatteryLevel;` (scope `UE::CaptureManager::CPS::Properties`)
- L116 _externvar_ `extern const TCHAR* GThermalState;` (scope `UE::CaptureManager::CPS::Properties`)
- L118 _externvar_ `extern const TCHAR* GTotal;` (scope `UE::CaptureManager::CPS::Properties`)
- L119 _externvar_ `extern const TCHAR* GRemaining;` (scope `UE::CaptureManager::CPS::Properties`)
- L120 _externvar_ `extern const TCHAR* GLevel;` (scope `UE::CaptureManager::CPS::Properties`)
- L121 _externvar_ `extern const TCHAR* GState;` (scope `UE::CaptureManager::CPS::Properties`)
- L125 _externvar_ `extern const TCHAR* GRequest;` (scope `UE::CaptureManager::CPS::Properties`) — Values Messages
- L126 _externvar_ `extern const TCHAR* GResponse;` (scope `UE::CaptureManager::CPS::Properties`)
- L127 _externvar_ `extern const TCHAR* GUpdate;` (scope `UE::CaptureManager::CPS::Properties`)
- L129 _externvar_ `extern const TCHAR* GIOS;` (scope `UE::CaptureManager::CPS::Properties`)
- L130 _externvar_ `extern const TCHAR* GAndroid;` (scope `UE::CaptureManager::CPS::Properties`)
- L131 _externvar_ `extern const TCHAR* GWindows;` (scope `UE::CaptureManager::CPS::Properties`)
- L132 _externvar_ `extern const TCHAR* GWindowsServer;` (scope `UE::CaptureManager::CPS::Properties`)
- L133 _externvar_ `extern const TCHAR* GLinux;` (scope `UE::CaptureManager::CPS::Properties`)
- L134 _externvar_ `extern const TCHAR* GMacOS;` (scope `UE::CaptureManager::CPS::Properties`)
- L137 _externvar_ `extern const TCHAR* GNominal;` (scope `UE::CaptureManager::CPS::Properties`) — Platform Specific: iOS
- L138 _externvar_ `extern const TCHAR* GFair;` (scope `UE::CaptureManager::CPS::Properties`)
- L139 _externvar_ `extern const TCHAR* GSerious;` (scope `UE::CaptureManager::CPS::Properties`)
- L140 _externvar_ `extern const TCHAR* GCritical;` (scope `UE::CaptureManager::CPS::Properties`)
- L143 _namespace_ `namespace UE`
- L143 _namespace_ `namespace CaptureManager` (scope `UE`)
- L143 _namespace_ `namespace CPS` (scope `UE::CaptureManager`)
- L143 _namespace_ `namespace ErrorNames` (scope `UE::CaptureManager::CPS`)
- L145 _externvar_ `extern const TCHAR* GUnsupportedProtocolVersion;` (scope `UE::CaptureManager::CPS::ErrorNames`)
- L146 _externvar_ `extern const TCHAR* GRequestFailed;` (scope `UE::CaptureManager::CPS::ErrorNames`)
- L147 _externvar_ `extern const TCHAR* GRequestParsingFailed;` (scope `UE::CaptureManager::CPS::ErrorNames`)
- L148 _externvar_ `extern const TCHAR* GNotSupported;` (scope `UE::CaptureManager::CPS::ErrorNames`)
- L149 _externvar_ `extern const TCHAR* GNoSession;` (scope `UE::CaptureManager::CPS::ErrorNames`)
- L150 _externvar_ `extern const TCHAR* GMissingBody;` (scope `UE::CaptureManager::CPS::ErrorNames`)
- L153 _namespace_ `namespace UE`
- L153 _namespace_ `namespace CaptureManager` (scope `UE`)
- L153 _namespace_ `namespace CPS` (scope `UE::CaptureManager`)
- L153 _namespace_ `namespace Capabilities` (scope `UE::CaptureManager::CPS`)
- L155 _externvar_ `extern const TCHAR* GId;` (scope `UE::CaptureManager::CPS::Capabilities`)
- L156 _externvar_ `extern const TCHAR* GName;` (scope `UE::CaptureManager::CPS::Capabilities`)
- L157 _externvar_ `extern const TCHAR* GValue;` (scope `UE::CaptureManager::CPS::Capabilities`)
- L158 _externvar_ `extern const TCHAR* GProperties;` (scope `UE::CaptureManager::CPS::Capabilities`)
- L159 _externvar_ `extern const TCHAR* GType;` (scope `UE::CaptureManager::CPS::Capabilities`)
- L160 _externvar_ `extern const TCHAR* GAccess;` (scope `UE::CaptureManager::CPS::Capabilities`)
- L161 _externvar_ `extern const TCHAR* GReadOnly;` (scope `UE::CaptureManager::CPS::Capabilities`)
- L162 _externvar_ `extern const TCHAR* GReadWrite;` (scope `UE::CaptureManager::CPS::Capabilities`)
- L163 _externvar_ `extern const TCHAR* GEnumOptions;` (scope `UE::CaptureManager::CPS::Capabilities`)
- L164 _externvar_ `extern const TCHAR* GCurrentValue;` (scope `UE::CaptureManager::CPS::Capabilities`)
- L165 _externvar_ `extern const TCHAR* GMin;` (scope `UE::CaptureManager::CPS::Capabilities`)
- L166 _externvar_ `extern const TCHAR* GMax;` (scope `UE::CaptureManager::CPS::Capabilities`)
- L167 _externvar_ `extern const TCHAR* GGet;` (scope `UE::CaptureManager::CPS::Capabilities`)
- L168 _externvar_ `extern const TCHAR* GSet;` (scope `UE::CaptureManager::CPS::Capabilities`)
- L169 _externvar_ `extern const TCHAR* GCommands;` (scope `UE::CaptureManager::CPS::Capabilities`)
- L170 _externvar_ `extern const TCHAR* GParameters;` (scope `UE::CaptureManager::CPS::Capabilities`)
- L171 _externvar_ `extern const TCHAR* GExecute;` (scope `UE::CaptureManager::CPS::Capabilities`)
- L172 _externvar_ `extern const TCHAR* GOptional;` (scope `UE::CaptureManager::CPS::Capabilities`)
- L173 _externvar_ `extern const TCHAR* GReturnType;` (scope `UE::CaptureManager::CPS::Capabilities`)
- L174 _externvar_ `extern const TCHAR* GDefaultValue;` (scope `UE::CaptureManager::CPS::Capabilities`)
- L175 _externvar_ `extern const TCHAR* GEvents;` (scope `UE::CaptureManager::CPS::Capabilities`)
- L176 _externvar_ `extern const TCHAR* GArguments;` (scope `UE::CaptureManager::CPS::Capabilities`)
- L177 _externvar_ `extern const TCHAR* GSubscribe;` (scope `UE::CaptureManager::CPS::Capabilities`)
- L178 _externvar_ `extern const TCHAR* GUnsubscribe;` (scope `UE::CaptureManager::CPS::Capabilities`)
- L179 _externvar_ `extern const TCHAR* GBoolean;` (scope `UE::CaptureManager::CPS::Capabilities`)
- L180 _externvar_ `extern const TCHAR* GInteger;` (scope `UE::CaptureManager::CPS::Capabilities`)
- L181 _externvar_ `extern const TCHAR* GFloat;` (scope `UE::CaptureManager::CPS::Capabilities`)
- L182 _externvar_ `extern const TCHAR* GString;` (scope `UE::CaptureManager::CPS::Capabilities`)
- L183 _externvar_ `extern const TCHAR* GEnumeration;` (scope `UE::CaptureManager::CPS::Capabilities`)

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureProtocolStack/Public/Control/Messages/ControlJsonUtilities.h` (Public)


#### class `UE::CaptureManager::FJsonUtility`  
`class FJsonUtility final`  
_L20-40_
- L23 _public prototype_ `static bool CreateJsonFromUTF8Data(const TArray<uint8>& InData, TSharedPtr<FJsonObject>& OutObject);`
- L24 _public prototype_ `static bool CreateUTF8DataFromJson(TSharedPtr<FJsonObject> InObject, TArray<uint8>& OutData);`
- L27 _public function_ `template <typename T> static TProtocolResult<void> ParseNumber(const TSharedPtr<FJsonObject>& InBody, const FString& InFieldName, T& OutFieldValue)`
- L36 _public prototype_ `static TProtocolResult<void> ParseString(const TSharedPtr<FJsonObject>& InBody, const FString& InFieldName, FString& OutFieldValue);`
- L37 _public prototype_ `static TProtocolResult<void> ParseBool(const TSharedPtr<FJsonObject>& InBody, const FString& InFieldName, bool& OutFieldValue);`
- L38 _public prototype_ `static TProtocolResult<void> ParseObject(const TSharedPtr<FJsonObject>& InBody, const FString& InFieldName, const TSharedPtr<FJsonObject>*& OutFieldValue);`
- L39 _public prototype_ `static TProtocolResult<void> ParseArray(const TSharedPtr<FJsonObject>& InBody, const FString& InFieldName, const TArray<TSharedPtr<FJsonValue>>*& OutFieldValue);`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API CAPTUREPROTOCOLSTACK_API`
- L15 _macro_ `#define CHECK_PARSE CPS_CHECK_VOID_RESULT`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace CaptureManager` (scope `UE`)

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureProtocolStack/Public/Control/Messages/ControlMessage.h` (Public)


#### class `UE::CaptureManager::FControlMessage`  
`class FControlMessage final`  
_L12-77_
- L25 _public prototype_ `FControlMessage(FString InAddressPath, EType InType, TSharedPtr<FJsonObject> InBody);`
- L27 _public prototype_ `FControlMessage(const FControlMessage& InOther) = default;`
- L28 _public prototype_ `FControlMessage(FControlMessage&& InOther) = default;`
- L30 _public prototype_ `FControlMessage& operator=(const FControlMessage& InOther) = default;`
- L31 _public prototype_ `FControlMessage& operator=(FControlMessage&& InOther) = default;`
- L33 _public prototype_ `static TProtocolResult<FControlMessage> Deserialize(const FControlPacket& InPacket);`
- L34 _public prototype_ `static TProtocolResult<FControlPacket> Serialize(const FControlMessage& InMessage);`
- L36 _public prototype_ `void SetSessionId(FString InSessionId);`
- L37 _public prototype_ `void SetTransactionId(uint32 InTrasactionId);`
- L38 _public prototype_ `void SetTimestamp(uint64 InTimestamp);`
- L40 _public prototype_ `const FString& GetSessionId() const;`
- L41 _public prototype_ `const FString& GetAddressPath() const;`
- L42 _public prototype_ `uint32 GetTransactionId() const;`
- L43 _public prototype_ `uint64 GetTimestamp() const;`
- L44 _public prototype_ `EType GetType() const;`
- L45 _public prototype_ `const TSharedPtr<FJsonObject>& GetBody() const;`
- L46 _public prototype_ `TSharedPtr<FJsonObject>& GetBody();`
- L48 _public prototype_ `const FString& GetErrorName() const;`
- L49 _public prototype_ `const FString& GetErrorDescription() const;`
- L59 _private prototype_ `FControlMessage(FString InSessionId, FString InAddressPath, uint32 InTransactionId, uint64 InTimestamp, EType InMessageType, TSharedPtr<FJsonObject> InBody, FErrorResponse InError);`
- L67 _private prototype_ `static EType DeserializeType(FString InMessageTypeStr);`
- L68 _private prototype_ `static FString SerializeType(EType InMessageType);`
- L70 _private member_ `FString SessionId;`
- L71 _private member_ `FString AddressPath;`
- L72 _private member_ `uint32 TransactionId = 0;`
- L73 _private member_ `uint64 Timestamp = 0;`
- L74 _private member_ `EType MessageType;`
- L75 _private member_ `TSharedPtr<FJsonObject> Body;`
- L76 _private member_ `FErrorResponse Error;`

#### enum `UE::CaptureManager::FControlMessage::EType`  
`enum class EType`  
_L16-23_
- L18 _public enumerator_ `Request`
- L19 _public enumerator_ `Response`
- L20 _public enumerator_ `Update`
- L22 _public enumerator_ `Invalid`

#### struct `UE::CaptureManager::FControlMessage::FErrorResponse`  
`struct FErrorResponse`  
_L53-57_
- L55 _public member_ `FString Name = TEXT("");`
- L56 _public member_ `FString Description = TEXT("");`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API CAPTUREPROTOCOLSTACK_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace CaptureManager` (scope `UE`)

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureProtocolStack/Public/Control/Messages/ControlRequest.h` (Public)


#### class `UE::CaptureManager::FControlRequest`  
`class FControlRequest`  
_L13-26_
- L17 _public prototype_ `FControlRequest(FString InAddressPath);`
- L18 _public prototype_ `virtual ~FControlRequest() = default;`
- L20 _public prototype_ `const FString& GetAddressPath() const;`
- L21 _public prototype_ `virtual TSharedPtr<FJsonObject> GetBody() const;`
- L25 _private member_ `FString AddressPath;`

#### class `UE::CaptureManager::FKeepAliveRequest`  
`class FKeepAliveRequest final : public FControlRequest`  
_L28-35_
- inherits: `FControlRequest`
- L32 _public typedef_ `using ResponseType = FKeepAliveResponse;`
- L34 _public prototype_ `FKeepAliveRequest();`

#### class `UE::CaptureManager::FStartSessionRequest`  
`class FStartSessionRequest final : public FControlRequest`  
_L37-44_
- inherits: `FControlRequest`
- L41 _public typedef_ `using ResponseType = FStartSessionResponse;`
- L43 _public prototype_ `FStartSessionRequest();`

#### class `UE::CaptureManager::FStopSessionRequest`  
`class FStopSessionRequest final : public FControlRequest`  
_L46-53_
- inherits: `FControlRequest`
- L50 _public typedef_ `using ResponseType = FStopSessionResponse;`
- L52 _public prototype_ `FStopSessionRequest();`

#### class `UE::CaptureManager::FGetServerInformationRequest`  
`class FGetServerInformationRequest final : public FControlRequest`  
_L56-63_
- inherits: `FControlRequest`
- L60 _public typedef_ `using ResponseType = FGetServerInformationResponse;`
- L62 _public prototype_ `FGetServerInformationRequest();`

#### class `UE::CaptureManager::FSubscribeRequest`  
`class FSubscribeRequest final : public FControlRequest`  
_L65-72_
- inherits: `FControlRequest`
- L69 _public typedef_ `using ResponseType = FSubscribeResponse;`
- L71 _public prototype_ `FSubscribeRequest();`

#### class `UE::CaptureManager::FUnsubscribeRequest`  
`class FUnsubscribeRequest final : public FControlRequest`  
_L74-81_
- inherits: `FControlRequest`
- L78 _public typedef_ `using ResponseType = FUnsubscribeResponse;`
- L80 _public prototype_ `FUnsubscribeRequest();`

#### class `UE::CaptureManager::FGetStateRequest`  
`class FGetStateRequest final : public FControlRequest`  
_L83-90_
- inherits: `FControlRequest`
- L87 _public typedef_ `using ResponseType = FGetStateResponse;`
- L89 _public prototype_ `FGetStateRequest();`

#### class `UE::CaptureManager::FStartRecordingTakeRequest`  
`class FStartRecordingTakeRequest final : public FControlRequest`  
_L92-113_
- inherits: `FControlRequest`
- L96 _public typedef_ `using ResponseType = FStartRecordingTakeResponse;`
- L98 _public prototype_ `FStartRecordingTakeRequest(FString InSlateName, uint16 InTakeNumber, TOptional<FString> InSubject = TOptional<FString>(), TOptional<FString> InScenario = TOptional<FString>(), TOptional<TArray<FString>> InTags = TOptional<TArray<FString>>());`
- L104 _public prototype_ `virtual TSharedPtr<FJsonObject> GetBody() const override;`
- L108 _private member_ `FString SlateName;`
- L109 _private member_ `uint16 TakeNumber;`
- L110 _private member_ `TOptional<FString> Subject;`
- L111 _private member_ `TOptional<FString> Scenario;`
- L112 _private member_ `TOptional<TArray<FString>> Tags;`

#### class `UE::CaptureManager::FStopRecordingTakeRequest`  
`class FStopRecordingTakeRequest final : public FControlRequest`  
_L115-122_
- inherits: `FControlRequest`
- L119 _public typedef_ `using ResponseType = FStopRecordingTakeResponse;`
- L121 _public prototype_ `FStopRecordingTakeRequest();`

#### class `UE::CaptureManager::FAbortRecordingTakeRequest`  
`class FAbortRecordingTakeRequest final : public FControlRequest`  
_L124-131_
- inherits: `FControlRequest`
- L128 _public typedef_ `using ResponseType = FAbortRecordingTakeResponse;`
- L130 _public prototype_ `FAbortRecordingTakeRequest();`

#### class `UE::CaptureManager::FGetTakeListRequest`  
`class FGetTakeListRequest final : public FControlRequest`  
_L133-140_
- inherits: `FControlRequest`
- L137 _public typedef_ `using ResponseType = FGetTakeListResponse;`
- L139 _public prototype_ `FGetTakeListRequest();`

#### class `UE::CaptureManager::FGetTakeMetadataRequest`  
`class FGetTakeMetadataRequest final : public FControlRequest`  
_L142-155_
- inherits: `FControlRequest`
- L146 _public typedef_ `using ResponseType = FGetTakeMetadataResponse;`
- L148 _public prototype_ `FGetTakeMetadataRequest(TArray<FString> InNames);`
- L150 _public prototype_ `virtual TSharedPtr<FJsonObject> GetBody() const override;`
- L154 _private member_ `TArray<FString> Names;`

#### class `UE::CaptureManager::FGetStreamingSubjectsRequest`  
`class FGetStreamingSubjectsRequest final : public FControlRequest`  
_L157-163_
- inherits: `FControlRequest`
- L160 _public typedef_ `using ResponseType = FGetStreamingSubjectsResponse;`
- L162 _public prototype_ `FGetStreamingSubjectsRequest();`

#### class `UE::CaptureManager::FStartStreamingRequest`  
`class FStartStreamingRequest final : public FControlRequest`  
_L165-198_
- inherits: `FControlRequest`
- L188 _public typedef_ `using ResponseType = FStartStreamingResponse;`
- L190 _public prototype_ `FStartStreamingRequest(uint16 InStreamPort, TArray<FSubject> InSubjects);`
- L192 _public prototype_ `virtual TSharedPtr<FJsonObject> GetBody() const override;`
- L196 _private member_ `uint16 StreamPort;`
- L197 _private member_ `TArray<FSubject> Subjects;`

#### struct `UE::CaptureManager::FStartStreamingRequest::FSubject`  
`struct FSubject`  
_L169-186_
- L171 _public member_ `FString Id;`
- L172 _public member_ `TOptional<FString> Name;`
- L174 _public prototype_ `FSubject() = delete;`
- L176 _public function_ `explicit FSubject(const FString& InId) : Id(InId)`
- L181 _public function_ `FSubject(const FString& InId, const FString& InName) : Id(InId) , Name(InName)`

#### class `UE::CaptureManager::FStopStreamingRequest`  
`class FStopStreamingRequest final : public FControlRequest`  
_L200-212_
- inherits: `FControlRequest`
- L204 _public typedef_ `using ResponseType = FStopStreamingResponse;`
- L206 _public prototype_ `FStopStreamingRequest(TOptional<TArray<FString>> InSubjectIds = TOptional<TArray<FString>>());`
- L208 _public prototype_ `virtual TSharedPtr<FJsonObject> GetBody() const override;`
- L211 _private member_ `TOptional<TArray<FString>> SubjectIds;`

#### class `UE::CaptureManager::FListAllCapabilitiesRequest`  
`class FListAllCapabilitiesRequest final : public FControlRequest`  
_L214-220_
- inherits: `FControlRequest`
- L217 _public typedef_ `using ResponseType = FListAllCapabilitiesResponse;`
- L219 _public prototype_ `FListAllCapabilitiesRequest();`

#### class `UE::CaptureManager::FSetCapabilityPropertyRequest`  
`class FSetCapabilityPropertyRequest final : public FControlRequest`  
_L222-233_
- inherits: `FControlRequest`
- L225 _public typedef_ `using ResponseType = FSetCapabilityPropertyResponse;`
- L227 _public prototype_ `FSetCapabilityPropertyRequest(FString InCapabilityId, FString InPropertyId, FCapabilityValue InValue);`
- L229 _public prototype_ `virtual TSharedPtr<FJsonObject> GetBody() const override;`
- L232 _private member_ `FCapabilityValue Value;`

#### class `UE::CaptureManager::FGetCapabilityPropertyRequest`  
`class FGetCapabilityPropertyRequest final : public FControlRequest`  
_L235-241_
- inherits: `FControlRequest`
- L238 _public typedef_ `using ResponseType = FGetCapabilityPropertyResponse;`
- L240 _public prototype_ `FGetCapabilityPropertyRequest(FString InCapabilityId, FString InPropertyId);`

#### class `UE::CaptureManager::FExecuteCapabilityCommandRequest`  
`class FExecuteCapabilityCommandRequest final : public FControlRequest`  
_L243-254_
- inherits: `FControlRequest`
- L246 _public typedef_ `using ResponseType = FExecuteCapabilityCommandResponse;`
- L248 _public prototype_ `FExecuteCapabilityCommandRequest(FString InCapabilityId, FString InCommandId, FCapabilityValues InArguments);`
- L250 _public prototype_ `virtual TSharedPtr<FJsonObject> GetBody() const override;`
- L253 _private member_ `FCapabilityValues Arguments;`

#### class `UE::CaptureManager::FCapabilitySubscribeRequest`  
`class FCapabilitySubscribeRequest final : public FControlRequest`  
_L256-262_
- inherits: `FControlRequest`
- L259 _public typedef_ `using ResponseType = FCapabilitySubscribeResponse;`
- L261 _public prototype_ `FCapabilitySubscribeRequest(FString InCapabilityId);`

#### class `UE::CaptureManager::FCapabilityUnsubscribeRequest`  
`class FCapabilityUnsubscribeRequest final : public FControlRequest`  
_L264-270_
- inherits: `FControlRequest`
- L267 _public typedef_ `using ResponseType = FCapabilityUnsubscribeResponse;`
- L269 _public prototype_ `FCapabilityUnsubscribeRequest(FString InCapabilityId);`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API CAPTUREPROTOCOLSTACK_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace CaptureManager` (scope `UE`)

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureProtocolStack/Public/Control/Messages/ControlResponse.h` (Public)


#### class `UE::CaptureManager::FControlResponse`  
`class FControlResponse`  
_L13-28_
- L17 _public prototype_ `FControlResponse(FString InAddressPath);`
- L18 _public prototype_ `virtual ~FControlResponse() = default;`
- L20 _public prototype_ `virtual TProtocolResult<void> Parse(TSharedPtr<FJsonObject> InBody);`
- L22 _public prototype_ `void SetAddressPath(const FString& InAddressPath);`
- L23 _public prototype_ `const FString& GetAddressPath() const;`
- L27 _private member_ `FString AddressPath;`

#### class `UE::CaptureManager::FKeepAliveResponse`  
`class FKeepAliveResponse final : public FControlResponse`  
_L30-35_
- inherits: `FControlResponse`
- L34 _public prototype_ `FKeepAliveResponse();`

#### class `UE::CaptureManager::FStartSessionResponse`  
`class FStartSessionResponse final : public FControlResponse`  
_L37-50_
- inherits: `FControlResponse`
- L41 _public prototype_ `FStartSessionResponse();`
- L43 _public prototype_ `virtual TProtocolResult<void> Parse(TSharedPtr<FJsonObject> InBody) override;`
- L45 _public prototype_ `const FString& GetSessionId() const;`
- L49 _private member_ `FString SessionId;`

#### class `UE::CaptureManager::FStopSessionResponse`  
`class FStopSessionResponse final : public FControlResponse`  
_L52-57_
- inherits: `FControlResponse`
- L56 _public prototype_ `FStopSessionResponse();`

#### class `UE::CaptureManager::FGetServerInformationResponse`  
`class FGetServerInformationResponse final : public FControlResponse`  
_L59-86_
- inherits: `FControlResponse`
- L63 _public prototype_ `FGetServerInformationResponse();`
- L65 _public prototype_ `virtual TProtocolResult<void> Parse(TSharedPtr<FJsonObject> InBody) override;`
- L67 _public prototype_ `const FString& GetId() const;`
- L68 _public prototype_ `const FString& GetName() const;`
- L69 _public prototype_ `const FString& GetModel() const;`
- L70 _public prototype_ `const FString& GetPlatformName() const;`
- L71 _public prototype_ `const FString& GetPlatformVersion() const;`
- L72 _public prototype_ `const FString& GetSoftwareName() const;`
- L73 _public prototype_ `const FString& GetSoftwareVersion() const;`
- L74 _public prototype_ `uint16 GetExportPort() const;`
- L78 _private member_ `FString Id;`
- L79 _private member_ `FString Name;`
- L80 _private member_ `FString Model;`
- L81 _private member_ `FString PlatformName;`
- L82 _private member_ `FString PlatformVersion;`
- L83 _private member_ `FString SoftwareName;`
- L84 _private member_ `FString SoftwareVersion;`
- L85 _private member_ `uint16 ExportPort = 0;`

#### class `UE::CaptureManager::FSubscribeResponse`  
`class FSubscribeResponse final : public FControlResponse`  
_L88-93_
- inherits: `FControlResponse`
- L92 _public prototype_ `FSubscribeResponse();`

#### class `UE::CaptureManager::FUnsubscribeResponse`  
`class FUnsubscribeResponse final : public FControlResponse`  
_L95-100_
- inherits: `FControlResponse`
- L99 _public prototype_ `FUnsubscribeResponse();`

#### class `UE::CaptureManager::FGetStateResponse`  
`class FGetStateResponse final : public FControlResponse`  
_L103-118_
- inherits: `FControlResponse`
- L107 _public prototype_ `FGetStateResponse();`
- L109 _public prototype_ `virtual TProtocolResult<void> Parse(TSharedPtr<FJsonObject> InBody) override;`
- L111 _public prototype_ `bool IsRecording() const;`
- L112 _public prototype_ `const TSharedPtr<FJsonObject>& GetPlatformState() const;`
- L116 _private member_ `bool bIsRecording;`
- L117 _private member_ `TSharedPtr<FJsonObject> PlatformState;`

#### class `UE::CaptureManager::FStartRecordingTakeResponse`  
`class FStartRecordingTakeResponse final : public FControlResponse`  
_L120-125_
- inherits: `FControlResponse`
- L124 _public prototype_ `FStartRecordingTakeResponse();`

#### class `UE::CaptureManager::FStopRecordingTakeResponse`  
`class FStopRecordingTakeResponse final : public FControlResponse`  
_L127-139_
- inherits: `FControlResponse`
- L131 _public prototype_ `FStopRecordingTakeResponse();`
- L133 _public prototype_ `virtual TProtocolResult<void> Parse(TSharedPtr<FJsonObject> InBody) override;`
- L135 _public prototype_ `const FString& GetTakeName() const;`
- L138 _private member_ `FString TakeName;`

#### class `UE::CaptureManager::FAbortRecordingTakeResponse`  
`class FAbortRecordingTakeResponse final : public FControlResponse`  
_L141-146_
- inherits: `FControlResponse`
- L145 _public prototype_ `FAbortRecordingTakeResponse();`

#### class `UE::CaptureManager::FGetTakeListResponse`  
`class FGetTakeListResponse final : public FControlResponse`  
_L148-161_
- inherits: `FControlResponse`
- L152 _public prototype_ `FGetTakeListResponse();`
- L154 _public prototype_ `virtual TProtocolResult<void> Parse(TSharedPtr<FJsonObject> InBody) override;`
- L156 _public prototype_ `const TArray<FString>& GetNames() const;`
- L160 _private member_ `TArray<FString> Names;`

#### class `UE::CaptureManager::FGetTakeMetadataResponse`  
`class FGetTakeMetadataResponse final : public FControlResponse`  
_L163-218_
- inherits: `FControlResponse`
- L206 _public prototype_ `FGetTakeMetadataResponse();`
- L208 _public prototype_ `virtual TProtocolResult<void> Parse(TSharedPtr<FJsonObject> InBody) override;`
- L210 _public prototype_ `const TArray<FTakeObject>& GetTakes() const;`
- L214 _private prototype_ `TProtocolResult<void> CreateTakeObject(const TSharedPtr<FJsonObject>& InTakeObject, FTakeObject& OutTake) const;`
- L215 _private prototype_ `TProtocolResult<void> CreateFileObject(const TSharedPtr<FJsonObject>& InFileObject, FFileObject& OutFile) const;`
- L217 _private member_ `TArray<FTakeObject> Takes;`

#### struct `UE::CaptureManager::FGetTakeMetadataResponse::FFileObject`  
`struct FFileObject`  
_L167-171_
- L169 _public member_ `FString Name;`
- L170 _public member_ `uint64 Length = 0;`

#### struct `UE::CaptureManager::FGetTakeMetadataResponse::FVideoObject`  
`struct FVideoObject`  
_L173-179_
- L175 _public member_ `uint64 Frames = 0;`
- L176 _public member_ `uint16 FrameRate = 0;`
- L177 _public member_ `uint32 Height = 0;`
- L178 _public member_ `uint32 Width = 0;`

#### struct `UE::CaptureManager::FGetTakeMetadataResponse::FAudioObject`  
`struct FAudioObject`  
_L181-186_
- L183 _public member_ `uint8 Channels = 0;`
- L184 _public member_ `uint32 SampleRate = 0;`
- L185 _public member_ `uint8 BitsPerChannel = 0;`

#### struct `UE::CaptureManager::FGetTakeMetadataResponse::FTakeObject`  
`struct FTakeObject`  
_L188-204_
- L190 _public member_ `FString Name;`
- L191 _public member_ `FString Slate;`
- L192 _public member_ `uint16 TakeNumber = 0;`
- L193 _public member_ `FString DateTime;`
- L194 _public member_ `FString AppVersion;`
- L195 _public member_ `FString Model;`
- L196 _public member_ `FString Subject;`
- L197 _public member_ `FString Scenario;`
- L198 _public member_ `TArray<FString> Tags;`
- L200 _public member_ `TArray<FFileObject> Files;`
- L202 _public member_ `FVideoObject Video;`
- L203 _public member_ `FAudioObject Audio;`

#### class `UE::CaptureManager::FGetStreamingSubjectsResponse`  
`class FGetStreamingSubjectsResponse final : public FControlResponse`  
_L220-250_
- inherits: `FControlResponse`
- L238 _public prototype_ `FGetStreamingSubjectsResponse();`
- L240 _public prototype_ `virtual TProtocolResult<void> Parse(TSharedPtr<FJsonObject> InBody) override;`
- L242 _public prototype_ `const TArray<FSubject>& GetSubjects() const;`
- L246 _private member_ `TArray<FSubject> Subjects;`
- L248 _private prototype_ `TProtocolResult<void> CreateSubject(const TSharedPtr<FJsonObject>& InSubjectObject, FSubject& OutSubject) const;`
- L249 _private prototype_ `TProtocolResult<void> CreateAnimationMetadata(const TSharedPtr<FJsonObject>& InAnimationObject, FAnimationMetadata& OutAnimationMetadata) const;`

#### struct `UE::CaptureManager::FGetStreamingSubjectsResponse::FAnimationMetadata`  
`struct FAnimationMetadata`  
_L224-229_
- L226 _public member_ `FString Type;`
- L227 _public member_ `uint16 Version;`
- L228 _public member_ `TArray<FString> Controls;`

#### struct `UE::CaptureManager::FGetStreamingSubjectsResponse::FSubject`  
`struct FSubject`  
_L231-236_
- L233 _public member_ `FString Id;`
- L234 _public member_ `FString Name;`
- L235 _public member_ `FAnimationMetadata AnimationMetadata;`

#### class `UE::CaptureManager::FStartStreamingResponse`  
`class FStartStreamingResponse final : public FControlResponse`  
_L252-258_
- inherits: `FControlResponse`
- L256 _public prototype_ `FStartStreamingResponse();`

#### class `UE::CaptureManager::FStopStreamingResponse`  
`class FStopStreamingResponse final : public FControlResponse`  
_L260-264_
- inherits: `FControlResponse`
- L263 _public prototype_ `FStopStreamingResponse();`

#### class `UE::CaptureManager::FListAllCapabilitiesResponse`  
`class FListAllCapabilitiesResponse final : public FControlResponse`  
_L266-279_
- inherits: `FControlResponse`
- L269 _public prototype_ `FListAllCapabilitiesResponse();`
- L271 _public prototype_ `TProtocolResult<void> Parse(TSharedPtr<FJsonObject> InBody) override;`
- L273 _public prototype_ `TArray<FCapability> GetCapabilities();`
- L276 _private member_ `TArray<FCapability> Capabilities;`
- L278 _private prototype_ `TProtocolResult<FCapability> ParseCapability(const TSharedPtr<FJsonObject>& InJsonObject);`

#### class `UE::CaptureManager::FSetCapabilityPropertyResponse`  
`class FSetCapabilityPropertyResponse final : public FControlResponse`  
_L281-285_
- inherits: `FControlResponse`
- L284 _public prototype_ `FSetCapabilityPropertyResponse();`

#### class `UE::CaptureManager::FGetCapabilityPropertyResponse`  
`class FGetCapabilityPropertyResponse final : public FControlResponse`  
_L287-298_
- inherits: `FControlResponse`
- L290 _public prototype_ `FGetCapabilityPropertyResponse();`
- L292 _public prototype_ `TProtocolResult<void> Parse(TSharedPtr<FJsonObject> InBody) override;`
- L294 _public prototype_ `TProtocolResult<FCapabilityValue> GetValue(ECapabilityValue::Type InExpectedType) const;`
- L297 _private member_ `TSharedPtr<FJsonObject> Body;`

#### class `UE::CaptureManager::FExecuteCapabilityCommandResponse`  
`class FExecuteCapabilityCommandResponse final : public FControlResponse`  
_L300-311_
- inherits: `FControlResponse`
- L303 _public prototype_ `FExecuteCapabilityCommandResponse();`
- L305 _public prototype_ `TProtocolResult<void> Parse(TSharedPtr<FJsonObject> InBody) override;`
- L307 _public prototype_ `TProtocolResult<FCapabilityValue> GetReturnValue(ECapabilityValue::Type InExpectedType) const;`
- L310 _private member_ `TSharedPtr<FJsonObject> Body;`

#### class `UE::CaptureManager::FCapabilitySubscribeResponse`  
`class FCapabilitySubscribeResponse final : public FControlResponse`  
_L313-317_
- inherits: `FControlResponse`
- L316 _public prototype_ `FCapabilitySubscribeResponse();`

#### class `UE::CaptureManager::FCapabilityUnsubscribeResponse`  
`class FCapabilityUnsubscribeResponse final : public FControlResponse`  
_L319-323_
- inherits: `FControlResponse`
- L322 _public prototype_ `FCapabilityUnsubscribeResponse();`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API CAPTUREPROTOCOLSTACK_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace CaptureManager` (scope `UE`)

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureProtocolStack/Public/Control/Messages/ControlUpdate.h` (Public)


#### class `UE::CaptureManager::FControlUpdateCreator`  
`class FControlUpdateCreator final`  
_L19-23_
- L22 _public prototype_ `static TProtocolResult<TSharedRef<FControlUpdate>> Create(const FString& InAddressPath);`

#### class `UE::CaptureManager::FControlUpdate`  
`class FControlUpdate`  
_L25-41_
- L29 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnUpdateMessage, TSharedPtr<FControlUpdate> InUpdateMessage);`
- L31 _public prototype_ `FControlUpdate(FString InAddressPath);`
- L32 _public prototype_ `virtual ~FControlUpdate() = default;`
- L34 _public prototype_ `const FString& GetAddressPath() const;`
- L36 _public prototype_ `virtual TProtocolResult<void> Parse(TSharedPtr<FJsonObject> InBody);`
- L40 _private member_ `FString AddressPath;`

#### class `UE::CaptureManager::FSessionStopped`  
`class FSessionStopped final : public FControlUpdate`  
_L43-48_
- inherits: `FControlUpdate`
- L47 _public prototype_ `FSessionStopped();`

#### class `UE::CaptureManager::FRecordingStatusUpdate`  
`class FRecordingStatusUpdate final : public FControlUpdate`  
_L50-63_
- inherits: `FControlUpdate`
- L54 _public prototype_ `FRecordingStatusUpdate();`
- L56 _public prototype_ `virtual TProtocolResult<void> Parse(TSharedPtr<FJsonObject> InBody) override;`
- L58 _public prototype_ `bool IsRecording() const;`
- L62 _private member_ `bool bIsRecording;`

#### class `UE::CaptureManager::FBaseTakeUpdate`  
`class FBaseTakeUpdate : public FControlUpdate`  
_L65-78_
- inherits: `FControlUpdate`
- L71 _public prototype_ `virtual TProtocolResult<void> Parse(TSharedPtr<FJsonObject> InBody) override;`
- L73 _public prototype_ `const FString& GetTakeName() const;`
- L77 _private member_ `FString TakeName;`

#### class `UE::CaptureManager::FTakeAddedUpdate`  
`class FTakeAddedUpdate final : public FBaseTakeUpdate`  
_L80-85_
- inherits: `FBaseTakeUpdate`
- L84 _public prototype_ `FTakeAddedUpdate();`

#### class `UE::CaptureManager::FTakeRemovedUpdate`  
`class FTakeRemovedUpdate final : public FBaseTakeUpdate`  
_L87-92_
- inherits: `FBaseTakeUpdate`
- L91 _public prototype_ `FTakeRemovedUpdate();`

#### class `UE::CaptureManager::FTakeUpdatedUpdate`  
`class FTakeUpdatedUpdate final : public FBaseTakeUpdate`  
_L94-99_
- inherits: `FBaseTakeUpdate`
- L98 _public prototype_ `FTakeUpdatedUpdate();`

#### class `UE::CaptureManager::FDiskCapacityUpdate`  
`class FDiskCapacityUpdate final : public FControlUpdate`  
_L103-118_
- inherits: `FControlUpdate`
- L107 _public prototype_ `FDiskCapacityUpdate();`
- L109 _public prototype_ `virtual TProtocolResult<void> Parse(TSharedPtr<FJsonObject> InBody) override;`
- L111 _public prototype_ `uint64 GetTotal() const;`
- L112 _public prototype_ `uint64 GetRemaining() const;`
- L116 _private member_ `uint64 Total = 0;`
- L117 _private member_ `uint64 Remaining = 0;`

#### class `UE::CaptureManager::FBatteryPercentageUpdate`  
`class FBatteryPercentageUpdate final : public FControlUpdate`  
_L120-133_
- inherits: `FControlUpdate`
- L124 _public prototype_ `FBatteryPercentageUpdate();`
- L126 _public prototype_ `virtual TProtocolResult<void> Parse(TSharedPtr<FJsonObject> InBody) override;`
- L128 _public prototype_ `float GetLevel() const;`
- L132 _private member_ `float Level = 0.0f;`

#### class `UE::CaptureManager::FThermalStateUpdate`  
`class FThermalStateUpdate final : public FControlUpdate`  
_L135-160_
- inherits: `FControlUpdate`
- L149 _public prototype_ `FThermalStateUpdate();`
- L151 _public prototype_ `virtual TProtocolResult<void> Parse(TSharedPtr<FJsonObject> InBody) override;`
- L153 _public prototype_ `EState GetState() const;`
- L157 _private prototype_ `static EState ConvertState(const FString& InStateString);`
- L159 _private member_ `EState State;`

#### enum `UE::CaptureManager::FThermalStateUpdate::EState`  
`enum class EState`  
_L139-147_
- L141 _public enumerator_ `Nominal = 0`
- L142 _public enumerator_ `Fair`
- L143 _public enumerator_ `Serious`
- L144 _public enumerator_ `Critical`
- L146 _public enumerator_ `Invalid`

#### class `UE::CaptureManager::FEventUpdate`  
`class FEventUpdate final : public FControlUpdate`  
_L162-173_
- inherits: `FControlUpdate`
- L165 _public prototype_ `FEventUpdate(FString InAddressPath);`
- L167 _public prototype_ `virtual UE::CaptureManager::TProtocolResult<void> Parse(TSharedPtr<FJsonObject> InBody) override;`
- L169 _public prototype_ `const TProtocolResult<TMap<FString, FCapabilityValue>> GetArguments(const TArray<FEventArgumentDescriptor>& InArgumentsDescriptor) const;`
- L172 _private member_ `TMap<FString, TSharedPtr<FJsonObject>> Arguments;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API CAPTUREPROTOCOLSTACK_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace CaptureManager` (scope `UE`)
- L29 _delegate_ `DECLARE_DELEGATE_OneParam(FOnUpdateMessage, TSharedPtr<FControlUpdate> InUpdateMessage);`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureProtocolStack/Public/Discovery/Communication/DiscoveryCommunication.h` (Public)


#### class `UE::CaptureManager::FDiscoveryCommunication`  
`class FDiscoveryCommunication final`  
_L15-53_
- L26 _public member_ `static const uint16 MulticastPort;`
- L27 _public member_ `static const FString MulticastAddress;`
- L31 _public typedef_ `using FRunnerType = TQueueRunner<FContext>;`
- L33 _public prototype_ `FDiscoveryCommunication();`
- L35 _public prototype_ `TProtocolResult<void> Start();`
- L36 _public prototype_ `TProtocolResult<void> Stop();`
- L38 _public prototype_ `void SendMessage(FDiscoveryPacket InMessage, const FString& Endpoint);`
- L39 _public prototype_ `void SendMessage(FDiscoveryPacket InMessage, const FString& EndpointIp, const uint16 EndpointPort);`
- L41 _public prototype_ `void SetReceiveHandler(FOnPacketReceived InReceiveHandler);`
- L45 _private prototype_ `void OnProcessReceivedPacket(FContext InContext);`
- L46 _private prototype_ `void OnPacketArrived(const FArrayReaderPtr& InPayload, const FIPv4Endpoint& InEndpoint);`
- L48 _private member_ `FUdpClient Client;`
- L50 _private member_ `FRunnerType SynchronizedReceiver;`
- L52 _private member_ `FOnPacketReceived OnPacketReceived;`

#### struct `UE::CaptureManager::FDiscoveryCommunication::FContext`  
`struct FContext`  
_L18-22_
- L20 _public member_ `FString ServerIp;`
- L21 _public member_ `FDiscoveryPacket Packet;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace CaptureManager` (scope `UE`)
- L29 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnPacketReceived, FString ServerIp, FDiscoveryPacket InPacket) using FRunnerType = TQueueRunner<FContext>;`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureProtocolStack/Public/Discovery/Communication/DiscoveryPacket.h` (Public)


#### class `UE::CaptureManager::FDiscoveryPacket`  
`class FDiscoveryPacket final`  
_L13-51_
- L26 _public member_ `static const TArray<uint8> Header;`
- L27 _public member_ `static const uint16 Version;`
- L29 _public prototype_ `static TProtocolResult<FDiscoveryPacket> Deserialize(const TConstArrayView<uint8>& InData);`
- L30 _public prototype_ `static TProtocolResult<TArray<uint8>> Serialize(const FDiscoveryPacket& InPacket);`
- L32 _public prototype_ `FDiscoveryPacket() = default;`
- L33 _public prototype_ `FDiscoveryPacket(EMessageType InMessageType, TArray<uint8> InPayload);`
- L35 _public prototype_ `FDiscoveryPacket(const FDiscoveryPacket& InOther) = default;`
- L36 _public prototype_ `FDiscoveryPacket(FDiscoveryPacket&& InOther) = default;`
- L38 _public prototype_ `FDiscoveryPacket& operator=(const FDiscoveryPacket& InOther) = default;`
- L39 _public prototype_ `FDiscoveryPacket& operator=(FDiscoveryPacket&& InOther) = default;`
- L41 _public prototype_ `const EMessageType GetMessageType() const;`
- L42 _public prototype_ `const TArray<uint8>& GetPayload() const;`
- L46 _private prototype_ `static EMessageType ToMessageType(uint8 InMessageType);`
- L47 _private prototype_ `static uint8 FromMessageType(EMessageType InMessageType);`
- L49 _private member_ `EMessageType MessageType;`
- L50 _private member_ `TArray<uint8> Payload;`

#### enum `UE::CaptureManager::FDiscoveryPacket::EMessageType`  
`enum class EMessageType : uint8`  
_L17-24_
- L19 _public enumerator_ `Request = 0`
- L20 _public enumerator_ `Response = 1`
- L21 _public enumerator_ `Notify = 2`
- L23 _public enumerator_ `Invalid = 255`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace CaptureManager` (scope `UE`)

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureProtocolStack/Public/Discovery/DiscoveryMessenger.h` (Public)


#### class `UE::CaptureManager::FDiscoveryMessenger`  
`class FDiscoveryMessenger final`  
_L19-44_
- L22 _public typedef_ `using FOnResponseArrived = TDelegate<void(FString, FDiscoveryResponse), FDefaultTSDelegateUserPolicy>;`
- L23 _public typedef_ `using FOnNotifyArrived = TDelegate<void(FString, FDiscoveryNotify), FDefaultTSDelegateUserPolicy>;`
- L25 _public prototype_ `FDiscoveryMessenger();`
- L26 _public prototype_ `~FDiscoveryMessenger();`
- L28 _public prototype_ `TProtocolResult<void> Start();`
- L29 _public prototype_ `TProtocolResult<void> Stop();`
- L31 _public prototype_ `TProtocolResult<void> SendRequest();`
- L33 _public prototype_ `void SetResponseHandler(FOnResponseArrived InOnResponse);`
- L34 _public prototype_ `void SetNotifyHandler(FOnNotifyArrived InOnNotify);`
- L38 _private prototype_ `void OnPacketArrived(FString InServerIp, FDiscoveryPacket InPacket);`
- L40 _private member_ `FDiscoveryCommunication Communication;`
- L42 _private member_ `FOnResponseArrived OnResponse;`
- L43 _private member_ `FOnNotifyArrived OnNotify;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API CAPTUREPROTOCOLSTACK_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace CaptureManager` (scope `UE`)

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureProtocolStack/Public/Discovery/Messages/DiscoveryNotify.h` (Public)


#### class `UE::CaptureManager::FDiscoveryNotify`  
`class FDiscoveryNotify`  
_L17-61_
- L21 _public member_ `static const uint32 MinPayloadSize;`
- L23 _public typedef_ `using FServerId = TStaticArray<uint8, 16>;`
- L34 _public prototype_ `FDiscoveryNotify(FServerId InServerId, uint16 InControlPort, EConnectionState InConnectionState, TArray<uint16> InSupportedVersions);` — `UE_DEPRECATED(5.6, "This constructor is no longer supported")`
- L36 _public prototype_ `FDiscoveryNotify(FServerId InServerId, FString InServerName, uint16 InControlPort, EConnectionState InConnectionState);`
- L38 _public prototype_ `static TProtocolResult<FDiscoveryNotify> Deserialize(const FDiscoveryPacket& InPacket);`
- L39 _public prototype_ `static TProtocolResult<FDiscoveryPacket> Serialize(const FDiscoveryNotify& InNotify);`
- L41 _public prototype_ `const FServerId& GetServerId() const;`
- L42 _public prototype_ `const FString& GetServerName() const;`
- L43 _public prototype_ `uint16 GetControlPort() const;`
- L44 _public prototype_ `EConnectionState GetConnectionState() const;`
- L47 _public prototype_ `const TArray<uint16>& GetSupportedVersions() const;` — `UE_DEPRECATED(5.6, "GetSupportedVersions is no longer supported")`
- L51 _private prototype_ `static EConnectionState ToConnectionState(uint8 InConnectionState);`
- L52 _private prototype_ `static uint8 FromConnectionState(EConnectionState InConnectionState);`
- L54 _private member_ `FServerId ServerId;`
- L55 _private member_ `FString ServerName;`
- L56 _private member_ `uint16 ControlPort;`
- L57 _private member_ `EConnectionState ConnectionState;`
- L60 _private member_ `TArray<uint16> SupportedVersions;` — Deprecated in 5.6.

#### enum `UE::CaptureManager::FDiscoveryNotify::EConnectionState`  
`enum class EConnectionState : uint8`  
_L25-31_
- L27 _public enumerator_ `Offline = 0`
- L28 _public enumerator_ `Online = 1`
- L30 _public enumerator_ `Invalid`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API CAPTUREPROTOCOLSTACK_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace CaptureManager` (scope `UE`)

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureProtocolStack/Public/Discovery/Messages/DiscoveryRequest.h` (Public)


#### class `UE::CaptureManager::FDiscoveryRequest`  
`class FDiscoveryRequest`  
_L15-25_
- L19 _public member_ `static const uint32 PayloadSize;`
- L21 _public prototype_ `FDiscoveryRequest() = default;`
- L23 _public prototype_ `static TProtocolResult<FDiscoveryRequest> Deserialize(const FDiscoveryPacket& InPacket);`
- L24 _public prototype_ `static TProtocolResult<FDiscoveryPacket> Serialize(const FDiscoveryRequest& InRequest);`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace CaptureManager` (scope `UE`)

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureProtocolStack/Public/Discovery/Messages/DiscoveryResponse.h` (Public)


#### class `UE::CaptureManager::FDiscoveryResponse`  
`class FDiscoveryResponse`  
_L17-48_
- L21 _public member_ `static const uint32 MinPayloadSize;`
- L23 _public typedef_ `using FServerId = TStaticArray<uint8, 16>;`
- L26 _public prototype_ `FDiscoveryResponse(FServerId InServerId, uint16 InControlPort, TArray<uint16> InSupportedVersions);` — `UE_DEPRECATED(5.6, "This constructor is no longer supported")`
- L28 _public prototype_ `FDiscoveryResponse(FServerId InServerId, FString InServerName, uint16 InControlPort);`
- L30 _public prototype_ `static TProtocolResult<FDiscoveryResponse> Deserialize(const FDiscoveryPacket& InPacket);`
- L31 _public prototype_ `static TProtocolResult<FDiscoveryPacket> Serialize(const FDiscoveryResponse& InResponse);`
- L33 _public prototype_ `const FServerId& GetServerId() const;`
- L34 _public prototype_ `const FString& GetServerName() const;`
- L35 _public prototype_ `uint16 GetControlPort() const;`
- L38 _public prototype_ `const TArray<uint16>& GetSupportedVersions() const;` — `UE_DEPRECATED(5.6, "GetSupportedVersions is no longer supported")`
- L42 _private member_ `FServerId ServerId;`
- L43 _private member_ `FString ServerName;`
- L44 _private member_ `uint16 ControlPort;`
- L47 _private member_ `TArray<uint16> SupportedVersions;` — Deprecated in 5.6

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API CAPTUREPROTOCOLSTACK_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace CaptureManager` (scope `UE`)

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureProtocolStack/Public/ExportClient/Communication/ExportCommunication.h` (Public)


#### struct `UE::CaptureManager::FExportRequestPacket`  
`struct FExportRequestPacket`  
_L20-26_
- L22 _public prototype_ `static TProtocolResult<void> Serialize(const FExportRequestPacket& InRequestPacket, ITcpSocketWriter& InWriter);`
- L24 _public member_ `FExportHeader Header;`
- L25 _public member_ `FExportRequest Request;`

#### struct `UE::CaptureManager::FExportResponseHeader`  
`struct FExportResponseHeader`  
_L28-34_
- L30 _public prototype_ `static TProtocolResult<FExportResponseHeader> Deserialize(ITcpSocketReader& InReader);`
- L32 _public member_ `FExportHeader Header;`
- L33 _public member_ `FExportResponse Response;`

#### class `UE::CaptureManager::FExportCommunication`  
`class FExportCommunication final`  
_L36-56_
- L40 _public prototype_ `FExportCommunication();`
- L42 _public prototype_ `TProtocolResult<void> Init();`
- L43 _public prototype_ `TProtocolResult<void> Start(const FString& InServerIp, const uint16 InServerPort);`
- L44 _public prototype_ `TProtocolResult<void> Stop();`
- L46 _public prototype_ `bool IsRunning() const;`
- L48 _public prototype_ `TProtocolResult<void> SendRequest(FExportHeader InHeader, FExportRequest InRequest);`
- L49 _public prototype_ `TProtocolResult<FExportResponseHeader> ReceiveResponseHeader();`
- L50 _public prototype_ `TProtocolResult<TArray<uint8>> ReceiveResponseData(const uint64 InSize);`
- L51 _public prototype_ `TProtocolResult<TStaticArray<uint8, 16>> ReceiveFileHash();`
- L55 _private member_ `FTcpClient Client;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace CaptureManager` (scope `UE`)

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureProtocolStack/Public/ExportClient/Communication/ExportHeader.h` (Public)


#### class `UE::CaptureManager::FExportHeader`  
`class FExportHeader final`  
_L15-40_
- L19 _public member_ `static const TArray<uint8> Header;`
- L21 _public prototype_ `FExportHeader() = default;`
- L22 _public prototype_ `FExportHeader(uint16 InVersion, uint32 InTransactionId);`
- L24 _public prototype_ `FExportHeader(const FExportHeader& InOther) = default;`
- L25 _public prototype_ `FExportHeader(FExportHeader&& InOther) = default;`
- L27 _public prototype_ `FExportHeader& operator=(const FExportHeader& InOther) = default;`
- L28 _public prototype_ `FExportHeader& operator=(FExportHeader&& InOther) = default;`
- L30 _public prototype_ `static TProtocolResult<FExportHeader> Deserialize(ITcpSocketReader& InReader);`
- L31 _public prototype_ `static TProtocolResult<void> Serialize(const FExportHeader& InHeader, ITcpSocketWriter& InWriter);`
- L33 _public prototype_ `uint16 GetVersion() const;`
- L34 _public prototype_ `uint32 GetTransactionId() const;`
- L38 _private member_ `uint16 Version = 0;`
- L39 _private member_ `uint32 TransactionId = 0;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace CaptureManager` (scope `UE`)

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureProtocolStack/Public/ExportClient/ExportClient.h` (Public)


#### class `UE::CaptureManager::FExportTaskStopToken`  
`class FExportTaskStopToken`  
_L15-27_
- L19 _public prototype_ `FExportTaskStopToken();`
- L21 _public prototype_ `void Cancel();`
- L22 _public prototype_ `bool IsCanceled();`
- L26 _private member_ `std::atomic_bool bCanceled;`

#### class `UE::CaptureManager::FExportClient`  
`class FExportClient final : public FExportTaskExecutor`  
_L29-74_
- inherits: `FExportTaskExecutor`
- L34 _public typedef_ `using FTaskId = uint32;`
- L35 _public member_ `static constexpr int32 AbortedError = -20;`
- L37 _public typedef_ `using FTakeFileArray = TArray<FTakeFile>;`
- L39 _public prototype_ `FExportClient(FString InServerIp, const uint16 InExportPort);`
- L40 _public prototype_ `~FExportClient();`
- L42 _public prototype_ `FTaskId ExportTakeFiles(FString InTakeName, FTakeFileArray InTakeFileArray, TUniquePtr<FBaseStream> InStream);`
- L43 _public prototype_ `FTaskId ExportFiles(TMap<FString, FTakeFileArray> InTakesFilesMap, TUniquePtr<FBaseStream> InStream);`
- L45 _public prototype_ `void AbortExport(const FTaskId InTaskId);`
- L46 _public prototype_ `void AbortAllExports();`
- L50 _private prototype_ `FTaskId StartExport(FExportTakeTask::FExportContexts InContexts, TUniquePtr<FBaseStream> InStream);`
- L52 _private prototype_ `virtual void OnTask(TUniquePtr<FExportTakeTask> InTask) override;`
- L53 _private prototype_ `bool OnExportTask(TUniquePtr<FExportTakeTask> InTask);`
- L55 _private prototype_ `TProtocolResult<TMap<uint32, TPair<FString, FTakeFile>>> SendRequests(FExportTakeTask::FExportContexts InContexts);`
- L56 _private prototype_ `TProtocolResult<void> ReceiveResponses(TMap<uint32, TPair<FString, FTakeFile>> InResponseMap, FBaseStream& InBaseStream);`
- L59 _private prototype_ `TProtocolResult<void> Start();`
- L60 _private prototype_ `TProtocolResult<void> Stop();`
- L62 _private member_ `FString ServerIp;`
- L63 _private member_ `uint16 ServerPort = 0;`
- L64 _private member_ `TUniquePtr<FExportCommunication> Communication;`
- L66 _private member_ `FExportWorker ExportWorker;`
- L67 _private member_ `TUniquePtr<FRunnableThread> Thread;`
- L69 _private member_ `std::atomic<FTaskId> CurrentTaskId{0};`
- L71 _private member_ `uint32 TransactionIdCounter = 0;`
- L73 _private member_ `TUniquePtr<FExportTaskStopToken> CurrentTaskStopToken;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CAPTUREPROTOCOLSTACK_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace CaptureManager` (scope `UE`)

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureProtocolStack/Public/ExportClient/ExportWorker.h` (Public)


#### struct `UE::CaptureManager::FTakeFile`  
`struct FTakeFile`  
_L13-18_
- L15 _public member_ `FString FileName;`
- L16 _public member_ `uint64 Length = 0;`
- L17 _public member_ `uint64 Offset = 0;`

#### class `UE::CaptureManager::FExportTakeTask`  
`class FExportTakeTask`  
_L20-37_
- L30 _public typedef_ `using FExportContexts = TArray<FExportContext>;`
- L32 _public prototype_ `FExportTakeTask(FExportContexts InExportContexts, TUniquePtr<FBaseStream> InStream);`
- L35 _public member_ `FExportContexts ExportContexts;`
- L36 _public member_ `TUniquePtr<FBaseStream> Stream;`

#### struct `UE::CaptureManager::FExportTakeTask::FExportContext`  
`struct FExportContext`  
_L24-28_
- L26 _public member_ `FString TakeName;`
- L27 _public member_ `FTakeFile File;`

#### class `UE::CaptureManager::FExportTaskExecutor`  
`class FExportTaskExecutor`  
_L39-45_
- L42 _public prototype_ `virtual ~FExportTaskExecutor() = default;`
- L44 _public prototype_ `virtual void OnTask(TUniquePtr<FExportTakeTask> InTask) = 0;`

#### class `UE::CaptureManager::FExportQueue`  
`class FExportQueue`  
_L47-69_
- L50 _public member_ `static const int32 MaxNumberOfElements = MAX_int32;`
- L52 _public prototype_ `FExportQueue();`
- L53 _public prototype_ `~FExportQueue() = default;`
- L55 _public prototype_ `TProtocolResult<void> Add(const uint32 InTaskId, TUniquePtr<FExportTakeTask> InElement);`
- L56 _public prototype_ `TUniquePtr<FExportTakeTask> Pop();`
- L58 _public prototype_ `TProtocolResult<TUniquePtr<FExportTakeTask>> Remove(uint32 InTaskId);`
- L60 _public prototype_ `bool IsEmpty() const;`
- L62 _public prototype_ `TArray<TUniquePtr<FExportTakeTask>> GetAndEmpty();`
- L66 _private member_ `mutable FCriticalSection Mutex;`
- L67 _private member_ `FSemaphore Semaphore;`
- L68 _private member_ `TArray<TPair<uint32, TUniquePtr<FExportTakeTask>>> Queue;`

#### class `UE::CaptureManager::FExportWorker`  
`class FExportWorker : public FRunnable`  
_L71-97_
- inherits: `FRunnable`
- L75 _public prototype_ `FExportWorker(FExportTaskExecutor& InClient);`
- L78 _public prototype_ `TProtocolResult<void> Add(const uint32 InTaskId, TUniquePtr<FExportTakeTask> InElement);`
- L79 _public prototype_ `TProtocolResult<TUniquePtr<FExportTakeTask>> Remove(uint32 InTaskId);`
- L81 _public prototype_ `bool IsEmpty() const;`
- L83 _public prototype_ `TArray<TUniquePtr<FExportTakeTask>> GetAndEmpty();`
- L87 _protected prototype_ `virtual uint32 Run() override;`
- L88 _protected prototype_ `virtual void Stop() override;`
- L92 _private member_ `std::atomic<bool> bRunning;`
- L94 _private member_ `FExportQueue Queue;`
- L96 _private member_ `FExportTaskExecutor& Client;`

#### class `UE::CaptureManager::FBaseStream`  
`class FBaseStream`  
_L99-111_
- L103 _public prototype_ `FBaseStream() = default;`
- L104 _public prototype_ `virtual ~FBaseStream() = default;`
- L106 _public prototype_ `virtual TProtocolResult<void> StartFile(const FString& InTakeName, const FString& InFileName) = 0;`
- L107 _public prototype_ `virtual TProtocolResult<void> ProcessData(const FString& InTakeName, const FString& InFileName, const TConstArrayView<uint8>& InData) = 0;`
- L108 _public prototype_ `virtual TProtocolResult<void> FinishFile(const FString& InTakeName, const FString& InFileName, const TStaticArray<uint8, 16>& InHash) = 0;`
- L110 _public prototype_ `virtual void Finalize(TProtocolResult<void> InResult) = 0;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace CaptureManager` (scope `UE`)

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureProtocolStack/Public/ExportClient/Messages/ExportRequest.h` (Public)


#### class `UE::CaptureManager::FExportRequest`  
`class FExportRequest final`  
_L10-35_
- L14 _public prototype_ `FExportRequest() = default;`
- L15 _public prototype_ `FExportRequest(FString InTakeName, FString InFileName, uint64 InOffset);`
- L17 _public prototype_ `FExportRequest(const FExportRequest& InOther) = default;`
- L18 _public prototype_ `FExportRequest(FExportRequest&& InOther) = default;`
- L20 _public prototype_ `FExportRequest& operator=(const FExportRequest& InOther) = default;`
- L21 _public prototype_ `FExportRequest& operator=(FExportRequest&& InOther) = default;`
- L23 _public prototype_ `static TProtocolResult<FExportRequest> Deserialize(ITcpSocketReader& InReader);`
- L24 _public prototype_ `static TProtocolResult<void> Serialize(const FExportRequest& InRequest, ITcpSocketWriter& InWriter);`
- L26 _public prototype_ `const FString& GetTakeName() const;`
- L27 _public prototype_ `const FString& GetFileName() const;`
- L28 _public prototype_ `uint64 GetOffset() const;`
- L32 _private member_ `FString TakeName;`
- L33 _private member_ `FString FileName;`
- L34 _private member_ `uint64 Offset = 0;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace CaptureManager` (scope `UE`)

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureProtocolStack/Public/ExportClient/Messages/ExportResponse.h` (Public)


#### class `UE::CaptureManager::FExportResponse`  
`class FExportResponse final`  
_L10-52_
- L26 _public prototype_ `FExportResponse(EStatus InStatus, uint64 InLength);`
- L28 _public prototype_ `FExportResponse(const FExportResponse& InOther) = default;`
- L29 _public prototype_ `FExportResponse(FExportResponse&& InOther) = default;`
- L31 _public prototype_ `FExportResponse& operator=(const FExportResponse& InOther) = default;`
- L32 _public prototype_ `FExportResponse& operator=(FExportResponse&& InOther) = default;`
- L34 _public prototype_ `static TProtocolResult<FExportResponse> Deserialize(ITcpSocketReader& InReader);`
- L35 _public prototype_ `static TProtocolResult<TStaticArray<uint8, 16>> DeserializeHash(ITcpSocketReader& InReader);`
- L37 _public prototype_ `static TProtocolResult<void> Serialize(const FExportResponse& InResponse, ITcpSocketWriter& InWriter);`
- L38 _public prototype_ `static TProtocolResult<void> SerializeHash(const TStaticArray<uint8, 16>& InHash, ITcpSocketWriter& InWriter);`
- L40 _public prototype_ `EStatus GetStatus() const;`
- L41 _public prototype_ `uint64 GetLength() const;`
- L45 _private prototype_ `FExportResponse() = default;`
- L47 _private prototype_ `static EStatus ToStatus(uint8 InStatus);`
- L48 _private prototype_ `static uint8 FromStatus(EStatus InStatus);`
- L50 _private member_ `EStatus Status;`
- L51 _private member_ `uint64 Length;`

#### enum `UE::CaptureManager::FExportResponse::EStatus`  
`enum class EStatus : uint8`  
_L14-24_
- L16 _public enumerator_ `Success = 0`
- L17 _public enumerator_ `InvalidTakeName = 1`
- L18 _public enumerator_ `InvalidFileName = 2`
- L19 _public enumerator_ `InvalidOffset = 3`
- L20 _public enumerator_ `ServerError = 4`
- L21 _public enumerator_ `UnsupportedProtocolVersion = 5`
- L23 _public enumerator_ `Reserved`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace CaptureManager` (scope `UE`)

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureProtocolStack/Public/Utility/Definitions.h` (Public)


#### Free symbols / members of external scopes

- L7 _macro_ `#define CPS_VERSION 1`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace CaptureManager` (scope `UE`)
- L12 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogCPSControlMessenger, Log, All);`
- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogCPSControlMessenger, Log, All);` (scope `UE::CaptureManager`)
- L13 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogCPSControlCommunication, Log, All);`
- L13 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogCPSControlCommunication, Log, All);` (scope `UE::CaptureManager`)
- L14 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogCPSDiscoveryMessenger, Log, All);`
- L14 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogCPSDiscoveryMessenger, Log, All);` (scope `UE::CaptureManager`)
- L15 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogCPSDiscoveryCommunication, Log, All);`
- L15 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogCPSDiscoveryCommunication, Log, All);` (scope `UE::CaptureManager`)
- L16 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogCPSExportHandler, Log, All);`
- L16 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogCPSExportHandler, Log, All);` (scope `UE::CaptureManager`)

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureProtocolStack/Public/Utility/Error.h` (Public)


#### Free symbols / members of external scopes

- L11 _macro_ `#define CPS_CHECK_VOID_RESULT(Function) if (UE::CaptureManager::TProtocolResult<void> Result = Function; Result.HasError()) { return Result.StealError(); }`
