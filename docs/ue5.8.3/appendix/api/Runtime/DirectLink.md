# Runtime / DirectLink

- module root: `Source/Runtime/Datasmith/DirectLink`
- headers: 21; symbols: 562
- symbol kinds: class=28, enum=12, enumerator=85, function=64, macro=6, member=171, namespace=19, prototype=121, struct=46, typedef=5, variable=5
- PrivateDependencyModuleNames: MessagingCommon
- PublicDependencyModuleNames: Core, CoreUObject, Messaging

### `Source/Runtime/Datasmith/DirectLink/Private/DirectLinkMessages.h` (Private)


#### struct `FDirectLinkMsg_EndpointLifecycle`  
`struct FDirectLinkMsg_EndpointLifecycle`  
_L21-43_
- reflection: `USTRUCT(meta=(Experimental))`
- L33 _public function_ `FDirectLinkMsg_EndpointLifecycle(ELifecycle InLifecycleState = ELifecycle::None, uint32 InEndpointStateRevision = 0) : LifecycleState(InLifecycleState) , EndpointStateRevision(InEndpointStateRevision)`
- L39 _public member_ `uint8 LifecycleState = ELifecycle::None;` — `UPROPERTY()`
- L42 _public member_ `uint32 EndpointStateRevision = 0;` — `UPROPERTY()`

#### enum `FDirectLinkMsg_EndpointLifecycle::ELifecycle`  
`enum ELifecycle : uint8`  
_L25-31_
- L27 _public enumerator_ `None`
- L28 _public enumerator_ `Start`
- L29 _public enumerator_ `Heartbeat`
- L30 _public enumerator_ `Stop`

#### struct `FNamedId`  
`struct FNamedId`  
_L48-60_
- reflection: `USTRUCT(meta=(Experimental))`
- L53 _public member_ `FString Name;` — `UPROPERTY()`
- L56 _public member_ `FGuid Id;` — `UPROPERTY()`
- L59 _public member_ `bool bIsPublic = false;` — `UPROPERTY()`

#### struct `FDirectLinkMsg_EndpointState`  
`struct FDirectLinkMsg_EndpointState`  
_L63-107_
- reflection: `USTRUCT(meta=(Experimental))`
- L66 _public prototype_ `FDirectLinkMsg_EndpointState() = default;`
- L68 _public function_ `FDirectLinkMsg_EndpointState(uint32 StateRevision, uint32 MinProtocolVersion, uint32 MaxProtocolVersion) : StateRevision(StateRevision) , MinProtocolVersion(MinProtocolVersion) , ProtocolVersion(MaxProtocolVersion) , UEVersion(FEngineVersion::Current().ToString())`
- L76 _public member_ `uint32 StateRevision = 0;` — `UPROPERTY()`
- L79 _public member_ `uint32 MinProtocolVersion = 0;` — `UPROPERTY()`
- L82 _public member_ `uint32 ProtocolVersion = 0;` — `UPROPERTY()`
- L85 _public member_ `FString UEVersion;` — `UPROPERTY()`
- L88 _public member_ `FString ComputerName;` — `UPROPERTY()`
- L91 _public member_ `FString UserName;` — `UPROPERTY()`
- L94 _public member_ `uint32 ProcessId = 0;` — `UPROPERTY()`
- L97 _public member_ `FString ExecutableName;` — `UPROPERTY()`
- L100 _public member_ `FString NiceName;` — `UPROPERTY()`
- L103 _public member_ `TArray<FNamedId> Destinations;` — `UPROPERTY()`
- L106 _public member_ `TArray<FNamedId> Sources;` — `UPROPERTY()`

#### struct `FDirectLinkMsg_QueryEndpointState`  
`struct FDirectLinkMsg_QueryEndpointState`  
_L112-115_
- reflection: `USTRUCT(meta=(Experimental))`

#### struct `FDirectLinkMsg_OpenStreamRequest`  
`struct FDirectLinkMsg_OpenStreamRequest`  
_L120-136_
- reflection: `USTRUCT(meta=(Experimental))`
- L126 _public member_ `bool bRequestFromSource = false;` — `UPROPERTY()`
- L129 _public member_ `int32 RequestFromStreamPort = DirectLink::InvalidStreamPort;` — `UPROPERTY()`
- L132 _public member_ `FGuid SourceGuid;` — `UPROPERTY()`
- L135 _public member_ `FGuid DestinationGuid;` — `UPROPERTY()`

#### struct `FDirectLinkMsg_OpenStreamAnswer`  
`struct FDirectLinkMsg_OpenStreamAnswer`  
_L141-156_
- reflection: `USTRUCT(meta=(Experimental))`
- L146 _public member_ `int32 RecipientStreamPort = DirectLink::InvalidStreamPort;` — `UPROPERTY()`
- L149 _public member_ `bool bAccepted = false;` — `UPROPERTY()`
- L152 _public member_ `FString Error;` — `UPROPERTY()` — optionnal: may be filled when the request is denied
- L155 _public member_ `int32 OpenedStreamPort = DirectLink::InvalidStreamPort;` — `UPROPERTY()`

#### struct `FDirectLinkMsg_CloseStreamRequest`  
`struct FDirectLinkMsg_CloseStreamRequest`  
_L160-166_
- reflection: `USTRUCT(meta=(Experimental))`
- L165 _public member_ `int32 RecipientStreamPort = DirectLink::InvalidStreamPort;` — `UPROPERTY()`

#### struct `FDirectLinkMsg_DeltaMessage`  
`struct FDirectLinkMsg_DeltaMessage`  
_L171-213_
- reflection: `USTRUCT(meta=(Experimental))`
- L186 _public prototype_ `FDirectLinkMsg_DeltaMessage() = default;` — required for UStructs
- L188 _public function_ `FDirectLinkMsg_DeltaMessage(EKind Kind, DirectLink::FStreamPort DestinationStreamPort, uint32 BatchNumber, uint32 MessageIndex) : DestinationStreamPort(DestinationStreamPort) , BatchCode(BatchNumber) , MessageCode(MessageIndex) , Kind(Kind)`
- L197 _public member_ `int32 DestinationStreamPort = DirectLink::InvalidStreamPort;` — `UPROPERTY()`
- L200 _public member_ `int8 BatchCode = 0;` — `UPROPERTY()`
- L203 _public member_ `int32 MessageCode = 0;` — `UPROPERTY()`
- L206 _public member_ `uint8 Kind = EKind::None;` — `UPROPERTY()`
- L209 _public member_ `bool CompressedPayload = false;` — `UPROPERTY()`
- L212 _public member_ `TArray<uint8> Payload;` — `UPROPERTY()`

#### enum `FDirectLinkMsg_DeltaMessage::EKind`  
`enum EKind`  
_L175-183_
- L177 _public enumerator_ `None`
- L178 _public enumerator_ `SetupScene` — setup the stream for a scene id
- L179 _public enumerator_ `OpenDelta`
- L180 _public enumerator_ `SetElements`
- L181 _public enumerator_ `RemoveElements`
- L182 _public enumerator_ `CloseDelta`

#### struct `FDirectLinkMsg_HaveListMessage`  
`struct FDirectLinkMsg_HaveListMessage`  
_L217-261_
- reflection: `USTRUCT(meta=(Experimental))`
- L231 _public prototype_ `FDirectLinkMsg_HaveListMessage() = default;` — required for UStructs
- L233 _public function_ `FDirectLinkMsg_HaveListMessage(EKind Kind, DirectLink::FStreamPort SourceStreamPort, uint32 SyncCycle, uint32 MessageIndex) : SourceStreamPort(SourceStreamPort) , SyncCycle(SyncCycle) , MessageCode(MessageIndex) , Kind(Kind)`
- L242 _public member_ `int32 SourceStreamPort = 0;` — `UPROPERTY()` — FStreamPort
- L245 _public member_ `int32 SyncCycle = 0;` — `UPROPERTY()`
- L248 _public member_ `int32 MessageCode = 0;` — `UPROPERTY()`
- L251 _public member_ `uint8 Kind = 0;` — `UPROPERTY()`
- L254 _public member_ `TArray<uint8> Payload;` — `UPROPERTY()`
- L257 _public member_ `TArray<int32> NodeIds;` — `UPROPERTY()`
- L260 _public member_ `TArray<int32> Hashes;` — `UPROPERTY()`

#### enum `FDirectLinkMsg_HaveListMessage::EKind`  
`enum EKind : uint8`  
_L221-228_
- L223 _public enumerator_ `None`
- L224 _public enumerator_ `OpenHaveList` — see Payload
- L225 _public enumerator_ `HaveListElement` — see NodeIds and Hashes
- L226 _public enumerator_ `AckDeltaMessage` — #ue_directlink_cleanup
- L227 _public enumerator_ `CloseHaveList`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace DirectLink`

### `Source/Runtime/Datasmith/DirectLink/Private/DirectLinkScenePipe.h` (Private)


#### class `DirectLink::FPipeBase`  
`class FPipeBase`  
_L20-38_
- L23 _protected function_ `FPipeBase(TSharedPtr<FMessageEndpoint, ESPMode::ThreadSafe> ThisEndpoint, const FMessageAddress& RemoteAddress, FStreamPort RemoteStreamPort) : ThisEndpoint(ThisEndpoint) , RemoteAddress(RemoteAddress) , RemoteStreamPort(RemoteStreamPort)`
- L32 _protected prototype_ `template<typename MessageType> void SendInternal(MessageType* Message, int32 ByteSizeHint=0);`
- L35 _protected member_ `TSharedPtr<FMessageEndpoint, ESPMode::ThreadSafe> ThisEndpoint;` — connectivity
- L36 _protected member_ `FMessageAddress RemoteAddress;`
- L37 _protected member_ `FStreamPort RemoteStreamPort;`

#### class `DirectLink::FScenePipeToNetwork`  
`class FScenePipeToNetwork : public FPipeBase , public IDeltaConsumer`  
_L45-78_
- inherits: `FPipeBase,IDeltaConsumer`
- desc: Responsibility: delegate DeltaConsumer/DeltaProducer link over network, including message ordering and acknowledgments.
- L50 _public function_ `FScenePipeToNetwork(TSharedPtr<FMessageEndpoint, ESPMode::ThreadSafe> ThisEndpoint, const FMessageAddress& RemoteAddress, FStreamPort RemoteStreamPort) : FPipeBase(ThisEndpoint, RemoteAddress, RemoteStreamPort)`
- L58 _public function_ `virtual void SetDeltaProducer(IDeltaProducer* Producer) override`
- L59 _public prototype_ `virtual void SetupScene(FSetupSceneArg& SetupSceneArg) override;`
- L60 _public prototype_ `virtual void OpenDelta(FOpenDeltaArg& OpenDeltaArg) override;`
- L61 _public prototype_ `virtual void OnSetElement(FSetElementArg& SetElementArg) override;`
- L62 _public prototype_ `virtual void RemoveElements(FRemoveElementsArg& RemoveElementsArg) override;`
- L63 _public prototype_ `virtual void OnCloseDelta(FCloseDeltaArg& CloseDeltaArg) override;`
- L66 _public function_ `int32 GetSentDeltaMessageCount() const`
- L69 _private prototype_ `void Send(FDirectLinkMsg_DeltaMessage* Message);`
- L70 _private prototype_ `void InitSetElementBuffer();`
- L71 _private prototype_ `void SendSetElementBuffer();`
- L75 _private member_ `int8 BatchNumber = 0;` — message ordering
- L76 _private member_ `int32 NextMessageNumber;`
- L77 _private member_ `TArray<uint8> SetElementBuffer;`

#### class `DirectLink::FScenePipeFromNetwork`  
`class FScenePipeFromNetwork : public FPipeBase , public IDeltaProducer , public IStreamCommunicationInterface`  
_L81-126_
- inherits: `FPipeBase,IDeltaProducer,IStreamCommunicationInterface`
- L87 _public function_ `FScenePipeFromNetwork(TSharedPtr<FMessageEndpoint, ESPMode::ThreadSafe> Sender, const FMessageAddress& RemoteAddress, FStreamPort RemoteStreamPort, const TSharedRef<IDeltaConsumer> Consumer) : FPipeBase(Sender, RemoteAddress, RemoteStreamPort) , Consumer(Consumer)`
- L94 _public prototype_ `void HandleDeltaMessage(FDirectLinkMsg_DeltaMessage& Message);`
- L97 _public prototype_ `virtual void OnOpenHaveList(const FSceneIdentifier& HaveSceneId, bool bKeepPreviousContent, int32 SyncCycle) override;` — delta producer
- L98 _public prototype_ `virtual void OnHaveElement(FSceneGraphId NodeId, FElementHash HaveHash) override;`
- L99 _public prototype_ `void SendHaveElements();`
- L100 _public prototype_ `virtual void OnCloseHaveList() override;`
- L103 _public function_ `virtual FCommunicationStatus GetCommunicationStatus() const override`
- L107 _private prototype_ `void DelegateDeltaMessage(FDirectLinkMsg_DeltaMessage& Message);` — transmits messages to the actual delta consumer, reordered
- L108 _private prototype_ `void Send(FDirectLinkMsg_HaveListMessage* Message);`
- L112 _private member_ `int32 BatchNumber = 0;` — sent message ordering
- L113 _private member_ `int32 NextMessageNumber;`
- L114 _private member_ `FDirectLinkMsg_HaveListMessage* BufferedHaveListContent = nullptr;`
- L115 _private member_ `static constexpr int32 BufferSize = 100;`
- L118 _private member_ `TMap<int32, FDirectLinkMsg_DeltaMessage> MessageBuffer;` — received message ordering
- L119 _private member_ `int32 NextTransmitableMessageIndex = 0;`
- L120 _private member_ `int32 CurrentBatchCode = 0;`
- L122 _private member_ `TSharedPtr<IDeltaConsumer> Consumer;`
- L125 _private member_ `FCommunicationStatus CurrentCommunicationStatus;` — reporting

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace DirectLink`
- L129 _prototype_ `FArchive& operator << (FArchive& Ar, FSceneIdentifier& SceneId);` (scope `DirectLink`)
- L130 _prototype_ `FArchive& operator << (FArchive& Ar, IDeltaConsumer::FSetupSceneArg& SetupSceneArg);` (scope `DirectLink`)
- L131 _prototype_ `FArchive& operator << (FArchive& Ar, IDeltaConsumer::FOpenDeltaArg& OpenDeltaArg);` (scope `DirectLink`)
- L132 _prototype_ `FArchive& operator << (FArchive& Ar, IDeltaConsumer::FCloseDeltaArg& CloseDeltaArg);` (scope `DirectLink`)

