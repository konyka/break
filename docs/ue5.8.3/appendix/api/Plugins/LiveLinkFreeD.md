# Plugins / LiveLinkFreeD

- module root: `Plugins/VirtualProduction/LiveLinkFreeD/Source/LiveLinkFreeD`
- headers: 7; symbols: 107
- symbol kinds: class=5, delegate=2, enum=1, enumerator=6, function=9, member=52, prototype=29, struct=3
- PrivateDependencyModuleNames: CoreUObject, Engine, Slate, SlateCore
- PublicDependencyModuleNames: Core, LiveLinkInterface, Messaging, Networking, Sockets, UdpMessaging

### `Plugins/VirtualProduction/LiveLinkFreeD/Source/LiveLinkFreeD/Private/LiveLinkFreeDConnectionSettings.h` (Private)


#### struct `FLiveLinkFreeDConnectionSettings`  
`struct FLiveLinkFreeDConnectionSettings`  
_L8-28_
- reflection: `USTRUCT()`
- L19 _public member_ `FString IPAddress = TEXT("0.0` — `UPROPERTY(EditAnywhere, Category = "Connection Settings", meta = (DisplayName = "Local IP Address"))` — Local interface IP address. 0.0.0.0 (INADDR_ANY) binds to all local network interfaces.
- L23 _public member_ `uint16 UDPPortNumber = 40000;` — `UPROPERTY(EditAnywhere, Category = "Connection Settings", meta = (DisplayName = "UDP Port Number"))` — UDP port number
- L27 _public member_ `FString SubjectName = TEXT("");` — `UPROPERTY(EditAnywhere, Category = "Connection Settings", meta = (DisplayName = "Subject Name"))` — Custom subject name (if empty, defaults to "Camera <Camera ID>")

### `Plugins/VirtualProduction/LiveLinkFreeD/Source/LiveLinkFreeD/Private/LiveLinkFreeDPacketInfo.h` (Private)


#### struct `FreeDPacketDefinition`  
`struct FreeDPacketDefinition`  
_L11-28_
- desc: Free-D protocol packet data definitions as per the official spec: https://www.manualsdir.com/manuals/641433/vinten-radamec-free-d.html
- L13 _public member_ `static const uint8 PacketTypeD1;`
- L14 _public member_ `static const uint8 PacketSizeD1;`
- L16 _public member_ `static const uint8 PacketType;`
- L17 _public member_ `static const uint8 CameraID;`
- L18 _public member_ `static const uint8 Yaw;`
- L19 _public member_ `static const uint8 Pitch;`
- L20 _public member_ `static const uint8 Roll;`
- L21 _public member_ `static const uint8 X;`
- L22 _public member_ `static const uint8 Y;`
- L23 _public member_ `static const uint8 Z;`
- L24 _public member_ `static const uint8 FocalLength;`
- L25 _public member_ `static const uint8 FocusDistance;`
- L26 _public member_ `static const uint8 UserDefined;`
- L27 _public member_ `static const uint8 Checksum;`

### `Plugins/VirtualProduction/LiveLinkFreeD/Source/LiveLinkFreeD/Private/SLiveLinkFreeDSourceFactory.h` (Private)


#### class `SLiveLinkFreeDSourceFactory`  
`class SLiveLinkFreeDSourceFactory : public SCompoundWidget`  
_L19-39_
- inherits: `SCompoundWidget`
- L21 _private function_ `SLATE_BEGIN_ARGS(SLiveLinkFreeDSourceFactory)`
- L23 _private prototype_ `SLATE_EVENT(FOnLiveLinkFreeDConnectionSettingsAccepted, OnConnectionSettingsAccepted) SLATE_END_ARGS() void Construct(const FArguments& Args);`
- L30 _private member_ `FLiveLinkFreeDConnectionSettings ConnectionSettings;`
- L33 _private member_ `TSharedPtr<FStructOnScope> StructOnScope;`
- L34 _private member_ `TSharedPtr<IStructureDetailsView> StructureDetailsView;`
- L37 _private prototype_ `FReply OnSettingsAccepted();`
- L38 _private member_ `FOnLiveLinkFreeDConnectionSettingsAccepted OnConnectionSettingsAccepted;`

#### Free symbols / members of external scopes

- L17 _delegate_ `DECLARE_DELEGATE_OneParam(FOnLiveLinkFreeDConnectionSettingsAccepted, FLiveLinkFreeDConnectionSettings);`
- L17 _prototype_ `DECLARE_DELEGATE_OneParam(FOnLiveLinkFreeDConnectionSettingsAccepted, FLiveLinkFreeDConnectionSettings);`

### `Plugins/VirtualProduction/LiveLinkFreeD/Source/LiveLinkFreeD/Public/LiveLinkFreeD.h` (Public)


