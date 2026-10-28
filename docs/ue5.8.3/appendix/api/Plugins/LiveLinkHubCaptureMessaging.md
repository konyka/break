# Plugins / LiveLinkHubCaptureMessaging

- module root: `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/LiveLinkHubCaptureMessaging`
- headers: 7; symbols: 171
- symbol kinds: class=8, delegate=7, enum=1, enumerator=3, function=7, macro=6, member=59, namespace=2, prototype=61, struct=13, typedef=2, variable=2
- PrivateDependencyModuleNames: MessagingCommon
- PublicDependencyModuleNames: CaptureProtocolStack, CaptureUtils, Core, CoreUObject, Engine

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/LiveLinkHubCaptureMessaging/Public/Features/ConnectAcceptor.h` (Public)


#### class `FConnectAcceptor`  
`class FConnectAcceptor : public FFeatureBase`  
_L16-54_
- inherits: `FFeatureBase`
- L20 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(FConnectResponse*, FConnectAccepted, const FConnectRequest& InRequest, const FMessageAddress& InAddress);`
- L21 _public prototype_ `DECLARE_DELEGATE_OneParam(FConnectionLostHandler, const FMessageAddress& InAddress);`
- L23 _public prototype_ `FConnectAcceptor();`
- L26 _public prototype_ `void SetConnectionHandler(FConnectAccepted InConnectHandler, FConnectionLostHandler InConnectionLostHandler);`
- L28 _public prototype_ `void Disconnect();`
- L29 _public prototype_ `bool IsConnected() const;`
- L33 _protected prototype_ `void Initialize(FMessageEndpointBuilder& InBuilder);`
- L37 _private prototype_ `void ConnectRequestHandler(const FConnectRequest& InRequest, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L38 _private prototype_ `void OnHangUpReceived(const FCaptureManagerHangUp& InRequest, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L39 _private prototype_ `void HandleKeepAlive(const FPingMessage& InRequest, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L41 _private prototype_ `void CheckConnectionActivity();`
- L43 _private member_ `double LastPingRequest = 0.0f;`
- L44 _private member_ `double InactivityTimeout = 20.0f;` — seconds
- L46 _private member_ `TSharedRef<UE::CaptureManager::FCaptureTimerManager> TimerManager;`
- L47 _private member_ `UE::CaptureManager::FCaptureTimerManager::FTimerHandle ClientActivity;`
- L49 _private member_ `std::atomic_bool bConnected = false;`
- L51 _private member_ `FCriticalSection CriticalSection;`
- L52 _private member_ `FConnectAccepted ConnectHandler;`
- L53 _private member_ `FConnectionLostHandler ConnectionLostHandler;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API LIVELINKHUBCAPTUREMESSAGING_API`
- L20 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(FConnectResponse*, FConnectAccepted, const FConnectRequest& InRequest, const FMessageAddress& InAddress);`
- L21 _delegate_ `DECLARE_DELEGATE_OneParam(FConnectionLostHandler, const FMessageAddress& InAddress);`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/LiveLinkHubCaptureMessaging/Public/Features/ConnectStarter.h` (Public)


#### class `FConnectStarter`  
`class FConnectStarter : public FFeatureBase, public TSharedFromThis<FConnectStarter>`  
_L16-63_
- inherits: `FFeatureBase,TSharedFromThis<FConnectStarter>`
- L22 _public prototype_ `DECLARE_DELEGATE_OneParam(FConnectHandler, const FConnectResponse& InResponse);`
- L23 _public prototype_ `DECLARE_DELEGATE(FDisconnectHandler);`
- L25 _public prototype_ `FConnectStarter();`
- L28 _public prototype_ `void Connect(FConnectHandler InConnectHandler);`
- L29 _public prototype_ `void Disconnect();`
- L30 _public prototype_ `void SetDisconnectHandler(FDisconnectHandler InHandler);`
- L32 _public prototype_ `bool IsConnected() const;`
- L36 _protected prototype_ `void Initialize(FMessageEndpointBuilder& InBuilder);`
- L40 _private member_ `static const float KeepAliveInterval;`
- L41 _private member_ `static const float KeepAliveTimeout;`
- L43 _private prototype_ `DECLARE_DELEGATE_OneParam(FPingCallback, const FPongMessage& InResponse);`
- L44 _private prototype_ `FGuid SendPingRequest(FPingCallback InCallback);`
- L46 _private prototype_ `void HandleConnectResponse(const FConnectResponse& InResponse, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L47 _private prototype_ `void HandlePingResponse(const FPongMessage& InResponse, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L48 _private prototype_ `void AddContext(FGuid InGuid, FConnectHandler InHandler);`
- L50 _private prototype_ `void OnKeepAliveInterval();`
- L52 _private member_ `FCriticalSection Mutex;`
- L53 _private member_ `TMap<FGuid, FConnectHandler> Contexts;`
- L55 _private member_ `FCriticalSection PingMutex;`
- L56 _private member_ `TMap<FGuid, FPingCallback> PingContexts;`
- L58 _private member_ `TSharedRef<UE::CaptureManager::FCaptureTimerManager> TimerManager;`
- L59 _private member_ `UE::CaptureManager::FCaptureTimerManager::FTimerHandle KeepAlive;`
- L60 _private member_ `FDisconnectHandler Handler;`
- L62 _private member_ `std::atomic_bool bConnected = false;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API LIVELINKHUBCAPTUREMESSAGING_API`
- L22 _delegate_ `DECLARE_DELEGATE_OneParam(FConnectHandler, const FConnectResponse& InResponse);`
- L23 _delegate_ `DECLARE_DELEGATE(FDisconnectHandler);`
- L43 _delegate_ `DECLARE_DELEGATE_OneParam(FPingCallback, const FPongMessage& InResponse);`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/LiveLinkHubCaptureMessaging/Public/Features/UploadStateHandler.h` (Public)


#### class `FUploadStateHandler`  
`class FUploadStateHandler : public FFeatureBase`  
_L14-37_
- inherits: `FFeatureBase`
- L18 _public prototype_ `DECLARE_DELEGATE_ThreeParams(FUploadStateCallback, const FGuid& InCaptureSourceId, const FGuid& InTakeUploadId, double InProgress);`
- L19 _public prototype_ `DECLARE_DELEGATE_FourParams(FUploadFinishedCallback, const FGuid& InCaptureSourceId, const FGuid& InTakeUploadId, FString InMessage, int32 InCode);`
- L21 _public prototype_ `FUploadStateHandler();`
- L23 _public prototype_ `void SetUploadCallbacks(FUploadStateCallback InStateCallback, FUploadFinishedCallback InFinishedCallback);`
- L28 _protected prototype_ `void Initialize(FMessageEndpointBuilder& InBuilder);`
- L31 _private prototype_ `void HandleUploadStateMessage(const FUploadState& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L32 _private prototype_ `void HandleUploadFinishedMessage(const FUploadFinished& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L34 _private member_ `FCriticalSection CriticalSection;`
- L35 _private member_ `FUploadStateCallback StateCallback;`
- L36 _private member_ `FUploadFinishedCallback FinishedCallback;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API LIVELINKHUBCAPTUREMESSAGING_API`
- L18 _delegate_ `DECLARE_DELEGATE_ThreeParams(FUploadStateCallback, const FGuid& InCaptureSourceId, const FGuid& InTakeUploadId, double InProgress);`
- L19 _delegate_ `DECLARE_DELEGATE_FourParams(FUploadFinishedCallback, const FGuid& InCaptureSourceId, const FGuid& InTakeUploadId, FString InMessage, int32 InCode);`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/LiveLinkHubCaptureMessaging/Public/Features/UploadStateSender.h` (Public)


#### class `FUploadStateSender`  
`class FUploadStateSender : public FFeatureBase`  
_L14-30_
- inherits: `FFeatureBase`
- L18 _public prototype_ `FUploadStateSender();`
- L20 _public prototype_ `void SendUploadStateMessage(const FGuid& InCaptureSourceId, const FGuid& InTakeUploadId, double InProgress);`
- L21 _public prototype_ `void SendUploadDoneMessage(const FGuid& InCaptureSourceId, const FGuid& InTakeUploadId, FString InMessage, int32 InCode);`
- L25 _protected prototype_ `void Initialize(FMessageEndpointBuilder& InBuilder);`
- L29 _private prototype_ `EStatus ConvertStatus(int32 InCode);`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API LIVELINKHUBCAPTUREMESSAGING_API`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/LiveLinkHubCaptureMessaging/Public/LiveLinkHubCaptureMessages.h` (Public)


#### enum `EStatus`  
`enum class EStatus`  
_L20-25_
- reflection: `UENUM()`
- L22 _public enumerator_ `Ok = 0`
- L23 _public enumerator_ `InvalidArgument = 1`
- L24 _public enumerator_ `InternalError = 2`

#### struct `FBaseMessage`  
`struct FBaseMessage`  
_L28-37_
- reflection: `USTRUCT()`
- L33 _public member_ `uint16 Version = UE::LiveLinkHubCaptureMessages::Version;` — `UPROPERTY()`
- L36 _public member_ `FGuid Guid;` — `UPROPERTY()`

#### struct `FBaseResponse`  
`struct FBaseResponse : public FBaseMessage`  
_L40-52_
- reflection: `USTRUCT()`
- inherits: `FBaseMessage`
- L45 _public member_ `EStatus Status = EStatus::Ok;` — `UPROPERTY()`
- L48 _public member_ `FString Message;` — `UPROPERTY()`
- L51 _public member_ `FGuid RequestGuid;` — `UPROPERTY()`

#### struct `FConnectRequest`  
`struct FConnectRequest : public FBaseMessage`  
_L55-58_
- reflection: `USTRUCT()`
- inherits: `FBaseMessage`

#### struct `FConnectResponse`  
`struct FConnectResponse : public FBaseResponse`  
_L61-64_
- reflection: `USTRUCT()`
- inherits: `FBaseResponse`

#### struct `FCaptureManagerHangUp`  
`struct FCaptureManagerHangUp : public FBaseMessage`  
_L67-70_
- reflection: `USTRUCT()`
- inherits: `FBaseMessage`

#### struct `FDiscoveryRequest`  
`struct FDiscoveryRequest`  
_L73-82_
- reflection: `USTRUCT()`
- L78 _public member_ `uint16 MessageVersion = UE::LiveLinkHubCaptureMessages::DiscoveryVersion;` — `UPROPERTY()`
- L81 _public member_ `FString HostName;` — `UPROPERTY()`

#### struct `FDiscoveryResponse`  
`struct FDiscoveryResponse`  
_L85-97_
- reflection: `USTRUCT()`
- L90 _public member_ `FString HostName;` — `UPROPERTY()`
- L93 _public member_ `FString IPAddress;` — `UPROPERTY()`
- L96 _public member_ `uint16 ExportPort = 0;` — `UPROPERTY()`

#### struct `FPingMessage`  
`struct FPingMessage : public FBaseMessage`  
_L100-103_
- reflection: `USTRUCT()`
- inherits: `FBaseMessage`

#### struct `FPongMessage`  
`struct FPongMessage : public FBaseResponse`  
_L106-109_
- reflection: `USTRUCT()`
- inherits: `FBaseResponse`

#### struct `FUploadState`  
`struct FUploadState`  
_L112-124_
- reflection: `USTRUCT()`
- L117 _public member_ `FGuid CaptureSourceId;` — `UPROPERTY()`
- L120 _public member_ `FGuid TakeUploadId;` — `UPROPERTY()`
- L123 _public member_ `double Progress = 0.0f;` — `UPROPERTY()`

#### struct `FUploadFinished`  
`struct FUploadFinished`  
_L127-142_
- reflection: `USTRUCT()`
- L132 _public member_ `FGuid CaptureSourceId;` — `UPROPERTY()`
- L135 _public member_ `FGuid TakeUploadId;` — `UPROPERTY()`
- L138 _public member_ `EStatus Status = EStatus::Ok;` — `UPROPERTY()`
- L141 _public member_ `FString Message;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace LiveLinkHubCaptureMessages` (scope `UE`)
- L15 _variable_ `constexpr uint16 Version = 1;` (scope `UE::LiveLinkHubCaptureMessages`)
- L16 _variable_ `constexpr uint16 DiscoveryVersion = 1;` (scope `UE::LiveLinkHubCaptureMessages`)

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/LiveLinkHubCaptureMessaging/Public/Messenger.h` (Public)


#### class `FFeatureBase`  
`class FFeatureBase`  
_L17-44_
- L22 _protected prototype_ `virtual ~FFeatureBase() = default;`
- L25 _protected prototype_ `virtual void Initialize(FMessageEndpointBuilder& InBuilder) = 0;`
- L28 _protected prototype_ `template <typename MessageType> void SendMessage(MessageType* InMessage);`
- L30 _protected prototype_ `void SetEndpoint(TSharedPtr<FMessageEndpoint> InEndpoint);`
- L31 _protected prototype_ `void SetAddress(const FMessageAddress& InAddress);`
- L32 _protected prototype_ `FMessageAddress GetAddress() const;`
- L36 _protected member_ `TSharedPtr<FMessageEndpoint> Endpoint;` — `UE_DEPRECATED(5.7, "Accessing the endpoint directly is deprecated and likely to result in a crash, use SendMessage instead. Access to this member will be removed in a future version")` — When removing this deprecation, make the member private and remove warning suppression in this class
- L40 _protected member_ `FMessageAddress Address;` — `UE_DEPRECATED(5.7, "Accessing the address directly is deprecated and likely to result in a crash, use Set/GetAddress instead. Access to this member will be removed in a future version")` — When removing this deprecation, make the member private and remove warning suppression in this classs
- L43 _private member_ `mutable FCriticalSection CriticalSection;`
- L47 _function_ `template <typename MessageType> void FFeatureBase::SendMessage(MessageType* InMessage)`

#### class `FMessenger`  
`template<class ... Features> class FMessenger : public Features...`  
_L76-127_
- inherits: `Features...`
- L81 _public member_ `inline static const FString Name = TEXT("Mes`
- L83 _public function_ `FMessenger() : Builder(*Name)`
- L95 _public function_ `~FMessenger()`
- L100 _public function_ `void SetAddress(FMessageAddress InAddress)`
- L107 _public function_ `FMessageAddress GetAddress() const`
- L112 _public function_ `FMessageAddress GetOwnAddress() const`
- L117 _public function_ `void SendDiscoveryResponse(FDiscoveryResponse* InResponse, FMessageAddress InReceiver)`
- L124 _private member_ `FMessageEndpointBuilder Builder;`
- L125 _private member_ `TSharedPtr<FMessageEndpoint> Endpoint;`
- L126 _private member_ `FMessageAddress Address;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API LIVELINKHUBCAPTUREMESSAGING_API`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/LiveLinkHubCaptureMessaging/Public/UploadDataMessage.h` (Public)


#### class `FUploadError`  
`class FUploadError`  
_L18-31_
- L22 _public prototype_ `FUploadError(FText InMessage, int32 InCode = 0);`
- L24 _public prototype_ `const FText& GetText() const;`
- L25 _public prototype_ `int32 GetCode() const;`
- L29 _private member_ `FText Message;`
- L30 _private member_ `int32 Code;`

#### struct `FUploadDataHeader`  
`struct FUploadDataHeader`  
_L38-50_
- L40 _public member_ `static const TArray<uint8> Header;`
- L42 _public member_ `FGuid ClientId;`
- L43 _public member_ `FGuid CaptureSourceId;`
- L44 _public member_ `FGuid TakeUploadId;`
- L46 _public member_ `FString CaptureSourceName;`
- L47 _public member_ `FString Slate;`
- L48 _public member_ `uint32 TakeNumber = 0;`
- L49 _public member_ `uint64 TotalLength = 0;`

#### struct `FUploadFileDataHeader`  
`struct FUploadFileDataHeader`  
_L52-56_
- L54 _public member_ `FString FileName;`
- L55 _public member_ `uint64 Length = 0;`

#### class `FUploadDataMessage`  
`class FUploadDataMessage`  
_L58-85_
- L62 _public member_ `static constexpr int32 HashSize = 16;`
- L64 _public prototype_ `static FUploadVoidResult SerializeHeader(FUploadDataHeader InHeader, UE::CaptureManager::ITcpSocketWriter& InWriter);`
- L65 _public prototype_ `static FUploadVoidResult SerializeFileHeader(FUploadFileDataHeader InFileHeader, UE::CaptureManager::ITcpSocketWriter& InWriter);`
- L66 _public prototype_ `static FUploadVoidResult SerializeData(TArray<uint8> InData, UE::CaptureManager::ITcpSocketWriter& InWriter);`
- L67 _public prototype_ `static FUploadVoidResult SerializeHash(TStaticArray<uint8, HashSize> InHash, UE::CaptureManager::ITcpSocketWriter& InWriter);`
- L69 _public prototype_ `static FUploadResult<FUploadDataHeader> DeserializeHeader(UE::CaptureManager::ITcpSocketReader& InReader);`
- L70 _public prototype_ `static FUploadResult<FUploadFileDataHeader> DeserializeFileHeader(UE::CaptureManager::ITcpSocketReader& InReader);`
- L71 _public prototype_ `static FUploadResult<TArray<uint8>> DeserializeData(uint32 InSize, UE::CaptureManager::ITcpSocketReader& InReader);`
- L72 _public prototype_ `static FUploadResult<TStaticArray<uint8, HashSize>> DeserializeHash(UE::CaptureManager::ITcpSocketReader& InReader);`
- L76 _private prototype_ `static FUploadVoidResult DeserializeStartHeader(UE::CaptureManager::ITcpSocketReader& InReader);`
- L77 _private prototype_ `static FUploadVoidResult DeserializeGuid(UE::CaptureManager::ITcpSocketReader& InReader, FGuid& OutFGuid);`
- L78 _private prototype_ `static FUploadVoidResult DeserializeTakeNumber(UE::CaptureManager::ITcpSocketReader& InReader, uint32& OutTakeNumber);`
- L79 _private prototype_ `static FUploadVoidResult DeserializeString(UE::CaptureManager::ITcpSocketReader& InReader, FString& OutTakeName);`
- L80 _private prototype_ `static FUploadVoidResult DeserializeTotalLength(UE::CaptureManager::ITcpSocketReader& InReader, uint64& OutTotalLength);`
- L81 _private prototype_ `static FUploadVoidResult DeserializeFileName(UE::CaptureManager::ITcpSocketReader& InReader, FString& OutFileName);`
- L82 _private prototype_ `static FUploadVoidResult DeserializeLength(UE::CaptureManager::ITcpSocketReader& InReader, uint64& OutLength);`
- L84 _private member_ `static constexpr uint32 InactivityTimeout = 15 * 1000;` — Miliseconds

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API LIVELINKHUBCAPTUREMESSAGING_API`
- L34 _typedef_ `template<typename T> using FUploadResult = TValueOrError<T, FUploadError>;`
- L36 _typedef_ `using FUploadVoidResult = FUploadResult<void>;`
