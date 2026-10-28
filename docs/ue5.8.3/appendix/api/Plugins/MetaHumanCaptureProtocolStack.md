# Plugins / MetaHumanCaptureProtocolStack

- module root: `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureProtocolStack`
- headers: 31; symbols: 832
- symbol kinds: class=77, delegate=14, enum=5, enumerator=23, externvar=92, function=10, macro=15, member=194, namespace=9, prototype=357, struct=11, typedef=24, variable=1
- PrivateDependencyModuleNames: CoreUObject, Engine, Json, JsonUtilities, Networking, Sockets, UnrealEd
- PublicDependencyModuleNames: Core, MetaHumanCaptureUtils

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureProtocolStack/Private/ExportClient/Definitions.h` (Private)


#### Free symbols / members of external scopes

- L7 _variable_ `static constexpr uint32 InactivityTimeoutMs = 15000;` — 15 seconds as recommended by the CPS Specification

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureProtocolStack/Private/MetaHumanCaptureProtocolStack.h` (Private)


#### class `FMetaHumanCaptureProtocolStackModule`  
`class FMetaHumanCaptureProtocolStackModule : public IModuleInterface`  
_L7-14_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L13 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureProtocolStack/Private/Utility/TimerManager.h` (Private)


#### class `FCPSTimerManager`  
`class FCPSTimerManager`  
_L10-47_
- L14 _public typedef_ `using FTimerHandle = FTSTicker::FDelegateHandle;`
- L16 _public member_ `static const float IdealTimeResolution;`
- L18 _public prototype_ `FCPSTimerManager(const float Resolution = IdealTimeResolution);`
- L20 _public prototype_ `static FCPSTimerManager& Get();`
- L21 _public prototype_ `~FCPSTimerManager();`
- L23 _public prototype_ `FTimerHandle AddTimer(FTimerDelegate InDelegate, float InRate, bool InbLoop = false, float InFirstDelay = 0.f);`
- L24 _public prototype_ `void RemoveTimer(FTimerHandle Handle);`
- L44 _private member_ `FTSTicker Ticker;`
- L45 _private member_ `TUniquePtr<FRunnableThread> Thread;`
- L46 _private member_ `TUniquePtr<FTimerManagerRunnable> Runnable;`

#### class `FCPSTimerManager::FTimerManagerRunnable`  
`class FTimerManagerRunnable final : public FRunnable`  
_L28-42_
- inherits: `FRunnable`
- L32 _public prototype_ `FTimerManagerRunnable(FCPSTimerManager* InOwner, const float InResolution);`
- L34 _public prototype_ `virtual uint32 Run() override;`
- L35 _public prototype_ `virtual void Stop() override;`
- L39 _private member_ `FCPSTimerManager* Owner;`
- L40 _private member_ `std::atomic_bool bShouldRun = true;`
- L41 _private member_ `const float IdealTimeResolution;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureProtocolStack/Public/Communication/TcpClient.h` (Public)


#### class `FTcpClient`  
`class FTcpClient final`  
_L25-51_
- L29 _public member_ `static constexpr uint32 BufferSize = 2 * 1024 * 1024;`
- L30 _public member_ `static constexpr int32 DisconnectedError = -10;`
- L31 _public member_ `static constexpr int32 TimeoutError = -1;`
- L33 _public prototype_ `FTcpClient();`
- L34 _public prototype_ `~FTcpClient();`
- L36 _public prototype_ `TProtocolResult<void> Init();`
- L38 _public prototype_ `TProtocolResult<void> Start(const FString& InServerAddress);` — Blocking function until connection is established
- L39 _public prototype_ `TProtocolResult<void> Stop();`
- L41 _public prototype_ `bool IsRunning() const;`
- L43 _public prototype_ `TProtocolResult<void> SendMessage(const TArray<uint8>& InPayload);`
- L44 _public prototype_ `TProtocolResult<TArray<uint8>> ReceiveMessage(const uint64 InSize, const uint32 InWaitTimeoutMs = ITcpSocketReader::DefaultWaitTimeoutMs);`
- L48 _private member_ `FSocketPtr TcpSocket;`
- L50 _private member_ `bool bRunning;`

#### class `FTcpClientReader`  
`class FTcpClientReader final : public ITcpSocketReader`  
_L53-62_
- inherits: `ITcpSocketReader`
- L56 _public prototype_ `FTcpClientReader(FTcpClient& InClient);`
- L58 _public prototype_ `virtual TProtocolResult<TArray<uint8>> ReceiveMessage(const uint64 InSize, const uint32 InWaitTimeoutMs = DefaultWaitTimeoutMs) override;`
- L61 _private member_ `FTcpClient& Client;`

#### class `FTcpClientWriter`  
`class FTcpClientWriter final : public ITcpSocketWriter`  
_L64-74_
- inherits: `ITcpSocketWriter`
- L67 _public prototype_ `FTcpClientWriter(FTcpClient& InClient);`
- L69 _public prototype_ `virtual TProtocolResult<void> SendMessage(const TArray<uint8>& InPayload) override;`
- L73 _private member_ `FTcpClient& Client;`

#### Free symbols / members of external scopes

- L23 _typedef_ `using FSocketPtr = TUniquePtr<FSocket, FSocketDeleter>;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureProtocolStack/Public/Communication/TcpReaderWriter.h` (Public)


#### class `ITcpSocketReader`  
`class ITcpSocketReader`  
_L9-17_
- L12 _public member_ `static constexpr uint32 DefaultWaitTimeoutMs = 1000;`
- L14 _public prototype_ `virtual ~ITcpSocketReader() = default;`
- L16 _public prototype_ `virtual TProtocolResult<TArray<uint8>> ReceiveMessage(const uint64 InSize, const uint32 InWaitTimeoutMs = DefaultWaitTimeoutMs) = 0;`

#### class `ITcpSocketWriter`  
`class ITcpSocketWriter`  
_L19-25_
- L22 _public prototype_ `virtual ~ITcpSocketWriter() = default;`
- L24 _public prototype_ `virtual TProtocolResult<void> SendMessage(const TArray<uint8>& InPayload) = 0;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureProtocolStack/Public/Communication/TcpServer.h` (Public)


#### class `FTcpClientHandler`  
`class FTcpClientHandler final`  
_L26-48_
- L30 _public member_ `static constexpr uint32 MaxBufferSize = 500 * 1024;`
- L31 _public member_ `static constexpr int32 DisconnectedError = -10;`
- L32 _public member_ `static constexpr int32 TimeoutError = -1;`
- L34 _public prototype_ `FTcpClientHandler(FSocketPtr InSocket, FString InEndpoint);`
- L35 _public prototype_ `~FTcpClientHandler();`
- L37 _public prototype_ `TProtocolResult<void> SendMessage(const TArray<uint8>& InData);`
- L38 _public prototype_ `TProtocolResult<TArray<uint8>> ReceiveMessage(const uint64 InSize, const uint32 InWaitTimeoutMs = ITcpSocketReader::DefaultWaitTimeoutMs);`
- L40 _public prototype_ `const FString& GetEndpoint() const;`
- L42 _public prototype_ `bool operator==(const FTcpClientHandler& InOther);`
- L46 _private member_ `FSocketPtr Socket;`
- L47 _private member_ `FString Endpoint;`

#### class `FTcpServer`  
`class FTcpServer`  
_L50-84_
- L54 _public member_ `static constexpr uint32 ThreadWaitTime = 500;` — Milliseconds
- L55 _public member_ `static constexpr uint16 AnyPort = 0;` — OS assigned port
- L57 _public prototype_ `DECLARE_DELEGATE_TwoParams(FConnectionHandler, TWeakPtr<FTcpClientHandler> InClient, bool bConnected) FTcpServer(const uint32 InMaxNumberOfClients);`
- L61 _public prototype_ `TProtocolResult<uint16> Start(const uint16 InListenPort = AnyPort);`
- L62 _public prototype_ `TProtocolResult<void> Stop();`
- L64 _public prototype_ `TProtocolResult<void> SendMessage(const TArray<uint8>& InMessage, const FString& InEndpoint);`
- L66 _public prototype_ `void DisconnectClient(const FString& InEndpoint);`
- L67 _public prototype_ `void DisconnectClientAsync(const FString& InEndpoint);`
- L68 _public prototype_ `void SetConnectionHandler(FConnectionHandler InOnConnectionHandler);`
- L70 _public prototype_ `int32 GetPort() const;`
- L74 _private member_ `TUniquePtr<FTcpListener> Listener;`
- L75 _private member_ `FSocketPtr Socket;`
- L77 _private member_ `uint32 MaxNumberOfClients;`
- L78 _private member_ `TMap<FString, TSharedPtr<FTcpClientHandler>> Clients;`
- L80 _private member_ `FConnectionHandler OnConnectionHandler;`
- L81 _private member_ `FRWLock Mutex;`
- L83 _private member_ `bool bRunning;`

#### class `FTcpConnectionReader`  
`class FTcpConnectionReader final : public ITcpSocketReader`  
_L86-95_
- inherits: `ITcpSocketReader`
- L89 _public prototype_ `FTcpConnectionReader(FTcpClientHandler& InClient);`
- L91 _public prototype_ `virtual TProtocolResult<TArray<uint8>> ReceiveMessage(const uint64 InSize, const uint32 InWaitTimeoutMs = DefaultWaitTimeoutMs) override;`
- L94 _private member_ `FTcpClientHandler& Client;`

#### class `FTcpConnectionWriter`  
`class FTcpConnectionWriter final : public ITcpSocketWriter`  
_L97-107_
- inherits: `ITcpSocketWriter`
- L100 _public prototype_ `FTcpConnectionWriter(FTcpClientHandler& InClient);`
- L102 _public prototype_ `virtual TProtocolResult<void> SendMessage(const TArray<uint8>& InPayload) override;`
- L106 _private member_ `FTcpClientHandler& Client;`

#### Free symbols / members of external scopes

- L24 _typedef_ `using FSocketPtr = TUniquePtr<FSocket, FSocketDeleter>;`
- L57 _delegate_ `DECLARE_DELEGATE_TwoParams(FConnectionHandler, TWeakPtr<FTcpClientHandler> InClient, bool bConnected) FTcpServer(const uint32 InMaxNumberOfClients);`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureProtocolStack/Public/Communication/UdpClient.h` (Public)


