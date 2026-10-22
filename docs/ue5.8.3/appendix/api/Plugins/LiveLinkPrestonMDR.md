# Plugins / LiveLinkPrestonMDR

- module root: `Plugins/VirtualProduction/LiveLinkPrestonMDR/Source/LiveLinkPrestonMDR`
- headers: 7; symbols: 238
- symbol kinds: class=5, delegate=5, enum=7, enumerator=38, function=11, member=106, prototype=56, struct=10
- PrivateDependencyModuleNames: Core, CoreUObject, Json, Networking, Sockets
- PublicDependencyModuleNames: LiveLinkInterface

### `Plugins/VirtualProduction/LiveLinkPrestonMDR/Source/LiveLinkPrestonMDR/Private/LiveLinkPrestonMDRRole.h` (Private)


#### class `ULiveLinkPrestonMDRRole`  
`class ULiveLinkPrestonMDRRole : public ULiveLinkCameraRole`  
_L13-27_
- reflection: `UCLASS(BlueprintType, meta = (DisplayName = "Preston MDR Role"))`
- inherits: `ULiveLinkCameraRole`
- desc: Role associated with Preston MDR data
- L19 _public prototype_ `virtual UScriptStruct* GetStaticDataStruct() const override;`
- L20 _public prototype_ `virtual UScriptStruct* GetFrameDataStruct() const override;`
- L21 _public prototype_ `virtual UScriptStruct* GetBlueprintDataStruct() const override;`
- L23 _public prototype_ `virtual bool InitializeBlueprintData(const FLiveLinkSubjectFrameData& InSourceData, FLiveLinkBlueprintDataStruct& OutBlueprintData) const override;`
- L25 _public prototype_ `virtual FText GetDisplayName() const override;`

### `Plugins/VirtualProduction/LiveLinkPrestonMDR/Source/LiveLinkPrestonMDR/Private/LiveLinkPrestonMDRSource.h` (Private)


#### enum `EPrestonSourceStatus`  
`enum class EPrestonSourceStatus : uint8`  
_L16-25_
- L18 _public enumerator_ `NotConnected`
- L19 _public enumerator_ `WaitingToConnect`
- L20 _public enumerator_ `ConnectedActive`
- L21 _public enumerator_ `ConnectedIdle`
- L22 _public enumerator_ `ConnectionFailed`
- L23 _public enumerator_ `ConnectionLost`
- L24 _public enumerator_ `ShuttingDown`

#### class `FLiveLinkPrestonMDRSource`  
`class FLiveLinkPrestonMDRSource : public ILiveLinkSource`  
_L27-84_
- inherits: `ILiveLinkSource`
- L31 _public prototype_ `FLiveLinkPrestonMDRSource(FLiveLinkPrestonMDRConnectionSettings ConnectionSettings);`
- L32 _public prototype_ `~FLiveLinkPrestonMDRSource();`
- L35 _public prototype_ `virtual void ReceiveClient(ILiveLinkClient* InClient, FGuid InSourceGuid) override;`
- L36 _public prototype_ `virtual void Update() override;`
- L37 _public prototype_ `virtual bool IsSourceStillValid() const override;`
- L39 _public prototype_ `virtual bool RequestSourceShutdown() override;`
- L41 _public prototype_ `virtual FText GetSourceType() const override;`
- L42 _public function_ `virtual FText GetSourceMachineName() const override`
- L43 _public prototype_ `virtual FText GetSourceStatus() const override;`
- L45 _public function_ `virtual TSubclassOf<ULiveLinkSourceSettings> GetSettingsClass() const`
- L47 _public prototype_ `virtual void InitializeSettings(ULiveLinkSourceSettings* Settings) override;`
- L48 _public prototype_ `virtual void OnSettingsChanged(ULiveLinkSourceSettings* Settings, const FPropertyChangedEvent& PropertyChangedEvent) override;`
- L52 _private prototype_ `void OpenConnection();`
- L53 _private prototype_ `void OnFrameDataReady(FLensDataPacket InData);`
- L54 _private prototype_ `void OnStatusChanged(FMDR3Status InStatus);`
- L55 _private prototype_ `void OnConnectionLost();`
- L56 _private prototype_ `void OnConnectionFailed();`
- L57 _private prototype_ `void UpdateStaticData();`
- L58 _private prototype_ `bool ShutdownMessageThreadAndSocket();`
- L60 _private member_ `ILiveLinkClient* Client = nullptr;`
- L61 _private member_ `FSocket* Socket = nullptr;`
- L62 _private member_ `ISocketSubsystem* SocketSubsystem = nullptr;`
- L64 _private member_ `FLiveLinkPrestonMDRConnectionSettings ConnectionSettings;`
- L65 _private member_ `FLiveLinkSubjectKey SubjectKey;`
- L66 _private member_ `FText SourceMachineName;`
- L68 _private member_ `TObjectPtr<ULiveLinkPrestonMDRSourceSettings> SavedSourceSettings = nullptr;`
- L70 _private member_ `TUniquePtr<FPrestonMDRMessageThread> MessageThread;`
- L72 _private member_ `FCriticalSection PrestonSourceCriticalSection;`
- L74 _private member_ `std::atomic<double> LastTimeDataReceived;`
- L75 _private member_ `double MessageThreadShutdownTime;`
- L77 _private member_ `EPrestonSourceStatus SourceStatus = EPrestonSourceStatus::NotConnected;`
- L79 _private member_ `FMDR3Status LatestMDRStatus;`
- L82 _private member_ `const float DataReceivedTimeout = 1.0f;`
- L83 _private member_ `const float MessageThreadShutdownTimeout = 2.0f;`

