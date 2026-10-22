# Plugins / Concert

- module root: `Plugins/Developer/Concert/ConcertMain/Source/Concert`
- headers: 14; symbols: 677
- symbol kinds: class=18, delegate=21, enum=17, enumerator=60, function=70, macro=1, member=209, namespace=7, prototype=204, struct=64, typedef=6
- PublicDependencyModuleNames: ConcertTransport, Core, CoreUObject, Serialization
- PublicIncludePathModuleNames: ConcertTransport

### `Plugins/Developer/Concert/ConcertMain/Source/Concert/Private/ConcertLogger.h` (Private)


#### class `FConcertLogger`  
`class FConcertLogger : public IConcertTransportLogger`  
_L14-73_
- inherits: `IConcertTransportLogger`
- L19 _public prototype_ `static IConcertTransportLoggerRef CreateLogger(const FConcertEndpointContext& InOwnerContext, FLogListener LogListenerFunc);` — Factory function for use with FConcertTransportLoggerFactory
- L22 _public prototype_ `static void SetVerboseLogging(bool bInState);` — Static function to enable / disable verbose logging.
- L24 _public prototype_ `FConcertLogger(const FConcertEndpointContext& InOwnerContext, FLogListener LogListenerFunc);`
- L28 _public prototype_ `virtual bool IsLogging() const override;` — IConcertTransportLogger interface
- L29 _public prototype_ `virtual void StartLogging() override;`
- L30 _public prototype_ `virtual void StopLogging() override;`
- L31 _public prototype_ `virtual void FlushLog() override;`
- L32 _public prototype_ `virtual void LogTimeOut(const TSharedRef<IConcertMessage>& Message, const FGuid& EndpointId, const FDateTime& UtcNow) override;`
- L33 _public prototype_ `virtual void LogSendAck(const FConcertAckData& AckData, const FGuid& DestEndpoint) override;`
- L34 _public prototype_ `virtual void LogSendEndpointClosed(const FConcertEndpointClosedData& EndpointClosedData, const FGuid& DestEndpoint, const FDateTime& UtcNow) override;`
- L35 _public prototype_ `virtual void LogSendReliableHandshake(const FConcertReliableHandshakeData& ReliableHandshakeData, const FGuid& DestEndpoint, const FDateTime& UtcNow) override;`
- L36 _public prototype_ `virtual void LogReceiveReliableHandshake(const FConcertReliableHandshakeData& ReliableHandshakeData, const FGuid& DestEndpoint, const FDateTime& UtcNow) override;`
- L37 _public prototype_ `virtual void LogPublish(const TSharedRef<IConcertMessage>& Message) override;`
- L38 _public prototype_ `virtual void LogSend(const TSharedRef<IConcertMessage>& Message, const FGuid& DestEndpoint) override;`
- L39 _public prototype_ `virtual void LogMessageReceived(const FConcertMessageContext& ConcertContext, const FGuid& DestEndpoint) override;`
- L40 _public prototype_ `virtual void LogMessageQueued(const FConcertMessageContext& ConcertContext, const FGuid& DestEndpoint) override;`
- L41 _public prototype_ `virtual void LogMessageDiscarded(const FConcertMessageContext& ConcertContext, const FGuid& DestEndpoint, const EMessageDiscardedReason Reason) override;`
- L42 _public prototype_ `virtual void LogProcessEvent(const FConcertMessageContext& ConcertContext, const FGuid& DestEndpoint) override;`
- L43 _public prototype_ `virtual void LogProcessRequest(const FConcertMessageContext& ConcertContext, const FGuid& DestEndpoint) override;`
- L44 _public prototype_ `virtual void LogProcessResponse(const FConcertMessageContext& ConcertContext, const FGuid& DestEndpoint) override;`
- L45 _public prototype_ `virtual void LogProcessAck(const FConcertMessageContext& ConcertContext, const FGuid& DestEndpoint) override;`
- L46 _public prototype_ `virtual void LogRemoteEndpointDiscovery(const FConcertMessageContext& ConcertContext, const FGuid& DestEndpoint) override;`
- L47 _public prototype_ `virtual void LogRemoteEndpointTimeOut(const FGuid& EndpointId, const FDateTime& UtcNow) override;`
- L48 _public prototype_ `virtual void LogRemoteEndpointClosure(const FGuid& EndpointId, const FDateTime& UtcNow) override;`
- L51 _private prototype_ `void InternalStartLogging();`
- L52 _private prototype_ `void InternalStopLogging();`
- L53 _private prototype_ `void InternalFlushLog();`
- L55 _private prototype_ `void LogHeader();`
- L56 _private prototype_ `void LogEntry(FConcertLog& Log);`
- L59 _private member_ `bool bIsLogging;`
- L62 _private member_ `FConcertEndpointContext OwnerContext;`
- L65 _private member_ `FLogListener LogListenerFunc;` — Called after a log is processed
- L68 _private member_ `TQueue<FConcertLog, EQueueMode::Mpsc> LogQueue;` — Queue for unprocessed logs
- L71 _private member_ `mutable FCriticalSection CSVArchiveCS;` — Archive & CS used to write CSV file, if any
- L72 _private member_ `TUniquePtr<FArchive> CSVArchive;`

### `Plugins/Developer/Concert/ConcertMain/Source/Concert/Public/ConcertMessageData.h` (Public)


#### enum `EConcertServerFlags`  
`enum class EConcertServerFlags : uint8`  
_L18-23_
- reflection: `UENUM()`
- L20 _public enumerator_ `None = 0`
- L22 _public enumerator_ `IgnoreSessionRequirement = 1 << 0` — The server will ignore the session requirement when someone try to join a session

#### enum `EConcertSessionState`  
`enum class EConcertSessionState : uint8`  
_L28-35_
- reflection: `UENUM()`
- L31 _public enumerator_ `Normal = 0` — Session is a normal state and can be joined.
- L34 _public enumerator_ `Transient` — Session is in a transient state and cannot be joined.

#### enum `EConcertPayloadCompressionType`  
`enum class EConcertPayloadCompressionType : uint8`  
_L38-46_
- reflection: `UENUM()`
- L41 _public enumerator_ `None = 0` — The serialized data will not be compressed.
- L43 _public enumerator_ `Heuristic` — The serialized data will be compressed based on struct size.
- L45 _public enumerator_ `Always` — The serialized data will always be compressed.

#### enum `EConcertCompressionDetails`  
`enum class UE_DEPRECATED(5.8, "Use EConcertCompressionMethod instead.") EConcertCompressionDetails : uint8`  
_L49-65_
- reflection: `UENUM()`
- L52 _public enumerator_ `Uncompressed = 0` — The package data (the body) is written uncompressed.
- L55 _public enumerator_ `Compressed = 1 << 0` — The package data (the body) is written in a single compressed block. The value 1 represents the original format. Still used to store small packages.
- L58 _public enumerator_ `CompressWithOodle = 1 << 1` — If compression is enabled and this bit is set then oodle compression is used for the package data.
- L61 _public enumerator_ `CompressForSpeed = 1 << 2` — Compress for speed.
- L64 _public enumerator_ `CompressForSize = 1 << 3` — Compress for smaller sizes.

#### enum `EConcertCompressionMethod`  
`enum class EConcertCompressionMethod : uint8`  
_L69-79_
- reflection: `UENUM()`
- desc: Compression method to use. Note that these are assigned a bit shifted value to match the previous implementation in EConcertCompressionDetails.
- L72 _public enumerator_ `Uncompressed = 0` — Data is uncompressed.
- L75 _public enumerator_ `Zlib = 1 << 0` — ZLib compression is used for the serialized data.
- L78 _public enumerator_ `Oodle = 1 << 1` — Oodle compression is used for the serialized data.

#### enum `EConcertCompressionBias`  
`enum class EConcertCompressionBias : uint8`  
_L83-93_
- reflection: `UENUM()`
- desc: The bias (if any) to use when compressing the data. Note that these are assigned a bit shifted value to match the previous implementation in EConcertCompressionDetails.
- L86 _public enumerator_ `None` — Compress without a bias.
- L89 _public enumerator_ `Speed = 1 << 2` — Compress with a bias for speed.
- L92 _public enumerator_ `Size = 1 << 3` — Compress with a bias for size.

#### enum `EConcertPayloadSerializationMethod`  
`enum class EConcertPayloadSerializationMethod : uint8`  
_L239-245_
- reflection: `UENUM()`
- L242 _public enumerator_ `Standard = 0` — The data will be serialized using standard platform method.
- L244 _public enumerator_ `Cbor` — The data will be serialized using Cbor method.

#### struct `FConcertSessionChallengeData`  
`struct FConcertSessionChallengeData`  
_L248-265_
- reflection: `USTRUCT()`
- L252 _public function_ `FConcertSessionChallengeData()`
- L258 _public prototype_ `bool operator==(const FConcertSessionChallengeData& Other) const = default;`
- L261 _public member_ `FGuid ChallengeKey;` — `UPROPERTY(Meta = (IgnoreForMemberInitializationTest))`
- L264 _public member_ `int64 CreationTimeInTicks;` — `UPROPERTY()`

#### struct `FConcertSessionFileShareChallenge`  
`struct FConcertSessionFileShareChallenge`  
_L268-277_
- reflection: `USTRUCT()`
- L273 _public member_ `FString Path;` — `UPROPERTY()`
- L276 _public member_ `FConcertSessionChallengeData Data;` — `UPROPERTY()`

#### struct `FConcertSessionFileShare`  
`struct FConcertSessionFileShare`  
_L280-302_
- reflection: `USTRUCT()`
- L288 _public member_ `bool bFileShareEnabled = false;` — `UPROPERTY()` — Indicates that file sharing is enabled and available on the server.
- L294 _public member_ `FString FileShareRoot;` — `UPROPERTY()` — Root path for all file shares for this session.
- L301 _public member_ `FConcertSessionFileShareChallenge Challenge;` — `UPROPERTY()` — A challenge id that can be shared with the server / client to confirm that file sharing can be established between a server and a client.

#### struct `FConcertInstanceInfo`  
`struct FConcertInstanceInfo`  
_L306-330_
- reflection: `USTRUCT()`
- desc: Holds info on an instance communicating through concert
- L311 _public prototype_ `void Initialize();` — Initialize this instance information based on the current environment
- L314 _public prototype_ `FText ToDisplayString() const;` — Create a user friendly display string for using in things such as tooltips.
- L318 _public member_ `FGuid InstanceId;` — `UPROPERTY(VisibleAnywhere, Category="Instance Info")` — Holds the instance identifier.
- L322 _public member_ `FString InstanceName;` — `UPROPERTY(VisibleAnywhere, Category="Instance Info")` — Holds the instance name.
- L326 _public member_ `FString InstanceType;` — `UPROPERTY(VisibleAnywhere, Category="Instance Info")` — Holds the instance type (Editor, Game, Server, etc).
- L328 _public prototype_ `bool operator==(const FConcertInstanceInfo& Other) const;`
- L329 _public prototype_ `bool operator!=(const FConcertInstanceInfo& Other) const;`

#### struct `FConcertServerInfo`  
`struct FConcertServerInfo`  
_L334-358_
- reflection: `USTRUCT()`
- desc: Holds info on a Concert server
- L339 _public prototype_ `void Initialize();` — Initialize this server information based on the current environment
- L342 _public prototype_ `FText ToDisplayString() const;` — Create a user friendly display string for using in things such as tooltips.
- L346 _public member_ `FGuid AdminEndpointId;` — `UPROPERTY()` — Server endpoint for performing administration tasks (FConcertAdmin_X messages)
- L349 _public member_ `FString ServerName;` — `UPROPERTY()`
- L353 _public member_ `FConcertInstanceInfo InstanceInfo;` — `UPROPERTY(VisibleAnywhere, Category="Server Info")` — Basic server information
- L357 _public member_ `EConcertServerFlags ServerFlags = EConcertServerFlags::None;` — `UPROPERTY(VisibleAnywhere, Category = "Server Info")` — Contains information on the server settings

#### struct `FConcertClientInfo`  
`struct FConcertClientInfo`  
_L362-417_
- reflection: `USTRUCT()`
- desc: Holds info on a client connected through concert
- L367 _public prototype_ `void Initialize();` — Initialize this client information based on the current environment
- L370 _public prototype_ `FText ToDisplayString() const;` — Create a user friendly display string for using in things such as tooltips.
- L373 _public member_ `FConcertInstanceInfo InstanceInfo;` — `UPROPERTY(VisibleAnywhere, Category="Client Info")`
- L377 _public member_ `FString DeviceName;` — `UPROPERTY(VisibleAnywhere, Category="Client Info")` — Holds the name of the device that the instance is running on.
- L381 _public member_ `FString PlatformName;` — `UPROPERTY(VisibleAnywhere, Category="Client Info")` — Holds the name of the platform that the instance is running on.
- L385 _public member_ `FString UserName;` — `UPROPERTY(VisibleAnywhere, Category="Client Info")` — Holds the name of the user that owns this instance.
- L389 _public member_ `FString DisplayName;` — `UPROPERTY(VisibleAnywhere, Category="Client Info")` — Holds the display name of the user that owns this instance.
- L393 _public member_ `FLinearColor AvatarColor = {1.0f, 1.0f, 1.0f, 1.0f};` — `UPROPERTY(VisibleAnywhere, Category = "Client Info")` — Holds the color of the user avatar in a session.
- L397 _public member_ `FString DesktopAvatarActorClass;` — `UPROPERTY(VisibleAnywhere, Category = "Client Info")` — Holds the string representation of the desktop actor class to be used as the avatar for a representation of a client
- L401 _public member_ `FString VRAvatarActorClass;` — `UPROPERTY(VisibleAnywhere, Category = "Client Info")` — Holds the string representation of the VR actor class to be used as the avatar for a representation of a client
- L405 _public member_ `TArray<FName> Tags;` — `UPROPERTY(VisibleAnywhere, AdvancedDisplay, Category = "Client Info")` — Holds an array of tags that can be used for grouping and categorizing.
- L409 _public member_ `bool bHasEditorData = true;` — `UPROPERTY(VisibleAnywhere, Category="Client Info")` — True if this instance was built with editor-data
- L413 _public member_ `bool bRequiresCookedData = false;` — `UPROPERTY(VisibleAnywhere, Category="Client Info")` — True if this platform requires cooked data
- L415 _public prototype_ `bool operator==(const FConcertClientInfo& Other) const;`
- L416 _public prototype_ `bool operator!=(const FConcertClientInfo& Other) const;`

