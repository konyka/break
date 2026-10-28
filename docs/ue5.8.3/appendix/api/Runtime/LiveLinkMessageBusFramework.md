# Runtime / LiveLinkMessageBusFramework

- module root: `Source/Runtime/LiveLinkMessageBusFramework`
- headers: 4; symbols: 176
- symbol kinds: delegate=1, enum=6, enumerator=16, function=30, macro=3, member=45, namespace=6, prototype=55, struct=14
- PrivateIncludePathModuleNames: Messaging
- PublicDependencyModuleNames: Core, CoreUObject, LiveLinkInterface, MessagingCommon, Serialization

### `Source/Runtime/LiveLinkMessageBusFramework/Public/LiveLinkCompression.h` (Public)


#### struct `FLiveLinkByteArray`  
`struct FLiveLinkByteArray`  
_L13-31_
- reflection: `USTRUCT()`
- desc: Utility struct to serialize a byte array.
- L17 _public function_ `bool Serialize(FArchive& Ar)`
- L30 _public member_ `TArray<uint8> Bytes;` — `UPROPERTY()`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FLiveLinkByteArray> : public TStructOpsTypeTraitsBase2<FLiveLinkByteArray>`  
_L34-40_
- inherits: `TStructOpsTypeTraitsBase2<FLiveLinkByteArray>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L37-39_

#### enum `ELiveLinkCompressionMethod`  
`enum class ELiveLinkCompressionMethod : uint8`  
_L44-54_
- reflection: `UENUM()`
- desc: What compression method should be used on the LiveLink data.
- L47 _public enumerator_ `Uncompressed` — Data is uncompressed.
- L50 _public enumerator_ `Oodle` — Oodle compression is used for the serialized data.
- L53 _public enumerator_ `Zlib` — ZLib compression is used for the serialized data.

#### enum `ELiveLinkCompressionBias`  
`enum class ELiveLinkCompressionBias : uint8`  
_L58-68_
- reflection: `UENUM()`
- desc: The bias (if any) to use when compressing the data.
- L61 _public enumerator_ `None` — Compress without a bias.
- L64 _public enumerator_ `Size` — Compress with a bias for size
- L67 _public enumerator_ `Speed` — Compress with a bias for speed.

#### enum `ELiveLinkPayloadSerializationMethod`  
`enum class ELiveLinkPayloadSerializationMethod : uint8`  
_L174-180_
- reflection: `UENUM()`
- desc: What method should be used for serialziing.
- L177 _public enumerator_ `Standard = 0` — The data will be serialized using standard platform method.
- L179 _public enumerator_ `Cbor` — The data will be serialized using Cbor method.

#### enum `ELiveLinkPayloadCompressionType`  
`enum class ELiveLinkPayloadCompressionType : uint8`  
_L184-192_
- reflection: `UENUM()`
- desc: Dictates when compression should be used.
- L187 _public enumerator_ `None = 0` — The serialized data will not be compressed.
- L189 _public enumerator_ `Heuristic` — The serialized data will be compressed based on struct size.
- L191 _public enumerator_ `Always` — The serialized data will always be compressed.