#### class `FLiveLinkFreeDModule`  
`class FLiveLinkFreeDModule : public IModuleInterface`  
_L10-22_
- inherits: `IModuleInterface`
- L14 _public function_ `static FLiveLinkFreeDModule& Get()`
- L20 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L21 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogLiveLinkFreeD, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogLiveLinkFreeD, Log, All);`

### `Plugins/VirtualProduction/LiveLinkFreeD/Source/LiveLinkFreeD/Public/LiveLinkFreeDSource.h` (Public)


#### class `FLiveLinkFreeDSource`  
`class FLiveLinkFreeDSource : public ILiveLinkSource, public FRunnable, public TSharedFromThis<FLiveLinkFreeDSource>`  
_L26-120_
- inherits: `ILiveLinkSource,FRunnable,TSharedFromThis<FLiveLinkFreeDSource>`
- L30 _public prototype_ `FLiveLinkFreeDSource(const FLiveLinkFreeDConnectionSettings& ConnectionSettings);`
- L32 _public prototype_ `virtual ~FLiveLinkFreeDSource();`
- L36 _public prototype_ `virtual void ReceiveClient(ILiveLinkClient* InClient, FGuid InSourceGuid) override;`
- L37 _public prototype_ `virtual void InitializeSettings(ULiveLinkSourceSettings* Settings) override;`
- L39 _public prototype_ `virtual bool IsSourceStillValid() const override;`
- L41 _public prototype_ `virtual bool RequestSourceShutdown() override;`
- L43 _public function_ `virtual FText GetSourceType() const override`
- L44 _public function_ `virtual FText GetSourceMachineName() const override`
- L45 _public function_ `virtual FText GetSourceStatus() const override`
- L47 _public function_ `virtual TSubclassOf<ULiveLinkSourceSettings> GetSettingsClass() const override`
- L48 _public prototype_ `virtual void OnSettingsChanged(ULiveLinkSourceSettings* Settings, const FPropertyChangedEvent& PropertyChangedEvent) override;`
- L54 _public function_ `virtual bool Init() override`
- L55 _public prototype_ `virtual uint32 Run() override;`
- L56 _public prototype_ `void Start();`
- L57 _public prototype_ `virtual void Stop() override;`
- L58 _public function_ `virtual void Exit() override`
- L62 _public prototype_ `void UpdateEncoderData(FFreeDEncoderData* InEncoderData);`
- L63 _public prototype_ `void Send(FLiveLinkFrameDataStruct* FrameDataToSend, FName SubjectName);`
- L64 _public prototype_ `float ProcessEncoderData(FFreeDEncoderData& EncoderData, int32 RawEncoderValueInt);`
- L66 _public prototype_ `float Decode_Signed_8_15(uint8* InBytes);`
- L67 _public prototype_ `float Decode_Signed_17_6(uint8* InBytes);`
- L68 _public prototype_ `uint32 Decode_Unsigned_24(uint8* InBytes);`
- L69 _public prototype_ `uint16 Decode_Unsigned_16(uint8* InBytes);`
- L70 _public prototype_ `uint8 CalculateChecksum(uint8* InBytes, uint32 Size);`
- L73 _private member_ `ILiveLinkClient* Client;`
- L76 _private member_ `FGuid SourceGuid;` — Our identifier in LiveLink
- L78 _private member_ `FMessageAddress ConnectionAddress;`
- L80 _private member_ `FText SourceType;`
- L81 _private member_ `FText SourceMachineName;`
- L82 _private member_ `FText SourceStatus;`
- L85 _private member_ `FThreadSafeBool Stopping;` — Threadsafe Bool for terminating the main thread loop
- L88 _private member_ `FRunnableThread* Thread;` — Thread to run socket operations on
- L91 _private member_ `FString ThreadName;` — Name of the sockets thread
- L93 _private member_ `FSocket* Socket;`
- L94 _private member_ `ISocketSubsystem* SocketSubsystem;`
- L95 _private member_ `FIPv4Endpoint DeviceEndpoint;`
- L98 _private member_ `const uint32 ReceiveBufferSize = 1024 * 16;` — Size of receive buffer
- L101 _private member_ `TArray<uint8> ReceiveBuffer;` — Receive buffer for UDP socket
- L104 _private member_ `TSet<FName> EncounteredSubjects;` — List of subjects we've already encountered
- L107 _private member_ `FDelegateHandle DeferredStartDelegateHandle;` — Deferred start delegate handle.
- L110 _private member_ `int32 FrameCounter = 0;` — Frame counter for incoming data packets
- L113 _private member_ `FString CameraSubjectName = TEXT("Cam` — LiveLink subject name for this camera data
- L116 _private member_ `FString CustomSubjectName;` — Custom subject name from connection settings
- L119 _private member_ `ULiveLinkFreeDSourceSettings* SavedSourceSettings = nullptr;` — Pointer to the settings for this source so we don't have to duplicate data

### `Plugins/VirtualProduction/LiveLinkFreeD/Source/LiveLinkFreeD/Public/LiveLinkFreeDSourceFactory.h` (Public)


#### class `ULiveLinkFreeDSourceFactory`  
`class ULiveLinkFreeDSourceFactory : public ULiveLinkSourceFactory`  
_L10-24_
- reflection: `UCLASS()`
- inherits: `ULiveLinkSourceFactory`
- L15 _public prototype_ `virtual FText GetSourceDisplayName() const override;`
- L16 _public prototype_ `virtual FText GetSourceTooltip() const override;`
- L18 _public function_ `virtual EMenuType GetMenuType() const override`
- L19 _public prototype_ `virtual TSharedPtr<SWidget> BuildCreationPanel(FOnLiveLinkSourceCreated OnLiveLinkSourceCreated) const override;`
- L20 _public prototype_ `virtual TSharedPtr<ILiveLinkSource> CreateSource(const FString& ConnectionString) const override;`
- L23 _private prototype_ `void CreateSourceFromSettings(FLiveLinkFreeDConnectionSettings ConnectionSettings, FOnLiveLinkSourceCreated OnSourceCreated) const;`

### `Plugins/VirtualProduction/LiveLinkFreeD/Source/LiveLinkFreeD/Public/LiveLinkFreeDSourceSettings.h` (Public)


#### struct `FFreeDEncoderData`  
`struct FFreeDEncoderData`  
_L10-37_
- reflection: `USTRUCT()`
- L16 _public member_ `bool bIsValid = false;` — `UPROPERTY(EditAnywhere, Category = "Encoder Data")` — Is this encoder data valid?
- L20 _public member_ `bool bInvertEncoder = false;` — `UPROPERTY(EditAnywhere, Category = "Encoder Data", meta = (EditCondition = "bIsValid"))` — Invert the encoder input direction
- L24 _public member_ `bool bUseManualRange = false;` — `UPROPERTY(EditAnywhere, Category = "Encoder Data", meta = (EditCondition = "bIsValid"))` — Use manual Min/Max values for the encoder normalization (normally uses dynamic auto ranging based on inputs)
- L28 _public member_ `int32 Min = 0x00FFFFFF;` — `UPROPERTY(EditAnywhere, Category = "Encoder Data", meta = (ClampMin = 0, ClampMax = 0x00ffffff, EditCondition = "bIsValid && bUseManualRange"))` — Minimum raw encoder value
- L32 _public member_ `int32 Max = 0;` — `UPROPERTY(EditAnywhere, Category = "Encoder Data", meta = (ClampMin = 0, ClampMax = 0x00ffffff, EditCondition = "bIsValid && bUseManualRange"))` — Maximum raw encoder value
- L36 _public member_ `int32 MaskBits = 0x00FFFFFF;` — `UPROPERTY(EditAnywhere, Category = "Encoder Data", meta = (ClampMin = 0, ClampMax = 0x00ffffff, EditCondition = "bIsValid"))` — Mask bits for raw encoder value

#### enum `EFreeDDefaultConfigs`  
`enum class EFreeDDefaultConfigs : uint8`  
_L40-48_
- reflection: `UENUM(BlueprintType)`
- L42 _public enumerator_ `Generic`
- L43 _public enumerator_ `Panasonic`
- L44 _public enumerator_ `Sony`
- L45 _public enumerator_ `Stype UMETA(DisplayName="stYpe")`
- L46 _public enumerator_ `Mosys`
- L47 _public enumerator_ `Ncam`

#### class `ULiveLinkFreeDSourceSettings`  
`class ULiveLinkFreeDSourceSettings : public ULiveLinkSourceSettings`  
_L51-75_
- reflection: `UCLASS()`
- inherits: `ULiveLinkSourceSettings`
- L58 _public member_ `bool bSendExtraMetaData = false;` — `UPROPERTY(EditAnywhere, Category = "Source")` — Send extra string meta data (Camera ID and FrameCounter)
- L62 _public member_ `EFreeDDefaultConfigs DefaultConfig = EFreeDDefaultConfigs::Generic;` — `UPROPERTY(EditAnywhere, Category = "Source")` — Default configurations for specific manufacturers
- L66 _public member_ `FFreeDEncoderData FocusDistanceEncoderData = { true, false, false, 0x00ffffff, 0, 0x00ffffff };` — `UPROPERTY(EditAnywhere, Category = "Source")` — Raw focus distance (in cm) encoder parameters for this camera - 24 bits max
- L70 _public member_ `FFreeDEncoderData FocalLengthEncoderData = { true, false, false, 0x00ffffff, 0, 0x00ffffff };` — `UPROPERTY(EditAnywhere, Category = "Source")` — Raw focal length/zoom (in mm) encoder parameters for this camera - 24 bits max
- L74 _public member_ `FFreeDEncoderData UserDefinedEncoderData = { false, false, false, 0x0000ffff, 0, 0x0000ffff };` — `UPROPERTY(EditAnywhere, Category = "Source")` — Raw user defined/spare data encoder (normally used for Aperture) parameters for this camera - 16 bits max
