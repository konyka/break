# Plugins / LiveLinkMasterLockit

- module root: `Plugins/VirtualProduction/LiveLinkMasterLockit/Source/LiveLinkMasterLockit`
- headers: 5; symbols: 191
- symbol kinds: class=4, delegate=3, enum=9, enumerator=50, function=9, member=75, prototype=33, struct=6, typedef=1, variable=1
- PrivateDependencyModuleNames: Core, CoreUObject, Json, Networking, Sockets
- PublicDependencyModuleNames: LiveLinkInterface

### `Plugins/VirtualProduction/LiveLinkMasterLockit/Source/LiveLinkMasterLockit/Private/LiveLinkMasterLockitSource.h` (Private)


#### class `FLiveLinkMasterLockitSource`  
`class FLiveLinkMasterLockitSource : public ILiveLinkSource`  
_L21-62_
- inherits: `ILiveLinkSource`
- L25 _public prototype_ `FLiveLinkMasterLockitSource(FLiveLinkMasterLockitConnectionSettings ConnectionSettings);`
- L26 _public prototype_ `~FLiveLinkMasterLockitSource();`
- L29 _public prototype_ `virtual void ReceiveClient(ILiveLinkClient* InClient, FGuid InSourceGuid) override;`
- L31 _public prototype_ `virtual bool IsSourceStillValid() const override;`
- L33 _public prototype_ `virtual bool RequestSourceShutdown() override;`
- L35 _public prototype_ `virtual FText GetSourceType() const override;`
- L36 _public function_ `virtual FText GetSourceMachineName() const override`
- L37 _public prototype_ `virtual FText GetSourceStatus() const override;`
- L39 _public function_ `virtual TSubclassOf<ULiveLinkSourceSettings> GetSettingsClass() const`
- L43 _private prototype_ `void OpenConnection();`
- L44 _private prototype_ `void OnHandshakeEstablished_AnyThread();`
- L45 _private prototype_ `void OnFrameDataReady_AnyThread(FLensPacket InData);`
- L47 _private member_ `ILiveLinkClient* Client = nullptr;`
- L48 _private member_ `FSocket* Socket = nullptr;`
- L49 _private member_ `ISocketSubsystem* SocketSubsystem = nullptr;`
- L51 _private member_ `FLiveLinkMasterLockitConnectionSettings ConnectionSettings;`
- L52 _private member_ `FLiveLinkSubjectKey SubjectKey;`
- L53 _private member_ `FText SourceMachineName;`
- L55 _private member_ `TUniquePtr<FMasterLockitMessageThread> MessageThread;`
- L57 _private member_ `std::atomic<double> LastTimeDataReceived;`
- L58 _private member_ `std::atomic<bool> bReceivedData;`
- L61 _private member_ `const float DataReceivedTimeout = 20.0f;`

#### Free symbols / members of external scopes

- L17 _variable_ `static constexpr int MasterLockitPortNumber = 42000;` — From the MasterLockit API

### `Plugins/VirtualProduction/LiveLinkMasterLockit/Source/LiveLinkMasterLockit/Private/LiveLinkMasterLockitSourceSettings.h` (Private)


#### class `ULiveLinkMasterLockitSourceSettings`  
`class ULiveLinkMasterLockitSourceSettings : public ULiveLinkSourceSettings`  
_L11-15_
- reflection: `UCLASS()`
- inherits: `ULiveLinkSourceSettings`

### `Plugins/VirtualProduction/LiveLinkMasterLockit/Source/LiveLinkMasterLockit/Private/MasterLockitMessageThread.h` (Private)


#### struct `FLensPacket`  
`struct FLensPacket`  
_L23-35_
- L25 _public member_ `FQualifiedFrameTime FrameTime;`
- L27 _public member_ `float FocusDistance = 0.0f;`
- L28 _public member_ `float Aperture = 0.0f;`
- L29 _public member_ `float HorizontalFOV = 0.0f;`
- L30 _public member_ `int16 EntrancePupilPosition = 0;`
- L31 _public member_ `float ShadingData[6] = { 0.0f };`
- L32 _public member_ `float DistortionData[6] = { 0.0f };`
- L34 _public member_ `float FocalLength = 0.0f;`

#### struct `FMessageHash`  
`struct FMessageHash`  
_L37-47_
- L39 _public member_ `TArray<uint8> Hash;`
- L41 _public function_ `FMessageHash(TArray<uint8> InArray)`
- L43 _public function_ `bool operator==(const FMessageHash& OtherMessage) const`