#### struct `FLiveLinkSerializedFrameData`  
`struct FLiveLinkSerializedFrameData`  
_L196-256_
- reflection: `USTRUCT()`
- desc: Utility struct used to wrap serialized data and handle compression / decompression.
- L200 _public prototype_ `FLiveLinkSerializedFrameData() = default;`
- L202 _public function_ `FLiveLinkSerializedFrameData(ELiveLinkPayloadSerializationMethod SerializeMethod) : SerializationMethod(SerializeMethod)`
- L208 _public prototype_ `bool SetPayload(const FStructOnScope& InPayload, ELiveLinkPayloadCompressionType CompressionType = ELiveLinkPayloadCompressionType::Heuristic);` — Initialize this payload from the given data
- L209 _public prototype_ `bool SetPayload(const UScriptStruct* InPayloadType, const void* InPayloadData, ELiveLinkPayloadCompressionType CompressionType = ELiveLinkPayloadCompressionType::Heuristic);`
- L212 _public function_ `template <typename T> bool SetTypedPayload(const T& InPayloadData, ELiveLinkPayloadCompressionType CompressType = ELiveLinkPayloadCompressionType::Heuristic)`
- L218 _public prototype_ `bool GetPayload(FStructOnScope& OutPayload) const;` — Extract the payload into an in-memory instance
- L219 _public prototype_ `bool GetPayload(const UScriptStruct* InPayloadType, void* InOutPayloadData) const;`
- L221 _public prototype_ `bool IsTypeChildOf(const UScriptStruct* InPayloadType) const;`
- L224 _public function_ `template<typename T> bool IsTypeChildOf() const`
- L230 _public function_ `template <typename T> bool GetTypedPayload(T& OutPayloadData) const`
- L237 _public member_ `FName PayloadTypeName;` — `UPROPERTY(VisibleAnywhere, Category = "Payload")` — The typename of the user-defined payload.
- L241 _public member_ `ELiveLinkPayloadSerializationMethod SerializationMethod = ELiveLinkPayloadSerializationMethod::Standard;` — `UPROPERTY(VisibleAnywhere, Category = "Payload")` — Specifies the serialization method used to pack the data
- L244 _public member_ `ELiveLinkCompressionMethod CompressionMethod = ELiveLinkCompressionMethod::Uncompressed;` — `UPROPERTY(VisibleAnywhere, Category = "Payload")`
- L247 _public member_ `ELiveLinkCompressionBias CompressionBias = ELiveLinkCompressionBias::None;` — `UPROPERTY(VisibleAnywhere, Category = "Payload")`
- L251 _public member_ `int32 PayloadSize = 0;` — `UPROPERTY(VisibleAnywhere, Category = "Payload")` — The uncompressed size of the user-defined payload data.
- L255 _public member_ `FLiveLinkByteArray PayloadBytes;` — `UPROPERTY()` — The data of the user-defined payload (potentially stored as compressed binary for compact transfer).

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API LIVELINKMESSAGEBUSFRAMEWORK_API`
- L38 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anona4f8f3070103`)
- L70 _namespace_ `namespace UE`
- L70 _namespace_ `namespace LiveLink` (scope `UE`)
- L70 _namespace_ `namespace Compression` (scope `UE::LiveLink`)
- L74 _prototype_ `int32 GetConsoleVariableCompressionType();` (scope `UE::LiveLink::Compression`) — Get the compression type from the console variable setting.
- L77 _prototype_ `int32 GetConsoleVariableCompressionFlags();` (scope `UE::LiveLink::Compression`) — Function to check the console variable for the compression flags. Speed vs size.
- L81 _function_ `template <typename SizeType> inline bool ShouldCompress(SizeType DataSize)` (scope `UE::LiveLink::Compression`) — Based on the size of the data to compress indicate if we should invoke the compressor.
- L95 _function_ `inline FName GetCompressionAlgorithm()` (scope `UE::LiveLink::Compression`) — Get the named compression algorithm to invoke with serializer and memory compressors.
- L106 _function_ `inline ECompressionFlags GetCompressionFlags()` (scope `UE::LiveLink::Compression`) — Get the default flags to use when invoking the compressor.
- L121 _function_ `inline FName GetCompressionAlgorithm(ELiveLinkCompressionMethod Method)` (scope `UE::LiveLink::Compression`) — Get the named compression algorithm based on the provided details.  Current this is only Zlib or Oodle.
- L127 _function_ `inline ECompressionFlags GetCoreCompressionFlags(ELiveLinkCompressionBias InBias)` (scope `UE::LiveLink::Compression`) — Get the compression enum value given the LiveLink compression settings.  This the value passed into the serializer and memory compressor.
- L141 _function_ `inline ELiveLinkCompressionBias GetCompressionBias(ECompressionFlags Flags)` (scope `UE::LiveLink::Compression`) — Get LiveLinkCompressionBias from a ECompressionFlags.
- L158 _function_ `inline ELiveLinkCompressionMethod GetCompressionMethod(FName NamedMethod)` (scope `UE::LiveLink::Compression`) — Convert a compression method name to a ELiveLinkCompressionMethod.