### `Plugins/VirtualProduction/LiveLinkPrestonMDR/Source/LiveLinkPrestonMDR/Private/LiveLinkPrestonMDRSourceSettings.h` (Private)


#### struct `FEncoderRange`  
`struct FEncoderRange`  
_L11-22_
- reflection: `USTRUCT()`
- L17 _public member_ `uint16 Min = 0x0000;` — `UPROPERTY(EditAnywhere, Category = "Encoder Data")` — Minimum raw encoder value
- L21 _public member_ `uint16 Max = 0xFFFF;` — `UPROPERTY(EditAnywhere, Category = "Encoder Data")` — Maximum raw encoder value

#### enum `EFIZDataMode`  
`enum class EFIZDataMode : uint8`  
_L25-29_
- reflection: `UENUM()`
- L27 _public enumerator_ `EncoderData = 0`
- L28 _public enumerator_ `CalibratedData = 1`

#### class `ULiveLinkPrestonMDRSourceSettings`  
`class ULiveLinkPrestonMDRSourceSettings : public ULiveLinkSourceSettings`  
_L32-52_
- reflection: `UCLASS()`
- inherits: `ULiveLinkSourceSettings`
- L39 _public member_ `EFIZDataMode IncomingDataMode = EFIZDataMode::EncoderData;` — `UPROPERTY(EditAnywhere, Category = "Source")` — The mode in which the Preston MDR is configured to send FIZ data (pre-calibrated or raw encoder positions)
- L43 _public member_ `FEncoderRange FocusEncoderRange;` — `UPROPERTY(EditAnywhere, Category = "Source")` — Raw focus encoder range
- L47 _public member_ `FEncoderRange IrisEncoderRange;` — `UPROPERTY(EditAnywhere, Category = "Source")` — Raw iris encoder range
- L51 _public member_ `FEncoderRange ZoomEncoderRange;` — `UPROPERTY(EditAnywhere, Category = "Source")` — Raw zoom encoder range

### `Plugins/VirtualProduction/LiveLinkPrestonMDR/Source/LiveLinkPrestonMDR/Private/LiveLinkPrestonMDRTypes.h` (Private)


