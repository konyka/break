# Plugins / LiveLinkOpenTrackIO

- module root: `Plugins/VirtualProduction/LiveLinkOpenTrackIO/Source/LiveLinkOpenTrackIO`
- headers: 14; symbols: 498
- symbol kinds: class=8, delegate=2, enum=3, enumerator=10, function=88, member=211, namespace=8, prototype=118, struct=44, typedef=1, variable=5
- PrivateDependencyModuleNames: ApplicationCore, Cbor, CoreUObject, Engine, Json, JsonUtilities, LiveLinkLens, Networking, Projects, Serialization, Slate, SlateCore, Sockets
- PublicDependencyModuleNames: Core, LiveLinkInterface

### `Plugins/VirtualProduction/LiveLinkOpenTrackIO/Source/LiveLinkOpenTrackIO/Private/LiveLinkOpenTrackIOConnectionSettings.h` (Private)


#### enum `ELiveLinkOpenTrackIONetworkProtocol`  
`enum class ELiveLinkOpenTrackIONetworkProtocol : uint8`  
_L12-16_
- reflection: `UENUM(BlueprintType)`
- desc: Pick between Multicast or Unicast for this connection
- L14 _public enumerator_ `Multicast UMETA(DisplayName = "Multicast")`
- L15 _public enumerator_ `Unicast UMETA(DisplayName = "Unicast")`