#### enum `EMasterLockitMessageType`  
`enum class EMasterLockitMessageType : uint8`  
_L54-67_
- L56 _public enumerator_ `ClientToServerDataRequest = 0x01`
- L57 _public enumerator_ `ClientToServerNotification = 0x02`
- L58 _public enumerator_ `ClientToServerAcknowledge = 0x03`
- L59 _public enumerator_ `ClientToServerNegativeAcknowledge = 0x04`
- L60 _public enumerator_ `ClientToServerHandshake = 0x0F`
- L62 _public enumerator_ `ServerToClientDataRequest = 0x11`
- L63 _public enumerator_ `ServerToClientNotification = 0x12`
- L64 _public enumerator_ `ServerToClientAcknowledge = 0x13`
- L65 _public enumerator_ `ServerToClientNegativeAcknowledge = 0x14`
- L66 _public enumerator_ `ServerToClientHandshake = 0x1F`

#### enum `EServerHandshakeMessageCode`  
`enum class EServerHandshakeMessageCode : uint8`  
_L69-74_
- L71 _public enumerator_ `Challenge = 0x00`
- L72 _public enumerator_ `Success = 0x01`
- L73 _public enumerator_ `Failure = 0x02`

#### enum `EServerDataRequestMessageCode`  
`enum class EServerDataRequestMessageCode : uint8`  
_L76-80_
- L78 _public enumerator_ `DataEvent = 0x01`
- L79 _public enumerator_ `Ping = 0x02`

#### enum `EServerNotificationMessageCode`  
`enum class EServerNotificationMessageCode : uint8`  
_L82-88_
- L84 _public enumerator_ `DeviceAppeared = 0x01`
- L85 _public enumerator_ `DeviceDisappeared = 0x02`
- L86 _public enumerator_ `DeviceMetaEvent = 0x04`
- L87 _public enumerator_ `VolatileDataEvent = 0x05`

#### enum `EClientDataRequestMessageCode`  
`enum class EClientDataRequestMessageCode : uint8`  
_L90-108_
- L92 _public enumerator_ `SubscribeDataUpdates = 0x01`
- L93 _public enumerator_ `UnsubscribeDataUpdates = 0x02`
- L94 _public enumerator_ `SubscribeDeviceUpdates = 0x03`
- L95 _public enumerator_ `UnsubscribeDeviceUpdates = 0x04`
- L96 _public enumerator_ `REGISTER_AS_DEVICE = 0x05`
- L97 _public enumerator_ `UnregisterAsDevice = 0x06`
- L98 _public enumerator_ `DataEvent = 0x07`
- L99 _public enumerator_ `FetchClips = 0x08`
- L100 _public enumerator_ `DeleteClips = 0x09`
- L101 _public enumerator_ `Export = 0x0A`
- L102 _public enumerator_ `SubscribeVolatileDataUpdates = 0x0B`
- L103 _public enumerator_ `UnsubscribeVolatileDataUpdates = 0x0C`
- L104 _public enumerator_ `FetechLensData = 0x0D`
- L105 _public enumerator_ `StartCJam = 0x0E`
- L106 _public enumerator_ `RenameDevice = 0x0F`
- L107 _public enumerator_ `RemoveDevice = 0x10`

#### enum `EClientNotificationMessageCode`  
`enum class EClientNotificationMessageCode : uint8`  
_L110-113_
- L112 _public enumerator_ `DeviceMetaEvent = 0x01`

#### enum `EMasterLockitDeviceType`  
`enum class EMasterLockitDeviceType : uint8`  
_L115-125_
- L117 _public enumerator_ `Unknown = 0x00`
- L118 _public enumerator_ `Camera = 0x01`
- L119 _public enumerator_ `SoundRecorder = 0x02`
- L120 _public enumerator_ `TimecodeGenerator = 0x03`
- L121 _public enumerator_ `SlateInfoDevice = 0x04`
- L122 _public enumerator_ `Slate = 0x05`
- L123 _public enumerator_ `Storage = 0x06`
- L124 _public enumerator_ `Lens = 0x07`

#### enum `EMasterLockitUnitType`  
`enum class EMasterLockitUnitType : uint8`  
_L127-132_
- L129 _public enumerator_ `Unknown = 0x00`
- L130 _public enumerator_ `Imperial = 0x01`
- L131 _public enumerator_ `Metric = 0x02`

#### enum `EMasterLockitLensType`  
`enum class EMasterLockitLensType : uint8`  
_L134-139_
- L136 _public enumerator_ `Unknown = 0x00`
- L137 _public enumerator_ `Prime = 0x01`
- L138 _public enumerator_ `Zoom = 0x02`