### `Source/Runtime/Datasmith/DirectLink/Private/DirectLinkStreamCommunicationInterface.h` (Private)


#### class `DirectLink::IStreamCommunicationInterface`  
`class IStreamCommunicationInterface`  
_L11-17_
- L14 _public prototype_ `virtual ~IStreamCommunicationInterface() = default;`
- L15 _public prototype_ `virtual FCommunicationStatus GetCommunicationStatus() const = 0;`
- L16 _public function_ `virtual void Tick(double Now_s)`

#### class `DirectLink::IStreamReceiver`  
`class IStreamReceiver : public IStreamCommunicationInterface`  
_L21-27_
- inherits: `IStreamCommunicationInterface`
- L25 _public prototype_ `virtual ~IStreamReceiver() = default;`
- L26 _public prototype_ `virtual void HandleDeltaMessage(struct FDirectLinkMsg_DeltaMessage& Message) = 0;`

#### class `DirectLink::IStreamSender`  
`class IStreamSender : public IStreamCommunicationInterface`  
_L31-38_
- inherits: `IStreamCommunicationInterface`
- L35 _public prototype_ `virtual ~IStreamSender() = default;`
- L36 _public prototype_ `virtual void SetSceneSnapshot(TSharedPtr<class FSceneSnapshot> SceneSnapshot) = 0;`
- L37 _public prototype_ `virtual void HandleHaveListMessage(const struct FDirectLinkMsg_HaveListMessage& Message) = 0;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace DirectLink`

### `Source/Runtime/Datasmith/DirectLink/Private/DirectLinkStreamConnectionPoint.h` (Private)


#### class `DirectLink::FStreamConnectionPoint`  
`class FStreamConnectionPoint`  
_L12-29_
- L15 _public function_ `FStreamConnectionPoint(const FString& Name, EVisibility Visibility) : Name(Name) , Id(FGuid::NewGuid()) , Visibility(Visibility)`
- L20 _public function_ `const FString GetName() const`
- L21 _public function_ `const FGuid& GetId() const`
- L22 _public function_ `EVisibility GetVisibility() const`
- L23 _public function_ `bool IsPublic()`
- L26 _private member_ `FString Name;`
- L27 _private member_ `FGuid Id;`
- L28 _private member_ `EVisibility Visibility;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace DirectLink`

### `Source/Runtime/Datasmith/DirectLink/Private/DirectLinkStreamDescription.h` (Private)


#### struct `DirectLink::FStreamDescription`  
`struct FStreamDescription`  
_L15-28_
- L17 _public member_ `bool bThisIsSource = false;`
- L19 _public member_ `FGuid SourcePoint;`
- L20 _public member_ `FGuid DestinationPoint;`
- L21 _public member_ `FStreamPort LocalStreamPort = 0;` — works like an Id within that endpoint
- L22 _public member_ `FMessageAddress RemoteAddress;`
- L23 _public member_ `FStreamPort RemoteStreamPort = 0;`
- L24 _public member_ `EStreamConnectionState Status = EStreamConnectionState::Uninitialized;`
- L26 _public member_ `TUniquePtr<IStreamReceiver> Receiver;`
- L27 _public member_ `TSharedPtr<IStreamSender> Sender;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace DirectLink`

### `Source/Runtime/Datasmith/DirectLink/Private/DirectLinkStreamDestination.h` (Private)


#### class `DirectLink::FStreamDestination`  
`class FStreamDestination : public FStreamConnectionPoint`  
_L15-28_
- inherits: `FStreamConnectionPoint`
- L19 _public function_ `FStreamDestination(const FString& Name, EVisibility Visibility, const TSharedPtr<IConnectionRequestHandler>& Provider) : FStreamConnectionPoint(Name, Visibility) , Provider(Provider)`
- L24 _public function_ `const TSharedPtr<IConnectionRequestHandler>& GetProvider() const`
- L27 _private member_ `TSharedPtr<IConnectionRequestHandler> Provider;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace DirectLink`

### `Source/Runtime/Datasmith/DirectLink/Private/DirectLinkStreamReceiver.h` (Private)


#### class `DirectLink::FStreamReceiver`  
`class FStreamReceiver : public IStreamReceiver`  
_L19-35_
- inherits: `IStreamReceiver`
- L23 _public prototype_ `FStreamReceiver( TSharedPtr<FMessageEndpoint, ESPMode::ThreadSafe> ThisEndpoint, const FMessageAddress& DestinationAddress, FStreamPort ReceiverStreamPort, const TSharedRef<ISceneReceiver>& Consumer);`
- L29 _public prototype_ `virtual void HandleDeltaMessage(FDirectLinkMsg_DeltaMessage& Message) override;`
- L31 _public prototype_ `virtual FCommunicationStatus GetCommunicationStatus() const override;`
- L34 _private member_ `FScenePipeFromNetwork PipeFromNetwork;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace DirectLink`

### `Source/Runtime/Datasmith/DirectLink/Private/DirectLinkStreamSender.h` (Private)


#### class `DirectLink::FStreamSender`  
`class FStreamSender : public IStreamSender`  
_L27-65_
- inherits: `IStreamSender`
- desc: This is used to sync a Stream over MessageBus. See also: FStreamReceiver It keeps an Hash table of what the remote receiver already have, and diff with that. There is no handling of bad connection in this class. We accept arbitrary delays that can arise with remote slow operation (file load, breakpoint...). Some requests messages can be sent multiple times though, but with a unique 'SyncCycle' value so that the receiver is able to ignore duplicated requests.
- L30 _public prototype_ `FStreamSender(TSharedPtr<FMessageEndpoint, ESPMode::ThreadSafe> ThisEndpoint, const FMessageAddress& DestinationAddress, FStreamPort ReceiverStreamPort);`
- L31 _public prototype_ `~FStreamSender();`
- L32 _public prototype_ `virtual void SetSceneSnapshot(TSharedPtr<FSceneSnapshot> SceneSnapshot) override;`
- L33 _public prototype_ `virtual void Tick(double Now_s) override;`
- L34 _public prototype_ `virtual void HandleHaveListMessage(const FDirectLinkMsg_HaveListMessage& Message) override;` — update RemoteView
- L37 _public function_ `virtual FCommunicationStatus GetCommunicationStatus() const override`
- L50 _private member_ `EStep NextStep = EStep::Idle;`
- L51 _private member_ `int32 SyncCycle = 0;`
- L53 _private member_ `FScenePipeToNetwork PipeToNetwork;`
- L54 _private member_ `TUniquePtr<FHaveListReceiver> HaveListReceiver;`
- L55 _private member_ `double LastHaveListMessage_s = 0;`
- L57 _private member_ `TSharedPtr<FSceneSnapshot> Snapshot;`
- L58 _private member_ `FCriticalSection NextSnapshotLock;`
- L59 _private member_ `TSharedPtr<FSceneSnapshot> NextSnapshot;`
- L61 _private member_ `TUniquePtr<FRemoteSceneView> RemoteScene;`
- L64 _private member_ `FCommunicationStatus CurrentCommunicationStatus;` — Reporting

#### enum `DirectLink::FStreamSender::EStep`  
`enum class EStep`  
_L40-48_
- L42 _public enumerator_ `Idle`
- L43 _public enumerator_ `SetupScene`
- L44 _public enumerator_ `ReceiveHaveList`
- L45 _public enumerator_ `GenerateDelta`
- L46 _public enumerator_ `SendDelta`
- L47 _public enumerator_ `Synced`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace DirectLink`

### `Source/Runtime/Datasmith/DirectLink/Private/DirectLinkStreamSource.h` (Private)


#### class `DirectLink::FStreamSource`  
`class FStreamSource : public FStreamConnectionPoint`  
_L20-42_
- inherits: `FStreamConnectionPoint`
- desc: Define a content source. A source is linked to N Destinations through Streams, and uses Senders to write on them.
- L23 _public function_ `FStreamSource(const FString& Name, EVisibility Visibility) : FStreamConnectionPoint(Name, Visibility)`
- L28 _public prototype_ `void SetRoot(ISceneGraphNode* InRoot);` — Defines the content, which is a root node and its referenced tree.
- L31 _public prototype_ `void Snapshot();` — Snapshot the current state of the scene
- L34 _public prototype_ `void LinkSender(const TSharedPtr<IStreamSender>& Sender);` — Link a stream to this source (via a sender)
- L37 _private member_ `ISceneGraphNode* Root = nullptr;`
- L38 _private member_ `FRWLock SendersLock;`
- L39 _private member_ `TArray<TSharedPtr<IStreamSender>> Senders;`
- L40 _private member_ `FRWLock CurrentSnapshotLock;`
- L41 _private member_ `TSharedPtr<FSceneSnapshot> CurrentSnapshot;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace DirectLink`

### `Source/Runtime/Datasmith/DirectLink/Public/DirectLinkCommon.h` (Public)


#### struct `DirectLink::FSceneIdentifier`  
`struct FSceneIdentifier`  
_L32-46_
- desc: Guid and optional name, used to designate a scene across processes without ambiguity. The name is not necessary to identify a scene, but it offer a better UX
- L34 _public prototype_ `FSceneIdentifier() = default;`
- L36 _public function_ `FSceneIdentifier(const FGuid& Id, const FString& Name) : SceneGuid(Id) , DisplayName(Name)`
- L42 _public member_ `FGuid SceneGuid;` — Id of scene SharedState
- L45 _public member_ `FString DisplayName;` — Nice user-facing name. Do not expect it to be stable or consistent.

#### enum `DirectLink::EVisibility`  
`enum class EVisibility`  
_L58-62_
- desc: Used by data source and destination to describe how they are discovered by remote endpoints
- L60 _public enumerator_ `Public` — The connection point can accept connection requests from remote
- L61 _public enumerator_ `Private` — The connection point is not expected to be contacted from a remote

#### enum `DirectLink::EStreamConnectionState`  
`enum class EStreamConnectionState`  
_L64-70_
- L66 _public enumerator_ `Uninitialized`
- L67 _public enumerator_ `RequestSent`
- L68 _public enumerator_ `Active`
- L69 _public enumerator_ `Closed`

#### struct `DirectLink::FCommunicationStatus`  
`struct FCommunicationStatus`  
_L72-83_
- L74 _public function_ `bool IsTransmitting() const`
- L75 _public function_ `bool IsProgressKnown() const`
- L76 _public function_ `float GetProgress() const`
- L79 _public member_ `bool bIsSending = false;`
- L80 _public member_ `bool bIsReceiving = false;`
- L81 _public member_ `int32 TaskTotal = 0;`
- L82 _public member_ `int32 TaskCompleted = 0;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace DirectLink`
- L17 _typedef_ `using FSceneGraphId = uint32;` (scope `DirectLink`) — Node Id, aka Element Id. Represent a node within a scene. As a scene has a guid, the combination guid/id must be globally unique.
- L18 _variable_ `constexpr FSceneGraphId InvalidId = 0;` (scope `DirectLink`)
- L21 _typedef_ `using FElementHash = uint32;` (scope `DirectLink`)
- L22 _variable_ `constexpr FElementHash InvalidHash = 0;` (scope `DirectLink`)
- L25 _typedef_ `using FStreamPort = uint32;` (scope `DirectLink`)
- L26 _variable_ `constexpr FStreamPort InvalidStreamPort = 0;` (scope `DirectLink`)
- L50 _prototype_ `uint8 GetCurrentProtocolVersion();` (scope `DirectLink`) — DirectLink exchanges messages between pairs. Those versions numbers helps making sure pairs are compatible
- L53 _prototype_ `uint8 GetMinSupportedProtocolVersion();` (scope `DirectLink`) — oldest supported version

### `Source/Runtime/Datasmith/DirectLink/Public/DirectLinkConnectionRequestHandler.h` (Public)


#### class `DirectLink::IConnectionRequestHandler`  
`class IConnectionRequestHandler`  
_L19-41_
- desc: In DirectLink, Source points can request connections on Destinations points. For each destination, an instance of this class is used to accept/refuse incoming connections requests, and provide a SceneReceiver associated to each accepted Source. Each stream (pair Source-Destination) must have a distinct SceneReceiver.
- L28 _public prototype_ `virtual ~IConnectionRequestHandler() = default;`
- L34 _public prototype_ `virtual bool CanOpenNewConnection(const FSourceInformation& Source) = 0;` — @param Source    Information about the incoming Source @return          whether the source can be accepted as input of the Destination
- L40 _public prototype_ `virtual TSharedPtr<ISceneReceiver> GetSceneReceiver(const FSourceInformation& Source) = 0;` — @param Source    Information about the incoming Source @return          DeltaConsumer dedicated for this source that will receive Delta information from the source

#### struct `DirectLink::IConnectionRequestHandler::FSourceInformation`  
`struct FSourceInformation`  
_L22-25_
- L24 _public member_ `FGuid Id;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace DirectLink`

### `Source/Runtime/Datasmith/DirectLink/Public/DirectLinkDeltaConsumer.h` (Public)


#### class `DirectLink::IDeltaProducer`  
`class IDeltaProducer`  
_L12-20_
- L15 _public prototype_ `virtual ~IDeltaProducer() = default;`
- L17 _public prototype_ `virtual void OnOpenHaveList(const FSceneIdentifier& HaveSceneId, bool bKeepPreviousContent, int32 SyncCycle) = 0;`
- L18 _public prototype_ `virtual void OnHaveElement(FSceneGraphId NodeId, FElementHash HaveHash) = 0;`
- L19 _public prototype_ `virtual void OnCloseHaveList() = 0;`

#### class `DirectLink::IDeltaConsumer`  
`class IDeltaConsumer`  
_L24-70_
- L27 _public prototype_ `virtual ~IDeltaConsumer() = default;`
- L29 _public prototype_ `virtual void SetDeltaProducer(IDeltaProducer* Producer) = 0;`
- L38 _public prototype_ `virtual void SetupScene(FSetupSceneArg& SetupSceneArg) = 0;`
- L47 _public prototype_ `virtual void OpenDelta(FOpenDeltaArg& OpenDeltaArg) = 0;`
- L55 _public prototype_ `virtual void OnSetElement(FSetElementArg& SetElementArg) = 0;`
- L62 _public prototype_ `virtual void RemoveElements(FRemoveElementsArg& RemoveElementsArg) = 0;`
- L69 _public prototype_ `virtual void OnCloseDelta(FCloseDeltaArg& CloseDeltaArg) = 0;`

#### struct `DirectLink::IDeltaConsumer::FSetupSceneArg`  
`struct FSetupSceneArg`  
_L32-37_
- desc: On SetupScene message, the receiver is expected to send it's HaveList
- L34 _public member_ `FSceneIdentifier SceneId;`
- L35 _public member_ `bool bExpectHaveList;`
- L36 _public member_ `int32 SyncCycle;`

#### struct `DirectLink::IDeltaConsumer::FOpenDeltaArg`  
`struct FOpenDeltaArg`  
_L42-46_
- desc: signal beginning of a delta
- L44 _public member_ `bool bBasedOnNewScene;` — start from a fresh scene. (expect only new content)
- L45 _public member_ `uint32 ElementCountHint = 0;`

#### struct `DirectLink::IDeltaConsumer::FSetElementArg`  
`struct FSetElementArg`  
_L50-54_
- L52 _public member_ `TSharedPtr<FElementSnapshot> Snapshot;`
- L53 _public member_ `int32 ElementIndexHint = -1;`

#### struct `DirectLink::IDeltaConsumer::FRemoveElementsArg`  
`struct FRemoveElementsArg`  
_L58-61_
- L60 _public member_ `TArray<FSceneGraphId> Elements;`

#### struct `DirectLink::IDeltaConsumer::FCloseDeltaArg`  
`struct FCloseDeltaArg`  
_L65-68_
- L67 _public member_ `bool bCancelled = false;` — if an error occured and the delta is unusable

#### class `DirectLink::ISceneReceiver`  
`class ISceneReceiver`  
_L74-79_
- L77 _public prototype_ `virtual ~ISceneReceiver() = default;`
- L78 _public function_ `virtual void FinalSnapshot(const class FSceneSnapshot& SceneSnapshot)`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace DirectLink`