### `Source/Runtime/LiveLinkMessageBusFramework/Public/LiveLinkMessages.h` (Public)


#### struct `FLiveLinkMessageAnnotation`  
`struct FLiveLinkMessageAnnotation`  
_L11-20_
- L13 _public member_ `static FName SubjectAnnotation;`
- L14 _public member_ `static FName RoleAnnotation;`
- L15 _public member_ `static FName OriginalSourceAnnotation;`
- L17 _public member_ `static FName TopologyModeAnnotation;` — Indicates what mode this instance is running in.
- L19 _public member_ `static FName CompressedPayloadSupport;` — Presense of this annotation informs providers that this client supports compressed animation payloads.

#### enum `ELiveLinkTopologyMode`  
`enum class ELiveLinkTopologyMode : uint8`  
_L23-29_
- reflection: `UENUM()`
- L25 _public enumerator_ `Hub UMETA(ToolTip = "LiveLinkHub instance that can receive data from other hub instances and transmit it to Unreal Editor instances.")`
- L26 _public enumerator_ `Spoke UMETA(ToolTip = "LiveLinkHub instance can only transmit data to other LiveLinkHub instances.")`
- L27 _public enumerator_ `UnrealClient UMETA(ToolTip = "Unreal Editor instance that can only receive data from LiveLinkHub")`
- L28 _public enumerator_ `External UMETA(ToolTip = "Client that can transmit to Hubs, Spokes and UnrealClients. (Default mode for message bus providers)")`

#### struct `FLiveLinkPingMessage`  
`struct FLiveLinkPingMessage`  
_L42-64_
- reflection: `USTRUCT()`
- L47 _public member_ `FGuid PollRequest;` — `UPROPERTY()`
- L50 _public member_ `int32 LiveLinkVersion = 1;` — `UPROPERTY()`
- L54 _public member_ `int32 DiscoveryProtocolVersion = 1;` — `UPROPERTY()` — V1: 5.6 and earlier, V2: 5.7 and later.
- L57 _public prototype_ `FLiveLinkPingMessage() = default;` — default constructor for the receiver
- L59 _public function_ `FLiveLinkPingMessage(const FGuid& InPollRequest, int32 InLiveLinkVersion) : PollRequest(InPollRequest) , LiveLinkVersion(InLiveLinkVersion) , DiscoveryProtocolVersion(2)`

#### struct `FLiveLinkPongMessage`  
`struct FLiveLinkPongMessage`  
_L67-97_
- reflection: `USTRUCT()`
- L72 _public member_ `FString ProviderName;` — `UPROPERTY()`
- L75 _public member_ `FString MachineName;` — `UPROPERTY()`
- L78 _public member_ `FGuid PollRequest;` — `UPROPERTY()`
- L81 _public member_ `int32 LiveLinkVersion = 1;` — `UPROPERTY()`
- L85 _public member_ `int32 DiscoveryProtocolVersion = 1;` — `UPROPERTY()` — V1: 5.6 and earlier, V2: 5.7 and later.
- L88 _public member_ `double CreationPlatformTime = -1.0;` — `UPROPERTY()`
- L91 _public prototype_ `FLiveLinkPongMessage() = default;` — default constructor for the receiver
- L94 _public function_ `FLiveLinkPongMessage(const FString& InProviderName, const FString& InMachineName, const FGuid& InPollRequest) : ProviderName(InProviderName), MachineName(InMachineName), PollRequest(InPollRequest), DiscoveryProtocolVersion(2), CreationPlatformTime(FPlatformTime::Seconds())` — `UE_DEPRECATED(5.0, "This version of the FLiveLinkPongMessage constructor is deprecated. Please use the new constructor instead to ensure the LiveLinkVersion is set properly.")`
- L96 _public function_ `FLiveLinkPongMessage(const FString& InProviderName, const FString& InMachineName, const FGuid& InPollRequest, int32 InLiveLinkVersion) : ProviderName(InProviderName), MachineName(InMachineName), PollRequest(InPollRequest), LiveLinkVersion(InLiveLinkVersion), DiscoveryProtocolVersion(2), CreationPlatformTime(FPlatformTime::Seconds())`