#### struct `FLiveLinkOpenTrackIOConnectionSettings`  
`struct FLiveLinkOpenTrackIOConnectionSettings`  
_L20-62_
- reflection: `USTRUCT()`
- L25 _public member_ `static constexpr TCHAR AutoSubjectName[] = TEXT("Aut` — Using this is equivalent to leaving the SubjectName empty.
- L29 _public member_ `FString SubjectName = AutoSubjectName;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — If empty or "Auto", one will be automatically generated.
- L33 _public member_ `ELiveLinkOpenTrackIONetworkProtocol Protocol = ELiveLinkOpenTrackIONetworkProtocol::Multicast;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Protocol selection: Multicast (default) or Unicast.
- L40 _public member_ `FString MulticastGroup = TEXT("239` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = ( EditCondition = "Protocol == ELiveLinkOpenTrackIONetworkProtocol::Multicast", EditConditionHides ))` — Multicast Group. The last octet is the SourceNumber and should stay within the range [1,200], per the OpenTrackIO spec.
- L49 _public member_ `uint16 MulticastPort = 55555;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = ( EditCondition = "Protocol == ELiveLinkOpenTrackIONetworkProtocol::Multicast", EditConditionHides, ClampMin = "1", ClampMax = "65535", UIMin = "1", UIMax = "65535" ))` — Multicast Port.
- L53 _public member_ `FString LocalInterface = TEXT("0.0` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Local interface (used in both Unicast and Multicast protocols).
- L60 _public member_ `uint16 UnicastPort = 0;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = ( EditCondition = "Protocol == ELiveLinkOpenTrackIONetworkProtocol::Unicast", EditConditionHides ))` — Unicast Port. 0 means self-assign. Use a port number available in your system.

### `Plugins/VirtualProduction/LiveLinkOpenTrackIO/Source/LiveLinkOpenTrackIO/Private/LiveLinkOpenTrackIOConversions.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace LiveLinkOpenTrackIOConversions`
- L32 _variable_ `inline constexpr float MetersToCentimeters = 100.f;` (scope `LiveLinkOpenTrackIOConversions`) — Factor to convert from OpenTrackIO's meters to Unreal's centimeters
- L36 _prototype_ `void ToUnrealLens( FLiveLinkLensFrameData& OutUnrealLensData, const FLiveLinkOpenTrackIOLens* InLensData, const FLiveLinkOpenTrackIOStaticCamera* InCamera );` (scope `LiveLinkOpenTrackIOConversions`) — Populate Live Link Lens Frame Data from relevant OpenTrackIO structures
- L43 _function_ `inline FVector ToUnrealTranslation(const FLiveLinkOpenTrackIO_XYZ& InXYZ)` (scope `LiveLinkOpenTrackIOConversions`) — From OpenTrackIO to Unreal Translation: Swap X <-> Y and convert meters to cm
- L49 _function_ `inline FVector ToUnrealScale(const FLiveLinkOpenTrackIO_XYZ& InXYZ)` (scope `LiveLinkOpenTrackIOConversions`) — From OpenTrackIO to Unreal Scale: Swap X <-> Y (unitless)
- L55 _function_ `inline FRotator ToUnrealRotation(const FLiveLinkOpenTrackIO_Rotator& InRotator)` (scope `LiveLinkOpenTrackIOConversions`) — From OpenTrackIO to Unreal Translation: Invert sign of Yaw
- L61 _function_ `inline FTransform ToUnrealTransform(const FLiveLinkOpenTrackIOTransform& InTransform)` (scope `LiveLinkOpenTrackIOConversions`) — From OpenTrackIO to Unreal FTransform

### `Plugins/VirtualProduction/LiveLinkOpenTrackIO/Source/LiveLinkOpenTrackIO/Private/LiveLinkOpenTrackIODatagram.h` (Private)


#### struct `FLiveLinkOpenTrackIODatagramHeader`  
`struct FLiveLinkOpenTrackIODatagramHeader`  
_L15-87_
- reflection: `USTRUCT()`
- desc: This struct stores the header portion of a UDP or serial OpenTrackIO payload. It only contains the header portion and the payload part will be handled separately via payload parsers. See specification at https://www.opentrackio.org/
- L24 _public member_ `uint32 Identifier = 0;` — `UPROPERTY()` — Bit offset 0-31 4 bytes: Static value to indicate OpenTrackIO packet, set to ASCII "OTrk" (0x4F54726B)
- L31 _public member_ `uint8 Reserved = 0;` — `UPROPERTY()` — Bit offset 32-39 1 byte: This field is reserved for future use and should be ignored by both Producers and Consumers.
- L38 _public member_ `uint8 Encoding = 0;` — `UPROPERTY()` — Bit offset 40-47 1 byte: Indicates the payload format (e.g., JSON = 0x01, CBOR = 0x02, OTP = 0x02). 0x80 and above are reserved for vendor specific protocols
- L45 _public member_ `uint16 SequenceNumber = 0;` — `UPROPERTY()` — Bit offset 48-63 2 bytes: A 16-bit unsigned integer indicating the OpenTrackIO packet's unique sequence number (0x01 to UINT16)
- L52 _public member_ `uint32 SegmentOffset = 0;` — `UPROPERTY()` — Bit offset 64-95 4 bytes: A 32-bit field indicating the byte offset of this payload segment when the overall payload length necessitates segmentation. Must be set to 0x00 for single-segment payloads.
- L62 _public member_ `uint16 LastSegmentFlagAndPayloadLength = 0;` — `UPROPERTY()` — Bit offset 96-111 The first bit shall be set to 1 if this is the only segment or the last segment in a segmented payload, or 0 if more segments are expected. The rest of the bits represent the total lenght of the payload. This differs slightly from the OpenTrackIO spec in that they have broken out LastSegment and Payload as separate fields but to use as a USTRUCT we must lump them together.
- L69 _public member_ `uint16 Checksum = 0;` — `UPROPERTY()` — Bit offset 112-127 2 bytes: A 16-bit checksum computed using the Fletcher-16 algorithm, covering the header (excluding checksum bytes) and payload.
- L74 _public function_ `bool IsLastSegment() const` — Returns true if the payload is complete and can be parsed.  If the payload is segmented then this will return false.
- L80 _public function_ `uint16 GetPayloadSize() const` — Helper function to return the size of the payload by and-ing the last 15 bits.

### `Plugins/VirtualProduction/LiveLinkOpenTrackIO/Source/LiveLinkOpenTrackIO/Private/LiveLinkOpenTrackIOLiveLinkTypes.h` (Private)


#### struct `FLiveLinkOpenTrackIOStaticData`  
`struct FLiveLinkOpenTrackIOStaticData : public FLiveLinkLensStaticData`  
_L15-18_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FLiveLinkLensStaticData`
- desc: Struct for static OpenTrackIO data

#### struct `FLiveLinkOpenTrackIOFrameData`  
`struct FLiveLinkOpenTrackIOFrameData : public FLiveLinkLensFrameData`  
_L24-31_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FLiveLinkLensFrameData`
- desc: Struct for dynamic (per-frame) OpenTrackIO data
- L30 _public member_ `FLiveLinkOpenTrackIOData OpenTrackData;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — Access to the received OpenTrackIO data

#### struct `FLiveLinkOpenTrackIOBlueprintData`  
`struct FLiveLinkOpenTrackIOBlueprintData : public FLiveLinkBaseBlueprintData`  
_L37-48_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FLiveLinkBaseBlueprintData`
- desc: Facility structure to handle OpenTrackIO data in blueprint
- L43 _public member_ `FLiveLinkOpenTrackIOStaticData StaticData;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink")` — Static data that should not change every frame
- L47 _public member_ `FLiveLinkOpenTrackIOFrameData FrameData;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink")` — Dynamic data that can change every frame

### `Plugins/VirtualProduction/LiveLinkOpenTrackIO/Source/LiveLinkOpenTrackIO/Private/LiveLinkOpenTrackIOParser.h` (Private)


#### struct `FLiveLinkOpenTrackIOPayload`  
`struct FLiveLinkOpenTrackIOPayload`  
_L20-78_
- desc: Payload storage for inbound data stream. If the datagram header indicates a payload will be transmitted over multiple units, we store payload data by calling AddBytes per new packet arrival until all packets are received (last segment flag on the header). There is no reliable transmission protocol for OpenTrackIO. If we detect that the entire payload was not delivered by the time we receive the last segment flag then we throw out the entire payload.
- L22 _public prototype_ `FLiveLinkOpenTrackIOPayload() = default;`
- L25 _public prototype_ `void AddBytes(uint32 InOffset, TArrayView<const uint8> InBytes);` — Add a partial payload to this class.
- L33 _public prototype_ `bool IsComplete() const;` — Inspect all data received and confirm that it is complete. To qualify as completed, we must have no gaps in our received data and the payload must not have exceeded our payload limit set in OpenTrackIO.PayloadLimitSize
- L39 _public function_ `bool HasAnyPayloadData() const` — Returns true if any payload data exists on this struct. This is useful for detecting continuity of data between header values.
- L49 _public function_ `TArrayView<const uint8> GetBytes() const` — Return a view into the data such that it can be passed into the CBOR or JSON parsers. You must ensure that you check that the payload is complete.
- L57 _private member_ `bool bValidPayload = true;` — Tracks if the payload is valid across all segments.  If we exceed our maximum payload size or we have received duplicate values
- L74 _private member_ `mutable TArray<FSegmentSection> Sections;` — Array to track all of the segment sections added to this payload. It is tagged mutable to support sorting within IsComplete() method.
- L77 _private member_ `TArray<uint8> PayloadBytes;` — Storage buffer for payload data from a packet stream.

#### struct `FLiveLinkOpenTrackIOPayload::FSegmentSection`  
`struct FSegmentSection`  
_L60-67_
- desc: Each segment received with Offset / Size pair.
- L63 _public member_ `uint32 Offset;` — InOffset value
- L66 _public member_ `int32 Size;` — Size

#### struct `FOpenTrackIOHeaderWithPayload`  
`struct FOpenTrackIOHeaderWithPayload`  
_L81-119_
- L86 _public function_ `const FLiveLinkOpenTrackIODatagramHeader& GetHeader() const` — Return a const reference to the header.
- L94 _public function_ `const FLiveLinkOpenTrackIOPayload& GetPayload() const` — Return a const reference to the payload data.
- L102 _public function_ `FLiveLinkOpenTrackIODatagramHeader& GetMutableHeader()` — Read / write access to the header.
- L110 _public function_ `FLiveLinkOpenTrackIOPayload& GetMutablePayload()` — Read / write access to the payload datga.
- L117 _private member_ `FLiveLinkOpenTrackIODatagramHeader Header;`
- L118 _private member_ `FLiveLinkOpenTrackIOPayload Payload;`

#### Free symbols / members of external scopes

- L121 _namespace_ `namespace UE`
- L121 _namespace_ `namespace OpenTrackIO` (scope `UE`)
- L121 _namespace_ `namespace Private` (scope `UE::OpenTrackIO`)
- L130 _prototype_ `TOptional<FLiveLinkOpenTrackIOData> ParseJsonBlob(const FString& JsonBlob);` (scope `UE::OpenTrackIO::Private`) — Try to parse a JSON string and return an optional FLiveLinkOpenTrackIOData type.  If parsing fails an unset optional will be returned.  If parsing succeeds then data will be returned. It is assumed that the JSON blob conforms to the minimal JSON. If it does not conform to the minimal JSON then an unset optional will be returned.
- L135 _prototype_ `TOptional<FLiveLinkOpenTrackIOData> ParseCborBlob(TArrayView<const uint8> ByteArray);` (scope `UE::OpenTrackIO::Private`) — Try to parse a CBOR blob. Return an optional FLiveLinkOpenTrackIOData type if CBOR parsing succeeds.
- L144 _prototype_ `bool GetHeaderAndPayloadFromBytes(TArrayView<const uint8> Bytes, FOpenTrackIOHeaderWithPayload& OutPayloadContainer);` (scope `UE::OpenTrackIO::Private`) — From a byte data, split the byte stream into a header and payload part validating the header and running a Fletcher-16 checksum on the header and payload. The result, if successful, is placed into OutPayloadContainer.  The function will return false if the checksum, header, or payload data is invalid.
- L150 _prototype_ `TOptional<FLiveLinkOpenTrackIOData> ParsePayload(const FOpenTrackIOHeaderWithPayload& HeaderAndPayload);` (scope `UE::OpenTrackIO::Private`) — Try to parse the payload from the given header and payload data. This will produce a FLiveLinkOpenTrackIOData struct that contains the full values read from the payload data. If the parsers fail to read the payload then an unset optional will be returned.

### `Plugins/VirtualProduction/LiveLinkOpenTrackIO/Source/LiveLinkOpenTrackIO/Private/LiveLinkOpenTrackIORole.h` (Private)


#### class `ULiveLinkOpenTrackIORole`  
`class ULiveLinkOpenTrackIORole : public ULiveLinkLensRole`  
_L13-27_
- reflection: `UCLASS(BlueprintType, meta = (DisplayName = "OpenTrackIO Role"))`
- inherits: `ULiveLinkLensRole`
- desc: Role associated with OpenTrackIO data
- L19 _public prototype_ `virtual UScriptStruct* GetStaticDataStruct() const override;`
- L20 _public prototype_ `virtual UScriptStruct* GetFrameDataStruct() const override;`
- L21 _public prototype_ `virtual UScriptStruct* GetBlueprintDataStruct() const override;`
- L23 _public prototype_ `virtual bool InitializeBlueprintData(const FLiveLinkSubjectFrameData& InSourceData, FLiveLinkBlueprintDataStruct& OutBlueprintData) const override;`
- L25 _public prototype_ `virtual FText GetDisplayName() const override;`

### `Plugins/VirtualProduction/LiveLinkOpenTrackIO/Source/LiveLinkOpenTrackIO/Private/LiveLinkOpenTrackIOSource.h` (Private)


#### enum `ELiveLinkOpenTrackIOState`  
`enum class ELiveLinkOpenTrackIOState : uint8`  
_L34-50_
- L37 _public enumerator_ `NotStarted = 0` — Default state on source initialization.
- L40 _public enumerator_ `EndpointsReady` — We have parsed the endpoints data from the source settings and will prepare to open receiving connections
- L43 _public enumerator_ `Receiving` — Sockets have been opened and we are listening for data.
- L46 _public enumerator_ `ResetRequested` — The user has changed endpoints or user requested a socket reset.
- L49 _public enumerator_ `ShutDown` — Final state

#### class `FLiveLinkOpenTrackIOSource`  
`class FLiveLinkOpenTrackIOSource : public ILiveLinkSource, public TSharedFromThis<FLiveLinkOpenTrackIOSource>`  
_L52-188_
- inherits: `ILiveLinkSource,TSharedFromThis<FLiveLinkOpenTrackIOSource>`
- L56 _public prototype_ `FLiveLinkOpenTrackIOSource(FLiveLinkOpenTrackIOConnectionSettings ConnectionSettings);`
- L58 _public prototype_ `virtual ~FLiveLinkOpenTrackIOSource();`
- L61 _public prototype_ `virtual void ReceiveClient(ILiveLinkClient* InClient, FGuid InSourceGuid) override;`
- L62 _public prototype_ `virtual void InitializeSettings(ULiveLinkSourceSettings* Settings) override;`
- L64 _public prototype_ `virtual bool IsSourceStillValid() const override;`
- L66 _public prototype_ `virtual bool RequestSourceShutdown() override;`
- L68 _public prototype_ `virtual void Update() override;`
- L70 _public function_ `virtual FText GetSourceType() const override`
- L71 _public function_ `virtual FText GetSourceMachineName() const override`
- L72 _public function_ `virtual FText GetSourceStatus() const override`
- L74 _public function_ `virtual TSubclassOf<ULiveLinkSourceSettings> GetSettingsClass() const override`
- L80 _private prototype_ `bool OpenSockets();` — Create listening sockets for OpenTrack channels. Returns true if socket handles were successfully opened and receivers started.
- L83 _private prototype_ `bool OpenMulticastSocket();` — Create Multicast socket (called by OpenSockets)
- L86 _private prototype_ `bool OpenUnicastSocket();` — Create Uniicast socket (called by OpenSockets)
- L89 _private prototype_ `void CloseSockets();` — Close any open sockets.
- L92 _private prototype_ `void StopUdpReceivers();` — Stop the udp receivers, but does not destroy the sockets.
- L95 _private prototype_ `bool ParseEndpointFromSourceSettings();` — Read the source settings and assign the endpoint addresses. Returns true if the endpoints are ready
- L98 _private prototype_ `void HandleInboundData(const TSharedPtr<FArrayReader, ESPMode::ThreadSafe>& InData, const FIPv4Endpoint& InSender);` — Delegate for handling inbound segments.
- L101 _private prototype_ `void PushDataToLiveLink_AnyThread(const FLiveLinkOpenTrackIODatagramHeader& Header, FLiveLinkOpenTrackIOData InData);` — Copy the open track data into Live Link equivalent data. This will establish any static data if the InData specifies it.
- L104 _private prototype_ `void RemoveAllTransformSubjects(FLiveLinkOpenTrackIOCache* Cache);` — Remove all transform subjects from the LL source.
- L107 _private prototype_ `void ConditionallyPushLiveLinkTransformData(FLiveLinkOpenTrackIOCache* Cache, const FLiveLinkOpenTrackIOData& InData);` — Push transform data to Live Link if the user has asked for it in the SavedSourceSettings. New subjects will get created automatically.
- L110 _private function_ `inline void SetConnectionState(const ELiveLinkOpenTrackIOState InConnectionState)` — Sets connection state
- L117 _private prototype_ `void OnEnginePreExit();` — Called when FCoreDelegates::OnEnginePreExit fires
- L131 _private typedef_ `using FOpenTrackIOCachePtr = TPimplPtr<FLiveLinkOpenTrackIOCache>;` — Pointer to implementation of our OpenTrackIO cache so that we can track camera and lens information.
- L134 _private member_ `TMap<FIPv4Endpoint, FOpenTrackIOHeaderWithPayload> WorkingPayloads;` — Keep track of payloads per endpoint. This is used to keep track of segmented data per endpoint.
- L137 _private member_ `TMap<FString, FOpenTrackIOCachePtr> OpenTrackIOCacheMap;` — Cache of data relevant to open track protocol. It is keyed by the sourceId. We can support multiple source ids
- L140 _private member_ `ILiveLinkClient* Client = nullptr;` — The LiveLink client provided via ReceiveClient
- L143 _private member_ `FGuid SourceGuid;` — Our identifier in LiveLink
- L146 _private member_ `FText SourceType;` — Text objects that are reflected back in the Live Link UI.
- L147 _private member_ `FText SourceMachineName;`
- L148 _private member_ `FText SourceStatus;`
- L151 _private member_ `TObjectPtr<ULiveLinkOpenTrackIOSourceSettings> SavedSourceSettings;` — Handle the source settings for this source. The IP addresses are stored so that they can be changed after source creation.
- L154 _private member_ `FLiveLinkOpenTrackIOConnectionSettings ConnectionSettings;` — Holds the connection settings to use for this source. This is established when the source is first created.
- L157 _private member_ `FSocket* MulticastSocket = nullptr;` — Holds the multicast socket.
- L160 _private member_ `TUniquePtr<FUdpSocketReceiver> UnicastReceiver;` — Holds the unicast socket receiver.
- L163 _private member_ `TUniquePtr<FUdpSocketReceiver> MulticastReceiver;` — Holds the multicast socket receiver.
- L166 _private member_ `FSocket* UnicastSocket = nullptr;` — Holds the unicast socket.
- L169 _private member_ `FIPv4Endpoint UnicastEndpoint;` — Holds the local endpoint to receive messages.
- L172 _private member_ `FIPv4Endpoint MulticastEndpoint;` — Multicast Endpoint endpoint to receive messages.
- L175 _private member_ `ELiveLinkOpenTrackIOState ConnectionState = ELiveLinkOpenTrackIOState::NotStarted;` — State of the state machine. Only write/read in the game thread
- L178 _private member_ `FIPv4Endpoint LastSender_RunnableThread;` — Cached sender ip address, used to update the UI
- L181 _private member_ `std::atomic<double> LastDataReadTime = 0;` — Used to detect staleness in the source
- L184 _private member_ `bool bShutdownRequested = false;` — Tells the state machine that a shutdown of the source has been requested. One time only use, will never get cleared.
- L187 _private member_ `bool bResetRequested = false;` — Tells the state machine that the connection should be reset, probably because a relevant setting has been changed.

#### struct `FLiveLinkOpenTrackIOSource::FInboundMessage`  
`struct FInboundMessage`  
_L121-128_
- L124 _public member_ `TSharedPtr<FArrayReader, ESPMode::ThreadSafe> Data;` — Holds the segment data.
- L127 _public member_ `FIPv4Endpoint Sender;` — Holds the sender's network endpoint.

### `Plugins/VirtualProduction/LiveLinkOpenTrackIO/Source/LiveLinkOpenTrackIO/Private/LiveLinkOpenTrackIOSourceFactory.h` (Private)


#### class `ULiveLinkOpenTrackIOSourceFactory`  
`class ULiveLinkOpenTrackIOSourceFactory : public ULiveLinkSourceFactory`  
_L10-24_
- reflection: `UCLASS()`
- inherits: `ULiveLinkSourceFactory`
- L15 _public prototype_ `virtual FText GetSourceDisplayName() const override;`
- L16 _public prototype_ `virtual FText GetSourceTooltip() const override;`
- L18 _public function_ `virtual EMenuType GetMenuType() const override`
- L19 _public prototype_ `virtual TSharedPtr<SWidget> BuildCreationPanel(FOnLiveLinkSourceCreated OnLiveLinkSourceCreated) const override;`
- L20 _public prototype_ `virtual TSharedPtr<ILiveLinkSource> CreateSource(const FString& ConnectionString) const override;`
- L23 _private prototype_ `void CreateSourceFromSettings(FLiveLinkOpenTrackIOConnectionSettings ConnectionSettings, FOnLiveLinkSourceCreated OnSourceCreated) const;`

### `Plugins/VirtualProduction/LiveLinkOpenTrackIO/Source/LiveLinkOpenTrackIO/Private/LiveLinkOpenTrackIOTranscoder.h` (Private)


#### struct `FLiveLinkOpenTrackIOCache`  
`struct FLiveLinkOpenTrackIOCache`  
_L12-69_
- L15 _public member_ `FName SubjectName;` — Last known Subject Name
- L18 _public member_ `TSet<FName> TransformSubjectNames;` — List of transform subject names known.
- L21 _public member_ `FLiveLinkStaticDataStruct StaticData;` — Live Link Static Data, used to detect changes
- L24 _public member_ `FLiveLinkOpenTrackIOStaticCamera StaticCamera;` — OpenTrackIO static camera data (make, model, etc.)
- L27 _public member_ `TOptional<FLiveLinkOpenTrackIOStaticLens> StaticLens;` — OpenTrackIO static lens data
- L30 _public member_ `bool bSendTransformsAsSubjects = false;` — Cached state of exposing the transforms as subjects.
- L36 _public prototype_ `bool IsPacketInSequence(uint16 SequenceNumber, const FFrameRate& InRate) const;` — Check the given sequence number and return true if it is the expected number. Sequence numbers should be incrementing modulo UINT16_MAX.  This also accounts for delays in transmission based on sample rate provided by the first inbound packets.
- L41 _public function_ `void UpdateLastKnownSequenceNumber(uint16 SequenceNumber)` — Caches the processed sequence number so that it can be compared when the next packet is received.
- L52 _public prototype_ `FName GetSubjectNameFromData(const FString& Prefix, const FLiveLinkOpenTrackIOData& Data);` — Constructs a subject name from the given data.
- L55 _public prototype_ `FName GetTransformName(const FLiveLinkOpenTrackIOTransform& InTransform);` — Constructs a subject name from the given data.
- L58 _public prototype_ `FLiveLinkStaticDataStruct MakeStaticData(const FLiveLinkOpenTrackIOData& StaticData, const bool bApplyXform);` — Create Live Link static data from the OpenTrackIO data
- L61 _public prototype_ `FLiveLinkFrameDataStruct MakeFrameData(const FLiveLinkOpenTrackIOData& Data, const bool bApplyXform);` — Create Live Link the per-frame data from the OpenTrackIO data
- L65 _private member_ `int32 ExpectedSequenceNumber = -1;` — Tracks the current sequence number for the source.
- L68 _private member_ `double LastDataReceiveTimeInSeconds = 0;` — Store the last time in FPlatformTime::Seconds() we received data from this source.

### `Plugins/VirtualProduction/LiveLinkOpenTrackIO/Source/LiveLinkOpenTrackIO/Private/LiveLinkOpenTrackIOTypes.h` (Private)


#### struct `FOpenTrackIOOptionalFloat`  
`struct FOpenTrackIOOptionalFloat`  
_L22-85_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Optional Float (OpenTrackIO)"))`
- desc: Contains a float and bIsSet flag, mimicking TOptional, to be exposed in Blueprints. The intention is that it is clear to the user if the value contained has been set by the sender or not.
- L28 _public member_ `bool bIsSet = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Optional")` — Whether Value has been set or not
- L32 _public member_ `float Value = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Optional", meta = (EditCondition = "bIsSet"))` — The actual float value (only valid when bIsSet == true)
- L37 _public function_ `bool operator==(const FOpenTrackIOOptionalFloat& Other) const` — Equals Operator
- L55 _public function_ `bool operator!=(const FOpenTrackIOOptionalFloat& Other) const` — Different Than operator
- L61 _public function_ `bool IsSet() const` — Check if Value has been set. Mimicks IsSet() in TOptional
- L67 _public function_ `float GetValue() const` — Gets the set Value. Mimicks GetValue() in TOptional
- L73 _public function_ `void SetValue(float InValue)` — Sets the Value of this container
- L80 _public function_ `void Reset()` — Clears the bIsSet flag. Mimicks Reset() in TOptional

#### struct `FOpenTrackIOOptionalInt32`  
`struct FOpenTrackIOOptionalInt32`  
_L94-157_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Optional Int32 (OpenTrackIO)"))`
- desc: Contains an int32 and bIsSet flag, mimicking TOptional, to be exposed in Blueprints. The intention is that it is clear to the user if the value contained has been set by the sender or not.
- L100 _public member_ `bool bIsSet = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Optional")` — Whether Value has been set or not
- L104 _public member_ `int32 Value = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Optional", meta = (EditCondition = "bIsSet"))` — The actual int32 value (only valid when bIsSet == true)
- L109 _public function_ `bool operator==(const FOpenTrackIOOptionalInt32& Other) const` — Equals Operator
- L127 _public function_ `bool operator!=(const FOpenTrackIOOptionalInt32& Other) const` — Different Than operator
- L133 _public function_ `bool IsSet() const` — Check if Value has been set. Mimicks IsSet() in TOptional
- L139 _public function_ `int32 GetValue() const` — Gets the set Value. Mimicks GetValue() in TOptional
- L145 _public function_ `void SetValue(int32 InValue)` — Sets the Value of this container
- L152 _public function_ `void Reset()` — Clears the bIsSet flag. Mimicks Reset() in TOptional

#### struct `FOpenTrackIOOptionalDouble`  
`struct FOpenTrackIOOptionalDouble`  
_L166-229_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Optional Double (OpenTrackIO)"))`
- desc: Contains a double and bIsSet flag, mimicking TOptional, to be exposed in Blueprints. The intention is that it is clear to the user if the value contained has been set by the sender or not.
- L172 _public member_ `bool bIsSet = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Optional")` — Whether Value has been set or not
- L176 _public member_ `double Value = 0.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Optional", meta = (EditCondition = "bIsSet"))` — The actual double value (only valid when bIsSet == true)
- L181 _public function_ `bool operator==(const FOpenTrackIOOptionalDouble& Other) const` — Equals Operator
- L199 _public function_ `bool operator!=(const FOpenTrackIOOptionalDouble& Other) const` — Different Than operator
- L205 _public function_ `bool IsSet() const` — Check if Value has been set. Mimicks IsSet() in TOptional
- L211 _public function_ `double GetValue() const` — Gets the set Value. Mimicks GetValue() in TOptional
- L217 _public function_ `void SetValue(double InValue)` — Sets the Value of this container
- L224 _public function_ `void Reset()` — Clears the bIsSet flag. Mimicks Reset() in TOptional

#### struct `FLiveLinkOpenTrackIOFrameRate`  
`struct FLiveLinkOpenTrackIOFrameRate`  
_L237-263_
- reflection: `USTRUCT(BlueprintType)`
- desc: Represents frame rate type from OpenTrack I/O. Value is represented in hertz using an fractional representation Numerator / Denominator. The default value is 24 / 1 or 24 cycles per second.
- L242 _public function_ `bool IsDefault() const` — Returns true if the struct is equivalent to the default struct values.
- L248 _public prototype_ `bool operator==(const FLiveLinkOpenTrackIOFrameRate&) const = default;`
- L249 _public prototype_ `bool operator!=(const FLiveLinkOpenTrackIOFrameRate&) const = default;`
- L251 _public function_ `FFrameRate GetFrameRate() const`
- L258 _public member_ `int32 Num = 24;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — Numerator of the frame rate value.
- L262 _public member_ `int32 Denom = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — Denominator of the frame rate value.

#### struct `FLiveLinkOpenTrackIOSensorDimensions`  
`struct FLiveLinkOpenTrackIOSensorDimensions`  
_L310-329_
- reflection: `USTRUCT(BlueprintType)`
- desc: Height and width of the active area of the camera sensor in millimeters
- L315 _public function_ `bool IsDefault() const` — Returns true if the struct is equivalent to the default struct values.
- L321 _public prototype_ `bool operator==(const FLiveLinkOpenTrackIOSensorDimensions&) const = default;`
- L322 _public prototype_ `bool operator!=(const FLiveLinkOpenTrackIOSensorDimensions&) const = default;`
- L325 _public member_ `FOpenTrackIOOptionalFloat Height;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")`
- L328 _public member_ `FOpenTrackIOOptionalFloat Width;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")`

#### struct `FLiveLinkOpenTrackIOSensorResolution`  
`struct FLiveLinkOpenTrackIOSensorResolution`  
_L335-354_
- reflection: `USTRUCT(BlueprintType)`
- desc: Photosite resolution of the active area of the camera sensor in pixels
- L340 _public function_ `bool IsDefault() const` — Returns true if the struct is equivalent to the default struct values.
- L346 _public prototype_ `bool operator==(const FLiveLinkOpenTrackIOSensorResolution&) const = default;`
- L347 _public prototype_ `bool operator!=(const FLiveLinkOpenTrackIOSensorResolution&) const = default;`
- L350 _public member_ `int32 Height = 1920;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")`
- L353 _public member_ `int32 Width = 1080;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")`

#### struct `FLiveLinkOpenTrackIOAnamorphicSqueeze`  
`struct FLiveLinkOpenTrackIOAnamorphicSqueeze`  
_L362-381_
- reflection: `USTRUCT(BlueprintType)`
- desc: Nominal ratio of height to width of the image of an axis-aligned square captured by the camera sensor. It can be used to de-squeeze images but is not however an exact number over the entire captured area due to a lens’ intrinsic analog nature.
- L367 _public function_ `bool IsDefault() const` — Returns true if the struct is equivalent to the default struct values.
- L373 _public prototype_ `bool operator==(const FLiveLinkOpenTrackIOAnamorphicSqueeze&) const = default;`
- L374 _public prototype_ `bool operator!=(const FLiveLinkOpenTrackIOAnamorphicSqueeze&) const = default;`
- L377 _public member_ `int32 Num = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")`
- L380 _public member_ `int32 Denom = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")`

#### struct `FLiveLinkOpenTrackIOStaticCamera`  
`struct FLiveLinkOpenTrackIOStaticCamera`  
_L384-475_
- reflection: `USTRUCT(BlueprintType)`
- L389 _public function_ `bool IsDefault() const` — Returns true if the struct is equivalent to the default struct values.
- L395 _public function_ `bool operator==(const FLiveLinkOpenTrackIOStaticCamera& Other) const`
- L404 _public function_ `bool operator!=(const FLiveLinkOpenTrackIOStaticCamera& Other) const`
- L410 _public function_ `bool IsValid() const` — If the provided static camera specifies the correct properties to be considered valid.
- L415 _public function_ `void UpdateStaticData(const FLiveLinkOpenTrackIOStaticCamera& Other)`
- L424 _public member_ `FLiveLinkOpenTrackIOFrameRate CaptureFrameRate;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — Object representing the capture rate.
- L428 _public member_ `FLiveLinkOpenTrackIOSensorDimensions ActiveSensorPhysicalDimensions;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — Object representing the sensor dimensions.
- L432 _public member_ `FLiveLinkOpenTrackIOSensorResolution ActiveSensorResolution;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — Object representing the sensor resolution.
- L436 _public member_ `FString Make;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — Non-blank string naming camera manufacturer.
- L440 _public member_ `FString Model;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — Non-blank string naming camera model.
- L444 _public member_ `FString SerialNumber;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — Non-blank string for camera serial number.
- L448 _public member_ `FString FirmwareVersion;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — Non-blank string identifying camera firmware version
- L452 _public member_ `FString Label;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — Non-blank string containing user-determined camera identifier
- L456 _public member_ `FLiveLinkOpenTrackIOAnamorphicSqueeze AnamorphicSqueeze;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — Anamorphic squeeze ratio
- L460 _public member_ `int32 IsoSpeed = 400;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — Arithmetic ISO scale as defined in ISO 12232
- L467 _public member_ `FString FdlLink;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — URN identifying the ASC Framing Decision List used by the camera. Pattern:  ^urn:uuid:[0-9a-f]{8}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{12}$
- L474 _public member_ `float ShutterAngle = 180.0;` — `UPROPERTY(meta = (ClampMin = "0.0", ClampMax = "360.0"))` — Shutter speed as a fraction of the capture frame rate. The shutter speed (in units of 1/s) is equal to the value of the parameter divided by 360 times the capture frame rate.

#### struct `FLiveLinkOpenTrackIOStaticLens`  
`struct FLiveLinkOpenTrackIOStaticLens`  
_L478-543_
- reflection: `USTRUCT(BlueprintType)`
- L483 _public function_ `bool IsDefault() const` — Returns true if the struct is equivalent to the default struct values.
- L489 _public prototype_ `bool operator==(const FLiveLinkOpenTrackIOStaticLens&) const = default;`
- L490 _public prototype_ `bool operator!=(const FLiveLinkOpenTrackIOStaticLens&) const = default;`
- L493 _public function_ `bool IsValid() const` — If the provided static lens specifies the correct properties to be considered valid.
- L498 _public function_ `void UpdateStaticData(const FLiveLinkOpenTrackIOStaticLens&)`
- L509 _public member_ `float DistortionOverscanMax = 1.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — Static maximum overscan factor on lens distortion. This is an alternative to providing dynamic overscan values each frame. Note it should be the maximum of both projection-matrix-based and field-of-view-based rendering as per the OpenLensIO documentation.
- L518 _public member_ `float UndistortionOverscanMax = 1.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — Static maximum overscan factor on lens undistortion. This is an alternative to providing dynamic overscan values each frame. Note it should bethe maximum of both projection-matrix-based and field-of-view-based rendering as per the OpenLensIO documentation.
- L522 _public member_ `FString Make;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — Non-blank string naming lens manufacturer
- L526 _public member_ `FString Model;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — Non-blank string identifying lens model
- L530 _public member_ `FString SerialNumber;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — Non-blank string uniquely identifying the lens
- L534 _public member_ `FString FirmwareVersion;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — Non-blank string identifying lens firmware version
- L538 _public member_ `float NominalFocalLength = 50;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — Nominal focal length of the lens. The number printed on the side of a prime lens, e.g. 50 mm, and undefined in the case of a zoom lens.
- L542 _public member_ `TArray<FString> CalibrationHistory;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — List of free strings that describe the history of calibrations of the lens.

#### struct `FLiveLinkOpenTrackIOStaticTracker`  
`struct FLiveLinkOpenTrackIOStaticTracker`  
_L546-581_
- reflection: `USTRUCT(BlueprintType)`
- L551 _public function_ `bool IsDefault() const` — Returns true if the struct is equivalent to the default struct values.
- L557 _public prototype_ `bool operator==(const FLiveLinkOpenTrackIOStaticTracker&) const = default;`
- L558 _public prototype_ `bool operator!=(const FLiveLinkOpenTrackIOStaticTracker&) const = default;`
- L561 _public function_ `bool IsValid() const` — If the provided static lens specifies the correct properties to be considered valid.
- L568 _public member_ `FString Make;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — Non-blank string naming tracking device manufacturer
- L572 _public member_ `FString Model;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — Non-blank string identifying tracking device model
- L576 _public member_ `FString SerialNumber;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — Non-blank string uniquely identifying the tracking device
- L580 _public member_ `FString FirmwareVersion;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — Non-blank string identifying tracking device firmware version

#### struct `FLiveLinkOpenTrackIOStaticDuration`  
`struct FLiveLinkOpenTrackIOStaticDuration`  
_L584-603_
- reflection: `USTRUCT(BlueprintType)`
- L589 _public function_ `bool IsDefault() const` — Returns true if the struct is equivalent to the default struct values.
- L595 _public prototype_ `bool operator==(const FLiveLinkOpenTrackIOStaticDuration&) const = default;`
- L596 _public prototype_ `bool operator!=(const FLiveLinkOpenTrackIOStaticDuration&) const = default;`
- L599 _public member_ `int32 Num = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")`
- L602 _public member_ `int32 Denom = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")`

#### struct `FLiveLinkOpenTrackIOStatics`  
`struct FLiveLinkOpenTrackIOStatics`  
_L609-634_
- reflection: `USTRUCT(BlueprintType)`
- desc: Static data from a parsed OpenTrackIO datagram. Per the spec this will be sent periodically from the source.
- L614 _public function_ `bool IsDefault() const` — Returns true if the struct is equivalent to the default struct values.
- L620 _public prototype_ `bool operator==(const FLiveLinkOpenTrackIOStatics&) const = default;`
- L621 _public prototype_ `bool operator!=(const FLiveLinkOpenTrackIOStatics&) const = default;`
- L624 _public member_ `FLiveLinkOpenTrackIOStaticDuration Duration;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")`
- L627 _public member_ `FLiveLinkOpenTrackIOStaticCamera Camera;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")`
- L630 _public member_ `FLiveLinkOpenTrackIOStaticLens Lens;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")`
- L633 _public member_ `FLiveLinkOpenTrackIOStaticTracker Tracker;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")`

#### struct `FLiveLinkOpenTrackIOTracker`  
`struct FLiveLinkOpenTrackIOTracker`  
_L637-666_
- reflection: `USTRUCT(BlueprintType)`
- L642 _public function_ `bool IsDefault() const` — Returns true if the struct is equivalent to the default struct values.
- L648 _public prototype_ `bool operator==(const FLiveLinkOpenTrackIOTracker&) const = default;`
- L649 _public prototype_ `bool operator!=(const FLiveLinkOpenTrackIOTracker&) const = default;`
- L653 _public member_ `FString Notes;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — Non-blank string containing notes about tracking system
- L657 _public member_ `bool Recording = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — Boolean indicating whether tracking system is recording data.
- L661 _public member_ `FString Slate;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — Non-blank string describing the recording slate
- L665 _public member_ `FString Status;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — Non-blank string describing status of tracking system

#### struct `FLiveLinkOpenTrackIOTimestamp`  
`struct FLiveLinkOpenTrackIOTimestamp`  
_L676-697_
- reflection: `USTRUCT(BlueprintType)`
- desc: Representation of a OpenTrackIO Timestamp. The timestamp comprises a 48-bit unsigned integer (seconds), a 32-bit unsigned integer (nanoseconds). We use 64-bit unsigned values for storing seconds.
- L681 _public function_ `bool IsDefault() const` — Returns true if the struct is equivalent to the default struct values.
- L687 _public prototype_ `bool operator==(const FLiveLinkOpenTrackIOTimestamp&) const = default;`
- L688 _public prototype_ `bool operator!=(const FLiveLinkOpenTrackIOTimestamp&) const = default;`
- L692 _public member_ `int64 Seconds = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — Although the schema specifies a 48 bit number. We allocate a full 64 bit integer here to store it.
- L696 _public member_ `int32 Nanoseconds = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — A 32-bit unsigned number for nanoseconds

#### struct `FLiveLinkOpenTrackIOSynchronizationOffsets`  
`struct FLiveLinkOpenTrackIOSynchronizationOffsets`  
_L700-722_
- reflection: `USTRUCT(BlueprintType)`
- L705 _public function_ `bool IsDefault() const` — Returns true if the struct is equivalent to the default struct values.
- L711 _public prototype_ `bool operator==(const FLiveLinkOpenTrackIOSynchronizationOffsets&) const = default;`
- L712 _public prototype_ `bool operator!=(const FLiveLinkOpenTrackIOSynchronizationOffsets&) const = default;`
- L715 _public member_ `double Translation = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")`
- L718 _public member_ `double Rotation = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")`
- L721 _public member_ `double LensEncoders = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")`

#### struct `FLiveLinkOpenTrackIO_PTPLeaderPriorities`  
`struct FLiveLinkOpenTrackIO_PTPLeaderPriorities`  
_L725-744_
- reflection: `USTRUCT(BlueprintType)`
- L730 _public function_ `bool IsDefault() const` — Returns true if the struct is equivalent to the default struct values.
- L736 _public prototype_ `bool operator==(const FLiveLinkOpenTrackIO_PTPLeaderPriorities&) const = default;`
- L737 _public prototype_ `bool operator!=(const FLiveLinkOpenTrackIO_PTPLeaderPriorities&) const = default;`
- L740 _public member_ `uint8 Priority1 = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")`
- L743 _public member_ `uint8 Priority2 = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")`

#### struct `FLiveLinkOpenTrackIO_PTP`  
`struct FLiveLinkOpenTrackIO_PTP`  
_L747-792_
- reflection: `USTRUCT(BlueprintType)`
- L752 _public function_ `bool IsDefault() const` — Returns true if the struct is equivalent to the default struct values.
- L758 _public prototype_ `bool operator==(const FLiveLinkOpenTrackIO_PTP&) const = default;`
- L759 _public prototype_ `bool operator!=(const FLiveLinkOpenTrackIO_PTP&) const = default;`
- L763 _public member_ `FString Profile = TEXT("SMP` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — PTP Profile: Can be one the following values [IEEE Std 1588-2019, IEEE Std 802.1AS-2020, SMPTE ST2059-2:2021]
- L766 _public member_ `int8 Domain = 0;` — `UPROPERTY(meta = (ClampMin = "0"))`
- L774 _public member_ `FString LeaderIdentity;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — PTP Leader identity follows the pattern: (?:^[0-9a-f]{2}(?::[0-9a-f]{2}){5}$)|(?:^[0-9a-f]{2}(?:-[0-9a-f]{2}){5}$)
- L778 _public member_ `FLiveLinkOpenTrackIO_PTPLeaderPriorities LeaderPriorities;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — Data structure for PTP synchronization priorities
- L781 _public member_ `double LeaderAccuracy = 0.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")`
- L785 _public member_ `FString LeaderTimeSource = TEXT("NTP` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — Enum string property [GNSS, Atomic clock, NTP]
- L788 _public member_ `double MeanPathDelay = 0.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")`
- L791 _public member_ `int32 Vlan = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")`

#### struct `FLiveLinkOpenTrackIOSynchronization`  
`struct FLiveLinkOpenTrackIOSynchronization`  
_L850-883_
- reflection: `USTRUCT(BlueprintType)`
- desc: Object describing how the tracking device is synchronized for this sample. frequency: The frequency of a synchronization signal.This may differ from the sample frame rate for example in a genlocked tracking device. This is not required if the synchronization source is PTP or NTP. locked: Is the tracking device locked to the synchronization source offsets: Offsets in seconds between sync and sample. Critical for e.g. frame remapping, or when using different data sources for position/rotation and lens encoding present: Is the synchronization source present (a synchronization source can be present but not locked if frame rates differ) ptp: If the synchronization source is a PTP leader, then this object contains: - "profile": Specifies the PTP profile in use. This defines the operational rules and parameters for synchronization. For example "SMPTE ST2059-2:2021" for SMPTE 2110 based systems, or "IEEE Std 1588-2019" or "IEEE Std 802.1AS-2020" for industrial applications - "domain": Identifies the PTP domain the device belongs to. Devices in the same domain can synchronize with each other - "leaderIdentity": The unique identifier (usually MAC address) of the current PTP leader - "leaderPriorities": The priority values of the leader used in the Best Clock Algorithm (BMCA). Lower values indicate higher priority - "priority1": Static priority set by the administrator - "priority2": Dynamic priority based on the leader’s role or clock quality - "leaderAccuracy": The timing offset in se
- L855 _public function_ `bool IsDefault() const` — Returns true if the struct is equivalent to the default struct values.
- L861 _public prototype_ `bool operator==(const FLiveLinkOpenTrackIOSynchronization&) const = default;`
- L862 _public prototype_ `bool operator!=(const FLiveLinkOpenTrackIOSynchronization&) const = default;`
- L865 _public member_ `bool Locked = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")`
- L869 _public member_ `FString Source;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — Enum as string value can be "genlock", "videoIn", "ptp", ...
- L873 _public member_ `FLiveLinkOpenTrackIOFrameRate Frequency;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — Synchonization rate.
- L876 _public member_ `FLiveLinkOpenTrackIOSynchronizationOffsets Offsets;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")`
- L879 _public member_ `bool Present = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")`
- L882 _public member_ `FLiveLinkOpenTrackIO_PTP Ptp;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")`

#### struct `FLiveLinkOpenTrackIOTimecode`  
`struct FLiveLinkOpenTrackIOTimecode`  
_L896-947_
- reflection: `USTRUCT(BlueprintType)`
- desc: SMPTE timecode of the sample. Timecode is a standard for labeling individual frames of data in media systems and is useful for inter-frame synchronization. Frame rate is a rational number, allowing drop frame rates such as that colloquially called 29.97 to be represented exactly, as 30000/1001. The timecode frame rate may differ from the sample frequency. The zero-based sub-frame field allows for finer division of the frame, e.g. interlaced frames have two sub-frames, one per field.
- L901 _public function_ `bool IsDefault() const` — Returns true if the struct is equivalent to the default struct values.
- L907 _public prototype_ `bool operator==(const FLiveLinkOpenTrackIOTimecode&) const = default;`
- L908 _public prototype_ `bool operator!=(const FLiveLinkOpenTrackIOTimecode&) const = default;`
- L910 _public function_ `FQualifiedFrameTime GetQualifiedFrameTime() const`
- L927 _public member_ `int32 Hours = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")`
- L930 _public member_ `int32 Minutes = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")`
- L933 _public member_ `int32 Seconds = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")`
- L936 _public member_ `int32 Frames = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")`
- L939 _public member_ `FLiveLinkOpenTrackIOFrameRate FrameRate;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")`
- L942 _public member_ `int32 SubFrame = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")`
- L946 _public member_ `int32 SubframesPerFrame = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — Number of subframes per frame. 1 is the minimum

#### struct `FLiveLinkOpenTrackIOTiming`  
`struct FLiveLinkOpenTrackIOTiming`  
_L950-1002_
- reflection: `USTRUCT(BlueprintType)`
- L955 _public function_ `bool IsDefault() const` — Returns true if the struct is equivalent to the default struct values.
- L961 _public prototype_ `bool operator==(const FLiveLinkOpenTrackIOTiming&) const = default;`
- L962 _public prototype_ `bool operator!=(const FLiveLinkOpenTrackIOTiming&) const = default;`
- L970 _public member_ `FString Mode;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — Enumerated value indicating whether the sample transport mechanism provides inherent (’external’) timing, or whether the transport mechanism lacks inherent timing and so the sample must contain a PTP timestamp itself (’internal’) to carry timing information.
- L974 _public member_ `FLiveLinkOpenTrackIOTimestamp RecordedTimestamp;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — PTP timestamp of the data recording instant, provided for convenience during playback of e.g. pre-recorded tracking data.
- L982 _public member_ `FLiveLinkOpenTrackIOFrameRate SampleRate;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — Sample frame rate as a rational number. Drop frame rates such as 29.97 should be represented as e.g. 30000/1001. In a variable rate system this should be estimated from the last sample delta time.
- L989 _public member_ `FLiveLinkOpenTrackIOTimestamp SampleTimestamp;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — PTP timestamp of the data recording instant, provided for convenience during playback of e.g. pre-recorded tracking data. The timestamp comprises a 48-bit unsigned integer (seconds), a 32-bit unsigned integer (nanoseconds)
- L993 _public member_ `int32 SequenceNumber = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — Integer incrementing with each sample.
- L997 _public member_ `FLiveLinkOpenTrackIOSynchronization Synchronization;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — Synchronization object for the timing.
- L1001 _public member_ `FLiveLinkOpenTrackIOTimecode Timecode;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — SMTPE timecode of the sample.

#### struct `FLiveLinkOpenTrackIOLens_DistortionOffset`  
`struct FLiveLinkOpenTrackIOLens_DistortionOffset`  
_L1005-1029_
- reflection: `USTRUCT(BlueprintType)`
- L1010 _public function_ `bool IsDefault() const` — Returns true if the struct is equivalent to the default struct values.
- L1016 _public prototype_ `bool operator==(const FLiveLinkOpenTrackIOLens_DistortionOffset&) const = default;`
- L1017 _public prototype_ `bool operator!=(const FLiveLinkOpenTrackIOLens_DistortionOffset&) const = default;`
- L1019 _public function_ `FVector2D AsVector() const`
- L1025 _public member_ `float X = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")`
- L1028 _public member_ `float Y = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")`

#### struct `FLiveLinkOpenTrackIOLens_Encoders`  
`struct FLiveLinkOpenTrackIOLens_Encoders`  
_L1044-1066_
- reflection: `USTRUCT(BlueprintType)`
- desc: Encoders are represented in this way (as opposed to raw integer values) to ensure values remain independent of encoder resolution, minimum and maximum (at an acceptable loss of precision). These values are only relevant in lenses with end-stops that demarcate the 0 and 1 range. Value should be provided in the following directions (if known): Focus:   0=infinite     1=closest Iris:    0=open         1=closed Zoom:    0=wide angle   1=telephoto
- L1049 _public function_ `bool IsDefault() const` — Returns true if the struct is equivalent to the default struct values.
- L1055 _public prototype_ `bool operator==(const FLiveLinkOpenTrackIOLens_Encoders&) const = default;`
- L1056 _public prototype_ `bool operator!=(const FLiveLinkOpenTrackIOLens_Encoders&) const = default;`
- L1059 _public member_ `float Focus = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")`
- L1062 _public member_ `float Iris = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")`
- L1065 _public member_ `float Zoom = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")`

#### struct `FLiveLinkOpenTrackIOLens_RawEncoders`  
`struct FLiveLinkOpenTrackIOLens_RawEncoders`  
_L1075-1097_
- reflection: `USTRUCT(BlueprintType)`
- desc: Raw encoder values for focus, iris and zoom. These values are dependent on encoder resolution and before any homing / ranging has taken place.
- L1080 _public function_ `bool IsDefault() const` — Returns true if the struct is equivalent to the default struct values.
- L1086 _public prototype_ `bool operator==(const FLiveLinkOpenTrackIOLens_RawEncoders&) const = default;`
- L1087 _public prototype_ `bool operator!=(const FLiveLinkOpenTrackIOLens_RawEncoders&) const = default;`
- L1090 _public member_ `int32 Focus = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")`
- L1093 _public member_ `int32 Iris = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")`
- L1096 _public member_ `int32 Zoom = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")`

#### struct `FLiveLinkOpenTrackIOLens_ExposureFalloff`  
`struct FLiveLinkOpenTrackIOLens_ExposureFalloff`  
_L1103-1125_
- reflection: `USTRUCT(BlueprintType)`
- desc: Coefficients for calculating the exposure fall-off (vignetting) of a lens.
- L1108 _public function_ `bool IsDefault() const` — Returns true if the struct is equivalent to the default struct values.
- L1114 _public prototype_ `bool operator==(const FLiveLinkOpenTrackIOLens_ExposureFalloff&) const = default;`
- L1115 _public prototype_ `bool operator!=(const FLiveLinkOpenTrackIOLens_ExposureFalloff&) const = default;`
- L1118 _public member_ `float A1 = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")`
- L1121 _public member_ `float A2 = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")`
- L1124 _public member_ `float A3 = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")`

#### struct `FLiveLinkOpenTrackIOLens_DistortionCoeff`  
`struct FLiveLinkOpenTrackIOLens_DistortionCoeff`  
_L1128-1157_
- reflection: `USTRUCT(BlueprintType)`
- L1133 _public function_ `bool IsDefault() const` — Returns true if the struct is equivalent to the default struct values.
- L1139 _public prototype_ `bool operator==(const FLiveLinkOpenTrackIOLens_DistortionCoeff&) const = default;`
- L1140 _public prototype_ `bool operator!=(const FLiveLinkOpenTrackIOLens_DistortionCoeff&) const = default;`
- L1143 _public member_ `FName Model;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")`
- L1146 _public member_ `TArray<float> Radial;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")`
- L1149 _public member_ `TArray<float> Tangential;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")`
- L1152 _public member_ `float Overscan = 0.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")`
- L1156 _public member_ `TArray<float> Custom;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — This is not currently in the spec but it would simplify sending any set of unnamed parameters

#### struct `FLiveLinkOpenTrackIOLens`  
`struct FLiveLinkOpenTrackIOLens`  
_L1160-1240_
- reflection: `USTRUCT(BlueprintType)`
- L1165 _public function_ `bool IsDefault() const` — Returns true if the struct is equivalent to the default struct values.
- L1171 _public prototype_ `bool operator==(const FLiveLinkOpenTrackIOLens&) const = default;`
- L1172 _public prototype_ `bool operator!=(const FLiveLinkOpenTrackIOLens&) const = default;`
- L1180 _public member_ `TArray<float> Custom;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — This list provides optional additional custom coefficients that can extend the existing lens model. The meaning of and how these characteristics are to be applied to a virtual camera would require negotiation between a particular producer and consumer.
- L1189 _public member_ `TArray<FLiveLinkOpenTrackIOLens_DistortionCoeff> Distortion;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — A list of Distortion objects that each define the coefficients for calculating the distortion characteristics of a lens comprising radial distortion coefficients of the spherical distortion (k1-N) and (optionally) the tangential distortion (p1-N). The key ’model’ names the distortion model. Typical values for ’model’ include "Brown-Conrady D-U" when mapping distorted to undistorted coordinates, and "Brown-Conrady U-D" when mapping undistorted to undistorted coordinates. If not provided, the default model is "Brown-Conrady D-U".
- L1195 _public member_ `FLiveLinkOpenTrackIOLens_DistortionOffset DistortionOffset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — Offset in x and y of the centre of distortion of the virtual camera in millimeter
- L1199 _public member_ `FLiveLinkOpenTrackIOLens_Encoders Encoders;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — Normalised real numbers (0-1) for focus, iris and zoom
- L1209 _public member_ `float EntrancePupilOffset = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — Offset of the entrance pupil relative to the nominal imaging plane (positive if the entrance pupil is located on the side of the nominal imaging plane that is towards the object, and negative otherwise). Measured in meters as in a render engine it is often applied in the virtual camera’s transform chain.
- L1215 _public member_ `FLiveLinkOpenTrackIOLens_ExposureFalloff ExposureFalloff;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — Coefficients for calculating the exposure fall-off (vignetting) of a lens
- L1219 _public member_ `FOpenTrackIOOptionalFloat FStop;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — The linear f-number of the lens, equal to the focal length divided by the diameter of the entrance pupil.
- L1223 _public member_ `FOpenTrackIOOptionalFloat PinholeFocalLength;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — Distance between the pinhole and the image plane in the simple CGI pinhole camera model. (millimeters)
- L1227 _public member_ `FOpenTrackIOOptionalFloat FocusDistance;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — Focus distance/position of the lens in meters.
- L1231 _public member_ `FLiveLinkOpenTrackIOLens_DistortionOffset ProjectionOffset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — Offset in x and y of the centre of perspective projection of the virtual camera
- L1235 _public member_ `FLiveLinkOpenTrackIOLens_RawEncoders RawEncoders;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — Raw encoder values.
- L1239 _public member_ `FOpenTrackIOOptionalFloat TStop;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — T-stop: Linear t-number of the lens, equal to the F-number of the lens divided by the square root of the transmittance of the lens.

#### struct `FLiveLinkOpenTrackIOProtocol`  
`struct FLiveLinkOpenTrackIOProtocol`  
_L1247-1282_
- reflection: `USTRUCT(BlueprintType)`
- desc: Name of the protocol in which the sample is being employed, and version of that protocol
- L1251 _public function_ `FLiveLinkOpenTrackIOProtocol()`
- L1257 _public function_ `bool IsDefault() const` — Returns true if the struct is equivalent to the default struct values.
- L1263 _public prototype_ `bool operator==(const FLiveLinkOpenTrackIOProtocol&) const = default;`
- L1264 _public prototype_ `bool operator!=(const FLiveLinkOpenTrackIOProtocol&) const = default;`
- L1266 _public function_ `bool IsSupported() const`
- L1277 _public member_ `FString Name;` — `UPROPERTY(BlueprintReadOnly, Category = "OpenTrackIO")` — The name of the protocol. If you want to extract the full version string then use GetVersionString().
- L1281 _public member_ `TArray<int8> Version;` — `UPROPERTY()` — Three numbers that represent the protocol version.  This is not accessible by Blueprints because int8 is not supported.

#### class `ULiveLinkOpenTrackIOLibrary`  
`class ULiveLinkOpenTrackIOLibrary : public UBlueprintFunctionLibrary`  
_L1285-1300_
- reflection: `UCLASS(meta=(BlueprintThreadSafe, ScriptName = "OpenTrackIO"), MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- L1293 _public function_ `static FString GetVersionString(const FLiveLinkOpenTrackIOProtocol& Protocol)` — `UFUNCTION(BlueprintPure, Category = "OpenTrackIO")` — A string representing the protocol name plus version.

#### struct `FLiveLinkOpenTrackIOGlobalStage`  
`struct FLiveLinkOpenTrackIOGlobalStage`  
_L1309-1340_
- reflection: `USTRUCT(BlueprintType)`
- desc: Position of stage origin in global ENU and geodetic coordinates (E, N, U, lat0, lon0, h0). Note this may be dynamic if the stage is inside a moving vehicle. Units represented in meters.
- L1314 _public function_ `bool IsDefault() const` — Returns true if the struct is equivalent to the default struct values.
- L1320 _public prototype_ `bool operator==(const FLiveLinkOpenTrackIOGlobalStage&) const = default;`
- L1321 _public prototype_ `bool operator!=(const FLiveLinkOpenTrackIOGlobalStage&) const = default;`
- L1324 _public member_ `double E = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")`
- L1327 _public member_ `double N = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")`
- L1330 _public member_ `double U = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")`
- L1333 _public member_ `double Lat0 = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")`
- L1336 _public member_ `double Lon0 = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")`
- L1339 _public member_ `double H0 = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")`

#### struct `FLiveLinkOpenTrackIO_Rotator`  
`struct FLiveLinkOpenTrackIO_Rotator`  
_L1343-1365_
- reflection: `USTRUCT(BlueprintType)`
- L1348 _public function_ `bool IsDefault() const` — Returns true if the struct is equivalent to the default struct values.
- L1354 _public prototype_ `bool operator==(const FLiveLinkOpenTrackIO_Rotator&) const = default;`
- L1355 _public prototype_ `bool operator!=(const FLiveLinkOpenTrackIO_Rotator&) const = default;`
- L1358 _public member_ `double Pan = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")`
- L1361 _public member_ `double Tilt = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")`
- L1364 _public member_ `double Roll = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")`

#### struct `FLiveLinkOpenTrackIO_XYZ`  
`struct FLiveLinkOpenTrackIO_XYZ`  
_L1368-1396_
- reflection: `USTRUCT(BlueprintType)`
- L1372 _public prototype_ `FLiveLinkOpenTrackIO_XYZ() = default;`
- L1373 _public function_ `FLiveLinkOpenTrackIO_XYZ(double InX, double InY, double InZ) : X(InX), Y(InY), Z(InZ)`
- L1379 _public function_ `bool IsDefault() const` — Returns true if the struct is equivalent to the default struct values.
- L1385 _public prototype_ `bool operator==(const FLiveLinkOpenTrackIO_XYZ&) const = default;`
- L1386 _public prototype_ `bool operator!=(const FLiveLinkOpenTrackIO_XYZ&) const = default;`
- L1389 _public member_ `double X = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")`
- L1392 _public member_ `double Y = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")`
- L1395 _public member_ `double Z = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")`

#### struct `FLiveLinkOpenTrackIOTransform`  
`struct FLiveLinkOpenTrackIOTransform`  
_L1399-1428_
- reflection: `USTRUCT(BlueprintType)`
- L1404 _public function_ `bool IsDefault() const` — Returns true if the struct is equivalent to the default struct values.
- L1410 _public prototype_ `bool operator==(const FLiveLinkOpenTrackIOTransform&) const = default;`
- L1411 _public prototype_ `bool operator!=(const FLiveLinkOpenTrackIOTransform&) const = default;`
- L1415 _public member_ `FLiveLinkOpenTrackIO_XYZ Translation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — Translation part of a OpenTrackIO xform
- L1419 _public member_ `FLiveLinkOpenTrackIO_Rotator Rotation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — Rotation part of a OpenTrackIO xform
- L1423 _public member_ `FLiveLinkOpenTrackIO_XYZ Scale = FLiveLinkOpenTrackIO_XYZ(1,1,1);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — Scale part of a OpenTrackIO xform
- L1427 _public member_ `FString Id;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — OpenTrackIO identifier (can be empty)

#### struct `FLiveLinkOpenTrackIOCustomDataField`  
`struct FLiveLinkOpenTrackIOCustomDataField`  
_L1431-1452_
- reflection: `USTRUCT(BlueprintType)`
- L1436 _public function_ `bool IsDefault() const` — Returns true if the struct is equivalent to the default struct values.
- L1442 _public prototype_ `bool operator==(const FLiveLinkOpenTrackIOCustomDataField&) const = default;`
- L1443 _public prototype_ `bool operator!=(const FLiveLinkOpenTrackIOCustomDataField&) const = default;`
- L1447 _public member_ `FString Key;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — Meta data is inserted into Live Link Frame data using a Key, Value pair. This is the key part of that pair.
- L1451 _public member_ `FString Value;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — Meta data is inserted into Live Link Frame data using a Key, Value pair. This is the value part of that pair.

#### struct `FLiveLinkOpenTrackIOCustomData`  
`struct FLiveLinkOpenTrackIOCustomData`  
_L1455-1472_
- reflection: `USTRUCT(BlueprintType)`
- L1460 _public function_ `bool IsDefault() const` — Returns true if the struct is equivalent to the default struct values.
- L1466 _public prototype_ `bool operator==(const FLiveLinkOpenTrackIOCustomData&) const = default;`
- L1467 _public prototype_ `bool operator!=(const FLiveLinkOpenTrackIOCustomData&) const = default;`
- L1471 _public member_ `TArray<FLiveLinkOpenTrackIOCustomDataField> LiveLinkMetaData;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — A list of string based key/value pairs that can be read and applied to the Live Link data stream.

#### struct `FLiveLinkOpenTrackIOData`  
`struct FLiveLinkOpenTrackIOData`  
_L1481-1575_
- reflection: `USTRUCT(BlueprintType)`
- desc: Data from a parsed header that was read by other CBOR or JSON format. Schema can be found here: https://www.opentrackio.org/schema.json
- L1486 _public function_ `bool IsDefault() const` — Returns true if the struct is equivalent to the default struct values.
- L1492 _public prototype_ `bool operator==(const FLiveLinkOpenTrackIOData&) const = default;`
- L1493 _public prototype_ `bool operator!=(const FLiveLinkOpenTrackIOData&) const = default;`
- L1496 _public member_ `FLiveLinkOpenTrackIOStatics Static;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")`
- L1499 _public member_ `FLiveLinkOpenTrackIOTracker Tracker;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")`
- L1502 _public member_ `FLiveLinkOpenTrackIOTiming Timing;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")`
- L1505 _public member_ `FLiveLinkOpenTrackIOLens Lens;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")`
- L1508 _public member_ `FLiveLinkOpenTrackIOProtocol Protocol;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")`
- L1515 _public member_ `FString SampleId;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — URN serving as unique identifier of the sample in which data is being transported. Pattern -> ^urn:uuid:[0-9a-f]{8}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{12}$
- L1522 _public member_ `FString SourceId;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — URN serving as unique identifier of the source from which data is being transported. Pattern -> ^urn:uuid:[0-9a-f]{8}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{12}$
- L1530 _public member_ `int64 SourceNumber = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — Number that identifies the index of the stream from a source from which data is being transported. This is most important in the case where a source is producing multiple streams of samples.
- L1537 _public member_ `TArray<FString> RelatedSampleIds;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — List of sampleId properties of samples related to this sample. The existence of a sample with a given sampleId is not guaranteed.
- L1541 _public member_ `FLiveLinkOpenTrackIOGlobalStage GlobalStage;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — Position of stage origin in global ENU and geodetic coordinates
- L1554 _public member_ `TArray<FLiveLinkOpenTrackIOTransform> Transforms;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — A list of transforms. Transforms are composed in order with the last in the list representing the X,Y,Z in meters of camera sensor relative to stage origin. The Z axis points upwards and the coordinate system is right-handed. Y points in the forward camera direction (when pan, tilt and roll are zero). For example in an LED volume Y would point towards the centre of the LED wall and so X would point to camera-right. Rotation expressed as euler angles in degrees of the camera sensor relative to stage origin Rotations are intrinsic and are measured around the axes ZXY, commonly referred to as [pan, tilt, roll] Notes on Euler angles: Euler angles are human readable and unlike quarternions, provide the ability for cycles (with angles >360 or <0 degrees). Where a tracking system is providing the pose of a virtual camera, gimbal lock does not present the physical challenges of a robotic system. Conversion to and from quarternions is trivial with an acceptable loss of precision.
- L1574 _public member_ `FLiveLinkOpenTrackIOCustomData Custom;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenTrackIO")` — Typed property to allow users to add custom data to the incoming OpenTrackIO data. Our implementation only supports a field called LiveLinkMetaData. For example, "custom" : { "liveLinkMetaData" : [ { "key": "mykey", "value": "myvalue" }, { "key": "otherKey", "value": "otherValue" } ] }

#### Free symbols / members of external scopes

- L281 _namespace_ `namespace UE`
- L281 _namespace_ `namespace OpenTrackIO` (scope `UE`)
- L285 _function_ `template<CHasModelAndMake T> FName ConvertTypeToFName(const T& Type, const FString& Postfix)` (scope `UE::OpenTrackIO`)
- L1578 _namespace_ `namespace UE`
- L1578 _namespace_ `namespace OpenTrackIO` (scope `UE`)
- L1581 _variable_ `static const FName BrownConradyDU = TEXT("Bro` (scope `UE::OpenTrackIO`) — Brown-Conrady D-U, the default for nameless distortion model per opentrackio.org
- L1584 _variable_ `static const FName BrownConradyUD = TEXT("Bro` (scope `UE::OpenTrackIO`) — Brown-Conrady U-D distortion model
- L1587 _variable_ `static const FName OptionalTypeIsSetName = GET_MEMBER_NAME_CHECKED(FOpenTrackIOOptionalFloat, bIsSet);` (scope `UE::OpenTrackIO`) — Name of the FOpenTrackIOOptional "bIsSet" property
- L1590 _variable_ `static const FName OptionalTypeValueName = GET_MEMBER_NAME_CHECKED(FOpenTrackIOOptionalFloat, Value);` (scope `UE::OpenTrackIO`) — Name of the FOpenTrackIOOptional "Value" property
- L1595 _function_ `static bool IsOpenTrackIOOptionalType(const UScriptStruct* ScriptStruct)` (scope `UE::OpenTrackIO`) — Returns true if Struct is one of our custom optional USTRUCT types.

### `Plugins/VirtualProduction/LiveLinkOpenTrackIO/Source/LiveLinkOpenTrackIO/Private/OpenTrackIOCborStructDeserializerBackend.h` (Private)


#### class `FOpenTrackIOCborStructDeserializerBackend`  
`class FOpenTrackIOCborStructDeserializerBackend : public IStructDeserializerBackend`  
_L19-59_
- inherits: `IStructDeserializerBackend`
- desc: Implements a reader for UStruct deserialization using Cbor.
- L29 _public prototype_ `FOpenTrackIOCborStructDeserializerBackend(FArchive& Archive);` — Creates and initializes a new instance. @param Archive The archive to deserialize from.
- L30 _public prototype_ `virtual ~FOpenTrackIOCborStructDeserializerBackend();`
- L35 _public prototype_ `virtual const FString& GetCurrentPropertyName() const override;` — IStructDeserializerBackend interface
- L36 _public prototype_ `virtual FString GetDebugString() const override;`
- L37 _public prototype_ `virtual const FString& GetLastErrorMessage() const override;`
- L38 _public prototype_ `virtual bool GetNextToken(EStructDeserializerBackendTokens& OutToken) override;`
- L39 _public prototype_ `virtual bool ReadProperty(FProperty* Property, FProperty* Outer, void* Data, int32 ArrayIndex) override;`
- L40 _public prototype_ `virtual bool ReadPODArray(FArrayProperty* ArrayProperty, void* Data) override;`
- L41 _public prototype_ `virtual void SkipArray() override;`
- L42 _public prototype_ `virtual void SkipStructure() override;`
- L46 _private member_ `FCborReader CborReader;` — Holds the Cbor reader used for the actual reading of the archive.
- L49 _private member_ `FCborContext LastContext;` — Holds the last read Cbor Context.
- L52 _private member_ `FString LastMapKey;` — Holds the last map key.
- L55 _private member_ `int32 DeserializingByteArrayIndex = 0;` — The index of the next byte to copy from the CBOR byte stream into the corresponding TArray<uint8>/TArray<int8> property.
- L58 _private member_ `bool bDeserializingByteArray = false;` — Whether a TArray<uint8>/TArray<int8> property is being deserialized.

### `Plugins/VirtualProduction/LiveLinkOpenTrackIO/Source/LiveLinkOpenTrackIO/Private/SLiveLinkOpenTrackIOSourceFactory.h` (Private)


#### class `SLiveLinkOpenTrackIOSourceFactory`  
`class SLiveLinkOpenTrackIOSourceFactory : public SCompoundWidget`  
_L19-39_
- inherits: `SCompoundWidget`
- L21 _private function_ `SLATE_BEGIN_ARGS(SLiveLinkOpenTrackIOSourceFactory)`
- L23 _private prototype_ `SLATE_EVENT(FOnLiveLinkOpenTrackIOConnectionSettingsAccepted, OnConnectionSettingsAccepted) SLATE_END_ARGS() void Construct(const FArguments& Args);`
- L30 _private member_ `FLiveLinkOpenTrackIOConnectionSettings ConnectionSettings;`
- L33 _private member_ `TSharedPtr<FStructOnScope> StructOnScope;`
- L34 _private member_ `TSharedPtr<IStructureDetailsView> StructureDetailsView;`
- L37 _private prototype_ `FReply OnSettingsAccepted();`
- L38 _private member_ `FOnLiveLinkOpenTrackIOConnectionSettingsAccepted OnConnectionSettingsAccepted;`

#### Free symbols / members of external scopes

- L17 _delegate_ `DECLARE_DELEGATE_OneParam(FOnLiveLinkOpenTrackIOConnectionSettingsAccepted, FLiveLinkOpenTrackIOConnectionSettings);`
- L17 _prototype_ `DECLARE_DELEGATE_OneParam(FOnLiveLinkOpenTrackIOConnectionSettingsAccepted, FLiveLinkOpenTrackIOConnectionSettings);`

### `Plugins/VirtualProduction/LiveLinkOpenTrackIO/Source/LiveLinkOpenTrackIO/Public/LiveLinkOpenTrackIO.h` (Public)


#### class `FLiveLinkOpenTrackIOModule`  
`class FLiveLinkOpenTrackIOModule : public IModuleInterface`  
_L13-25_
- inherits: `IModuleInterface`
- desc: This module reads OpenTrackIO data from a UDP source.
- L17 _public function_ `static FLiveLinkOpenTrackIOModule& Get()`
- L23 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L24 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogLiveLinkOpenTrackIO, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogLiveLinkOpenTrackIO, Log, All);`

### `Plugins/VirtualProduction/LiveLinkOpenTrackIO/Source/LiveLinkOpenTrackIO/Public/LiveLinkOpenTrackIOSourceSettings.h` (Public)


#### enum `ELiveLinkOpenTrackIOTransformSubjects`  
`enum class ELiveLinkOpenTrackIOTransformSubjects`  
_L12-17_
- reflection: `UENUM()`
- L14 _public enumerator_ `NoTransformSubjects UMETA(ToolTip = "Do not generate transform subjects from OpenTrackIO data.")`
- L15 _public enumerator_ `EnableTransformSubjects UMETA(ToolTip = "Generate transform subjects and calculate final transform on the camera frame data.")`
- L16 _public enumerator_ `EnableTransformSubjectsNoCameraXForm UMETA(ToolTip = "Generate transform subjects and do not calculate final transform on the camera frame data.")`

#### class `ULiveLinkOpenTrackIOSourceSettings`  
`class ULiveLinkOpenTrackIOSourceSettings : public ULiveLinkSourceSettings`  
_L20-67_
- reflection: `UCLASS()`
- inherits: `ULiveLinkSourceSettings`
- L28 _public member_ `ELiveLinkOpenTrackIONetworkProtocol Protocol = ELiveLinkOpenTrackIONetworkProtocol::Multicast;` — `UPROPERTY(VisibleAnywhere, Category = Transport)` — Protocol being used for the connection.
- L39 _public member_ `FString MulticastEndpoint = TEXT("239` — `UPROPERTY(VisibleAnywhere, Category = Transport, meta = ( EditCondition = "Protocol == ELiveLinkOpenTrackIONetworkProtocol::Multicast", EditConditionHides ))` — The Multicast endpoint to receive packets on. The default value is 239.135.1.1:55555 per OpenTrackIO specifications.
- L50 _public member_ `FString UnicastEndpoint = TEXT("0.0` — `UPROPERTY(VisibleAnywhere, Category=Transport)` — The IP endpoint to listen to and send packets from. The format is IP_ADDRESS:PORT_NUMBER. 0.0.0.0:0 will bind to the default network adapter on Windows, and all available network adapters on other operating systems.
- L56 _public member_ `ELiveLinkOpenTrackIOTransformSubjects SubjectsPerTransform = ELiveLinkOpenTrackIOTransformSubjects::NoTransformSubjects;` — `UPROPERTY(EditAnywhere, Category=Subjects)` — Emit subjects for each transform included in the OpenTrackIO channel.
- L58 _public function_ `bool ShouldExtractTransformSubjects() const`
- L63 _public function_ `bool ShouldApplyXformToCamera() const`