#### struct `FLiveLinkPrestonMDRStaticData`  
`struct FLiveLinkPrestonMDRStaticData : public FLiveLinkCameraStaticData`  
_L13-16_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FLiveLinkCameraStaticData`
- desc: Struct for static Preston MDR data

#### struct `FLiveLinkPrestonMDRFrameData`  
`struct FLiveLinkPrestonMDRFrameData : public FLiveLinkCameraFrameData`  
_L22-37_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FLiveLinkCameraFrameData`
- desc: Struct for dynamic (per-frame) Preston MDR data
- L28 _public member_ `uint16 RawFocusEncoderValue = 0;` — `UPROPERTY(VisibleAnywhere, Category = "Raw Encoder Values")` — Raw encoder value for focus motor
- L32 _public member_ `uint16 RawIrisEncoderValue = 0;` — `UPROPERTY(VisibleAnywhere, Category = "Raw Encoder Values")` — Raw encoder value for iris motor
- L36 _public member_ `uint16 RawZoomEncoderValue = 0;` — `UPROPERTY(VisibleAnywhere, Category = "Raw Encoder Values")` — Raw encoder value for zoom motor

#### struct `FLiveLinkPrestonMDRBlueprintData`  
`struct FLiveLinkPrestonMDRBlueprintData : public FLiveLinkBaseBlueprintData`  
_L43-54_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FLiveLinkBaseBlueprintData`
- desc: Facility structure to handle Preston MDR data in blueprint
- L49 _public member_ `FLiveLinkPrestonMDRStaticData StaticData;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink")` — Static data that should not change every frame
- L53 _public member_ `FLiveLinkPrestonMDRFrameData FrameData;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink")` — Dynamic data that can change every frame

### `Plugins/VirtualProduction/LiveLinkPrestonMDR/Source/LiveLinkPrestonMDR/Private/PrestonMDRMessageThread.h` (Private)


#### enum `EDataMessageBitmask`  
`enum class EDataMessageBitmask : uint8`  
_L20-30_
- L22 _public enumerator_ `Iris = 0x01`
- L23 _public enumerator_ `Focus = 0x02`
- L24 _public enumerator_ `Zoom = 0x04`
- L25 _public enumerator_ `AUX = 0x08`
- L26 _public enumerator_ `Speed = 0x10`
- L27 _public enumerator_ `Distance = 0x20`
- L28 _public enumerator_ `Mode = 0x40`
- L29 _public enumerator_ `Status = 0x80`

#### enum `EAuxMotorAssignment`  
`enum EAuxMotorAssignment : uint8`  
_L32-44_
- L34 _public enumerator_ `None = 0`
- L35 _public enumerator_ `HandUnit3Focus = 1`
- L36 _public enumerator_ `HandUnit3Iris = 2`
- L37 _public enumerator_ `HandUnit3Zoom = 3`
- L38 _public enumerator_ `WirelessFocus = 4`
- L39 _public enumerator_ `WirelessIris = 5`
- L40 _public enumerator_ `RadioMF = 6`
- L41 _public enumerator_ `AnalogFocus = 7`
- L42 _public enumerator_ `AnalogIris = 8`
- L43 _public enumerator_ `AnalogZoom = 9`

#### enum `EZoomControl`  
`enum class EZoomControl : uint8`  
_L46-50_
- L48 _public enumerator_ `Velocity = 0`
- L49 _public enumerator_ `Position = 1`

#### enum `ECameraRunStop`  
`enum class ECameraRunStop : uint8`  
_L52-56_
- L54 _public enumerator_ `Stop = 0`
- L55 _public enumerator_ `Run = 1`

#### enum `EMDRCommand`  
`enum class EMDRCommand : uint8`  
_L58-67_
- L60 _public enumerator_ `Null = 0x00`
- L61 _public enumerator_ `Status = 0x02`
- L62 _public enumerator_ `Data = 0x04`
- L63 _public enumerator_ `Time = 0x05`
- L64 _public enumerator_ `TimeCodeStatus = 0x0B`
- L65 _public enumerator_ `Info = 0x0E`
- L66 _public enumerator_ `Error = 0x11`