#### struct `FUdpClientConfigure`  
`struct FUdpClientConfigure`  
_L21-25_
- L23 _public member_ `uint16 ListenPort;`
- L24 _public member_ `FString MulticastIpAddress = "";`

#### class `FUdpClient`  
`class FUdpClient final`  
_L35-58_
- L39 _public member_ `static constexpr uint32 ThreadWaitTime = 500;` — Milliseconds
- L40 _public member_ `static constexpr uint32 BufferSize = 2 * 1024 * 1024;`
- L42 _public prototype_ `FUdpClient();`
- L43 _public prototype_ `~FUdpClient();`
- L45 _public prototype_ `TProtocolResult<void> Init(FUdpClientConfigure InConfig, FOnSocketDataReceived InReceiveHandler);`
- L46 _public prototype_ `TProtocolResult<void> Start();`
- L47 _public prototype_ `TProtocolResult<void> Stop();`
- L49 _public prototype_ `TProtocolResult<int32> SendMessage(const TArray<uint8>& InPayload, const FString& InEndpoint);`
- L53 _private member_ `TUniquePtr<FSocket> UdpSocket;`
- L55 _private member_ `TUniquePtr<FUdpSocketReceiver> UdpReceiver;`
- L57 _private member_ `bool bRunning;`

#### Free symbols / members of external scopes

- L27 _macro_ `#define CHECK_BOOL(Function) \`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureProtocolStack/Public/Control/Communication/ControlCommunication.h` (Public)


#### class `FControlCommunication`  
`class FControlCommunication final`  
_L15-71_
- L21 _public typedef_ `using FRunnerType = TQueueRunner<FControlPacket>;`
- L23 _public prototype_ `FControlCommunication();`
- L25 _public prototype_ `TProtocolResult<void> Init();`
- L26 _public prototype_ `TProtocolResult<void> Start(const FString& InServerIp, const uint16 InServerPort);`
- L27 _public prototype_ `TProtocolResult<void> Stop();`
- L29 _public prototype_ `bool IsRunning() const;`
- L31 _public prototype_ `void SendMessage(FControlPacket InMessage);`
- L33 _public prototype_ `void SetReceiveHandler(FOnPacketReceived InReceiveHandler);`
- L57 _private prototype_ `void OnProcessReceivedPacket(FControlPacket InMessage);`
- L58 _private prototype_ `void OnProcessSentPacket(FControlPacket InMessage);`
- L59 _private prototype_ `void RunnableHandler(TSharedPtr<FRunnable> InRunnable);`
- L61 _private prototype_ `TProtocolResult<FControlPacketHeader> ReceiveControlHeader();`
- L62 _private prototype_ `TProtocolResult<void> ReceiveControlPacket(const FControlPacketHeader& InHeader);`
- L64 _private member_ `FTcpClient Client;`
- L65 _private member_ `FOnPacketReceived ReceiveHandler;`
- L67 _private member_ `FRunnerType SynchronizedReceiver;`
- L68 _private member_ `FRunnerType SynchronizedSender;`
- L69 _private member_ `TQueueRunner<TSharedPtr<FRunnable>> SynchronizedRunnable;`
- L70 _private member_ `TWeakPtr<FCommunicationRunnable> Runnable;`

#### class `FControlCommunication::FCommunicationRunnable`  
`class FCommunicationRunnable : public FRunnable`  
_L37-54_
- inherits: `FRunnable`
- L41 _public prototype_ `FCommunicationRunnable(FControlCommunication& InCommunication);`
- L42 _public prototype_ `virtual ~FCommunicationRunnable();`
- L44 _public prototype_ `uint32 Run() override;`
- L45 _public prototype_ `void Stop() override;`
- L47 _public prototype_ `void Join();`
- L51 _private member_ `FControlCommunication& Communication;`
- L52 _private member_ `bool bIsRunning;`
- L53 _private member_ `FEvent* DoneEvent;`

#### Free symbols / members of external scopes

- L19 _delegate_ `DECLARE_DELEGATE_OneParam(FOnPacketReceived, FControlPacket InPacket) using FRunnerType = TQueueRunner<FControlPacket>;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureProtocolStack/Public/Control/Communication/ControlPacket.h` (Public)


#### class `FControlPacketHeader`  
`class FControlPacketHeader final`  
_L13-32_
- L17 _public member_ `static const TArray<uint8> Header;`
- L19 _public prototype_ `static TProtocolResult<FControlPacketHeader> Deserialize(ITcpSocketReader& InReader);`
- L20 _public prototype_ `static uint32 GetHeaderSize();`
- L22 _public prototype_ `FControlPacketHeader();`
- L23 _public prototype_ `FControlPacketHeader(uint16 InVersion, uint32 InPayloadSize);`
- L25 _public prototype_ `uint16 GetVersion() const;`
- L26 _public prototype_ `uint32 GetPayloadSize() const;`
- L30 _private member_ `uint16 Version;`
- L31 _private member_ `uint32 PayloadSize;`

#### class `FControlPacket`  
`class FControlPacket final`  
_L34-58_
- L38 _public prototype_ `static TProtocolResult<FControlPacket> Deserialize(const FControlPacketHeader& InPacketHeader, ITcpSocketReader& InReader);`
- L39 _public prototype_ `static TProtocolResult<void> Serialize(const FControlPacket& InMessage, ITcpSocketWriter& InWriter);`
- L41 _public prototype_ `FControlPacket();`
- L42 _public prototype_ `FControlPacket(uint16 InVersion, TArray<uint8> InPayload);`
- L44 _public prototype_ `FControlPacket(const FControlPacket& InOther) = default;`
- L45 _public prototype_ `FControlPacket(FControlPacket&& InOther) = default;`
- L47 _public prototype_ `FControlPacket& operator=(const FControlPacket& InOther) = default;`
- L48 _public prototype_ `FControlPacket& operator=(FControlPacket&& InOther) = default;`
- L50 _public prototype_ `uint16 GetVersion() const;`
- L51 _public prototype_ `const TArray<uint8>& GetPayload() const;`
- L52 _public prototype_ `uint32 GetPayloadSize() const;`
- L56 _private member_ `FControlPacketHeader Header;`
- L57 _private member_ `TArray<uint8> Payload;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureProtocolStack/Public/Control/ControlMessenger.h` (Public)


#### class `FKeepAliveCounter`  
`class FKeepAliveCounter`  
_L24-36_
- L27 _public prototype_ `FKeepAliveCounter();`
- L29 _public prototype_ `void Increment();`
- L30 _public prototype_ `void Reset();`
- L31 _public prototype_ `bool HasReached(uint16 InBound);`
- L35 _private member_ `std::atomic<uint16> Counter;`

#### class `FControlMessenger`  
`FControlMessenger final`  
_L39-212_
- reflection: `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L45 _public typedef_ `template<class RequestType> using FOnControlResponse = TDelegate<void(TProtocolResult<typename RequestType::ResponseType> InResult)>;`
- L48 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnDisconnect, const FString& InCause);`
- L50 _public member_ `static constexpr int32 ResponseWaitTime = 3;` — Seconds
- L51 _public member_ `static constexpr int32 KeepAliveInterval = 5;` — Seconds
- L52 _public member_ `static const TCHAR* HandshakeSessionId;`
- L54 _public prototype_ `FControlMessenger();`
- L55 _public prototype_ `~FControlMessenger();`
- L58 _public prototype_ `void RegisterUpdateHandler(FString InAddressPath, FControlUpdate::FOnUpdateMessage InUpdateHandler);`
- L59 _public prototype_ `void RegisterDisconnectHandler(FOnDisconnect InOnDisconnectHandler);`
- L62 _public prototype_ `TProtocolResult<void> Start(const FString& InServerIp, const uint16 InServerPort);`
- L63 _public prototype_ `TProtocolResult<void> Stop();`
- L65 _public prototype_ `TProtocolResult<void> StartSession();`
- L67 _public prototype_ `TProtocolResult<FGetServerInformationResponse> GetServerInformation();`
- L71 _public function_ `template<class RequestType> TProtocolResult<typename RequestType::ResponseType> SendRequest(RequestType InRequest)`
- L152 _public function_ `template<class RequestType> void SendAsyncRequest(RequestType InRequest, FOnControlResponse<RequestType> InOnResponse)`
- L180 _private prototype_ `void SendPacket(FControlPacket InPacket);`
- L181 _private prototype_ `void KeepAlive();`
- L182 _private prototype_ `void MessageHandler(FControlPacket InPacket);`
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
- L202 _private member_ `TMap<FString, FControlUpdate::FOnUpdateMessage> UpdateHandlers;`
- L205 _private member_ `FTSTicker::FDelegateHandle KeepAliveTimer;`
- L206 _private member_ `FKeepAliveCounter KeepAliveFailures;`
- L208 _private member_ `TQueueRunner<FAsyncRequestDelegate> AsyncRequestRunner;`
- L209 _private member_ `FOnDisconnect OnDisconnectHandler;`
- L211 _private member_ `FRandomStream RandomStream;`

#### struct `FControlMessenger::FRequestContext`  
`struct FRequestContext`  
_L166-178_
- L169 _public function_ `FRequestContext(FControlMessage InRequest, TPromise<TProtocolResult<FControlMessage>> InPromise) : Request(MoveTemp(InRequest)) , Promise(MoveTemp(InPromise))`
- L175 _public member_ `FControlMessage Request;`
- L176 _public member_ `TPromise<TProtocolResult<FControlMessage>> Promise;`

#### Free symbols / members of external scopes