#### struct `FLiveLinkConnectMessage`  
`struct FLiveLinkConnectMessage`  
_L100-106_
- reflection: `USTRUCT()`
- L105 _public member_ `int32 LiveLinkVersion = 1;` — `UPROPERTY()`

#### struct `FLiveLinkHeartbeatMessage`  
`struct FLiveLinkHeartbeatMessage`  
_L109-112_
- reflection: `USTRUCT()`

#### struct `FLiveLinkClearSubject`  
`struct FLiveLinkClearSubject`  
_L115-125_
- reflection: `USTRUCT()`
- L121 _public member_ `FName SubjectName;` — `UPROPERTY()` — Name of the subject to clear
- L123 _public function_ `FLiveLinkClearSubject()`
- L124 _public function_ `FLiveLinkClearSubject(const FName& InSubjectName) : SubjectName(InSubjectName)`

#### struct `FLiveLinkSubjectDataMessage`  
`struct UE_DEPRECATED(4.23, "FLiveLinkSubjectDataMessage is deprecated. Please use the LiveLink animation role.") FLiveLinkSubjectDataMessage`  
_L129-138_
- reflection: `USTRUCT()`
- L134 _public member_ `FLiveLinkRefSkeleton RefSkeleton;` — `UPROPERTY()`
- L137 _public member_ `FName SubjectName;` — `UPROPERTY()`