#### struct `FMDRProtocol`  
`struct FMDRProtocol`  
_L70-104_
- desc: Preston MDR Protocol Constants
- L73 _public member_ `static const uint8 STX;` — ASCII Constants
- L74 _public member_ `static const uint8 ETX;`
- L75 _public member_ `static const uint8 ACK;`
- L78 _public member_ `static constexpr uint32 ACKByte = 0;`
- L79 _public member_ `static constexpr uint32 STXByte = ACKByte + 1;`
- L80 _public member_ `static constexpr uint32 CommandByte = STXByte + 1;`
- L81 _public member_ `static constexpr uint32 PayloadLengthByte = CommandByte + 2;`
- L84 _public member_ `static constexpr uint32 FirstPayloadByte = PayloadLengthByte + 2;`
- L87 _public member_ `static constexpr uint32 ETXByte = -1;`
- L88 _public member_ `static constexpr uint32 ChecksumByte = ETXByte - 2;`
- L91 _public member_ `static constexpr uint32 HeaderSize = 6;`
- L92 _public member_ `static constexpr uint32 FooterSize = 3;`
- L95 _public member_ `static const uint8 StatusMessageLength;` — These values represent the static length of each request message type
- L96 _public member_ `static const uint8 DataMessageLength;`
- L97 _public member_ `static const uint8 TimeMessageLength;`
- L98 _public member_ `static const uint8 TimecodeMessageLength;`
- L101 _public member_ `static constexpr uint32 NumPayloadBytesInStatusMessage = 2;` — These values represent the static length of the payload in each message type
- L102 _public member_ `static constexpr uint32 NumPayloadBytesInTimeMessage = 9;`
- L103 _public member_ `static constexpr uint32 NumPayloadBytesInTimecodeMessage = 1;`

#### struct `FLensDataPacket`  
`struct FLensDataPacket`  
_L106-114_
- L108 _public member_ `FQualifiedFrameTime FrameTime;`
- L110 _public member_ `float Focus = 0.0f;`
- L111 _public member_ `float Iris = 0.0f;`
- L112 _public member_ `float Zoom = 0.0f;`
- L113 _public member_ `float Aux = 0.0f;`

#### struct `FMDR3Status`  
`struct FMDR3Status`  
_L116-128_
- L118 _public member_ `bool bIsAuxMotorSet = false;`
- L119 _public member_ `bool bIsZoomMotorSet = false;`
- L120 _public member_ `bool bIsFocusMotorSet = false;`
- L121 _public member_ `bool bIsIrisMotorSet = false;`
- L122 _public member_ `bool bIsCameraSelected = false;`
- L123 _public member_ `ECameraRunStop CameraRunStop = ECameraRunStop::Stop;`
- L124 _public member_ `bool bIsFocusAssistDetected = false;`
- L125 _public member_ `bool bIsFocusCalibrated = false;`
- L126 _public member_ `EAuxMotorAssignment AuxMotorAssignment = EAuxMotorAssignment::None;`
- L127 _public member_ `EZoomControl ZoomControl = EZoomControl::Position;`

#### struct `FDataMessageDescription`  
`struct FDataMessageDescription`  
_L131-141_
- desc: Settings used to encode which pieces of data the MDR should send in a "DATA" message
- L133 _public member_ `bool bContainsMDRStatus = false;`
- L134 _public member_ `EFIZDataMode LensDataMode = EFIZDataMode::EncoderData;`
- L135 _public member_ `bool bContainsDistance = false;`
- L136 _public member_ `bool bContainsSpeed = false;`
- L137 _public member_ `bool bContainsAux = false;`
- L138 _public member_ `bool bContainsZoom = false;`
- L139 _public member_ `bool bContainsFocus = false;`
- L140 _public member_ `bool bContainsIris = false;`

#### struct `FAsciiByte`  
`struct FAsciiByte`  
_L143-155_
- L145 _public member_ `uint8 ByteHigh = 0;`
- L146 _public member_ `uint8 ByteLow = 0;`
- L148 _public function_ `FAsciiByte()`
- L150 _public function_ `FAsciiByte(const uint8* const InData)`