#### struct `FMasterLockitDevice`  
`struct FMasterLockitDevice`  
_L141-162_
- L143 _public member_ `uint64 DeviceID = 0x00;`
- L144 _public member_ `EMasterLockitDeviceType DeviceType = EMasterLockitDeviceType::Unknown;`
- L147 _public member_ `bool bHasAppeared = false;` — Whether the MasterLockit has sent a DeviceAppeared message about this device yet
- L150 _public member_ `static const FString ZeissLensName;`
- L152 _public member_ `FString ManufacturerName;`
- L153 _public member_ `FString LensName;`
- L154 _public member_ `FString SerialNumber;`
- L156 _public member_ `uint16 FirmwareMajorVersion = 0;`
- L157 _public member_ `uint16 FirmwareMinorVersion = 0;`
- L159 _public member_ `EMasterLockitUnitType UnitType = EMasterLockitUnitType::Unknown;`
- L160 _public member_ `EMasterLockitLensType LensType = EMasterLockitLensType::Unknown;`

#### struct `FZeissRawPacket`  
`struct FZeissRawPacket`  
_L164-189_
- L166 _public member_ `static const uint32 NumFocusDistanceBytes = 4;`
- L167 _public member_ `static const uint32 NumApertureBytes = 2;`
- L168 _public member_ `static const uint32 NumHorizontalFOVBytes = 2;`
- L169 _public member_ `static const uint32 NumEntrancePupilBytes = 2;`
- L170 _public member_ `static const uint32 NumShadingBytes = 12;`
- L171 _public member_ `static const uint32 NumDistortionBytes = 12;`
- L173 _public member_ `TArray<uint8> RawFocusDistance;`
- L174 _public member_ `TArray<uint8> RawAperture;`
- L175 _public member_ `TArray<uint8> RawHorizontalFOV;`
- L176 _public member_ `TArray<uint8> RawEntrancePupilPosition;`
- L177 _public member_ `TArray<uint8> RawShadingData;`
- L178 _public member_ `TArray<uint8> RawDistortionData;`
- L180 _public function_ `FZeissRawPacket()`

#### struct `FMasterLockitProtocol`  
`struct FMasterLockitProtocol`  
_L191-214_
- L193 _public member_ `static const FString CommonCategoryString;`
- L194 _public member_ `static const FString ConnectedStatusString;`
- L196 _public member_ `static const FString VendorDataCategoryString;`
- L197 _public member_ `static const FString ManufacturerNameString;`
- L199 _public member_ `static const FString UnitTypeString;`
- L200 _public member_ `static const FString ImperialUnitString;`
- L201 _public member_ `static const FString MetricUnitString;`
- L203 _public member_ `static const FString SerialNumberString;`
- L204 _public member_ `static const FString LensTypeNameString;`
- L205 _public member_ `static const FString FirmwareVersionString;`
- L207 _public member_ `static const FString LensTypeString;`
- L208 _public member_ `static const FString PrimeLensString;`
- L209 _public member_ `static const FString ZoomLensString;`
- L211 _public member_ `static const FString FrameRateString;`
- L212 _public member_ `static const FString FrameRateDelimiter;`
- L213 _public member_ `static const FString DropFrameRateString;`