#### struct `FLiveLinkSubjectFrameMessage`  
`struct UE_DEPRECATED(4.23, "FLiveLinkSubjectDataMessage is deprecated. Please use the LiveLink animation role.") FLiveLinkSubjectFrameMessage`  
_L141-163_
- reflection: `USTRUCT()`
- L146 _public member_ `FName SubjectName;` — `UPROPERTY()`
- L150 _public member_ `TArray<FTransform> Transforms;` — `UPROPERTY()` — Bone Transform data for this frame
- L154 _public member_ `TArray<FLiveLinkCurveElement> Curves;` — `UPROPERTY()` — Curve data for this frame
- L158 _public member_ `FLiveLinkMetaData MetaData;` — `UPROPERTY()` — Subject MetaData for this frame
- L162 _public member_ `double Time = 0.0;` — `UPROPERTY()` — Incrementing time for interpolation

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API LIVELINKMESSAGEBUSFRAMEWORK_API`
- L32 _namespace_ `namespace UE`
- L32 _namespace_ `namespace LiveLink` (scope `UE`)
- L32 _namespace_ `namespace Messaging` (scope `UE::LiveLink`)
- L35 _prototype_ `bool CanReceiveFrom(ELiveLinkTopologyMode LHSMode, ELiveLinkTopologyMode RHSMode);` (scope `UE::LiveLink::Messaging`) — Whether the left hand side mode can receive from the right hand side mode LiveLink Source.
- L38 _prototype_ `bool CanTransmitTo(ELiveLinkTopologyMode LHSMode, ELiveLinkTopologyMode RHSMode);` (scope `UE::LiveLink::Messaging`) — Whether the left hand side mode can transmit to the right hand side mode Client.

### `Source/Runtime/LiveLinkMessageBusFramework/Public/LiveLinkProvider.h` (Public)


#### struct `ILiveLinkProvider`  
`struct ILiveLinkProvider`  
_L25-84_
- L28 _public prototype_ `static TSharedPtr<ILiveLinkProvider> CreateLiveLinkProvider(const FString& ProviderName);`
- L37 _public function_ `template<typename T> static TSharedPtr<ILiveLinkProvider> CreateLiveLinkProvider(const FString& ProviderName, struct FMessageEndpointBuilder&& EndpointBuilder)` — Create a Live Link Provider based on a class derived from ILiveLinkProvider instead of using the default Live Link Provider. @param ProviderName		The provider name. @param EndpointBuilder	An endpoint builder that can be used to add additional message handlers. @return					Shared pointer to the ILiveLinkProvider-derived class. Use StaticCastSharedPtr to cast it back to child class type.
- L43 _public prototype_ `virtual ~ILiveLinkProvider() = default;`
- L56 _public prototype_ `virtual bool UpdateSubjectStaticData(const FName SubjectName, TSubclassOf<ULiveLinkRole> Role, FLiveLinkStaticDataStruct&& StaticData, const TMap<FName, FString>& ExtraAnnotations = {}) = 0;` — Send, to UE, the static data of a subject. @param SubjectName	    The name of the subject @param Role			    The Live Link role of the subject. The StaticData type should match the role's data. @param StaticData	    The static data of the subject. The FLiveLinkStaticDataStruct doesn't have a copy constructor. The argument is passed by r-value to help the user understand the compiler error message. @param ExtraAnnotations	Extra annotations to pass in with the static data message. @return				True if the message was sent or is pending an active connection. @see					UpdateSubjectFrameData, RemoveSubject
- L62 _public prototype_ `virtual void RemoveSubject(const FName SubjectName) = 0;` — Inform UE that a subject won't be streamed anymore. @param SubjectName	The name of the subject.
- L74 _public prototype_ `virtual bool UpdateSubjectFrameData(const FName SubjectName, FLiveLinkFrameDataStruct&& FrameData, const TMap<FName, FString>& ExtraAnnotations = {}) = 0;` — Send the static data of a subject to UE. @param SubjectName		The name of the subject @param StaticData		The frame data of the subject. The type should match the role's data send with UpdateSubjectStaticData. The FLiveLinkFrameDataStruct doesn't have a copy constructor. The argument is passed by r-value to help the user understand the compiler error message. @param ExtraAnnotations	Extra annotations to pass in with the frame data message. @return					True if the message was sent or is pending an active connection. @see						UpdateSubjectStaticData, RemoveSubject
- L77 _public prototype_ `virtual bool HasConnection() const = 0;` — Is this provider currently connected to something.
- L80 _public prototype_ `virtual FDelegateHandle RegisterConnStatusChangedHandle(const FLiveLinkProviderConnectionStatusChanged::FDelegate& ConnStatusChanged) = 0;` — Function for managing connection status changed delegate.
- L83 _public prototype_ `virtual void UnregisterConnStatusChangedHandle(FDelegateHandle Handle) = 0;` — Function for managing connection status changed delegate.

#### Free symbols / members of external scopes

- L23 _delegate_ `DECLARE_MULTICAST_DELEGATE(FLiveLinkProviderConnectionStatusChanged);` — Delegate called when the connection status of the provider has changed.
- L23 _prototype_ `DECLARE_MULTICAST_DELEGATE(FLiveLinkProviderConnectionStatusChanged);` — Delegate called when the connection status of the provider has changed.

### `Source/Runtime/LiveLinkMessageBusFramework/Public/LiveLinkProviderImpl.h` (Public)


#### struct `FTrackedSubject`  
`struct FTrackedSubject`  
_L15-31_
- desc: Subject that the application has told us about
- L18 _public member_ `FLiveLinkRefSkeleton RefSkeleton;` — Ref skeleton to go with transform data
- L21 _public member_ `TArray<FTransform> Transforms;` — Bone transform data
- L24 _public member_ `TArray<FLiveLinkCurveElement> Curves;` — Curve data
- L27 _public member_ `FLiveLinkMetaData MetaData;` — MetaData for subject
- L30 _public member_ `double Time;` — Incrementing time (application time) for interpolation purposes

#### struct `FLiveLinkProvider`  
`struct FLiveLinkProvider : public ILiveLinkProvider`  
_L34-264_
- inherits: `ILiveLinkProvider`
- L37 _private member_ `const FString ProviderName;`
- L38 _private member_ `const FString MachineName;`
- L40 _private member_ `TSharedPtr<class FMessageEndpoint, ESPMode::ThreadSafe> MessageEndpoint;`
- L43 _private member_ `mutable FCriticalSection CriticalSection;` — Lock to stop multiple threads accessing the CurrentPreset at the same time
- L46 _private member_ `TArray<struct FTrackedAddress> ConnectedAddresses;` — Array of our current connections
- L49 _private member_ `TArray<struct FTrackedStaticData> StaticDatas;` — Cache of our current subject state
- L50 _private member_ `TArray<struct FTrackedFrameData> FrameDatas;`
- L51 _private member_ `TMap<FName, FTrackedSubject> Subjects;`
- L54 _private member_ `TMap<FName, int32> SubjectFrameIds;` — Per-subject FrameIds
- L57 _private member_ `FLiveLinkProviderConnectionStatusChanged OnConnectionStatusChanged;` — Delegate to notify interested parties when the client sources have changed
- L64 _private prototype_ `void HandlePingMessage(const FLiveLinkPingMessage& Message, const TSharedRef<class IMessageContext, ESPMode::ThreadSafe>& Context);` — Handles ping message and sends back a pong
- L66 _private prototype_ `void HandleHeartbeat(const FLiveLinkHeartbeatMessage& Message, const TSharedRef<class IMessageContext, ESPMode::ThreadSafe>& Context);`
- L70 _private prototype_ `FTrackedSubject& GetTrackedSubject(const FName& SubjectName);`
- L72 _private prototype_ `void SendSubject(FName SubjectName, const struct FTrackedSubject& Subject);`
- L74 _private prototype_ `void SendSubjectFrame(FName SubjectName, const struct FTrackedSubject& Subject);`
- L77 _private prototype_ `FTrackedStaticData* GetLastSubjectStaticData(const FName& SubjectName);` — Get the cached data for the named subject
- L79 _private prototype_ `FTrackedFrameData* GetLastSubjectFrameData(const FName& SubjectName);`
- L81 _private prototype_ `void SetLastSubjectStaticData(FName SubjectName, TSubclassOf<ULiveLinkRole> Role, FLiveLinkStaticDataStruct&& StaticData, TMap<FName, FString>&& Annotations);`
- L83 _private prototype_ `void SetLastSubjectFrameData(FName SubjectName, FLiveLinkFrameDataStruct&& FrameData, TMap<FName, FString>&& SubjectAnnotations);`
- L86 _private prototype_ `void ClearTrackedSubject(const FName& SubjectName);` — Clear a existing track subject
- L89 _private prototype_ `void GetFilteredAddresses(FName SubjectName, TArray<FMessageAddress>& Addresses);` — Get the connected addresses that should receive livelink data.
- L92 _private prototype_ `struct FLiveLinkSerializedFrameData SerializeAnimationData(struct FLiveLinkAnimationFrameData* AnimData);` — Serialize animation frame data into a compressed payload to reduce throughput.
- L96 _protected prototype_ `static int32 GetSupportedLiveLinkVersion();` — Get the minimum supported version of livelink clients that can connect to this provider.
- L99 _protected prototype_ `void HandleConnectMessage(const FLiveLinkConnectMessage& Message, const TSharedRef<class IMessageContext, ESPMode::ThreadSafe>& Context);` — Update connected addresses and send information to the connected source
- L102 _protected prototype_ `void CreateMessageEndpoint(struct FMessageEndpointBuilder& EndpointBuilder);` — Create the message bus message endoing responsble for dispatching message bus messages to their respective handlers
- L105 _protected prototype_ `void GetConnectedAddresses(TArray<FMessageAddress>& Addresses);` — Get the addresses of all connected instances.
- L108 _protected prototype_ `void ValidateConnections();` — Validate our current connections, removing those that have timed out.
- L111 _protected prototype_ `void CloseConnection(FMessageAddress Address);` — Close a connection using its address.
- L114 _protected prototype_ `TPair<UClass*, FLiveLinkStaticDataStruct*> GetLastSubjectStaticDataStruct(FName SubjectName);` — Get the cached data struct for a subject
- L117 _protected function_ `virtual void OnMessageBusNotification(const FMessageBusNotification& Notification)` — Invoked by MessageBus when a node is registered or unregistered.
- L121 _protected function_ `template<typename MessageType> void SendMessage(MessageType* Message, EMessageFlags Flags = EMessageFlags::None)` — Send message (only to connected addresses)
- L138 _protected function_ `template<typename MessageType> void SendMessage(MessageType* Message, const FMessageAddress& Address, EMessageFlags Flags = EMessageFlags::None, const TMap<FName, FString>& Annotations = {})` — Send message to a specific address.
- L150 _protected function_ `template<typename MessageType> void SendMessage(MessageType* Message, const TArray<FMessageAddress>& Addresses, EMessageFlags Flags = EMessageFlags::None, const TMap<FName, FString>& Annotations = {})` — Send message to a list of addresses.
- L162 _protected function_ `template<typename MessageType> void Publish(MessageType* Message)` — Broadcast message on the network.
- L174 _protected function_ `template<typename MessageType> void Publish(MessageType* Message, const TMap<FName, FString>& Annotations)` — Broadcast message on the network with annotations.
- L186 _protected function_ `template<typename MessageType> void Subscribe()` — Subscribe to a message that's been published.
- L195 _protected function_ `const FString& GetProviderName() const` — Get the name of this provider.
- L201 _protected function_ `const FString& GetMachineName() const` — Get the name of this machine.
- L207 _protected function_ `virtual void OnConnectionsClosed(const TArray<FMessageAddress>& ClosedAddresses)` — Called after ValidateConnections removes invalid connections
- L210 _protected function_ `virtual TMap<FName, FString> GetAnnotations() const` — Get annotations to include on every message sent by this provider
- L221 _protected function_ `virtual bool ShouldTransmitToSubject_AnyThread(FName SubjectName, FMessageAddress Address) const` — Get whether a combination of a subject/client should receive livelink data.
- L227 _protected prototype_ `void SendClearSubjectToConnections(FName SubjectName);` — Send a clear subject message to indicate that the subject should be removed from the connected client.
- L230 _protected prototype_ `FMessageAddress GetEndpointAddress() const;` — Get the MessageBus address of the provider.
- L233 _protected prototype_ `FLiveLinkProvider(const FString& InProviderName, bool bInCreateEndpoint);` — Constructor for derived classes that allows specifying that no endpoint should be created.
- L236 _public prototype_ `FLiveLinkProvider(const FString& InProviderName);`
- L238 _public prototype_ `FLiveLinkProvider(const FString& InProviderName, struct FMessageEndpointBuilder&& EndpointBuilder);`
- L242 _public prototype_ `virtual void UpdateSubject(const FName& SubjectName, const TArray<FName>& BoneNames, const TArray<int32>& BoneParents);`
- L244 _public prototype_ `virtual bool UpdateSubjectStaticData(const FName SubjectName, TSubclassOf<ULiveLinkRole> Role, FLiveLinkStaticDataStruct&& StaticData, const TMap<FName, FString>& ExtraAnnotations = {}) override;`
- L246 _public prototype_ `virtual void ClearSubject(const FName& SubjectName);`
- L248 _public prototype_ `virtual void RemoveSubject(const FName SubjectName) override;`
- L251 _public prototype_ `virtual void UpdateSubjectFrame(const FName& SubjectName, const TArray<FTransform>& BoneTransforms, const TArray<FLiveLinkCurveElement>& CurveData, double Time);`
- L253 _public prototype_ `virtual void UpdateSubjectFrame(const FName& SubjectName, const TArray<FTransform>& BoneTransforms, const TArray<FLiveLinkCurveElement>& CurveData, const FLiveLinkMetaData& MetaData, double Time);`
- L257 _public prototype_ `virtual bool UpdateSubjectFrameData(const FName SubjectName, FLiveLinkFrameDataStruct&& FrameData, const TMap<FName, FString>& ExtraAnnotations = {}) override;`
- L259 _public prototype_ `virtual bool HasConnection() const override;`
- L261 _public prototype_ `virtual FDelegateHandle RegisterConnStatusChangedHandle(const FLiveLinkProviderConnectionStatusChanged::FDelegate& ConnStatusChanged) override;`
- L263 _public prototype_ `virtual void UnregisterConnStatusChangedHandle(FDelegateHandle Handle) override;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API LIVELINKMESSAGEBUSFRAMEWORK_API`