#### class `FPrestonMDRMessageThread`  
`class FPrestonMDRMessageThread : public FRunnable`  
_L157-283_
- inherits: `FRunnable`
- L161 _public prototype_ `FPrestonMDRMessageThread(FSocket* InSocket);`
- L162 _public prototype_ `~FPrestonMDRMessageThread();`
- L164 _public prototype_ `void Start();`
- L166 _public function_ `bool IsThreadRunning() const`
- L167 _public function_ `bool IsFinished() const`
- L174 _public function_ `FOnFrameDataReady& OnFrameDataReady()` — Returns a delegate that is executed when frame data is ready. @return The delegate.
- L179 _public function_ `FOnStatusChanged& OnStatusChanged()`
- L184 _public function_ `FOnConnectionLost& OnConnectionLost()`
- L189 _public function_ `FOnConnectionFailed& OnConnectionFailed()`
- L197 _public prototype_ `virtual bool Init() override;`
- L198 _public prototype_ `virtual uint32 Run() override;`
- L199 _public prototype_ `virtual void Stop() override;`
- L202 _public prototype_ `void SetSocket(FSocket* InSocket);`
- L204 _public prototype_ `void SoftReset();`
- L206 _public prototype_ `void ForceKill();`
- L208 _public prototype_ `void SetIncomingDataMode_GameThread(EFIZDataMode InDataMode);`
- L212 _private prototype_ `void SendNextCommandToServer();`
- L214 _private prototype_ `void ParseMessageFromServer(const uint8* const InPacketData, const uint32 InNumPacketBytes);`
- L215 _private prototype_ `void SendMessageToServer(const uint8* const InMessageToSend, const int32 InNumBytesToSend);`
- L217 _private prototype_ `void ParseStatusMessage(const uint8* const InData);`
- L218 _private prototype_ `void ParseDataMessage(const uint8* const InData, const uint8 InNumDataBytes);`
- L219 _private prototype_ `void ParseTimeMessage(const uint8* const InData);`
- L220 _private prototype_ `void ParseTimecodeStatusMessage(const uint8* const InData);`
- L222 _private prototype_ `void BuildStaticMessages();`
- L223 _private prototype_ `void UpdateDataDescriptionMessage_AnyThread();`
- L224 _private prototype_ `void InitializeCommandQueue();`
- L225 _private prototype_ `void HardReset();`
- L228 _private prototype_ `FAsciiByte HexToAscii(const uint8 InHexByte);` — Conversion functions to translate between data bytes and ASCII-encoded bytes
- L229 _private prototype_ `uint8 AsciiToHex(const FAsciiByte InAsciiByte);`
- L230 _private prototype_ `uint8 AsciiToDec(const FAsciiByte InAsciiByte);`
- L232 _private prototype_ `uint8 ComputeChecksum(const uint8* const InData, const uint8 InDataLength);`
- L233 _private prototype_ `uint8 GetDataDescritionSettings();`
- L236 _private member_ `FSocket* Socket;`
- L238 _private member_ `TUniquePtr<FRunnableThread> Thread;`
- L239 _private member_ `std::atomic<bool> bIsThreadRunning = false;`
- L241 _private member_ `FOnFrameDataReady FrameDataReadyDelegate;`
- L242 _private member_ `FOnStatusChanged StatusChangedDelegate;`
- L243 _private member_ `FOnConnectionLost ConnectionLostDelegate;`
- L244 _private member_ `FOnConnectionFailed ConnectionFailedDelegate;`
- L246 _private member_ `FCriticalSection PrestonCriticalSection;`
- L248 _private member_ `TQueue<EMDRCommand> CommandQueue;`
- L249 _private member_ `TArray<uint8> StatusRequestMessage;`
- L250 _private member_ `TArray<uint8> DataRequestMessage;`
- L251 _private member_ `TArray<uint8> TimeRequestMessage;`
- L252 _private member_ `TArray<uint8> TimecodeRequestMessage;`
- L254 _private member_ `FMDR3Status MDR3Status;`
- L255 _private member_ `FLensDataPacket LensData;`
- L257 _private member_ `FFrameRate MDRFrameRate = { 24, 1 };`
- L258 _private member_ `bool bIsDropFrameRate = false;`
- L260 _private member_ `FDataMessageDescription DataDescriptionSettings;`
- L261 _private member_ `bool bIsFrameDataReady = false;`
- L262 _private member_ `bool bIsFrameTimeReady = false;`
- L263 _private member_ `bool bReadyToSendCommandToServer = false;`
- L265 _private member_ `TArray<uint16> ParsedFIZData;`
- L267 _private member_ `double LastTimeDataReceived = 0.0;`
- L269 _private member_ `bool bSoftResetTriggered = false;`
- L270 _private member_ `bool bHardResetTriggered = false;`
- L272 _private member_ `std::atomic<bool> bIsFinished = true;`
- L273 _private member_ `std::atomic<bool> bForceKillThread = false;`
- L276 _private member_ `static constexpr uint32 MaximumMDRMessageLength = 512;`
- L278 _private member_ `static constexpr uint32 ThreadStackSize = 1024 * 128;`
- L280 _private member_ `static constexpr float ConnectionWaitInterval = 0.02f;` — 20ms
- L281 _private member_ `static constexpr double ConnectionTimeout = 5.0;` — 3sec
- L282 _private member_ `static constexpr double DataReceivedTimeout = 2.0;` — 2sec