#### struct `FConcertSessionClientInfo`  
`struct FConcertSessionClientInfo`  
_L421-433_
- reflection: `USTRUCT()`
- desc: Holds information on session client
- L426 _public prototype_ `FText ToDisplayString() const;` — Create a user friendly display string for using in things such as tooltips.
- L429 _public member_ `FGuid ClientEndpointId;` — `UPROPERTY()`
- L432 _public member_ `FConcertClientInfo ClientInfo;` — `UPROPERTY(VisibleAnywhere, Category="Client Info")`

#### struct `FConcertSessionInfo`  
`struct FConcertSessionInfo`  
_L437-495_
- reflection: `USTRUCT()`
- desc: Holds info on a session
- L442 _public prototype_ `FText ToDisplayString() const;` — Create a user friendly display string for using in things such as tooltips.
- L445 _public member_ `FGuid ServerInstanceId;` — `UPROPERTY(VisibleAnywhere, Category="Session Info")`
- L448 _public member_ `FGuid ServerEndpointId;` — `UPROPERTY(VisibleAnywhere, Category="Session Info")`
- L451 _public member_ `FGuid OwnerInstanceId;` — `UPROPERTY(VisibleAnywhere, Category="Session Info")`
- L454 _public member_ `FGuid SessionId;` — `UPROPERTY(VisibleAnywhere, Category="Session Info")`
- L457 _public member_ `FString SessionName;` — `UPROPERTY(VisibleAnywhere, Category="Session Info")`
- L460 _public member_ `FString OwnerUserName;` — `UPROPERTY(VisibleAnywhere, Category="Session Info")`
- L463 _public member_ `FString OwnerDeviceName;` — `UPROPERTY(VisibleAnywhere, Category = "Session Info")`
- L467 _public member_ `FConcertSessionSettings Settings;` — `UPROPERTY(VisibleAnywhere, Category="Session Info")` — Settings pertaining to project, change list number etc
- L471 _public member_ `TArray<FConcertSessionVersionInfo> VersionInfos;` — `UPROPERTY()` — Version information for this session. This is set during creation, and updated each time the session is restored
- L475 _public member_ `EConcertSessionState State = EConcertSessionState::Normal;` — `UPROPERTY()` — Current state of the session used to determine joinability by clients.
- L477 _public function_ `FDateTime GetLastModified() const`
- L478 _public function_ `void SetLastModified(const FDateTime& Value)`
- L479 _public function_ `void SetLastModifiedToNow()`
- L482 _public member_ `FConcertSessionFileShare FileSharing;` — `UPROPERTY()`
- L494 _private member_ `int64 LastModifiedTicks {};` — `UPROPERTY(VisibleAnywhere, Category="Session Info")` — The last time the session directory was modified in local time. Stored in ticks instead of FDateTime because FDateTime is not serialized properly by FStructSerializer::Serialize and FStructDeserializer::Deserialize. These functions are used for packing data when sent across the network. The issue is that in UObject/NoExportTypes.h FDateTime does not expose Ticks as UProperty; doing this would be the 'proper' fix but it may cause instability this late into 5.1 dev.

#### struct `FConcertSessionFilter`  
`struct FConcertSessionFilter`  
_L499-536_
- reflection: `USTRUCT()`
- desc: Holds filter rules used when migrating session data
- L507 _public prototype_ `bool ActivityIdPassesFilter(const int64 InActivityId) const;` — Return true if the given activity ID passes the ID tests of this filter. @note This function only tests the ID conditions, not any data specific checks like bOnlyLiveData and bIncludeIgnoredActivities.
- L511 _public member_ `int64 ActivityIdLowerBound = 1;` — `UPROPERTY()` — The lower-bound (inclusive) of activity IDs to include (unless explicitly excluded via ActivityIdsToExclude)
- L515 _public member_ `int64 ActivityIdUpperBound = MAX_int64;` — `UPROPERTY()` — The upper-bound (inclusive) of activity IDs to include (unless explicitly excluded via ActivityIdsToExclude)
- L519 _public member_ `TArray<int64> ActivityIdsToExclude;` — `UPROPERTY()` — Activity IDs to explicitly exclude, even if inside of the bounded-range specified above
- L523 _public member_ `TArray<int64> ActivityIdsToInclude;` — `UPROPERTY()` — Activity IDs to explicitly include, even if outside of the bounded-range specified above (takes precedence over ActivityIdsToExclude)
- L527 _public member_ `bool bOnlyLiveData = false;` — `UPROPERTY()` — True if only live data should be included (live transactions and head package revisions)
- L531 _public member_ `bool bMetaDataOnly = false;` — `UPROPERTY()` — True to export the activity summaries without the package/transaction data to look at the log rather than replaying the activities.
- L535 _public member_ `bool bIncludeIgnoredActivities = false;` — `UPROPERTY()` — True to include ignored activities

#### struct `FConcertByteArray`  
`struct FConcertByteArray`  
_L539-557_
- reflection: `USTRUCT()`
- L543 _public function_ `bool Serialize(FArchive& Ar)`
- L556 _public member_ `TArray<uint8> Bytes;` — `UPROPERTY()`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FConcertByteArray> : public TStructOpsTypeTraitsBase2<FConcertByteArray>`  
_L560-566_
- inherits: `TStructOpsTypeTraitsBase2<FConcertByteArray>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L563-565_

#### struct `FConcertSessionSerializedPayload`  
`struct FConcertSessionSerializedPayload`  
_L570-638_
- reflection: `USTRUCT()`
- L574 _public prototype_ `FConcertSessionSerializedPayload() = default;`
- L576 _public function_ `FConcertSessionSerializedPayload( EConcertPayloadSerializationMethod SerializeMethod ) : SerializationMethod(SerializeMethod)`
- L582 _public prototype_ `bool SetPayload(const FStructOnScope& InPayload, EConcertPayloadCompressionType CompressionType = EConcertPayloadCompressionType::Heuristic);` — Initialize this payload from the given data
- L583 _public prototype_ `bool SetPayload(const UScriptStruct* InPayloadType, const void* InPayloadData, EConcertPayloadCompressionType CompressionType = EConcertPayloadCompressionType::Heuristic);`
- L586 _public function_ `template <typename T> bool SetTypedPayload(const T& InPayloadData, EConcertPayloadCompressionType CompressType = EConcertPayloadCompressionType::Heuristic)`
- L592 _public prototype_ `bool GetPayload(FStructOnScope& OutPayload) const;` — Extract the payload into an in-memory instance
- L593 _public prototype_ `bool GetPayload(const UScriptStruct* InPayloadType, void* InOutPayloadData) const;`
- L595 _public prototype_ `bool IsTypeChildOf(const UScriptStruct* InPayloadType) const;`
- L598 _public function_ `template<typename T> bool IsTypeChildOf() const`
- L604 _public function_ `template <typename T> bool GetTypedPayload(T& OutPayloadData) const`
- L610 _public function_ `bool PayloadIsCompressed() const` — Indicates if the stored payload has been compressed with any compression algorithm.
- L617 _public member_ `FName PayloadTypeName;` — `UPROPERTY(VisibleAnywhere, Category="Payload")` — The typename of the user-defined payload.
- L621 _public member_ `EConcertPayloadSerializationMethod SerializationMethod = EConcertPayloadSerializationMethod::Standard;` — `UPROPERTY(VisibleAnywhere, Category = "Payload")` — Specifies the serialization method used to pack the data
- L625 _public member_ `EConcertCompressionMethod PayloadCompressionMethod = EConcertCompressionMethod::Uncompressed;` — `UPROPERTY(VisibleAnywhere, Category = "Payload")` — Indicates how the serialized payload has been compressed.
- L629 _public member_ `EConcertCompressionBias PayloadCompressionBias = EConcertCompressionBias::None;` — `UPROPERTY(VisibleAnywhere, Category = "Payload")` — Indicates how the serialized payload has been compressed.
- L633 _public member_ `int32 PayloadSize = 0;` — `UPROPERTY(VisibleAnywhere, Category="Payload")` — The uncompressed size of the user-defined payload data.
- L637 _public member_ `FConcertByteArray PayloadBytes;` — `UPROPERTY()` — The data of the user-defined payload (potentially stored as compressed binary for compact transfer).

#### Free symbols / members of external scopes