### `Source/Runtime/Datasmith/DirectLink/Public/DirectLinkElementSnapshot.h` (Public)


#### enum `DirectLink::ESerializationStatus`  
`enum class ESerializationStatus`  
_L20-26_
- L22 _public enumerator_ `Ok`
- L23 _public enumerator_ `StreamError`
- L24 _public enumerator_ `VersionMinNotRespected`
- L25 _public enumerator_ `VersionMaxNotRespected`

#### struct `DirectLink::FReferenceSnapshot`  
`struct FReferenceSnapshot`  
_L29-41_
- L31 _public prototype_ `void Serialize(FArchive& Ar);`
- L32 _public prototype_ `FElementHash Hash() const;`
- L40 _public member_ `TArray<FReferenceGroup> Groups;`

#### struct `DirectLink::FReferenceSnapshot::FReferenceGroup`  
`struct FReferenceGroup`  
_L34-38_
- L36 _public member_ `FName Name;`
- L37 _public member_ `TArray<FSceneGraphId> ReferencedIds;`

#### class `DirectLink::FElementSnapshot`  
`class FElementSnapshot`  
_L45-76_
- L48 _public prototype_ `FElementSnapshot() = default;`
- L49 _public prototype_ `FElementSnapshot(const ISceneGraphNode& Node);`
- L53 _public prototype_ `ESerializationStatus Serialize(FArchive& Ar);`
- L55 _public prototype_ `FElementHash GetHash() const;`
- L56 _public prototype_ `FElementHash GetDataHash() const;` — #ue_directlink_sync: serialize hashs
- L57 _public prototype_ `FElementHash GetRefHash() const;`
- L59 _public prototype_ `void UpdateNodeReferences(IReferenceResolutionProvider& Resolver, ISceneGraphNode& Node) const;`
- L60 _public prototype_ `void UpdateNodeData(ISceneGraphNode& Node) const;`
- L62 _public function_ `FSceneGraphId GetNodeId() const`
- L65 _public function_ `template<typename T> bool GetValueAs(FName Name, T& Out) const`
- L71 _private member_ `FSceneGraphId NodeId;`
- L72 _private member_ `mutable FElementHash DataHash = InvalidHash;`
- L73 _private member_ `mutable FElementHash RefHash = InvalidHash;`
- L74 _private member_ `FParameterStoreSnapshot DataSnapshot;`
- L75 _private member_ `FReferenceSnapshot RefSnapshot;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API DIRECTLINK_API`
- L14 _namespace_ `namespace DirectLink`

### `Source/Runtime/Datasmith/DirectLink/Public/DirectLinkEndpoint.h` (Public)


#### enum `DirectLink::ECommunicationStatus`  
`enum class ECommunicationStatus`  
_L31-36_
- L32 _public enumerator_ `NoIssue = 0`
- L33 _public enumerator_ `ModuleNotLoaded_Messaging = 1<<0`
- L34 _public enumerator_ `ModuleNotLoaded_UdpMessaging = 1<<1`
- L35 _public enumerator_ `ModuleNotLoaded_Networking = 1<<2`

#### struct `DirectLink::FRawInfo`  
`struct FRawInfo`  
_L40-84_
- L80 _public member_ `FMessageAddress ThisEndpointAddress;`
- L81 _public member_ `TMap<FMessageAddress, FEndpointInfo> EndpointsInfo;`
- L82 _public member_ `TMap<FGuid, FDataPointInfo> DataPointsInfo;`
- L83 _public member_ `TArray<FStreamInfo> StreamsInfo;`

#### struct `DirectLink::FRawInfo::FDataPointId`  
`struct FDataPointId`  
_L42-47_
- L44 _public member_ `FString Name;`
- L45 _public member_ `FGuid Id;`
- L46 _public member_ `bool bIsPublic = false;`

#### struct `DirectLink::FRawInfo::FEndpointInfo`  
`struct FEndpointInfo`  
_L49-61_
- L51 _public prototype_ `FEndpointInfo() = default;`
- L52 _public member_ `FString Name;`
- L53 _public member_ `FEngineVersion Version;` — Unreal version. This field is empty when the client predates 4.27.0
- L54 _public member_ `TArray<FDataPointId> Destinations;`
- L55 _public member_ `TArray<FDataPointId> Sources;`
- L56 _public member_ `FString UserName;`
- L57 _public member_ `FString ExecutableName;`
- L58 _public member_ `FString ComputerName;`
- L59 _public member_ `bool bIsLocal = false;`
- L60 _public member_ `uint32 ProcessId = 0;`

#### struct `DirectLink::FRawInfo::FDataPointInfo`  
`struct FDataPointInfo`  
_L63-70_
- L65 _public member_ `FMessageAddress EndpointAddress;`
- L66 _public member_ `FString Name;`
- L67 _public member_ `bool bIsSource = false;` — as opposed to a destination
- L68 _public member_ `bool bIsOnThisEndpoint = false;`
- L69 _public member_ `bool bIsPublic = false;` — if public, can be displayed as candidate for connection

#### struct `DirectLink::FRawInfo::FStreamInfo`  
`struct FStreamInfo`  
_L72-79_
- L74 _public member_ `FStreamPort StreamId = InvalidStreamPort;`
- L75 _public member_ `FGuid Source;`
- L76 _public member_ `FGuid Destination;`
- L77 _public member_ `EStreamConnectionState ConnectionState;`
- L78 _public member_ `FCommunicationStatus CommunicationStatus;`

#### class `DirectLink::IEndpointObserver`  
`class IEndpointObserver`  
_L87-93_
- L90 _public prototype_ `virtual ~IEndpointObserver() = default;`
- L92 _public function_ `virtual void OnStateChanged(const FRawInfo& RawInfo)`

#### class `DirectLink::FEndpoint`  
`class FEndpoint : public FNoncopyable`  
_L129-237_
- inherits: `FNoncopyable`
- desc: FEndpoint class is the main interface for sending and receiving data with the DirectLink system. Instances of this class discover themselves (through MessageBus) and can see Sources and Destinations available on each others. This is automatic and works for multiple applications. With that system, one can expose data from an application and consume it from another. An endpoint can exposes N sources and N Destinations. That being said, a more classic setup is to have an 'exporter' process that only exposes sources, and some 'consumer' process that only have Destinations. As a convention, 'consumers' have the responsibility to handle the connections management. Exporters have the sole responsibility to exposes their data. Setup example: - Exporter process - Source "My First Source" - Source "My Second Source" - Consumer process - Destination "Viewport" The consumer process can handle the connections between Sources and Destinations with the OpenStream and CloseStream methods.
- L144 _public prototype_ `FEndpoint(const FString& InName);`
- L145 _public prototype_ `~FEndpoint();`
- L147 _public prototype_ `void SetVerbose(bool bVerbose=true);`
- L156 _public prototype_ `FSourceHandle AddSource(const FString& Name, EVisibility Visibility=EVisibility::Public);` — Add a Source to that endpoint. A source can hold content (a scene snapshot) and is able to stream that content to remote destinations. @param Name          User facing name for this source. @param Visibility    Whether that Source is visible to remote endpoints @return              A Handle required by other Source related methods
- L162 _public prototype_ `void RemoveSource(const FSourceHandle& Source);` — Closes all streams related to this Source and remove it from the endpoint. @param Source Handle of the source to remove
- L170 _public prototype_ `void SetSourceRoot(const FSourceHandle& Source, ISceneGraphNode* InRoot, bool bSnapshot);` — Set the root of the content that should be exposed from that source. @param Source        Handle of the source to setup @param InRoot        Root of the graph that should be exposed @param bSnapshot     Whether the graph should be snapshotted right away
- L176 _public prototype_ `void SnapshotSource(const FSourceHandle& Source);` — Use the Source root to discover the graph and snapshot the content in its current state. @param Source        Handle of the source to snapshot
- L187 _public prototype_ `FDestinationHandle AddDestination(const FString& Name, EVisibility Visibility, const TSharedPtr<class IConnectionRequestHandler>& ConnectionRequestHandler);` — Add a Destination on that endpoint @param Name          Name of that destination @param Visibility    Whether this destination should be visible to remote endpoints @param ConnectionRequestHandler Object that will handle connections requests from Sources @return              A handle to the new destination
- L194 _public prototype_ `void RemoveDestination(const FDestinationHandle& Destination);` — Disconnect all streams related to that destination and removes the Destination itself from that endpoint @param Destination   Handle of the destination to remove
- L202 _public prototype_ `FRawInfo GetRawInfoCopy() const;` — Get a snapshot of the current state of the DirectLink swarm. It includes discovered Endpoints, their sources and destinations, and the streams descriptions. @return              Description of the last state of swarm
- L208 _public prototype_ `void AddEndpointObserver(IEndpointObserver* Observer);` — Register an IEndpointObserver that will be notified periodically with the last state of the swarm. @param Observer      Object that should be notified
- L214 _public prototype_ `void RemoveEndpointObserver(IEndpointObserver* Observer);` — Removes a previously added observer @param Observer      Observer to remove
- L222 _public prototype_ `EOpenStreamResult OpenStream(const FSourceHandle& SourceId, const FDestinationHandle& DestinationId);` — Open a Stream between a Source and a Destination @param SourceId      Handle to the Source @param DestinationId Handle to the Destination @return              Whether the stream is correctly opened
- L229 _public prototype_ `void CloseStream(const FSourceHandle& SourceId, const FDestinationHandle& DestinationId);` — Close a previously opened stream @param SourceId      Handle to the Source @param DestinationId Handle to the Destination
- L232 _private member_ `TUniquePtr<class FSharedState> SharedStatePtr;`
- L233 _private member_ `class FSharedState& SharedState;`
- L235 _private member_ `TUniquePtr<class FInternalThreadState> InternalPtr;`
- L236 _private member_ `class FInternalThreadState& Internal;`