#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_DELEGATE_OneParam(FOnFrameDataReady, FLensDataPacket InData);`
- L15 _prototype_ `DECLARE_DELEGATE_OneParam(FOnFrameDataReady, FLensDataPacket InData);`
- L16 _delegate_ `DECLARE_DELEGATE_OneParam(FOnStatusChanged, FMDR3Status InStatus);`
- L16 _prototype_ `DECLARE_DELEGATE_OneParam(FOnStatusChanged, FMDR3Status InStatus);`
- L17 _delegate_ `DECLARE_DELEGATE(FOnConnectionLost) DECLARE_DELEGATE(FOnConnectionFailed) enum class EDataMessageBitmask : uint8 { Iris = 0x01, Focus = 0x02, Zoom = 0x04, AUX = 0x08, Speed = 0x10, Distance = 0x20, Mode = 0x40, Status = 0x80 };`
- L18 _delegate_ `DECLARE_DELEGATE(FOnConnectionFailed) enum class EDataMessageBitmask : uint8 { Iris = 0x01, Focus = 0x02, Zoom = 0x04, AUX = 0x08, Speed = 0x10, Distance = 0x20, Mode = 0x40, Status = 0x80 };`

### `Plugins/VirtualProduction/LiveLinkPrestonMDR/Source/LiveLinkPrestonMDR/Public/LiveLinkPrestonMDRConnectionSettings.h` (Public)


#### struct `FLiveLinkPrestonMDRConnectionSettings`  
`struct FLiveLinkPrestonMDRConnectionSettings`  
_L8-20_
- reflection: `USTRUCT()`
- L13 _public member_ `FString IPAddress = TEXT("0.0` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L16 _public member_ `uint16 PortNumber = 0;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L19 _public member_ `FName SubjectName = TEXT("Pre` — `UPROPERTY(EditAnywhere, Category = "Settings")`

### `Plugins/VirtualProduction/LiveLinkPrestonMDR/Source/LiveLinkPrestonMDR/Public/LiveLinkPrestonMDRFactory.h` (Public)


#### class `ULiveLinkPrestonMDRSourceFactory`  
`class ULiveLinkPrestonMDRSourceFactory : public ULiveLinkSourceFactory`  
_L13-32_
- reflection: `UCLASS()`
- inherits: `ULiveLinkSourceFactory`
- L16 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(TSharedPtr<SWidget>, FBuildCreationPanelDelegate, const ULiveLinkPrestonMDRSourceFactory*, FOnLiveLinkSourceCreated);`
- L17 _public member_ `static FBuildCreationPanelDelegate OnBuildCreationPanel;`
- L23 _public prototype_ `virtual FText GetSourceDisplayName() const;`
- L24 _public prototype_ `virtual FText GetSourceTooltip() const;`
- L26 _public function_ `virtual EMenuType GetMenuType() const override`
- L27 _public prototype_ `virtual TSharedPtr<SWidget> BuildCreationPanel(FOnLiveLinkSourceCreated OnLiveLinkSourceCreated) const override;`
- L28 _public prototype_ `virtual TSharedPtr<ILiveLinkSource> CreateSource(const FString& ConnectionString) const override;`
- L31 _public prototype_ `static FString CreateConnectionString(const FLiveLinkPrestonMDRConnectionSettings& Settings);`

#### Free symbols / members of external scopes

- L16 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(TSharedPtr<SWidget>, FBuildCreationPanelDelegate, const ULiveLinkPrestonMDRSourceFactory*, FOnLiveLinkSourceCreated);`