- L15 _typedef_ `using FActivityID = int64;`
- L97 _namespace_ `namespace UE`
- L97 _namespace_ `namespace Concert` (scope `UE`)
- L97 _namespace_ `namespace Compression` (scope `UE::Concert`)
- L101 _prototype_ `int32 GetConsoleVariableCompressionType();` (scope `UE::Concert::Compression`) — Get the compression type from the console variable setting.
- L104 _prototype_ `int32 GetConsoleVariableCompressionFlags();` (scope `UE::Concert::Compression`) — Function to check the console variable for the compression flags. Speed vs size.
- L107 _prototype_ `int32 GetConsoleVariableCompressionSizeLimit();` (scope `UE::Concert::Compression`) — Function to check the console variable for compression size limit.
- L111 _function_ `template <typename SizeType> inline bool ShouldCompress(SizeType DataSize)` (scope `UE::Concert::Compression`) — Based on the size of the data to compress indicate if we should invoke the compressor.
- L125 _function_ `inline bool DataIsCompressed(EConcertCompressionMethod InFormat)` (scope `UE::Concert::Compression`) — Returns truen if the compression details is set to compressed format.
- L131 _function_ `inline bool DataIsUncompressed(EConcertCompressionMethod InFormat)` (scope `UE::Concert::Compression`) — Returns true if the compression details is set to uncompressed format.
- L137 _function_ `inline bool DataIsCompressedWithOodle(EConcertCompressionMethod InFormat)` (scope `UE::Concert::Compression`) — Returns true if we are suppose to use Oodle for compression.
- L143 _function_ `inline FName GetCompressionAlgorithm()` (scope `UE::Concert::Compression`) — Get the named compression algorithm to invoke with serializer and memory compressors.
- L154 _function_ `inline ECompressionFlags GetCompressionFlags()` (scope `UE::Concert::Compression`) — Get the default flags to use when invoking the compressor.
- L169 _function_ `inline FName GetCompressionAlgorithm(EConcertCompressionMethod InDetails)` (scope `UE::Concert::Compression`) — Get the named compression algorithm based on the provided details.  Current this is only Zlib or Oodle.
- L175 _function_ `inline ECompressionFlags GetCoreCompressionFlags(EConcertCompressionBias InBias)` (scope `UE::Concert::Compression`) — Get the compression enum value given the concert compression settings.  This the value passed into the serializer and memory compressor.
- L189 _function_ `inline EConcertCompressionBias GetConcertCompressionBias(ECompressionFlags InFlags)` (scope `UE::Concert::Compression`) — Get the concert compression bias value given the compressor compression flags.
- L205 _function_ `inline EConcertCompressionMethod GetCompressionFromNamedType(FName NamedMethod)` (scope `UE::Concert::Compression`) — For a given named compression algorithm and compression flags convert it into a EConcertCompressionMethod
- L221 _function_ `template <typename SizeType> inline EConcertCompressionMethod GetCompressionMethod(SizeType DataSize)` (scope `UE::Concert::Compression`) — Based on the data size return the current compression details to store.
- L564 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anon1c321be90103`)

### `Plugins/Developer/Concert/ConcertMain/Source/Concert/Public/ConcertMessages.h` (Public)


#### enum `EConcertConnectionStatus`  
`enum class EConcertConnectionStatus : uint8`  
_L15-25_
- reflection: `UENUM()`
- desc: Connection status for Concert client sessions
- L18 _public enumerator_ `Connecting` — Currently establishing connection to the server session
- L20 _public enumerator_ `Connected` — Connection established and alive
- L22 _public enumerator_ `Disconnecting` — Currently severing connection to the server session gracefully
- L24 _public enumerator_ `Disconnected` — Disconnected

#### enum `EConcertConnectionResult`  
`enum class EConcertConnectionResult : uint8`  
_L29-39_
- reflection: `UENUM()`
- desc: Connection Result for Concert client session
- L32 _public enumerator_ `None` — No result yet
- L34 _public enumerator_ `ConnectionAccepted` — Server has accepted connection
- L36 _public enumerator_ `ConnectionRefused` — Server has refused the connection session messages beside other connection request are ignored
- L38 _public enumerator_ `AlreadyConnected` — Server already accepted connection

#### enum `EConcertClientStatus`  
`enum class EConcertClientStatus : uint8`  
_L43-54_
- reflection: `UENUM()`
- desc: Status for Concert session clients
- L46 _public enumerator_ `Connected` — Client connected
- L48 _public enumerator_ `Disconnected` — Client disconnected
- L50 _public enumerator_ `Updated` — Client state updated
- L53 _public enumerator_ `Count` — Not an actual state - add new entries above.

#### enum `EConcertSendReceiveState`  
`enum class EConcertSendReceiveState : uint8`  
_L57-67_
- reflection: `UENUM()`
- L60 _public enumerator_ `Default` — Full send / receive
- L63 _public enumerator_ `SendOnly` — Sender only. Local transaction events will be sent to server but receiving data from clients has been suspended
- L66 _public enumerator_ `ReceiveOnly` — Receive only. Updates will be received from clients but local transaction events will be deferred until state has been set to default or send.

#### enum `EConcertSessionResponseCode`  
`enum class EConcertSessionResponseCode : uint8`  
_L71-79_
- reflection: `UENUM()`
- desc: Response codes for a session custom request
- L74 _public enumerator_ `Success` — The request data was valid. A response was generated.
- L76 _public enumerator_ `Failed` — The request data was valid, but the request failed. A response was generated.
- L78 _public enumerator_ `InvalidRequest` — The request data was invalid. No response was generated.

#### enum `EConcertSessionRepositoryMountResponseCode`  
`enum class EConcertSessionRepositoryMountResponseCode : uint8`  
_L83-93_
- reflection: `UENUM()`
- desc: Response code returned when trying to mount a session repository on the server.
- L86 _public enumerator_ `None` — No response code yet.
- L88 _public enumerator_ `Mounted` — The repository was mounted on the invoked server.
- L90 _public enumerator_ `AlreadyMounted` — The repository is already mounted by another server instance.
- L92 _public enumerator_ `NotFound` — The repository ID could not be found in the server list.

#### struct `FConcertAdmin_DiscoverServersEvent`  
`struct FConcertAdmin_DiscoverServersEvent : public FConcertEndpointDiscoveryEvent`  
_L97-112_
- reflection: `USTRUCT()`
- inherits: `FConcertEndpointDiscoveryEvent`
- L103 _public member_ `FString RequiredRole;` — `UPROPERTY(VisibleAnywhere, Category = "Concert Message")` — The required role of the server (eg, MultiUser, DisasterRecovery, etc)
- L107 _public member_ `FString RequiredVersion;` — `UPROPERTY(VisibleAnywhere, Category = "Concert Message")` — The required version of the server (eg, 4.22, 4.23, etc)
- L111 _public member_ `FString ClientAuthenticationKey;` — `UPROPERTY(VisibleAnywhere, Category = "Concert Message")` — If a server was configured to restrict access to specific client(s), it will search for this key in its list of authorized keys.

#### struct `FConcertAdmin_ServerDiscoveredEvent`  
`struct FConcertAdmin_ServerDiscoveredEvent : public FConcertEndpointDiscoveryEvent`  
_L115-130_
- reflection: `USTRUCT()`
- inherits: `FConcertEndpointDiscoveryEvent`
- L121 _public member_ `FString ServerName;` — `UPROPERTY(VisibleAnywhere, Category = "Concert Message")` — Server designated name
- L125 _public member_ `FConcertInstanceInfo InstanceInfo;` — `UPROPERTY(VisibleAnywhere, Category="Concert Message")` — Basic information about the server instance
- L129 _public member_ `EConcertServerFlags ServerFlags = EConcertServerFlags::None;` — `UPROPERTY(VisibleAnywhere, Category = "Concert Message")` — Contains information on the server settings

#### struct `FConcertSessionRepositoryInfo`  
`struct FConcertSessionRepositoryInfo`  
_L134-145_
- reflection: `USTRUCT()`
- desc: Contains information about a session repository.
- L140 _public member_ `FGuid RepositoryId;` — `UPROPERTY(VisibleAnywhere, Category = "Concert Message")` — The repository ID.
- L144 _public member_ `bool bMounted = false;` — `UPROPERTY(VisibleAnywhere, Category = "Concert Message")` — The mounted state of this repository.

#### struct `FConcertAdmin_MountSessionRepositoryRequest`  
`struct FConcertAdmin_MountSessionRepositoryRequest : public FConcertRequestData`  
_L151-170_
- reflection: `USTRUCT()`
- inherits: `FConcertRequestData`
- desc: Mount a session repository used to store session files.
- L157 _public member_ `FGuid RepositoryId;` — `UPROPERTY(VisibleAnywhere, Category = "Concert Message")` — The repository unique Id. Must be valid.
- L161 _public member_ `FString RepositoryRootDir;` — `UPROPERTY(VisibleAnywhere, Category = "Concert Message")` — The repository root dir (absolute path) where the repository should be found/created. If empty, the server will use its default one.
- L165 _public member_ `bool bAsServerDefault = false;` — `UPROPERTY(VisibleAnywhere, Category = "Concert Message")` — Whether this repository is set as the default one used by server to store new sessions.
- L169 _public member_ `bool bCreateIfNotExist = false;` — `UPROPERTY(VisibleAnywhere, Category = "Concert Message")` — Whether the repository should be created if it was not found.

#### struct `FConcertAdmin_MountSessionRepositoryResponse`  
`struct FConcertAdmin_MountSessionRepositoryResponse : public FConcertResponseData`  
_L173-179_
- reflection: `USTRUCT()`
- inherits: `FConcertResponseData`
- L178 _public member_ `EConcertSessionRepositoryMountResponseCode MountStatus = EConcertSessionRepositoryMountResponseCode::None;` — `UPROPERTY(VisibleAnywhere, Category = "Concert Message")`

#### struct `FConcertAdmin_GetSessionRepositoriesRequest`  
`struct FConcertAdmin_GetSessionRepositoriesRequest : public FConcertRequestData`  
_L183-186_
- reflection: `USTRUCT()`
- inherits: `FConcertRequestData`
- desc: Returns the list of repositories known of the server.

#### struct `FConcertAdmin_GetSessionRepositoriesResponse`  
`struct FConcertAdmin_GetSessionRepositoriesResponse : public FConcertResponseData`  
_L189-195_
- reflection: `USTRUCT()`
- inherits: `FConcertResponseData`
- L194 _public member_ `TArray<FConcertSessionRepositoryInfo> SessionRepositories;` — `UPROPERTY(VisibleAnywhere, Category = "Concert Message")`

#### struct `FConcertAdmin_DropSessionRepositoriesRequest`  
`struct FConcertAdmin_DropSessionRepositoriesRequest : public FConcertRequestData`  
_L201-208_
- reflection: `USTRUCT()`
- inherits: `FConcertRequestData`
- desc: Drop one or more session repositories from the server, deleting all the contained files.
- L207 _public member_ `TArray<FGuid> RepositoryIds;` — `UPROPERTY(VisibleAnywhere, Category = "Concert Message")` — The list of repository IDs to drop.

#### struct `FConcertAdmin_DropSessionRepositoriesResponse`  
`struct FConcertAdmin_DropSessionRepositoriesResponse : public FConcertResponseData`  
_L211-218_
- reflection: `USTRUCT()`
- inherits: `FConcertResponseData`
- L217 _public member_ `TArray<FGuid> DroppedRepositoryIds;` — `UPROPERTY(VisibleAnywhere, Category = "Concert Message")` — The list of repository IDs successfully dropped (not found == dropped).

#### struct `FConcertAdmin_GetAllSessionsRequest`  
`struct FConcertAdmin_GetAllSessionsRequest : public FConcertRequestData`  
_L221-224_
- reflection: `USTRUCT()`
- inherits: `FConcertRequestData`

#### struct `FConcertAdmin_GetAllSessionsResponse`  
`struct FConcertAdmin_GetAllSessionsResponse : public FConcertResponseData`  
_L227-236_
- reflection: `USTRUCT()`
- inherits: `FConcertResponseData`
- L232 _public member_ `TArray<FConcertSessionInfo> LiveSessions;` — `UPROPERTY(VisibleAnywhere, Category="Concert Message")`
- L235 _public member_ `TArray<FConcertSessionInfo> ArchivedSessions;` — `UPROPERTY(VisibleAnywhere, Category="Concert Message")`

#### struct `FConcertAdmin_GetLiveSessionsRequest`  
`struct FConcertAdmin_GetLiveSessionsRequest : public FConcertRequestData`  
_L239-242_
- reflection: `USTRUCT()`
- inherits: `FConcertRequestData`

#### struct `FConcertAdmin_GetArchivedSessionsRequest`  
`struct FConcertAdmin_GetArchivedSessionsRequest : public FConcertRequestData`  
_L245-248_
- reflection: `USTRUCT()`
- inherits: `FConcertRequestData`

#### struct `FConcertAdmin_GetSessionsResponse`  
`struct FConcertAdmin_GetSessionsResponse : public FConcertResponseData`  
_L251-257_
- reflection: `USTRUCT()`
- inherits: `FConcertResponseData`
- L256 _public member_ `TArray<FConcertSessionInfo> Sessions;` — `UPROPERTY(VisibleAnywhere, Category="Concert Message")`

#### struct `FConcertAdmin_CreateSessionRequest`  
`struct FConcertAdmin_CreateSessionRequest : public FConcertRequestData`  
_L260-278_
- reflection: `USTRUCT()`
- inherits: `FConcertRequestData`
- L265 _public member_ `FString SessionName;` — `UPROPERTY(VisibleAnywhere, Category="Concert Message")`
- L268 _public member_ `FConcertClientInfo OwnerClientInfo;` — `UPROPERTY(VisibleAnywhere, Category="Concert Message")`
- L271 _public member_ `FConcertSessionSettings SessionSettings;` — `UPROPERTY(VisibleAnywhere, Category="Concert Message")`
- L274 _public member_ `FConcertSessionVersionInfo VersionInfo;` — `UPROPERTY(VisibleAnywhere, Category="Concert Message")`
- L277 _public member_ `FConcertSessionFileShare FileShare;` — `UPROPERTY(VisibleAnywhere, Category="Concert Message")`

#### struct `FConcertAdmin_FindSessionRequest`  
`struct FConcertAdmin_FindSessionRequest : public FConcertRequestData`  
_L281-299_
- reflection: `USTRUCT()`
- inherits: `FConcertRequestData`
- L286 _public member_ `FGuid SessionId;` — `UPROPERTY(VisibleAnywhere, Category="Concert Message")`
- L289 _public member_ `FConcertClientInfo OwnerClientInfo;` — `UPROPERTY(VisibleAnywhere, Category="Concert Message")`
- L292 _public member_ `FConcertSessionSettings SessionSettings;` — `UPROPERTY(VisibleAnywhere, Category="Concert Message")`
- L295 _public member_ `FConcertSessionVersionInfo VersionInfo;` — `UPROPERTY(VisibleAnywhere, Category="Concert Message")`
- L298 _public member_ `FConcertSessionFileShare FileShare;` — `UPROPERTY(VisibleAnywhere, Category="Concert Message")`

#### struct `FConcertAdmin_CopySessionRequest`  
`struct FConcertAdmin_CopySessionRequest : public FConcertRequestData`  
_L303-333_
- reflection: `USTRUCT()`
- inherits: `FConcertRequestData`
- desc: Used to copy a live session or restore an archived one.
- L309 _public member_ `FGuid SessionId;` — `UPROPERTY(VisibleAnywhere, Category="Concert Message")` — The ID of the session to copy or restore. It can be a live or an archived session unless bRestoreOnly is true, in which case, the session to copy must be an archived one.
- L313 _public member_ `FString SessionName;` — `UPROPERTY(VisibleAnywhere, Category="Concert Message")` — The name of the session to create.
- L317 _public member_ `FConcertClientInfo OwnerClientInfo;` — `UPROPERTY(VisibleAnywhere, Category="Concert Message")` — Information about the owner of the copied session.
- L321 _public member_ `FConcertSessionSettings SessionSettings;` — `UPROPERTY(VisibleAnywhere, Category="Concert Message")` — Settings to apply to the copied session.
- L325 _public member_ `FConcertSessionVersionInfo VersionInfo;` — `UPROPERTY(VisibleAnywhere, Category="Concert Message")` — Version information of the client requesting the copy.
- L329 _public member_ `FConcertSessionFilter SessionFilter;` — `UPROPERTY(VisibleAnywhere, Category="Concert Message")` — The filter controlling which activities from the session should be copied over.
- L332 _public member_ `bool bRestoreOnly = false;` — True to constrain the session to copy to be an archive (implying a restore operation).

#### struct `FConcertAdmin_SessionInfoResponse`  
`struct FConcertAdmin_SessionInfoResponse : public FConcertResponseData`  
_L336-345_
- reflection: `USTRUCT()`
- inherits: `FConcertResponseData`
- L341 _public member_ `FConcertSessionInfo SessionInfo;` — `UPROPERTY(VisibleAnywhere, Category="Concert Message")`
- L344 _public member_ `FConcertSessionFileShare FileShare;` — `UPROPERTY(VisibleAnywhere, Category = "Concert Message")`

#### struct `FConcertAdmin_ArchiveSessionRequest`  
`struct FConcertAdmin_ArchiveSessionRequest : public FConcertRequestData`  
_L349-372_
- reflection: `USTRUCT()`
- inherits: `FConcertRequestData`
- desc: Create an archived copy of a live session.
- L355 _public member_ `FGuid SessionId;` — `UPROPERTY(VisibleAnywhere, Category = "Concert Message")` — The ID of the session to archive (must be a live session).
- L359 _public member_ `FString ArchiveNameOverride;` — `UPROPERTY(VisibleAnywhere, Category = "Concert Message")` — The override for the archive.
- L363 _public member_ `FString UserName;` — `UPROPERTY(VisibleAnywhere, Category = "Concert Message")` — The caller user name.
- L367 _public member_ `FString DeviceName;` — `UPROPERTY(VisibleAnywhere, Category = "Concert Message")` — The caller device name.
- L371 _public member_ `FConcertSessionFilter SessionFilter;` — `UPROPERTY(VisibleAnywhere, Category = "Concert Message")` — The filter controlling which activities from the session should be archived.

#### struct `FConcertAdmin_ArchiveSessionResponse`  
`struct FConcertAdmin_ArchiveSessionResponse : public FConcertResponseData`  
_L375-394_
- reflection: `USTRUCT()`
- inherits: `FConcertResponseData`
- L381 _public member_ `FGuid SessionId;` — `UPROPERTY(VisibleAnywhere, Category = "Concert Message")` — The ID of the session that was requested to be archived.
- L385 _public member_ `FString SessionName;` — `UPROPERTY(VisibleAnywhere, Category = "Concert Message")` — The name of the session that was requested to be archived.
- L389 _public member_ `FGuid ArchiveId;` — `UPROPERTY(VisibleAnywhere, Category = "Concert Message")` — The ID of the new archived session (on success).
- L393 _public member_ `FString ArchiveName;` — `UPROPERTY(VisibleAnywhere, Category = "Concert Message")` — The name of the new archived session (on success).

#### struct `FConcertAdmin_RenameSessionRequest`  
`struct FConcertAdmin_RenameSessionRequest : public FConcertRequestData`  
_L398-416_
- reflection: `USTRUCT()`
- inherits: `FConcertRequestData`
- desc: Rename a session.
- L404 _public member_ `FGuid SessionId;` — `UPROPERTY(VisibleAnywhere, Category = "Concert Message")` — The ID of the session to rename.
- L408 _public member_ `FString NewName;` — `UPROPERTY(VisibleAnywhere, Category = "Concert Message")` — The new session name.
- L412 _public member_ `FString UserName;` — `UPROPERTY(VisibleAnywhere, Category = "Concert Message")` — For now only the user name and device name of the client is used to id it as the owner of a session
- L415 _public member_ `FString DeviceName;` — `UPROPERTY(VisibleAnywhere, Category = "Concert Message")`

#### struct `FConcertAdmin_RenameSessionResponse`  
`struct FConcertAdmin_RenameSessionResponse : public FConcertResponseData`  
_L419-430_
- reflection: `USTRUCT()`
- inherits: `FConcertResponseData`
- L425 _public member_ `FGuid SessionId;` — `UPROPERTY(VisibleAnywhere, Category = "Concert Message")` — The ID of the session that was requested to be renamed.
- L429 _public member_ `FString OldName;` — `UPROPERTY(VisibleAnywhere, Category = "Concert Message")` — The old session name (if the session exist).

#### struct `FConcertAdmin_DeleteSessionRequest`  
`struct FConcertAdmin_DeleteSessionRequest : public FConcertRequestData`  
_L435-449_
- reflection: `USTRUCT()`
- inherits: `FConcertRequestData`
- desc: Delete an archived or live session.
- L441 _public member_ `FGuid SessionId;` — `UPROPERTY(VisibleAnywhere, Category = "Concert Message")` — The ID of the session to delete.
- L445 _public member_ `FString UserName;` — `UPROPERTY(VisibleAnywhere, Category = "Concert Message")` — For now only the user name and device name of the client is used to id it as the owner of a session
- L448 _public member_ `FString DeviceName;` — `UPROPERTY(VisibleAnywhere, Category = "Concert Message")`

#### struct `FConcertAdmin_DeleteSessionResponse`  
`struct FConcertAdmin_DeleteSessionResponse : public FConcertResponseData`  
_L452-463_
- reflection: `USTRUCT()`
- inherits: `FConcertResponseData`
- L458 _public member_ `FGuid SessionId;` — `UPROPERTY(VisibleAnywhere, Category = "Concert Message")` — The ID of the session that was requested to be deleted.
- L462 _public member_ `FString SessionName;` — `UPROPERTY(VisibleAnywhere, Category = "Concert Message")` — The name of the session that was was requested to be deleted.

#### enum `EBatchSessionDeletionFlags`  
`enum class EBatchSessionDeletionFlags`  
_L466-477_
- reflection: `UENUM()`
- L469 _public enumerator_ `Strict` — Any error in the request will make the entire operation fail.
- L476 _public enumerator_ `SkipForbiddenSessions = 0x01` — If the request contains sessions that is not owned by the requesting client, skip them. Skipped sessions are added to FConcertAdmin_BatchDeleteSessionResponse::NotOwnedByClient. This avoids clients having to request ownership info before ensuring an atomic and consistent operation.

#### struct `FConcertAdmin_BatchDeleteSessionRequest`  
`struct FConcertAdmin_BatchDeleteSessionRequest : public FConcertRequestData`  
_L482-500_
- reflection: `USTRUCT()`
- inherits: `FConcertRequestData`
- desc: Deletes several archived and/or live sessions.
- L488 _public member_ `TSet<FGuid> SessionIds;` — `UPROPERTY(VisibleAnywhere, Category = "Concert Message")` — The ID of the session to delete.
- L492 _public member_ `EBatchSessionDeletionFlags Flags = EBatchSessionDeletionFlags::Strict;` — `UPROPERTY(VisibleAnywhere, Category = "Concert Message")` — How the operation input is supposed to be interpreted
- L496 _public member_ `FString UserName;` — `UPROPERTY(VisibleAnywhere, Category = "Concert Message")` — For now only the user name and device name of the client is used to id it as the owner of a session
- L499 _public member_ `FString DeviceName;` — `UPROPERTY(VisibleAnywhere, Category = "Concert Message")`

#### struct `FDeletedSessionInfo`  
`struct FDeletedSessionInfo`  
_L503-514_
- reflection: `USTRUCT()`
- L509 _public member_ `FGuid SessionId;` — `UPROPERTY(VisibleAnywhere, Category = "Concert Message")` — The ID of the session that was requested to be deleted.
- L513 _public member_ `FString SessionName;` — `UPROPERTY(VisibleAnywhere, Category = "Concert Message")` — The name of the session that was was requested to be deleted.

#### struct `FConcertAdmin_BatchDeleteSessionResponse`  
`struct FConcertAdmin_BatchDeleteSessionResponse : public FConcertResponseData`  
_L518-529_
- reflection: `USTRUCT()`
- inherits: `FConcertResponseData`
- desc: Answer by server
- L524 _public member_ `TArray<FDeletedSessionInfo> DeletedItems;` — `UPROPERTY(VisibleAnywhere, Category = "Concert Message")` — The IDs of the session that were requested to be deleted.
- L528 _public member_ `TArray<FDeletedSessionInfo> NotOwnedByClient;` — `UPROPERTY(VisibleAnywhere, Category = "Concert Message")` — Contains the sessions that were skipped if FConcertAdmin_BatchDeleteSessionRequest::Flags has the SkipForbiddenSessions flag set.

#### struct `FConcertAdmin_GetSessionClientsRequest`  
`struct FConcertAdmin_GetSessionClientsRequest : public FConcertRequestData`  
_L532-538_
- reflection: `USTRUCT()`
- inherits: `FConcertRequestData`
- L537 _public member_ `FGuid SessionId;` — `UPROPERTY(VisibleAnywhere, Category="Concert Message")`

#### struct `FConcertAdmin_GetSessionClientsResponse`  
`struct FConcertAdmin_GetSessionClientsResponse : public FConcertResponseData`  
_L541-547_
- reflection: `USTRUCT()`
- inherits: `FConcertResponseData`
- L546 _public member_ `TArray<FConcertSessionClientInfo> SessionClients;` — `UPROPERTY(VisibleAnywhere, Category="Concert Message")`

#### struct `FConcertAdmin_GetSessionActivitiesRequest`  
`struct FConcertAdmin_GetSessionActivitiesRequest : public FConcertRequestData`  
_L550-565_
- reflection: `USTRUCT()`
- inherits: `FConcertRequestData`
- L555 _public member_ `FGuid SessionId;` — `UPROPERTY(VisibleAnywhere, Category="Concert Message")`
- L558 _public member_ `int64 FromActivityId = 1;` — `UPROPERTY(VisibleAnywhere, Category="Concert Message")`
- L561 _public member_ `int64 ActivityCount = 1024;` — `UPROPERTY(VisibleAnywhere, Category="Concert Message")`
- L564 _public member_ `bool bIncludeDetails = false;` — `UPROPERTY(VisibleAnywhere, Category="Concert Message")`

#### struct `FConcertAdmin_GetSessionActivitiesResponse`  
`struct FConcertAdmin_GetSessionActivitiesResponse : public FConcertResponseData`  
_L568-579_
- reflection: `USTRUCT()`
- inherits: `FConcertResponseData`
- L574 _public member_ `TArray<FConcertSessionSerializedPayload> Activities;` — `UPROPERTY(VisibleAnywhere, Category="Concert Message")` — The list of activities.
- L578 _public member_ `TMap<FGuid, FConcertClientInfo> EndpointClientInfoMap;` — `UPROPERTY(VisibleAnywhere, Category="Concert Message")` — Maps each activity endpoint to its client info.

#### struct `FConcertSession_DiscoverAndJoinSessionEvent`  
`struct FConcertSession_DiscoverAndJoinSessionEvent : public FConcertEndpointDiscoveryEvent`  
_L582-591_
- reflection: `USTRUCT()`
- inherits: `FConcertEndpointDiscoveryEvent`
- L587 _public member_ `FGuid SessionServerEndpointId;` — `UPROPERTY(VisibleAnywhere, Category="Concert Message")`
- L590 _public member_ `FConcertClientInfo ClientInfo;` — `UPROPERTY(VisibleAnywhere, Category="Concert Message")`

#### struct `FConcertSession_JoinSessionResultEvent`  
`struct FConcertSession_JoinSessionResultEvent : public FConcertEndpointDiscoveryEvent`  
_L594-606_
- reflection: `USTRUCT()`
- inherits: `FConcertEndpointDiscoveryEvent`
- L599 _public member_ `FGuid SessionServerEndpointId;` — `UPROPERTY(VisibleAnywhere, Category="Concert Message")`
- L602 _public member_ `EConcertConnectionResult ConnectionResult = EConcertConnectionResult::None;` — `UPROPERTY(VisibleAnywhere, Category="Concert Message")`
- L605 _public member_ `TArray<FConcertSessionClientInfo> SessionClients;` — `UPROPERTY(VisibleAnywhere, Category="Concert Message")`

#### struct `FConcertSession_LeaveSessionEvent`  
`struct FConcertSession_LeaveSessionEvent : public FConcertEventData`  
_L609-615_
- reflection: `USTRUCT()`
- inherits: `FConcertEventData`
- L614 _public member_ `FGuid SessionServerEndpointId;` — `UPROPERTY(VisibleAnywhere, Category="Concert Message")`

#### struct `FConcertSession_UpdateClientInfoEvent`  
`struct FConcertSession_UpdateClientInfoEvent : public FConcertEventData`  
_L618-624_
- reflection: `USTRUCT()`
- inherits: `FConcertEventData`
- L623 _public member_ `FConcertSessionClientInfo SessionClient;` — `UPROPERTY(VisibleAnywhere, Category="Concert Message")`

#### struct `FConcertSession_ClientListUpdatedEvent`  
`struct FConcertSession_ClientListUpdatedEvent : public FConcertEventData`  
_L627-633_
- reflection: `USTRUCT()`
- inherits: `FConcertEventData`
- L632 _public member_ `TArray<FConcertSessionClientInfo> SessionClients;` — `UPROPERTY(VisibleAnywhere, Category="Concert Message")`

#### struct `FConcertSession_SessionRenamedEvent`  
`struct FConcertSession_SessionRenamedEvent : public FConcertEventData`  
_L636-642_
- reflection: `USTRUCT()`
- inherits: `FConcertEventData`
- L641 _public member_ `FString NewName;` — `UPROPERTY(VisibleAnywhere, Category="Concert Message")`

#### struct `FConcertSession_CustomEvent`  
`struct FConcertSession_CustomEvent : public FConcertEventData`  
_L645-663_
- reflection: `USTRUCT()`
- inherits: `FConcertEventData`
- L649 _public function_ `virtual bool IsSafeToHandle() const override`
- L655 _public member_ `FGuid SourceEndpointId;` — `UPROPERTY(VisibleAnywhere, Category="Concert Custom Message")`
- L658 _public member_ `TArray<FGuid> DestinationEndpointIds;` — `UPROPERTY(VisibleAnywhere, Category="Concert Custom Message")`
- L662 _public member_ `FConcertSessionSerializedPayload SerializedPayload;` — `UPROPERTY(VisibleAnywhere, Category="Concert Custom Message")` — The serialized payload that we're hosting.

#### struct `FConcertSession_CustomRequest`  
`struct FConcertSession_CustomRequest : public FConcertRequestData`  
_L666-684_
- reflection: `USTRUCT()`
- inherits: `FConcertRequestData`
- L670 _public function_ `virtual bool IsSafeToHandle() const override`
- L676 _public member_ `FGuid SourceEndpointId;` — `UPROPERTY(VisibleAnywhere, Category="Concert Custom Message")`
- L679 _public member_ `FGuid DestinationEndpointId;` — `UPROPERTY(VisibleAnywhere, Category="Concert Custom Message")`
- L683 _public member_ `FConcertSessionSerializedPayload SerializedPayload;` — `UPROPERTY(VisibleAnywhere, Category="Concert Custom Message")` — The serialized payload that we're hosting.

#### struct `FConcertSession_CustomResponse`  
`struct FConcertSession_CustomResponse : public FConcertResponseData`  
_L687-719_
- reflection: `USTRUCT()`
- inherits: `FConcertResponseData`
- L691 _public function_ `virtual bool IsSafeToHandle() const override`
- L697 _public function_ `void SetResponseCode(const EConcertSessionResponseCode InResponseCode)` — Set the internal Concert response code from the custom response code from the request handler
- L718 _public member_ `FConcertSessionSerializedPayload SerializedPayload;` — `UPROPERTY(VisibleAnywhere, Category="Concert Custom Message")` — The serialized payload that we're hosting.

### `Plugins/Developer/Concert/ConcertMain/Source/Concert/Public/ConcertServerEvents.h` (Public)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace ConcertServerEvents`
- L14 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnLiveSessionCreated, bool , const IConcertServer& , TSharedRef<IConcertServerSession> );`
- L14 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnLiveSessionCreated, bool , const IConcertServer& , TSharedRef<IConcertServerSession> );` (scope `ConcertServerEvents`)
- L15 _delegate_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnArchivedSessionCreated, bool , const IConcertServer& , const FString& , const FConcertSessionInfo& );`
- L15 _prototype_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnArchivedSessionCreated, bool , const IConcertServer& , const FString& , const FConcertSessionInfo& );` (scope `ConcertServerEvents`)
- L17 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnLiveSessionDestroyed, const IConcertServer& , TSharedRef<IConcertServerSession> );`
- L17 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnLiveSessionDestroyed, const IConcertServer& , TSharedRef<IConcertServerSession> );` (scope `ConcertServerEvents`)
- L18 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnArchivedSessionDestroyed, const IConcertServer& , const FGuid& );`
- L18 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnArchivedSessionDestroyed, const IConcertServer& , const FGuid& );` (scope `ConcertServerEvents`)
- L19 _delegate_ `DECLARE_MULTICAST_DELEGATE_SixParams(FArchiveSession_WithSession, bool , const IConcertServer& , TSharedRef<IConcertServerSession> , const FString& , const FConcertSessionInfo& , const FConcertSessionFilter& );`
- L19 _prototype_ `DECLARE_MULTICAST_DELEGATE_SixParams(FArchiveSession_WithSession, bool , const IConcertServer& , TSharedRef<IConcertServerSession> , const FString& , const FConcertSessionInfo& , const FConcertSessionFilter& );` (scope `ConcertServerEvents`)
- L20 _delegate_ `DECLARE_MULTICAST_DELEGATE_SixParams(FArchiveSession_WithWorkingDir, bool , const IConcertServer& , const FString& , const FString& , const FConcertSessionInfo& , const FConcertSessionFilter& );`
- L20 _prototype_ `DECLARE_MULTICAST_DELEGATE_SixParams(FArchiveSession_WithWorkingDir, bool , const IConcertServer& , const FString& , const FString& , const FConcertSessionInfo& , const FConcertSessionFilter& );` (scope `ConcertServerEvents`)
- L22 _delegate_ `DECLARE_MULTICAST_DELEGATE_FiveParams(FCopySession, bool , const IConcertServer& , TSharedRef<IConcertServerSession> , const FString& , const FConcertSessionFilter& );`
- L22 _prototype_ `DECLARE_MULTICAST_DELEGATE_FiveParams(FCopySession, bool , const IConcertServer& , TSharedRef<IConcertServerSession> , const FString& , const FConcertSessionFilter& );` (scope `ConcertServerEvents`)
- L23 _delegate_ `DECLARE_MULTICAST_DELEGATE_SixParams(FExportSession, bool , const IConcertServer& , const FGuid& , const FString& , const FConcertSessionFilter& , bool );`
- L23 _prototype_ `DECLARE_MULTICAST_DELEGATE_SixParams(FExportSession, bool , const IConcertServer& , const FGuid& , const FString& , const FConcertSessionFilter& , bool );` (scope `ConcertServerEvents`)
- L24 _delegate_ `DECLARE_MULTICAST_DELEGATE_SixParams(FRestoreSession, bool , const IConcertServer& , const FGuid& , const FString& , const FConcertSessionInfo& , const FConcertSessionFilter& );`
- L24 _prototype_ `DECLARE_MULTICAST_DELEGATE_SixParams(FRestoreSession, bool , const IConcertServer& , const FGuid& , const FString& , const FConcertSessionInfo& , const FConcertSessionFilter& );` (scope `ConcertServerEvents`)
- L26 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnLiveSessionRenamed, const IConcertServer& , TSharedRef<IConcertServerSession> );`
- L26 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnLiveSessionRenamed, const IConcertServer& , TSharedRef<IConcertServerSession> );` (scope `ConcertServerEvents`)
- L27 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnArchivedSessionRenamed, const IConcertServer& , const FString& , const FConcertSessionInfo& );`
- L27 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnArchivedSessionRenamed, const IConcertServer& , const FString& , const FConcertSessionInfo& );` (scope `ConcertServerEvents`)
- L29 _prototype_ `FOnLiveSessionCreated& OnLiveSessionCreated();` (scope `ConcertServerEvents`)
- L30 _prototype_ `FOnArchivedSessionCreated& OnArchivedSessionCreated();` (scope `ConcertServerEvents`)
- L31 _prototype_ `FOnLiveSessionDestroyed& OnLiveSessionDestroyed();` (scope `ConcertServerEvents`)
- L32 _prototype_ `FOnArchivedSessionDestroyed& OnArchivedSessionDestroyed();` (scope `ConcertServerEvents`)
- L33 _prototype_ `FArchiveSession_WithSession& ArchiveSession_WithSession();` (scope `ConcertServerEvents`)
- L34 _prototype_ `FArchiveSession_WithWorkingDir& ArchiveSession_WithWorkingDir();` (scope `ConcertServerEvents`)
- L35 _prototype_ `FCopySession& CopySession();` (scope `ConcertServerEvents`)
- L36 _prototype_ `FExportSession& ExportSession();` (scope `ConcertServerEvents`)
- L37 _prototype_ `FRestoreSession& RestoreSession();` (scope `ConcertServerEvents`)
- L38 _prototype_ `FOnLiveSessionRenamed& OnLiveSessionRenamed();` (scope `ConcertServerEvents`)
- L39 _prototype_ `FOnArchivedSessionRenamed& OnArchivedSessionRenamed();` (scope `ConcertServerEvents`)