#### enum `DirectLink::FEndpoint::EOpenStreamResult`  
`enum class EOpenStreamResult`  
_L133-141_
- L135 _public enumerator_ `Opened`
- L136 _public enumerator_ `AlreadyOpened`
- L137 _public enumerator_ `SourceAndDestinationNotFound`
- L138 _public enumerator_ `RemoteEndpointNotFound`
- L139 _public enumerator_ `Unsuppported`
- L140 _public enumerator_ `CannotConnectToPrivate`

#### Free symbols / members of external scopes

- L22 _macro_ `#define UE_API DIRECTLINK_API`
- L26 _namespace_ `namespace DirectLink`
- L37 _prototype_ `ENUM_CLASS_FLAGS(ECommunicationStatus) ECommunicationStatus ValidateCommunicationStatus();` (scope `DirectLink`)
- L96 _typedef_ `using FSourceHandle = FGuid;` (scope `DirectLink`)
- L97 _typedef_ `using FDestinationHandle = FGuid;` (scope `DirectLink`)

### `Source/Runtime/Datasmith/DirectLink/Public/DirectLinkLog.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/Datasmith/DirectLink/Public/DirectLinkMisc.h` (Public)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace DirectLink`
- L16 _prototype_ `const FString& GetDumpPath();` (scope `DirectLink`)
- L18 _prototype_ `void DumpSceneSnapshot(FSceneSnapshot& SceneSnapshot, const FString& BaseFileName);` (scope `DirectLink`)

### `Source/Runtime/Datasmith/DirectLink/Public/DirectLinkModule.h` (Public)


#### class `FDirectLinkModule`  
`class FDirectLinkModule : public IModuleInterface`  
_L39-53_
- inherits: `IModuleInterface`
- desc: The DirectLink system enable multiple application to send and receive data over the network. This is a N to N system that can be used to broadcast or consume content. The main components of that systems: - Endpoint (DirectLink::FEndpoint class) Represent a node on the network, capable of discovering other nodes. It is the main interface for that systems. - Source Declared on an Endpoint, a Source is a Named handle that can hold content. - Destination Similar to a Source, it is a named handle declared on an endpoint, capable of receiving content. - Stream (aka. connection) A stream represents a connection between a Source and a Destination. When a stream is established, the content of the source is kept in sync on the Destination. - Snapshot DirectLink works with snapshots. When a Source is snapshotted, the content graph is discovered from the root, and each reached node is serialized. This snapshot is the content that will be streamed to connected destinations.
- L42 _public function_ `static inline FDirectLinkModule& Get()`
- L47 _public function_ `static inline bool IsAvailable()`
- L52 _public prototype_ `virtual void StartupModule() override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define DIRECTLINK_MODULE_NAME TEXT("DirectLink")`

### `Source/Runtime/Datasmith/DirectLink/Public/DirectLinkParameterStore.h` (Public)


#### class `DirectLink::TStoreKey`  
`template<typename T, typename S = T> class TStoreKey`  
_L27-49_
- desc: rename TReflected ?
- L30 _public function_ `TStoreKey(const T& InitialValue = {}) : NativeValue(InitialValue)`
- L34 _public function_ `const T& Get() const`
- L35 _public function_ `T& Get()`
- L36 _public function_ `operator const T&() const`
- L37 _public function_ `operator T&()`
- L39 _public function_ `T& operator=(const T& InValue)`
- L47 _private member_ `T NativeValue;`

#### class `DirectLink::FParameterStoreSnapshot`  
`class FParameterStoreSnapshot`  
_L56-103_
- desc: Diffable, and serializable to a buffer
- L59 _public prototype_ `void SerializeAll(FArchive& Ar);`
- L62 _public function_ `template<typename T> bool GetValueAs(int32 I, T& Out) const`
- L76 _public function_ `template<typename T> bool GetValueAs(FName Name, T& Out) const`
- L78 _public function_ `int32 GetParameterIndex(FName ParameterName) const`
- L85 _public prototype_ `void AddParam(FName Name, Reflect::ESerialMethod StorageMethod, void* StorageLocation);`
- L87 _public function_ `void ReserveParamCount(uint32 PropCount)`
- L92 _public prototype_ `FElementHash Hash() const;`
- L102 _private member_ `TArray<FParameterDetails> Parameters;`

#### struct `DirectLink::FParameterStoreSnapshot::FParameterDetails`  
`struct FParameterDetails`  
_L96-101_
- L98 _public member_ `FName Name;`
- L99 _public member_ `Reflect::ESerialMethod StorageMethod;`
- L100 _public member_ `TArray<uint8> Buffer;`

#### class `DirectLink::FParameterStore`  
`class FParameterStore`  
_L107-164_
- L110 _public prototype_ `FParameterStore();`
- L111 _public prototype_ `~FParameterStore();`
- L112 _public prototype_ `FParameterStore(const FParameterStore&);`
- L113 _public prototype_ `FParameterStore& operator=(const FParameterStore&);`
- L114 _public prototype_ `FParameterStore(FParameterStore&&);`
- L115 _public prototype_ `FParameterStore& operator=(FParameterStore&&);`
- L118 _public function_ `template<typename T, typename S> TStoreKey<T, S>& RegisterParameter(TStoreKey<T, S>& Key, FName Name)`
- L132 _public prototype_ `uint32 GetParameterCount() const;`
- L133 _public prototype_ `int32 GetParameterIndex(FName Name) const;`
- L134 _public prototype_ `bool HasParameterNamed(FName Name) const;`
- L135 _public prototype_ `FName GetParameterName(int32 Index) const;`
- L138 _public function_ `template<typename T> bool GetValueAs(FName ParameterName, T& Out) const`
- L152 _public prototype_ `FParameterStoreSnapshot Snapshot() const;`
- L154 _public prototype_ `void Update(const FParameterStoreSnapshot& NewValues);`
- L163 _private member_ `TArray<FParameterDetails> Parameters;`

#### struct `DirectLink::FParameterStore::FParameterDetails`  
`struct FParameterDetails`  
_L157-162_
- L159 _public member_ `FName Name;`
- L160 _public member_ `void* StorageLocation;`
- L161 _public member_ `Reflect::ESerialMethod StorageMethod;`