#### class `FMasterLockitMessageThread`  
`class FMasterLockitMessageThread : public FRunnable`  
_L216-294_
- inherits: `FRunnable`
- L220 _public prototype_ `FMasterLockitMessageThread(FSocket* InSocket);`
- L221 _public prototype_ `~FMasterLockitMessageThread();`
- L223 _public prototype_ `void Start();`
- L230 _public function_ `FOnFrameDataReady& OnFrameDataReady_AnyThread()` — Returns a delegate that is executed when frame data is ready. @return The delegate.
- L235 _public function_ `FOnHandshakeEstablished& OnHandshakeEstablished_AnyThread()`
- L243 _public prototype_ `virtual bool Init() override;`
- L244 _public prototype_ `virtual uint32 Run() override;`
- L245 _public prototype_ `virtual void Stop() override;`
- L250 _private prototype_ `void GenerateFrameRateMap();`
- L252 _private prototype_ `void ParsePacket(FArrayReader& InData);`
- L254 _private prototype_ `void InitiateHandshake();`
- L256 _private prototype_ `void SendMessageToServer(const FArrayWriter InMessageToSend);`
- L257 _private prototype_ `void AcknowledgeMessageFromServer(const TArray<uint8> InMessageFromServer, const uint32 InServerMessageLength);`
- L259 _private prototype_ `void HashDataRequestMessage(const FArrayWriter InMessage, const FString InRequestName);`
- L261 _private prototype_ `void SubscribeToDeviceMetadataUpdates(const EMasterLockitDeviceType InDeviceType);`
- L262 _private prototype_ `void SubscribeToVolatileDataUpdates(uint64 InDeviceID, const EMasterLockitDeviceType InDeviceType);`
- L264 _private prototype_ `void ParseZeissLensData(FArrayReader& InData, const FMasterLockitDevice& Device);`
- L268 _private member_ `FSocket* const Socket;`
- L269 _private member_ `TUniquePtr<FRunnableThread> Thread;`
- L270 _private member_ `bool bIsThreadRunning = false;`
- L272 _private member_ `TMap<FMessageHash, FString> DataRequests;`
- L273 _private member_ `TMap<uint64, FMasterLockitDevice> DetectedDevices;`
- L275 _private member_ `TMap<FString, FFrameRate> FrameRates;`
- L276 _private member_ `FFrameRate MasterLockitFrameRate = { 24, 0 };`
- L277 _private member_ `bool bIsDropFrameRate = false;`
- L279 _private member_ `FOnHandshakeEstablished HandshakeEstablishedDelegate;`
- L280 _private member_ `FOnFrameDataReady FrameDataReadyDelegate;`
- L283 _private member_ `FArrayReader Packet;` — Pre-allocated space to copy the data for one MasterLockit packet into
- L286 _private member_ `FZeissRawPacket ZeissRawPacket;` — Pre-allocated space to read raw (unparsed) Zeiss lens data into
- L290 _private member_ `static constexpr uint32 ReceiveBufferSize = 1024 * 32;` — In practice, 32KB is more than enough space to hold as much data as the socket can send at one time
- L292 _private member_ `static constexpr uint32 ThreadStackSize = 1024 * 128;`

#### Free symbols / members of external scopes

- L16 _typedef_ `typedef FBufferArchive FArrayWriter;`
- L20 _delegate_ `DECLARE_DELEGATE_OneParam(FOnFrameDataReady, FLensPacket InData);`
- L20 _prototype_ `DECLARE_DELEGATE_OneParam(FOnFrameDataReady, FLensPacket InData);`
- L21 _delegate_ `DECLARE_DELEGATE(FOnHandshakeEstablished);`
- L21 _prototype_ `DECLARE_DELEGATE(FOnHandshakeEstablished);`
- L49 _function_ `FORCEINLINE uint32 GetTypeHash(const FMessageHash& MessageHash)`

### `Plugins/VirtualProduction/LiveLinkMasterLockit/Source/LiveLinkMasterLockit/Public/LiveLinkMasterLockitConnectionSettings.h` (Public)


#### struct `FLiveLinkMasterLockitConnectionSettings`  
`struct FLiveLinkMasterLockitConnectionSettings`  
_L8-17_
- reflection: `USTRUCT()`
- L13 _public member_ `FString IPAddress = TEXT("0.0` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L16 _public member_ `FName SubjectName = TEXT("Mas` — `UPROPERTY(EditAnywhere, Category = "Settings")`

### `Plugins/VirtualProduction/LiveLinkMasterLockit/Source/LiveLinkMasterLockit/Public/LiveLinkMasterLockitFactory.h` (Public)


#### class `ULiveLinkMasterLockitSourceFactory`  
`class ULiveLinkMasterLockitSourceFactory : public ULiveLinkSourceFactory`  
_L13-32_
- reflection: `UCLASS()`
- inherits: `ULiveLinkSourceFactory`
- L16 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(TSharedPtr<SWidget>, FBuildCreationPanelDelegate, const ULiveLinkMasterLockitSourceFactory*, FOnLiveLinkSourceCreated);`
- L17 _public member_ `static FBuildCreationPanelDelegate OnBuildCreationPanel;`
- L23 _public prototype_ `virtual FText GetSourceDisplayName() const;`
- L24 _public prototype_ `virtual FText GetSourceTooltip() const;`
- L26 _public function_ `virtual EMenuType GetMenuType() const override`
- L27 _public prototype_ `virtual TSharedPtr<SWidget> BuildCreationPanel(FOnLiveLinkSourceCreated OnLiveLinkSourceCreated) const override;`
- L28 _public prototype_ `virtual TSharedPtr<ILiveLinkSource> CreateSource(const FString& ConnectionString) const override;`
- L31 _public prototype_ `static FString CreateConnectionString(const FLiveLinkMasterLockitConnectionSettings& Settings);`

#### Free symbols / members of external scopes

- L16 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(TSharedPtr<SWidget>, FBuildCreationPanelDelegate, const ULiveLinkMasterLockitSourceFactory*, FOnLiveLinkSourceCreated);`