### `Plugins/Developer/Concert/ConcertMain/Source/Concert/Public/ConcertSession.h` (Public)


#### class `FConcertSessionCommonImpl`  
`class FConcertSessionCommonImpl`  
_L16-85_
- desc: Common implementation for Concert Client and Server sessions (@see IConcertSession for the API description). @note	This doesn't inherit from any session interface, but does implement some of their API with a "Common" prefix on the function names. Interface implementations can also inherit from this common impl and then call the "Common" functions from the interface overrides.
- L19 _public prototype_ `explicit FConcertSessionCommonImpl(const FConcertSessionInfo& InSessionInfo);`
- L21 _public prototype_ `void CommonStartup();`
- L22 _public prototype_ `void CommonShutdown();`
- L24 _public function_ `const FGuid& CommonGetId() const`
- L29 _public function_ `const FString& CommonGetName() const`
- L34 _public function_ `void CommonSetName(const FString& NewName)`
- L39 _public function_ `const FConcertSessionInfo& CommonGetSessionInfo() const`
- L44 _public prototype_ `TArray<FGuid> CommonGetSessionClientEndpointIds() const;`
- L45 _public prototype_ `TArray<FConcertSessionClientInfo> CommonGetSessionClients() const;`
- L46 _public prototype_ `bool CommonFindSessionClient(const FGuid& EndpointId, FConcertSessionClientInfo& OutSessionClientInfo) const;`
- L48 _public prototype_ `FConcertScratchpadRef CommonGetScratchpad() const;`
- L49 _public prototype_ `FConcertScratchpadPtr CommonGetClientScratchpad(const FGuid& ClientEndpointId) const;`
- L51 _public prototype_ `FDelegateHandle CommonRegisterCustomEventHandler(const FName& EventMessageType, const TSharedRef<IConcertSessionCustomEventHandler>& Handler);`
- L52 _public prototype_ `void CommonUnregisterCustomEventHandler(const FName& EventMessageType, const FDelegateHandle EventHandle);`
- L53 _public prototype_ `void CommonUnregisterCustomEventHandler(const FName& EventMessageType, const void* EventHandler);`
- L54 _public prototype_ `void CommonClearCustomEventHandler(const FName& EventMessageType);`
- L55 _public prototype_ `void CommonHandleCustomEvent(const FConcertMessageContext& Context);`
- L57 _public prototype_ `void CommonRegisterCustomRequestHandler(const FName& RequestMessageType, const TSharedRef<IConcertSessionCustomRequestHandler>& Handler);`
- L58 _public prototype_ `void CommonUnregisterCustomRequestHandler(const FName& RequestMessageType);`
- L59 _public prototype_ `TFuture<FConcertSession_CustomResponse> CommonHandleCustomRequest(const FConcertMessageContext& Context);`
- L61 _public prototype_ `static bool CommonBuildCustomEvent(const UScriptStruct* EventType, const void* EventData, const FGuid& SourceEndpointId, const TArray<FGuid>& DestinationEndpointIds, FConcertSession_CustomEvent& OutCustomEvent);`
- L62 _public prototype_ `static bool CommonBuildCustomRequest(const UScriptStruct* RequestType, const void* RequestData, const FGuid& SourceEndpointId, const FGuid& DestinationEndpointId, FConcertSession_CustomRequest& OutCustomRequest);`
- L63 _public prototype_ `static void CommonHandleCustomResponse(const FConcertSession_CustomResponse& Response, const TSharedRef<IConcertSessionCustomResponseHandler>& Handler);`
- L67 _protected member_ `FConcertSessionInfo SessionInfo;` — Information about this session
- L70 _protected member_ `FConcertScratchpadPtr Scratchpad;` — The scratchpad for this session
- L78 _protected member_ `TMap<FGuid, FSessionClient> SessionClients;`
- L81 _protected member_ `TMap<FName, TArray<TSharedPtr<IConcertSessionCustomEventHandler>>> CustomEventHandlers;` — Map of custom event handlers for this session
- L84 _protected member_ `TMap<FName, TSharedPtr<IConcertSessionCustomRequestHandler>> CustomRequestHandlers;` — Map of custom request handlers for this session