- L22 _macro_ `#define UE_API METAHUMANCAPTUREPROTOCOLSTACK_API`
- L48 _delegate_ `DECLARE_DELEGATE_OneParam(FOnDisconnect, const FString& InCause);`
- L155 _function_ `` (scope `FControlMessenger::SendAsyncRequest`)
- L164 _delegate_ `DECLARE_DELEGATE(FAsyncRequestDelegate) struct FRequestContext { PRAGMA_DISABLE_DEPRECATION_WARNINGS FRequestContext(FControlMessage InRequest, TPromise<TProtocolResult<FControlMessage>> InPromise) : Request(MoveTemp(InRequest)) , Promise(MoveTemp(InPromise)) { } FControlMessage Request; TPromise<TProtocolResult<FControlMessage>> Promise; PRAGMA_ENABLE_DEPRECATION_WARNINGS };`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureProtocolStack/Public/Control/Messages/Constants.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace CPS` (scope `UE`)
- L7 _namespace_ `namespace AddressPaths` (scope `UE::CPS`)
- L11 _externvar_ `extern const TCHAR* GKeepAlive;` (scope `UE::CPS::AddressPaths`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")` — Requests/Responses
- L13 _externvar_ `extern const TCHAR* GStartSession;` (scope `UE::CPS::AddressPaths`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L15 _externvar_ `extern const TCHAR* GStopSession;` (scope `UE::CPS::AddressPaths`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L17 _externvar_ `extern const TCHAR* GSubscribe;` (scope `UE::CPS::AddressPaths`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L19 _externvar_ `extern const TCHAR* GUnsubscribe;` (scope `UE::CPS::AddressPaths`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L21 _externvar_ `extern const TCHAR* GGetServerInformation;` (scope `UE::CPS::AddressPaths`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L23 _externvar_ `extern const TCHAR* GGetState;` (scope `UE::CPS::AddressPaths`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L25 _externvar_ `extern const TCHAR* GStartRecordingTake;` (scope `UE::CPS::AddressPaths`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L27 _externvar_ `extern const TCHAR* GStopRecordingTake;` (scope `UE::CPS::AddressPaths`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L29 _externvar_ `extern const TCHAR* GAbortRecordingTake;` (scope `UE::CPS::AddressPaths`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L31 _externvar_ `extern const TCHAR* GGetTakeList;` (scope `UE::CPS::AddressPaths`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L33 _externvar_ `extern const TCHAR* GGetTakeMetadata;` (scope `UE::CPS::AddressPaths`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L35 _externvar_ `extern const TCHAR* GExportTakeData;` (scope `UE::CPS::AddressPaths`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L37 _externvar_ `extern const TCHAR* GExportTakeVideoFrame;` (scope `UE::CPS::AddressPaths`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L39 _externvar_ `extern const TCHAR* GExportCameraFeedFrame;` (scope `UE::CPS::AddressPaths`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L41 _externvar_ `extern const TCHAR* GPauseExport;` (scope `UE::CPS::AddressPaths`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L43 _externvar_ `extern const TCHAR* GCancelExport;` (scope `UE::CPS::AddressPaths`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L47 _externvar_ `extern const TCHAR* GSessionStopped;` (scope `UE::CPS::AddressPaths`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")` — Updates
- L49 _externvar_ `extern const TCHAR* GRecordingStatus;` (scope `UE::CPS::AddressPaths`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L51 _externvar_ `extern const TCHAR* GTakeAdded;` (scope `UE::CPS::AddressPaths`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L53 _externvar_ `extern const TCHAR* GTakeRemoved;` (scope `UE::CPS::AddressPaths`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L55 _externvar_ `extern const TCHAR* GTakeUpdated;` (scope `UE::CPS::AddressPaths`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L59 _externvar_ `extern const TCHAR* GDiskCapacity;` (scope `UE::CPS::AddressPaths`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")` — Platform Specific: IOS
- L61 _externvar_ `extern const TCHAR* GBattery;` (scope `UE::CPS::AddressPaths`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L63 _externvar_ `extern const TCHAR* GThermalState;` (scope `UE::CPS::AddressPaths`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L66 _namespace_ `namespace UE`
- L66 _namespace_ `namespace CPS` (scope `UE`)
- L66 _namespace_ `namespace Properties` (scope `UE::CPS`)
- L71 _externvar_ `extern const TCHAR* GSessionId;` (scope `UE::CPS::Properties`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")` — Keys Messages
- L73 _externvar_ `extern const TCHAR* GAddressPath;` (scope `UE::CPS::Properties`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L75 _externvar_ `extern const TCHAR* GTransactionId;` (scope `UE::CPS::Properties`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L77 _externvar_ `extern const TCHAR* GTimestamp;` (scope `UE::CPS::Properties`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L79 _externvar_ `extern const TCHAR* GType;` (scope `UE::CPS::Properties`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L81 _externvar_ `extern const TCHAR* GBody;` (scope `UE::CPS::Properties`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L83 _externvar_ `extern const TCHAR* GError;` (scope `UE::CPS::Properties`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L85 _externvar_ `extern const TCHAR* GDescription;` (scope `UE::CPS::Properties`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L89 _externvar_ `extern const TCHAR* GSlateName;` (scope `UE::CPS::Properties`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")` — Requests
- L91 _externvar_ `extern const TCHAR* GTakeNumber;` (scope `UE::CPS::Properties`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L93 _externvar_ `extern const TCHAR* GSubject;` (scope `UE::CPS::Properties`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L95 _externvar_ `extern const TCHAR* GScenario;` (scope `UE::CPS::Properties`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L97 _externvar_ `extern const TCHAR* GTags;` (scope `UE::CPS::Properties`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L99 _externvar_ `extern const TCHAR* GNames;` (scope `UE::CPS::Properties`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L101 _externvar_ `extern const TCHAR* GTakeName;` (scope `UE::CPS::Properties`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L103 _externvar_ `extern const TCHAR* GFiles;` (scope `UE::CPS::Properties`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L105 _externvar_ `extern const TCHAR* GName;` (scope `UE::CPS::Properties`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L107 _externvar_ `extern const TCHAR* GOffset;` (scope `UE::CPS::Properties`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L112 _externvar_ `extern const TCHAR* GId;` (scope `UE::CPS::Properties`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")` — Responses
- L114 _externvar_ `extern const TCHAR* GModel;` (scope `UE::CPS::Properties`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L116 _externvar_ `extern const TCHAR* GPlatformName;` (scope `UE::CPS::Properties`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L118 _externvar_ `extern const TCHAR* GPlatformVersion;` (scope `UE::CPS::Properties`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L120 _externvar_ `extern const TCHAR* GSoftwareName;` (scope `UE::CPS::Properties`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L122 _externvar_ `extern const TCHAR* GSoftwareVersion;` (scope `UE::CPS::Properties`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L124 _externvar_ `extern const TCHAR* GExportPort;` (scope `UE::CPS::Properties`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L126 _externvar_ `extern const TCHAR* GIsRecording;` (scope `UE::CPS::Properties`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L128 _externvar_ `extern const TCHAR* GPlatformState;` (scope `UE::CPS::Properties`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L130 _externvar_ `extern const TCHAR* GTakes;` (scope `UE::CPS::Properties`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L132 _externvar_ `extern const TCHAR* GDateTime;` (scope `UE::CPS::Properties`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L134 _externvar_ `extern const TCHAR* GFrames;` (scope `UE::CPS::Properties`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L136 _externvar_ `extern const TCHAR* GAppVersion;` (scope `UE::CPS::Properties`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L138 _externvar_ `extern const TCHAR* GLength;` (scope `UE::CPS::Properties`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L140 _externvar_ `extern const TCHAR* GVideo;` (scope `UE::CPS::Properties`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L142 _externvar_ `extern const TCHAR* GFrameRate;` (scope `UE::CPS::Properties`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L144 _externvar_ `extern const TCHAR* GHeight;` (scope `UE::CPS::Properties`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L146 _externvar_ `extern const TCHAR* GWidth;` (scope `UE::CPS::Properties`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L148 _externvar_ `extern const TCHAR* GAudio;` (scope `UE::CPS::Properties`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L150 _externvar_ `extern const TCHAR* GChannels;` (scope `UE::CPS::Properties`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L152 _externvar_ `extern const TCHAR* GSampleRate;` (scope `UE::CPS::Properties`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L154 _externvar_ `extern const TCHAR* GBitsPerChannel;` (scope `UE::CPS::Properties`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L158 _externvar_ `extern const TCHAR* GTotalCapacity;` (scope `UE::CPS::Properties`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")` — Platform Specific: iOS
- L160 _externvar_ `extern const TCHAR* GRemainingCapacity;` (scope `UE::CPS::Properties`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L162 _externvar_ `extern const TCHAR* GBatteryLevel;` (scope `UE::CPS::Properties`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L164 _externvar_ `extern const TCHAR* GThermalState;` (scope `UE::CPS::Properties`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L167 _externvar_ `extern const TCHAR* GTotal;` (scope `UE::CPS::Properties`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L169 _externvar_ `extern const TCHAR* GRemaining;` (scope `UE::CPS::Properties`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L171 _externvar_ `extern const TCHAR* GLevel;` (scope `UE::CPS::Properties`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L173 _externvar_ `extern const TCHAR* GState;` (scope `UE::CPS::Properties`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L178 _externvar_ `extern const TCHAR* GRequest;` (scope `UE::CPS::Properties`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")` — Values Messages
- L180 _externvar_ `extern const TCHAR* GResponse;` (scope `UE::CPS::Properties`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L182 _externvar_ `extern const TCHAR* GUpdate;` (scope `UE::CPS::Properties`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L185 _externvar_ `extern const TCHAR* GIOS;` (scope `UE::CPS::Properties`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L187 _externvar_ `extern const TCHAR* GAndroid;` (scope `UE::CPS::Properties`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L189 _externvar_ `extern const TCHAR* GWindows;` (scope `UE::CPS::Properties`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L191 _externvar_ `extern const TCHAR* GWindowsServer;` (scope `UE::CPS::Properties`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L193 _externvar_ `extern const TCHAR* GLinux;` (scope `UE::CPS::Properties`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L195 _externvar_ `extern const TCHAR* GMacOS;` (scope `UE::CPS::Properties`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L199 _externvar_ `extern const TCHAR* GNominal;` (scope `UE::CPS::Properties`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")` — Platform Specific: iOS
- L201 _externvar_ `extern const TCHAR* GFair;` (scope `UE::CPS::Properties`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L203 _externvar_ `extern const TCHAR* GSerious;` (scope `UE::CPS::Properties`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L205 _externvar_ `extern const TCHAR* GCritical;` (scope `UE::CPS::Properties`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L208 _namespace_ `namespace UE`
- L208 _namespace_ `namespace CPS` (scope `UE`)
- L208 _namespace_ `namespace ErrorNames` (scope `UE::CPS`)
- L211 _externvar_ `extern const TCHAR* GUnsupportedProtocolVersion;` (scope `UE::CPS::ErrorNames`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L213 _externvar_ `extern const TCHAR* GRequestFailed;` (scope `UE::CPS::ErrorNames`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L215 _externvar_ `extern const TCHAR* GRequestParsingFailed;` (scope `UE::CPS::ErrorNames`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L217 _externvar_ `extern const TCHAR* GNotSupported;` (scope `UE::CPS::ErrorNames`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L219 _externvar_ `extern const TCHAR* GNoSession;` (scope `UE::CPS::ErrorNames`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L221 _externvar_ `extern const TCHAR* GMissingBody;` (scope `UE::CPS::ErrorNames`) — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureProtocolStack/Public/Control/Messages/ControlJsonUtilities.h` (Public)


#### class `FJsonUtility`  
`class UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")FJsonUtility final`  
_L17-37_
- L20 _public prototype_ `static bool CreateJsonFromUTF8Data(const TArray<uint8>& InData, TSharedPtr<FJsonObject>& OutObject);`
- L21 _public prototype_ `static bool CreateUTF8DataFromJson(TSharedPtr<FJsonObject> InObject, TArray<uint8>& OutData);`
- L24 _public function_ `template <typename T> static TProtocolResult<void> ParseNumber(const TSharedPtr<FJsonObject>& InBody, const FString& InFieldName, T& OutFieldValue)`
- L33 _public prototype_ `static TProtocolResult<void> ParseString(const TSharedPtr<FJsonObject>& InBody, const FString& InFieldName, FString& OutFieldValue);`
- L34 _public prototype_ `static TProtocolResult<void> ParseBool(const TSharedPtr<FJsonObject>& InBody, const FString& InFieldName, bool& OutFieldValue);`
- L35 _public prototype_ `static TProtocolResult<void> ParseObject(const TSharedPtr<FJsonObject>& InBody, const FString& InFieldName, const TSharedPtr<FJsonObject>*& OutFieldValue);`
- L36 _public prototype_ `static TProtocolResult<void> ParseArray(const TSharedPtr<FJsonObject>& InBody, const FString& InFieldName, const TArray<TSharedPtr<FJsonValue>>*& OutFieldValue);`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API METAHUMANCAPTUREPROTOCOLSTACK_API`
- L15 _macro_ `#define CHECK_PARSE CPS_CHECK_VOID_RESULT`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureProtocolStack/Public/Control/Messages/ControlMessage.h` (Public)


#### class `FControlMessage`  
`FControlMessage final`  
_L10-75_
- reflection: `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L23 _public prototype_ `FControlMessage(FString InAddressPath, EType InType, TSharedPtr<FJsonObject> InBody);`
- L25 _public prototype_ `FControlMessage(const FControlMessage& InOther) = default;`
- L26 _public prototype_ `FControlMessage(FControlMessage&& InOther) = default;`
- L28 _public prototype_ `FControlMessage& operator=(const FControlMessage& InOther) = default;`
- L29 _public prototype_ `FControlMessage& operator=(FControlMessage&& InOther) = default;`
- L31 _public prototype_ `static TProtocolResult<FControlMessage> Deserialize(const FControlPacket& InPacket);`
- L32 _public prototype_ `static TProtocolResult<FControlPacket> Serialize(const FControlMessage& InMessage);`
- L34 _public prototype_ `void SetSessionId(FString InSessionId);`
- L35 _public prototype_ `void SetTransactionId(uint32 InTransactionId);`
- L36 _public prototype_ `void SetTimestamp(uint64 InTimestamp);`
- L38 _public prototype_ `const FString& GetSessionId() const;`
- L39 _public prototype_ `const FString& GetAddressPath() const;`
- L40 _public prototype_ `uint32 GetTransactionId() const;`
- L41 _public prototype_ `uint64 GetTimestamp() const;`
- L42 _public prototype_ `EType GetType() const;`
- L43 _public prototype_ `const TSharedPtr<FJsonObject>& GetBody() const;`
- L44 _public prototype_ `TSharedPtr<FJsonObject>& GetBody();`
- L46 _public prototype_ `const FString& GetErrorName() const;`
- L47 _public prototype_ `const FString& GetErrorDescription() const;`
- L57 _private prototype_ `FControlMessage(FString InSessionId, FString InAddressPath, uint32 InTransactionId, uint64 InTimestamp, EType InMessageType, TSharedPtr<FJsonObject> InBody, FErrorResponse InError);`
- L65 _private prototype_ `static EType DeserializeType(FString InMessageTypeStr);`
- L66 _private prototype_ `static FString SerializeType(EType InMessageType);`
- L68 _private member_ `FString SessionId;`
- L69 _private member_ `FString AddressPath;`
- L70 _private member_ `uint32 TransactionId;`
- L71 _private member_ `uint64 Timestamp;`
- L72 _private member_ `EType MessageType;`
- L73 _private member_ `TSharedPtr<FJsonObject> Body;`
- L74 _private member_ `FErrorResponse Error;`

#### enum `FControlMessage::EType`  
`enum class EType`  
_L14-21_
- L16 _public enumerator_ `Request`
- L17 _public enumerator_ `Response`
- L18 _public enumerator_ `Update`
- L20 _public enumerator_ `Invalid`

#### struct `FControlMessage::FErrorResponse`  
`struct FErrorResponse`  
_L51-55_
- L53 _public member_ `FString Name = TEXT("");`
- L54 _public member_ `FString Description = TEXT("");`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API METAHUMANCAPTUREPROTOCOLSTACK_API`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureProtocolStack/Public/Control/Messages/ControlRequest.h` (Public)


#### class `FControlRequest`  
`class UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module") FControlRequest`  
_L10-23_
- L14 _public prototype_ `FControlRequest(FString InAddressPath);`
- L15 _public prototype_ `virtual ~FControlRequest() = default;`
- L17 _public prototype_ `const FString& GetAddressPath() const;`
- L18 _public prototype_ `virtual TSharedPtr<FJsonObject> GetBody() const;`
- L22 _private member_ `FString AddressPath;`

#### class `FKeepAliveRequest`  
`class UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module") FKeepAliveRequest final : public FControlRequest`  
_L26-33_
- inherits: `FControlRequest`
- L30 _public typedef_ `using ResponseType = FKeepAliveResponse;`
- L32 _public prototype_ `FKeepAliveRequest();`

#### class `FStartSessionRequest`  
`class UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module") FStartSessionRequest final : public FControlRequest`  
_L35-42_
- inherits: `FControlRequest`
- L39 _public typedef_ `using ResponseType = FStartSessionResponse;`
- L41 _public prototype_ `FStartSessionRequest();`

#### class `FStopSessionRequest`  
`class UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module") FStopSessionRequest final : public FControlRequest`  
_L44-51_
- inherits: `FControlRequest`
- L48 _public typedef_ `using ResponseType = FStopSessionResponse;`
- L50 _public prototype_ `FStopSessionRequest();`

#### class `FGetServerInformationRequest`  
`class UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module") FGetServerInformationRequest final : public FControlRequest`  
_L54-61_
- inherits: `FControlRequest`
- L58 _public typedef_ `using ResponseType = FGetServerInformationResponse;`
- L60 _public prototype_ `FGetServerInformationRequest();`

#### class `FSubscribeRequest`  
`class UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module") FSubscribeRequest final : public FControlRequest`  
_L63-70_
- inherits: `FControlRequest`
- L67 _public typedef_ `using ResponseType = FSubscribeResponse;`
- L69 _public prototype_ `FSubscribeRequest();`

#### class `FUnsubscribeRequest`  
`class UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module") FUnsubscribeRequest final : public FControlRequest`  
_L72-79_
- inherits: `FControlRequest`
- L76 _public typedef_ `using ResponseType = FUnsubscribeResponse;`
- L78 _public prototype_ `FUnsubscribeRequest();`

#### class `FGetStateRequest`  
`class UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module") FGetStateRequest final : public FControlRequest`  
_L81-88_
- inherits: `FControlRequest`
- L85 _public typedef_ `using ResponseType = FGetStateResponse;`
- L87 _public prototype_ `FGetStateRequest();`

#### class `FStartRecordingTakeRequest`  
`class UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module") FStartRecordingTakeRequest final : public FControlRequest`  
_L90-111_
- inherits: `FControlRequest`
- L94 _public typedef_ `using ResponseType = FStartRecordingTakeResponse;`
- L96 _public prototype_ `FStartRecordingTakeRequest(FString InSlateName, uint16 InTakeNumber, TOptional<FString> InSubject = TOptional<FString>(), TOptional<FString> InScenario = TOptional<FString>(), TOptional<TArray<FString>> InTags = TOptional<TArray<FString>>());`
- L102 _public prototype_ `virtual TSharedPtr<FJsonObject> GetBody() const override;`
- L106 _private member_ `FString SlateName;`
- L107 _private member_ `uint16 TakeNumber;`
- L108 _private member_ `TOptional<FString> Subject;`
- L109 _private member_ `TOptional<FString> Scenario;`
- L110 _private member_ `TOptional<TArray<FString>> Tags;`

#### class `FStopRecordingTakeRequest`  
`class UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module") FStopRecordingTakeRequest final : public FControlRequest`  
_L113-120_
- inherits: `FControlRequest`
- L117 _public typedef_ `using ResponseType = FStopRecordingTakeResponse;`
- L119 _public prototype_ `FStopRecordingTakeRequest();`

#### class `FAbortRecordingTakeRequest`  
`class UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module") FAbortRecordingTakeRequest final : public FControlRequest`  
_L122-129_
- inherits: `FControlRequest`
- L126 _public typedef_ `using ResponseType = FAbortRecordingTakeResponse;`
- L128 _public prototype_ `FAbortRecordingTakeRequest();`

#### class `FGetTakeListRequest`  
`class UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module") FGetTakeListRequest final : public FControlRequest`  
_L131-138_
- inherits: `FControlRequest`
- L135 _public typedef_ `using ResponseType = FGetTakeListResponse;`
- L137 _public prototype_ `FGetTakeListRequest();`

#### class `FGetTakeMetadataRequest`  
`class UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module") FGetTakeMetadataRequest final : public FControlRequest`  
_L140-153_
- inherits: `FControlRequest`
- L144 _public typedef_ `using ResponseType = FGetTakeMetadataResponse;`
- L146 _public prototype_ `FGetTakeMetadataRequest(TArray<FString> InNames);`
- L148 _public prototype_ `virtual TSharedPtr<FJsonObject> GetBody() const override;`
- L152 _private member_ `TArray<FString> Names;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API METAHUMANCAPTUREPROTOCOLSTACK_API`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureProtocolStack/Public/Control/Messages/ControlResponse.h` (Public)


#### class `FControlResponse`  
`class UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")FControlResponse`  
_L9-23_
- L13 _public prototype_ `FControlResponse(FString InAddressPath);`
- L14 _public prototype_ `virtual ~FControlResponse() = default;`
- L16 _public prototype_ `virtual TProtocolResult<void> Parse(TSharedPtr<FJsonObject> InBody);`
- L18 _public prototype_ `const FString& GetAddressPath() const;`
- L22 _private member_ `FString AddressPath;`

#### class `FKeepAliveResponse`  
`class UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module") FKeepAliveResponse final : public FControlResponse`  
_L26-31_
- inherits: `FControlResponse`
- L30 _public prototype_ `FKeepAliveResponse();`

#### class `FStartSessionResponse`  
`class UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module") FStartSessionResponse final : public FControlResponse`  
_L33-46_
- inherits: `FControlResponse`
- L37 _public prototype_ `FStartSessionResponse();`
- L39 _public prototype_ `virtual TProtocolResult<void> Parse(TSharedPtr<FJsonObject> InBody) override;`
- L41 _public prototype_ `const FString& GetSessionId() const;`
- L45 _private member_ `FString SessionId;`

#### class `FStopSessionResponse`  
`class UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module") FStopSessionResponse final : public FControlResponse`  
_L48-53_
- inherits: `FControlResponse`
- L52 _public prototype_ `FStopSessionResponse();`

#### class `FGetServerInformationResponse`  
`class UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module") FGetServerInformationResponse final : public FControlResponse`  
_L55-82_
- inherits: `FControlResponse`
- L59 _public prototype_ `FGetServerInformationResponse();`
- L61 _public prototype_ `virtual TProtocolResult<void> Parse(TSharedPtr<FJsonObject> InBody) override;`
- L63 _public prototype_ `const FString& GetId() const;`
- L64 _public prototype_ `const FString& GetName() const;`
- L65 _public prototype_ `const FString& GetModel() const;`
- L66 _public prototype_ `const FString& GetPlatformName() const;`
- L67 _public prototype_ `const FString& GetPlatformVersion() const;`
- L68 _public prototype_ `const FString& GetSoftwareName() const;`
- L69 _public prototype_ `const FString& GetSoftwareVersion() const;`
- L70 _public prototype_ `uint16 GetExportPort() const;`
- L74 _private member_ `FString Id;`
- L75 _private member_ `FString Name;`
- L76 _private member_ `FString Model;`
- L77 _private member_ `FString PlatformName;`
- L78 _private member_ `FString PlatformVersion;`
- L79 _private member_ `FString SoftwareName;`
- L80 _private member_ `FString SoftwareVersion;`
- L81 _private member_ `uint16 ExportPort;`

#### class `FSubscribeResponse`  
`class UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module") FSubscribeResponse final : public FControlResponse`  
_L84-89_
- inherits: `FControlResponse`
- L88 _public prototype_ `FSubscribeResponse();`

#### class `FUnsubscribeResponse`  
`class UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module") FUnsubscribeResponse final : public FControlResponse`  
_L91-96_
- inherits: `FControlResponse`
- L95 _public prototype_ `FUnsubscribeResponse();`

#### class `FGetStateResponse`  
`class UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module") FGetStateResponse final : public FControlResponse`  
_L99-114_
- inherits: `FControlResponse`
- L103 _public prototype_ `FGetStateResponse();`
- L105 _public prototype_ `virtual TProtocolResult<void> Parse(TSharedPtr<FJsonObject> InBody) override;`
- L107 _public prototype_ `bool IsRecording() const;`
- L108 _public prototype_ `const TSharedPtr<FJsonObject>& GetPlatformState() const;`
- L112 _private member_ `bool bIsRecording;`
- L113 _private member_ `TSharedPtr<FJsonObject> PlatformState;`

#### class `FStartRecordingTakeResponse`  
`class UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module") FStartRecordingTakeResponse final : public FControlResponse`  
_L116-121_
- inherits: `FControlResponse`
- L120 _public prototype_ `FStartRecordingTakeResponse();`

#### class `FStopRecordingTakeResponse`  
`class UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module") FStopRecordingTakeResponse final : public FControlResponse`  
_L123-135_
- inherits: `FControlResponse`
- L127 _public prototype_ `FStopRecordingTakeResponse();`
- L129 _public prototype_ `virtual TProtocolResult<void> Parse(TSharedPtr<FJsonObject> InBody) override;`
- L131 _public prototype_ `const FString& GetTakeName() const;`
- L134 _private member_ `FString TakeName;`

#### class `FAbortRecordingTakeResponse`  
`class UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module") FAbortRecordingTakeResponse final : public FControlResponse`  
_L137-142_
- inherits: `FControlResponse`
- L141 _public prototype_ `FAbortRecordingTakeResponse();`

#### class `FGetTakeListResponse`  
`class UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module") FGetTakeListResponse final : public FControlResponse`  
_L144-157_
- inherits: `FControlResponse`
- L148 _public prototype_ `FGetTakeListResponse();`
- L150 _public prototype_ `virtual TProtocolResult<void> Parse(TSharedPtr<FJsonObject> InBody) override;`
- L152 _public prototype_ `const TArray<FString>& GetNames() const;`
- L156 _private member_ `TArray<FString> Names;`

#### class `FGetTakeMetadataResponse`  
`class UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module") FGetTakeMetadataResponse final : public FControlResponse`  
_L159-214_
- inherits: `FControlResponse`
- L202 _public prototype_ `FGetTakeMetadataResponse();`
- L204 _public prototype_ `virtual TProtocolResult<void> Parse(TSharedPtr<FJsonObject> InBody) override;`
- L206 _public prototype_ `const TArray<FTakeObject>& GetTakes() const;`
- L210 _private prototype_ `TProtocolResult<void> CreateTakeObject(const TSharedPtr<FJsonObject>& InTakeObject, FTakeObject& OutTake) const;`
- L211 _private prototype_ `TProtocolResult<void> CreateFileObject(const TSharedPtr<FJsonObject>& InFileObject, FFileObject& OutFile) const;`
- L213 _private member_ `TArray<FTakeObject> Takes;`

#### struct `FGetTakeMetadataResponse::FFileObject`  
`struct FFileObject`  
_L163-167_
- L165 _public member_ `FString Name;`
- L166 _public member_ `uint64 Length;`

#### struct `FGetTakeMetadataResponse::FVideoObject`  
`struct FVideoObject`  
_L169-175_
- L171 _public member_ `uint64 Frames;`
- L172 _public member_ `uint16 FrameRate;`
- L173 _public member_ `uint32 Height;`
- L174 _public member_ `uint32 Width;`

#### struct `FGetTakeMetadataResponse::FAudioObject`  
`struct FAudioObject`  
_L177-182_
- L179 _public member_ `uint8 Channels;`
- L180 _public member_ `uint32 SampleRate;`
- L181 _public member_ `uint8 BitsPerChannel;`

#### struct `FGetTakeMetadataResponse::FTakeObject`  
`struct FTakeObject`  
_L184-200_
- L186 _public member_ `FString Name;`
- L187 _public member_ `FString Slate;`
- L188 _public member_ `uint16 TakeNumber;`
- L189 _public member_ `FString DateTime;`
- L190 _public member_ `FString AppVersion;`
- L191 _public member_ `FString Model;`
- L192 _public member_ `FString Subject;`
- L193 _public member_ `FString Scenario;`
- L194 _public member_ `TArray<FString> Tags;`
- L196 _public member_ `TArray<FFileObject> Files;`
- L198 _public member_ `FVideoObject Video;`
- L199 _public member_ `FAudioObject Audio;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API METAHUMANCAPTUREPROTOCOLSTACK_API`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureProtocolStack/Public/Control/Messages/ControlUpdate.h` (Public)


#### class `FControlUpdateCreator`  
`class FControlUpdateCreator final`  
_L14-18_
- L17 _public prototype_ `static TProtocolResult<TSharedRef<FControlUpdate>> Create(const FString& InAddressPath);`

#### class `FControlUpdate`  
`class UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")FControlUpdate`  
_L20-36_
- L24 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnUpdateMessage, TSharedPtr<FControlUpdate> InUpdateMessage);`
- L26 _public prototype_ `FControlUpdate(FString InAddressPath);`
- L27 _public prototype_ `virtual ~FControlUpdate() = default;`
- L29 _public prototype_ `const FString& GetAddressPath() const;`
- L31 _public prototype_ `virtual TProtocolResult<void> Parse(TSharedPtr<FJsonObject> InBody);`
- L35 _private member_ `FString AddressPath;`

#### class `FSessionStopped`  
`class UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")FSessionStopped final : public FControlUpdate`  
_L39-44_
- inherits: `FControlUpdate`
- L43 _public prototype_ `FSessionStopped();`

#### class `FRecordingStatusUpdate`  
`class UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")FRecordingStatusUpdate final : public FControlUpdate`  
_L46-59_
- inherits: `FControlUpdate`
- L50 _public prototype_ `FRecordingStatusUpdate();`
- L52 _public prototype_ `virtual TProtocolResult<void> Parse(TSharedPtr<FJsonObject> InBody) override;`
- L54 _public prototype_ `bool IsRecording() const;`
- L58 _private member_ `bool bIsRecording;`

#### class `FBaseTakeUpdate`  
`class UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")FBaseTakeUpdate : public FControlUpdate`  
_L61-74_
- inherits: `FControlUpdate`
- L67 _public prototype_ `virtual TProtocolResult<void> Parse(TSharedPtr<FJsonObject> InBody) override;`
- L69 _public prototype_ `const FString& GetTakeName() const;`
- L73 _private member_ `FString TakeName;`

#### class `FTakeAddedUpdate`  
`class UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module") FTakeAddedUpdate final : public FBaseTakeUpdate`  
_L76-81_
- inherits: `FBaseTakeUpdate`
- L80 _public prototype_ `FTakeAddedUpdate();`

#### class `FTakeRemovedUpdate`  
`class UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module") FTakeRemovedUpdate final : public FBaseTakeUpdate`  
_L83-88_
- inherits: `FBaseTakeUpdate`
- L87 _public prototype_ `FTakeRemovedUpdate();`

#### class `FTakeUpdatedUpdate`  
`class UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module") FTakeUpdatedUpdate final : public FBaseTakeUpdate`  
_L90-95_
- inherits: `FBaseTakeUpdate`
- L94 _public prototype_ `FTakeUpdatedUpdate();`

#### class `FDiskCapacityUpdate`  
`class UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module") FDiskCapacityUpdate final : public FControlUpdate`  
_L99-114_
- inherits: `FControlUpdate`
- L103 _public prototype_ `FDiskCapacityUpdate();`
- L105 _public prototype_ `virtual TProtocolResult<void> Parse(TSharedPtr<FJsonObject> InBody) override;`
- L107 _public prototype_ `uint64 GetTotal() const;`
- L108 _public prototype_ `uint64 GetRemaining() const;`
- L112 _private member_ `uint64 Total;`
- L113 _private member_ `uint64 Remaining;`

#### class `FBatteryPercentageUpdate`  
`class UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module") FBatteryPercentageUpdate final : public FControlUpdate`  
_L116-129_
- inherits: `FControlUpdate`
- L120 _public prototype_ `FBatteryPercentageUpdate();`
- L122 _public prototype_ `virtual TProtocolResult<void> Parse(TSharedPtr<FJsonObject> InBody) override;`
- L124 _public prototype_ `float GetLevel() const;`
- L128 _private member_ `float Level;`

#### class `FThermalStateUpdate`  
`class UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module") FThermalStateUpdate final : public FControlUpdate`  
_L131-156_
- inherits: `FControlUpdate`
- L145 _public prototype_ `FThermalStateUpdate();`
- L147 _public prototype_ `virtual TProtocolResult<void> Parse(TSharedPtr<FJsonObject> InBody) override;`
- L149 _public prototype_ `EState GetState() const;`
- L153 _private prototype_ `static EState ConvertState(const FString& InStateString);`
- L155 _private member_ `EState State;`

#### enum `FThermalStateUpdate::EState`  
`enum class EState`  
_L135-143_
- L137 _public enumerator_ `Nominal = 0`
- L138 _public enumerator_ `Fair`
- L139 _public enumerator_ `Serious`
- L140 _public enumerator_ `Critical`
- L142 _public enumerator_ `Invalid`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API METAHUMANCAPTUREPROTOCOLSTACK_API`
- L24 _delegate_ `DECLARE_DELEGATE_OneParam(FOnUpdateMessage, TSharedPtr<FControlUpdate> InUpdateMessage);`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureProtocolStack/Public/Discovery/Communication/DiscoveryCommunication.h` (Public)


#### class `FDiscoveryCommunication`  
`class FDiscoveryCommunication final`  
_L12-43_
- L16 _public member_ `static const uint16 MulticastPort;`
- L17 _public member_ `static const FString MulticastAddress;`
- L21 _public typedef_ `using FRunnerType = TQueueRunner<FDiscoveryPacket>;`
- L23 _public prototype_ `FDiscoveryCommunication();`
- L25 _public prototype_ `TProtocolResult<void> Start();`
- L26 _public prototype_ `TProtocolResult<void> Stop();`
- L28 _public prototype_ `void SendMessage(FDiscoveryPacket InMessage, const FString& Endpoint);`
- L29 _public prototype_ `void SendMessage(FDiscoveryPacket InMessage, const FString& EndpointIp, const uint16 EndpointPort);`
- L31 _public prototype_ `void SetReceiveHandler(FOnPacketReceived InReceiveHandler);`
- L35 _private prototype_ `void OnProcessReceivedPacket(FDiscoveryPacket InPacket);`
- L36 _private prototype_ `void OnPacketArrived(const FArrayReaderPtr& InPayload, const FIPv4Endpoint& InEndpoint);`
- L38 _private member_ `FUdpClient Client;`
- L40 _private member_ `FRunnerType SynchronizedReceiver;`
- L42 _private member_ `FOnPacketReceived OnPacketReceived;`

#### Free symbols / members of external scopes

- L19 _delegate_ `DECLARE_DELEGATE_OneParam(FOnPacketReceived, FDiscoveryPacket InPacket) using FRunnerType = TQueueRunner<FDiscoveryPacket>;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureProtocolStack/Public/Discovery/Communication/DiscoveryPacket.h` (Public)


#### class `FDiscoveryPacket`  
`class FDiscoveryPacket final`  
_L10-47_
- L23 _public member_ `static const TArray<uint8> Header;`
- L25 _public prototype_ `static TProtocolResult<FDiscoveryPacket> Deserialize(const TConstArrayView<uint8>& InData);`
- L26 _public prototype_ `static TProtocolResult<TArray<uint8>> Serialize(const FDiscoveryPacket& InPacket);`
- L28 _public prototype_ `FDiscoveryPacket() = default;`
- L29 _public prototype_ `FDiscoveryPacket(EMessageType InMessageType, TArray<uint8> InPayload);`
- L31 _public prototype_ `FDiscoveryPacket(const FDiscoveryPacket& InOther) = default;`
- L32 _public prototype_ `FDiscoveryPacket(FDiscoveryPacket&& InOther) = default;`
- L34 _public prototype_ `FDiscoveryPacket& operator=(const FDiscoveryPacket& InOther) = default;`
- L35 _public prototype_ `FDiscoveryPacket& operator=(FDiscoveryPacket&& InOther) = default;`
- L37 _public prototype_ `const EMessageType GetMessageType() const;`
- L38 _public prototype_ `const TArray<uint8>& GetPayload() const;`
- L42 _private prototype_ `static EMessageType ToMessageType(uint8 InMessageType);`
- L43 _private prototype_ `static uint8 FromMessageType(EMessageType InMessageType);`
- L45 _private member_ `EMessageType MessageType;`
- L46 _private member_ `TArray<uint8> Payload;`

#### enum `FDiscoveryPacket::EMessageType`  
`enum class EMessageType : uint8`  
_L14-21_
- L16 _public enumerator_ `Request = 0`
- L17 _public enumerator_ `Response = 1`
- L18 _public enumerator_ `Notify = 2`
- L20 _public enumerator_ `Invalid = 255`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureProtocolStack/Public/Discovery/DiscoveryMessenger.h` (Public)


#### class `FDiscoveryMessenger`  
`class UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")FDiscoveryMessenger final`  
_L16-46_
- L21 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnResponseArrived, FDiscoveryResponse InResponse);`
- L22 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnNotifyArrived, FDiscoveryNotify InResponse);`
- L25 _public prototype_ `FDiscoveryMessenger();`
- L26 _public prototype_ `~FDiscoveryMessenger();`
- L28 _public prototype_ `TProtocolResult<void> Start();`
- L29 _public prototype_ `TProtocolResult<void> Stop();`
- L31 _public prototype_ `TProtocolResult<void> SendMulticastRequest();`
- L33 _public prototype_ `void SetResponseHandler(FOnResponseArrived InOnResponse);`
- L34 _public prototype_ `void SetNotifyHandler(FOnNotifyArrived InOnNotify);`
- L38 _private prototype_ `void OnPacketArrived(FDiscoveryPacket InPacket);`
- L40 _private member_ `FDiscoveryCommunication Communication;`
- L43 _private member_ `FOnResponseArrived OnResponse;`
- L44 _private member_ `FOnNotifyArrived OnNotify;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API METAHUMANCAPTUREPROTOCOLSTACK_API`
- L21 _delegate_ `DECLARE_DELEGATE_OneParam(FOnResponseArrived, FDiscoveryResponse InResponse);`
- L22 _delegate_ `DECLARE_DELEGATE_OneParam(FOnNotifyArrived, FDiscoveryNotify InResponse);`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureProtocolStack/Public/Discovery/Messages/DiscoveryNotify.h` (Public)


#### class `FDiscoveryNotify`  
`class UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")FDiscoveryNotify`  
_L14-49_
- L18 _public member_ `static const uint32 MinPayloadSize;`
- L20 _public typedef_ `using FServerId = TStaticArray<uint8, 16>;`
- L30 _public prototype_ `FDiscoveryNotify(FServerId InServerId, uint16 InControlPort, EConnectionState InConnectionState, TArray<uint16> InSupportedVersions);`
- L32 _public prototype_ `static TProtocolResult<FDiscoveryNotify> Deserialize(const FDiscoveryPacket& InPacket);`
- L33 _public prototype_ `static TProtocolResult<FDiscoveryPacket> Serialize(const FDiscoveryNotify& InNotify);`
- L35 _public prototype_ `const FServerId& GetServerId() const;`
- L36 _public prototype_ `uint16 GetControlPort() const;`
- L37 _public prototype_ `EConnectionState GetConnectionState() const;`
- L38 _public prototype_ `const TArray<uint16>& GetSupportedVersions() const;`
- L42 _private prototype_ `static EConnectionState ToConnectionState(uint8 InConnectionState);`
- L43 _private prototype_ `static uint8 FromConnectionState(EConnectionState InConnectionState);`
- L45 _private member_ `FServerId ServerId;`
- L46 _private member_ `uint16 ControlPort;`
- L47 _private member_ `EConnectionState ConnectionState;`
- L48 _private member_ `TArray<uint16> SupportedVersions;`

#### enum `FDiscoveryNotify::EConnectionState`  
`enum class EConnectionState : uint8`  
_L22-28_
- L24 _public enumerator_ `Offline = 0`
- L25 _public enumerator_ `Online = 1`
- L27 _public enumerator_ `Invalid`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API METAHUMANCAPTUREPROTOCOLSTACK_API`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureProtocolStack/Public/Discovery/Messages/DiscoveryRequest.h` (Public)


#### class `FDiscoveryRequest`  
`class FDiscoveryRequest`  
_L12-22_
- L16 _public member_ `static const uint32 PayloadSize;`
- L18 _public prototype_ `FDiscoveryRequest() = default;`
- L20 _public prototype_ `static TProtocolResult<FDiscoveryRequest> Deserialize(const FDiscoveryPacket& InPacket);`
- L21 _public prototype_ `static TProtocolResult<FDiscoveryPacket> Serialize(const FDiscoveryRequest& InRequest);`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureProtocolStack/Public/Discovery/Messages/DiscoveryResponse.h` (Public)


#### class `FDiscoveryResponse`  
`class UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")FDiscoveryResponse`  
_L14-36_
- L18 _public member_ `static const uint32 MinPayloadSize;`
- L20 _public typedef_ `using FServerId = TStaticArray<uint8, 16>;`
- L22 _public prototype_ `FDiscoveryResponse(FServerId InServerId, uint16 InControlPort, TArray<uint16> InSupportedVersions);`
- L24 _public prototype_ `static TProtocolResult<FDiscoveryResponse> Deserialize(const FDiscoveryPacket& InPacket);`
- L25 _public prototype_ `static TProtocolResult<FDiscoveryPacket> Serialize(const FDiscoveryResponse& InResponse);`
- L27 _public prototype_ `const FServerId& GetServerId() const;`
- L28 _public prototype_ `uint16 GetControlPort() const;`
- L29 _public prototype_ `const TArray<uint16>& GetSupportedVersions() const;`
- L33 _private member_ `FServerId ServerId;`
- L34 _private member_ `uint16 ControlPort;`
- L35 _private member_ `TArray<uint16> SupportedVersions;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API METAHUMANCAPTUREPROTOCOLSTACK_API`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureProtocolStack/Public/ExportClient/Communication/ExportCommunication.h` (Public)


#### struct `FExportRequestPacket`  
`struct FExportRequestPacket`  
_L17-23_
- L19 _public prototype_ `static TProtocolResult<void> Serialize(const FExportRequestPacket& InRequestPacket, ITcpSocketWriter& InWriter);`
- L21 _public member_ `FExportHeader Header;`
- L22 _public member_ `FExportRequest Request;`

#### struct `FExportResponseHeader`  
`struct FExportResponseHeader`  
_L25-31_
- L27 _public prototype_ `static TProtocolResult<FExportResponseHeader> Deserialize(ITcpSocketReader& InReader);`
- L29 _public member_ `FExportHeader Header;`
- L30 _public member_ `FExportResponse Response;`

#### class `FExportCommunication`  
`class FExportCommunication final`  
_L33-53_
- L37 _public prototype_ `FExportCommunication();`
- L39 _public prototype_ `TProtocolResult<void> Init();`
- L40 _public prototype_ `TProtocolResult<void> Start(const FString& InServerIp, const uint16 InServerPort);`
- L41 _public prototype_ `TProtocolResult<void> Stop();`
- L43 _public prototype_ `bool IsRunning() const;`
- L45 _public prototype_ `TProtocolResult<void> SendRequest(FExportHeader InHeader, FExportRequest InRequest);`
- L46 _public prototype_ `TProtocolResult<FExportResponseHeader> ReceiveResponseHeader();`
- L47 _public prototype_ `TProtocolResult<TArray<uint8>> ReceiveResponseData(const uint64 InSize);`
- L48 _public prototype_ `TProtocolResult<TStaticArray<uint8, 16>> ReceiveFileHash();`
- L52 _private member_ `FTcpClient Client;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureProtocolStack/Public/ExportClient/Communication/ExportHeader.h` (Public)


#### class `FExportHeader`  
`class FExportHeader final`  
_L12-37_
- L16 _public member_ `static const TArray<uint8> Header;`
- L18 _public prototype_ `FExportHeader() = default;`
- L19 _public prototype_ `FExportHeader(uint16 InVersion, uint32 InTransactionId);`
- L21 _public prototype_ `FExportHeader(const FExportHeader& InOther) = default;`
- L22 _public prototype_ `FExportHeader(FExportHeader&& InOther) = default;`
- L24 _public prototype_ `FExportHeader& operator=(const FExportHeader& InOther) = default;`
- L25 _public prototype_ `FExportHeader& operator=(FExportHeader&& InOther) = default;`
- L27 _public prototype_ `static TProtocolResult<FExportHeader> Deserialize(ITcpSocketReader& InReader);`
- L28 _public prototype_ `static TProtocolResult<void> Serialize(const FExportHeader& InHeader, ITcpSocketWriter& InWriter);`
- L30 _public prototype_ `uint16 GetVersion() const;`
- L31 _public prototype_ `uint32 GetTransactionId() const;`
- L35 _private member_ `uint16 Version;`
- L36 _private member_ `uint32 TransactionId;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureProtocolStack/Public/ExportClient/ExportClient.h` (Public)


#### class `FExportTaskStopToken`  
`class UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")FExportTaskStopToken`  
_L12-24_
- L16 _public prototype_ `FExportTaskStopToken();`
- L18 _public prototype_ `void Cancel();`
- L19 _public prototype_ `bool IsCanceled();`
- L23 _private member_ `std::atomic_bool bCanceled;`

#### class `FExportClient`  
`class UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")FExportClient final : public FExportTaskExecutor`  
_L27-73_
- inherits: `FExportTaskExecutor`
- L32 _public typedef_ `using FTaskId = uint32;`
- L34 _public typedef_ `using FTakeFileArray = TArray<FTakeFile>;`
- L36 _public prototype_ `FExportClient(FString InServerIp, const uint16 InExportPort);`
- L37 _public prototype_ `~FExportClient();`
- L39 _public prototype_ `FTaskId ExportTakeFiles(FString InTakeName, FTakeFileArray InTakeFileArray, TUniquePtr<FBaseStream> InStream);`
- L40 _public prototype_ `FTaskId ExportFiles(TMap<FString, FTakeFileArray> InTakesFilesMap, TUniquePtr<FBaseStream> InStream);`
- L42 _public prototype_ `void AbortExport(const FTaskId InTaskId);`
- L43 _public prototype_ `void AbortAllExports();`
- L47 _private prototype_ `FTaskId StartExport(FExportTakeTask::FExportContexts InContexts, TUniquePtr<FBaseStream> InStream);`
- L49 _private prototype_ `virtual void OnTask(TUniquePtr<FExportTakeTask> InTask) override;`
- L50 _private prototype_ `bool OnExportTask(TUniquePtr<FExportTakeTask> InTask);`
- L52 _private prototype_ `TProtocolResult<TMap<uint32, TPair<FString, FTakeFile>>> SendRequests(FExportTakeTask::FExportContexts InContexts);`
- L53 _private prototype_ `TProtocolResult<void> ReceiveResponses(TMap<uint32, TPair<FString, FTakeFile>> InResponseMap, FBaseStream& InBaseStream);`
- L56 _private prototype_ `TProtocolResult<void> Start();`
- L57 _private prototype_ `TProtocolResult<void> Stop();`
- L59 _private member_ `FString ServerIp;`
- L60 _private member_ `uint16 ServerPort;`
- L61 _private member_ `TUniquePtr<FExportCommunication> Communication;`
- L63 _private member_ `FExportWorker ExportWorker;`
- L64 _private member_ `TUniquePtr<FRunnableThread> Thread;`
- L66 _private member_ `std::atomic<FTaskId> CurrentTaskId;`
- L68 _private member_ `uint32 TransactionIdCounter;`
- L71 _private member_ `TUniquePtr<FExportTaskStopToken> CurrentTaskStopToken;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API METAHUMANCAPTUREPROTOCOLSTACK_API`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureProtocolStack/Public/ExportClient/ExportWorker.h` (Public)


#### struct `FTakeFile`  
`struct FTakeFile`  
_L10-15_
- L12 _public member_ `FString FileName;`
- L13 _public member_ `uint64 Length;`
- L14 _public member_ `uint64 Offset;`

#### class `FExportTakeTask`  
`class FExportTakeTask`  
_L17-34_
- L27 _public typedef_ `using FExportContexts = TArray<FExportContext>;`
- L29 _public prototype_ `FExportTakeTask(FExportContexts InExportContexts, TUniquePtr<FBaseStream> InStream);`
- L32 _public member_ `FExportContexts ExportContexts;`
- L33 _public member_ `TUniquePtr<FBaseStream> Stream;`

#### struct `FExportTakeTask::FExportContext`  
`struct FExportContext`  
_L21-25_
- L23 _public member_ `FString TakeName;`
- L24 _public member_ `FTakeFile File;`

#### class `FExportTaskExecutor`  
`class FExportTaskExecutor`  
_L36-42_
- L39 _public prototype_ `virtual ~FExportTaskExecutor() = default;`
- L41 _public prototype_ `virtual void OnTask(TUniquePtr<FExportTakeTask> InTask) = 0;`

#### class `FExportQueue`  
`class FExportQueue`  
_L44-66_
- L47 _public member_ `static const int32 MaxNumberOfElements = MAX_int32;`
- L49 _public prototype_ `FExportQueue();`
- L50 _public prototype_ `~FExportQueue() = default;`
- L52 _public prototype_ `TProtocolResult<void> Add(const uint32 InTaskId, TUniquePtr<FExportTakeTask> InElement);`
- L53 _public prototype_ `TUniquePtr<FExportTakeTask> Pop();`
- L55 _public prototype_ `TProtocolResult<TUniquePtr<FExportTakeTask>> Remove(uint32 InTaskId);`
- L57 _public prototype_ `bool IsEmpty() const;`
- L59 _public prototype_ `TArray<TUniquePtr<FExportTakeTask>> GetAndEmpty();`
- L63 _private member_ `mutable FCriticalSection Mutex;`
- L64 _private member_ `FSemaphore Semaphore;`
- L65 _private member_ `TArray<TPair<uint32, TUniquePtr<FExportTakeTask>>> Queue;`

#### class `FExportWorker`  
`class FExportWorker : public FRunnable`  
_L68-94_
- inherits: `FRunnable`
- L72 _public prototype_ `FExportWorker(FExportTaskExecutor& InClient);`
- L75 _public prototype_ `TProtocolResult<void> Add(const uint32 InTaskId, TUniquePtr<FExportTakeTask> InElement);`
- L76 _public prototype_ `TProtocolResult<TUniquePtr<FExportTakeTask>> Remove(uint32 InTaskId);`
- L78 _public prototype_ `bool IsEmpty() const;`
- L80 _public prototype_ `TArray<TUniquePtr<FExportTakeTask>> GetAndEmpty();`
- L84 _protected prototype_ `virtual uint32 Run() override;`
- L85 _protected prototype_ `virtual void Stop() override;`
- L89 _private member_ `std::atomic<bool> bRunning;`
- L91 _private member_ `FExportQueue Queue;`
- L93 _private member_ `FExportTaskExecutor& Client;`

#### class `FBaseStream`  
`class FBaseStream`  
_L96-108_
- L100 _public prototype_ `FBaseStream() = default;`
- L101 _public prototype_ `virtual ~FBaseStream() = default;`
- L103 _public prototype_ `virtual bool StartFile(const FString& InTakeName, const FString& InFileName) = 0;`
- L104 _public prototype_ `virtual bool ProcessData(const FString& InTakeName, const FString& InFileName, const TConstArrayView<uint8>& InData) = 0;`
- L105 _public prototype_ `virtual bool FinishFile(const FString& InTakeName, const FString& InFileName, const TStaticArray<uint8, 16>& InHash) = 0;`
- L107 _public prototype_ `virtual void Done(TProtocolResult<void> InResult) = 0;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureProtocolStack/Public/ExportClient/Messages/ExportRequest.h` (Public)


#### class `FExportRequest`  
`class FExportRequest final`  
_L7-32_
- L11 _public prototype_ `FExportRequest() = default;`
- L12 _public prototype_ `FExportRequest(FString InTakeName, FString InFileName, uint64 InOffset);`
- L14 _public prototype_ `FExportRequest(const FExportRequest& InOther) = default;`
- L15 _public prototype_ `FExportRequest(FExportRequest&& InOther) = default;`
- L17 _public prototype_ `FExportRequest& operator=(const FExportRequest& InOther) = default;`
- L18 _public prototype_ `FExportRequest& operator=(FExportRequest&& InOther) = default;`
- L20 _public prototype_ `static TProtocolResult<FExportRequest> Deserialize(ITcpSocketReader& InReader);`
- L21 _public prototype_ `static TProtocolResult<void> Serialize(const FExportRequest& InRequest, ITcpSocketWriter& InWriter);`
- L23 _public prototype_ `const FString& GetTakeName() const;`
- L24 _public prototype_ `const FString& GetFileName() const;`
- L25 _public prototype_ `uint64 GetOffset() const;`
- L29 _private member_ `FString TakeName;`
- L30 _private member_ `FString FileName;`
- L31 _private member_ `uint64 Offset;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureProtocolStack/Public/ExportClient/Messages/ExportResponse.h` (Public)


#### class `FExportResponse`  
`class FExportResponse final`  
_L7-49_
- L23 _public prototype_ `FExportResponse(EStatus InStatus, uint64 InLength);`
- L25 _public prototype_ `FExportResponse(const FExportResponse& InOther) = default;`
- L26 _public prototype_ `FExportResponse(FExportResponse&& InOther) = default;`
- L28 _public prototype_ `FExportResponse& operator=(const FExportResponse& InOther) = default;`
- L29 _public prototype_ `FExportResponse& operator=(FExportResponse&& InOther) = default;`
- L31 _public prototype_ `static TProtocolResult<FExportResponse> Deserialize(ITcpSocketReader& InReader);`
- L32 _public prototype_ `static TProtocolResult<TStaticArray<uint8, 16>> DeserializeHash(ITcpSocketReader& InReader);`
- L34 _public prototype_ `static TProtocolResult<void> Serialize(const FExportResponse& InResponse, ITcpSocketWriter& InWriter);`
- L35 _public prototype_ `static TProtocolResult<void> SerializeHash(const TStaticArray<uint8, 16>& InHash, ITcpSocketWriter& InWriter);`
- L37 _public prototype_ `EStatus GetStatus() const;`
- L38 _public prototype_ `uint64 GetLength() const;`
- L42 _private prototype_ `FExportResponse() = default;`
- L44 _private prototype_ `static EStatus ToStatus(uint8 InStatus);`
- L45 _private prototype_ `static uint8 FromStatus(EStatus InStatus);`
- L47 _private member_ `EStatus Status;`
- L48 _private member_ `uint64 Length;`

#### enum `FExportResponse::EStatus`  
`enum class EStatus : uint8`  
_L11-21_
- L13 _public enumerator_ `Success = 0`
- L14 _public enumerator_ `InvalidTakeName = 1`
- L15 _public enumerator_ `InvalidFileName = 2`
- L16 _public enumerator_ `InvalidOffset = 3`
- L17 _public enumerator_ `ServerError = 4`
- L18 _public enumerator_ `UnsupportedProtocolVersion = 5`
- L20 _public enumerator_ `Reserved`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureProtocolStack/Public/Utility/Definitions.h` (Public)


#### Free symbols / members of external scopes

- L7 _macro_ `#define CPS_VERSION 1`
- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogCPSControlMessenger, Log, All);`
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogCPSControlMessenger, Log, All);`
- L10 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogCPSControlCommunication, Log, All);`
- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogCPSControlCommunication, Log, All);`
- L11 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogCPSDiscoveryMessenger, Log, All);`
- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogCPSDiscoveryMessenger, Log, All);`
- L12 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogCPSDiscoveryCommunication, Log, All);`
- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogCPSDiscoveryCommunication, Log, All);`
- L13 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogCPSExportHandler, Log, All);`
- L13 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogCPSExportHandler, Log, All);`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureProtocolStack/Public/Utility/Error.h` (Public)


#### class `FCaptureProtocolError`  
`class FCaptureProtocolError`  
_L13-31_
- L19 _public prototype_ `FCaptureProtocolError();` — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")` — We can't deprecate the type itself without encountering seemingly impossible to suppress warnings, so we deprecate the constructors to at least provide some degree of warning
- L22 _public prototype_ `FCaptureProtocolError(FString InMessage, int32 InCode = 0);` — `UE_DEPRECATED(5.7, "MetaHumanAnimator/MetaHumanCaptureProtocolStack is deprecated. This functionality is now available in the CaptureManagerCore/CaptureProtocolStack module")`
- L24 _public prototype_ `const FString& GetMessage() const;`
- L25 _public prototype_ `int32 GetCode() const;`
- L29 _private member_ `FString Message;`
- L30 _private member_ `int32 Code;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API METAHUMANCAPTUREPROTOCOLSTACK_API`
- L34 _typedef_ `template <typename ValueType> using TProtocolResult = TResult<ValueType, FCaptureProtocolError>;`
- L36 _macro_ `#define CPS_CHECK_VOID_RESULT(Function) \`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureProtocolStack/Public/Utility/QueueRunner.h` (Public)


#### class `TQueueRunner`  
`template<class T> class TQueueRunner : public FRunnable`  
_L14-90_
- inherits: `FRunnable`
- L18 _public function_ `DECLARE_DELEGATE_OneParam(FOnProcess, T InElem) TQueueRunner(FOnProcess InProcess) : bRunning(true) , OnProcess(MoveTemp(InProcess))`
- L30 _public function_ `~TQueueRunner()`
- L37 _public function_ `void Add(T InElement)`
- L49 _protected function_ `virtual uint32 Run() override`
- L74 _protected function_ `virtual void Stop() override`
- L83 _private member_ `std::atomic<bool> bRunning;`
- L84 _private member_ `FOnProcess OnProcess;`
- L86 _private member_ `FCriticalSection Mutex;`
- L87 _private member_ `FEvent* Event;`
- L88 _private member_ `TQueue<T> Queue;`
- L89 _private member_ `TUniquePtr<FRunnableThread> Thread;`

#### Free symbols / members of external scopes

- L18 _delegate_ `DECLARE_DELEGATE_OneParam(FOnProcess, T InElem) TQueueRunner(FOnProcess InProcess) : bRunning(true) , OnProcess(MoveTemp(InProcess)) { Event = FGenericPlatformProcess::GetSynchEventFromPool(false); check(Event); Thread.Reset(FRunnableThread::Create(this, TEXT("Queue Runner"), 128 * 1024, TPri_Normal, FPlatformAffinity::GetPoolThreadMask())); } ~TQueueRunner() { Thread->Kill(true); FGenericPlatformProcess::ReturnSynchEventToPool(Event); } void Add(T InElement) { { FScopeLock lock(&Mutex); Queue.Enqueue(MoveTemp(InElement)); } Event->Trigger(); } protected: virtual uint32 Run() override { T Elem; while (bRunning.load()) { Event->Wait(); for (;;)`