#### class `DirectLink::FSnapshotProxy`  
`class FSnapshotProxy`  
_L167-194_
- L170 _public function_ `FSnapshotProxy(FParameterStoreSnapshot& Storage, bool bIsSaving) : Storage(Storage) , bIsSaving(bIsSaving)`
- L175 _public function_ `bool IsSaving() const`
- L178 _public function_ `template<typename T> bool TagSerialize(FName SerialTag, T& Item)`
- L192 _private member_ `FParameterStoreSnapshot& Storage;`
- L193 _private member_ `const bool bIsSaving;`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API DIRECTLINK_API`
- L22 _namespace_ `namespace DirectLink`
- L80 _function_ `return Parameters.IndexOfByPredicate([&](const FParameterDetails& Parameter) { return Parameter.Name == ParameterName; });` (scope `DirectLink::FParameterStoreSnapshot::GetParameterIndex`)

### `Source/Runtime/Datasmith/DirectLink/Public/DirectLinkSceneGraphNode.h` (Public)


#### class `DirectLink::FSceneGraphSharedState`  
`class FSceneGraphSharedState`  
_L31-41_
- desc: Data shared by all element of a given scene. The scene is uniquely identified by this element. Within this scene, all elements ids are unique. To ensure this property, this shared state is responsible for the id attribution. Id 0 is considered invalid (see InvalidId).
- L34 _public function_ `FSceneGraphId MakeId()`
- L35 _public function_ `const FGuid& GetGuid() const`
- L36 _public function_ `const FSceneIdentifier& GetSceneId() const`
- L39 _protected member_ `FSceneGraphId LastElementId = InvalidId;`
- L40 _protected member_ `FSceneIdentifier SceneId{FGuid::NewGuid(), FString()};`

#### class `DirectLink::ISceneGraphNode`  
`class ISceneGraphNode`  
_L53-95_
- desc: Represents a scene part. #ue_directlink_doc: full doc pass - sharedState concept Notes: - replication of references via DirectLink::FReferenceSnapshot - replication of data by the Store (DirectLink::FParameterStore)
- L56 _public prototype_ `virtual ~ISceneGraphNode() = default;`
- L59 _public function_ `virtual TSharedPtr<FSceneGraphSharedState> MakeSharedState() const` — Related nodes share a common object
- L60 _public function_ `virtual TSharedPtr<FSceneGraphSharedState> GetSharedState() const`
- L61 _public prototype_ `void SetSharedState(TSharedPtr<FSceneGraphSharedState> NewSharedState);`
- L64 _public prototype_ `virtual const FParameterStore& GetStore() const = 0;` — data
- L65 _public prototype_ `virtual FParameterStore& GetStore() = 0;` — protected ?
- L67 _public function_ `virtual void CustomSerialize(class FSnapshotProxy& Ar)`
- L68 _public function_ `void CustomSerialize(class FSnapshotProxy& Ar) const`
- L72 _public function_ `FSceneGraphId GetNodeId() const` — References This Id is unique within a SceneGraph
- L74 _public function_ `void SetNodeId(FSceneGraphId Id)` — private: friend class ...  #ue_directlink_design -> only accessible from the scene that owns the dep graph
- L76 _public prototype_ `void RegisterReferenceProxy(class IReferenceProxy& View, FName Name);`
- L77 _public prototype_ `int32 GetReferenceProxyCount() const;`
- L78 _public prototype_ `class IReferenceProxy* GetReferenceProxy(int32 Index) const;`
- L79 _public prototype_ `FName GetReferenceProxyName(int32 Index) const;`
- L81 _public prototype_ `FSceneGraphId RegisterReference(ISceneGraphNode* Referenced);`
- L82 _public prototype_ `void UpdateRefs(class IReferenceResolutionProvider& Resolver, const FReferenceSnapshot& NewRefs);`
- L86 _private member_ `FSceneGraphId SceneGraphId = 0;`
- L87 _private member_ `TSharedPtr<FSceneGraphSharedState> SharedState;`
- L94 _private member_ `TArray<FNamedReferenceProxy> ReferenceProxies;`

#### struct `DirectLink::ISceneGraphNode::FNamedReferenceProxy`  
`struct FNamedReferenceProxy`  
_L89-93_
- L91 _public member_ `FName Name;`
- L92 _public member_ `IReferenceProxy* View;`

#### class `DirectLink::IReferenceResolutionProvider`  
`class IReferenceResolutionProvider`  
_L97-102_
- desc: #ue_directlink_design: improve: ClaimRef in the ds shared state
- L100 _public prototype_ `virtual ~IReferenceResolutionProvider() = default;`
- L101 _public function_ `virtual TSharedPtr<ISceneGraphNode> AsSharedPtr(FSceneGraphId NodeId)`

#### class `DirectLink::IReferenceProxy`  
`class IReferenceProxy`  
_L104-111_
- L107 _public prototype_ `virtual ~IReferenceProxy() = default;`
- L108 _public prototype_ `virtual int32 Num() const = 0;`
- L109 _public prototype_ `virtual ISceneGraphNode* GetNode(int32 Index) const = 0;`
- L110 _public prototype_ `virtual void SetNodes(IReferenceResolutionProvider& ResolutionProvider, const TArray<FSceneGraphId>& NodeIds) = 0;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API DIRECTLINK_API`
- L16 _namespace_ `namespace DirectLink`

### `Source/Runtime/Datasmith/DirectLink/Public/DirectLinkSceneSnapshot.h` (Public)


#### class `DirectLink::FSceneSnapshot`  
`class FSceneSnapshot`  
_L17-22_
- L20 _public member_ `TMap<FSceneGraphId, TSharedRef<FElementSnapshot>> Elements;`
- L21 _public member_ `FSceneIdentifier SceneId;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace DirectLink`
- L25 _prototype_ `TSet<ISceneGraphNode*> BuildIndexForScene(ISceneGraphNode* RootElement);` (scope `DirectLink`)
- L26 _prototype_ `TSharedPtr<FSceneSnapshot> SnapshotScene(ISceneGraphNode* RootElement);` (scope `DirectLink`)

### `Source/Runtime/Datasmith/DirectLink/Public/DirectLinkSerialMethods.h` (Public)


#### enum `Reflect::EStoreType`  
`enum EStoreType : uint8`  
_L18-30_
- desc: clang-format off
- L20 _public enumerator_ `_bool = 1`
- L21 _public enumerator_ `_i8`
- L21 _public enumerator_ `_i8`
- L21 _public enumerator_ `_i8`
- L21 _public enumerator_ `_i8`
- L22 _public enumerator_ `_u8`
- L22 _public enumerator_ `_u8`
- L22 _public enumerator_ `_u8`
- L22 _public enumerator_ `_u8`
- L23 _public enumerator_ `_f32`
- L23 _public enumerator_ `_f32`
- L24 _public enumerator_ `_str`
- L25 _public enumerator_ `_vector`
- L25 _public enumerator_ `_vector`
- L25 _public enumerator_ `_vector`
- L26 _public enumerator_ `_linearcolor`
- L27 _public enumerator_ `_md5hash`
- L28 _public enumerator_ `_transform`
- L29 _public enumerator_ `_storeTypeLast`

#### enum `Reflect::ESerialModifier`  
`enum ESerialModifier : uint8`  
_L32-37_
- L34 _public enumerator_ `_default = 0 << 5`
- L35 _public enumerator_ `_array = 1 << 5`
- L36 _public enumerator_ `_alt1 = 2 << 5`

#### enum `Reflect::ESerialMethod`  
`enum class ESerialMethod : uint8`  
_L43-68_
- L45 _public enumerator_ `None = 0`
- L46 _public enumerator_ `Bool_Default = _bool | _default`
- L47 _public enumerator_ `Uint8_Default = _u8 | _default`
- L48 _public enumerator_ `Int32_Default = _i32 | _default`
- L49 _public enumerator_ `Int32_Array = _i32 | _array`
- L50 _public enumerator_ `Uint32_Default = _u32 | _default`
- L51 _public enumerator_ `Uint64_Default = _u64 | _default`
- L52 _public enumerator_ `Uint32_Packed = _u32 | _alt1`
- L53 _public enumerator_ `String_Default = _str | _default`
- L54 _public enumerator_ `String_Array = _str | _array`
- L55 _public enumerator_ `Float_Default = _f32 | _default`
- L56 _public enumerator_ `Float_Array = _f32 | _array`
- L57 _public enumerator_ `Double_Default = _f64 | _default`
- L58 _public enumerator_ `Vector_f32 = _vector | _default` — FVector serialized as FVector3f
- L59 _public enumerator_ `Vector_f64 = _vector | _alt1` — FVector serialized as FVector3d (native since 5.0)
- L60 _public enumerator_ `Quat_f32 = _quat | _default` — FQuat serialized as FQuat4f
- L61 _public enumerator_ `Quat_f64 = _quat | _alt1` — FQuat serialized as FQuat4d (native since 5.0)
- L62 _public enumerator_ `LinearColor_Default= _linearcolor| _default`
- L63 _public enumerator_ `MD5Hash_Default = _md5hash | _default`
- L64 _public enumerator_ `Transform_Default = _transform | _default` — Added in 5.0, uses LWC.
- L65 _public enumerator_ `Transform_Array = _transform | _array` — Added in 5.0, uses LWC.
- L67 _public enumerator_ `_NotImplementedYet = 0xff`

#### struct `Reflect::TDefaultSerialMethod`  
`template<typename T> struct TDefaultSerialMethod`  
_L74-74_
- desc: This list maps which serialization method should be used for each Type reflected by directlink
- L74 _public member_ `template<typename T> struct TDefaultSerialMethod { constexpr static ESerialMethod Value = ESerialMethod::_NotImplementedYet; };` — This list maps which serialization method should be used for each Type reflected by directlink
- L78 _public member_ `template<> struct TDefaultSerialMethod<bool> { constexpr static ESerialMethod Value = ESerialMethod::Uint8_Default; };`
- L79 _public member_ `template<> struct TDefaultSerialMethod<uint8> { constexpr static ESerialMethod Value = ESerialMethod::Uint8_Default; };`
- L80 _public member_ `template<> struct TDefaultSerialMethod<int32> { constexpr static ESerialMethod Value = ESerialMethod::Int32_Default; };`
- L81 _public member_ `template<> struct TDefaultSerialMethod<uint32> { constexpr static ESerialMethod Value = ESerialMethod::Uint32_Default; };`
- L82 _public member_ `template<> struct TDefaultSerialMethod<uint64> { constexpr static ESerialMethod Value = ESerialMethod::Uint64_Default; };`
- L83 _public member_ `template<> struct TDefaultSerialMethod<FString> { constexpr static ESerialMethod Value = ESerialMethod::String_Default; };`
- L84 _public member_ `template<> struct TDefaultSerialMethod<float> { constexpr static ESerialMethod Value = ESerialMethod::Float_Default; };`
- L85 _public member_ `template<> struct TDefaultSerialMethod<double> { constexpr static ESerialMethod Value = ESerialMethod::Double_Default; };`
- L86 _public member_ `template<> struct TDefaultSerialMethod<TArray<int32>> { constexpr static ESerialMethod Value = ESerialMethod::Int32_Array; };`
- L87 _public member_ `template<> struct TDefaultSerialMethod<TArray<FString>> { constexpr static ESerialMethod Value = ESerialMethod::String_Array; };`
- L88 _public member_ `template<> struct TDefaultSerialMethod<TArray<float>> { constexpr static ESerialMethod Value = ESerialMethod::Float_Array; };`
- L89 _public member_ `template<> struct TDefaultSerialMethod<FLinearColor> { constexpr static ESerialMethod Value = ESerialMethod::LinearColor_Default;};`
- L90 _public member_ `template<> struct TDefaultSerialMethod<FMD5Hash> { constexpr static ESerialMethod Value = ESerialMethod::MD5Hash_Default; };`
- L91 _public member_ `template<> struct TDefaultSerialMethod<FTransform> { constexpr static ESerialMethod Value = ESerialMethod::Transform_Default; };`

#### struct `Reflect::TDefaultSerialMethod`  
`template<typename T> struct TDefaultSerialMethod`  
_L75-75_
- desc: This list maps which serialization method should be used for each Type reflected by directlink
- L74 _public member_ `template<typename T> struct TDefaultSerialMethod { constexpr static ESerialMethod Value = ESerialMethod::_NotImplementedYet; };` — This list maps which serialization method should be used for each Type reflected by directlink
- L78 _public member_ `template<> struct TDefaultSerialMethod<bool> { constexpr static ESerialMethod Value = ESerialMethod::Uint8_Default; };`
- L79 _public member_ `template<> struct TDefaultSerialMethod<uint8> { constexpr static ESerialMethod Value = ESerialMethod::Uint8_Default; };`
- L80 _public member_ `template<> struct TDefaultSerialMethod<int32> { constexpr static ESerialMethod Value = ESerialMethod::Int32_Default; };`
- L81 _public member_ `template<> struct TDefaultSerialMethod<uint32> { constexpr static ESerialMethod Value = ESerialMethod::Uint32_Default; };`
- L82 _public member_ `template<> struct TDefaultSerialMethod<uint64> { constexpr static ESerialMethod Value = ESerialMethod::Uint64_Default; };`
- L83 _public member_ `template<> struct TDefaultSerialMethod<FString> { constexpr static ESerialMethod Value = ESerialMethod::String_Default; };`
- L84 _public member_ `template<> struct TDefaultSerialMethod<float> { constexpr static ESerialMethod Value = ESerialMethod::Float_Default; };`
- L85 _public member_ `template<> struct TDefaultSerialMethod<double> { constexpr static ESerialMethod Value = ESerialMethod::Double_Default; };`
- L86 _public member_ `template<> struct TDefaultSerialMethod<TArray<int32>> { constexpr static ESerialMethod Value = ESerialMethod::Int32_Array; };`
- L87 _public member_ `template<> struct TDefaultSerialMethod<TArray<FString>> { constexpr static ESerialMethod Value = ESerialMethod::String_Array; };`
- L88 _public member_ `template<> struct TDefaultSerialMethod<TArray<float>> { constexpr static ESerialMethod Value = ESerialMethod::Float_Array; };`
- L89 _public member_ `template<> struct TDefaultSerialMethod<FLinearColor> { constexpr static ESerialMethod Value = ESerialMethod::LinearColor_Default;};`
- L90 _public member_ `template<> struct TDefaultSerialMethod<FMD5Hash> { constexpr static ESerialMethod Value = ESerialMethod::MD5Hash_Default; };`
- L91 _public member_ `template<> struct TDefaultSerialMethod<FTransform> { constexpr static ESerialMethod Value = ESerialMethod::Transform_Default; };`

#### struct `Reflect::TDefaultSerialMethod`  
`template<typename T> struct TDefaultSerialMethod`  
_L76-76_
- desc: This list maps which serialization method should be used for each Type reflected by directlink
- L74 _public member_ `template<typename T> struct TDefaultSerialMethod { constexpr static ESerialMethod Value = ESerialMethod::_NotImplementedYet; };` — This list maps which serialization method should be used for each Type reflected by directlink
- L78 _public member_ `template<> struct TDefaultSerialMethod<bool> { constexpr static ESerialMethod Value = ESerialMethod::Uint8_Default; };`
- L79 _public member_ `template<> struct TDefaultSerialMethod<uint8> { constexpr static ESerialMethod Value = ESerialMethod::Uint8_Default; };`
- L80 _public member_ `template<> struct TDefaultSerialMethod<int32> { constexpr static ESerialMethod Value = ESerialMethod::Int32_Default; };`
- L81 _public member_ `template<> struct TDefaultSerialMethod<uint32> { constexpr static ESerialMethod Value = ESerialMethod::Uint32_Default; };`
- L82 _public member_ `template<> struct TDefaultSerialMethod<uint64> { constexpr static ESerialMethod Value = ESerialMethod::Uint64_Default; };`
- L83 _public member_ `template<> struct TDefaultSerialMethod<FString> { constexpr static ESerialMethod Value = ESerialMethod::String_Default; };`
- L84 _public member_ `template<> struct TDefaultSerialMethod<float> { constexpr static ESerialMethod Value = ESerialMethod::Float_Default; };`
- L85 _public member_ `template<> struct TDefaultSerialMethod<double> { constexpr static ESerialMethod Value = ESerialMethod::Double_Default; };`
- L86 _public member_ `template<> struct TDefaultSerialMethod<TArray<int32>> { constexpr static ESerialMethod Value = ESerialMethod::Int32_Array; };`
- L87 _public member_ `template<> struct TDefaultSerialMethod<TArray<FString>> { constexpr static ESerialMethod Value = ESerialMethod::String_Array; };`
- L88 _public member_ `template<> struct TDefaultSerialMethod<TArray<float>> { constexpr static ESerialMethod Value = ESerialMethod::Float_Array; };`
- L89 _public member_ `template<> struct TDefaultSerialMethod<FLinearColor> { constexpr static ESerialMethod Value = ESerialMethod::LinearColor_Default;};`
- L90 _public member_ `template<> struct TDefaultSerialMethod<FMD5Hash> { constexpr static ESerialMethod Value = ESerialMethod::MD5Hash_Default; };`
- L91 _public member_ `template<> struct TDefaultSerialMethod<FTransform> { constexpr static ESerialMethod Value = ESerialMethod::Transform_Default; };`

#### struct `Reflect::TDefaultSerialMethod`  
`template<typename T> struct TDefaultSerialMethod`  
_L77-77_
- desc: This list maps which serialization method should be used for each Type reflected by directlink
- L74 _public member_ `template<typename T> struct TDefaultSerialMethod { constexpr static ESerialMethod Value = ESerialMethod::_NotImplementedYet; };` — This list maps which serialization method should be used for each Type reflected by directlink
- L78 _public member_ `template<> struct TDefaultSerialMethod<bool> { constexpr static ESerialMethod Value = ESerialMethod::Uint8_Default; };`
- L79 _public member_ `template<> struct TDefaultSerialMethod<uint8> { constexpr static ESerialMethod Value = ESerialMethod::Uint8_Default; };`
- L80 _public member_ `template<> struct TDefaultSerialMethod<int32> { constexpr static ESerialMethod Value = ESerialMethod::Int32_Default; };`
- L81 _public member_ `template<> struct TDefaultSerialMethod<uint32> { constexpr static ESerialMethod Value = ESerialMethod::Uint32_Default; };`
- L82 _public member_ `template<> struct TDefaultSerialMethod<uint64> { constexpr static ESerialMethod Value = ESerialMethod::Uint64_Default; };`
- L83 _public member_ `template<> struct TDefaultSerialMethod<FString> { constexpr static ESerialMethod Value = ESerialMethod::String_Default; };`
- L84 _public member_ `template<> struct TDefaultSerialMethod<float> { constexpr static ESerialMethod Value = ESerialMethod::Float_Default; };`
- L85 _public member_ `template<> struct TDefaultSerialMethod<double> { constexpr static ESerialMethod Value = ESerialMethod::Double_Default; };`
- L86 _public member_ `template<> struct TDefaultSerialMethod<TArray<int32>> { constexpr static ESerialMethod Value = ESerialMethod::Int32_Array; };`
- L87 _public member_ `template<> struct TDefaultSerialMethod<TArray<FString>> { constexpr static ESerialMethod Value = ESerialMethod::String_Array; };`
- L88 _public member_ `template<> struct TDefaultSerialMethod<TArray<float>> { constexpr static ESerialMethod Value = ESerialMethod::Float_Array; };`
- L89 _public member_ `template<> struct TDefaultSerialMethod<FLinearColor> { constexpr static ESerialMethod Value = ESerialMethod::LinearColor_Default;};`
- L90 _public member_ `template<> struct TDefaultSerialMethod<FMD5Hash> { constexpr static ESerialMethod Value = ESerialMethod::MD5Hash_Default; };`
- L91 _public member_ `template<> struct TDefaultSerialMethod<FTransform> { constexpr static ESerialMethod Value = ESerialMethod::Transform_Default; };`

#### struct `Reflect::TDefaultSerialMethod`  
`template<> struct TDefaultSerialMethod<bool>`  
_L78-78_
- L74 _public member_ `template<typename T> struct TDefaultSerialMethod { constexpr static ESerialMethod Value = ESerialMethod::_NotImplementedYet; };` — This list maps which serialization method should be used for each Type reflected by directlink
- L78 _public member_ `template<> struct TDefaultSerialMethod<bool> { constexpr static ESerialMethod Value = ESerialMethod::Uint8_Default; };`
- L79 _public member_ `template<> struct TDefaultSerialMethod<uint8> { constexpr static ESerialMethod Value = ESerialMethod::Uint8_Default; };`
- L80 _public member_ `template<> struct TDefaultSerialMethod<int32> { constexpr static ESerialMethod Value = ESerialMethod::Int32_Default; };`
- L81 _public member_ `template<> struct TDefaultSerialMethod<uint32> { constexpr static ESerialMethod Value = ESerialMethod::Uint32_Default; };`
- L82 _public member_ `template<> struct TDefaultSerialMethod<uint64> { constexpr static ESerialMethod Value = ESerialMethod::Uint64_Default; };`
- L83 _public member_ `template<> struct TDefaultSerialMethod<FString> { constexpr static ESerialMethod Value = ESerialMethod::String_Default; };`
- L84 _public member_ `template<> struct TDefaultSerialMethod<float> { constexpr static ESerialMethod Value = ESerialMethod::Float_Default; };`
- L85 _public member_ `template<> struct TDefaultSerialMethod<double> { constexpr static ESerialMethod Value = ESerialMethod::Double_Default; };`
- L86 _public member_ `template<> struct TDefaultSerialMethod<TArray<int32>> { constexpr static ESerialMethod Value = ESerialMethod::Int32_Array; };`
- L87 _public member_ `template<> struct TDefaultSerialMethod<TArray<FString>> { constexpr static ESerialMethod Value = ESerialMethod::String_Array; };`
- L88 _public member_ `template<> struct TDefaultSerialMethod<TArray<float>> { constexpr static ESerialMethod Value = ESerialMethod::Float_Array; };`
- L89 _public member_ `template<> struct TDefaultSerialMethod<FLinearColor> { constexpr static ESerialMethod Value = ESerialMethod::LinearColor_Default;};`
- L90 _public member_ `template<> struct TDefaultSerialMethod<FMD5Hash> { constexpr static ESerialMethod Value = ESerialMethod::MD5Hash_Default; };`
- L91 _public member_ `template<> struct TDefaultSerialMethod<FTransform> { constexpr static ESerialMethod Value = ESerialMethod::Transform_Default; };`

#### struct `Reflect::TDefaultSerialMethod`  
`template<> struct TDefaultSerialMethod<uint8>`  
_L79-79_
- L74 _public member_ `template<typename T> struct TDefaultSerialMethod { constexpr static ESerialMethod Value = ESerialMethod::_NotImplementedYet; };` — This list maps which serialization method should be used for each Type reflected by directlink
- L78 _public member_ `template<> struct TDefaultSerialMethod<bool> { constexpr static ESerialMethod Value = ESerialMethod::Uint8_Default; };`
- L79 _public member_ `template<> struct TDefaultSerialMethod<uint8> { constexpr static ESerialMethod Value = ESerialMethod::Uint8_Default; };`
- L80 _public member_ `template<> struct TDefaultSerialMethod<int32> { constexpr static ESerialMethod Value = ESerialMethod::Int32_Default; };`
- L81 _public member_ `template<> struct TDefaultSerialMethod<uint32> { constexpr static ESerialMethod Value = ESerialMethod::Uint32_Default; };`
- L82 _public member_ `template<> struct TDefaultSerialMethod<uint64> { constexpr static ESerialMethod Value = ESerialMethod::Uint64_Default; };`
- L83 _public member_ `template<> struct TDefaultSerialMethod<FString> { constexpr static ESerialMethod Value = ESerialMethod::String_Default; };`
- L84 _public member_ `template<> struct TDefaultSerialMethod<float> { constexpr static ESerialMethod Value = ESerialMethod::Float_Default; };`
- L85 _public member_ `template<> struct TDefaultSerialMethod<double> { constexpr static ESerialMethod Value = ESerialMethod::Double_Default; };`
- L86 _public member_ `template<> struct TDefaultSerialMethod<TArray<int32>> { constexpr static ESerialMethod Value = ESerialMethod::Int32_Array; };`
- L87 _public member_ `template<> struct TDefaultSerialMethod<TArray<FString>> { constexpr static ESerialMethod Value = ESerialMethod::String_Array; };`
- L88 _public member_ `template<> struct TDefaultSerialMethod<TArray<float>> { constexpr static ESerialMethod Value = ESerialMethod::Float_Array; };`
- L89 _public member_ `template<> struct TDefaultSerialMethod<FLinearColor> { constexpr static ESerialMethod Value = ESerialMethod::LinearColor_Default;};`
- L90 _public member_ `template<> struct TDefaultSerialMethod<FMD5Hash> { constexpr static ESerialMethod Value = ESerialMethod::MD5Hash_Default; };`
- L91 _public member_ `template<> struct TDefaultSerialMethod<FTransform> { constexpr static ESerialMethod Value = ESerialMethod::Transform_Default; };`

#### struct `Reflect::TDefaultSerialMethod`  
`template<> struct TDefaultSerialMethod<int32>`  
_L80-80_
- L74 _public member_ `template<typename T> struct TDefaultSerialMethod { constexpr static ESerialMethod Value = ESerialMethod::_NotImplementedYet; };` — This list maps which serialization method should be used for each Type reflected by directlink
- L78 _public member_ `template<> struct TDefaultSerialMethod<bool> { constexpr static ESerialMethod Value = ESerialMethod::Uint8_Default; };`
- L79 _public member_ `template<> struct TDefaultSerialMethod<uint8> { constexpr static ESerialMethod Value = ESerialMethod::Uint8_Default; };`
- L80 _public member_ `template<> struct TDefaultSerialMethod<int32> { constexpr static ESerialMethod Value = ESerialMethod::Int32_Default; };`
- L81 _public member_ `template<> struct TDefaultSerialMethod<uint32> { constexpr static ESerialMethod Value = ESerialMethod::Uint32_Default; };`
- L82 _public member_ `template<> struct TDefaultSerialMethod<uint64> { constexpr static ESerialMethod Value = ESerialMethod::Uint64_Default; };`
- L83 _public member_ `template<> struct TDefaultSerialMethod<FString> { constexpr static ESerialMethod Value = ESerialMethod::String_Default; };`
- L84 _public member_ `template<> struct TDefaultSerialMethod<float> { constexpr static ESerialMethod Value = ESerialMethod::Float_Default; };`
- L85 _public member_ `template<> struct TDefaultSerialMethod<double> { constexpr static ESerialMethod Value = ESerialMethod::Double_Default; };`
- L86 _public member_ `template<> struct TDefaultSerialMethod<TArray<int32>> { constexpr static ESerialMethod Value = ESerialMethod::Int32_Array; };`
- L87 _public member_ `template<> struct TDefaultSerialMethod<TArray<FString>> { constexpr static ESerialMethod Value = ESerialMethod::String_Array; };`
- L88 _public member_ `template<> struct TDefaultSerialMethod<TArray<float>> { constexpr static ESerialMethod Value = ESerialMethod::Float_Array; };`
- L89 _public member_ `template<> struct TDefaultSerialMethod<FLinearColor> { constexpr static ESerialMethod Value = ESerialMethod::LinearColor_Default;};`
- L90 _public member_ `template<> struct TDefaultSerialMethod<FMD5Hash> { constexpr static ESerialMethod Value = ESerialMethod::MD5Hash_Default; };`
- L91 _public member_ `template<> struct TDefaultSerialMethod<FTransform> { constexpr static ESerialMethod Value = ESerialMethod::Transform_Default; };`

#### struct `Reflect::TDefaultSerialMethod`  
`template<> struct TDefaultSerialMethod<uint32>`  
_L81-81_
- L74 _public member_ `template<typename T> struct TDefaultSerialMethod { constexpr static ESerialMethod Value = ESerialMethod::_NotImplementedYet; };` — This list maps which serialization method should be used for each Type reflected by directlink
- L78 _public member_ `template<> struct TDefaultSerialMethod<bool> { constexpr static ESerialMethod Value = ESerialMethod::Uint8_Default; };`
- L79 _public member_ `template<> struct TDefaultSerialMethod<uint8> { constexpr static ESerialMethod Value = ESerialMethod::Uint8_Default; };`
- L80 _public member_ `template<> struct TDefaultSerialMethod<int32> { constexpr static ESerialMethod Value = ESerialMethod::Int32_Default; };`
- L81 _public member_ `template<> struct TDefaultSerialMethod<uint32> { constexpr static ESerialMethod Value = ESerialMethod::Uint32_Default; };`
- L82 _public member_ `template<> struct TDefaultSerialMethod<uint64> { constexpr static ESerialMethod Value = ESerialMethod::Uint64_Default; };`
- L83 _public member_ `template<> struct TDefaultSerialMethod<FString> { constexpr static ESerialMethod Value = ESerialMethod::String_Default; };`
- L84 _public member_ `template<> struct TDefaultSerialMethod<float> { constexpr static ESerialMethod Value = ESerialMethod::Float_Default; };`
- L85 _public member_ `template<> struct TDefaultSerialMethod<double> { constexpr static ESerialMethod Value = ESerialMethod::Double_Default; };`
- L86 _public member_ `template<> struct TDefaultSerialMethod<TArray<int32>> { constexpr static ESerialMethod Value = ESerialMethod::Int32_Array; };`
- L87 _public member_ `template<> struct TDefaultSerialMethod<TArray<FString>> { constexpr static ESerialMethod Value = ESerialMethod::String_Array; };`
- L88 _public member_ `template<> struct TDefaultSerialMethod<TArray<float>> { constexpr static ESerialMethod Value = ESerialMethod::Float_Array; };`
- L89 _public member_ `template<> struct TDefaultSerialMethod<FLinearColor> { constexpr static ESerialMethod Value = ESerialMethod::LinearColor_Default;};`
- L90 _public member_ `template<> struct TDefaultSerialMethod<FMD5Hash> { constexpr static ESerialMethod Value = ESerialMethod::MD5Hash_Default; };`
- L91 _public member_ `template<> struct TDefaultSerialMethod<FTransform> { constexpr static ESerialMethod Value = ESerialMethod::Transform_Default; };`

#### struct `Reflect::TDefaultSerialMethod`  
`template<> struct TDefaultSerialMethod<uint64>`  
_L82-82_
- L74 _public member_ `template<typename T> struct TDefaultSerialMethod { constexpr static ESerialMethod Value = ESerialMethod::_NotImplementedYet; };` — This list maps which serialization method should be used for each Type reflected by directlink
- L78 _public member_ `template<> struct TDefaultSerialMethod<bool> { constexpr static ESerialMethod Value = ESerialMethod::Uint8_Default; };`
- L79 _public member_ `template<> struct TDefaultSerialMethod<uint8> { constexpr static ESerialMethod Value = ESerialMethod::Uint8_Default; };`
- L80 _public member_ `template<> struct TDefaultSerialMethod<int32> { constexpr static ESerialMethod Value = ESerialMethod::Int32_Default; };`
- L81 _public member_ `template<> struct TDefaultSerialMethod<uint32> { constexpr static ESerialMethod Value = ESerialMethod::Uint32_Default; };`
- L82 _public member_ `template<> struct TDefaultSerialMethod<uint64> { constexpr static ESerialMethod Value = ESerialMethod::Uint64_Default; };`
- L83 _public member_ `template<> struct TDefaultSerialMethod<FString> { constexpr static ESerialMethod Value = ESerialMethod::String_Default; };`
- L84 _public member_ `template<> struct TDefaultSerialMethod<float> { constexpr static ESerialMethod Value = ESerialMethod::Float_Default; };`
- L85 _public member_ `template<> struct TDefaultSerialMethod<double> { constexpr static ESerialMethod Value = ESerialMethod::Double_Default; };`
- L86 _public member_ `template<> struct TDefaultSerialMethod<TArray<int32>> { constexpr static ESerialMethod Value = ESerialMethod::Int32_Array; };`
- L87 _public member_ `template<> struct TDefaultSerialMethod<TArray<FString>> { constexpr static ESerialMethod Value = ESerialMethod::String_Array; };`
- L88 _public member_ `template<> struct TDefaultSerialMethod<TArray<float>> { constexpr static ESerialMethod Value = ESerialMethod::Float_Array; };`
- L89 _public member_ `template<> struct TDefaultSerialMethod<FLinearColor> { constexpr static ESerialMethod Value = ESerialMethod::LinearColor_Default;};`
- L90 _public member_ `template<> struct TDefaultSerialMethod<FMD5Hash> { constexpr static ESerialMethod Value = ESerialMethod::MD5Hash_Default; };`
- L91 _public member_ `template<> struct TDefaultSerialMethod<FTransform> { constexpr static ESerialMethod Value = ESerialMethod::Transform_Default; };`

#### struct `Reflect::TDefaultSerialMethod`  
`template<> struct TDefaultSerialMethod<FString>`  
_L83-83_
- L74 _public member_ `template<typename T> struct TDefaultSerialMethod { constexpr static ESerialMethod Value = ESerialMethod::_NotImplementedYet; };` — This list maps which serialization method should be used for each Type reflected by directlink
- L78 _public member_ `template<> struct TDefaultSerialMethod<bool> { constexpr static ESerialMethod Value = ESerialMethod::Uint8_Default; };`
- L79 _public member_ `template<> struct TDefaultSerialMethod<uint8> { constexpr static ESerialMethod Value = ESerialMethod::Uint8_Default; };`
- L80 _public member_ `template<> struct TDefaultSerialMethod<int32> { constexpr static ESerialMethod Value = ESerialMethod::Int32_Default; };`
- L81 _public member_ `template<> struct TDefaultSerialMethod<uint32> { constexpr static ESerialMethod Value = ESerialMethod::Uint32_Default; };`
- L82 _public member_ `template<> struct TDefaultSerialMethod<uint64> { constexpr static ESerialMethod Value = ESerialMethod::Uint64_Default; };`
- L83 _public member_ `template<> struct TDefaultSerialMethod<FString> { constexpr static ESerialMethod Value = ESerialMethod::String_Default; };`
- L84 _public member_ `template<> struct TDefaultSerialMethod<float> { constexpr static ESerialMethod Value = ESerialMethod::Float_Default; };`
- L85 _public member_ `template<> struct TDefaultSerialMethod<double> { constexpr static ESerialMethod Value = ESerialMethod::Double_Default; };`
- L86 _public member_ `template<> struct TDefaultSerialMethod<TArray<int32>> { constexpr static ESerialMethod Value = ESerialMethod::Int32_Array; };`
- L87 _public member_ `template<> struct TDefaultSerialMethod<TArray<FString>> { constexpr static ESerialMethod Value = ESerialMethod::String_Array; };`
- L88 _public member_ `template<> struct TDefaultSerialMethod<TArray<float>> { constexpr static ESerialMethod Value = ESerialMethod::Float_Array; };`
- L89 _public member_ `template<> struct TDefaultSerialMethod<FLinearColor> { constexpr static ESerialMethod Value = ESerialMethod::LinearColor_Default;};`
- L90 _public member_ `template<> struct TDefaultSerialMethod<FMD5Hash> { constexpr static ESerialMethod Value = ESerialMethod::MD5Hash_Default; };`
- L91 _public member_ `template<> struct TDefaultSerialMethod<FTransform> { constexpr static ESerialMethod Value = ESerialMethod::Transform_Default; };`

#### struct `Reflect::TDefaultSerialMethod`  
`template<> struct TDefaultSerialMethod<float>`  
_L84-84_
- L74 _public member_ `template<typename T> struct TDefaultSerialMethod { constexpr static ESerialMethod Value = ESerialMethod::_NotImplementedYet; };` — This list maps which serialization method should be used for each Type reflected by directlink
- L78 _public member_ `template<> struct TDefaultSerialMethod<bool> { constexpr static ESerialMethod Value = ESerialMethod::Uint8_Default; };`
- L79 _public member_ `template<> struct TDefaultSerialMethod<uint8> { constexpr static ESerialMethod Value = ESerialMethod::Uint8_Default; };`
- L80 _public member_ `template<> struct TDefaultSerialMethod<int32> { constexpr static ESerialMethod Value = ESerialMethod::Int32_Default; };`
- L81 _public member_ `template<> struct TDefaultSerialMethod<uint32> { constexpr static ESerialMethod Value = ESerialMethod::Uint32_Default; };`
- L82 _public member_ `template<> struct TDefaultSerialMethod<uint64> { constexpr static ESerialMethod Value = ESerialMethod::Uint64_Default; };`
- L83 _public member_ `template<> struct TDefaultSerialMethod<FString> { constexpr static ESerialMethod Value = ESerialMethod::String_Default; };`
- L84 _public member_ `template<> struct TDefaultSerialMethod<float> { constexpr static ESerialMethod Value = ESerialMethod::Float_Default; };`
- L85 _public member_ `template<> struct TDefaultSerialMethod<double> { constexpr static ESerialMethod Value = ESerialMethod::Double_Default; };`
- L86 _public member_ `template<> struct TDefaultSerialMethod<TArray<int32>> { constexpr static ESerialMethod Value = ESerialMethod::Int32_Array; };`
- L87 _public member_ `template<> struct TDefaultSerialMethod<TArray<FString>> { constexpr static ESerialMethod Value = ESerialMethod::String_Array; };`
- L88 _public member_ `template<> struct TDefaultSerialMethod<TArray<float>> { constexpr static ESerialMethod Value = ESerialMethod::Float_Array; };`
- L89 _public member_ `template<> struct TDefaultSerialMethod<FLinearColor> { constexpr static ESerialMethod Value = ESerialMethod::LinearColor_Default;};`
- L90 _public member_ `template<> struct TDefaultSerialMethod<FMD5Hash> { constexpr static ESerialMethod Value = ESerialMethod::MD5Hash_Default; };`
- L91 _public member_ `template<> struct TDefaultSerialMethod<FTransform> { constexpr static ESerialMethod Value = ESerialMethod::Transform_Default; };`

#### struct `Reflect::TDefaultSerialMethod`  
`template<> struct TDefaultSerialMethod<double>`  
_L85-85_
- L74 _public member_ `template<typename T> struct TDefaultSerialMethod { constexpr static ESerialMethod Value = ESerialMethod::_NotImplementedYet; };` — This list maps which serialization method should be used for each Type reflected by directlink
- L78 _public member_ `template<> struct TDefaultSerialMethod<bool> { constexpr static ESerialMethod Value = ESerialMethod::Uint8_Default; };`
- L79 _public member_ `template<> struct TDefaultSerialMethod<uint8> { constexpr static ESerialMethod Value = ESerialMethod::Uint8_Default; };`
- L80 _public member_ `template<> struct TDefaultSerialMethod<int32> { constexpr static ESerialMethod Value = ESerialMethod::Int32_Default; };`
- L81 _public member_ `template<> struct TDefaultSerialMethod<uint32> { constexpr static ESerialMethod Value = ESerialMethod::Uint32_Default; };`
- L82 _public member_ `template<> struct TDefaultSerialMethod<uint64> { constexpr static ESerialMethod Value = ESerialMethod::Uint64_Default; };`
- L83 _public member_ `template<> struct TDefaultSerialMethod<FString> { constexpr static ESerialMethod Value = ESerialMethod::String_Default; };`
- L84 _public member_ `template<> struct TDefaultSerialMethod<float> { constexpr static ESerialMethod Value = ESerialMethod::Float_Default; };`
- L85 _public member_ `template<> struct TDefaultSerialMethod<double> { constexpr static ESerialMethod Value = ESerialMethod::Double_Default; };`
- L86 _public member_ `template<> struct TDefaultSerialMethod<TArray<int32>> { constexpr static ESerialMethod Value = ESerialMethod::Int32_Array; };`
- L87 _public member_ `template<> struct TDefaultSerialMethod<TArray<FString>> { constexpr static ESerialMethod Value = ESerialMethod::String_Array; };`
- L88 _public member_ `template<> struct TDefaultSerialMethod<TArray<float>> { constexpr static ESerialMethod Value = ESerialMethod::Float_Array; };`
- L89 _public member_ `template<> struct TDefaultSerialMethod<FLinearColor> { constexpr static ESerialMethod Value = ESerialMethod::LinearColor_Default;};`
- L90 _public member_ `template<> struct TDefaultSerialMethod<FMD5Hash> { constexpr static ESerialMethod Value = ESerialMethod::MD5Hash_Default; };`
- L91 _public member_ `template<> struct TDefaultSerialMethod<FTransform> { constexpr static ESerialMethod Value = ESerialMethod::Transform_Default; };`

#### struct `Reflect::TDefaultSerialMethod`  
`template<> struct TDefaultSerialMethod<TArray<int32>>`  
_L86-86_
- L74 _public member_ `template<typename T> struct TDefaultSerialMethod { constexpr static ESerialMethod Value = ESerialMethod::_NotImplementedYet; };` — This list maps which serialization method should be used for each Type reflected by directlink
- L78 _public member_ `template<> struct TDefaultSerialMethod<bool> { constexpr static ESerialMethod Value = ESerialMethod::Uint8_Default; };`
- L79 _public member_ `template<> struct TDefaultSerialMethod<uint8> { constexpr static ESerialMethod Value = ESerialMethod::Uint8_Default; };`
- L80 _public member_ `template<> struct TDefaultSerialMethod<int32> { constexpr static ESerialMethod Value = ESerialMethod::Int32_Default; };`
- L81 _public member_ `template<> struct TDefaultSerialMethod<uint32> { constexpr static ESerialMethod Value = ESerialMethod::Uint32_Default; };`
- L82 _public member_ `template<> struct TDefaultSerialMethod<uint64> { constexpr static ESerialMethod Value = ESerialMethod::Uint64_Default; };`
- L83 _public member_ `template<> struct TDefaultSerialMethod<FString> { constexpr static ESerialMethod Value = ESerialMethod::String_Default; };`
- L84 _public member_ `template<> struct TDefaultSerialMethod<float> { constexpr static ESerialMethod Value = ESerialMethod::Float_Default; };`
- L85 _public member_ `template<> struct TDefaultSerialMethod<double> { constexpr static ESerialMethod Value = ESerialMethod::Double_Default; };`
- L86 _public member_ `template<> struct TDefaultSerialMethod<TArray<int32>> { constexpr static ESerialMethod Value = ESerialMethod::Int32_Array; };`
- L87 _public member_ `template<> struct TDefaultSerialMethod<TArray<FString>> { constexpr static ESerialMethod Value = ESerialMethod::String_Array; };`
- L88 _public member_ `template<> struct TDefaultSerialMethod<TArray<float>> { constexpr static ESerialMethod Value = ESerialMethod::Float_Array; };`
- L89 _public member_ `template<> struct TDefaultSerialMethod<FLinearColor> { constexpr static ESerialMethod Value = ESerialMethod::LinearColor_Default;};`
- L90 _public member_ `template<> struct TDefaultSerialMethod<FMD5Hash> { constexpr static ESerialMethod Value = ESerialMethod::MD5Hash_Default; };`
- L91 _public member_ `template<> struct TDefaultSerialMethod<FTransform> { constexpr static ESerialMethod Value = ESerialMethod::Transform_Default; };`

#### struct `Reflect::TDefaultSerialMethod`  
`template<> struct TDefaultSerialMethod<TArray<FString>>`  
_L87-87_
- L74 _public member_ `template<typename T> struct TDefaultSerialMethod { constexpr static ESerialMethod Value = ESerialMethod::_NotImplementedYet; };` — This list maps which serialization method should be used for each Type reflected by directlink
- L78 _public member_ `template<> struct TDefaultSerialMethod<bool> { constexpr static ESerialMethod Value = ESerialMethod::Uint8_Default; };`
- L79 _public member_ `template<> struct TDefaultSerialMethod<uint8> { constexpr static ESerialMethod Value = ESerialMethod::Uint8_Default; };`
- L80 _public member_ `template<> struct TDefaultSerialMethod<int32> { constexpr static ESerialMethod Value = ESerialMethod::Int32_Default; };`
- L81 _public member_ `template<> struct TDefaultSerialMethod<uint32> { constexpr static ESerialMethod Value = ESerialMethod::Uint32_Default; };`
- L82 _public member_ `template<> struct TDefaultSerialMethod<uint64> { constexpr static ESerialMethod Value = ESerialMethod::Uint64_Default; };`
- L83 _public member_ `template<> struct TDefaultSerialMethod<FString> { constexpr static ESerialMethod Value = ESerialMethod::String_Default; };`
- L84 _public member_ `template<> struct TDefaultSerialMethod<float> { constexpr static ESerialMethod Value = ESerialMethod::Float_Default; };`
- L85 _public member_ `template<> struct TDefaultSerialMethod<double> { constexpr static ESerialMethod Value = ESerialMethod::Double_Default; };`
- L86 _public member_ `template<> struct TDefaultSerialMethod<TArray<int32>> { constexpr static ESerialMethod Value = ESerialMethod::Int32_Array; };`
- L87 _public member_ `template<> struct TDefaultSerialMethod<TArray<FString>> { constexpr static ESerialMethod Value = ESerialMethod::String_Array; };`
- L88 _public member_ `template<> struct TDefaultSerialMethod<TArray<float>> { constexpr static ESerialMethod Value = ESerialMethod::Float_Array; };`
- L89 _public member_ `template<> struct TDefaultSerialMethod<FLinearColor> { constexpr static ESerialMethod Value = ESerialMethod::LinearColor_Default;};`
- L90 _public member_ `template<> struct TDefaultSerialMethod<FMD5Hash> { constexpr static ESerialMethod Value = ESerialMethod::MD5Hash_Default; };`
- L91 _public member_ `template<> struct TDefaultSerialMethod<FTransform> { constexpr static ESerialMethod Value = ESerialMethod::Transform_Default; };`

#### struct `Reflect::TDefaultSerialMethod`  
`template<> struct TDefaultSerialMethod<TArray<float>>`  
_L88-88_
- L74 _public member_ `template<typename T> struct TDefaultSerialMethod { constexpr static ESerialMethod Value = ESerialMethod::_NotImplementedYet; };` — This list maps which serialization method should be used for each Type reflected by directlink
- L78 _public member_ `template<> struct TDefaultSerialMethod<bool> { constexpr static ESerialMethod Value = ESerialMethod::Uint8_Default; };`
- L79 _public member_ `template<> struct TDefaultSerialMethod<uint8> { constexpr static ESerialMethod Value = ESerialMethod::Uint8_Default; };`
- L80 _public member_ `template<> struct TDefaultSerialMethod<int32> { constexpr static ESerialMethod Value = ESerialMethod::Int32_Default; };`
- L81 _public member_ `template<> struct TDefaultSerialMethod<uint32> { constexpr static ESerialMethod Value = ESerialMethod::Uint32_Default; };`
- L82 _public member_ `template<> struct TDefaultSerialMethod<uint64> { constexpr static ESerialMethod Value = ESerialMethod::Uint64_Default; };`
- L83 _public member_ `template<> struct TDefaultSerialMethod<FString> { constexpr static ESerialMethod Value = ESerialMethod::String_Default; };`
- L84 _public member_ `template<> struct TDefaultSerialMethod<float> { constexpr static ESerialMethod Value = ESerialMethod::Float_Default; };`
- L85 _public member_ `template<> struct TDefaultSerialMethod<double> { constexpr static ESerialMethod Value = ESerialMethod::Double_Default; };`
- L86 _public member_ `template<> struct TDefaultSerialMethod<TArray<int32>> { constexpr static ESerialMethod Value = ESerialMethod::Int32_Array; };`
- L87 _public member_ `template<> struct TDefaultSerialMethod<TArray<FString>> { constexpr static ESerialMethod Value = ESerialMethod::String_Array; };`
- L88 _public member_ `template<> struct TDefaultSerialMethod<TArray<float>> { constexpr static ESerialMethod Value = ESerialMethod::Float_Array; };`
- L89 _public member_ `template<> struct TDefaultSerialMethod<FLinearColor> { constexpr static ESerialMethod Value = ESerialMethod::LinearColor_Default;};`
- L90 _public member_ `template<> struct TDefaultSerialMethod<FMD5Hash> { constexpr static ESerialMethod Value = ESerialMethod::MD5Hash_Default; };`
- L91 _public member_ `template<> struct TDefaultSerialMethod<FTransform> { constexpr static ESerialMethod Value = ESerialMethod::Transform_Default; };`

#### struct `Reflect::TDefaultSerialMethod`  
`template<> struct TDefaultSerialMethod<FLinearColor>`  
_L89-89_
- L74 _public member_ `template<typename T> struct TDefaultSerialMethod { constexpr static ESerialMethod Value = ESerialMethod::_NotImplementedYet; };` — This list maps which serialization method should be used for each Type reflected by directlink
- L78 _public member_ `template<> struct TDefaultSerialMethod<bool> { constexpr static ESerialMethod Value = ESerialMethod::Uint8_Default; };`
- L79 _public member_ `template<> struct TDefaultSerialMethod<uint8> { constexpr static ESerialMethod Value = ESerialMethod::Uint8_Default; };`
- L80 _public member_ `template<> struct TDefaultSerialMethod<int32> { constexpr static ESerialMethod Value = ESerialMethod::Int32_Default; };`
- L81 _public member_ `template<> struct TDefaultSerialMethod<uint32> { constexpr static ESerialMethod Value = ESerialMethod::Uint32_Default; };`
- L82 _public member_ `template<> struct TDefaultSerialMethod<uint64> { constexpr static ESerialMethod Value = ESerialMethod::Uint64_Default; };`
- L83 _public member_ `template<> struct TDefaultSerialMethod<FString> { constexpr static ESerialMethod Value = ESerialMethod::String_Default; };`
- L84 _public member_ `template<> struct TDefaultSerialMethod<float> { constexpr static ESerialMethod Value = ESerialMethod::Float_Default; };`
- L85 _public member_ `template<> struct TDefaultSerialMethod<double> { constexpr static ESerialMethod Value = ESerialMethod::Double_Default; };`
- L86 _public member_ `template<> struct TDefaultSerialMethod<TArray<int32>> { constexpr static ESerialMethod Value = ESerialMethod::Int32_Array; };`
- L87 _public member_ `template<> struct TDefaultSerialMethod<TArray<FString>> { constexpr static ESerialMethod Value = ESerialMethod::String_Array; };`
- L88 _public member_ `template<> struct TDefaultSerialMethod<TArray<float>> { constexpr static ESerialMethod Value = ESerialMethod::Float_Array; };`
- L89 _public member_ `template<> struct TDefaultSerialMethod<FLinearColor> { constexpr static ESerialMethod Value = ESerialMethod::LinearColor_Default;};`
- L90 _public member_ `template<> struct TDefaultSerialMethod<FMD5Hash> { constexpr static ESerialMethod Value = ESerialMethod::MD5Hash_Default; };`
- L91 _public member_ `template<> struct TDefaultSerialMethod<FTransform> { constexpr static ESerialMethod Value = ESerialMethod::Transform_Default; };`

#### struct `Reflect::TDefaultSerialMethod`  
`template<> struct TDefaultSerialMethod<FMD5Hash>`  
_L90-90_
- L74 _public member_ `template<typename T> struct TDefaultSerialMethod { constexpr static ESerialMethod Value = ESerialMethod::_NotImplementedYet; };` — This list maps which serialization method should be used for each Type reflected by directlink
- L78 _public member_ `template<> struct TDefaultSerialMethod<bool> { constexpr static ESerialMethod Value = ESerialMethod::Uint8_Default; };`
- L79 _public member_ `template<> struct TDefaultSerialMethod<uint8> { constexpr static ESerialMethod Value = ESerialMethod::Uint8_Default; };`
- L80 _public member_ `template<> struct TDefaultSerialMethod<int32> { constexpr static ESerialMethod Value = ESerialMethod::Int32_Default; };`
- L81 _public member_ `template<> struct TDefaultSerialMethod<uint32> { constexpr static ESerialMethod Value = ESerialMethod::Uint32_Default; };`
- L82 _public member_ `template<> struct TDefaultSerialMethod<uint64> { constexpr static ESerialMethod Value = ESerialMethod::Uint64_Default; };`
- L83 _public member_ `template<> struct TDefaultSerialMethod<FString> { constexpr static ESerialMethod Value = ESerialMethod::String_Default; };`
- L84 _public member_ `template<> struct TDefaultSerialMethod<float> { constexpr static ESerialMethod Value = ESerialMethod::Float_Default; };`
- L85 _public member_ `template<> struct TDefaultSerialMethod<double> { constexpr static ESerialMethod Value = ESerialMethod::Double_Default; };`
- L86 _public member_ `template<> struct TDefaultSerialMethod<TArray<int32>> { constexpr static ESerialMethod Value = ESerialMethod::Int32_Array; };`
- L87 _public member_ `template<> struct TDefaultSerialMethod<TArray<FString>> { constexpr static ESerialMethod Value = ESerialMethod::String_Array; };`
- L88 _public member_ `template<> struct TDefaultSerialMethod<TArray<float>> { constexpr static ESerialMethod Value = ESerialMethod::Float_Array; };`
- L89 _public member_ `template<> struct TDefaultSerialMethod<FLinearColor> { constexpr static ESerialMethod Value = ESerialMethod::LinearColor_Default;};`
- L90 _public member_ `template<> struct TDefaultSerialMethod<FMD5Hash> { constexpr static ESerialMethod Value = ESerialMethod::MD5Hash_Default; };`
- L91 _public member_ `template<> struct TDefaultSerialMethod<FTransform> { constexpr static ESerialMethod Value = ESerialMethod::Transform_Default; };`

#### struct `Reflect::TDefaultSerialMethod`  
`template<> struct TDefaultSerialMethod<FTransform>`  
_L91-91_
- L74 _public member_ `template<typename T> struct TDefaultSerialMethod { constexpr static ESerialMethod Value = ESerialMethod::_NotImplementedYet; };` — This list maps which serialization method should be used for each Type reflected by directlink
- L78 _public member_ `template<> struct TDefaultSerialMethod<bool> { constexpr static ESerialMethod Value = ESerialMethod::Uint8_Default; };`
- L79 _public member_ `template<> struct TDefaultSerialMethod<uint8> { constexpr static ESerialMethod Value = ESerialMethod::Uint8_Default; };`
- L80 _public member_ `template<> struct TDefaultSerialMethod<int32> { constexpr static ESerialMethod Value = ESerialMethod::Int32_Default; };`
- L81 _public member_ `template<> struct TDefaultSerialMethod<uint32> { constexpr static ESerialMethod Value = ESerialMethod::Uint32_Default; };`
- L82 _public member_ `template<> struct TDefaultSerialMethod<uint64> { constexpr static ESerialMethod Value = ESerialMethod::Uint64_Default; };`
- L83 _public member_ `template<> struct TDefaultSerialMethod<FString> { constexpr static ESerialMethod Value = ESerialMethod::String_Default; };`
- L84 _public member_ `template<> struct TDefaultSerialMethod<float> { constexpr static ESerialMethod Value = ESerialMethod::Float_Default; };`
- L85 _public member_ `template<> struct TDefaultSerialMethod<double> { constexpr static ESerialMethod Value = ESerialMethod::Double_Default; };`
- L86 _public member_ `template<> struct TDefaultSerialMethod<TArray<int32>> { constexpr static ESerialMethod Value = ESerialMethod::Int32_Array; };`
- L87 _public member_ `template<> struct TDefaultSerialMethod<TArray<FString>> { constexpr static ESerialMethod Value = ESerialMethod::String_Array; };`
- L88 _public member_ `template<> struct TDefaultSerialMethod<TArray<float>> { constexpr static ESerialMethod Value = ESerialMethod::Float_Array; };`
- L89 _public member_ `template<> struct TDefaultSerialMethod<FLinearColor> { constexpr static ESerialMethod Value = ESerialMethod::LinearColor_Default;};`
- L90 _public member_ `template<> struct TDefaultSerialMethod<FMD5Hash> { constexpr static ESerialMethod Value = ESerialMethod::MD5Hash_Default; };`
- L91 _public member_ `template<> struct TDefaultSerialMethod<FTransform> { constexpr static ESerialMethod Value = ESerialMethod::Transform_Default; };`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace Reflect`
- L39 _variable_ `static constexpr uint8 _storeTypeMask = 0b0001'1111u;` (scope `Reflect`)
- L40 _variable_ `static constexpr uint8 _modifierMask = 0b1110'0000u;` (scope `Reflect`)
- L71 _function_ `static constexpr EStoreType GetStoreType(ESerialMethod Method)` (scope `Reflect`)
- L94 _function_ `template<typename T> EStoreType GetStoreTypeForType()` (scope `Reflect`)
- L95 _function_ `template<typename T> EStoreType GetStoreTypeForType()` (scope `Reflect`)
- L100 _function_ `template<ESerialMethod Code, typename T> void Serial(FArchive& Ar, T* Param)` (scope `Reflect`) — Serialization implementations
- L102 _function_ `template<> inline void Serial<ESerialMethod::Uint32_Packed>(FArchive& Ar, uint32* ValuePtr)` (scope `Reflect`)
- L104 _function_ `template<> inline void Serial<ESerialMethod::Vector_f32>(FArchive& Ar, FVector* ValuePtr)` (scope `Reflect`)
- L119 _function_ `template<> inline void Serial<ESerialMethod::Quat_f32>(FArchive& Ar, FQuat* ValuePtr)` (scope `Reflect`)
- L135 _function_ `inline bool SerialAny(FArchive& Ar, void* data, ESerialMethod Method)` (scope `Reflect`)
- L137 _macro_ `#define SerialAny_Case(enumvalue, casttype) case enumvalue: Serial<enumvalue>(Ar, (casttype*)data); return true;`