#### struct `FConcertSessionCommonImpl::FSessionClient`  
`struct FSessionClient`  
_L73-77_
- desc: Map of clients connected to this session (excluding us if we're a client session)
- L75 _public member_ `FConcertSessionClientInfo ClientInfo;`
- L76 _public member_ `FConcertScratchpadPtr Scratchpad;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CONCERT_API`

### `Plugins/Developer/Concert/ConcertMain/Source/Concert/Public/ConcertSettings.h` (Public)


#### struct `FConcertSessionSettings`  
`struct FConcertSessionSettings`  
_L29-84_
- reflection: `USTRUCT()`
- L33 _public function_ `void Initialize()`
- L39 _public function_ `bool ValidateRequirements(const FConcertSessionSettings& Other, FText* OutFailureReason = nullptr) const`
- L67 _public member_ `FString ProjectName;` — `UPROPERTY(config, VisibleAnywhere, Category="Session Settings")` — Name of the project of the session. Can be specified on the server cmd with `-CONCERTPROJECT=`
- L74 _public member_ `uint32 BaseRevision = 0;` — `UPROPERTY(config, VisibleAnywhere, Category="Session Settings")` — Base Revision the session was created at. Can be specified on the server cmd with `-CONCERTREVISION=`
- L81 _public member_ `FString ArchiveNameOverride;` — `UPROPERTY(config, VisibleAnywhere, Category="Session Settings")` — Override the default name chosen when archiving this session. Can be specified on the server cmd with `-CONCERTSAVESESSIONAS=`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace ConcertSettingsUtils`
- L19 _prototype_ `FText ValidateDisplayName(const FString& Name);` (scope `ConcertSettingsUtils`) — Returns an error messages if the user display name is invalid, otherwise, returns an empty text.
- L22 _prototype_ `FText ValidateSessionName(const FString& Name);` (scope `ConcertSettingsUtils`) — Returns an error messages if the specified session name is invalid, otherwise, returns an empty text.
- L25 _prototype_ `FText ValidateFileSharingPath(const FString& Path);` (scope `ConcertSettingsUtils`) — Returns an error messages if the specified path name is invalid, otherwise, returns an empty text.

### `Plugins/Developer/Concert/ConcertMain/Source/Concert/Public/ConcertTransportEvents.h` (Public)


#### enum `EConcertLogMessageAction`  
`enum class EConcertLogMessageAction : uint8`  
_L13-27_
- reflection: `UENUM()`
- L15 _public enumerator_ `None`
- L16 _public enumerator_ `Send`
- L17 _public enumerator_ `Publish`
- L18 _public enumerator_ `Receive`
- L19 _public enumerator_ `Queue`
- L20 _public enumerator_ `Discard`
- L21 _public enumerator_ `Duplicate`
- L22 _public enumerator_ `TimeOut`
- L23 _public enumerator_ `Process`
- L24 _public enumerator_ `EndpointDiscovery`
- L25 _public enumerator_ `EndpointTimeOut`
- L26 _public enumerator_ `EndpointClosure`

#### struct `FConcertLog`  
`struct FConcertLog`  
_L30-72_
- reflection: `USTRUCT()`
- L35 _public member_ `uint64 Frame = 0;` — `UPROPERTY()`
- L38 _public member_ `FGuid MessageId;` — `UPROPERTY()`
- L41 _public member_ `uint16 MessageOrderIndex = 0;` — `UPROPERTY()`
- L44 _public member_ `uint16 ChannelId = 0;` — `UPROPERTY()`
- L47 _public member_ `FDateTime Timestamp = {0};` — `UPROPERTY()`
- L50 _public member_ `EConcertLogMessageAction MessageAction = EConcertLogMessageAction::None;` — `UPROPERTY()`
- L53 _public member_ `FName MessageTypeName;` — `UPROPERTY()`
- L56 _public member_ `FGuid OriginEndpointId;` — `UPROPERTY()`
- L59 _public member_ `FGuid DestinationEndpointId;` — `UPROPERTY()`
- L62 _public member_ `FName CustomPayloadTypename;` — `UPROPERTY()`
- L65 _public member_ `int32 CustomPayloadUncompressedByteSize = 0;` — `UPROPERTY()`
- L68 _public member_ `FString StringPayload;` — `UPROPERTY()`
- L71 _public member_ `FConcertSessionSerializedPayload SerializedPayload;` — `UPROPERTY(Transient)`

#### Free symbols / members of external scopes

- L74 _namespace_ `namespace ConcertTransportEvents`
- L76 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FConcertTransportLoggingEnabledChanged, bool );`
- L76 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FConcertTransportLoggingEnabledChanged, bool );` (scope `ConcertTransportEvents`)
- L77 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FConcertClientLogEvent, const IConcertClient&, const FConcertLog&);`
- L77 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FConcertClientLogEvent, const IConcertClient&, const FConcertLog&);` (scope `ConcertTransportEvents`)
- L78 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FConcertServerLogEvent, const IConcertServer&, const FConcertLog&);`
- L78 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FConcertServerLogEvent, const IConcertServer&, const FConcertLog&);` (scope `ConcertTransportEvents`)
- L80 _prototype_ `bool IsLoggingEnabled();` (scope `ConcertTransportEvents`)
- L81 _prototype_ `void SetLoggingEnabled(bool bEnabled);` (scope `ConcertTransportEvents`)
- L83 _prototype_ `FConcertTransportLoggingEnabledChanged& OnConcertTransportLoggingEnabledChangedEvent();` (scope `ConcertTransportEvents`)
- L85 _prototype_ `FConcertClientLogEvent& OnConcertClientLogEvent();` (scope `ConcertTransportEvents`) — Use this when your local instance is a client. All client-generated logs are emitted by this event.
- L87 _prototype_ `FConcertServerLogEvent& OnConcertServerLogEvent();` (scope `ConcertTransportEvents`) — Use this when your local instance is a server. All server-generated logs are emitted by this event.

### `Plugins/Developer/Concert/ConcertMain/Source/Concert/Public/ConcertUtil.h` (Public)


#### Free symbols / members of external scopes

- L12 _typedef_ `using FLogListener = TFunction<void(const FConcertLog&)>;`
- L14 _namespace_ `namespace ConcertUtil`
- L18 _prototype_ `bool DeleteDirectoryTree(const TCHAR* InDirectoryToDelete, const TCHAR* InMoveToDirBeforeDelete = nullptr);` (scope `ConcertUtil`) — Delete a directory tree via a move and delete
- L21 _prototype_ `bool Copy(FArchive& DstAr, FArchive& SrcAr, int64 Size);` (scope `ConcertUtil`) — Copy the specified data size from a source archive into a destination archive.
- L24 _prototype_ `void SetVerboseLogging(bool bInState);` (scope `ConcertUtil`) — Turn on verbose logging for all loggers (including console loggers).
- L27 _prototype_ `IConcertTransportLoggerRef CreateLogger(const FConcertEndpointContext& InOwnerContext, FLogListener LogListenerFunc);` (scope `ConcertUtil`) — Factory function for use with FConcertTransportLoggerFactory

### `Plugins/Developer/Concert/ConcertMain/Source/Concert/Public/ConcertVersion.h` (Public)


#### enum `EConcertVersionValidationMode`  
`enum EConcertVersionValidationMode : uint8`  
_L12-20_
- desc: Modes that can be used when validating Concert version information
- L15 _public enumerator_ `Identical` — Check that the version information is identical
- L17 _public enumerator_ `Compatible` — Check that the version information is compatible (other version is equal or newer than the current version)
- L19 _public enumerator_ `PatchCompatible` — Check that the major and minor version are identical but allow compatible patch versions.

#### struct `FConcertFileVersionInfo`  
`struct FConcertFileVersionInfo`  
_L24-45_
- reflection: `USTRUCT()`
- desc: Holds file version information
- L29 _public prototype_ `void Initialize();` — Initialize this version info from the compiled in data
- L32 _public prototype_ `bool Validate(const FConcertFileVersionInfo& InOther, const EConcertVersionValidationMode InValidationMode, FText* OutFailureReason = nullptr) const;` — Validate this version info against another
- L36 _public member_ `int32 FileVersion = 0;` — `UPROPERTY()` — UE4 File version
- L40 _public member_ `int32 FileVersionUE5 = 0;` — `UPROPERTY()` — UE5 File version
- L44 _public member_ `int32 FileVersionLicensee = 0;` — `UPROPERTY()` — Licensee file version

#### struct `FConcertEngineVersionInfo`  
`struct FConcertEngineVersionInfo`  
_L49-74_
- reflection: `USTRUCT()`
- desc: Holds engine version information
- L54 _public prototype_ `void Initialize(const FEngineVersion& InVersion);` — Initialize this version info from the given version
- L57 _public prototype_ `bool Validate(const FConcertEngineVersionInfo& InOther, const EConcertVersionValidationMode InValidationMode, FText* OutFailureReason = nullptr) const;` — Validate this version info against another
- L61 _public member_ `uint16 Major = 0;` — `UPROPERTY()` — Major version number
- L65 _public member_ `uint16 Minor = 0;` — `UPROPERTY()` — Minor version number
- L69 _public member_ `uint16 Patch = 0;` — `UPROPERTY()` — Patch version number
- L73 _public member_ `uint32 Changelist = 0;` — `UPROPERTY()` — Changelist number. This is used to arbitrate when Major/Minor/Patch version numbers match

#### struct `FConcertCustomVersionInfo`  
`struct FConcertCustomVersionInfo`  
_L78-99_
- reflection: `USTRUCT()`
- desc: Holds custom version information
- L83 _public prototype_ `void Initialize(const FCustomVersion& InVersion);` — Initialize this version info from the given version
- L86 _public prototype_ `bool Validate(const FConcertCustomVersionInfo& InOther, const EConcertVersionValidationMode InValidationMode, FText* OutFailureReason = nullptr) const;` — Validate this version info against another
- L90 _public member_ `FName FriendlyName;` — `UPROPERTY()` — Friendly name of the version
- L94 _public member_ `FGuid Key;` — `UPROPERTY()` — Unique custom key
- L98 _public member_ `int32 Version = 0;` — `UPROPERTY()` — Custom version

#### struct `FConcertSessionVersionInfo`  
`struct FConcertSessionVersionInfo`  
_L103-127_
- reflection: `USTRUCT()`
- desc: Holds version information for a session
- L108 _public prototype_ `void Initialize(bool bSupportMixedBuildTypes);` — Initialize this version info from the compiled in data
- L111 _public prototype_ `bool Validate(const FConcertSessionVersionInfo& InOther, const EConcertVersionValidationMode InValidationMode, FText* OutFailureReason = nullptr) const;` — Validate this version info against another
- L114 _public prototype_ `FText AsText() const;` — Return the version information in string represenation.
- L118 _public member_ `FConcertFileVersionInfo FileVersion;` — `UPROPERTY()` — File version info
- L122 _public member_ `FConcertEngineVersionInfo EngineVersion;` — `UPROPERTY()` — Engine version info
- L126 _public member_ `TArray<FConcertCustomVersionInfo> CustomVersions;` — `UPROPERTY()` — Custom version info

### `Plugins/Developer/Concert/ConcertMain/Source/Concert/Public/IConcertFileSharingService.h` (Public)


#### class `IConcertFileSharingService`  
`class IConcertFileSharingService`  
_L24-98_
- desc: Implements a file sharing service used as a side channel to ConcertTransport to exchange large files. This API is designed to work hand in hand with the request/response/event layer. When a file needs to be exchanged between the client and the server: The publisher side would: - Publish a file using file sharing service. The service tracks the request and capture the file for sharing (can sent it to a server asynchronously, can be copied to a shared folder, etc.) - Notify the consumer(s) by sending a Concert request/event/response with the ID of the published file. The consumer(s) side would: - Receive and process the Concert request/event/response and extract the file ID. - Create a stream to read the shared file, ideally in a background task. If required, new method could be added to simplify asynchrous IO. * @note The lifetime of the shared files is implementation specific.
- L27 _public prototype_ `virtual ~IConcertFileSharingService() = default;`
- L30 _public prototype_ `virtual IConcertFileSharingService* Clone() const = 0;` — Make a clone of this sharing service to be used. Ownership is transferred to the caller. Callers can choose to wrap this into a unique or shared pointer.
- L33 _public prototype_ `virtual bool IsEnabled() const = 0;` — Indicates if the file sharing service is enabled.
- L36 _public prototype_ `virtual void SetEnabled(bool bInEnabled) = 0;` — Turn on/off the file sharing service.
- L45 _public prototype_ `virtual void SetPath(const FString& FileShareRoot) = 0;` — Sets the desired path to use for the service. Implementors have the right to ignore the path specified. Implementors should set the enabled state based on if the path can be written. @param FileShareRoot to set as the root folder for content.
- L50 _public prototype_ `virtual FString GetPath() const = 0;` — Get the assign path for file sharing root.
- L53 _public prototype_ `virtual void Delete(const FString& InFileId) = 0;` — Deletes the specified outfile id.
- L62 _public prototype_ `virtual bool Publish(const FString& Pathname, FString& OutFileId) = 0;` — Copy the specified files in a uniquely named file stored in the service directory for sharing. The lifetime of the shared file is implementation specific. @param Pathname The file to copy and share. @param OutFileId The ID of the published file. The publisher is expected to send the ID through the Concert transport layer to the consumer(s) (request/response/event). @return True if the file was published successfully.
- L73 _public prototype_ `virtual bool Publish(FArchive& SrcAr, int64 Count, FString& OutFileId) = 0;` — Copies up to Count bytes contained in the archives in a uniquely named file stored in the service directory for sharing. The functions reads the archive from its current position up to \a Count bytes. The lifetime of the shared file is implementation specific. @param SrcAr The Archive containing the bytes to share. The archive is already at the right position, not necessarily 0. @param Count The number of bytes to read from the archive. @param OutFileId The ID of the published file. The publisher is expected to send the ID through the Concert transport layer to the consumer(s) (request/response/event). @return True if the file was published successfully.
- L81 _public function_ `bool Publish(FArchive& SrcAr, FString& OutFileId)` — Copies all the bytes contained in the archives in a uniquely named file stored in the service directory for sharing. @param SrcAr The Archive containing the bytes to share. Expected to be at position 0. @param OutFileId The ID of the published file. The publisher is expected to send the ID through the Concert transport layer to the consumer(s) (request/response/event). @return True if the file was published successfully.
- L89 _public prototype_ `virtual TSharedPtr<FArchive> CreateReader(const FString& InFileId) = 0;` — Open a shared file for consumption. @param InFileId The Id of the file to read. The consumer is expected to receives this ID through the Concert transport layer (request/response/event). @return An archive (loading mode) to stream the content of the file or nullptr if the file could not be found or opened. @note The function can be used to poll until the resources is fully available. A more sophisticated API could be added to wait for a ressource if needed later.
- L97 _public prototype_ `virtual TSharedPtr<FArchive> CreateWriter(FString& OutFileId) = 0;` — Open a file for writing. @param OutFileId The id of the file opened for write. @return An archive (write mode) to stream the content of the file.

### `Plugins/Developer/Concert/ConcertMain/Source/Concert/Public/IConcertModule.h` (Public)


#### class `IConcertModule`  
`class IConcertModule : public IModuleInterface`  
_L12-37_
- inherits: `IModuleInterface`
- desc: Interface for the Main Concert module.
- L21 _public function_ `static inline IConcertModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L32 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() during shutdown if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Plugins/Developer/Concert/ConcertMain/Source/Concert/Public/IConcertServerEventSink.h` (Public)


#### struct `FInternalLiveSessionCreationParams`  
`struct FInternalLiveSessionCreationParams`  
_L14-20_
- L16 _public prototype_ `DECLARE_DELEGATE(FOnSessionModified) FOnSessionModified OnModifiedCallback;`

#### class `IConcertServerEventSink`  
`class IConcertServerEventSink`  
_L23-101_
- desc: Interface for events that Concert server can emit
- L29 _public prototype_ `virtual void GetSessionsFromPath(const IConcertServer& InServer, const FString& InPath, TArray<FConcertSessionInfo>& OutSessionInfos, TArray<FDateTime>* OutSessionCreationTimes = nullptr) = 0;` — Called to enumerate all the sessions under the given root path and retrieve their session info.
- L36 _public prototype_ `virtual bool OnLiveSessionCreated(const IConcertServer& InServer, TSharedRef<IConcertServerSession> InLiveSession, const FInternalLiveSessionCreationParams& AdditionalParams) = 0;` — Called after the session has been created (and before Startup has been called on it). @note This function is called for both newly created sessions and after recovering a live session during server start-up. @return true if the session creation could be completed without error, false otherwise (ex if the database fails to open).
- L42 _public prototype_ `virtual void OnLiveSessionDestroyed(const IConcertServer& InServer, TSharedRef<IConcertServerSession> InLiveSession) = 0;` — Called before the session is destroyed (and before Shutdown is called on it). @note Destroyed in this case means that the resources for the session should be closed/freed, but not that persistent data should be deleted from disk.
- L49 _public prototype_ `virtual bool OnArchivedSessionCreated(const IConcertServer& InServer, const FString& InArchivedSessionRoot, const FConcertSessionInfo& InArchivedSessionInfo) = 0;` — Called after the session has been created. @note This function is called for both newly created sessions and after recovering an archived session during server start-up. @return true if the session creation could be completed without error, false otherwise (ex if the database fails to open).
- L55 _public prototype_ `virtual void OnArchivedSessionDestroyed(const IConcertServer& InServer, const FGuid& InArchivedSessionId) = 0;` — Called before the session is destroyed. @note Destroyed in this case means that the resources for the session should be closed/freed, but not that persistent data should be deleted from disk.
- L61 _public prototype_ `virtual bool ArchiveSession(const IConcertServer& InServer, TSharedRef<IConcertServerSession> InLiveSession, const FString& InArchivedSessionRoot, const FConcertSessionInfo& InArchivedSessionInfo, const FConcertSessionFilter& InSessionFilter) = 0;` — Called to migrate the data for a live session into an archived session. @note OnArchivedSessionCreated will be called if this archive was successful.
- L67 _public prototype_ `virtual bool ArchiveSession(const IConcertServer& InServer, const FString& InLiveSessionWorkingDir, const FString& InArchivedSessionRoot, const FConcertSessionInfo& InArchivedSessionInfo, const FConcertSessionFilter& InSessionFilter) = 0;` — Called to migrate the data of an offline live session into and offline archived session. @note This function is use at boot time to auto-archive session that were not archived at shutdown because the server crashed or was killed.
- L72 _public prototype_ `virtual bool CopySession(const IConcertServer& InServer, TSharedRef<IConcertServerSession> InLiveSession, const FString& NewSessionRoot, const FConcertSessionFilter& InSessionFilter) = 0;` — Called to copy the data of a live session into another live session.
- L78 _public prototype_ `virtual bool ExportSession(const IConcertServer& InServer, const FGuid& InSessionId, const FString& DestDir, const FConcertSessionFilter& InSessionFilter, bool bAnonymizeData) = 0;` — Called to migrate and gather the data of a live or archived session to a directory for external usage. @note As opposed to archiving a session, once exported, the session is not tracked anymore by the server and the exported files can be copied/modified while the server is running.
- L84 _public prototype_ `virtual bool RestoreSession(const IConcertServer& InServer, const FGuid& InArchivedSessionId, const FString& InLiveSessionRoot, const FConcertSessionInfo& InLiveSessionInfo, const FConcertSessionFilter& InSessionFilter) = 0;` — Called to migrate the data for an archived session into a live session. @note OnLiveSessionCreated will be called if this restoration was successful.
- L90 _public prototype_ `virtual bool GetUnmutedSessionActivities(const IConcertServer& InServer, const FGuid& SessionId, int64 FromActivityId, int64 ActivityCount, TArray<FConcertSessionSerializedPayload>& OutActivities, TMap<FGuid, FConcertClientInfo>& OutEndpointClientInfoMap, bool bIncludeDetails) = 0;` — Called to get the all activities that are not muted (i.e. don't have EConcertSyncActivityFlags::Muted flag set) for an archived or a live session without being connected to it. @note If ActivityCount is negative, the function returns the last activities (the tail) from Max(1, TotalActivityCount + ActivityCount + 1)
- L95 _public prototype_ `virtual void OnLiveSessionRenamed(const IConcertServer& InServer, TSharedRef<IConcertServerSession> InLiveSession) = 0;` — Called when a live session is renamed.
- L100 _public prototype_ `virtual void OnArchivedSessionRenamed(const IConcertServer& InServer, const FString& InArchivedSessionRoot, const FConcertSessionInfo& InArchivedSessionInfo) = 0;` — Called when an archived session is renamed.

#### Free symbols / members of external scopes

- L16 _delegate_ `DECLARE_DELEGATE(FOnSessionModified) FOnSessionModified OnModifiedCallback;`

### `Plugins/Developer/Concert/ConcertMain/Source/Concert/Public/IConcertSession.h` (Public)


#### struct `FConcertClientInfoUpdate`  
`struct FConcertClientInfoUpdate`  
_L26-63_
- desc: Contains the FConcertClientInfo fields that can be updated.
- L28 _public member_ `TOptional<FString> DisplayName;`
- L29 _public member_ `TOptional<FLinearColor> AvatarColor;`
- L30 _public member_ `TOptional<FString> DesktopAvatarActorClass;`
- L31 _public member_ `TOptional<FString> VRAvatarActorClass;`
- L34 _public function_ `bool ApplyTo(FConcertClientInfo& InOutInfo) const` — Applies the valid optional fields to the specified client info, and return true if the client info was modified, false otherwise.

#### struct `FConcertSequencedCustomEvent`  
`struct FConcertSequencedCustomEvent`  
_L67-81_
- L69 _public prototype_ `FConcertSequencedCustomEvent() = default;`
- L70 _public prototype_ `~FConcertSequencedCustomEvent() = default;`
- L75 _private function_ `FConcertSequencedCustomEvent(int32 InIndex) : Index(InIndex)`
- L80 _private member_ `int32 Index = INDEX_NONE;`

#### class `FConcertSequencedCustomEventManager`  
`class FConcertSequencedCustomEventManager`  
_L84-162_
- desc: Allows users to reserve a spot in the outbound queues.
- L87 _public function_ `FConcertSequencedCustomEventManager()`
- L90 _public prototype_ `~FConcertSequencedCustomEventManager() = default;`
- L92 _public function_ `FConcertSequencedCustomEvent AddSequencedCustomEvent()`
- L98 _public function_ `void RemoveSequencedEvent(const FConcertSequencedCustomEvent& EventDetails)`
- L107 _public function_ `bool HasEventsPending() const`
- L120 _public function_ `TOptional<FPendingCustomEvent> PopSendEvent()`
- L143 _public function_ `void FillPendingSequenceEvent(const FConcertSequencedCustomEvent& InEventId, FPendingCustomEvent InEventData)`
- L152 _public function_ `bool CanSend(const FConcertSequencedCustomEvent& InEventId) const`
- L158 _private member_ `TMap<int32, TOptional<FPendingCustomEvent> > Events;`
- L160 _private member_ `int32 LastSendId = 0;`
- L161 _private member_ `int32 CurrentId = 0;`

#### struct `FConcertSequencedCustomEventManager::FPendingCustomEvent`  
`struct FPendingCustomEvent`  
_L112-118_
- L114 _public member_ `FConcertSession_CustomEvent CustomEvent;`
- L115 _public member_ `EConcertMessageFlags Flags;`
- L116 _public member_ `TMap<FName, FString> Annotations;`
- L117 _public member_ `FGuid ServerEndpointId;`

#### class `IConcertSession`  
`class IConcertSession`  
_L165-341_
- desc: Interface for Concert sessions
- L168 _public prototype_ `virtual ~IConcertSession() = default;`
- L170 _public prototype_ `virtual void Startup() = 0;`
- L172 _public prototype_ `virtual void Shutdown() = 0;`
- L174 _public prototype_ `virtual const FGuid& GetId() const = 0;`
- L176 _public prototype_ `virtual const FString& GetName() const = 0;`
- L178 _public prototype_ `virtual const FConcertSessionInfo& GetSessionInfo() const = 0;`
- L181 _public prototype_ `virtual FString GetSessionWorkingDirectory() const = 0;` — Give the working directory for this session
- L184 _public prototype_ `virtual TArray<FGuid> GetSessionClientEndpointIds() const = 0;` — Get the list of connected client endpoint IDs
- L187 _public prototype_ `virtual TArray<FConcertSessionClientInfo> GetSessionClients() const = 0;` — Get the information about all connected clients
- L190 _public prototype_ `virtual bool FindSessionClient(const FGuid& EndpointId, FConcertSessionClientInfo& OutSessionClientInfo) const = 0;` — Find the the client for the specified endpoint ID
- L195 _public prototype_ `virtual FConcertScratchpadRef GetScratchpad() const = 0;` — Get the scratchpad associated with this concert session.
- L200 _public prototype_ `virtual FConcertScratchpadPtr GetClientScratchpad(const FGuid& ClientEndpointId) const = 0;` — Get the scratchpad associated with the given client ID.
- L207 _public function_ `template<typename EventType> FDelegateHandle RegisterCustomEventHandler(typename TConcertFunctionSessionCustomEventHandler<EventType>::FFuncType Func)` — Register a custom event handler for this session
- L216 _public function_ `template<typename EventType, typename HandlerType> FDelegateHandle RegisterCustomEventHandler(HandlerType* Handler, typename TConcertRawSessionCustomEventHandler<EventType, HandlerType>::FFuncType Func)` — Register a custom event handler for this session
- L225 _public function_ `template<typename EventType> void UnregisterCustomEventHandler(const FDelegateHandle EventHandle)` — Unregister a custom event handler for this session
- L234 _public function_ `template<typename EventType, typename HandlerType> void UnregisterCustomEventHandler(HandlerType* EventHandler)` — Unregister a custom event handler for this session
- L243 _public function_ `template<typename EventType> void ClearCustomEventHandler()` — Clear a custom event handler for this session
- L252 _public function_ `template<typename EventType> void SendCustomEvent(const EventType& Event, const FGuid& DestinationEndpointId, EConcertMessageFlags Flags, TOptional<FConcertSequencedCustomEvent> SequencedId = {})` — Send a custom event event to the given endpoint
- L261 _public function_ `template<typename EventType> void SendCustomEvent(const EventType& Event, const TArray<FGuid>& DestinationEndpointIds, EConcertMessageFlags Flags, TOptional<FConcertSequencedCustomEvent> SequencedId = {})` — Send a custom event event to the given endpoints
- L270 _public function_ `template<typename RequestType, typename ResponseType> void RegisterCustomRequestHandler(typename TConcertFunctionSessionCustomRequestHandler<RequestType, ResponseType>::FFuncType Func)` — Register a custom request handler for this session
- L279 _public function_ `template<typename RequestType, typename ResponseType, typename HandlerType> void RegisterCustomRequestHandler(HandlerType* Handler, typename TConcertRawSessionCustomRequestHandler<RequestType, ResponseType, HandlerType>::FFuncType Func)` — Register a custom request handler for this session
- L288 _public function_ `template<typename RequestType> void UnregisterCustomRequestHandler()` — Unregister a custom request handler for this session
- L297 _public function_ `template<typename RequestType, typename ResponseType> TFuture<ResponseType> SendCustomRequest(const RequestType& Request, const FGuid& DestinationEndpointId)` — Send a custom request to the given endpoint
- L308 _protected prototype_ `virtual FDelegateHandle InternalRegisterCustomEventHandler(const FName& EventMessageType, const TSharedRef<IConcertSessionCustomEventHandler>& Handler) = 0;` — Register a custom event handler for this session
- L313 _protected prototype_ `virtual void InternalUnregisterCustomEventHandler(const FName& EventMessageType, const FDelegateHandle EventHandle) = 0;` — Unregister a custom event handler for this session
- L314 _protected prototype_ `virtual void InternalUnregisterCustomEventHandler(const FName& EventMessageType, const void* EventHandler) = 0;`
- L319 _protected prototype_ `virtual void InternalClearCustomEventHandler(const FName& EventMessageType) = 0;` — Clear a custom event handler for this session
- L324 _protected prototype_ `virtual void InternalSendCustomEvent(const UScriptStruct* EventType, const void* EventData, const TArray<FGuid>& DestinationEndpointIds, EConcertMessageFlags Flags, TOptional<FConcertSequencedCustomEvent> InSequenceId={}) = 0;` — Send a custom event event to the given endpoints
- L329 _protected prototype_ `virtual void InternalRegisterCustomRequestHandler(const FName& RequestMessageType, const TSharedRef<IConcertSessionCustomRequestHandler>& Handler) = 0;` — Register a custom request handler for this session
- L334 _protected prototype_ `virtual void InternalUnregisterCustomRequestHandler(const FName& RequestMessageType) = 0;` — Unregister a custom request handler for this session
- L339 _protected prototype_ `virtual void InternalSendCustomRequest(const UScriptStruct* RequestType, const void* RequestData, const FGuid& DestinationEndpointId, const TSharedRef<IConcertSessionCustomResponseHandler>& Handler) = 0;` — Send a custom request to the given endpoint

#### class `IConcertServerSession`  
`class IConcertServerSession : public IConcertSession`  
_L344-363_
- inherits: `IConcertSession`
- desc: Interface for Concert server sessions
- L347 _public prototype_ `virtual ~IConcertServerSession() = default;`
- L350 _public prototype_ `virtual void SetName(const FString& NewName) = 0;` — Rename the session.
- L353 _public prototype_ `virtual FMessageAddress GetClientAddress(const FGuid& ClientEndpointId) const = 0;` — Gets the client's address used by the messaging system. Can be fed into
- L356 _public prototype_ `virtual FOnConcertServerSessionTick& OnTick() = 0;` — Callback when a server session gets ticked
- L359 _public prototype_ `virtual FOnConcertServerSessionClientChanged& OnSessionClientChanged() = 0;` — Callback when a session client state changes
- L362 _public prototype_ `virtual FOnConcertMessageAcknowledgementReceivedFromLocalEndpoint& OnConcertMessageAcknowledgementReceived() = 0;` — Callback when a session message is acknowledged

#### class `IConcertClientSession`  
`class IConcertClientSession : public IConcertSession`  
_L366-412_
- inherits: `IConcertSession`
- desc: Interface for Concert client sessions
- L369 _public prototype_ `virtual ~IConcertClientSession() = default;`
- L372 _public prototype_ `virtual EConcertConnectionStatus GetConnectionStatus() const = 0;` — Get the session connection status to the server session
- L375 _public prototype_ `virtual FGuid GetSessionClientEndpointId() const = 0;` — Get the client endpoint ID
- L378 _public prototype_ `virtual FGuid GetSessionServerEndpointId() const = 0;` — Get the server endpoint ID
- L381 _public prototype_ `virtual const FConcertClientInfo& GetLocalClientInfo() const = 0;` — Get the local user's ClientInfo
- L384 _public prototype_ `virtual void UpdateLocalClientInfo(const FConcertClientInfoUpdate& UpdatedFields) = 0;` — Update the local user's ClientInfo
- L387 _public prototype_ `virtual void Connect() = 0;` — Start the connection handshake with the server session
- L390 _public prototype_ `virtual void Disconnect() = 0;` — Disconnect  gracefully from the server session
- L393 _public prototype_ `virtual FConcertSequencedCustomEventManager& GetSequencedEventManager() = 0;` — Manager for helping sequence custom events on client sessions.
- L396 _public prototype_ `virtual EConcertSendReceiveState GetSendReceiveState() const = 0;` — Get the send/receive state for this session.
- L399 _public prototype_ `virtual void SetSendReceiveState(EConcertSendReceiveState InSendReceiveState) = 0;` — Set the send/receive state for this session.
- L402 _public prototype_ `virtual FOnConcertClientSessionTick& OnTick() = 0;` — Callback when a connected client session gets ticked
- L405 _public prototype_ `virtual FOnConcertClientSessionConnectionChanged& OnConnectionChanged() = 0;` — Callback when the session connection state changes
- L408 _public prototype_ `virtual FOnConcertClientSessionClientChanged& OnSessionClientChanged() = 0;` — Callback when a session client state changes
- L411 _public prototype_ `virtual FOnConcertSessionRenamed& OnSessionRenamed() = 0;` — Callback when the session name changes.

#### Free symbols / members of external scopes

- L18 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnConcertClientSessionTick, IConcertClientSession&, float);`
- L18 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnConcertClientSessionTick, IConcertClientSession&, float);`
- L19 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnConcertServerSessionTick, IConcertServerSession&, float);`
- L19 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnConcertServerSessionTick, IConcertServerSession&, float);`
- L20 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnConcertClientSessionConnectionChanged, IConcertClientSession&, EConcertConnectionStatus);`
- L20 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnConcertClientSessionConnectionChanged, IConcertClientSession&, EConcertConnectionStatus);`
- L21 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnConcertClientSessionClientChanged, IConcertClientSession&, EConcertClientStatus, const FConcertSessionClientInfo&);`
- L21 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnConcertClientSessionClientChanged, IConcertClientSession&, EConcertClientStatus, const FConcertSessionClientInfo&);`
- L22 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnConcertServerSessionClientChanged, IConcertServerSession&, EConcertClientStatus, const FConcertSessionClientInfo&);`
- L22 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnConcertServerSessionClientChanged, IConcertServerSession&, EConcertClientStatus, const FConcertSessionClientInfo&);`
- L23 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnConcertSessionRenamed, const FString&, const FString&);`
- L23 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnConcertSessionRenamed, const FString&, const FString&);`

### `Plugins/Developer/Concert/ConcertMain/Source/Concert/Public/IConcertSessionHandler.h` (Public)


#### struct `FConcertSessionContext`  
`struct FConcertSessionContext`  
_L13-19_
- desc: Context struct for session custom message handlers
- L15 _public member_ `FGuid SourceEndpointId;`
- L16 _public member_ `FGuid MessageId;`
- L17 _public member_ `EConcertMessageFlags MessageFlags;`
- L18 _public member_ `FConcertScratchpadPtr SenderScratchpad;`

#### class `IConcertSessionCustomEventHandler`  
`class IConcertSessionCustomEventHandler`  
_L22-32_
- desc: Interface for session custom event handler
- L25 _public prototype_ `virtual ~IConcertSessionCustomEventHandler() = default;`
- L27 _public prototype_ `virtual FDelegateHandle GetHandle() const = 0;`
- L29 _public prototype_ `virtual bool HasSameObject(const void* InObject) const = 0;`
- L31 _public prototype_ `virtual void HandleEvent(const FConcertSessionContext& Context, const void* EventData) const = 0;`

#### class `FConcertSessionCustomEventHandlerBase`  
`class FConcertSessionCustomEventHandlerBase : public IConcertSessionCustomEventHandler`  
_L37-52_
- inherits: `IConcertSessionCustomEventHandler`
- desc: Common implementation of a session custom event handler.
- L40 _public function_ `explicit FConcertSessionCustomEventHandlerBase(FDelegateHandle InHandle) : Handle(MoveTemp(InHandle))`
- L45 _public function_ `virtual FDelegateHandle GetHandle() const override`
- L51 _protected member_ `FDelegateHandle Handle;`

#### class `TConcertRawSessionCustomEventHandler`  
`template<typename EventType, typename HandlerType> class TConcertRawSessionCustomEventHandler : public FConcertSessionCustomEventHandlerBase`  
_L58-85_
- inherits: `FConcertSessionCustomEventHandlerBase`
- desc: Implementation of a session custom event handler that uses a raw member function pointer with the correct event type in the handler function signature.
- L61 _public typedef_ `typedef void (HandlerType::*FFuncType)(const FConcertSessionContext&, const EventType&);`
- L63 _public function_ `TConcertRawSessionCustomEventHandler(FDelegateHandle InHandle, HandlerType* InHandler, FFuncType InFunc) : FConcertSessionCustomEventHandlerBase(MoveTemp(InHandle)) , Handler(InHandler) , Func(InFunc)`
- L72 _public function_ `virtual bool HasSameObject(const void* InObject) const override`
- L77 _public function_ `virtual void HandleEvent(const FConcertSessionContext& Context, const void* EventData) const override`
- L83 _private member_ `HandlerType* Handler;`
- L84 _private member_ `FFuncType Func;`

#### class `TConcertFunctionSessionCustomEventHandler`  
`template<typename EventType> class TConcertFunctionSessionCustomEventHandler : public FConcertSessionCustomEventHandlerBase`  
_L91-116_
- inherits: `FConcertSessionCustomEventHandlerBase`
- desc: Implementation of a session custom event handler that calls a function with the correct event type in the handler function signature.
- L94 _public typedef_ `typedef TFunction<void(const FConcertSessionContext&, const EventType&)> FFuncType;`
- L96 _public function_ `TConcertFunctionSessionCustomEventHandler(FDelegateHandle InHandle, FFuncType InFunc) : FConcertSessionCustomEventHandlerBase(MoveTemp(InHandle)) , Func(MoveTemp(InFunc))`
- L103 _public function_ `virtual bool HasSameObject(const void* InObject) const override`
- L108 _public function_ `virtual void HandleEvent(const FConcertSessionContext& Context, const void* EventData) const override`
- L115 _private member_ `FFuncType Func;` — The Handler function

#### class `IConcertSessionCustomRequestHandler`  
`class IConcertSessionCustomRequestHandler`  
_L119-127_
- desc: Interface for session custom request handler
- L122 _public prototype_ `virtual ~IConcertSessionCustomRequestHandler() = default;`
- L124 _public prototype_ `virtual UScriptStruct* GetResponseType() const = 0;`
- L126 _public prototype_ `virtual EConcertSessionResponseCode HandleRequest(const FConcertSessionContext& Context, const void* RequestData, void* ResponseData) const = 0;`

#### class `TConcertRawSessionCustomRequestHandler`  
`template<typename RequestType, typename ResponseType, typename HandlerType> class TConcertRawSessionCustomRequestHandler : public IConcertSessionCustomRequestHandler`  
_L133-161_
- inherits: `IConcertSessionCustomRequestHandler`
- desc: Implementation of a session custom request handler that calls a raw member function with the correct request type in the handler function signature.
- L136 _public typedef_ `typedef EConcertSessionResponseCode (HandlerType::*FFuncType)(const FConcertSessionContext&, const RequestType&, ResponseType&);`
- L138 _public function_ `TConcertRawSessionCustomRequestHandler(HandlerType* InHandler, FFuncType InFunc) : Handler(InHandler) , Func(InFunc)`
- L146 _public prototype_ `virtual ~TConcertRawSessionCustomRequestHandler() = default;`
- L148 _public function_ `virtual UScriptStruct* GetResponseType() const override`
- L153 _public function_ `virtual EConcertSessionResponseCode HandleRequest(const FConcertSessionContext& Context, const void* RequestData, void* ResponseData) const override`
- L159 _private member_ `HandlerType* Handler;`
- L160 _private member_ `FFuncType Func;`

#### class `TConcertFunctionSessionCustomRequestHandler`  
`template<typename RequestType, typename ResponseType> class TConcertFunctionSessionCustomRequestHandler : public IConcertSessionCustomRequestHandler`  
_L167-192_
- inherits: `IConcertSessionCustomRequestHandler`
- desc: Implementation of a session custom request handler that calls a function with the correct request type in the handler function signature.
- L170 _public typedef_ `typedef TFunction<EConcertSessionResponseCode(const FConcertSessionContext&, const RequestType&, ResponseType&)> FFuncType;`
- L172 _public function_ `TConcertFunctionSessionCustomRequestHandler(FFuncType InFunc) : Func(MoveTemp(InFunc))`
- L178 _public prototype_ `virtual ~TConcertFunctionSessionCustomRequestHandler() = default;`
- L180 _public function_ `virtual UScriptStruct* GetResponseType() const override`
- L185 _public function_ `virtual EConcertSessionResponseCode HandleRequest(const FConcertSessionContext& Context, const void* RequestData, void* ResponseData) const override`
- L191 _private member_ `FFuncType Func;`

#### class `IConcertSessionCustomResponseHandler`  
`class IConcertSessionCustomResponseHandler`  
_L195-201_
- desc: Interface for session custom request handler  TODO: replace by a generalized erased promise/future pair??
- L198 _public prototype_ `virtual ~IConcertSessionCustomResponseHandler() = default;`
- L200 _public prototype_ `virtual void HandleResponse(const void* ResponseData) = 0;`

#### class `TConcertFutureSessionCustomResponseHandler`  
`template<typename ResponseType> class TConcertFutureSessionCustomResponseHandler : public IConcertSessionCustomResponseHandler`  
_L207-232_
- inherits: `IConcertSessionCustomResponseHandler`
- desc: Implementation of a session custom response handler that uses a future to dispatch back the response
- L210 _public prototype_ `virtual ~TConcertFutureSessionCustomResponseHandler() = default;`
- L212 _public function_ `virtual void HandleResponse(const void* ResponseData) override`
- L226 _public function_ `TFuture<ResponseType> GetFuture()`
- L231 _private member_ `TPromise<ResponseType> Promise;`
